#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

#include <mutex>
#include "NonCopyable.hpp"

template <typename T>
class Singleton : public NonCopyable
{
public :
        inline static T* GetInstance() { return mInstance; }

        static void CreateInstance()
        {
                if (nullptr == mInstance)
                {
                        std::lock_guard<std::mutex> lock(mMutex);
                        if (nullptr == mInstance)
                                mInstance = new T;
                }
        }

        static void DestroyInstance()
        {
                if (nullptr != mInstance)
                {
                        std::lock_guard<std::mutex> lock(mMutex);
                        if (nullptr != mInstance)
                        {
                                delete mInstance;
                                mInstance = nullptr;
                        }
                }
        }

private :
        static T* mInstance;
        static std::mutex mMutex;
};

template <typename T>
T* Singleton<T>::mInstance = nullptr;

template <typename T>
std::mutex Singleton<T>::mMutex;

#endif // __SINGLETON_HPP__
