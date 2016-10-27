# BoneOS RoadMap

This file contains the development roadmap for the first upcoming release of BoneOS.

&nbsp;
&nbsp;

## v0.0.1

This section will talk about the feautures we will include for the first ever release of BoneOS(0.0.1) . **NOTE** : This is not at all new feautres we will start adding our ideas once we get quite advanced in the Operating System Developement Field. This release wont include bug fixes and so, since we havent made any releases yet to have bugs :P . Please note that we dont have a specific time to finish implementing this release , since dates may subject to change depending on our enviorment. Now here is the ROADMAP For our first ever release(v0.0.1)! 

**NOTE** : We Will Start Adding to this ROADMAP or deleting as this project moves onward.


+ **Drivers**
  + We will include many drivers such as Keyboard , Mouse , Timer Driver(PIT), ATA, etc...
  + These drivers we will implement will be as abstract as possible for contribution to 
    have seperate drivers. For example if you want to have your specific keyboard layout
    that wasnt implemented in BoneOS you will just give the scancode and the KBD Driver
    code will be well designed to recognize that scancode.
  +  Drivers will be implemented mostly under the drv/ folder.

+ **File System**
  + This is a very undecided subject , but BoneOS Will either have an implementation of
  its own file system, or use one of the extX(Extended FileSystem) with version not 
  defined(X).

+ **Dynamic Memory**    
  + Our Dynamic Memory Allocation System is also not defined as we have not reached
  this point to decide yet, but we will soon!

+ **GUI**
  + Again the Graphical User Interface will be highly abstract like the drivers so 
  other contributors can easily contribute to the GUI Interface. (A.K.A What the 
  User Primarly Sees).  