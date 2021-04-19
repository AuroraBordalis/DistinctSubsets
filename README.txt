Shawn John. 


Once you run the makefile you can run the executable like beloew. 
	ssum <TARGET> < <INPUT-FILE>

The cmd-line argument is the target sum itself.
The program reads the elements ​a[1]...a[N]​ from std-input.

This program is an example of dynamic programming. The program takes in a list of integers and labels.
The program then finds if those list of integers have a subset that add up to the target given by the user. 
For example, the eloctoral.txt file provides the electoral votes for each state. The user can then find out if there is a 
combination of states that add up to 270. The program finds the number of distinct subsets that add up to that target value, 
the size of the smallest subset, and provides the actual smallest subset that adds up to the target. 

Space and Runtime. 
The program takes up an O(NxT) space. N being the number of elements in the list and t being the target value. The largest data 
strucuture is the vector of vectors that has NxT for all the booking keeping needed. 

The runtime is O(N^2xT) because the algorithim traverses through the table once doing constant time calculations but it also copies a vector from the previous position and 
each vector could be at most size N. 

