###Changing the RAM

You can change the total RAM boneos can use.

Once can use the `configure` script to do this. First, let's change the mode:

    chmod +x configure
    
Now, let's execute it:

    ./configure --m=<total memory you want to use>
    
The total memory to be used has to be suffixed by `G` for Gigabytes and `M` for Megabytes. RAM configuration typically cannot be smaller then 5 Megabytes or larger than 2 Gigabytes for QEmu.

Also note that this can be done only in QEmu for now.