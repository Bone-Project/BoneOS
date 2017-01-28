###Changing the Linker used

BoneOS uses the `ld` linker by default. We can change this.

To do this, we need to use the `configure` script. First, let's change the mode:

    chmod +x configure
    
Now, let's change the linker:

    ./configure --ld=<your linker here>
    
and that will change the linker. Now, build from the source as you used to.