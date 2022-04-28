This program takes an input file of a system of processes' resource use data, and uses the bankers
algorithm to determine whether or not the system is in a safe state.


Input file format:

There must be just a number for each data point,
with a space or a new line between each number.
The resource types must be in the same order for each process.

Start with resources allocated to each process,
then have the max resources each process will use,
finish with the available resources.
The processes must be in the same order between the resources allocated and max resources sections.

Insert -1 as a data point after each process.
Insert -2 as a data point after the final -1 in the resources allocated and max resources sections.

Name the input file "input.txt".
Put in the same directory as bankersAlgorithm.cpp.


To run:
g++ -o bankersAlgorithm bankersAlgorithm.cpp 
./bankersAlgorithm
