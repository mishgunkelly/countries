#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "countries.h"



bool runTest(const char *inputFilePath, const char *resultOutputFilePath, const char *expectedOutputFilePath)
{
    solution(inputFilePath, resultOutputFilePath); // Example call to the function being tested
    FILE* expectedFile = fopen(expectedOutputFilePath, "r");
    if (!expectedFile) {
        fprintf(stderr, "Could not open test files\n");
        return false;
    }
    FILE* resultFile = fopen(resultOutputFilePath, "r");
    if (!resultFile) {
        fclose(expectedFile);
        fprintf(stderr, "Could not open test files\n");
        return false;
    }


    char expectedLine[256];
    char resultLine[256];
    bool testPassed = true;
    while (fgets(expectedLine, sizeof(expectedLine), expectedFile) &&
           fgets(resultLine, sizeof(resultLine), resultFile)) {
        
        int diff = 0;
        for (int i = 0; expectedLine[i] != '\0' && resultLine[i] != '\0'; i++) {
            if (expectedLine[i] != resultLine[i]) {
                diff++;
                printf("Difference at line: %sExpected: %sGot: %s\n%d\n%c\n%c\n", expectedLine, expectedLine, resultLine, i, expectedLine[i], resultLine[i]);
            }
        }
        if (diff > 0) {
            testPassed = false;
            break;
        }
    }

    fclose(expectedFile);
    fclose(resultFile);

    return testPassed; // Return the test result
}


void testRunner() {
    printf("Running tests...\n");
    const char *testCases[][3] = { 
        {"D:\\C++\\Countries\\GPTests\\inputs\\input1.txt", "D:\\C++\\Countries\\Results\\output1.txt", "D:\\C++\\Countries\\GPTests\\outputs\\output1.txt"},
        {"D:\\C++\\Countries\\GPTests\\inputs\\input2.txt", "D:\\C++\\Countries\\Results\\output2.txt", "D:\\C++\\Countries\\GPTests\\outputs\\output2.txt"},
        {"D:\\C++\\Countries\\GPTests\\inputs\\input3.txt", "D:\\C++\\Countries\\Results\\output3.txt", "D:\\C++\\Countries\\GPTests\\outputs\\output3.txt"},
        {"D:\\C++\\Countries\\GPTests\\inputs\\input4.txt", "D:\\C++\\Countries\\Results\\output4.txt", "D:\\C++\\Countries\\GPTests\\outputs\\output4.txt"},
        {"D:\\C++\\Countries\\GPTests\\inputs\\input5.txt", "D:\\C++\\Countries\\Results\\output5.txt", "D:\\C++\\Countries\\GPTests\\outputs\\output5.txt"},
    };

    for (int i = 0; i < 5; i++) {
        const char *inputFilePath = testCases[i][0];
        const char *resultOutputFilePath = testCases[i][1];
        const char *expectedOutputFilePath = testCases[i][2];

        if (runTest(inputFilePath, resultOutputFilePath, expectedOutputFilePath)) {
            printf("Test %d passed.\n\n\n", i + 1);
        } else {
            printf("Test %d failed.\n\n\n", i + 1);
        }
    }

    printf("All tests completed.\n");
}



int main(int argc, char *argv[]) {
    
    testRunner();



    return 0;
}