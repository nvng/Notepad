#include "pre_compiled.h"

#define LOOP_TIMES      (1000 * 1000)
#define STR_VAL         ("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa \
                aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa \
                aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa \
                aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa \
                aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa \
                aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa \
                aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa \
                aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa \
                aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")

class Test_1
{
public :
        Test_1()
                : a_1(0)
                  , a_2(0)
                  , a_3(0)
                  , a_4(0)
                  , a_5(0)
                  , a_6(0)
                  , a_7(0)
                  , a_8(0)
                  , a_9(0)
                  , a_10(0)
                  , a_11(0)
                  , a_12(STR_VAL)
        {
        }

private :
        int32_t a_1;
        int32_t a_2;
        int32_t a_3;
        int32_t a_4;
        int32_t a_5;
        int32_t a_6;
        int32_t a_7;
        int32_t a_8;
        int32_t a_9;
        int32_t a_10;
        int32_t a_11;
        std::string a_12;
};

class Test_2
{
public :
        Test_2()
        {
                a_1 = 0;
                a_2 = 0;
                a_3 = 0;
                a_4 = 0;
                a_5 = 0;
                a_6 = 0;
                a_7 = 0;
                a_8 = 0;
                a_9 = 0;
                a_10 = 0;
                a_11 = 0;
                a_12 = STR_VAL;
        }

private :
        int32_t a_1;
        int32_t a_2;
        int32_t a_3;
        int32_t a_4;
        int32_t a_5;
        int32_t a_6;
        int32_t a_7;
        int32_t a_8;
        int32_t a_9;
        int32_t a_10;
        int32_t a_11;
        std::string a_12;
};

int main(void)
{
        Test_1* p = nullptr;
        {
                CTimeCost t("initialization list");
                for (int i=0; i<LOOP_TIMES; ++i)
                        p = new Test_1();
        }
        (void)p;

        Test_2* p_2 = nullptr;
        {
                CTimeCost t("assign");
                for (int i=0; i<LOOP_TIMES; ++i)
                        p_2 = new Test_2();
        }
        (void)p_2;

        return 0;
}
