/* file : set_vs_unordered_set_small.cc --> set 和 unordered_set 小量数据时效率对比
 * result : 380左右为分界点，较大量数据时，unordered_set 有明显优势。
 * desc : unordered_set 无序的，使用的是 hash table. set 为树
 */

template <typename T>
void testSet(T obj, std::vector<int32_t>& randList)
{
        {
                CTimeCost t("insert");
                for (int32_t val : randList)
                        obj.insert(val);
        }

        {
                CTimeCost t("find");
                for (int i=0; i<1000 * 100; ++i)
                        for (int32_t val : randList)
                                obj.find(val);
        }

        uint64_t tmp = 0;
        (void)tmp;
        {
                CTimeCost t("traversal");
                for (int i=0; i<1000 * 100; ++i)
                        for (typename T::value_type val : obj)
                                tmp = val;
        }

        {
                CTimeCost t("erase");
                for (int32_t val : randList)
                        obj.erase(val);
        }
}

int main(void)
{
        srand(time(NULL));

        std::vector<int32_t> gRandList;
        const int32_t times = 380;
        for (int32_t i=0; i<times; ++i)
                gRandList.push_back(rand());

        printf("=============== unordered_set ===============\n");
        testSet(std::unordered_set<uint64_t>(), gRandList);
        printf("==================== set ====================\n");
        testSet(std::set<uint64_t>(), gRandList);

        return 0;
}
