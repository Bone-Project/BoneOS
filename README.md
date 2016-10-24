# [BoneOS](https://BoneOS.org)

### [BoneOS Meta](https://meta.boneos.org/)

<img src="https://i.imgur.com/H6ixAr4.png" width="300" height="300" />

Welcome! This is the official and main repository of BoneOS. This project is currently in high development, as we are working on getting the basic setup sorted out. Later on, we will start developing multitude of features. We have converted the project from C++ to C. This Operating System is predominately written in C, but there are parts (like hardware communication, scripting, building, etc ...) which will use other common languages. If you find any issue using this OS please request an issue [**here**](https://meta.boneos.org/)! If you have any contributions or pull requests, which will be highly appreciated, please issue a pull request [**here**](https://github.com/Bone-Project/BoneOS/pulls)! 

# Discussions

Any Questions, Comments, Ideas, Feature Requests, etc. may be brought up on the [BoneOS Meta](https://meta.boneos.org/).

# Installation
---

There are two ways to install BoneOS: one for the normal user to get it into his Virtual Machine and the other for the developer who want to contribute (building from source). Finally, there is a better way for developers and that’s to get Floobits.

#### Normal Installation (For user)
  First download the ISO from this repository by either downloading the zip and extracting it, or by cloning it using git. Next, plug it into your Virtual Machine. [**here**](https://www.youtube.com/watch?v=gNfntwnkvzo&feature=youtu.be) is a video showing how to do this using VirtualBox as the Virtual Machine Emulator. You can download Virtual Box [**here**](https://www.virtualbox.org/).
  

#### Using Floobits (For developer)
 Register to Floobits [**here**](https://floobits.com) and join our workspace [**here**](https://floobits.com/aboga/BoneOS). **Note** : There are editor packages for Floobits so you can work using your favorite editor! I normally use the Sublime Floobits Package.
 
#### Building From Source (For developer)

 First make sure you have a Ubuntu Terminal (If you are on Windows, use the new Linux Subsystem Feature). Then download the dependencies using `sh setup.sh`. Then install the cross compiler using `make c_compiler`. Next, set the cross compiler in your environment variables `cd cross` and then `. ./setenv.sh`. Finally, run the following commands:
 ```
 cd ../
 make compile
 make BoneOS.bin -B
 make BoneOS.iso -B
 ```
 That should set you up with the development environment.
 
#### More Info(For Developer)
For more information, go to `Documentation/{Desired OS}/README.md`
 
Directory Structure
----
Our firectory structure currently is as follows:

- ***arch*** : archecture dependant assembly files
- ***Documentation*** : For More Documentation on BoneOS
- ***io*** : I/O Software Code
- ***cpu***: Directory for processor related code
- ***boot***: GRUB Bootloader information 
   - ***boot***: Grub Multiboot information
- ***link***: Where the linker is located.
- ***kernel***: Main kernel function getting called by GRUB Bootloader
- ***libc***: C Library constructed and used by BoneOS.
- ***screen***: Directory for screen related code such as VGA.
- ***utils***: Utilities for users.
   - ***cross_compiler***: Script for installing the cross compiler

License
---

BoneOS is Licensed under the GPLv3 License.
