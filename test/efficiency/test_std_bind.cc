#include "pre_compiled.h"

#define MAX_SIZE        (1000 * 1000)

class Test
{
public :
        void TestBind(int t) { }
};

void myBind(int t) { }

int main(void)
{
        typedef std::function<void()> callback;
        std::vector<callback> cbList;
        /*
        cbList.resize(MAX_SIZE);
        cbList.clear();
        */
        cbList.reserve(MAX_SIZE);
        {
                Test test;
                CTimeCost t("bind");
                for (int i=0; i<MAX_SIZE; ++i)
                        cbList.push_back(std::bind(&Test::TestBind, test, i));
        }
        printf("cbList.size() = %lu\n", cbList.size());

        {
                CTimeCost t("call bind");
                for (int i=0; i<MAX_SIZE; ++i)
                        cbList[i]();
        }

        typedef void(*func)(int);
        func funcList[MAX_SIZE];
        {
                CTimeCost t("func point");
                for (int i=0; i<MAX_SIZE; ++i)
                {
                        funcList[i] = &myBind;
                }
        }

        {
                CTimeCost t("call func");
                for (int i=0; i<MAX_SIZE; ++i)
                        funcList[i](i);
        }

        return 0;
}
