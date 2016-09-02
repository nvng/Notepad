#include "pre_compiled.h"

#define MAX_SIZE        (1000)
#define BUFF_SIZE       (1024*10)

int main(void)
{
        char* srcList[MAX_SIZE];
        for (int32_t i=0; i<MAX_SIZE; ++i)
                // srcList[i] = (char*)malloc(sizeof(char) * BUFF_SIZE);
                srcList[i] = new char[BUFF_SIZE];

        char* destList[MAX_SIZE];
        for (int32_t i=0; i<MAX_SIZE; ++i)
                // destList[i] = (char*)malloc(sizeof(char) * BUFF_SIZE);
                destList[i] = new char[BUFF_SIZE];

        // memset(src, 0x1, MAX_SIZE);
        // char dest[BUFF_SIZE] = {0};
        {
                CTimeCost t("memcpy");
                for (int32_t j=0; j<MAX_SIZE; ++j)
                        for (int32_t i=0; i<MAX_SIZE; ++i)
                                memcpy(destList[i], srcList[i], BUFF_SIZE);
        }

        {
                CTimeCost t("memset");
                for (int32_t j=0; j<MAX_SIZE; ++j)
                        for (int32_t i=0; i<MAX_SIZE; ++i)
                                memset(destList[i], 0xff, BUFF_SIZE);
        }

        return 0;
}
