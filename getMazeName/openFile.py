import tkinter as tk
from tkinter import filedialog
import sys

root = tk.Tk()
root.withdraw()
recommended_filename = ""
try:
    
    recommended_filename = sys.argv[-1].split('/')
    print(recommended_filename)

    recommended_filename = recommended_filename[-1]
except IndexError:
    print("epic fail")
    pass
file_path = filedialog.askopenfilename(defaultextension=".maze", filetypes=(("MAZE file", "*.maze"),), initialfile=recommended_filename)
with open("getMazeName/filename.txt", 'w') as file:
    file.write(file_path)