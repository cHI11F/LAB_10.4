#include "pch.h"
#include "CppUnitTest.h"
#include "../LAB_10.4/LAB_10.4.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestMethod1)
        {
            
            vector<vector<int>> matrix1 = { {1, 2}, {3, 4} };
            vector<vector<int>> matrix2 = { {5, 6}, {7, 8} };
            vector<vector<int>> expectedResult = { {19, 22}, {43, 50} };
            vector<vector<int>> actualResult;

            
            try {
                actualResult = multiplyMatrices(matrix1, matrix2);
            }
            catch (const exception& e) {
                Logger::WriteMessage(e.what());
            }

            
            Assert::AreEqual(expectedResult.size(), actualResult.size(), L"Row count mismatch");
            for (size_t i = 0; i < expectedResult.size(); ++i) {
                Assert::AreEqual(expectedResult[i].size(), actualResult[i].size(), L"Column count mismatch");
                for (size_t j = 0; j < expectedResult[i].size(); ++j) {
                    Assert::AreEqual(expectedResult[i][j], actualResult[i][j], L"Element mismatch");
                }
            }
        }
    };
}
