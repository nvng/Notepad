#ifndef __RANDOM_SELECT_HPP__
#define __RANDOM_SELECT_HPP__

class RandomSelect : public NonCopyable
{
public :
        RandomSelect() : sum_(0) {}

        inline bool Add(int64_t ratio, void* val)
        {
                if (0!=ratio && nullptr!=val)
                {
                        SRandomKey key(sum_, sum_+ratio);
                        sum_ += ratio;
                        mRandomList.insert(std::make_pair(key, val));
                        assert(0!=key.low_ || 0!=key.hight_);
                        return true;
                }
                return false;
        }

        inline void* Get(int64_t ratio)
        {
                static SRandomKey key(ratio);
                key.key_ = ratio;
                auto it = mRandomList.find(key);
#ifdef NDEBUG
                return (mRandomList.end()!=it) ? it->second : nullptr;
#else
                if (mRandomList.end() != it)
                {
                        const SRandomKey& tmpKey = it->first;
                        assert(ratio>=tmpKey.low_ && ratio<tmpKey.hight_);
                        return it->second;
                }
                else
                {
                        assert(false);
                        return nullptr;
                }
#endif // NDEBUG
        }

        inline int64_t GetSum() { return sum_; }

private :
        // [low_, hight_)
        struct SRandomKey
        {
                SRandomKey(int64_t low, int64_t hight)
                        : low_(low), hight_(hight), key_(0)
                {
                }

                SRandomKey(int64_t key) : low_(0), hight_(0), key_(key) {}

                int64_t low_;
                int64_t hight_;
                int64_t key_;
        };
        friend bool operator<(const SRandomKey&, const SRandomKey&);

        std::map<SRandomKey, void*> mRandomList;
        int64_t sum_;
};

inline bool operator<(const RandomSelect::SRandomKey& lhs, const RandomSelect::SRandomKey& rhs)
{
        if (0==lhs.key_ && 0==rhs.key_)
                return lhs.low_ < rhs.low_;
        else
        {
                if (0 != lhs.key_)
                        return rhs.key_ < lhs.low_;
                else
                        return rhs.key_ >= lhs.hight_;
        }
}

#endif // __RANDOM_SELECT_HPP__
