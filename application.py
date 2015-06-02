import os.path
import sys
import curses

from GUI.address_block import *
from GUI.byte_grid import *
from GUI.ui_utils import Rectangle as Rect

import file_buffer


class Application:
    def __init__(self, context, file_path):
        self.__file_size = os.stat(file_path).st_size

        file_buffer.init(128)
        file_buffer.open_file(file_path)

        self.__context = context

        self.__init_context(self.__context)
        self.__max_y, self.__max_x = self.__context.getmaxyx()

        self.__init_GUI()


    def __init_GUI(self):
        self.address_block = AddressBlock(Rect(0,0,8,self.__max_y))
        self.address_block.start_address = 0
        self.address_block.color = 2
        self.address_block.highlight = 3
        self.address_block.highlight_inx = 0

        self.byte_grid = ByteGrid(Rect(self.address_block.draw_zone.width + 1,
                                       0,
                                       self.__max_x - self.address_block.draw_zone.width - 1,
                                       self.__max_y))
        self.byte_grid.color = 2
        self.byte_grid.highlight = 3
        self.byte_grid.data = bytearray()
        self.byte_grid.cursor_position = (1, 1)
        self.byte_grid.autosize()

        self.address_block.step = self.byte_grid.col_count

    def __init_context(self, context):

        if curses.has_colors():
            curses.init_pair(1, curses.COLOR_YELLOW, curses.COLOR_BLUE)
            curses.init_pair(2, curses.COLOR_WHITE, curses.COLOR_BLUE)
            curses.init_pair(3, curses.COLOR_BLUE, curses.COLOR_WHITE)

        context.bkgdset(curses.color_pair(2))

    def keyloop(self):

        data = []
        data_size = self.byte_grid.col_count * self.byte_grid.row_count
        if data_size > self.__file_size:
            data_size = self.__file_size

        for i in range(data_size):
            data.append(ord(file_buffer.get_byte(i)))

        self.byte_grid.data = bytearray(data)
        self.__context.clear()

        key = ''
        while key != ord('q'):

            self.address_block.draw(self.__context)
            self.byte_grid.draw(self.__context)
            self.__context.refresh()

            key = self.__context.getch()
            if key == curses.KEY_DOWN:
                self.byte_grid.cursor_position = \
                    (self.byte_grid.cursor_position[0]+1,
                     self.byte_grid.cursor_position[1])
                self.address_block.highlight_inx = \
                    self.byte_grid.cursor_position[0]
            if key == curses.KEY_UP:
                self.byte_grid.cursor_position = \
                    (self.byte_grid.cursor_position[0]-1,
                    self.byte_grid.cursor_position[1])
                self.address_block.highlight_inx = \
                    self.byte_grid.cursor_position[0]
            if key == curses.KEY_LEFT:
                self.byte_grid.cursor_position = \
                   (self.byte_grid.cursor_position[0],
                    self.byte_grid.cursor_position[1]-1)
                self.address_block.highlight_inx = \
                    self.byte_grid.cursor_position[0]
            if key == curses.KEY_RIGHT:
                self.byte_grid.cursor_position = \
                    (self.byte_grid.cursor_position[0],
                    self.byte_grid.cursor_position[1]+1)
                self.address_block.highlight_inx = \
                    self.byte_grid.cursor_position[0]

        self.exit()

    def exit(self):
        file_buffer.close_file()
        curses.endwin()

    @property
    def address_block(self):
        return self.__address_block

    @address_block.setter
    def address_block(self, widget):
        self.__address_block = widget

    @property
    def byte_grid(self):
        return self.__byte_grid

    @byte_grid.setter
    def byte_grid(self, widget):
        self.__byte_grid = widget
