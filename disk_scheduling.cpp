// COMPILATION: gcc disk_scheduling.cpp -o disk_scheduling -lstdc++
//         RUN: ./disk_scheduling HEAD
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
 


int size = 1000;
int disk_size = 5000;
void fcfs(int arr[], int head)
{
    int move_count = 0;
    int dist, current_track;
 
    for (int i = 0; i < size; i++) {
        current_track = arr[i];
        // absolute dist measuring
        dist = abs(current_track - head);
        // adding to the total count
        move_count += dist;
        // accessed track is now new head
        head = current_track;
    }
 
    cout << "Total head movement using FCFS: "
         << move_count << endl;
}

void scan(int arr[], int head, string direction)
{
    int move_count = 0;
    int dist, current_track;
    vector<int> left, right;
    vector<int> seek_sequence;
 
    // adding visited end values before direction reversing 
    if (direction == "left")
        left.push_back(0);
    else if (direction == "right")
        right.push_back(disk_size - 1);
 
    for (int i = 0; i < size; i++) {
        if (arr[i] < head)
            left.push_back(arr[i]);
        if (arr[i] > head)
            right.push_back(arr[i]);
    }
 
    // sorting left-right vectors
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
 
    // two loops for left and right
    int run = 2;
    while (run--) {
        if (direction == "left") {
            for (int i = left.size() - 1; i >= 0; i--) {
                current_track = left[i];
 
                // adding the current track to the seek
                seek_sequence.push_back(current_track);
 
                // calculate absolute dist
             dist = abs(current_track - head);
 
                // increase the total count
                move_count += dist;
 
                // new head
                head = current_track;
            }
            direction = "right";
        }
        else if (direction == "right") {
            for (int i = 0; i < right.size(); i++) {
                current_track = right[i];
                // adding the current track to the seek
                seek_sequence.push_back(current_track);
 
                // calculate absolute dist
             dist = abs(current_track - head);
 
                // increase the total count
                move_count += dist;
 
                // now new head
                head = current_track;
            }
            direction = "left";
        }
    }
 
    cout << "Total head movement using SCAN: "
         << move_count << endl;
}

void cscan(int arr[], int head)
{
    int move_count = 0;
    int dist, current_track;
    vector<int> left, right;
    vector<int> seek_sequence;
 
    // adding visited end values before direction reversing 
    left.push_back(0);
    right.push_back(disk_size - 1);
    // when the head moves to the start point, the left side tracks will be used
    for (int i = 0; i < size; i++) {
        if (arr[i] < head)
            left.push_back(arr[i]);
        if (arr[i] > head)
            right.push_back(arr[i]);
    }
 
    // sorting left-right vectors
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
 
    // first serve the requests on the right side of the head
    for (int i = 0; i < right.size(); i++) {
        current_track = right[i];
        // appending current track to seek sequence
        seek_sequence.push_back(current_track);
 
        // calculate absolute dist
     dist = abs(current_track - head);
 
        // increase the total count
        move_count += dist;
 
        // new head
        head = current_track;
    }
 
    // gor to the start once gets to the right end
    head = 0;
 
    // adding seek count for head
    move_count += (disk_size - 1);
 
    // servethe the left requests again
    for (int i = 0; i < left.size(); i++) {
        current_track = left[i];
 
        // appending current track to the seek
        seek_sequence.push_back(current_track);
 
        // calculate absolute dist
     dist = abs(current_track - head);
 
        // increase the total count
        move_count += dist;
 
        // accessed track is now the new head
        head = current_track;
    }
 
    cout << "Total head movement using C-SCAN: "
         << move_count << endl;
}

int main(int argc, char **argv)
{
    // direction of the movement
    string direction = "left";
    // head location as an argument
    int head = atoi(argv[1]);
    // generating an array of 1000 element between 0 to 4999
    int arr[size];
    for(int i = 0; i < size; i++){
        arr[i] = rand() % disk_size;
    }
    // running the algorithms
    fcfs(arr, head);
    scan(arr, head, direction);
    cscan(arr, head);
    return 0;
}
// Reference
// https://www.geeksforgeeks.org/fcfs-disk-scheduling-algorithms/
// https://www.geeksforgeeks.org/scan-elevator-disk-scheduling-algorithms/
// https://www.geeksforgeeks.org/c-scan-disk-scheduling-algorithm/