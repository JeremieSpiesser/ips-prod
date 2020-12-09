#include <cxxtest/TestSuite.h>
#include <armadillo>
#include "../headers/utils.h"

class TestUtils : public CxxTest::TestSuite
{
public:
    void testFact(void) {
        TS_ASSERT_EQUALS(Utils::fact(0), 1);
        TS_ASSERT_EQUALS(Utils::fact(1), 1);
        TS_ASSERT_EQUALS(Utils::fact(2), 2);
        TS_ASSERT_EQUALS(Utils::fact(3), 6);
        TS_ASSERT_EQUALS(Utils::fact(10), 3628800);
    }
};