void testParamFunc(
                int32_t a_1,
                int32_t a_2,
                int32_t a_3,
                int32_t a_4,
                int32_t a_5
                )
{
}

void testParamFunc_2(
                int32_t a_1,
                int32_t a_2,
                int32_t a_3,
                int32_t a_4,
                int32_t a_5,
                int32_t a_6
                /*
                int32_t a_7,
                int32_t a_8,
                int32_t a_9,
                int32_t a_10,
                int32_t a_11,
                int32_t a_12,
                int32_t a_13,
                int32_t a_14,
                int32_t a_15,
                int32_t a_16,
                int32_t a_17,
                int32_t a_18,
                int32_t a_19,
                int32_t a_20,
                int32_t a_21
                */
                )
{
}

#define MAX_COUNT       (1000 * 1000)

int main(void)
{
        int32_t arr[22];
        {
                CTimeCost t("5");
                for (int i=0; i<MAX_COUNT; ++i)
                        testParamFunc(arr[1], arr[2], arr[3], arr[4], arr[5]);
        }

        {
                CTimeCost t("21");
                for (int i=0; i<MAX_COUNT; ++i)
                        testParamFunc_2(
                                        arr[1],
                                        arr[2],
                                        arr[3],
                                        arr[4],
                                        arr[5],
                                        arr[6]
                                        /*
                                        arr[7],
                                        arr[8],
                                        arr[9],
                                        arr[10],
                                        arr[11],
                                        arr[12],
                                        arr[13],
                                        arr[14],
                                        arr[15],
                                        arr[16],
                                        arr[17],
                                        arr[18],
                                        arr[19],
                                        arr[20],
                                        arr[21]
                                        */
                                     );
        }

        return 0;
}
