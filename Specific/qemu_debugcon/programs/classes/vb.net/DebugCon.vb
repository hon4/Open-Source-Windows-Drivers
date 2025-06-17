Imports System
Imports System.Runtime.InteropServices
Imports Microsoft.Win32.SafeHandles
Public Class DebugCon
    'honCode 2025
    'hon QEMU DebugCon Driver Functions 4 Programs
    '====================================
    'Example usage:
    '   DebugCon.Write("Example")
    '   DebugCon.WriteLine("Example")

    'Required WinAPI Functions

    <DllImport("kernel32.dll", SetLastError:=True, CharSet:=CharSet.Auto)>
    Private Shared Function CreateFile(
        ByVal lpFileName As String,
        ByVal dwDesiredAccess As UInteger,
        ByVal dwShareMode As UInteger,
        ByVal lpSecurityAttributes As IntPtr,
        ByVal dwCreationDisposition As UInteger,
        ByVal dwFlagsAndAttributes As UInteger,
        ByVal hTemplateFile As IntPtr) As SafeFileHandle
    End Function

    <DllImport("kernel32.dll", SetLastError:=True)>
    Private Shared Function DeviceIoControl(
        ByVal hDevice As SafeFileHandle,
        ByVal dwIoControlCode As UInteger,
        <[In]()> ByVal lpInBuffer As Byte(),
        ByVal nInBufferSize As UInteger,
        ByVal lpOutBuffer As IntPtr,
        ByVal nOutBufferSize As UInteger,
        ByRef lpBytesReturned As UInteger,
        ByVal lpOverlapped As IntPtr) As Boolean
    End Function

    <DllImport("kernel32.dll", SetLastError:=True)>
    Private Shared Function CloseHandle(ByVal hObject As IntPtr) As Boolean
    End Function

    ' Constants for CreateFile
    Private Const GENERIC_WRITE As UInteger = &H40000000
    Private Const FILE_SHARE_READ As UInteger = &H1
    Private Const FILE_SHARE_WRITE As UInteger = &H2
    Private Const OPEN_EXISTING As UInteger = 3

    ' Define device symbolic link name
    Private Const DeviceName As String = "\\.\qemu_debugcon"

    ' Define IOCTL code - must match driver CTL_CODE definition
    ' Example: #define IOCTL_PRINT_STRING CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_WRITE_DATA)
    Private Const FILE_DEVICE_UNKNOWN As UInteger = &H22
    Private Const METHOD_BUFFERED As UInteger = 0
    Private Const FILE_WRITE_DATA As UInteger = &H2

    Private Const FUNCTION_PRINT_STRING As UInteger = &H800

    Private Const IOCTL_PRINT_STRING As UInteger = (FILE_DEVICE_UNKNOWN << 16) Or (FILE_WRITE_DATA << 14) Or (FUNCTION_PRINT_STRING << 2) Or METHOD_BUFFERED

    Public Shared Sub Write(ByVal s As String)
        Dim deviceHandle As SafeFileHandle = CreateFile(DeviceName, GENERIC_WRITE, FILE_SHARE_READ Or FILE_SHARE_WRITE, IntPtr.Zero, OPEN_EXISTING, 0, IntPtr.Zero)

        If deviceHandle.IsInvalid Then
            Dim errCode = Marshal.GetLastWin32Error()
            Throw New UnauthorizedAccessException("Failed to open hon QEMU DebugCon device " & DeviceName & ". Error code: " & errCode)
            Return
        End If

        Dim inputBytes As Byte() = System.Text.Encoding.ASCII.GetBytes(s & vbNullChar) ' NULL terminated string -> Converted to Byte Array

        Dim bytesReturned As UInteger = 0 'Useless uint

        Dim success As Boolean = DeviceIoControl(deviceHandle, IOCTL_PRINT_STRING, inputBytes, CUInt(inputBytes.Length), IntPtr.Zero, 0, bytesReturned, IntPtr.Zero)

        If Not success Then
            Console.WriteLine("Failed to send string to hon QEMU DebugCon. Error code: " & Marshal.GetLastWin32Error())
        End If

        deviceHandle.Close()
    End Sub

    Public Shared Sub WriteLine(ByVal s As String)
        Write(s & vbNewLine)
    End Sub
End Class

