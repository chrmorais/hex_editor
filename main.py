import os.path
import sys

from GUI.address_block import *
from GUI.byte_grid import *
from GUI.ui_utils import Rectangle as Rect

import file_buffer


if(len(sys.argv) == 1):
    print("Не указано имя файла!")
    exit()

file_path = sys.argv[1]

if not(os.path.isfile(file_path)):
    print("Указанный файл не существует!")
    exit()

file_size = os.stat(file_path).st_size

def keyloop(context):

    max_y, max_x = context.getmaxyx()

    address_block = AddressBlock(Rect(0,0,8,max_y))
    address_block.start_address = 0
    address_block.color = 2
    address_block.highlight = 3
    address_block.highlight_inx = 0

    byte_grid = ByteGrid(Rect(address_block.draw_zone.width + 1,
                              0,
                              max_x - address_block.draw_zone.width - 1,
                              max_y))
    byte_grid.color = 2
    byte_grid.highlight = 3
    byte_grid.data = bytearray()
    byte_grid.cursor_position = (1, 1)

    address_block.step = byte_grid.col_count

    file_buffer.init(128)
    file_buffer.open_file(file_path)

    data = []
    data_size = byte_grid.col_count * byte_grid.row_count
    if data_size > file_size:
        data_size = file_size
    for i in range(data_size):
        data.append(ord(file_buffer.get_byte(i)))

    byte_grid.data = bytearray(data)


    if curses.has_colors():
        curses.init_pair(1, curses.COLOR_YELLOW, curses.COLOR_BLUE)
        curses.init_pair(2, curses.COLOR_WHITE, curses.COLOR_BLUE)
        curses.init_pair(3, curses.COLOR_BLUE, curses.COLOR_WHITE)

        context.bkgdset(curses.color_pair(2))

    context.clear()

    key = ''
    while key != ord('q'):

        address_block.draw(context)
        byte_grid.draw(context)
        context.refresh()

        key = context.getch()
        if key == curses.KEY_DOWN:
            byte_grid.cursor_position = (byte_grid.cursor_position[0]+1, byte_grid.cursor_position[1])
            address_block.highlight_inx = byte_grid.cursor_position[0]
        if key == curses.KEY_UP:
            byte_grid.cursor_position = (byte_grid.cursor_position[0]-1, byte_grid.cursor_position[1])
            address_block.highlight_inx = byte_grid.cursor_position[0]
        if key == curses.KEY_LEFT:
            byte_grid.cursor_position = (byte_grid.cursor_position[0], byte_grid.cursor_position[1]-1)
            address_block.highlight_inx = byte_grid.cursor_position[0]
        if key == curses.KEY_RIGHT:
            byte_grid.cursor_position = (byte_grid.cursor_position[0], byte_grid.cursor_position[1]+1)
            address_block.highlight_inx = byte_grid.cursor_position[0]

    curses.endwin()

def main(stdscr):
    keyloop(stdscr)

if __name__ == '__main__':
    curses.wrapper(main)
