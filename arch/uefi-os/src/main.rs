#![no_main]
#![no_std]
use log::info;
use uefi::prelude::*;


#[entry]
fn efi_main(_image: Handle, mut table: SystemTable<Boot>) -> Status {
    uefi::helpers::init(&mut table);
    info!("Hi Mom");
    table.boot_services().stall(10_000_000);
    Status::SUCCESS
}
