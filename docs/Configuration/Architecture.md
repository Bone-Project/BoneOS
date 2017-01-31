###Changing the Architecture

BoneOS currently supports a bunch of architectures. You can change the architecture before compiling the Operating System.

To change the architecture we need to use the `configure` script. First, let's change its mode:

    chmod +x configure
    
Now, let's change the architecture:

    ./configure --arch=<your architecture>
    
and replace your specified architecture in the specified place.

You can currently type in these 32 bit architectures

 - x86 (default)
 - i386
 - amd32
 - 80386
 
and these 64 bit architectures

 - amd64
 - x86_64
 - x86-64
 - x64
 - emt64
 
Though note that some of the architecture have bugs and/or have not bee completed, so it is the best to use the 32 bit `x86` architecture which is completely finished and the default.