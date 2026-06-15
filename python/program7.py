import os

def findfiles(path):
    for item in os.listdir(path):

        full_path = os.path.join(path, item)

        if os.path.isfile(full_path):
            yield full_path

        elif os.path.isdir(full_path):
            yield from findfiles(full_path)


directory = 'folder'

for file in findfiles(directory):
    print(file)

