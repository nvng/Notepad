#ifndef __BUFFER_POOL_2_HPP__
#define __BUFFER_POOL_2_HPP__

class BufferPoolTmp
{
public :
        BufferPoolTmp(size_t buffer_size, size_t cnt)
        {
                max_buffer_size_ = buffer_size;
                cur_pos_ = 0;
                inc_buffer(cnt);
        }

        ~BufferPoolTmp()
        {
                for (auto val : buffer_list_)
                        delete[] val;
        }

        inline char* malloc_buffer()
        {
                if (cur_pos_ == max_pos_)
                        inc_buffer(1);
                else if (cur_pos_ > max_pos_)
                        assert(false);

                return buffer_list_[cur_pos_++];
        }

        inline void free_buffer(char* buff)
        {
                assert(cur_pos_ > 0);
                buffer_list_[--cur_pos_] = buff;
        }

private :
        std::vector<char*> buffer_list_;
        size_t max_pos_;
        size_t cur_pos_;
        size_t max_buffer_size_;

        inline void inc_buffer(size_t cnt)
        {
                // buffer_list_.resize();
                for (size_t i=0; i<cnt; ++i)
                        buffer_list_.push_back(new char[max_buffer_size_]);
                max_pos_ = buffer_list_.size();
        }
};

struct SBufferHeader
{
        int16_t size_;
};

class BufferPool2
{
public :
        BufferPool2()
        {
                for (size_t i=1; i<sArrSize; ++i)
                        arr_[i] = new BufferPoolTmp(i+sizeof(SBufferHeader), 0);
        }

        ~BufferPool2()
        {
                for (size_t i=1; i<sArrSize; ++i)
                        delete arr_[i];
        }

        inline char* malloc_buffer(size_t size)
        {
                assert(size>0 && size<sArrSize);
                char* tmp = arr_[size]->malloc_buffer();
                ((SBufferHeader*)tmp)->size_ = size;
                return tmp+sizeof(SBufferHeader);
        }

        inline void free_buffer(char* buff)
        {
                SBufferHeader* head = (SBufferHeader*)(buff-sizeof(SBufferHeader));
                arr_[head->size_]->free_buffer((char*)head);
        }

private :
        static const size_t sArrSize = 1024;
        BufferPoolTmp* arr_[sArrSize];
};

#endif // __BUFFER_POOL_2_HPP__
