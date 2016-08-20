/* file : new_vs_pool.cc --> C++ new 操作符和 内存池 效率对比 */

#include "pre_compiled.h"

#define MAX_SIZE        (1000 * 1000 * 10)
#define BUFF_SIZE       (2048)
#define ARRAY_SIZE      (1024)

#include <list>

class CPool
{
public :
        static inline void Init()
        {
                for (int32_t i=0; i<ARRAY_SIZE; ++i)
                        pool[i] = (new char[BUFF_SIZE]);
                pos = ARRAY_SIZE - 1;
        }

        static inline char* Get()
        {
                char* buff = nullptr;
                if (CheckPos(pos))
                {
                        buff = pool[pos--];
                        // pool[pos] = nullptr;
                        // --pos;
                }
                else
                {
                        return new char[BUFF_SIZE];
                }
                // pool.pop_back();
                // char* buff = pool[1];
                return buff;
        }

        static inline void push(char* buff)
        {
                pool[++pos] = buff;
                // pool[1] = buff;
                // pool.push_back(buff);
        }

private :
        CPool();
        static inline bool CheckPos(int32_t pos)
        { return pos>=0 && pos<ARRAY_SIZE; }

        static char* pool[ARRAY_SIZE];
        static int32_t pos;
};
char* CPool::pool[1024];
int32_t CPool::pos = 0;

int main(void)
{
        char* buff = nullptr;
        {
                CTimeCost t("new");
                for (int32_t i=0; i<MAX_SIZE; ++i)
                {
                        buff = new char[BUFF_SIZE];
                        // memset(buff, 0x00, BUFF_SIZE);
                        delete buff;
                }
        }

        CPool::Init();
        {
                CTimeCost t("pool");
                for (int32_t i=0; i<MAX_SIZE; ++i)
                {
                        char* buff = CPool::Get();
                        CPool::push(buff);
                        // memset(buff, 0x00, BUFF_SIZE);
                }
        }
        (void)buff;

        return 0;
}
