import subprocess

# Command to run the executable
command = './hw4_client.exe'

# Input to be provided to the program
input_data = 'uArcher\n18A0PYCZURBVJDQE\nUSER'

# Run the command and provide input
process = subprocess.Popen(command, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
output, error = process.communicate(input=input_data)

# Print the output and error (if any)
print(output)