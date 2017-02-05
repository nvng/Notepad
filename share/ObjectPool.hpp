#ifndef __OBJECT_POOL_HPP__
#define __OBJECT_POOL_HPP__

#include <vector>

// �̲߳���ȫ�����
// ֻ�����߼�����ٷ�����ͷŶ��󣬶�����GC��
// ���ʹ��ʱ���������ʹ��Malloc��Free������
template <typename T>
class ObjectPool
{
public :
	typedef T value_type;
	typedef value_type* value_pointer;

	// ������Ҫ������һ���ȽϾ�ȷ�ĳ�ʼ��С��
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
	// ֻ����
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