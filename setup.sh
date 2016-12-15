#Install Dependencies

echo "SETTING UP DEPENDENCIES"
if [ "$(uname)" == "Darwin" ]; then
  echo "RUNNING UNDER Max OSX"
   sleep 2
   brew install nasm
   brew install gcc
   brew install qemu
   brew install grub-common
   brew install xorriso
   brew install grub-pc-bin   
   brew install easy_install 
   easy_install supervisor
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
   echo pwd
   echo "RUNNING UNDER a linux distro"
    sleep 2
    sudo apt-get update
    sudo apt-get install nasm
    sudo apt-get install gcc
    sudo apt-get install qemu
    sudo apt-get install grub-common
    sudo apt-get install xorriso
    sudo apt-get install grub-pc-bin
    sudo apt-get install easy_install 
    easy_install supervisor
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ]; then
    # Do something under Windows NT platform
    echo "BoneOS Isnt Available on Windows Operating Systems Yet."
    echo "You Can Code here : https://ide.c9.io/amanuel2/osdev , or contact us at : https://meta.boneos.org"
fi


