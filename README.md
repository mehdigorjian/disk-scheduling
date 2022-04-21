# disk-scheduling
Operating system disk scheduling algorithms implementing the following disk-scheduling algorithms:

a. FCFS
b. SCAN
c. C-SCAN

The program will service a disk with 5,000 cylinders numbered 0 to 4,999, and generates a random series of 1,000-cylinder requests and service them according to each of the algorithms listed above. The program will be passed the initial position of the disk head (as a parameter on the command line) and report the total amount of head movement required by each algorithm.

`// COMPILATION: gcc disk_scheduling.cpp -o disk_scheduling -lstdc++` \
`//         RUN: ./disk_scheduling HEAD`
