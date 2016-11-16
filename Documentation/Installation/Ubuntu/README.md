# Building BoneOS From Source on Ubuntu

Here is how you build BoneOS from Ubuntu


First Clone this repository the Cross Compiler 

```sh
git clone <REPO_URL>
```

After you did this `cd` into the cloned directory and then

```sh
make get-toolchain 
```

After this , if you dont have all the dependencies listed in the requirements do: 

```sh
make
```

This will give you the .iso file on the outermost dir. You can then Hook up
A Virtual Machine Emulator(Like VirtualBox or VMWare) on the ISO And Finally Run BoneOS :)

#Issues

If there are any whatsoever issues , please request an issue here! https://meta.boneos.org/