# Set video mode using VBE (Video Bios Extensions)
# Reference: http:#www.techhelpmanual.com/936-vesa_svga_bios_functions.html


# ax = 0x4f02 "Set VBE Mode"
# bx = mode
#    D0-8   = Mode Number
#    D9-10  = Reserved (must be 0)
#    D11    = 0 Use current default refresh rate.
#    D12-13 = 0 Reserved
#    D14    = 0 Use windowed frame buffer model.
#           = 1 Use linear frame buffer model.
#    D15    = 0 Clear display memory.
#    ES:DI  = Pointer to CRCTCInfoBlock structure

# try to get one of the resolutions by calling with different modes
# reference: https:#en.wikipedia.org/wiki/VESA_BIOS_Extensionss
video_start:
  video1280:
    mov	$0x4f02, %ax
    mov	$0x411b, %bx
    int	$0x10
    cmp	$0x004f, %ax
    je	videodone
  video1024:
    mov	$0x4f02, %ax
    mov	$0x4118, %bx
    int	$0x10
    cmp	$0x004f, %ax
    je	videodone
  video800:
    mov	$0x4f02, %ax
    mov	$0x4115, %bx
    int	$0x10
    cmp	$0x004f, %ax
    je	videodone
  video640:
    mov	$0x4f02, %ax
    mov	$0x4112, %bx
    int	$0x10
    cmp	$0x004f, %ax
    je	videodone
  video640_lowcolor:
    mov	$0x4f02, %ax
    mov	$0x4111, %bx
    int	$0x10
    cmp	$0x004f, %ax
    je	videodone

  videofailed:
    mov	$videomsg, %esi
    call puts16
    
  .halt_vid:
    hlt
    jmp .halt_vid

  videodone:
  # Loading up es:di with the pointer to our buffer
  # to get Super VGA mode information loaded
    mov	%ds, %ax		# Set up the extra segment
    mov	%ax, %es		# with the data segment

    mov	$(video_info-_start),%di
    mov	$0x4f01, %ax
    mov	%bx, %cx
    int	$0x10
    ret

##### DATA

# Expects: AX    4f01H
#           CX    VESA/SVGA Video Mode number (may also be std modes 00-13H)
#           ES:DI Addr of buffer to receive an SvgaModeInfoRec
#           ──────────────────────────────────────────────────────────────────
#  Returns: AX    VESA status: AH=0 means successful (else failed)
#                              AL=4fH means function supported
#           ES:DI buffer contains returned data (if successful)
#           ──────────────────────────────────────────────────────────────────
#     Info: Obtains information about the capabilities, resolution, memory
#           access model, etc. for a particular SuperVGA video mode.

#           The buffer at ES:DI must be 256 bytes long (though only the first
#           29 bytes are defined).  See SvgaModeInfoRec for a layout of the
#           returned information.

#    Notes: ■ VESA implementations may not return the entire data structure.
#             Be sure to check bit 1 of the byte at offset 0.
#
#   STRUCTURE LAYOUT
#   ------------------
#
# ModeInfoBlock   STRUC
#         ModeAttributes      dw  ?  ; mode attributes
#         WinAAttributes      db  ?  ; window A attributes
#         WinBAttributes      db  ?  ; window B attributes
#         WinGranularity      dw  ?  ; window granularity
#         WinSize             dw  ?  ; window size
#         WinASegment         dw  ?  ; window A start segment
#         WinBSegment         dw  ?  ; window B start segment
#         WinFuncPtr          dd  ?  ; pointer to windor function
#         BytesPerScanLine    dw  ?  ; bytes per scan line

# ; formerly optional information (now mandatory)

#         XResolution         dw  ?  ; horizontal resolution
#         YResolution         dw  ?  ; vertical resolution
#         XCharSize           db  ?  ; character cell width
#         YCharSize           db  ?  ; character cell height
#         NumberOfPlanes      db  ?  ; number of memory planes
#         BitsPerPixel        db  ?  ; bits per pixel
#         NumberOfBanks       db  ?  ; number of banks
#         MemoryModel         db  ?  ; memory model type
#         BankSize            db  ?  ; bank size in kb
#         NumberOfImagePages  db  ?  ; number of images
#         Reserved            db  1  ; reserved for page function

# ; new Direct Color fields

#         RedMaskSize         db  ?  ; size of direct color red mask in bits
#         RedFieldPosition    db  ?  ; bit position of LSB of red mask
#         GreenMaskSize       db  ?  ; size of direct color green mask in bits
#         GreenFieldPosition  db  ?  ; bit position of LSB of green mask
#         BlueMaskSize        db  ?  ; size of direct color blue mask in bits
#         BlueFieldPosition   db  ?  ; bit position of LSB of blue mask
#         RsvdMaskSize        db  ?  ; size of direct color reserved mask in bits
#         DirectColorModeInfo db  ?  ; Direct Color mode attributes
#         Reserved            db  216 dup(?)      ; remainder of ModeInfoBlock
# ModeInfoBlock   ENDS

.align 4
video_info:
	.word	0
	.byte	0,0
	.word	0,0,0,0
	.long	0
.global video_xbytes
video_xbytes:
	.word	0
.global video_xres
video_xres:
	.word	0 
.global video_yres
video_yres:
	.word	0
	.byte	0,0,0,0,0,0,0,0,0
	.byte	0,0,0,0,0,0,0,0,0
.global video_buffer
video_buffer:
	.long	0
	.long	0
	.word	0
	.word	0
	.byte	0,0,0,0,0,0,0,0,0,0
	.long	0
.rept 190
	.byte	0
.endr

.align 4
videomsg:
	.asciz	"fatal error: couldn't find suitable video mode!\r\n"
#####
