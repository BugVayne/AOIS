#include "Minimization.h"
#include "gtest/gtest.h"
#include<sstream>


TEST(MinimizationTest, ConstructorTest)
{
    Minimization min(" ( ( A & ( D > G ) ) ~ ( B | ( ! C ) ) )");
}
TEST(MinimizationTest, PrintTest)
{
    Minimization min(" ( ( A & ( D > G ) ) ~ ( B | ( ! C ) ) )");
    min.Printsheet();
    min.PrintFormules();
}
TEST(MinimizationTest, TableMethodTest)
{
    Minimization min(" ( ( A & ( D > G ) ) ~ ( B | ( ! C ) ) )");
    min.PrintTableMethod();
}
TEST(MinimizationTest, CalculateMethodTest)
{
    Minimization min(" ( ( A & ( D > G ) ) ~ ( B | ( ! C ) ) )");
    min.PrintCalcMethod();
}
TEST(MinimizationTest, KarnoMethodTest)
{
    Minimization min(" ( ( A & D ) ~ ( B | ( ! C ) ) )");
    min.KarnoMethod();
}
