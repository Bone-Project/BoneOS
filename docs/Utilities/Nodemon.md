###Nodemon

BoneOS provides a utility which keeps on checking if something has changed, and once something is changed, it builds the OS again and boots it using QEmu.

We are going to use a shell script located in `utils/watch.sh` to do this. First, let's change the mode:

    chmod +x utils/watch.sh
    
Now, let's run the shell script:

    ./utils/watch.sh
    
which will keep watching for code changes. To quit this script, press <kbd>Control</kbd> + <kbd>C</kbd>.