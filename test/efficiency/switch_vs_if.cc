/* file : switch_vs_if.cc --> switch 和 if 做枚举有效性判断效率对比
 * result : 两者效率相当，都快点可以忽略不计的程度。但 if else 判断居然也差不多。
 * desc : switch 适合所有情况，连接和非连续，但写起来有点麻烦。
 *        if 只适合连续情况。
 *        多个 if 做多余判断，编译器居然优化得那么变态，最好别用这种方式
 */

enum ETest
{
        ET_0,
        ET_1,
        ET_2,
        ET_3,
        ET_4,
        ET_5,
        ET_6,
        ET_7,
        ET_8,
        ET_9,
        ET_10,
        ET_COUNT,
};

bool IsValid(ETest t)
{
        switch (t)
        {
        case ET_0:
        case ET_1:
        case ET_2:
        case ET_3:
        case ET_4:
        case ET_5:
        case ET_6:
        case ET_7:
        case ET_8:
        case ET_9:
        case ET_10:
                return true;
                break;
        default : return false; break;
        }
}

bool IsValidIF(ETest t)
{
        bool ret = false;
        if (ET_0 == t)  ret = true;
        if (ET_1 == t)  ret = true;
        if (ET_2 == t)  ret = true;
        if (ET_3 == t)  ret = true;
        if (ET_4 == t)  ret = true;
        if (ET_5 == t)  ret = true;
        if (ET_6 == t)  ret = true;
        if (ET_7 == t)  ret = true;
        if (ET_8 == t)  ret = true;
        if (ET_9 == t)  ret = true;
        if (ET_10 == t) ret = true;
        return ret;
}

#define MAX_LOOP_CNT    (1000 * 1000 * 100)

int main(void)
{
        srand(time(nullptr));

        std::vector<int32_t> tmpList;
        tmpList.reserve(MAX_LOOP_CNT);
        for (int i=0; i<MAX_LOOP_CNT; ++i)
                tmpList.push_back(rand() % 11);

        /*
        for (int i=0; i<100; ++i)
                printf("%d ", tmpList[i]);
        putchar('\n');
        */

        bool ret = false;
        (void)ret;
        {
                CTimeCost t("switch");
                for (int i=0; i<MAX_LOOP_CNT; ++i)
                        ret = IsValid((ETest)tmpList[i]);
        }

        {
                CTimeCost t("if");
                for (int i=0; i<MAX_LOOP_CNT; ++i)
                        ret = tmpList[i]>=0 && tmpList[i]<=ET_COUNT;
        }

        {
                CTimeCost t("if more");
                for (int i=0; i<MAX_LOOP_CNT; ++i)
                        ret = IsValidIF((ETest)tmpList[i]);
        }

        return 0;
}
