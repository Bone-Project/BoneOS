# Building BoneOS From Source on Ubuntu

Here is how you build BoneOS from Ubuntu


First Clone this repository the Cross Compiler 

```sh
git clone <REPO_URL>
```

After sucessfully cloning the project You can have additonal configurations 
to run at a specific Architecture / Platform / Compiler / etc...

Look at Documentation/Options for more on this.

If you choose not to have additonal options it will configure with the defaults
set by Makefile `?=` . Now run make 

```sh
make
```

And this will give you a sucessfull Image File(ISO) for BoneOS. If you have
a qemu for testing you can run

```sh
make qemu_compile
```

for running the Binary version or the actual ISO using :

```sh
make qemu_iso
```

#Issues

If there are any whatsoever issues , please request an issue [here](https://meta.boneos.org/)!