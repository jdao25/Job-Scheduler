#ifndef SCHEDULING_ALGORITHMS_H
#define SCHEDULING_ALGORITHMS_H

#include "functions.h"

// List the order of the jobs according to the scheduling algorithm
std::vector<std::string> FCFS_order(const std::vector<std::string>&); // First Come First Serve
std::vector<std::string> SJF_order(const std::multimap<unsigned int, std::string>&); // Shortest Job First
std::vector<std::string> RR_2_order(const std::vector<std::string>&, const std::vector<unsigned int>&); // Round-Robin (time slice of 2)
std::vector<std::string> RR_5_order(const std::vector<std::string>&, const std::vector<unsigned int>&); // Round-Robin (time slice of 5)

// Return the average turnaround time of the algorithm
float FCFS_time(const std::vector<unsigned int>&);
float SJF_time(const std::multimap<unsigned int, std::string>&);
float RR_2_time(const std::vector<std::string>&, const std::vector<unsigned int>&);
float RR_5_time(const std::vector<std::string>&, const std::vector<unsigned int>&);

// Round-Robin
std::vector<std::string> RR_2_order_complete(const std::vector<std::string>&, const std::vector<unsigned int>&);
std::vector<std::string> RR_5_order_complete(const std::vector<std::string>&, const std::vector<unsigned int>&);


// Listing each scheduling algorithm's jobs order below


// First Come First Serve should be the same order it was received
std::vector<std::string> FCFS_order(const std::vector<std::string>& job)
{
    return job; // Just return the current job order
}


std::vector<std::string> SJF_order(const std::multimap<unsigned int, std::string>& jobs)
{
    // This vector will hold the job names in order if we are to use this scheduling algorithm
    std::vector<std::string> order;

    for (auto iter: jobs)
        order.push_back(iter.second);

    return order;
}


std::vector<std::string> RR_2_order(const std::vector<std::string>&jobNames,
    const std::vector<unsigned int>& burstTimes)
{
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

            startTime = endTime;
        }

        if (jobsLeft.size() <= 0)
            break;
    }

    return order;
}


std::vector<std::string> RR_5_order(const std::vector<std::string>&jobNames,
    const std::vector<unsigned int>& burstTimes)
{
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




// Calculating Average Turnaround Time for each Algorithm below


float FCFS_time(const std::vector<unsigned int>& burstTimes)
{
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

    // Return the avg by dividing avgTime with num of jobs
    return sum / numJobs;
}


float SJF_time(const std::multimap<unsigned int, std::string>& jobs)
{
    unsigned int totalTime = 0; // Keep track of the times as each job finishes
    unsigned int numJobs = jobs.size(); // Number of jobs
    std::vector<unsigned int> times; // Vector to collect each job's finish time

    for (auto iter: jobs)
    {
        totalTime += iter.first;
        times.push_back(totalTime);
    }

    // Add all the times together starting from 0
    float sum = accumulate(times);

    return sum / numJobs;
}


float RR_2_time(const std::vector<std::string>& jobNames,
    const std::vector<unsigned int>& burstTimes)
{
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

            if (jobFinished) jobCompleteTimes.push_back(endTime);

            startTime = endTime;
        }

        if (jobsLeft.size() <= 0)
            break;
    }

    float sum = accumulate(jobCompleteTimes);

    return sum / numJobs;
}


float RR_5_time(const std::vector<std::string>& jobNames,
    const std::vector<unsigned int>& burstTimes)
{
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

    return sum / numJobs;
}




// Round-Robin Additional functions
std::vector<std::string> RR_2_order_complete(const std::vector<std::string>& jobNames,
    const std::vector<unsigned int>& burstTimes)
{
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

            if (jobFinished)
                orderCompleted.push_back(currentJob);

            startTime = endTime;
        }

        if (jobsLeft.size() <= 0)
            break;
    }

    return orderCompleted;
}


std::vector<std::string> RR_5_order_complete(const std::vector<std::string>& jobNames,
    const std::vector<unsigned int>& burstTimes)
{
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


#endif // !SCHEDULING_ALGORITHMS_H
