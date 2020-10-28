import tkinter as tk
from tkinter import filedialog
import sys
import os


root = tk.Tk()
root.withdraw()
recommended_filepath = os.path.abspath("../user_data/levels")

file_path = filedialog.askopenfilename(initialdir=recommended_filepath,
                                       defaultextension=".maze",
                                       filetypes=(("MAZE file", "*.maze"),))
with open("../src/python/filename.txt", 'w') as file:
    file.write(file_path)

