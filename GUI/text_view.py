import curses

class TextView:
    def __init__(self, view_zone):
        self.draw_zone = view_zone
        self.color = 1
        self.highlight_index = -1
        self.highlight_color = 1
        self.symbol_in_row = 8 #кол-во символов в одной строке
        self.invisible_symbol = ord('.')
        self.data = []

    # Проверяет может ли быть отображен символ в ascii кодировке
    def __is_visual(self, symbol):
        return 33 < symbol < 127

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
    def invisible_symbol(self):
        return self.__invisible_symbol

    @invisible_symbol.setter
    def invisible_symbol(self, symbol):
        #символ должен быть визуальным
        if self.__is_visual(symbol):
            self.__invisible_symbol = symbol

    @property
    def highlight_index(self):
        return self.__highlight_index

    @highlight_index.setter
    def highlight_index(self, index):
        self.__highlight_index = index

    @property
    def highlight_color(self):
        return self.__highlight_color

    @highlight_color.setter
    def highlight_color(self, color):
        self.__highlight_color = color

    @property
    def symbol_in_row(self):
        return self.__symbol_in_row

    @symbol_in_row.setter
    def symbol_in_row(self, count):
        if 0 < count <= self.draw_zone.width:
            self.__symbol_in_row = count

    @property
    def data(self):
        return self.__data

    @data.setter
    def data(self, data):
        """data - одномерный массив, содержащий байты отображаемых данных"""
        if len(data) <= self.symbol_in_row * self.draw_zone.height:
            self.__data = data
        else:
            raise Exception("Data length more than TextView size")

    def draw(self, context):
        context.attrset(curses.color_pair(self.color))

        for row in range(self.draw_zone.height):
            for col in range(self.symbol_in_row):
                context.move(self.draw_zone.top + row,
                             self.draw_zone.left + col)

                sym_inx = row * self.symbol_in_row + col

                if self.highlight_index == sym_inx:
                    context.attrset(curses.color_pair(self.highlight_color))

                if sym_inx < len(self.data):
                    if self.__is_visual(self.data[sym_inx]):
                        context.addch(chr(self.__data[sym_inx]))
                    else:
                        context.addch(chr(self.invisible_symbol))

                if self.highlight_index == sym_inx:
                    context.attrset(curses.color_pair(self.color))
