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

    if(result.returncode != 0):
        print(f"{BOLD}{RED}Failed{RESET}. Output: {result.stderr}", end="")
        continue

    test_output_name = tests[testNum].replace(".asm", ".pre")

    generated_output = test_output_name
    correct_output = os.path.join("out", test_output_name)

    diff = subprocess.run(["diff", "-q", correct_output, generated_output], capture_output=True, text=True)

    if diff.returncode == 0:
        print(f"{BOLD}{GREEN}Passed{RESET}")
        os.remove(test_output_name)
    else:
        print(f"{BOLD}{RED}Failed{RESET}. Output: {diff.stdout}", end="")
