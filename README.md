# [BoneOS](https://BoneOS.org)


<p align="center"><a href="https://boneos.org" target="_blank"><img width="200"src="https://i.imgur.com/H6ixAr4.png"></a></p>


<p align="center">

<a href="https://amanuel2.gitbooks.io/boneos/content"><img src="https://img.shields.io/badge/Documentation-passing-brightgreen.svg"></a>

<a href="https://gitter.im/amanuel2/BoneOS?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge"><img src="https://badges.gitter.im/amanuel2/BoneOS.svg"></a>

<a href="https://BoneOS.slack.com"><img src="https://slack.boneos.org/badge.svg"></a>

<a href="https://zenhub.com"><img src="https://raw.githubusercontent.com/ZenHubIO/support/master/zenhub-badge.png"></a>

<a href="https://www.bountysource.com/teams/boneos"><img src="https://api.bountysource.com/badge/team?team_id=184475"></a>
<table>
  <tr>
    <th>Release Version</th>
    <th>Release Date</th>
    <th>Github Releases</th>
    <th>SourceForge</th>
  </tr>
  
  <tr>
   <td>V 0.0.1</td>
   <td>Dec/29/2016</td>
   <td>To Be Added</td>
   <td>
   <a href="https://sourceforge.net/projects/boneproject-boneos/files/Release%20V%200.0.1/BoneOS.iso/download"><img src="https://a.fsdn.com/con/app/sf-download-button"/></a>
   </td>
  </tr>
</table>

<table>
  <tr>
    <th>Branch</th>
    <th>Status</th>
    <th>Main Developer</th>
  </tr>
  
   <tr>
    <td>master</td>
    <td>
    <a href="https://travis-ci.org/Bone-Project/BoneOS/branches"> <img src="https://api.travis-ci.org/Bone-Project/BoneOS.svg?branch=master"/></a>
    </td>
    <td><strong><a href="https://github.com/Bone-Project">BoneOS Community</a></strong></td>
  </tr>
  
  <tr>
    <td>amanuel_dev</td>
    <td>
    <a href="https://travis-ci.org/Bone-Project/BoneOS/branches"> <img src="https://api.travis-ci.org/Bone-Project/BoneOS.svg?branch=amanuel_dev"/></a>
    </td>
    <td><strong><a href="https://github.com/amanuel2">amanuel2</a></strong></td>
  </tr>
   <tr>
    <td>doug_dev</td>
    <td>
    <a href="https://travis-ci.org/Bone-Project/BoneOS/branches"> <img src="https://api.travis-ci.org/Bone-Project/BoneOS.svg?branch=doug_dev"/></a>
    </td>
    <td><strong><a href="https://github.com/doug65536">doug65536</a></strong></td>
  </tr>
   <tr>
    <td>ashish_dev</td>
    <td>
    <a href="https://travis-ci.org/Bone-Project/BoneOS/branches"> <img src="https://api.travis-ci.org/Bone-Project/BoneOS.svg?branch=ashish_dev"/></a>
    </td>
    <td><strong><a href="https://github.com/Fortunate-MAN">Fortunate-MAN</a></strong></td>
  </tr>
</table>



</p>




<h3 color="red"> Current BoneOS Version : V 0.0.1 </h3>




[![gitcheese.com](https://api.gitcheese.com/v1/projects/fa53637b-26a0-49e0-b836-ae4b5c63adc8/badges?type=1)](https://www.gitcheese.com/app/#/projects/fa53637b-26a0-49e0-b836-ae4b5c63adc8/pledges/create)






### [BoneOS Meta](https://meta.boneos.org/)


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

Documentation
---
You can take a look at the Documentation/ Directory for docs on BoneOS , or even online [**here**](https://amanuel2.gitbooks.io/boneos/content). Documentation are for presistant information , not code details.

Architectures
---
Architecture          |   Status    | Plan to support |
------------- | ------------- | -----------|
x86(32 BIT) |    Ready   |  Already Supported        |
x64| On Progress  |    Currently updating to support this architecture       |
PowerPC| Unavailable  |   Yes, in later releases       |
Arm| Unavailable   |    Yes, in later releases       |
MIPS | Unavailable|     Yes, in later releases     |

if there are architectures you want BoneOS to support , please request an issue to talk about it. 

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