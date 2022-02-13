#include <utest.h>
#include "../include/backend.h"
UTEST_MAIN();

UTEST(Backend,appendNodeToFile)
{
    //Arange
    std::ifstream dataFile1;

    //Act
    appendNodeToFile();
    dataFile1.open("data.csv",std::ios::app);

    //Assert
    ASSERT_TRUE(dataFile1);

}


UTEST(Backend,deleteNodeAtIndex)
{
    //Arange
    std::ifstream dataFile2;

    //Act
    deleteNodeAtIndex();
    dataFile2.open("data.csv", std::ios::out | std::ios::trunc);
    
    //Assert
    ASSERT_TRUE(dataFile2);
}


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


UTEST(Backend,mergeList)
{
    //Arrange
    std::ifstream dataFile3;

    //Act
    mergeList();
    dataFile3.open(std::ios::res);

    //Assert
    ASSERT_TRUE(dataFile3);
}


UTEST(Backend,splitListInMiddle)
{
    //Arrange
   std::ifstream dataFile4;

   //Act
   splitListInMiddle();
   dataFile4.open(startRight);

   //Assert
   ASSERT_TRUE(dataFile4);

}


UTEST(Backend,sortList)
{
    //Arange
    std::ifstream dataFile5;

    //Act
    sortList();
    dataFile5.open(evRef);

    //Assert
    ASSERT_TRUE(dataFile5);
}


UTEST(Backend,updateEventList)
{
    //Arange
    std::ifstream dataFile6;

    //Act
    updateEventList();
    dataFile6.open(ev);

    //Assert
    ASSERT_TRUE(dataFile6);
}
