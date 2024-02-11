#!/bin/bash

if [ $UID -ne 0 ]; then
    echo Error: Must be root! >&2
    exit 1
fi

set -e

##--- SDL --------------------------------------------------------------##

wget https://github.com/libsdl-org/SDL/archive/refs/tags/release-2.30.0.zip
unzip release-2.30.0.zip
cd SDL-release-2.30.0

sudo ./configure; sudo make; sudo make install

cd ..
rm release-2.30.0.zip
rm -fr SDL-release-2.30.0

##--- SDL_image --------------------------------------------------------------##

wget https://github.com/libsdl-org/SDL_image/archive/refs/tags/release-2.8.2.zip

unzip release-2.8.2.zip
cd SDL_image-release-2.8.2

sudo ./configure; sudo make; sudo make install

cd ..
rm release-2.8.2.zip
sudo rm -r SDL_image-release-2.8.2

##--- SDL_mixer --------------------------------------------------------------##

wget https://github.com/libsdl-org/SDL_mixer/archive/refs/tags/release-2.8.0.zip
unzip release-2.8.0.zip
cd SDL_mixer-release-2.8.0

sudo ./configure; sudo make; sudo make install

cd ..
rm release-2.8.0.zip
sudo rm -r SDL_mixer-release-2.8.0
