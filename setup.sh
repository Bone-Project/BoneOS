#Install Dependencies

echo "SETTING UP DEPENDENCIES"
if [ "$(uname)" == "Darwin" ]; then
   sleep 2
   brew nasm
   brew gcc
   brew qemu
   brew grub-common
   brew xorriso
   brew grub-pc-bin      
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    sleep 2
    sudo apt-get update
    sudo apt-get install nasm
    sudo apt-get install gcc
    sudo apt-get install qemu
    sudo apt-get install grub-common
    sudo apt-get install xorriso
    sudo apt-get install grub-pc-bin
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ]; then
    # Do something under Windows NT platform
    echo "BoneOS Isnt Available on Windows Operating Systems Yet."
fi


