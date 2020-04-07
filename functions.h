/*
    This header file contains all the helper functions.

    Functions such as:
    createJobFile,
    displayTables,
    etc.
*/


#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>  // Read in job.txt
#include <vector>   // used to store job.txt lines, etc
#include <map>      // multimap for SJF algorithm since keys are ordered
#include <ctime>        // rand() srand()
#include <chrono>       // Also for random numbers. Number generated based on time

#ifdef _WIN32
#include <string>   // Required in order to use getline for Windows
#endif


// Overload Stream Insertion Operator
template<typename T>
std::ostream& operator<<(std::ostream&, const std::vector<T>&);

// Create job.txt file
void createJobFile(unsigned int);
void createJobFileTesting(unsigned int);  // Will have different seed values

// Tables
void generateTable(const std::vector<std::string>&, const std::vector<unsigned int>&);
void display_FCFS_info(const std::vector<std::string>&, const std::vector<unsigned int>&);
void display_SJF_info(const std::multimap<unsigned int, std::string>&);
void display_RR_2_info(const std::vector<std::string>&, const std::vector<unsigned int>&);
void display_RR_2_info(const std::vector<std::string>&, const std::vector<unsigned int>&);

// Helper functions for generateTable
void dashRows(unsigned int);
void displayJobNames(const std::vector<std::string>&, unsigned int);
void displayBurstTimes(const std::vector<unsigned int>&, unsigned int);

// Helper functions for scheduleTables
void headers();
std::string spacing1(unsigned int);
std::string spacing2(unsigned int);
std::string spacing3(unsigned int);

// Helper funtions for the scheduling algorithm
float accumulate(const std::vector<unsigned int>&);
float accumulate(const std::vector<float>&);
void ceil(float&);
void round(float&);


template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& jobs)
{
    unsigned int num = 0;

    out << "\n\t\t[  ";
    for (auto iter: jobs)
    {
        if (num++ > 9)  // So that only 10 numbers will be printed on one line
        {
            out << "\n\t\t   ";
            num = 0;
        }
        out << iter << "  ";
    }
    out << "]" << std::endl;

    return out;
}


// Function to create job.txt file
void createJobFile(unsigned int numJobs)
{
    // Create a file call "job.txt" to write to
    std::ofstream jobFile("job.txt");

    srand((unsigned int)time(0)); // Create seed for random burstTimes

    // Creating each job as many as numJobs
    for (int job = 1; job <= numJobs; job++)
    {
        // jobName = "Job1", "Job2", "Job3", etc
        std::string jobName = "Job" + ((job < 10)? "0" + std::to_string(job) : std::to_string(job) );
        unsigned int burstTime = (rand() % 20) + 1; // Randomly assigning burst time in ms

        // Writing to the job.txt file
        jobFile
            << jobName << std::endl
            << burstTime << std::endl;
    }

    // Properly close the job.txt file
    jobFile.close();
}


void createJobFileTesting(unsigned int numJobs)
{
    // Create a file call "job.txt" to write to
    std::ofstream jobFile("job.txt");

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    srand(seed); // Create seed for random burstTimes

    // Creating each job as many as numJobs
    for (int job = 1; job <= numJobs; job++)
    {
        // jobName = "Job1", "Job2", "Job3", etc
        std::string jobName = "Job" + ((job < 10)? "0" + std::to_string(job) : std::to_string(job) );
        unsigned int burstTime = (rand() % 20) + 1; // Randomly assigning burst time in ms

        // Writing to the job.txt file
        jobFile
            << jobName << std::endl
            << burstTime << std::endl;
    }

    // Properly close the job.txt file
    jobFile.close();
}


void generateTable(const std::vector<std::string>& jobNames,
    const std::vector<unsigned int>& burstTimes)
{
    // Getting the size of the table
    unsigned int size = jobNames.size();

    dashRows(size); // Top +--+
    displayJobNames(jobNames, size); // Display the job names
    dashRows(size); // middle +--+
    displayBurstTimes(burstTimes, size);
    dashRows(size); // bottom +--+

    std::cout << std::endl;
}


