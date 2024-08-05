
### install rust bindgen
cargo install bindgen-cli

## if there is a kconfig.h in root directory(../) then generate a bindings.rs from ../kconfig.h
file=../kconfig.h
if [ -f kconfig.h ]; then
    bindgen kconfig.h -o bindings.rs
    echo "Bindings.rs generated"
fi  