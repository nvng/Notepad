#ifndef __DOUBLE_QUEUE_HPP__
#define __DOUBLE_QUEUE_HPP__

#include <mutex>
#include <vector>
#include <deque>

#include "NonCopyable.hpp"

#define USE_VECTOR

#ifdef USE_VECTOR
class DoubleQueueData
{
public :
        DoubleQueueData() : add_pos_(0), get_pos_(0), max_size_(1000*1000*10)
        {
                list_.resize(max_size_);
        }

        inline void AddItem(void* item)
        {
                if (add_pos_ >= max_size_)
                {
                        max_size_ *= 2;
                        list_.resize(max_size_);
                        // printf("max_size_ = %lu\n", max_size_);
                }
                list_[add_pos_++] = item;
        }

        inline void* GetItem() { return Empty() ? nullptr : list_[get_pos_++]; }
        inline size_t Size() { return add_pos_ - get_pos_; }
        inline bool Empty() { return get_pos_ >= add_pos_; }
        inline void Clear() { add_pos_ = 0; get_pos_ = 0; }

private :
        size_t add_pos_;
        size_t get_pos_;
        size_t max_size_;
        std::vector<void*> list_;
};

#else

class DoubleQueueData
{
public :
        DoubleQueueData()
        {
        }

        inline void AddItem(void* item)
        {
                list_.push_back(item);
        }

        inline void* GetItem()
        {
                void* val = nullptr;
                if (!Empty())
                {
                        val = list_.front();
                        list_.pop_front();
                }
                return val;
        }
        inline size_t Size() { return list_.size(); }
        inline bool Empty() { return list_.empty(); }
        inline void Clear() { }

private :
        std::deque<void*> list_;
};
#endif

class DoubleQueue : public NonCopyable
{
public :
        DoubleQueue() : idx_(0) {}

        inline void PushItem(void* item)
        {
                std::lock_guard<std::mutex> lock(mMutex);
                mQueue[idx_].AddItem(item);
        }

        inline DoubleQueueData* GetQueue()
        {
                std::lock_guard<std::mutex> lock(mMutex);
                DoubleQueueData* data = &(mQueue[idx_]);
                idx_ = (0==idx_) ? 1 : 0;
                return data;
        }

private :
        std::mutex mMutex;
        uint8_t idx_;
        DoubleQueueData mQueue[2];
};

#endif // __DOUBLE_QUEUE_HPP__
