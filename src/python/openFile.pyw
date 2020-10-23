import tkinter as tk
from tkinter import filedialog
import sys

root = tk.Tk()
root.withdraw()
recommended_filename = ""
try: # if the c++ system() call had an argument for the script
    recommended_filename = sys.argv[1].split('/')[-1] # gets file name without path given by c++
except IndexError:
    pass
file_path = filedialog.askopenfilename(defaultextension=".maze", filetypes=(("MAZE file", "*.maze"),), initialfile=recommended_filename)
with open("../src/python/filename.txt", 'w') as file:
    file.write(file_path)