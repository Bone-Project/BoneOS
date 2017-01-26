#Install Dependencies

echo "SETTING UP DEPENDENCIES"
if [ "$(uname)" == "Darwin" ]; then
   if hash brew 2>/dev/null; then
   		brew install nasm
		brew install supervisor #C9 -> NoVNC
		brew tap xrisk/i686-toolchain
		brew install --HEAD i686-elf-grub
		curl -s -o ~/cross-dev.sh https://raw.githubusercontent.com/xrisk/homebrew-i686-toolchain/master/setenv.sh
		echo "The cross compiler has been installed and a config file has been created at $HOME/cross-dev.sh"
		echo "Please run: 'source $HOME/cross-dev.sh' before using the cross-compiler."
	else
		echo "Please install Homebrew from http://brew.sh."
		echo "BoneOS uses Homebrew to manage dependencies."
	fi
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
   echo pwd
   echo "RUNNING UNDER a linux distro"
    sudo apt-get update
	if [ -z "$TRAVIS" ]; then
		sudo apt-get install -y nasm gcc-5 gcc-5-multilib qemu grub-common xorriso grub-pc-bin supervisor
	else
		sudo apt-get install nasm gcc-5 gcc-5-multilib qemu grub-common xorriso grub-pc-bin supervisor
	fi
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ]; then
    # Do something under Windows NT platform
    echo "BoneOS Isnt Available on Windows Operating Systems Yet."
    echo "You Can Code here : https://ide.c9.io/amanuel2/osdev , or contact us at : https://github.com/Bone-Project/BoneOS/issues"
fi


