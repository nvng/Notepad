BufferPool2 bp;
BufferPoolTmp testBP(1024*2, 30000);
std::vector<char*> testList;

int main(void)
{
        testList.reserve(30000);
        {
                CTimeCost t("buffer");
                for (int j=0; j<60; ++j)
                {
                        for (int i=1; i<30000; ++i)
                        {
                                char* tmp = bp.malloc_buffer(1000);
                                testList[i] = tmp;
                        }

                        for (int i=1; i<30000; ++i)
                                bp.free_buffer((char*)testList[i]);
                }
        }

        testList.clear();
        {
                CTimeCost t("new");
                for (int j=0; j<60; ++j)
                {
                        for (int i=1; i<30000; ++i)
                        {
                                char* tmp = new char[1000];
                                testList[i] = tmp;
                        }
                        for (int i=1; i<30000; ++i)
                                delete[] testList[i];
                }
        }

        /*
        testList.clear();
        {
                CTimeCost t("test buffer_pool");
                for (int j=0; j<60; ++j)
                {
                        for (int i=1; i<30000; ++i)
                        {
                                char* tmp = testBP.malloc_buffer();
                                testList[i] = tmp;
                        }
                        for (int i=1; i<30000; ++i)
                                testBP.free_buffer(testList[i]);
                }

        }

        {
                testList.clear();
                CTimeCost t("test new");
                for (int j=0; j<60; ++j)
                {
                        for (int i=1; i<30000; ++i)
                        {
                                char* tmp = new char[1024*2];
                                testList[i] = tmp;
                        }
                        for (int i=1; i<30000; ++i)
                                delete[] testList[i];
                }
        }
        */

        return 0;
}
