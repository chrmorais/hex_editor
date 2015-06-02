import os.path
import sys

from GUI.address_block import *
from GUI.byte_grid import *
from GUI.ui_utils import Rectangle as Rect
from application import Application

import file_buffer


if(len(sys.argv) == 1):
    print("Не указано имя файла!")
    exit()

file_path = sys.argv[1]

if not(os.path.isfile(file_path)):
    print("Указанный файл не существует!")
    exit()

file_size = os.stat(file_path).st_size

def main(stdscr):
    app = Application(stdscr,file_path)
    app.keyloop()

if __name__ == '__main__':
    curses.wrapper(main)
