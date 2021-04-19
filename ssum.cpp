

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>


struct ssum_elem {
  unsigned int x;
  std::string name;
};

struct book{
    bool possible = false;
    unsigned long long int distinct = 0;
    unsigned long long int smallest_size = 0;
    unsigned long long int num_of_small_sets = 0;
    std::vector<ssum_elem> elemsFrom;
    
};


//Function that returns of the two vectors which is alphabetically lower
int returnLowestVector(std::vector<ssum_elem> elems1, std::vector<ssum_elem> elems2){
    int size1 = elems1.size();
    int size2 = elems2.size();
    
    if (size1 == 0 && size2 ==0){
        return 1;
    }
    
    if(size1 > size2){
        return 1;
    }
    
    else if (size1 < size2){
        return 2;
    }
    
    //equals sizes
    else{
        std::string global1 = elems1[0].name;
        std::string global2 = elems2[0].name;
        for(int i = 1 ; i <size1; i++){
            //concacatenate strings
            global1+= elems1[i].name;
            global2+= elems2[i].name;
        }
        //compare if they are lower
        if(global1 < global2){
            return 1;
        }
        else{
            return 2;
        }
    }
}

class ssum_instance {
    unsigned int target=0;
    std::vector<ssum_elem> elems;
    std::vector<std::vector<book> > feasible;
    // feasible[i][x] = TRUE if there is a subset
    //  of a[0..i] adding up to x; FALSE otherwise
    //  (once instacne has been solved)
    //
    int done=false;    // flag indicating if dp has been run or 
                       //   not on this instance

    public:

    // Function:  read_elems
    // Description:  reads elements from standard-input; 
    //   Format:  sequence of <number> <name> pairs where
    //      <number> is non-negative int and
    //      <name> is a string associated with element
    void read_elems( std::istream &stream) {
        ssum_elem e;

        elems.clear();
        // while(std::cin >> e.x && std::cin >> e.name) {
        while(stream>> e.x && stream >> e.name) {
            elems.push_back(e);
        }
        done = false;
    }

