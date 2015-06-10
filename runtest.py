import unittest

from tests.test_address_block import TestAddressBlock
from tests.test_byte_grid import TestByteGrid
from tests.test_text_view import TestTextView

suite = unittest.TestLoader().loadTestsFromTestCase(TestAddressBlock)
suite.addTest(unittest.TestLoader().loadTestsFromTestCase(TestByteGrid))
suite.addTest(unittest.TestLoader().loadTestsFromTestCase(TestTextView))

unittest.TextTestRunner(verbosity=2).run(suite)
