import tkinter as tk
from tkinter import filedialog
import sys
root = tk.Tk()
root.withdraw()

recommended_filename = ""
try:
    recommended_filename = sys.argv[1].split('/')
    recommended_filename = recommended_filename[-1]
except IndexError:
    pass
file_name = filedialog.asksaveasfilename(defaultextension=".maze", filetypes=(("MAZE file", ".maze"),), initialfile=recommended_filename)
with open("getMazeName/filename.txt", 'w') as file:
    file.write(file_name)