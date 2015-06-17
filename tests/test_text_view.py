import unittest

from GUI.text_view import TextView
from GUI.ui_utils import Rectangle as Rect

class TestTextView(unittest.TestCase):

    def setUp(self):
        self.model = TextView(Rect(0,0,10,10))

    def test_set_not_correct_invisible_symbol(self):
        self.model.invisible_symbol = ord('.')
        self.model.invisible_symbol = 0

        self.assertTrue(self.model.invisible_symbol != 0)

    def test_set_data_size_more_than_allow(self):
        data = bytearray(range(self.model.symbol_in_row *
                               self.model.draw_zone.height + 1))

        with self.assertRaises(Exception):
            self.model.data = data

    def test_set_symbol_in_row_more_than_width(self):
        self.model.symbol_in_row = -1
        self.model.symbol_in_row = self.model.draw_zone.width + 1

        self.assertTrue(0 < self.model.symbol_in_row <= self.model.draw_zone.width)

    def tearDown(self):
        pass
