#include "pre_compiled.h"

#define MAX_SIZE        (1000 * 1000)
#define BUFFER_SIZE     (1024)

typedef char* BufferPtr;
#define CREATE_BUFFER_PTR (new char[BUFFER_SIZE])

class BufferPool
{
public :
        bool init(size_t buffer_size, size_t count)
        {
                buffer_list_.reserve(count);
                for (size_t i=0; i<count; ++i)
                        buffer_list_.push_back(CREATE_BUFFER_PTR);

                max_pos_ = buffer_list_.size();
                cur_pos_ = 0;

                return true;
        }

        inline BufferPtr malloc_buffer()
        {
                BufferPtr ret = nullptr;
                {
                        std::lock_guard<std::mutex> lock(mutex_);
                        if (cur_pos_ < max_pos_)
                                ret = buffer_list_[cur_pos_++];
                }
                return ret;
        }

        inline void free_buffer(BufferPtr buff)
        {
                {
                        std::lock_guard<std::mutex> lock(mutex_);
                        if (cur_pos_ >= 0)
                                buffer_list_[cur_pos_--] = buff;
                }
        }

        void resize(size_t count)
        {
                for (size_t i=0; i<count; ++i)
                        buffer_list_.push_back(CREATE_BUFFER_PTR);
                max_pos_ = buffer_list_.size();
        }

private :
        std::vector<BufferPtr> buffer_list_;
        size_t max_pos_;
        size_t cur_pos_;
        std::mutex mutex_;
};


int main(void)
{
        BufferPool bp;
        bp.init(BUFFER_SIZE, MAX_SIZE);
        BufferPtr p;
        {
                BufferPtr list[MAX_SIZE];
                CTimeCost t("BufferPool");
                for (int j=0; j<MAX_SIZE; ++j)
                {
                        list[j] = bp.malloc_buffer();
                        // assert(nullptr != p);
                }

                for (int j=0; j<MAX_SIZE; ++j)
                        bp.free_buffer(list[j]);
        }

        {
                BufferPtr list[MAX_SIZE];
                CTimeCost t("new free");
                for (int j=0; j<MAX_SIZE; ++j)
                {
                        list[j] = CREATE_BUFFER_PTR;
                        // assert(nullptr != p);
                }
                for (int j=0; j<MAX_SIZE; ++j)
                        delete[] list[j];
        }
        (void)p;

        return 0;
}
