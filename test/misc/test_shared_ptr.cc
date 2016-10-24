// const shared_ptr<T>& 能够提高效率，但从容器中出来的，不能使用这种方式来接。
// 如果在接下来的深层次调用时，将容器中的该元素删除，那这个引用就成野指针了。

class Test
{
public :
        Test() { printf("Test()\n"); }
        ~Test() { printf("~Test()\n"); }
};
typedef std::shared_ptr<Test> TestPtr;
typedef std::vector<TestPtr> TestListType;

int main(void)
{
        TestListType testList;
        {
                TestPtr t = std::make_shared<Test>();
                testList.push_back(t);
        }

        const TestPtr& t = testList.front();
        {
                testList.clear();
                printf("bbbbbbbbbb\n");
        }

        printf("t.get() = %p\n", t.get());

        return 0;
}
