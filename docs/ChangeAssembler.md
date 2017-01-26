###Changing the assembler to be used

BoneOS uses an assembler as some of the instructions are in Assembly. You can change this to an assembler you want. The default assembler BoneOS uses is `as`.

To change the assembler used, we need to run the configure script. First, let's change the mode:

    chmod +x configure
    
Now, let's change the assembler:

    ./configure --as=<your assembler here>
    
and insert the assembler you wanted to use in the space given above. Then, build from the source as you normally would, but this time it will use the assembler you specified.