    // Function:  solve
    // Desc:  populates dynamic programming table of
    //    calling object for specified target sum.
    //    Returns true/false depending on whether the
    //    target sum is achievalble or not.
    //    Table remains intact after call.
    //    Object can be reused for alternative target sums.
    book solve(unsigned int tgt) {
        unsigned int n = elems.size();
        unsigned int i, x;

        if(target == tgt && done) 
            return feasible[n-1][tgt];

        target = tgt;
        feasible = 
            std::vector<std::vector<book> >(n, std::vector<book>(target+1));

        // leftmost column (column zero) is all TRUE because 
        //    a target sum of zero is always acheivable (via the
        //    empty set).
        for(i=0; i<n; i++){
            feasible[i][0].possible = true;
            feasible[i][0].distinct = 1;
            feasible[i][0].smallest_size = 0;
            feasible[i][0].num_of_small_sets = 1;
        }

        for(x=1; x<=target; x++) {
            if(elems[0].x == x){
                feasible[0][x].possible = true;
                feasible[0][x].distinct = 1;
                feasible[0][x].smallest_size = 1;
                feasible[0][x].num_of_small_sets = 1;
                feasible[0][x].elemsFrom.push_back(elems[0]);

            }
            // otherwise, feasible[0][x] remains false
        }
        
        for(i=1; i<n; i++) {
            for(x=1; x<=tgt; x++) {
                
                bool upAndLeft = false;
                bool justUp = false;
                int val;
                
                if(feasible[i-1][x].possible){
                    feasible[i][x].possible = true;
                    feasible[i][x].distinct += feasible[i-1][x].distinct;
                    justUp = true;
                }
                
                if(x >= elems[i].x && feasible[i-1][x-elems[i].x].possible){
                    feasible[i][x].possible = true;
                    feasible[i][x].distinct += feasible[i-1][x-elems[i].x].distinct;
                    upAndLeft = true;
                }
                
                if (upAndLeft && justUp){
                    if( (feasible[i-1][x-elems[i].x].smallest_size + 1 ) < feasible[i-1][x].smallest_size ){
                        feasible[i][x].smallest_size = feasible[i-1][x-elems[i].x].smallest_size + 1;
                        feasible[i][x].num_of_small_sets = feasible[i-1][x-elems[i].x].num_of_small_sets;
                        std::vector<ssum_elem> temp1 = feasible[i-1][x-elems[i].x].elemsFrom;
                        temp1.push_back(elems[i]);
                       
                        std::vector<ssum_elem> temp2 = feasible[i][x].elemsFrom;
                        val = returnLowestVector(temp1,temp2);
                            if(val == 1){
                                feasible[i][x].elemsFrom = temp1;
                            }
                        
                    }
                    
                    else if ( (feasible[i-1][x-elems[i].x].smallest_size + 1 ) == (feasible[i-1][x].smallest_size) ){
                        feasible[i][x].smallest_size = feasible[i-1][x].smallest_size;
                        feasible[i][x].num_of_small_sets = feasible[i-1][x-elems[i].x].num_of_small_sets + feasible[i-1][x].num_of_small_sets;
                        
                        //Create a vector with the element we are looking for
                        //Now there are three possible vectors, the position already has a vector, up and to left has a vector plus the element we are on,
                        //or the vector that is directly above us.
                        //Of those vectors determine which is lexically the lowest using the returnLowestVectorFunction
                        // then put that vector into the feasible position we are on's vector
                        std::vector<ssum_elem> temp1 = feasible[i-1][x-elems[i].x].elemsFrom;
                        temp1.push_back(elems[i]);
                        std::vector<ssum_elem> temp2 = feasible[i][x].elemsFrom;
                        std::vector<ssum_elem> temp3 = feasible[i-1][x].elemsFrom;
                        val = returnLowestVector(temp1,temp3);
                        if(val == 1){
                            val = returnLowestVector(temp1,temp2);
                            if(val == 1){
                                feasible[i][x].elemsFrom = temp1;
                            }
                        }
                        
                        else{
                            val = returnLowestVector(temp3,temp2);
                            if(val==1){
                                feasible[i][x].elemsFrom = temp3;
                            }
                        }
    
                    }
                    else{
                        feasible[i][x].smallest_size = feasible[i-1][x].smallest_size;
                        feasible[i][x].num_of_small_sets = feasible[i-1][x].num_of_small_sets;
                        feasible[i][x].elemsFrom = feasible[i-1][x].elemsFrom;
                    }
                }
                
                if (upAndLeft && !justUp){
                    feasible[i][x].smallest_size = feasible[i-1][x-elems[i].x].smallest_size + 1;
                    feasible[i][x].num_of_small_sets = feasible[i-1][x-elems[i].x].num_of_small_sets;
                    std::vector<ssum_elem> temp1 = feasible[i-1][x-elems[i].x].elemsFrom;
                    temp1.push_back(elems[i]);
                    std::vector<ssum_elem> temp2 = feasible[i][x].elemsFrom;
                    val = returnLowestVector(temp1,temp2);
                    if(val == 1){
                        feasible[i][x].elemsFrom = temp1;
                    }
    
                        
                }
                
                if (!upAndLeft && justUp){
                    feasible[i][x].smallest_size = feasible[i-1][x].smallest_size;
                    feasible[i][x].num_of_small_sets = feasible[i-1][x].num_of_small_sets;
                    feasible[i][x].elemsFrom = feasible[i-1][x].elemsFrom;
                }
                
            }
            // otherwise, feasible[0][x] remains false
        }
        done = true;
       
        return feasible[n-1][target];
    }
};  // end class





/**
* usage:  ssum  <target> < <input-file>
*
*
* input file format:
*
*     sequence of non-negative-int, string pairs
*
*     example:

    12 alice
    9  bob
    22 cathy
    12 doug

* such a file specifies a collection of 4 integers: 12, 9, 22, 12
* "named" alice, bob, cathy and doug.
*/
int main(int argc, char *argv[]) {
  unsigned int target;
  ssum_instance ssi;

  if(argc != 2) {
    fprintf(stderr, "one cmd-line arg expected: target sum\n");
    return 0;
  }
  if(sscanf(argv[1], "%u", &target) != 1) {
    fprintf(stderr, "bad argument '%s'\n", argv[1]);
    fprintf(stderr, "   Expected unsigned integer\n");
    return 0;
  }

  ssi.read_elems(std::cin);

  book myBook = ssi.solve(target);
  if(myBook.possible) {
    std::cout << "HOORAY!  Apparently, the target sum of " <<
      target << " is achievable\n";
    std::cout << "Distinct Subsets are :"<<myBook.distinct<<"\n" <<
      "Smallest Size is : " <<myBook.smallest_size<<"\n" <<
      "Number of subsets with the smallest size :" <<myBook.num_of_small_sets<<"\n";
      int size = myBook.elemsFrom.size();
      for(int i = 0; i < size ; i++){
          std::cout<<myBook.elemsFrom[i].name<<"\n";
      }
  }
  else {
    std::cout << "SORRY!  Apparently, the target sum of " <<
      target << " is NOT achievable\n";
  }

}
