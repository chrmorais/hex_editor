import unittest

from tests.test_address_block import TestAddressBlock

suite = unittest.TestLoader().loadTestsFromTestCase(TestAddressBlock)
#suite.addTest(unittest.TestLoader().loadTestsFromTestCase(tests.list.TestList))

unittest.TextTestRunner(verbosity=2).run(suite)
