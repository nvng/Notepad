#define MAX_LOOP_CNT    (1000 * 1000)

template <typename T>
void Operator(T& list, bool has_equal_range, std::string prefix)
{
        printf("============================================================\n");
        {
                std::string pre = prefix + " insert";
                CTimeCost t(pre.c_str());
                for (int i=0; i<MAX_LOOP_CNT; ++i)
                        list.insert(std::make_pair(i, i));
        }

        {
                CTimeCost t((prefix + " find").c_str());
                for (int i=0; i<MAX_LOOP_CNT; ++i)
                {
                        auto it = list.find(i);
                        if (list.end() == it)
                                printf("abc\n");
                }
        }

        if (has_equal_range)
        {
                CTimeCost t((prefix + " equal_range").c_str());
                for (int i=0; i<MAX_LOOP_CNT; ++i)
                {
                        auto range = list.equal_range(i);
                        if (range.first == range.second)
                                printf("abc\n");
                }
        }
}

int main(void)
{
        std::multimap<int, int> multiList;
        Operator(multiList, true, "multimap");

        std::unordered_multimap<int, int> unorderedMultiList;
        Operator(unorderedMultiList, true, "unordered_multimap");

        std::map<int, int> List;
        Operator(List, false, "map");
        std::unordered_map<int, int> unorderedList;
        Operator(unorderedList, false, "unordered_map");

        return 0;
}
