#ifndef __DOUBLE_QUEUE_2_HPP__
#define __DOUBLE_QUEUE_2_HPP__

#include <mutex>
#include <vector>
#include <condition_variable>

#include "DoubleQueue.hpp"

class DoubleQueue2 : public NonCopyable
{
public :
        DoubleQueue2() : queue_(mQueue.GetQueue()) {}

        inline void PushItem(void* item)
        {
                mQueue.PushItem(item);
                cond.notify_all();
        }

        inline void* TryGet()
        {
                std::lock_guard<std::mutex> lock(mMutex);
                if (queue_->Empty())
                {
#ifdef USE_VECTOR
                        queue_->Clear();
#endif
                        queue_ = mQueue.GetQueue();
                }
                return queue_->GetItem();
        }

        inline void* WaitGet()
        {
                std::unique_lock<std::mutex> lock(mMutex);
                while (queue_->Empty())
                {
#ifdef USE_VECTOR
                        queue_->Clear();
#endif
                        queue_ = mQueue.GetQueue();
                        if (queue_->Empty())
                                cond.wait(lock);
                }

                return queue_->GetItem();
        }

private :
        DoubleQueue mQueue;
        DoubleQueueData* queue_;
        std::mutex mMutex;
        std::condition_variable cond;
};

#endif // __DOUBLE_QUEUE_2_HPP__
