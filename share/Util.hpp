void PrintBit(const char* p, size_t size, int perLine=10)
{
        assert(perLine >= 1);

        size_t i = 1;
        for (; i<=size; ++i)
        {
                printf("%0#X ", *(p+i-1));
                if (i % perLine == 0)
                        putchar('\n');
        }

        if (0 != i % perLine)
                putchar('\n');
}
