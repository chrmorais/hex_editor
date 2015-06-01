import unittest

from GUI.byte_grid import ByteGrid
from GUI.ui_utils import Rectangle as Rect

class TestByteGrid(unittest.TestCase):

    def setUp(self):
        self.model = ByteGrid(Rect(1,1,20,20))

    def test_row_and_col_count(self):
        self.model.row_count = -1
        self.model.col_count = -1

        self.assertTrue(self.model.row_count != -1)
        self.assertTrue(self.model.col_count != -1)

    def test_autosize(self):
        self.model.row_count = 0
        self.model.col_count = 0

        self.model.draw_zone = Rect(0,0,20,20)
        self.model.autosize()

        self.assertTrue(self.model.row_count != 0)
        self.assertTrue(self.model.col_count != 0)

    def test_cursor_position(self):
        self.model.draw_zone = Rect(0,0,20,20)

        self.model.cursor_position = (30,30)
        self.assertTrue(self.model.cursor_position != (30,30))

        self.model.cursor_position = (-1,-1)
        self.assertTrue(self.model.cursor_position != (-1,-1))

    def tearDown(self):
        pass
