###Building from source

To build from the source of BoneOS, you **need to have access to a linux terminal**. If you are in Windows, make use of the new feature "Windows Subsystem for Linux". If you can't access a linux terminal (or something which provides the commands of a linux terminal), it is **not** possible to build from the source.

First, we need to clone BoneOS's repository:

    git clone https://github.com/Bone-Project/BoneOS
    
Then, we go into the directory where BoneOS was cloned:

    cd BoneOS
    
Now, we need to install the dependencies on the specific computer. First, make the file `setup.sh` an executable:

    chmod +x setup.sh
    
and now execute it:

    ./setup.sh
    
This downloads and install all the dependencies required for the successful compilation of BoneOS. This might take a bit of a while, so have patience, and let the process complete.

Now, we need to compile the OS:

    make
    
this will output three files. You can see the files by running the command:

    ls -pal | grep BoneOS
    
which should give an output similar to:

    -rwxrwxr-x  1 ashish ashish   183026 Jan 25 18:32 BoneOS.bin
    -rw-rw-r--  1 ashish ashish 11423744 Jan 25 18:32 BoneOS.iso
    -rw-rw-r--  1 ashish ashish   132346 Jan 25 18:32 BoneOS.map
    
If you don't get _any_ output when running the above command, especially if you don't get the file `BoneOS.iso`, there has been an error in this compilation, or you have made a mistake. If so, please post an issue on our Github repository giving _all_ the necessary steps to reproduce this problem (give the commands which you have run, the OS you are on, the output of the compilation, and the date and time when you compiled it so that we can see on which commit did you see this issue).

We now have the file `BoneOS.iso` which is basically the file we have to run. You can either load and run it in your virtual machine (VirtualBox or VMWare), or run it with qemu:

    make qemu_iso
    
which will run the actual `.iso` file. You can also do 

    make qemu_compile
    
which will be a bit faster.

