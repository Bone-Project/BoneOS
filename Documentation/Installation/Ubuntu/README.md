# Building BoneOS From Source on Ubuntu

Before coming here, make sure you have all the required dependancies in the README.MD Listed on the outermost dir (On the Ubuntu OS Section).

If thats the case, well here is how you build it from Ubuntu OS


First Clone this repository the Cross Compiler 

```sh
git clone <REPO_URL>
```

After you did this `cd` into the cloned directory and then

```sh
make cc_install 
```

After this , if you dont have all the dependencies listed in the requirements do: 

```sh
. ./setenv.sh #To Set Enviorment Variables
make compile
make BoneOS.iso
```

This will give you the .iso file on the outermost dir. You can then Hook up
A Virtual Machine Emulator(Like VirtualBox or VMWare) on the ISO And Finally Run BoneOS :)

#Issues

If there are any whatsoever issues , please request an issue here! https://meta.boneos.org/