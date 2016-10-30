#define MAX_LOOP_CNT    (1000 * 1000)

int main(void)
{
        {
                std::vector<int32_t> testList;
                testList.reserve(MAX_LOOP_CNT);
                CTimeCost t("push_back");
                for (int i=0; i<MAX_LOOP_CNT; ++i)
                        testList.push_back(i);
        }

        {
                std::vector<int32_t> testList;
                testList.reserve(MAX_LOOP_CNT);
                CTimeCost t("no push_back");
                for (int i=0; i<MAX_LOOP_CNT; ++i)
                        testList[i] = i;
        }

        return 0;
}
