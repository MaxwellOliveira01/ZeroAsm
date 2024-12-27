import os
import subprocess

tests = sorted([file for file in os.listdir("in") if file.endswith(".asm")], 
            key = lambda x: int(x.split(".")[0]))

GREEN = '\033[32m'
RED = '\033[31m'
BOLD = '\033[1m'
RESET = '\033[0m'

for testNum in range(len(tests)):
    print("Running test #" + str(testNum + 1) + ": ", end="")

    input_file = os.path.join("in", tests[testNum])

    result = subprocess.run(["./../../cod", input_file], capture_output=True, text=True)

    if result.returncode == 0:
        print(f"{BOLD}{GREEN}Passed{RESET}")
    else:
        print(f"{BOLD}{RED}Failed{RESET}. Output: {result.stdout}", end="")

    os.remove(tests[testNum].replace(".asm", ".pre"))