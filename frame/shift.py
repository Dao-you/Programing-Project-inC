import os
import shutil
import random

# 原始檔案目錄
original_directory = "./"

# # 將檔案名稱的數字 + 60 並修改檔名
# for i in range(6629, 0, -1):
#     old_file = os.path.join(original_directory, f"BA{i}.txt")
#     new_file = os.path.join(original_directory, f"BA{i+60}.txt")
#     if os.path.exists(old_file):
#         os.rename(old_file, new_file)

# for i in range(60):
#     new_file = os.path.join(original_directory, f"BA{i+1}.txt")
#     shutil.copy(os.path.join(original_directory, f"BA65.txt"), new_file)

def replace_spaces_with_random_char(file_path, encoding='utf-8'):
    try:
        with open(file_path, 'r', encoding=encoding) as file:
            text = file.read()
            space_indices = [i for i, char in enumerate(text) if char == ' ']
            num_spaces = len(space_indices)
            num_replacements = int(0.01 * num_spaces)
            selected_indices = random.sample(space_indices, num_replacements)
            
            # 隨機選取的索引替換為指定的字元
            for index in selected_indices:
                random_char = random.choice([';', ':', "'", '"', 'i', 'j', '!'])
                text = text[:index] + random_char + text[index + 1:]
            
            # 寫入替換後的內容到原始檔案
            with open(file_path, 'w', encoding=encoding) as file:
                file.write(text)
                
            print(f"已成功替換 {num_replacements} 個空格為隨機字元。")
    except FileNotFoundError:
        print("找不到檔案。")
    except UnicodeDecodeError:
        print(f"無法使用 {encoding} 解碼檔案。")

# 使用範例
file_path = './BA1.txt'  # 將 'your_file_path.txt' 替換為檔案的實際路徑
for i in range(150):
    file_path = f'./BA{i}.txt'
    replace_spaces_with_random_char(file_path)
