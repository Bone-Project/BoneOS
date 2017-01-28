###Command `cursor` manual

**NAME**

> `cursor` - changes the cursor type

**SYNOPSIS**

> `cursor [compulsory options]`
    
**DESCRIPTION**

> `cursor` change the cursor type to either a custom cursor or a predefined one (block cursor and underline cursor)

**OPTIONS**

>- `--help`: prints the help for this command in the terminal

>- `-t block`: changes the cursor to block cursor (START:0, END:20)

>- `-t def`: changes the cursor to the default underline cursor (START: 15, END: 15)

>- `-t <START> <END>` changes the cursor to the custom specified type