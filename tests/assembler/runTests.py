import os
import subprocess

GREEN = '\033[32m'
RED = '\033[31m'
BOLD = '\033[1m'
RESET = '\033[0m'

for folder in ["generalErrors", "fewArguments", "tooManyArguments"]:

    tests = sorted([file for file in os.listdir(folder) if file.endswith(".pre")], 
            key = lambda x: int(x.split(".")[0].replace("in","")))

    print(f"\n{BOLD}Running tests for {folder}{RESET}\n")

    for testNum in range(len(tests)):
        print("Running test #" + str(testNum + 1) + ": ", end="")

        input_file = os.path.join(folder, tests[testNum])

        result = subprocess.run(["./../../cod", input_file], capture_output=True, text=True)

        if(result.returncode == 0):
            print(f"{BOLD}{RED}Failed{RESET}. It should detect an error")
        else:
            print(f"{BOLD}{GREEN}Passed{RESET}. It detected an error as expected")