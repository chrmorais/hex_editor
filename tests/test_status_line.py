import unittest

from GUI.status_line import StatusLine
from GUI.ui_utils import Rectangle as Rect

class TestStatusLine(unittest.TestCase):

    def setUp(self):
        self.model = StatusLine(Rect(0,0,80,1))

    def test_correct_size(self):
        status_line = StatusLine(Rect(0,0,80,10))
        self.assertTrue(status_line.draw_zone.left == 0)
        self.assertTrue(status_line.draw_zone.top == 0)
        self.assertTrue(status_line.draw_zone.width == 80)
        self.assertTrue(status_line.draw_zone.height == 1)

    def test_correct_offset(self):
        #Смещение не может быть отрицательным числом
        self.model.offset = -1
        self.assertTrue(self.model.offset >= 0)

        self.model.offset = 0
        self.assertTrue(self.model.offset == 0)

    def tearDown(self):
        pass
