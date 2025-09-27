#include "efi_shell_utils.h"

void clearscreen(EFI_SYSTEM_TABLE* SystemTable)
{
    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
}

void reset(EFI_SYSTEM_TABLE* SystemTable)
{
    SystemTable->ConOut->Reset(SystemTable->ConOut, 1);
}

void printstr(EFI_SYSTEM_TABLE* SystemTable, const CHAR16 *str)
{   
    SystemTable->ConOut->OutputString(SystemTable->ConOut, (CHAR16 *)str);
}

void printuintn(EFI_SYSTEM_TABLE* SystemTable, UINTN num)
{
    CHAR16 buf[64];
    UINTN digits = 0;
    UINTN temp = num;
    do
    {
        digits += 1;
        temp /= 10;
    } while (temp > 0);
    
    buf[digits] = L'\0';
    temp = num;
    for (UINTN i = 0; i < digits - 1; i++)
    {
        buf[digits - 1 - i] = L'0' + (temp % 10);
        temp /= 10;
    }
    printstr(SystemTable, buf);
}

CHAR16* read(EFI_SYSTEM_TABLE* SystemTable, CHAR16* Input_buf, CHAR16* Output_buf)
{
    CHAR16* input_buf_ptr = Input_buf;
    CHAR16* output_buf_ptr = Output_buf;
    while (*(input_buf_ptr) != L'\0')
    {
        *(output_buf_ptr) = *(input_buf_ptr);
        input_buf_ptr++;
        output_buf_ptr++;
    }
    return Output_buf;
}

void waitforkey(EFI_SYSTEM_TABLE* SystemTable, EFI_INPUT_KEY* Key)
{
    EFI_STATUS status;
    while (1)
    {
        if (SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, Key) == EFI_SUCCESS)
        {
            break;
        }
    }
}

int strcmp(const CHAR16* str1, const CHAR16* str2)
{
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
    return *(const unsigned short*)str1 - *(const unsigned short*)str2;
}

void clear_input_buffer(CHAR16* buffer, UINTN length)
{
    for (UINTN i = 0; i < length; i++)
    {
        buffer[i] = L'\0';
    }
}