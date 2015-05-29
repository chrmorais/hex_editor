import unittest

from tests.test_address_block import TestAddressBlock
from tests.test_byte_grid import TestByteGrid

suite = unittest.TestLoader().loadTestsFromTestCase(TestAddressBlock)
suite.addTest(unittest.TestLoader().loadTestsFromTestCase(TestByteGrid))

unittest.TextTestRunner(verbosity=2).run(suite)
