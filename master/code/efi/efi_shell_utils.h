#ifndef EFI_SHELL_UTILS_H
#define EFI_SHELL_UTILS_H
#include "efi_data_type.h"
#include "efi_system_table.h"
void printstr(EFI_SYSTEM_TABLE* SystemTable, const CHAR16* str);
void printuintn(EFI_SYSTEM_TABLE* SystemTable, UINTN num);
void clearscreen(EFI_SYSTEM_TABLE* SystemTable);
void reset(EFI_SYSTEM_TABLE* SystemTable);
void waitforkey(EFI_SYSTEM_TABLE* SystemTable, EFI_INPUT_KEY* Key);
int strcmp(const CHAR16* str1, const CHAR16* str2);

void clear_input_buffer(CHAR16* buffer, UINTN length);
#endif