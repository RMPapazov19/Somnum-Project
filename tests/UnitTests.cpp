#include <utest.h>
#include "../include/backend.h"
UTEST_MAIN();


UTEST(Backend,InitTestFile)
{
    // Arrange
    std::ifstream dataFile;

    // Act
    initDataFile();
    dataFile.open("data.csv");

    // Assert
    ASSERT_TRUE(dataFile);
}
UTEST(Backend,appendNodeToFile)
{
    //Arrange
     char *evName="ev1";
     char *evDate="2022-02-14";
     std::fstream dataFile;
     std::string testString;

    //Act
    appendNodeToFile(evName,evDate);
    dataFile.open("data.csv",std::ios::in);
    std::getline(dataFile,testString);
    std::getline(dataFile,testString);

    //Assert
    ASSERT_STREQ("ev1,2022-02-14,\"Edit me to add description\",",testString.c_str());
}


UTEST(Backend,updateEventList)
{
    //Arrange
    EventNode *ev;
    std::fstream dataFile;

    //Act
updateEventList(ev);
dataFile.open("data.csv", std::ios::in);
    //Assert
ASSERT_TRUE(ev);
}