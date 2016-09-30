void PrintBit(const std::vector<bool>& bit)
{
        const int size = bit.size();
        int i = 1;
        for (; i<=size; ++i)
        {
                printf("%s ", bit[i-1]?"true":"false");
                if (i % 10 == 0)
                        putchar('\n');
        }
        if (i % 10 != 0)
                putchar('\n');

}

int main(void)
{
        std::vector<bool> bitMap(64, false);

        printf("bitMap.size() = %lu\n", bitMap.size());
        PrintBit(bitMap);
        bitMap.insert(bitMap.begin(), true);
        // PrintBit(bitMap);

        return 0;
}
