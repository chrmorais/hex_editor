import unittest

from tests.test_address_block import TestAddressBlock
from tests.test_byte_grid import TestByteGrid
from tests.test_text_view import TestTextView
from tests.test_status_line import TestStatusLine

suite = unittest.TestLoader().loadTestsFromTestCase(TestAddressBlock)
suite.addTest(unittest.TestLoader().loadTestsFromTestCase(TestByteGrid))
suite.addTest(unittest.TestLoader().loadTestsFromTestCase(TestTextView))
suite.addTest(unittest.TestLoader().loadTestsFromTestCase(TestStatusLine))

unittest.TextTestRunner(verbosity=2).run(suite)
