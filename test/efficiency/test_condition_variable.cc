std::condition_variable gCond;
std::vector<int32_t> testList;

#define MAX_LOOP_CNT (1000 * 1000)

int main(void)
{
        int i=0;
        (void)i;
        {
                CTimeCost t("cond");
                for (int i=0; i<MAX_LOOP_CNT; ++i)
                {
                        testList.push_back(i);
                        testList.clear();
                        gCond.notify_all();
                }
        }

        {
                CTimeCost t("no cond");
                for (int i=0; i<MAX_LOOP_CNT; ++i)
                {
                        testList.push_back(i);
                        testList.clear();
                }
        }

        return 0;
}