void display_FCFS_info(const std::vector<std::string>& jobNames,
    const std::vector<unsigned int>& burstTimes)
{
    // Display the headers
    headers();

    unsigned int size = jobNames.size(); // Number of jobs
    unsigned int startTime = 0; // Start time initially start at 0
    unsigned int endTime = 0;   // End time default at 0

    for (int idx = 0; idx < size; idx++)
    {
        std::cout
            << "\t| " << jobNames[idx] << " | "
            << "    " << startTime << spacing1(startTime);

        endTime += burstTimes[idx];     // Calculate the endTime

        std::cout
            << "   " << endTime << spacing2(endTime)
            << jobNames[idx] << " completed @ " << endTime << spacing3(endTime);

        startTime = endTime;    // Calculate the new start time
    }

    std::cout << "\t+-------+------------+----------+------------------------+";
    std::cout << std::endl << std::endl;
}


void display_SJF_info(const std::multimap<unsigned int, std::string>& jobs)
{
    // Display headers
    headers();

    unsigned int size = jobs.size();    // Number of jobs
    unsigned int startTime = 0;         // Initially start at 0
    unsigned int endTime = 0;           // Set to 0 by default

    for (auto iter: jobs)
    {
        std::cout
            << "\t| " << iter.second << " | "
            << "    " << startTime << spacing1(startTime);

        endTime += iter.first;

        std::cout
            << "   " << endTime << spacing2(endTime)
            << iter.second << " completed @ " << endTime << spacing3(endTime);

        startTime = endTime;    // Calculate the new start time
    }

    std::cout << "\t+-------+------------+----------+------------------------+";
    std::cout << std::endl << std::endl;
}


void display_RR_2_info(const std::vector<std::string>& jobNames,
    const std::vector<unsigned int>& burstTimes)
{
    // Display the headers
    headers();

    std::vector<std::string> jobsLeft(jobNames);    // All the jobs that hasn't finished
    std::vector<unsigned int> times(burstTimes);    // Copy of burstTimes

    unsigned int startTime = 0;             // Initially start at 0
    unsigned int endTime = 0;               // Set to 0 by default

    // Will loop until jobLeft size = 0
    while (true)
    {
        for (int idx = 0; idx < jobsLeft.size();) // Loop what jobs are left
        {
            std::string currentJob = jobsLeft[idx]; // What is the current job name
            bool jobFinished = false;   // Track what jobs are completed

            std::cout
                << "\t| " << jobsLeft[idx] << " | "
                << "    " << startTime << spacing1(startTime);

            // if the burst time is greater than 2 then subtract only 2 else subtract the burst time
            if (times[idx] > 2)
            {
                endTime += 2;   // Increment the burst time by 2
                times[idx] -= 2;
                idx++;
            }
            else
            {
                endTime += times[idx];
                jobsLeft.erase(jobsLeft.begin() + idx); // Remove job since it's complete
                times.erase(times.begin() + idx); // burst time is at 0, remove
                jobFinished = true; // Job is now complete set to true
            }

            std::cout << "   " << endTime << spacing2(endTime);

            if (jobFinished)
                std::cout << currentJob << " completed @ " << endTime << spacing3(endTime);
            else
                std::cout << "                       |" << std::endl;

            startTime = endTime;
        }

        if (jobsLeft.size() <= 0)
            break;
    }

    std::cout << "\t+-------+------------+----------+------------------------+";
    std::cout << std::endl << std::endl;
}


