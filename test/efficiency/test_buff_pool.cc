#include "pre_compiled.h"

#define PER_SIZE        (30000)
#define MAX_SIZE        (60)
#define BUFFER_SIZE     (1024 * 2)

typedef char* BufferPtr;
#define CREATE_BUFFER_PTR (new char[BUFFER_SIZE])

class BufferPool
{
public :
        BufferPool()
        {
        }

        ~BufferPool()
        {
                for (auto p : buffer_list_)
                        delete[] p;
        }

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
                if (cur_pos_ < max_pos_)
                        return buffer_list_[cur_pos_++];
                return nullptr;
        }

        inline void free_buffer(BufferPtr buff)
        {
                if (cur_pos_ >= 0)
                        buffer_list_[cur_pos_--] = buff;
                else
                        assert(false);
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

void testBufferPool()
{
        BufferPool bp;
        bp.init(BUFFER_SIZE, PER_SIZE);
        {
                BufferPtr list[PER_SIZE];
                CTimeCost t("BufferPool");
                for (int i=0; i<MAX_SIZE; ++i)
                {
                        for (int j=0; j<PER_SIZE; ++j)
                        {
                                list[j] = bp.malloc_buffer();
                                // assert(nullptr != list[j]);
                        }

                        for (int j=0; j<PER_SIZE; ++j)
                                bp.free_buffer(list[j]);
                }

        }

        {
                BufferPtr list[PER_SIZE];
                CTimeCost t("new free");
                for (int i=0; i<MAX_SIZE; ++i)
                {
                        for (int j=0; j<PER_SIZE; ++j)
                        {
                                list[j] = CREATE_BUFFER_PTR;
                                // assert(nullptr != list[j]);
                        }
                        for (int j=0; j<PER_SIZE; ++j)
                                delete[] list[j];
                }
        }
}

class Test
{
public :
        Test() { ++construct; }
        /*
        ~Test() { }
        */

        static int construct;
        static int deconstruct;
private :
        char arr[10];
};

int Test::construct = 0;
int Test::deconstruct = 0;

void testObjectPool()
{
        BufferPool bp;
        bp.init(sizeof(Test), PER_SIZE);
        {
                Test* list[PER_SIZE];
                CTimeCost t("BufferPool");
                for (int i=0; i<MAX_SIZE; ++i)
                {
                        for (int j=0; j<PER_SIZE; ++j)
                        {
                                char* p = bp.malloc_buffer();
                                list[j] = new (p) Test();
                                /*
                                assert(nullptr != p);
                                assert(nullptr != list[j]);
                                */
                                assert(p == (char*)(list[j]));
                        }

                        for (int j=0; j<PER_SIZE; ++j)
                        {
                                bp.free_buffer((char*)(list[j]));
                                list[j]->~Test();
                        }
                }

                printf("con[%d] decon[%d]\n", Test::construct, Test::deconstruct);
        }

        {
                Test* list[PER_SIZE];
                CTimeCost t("new free");
                for (int i=0; i<MAX_SIZE; ++i)
                {
                        for (int j=0; j<PER_SIZE; ++j)
                        {
                                list[j] = new Test();
                                assert(nullptr != list[j]);
                        }
                        for (int j=0; j<PER_SIZE; ++j)
                                delete list[j];
                }
        }
}

int main(void)
{
        testBufferPool();
        // printf("sizeof(Test) = %lu\n", sizeof(Test));
        // testObjectPool();

        return 0;
}
