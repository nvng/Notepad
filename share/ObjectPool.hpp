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

	explicit ObjectPool(size_t size=1000)
                : mIndex(0), mMaxSize(0)
	{
		Resize(size);
	}

	~ObjectPool()
	{
		for (value_pointer p : mObjectList)
			delete p;
	}

	inline value_pointer Malloc()
	{
		if (mIndex >= mMaxSize)
			Resize(10);
		return mObjectList[mIndex++];
	}

	inline void Free(value_pointer p)
	{
		if (nullptr!=p && mIndex>0 && mIndex<=mMaxSize)
			mObjectList[--mIndex] = p;
	}

	inline size_t GetSize() { return mObjectList.size(); }
	inline size_t GetIndex() { return mIndex; }

private :
	void Resize(size_t size)
	{
		if (size <= 0)
			return;

		mObjectList.reserve(mObjectList.size() + size);
		for (size_t i=0; i<size; ++i)
			mObjectList.push_back(new value_type());
		mMaxSize = mObjectList.size();
	}

	std::vector<value_pointer> mObjectList;
	size_t mIndex;
	size_t mMaxSize;
};

#endif // __OBJECT_POOL_HPP__
