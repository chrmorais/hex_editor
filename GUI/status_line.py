import curses


class StatusLine():
    def __init__(self, view_zone):
        self.draw_zone = view_zone
        self.file_name = ''
        self.file_size = 0
        self.offset = 0
        self.color = 1

    @property
    def draw_zone(self):
        return self.__draw_zone

    @draw_zone.setter
    def draw_zone(self, zone):
        self.__draw_zone = zone
        self.draw_zone.height = 1 #высота статусной строки не может быть >1

    @property
    def file_name(self):
        return self.__file_name

    @file_name.setter
    def file_name(self, file_name):
        self.__file_name = file_name

    @property
    def offset(self):
        return self.__offset

    @offset.setter
    def offset(self, offset):
        if offset >= 0:
            self.__offset = offset

    @property
    def file_size(self):
        return self.__file_size

    @file_size.setter
    def file_size(self, size):
        self.__file_size = size

    @property
    def color(self):
        return self.__color

    @color.setter
    def color(self, color):
        self.__color = color

    def draw(self, context):
        context.attrset(curses.color_pair(self.color))
        context.move(self.draw_zone.top, self.draw_zone.left)

        status_str = self.file_name + ' | ' + '0x{:08X}'.format(self.offset)
        status_str += "(%d/%d)" % (self.offset, self.file_size-1)

        #строка должна быть во всю ширину экрана, чтобы не было видно фона
        status_str += ' ' * (self.draw_zone.width - len(status_str))

        context.addstr(status_str)

