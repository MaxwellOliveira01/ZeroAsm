import os
import sys

def list_files_with_extension(folder, extension):
    for root, dirs, files in os.walk(folder):
        for file in files:
            if file.endswith(extension):
                print(os.path.join(root, file))

list_files_with_extension("./", ".pre")

# TODO