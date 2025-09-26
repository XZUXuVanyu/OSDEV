#include "efi_shell_utils.h"

void clearscreen(EFI_SYSTEM_TABLE* SystemTable)
{
    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
}

void reset(EFI_SYSTEM_TABLE* SystemTable)
{
    SystemTable->ConOut->Reset(SystemTable->ConOut, 1);
}

void print(EFI_SYSTEM_TABLE* SystemTable, const CHAR16 *str)
{   
    SystemTable->ConOut->OutputString(SystemTable->ConOut, (CHAR16 *)str);
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