# Open-Source-Windows-Drivers
Open Source Windows Driver Source Codes

## ⚠ Warning
The drivers in this repository just work, there is no guarantee that they will function properly.
Use at your own risk.

## OS Support
All these drivers are tested with WDK (Windows Driver Kit) Version 7.1.0 and work on Windows XP and newer.

## I want to submit my driver code
You can create a merge request with your driver source files. Your driver must be compatible with WDK 7.1.0 and Windows XP to be merged.

## Driver Types

| Type     | Description                                                                                                                               |
|----------|-------------------------------------------------------------------------------------------------------------------------------------------|
| Generic  | The drivers that are for a type of hardware and not for a specific device. (eg. Generic VGA Driver -> A driver that can run on all GPUs)  |
| Specific | Drivers for specific hardware (eg. NVIDIA GeForce 8800 GTS 512 -> A driver for this GPU only)                                             |

## License
All of this code is completely open source. You can copy, edit, modify, build your own code based on it, and generally do whatever you want.
