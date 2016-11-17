# Building BoneOS From Source on Windows OS

Here is how you build it from Windows OS. Before you do this remember to get the linux subsystem for windows New feature. [**Here**](http://www.howtogeek.com/249966/how-to-install-and-use-the-linux-bash-shell-on-windows-10/) is a guide on how to install this awesome feature!


First Clone this repository the Cross Compiler 

```sh
git clone <REPO_URL>
```

After you did this `cd` into the cloned directory and then

```sh
make get-toolchain 
```

After this , using your Ubuntu Bash (One of requirements listed) , if you dont have all the dependencies listed in the requirements(Microsoft Ubuntu Bash is a 100% Need) do: 

```sh
make
```

This will give you the .iso file on the outermost dir. You can then Hook up
A Virtual Machine Emulator(Like VirtualBox or VMWare) on the ISO And Finally Run BoneOS :)

#Issues

If there are any whatsoever issues , please request an issue here! https://meta.boneos.org/