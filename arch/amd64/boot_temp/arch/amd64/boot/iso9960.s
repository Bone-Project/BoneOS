


# read_sector:
#
# Reads from the disk and stores it into the 
# buffer specified by the %es segment.
#
# Parameters:
# 
#     - %ax: Segment of buffer to write to
#     - %bx: Lower 32 bit of starting LBA
#     - %cx: Number of sectors to read
#
# Returns:
#       disk address packet's block count field set to number of blocks
#       successfully transferred

read_sector:
	movw %bx, dap_ptr_llba
	movw %cx, dap_ptr_cnum

	lea dap, %si

	movw %ax, dap_ptr_segm

	movb $0x42, %ah
	int $0x13
	jc .bios_error

	ret

.bios_error:
	lea  bios_error_msg, %si
	call puts16
	jmp .


# find_directory_entry:
# 
# Locates a file or directory within the current directory described in
# the buffer located at $DIR_BUFFER_SEGMENT.
# 
# Parameters:
# 
#     - %ax: The address of the name to search for
#     - %bl: The length of the name
#
#	Returns:
#			- sets %al to 1 if the root directory was found

find_directory_entry:
	push    %di

	movw    %ax, %di
	xorw    %ax, %ax
	movw    %ax, %si

.find_directory_entry_loop:
	cmpb    $0, %es:DIR_LENGTH_OFFSET(%si)
	je      .directory_entry_return

	# Check file name size

	xorw    %cx, %cx
	movb    %es:DIR_FILE_ID_LENGTH_OFFSET(%si), %cl

	cmpb    %bl, %cl # cmp size against param (you want the exact one)
	jne     .directory_next_entry

	xorw    %bp, %bp

.directory_strcmp_loop:

	movb    %ds:(%bp,%di), %cl # %cl contains the character from the string
	movb    %es:DIR_FILE_ID_OFFSET(%bp,%si), %ch # %ch contains the character from the directory entry

	test    %cl, %cl
	jz      .directory_strcmp_check # this is a file

	cmpb    $'/', %cl # at root (still check if root dir is what we want)
	je      .directory_strcmp_check

	cmpb    %ch, %cl
	jne     .directory_next_entry

	inc     %bp

	jmp     .directory_strcmp_loop

.directory_strcmp_check:
	test    %ch, %ch
	jz      .directory_entry_found

	movw    %bp, %cx
	 # compare the length of the directory entry name (stored at DIR_FILE_ID_LENGTH_OFFSET) 
	 # with %cl (which now contains the number of characters we've compared).
	cmpb    %es:DIR_FILE_ID_LENGTH_OFFSET(%si), %cl
	je      .directory_entry_found

.directory_next_entry:
	xorw    %cx, %cx

	# Move on to next directory entry

	movb    %es:DIR_LENGTH_OFFSET(%si), %cl
	addw    %cx, %si

	jmp     .find_directory_entry_loop

.directory_entry_found:
	movw    $1, %ax

.directory_entry_return:
	pop     %di
	ret

# read_entry:
# 
# Locates a file on the disk and loads it at the
# address specified by %di.
# 
# Parameters:
#
#     - %ax: Address of the full path to the file 
#						 Expects the path to be a full path, i.e. starting with '/'
#     - %di: Destination segment where to load the file

read_entry:
	push %es
	push %di

	# Store address parameter

	push %ax

	# Store destination parameter
	movw $DIR_BUFFER_SEGMENT, %ax
	push %ax

	call read_root_dir # load root dir into the DIR_BUFFER_SEGMENT

	# %es now *points* to the root directory
	pop  %es # DIR_BUFF_SEG
	pop  %si # Adress of full path (%ax param)

	inc  %si

.read_entry_dir_loop:
	xorw %bx, %bx
	push %si

.read_entry_strlen:
	
	# Determine length of the current path component

	cmpb $0, (%si) # end of file path so go read the file
	je .read_file

	cmpb $'/', (%si) # root just skip
	jne .entry_next_char

	test %bl, %bl # checks for "//" => invalid
	jnz .read_directory

	jmp .

.entry_next_char:
	inc %bl
	inc %si
	jmp .read_entry_strlen

.read_file:
	movb $1, %bh

.read_directory:
	# Read current directory entry
	pop %ax
	push %si

	call find_directory_entry
 	test %ax, %ax
 	jz  .

 	test %bh, %bh # from read_file
 	jz .load_directory

 	# If the current entry describes a file, set the address
.load_file:
	
	movw %si, %di
	pop %si

 	pop %ax

 	push %si
 	movw %di, %si

 	jmp .load_entry

.load_directory:

 	# If the current entry describes a directory, overwrite it
 	movw %es, %ax # overrite with the cur buff that points to curr dir

.load_entry:
 	push %bx

	# Read entry

	movl %es:DIR_EXTR_SEC_OFFSET(%si), %ebx # LBA of extent
 	movl %es:DIR_DATA_LEN_OFFSET(%si), %ecx # Length of extent

 	# Adjust number of bytes to read
 	cmpw $0x0800, %cx # or 2048 bytes (size of ISO9960 sector)
 	jae .read_directory_sector
 	addl $0x7ff, %ecx

