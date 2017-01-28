###Troubleshooting

There is quite a high probability you will run into errors while you are trying to run BoneOS. This page covers all the frequent problems with running BoneOS the first time. If this page does not solve your problems, please [post an issue here](https://github.com/Bone-Project/BoneOS/issues/new).

**During compilation, there is an error that it cannot find `-lgcc`**

This is a common problem. It basically means you are missing the 32 bit libgcc, so let's install it:

    sudo apt-get install g++-multilib
    
**The Makefile cannot find the gcc compiler!**

This _mostly_ means you are on a system which does not have the `gcc` compiler installed by default. You can either install it, [or use a different compiler which is installed on your system](https://github.com/Bone-Project/BoneOS/blob/master/docs/ChangeCompiler.md).

**I am on Windows, and can't access any distributions of Linux! How do I build this OS?**

Unfortunately, we do not have a Windows build right now. You can use the new "Windows Subsystem for Linux" feature to build this, but if you can't use this feature or access a Linux distribution, sorry. We are not supporting a Windows build right now.

**I installed Virtual Box to run BoneOS on my Ubuntu PC, and now when I login all I get is the wallpaper**

This is a known issue, and thus we recommend to use QEmu on Linux Distributions. If you ever encounter this issue, [follow the steps in this answer](http://askubuntu.com/a/76951/493875), and if you don't see Unity in the list, [follow these steps](http://askubuntu.com/questions/17381/unity-doesnt-load-no-launcher-no-dash-appears#comment567329_76951).

**I still have an issue while building this Operating System!**

If so, please [post an issue here](https://github.com/Bone-Project/BoneOS/issues/new) with the following details _at least_:

 - The OS you are working on while compiling BoneOS.
 - The date and time you are trying to compile the OS.
 - The output of the compilation.
 - The list of commands you have executed for trying to build BoneOS.
 - The exact error message.
 - Some description if you want.

