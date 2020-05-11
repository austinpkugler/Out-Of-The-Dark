import tkinter as tk
from tkinter import filedialog

root = tk.Tk()
root.withdraw()
file_path = filedialog.askopenfilename(defaultextension=".maze", filetypes=(("MAZE file", "*.maze"),))
with open("getMazeName/filename.txt", 'w') as file:
    file.write(file_path)