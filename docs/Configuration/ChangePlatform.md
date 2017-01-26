###Changing the Platform

You can change the platform you are planning to run BoneOS on. 

We will use the `configure` script to do this. First, let's change the mode:

    chmod +x configure
    
Now, let's execute it

    ./configure --plat=<your platform here>
    
BoneOS only support the `pc` platform right now, so this might not be too useful presently.