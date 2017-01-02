add-auto-load-safe-path /mnt/c/Users/aboga/BoneOS/.gdbinit
file BoneOS.bin
target remote localhost:1234
symbol-file BoneOS.bin
win
b kernelMain
c