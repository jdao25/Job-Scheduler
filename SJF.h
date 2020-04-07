/*
    Shortest Job First functions
*/


#ifndef SJF_H
#define SJF_H

#include "functions.h"


// List the job order when using this scheduling algorithm
std::vector<std::string> FCFS_order(const std::vector<std::string>&); // First Come First Serve

// Calculate the Average Turnaround Time of SJF
float SJF_time(const std::multimap<unsigned int, std::string>&);


std::vector<std::string> SJF_order(const std::multimap<unsigned int, std::string>& jobs)
{
    /*
        By putting the element into a multimap with pair < burstTime, jobName >
        by default the burstTimes will be in ascending order. If we print out
        the second value, JobName, of each pair in the multimap, the jobName
        would be in Shortest Job First order.

        Input: multimap with pair < burstTime, jobNames >
        Output: a vector with SJF order
    */


    // This vector will hold the job names in order if we are to use this scheduling algorithm
    std::vector<std::string> order;

    for (auto iter: jobs)
        order.push_back(iter.second);

    return order;
}


float SJF_time(const std::multimap<unsigned int, std::string>& jobs)
{
    /*
        To calculate the time, I would add the first value, burstTime, of each
        in the multimap. Since the first values (keys) of the pair is by default
        in ascending order. Then divide the sum by the number of jobs.

        Input: multimap jobs with pair < burstTime, jobName >
        Output: Float, Average Turnaround Time
    */


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

    // divide sum by the number of jobs to get average
    float avgTurnaroundTime = sum / numJobs;

    // Round to two decimal places
    round(avgTurnaroundTime);

    return avgTurnaroundTime;   // Return the average
}


#endif // ! SJF_H
