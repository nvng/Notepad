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

        if (0 != (i-1) % perLine)
                putchar('\n');
}

inline bool DoubleEqual(double lhs, double rhs)
{
        return abs(lhs - rhs) < 0.00001;
}

// [Low, up)
inline double RandInRange(double Low, double Up)
{
        return Low + double(rand()) / ((double)RAND_MAX + 1) * (Up - Low);
}

// [Low, up)
inline int RandInRange(int Low, int Up)
{
        return (int)(Low + double(rand()) / ((double)RAND_MAX + 1) * (Up - Low));
}

// [Low, Up]
inline int32_t Rand(int32_t Low, int32_t Up)
{
        return (int32_t)(double(rand()) / (RAND_MAX) * (Up - Low)) + Low;
}

#define FLAG_ADD(val, flag) ((int&)val) |= (flag)
#define FLAG_SET(val, flag) ((int&)val) = (flag)
#define FLAG_DEL(val, flag) ((int&)val) &= ~(flag)
#define FLAG_HAS(val, flag) ((((int&)val) & (flag)) != 0)
