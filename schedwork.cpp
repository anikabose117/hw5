#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t day,
    std::vector<size_t> shiftTrack, // tracks how many total shifts each worker is scheduled for, using 0-based indexing
    size_t n,
    size_t k
);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed, // d 
    const size_t maxShifts, // m
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    size_t n = avail.size(); // days
    size_t k = avail[0].size(); // workers



    std::vector<size_t> shiftTracker;
    for (size_t i = 0; i < k; i++){
        shiftTracker.push_back(0);
    }

    for (size_t i = 0; i < n; i++) {
        // sched passed through schedule has no specific size
        // update so it is the length of days
        vector<Worker_T> temp;
        sched.push_back(temp);
    }

    // pass through with day as 0, using 0-based indexing
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, 0, shiftTracker, n, k);

}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t day,
    std::vector<size_t> shiftTrack, // tracks how many total shifts each worker is scheduled for, using 0-based indexing
    size_t n,
    size_t k
){
    
    // we have reached the end of the schedule, i.e. no more days that need to be filled
    // recall: using 0-based indexing for day, and n is avail.size()
    if (day >= n){ 
        return true;    
    }

    // number of nurses scheduled on the day meet dailyNeed, recurse to the next day in the schedule that needs to be filled
    if (sched[day].size() >= dailyNeed){
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, day + 1, shiftTrack, n, k);
    }   


    // loop through all workers 
    for (size_t i = 0; i < k; i++){
        // conditional to check if worker i has not exceeded their shift count and are available that day to work
        // checks through schedule to ensure worker has not already been booked for the day
        
        if (shiftTrack[i] < maxShifts && avail[day][i] == true && std::find(sched[day].begin(), sched[day].end(), i) == sched[day].end()){
            // add nurse to the vector of nurses working that day
            sched[day].push_back(i);
            
            // increase their tracker by 1 shift
            shiftTrack[i]++;

            // recursively call to ensure day has been been filled , if false then backtrack
            if (scheduleHelper(avail, dailyNeed, maxShifts, sched, day, shiftTrack, n, k) == true){
                return true;
            }

            // backtrack by deleting worker from the day's schedule and updating their shift count
            sched[day].pop_back();
            shiftTrack[i]--;

        }
    }

    // doesn't work
   return false;
}

