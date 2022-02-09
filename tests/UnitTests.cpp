#include <utest.h>
#include "backend.h"
UTEST_MAIN();

// UTEST(Group, TestName)
UTEST(Backend, Test1)
{
    EventNode *n = new EventNode;
    n->date.tm_mday = 1;
    ASSERT_EQ(n->date.tm_mday, 1);
}