#include "RandomSelect.hpp"

int32_t DEBUG_OPERATOR = 0;
#define MAX_COUNT       (1000 * 100)
#define MAX_LOOP_COUNT  (1000 * 1000)

int32_t cnt = 0;

struct SRandomKey
{
        SRandomKey(int32_t low, int32_t hight)
                : low_(low), hight_(hight), key_(0)
        {
        }

        SRandomKey() : SRandomKey(0, 0) {}

        int32_t low_;
        int32_t hight_;
        int32_t key_;
};

inline bool operator<(const SRandomKey& lhs, const SRandomKey& rhs)
{
        /*
        if (1 == DEBUG_OPERATOR)
        {
                printf("operator< lhs[%d %d %d] rhs[%d %d %d]",
                                lhs.low_, lhs.hight_, lhs.key_,
                                rhs.low_, rhs.hight_, rhs.key_);
        }
        */

        ++cnt;
        bool ret = false;
        if (0==lhs.key_ && 0==rhs.key_)
                ret = lhs.low_ < rhs.low_;
        else
        {
                if (0 != lhs.key_)
                {
                        ret = rhs.key_ < lhs.low_;
                }
                else
                {
                        ret = rhs.key_ >= lhs.hight_;
                }
        }

        /*
        if (1 == DEBUG_OPERATOR)
                printf(" %s\n", ret?"true":"false");
                */

        return ret;
}

void test_1()
{
        std::map<SRandomKey, int32_t> mRandomList;
        int32_t sum = 0;
        for (int i=0; i<MAX_COUNT; ++i)
        {
                int32_t r = 1 + rand() % 999;
                SRandomKey key(sum, sum+r);
                sum += r;
                mRandomList.insert(std::make_pair(key, i));
        }

        printf("==================================================\n");
        SRandomKey key;
        int32_t maxCnt = 0;
        for (int i=0; i<sum; ++i)
        {
                key.key_ = i;
#if 0
                int32_t idx = -1;
                for (auto& v : mRandomList)
                {
                        auto& val = v.first;
                        if (key.key_ < val.hight_)
                        {
                                if (key.key_ >= val.low_)
                                        idx = v.second;
                                break;
                        }

                        /*
                        if (key.key_>=val.low_ && key.key_<val.hight_)
                        {
                                // printf("key[%d] low[%d] hight[%d]\n", key.key_, val.first.low_, val.first.hight_);
                                idx = v.second;
                                break;
                        }
                        */
                }

                if (-1 == idx)
                {
                        printf("aaaaa not found key[%d]\n", key.key_);
                }
#endif

                cnt = 0;
                auto it = mRandomList.find(key);
                if (cnt > maxCnt)
                        maxCnt = cnt;
                if (mRandomList.end() == it)
                {
                        printf("bbbbb not found key[%d]\n", key.key_);
                }
                else
                {
                        const SRandomKey& val = it->first;
                        if (!(key.key_>=val.low_ && key.key_<val.hight_))
                                printf("error\n");

#if 0
                        if (idx != it->second)
                        {
                                SRandomKey key_1(it->first.low_, it->first.hight_);
                                auto it_ = mRandomList.find(key_1);
                                printf("error idx_1[%d] idx_2[%d] low_[%d] hight_[%d]\n",
                                                idx, it->second, it_->first.low_, it_->first.hight_);

                                /*
                                   DEBUG_OPERATOR = 1;
                                   mRandomList.find(key);
                                   DEBUG_OPERATOR = 0;
                                   */

                                return;
                        }
#endif
                }
        }
        printf("maxCnt = %d\n", maxCnt);
}

void test_2()
{
        std::map<SRandomKey, int32_t> mRandomList;
        int32_t sum = 0;
        for (int i=0; i<MAX_COUNT; ++i)
        {
                int32_t r = 1 + rand() % 999;
                SRandomKey key(sum, sum+r);
                sum += r;
                mRandomList.insert(std::make_pair(key, i));
        }

        printf("==================================================\n");
#if 0
        {
                CTimeCost t("transfor");
                for (int i=0; i<MAX_LOOP_COUNT; ++i)
                {
                        SRandomKey key;
                        key.key_ = rand() % sum;
                        int32_t idx = -1;
                        for (auto& v : mRandomList)
                        {
                                auto& val = v.first;
                                if (key.key_ < val.hight_)
                                {
                                        if (key.key_ >= val.low_)
                                                idx = v.second;
                                        break;
                                }

                                /*
                                if (key.key_>=val.low_ && key.key_<val.hight_)
                                {
                                        // printf("key[%d] low[%d] hight[%d]\n", key.key_, val.first.low_, val.first.hight_);
                                        idx = v.second;
                                        break;
                                }
                                */
                        }

                        if (-1 == idx)
                        {
                                printf("aaaaa not found key[%d]\n", key.key_);
                        }
                        /*
                        else
                                printf("found idx[%d]\n", idx);
                                */
                }
        }
#endif

        {
                SRandomKey key;
                CTimeCost t("bin");
                for (int i=0; i<MAX_LOOP_COUNT; ++i)
                {
                        key.key_ = rand() % sum;
                        // auto it = std::find(mRandomList.begin(), mRandomList.end(), key);
                        auto it = mRandomList.find(key);
                        if (mRandomList.end() == it)
                        {
                                printf("bbbbb not found key[%d]\n", key.key_);
                        }
                        /*
                        else
                        {
                                const SRandomKey& val = it->first;
                                if (!(key.key_>=val.low_ && key.key_<val.hight_))
                                        printf("error\n");
                        }
                        */
                }
        }
}

int main(void)
{
        srand(time(NULL));
        test_1();
        // test_2();

        return 0;
}
