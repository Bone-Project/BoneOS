###Changing the RAM

You can change the RAM you are planning to run BoneOS on. 

We will use the `configure` script to do this. First, let's change the mode:

    chmod +x configure
    
Now, let's execute it

    ./configure --m=<Amount>
    
The support for a number x , xG For x gigabytes or xM for x megabytes. RAM Configuration typically
cant be smaller than 5M or larger than 2G for qemu.