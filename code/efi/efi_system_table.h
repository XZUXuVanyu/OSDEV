#ifndef EFI_SYSTEM_TABLE_H
#define EFI_SYSTEM_TABLE_H
#include "efi_data_type.h"

typedef struct EFI_INPUT_KEY EFI_INPUT_KEY;
typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
typedef struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL EFI_SIMPLE_TEXT_INPUT_PROTOCOL;
typedef struct EFI_RUNTIME_SERVICES EFI_RUNTIME_SERVICES;
typedef struct EFI_BOOT_SERVICES EFI_BOOT_SERVICES;

typedef struct EFI_SYSTEM_TABLE
{
    char _buf[44];
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;
    char _EFI_OUTPUT_HANDLE_[8];
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
    char _EFI_STANDARD_ERROR_HANDLE_[8];
    char _STDERR_[8];
    EFI_RUNTIME_SERVICES *RuntimeServices;
    EFI_BOOT_SERVICES *BootServices;
}EFI_SYSTEM_TABLE;


typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
{
    EFI_STATUS (*Reset)(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, BOOLEAN ExtendedVerification);
    EFI_STATUS (*OutputString)(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, unsigned short *String);
    char _EFI_TEST_STRING_[8];
    char _EFI_QUERY_MODE_[8];
    char _EFI_SET_MODE_[8];
    char _EFI_SET_ATTRIBUTE_[8];
    EFI_STATUS (*ClearScreen)(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);
    EFI_STATUS (*SetCursorPosition)(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, UINTN Column, UINTN Row);
    EFI_STATUS (*EnableCursor)(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, BOOLEAN Visible);
}EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL
{
    char _EFI_TEXT_RESET_[8];
    EFI_STATUS (*ReadKeyStroke)(EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, EFI_INPUT_KEY *Key);
    EFI_EVENT WaitForKey;

}EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef struct EFI_INPUT_KEY
{
    UINT16 ScanCode;
    CHAR16 UnicodeChar;
}EFI_INPUT_KEY;

typedef struct  EFI_RUNTIME_SERVICES
{
    /* data */
}EFI_RUNTIME_SERVICES;

typedef struct EFI_BOOT_SERVICES
{
    EFI_STATUS (*Create_event)(UINT32 Type, UINT32 NotifyTpl, VOID *NotifyFunction, VOID *NotifyContext, EFI_EVENT *Event);
    char _Create_eventEx_[8];
    EFI_STATUS (*Close_event)(EFI_EVENT Event);
    char _Signal_event_[8];
    EFI_STATUS (*Wait_for_event)(UINTN NumberOfEvents, EFI_EVENT *Event, UINTN *Index);
    char _placeholder_[(4+5+18+6)*8];
    EFI_EVENT (*Set_watchdog_timer)(UINTN Timeout, UINT64 WatchdogCode, UINT32 DataSize, CHAR16 *WatchdogData);
}EFI_BOOT_SERVICES;


typedef struct EFI_EVENT
{
    /* data */
};

#endif

