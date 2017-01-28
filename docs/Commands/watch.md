###Command `watch` manual

**NAME**

> `watch` - execute a program periodically, showing the output

**SYNOPSIS**

> `watch [options] [command to run]`
    
**DESCRIPTION**

> `watch` runs the specified command repeatedly, displaying its output and error on the screen. This allows one to watch the program output change over time. By default, the program is run every 2 seconds. `watch` will run till one presses the key `q` to quit the command. 

**OPTIONS**

>- `--help`: prints the help for this command in the terminal

>- `-t`: turn off the header showing the interval and the command at the top of the display, as well as the following blank line.

>- `-n <seconds>`: Specify the update interval.