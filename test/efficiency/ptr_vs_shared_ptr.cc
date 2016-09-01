/* file : ptr_vs_shared_ptr.cc -->
 * result :
 * desc :
 */

#include "pre_compiled.h"

#define MAX_SIZE        (1000 * 1000 * 10)

template <typename T>
void callFunction(T obj)
{
}

template <typename T>
void ptrOperator(std::vector<T>& list)
{
        {
                CTimeCost t("sort");
                std::sort(list.begin(), list.end());
        }

        {
                CTimeCost t("copy");
                std::vector<T> tmpList = list;
        }

        {
                CTimeCost t("copy_2");
                std::vector<T> tmpList(list.begin(), list.end());
        }

        {
                CTimeCost t("function parm");
                for (int32_t i=0; i<MAX_SIZE; ++i)
                        callFunction(list[i]);
        }
}

int main(void)
{
        srand(time(NULL));

        printf("========== shared_ptr ==========\n");
        std::vector<std::shared_ptr<int32_t>> sharedPtrList;
        {
                CTimeCost t("insert");
                for (int32_t i=0; i<MAX_SIZE; ++i)
                        sharedPtrList.push_back(std::shared_ptr<int32_t>(new int32_t));
        }
        ptrOperator(sharedPtrList);
        {
                CTimeCost t("erase");
                sharedPtrList.erase(sharedPtrList.begin(), sharedPtrList.end());
        }
        printf("==========        ptr ==========\n");
        std::vector<int32_t*> ptrList;
        {
                CTimeCost t("insert");
                for (int32_t i=0; i<MAX_SIZE; ++i)
                        ptrList.push_back(new int32_t);
        }
        ptrOperator(ptrList);
        {
                CTimeCost t("erase");
                for (auto val : ptrList)
                        delete val;
                ptrList.erase(ptrList.begin(), ptrList.end());
        }

        return 0;
}
