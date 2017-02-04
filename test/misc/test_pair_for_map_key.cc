#define MAX_LOOP_CNT    (1000 * 1000 * 10)

int main(void)
{
        std::map<std::tuple<int, int, int, int, int, int, int, int>, int> testListTuple;
        std::map<int, int> testListGuid;
        std::map<std::pair<int, int>, int> testList;
        /*
        for (int i=0; i<MAX_LOOP_CNT; ++i)
        {
                testListTuple.insert(std::make_pair(std::make_tuple(i, i, i, i), i));
                testList.insert(std::make_pair(std::make_pair(i, i), i));
                testListGuid.insert(std::make_pair(i, i));
        }
        */

        {
                CTimeCost t("tuple insert");
                for (int i=0; i<MAX_LOOP_CNT; ++i)
                        testListTuple.insert(std::make_pair(std::make_tuple(i, i, i, i, i, i, i, i), i));
        }

        {
                const auto key = std::make_tuple(
                                MAX_LOOP_CNT-1,
                                MAX_LOOP_CNT-1,
                                MAX_LOOP_CNT-1,
                                MAX_LOOP_CNT-1,
                                MAX_LOOP_CNT-1,
                                MAX_LOOP_CNT-1,
                                MAX_LOOP_CNT-1,
                                MAX_LOOP_CNT-1
                                );
                CTimeCost t("tuple");
                for (int i=0; i<1000 * 1000; ++i)
                {
                        auto it = testListTuple.find(key);
                        if (testListTuple.end() == it)
                                printf("not found\n");
                }
        }

        {
                CTimeCost t("pair insert");
                for (int i=0; i<MAX_LOOP_CNT; ++i)
                        testList.insert(std::make_pair(std::make_pair(i, i), i));
        }

        {
                const auto key = std::make_pair(MAX_LOOP_CNT-1, MAX_LOOP_CNT-1);
                CTimeCost t("pair");
                for (int i=0; i<1000*1000; ++i)
                {
                        auto it = testList.find(key);
                        if (testList.end() == it)
                                printf("not found\n");
                }
        }

        {
                CTimeCost t("int insert");
                for (int i=0; i<MAX_LOOP_CNT; ++i)
                        testListGuid.insert(std::make_pair(i, i));
        }

        {
                CTimeCost t("int");
                for (int i=0; i<1000 * 1000; ++i)
                {
                        auto it = testListGuid.find(MAX_LOOP_CNT-1);
                        if (testListGuid.end() == it)
                                printf("not found\n");
                }
        }

        return 0;
}
