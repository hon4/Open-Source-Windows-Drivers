# Windows Driver Base (win_drv_base)
## Test driver to check if you have setup WDK correctly, built the .sys and installed the driver correctly.
It will display "DriverEntry called" in the DebugView when driver is loaded and "DriverUnload called" when the driver stopped.

## Make and test this driver.
Create the following folder structure:
```
drv
├─> drv.inf
└─> drv.sys
```