.read_directory_sector:

	shr $11, %ecx # byte -> sector (count to read_sector)
 	call read_sector

 	# Prepare to traverse the next entry

 	pop %bx
 	pop %si # point back to curr pos in path str

 	test %bh, %bh # bh -> file or dir
 	jnz .entry_found # check if file

 	inc %si # next char in path
 	jmp .read_entry_dir_loop

.entry_found: # found file
	pop %es
	ret


#
# read_pvd:
# 
# Loads the Primary Volume Descriptor (PVD) into the memory region
# at $PVD_BUFFER_SEGMENT.
#

read_pvd:
	movw $0x0010, %bx # start at 0x10(16)
	movw $0x0001, %cx # 1 seg

	# Store the PVD in the designed buffer
	movw $PVD_BUFFER_SEGMENT, %ax
	movw %ax, %es

.find_pvd_loop:
	call read_sector

	cmpb $PVD_TYPE_PVD, %es:PVD_TYPE_CODE_OFFSET # Check PVD
	je .pvd_found
	
	inc  %bx
	jmp  .find_pvd_loop

.pvd_found:
	ret


# read_root_dir:
#
# Stores the root directory located in the PVD at the address specified
# by the segment value stored in %ax.
#
# Parameters:
#
#     - %ax: Segment value where the root directory should be stored at (read_sector)

read_root_dir:
	
	# KEY: Segment %es is always pointing to the beginning of the PVD buffer

 	movl %es:PVD_ROOT_DIRECTORY_OFFSET + DIR_EXTR_SEC_OFFSET, %ebx
 	movl %es:PVD_ROOT_DIRECTORY_OFFSET + DIR_DATA_LEN_OFFSET, %ecx

 	# Number of sectors equals data length divided by 2^11 (2048)

	shr $11, %ecx
 	call read_sector
 	ret

### DATA
dap:
dap_ptr_size: .byte  0x10
dap_ptr_resv: .byte  0x00
dap_ptr_cnum: .short 0x0001
dap_ptr_dest: .short 0x00000000
dap_ptr_segm: .short 0x00000000
dap_ptr_llba: .long  0x00000000
dap_ptr_hlba: .long  0x00000000

bios_error_msg: .asciz "\r\nBIOS function error" # Ah => 1

# Address where the PVD is loaded
.set PVD_BUFFER_SEGMENT,                          0x0200

# Buffer address for temporary directories when searching for files
.set DIR_BUFFER_SEGMENT,                          0x0280

# Offsets within the PVD structure
.set PVD_TYPE_CODE_OFFSET,                          0
.set PVD_STD_ID_OFFSET,                             1
.set PVD_VERSNO_OFFSET,                             6
.set PVD_SYS_ID_OFFSET,                             8
.set PVD_VOL_ID_OFFSET,                            40
.set PVD_SPACE_SIZE_OFFSET,                        80
.set PVD_SET_SIZE_OFFSET,                         120
.set PVD_SEQ_NUMBER_OFFSET,                       124
.set PVD_BLOCK_SIZE_OFFSET,                       128
.set PVD_PATH_TABLE_SIZE_OFFSET,                  132
.set PVD_PATH_TABLE_L_OFFSET,                     140
.set PVD_OPT_PATH_TABLE_L_OFFSET,                 144
.set PVD_PATH_TABLE_M_OFFSET,                     148
.set PVD_OPT_PATH_TABLE_M_OFFSET,                 152
.set PVD_ROOT_DIRECTORY_OFFSET,                   156
.set PVD_VOL_SET_ID_OFFSET,                       190
.set PVD_PUB_ID_OFFSET,                           318
.set PVD_DATA_PREP_ID_OFFSET,                     446
.set PVD_APPLICATION_ID_OFFSET,                   574
.set PVD_COPYRIGHT_ID_OFFSET,                     702
.set PVD_ABSTRACT_ID_OFFSET,                      740
.set PVD_BIBLIOGRAPHIC_ID_OFFSET,                 776
.set PVD_VOL_CREATE_DATE_OFFSET,                  813
.set PVD_VOL_MODIFY_DATE_OFFSET,                  830
.set PVD_VOL_EXPIRE_DATE_OFFSET,                  847
.set PVD_VOL_EFFECT_DATE_OFFSET,                  864
.set PVD_FILE_STRUCTURE_VERSNO_OFFSET,            881

# Types of PVD
.set PVD_TYPE_BR,                                   0
.set PVD_TYPE_PVD,                                  1
.set PVD_TYPE_SVD,                                  2
.set PVD_TYPE_VPD,                                  3

# ISO 9660 directory fields
.set DIR_LENGTH_OFFSET,                            0
.set DIR_EXT_ATTR_LENGTH_OFFSET,                   1
.set DIR_EXTR_SEC_OFFSET,                          2
.set DIR_DATA_LEN_OFFSET,                         10
.set DIR_DATE_OFFSET,                             18
.set DIR_FILE_FLAG_OFFSET,                        25
.set DIR_FILE_UNIT_SIZE_OFFSET,                   26
.set DIR_FILE_INTL_SIZE_OFFSET,                   27
.set DIR_VSEQ_NUM_OFFSET,                         28
.set DIR_FILE_ID_LENGTH_OFFSET,                   32
.set DIR_FILE_ID_OFFSET,                          33
###
