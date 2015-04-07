import curses

from ui_utils import Rectangle as Rect

class ByteGrid:
    def __init__(self, view_zone):
        self.draw_zone = view_zone
        self.color = 1
        self.highlight = 1

    @property
    def draw_zone(self):
        return self.__draw_zone

    @draw_zone.setter
    def draw_zone(self, zone):
        self.__draw_zone = zone

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

