import unittest

from GUI.address_block import AddressBlock
from GUI.ui_utils import Rectangle as Rect

class TestAddressBlock(unittest.TestCase):

    def setUp(self):
        self.model = AddressBlock(Rect(1,2,3,4))

    def test_correct_size(self):
        address_block = AddressBlock(Rect(1,2,3,4))
        self.assertTrue(address_block.draw_zone.left == 1)
        self.assertTrue(address_block.draw_zone.top == 2)
        self.assertTrue(address_block.draw_zone.width == 3)
        self.assertTrue(address_block.draw_zone.height == 4)

    def test_start_address(self):
        #Адрес не может быть отрицательным числом
        self.model.start_address = -1
        self.assertTrue(self.model.start_address >= 0)

        self.model.start_address = 0
        self.assertTrue(self.model.start_address == 0)

    def test_step(self):
        self.model.step = -1
        self.assertTrue(self.model.step >= 0)

        self.model.step = 0
        self.assertTrue(self.model.step != 0)

        self.model.step = 1
        self.assertTrue(self.model.step == 1)

    def tearDown(self):
        pass
