###Running the `.iso` file of BoneOS

The easiest way of running BoneOS on your computer is running a `.iso` file of BoneOS.

First, you need to download a `.iso` file of BoneOS (Nightly builds is the latest build of master):

 - [Nightly Builds](https://bintray.com/boneos/BoneOS/download_file?file_path=BoneOS-master.iso) (the latest version)
 
 - [Version 0.0.2](https://github.com/Bone-Project/BoneOS/releases/download/v0.0.2/BoneOS.iso)
 
 - [Version 0.0.1](https://github.com/Bone-Project/BoneOS/releases/download/v0.0.1/BoneOS.iso)
 
 
 Download the file. After you have downloaded the file, go to the directory (normally it is in `~/Downloads`):
 
    cd path/to/dir
    
(and replace the path with the actual path).

Now, copy the file to the home directory:

    cp BoneOS.iso ~/
    
and switch to the home directory:

    cd ~/
    
If you get an error above saying that the file does not exist, replace `BoneOS` with the name of the file you downloaded.

Now, you need to run this in a virtual machine. In this page, I am going to cover three virtual machines:

 - QEmu
 - Virtual Box
 - VM Ware
 
**QEmu**

I am assuming that you have QEmu installed. If not, google it and install QEmu for your OS.

I am going to be showing running the OS using the command line. If you are on Windows, use the new "Windows Subsystem for Linux" tool. You can run it even _without_ the terminal, but for this doc we need it. If you cannot use a terminal, go ahead and use VirtualBox or VMWare for now (**NOTE**: Installing Virtual Box and maybe even VM Ware is **known to cause some problems** on Linux distributions, so it is recommended that you do not install them on a Linux distribution).

When you install QEmu, and you want to use it through the command line, you use it with the command `qemu-system-i386` or something like that. It varies from system to system, so just check the docs and use the command. 

First, make an alias to `qemu` with the actual name (`qemu-system-i386` or something like that) so that you don't have to type the long command everytime:

    alias qemu='<insert the command name here>'
    
and put the actual command (might be `qemu-system-i386`) over there.

Now, we have the `.iso` file which we need to run through QEmu. To do that, do:

    qemu BoneOS.iso
    
and then you should get a new window with the text "Gnu GRUB ...". Press "Enter" over there.

You should see BoneOS starting then.

**Virtual Box**

To run BoneOS in Virtual Box (not recommended for Linux Distributions, as it is known to cause problems), see the following video: https://www.youtube.com/watch?v=rBjlaEAzUZo

**VM Ware**

To run BoneOS in VM Ware (not recommended for Linux Distributions, as it is known to cause problems), see the following video: https://www.youtube.com/watch?v=yDiwl6AxNrc






 