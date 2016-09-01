/* file : wstring.cc -->
 * result :
 * dest :
 */

#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <fstream>

#include "pre_compiled.h"

int main(void)
{
        std::string str_1 = "我是刘绍伟";
        {
                std::ofstream ofs("./test_1.txt");
                ofs << str_1;
        }

        std::wstring str = L"我是刘绍伟";
        // printf("str = %ls\n", str.c_str());
        std::wcout << "str = " << str << std::endl;

        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        std::string narrowStr = conv.to_bytes(str);
        {
                std::ofstream ofs("./test.txt");
                ofs << narrowStr;
        }
        std::wcout << "str = " << narrowStr << std::endl;

        /*
        std::wstring wideStr = conv.from_bytes(narrowStr);
        {
                std::locale::global(std::locale("Chinese-simplified"));
                std::wstring fileName = L"./testW.txt";
                std::wofstream ofs(fileName);
                ofs << wideStr;
        }
        */

        return 0;
}
