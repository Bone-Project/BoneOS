# Options
 Options come through running `./configure` script. `(chmod +x)` to make it executable.
 Options Avaiable are
    
- ***Architecture (Default x86)***
- ***Compiler(Default GCC)***
- ***Platform (Default pc)***
    
### Changing Compiler
In order to change compiler just use the configure script
`CC_NAME` being the Compiler name 

```sh
./configure --cc=CC_NAME
```
`--arch` and `--plat` being the default x86 and pc.

### Changing Architecture
In order to change architecture just use the configure script
`ARCH_NAME` being the architecture name 

```sh
./configure --arch=ARCH_NAME
```
`--cc` and `--plat` being the default GCC and pc.

### Changing Platform
In order to change platform just use the configure script
`P_NAME` being the platform name 

```sh
./configure --plat=P_NAME
```
`--cc` and `--arch` being the default GCC and x86.

# More Help

Execute the help command for `./configure` command using this:

```sh
./configure --help
```