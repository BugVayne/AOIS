#include "gtest/gtest.h"
#include "Matrix.h"
#include <sstream>

TEST(MatrixTest, Constructor_test_0)
{std::stringstream input;
    input << "2";
    std::cin.rdbuf(input.rdbuf());
    Matrix matrix;
}

TEST(MatrixTest, Constructor_test_1)
{
    std::stringstream input;
    input << "1";
    std::cin.rdbuf(input.rdbuf());
    Matrix matrix;

}
TEST(MatrixTest, GetWordTest)
{
    std::stringstream input;
    input << "1";
    std::cin.rdbuf(input.rdbuf());
    Matrix matrix;

    matrix.GetWord(1);
}
TEST(MatrixTest, SetWordTest)
{
    std::stringstream input;
    input << "1";
    std::cin.rdbuf(input.rdbuf());
    Matrix matrix;

    matrix.SetWord(1, vector<bool>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1});
}
TEST(MatrixTest, GetAdressColumn)
{
    std::stringstream input;
    input << "1";
    std::cin.rdbuf(input.rdbuf());
    Matrix matrix;

    vector<bool> vec = matrix.GetAdressColumn(1);
    Matrix::PrintVector(vec);
}
TEST(MatrixTest, AdditionTest)
{
    std::stringstream input;
    input << "1";
    std::cin.rdbuf(input.rdbuf());
    Matrix matrix;

    matrix.Addition("111");
}

TEST(MatrixTest, SortTest)
{
    std::stringstream input;
    input << "1";
    std::cin.rdbuf(input.rdbuf());
    Matrix matrix;

    matrix.Sort();
}
TEST(MatrixTest, DisparityTest)
{
    std::stringstream input;
    input << "1";
    std::cin.rdbuf(input.rdbuf());
    Matrix matrix;

    matrix.Disparity(1, 2, 3);
}
TEST(MatrixTest, EquivalenceTest)
{
    std::stringstream input;
    input << "1";
    std::cin.rdbuf(input.rdbuf());
    Matrix matrix;

    matrix.Equivalence(1, 2, 3);
}
TEST(MatrixTest, DenialTest)
{
    std::stringstream input;
    input << "1";
    std::cin.rdbuf(input.rdbuf());
    Matrix matrix;

    matrix.DenialForSecond(1, 2, 3);
}
TEST(MatrixTest, ImplicationTest)
{
    std::stringstream input;
    input << "1";
    std::cin.rdbuf(input.rdbuf());
    Matrix matrix;

    matrix.Implication(1, 2, 3);
}
TEST(MatrixTest, OperAddTest)
{
    std::stringstream input;
    input << "1";
    std::cin.rdbuf(input.rdbuf());
    Matrix matrix;

    matrix.OperAdd(1);
}

TEST(MatrixTest, IndexInputTest1)
{
    std::stringstream input;
    input << "1";
    std::cin.rdbuf(input.rdbuf());
    Matrix matrix;

    stringstream testinput;
    testinput<<"1";
    cin.rdbuf(testinput.rdbuf());
    int a = Matrix::IndexInput();
    ASSERT_EQ(a, 1);
}


TEST(MatrixTest, WordInputTest)
{
    std::stringstream input;
    input << "1";
    std::cin.rdbuf(input.rdbuf());
    Matrix matrix;

    stringstream testinput;
    testinput<<"1111 1111 1111 1111";
    cin.rdbuf(testinput.rdbuf());
    vector<bool> vec = Matrix::WordInput();
    vector<bool> expected{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    ASSERT_EQ( expected, vec);
}
TEST(MatrixTest, ComparisonTestTest)
{
    std::stringstream input;
    input << "1";
    std::cin.rdbuf(input.rdbuf());
    Matrix matrix;

    bool flag = matrix.Comparison(matrix.GetWord(1), matrix.GetWord(2));
    ASSERT_FALSE(flag);
}
TEST(MatrixTest, ShowMatrixAndWordsTest)
{
    std::stringstream input;
    input << "1";
    std::cin.rdbuf(input.rdbuf());
    Matrix matrix;

    matrix.ShowWords();
    matrix.ShowMatrix();
}



TEST(MatrixTest, MenuTest1)
{
    std::stringstream input;
    input << "1";
    std::cin.rdbuf(input.rdbuf());
    Matrix matrix;

    stringstream testinput;
    testinput<<"1\n1\n9\n";
    cin.rdbuf(testinput.rdbuf());
    matrix.Menu();

}
TEST(MatrixTest, MenuTest2)
{
    std::stringstream input;
    input << "1";
    std::cin.rdbuf(input.rdbuf());
    Matrix matrix;

    stringstream testinput;
    testinput<<"2\n1111 1111 1111 1111\n1\n9\n";
    cin.rdbuf(testinput.rdbuf());
    matrix.Menu();

    vector<bool> vec = matrix.GetWord(1);
    vector<bool> expected{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    ASSERT_EQ(expected, vec);

}

TEST(MatrixTest, MenuTest3)
{
    std::stringstream input;
    input << "2";
    std::cin.rdbuf(input.rdbuf());
    Matrix matrix;

    matrix.SetWord(1, vector<bool>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1});
    matrix.SetWord(2, vector<bool>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1});

    stringstream testinput;
    testinput<<"3\n1\n3\n2\n1\n9\n";
    cin.rdbuf(testinput.rdbuf());
    matrix.Menu();

    vector<bool> exp {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    vector<bool> actual = matrix.GetWord(3);

    ASSERT_EQ(exp, actual);

}

TEST(MatrixTest, MenuTest4)
{
    std::stringstream input;
    input << "1";
    std::cin.rdbuf(input.rdbuf());
    Matrix matrix;

    stringstream testinput;
    testinput<<"4\n111\n9\n";
    cin.rdbuf(testinput.rdbuf());
    matrix.Menu();

}


TEST(MatrixTest, MenuTest5)
{
    std::stringstream input;
    input << "1";
    std::cin.rdbuf(input.rdbuf());
    Matrix matrix;

    stringstream testinput;
    testinput<<"5\n9\n";
    cin.rdbuf(testinput.rdbuf());
    matrix.Menu();

    }

TEST(MatrixTest, MenuTest6)
{
    streambuf* original_cin_buf = cin.rdbuf();
    stringstream input;
    input << "1\n6\n9\n";
    cin.rdbuf(input.rdbuf());
    Matrix matrix;
    matrix.Menu();
    cin.rdbuf(original_cin_buf);
}

TEST(MatrixTest, MenuTest7)
{
    std::stringstream input;
    input << "1";
    std::cin.rdbuf(input.rdbuf());
    Matrix matrix;

    stringstream testinput;
    testinput<<"7\n1\n9\n";
    cin.rdbuf(testinput.rdbuf());
    matrix.Menu();
}
TEST(MatrixTest, MenuTest8)
{
    std::stringstream input;
    input << "1";
    std::cin.rdbuf(input.rdbuf());
    Matrix matrix;

    stringstream testinput;
    testinput<<"8\n9\n";
    cin.rdbuf(testinput.rdbuf());
    matrix.Menu();
}

