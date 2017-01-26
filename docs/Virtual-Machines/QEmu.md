###QEmu

This is showing the necessary instructions for installing QEmu in a Ubuntu/Debian based distribution (tested on Ubuntu 14.04). 

Run the command

    sudo apt-get install qemu-system
    
which _should_ install QEmu. To check if it successfully installed it in your system, run the command:

    which qemu-system-i386 
    
which should output something similar to

    /usr/bin/qemu-system-i386
    
If nothing comes as the output, that means either you have made a mistake or the instructions are wrong. Please then request an issue on our Github repository, and we will get back to you.