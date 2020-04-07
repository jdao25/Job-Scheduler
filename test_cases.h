/*
    Test Cases
*/


#ifndef TEST_CASES_H
#define TEST_CASES_H

#include "FCFS.h"
#include "SJF.h"
#include "RR_2.h"
#include "RR_5.h"


void test_FCFS();
void test_SJF();
void test_RR_2();
void test_RR_5();
void calculate_average();


void test_FCFS()
{
    std::cout << "First Come First Serve" << std::endl;

    // This will run test cases for 5 jobs, 10 jobs, 15 jobs
    for (int job = 5; job <= 15; job += 5)
    {
        std::cout << job << " jobs" << std::endl << std::endl;

        createJobFile(job); // Create a job.txt with specific number of jobs

        std::ifstream jobFile("job.txt"); // Open job.txt

        std::vector<std::string> jobNames; // Vector will hold "Job1", "Job2", "Job3", etc
        std::vector<unsigned int> burstTimes; // Vector that hold the jobs burstTime
        std::string line; // Will hold each line in job.txt

        while (!jobFile.eof()) // Keep looping until the end of the file
        {
            getline(jobFile, line); // Get the current line in job.txt

            if (isdigit(line[0])) // if the first index of the line is a number, then it's the job's burst time
                burstTimes.push_back(std::stoi(line));  // Convert burst time to int and add it to vector burstTimes
            else if (isalpha(line[0]))  // if the first index is a letter then it is the job's Name "Job1", etc
                jobNames.push_back(line);   // Add the job names to the vector jobNames
        }

        jobFile.close(); // Properly close job.txt file

        // Display the table
        std::cout << "\tTable:" << std::endl;
        generateTable(jobNames, burstTimes);


        // Display the scheduling table
        std::cout << "\tSchedule Table" << std::endl;
        display_FCFS_info(jobNames, burstTimes);

        // Display the Job order and the Average Turnaround Time
        std::cout
            << "\tFirst Come First Serve Job Order:" << std::endl
            << "\t" << FCFS_order(jobNames) << std::endl << std::endl;
        std::cout
            << "\tAverage Turnaround Time:" << std::endl
            << "\t" << FCFS_time(burstTimes) << " ms" << std::endl;

        std::cout << std::endl << std::endl << std::endl;
    }
}


void test_SJF()
{
    std::cout << "Shortest Job First" << std::endl;

    // This will run test cases for 5 jobs, 10 jobs, 15 jobs
    for (int job = 5; job <= 15; job += 5)
    {
        std::cout << job << " jobs" << std::endl << std::endl;

        createJobFile(job); // Create a job.txt with specific number of jobs

        std::ifstream jobFile("job.txt"); // Open job.txt

        std::vector<std::string> jobNames; // Vector will hold "Job1", "Job2", "Job3", etc
        std::vector<unsigned int> burstTimes; // Vector that hold the jobs' burstTime
        std::string line; // Will hold each line in job.txt

        while (!jobFile.eof()) // Keep looping until the end of the file
        {
            getline(jobFile, line); // Get the current line in job.txt

            if (isdigit(line[0])) // if the first index of the line is a number, then it's the job's burst time
                burstTimes.push_back(std::stoi(line));  // Convert burst time to int and add it to vector burstTimes
            else if (isalpha(line[0]))  // if the first index is a letter then it is the job's Name "Job1", etc
                jobNames.push_back(line);   // Add the job names to the vector jobNames
        }

        jobFile.close(); // Properly close job.txt file

        std::multimap<unsigned int, std::string> jobs; // Since burstTime is the key, by using a map the burst times are in order

        // Create map with pair( burstTime, jobName )
        for (int idx = 0; idx < jobNames.size(); idx++)
            jobs.insert(std::pair<unsigned int, std::string>(burstTimes[idx], jobNames[idx]));

        // Display the table
        std::cout << "\tTable:" << std::endl;
        generateTable(jobNames, burstTimes);

        // Free Memory my swapping vector with empty vectors
        std::vector<std::string>().swap(jobNames);
        std::vector<unsigned int>().swap(burstTimes);

        // Display the schedule table for Shortest Job First
        std::cout << "\tSchedule Table" << std::endl;
        display_SJF_info(jobs);

        std::cout
            << "\tShortest Job First order:" << std::endl
            << "\t" << SJF_order(jobs) << std::endl << std::endl;
        std::cout
            << "\tAverage Turnaround time:" << std::endl
            << "\t" << SJF_time(jobs) << " ms" << std::endl;

        std::cout << std::endl << std::endl;
    }
}


