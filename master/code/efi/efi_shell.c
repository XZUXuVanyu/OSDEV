// efi_shell.c
#include "efi_shell.h"
#include "efi_shell_commands.h"

int shell_active = 1;
void efi_shell(EFI_SYSTEM_TABLE* SystemTable)
{
    SystemTable->BootServices->SetWatchdogTimer(0, 0, 0, 0);

    EFI_INPUT_KEY Key;
    printstr(SystemTable, L"Watchdog timer disabled. Press any key to continue...\r\n");
    waitforkey(SystemTable, &Key);
    
    clearscreen(SystemTable);
    printstr(SystemTable, L"Welcome to simple UEFI shell!\r\n");

    register_commands();

    CHAR16 Input_buf[MAX_INPUT_LENGTH] = {0};
    UINTN input_index = 0;

    printstr(SystemTable, L"test >> ");

    while (shell_active)
    {
        if (SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &Key) == EFI_SUCCESS)
        {
            // enter trigger command execution
            if (Key.UnicodeChar == L'\r')
            {
                printstr(SystemTable, L"\r\n");
                
                // execute command
                command_execute(SystemTable, Input_buf);

                // clear input buffer
                input_index = 0;
                clear_input_buffer(Input_buf, MAX_INPUT_LENGTH);
                printstr(SystemTable, L"test >> ");
            }
            else
            {
                // add character to input buffer
                if (input_index < MAX_INPUT_LENGTH - 1)
                {
                    Input_buf[input_index] = Key.UnicodeChar;
                    input_index++;
                    Input_buf[input_index] = L'\0';
                    // echo character
                    CHAR16 charStr[2] = {Key.UnicodeChar, L'\0'};
                    printstr(SystemTable, charStr);
                }
            }
        }
    }
}