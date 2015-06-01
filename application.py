import os.path
import sys
import curses

from GUI.address_block import *
from GUI.byte_grid import *
from GUI.ui_utils import Rectangle as Rect

import file_buffer


class Application:
    def __init__(self, context, file_path):
        pass

    def __init_GUI(self):
        self.address_block = AddressBlock(Rect(0,0,8,max_y))
        self.address_block.start_address = 0
        self.address_block.color = 2
        self.address_block.highlight = 3
        self.address_block.highlight_inx = 0

        self.byte_grid = ByteGrid(Rect(self.address_block.draw_zone.width + 1,
                                       0,
                                       max_x - self.address_block.draw_zone.width - 1,
                                       max_y))
        self.byte_grid.color = 2
        self.byte_grid.highlight = 3
        self.byte_grid.data = bytearray()
        self.byte_grid.cursor_position = (1, 1)

        self.address_block.step = self.byte_grid.col_count

    def __init_context(self, context):
        pass


