// efi_shell.c
#include "efi_shell.h"
#include "efi_shell_commands.h"

int shell_active = 1;
void efi_shell(EFI_SYSTEM_TABLE* SystemTable)
{
    SystemTable->BootServices->Set_watchdog_timer(0, 0, 0, 0);

    EFI_INPUT_KEY Key;
    print(SystemTable, L"Watchdog timer disabled. Press any key to continue...\r\n");
    waitforkey(SystemTable, &Key);
    
    clearscreen(SystemTable);
    print(SystemTable, L"Welcome to simple UEFI shell!\r\n");

    // 初始化命令表（如果有动态注册，这里可以调用注册函数）
    register_commands();

    CHAR16 Input_buf[MAX_INPUT_LENGTH] = {0};
    UINTN input_index = 0;

    print(SystemTable, L"test >> ");

    while (shell_active)
    {
        if (SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &Key) == EFI_SUCCESS)
        {
            // 处理按键：回显并维护输入缓冲区
            if (Key.UnicodeChar == L'\r')
            {
                print(SystemTable, L"\r\n");
                // 执行命令
                command_execute(SystemTable, Input_buf);
                // 重置输入缓冲区
                input_index = 0;
                Input_buf[0] = L'\0';
                print(SystemTable, L"test >> ");
            }
            else
            {
                // 普通字符，添加到缓冲区
                if (input_index < MAX_INPUT_LENGTH - 1)
                {
                    Input_buf[input_index] = Key.UnicodeChar;
                    input_index++;
                    Input_buf[input_index] = L'\0';
                    // 回显字符
                    CHAR16 charStr[2] = {Key.UnicodeChar, L'\0'};
                    print(SystemTable, charStr);
                }
            }
        }
    }
}