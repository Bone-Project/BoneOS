###Command `shutdown` manual

**NAME**

> `shutdown` - brings the system down

**SYNOPSIS**

> `shutdown [option]`
    
**DESCRIPTION**

> `shutdown` arranges the system to be brought down in a safe way. You can specify a time with most options, which is assumed to be in seconds. The most common time provided is 'now', which brings the system down without any delay.

> Once the specified time has elapsed, `shutdown` uses the `poweroff` or the `reboot` command to reboot/poweroff the computer.

**OPTIONS**

>- `--help`: prints the help for this command in the terminal

>- `-r <time>`: reboots the system once the specified time has elapsed

>- `-h <time>`: powers off the system once the specified time has elapsed

**ALSO SEE**

>- `reboot`, `shutdown`