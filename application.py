import os.path
import curses

from GUI.address_block import *
from GUI.byte_grid import *
from GUI.text_view import *
from GUI.status_line import *
from GUI.ui_utils import Rectangle as Rect

from event import Event
import listeners
import file_buffer


class Application:
    def __init__(self, context, file_path):
        self.__file_path = file_path
        self.__offset_in_file = 0
        self.__file_size = os.stat(file_path).st_size

        self.__event_history = []
        self.__listeners = []
        listeners.link_listeners(self)

        file_buffer.init(128)
        file_buffer.open_file(file_path)

        self.__context = context
        self.__init_context(self.__context)
        self.__max_y, self.__max_x = self.__context.getmaxyx()

        self.__init_GUI()

        self.go_to(0)

    def __init_GUI(self):
        self.address_block = AddressBlock(Rect(0, 1, 8, self.__max_y-1))
        self.address_block.start_address = 0
        self.address_block.color = 2
        self.address_block.highlight = 3
        self.address_block.highlight_inx = 0

        busy_space = self.address_block.draw_zone.width
        ratio = (self.__max_x + 1 - busy_space) / 4
        self.byte_grid = ByteGrid(Rect(busy_space + 1,
                                       1,
                                       ratio*3,
                                       self.__max_y-1))
        self.byte_grid.color = 2
        self.byte_grid.highlight = 3
        self.byte_grid.data = bytearray()
        self.byte_grid.cursor_position = (1, 1)
        self.byte_grid.autosize()

        busy_space += self.byte_grid.draw_zone.width + 1

        self.address_block.step = self.byte_grid.col_count

        self.text_view = TextView(Rect(busy_space,
                                       1,
                                       self.byte_grid.col_count,
                                       self.__max_y-1))
        self.text_view.symbol_in_row = self.byte_grid.col_count
        self.text_view.color = 2
        self.text_view.highlight_color = 3

        self.status_line = StatusLine(Rect(0, 0, self.__max_x+1, 1))
        self.status_line.file_name = os.path.basename(self.__file_path)
        self.status_line.offset = self.__offset_in_file
        self.status_line.color = 4

    def __init_context(self, context):

        if curses.has_colors():
            curses.init_pair(1, curses.COLOR_YELLOW, curses.COLOR_BLUE)
            curses.init_pair(2, curses.COLOR_WHITE, curses.COLOR_BLUE)
            curses.init_pair(3, curses.COLOR_BLUE, curses.COLOR_WHITE)
            curses.init_pair(4, curses.COLOR_BLACK, curses.COLOR_CYAN)

        context.bkgdset(curses.color_pair(2))

    def keyloop(self):
        self.__context.clear()

        while True:

            self.status_line.draw(self.__context)
            self.address_block.draw(self.__context)
            self.byte_grid.draw(self.__context)
            self.text_view.draw(self.__context)
            self.__context.refresh()

            key = self.__context.getch()
            self.__event_history.append(Event('key_press', {'key': key}))
            self.__notify()

    def attach_listener(self, listener):
        if listener not in self.__listeners:
            self.__listeners.append(listener)

    def detach_listener(self, listener):
        self.__listeners.remove(listener)

    def __notify(self):
        for listener in self.__listeners:
            listener.update(self)

    def exit(self):
        file_buffer.close_file()
        curses.endwin()
        exit()

    @property
    def event_history(self):
        return self.__event_history

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

    @property
    def offset_in_file(self):
        return self.__offset_in_file

    def go_to(self, offset):
        "Позволяет перейти к произвольному байту в файле"
        if offset >= self.__file_size:
            return

        self.__offset_in_file = offset
        data = []
        for byte_offset in range(self.__file_size - offset):
            data.append(ord(file_buffer.get_byte(offset + byte_offset)))

        data = bytearray(data)
        self.byte_grid.data = data
        self.text_view.data = data
        self.address_block.start_address = offset
