/* honCode 2025
=================
DRIVER: hon QEMU DebugCon Driver 

Example Usage:
    DebugConPrintStr("I am an example!\n");
*/
#include <ntddk.h>

#define NT_DEVICE_NAME      L"\\Device\\qemu_debugcon"
#define DOS_DEVICE_NAME     L"\\DosDevices\\qemu_debugcon"

#define IOCTL_PRINT_STRING CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_WRITE_DATA)

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath);
VOID DriverUnload(IN PDRIVER_OBJECT DriverObject);
VOID WriteDebugConChar(const char c);
VOID DebugConPrintStr(const char* str);
NTSTATUS DeviceControl(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS CreateClose(PDEVICE_OBJECT DeviceObject, PIRP Irp);

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath) {
    NTSTATUS ntStatus;
    PDEVICE_OBJECT deviceObject = NULL;
    UNICODE_STRING ntDeviceName;
    UNICODE_STRING dosDeviceName;
    //First Vars then code
    UNREFERENCED_PARAMETER(RegistryPath);

    // Initialize device name
    RtlInitUnicodeString(&ntDeviceName, NT_DEVICE_NAME);

    // Create device object
    ntStatus = IoCreateDevice(
        DriverObject,
        0,                      // No device extension
        &ntDeviceName,
        FILE_DEVICE_UNKNOWN,
        FILE_DEVICE_SECURE_OPEN,
        FALSE,
        &deviceObject);

    if (!NT_SUCCESS(ntStatus)) {
        //DbgPrint("Failed to create device object.\n");
        return ntStatus;
    }

    // Initialize symbolic link name
    RtlInitUnicodeString(&dosDeviceName, DOS_DEVICE_NAME);

    // Create symbolic link for user mode access
    ntStatus = IoCreateSymbolicLink(&dosDeviceName, &ntDeviceName);
    if (!NT_SUCCESS(ntStatus)) {
        //DbgPrint("Failed to create symbolic link.\n");
        IoDeleteDevice(deviceObject);
        return ntStatus;
    }

    // Set dispatch routines
    DriverObject->MajorFunction[IRP_MJ_CREATE] = CreateClose;
    DriverObject->MajorFunction[IRP_MJ_CLOSE] = CreateClose;
    DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DeviceControl;

    DriverObject->DriverUnload = DriverUnload;

    //DbgPrint("DebugCon Driver Started.\n");
    //DebugConPrintStr("DebugCon Driver Started.\n");

    return STATUS_SUCCESS;
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject) {
    UNREFERENCED_PARAMETER(DriverObject);

    //DbgPrint("DriverUnload called\n");
}

VOID WriteDebugConChar(const char c) {
    // Write char to QEMU DebugCon I/O Port (0xE9)
    __asm {
        mov al, c
        out 0xE9, al
    }
}

VOID DebugConPrintStr(const char* str) {
    ULONG i;
    if (str == NULL) {
        return;
    }
    // While str[i] is not 0 (null rerminated string) keep printing chars
    for (i = 0; str[i] != 0; i++) {
        WriteDebugConChar(str[i]);
    }
}

NTSTATUS DeviceControl(PDEVICE_OBJECT DeviceObject, PIRP Irp) {
    PIO_STACK_LOCATION irpSp = IoGetCurrentIrpStackLocation(Irp);
    NTSTATUS status = STATUS_INVALID_DEVICE_REQUEST;
    ULONG_PTR information = 0;

    switch (irpSp->Parameters.DeviceIoControl.IoControlCode) {
    case IOCTL_PRINT_STRING:
    {
        // Input buffer contains the string to print
        char* inputBuffer = (char*)Irp->AssociatedIrp.SystemBuffer;
        ULONG inputBufferLength = irpSp->Parameters.DeviceIoControl.InputBufferLength;

        if (inputBuffer && inputBufferLength > 0) {
            // Null-terminate if needed
            if (inputBuffer[inputBufferLength - 1] != '\0') {
                inputBuffer[inputBufferLength] = '\0';
            }

            // Call QEMU DebugCon print string function
            DebugConPrintStr(inputBuffer);

            status = STATUS_SUCCESS;
            information = 0;
        } else {
            status = STATUS_INVALID_PARAMETER;
        }
        break;
    }
    default:
        // Invalid Device Function
        status = STATUS_INVALID_DEVICE_REQUEST;
        break;
    }

    Irp->IoStatus.Status = status;
    Irp->IoStatus.Information = information;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    return status;
}

NTSTATUS CreateClose(PDEVICE_OBJECT DeviceObject, PIRP Irp) {
    UNREFERENCED_PARAMETER(DeviceObject);

    Irp->IoStatus.Status = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;

    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    return STATUS_SUCCESS;
}
