/*****************************************************************************
*                    
*  Author:           Garrett Mathers
*  Email:            garrett.mathers@gmail.com
*  Label:            List Class
*  Title:            Basic Project Organization
*  Course:           Algorithms 3013
*  Semester:         Spring Semester // 2022
* 
*  Description:
*        A stack that resizes according to four params. they are all
*        thresholds based on the stack being fully dynamic and resizing
*        accordingly. 
*
*
*  Usage:
*        Run from the command line and provide four paramaters listed below.
*        use percentages like 0.75 or 0.25 you can even use 2.0 to double 
*        the size of it. But for the first two use between 0.0 and 1.0 
*         
*        1st: Too Full Threshold (where to enlarge it at)
*        2nd: Too Empty Threshold (where to shrink it at)
*        3rd: Enlarging Threshold (how much to enlarge it by)
*        4th: Shrinking Threshold (how much to shrink it by)
* 
*  Files:            N/A
*****************************************************************************/

#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;


/**
 * ArrayStack
 * 
 * Description:
 *      - Processes numerical elements from an input file and stores them in a stack
 *        if they are even they are pushed. if the number is odd we pop the last even
 *        and lose the odd in the heap.
 * 
 * Public Methods:
 *      - ArrayStack()
 *      - ArrayStack(double full = 1.0, double empty = 0.2, double enlarge = 1.5, 
 *        double shrink= 0.5, string inputFile = "nums_test.dat")
 *      - bool Empty()
 *      - 
 *      -
 *      -
 *      -
 *      -
 * 
 * Usage: 
 *      - not for typical usage, done for academic purposes
 *      
 */
class ArrayStack{

private:
  int *A;                // pointer to array of int's
  int size;              // current max stack size
  int top;               // top of stack 
  int numResizes = 0;    // keeps track of total number of resizes
  int maxSize = 10;      // keeps track of the largest the stack got
  double tooFull, tooEmpty, growScale, shrinkScale; // the four command line params
  ifstream inputF;       // input file to be used in auto method below
  int evenNums, oddNums; // keeps track of pushes and pops seperately
  int totalCommands;     // keeps track of the total commands processed
  string inputFileN;     // keeps track of the name of the input file for later use


public:
 /**
  * ArrayStack
  * 
  * Description:
  *      Constructor no params
  * 
  * Params:
  *     - None
  * 
  * Returns:
  *     - NULL
  */
  ArrayStack(){
    size = 10;
    A = new int[size];
    top = -1;
    tooFull = 0.9;
    tooEmpty = 0.2;
    growScale = 1.5;
    shrinkScale = 0.5;
    totalCommands = 0; 
    evenNums = 0;
    oddNums = 0;
    numResizes = 0; 
    inputFileN = "";
  }


 /**
  * ArrayStack(double full, double empty, double enlarge, double shrink, string inputFile)
  * 
  * Description:
  *      The constructor ran primarily from the command line to load in input File
  *      directly into the class and allow the class to do the pushing and popping
  *      internally through the function pullInFile()
  * 
  * Params:
  *        1st: Too Full Threshold (where to enlarge it at)
  *        2nd: Too Empty Threshold (where to shrink it at)
  *        3rd: Enlarging Threshold (how much to enlarge it by)
  *        4th: Shrinking Threshold (how much to shrink it by)
  *        5th: File Name in string format
  * 
  * Returns:
  *     - NULL
  */
  ArrayStack(double full = 1.0, double empty = 0.2, double enlarge = 1.5, double shrink= 0.5, string inputFile = "nums_test.dat"){
    size = 10;
    A = new int[size];
    top = -1;
    tooFull = full;
    tooEmpty = empty;
    growScale = enlarge;
    shrinkScale = shrink;
    inputF.open(inputFile);
    totalCommands = 0; 
    evenNums = 0;
    oddNums = 0;
    numResizes = 0; 
    inputFileN = inputFile;
  }


 /**
  * Public bool: Empty
  * 
  * Description:
  *      Stack smaller than the intended shrink threshold?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = empty
  */
  bool Empty(){
    // if top/ size is less than or equal to the too empty threshold
    // return true
    double temp = (double)top/(double)size;
    return (temp <= tooEmpty);

  }
  

 /**
  * Public bool: Full
  * 
  * Description:
  *      Stack bigger than intended grow threshold?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = full
  */
  bool Full(){
    // if top/ size is greater than or equal to the too full threshold
    // return true
    double temp = (double)top/(double)size;
    return (temp >= tooFull);
  }


