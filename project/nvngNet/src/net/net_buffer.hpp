#pragma once

class CNetBuffer : public CNonCopyable
{
public :
        CNetBuffer() : mCurrentPos(0) { }

        inline bool CopyBuff(void* buff, size_t size)
        {
                if (nullptr==buff || size<=0 || (sBuffMaxSize-mCurrentPos)<size)
                        return false;

                memcpy(mBuff+mCurrentPos, buff, size);
                mCurrentPos += size;
                return true;
        }

        inline void* GetPtr() { return mBuff + mCurrentPos; }
        inline void* GetPtr(size_t size)
        {
                if (size<=0 || mCurrentPos+size>sBuffMaxSize)
                        return nullptr;

                void* tmp = mBuff + mCurrentPos;
                mCurrentPos += size;
                return tmp;
        }

        inline size_t GetUsedSize() { return mCurrentPos; }
        inline void Clear() { mCurrentPos = 0; }

public :
        inline size_t GetMaxSize() { return sBuffMaxSize; }
private :
        static const size_t sBuffMaxSize = 10240;

private :
        char mBuff[sBuffMaxSize];
        size_t mCurrentPos;
};
