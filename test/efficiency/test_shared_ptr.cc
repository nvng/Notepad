#include "pre_compiled.h"

class Test
{
public :
        Test() { printf("Test::Test()\n"); }
        ~Test() { printf("Test::~Test()\n"); }
private :
        int i;
};
typedef std::shared_ptr<Test> TestPtr;

// 只是创建 shared_ptr 对象，没有 Test对象。生存周期同 testFunc2
void testFunc(const TestPtr& t = TestPtr())
{
        printf("testFunc\n");
}

// 参数的周期和函数内的变量一样，它在 { 之前创建或赋值。
void testFunc2(const Test& t = Test())
{
        printf("testFunc2\n");
}

// 如果创建的是临时对象，则创建之后马上析构。
void testFunc3()
{
        const Test& t = Test();
        printf("testFunc3\n");
}

/*
const Test& testFunc4(Test t = Test())
{
        return t; // error : return temprary val
}
*/

int main(void)
{
        // TestPtr tp(new Test());
        /*
        printf("before call testFunc\n");
        testFunc(tp);
        printf("after  call testFunc\n");
        */

        /*
        printf("before call testFunc\n");
        testFunc2();
        printf("after  call testFunc\n");
        */

        /*
        printf("before call testFunc\n");
        testFunc3();
        printf("after  call testFunc\n");
        */

        TestPtr tp(new Test());
        std::weak_ptr<Test> wpt = tp;
        {
                // const TestPtr& t = wpt.lock();
                // printf("use_count = %lu\n", tp.use_count());

                // const Test& t = Test();
                Test();
                printf("use_count = %lu\n", tp.use_count());
        }
        printf("use_count = %lu\n", tp.use_count());

        /*
        printf("before call testFunc4\n");
        testFunc4();
        printf("after  call testFunc4\n");
        */


        {
                std::shared_ptr<void> spv;
                printf("aaaaa use_count = %lu\n", tp.use_count());
                spv = tp;
                printf("bbbbb use_count = %lu\n", tp.use_count());
        }
        printf("ccccc use_count = %lu\n", tp.use_count());
        // spv = std::make_shared<int32_t>();

        /*
        int c = spv->i;
        (void)c;
        */

        return 0;
}