void test_RR_2()
{
    std::cout << "Round-Robin with time slice = 2" << std::endl;

    // This will run test cases for 5 jobs, 10 jobs, 15 jobs
    for (int job = 5; job <= 15; job += 5)
    {
        std::cout << job << " jobs" << std::endl << std::endl;

        createJobFile(job); // Create a job.txt with specific number of jobs

        std::ifstream jobFile("job.txt"); // Open job.txt

        std::vector<std::string> jobNames; // Vector will hold "Job1", "Job2", "Job3", etc
        std::vector<unsigned int> burstTimes; // Vector that hold the jobs burstTime
        std::string line; // Will hold each line in job.txt

        while (!jobFile.eof()) // Keep looping until the end of the file
        {
            getline(jobFile, line); // Get the current line in job.txt

            if (isdigit(line[0])) // if the first index of the line is a number, then it's the job's burst time
                burstTimes.push_back(std::stoi(line));  // Convert burst time to int and add it to vector burstTimes
            else if (isalpha(line[0]))  // if the first index is a letter then it is the job's Name "Job1", etc
                jobNames.push_back(line);   // Add the job names to the vector jobNames
        }

        jobFile.close(); // Properly close job.txt file

        // Display the table
        std::cout << "\tTable:" << std::endl;
        generateTable(jobNames, burstTimes);

        // Display the Schedule Table
        std::cout << "\tSchedule Table" << std::endl;
        display_RR_2_info(jobNames, burstTimes);

        std::cout
            << "\tRound-Robin with time slice = 2 order:" << std::endl
            << "\t" << RR_2_order(jobNames, burstTimes) << std::endl << std::endl;

        std::cout
            << "\tRound-Robin Order Completed:" << std::endl
            << "\t" << RR_2_order_complete(jobNames, burstTimes) << std::endl << std::endl;

        std::cout
            << "\tAverage Turnaround Time:" << std::endl
            << "\t" << RR_2_time(jobNames, burstTimes) << " ms" << std::endl;

        std::cout << std::endl << std::endl << std::endl;
    }
}


void test_RR_5()
{
    std::cout << "Round-Robin with time slice = 5" << std::endl;

    // This will run test cases for 5 jobs, 10 jobs, 15 jobs
    for (int job = 5; job <= 15; job += 5)
    {
        std::cout << job << " jobs" << std::endl << std::endl;

        createJobFile(job); // Create a job.txt with specific number of jobs

        std::ifstream jobFile("job.txt"); // Open job.txt

        std::vector<std::string> jobNames; // Vector will hold "Job1", "Job2", "Job3", etc
        std::vector<unsigned int> burstTimes; // Vector that hold the jobs burstTime
        std::string line; // Will hold each line in job.txt

        while (!jobFile.eof()) // Keep looping until the end of the file
        {
            getline(jobFile, line); // Get the current line in job.txt

            if (isdigit(line[0])) // if the first index of the line is a number, then it's the job's burst time
                burstTimes.push_back(std::stoi(line));  // Convert burst time to int and add it to vector burstTimes
            else if (isalpha(line[0]))  // if the first index is a letter then it is the job's Name "Job1", etc
                jobNames.push_back(line);   // Add the job names to the vector jobNames
        }

        jobFile.close(); // Properly close job.txt file

        // Display the table
        std::cout << "\tTable:" << std::endl;
        generateTable(jobNames, burstTimes);

        // Display the Schedule Table
        std::cout << "\tSchedule Table" << std::endl;
        display_RR_5_info(jobNames, burstTimes);

        std::cout
            << "\tRound-Robin with time slice = 5 order:" << std::endl
            << "\t" << RR_5_order(jobNames, burstTimes) << std::endl << std::endl;

        std::cout
            << "\tRound-Robin Order Completed:" << std::endl
            << "\t" << RR_5_order_complete(jobNames, burstTimes) << std::endl << std::endl;

        std::cout
            << "\tAverage Turnaround Time:" << std::endl
            << "\t" << RR_5_time(jobNames, burstTimes) << " ms" << std::endl;

        std::cout << std::endl << std::endl << std::endl;
    }
}


