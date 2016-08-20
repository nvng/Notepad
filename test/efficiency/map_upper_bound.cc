/* file : map_upper_bound.cc --> 
 * result :
 * desc :
 */

#include "pre_compiled.h"

#define MAX_SIZE        (1000 * 1000)

template <typename T>
void mapOperator(T obj)
{
        static int32_t arr[] =
        {
                1000,
                10000,
                100000,
                999999,
        };

        std::vector<int32_t> keyList;
        for (int i=0; i<(int)(sizeof(arr)/sizeof(arr[0])); ++i)
        {
                auto it = obj.begin();
                std::advance(it, arr[i]);
                keyList.push_back(it->first);
        }

        for (auto val : keyList)
        {
                int32_t tmpVal = 0;
                (void)tmpVal;
                CTimeCost t("map upper_bound");
                auto ie = obj.upper_bound(val);
                for (auto it=obj.begin(); ie!=it; ++it)
                        tmpVal = it->second;
                // obj.erase(obj.begin(), ie);
        }

        printf("========= by handle ========\n");
        for (auto val : keyList)
        {
                int32_t tmpVal = 0;
                (void)tmpVal;
                CTimeCost t("map upper_bound");
                for (auto mapVal : obj)
                {
                        /*
                        if (mapVal.first <= val)
                                tmpVal = mapVal.second;
                                */
                        if (mapVal.first > val)
                                break;
                        tmpVal = mapVal.second;
                }
        }
}

int main(void)
{
        srand(time(NULL));

        std::vector<int32_t> randList(MAX_SIZE, 0);
        for (int32_t i=0; i<MAX_SIZE; ++i)
                randList[i] = rand() % MAX_SIZE;

        std::map<int32_t, int32_t> mapList;
        std::multimap<int32_t, int32_t> multimapList;
        for (auto val : randList)
        {
                mapList.insert(std::make_pair(val, val));
                for (int i=0; i<3; ++i)
                        multimapList.insert(std::make_pair(val, val));
        }

        printf("===================== map =============\n");
        mapOperator(mapList);
        printf("===================== multimap =============\n");
        mapOperator(multimapList);

        return 0;
}