void display_RR_5_info(const std::vector<std::string>& jobNames,
    const std::vector<unsigned int>& burstTimes)
{
    // Display the headers
    headers();

    std::vector<std::string> jobsLeft(jobNames);    // All the jobs that hasn't finished
    std::vector<unsigned int> times(burstTimes);    // Copy of burstTimes

    unsigned int startTime = 0;             // Initially start at 0
    unsigned int endTime = 0;               // Set to 0 by default

    // Will loop until jobLeft size = 0
    while (true)
    {
        for (int idx = 0; idx < jobsLeft.size();) // Loop what jobs are left
        {
            std::string currentJob = jobsLeft[idx]; // What is the current job name
            bool jobFinished = false;   // Track what jobs are completed

            std::cout
                << "\t| " << jobsLeft[idx] << " | "
                << "    " << startTime << spacing1(startTime);

            // if the burst time is greater than 2 then subtract only 2 else subtract the burst time
            if (times[idx] > 5)
            {
                endTime += 5;   // Increment the burst time by 2
                times[idx] -= 5;
                idx++;
            }
            else
            {
                endTime += times[idx];
                jobsLeft.erase(jobsLeft.begin() + idx); // Remove job since it's complete
                times.erase(times.begin() + idx); // burst time is at 0, remove
                jobFinished = true; // Job is now complete set to true
            }

            std::cout << "   " << endTime << spacing2(endTime);

            if (jobFinished)
                std::cout << currentJob << " completed @ " << endTime << spacing3(endTime);
            else
                std::cout << "                       |" << std::endl;

            startTime = endTime;
        }

        if (jobsLeft.size() <= 0)
            break;
    }

    std::cout << "\t+-------+------------+----------+------------------------+";
    std::cout << std::endl << std::endl;
}


void headers()
{
    std::string headers[] = { "Job #", "Start Time", "End Time", "Job Completion" };

    unsigned int size = sizeof(headers) / sizeof(headers[0]);

    std::cout << "\t+-------+------------+----------+------------------------+" << std::endl;
    std::cout << "\t| ";
    for (int idx = 0; idx < size; idx++)
        std::cout << headers[idx] << ((idx < size - 1)? " | " : "         | " );
    std::cout << std::endl;
    std::cout << "\t+-------+------------+----------+------------------------+" << std::endl;

}


std::string spacing1(unsigned int size)
{
    if (size < 10) return "      | ";
    else if (size >= 10 && size < 100) return "     | ";
    else return "    | ";
}


std::string spacing2(unsigned int size)
{
    if (size < 10) return "     | ";
    else if (size >= 10 && size < 100) return "    | ";
    else return "   | ";
}


std::string spacing3(unsigned int size)
{
    if (size < 10) return "    |\n";
    else if (size >= 10 && size < 100) return "   |\n";
    else return "  |\n";
}


// function for generateTable()
void dashRows(unsigned int size)
{
    std::cout << "\t+---------------+-";
    for (int idx = 0; idx < size; idx++)
        std::cout << "------";
    std::cout << "+" << std::endl;
}


void displayJobNames(const std::vector<std::string>& jobNames, unsigned int size)
{
    std::cout << "\t| Job #         ";
    std::cout << "| ";
    for (int idx = 0; idx < size; idx++)
        std::cout << jobNames[idx] << " ";
    std::cout << "|" << std::endl;
}


void displayBurstTimes(const std::vector<unsigned int>& burstTimes, unsigned int size)
{
    std::cout << "\t| BurstTime (ms)";
    std::cout << "|";
    for (int idx = 0; idx < size; idx++)
        std::cout << "   " << burstTimes[idx] << ((burstTimes[idx] < 10)? "  " : " " );
    std::cout << " |" << std::endl;
}


// This function add all the elements in a vector
float accumulate(const std::vector<unsigned int>& times)
{
    float sum = 0.0;

    for (auto iter: times)
        sum += iter;

    return sum;
}


// This function add all the elements in a vector
float accumulate(const std::vector<float>& times)
{
    float sum = 0.0;

    for (auto iter: times)
        sum += iter;

    return sum;
}


// This function works the same way as ceil in cmath library
void ceil(float& number)
{
    int wholeNumber = int(number);  // Get the number before the decimal point
    float decimal = number - wholeNumber; // getting the numbers after the decimal

    if (decimal > 0)
    {
        // Subtracting the number after the decimal with 1 will give us how much we need to round up
        float remain = 1 - decimal;
        number += remain;   // Will round up for us
    }
}


void round(float& number)
{
    unsigned int z = ( number + 0.005 ) * 100;
    number = z / 100.0;
}


#endif // ! FUNCTIONS_H
