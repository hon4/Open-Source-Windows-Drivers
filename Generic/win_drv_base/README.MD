# Windows Driver Base (win_drv_base)
## Test driver to check if you have setup WDK correctly, built the .sys and installed the driver correctly.
It will display "DriverEntry called" in the DebugView when driver is loaded and "DriverUnload called" when the driver stopped.

## How to install and test
1. Create the following folder structure:
```
drv
├─> drv.inf
└─> drv.sys
```
2. Install this driver
3. Create service with the following command.
```
sc create drv type= kernel binPath= C:\WINDOWS\system32\drivers\drv.sys
```
4. Then run the driver with
```
sc start drv
```
You will see this in DebugView

![DebugView DriverEntry](https://i.postimg.cc/wx2jx0Xk/dbgview.png)
