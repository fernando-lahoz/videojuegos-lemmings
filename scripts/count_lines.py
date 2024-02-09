import os

def count_lines(file_path):
    with open(file_path, 'r', encoding='utf-8', errors='ignore') as file:
        return sum(1 for line in file)

def count_lines_in_directory(directory, extensions):
    total_lines = 0

    for root, _, files in os.walk(directory):
        for file_name in files:
            if file_name.endswith(tuple(extensions)):
                file_path = os.path.join(root, file_name)
                total_lines += count_lines(file_path)

    return total_lines

if __name__ == "__main__":
    directory_path = "./"
    valid_extensions = ['.cpp', '.cu']

    total_lines = count_lines_in_directory(directory_path, valid_extensions)

    print(f"Total lines in {', '.join(valid_extensions)} files: {total_lines}")
