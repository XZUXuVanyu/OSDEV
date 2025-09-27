// efi_shell_commands.c
#include "efi_shell_commands.h"

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
}

// parse and execute command
void command_execute(EFI_SYSTEM_TABLE* SystemTable, CHAR16* input)
{

    // skip leading spaces
    while (*input == L' ') input++;

    // find the position of the newline or space to determine the end of the command
    UINTN i;
    for (i = 0; input[i] != L'\0' && input[i] != L' '; i++);

    // extract the command name
    CHAR16 command_name[MAX_INPUT_LENGTH];
    for (UINTN j = 0; j < i; j++) {
        command_name[j] = input[j];
    }
    command_name[i] = L'\0';

    // find the command in the command table
    for (UINTN command_idx = 0; command_idx < command_count; command_idx++) {
        if (strcmp(command_table[command_idx].name, command_name) == 0)
        {
            // call the corresponding command function
            command_table[command_idx].execute(SystemTable, input, NULL);
            return;
        }
    }
    printstr(SystemTable, L"Unknown command: ");
    printstr(SystemTable, command_name);
    printstr(SystemTable, L"\r\n");
}

// command implementations
void command_help(EFI_SYSTEM_TABLE* SystemTable, CHAR16* Input_buf, CHAR16* Output_buf)
{
    printstr(SystemTable, L"Available commands:\r\n");
    for (UINTN i = 0; i < command_count; i++)
    {
        printstr(SystemTable, command_table[i].name);
        printstr(SystemTable, L"\r\n");
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
    printstr(SystemTable, L"Booting to OS...\r\n");

    //1.get map buffer size
    EFI_STATUS status;
    UINTN memory_map_size = 0;
    UINTN map_key;
    UINTN descriptor_size;
    UINT32 descriptor_version;
    EFI_MEMORY_DESCRIPTOR* memory_map = NULL;
    UINTN memory_map_entries;

    printstr(SystemTable, L"Getting memory map...\r\n");
    status = SystemTable->BootServices->GetMemoryMap(&memory_map_size, NULL, &map_key, &descriptor_size, &descriptor_version);
    printstr(SystemTable, L"Memory map buffer size needed: ");
    printuintn(SystemTable, memory_map_size);
    printstr(SystemTable, L"bytes.\r\n");

    UINTN memory_alloc_size = memory_map_size += 2 * descriptor_size;
    UINT32 EfiLoaderData;

    //2.allocate memory
    status = SystemTable->BootServices->AllocatePool(EfiLoaderData, memory_alloc_size, (void**)&memory_map);
    if (status == EFI_SUCCESS) 
    {
        printstr(SystemTable, L"Allocated ");
        printuintn(SystemTable, memory_alloc_size);
        printstr(SystemTable, L"bytes of memory successfully.\r\n");
    }

    //3.get full memory map
    printstr(SystemTable, L"Getting full memory table...\r\n");
    status = SystemTable->BootServices->GetMemoryMap(&memory_map_size, memory_map, &map_key, &descriptor_size, &descriptor_version);
    printstr(SystemTable,L"Memory map acquired.\r\n");

    printstr(SystemTable,L"Memory info:\r\n");
        {
            //print memory info
            printstr(SystemTable,L"- Total Size:");
            printuintn(SystemTable, memory_map_size);
            printstr(SystemTable,L"bytes\r\n");

            printstr(SystemTable, L"- Descriptor size: ");
            printuintn(SystemTable, descriptor_size);
            printstr(SystemTable, L" bytes\r\n");
            
            printstr(SystemTable, L"- Descriptor version: ");
            printuintn(SystemTable, descriptor_version);
            printstr(SystemTable, L"\r\n");
            
            UINTN entry_count = memory_map_size / descriptor_size;
            printstr(SystemTable, L"- Number of entries: ");
            printuintn(SystemTable, entry_count);
            printstr(SystemTable, L"\r\n");
        }

}