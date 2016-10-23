/* file : test_string.cc --> 测试 string 内部引用计数。
 * result : 初始赋值时，string对象有自己的空间。当复制时，会共用一个内存空间。但复制品之一有改变内容的行为，该复制就另起一个空间。
 * desc :
 */

void testFunc(std::string str)
{
        printf("testFunc str.c_str() addr = %p\n", str.c_str());
}

int main(void)
{
        // const char* c = "abc";
        char c[] = "abc";
        printf("c addr = %p\n", c);
        std::string str = c;
        printf("str.c_str() addr = %p\n", str.c_str());
        testFunc(str);

        std::string str_1;
        str_1 = str;
        printf("copy str_1.c_str() addr = %p\n", str_1.c_str());

        std::string str_2 = str;
        printf("copy con str_2.c_str() addr = %p\n", str_2.c_str());

        // for (int i=0; i<100; ++i)
        /*
        str.push_back('a');
        printf("push str.c_str() addr = %p\n", str.c_str());
        */

        str[1] = 'd';
        printf("push str.c_str() addr = %p\n", str.c_str());

        return 0;
}
