/*
    First Come First Serve functions
*/


#ifndef FCFS_H
#define FCFS_H

#include "functions.h"


// Display the order of FCFS Algorithm
std::vector<std::string> FCFS_order(const std::vector<std::string>&); // First Come First Serve

// Calculate the Average Turnaround Time of FCFS
float FCFS_time(const std::vector<unsigned int>&);


// First Come First Serve should be the same order it was received
std::vector<std::string> FCFS_order(const std::vector<std::string>& job)
{
    /*
        The order of First Come First Serve will be the default given order
        of the jobs.

        Input: vector<string> jobs. This is a list of the Job numbers
        Output: The order if FCFS was used
    */


    return job; // Just return the current job order
}


float FCFS_time(const std::vector<unsigned int>& burstTimes)
{
    /*
        To calculate the Average Turnaround Time of FCFS, we will
        add each job burst time with the previous. Then devided by the
        number of jobs.

        Input: A vector, burstTimes, that holds all the burst times of each job
        Output: A float, Average Turnaround Time
    */


    // Variable holding the total time
    unsigned int totalTime = 0;

    // Number of jobs
    unsigned int numJobs = burstTimes.size();

    // A vector to track all times when each job finishes
    std::vector<unsigned int> times;

    for (int idx = 0; idx < numJobs; idx++)
    {
        totalTime += burstTimes[idx];
        times.push_back(totalTime);
    }

    // Add up all of the times
    float sum = accumulate(times);

    // divide sum by the number of jobs to get average
    float avgTurnaroundTime = sum / numJobs;

    // Round to two decimal places
    round(avgTurnaroundTime);

    return avgTurnaroundTime;   // Return the average
}


#endif // ! FCFS_H
