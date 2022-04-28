// Chad Losey
// bankersAlgorithm.cpp
// This program takes an input file of a system of processes' resource
// use data, and uses bankers algorithm to determine whether or not the
// system is in a safe state

#include <iostream>
#include <fstream>
#include <vector>

int main() {
    // open file
    std::ifstream inputFile("input.txt");

    std::vector<std::vector<int>> allocatedResources;
    std::vector<int> processResources;
    std::vector<bool> processFinished;
    int number;

    // stores allocated resources as a vector of vectors of ints
    // uses -1 as a delimiter between procceses
    // uses -2 as a delimiter between allocated, max, and available resources
    inputFile >> number;
    while (number != -2) {
        while (number != -1) {
            processResources.push_back(number);
            inputFile >> number;
        }

        processFinished.push_back(false);
        allocatedResources.push_back(processResources);
        processResources.clear();

        inputFile >> number;
    }

    std::vector<std::vector<int>> maxResources;

    // stores max resources as vector of vectors of ints
    inputFile >> number;
    while (number != -2) {
        while (number != -1) {
            processResources.push_back(number);
            inputFile >> number;
        }
        
        maxResources.push_back(processResources);
        processResources.clear();

        inputFile >> number;
    }

    std::vector<int> availableResources;

    // stores available resources as vector of ints
    inputFile >> number;
    while (number != -1) {
            availableResources.push_back(number);
            inputFile >> number;
    }

    // needed resources = max resources - allocated resources
    std::vector<std::vector<int>> neededResources = maxResources;
    for (unsigned i = 0; i < maxResources.size(); ++i) {
        for (unsigned j = 0; j < maxResources[i].size(); ++j) {
            neededResources[i][j] = maxResources[i][j] - allocatedResources[i][j];
        }
    }
    
    std::vector<int> safeSequence;
    bool neededLessThanAvailable;
    bool keepLooping = true;
    while (keepLooping) {
        // will exit loop if no processes can be finished
        keepLooping = false;

        for (unsigned i = 0; i < neededResources.size(); ++i) {

            // determine if needed resources are less than
            // available resources for process i
            neededLessThanAvailable = true;
            for (unsigned j = 0; j < neededResources[i].size(); ++j) {
                if (neededResources[i][j]>availableResources[j]) {
                    neededLessThanAvailable = false;
                }
            }

            // if process is unfinished and needed resources
            // are less than available resources
            if (neededLessThanAvailable && (!processFinished[i])) {
                keepLooping = true;
                processFinished[i] = true;
                // records order processes finished for safe sequence
                safeSequence.push_back(i);

                // adds the now finished process's resources to the available resources
                for (unsigned j = 0; j < allocatedResources[i].size(); ++j) {
                    availableResources[j] += allocatedResources[i][j];
                }
            }
            
        }
    }

    // if all processes finished, it is in safe state
    // if there are any unfinished processes it is in unsafe state
    bool safeState = true;
    for (unsigned i = 0; i < processFinished.size(); ++i) {
            if (processFinished[i] == false) {
                safeState = false;
            }
    }

    // output whether it's in a safe or an unsafe state
    // if in a safe state, output safe sequence
    if (safeState) {
        std::cout << "System is in a safe state.\nA safe sequence is <";
        for (unsigned i = 0; i < safeSequence.size()-1; ++i) {
            std::cout << "p" << safeSequence[i] << ", ";
        }
        std::cout << "p" << safeSequence[safeSequence.size()-1] << ">.\n";

    } else {
        std::cout << "System is in an unsafe state.\n";
    }
}