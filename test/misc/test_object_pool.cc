struct MessageLitePtr
{
        int t;
};

struct SReSendInfo
{
        void Init(uint64_t guid, const MessageLitePtr& msg, float intervalTime, int32_t sendMsgType)
        {
                mGuid = guid;
                mMsg = msg;
                mIntervalTime = intervalTime;
                mSendMsgType = sendMsgType;
                ResetOverTime();
                mSendTimes = 0;
                mIsRemoved = false;
        }

        inline void ResetOverTime()
        {
                mOverTime += mIntervalTime;
        }

        uint64_t                        mGuid;
        float                        mOverTime;
        float                        mIntervalTime;
        MessageLitePtr mMsg;
        int32_t        mSendMsgType;
        int32_t                        mSendTimes;
        bool               mIsRemoved;
};

#define MAX_LOOP_CNT    (1000 * 1000 * 100)
ObjectPool<SReSendInfo> gObjectPool;

int main(void)
{
        {
                // CTimeCost t("object pool");
                clock_t begin = clock();
                for (int i=0; i<MAX_LOOP_CNT; ++i)
                        gObjectPool.Free(gObjectPool.Malloc());
                printf("object pool cost %fs\n", (float)(clock()-begin)/CLOCKS_PER_SEC);
        }


        {
                // CTimeCost t("new");
                clock_t begin = clock();
                for (int i=0; i<MAX_LOOP_CNT/100; ++i)
                        delete (new SReSendInfo());
                printf("new delete cost %fs\n", (float)(clock()-begin)/CLOCKS_PER_SEC);
        }

        auto func = []() { return new SReSendInfo(); };
        {
                // CTimeCost t("new");
                clock_t begin = clock();
                for (int i=0; i<MAX_LOOP_CNT/100; ++i)
                        delete func();
                printf("function cost %fs\n", (float)(clock()-begin)/CLOCKS_PER_SEC);
        }

        return 0;
}
