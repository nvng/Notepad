#ifndef __OBJECT_POOL_HPP__
#define __OBJECT_POOL_HPP__

#include <vector>

// 线程不安全对象池
template <typename T>
class ObjectPool
{
public :
	typedef T value_type;
	typedef value_type* value_pointer;

	explicit ObjectPool(size_t initSize=10, size_t incSize=10)
                : mIndex(0), mMaxSize(0), mIncSize(incSize)
	{
		Resize(initSize);
	}

	~ObjectPool()
	{
		for (value_pointer p : mObjectList)
			delete p;
	}

	inline value_pointer Malloc()
	{
		if (mIndex >= mMaxSize)
			Resize(mIncSize);
		return mObjectList[mIndex++];
	}

	inline void Free(value_pointer p)
	{
		if (nullptr!=p && mIndex>0 && mIndex<=mMaxSize)
			mObjectList[--mIndex] = p;
	}

private :
	void Resize(size_t size)
	{
		mObjectList.reserve(mObjectList.size() + size);
		for (size_t i=0; i<size; ++i)
			mObjectList.push_back(new value_type());
		mMaxSize = mObjectList.size();
	}

	std::vector<value_pointer> mObjectList;
	size_t mIndex;
	size_t mMaxSize;
        size_t mIncSize;
};

#endif // __OBJECT_POOL_HPP__
