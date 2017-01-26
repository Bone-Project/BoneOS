###Changing the default compiler

C is a compiled language, and thus even the Operating System has to be compiled. If you are on a specific system which does not support the default compiler `gcc`, you may want to change the compiler used.

First, go to the directory where you have cloned BoneOS:

    cd /path/to/bone/os/clone
    
To configure the compiler, we need to run a shell script named `configure`. First, lets change it's mode:

    chmod +x configure
    
Now, let's change the compiler (`gcc` which is there by default, `clang`, `cc` etc..):

    ./configure --cc=<compiler name>
    
Then, build it like you normally would. The difference will be that instead of the compilation happening through `gcc`, it will happen through your specified compiler.

You can also change the compiler during compiling, though this will not be permanent like the configure script:

    make cc=<compiler name> <your options here>
    
this will use the specified compiler while compiling the OS. 
    