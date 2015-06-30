import curses


class CommandLine():
    def __init__(self, view_zone):
        view_zone.height = 1
        self.draw_zone = view_zone
        self.active = False
        self.color = 1
        self.text = ''
        self.cursor_pos = 0

    @property
    def draw_zone(self):
        return self.__draw_zone

    @draw_zone.setter
    def draw_zone(self, zone):
        self.__draw_zone = zone

    @property
    def active(self):
        return self.__active

    @active.setter
    def active(self, is_active):
        self.__active = is_active

    @property
    def color(self):
        return self.__color

    @color.setter
    def color(self, color):
        self.__color = color

    @property
    def text(self):
        return self.__text

    @text.setter
    def text(self, text):
        if len(text) > self.draw_zone.width:
            text = text[:self.draw_zone.width]

        self.__text = text

    @property
    def cursor_pos(self):
        return self.__cursor_pos

    @cursor_pos.setter
    def cursor_pos(self, pos):
        if pos < self.draw_zone.width:
            self.__cursor_pos = pos
