#define MAX_COUNT       (1000 * 1000 * 10)

int main(void)
{
        {
                CTimeCost t("new");
                for (int i=0; i<MAX_COUNT; ++i)
                        std::shared_ptr<int> spi(new int);
        }

        {
                CTimeCost t("make_shared");
                for (int i=0; i<MAX_COUNT; ++i)
                        std::shared_ptr<int> spi = std::make_shared<int>();
        }

        return 0;
}
