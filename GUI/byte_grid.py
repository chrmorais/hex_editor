import curses


class ByteGrid:
    def __init__(self, view_zone):
        self.draw_zone = view_zone
        self.color = 1
        self.highlight = 1
        self.row_count = 0
        self.col_count = 0
        self.__cursor_position = (0, 0)
        self.data = []

        self.autosize()

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

    @property
    def data(self):
        return self.__data

    @data.setter
    def data(self, data):
        """data - одномерный массив, содержащий байты отображаемых данных"""
        if len(data) <= self.row_count * self.col_count:
            self.__data = data
            self.cursor_position = (0, 0)
        else:
            raise Exception("Data length more than ByteGrid size")

    @property
    def row_count(self):
        return self.__row_count

    @row_count.setter
    def row_count(self, row_count):
        if row_count < 0:
            return

        if row_count <= self.draw_zone.height:
            self.__row_count = row_count
        else:
            raise Exception("Row count more than acceptable")

    @property
    def col_count(self):
        return self.__col_count

    @col_count.setter
    def col_count(self, col_count):
        if col_count < 0:
            return

        if col_count * 3 + 1 <= self.draw_zone.width:
            self.__col_count = col_count
        else:
            raise Exception("Column count more than acceptable")

    @property
    def cursor_position(self):
        return self.__cursor_position

    @cursor_position.setter
    def cursor_position(self, position):
        if(0 <= position[0] < self.row_count and
           0 <= position[1] < self.col_count and
           position[0]*self.col_count + position[1] < len(self.data)):
            self.__cursor_position = position

    def data_size(self):
        return self.row_count * self.col_count

    def autosize(self):
        """Устанавливает максимально возможные значения кол-ва
           строк и столбцов, основываясь на размерах виджета"""

        self.row_count = int((self.draw_zone.height))
        self.col_count = int((self.draw_zone.width - 1) / 3)
        self.draw_zone.height = self.row_count
        self.draw_zone.width = self.col_count * 3 + 1

    def draw(self, context):
        context.attrset(curses.color_pair(self.color))
        for row in range(self.row_count):
            for col in range(self.col_count):
                context.move(self.draw_zone.top + (row),
                             self.draw_zone.left + (col*3))

                if not(0 <= self.__data[row*self.col_count+col] <= 256):
                    raise Exception("%s in not ascii symbol" %
                                    self.__data[row*self.col_count+col])

                if(row == self.__cursor_position[0] and
                   col == self.__cursor_position[1]):
                    context.attrset(curses.color_pair(self.highlight))

                if row * self.col_count + col < len(self.data):
                    context.addstr('{:02X}'.format(
                        self.__data[row*self.col_count+col]))

                if(row == self.__cursor_position[0] and
                   col == self.__cursor_position[1]):
                    context.attrset(curses.color_pair(self.color))
