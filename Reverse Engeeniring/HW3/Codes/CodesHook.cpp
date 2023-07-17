// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <stdio.h>

// Typedef for the hooked function signature, such as:
typedef int(_cdecl* FUNC_PTR)(const char* Str1, const char* Str2); //(WINAPI is for _stdcall)
// or in the simple case:
//typedef LPVOID FUNC_PTR;

// Ptr to the original function
FUNC_PTR original_func_address;

// Global variables
DWORD lpProtect = 0;
LPVOID IAT;
FUNC_PTR JumpTo;
bool strcmpFlag = true;

// Helper function to remove the hook (for the current call):
void _stdcall remove_hook() {
    VirtualProtect((char*)IAT, 0x4, PAGE_EXECUTE_READWRITE, &lpProtect);
    memcpy(IAT, &original_func_address, 0x4);
    VirtualProtect((char*)IAT, 0x4, PAGE_EXECUTE_READ, &lpProtect);
}

// Helper function to restore the hook (for the next calls)
void _stdcall restore_hook() {
    VirtualProtect((char*)IAT, 0x4, PAGE_EXECUTE_READWRITE, &lpProtect);
    memcpy(IAT, &JumpTo, 0x4);
    VirtualProtect((char*)IAT, 0x4, PAGE_EXECUTE_READ, &lpProtect);
}

// Hook function. Might use helper functions in C, i.e. void _stdcall helper(int num) {}
// Might even use only a funcHook c function instead!
int _cdecl funcHook(const char* Str1, const char* Str2) {
    if (strcmpFlag) {
        strcmpFlag = false;
        return 1;
    }
    else {
        return 0;
    }
}

void setHook() {
    HMODULE h = GetModuleHandle(NULL);
    HMODULE h2 = GetModuleHandle(L"msvcrt.dll");

    if ((h == NULL) || (h2 == NULL)) { return; }

    original_func_address = (FUNC_PTR)GetProcAddress(h2, "strcmp");
    if (original_func_address == NULL) {
        printf("Couldn't find the function in the specified dll\n");
        return;
    }

    int addr_beginning_of_our_exe = 0x400000; // change!
    int addr_func_to_hook_in_IAT = 0x409294; // change!
    IAT = h + (addr_func_to_hook_in_IAT - addr_beginning_of_our_exe) / 4; // Calc address of address to override in IAT

    if ((*(LPDWORD)IAT) != (DWORD)original_func_address) {
        printf("IAT contents does not match - maybe check the offset again\n");
        return;
    }

    JumpTo = (FUNC_PTR)((char*)&funcHook);
    restore_hook();
}


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        setHook();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}