# [BoneOS](https://BoneOS.org)

| Branch | Status                                                                                                                                               |
| ------:|:-----------------------------------------------------------------------------------------------------------------------------------------------------|
| Master | [![Build Status](https://api.travis-ci.org/Bone-Project/BoneOS.svg?branch=master)](https://travis-ci.org/Bone-Project/BoneOS)                        |
|  Amanuel Dev | [![Build Status](https://api.travis-ci.org/Bone-Project/BoneOS.svg?branch=amanuel_dev)](https://travis-ci.org/Bone-Project/BoneOS/branches) |
|  Doug Dev | [![Build Status](https://api.travis-ci.org/Bone-Project/BoneOS.svg?branch=doug_dev)](https://travis-ci.org/Bone-Project/BoneOS/branches) |

[![Stories in Ready](https://badge.waffle.io/Bone-Project/BoneOS.png?label=ready&title=Ready)](https://waffle.io/Bone-Project/BoneOS) 
[![Join the chat at https://gitter.im/amanuel2/BoneOS](https://badges.gitter.im/amanuel2/BoneOS.svg)](https://gitter.im/amanuel2/BoneOS?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
[![Join The chat](https://slack.boneos.org/badge.svg)](https://BoneOS.slack.com)
[![ZenHub](https://raw.githubusercontent.com/ZenHubIO/support/master/zenhub-badge.png)](https://zenhub.com)

[![badge_donation_bountysource](https://api.bountysource.com/badge/team?team_id=184475)](https://www.bountysource.com/teams/boneos)


[![gitcheese.com](https://api.gitcheese.com/v1/projects/fa53637b-26a0-49e0-b836-ae4b5c63adc8/badges?type=1)](https://www.gitcheese.com/app/#/projects/fa53637b-26a0-49e0-b836-ae4b5c63adc8/pledges/create)


SourceFourge : https://sourceforge.net/projects/boneproject-boneos/

### [BoneOS Meta](https://meta.boneos.org/)

<img src="https://i.imgur.com/H6ixAr4.png" width="300" height="300" />

Welcome! This is the official and main repository of BoneOS. This project is currently in high active development , 
and is predominately written in C ofcourse some parts such as  hardware communication, scripting, building, etc ...will use
other languages. 
If you find any issue using this OS please request an issue [**here**](https://meta.boneos.org/)!
If you have any contributions or pull requests, which will be highly appreciated, please issue a pull request 
[**here**](https://github.com/Bone-Project/BoneOS/pulls)! 

# Discussions

Any Questions, Comments, Ideas, Feature Requests, etc. may be brought up on the [BoneOS Meta](https://meta.boneos.org/).

# Installation
---

There are two ways to install BoneOS: one for the normal user to get it into his Virtual Machine and the other for the developer who want to contribute (building from source). 

#### Normal Installation (For user)
  First download the ISO from this repository by either downloading the zip and extracting it, or by cloning it using git. Next, plug it into your Virtual Machine. [**here**](https://www.youtube.com/watch?v=rBjlaEAzUZo&feature=youtu.be) is a video showing how to do this using VirtualBox as the Virtual Machine Emulator. You can download Virtual Box [**here**](https://www.virtualbox.org/). [Here](https://www.youtube.com/watch?v=yDiwl6AxNrc&feature=youtu.be) is a video showing how to get it in VMWare. VMWare is paid , there if a free trial though. You can get more Information at our Offical Download Page [here](https://boneos.org/download.html). 
 
#### Building From Source (For developer)

 First make sure you have a Ubuntu Terminal (If you are on Windows, use the new Linux Subsystem Feature). Then download the dependencies using `sh setup.sh`. Then compile BoneOS using `make`. Now that you have qemu after you executed `setup.sh` , you can go ahead and run on qemu using `make qemu_compile` for running the binary or `make qemu_iso` to run the actual Image File(.ISO).
 
#### Cloud9 Collaboration (For Developer) 
 
 You can collaborate with the Main BoneOS Developer in Cloud9. Cloud9 Is an Online IDE , with an Ubuntu Terminal. We use Cloud9IDE Terminal + NoVNC to make this possible.
 the workspace is located [here](https://ide.c9.io/amanuel2/osdev) . You can learn more [here](https://community.c9.io/t/cant-install-grub/11653/5?u=phpcoder231).
 
 If you want to setup NoVNC Server and you are in an Cloud9IDE You can use the command 
 
 ```sh
 make no_vnc
 ```
 
#### Extra Options (For Developer)

 There are extra options when building(`make`ing) , this OS. You can set the compiler instead of the default
 gcc(`$(CC)`) like so : 
 
 ```sh
  $ CC=clang make #If you want to run via clang
  $ CC=gcc-5 make #If you want to run via GCC Version 5
 ```
 
 You can see more in Documentation/options

#### More Info(For Developer)
For more information, go to `Documentation/TOC.md`
 
Directory Structure
----
Our firectory structure currently is as follows:

- ***Documentation*** : Documentation for BoneOS
- ***apps*** : Applications
   - ***term*** : Terminal
- ***arch*** : Architecture Dependant Codes
   - ***@(ARCH)*** : Architecture name.
     - ***boot***: GRUB Bootloader information 
       - ***multiboot***: Grub Multiboot information
     - ***drv***  : Device Drivers for @(ARCH) are located here.
     - ***io*** : I/O Software Code 
     - ***link***: Where the linker is located.
     - ***init***: Main kernel function getting called by GRUB Bootloader
  - ***shared*** : Shared piece of code between Proccecor Families
     - ***x86*** : Shared piece of code for x86 family
- ***bin*** : Non Adminstrator Terminal Commands
- ***sbin*** : Adminstrator Terminal Commands
- ***config*** : Configuration Files
- ***platform*** : Platform Dependant Code
   - ***pc*** : PC Platform
- ***libc***: C Library constructed and used by BoneOS, non-archecture and non-platform dependant code.
- ***utils***: Utilities for users.
   - ***cross_compiler***: Script for installing the cross compiler
   - ***no_vnc***: Setup No_vnc server in Cloud9IDE
   - ***watch.sh*** : Nodemon like script 
- ***include***: All Include Files(.h).

FAQ
---

1) **What is BoneOS Goal?**
 Our goal is to make an Operating System for 'Everyone'. Ranging from Programmers
 to Normal Users. We dont believe the "OS Problem" is solved by either Popular
 Operating Systems such as Windows, Mac OSX or even kernels such as Linux.

2) **Any new features?**
 We have some ideas in mind. But it will be a long way until we start adding
 new feautres, as we are just starting in the osdev world :).

3) **Need Help?**
 Absolutely! Any help would be appreciated! To get to us, either request an
 issue or check ask a question in meta : https://meta.boneos.org

License
---

BoneOS is Licensed under the GPLv3 License.