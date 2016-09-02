#pragma once

class CNetBuffer : public CNonCopyable
{
public :
        CNetBuffer() : mBuffMaxSize(10240), mBuff(new char[mBuffMaxSize]), mCurrentPos(0) { }
        CNetBuffer(void* buff, size_t size) : mBuffMaxSize(size), mBuff((char*)buff), mCurrentPos(0) {}
        ~CNetBuffer() { delete[] mBuff; }

        inline bool CopyBuff(void* buff, size_t size)
        {
                if (nullptr==buff || size<=0 || (mBuffMaxSize-mCurrentPos)<size)
                        return false;

                memcpy(mBuff+mCurrentPos, buff, size);
                mCurrentPos += size;
                return true;
        }

        inline void* GetPtr() { return mBuff + mCurrentPos; }
        inline void* GetPtr(size_t size)
        {
                if (size<=0 || mCurrentPos+size>mBuffMaxSize)
                        return nullptr;

                void* tmp = mBuff + mCurrentPos;
                mCurrentPos += size;
                return tmp;
        }

        inline size_t GetUsedSize() { return mBuffMaxSize-mCurrentPos; }
        inline void Clear() { mCurrentPos = 0; }

public :
        inline size_t GetMaxSize() { return mBuffMaxSize; }
private :
        size_t mBuffMaxSize;

private :
        char* mBuff;
        size_t mCurrentPos;
};
