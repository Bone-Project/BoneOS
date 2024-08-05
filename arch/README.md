# Architecture dependant code


### Boot

- You will find these under arch/boot and uefi.
- For boot those are for BIOS bootloaders which I haven't completely finished but have made progress
- let's just say its a pain in the rear and makes sense why we use UEFI now...

- For UEFI i had two options, either use gnu_efi and generate bindings myself or juts use the uefi crate (chose the later)