#include "tester.h"
#include <cassert>

#include "vector.h"

Tester::Tester()
{
}

void Tester::run()
{
    testVectorReflect();
}

void Tester::testVectorReflect()
{
    Vector3 n(0, 1, 0);
    Vector3 in(1, -1, 0);
    Vector3 r = in.reflect(n);
    Vector3 expect_r(1, 1, 0);
    assert((r == expect_r) && "test vector reflect!");
}
