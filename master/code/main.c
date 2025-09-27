#include "efi_shell.h"
void efi_main(void *ImageHandle __attribute__ ((unused)), EFI_SYSTEM_TABLE *SystemTable)
{
    SystemTable->ConOut->EnableCursor(SystemTable->ConOut, 1);
    efi_shell(SystemTable);
}