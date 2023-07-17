// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

void decode_helper(char* msg, int& i, char& bits) {
    switch (msg[i]) {
    case 'A':
        bits = 1;
        i++;
        break;
    case 'J':
        bits = 10;
        i++;
        break;
    case 'Q':
        bits = 11;
        i++;
        break;
    case 'K':
        bits = 12;
        i++;
        break;
    default:
        if (msg[i + 1] == '+') {
            bits = msg[i + 2] + msg[i] - '0' - '0';
            i += 3;
        }

        else if (msg[i + 1] == '-') {
            bits = 0;
            i += 3;
        }

        else {
            bits = msg[i] - '0';
            i++;
        }

        break;
    }
}

int decode(char* msg)
{
    int len = strlen(msg);
    int next_char = 0;
    int i = 0;

    while (i < len) {
        char upper_bits = 0;
        char lower_bits = 0;
        decode_helper(msg, i, upper_bits);
        decode_helper(msg, i, lower_bits);

        char curr = (upper_bits * 16) + lower_bits;

        msg[next_char] = curr;
        next_char++;
    }

    msg[next_char] = 0;
    return next_char;
}

// Typedef for the hooked function signature, such as:
typedef INT(WINAPI* FUNC_PTR)(SOCKET, char*, int, int); //(WINAPI is for _stdcall)
// or in the simple case:
//typedef LPVOID FUNC_PTR;

// Ptr to the original function
FUNC_PTR original_func_address;

// Global variables
DWORD lpProtect = 0;
LPVOID IAT;
FUNC_PTR JumpTo;

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
INT _stdcall funcHook(SOCKET s, char* buf, int len, int flags) {
    INT ret = original_func_address(s, buf, len, flags);
    ret = decode(buf);
    return ret;
}

void setHook() {
    HMODULE h = GetModuleHandle(NULL);
    HMODULE h2 = GetModuleHandle(L"Ws2_32.dll");

    if ((h == NULL) || (h2 == NULL)) { return; }

    original_func_address = (FUNC_PTR)GetProcAddress(h2, "recv");
    if (original_func_address == NULL) {
        return;
    }

    int addr_beginning_of_our_exe = 0x400000; // change!
    int addr_func_to_hook_in_IAT = 0x40A2AC; // change!
    IAT = h + (addr_func_to_hook_in_IAT - addr_beginning_of_our_exe) / 4; // Calc address of address to override in IAT
    
    if ((*(LPDWORD)IAT) != (DWORD)original_func_address) {
        printf("IAT contents does not match - maybe check the offset again");
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