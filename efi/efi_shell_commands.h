// efi_shell_commands.h
#ifndef EFI_SHELL_COMMANDS_H
#define EFI_SHELL_COMMANDS_H

#include "efi_system_table.h"
#include "efi_data_type.h"
#include "efi_shell_utils.h"

#define MAX_INPUT_LENGTH 128
#define MAX_OUTPUT_LENGTH 256

// 前向声明
typedef struct efi_command efi_command;

// 命令处理函数原型
typedef void (*COMMAND_FUNCTION)(EFI_SYSTEM_TABLE* SystemTable, CHAR16* Input_buf, CHAR16* Output_buf);

// 命令结构体定义
struct efi_command {
    CHAR16* name;
    COMMAND_FUNCTION execute;
};

// 声明全局命令表和相关函数
extern efi_command command_table[];
extern UINTN command_count;

void register_commands(void);
void command_execute(EFI_SYSTEM_TABLE* SystemTable, CHAR16* input);

// 具体命令的声明
void command_help(EFI_SYSTEM_TABLE* SystemTable, CHAR16* Input_buf, CHAR16* Output_buf);
void command_clear(EFI_SYSTEM_TABLE* SystemTable, CHAR16* Input_buf, CHAR16* Output_buf);
void command_reset(EFI_SYSTEM_TABLE* SystemTable, CHAR16* Input_buf, CHAR16* Output_buf);
void command_boot(EFI_SYSTEM_TABLE* SystemTable, CHAR16* Input_buf, CHAR16* Output_buf);

#endif