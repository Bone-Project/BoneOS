# [BoneOS](https://BoneOS.org)
<img src="https://designapp.io/user-design-function/previewMyLogo/?logo_id=271982&hash=129ac10fa5"/>

Welcome! This is the official and main repository of BoneOS. This project is currently in high development as we are working on getting the basic setup , and later more features. We have converted from C++ to C. This Operating System is predominately written in C , while there are parts like hardware-communication , scripting , building , etc ... which will use other common languages. If you find any issue using this OS please request an issue [**here**](https://github.com/Bone-Project/BoneOS/issues)! If you have any contributions or pull requests , Which will be highly appreciated , please issue a pull request [**here**](https://github.com/Bone-Project/BoneOS/pulls)! 

Installation
---
There are two ways to install BoneOS one which is for the normal user to get it into his Virtual Machine and the other is for the developer who wants to contribute (building from source). Finally, there is a better way for developer and that’s to get floobits.

#### Normal Installation(For User)
  First download the ISO Off the github repository located [**Here**](https://github.com/Bone-Project/BoneOS) , and then plug it into your Virtual Machine. [**Here**](https://www.youtube.com/watch?v=gNfntwnkvzo&feature=youtu.be) is a video showing this setup , using VirtualBox as the Virtual Machine Emulator. You can download Virtual Box [**Here**](https://www.virtualbox.org/).
  

#### Using Floobits (For Developer)
 First register to floobits [**here**](https://floobits.com) . And finally join our workspace [**here**](https://floobits.com/aboga/BoneOS). **Note** : There are editor packages for floobits so you can work using your favorite editor! I normally use the Sublime Floobits Package.
 
#### Building From Source (For developer)

 First make sure you have a Ubuntu Terminal (If you are on windows use the new Linux Subsystem Feauture). Then after you have that , download the dependencies using `sh setup.sh`. Then install the cross compiler using `make c_compiler`. then finally set the cross compiler in your environment variables `cd cross` and then `. ./setenv.sh`. Now go back `cd ../`. And finally run `make compile` , `make BoneOS.bin -B` , `make BoneOS.iso -B`. That should set you up with the development environment.
 
#### More Info(For Developer)
For more information go to the directory `Documentation/{Desired OS}/README.md`
 
Directory Structure
----
Our Directory Structure Currently is as follows:

- ***cpu*** : Directory For Processor Related Code
- ***boot*** : GRUB Bootloader Information 
   - ***boot*** : Grub Multiboot Information
- ***linkage*** : Where the linker is located.
- ***main*** : Main kernel function getting called by GRUB Bootloader
- ***utils*** : utilities for users.
   - ***cross_compiler*** : Script for installing the cross compiler

Licence
---

BoneOS Is Licensed under the GPLv3 License. This Operating System is licensed under the GPLv3 License so anyone making modifications to code can indeed make changes to code, but **cannot** profit off of this Open source and Free Operating System. Also the modified code has to be of same license (GPLv3) , and have to indicate what changes they have made to the code compared to this repository.


