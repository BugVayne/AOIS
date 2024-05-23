#include "Cell.h"
#include "gtest/gtest.h"
#include<sstream>

TEST(HashTest, ConstructorTest)
{
    Cell cell;
    Table table(20, 2);
}
TEST(HashTest, HashFuncTest1)
{
    Table table(20, 2);
    int hash = table.HashFunc("keyval");
    ASSERT_EQ(11, hash);
}
TEST(HashTest, HashFuncTest2)
{
    Table table(20, 2);
    int hash = table.HashFunc("k");
    ASSERT_EQ(-1, hash);
}
TEST(HashTest, AddTest1)
{
    Table table(20, 2);
    table.Add("keyval", "val");
    table.Add("keyval", "val");
    table.Add("keyval", "val");
}
TEST(HashTest, AddTest2)
{
    Table table(20, 2);
    table.Add("-&&#87", "val");
    table.Add("f", "123");
}
TEST(HashTest, AddTest3)
{
    Table table(5, 2);
    table.Add("keyval", "val");
    table.Add("keyval", "val");
    table.Add("keyval", "val");
    table.Add("keyval", "val");
    table.Add("keyval", "val");
    table.Add("keyval", "val");
}
TEST(HashTest, FindTest)
{
    Table table(20, 2);
    table.Find("keyval");
    table.Find("empty");
}
TEST(HashTest, UpdateTest)
{
    Table table(20, 2);
    table.Update("keyval", "123");
    table.Update("empty", "321");
}
TEST(HashTest, DeleteTest)
{
    Table table(20, 2);
    table.Delete("empty");
}
TEST(HashTest, ShowSheetTest)
{
    Table table(20, 2);
    table.ShowSheet();
}
TEST(HashTest, MenuTest1)
{
    Table table(20, 2);

    std::stringstream input;
    input << "1\nkey\nvalue\n";
    std::cin.rdbuf(input.rdbuf());

    table.Menu();
}
TEST(HashTest, MenuTest2)
{
    Table table(20, 2);

    std::stringstream input;
    input << "2\nkey\n";
    std::cin.rdbuf(input.rdbuf());

    table.Menu();
}
TEST(HashTest, MenuTest3)
{
    Table table(20, 2);

    std::stringstream input;
    input << "3\nkey\n";
    std::cin.rdbuf(input.rdbuf());

    table.Menu();
}
TEST(HashTest, MenuTest4)
{
    Table table(20, 2);

    std::stringstream input;
    input << "4\nkey\nvalue\n";
    std::cin.rdbuf(input.rdbuf());

    table.Menu();
}
TEST(HashTest, MenuTest5)
{
    Table table(20, 2);

    std::stringstream input;
    input << "1\n";
    std::cin.rdbuf(input.rdbuf());

    table.Menu();
}
TEST(HashTest, MenuTest6)
{
    Table table(20, 2);

    std::stringstream input;
    input << "6\n0\n";
    std::cin.rdbuf(input.rdbuf());

    table.Menu();
}




