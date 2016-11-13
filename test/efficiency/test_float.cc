#define MAC_CNT (1000 * 1000 * 100)

int main(void)
{
        srand(time(NULL));

        std::vector<double> dList;

        for (int i=0; i<MAC_CNT; ++i)
                dList.push_back(RandInRange(0.0, MAC_CNT*100.0)/100.0);

        {
                double d = 1.0;
                CTimeCost t("double");
                for (int i=0; i<MAC_CNT; ++i)
                        d = d / dList[i];
        }

        std::vector<int> sList;

        for (int i=0; i<MAC_CNT; ++i)
                sList.push_back(RandInRange(0, MAC_CNT));

        {
                int s = 1;
                CTimeCost t("int");
                for (int i=0; i<MAC_CNT; ++i)
                        s = s / sList[i];
        }

        return 0;
}
