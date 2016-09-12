#ifndef __DOUBLE_QUEUE_HPP__
#define __DOUBLE_QUEUE_HPP__

#include <mutex>
#include <vector>

#include "NonCopyable.hpp"

template <typename T>
class DoubleQueue : public NonCopyable
{
public :
        inline void PushItem(T item)
        {
                std::lock_guard<std::mutex> lock(mMutex);
                mQueue[1].push_back(item);
        }

        inline std::vector<T>& GetQueue()
        {
                {
                        std::lock_guard<std::mutex> lock(mMutex);
                        mQueue[0].swap(mQueue[1]);
                }
                return mQueue[0];
        }

private :
        std::mutex mMutex;
        std::vector<T> mQueue[2];
};

#endif // __DOUBLE_QUEUE_HPP__
