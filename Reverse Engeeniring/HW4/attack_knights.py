import time
from attack_shell import *

process = initial_attack()

# Send input to the other script
input_data = '$content = Get-Content -Path \"config\\attack.config\" ; $newContent = $content -replace \\"True\\", \\"False\\" ; $newContent | Out-File -FilePath \"config\\attack.config\" -Encoding UTF8'

run_shell_command(process, input_data)

time.sleep(5)
process.stdin.close()
process.kill()