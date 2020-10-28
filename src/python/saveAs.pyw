import tkinter as tk
from tkinter import filedialog
import os
import sys
root = tk.Tk()
root.withdraw()

print(sys.argv, " arvgs")

recommended_filename = ""
initial_dir = os.path.abspath("../user_data/levels")
try:
    recommended_filename = sys.argv[1].split('/')[-1]
    initial_dir = '/'.join(sys.argv[1].split('/')[0:-1])
except IndexError:
    pass

file_name = filedialog.asksaveasfilename(initialdir=initial_dir,
                                         defaultextension=".maze",
                                         filetypes=(("MAZE file", ".maze"),),
                                         initialfile=recommended_filename)

with open("../src/python/filename.txt", 'w') as file:
    file.write(file_name)