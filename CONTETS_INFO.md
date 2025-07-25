# Content Information

## Two folder in the root of this repository
1. `Generic`: Generic contains the general Drivers that work on all devices of the same hardware type (eg. Generic VGA/GPU Driver -> a driver that works with all the GPUs)
2. `Specific`: Specific contains Specific Drivers for a Device (eg. AMD B450 Chipset -> Driver for this specific chipset)

## Contents of each driver folder
All Drivers have:
1. `README.md`: File giving information related to the driver. (If information missing or unclear, write in Issues)
2. `driver`: Folder containg all the driver required files to be built (including .inf for installing the compiled .sys) by running `build` from the WinDDK (Windows Driver Development Kit) to have the .SYS file ready.
Some Drivers have:
3. `programs`: Folder containing User-Level program source codes for testing the drivers. `classes` sub-folder contains files that can be included in your own programs (eg. .h for C or .vb for vb.net) in order to use the driver easily.
