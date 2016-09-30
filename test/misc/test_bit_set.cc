/* file : test_bit_set.cc --> 如何使用 std::bitset
 *
 */

#define BIT_SIZE        (100)
typedef std::bitset<BIT_SIZE> BitMapType;

void PrintBit(const BitMapType& bit)
{
        const int size = bit.size();
        int i = 1;
        for (; i<=size; ++i)
        {
                printf("%s ", bit[i-1]?"true":"false");
                if (i % 10 == 0)
                        putchar('\n');
        }
        if ((i-1) % 10 != 0)
                putchar('\n');

}

int main(void)
{
        BitMapType bit;
        printf("size of bit = %lu\n", bit.size());

        bit.set(31, true);
        bit.set(54, true);
        bit.set(63, true);

        PrintBit(bit);
        printf("bit = %s\n", bit.to_string().c_str());
        printf("bit = %llu\n", bit.to_ullong());
        // bit.reset();
        // bit = ~bit;
        bit.flip(1);
        bit.flip(99);
        bit.flip();
        PrintBit(bit);
        bit.set(63, true);

        printf("bit = %s\n", bit.to_string().c_str());
        printf("bit = %llu\n", bit.to_ullong());

        return 0;
}
