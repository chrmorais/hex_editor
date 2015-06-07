class Event:
    def __init__(self, type, data={}):

        self.type = type
        self.data = data

    @property
    def type(self):
        return self.__type

    @type.setter
    def type(self, type):
        if type is None:
            raise Exception("Event type can not be None!")
        else:
            self.__type = type

    @property
    def data(self):
        return self.__data

    @data.setter
    def data(self, data):
        self.__data = data