 /**
  * Public int: Peek
  * 
  * Description:
  *      Returns top value without altering the stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
  int Peek(){
    if(!Empty()){
      return A[top];
    }
    
    return -99; // some sentinel value
                // not a good solution
  }


 /**
  * Public int: Pop
  * 
  * Description:
  *      Returns top value and removes it from stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
  int Pop(){
    CheckResize();
    totalCommands++;
    oddNums++;
    return A[top--];
  }


 /**
  * Public void: Print
  * 
  * Description:
  *      Prints all statisitics about the pulling in of the numbers. 
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
  void PrintProcess(){
    cout<<"************************************************************\n"
        << "    Assignment 4: Resizing The Stack\n"
        << "    CMPS 3013\n"
        << "    Garrett Mathers\n\n\n"
        << "    File Processed: " << inputFileN << endl << endl
        << "    Config Params:\n"
        << "      Full Threshold: " << tooFull << endl
        << "      Shrink Threshold: " << tooEmpty << endl
        << "      Grow Ratio: " << growScale << endl
        << "      Shrink Ratio: " << shrinkScale << endl << endl
        << "    Processed " << totalCommands << " commands.\n\n"
        << "    Max Stack Size: " << maxSize << endl
        << "    End Stack Size: " << size << endl
        << "    Stack Resized: " << numResizes << endl
        << "    Total Even Numbers: " << evenNums << endl
        << "    Total Odd Numbers: " << oddNums << endl << endl
        << "************************************************************\n";
  } 


 /**
  * Public bool: Push
  * 
  * Description:
  *      Adds an item to top of stack
  * 
  * Params:
  *      [int] : item to be added
  * 
  * Returns:
  *      [bool] ; success = true
  */
  void Push(int x){
    CheckResize();  // begin by checking if resize is needed
    A[++top] = x;   //
    totalCommands++;
    evenNums++;
  }


  /**
  * void ContainerGrow()
  * 
  * Description:
  *      increase the size of the container by the grow ratio provided or the default
  * 
  * Params:
  *      N/A
  * 
  * Returns:
  *      N/A
  */
  void ContainerGrow(){

    int newSize = size * growScale; // new size is the old size * the growscale

    int *newArr = new int[newSize]; // initialize the new arr with the new size

    for(int i = 0; i < size; i++){  // process all the elements from the old array
      newArr[i] = A[i];             // into the new array until all elements are in 
    }
 
    delete [] A;                    // delete the old array

    if(newSize > size){             // if the newsize is greater than the old
      maxSize = newSize;            // make the newsize the new maxsize
    }

    size = newSize;                 // reinstate the size as the new size

    A = newArr;                     // reinstate A as the new array

    numResizes++;                   // increment the number of resizes
  }


  /**
  * void ContainerShrink()
  * 
  * Description:
  *      decreases the size of the container by the shrink ratio provided or the default
  * 
  * Params:
  *      N/A
  * 
  * Returns:
  *      N/A
  */
  void ContainerShrink(){
    
    int newSize = size * shrinkScale; // creating the new size off of threshold
    int *newArr = new int[newSize];   // initializing the new arr to hold newsize elements

    for(int i = 0; i < top; i++){     // add each element to the new arr
      newArr[i] = A[i];
    }

    delete [] A;                      // delete the old array

    size = newSize;                   // reinitialize size

    A = newArr;                       // reassigning the value of A to keep consistent
    
    numResizes++;                     // incrementing number of resizes
  }


  /**
  * void CheckResize()
  * 
  * Description:
  *      checking the capacity of the array to see if a ContainerShrink or 
  *      ContainerGrow is needed to keep the dynamic aspect intact for the class
  * 
  * Params:
  *      N/A
  * 
  * Returns:
  *      N/A
  */
  void CheckResize(){
    
    if(Full()){            // if the stack is too full
      ContainerGrow();     // make it bigger
    } else if(Empty() && size * shrinkScale >= 10){
        ContainerShrink(); // and if it's too empty
    }                      // make it smaller if the resulting size is greater than 10
  }

  void pullInNums(){
    int number; 

    while(!inputF.eof()){
      inputF >> number;
      
      if(number % 2 == 0){ // if number is even
        Push(number);      // push it 
      }else{               // if the number is odd
        Pop();             // pop the last added number off the array
      }

      number = 0;          // resetting number incase pop is ran and num is not used

    }
  }
};


void help(){
  cout << "Please use the guidelines below to specify the dynamic components of your stack.\n\n"
      << ">>PARAMS<<\n"
      << "1st: Too Full Threshold (where to enlarge it at)\n"
      << "2nd: Too Empty Threshold (where to shrink it at)\n"
      << "3rd: Enlarge Amount (how much to enlarge it by)\n"
      << "4th: Shrink Amount (how much to shrink it by)\n"
      << "5th: File Name ( the file to process numbers from )\n\n";
}



int main(int argc, char** argv) {

    double tooBig = 0.8;
    double tooSmall = 0.25;
    double growScale = 1.5;
    double shrinkScale = 0.5;
    string file = "nums_test.dat";



  if(argc==1){
    help();
  }else if(argc>1){
    //initialization of command line params
    tooBig = atof(argv[1]);
    tooSmall = atof(argv[2]);
    growScale = atof(argv[3]);
    shrinkScale = atof(argv[4]);
    file = string(argv[5]);

  
    
    //building of the stack
    ArrayStack stack(tooBig, tooSmall, growScale, shrinkScale, file);
    stack.pullInNums();
    stack.PrintProcess();
  }


   

  

  return 0; 

} 
