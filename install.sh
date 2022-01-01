#!/bin/bash

mkdir -p ~/bin/diyDB
cp ./main ~/bin/diyDB/diyDB
chmod +x ~/bin/diyDB/diyDB
if ! command -v diyDB &> /dev/null
then
    echo "export PATH=$PATH:$HOME/bin/diyDB/" >> ~/.zshrc
fi