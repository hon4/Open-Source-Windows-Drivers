# hon QEMU DebugCon Driver

## Driver information
| Driver Full Name: | hon QEMU DebugCon Driver |
|-------------------|--------------------------|
| Driver ID:        | qemu_debugcon            |

## Description
A driver for using QEMU's DebugCon from Windows guest operating systems.

## Known Issues
If you know how to fix any of the following write an Issue or create a Pull Request.
| Issue ID | File              | Description                                                          |
|----------|-------------------|----------------------------------------------------------------------|
| 1        | qemu_debugcon.inf | Installing qemu_debugcon.sys but not registering the driver service. |

## Tests
| Operating System | Pass/Fail |
|------------------|-----------|
| Windows XP       | Pass      |
| Windows XP x64   | -         |
| Windows 7        | Pass      |
| Windows 7 x64    | -         |

## Resource Usage
| Type | Range |
|------|-------|
| I/O  | 0xE9  |
