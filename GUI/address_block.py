import curses
import sys

from ui_utils import Rectangle as Rect

class AddressBlock():
    def __init__(self, view_zone):
        self.draw_zone = view_zone
        self.start_address = 0
        self.step = 1
        self.color = 1
        self.highlight = 1
        self.highlight_inx = -1

    @property
    def draw_zone(self):
        return self.__draw_zone

    @draw_zone.setter
    def draw_zone(self, zone):
        self.__draw_zone = zone

    @property
    def start_address(self):
        return self.__start_address

    @start_address.setter
    def start_address(self, start):
        if start >= 0:
            self.__start_address = start

    @property
    def step(self):
        return self.__step

    @step.setter
    def step(self, step):
        if step > 0:
            self.__step = step

    @property
    def color(self):
        return self.__color

    @color.setter
    def color(self, color):
        self.__color = color

    @property
    def highlight(self):
        return self.__highlight

    @highlight.setter
    def highlight(self, color):
        self.__highlight = color

    @property
    def highlight_inx(self):
        return self.__highlight_inx

    @highlight_inx.setter
    def highlight_inx(self, inx):
        self.__highlight_inx = inx

    def draw(self, context):
        context.attrset(curses.color_pair(self.color))

        for row in range(self.draw_zone.height):
            context.move(self.draw_zone.top + row,
                         self.draw_zone.left)

            if row == self.highlight_inx:
                context.attrset(curses.color_pair(self.highlight))

            context.addstr(self.draw_zone.top + row,
                           self.draw_zone.left,
                           '{:08X}'.format(self.start_address+row*self.step))

            if row == self.highlight_inx:
                context.attrset(curses.color_pair(self.color))
