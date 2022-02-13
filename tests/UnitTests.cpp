#include <utest.h>
#include "../include/backend.h"
UTEST_MAIN();

UTEST(Backend, InitTestFile)
{
    // Arrange
    std::ifstream dataFile;

    // Act
    initDataFile();
    dataFile.open("data.csv");

    // Assert
    ASSERT_TRUE(dataFile);
}