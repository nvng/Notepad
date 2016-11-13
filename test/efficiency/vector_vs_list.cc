#define MAX_COUNT       (1000 * 1000)

int main(void)
{
        std::vector<int64_t> tmpVec;
        std::list<int64_t> tmpList;

        {
                tmpVec.reserve(MAX_COUNT);
                CTimeCost t("vector push_back");
                for (int i=0; i<MAX_COUNT; ++i)
                        tmpVec.push_back((int64_t)i);
        }

        {
                CTimeCost t("list push_back");
                for (int i=0; i<MAX_COUNT; ++i)
                        tmpList.push_back((int64_t)i);
        }

        {
                tmpList.clear();
                CTimeCost t("list push_front");
                for (int i=0; i<MAX_COUNT; ++i)
                        tmpList.push_front((int64_t)i);
        }

        return 0;
}
