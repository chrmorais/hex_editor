class Rectangle:

    def __init__(self, left=0, top=0, width=0, heigth=0):
        self.left   = left
        self.top    = top
        self.width  = width
        self.height = heigth

    def __str__(self):
        return "({0}, {1}, {2}, {3})".format(self.left,
                                            self.top,
                                            self.width,
                                            self.height)

    def __repr__(self):
        return self.__str__()

    @property
    def left(self):
        return self.__left

    @left.setter
    def left(self, value):
        self.__left = value

    @property
    def top(self):
        return self.__top

    @top.setter
    def top(self, value):
        self.__top = value

    @property
    def width(self):
        return self.__width

    @width.setter
    def width(self, value):
        self.__width = value

    @property
    def height(self):
        return self.__height

    @height.setter
    def height(self, value):
        self.__height = value
