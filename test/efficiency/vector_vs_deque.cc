int main(void)
{
        std::vector<void*> tmpList;
        // tmpList.reserve(1000);
        {
                CTimeCost t("vector");
                for (int i=0; i<1000; ++i)
                {
                        int pos = 0;
                        (void)pos;
                        for (int j=0; j<100000; ++j)
                                // tmpList[pos++] = nullptr;
                                tmpList.push_back(nullptr);

                        for (int j=0; j<100000; ++j)
                                tmpList.pop_back();
                                // tmpList[--pos] = nullptr;
                }
        }

        std::deque<void*> tmpQueue;
        {
                CTimeCost t("deque");
                for (int i=0; i<1000; ++i)
                {
                        for (int j=0; j<100000; ++j)
                                tmpQueue.push_back(nullptr);

                        for (int j=0; j<100000; ++j)
                                tmpQueue.pop_front();
                }
        }

        return 0;
}
