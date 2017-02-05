#ifndef __OBJECT_POOL_HPP__
#define __OBJECT_POOL_HPP__

#include <vector>

// 线程不安全对象池
// 只负责逻辑层快速分配和释放对象，而不是GC。
// 因此使用时，必须配对使用Malloc和Free函数。
template <typename T>
class ObjectPool
{
public :
	typedef T value_type;
	typedef value_type* value_pointer;

	// 根据需要，设置一个比较精确的初始大小。
	explicit ObjectPool(size_t initSize=10, size_t incSize=10)
		: mIndex(0), mMaxSize(0), mIncSize(incSize)
	{
		mObjectList.reserve(initSize);
		mObjectDeleteList.reserve(initSize);
		Resize(initSize);
	}

	~ObjectPool()
	{
		for (value_pointer p : mObjectDeleteList)
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
		if (mIndex>0 && mIndex<=mMaxSize)
			mObjectList[--mIndex] = p;
	}

private :
	// 只增加
	void Resize(size_t size)
	{
		value_pointer p = nullptr;
		for (size_t i=0; i<size; ++i)
		{
			p = new value_type();
			mObjectList.push_back(p);
			mObjectDeleteList.push_back(p);
		}
		mMaxSize = mObjectList.size();
	}

	std::vector<value_pointer> mObjectList;
	std::vector<value_pointer> mObjectDeleteList;
	size_t mIndex;
	size_t mMaxSize;
	const size_t mIncSize;
};

#endif // __OBJECT_POOL_HPP__