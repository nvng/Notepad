#ifndef __DOUBLE_QUEUE_2_HPP__
#define __DOUBLE_QUEUE_2_HPP__

#include <mutex>
#include <vector>
#include <condition_variable>

#include "DoubleQueue.hpp"

template <typename T>
class DoubleQueue2 : public NonCopyable
{
public :
        typedef T value_type;
        typedef DoubleQueue<value_type> DoubleQueueType;

        DoubleQueue2() : queue_(mQueue.GetQueue()), idx_(0) {}

        inline void PushItem(value_type item)
        {
                mQueue.PushItem(item);
                cond.notify_all();
        }

        inline bool TryGet(value_type& val)
        {
                std::lock_guard<std::mutex> lock(mMutex);
                if (queue_.empty())
                        queue_ = mQueue.GetQueue();

                if (queue_.empty())
                        return false;
                else
                {
                        val = GetValue();
                        return true;
                }
        }

        inline value_type WaitGet()
        {
                std::unique_lock<std::mutex> lock(mMutex);
                while (queue_.empty())
                {
                        queue_ = mQueue.GetQueue();
                        if (queue_.empty())
                                cond.wait(lock);
                }

                return GetValue();
        }

private :
        inline value_type& GetValue() // queue_ is not null
        {
                value_type& ret = queue_[idx_++];
                if (idx_ >= queue_.size())
                {
                        queue_.clear();
                        idx_ = 0;
                }
                return ret;
        }

        DoubleQueue<value_type> mQueue;
        typename DoubleQueueType::QueueType& queue_;
        std::mutex mMutex;
        std::condition_variable cond;
        std::size_t idx_;
};

#endif // __DOUBLE_QUEUE_2_HPP__
