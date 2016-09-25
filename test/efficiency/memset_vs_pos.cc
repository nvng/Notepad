#include "pre_compiled.h"

#define MAX_SIZE        (1000 * 1000)
#define BUFFER_SIZE     (1024)

class Buffer
{
public :
        inline void reset_pos() { cur_pos_ = 0; }
        inline void reset_memset() { memset(buff, 0x00, BUFFER_SIZE); }

        inline void copy_pos()
        {
                for (int i=0; i<100; ++i)
                        cur_pos_ += BUFFER_SIZE/100;
        }

        inline void copy_memcpy()
        {
                for (int i=0; i<100; ++i)
                        memcpy(buff, tmp, BUFFER_SIZE/100);
        }

private :
        char buff[BUFFER_SIZE];
        size_t cur_pos_;
        size_t max_size_;
        char tmp[BUFFER_SIZE/100];
};

int main(void)
{
        Buffer buffer;
        {
                CTimeCost t("pos");
                for (int i=0; i<MAX_SIZE; ++i)
                        buffer.reset_pos();
        }

        {
                size_t pos = 0;
                CTimeCost t("just pos");
                for (int i=0; i<MAX_SIZE; ++i)
                        pos = 0;
                (void)pos;
        }

        {
                CTimeCost t("memset");
                for (int i=0; i<MAX_SIZE; ++i)
                        buffer.reset_memset();
        }

        {
                CTimeCost t("copy pos");
                for (int i=0; i<MAX_SIZE; ++i)
                        buffer.copy_pos();
        }

        {
                CTimeCost t("copy memcpy");
                for (int i=0; i<MAX_SIZE; ++i)
                        buffer.copy_memcpy();
        }

        return 0;
}
