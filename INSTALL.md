# Build Instructions

## Prerequisites

Specialised software is required in order to compile this source code. If one or more prerequisites are not installed, the final executable may not build or lack certain features.

### CMake

Download [CMake](https://cmake.org/) from the website or via package manager.

- Arch Linux: `sudo pacman -Syu cmake`

## Building

1. Create a new, empty 'build' folder.
2. Open CMake by clicking its icon or entering `cmake-gui` in a command prompt.
3. Set the source code directory to this repositories root folder.
4. Set the build directory to the 'build' folder created in step 1.
5. Click on the `Configure` button to configure project settings.
6. When done configuring, click `Generate`, then `Open Project`.
7. Build the project with the IDE of your choice.

## Installation

1. Open up a terminal and enter the command `cmake --install .` in the build directory created in the building process. Read the __Building__ section for more info on this directory.

By default, this software installs to /usr/local. To change the install location, set the CMAKE\_INSTALL\_PREFIX variable via the CMake GUI or by entering the command `cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr .` and rebuilding the project.

