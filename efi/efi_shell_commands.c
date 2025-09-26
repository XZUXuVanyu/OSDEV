// efi_shell_commands.c
#include "efi_shell_commands.h"

// 全局命令表
efi_command command_table[] =
{
    {L"help", command_help},
    {L"clear", command_clear},
    {L"reset", command_reset},
    {L"boot", command_boot}
};

UINTN command_count = sizeof(command_table) / sizeof(efi_command);

void register_commands(void)
{
    // todo: 添加动态注册命令的逻辑，目前命令是静态定义的
}

// 执行命令：解析输入，查找命令并执行
void command_execute(EFI_SYSTEM_TABLE* SystemTable, CHAR16* input)
{
    // 跳过前导空格
    while (*input == L' ') input++;

    // 找到回车符或空格位置，确定命令结尾
    UINTN i;
    for (i = 0; input[i] != L'\0' && input[i] != L' '; i++);

    // 临时保存命令字符串
    CHAR16 command_name[MAX_INPUT_LENGTH];
    for (UINTN j = 0; j < i; j++) {
        command_name[j] = input[j];
    }
    command_name[i] = L'\0';

    // 在命令表中查找命令
    for (UINTN command_idx = 0; command_idx < command_count; command_idx++) {
        if (strcmp(command_table[command_idx].name, command_name) == 0)
        {
            // 调用对应的命令函数
            command_table[command_idx].execute(SystemTable, input, 0);
            return;
        }
    }
    print(SystemTable, L"Unknown command: ");
    print(SystemTable, command_name);
    print(SystemTable, L"\r\n");
}

// 具体命令的实现
void command_help(EFI_SYSTEM_TABLE* SystemTable, CHAR16* Input_buf, CHAR16* Output_buf)
{
    print(SystemTable, L"Available commands:\r\n");
    for (UINTN i = 0; i < command_count; i++)
    {
        print(SystemTable, command_table[i].name);
        print(SystemTable, L"\r\n");
    }
}

void command_clear(EFI_SYSTEM_TABLE* SystemTable, CHAR16* Input_buf, CHAR16* Output_buf)
{
    clearscreen(SystemTable);
}

void command_reset(EFI_SYSTEM_TABLE* SystemTable, CHAR16* Input_buf, CHAR16* Output_buf)
{
    reset(SystemTable);
}


void command_boot(EFI_SYSTEM_TABLE* SystemTable, CHAR16* Input_buf, CHAR16* Output_buf)
{
    // 这里实现boot命令，退出BootServices并跳转到操作系统内核
    // 由于这个函数比较复杂，我们这里只打印一条消息
    print(SystemTable, L"Booting to OS...\r\n");
    // 实际的操作应该包括获取内存映射、退出BootServices、跳转到内核等步骤。
}