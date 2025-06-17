# Visual Basic .NET (vb.net) Class For using QEMU DebugCon from your vb.net program

## Info
| Support      | Full                        |
|--------------|-----------------------------|
| Requirements | .NET Framework 2.0 or newer |

## How to use it
1. Get the `DebugCon.vb` file from this folder and place it in your project.
2. You can use the QEMU DebugCon in your program.

## Example Usage
The commands are like vb.net ConsoleApplication Write and WriteLine.
1. ***Write***: Writes to DebugCon without new line.
   Usage:
   ```
   DebugCon.Write("Your string.")
   ```
   or
   ```
   DebugCon.Write(TextBox1.Text)
   ```
2. ***WriteLine***: Writes to DebugCon with newline.
   Usage:
   ```
   DebugCon.WriteLine("Your string.")
   ```
   or
   ```
   DebugCon.WriteLine(TextBox1.Text)
   ```