// Display the Average Turnaround Time for 20 trials
void calculate_average()
{
    unsigned int numTrials = 20;    // Number of trials we want to perform

    // This will give us 5 jobs, 10 jobs, and 15 jobs
    for (int job = 5; job <= 15; job += 5)
    {
        std::cout << job << " jobs" << std::endl;

        std::vector<float> FCFS_averages;  // Hold all Avg Turnaround Times of FCFS
        std::vector<float> SJF_averages;  // Hold all Avg Turnaround Times of SJF
        std::vector<float> RR_2_averages; // Hold all Avg Turnaround Times of RR2
        std::vector<float> RR_5_averages; // Hold all Avg Turnaround Times of RR5

        // Calcuate for 20 trials
        for (int trial = 1; trial <= numTrials; trial++)
        {
            // Create job.txt with "job" number of jobs
            createJobFileTesting(job);

            std::ifstream jobFile("job.txt"); // Open job.txt

            std::vector<std::string> jobNames; // Vector will hold "Job1", "Job2", "Job3", etc
            std::vector<unsigned int> burstTimes; // Vector that hold the jobs burstTime
            std::string line; // Will hold each line in job.txt

            while (!jobFile.eof()) // Keep looping until the end of the file
            {
                getline(jobFile, line); // Get the current line in job.txt

                if (isdigit(line[0])) // if the first index of the line is a number, then it's the job's burst time
                    burstTimes.push_back(std::stoi(line));  // Convert burst time to int and add it to vector burstTimes
                else if (isalpha(line[0]))  // if the first index is a letter then it is the job's Name "Job1", etc
                    jobNames.push_back(line);   // Add the job names to the vector jobNames
            }

            jobFile.close(); // Properly close job.txt file

            // Since burstTime is the key, by using a map the burst times are in order
            std::multimap<unsigned int, std::string> jobs;  // This will be use for SJF

            // Create map with pair( burstTime, jobName )
            for (int idx = 0; idx < jobNames.size(); idx++)
                jobs.insert(std::pair<unsigned int, std::string>(burstTimes[idx], jobNames[idx]));

            // Appending all averages
            FCFS_averages.push_back(FCFS_time(burstTimes));
            SJF_averages.push_back(SJF_time(jobs));
            RR_2_averages.push_back(RR_2_time(jobNames, burstTimes));
            RR_5_averages.push_back(RR_5_time(jobNames, burstTimes));
        }

        // Printing out the Averages for each scheduling algorithms
        std::cout
            << "\tFirst Come First Serve: (" << numTrials << " trials)" << std::endl
            << "\tList of all Average Turnaround Times:  "<< std::endl
            << FCFS_averages << std::endl
            << "\tOverall Average:  " << ( accumulate(FCFS_averages) / numTrials ) << " ms"
            << std::endl << std::endl;

        std::cout
            << "\tShortest Job First: (" << numTrials << " trials)" << std::endl
            << "\tList of all Average Turnaround Times:  "<< std::endl
            << SJF_averages << std::endl
            << "\tOverall Average:  " << ( accumulate(SJF_averages) / numTrials ) << " ms"
            << std::endl << std::endl;

        std::cout
            << "\tRound-Robin (w/ time slice = 2): (" << numTrials << " trials)" << std::endl
            << "\tList of all Average Turnaround Times:  "<< std::endl
            << RR_2_averages << std::endl
            << "\tOverall Average:  " << ( accumulate(RR_2_averages) / numTrials ) << " ms"
            << std::endl << std::endl;

        std::cout
            << "\tRound-Robin (w/ time slice = 5): (" << numTrials << " trials)" << std::endl
            << "\tList of all Average Turnaround Times:  "<< std::endl
            << RR_5_averages << std::endl
            << "\tOverall Average:  " << ( accumulate(RR_5_averages) / numTrials ) << " ms"
            << std::endl << std::endl;
    }
}


#endif // ! TEST_CASES_H
