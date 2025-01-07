import os
import subprocess

GREEN = '\033[32m'
RED = '\033[31m'
BOLD = '\033[1m'
RESET = '\033[0m'

def get_test_main_folder(path):
    p = path.split("/")
    p.pop(); # removing file name
    
    if p[-1] == "in" or p[-1] == "out":
        p.pop() # removing in/out folder

    return p[-1]    

def get_test_number(path):
    file_name_with_extesion = path.split("/")[-1]
    file_name = file_name_with_extesion.split(".")[0]
    return int(file_name)

def get_test_name(path):
    return path.split("/")[-1]

def get_test_result_extesion(path):
    tmp = { 'asm' : 'pre', 'pre' : 'obj' }
    return tmp[path.split(".")[-1]]

def test_has_output(path):
    return 'in' in path.split('/')

def get_test_expected_output_path(path):
    p = path.split("/")
    full_file_name = p[-1]
    p.pop() # removing file name

    [file_name, extension] = full_file_name.split(".")

    p.pop() # removing in folder
    p.append('out')
    p.append(file_name + "." + get_test_result_extesion(extension))

    return "/".join(p)


def run_test(path):

    result = subprocess.run(["./../montador", path], capture_output=True, text=True)
    
    test_expected_output_path = get_test_expected_output_path(path)
    
    program_generated_output_path = "./" + test_expected_output_path.split('/')[-1] # same name, but on root folder

    if result.returncode != 0:
        os.remove(program_generated_output_path)
        if test_has_output(path):
            return (False, f"{BOLD}{RED}Runtime error{RESET}, couldnt check output. Output: " + result.stderr)
        return (True, f"{BOLD}{GREEN}Accepted{RESET} (get an error as expected)")
    
    if not test_has_output(path):
        os.remove(program_generated_output_path)
        return (True, f"{BOLD}{GREEN}Accepted{RESET}, no output file expected. Output:\n" + result.stdout)

    assert(os.path.exists(test_expected_output_path))

    diff = subprocess.run(["diff", test_expected_output_path, program_generated_output_path],
                        capture_output=True, text=True)

    os.remove(program_generated_output_path)

    if diff.returncode == 0:
        return (True, f"{BOLD}{GREEN}Accepted! :){RESET}")
    else:
        return (False, f"{BOLD}{RED}Wrong Answer ;({RESET}. Diff:\n" + diff.stdout)


extensions = ["asm", "pre", "obj"]
tests = []

for root, dirs, files in os.walk("./"):
    for file in files:
        if file.split(".")[-1] in extensions:
            full_path = os.path.join(root, file)

            if "out" in full_path.split("/"):
                continue # ignoring result files

            tests.append(full_path)

tests.sort(key=lambda x: get_test_main_folder(x))

total_tests = 0

tests_by_folder = {}

for t in tests:
    folder = get_test_main_folder(t)

    if folder not in tests_by_folder:
        tests_by_folder[folder] = []

    tests_by_folder[folder].append(t)
    total_tests += 1

current_test = 0

# before running tests, we need to compile the code

print("Compiling code...")
result = subprocess.run(["make", "-C", "../"], capture_output=True, text=True)

if result.returncode != 0:
    print(f"Error while compiling code: {result.stderr}")
    exit(1)


ac_count = 0

for folder in tests_by_folder:  
    tests = tests_by_folder[folder]

    print(f"\n\nRunning { len(tests) } tests of folder '{folder}':\n")

    tests = sorted(tests, key=lambda x : get_test_number(x))

    for t in tests:
        current_test += 1
        print(f"Running test {get_test_name(t)} ({current_test}/{total_tests}) and...", end="")
    
        [passed, message] = run_test(t)
    
        print(message)

        if passed:
            ac_count += 1



print(f"\n\n{ac_count}/{total_tests} tests passed")