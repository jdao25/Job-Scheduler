/*
    Round-Robin (with a time slice of 5) functions
*/


#ifndef RR_5_H
#define RR_5_H

#include "functions.h"


// List the job order when using this scheduling algorithm
std::vector<std::string> RR_5_order(const std::vector<std::string>&, const std::vector<unsigned int>&); // Round-Robin (time slice of 5)

// Calculate the Average Turnaround Time of Round-Robin 5
float RR_5_time(const std::vector<std::string>&, const std::vector<unsigned int>&);

// List the job complete order
std::vector<std::string> RR_5_order_complete(const std::vector<std::string>&, const std::vector<unsigned int>&);


std::vector<std::string> RR_5_order(const std::vector<std::string>&jobNames,
    const std::vector<unsigned int>& burstTimes)
{
    /*
        By having a vector, jobLeft, that contains all the jobs that needs to
        be executed, in the same order given, and another vector with the burst
        time with each index of both vector cooresponding, we can give the order
        that each job will be executed.

        Input: Two vectors, jobNames, burstTimes
        Output: A list of all the jobs in Round-Robin order
    */


    std::vector<std::string> order;     // Will hold the schedule algorithm's job order
    std::vector<std::string> jobsLeft(jobNames);    // All the jobs that hasn't finished
    std::vector<unsigned int> times(burstTimes);    // Copy of burstTimes

    unsigned int startTime = 0;             // Initially start at 0
    unsigned int endTime = 0;               // Set to 0 by default

    // Will loop until jobLeft size = 0
    while (true)
    {
        for (int idx = 0; idx < jobsLeft.size();) // Loop what jobs are left
        {
            order.push_back(jobsLeft[idx]);

            bool jobFinished = false;   // Track what jobs are completed

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

            startTime = endTime;
        }

        if (jobsLeft.size() <= 0)
            break;
    }

    return order;
}


float RR_5_time(const std::vector<std::string>& jobNames,
    const std::vector<unsigned int>& burstTimes)
{
    /*
        Calcuate the Average Turnaround Time of Round-Robin 5

        Input: Two vectors, jobNames, burstTimes
        Output: A Float, Average Turnaround Time
    */


    std::vector<std::string> jobsLeft(jobNames);    // All the jobs that hasn't finished
    std::vector<unsigned int> times(burstTimes);    // Copy of burstTimes
    std::vector<unsigned int> jobCompleteTimes;     // Hold all of the job complete times

    unsigned int numJobs = jobNames.size();
    unsigned int startTime = 0;             // Initially start at 0
    unsigned int endTime = 0;               // Set to 0 by default

    // Will loop until jobLeft size = 0
    while (true)
    {
        for (int idx = 0; idx < jobsLeft.size();) // Loop what jobs are left
        {
            bool jobFinished = false;   // Track what jobs are completed

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

            if (jobFinished) jobCompleteTimes.push_back(endTime);

            startTime = endTime;
        }

        if (jobsLeft.size() <= 0)
            break;
    }

    float sum = accumulate(jobCompleteTimes);

    // divide sum by the number of jobs to get average
    float avgTurnaroundTime = sum / numJobs;

    // Round to two decimal places
    round(avgTurnaroundTime);

    return avgTurnaroundTime;   // Return the average
}


std::vector<std::string> RR_5_order_complete(const std::vector<std::string>& jobNames,
    const std::vector<unsigned int>& burstTimes)
{
    /*
        This function will give us the order in with each job is completed

        Input: Two vectors, jobNames and burstTimes
        Output: A vector of each jobName in order of completion
    */


    std::vector<std::string> jobsLeft(jobNames);    // All the jobs that hasn't finished
    std::vector<unsigned int> times(burstTimes);    // Copy of burstTimes
    std::vector<std::string> orderCompleted;

    unsigned int startTime = 0;             // Initially start at 0
    unsigned int endTime = 0;               // Set to 0 by default

    // Will loop until jobLeft size = 0
    while (true)
    {
        for (int idx = 0; idx < jobsLeft.size();) // Loop what jobs are left
        {
            std::string currentJob = jobsLeft[idx]; // What is the current job name
            bool jobFinished = false;   // Track what jobs are completed

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

            if (jobFinished)
                orderCompleted.push_back(currentJob);

            startTime = endTime;
        }

        if (jobsLeft.size() <= 0)
            break;
    }

    return orderCompleted;
}


#endif // ! RR_5_H
