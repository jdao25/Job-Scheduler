#include "test_cases.h"


int main(int argc, char const *argv[])
{
    // Run test cases for First Come First Serve
    test_FCFS();

    // Run test cases for Shortest Job First
    test_SJF();

    // Run test cases for Round-Robin with time slice = 2 (RR-2)
    test_RR_2();

    // Run test cases for Round-Robin with time slice = 5 (RR-5)
    test_RR_5();

    return 0;
}
