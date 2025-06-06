#include <ntddk.h>

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject);

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);

    DbgPrint("DriverEntry called\n");

    DriverObject->DriverUnload = DriverUnload;

    return STATUS_SUCCESS;
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject) {
    UNREFERENCED_PARAMETER(DriverObject);

    DbgPrint("DriverUnload called\n");
}
