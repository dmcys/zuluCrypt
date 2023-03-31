#!/bin/bash
build() {
# define the menu options
options=("Install ZuluCrypt" "Uninstall ZuluCrypt" "Quit")

# loop until the user chooses to quit
while true; do
    # print the menu
    echo "Select an option:"
    for i in "${!options[@]}"; do
        echo "$((i+1)). ${options[i]}"
    done

    # read the user's choice
    read -p "Option number: " choice
    case $choice in
        1)
            # clone the ZuluCrypt repository
            git clone https://github.com/defiminds/zuluCrypt.git

            # change into the cloned directory
            cd zuluCrypt

            # install dependencies
            sudo apt-get update
            sudo apt-get install -y libqt4-dev libssl-dev libgcrypt20-dev libparted-dev libblkid-dev libdevmapper-dev pkg-config make gcc

            # build and install ZuluCrypt
            ./configure
            make
            sudo make install

            # cleanup
            cd ..
            rm -rf zuluCrypt
            ;;
        2)
            # uninstall ZuluCrypt
            sudo make uninstall
            sudo rm /usr/local/bin/zuluCrypt-cli /usr/local/share/man/man1/zuluCrypt-cli.1.gz
            ;;
        3)
            # quit
            exit 0
            ;;
        *)
            # invalid choice
            echo "Invalid option, please try again."
            ;;
    esac
done
}
build
