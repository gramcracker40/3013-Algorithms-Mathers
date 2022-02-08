/*****************************************************************************
*                    
*  Author:           Garrett Mathers
*  Email:            garrett.mathers@gmail.com
*  Label:            Dictionary Lookup Example
*  Title:            LinkedWordNodes
*  Course:           Advanced Algorithms
*  Semester:         Spring Semester // 2022
* 
*  Description:
*        Create a class called LinkedWordNodes that holds a double linked
*        list of wordNode's that hold strings as their data. 
*
*
* Usage:
*        The class and struct have detailed usage in their description and
*        usage. Load in a ton of words from an input file and be able to
*        search through them easily.
* 
*  Files:         
*        getch.hpp
*        termcolor.hpp
*        timer.hpp
*        dictionary.txt
*****************************************************************************/
#include <iostream>
#include "getch.hpp"
#include "timer.hpp"
#include "termcolor.hpp"
#include <string>
#include <fstream>
#include <vector>
using namespace std;


/**STRUCT:
 *
 * wordNode
 * 
 * Description:
 *      The nodes that the class uses to process the data pulled in. 
 * 
 * Public Methods:
 *      - wordNode(string chars, wordNode* nextInList, wordNode* prevInList)
 *      - wordNode(string chars)
 *
 * Overloaded Methods:
 *      - friend ostream& operator<<(ostream& cout, const wordNode &printable)
 * 
 * Usage: 
 * 
 *      - Used as the data for the LinkedWordNodes class. 
 */
struct wordNode{
  string word;    // the word that the node is holding

  wordNode* next; // the next element in the list
  wordNode* prev; // the previous element in the list

  //for initializing a new linked node easily
  wordNode(string chars, wordNode* nextInList, wordNode* prevInList){
    word = chars;
    next = nextInList;
    prev = prevInList; 
  }

  //for initializing new unlinked temporary wordNodes
  wordNode(string chars){
    word = chars;
    next = NULL;
    prev = NULL; 
  }

  //overloaded the ostream to come in handy later
  friend ostream& operator<<(ostream& cout, const wordNode &printable){
    cout << printable.word; 

    return cout; 
  }

};


 /**CLASS:
 *
 * LinkedWordNodes
 * 
 * Description:
 *      This class can initialize a double linked list with an input file
 *      of strings and perform lookup operations with string comparason programming
 *      classic push function for this edition of the program and a simple constructor
 *      for a super self explanitory setup. 
 * 
 * Public Methods:
 *      - LinkedWordNodes()
 *      - void push(string value)
 *      - void pullInWords(string infileName)
 *      - void print()
 *      - void findWords(string wordToFind)
 * 
 * Usage: 
 * 
 *      - programming for a fast effective lookup speed on a huge linked list
 *        of strings pushed with a string or using the pullInWords() method. 
 */
class LinkedWordNodes{
  private:
    wordNode *head;   // the front of the list
    wordNode *tail;   // the back of the list
    int totalWords;   // the total number of words
    ifstream infile;  // initializing the input file 
    Timer T;          // initializing the timer
  public:
    /**
     * Constructor : LinkedWordNodes(){
     * 
     * Description:
     *      - initializes key values of the class 
     *      - use in coordination with other methods to perform key class utilities
    */
    LinkedWordNodes(){
      head = NULL;
      totalWords = 0;
    }


     /**
     * Method : void push(string value)
     * 
     * Description:
     *      -  the push function that adds on items to the front of the list
     *         in a double linked fashion
     * 
     * Parameters: 
     *      - [string] value: the value of the string you desire to push. 
     *
     * Usage: 
     *      - push words into a doubly linked list for future searching algorithms 
     */
    void push(string value){ 
      
      if(!head){                             // if head doesnt exist
        head = tail = new wordNode(value);   // initialize head to a new node with the value
        totalWords++;                        // increment the total words
      }
      else{
        wordNode *temp = new wordNode(value);// initialize a new node with the value
        temp->next = head;                   // put the node infront of head
        head->prev = temp;                   // make heads previous = temp
        head = temp;                         // set the new node to head
        totalWords++;                        // increment total words
      }

    }


     /**
     * Method : void pullInWords(string infileName)
     * 
     * Description:
     *      -  pulls in individual words from an input file and stores them in a double
     *         linked list
     * 
     * Parameters: 
     *      - [string] infileName : the name of the input file with all the words to put 
     *        in the list
     *
     * Usage: 
     *      - pull in massive amounts of words at one time from an input file and stores
     *        them in a double linked list. 
     */
    void pullInWords(string infileName){
      string data; 
      infile.open(infileName); 

      T.Start();        // starting the stopwatch to time how long it takes

      while(!infile.eof()){
        infile >> data; // grab the data
        push(data);     // push the data
      }

      T.End();          // stopping stopwatch
      
      //printing terminal message on data
      cout << "It took "
           << termcolor::green << T.MilliSeconds() << termcolor::reset << termcolor::red 
           << " milliseconds "<< termcolor::reset 
           << "to load in all the words from the english dictionary...\n"; 
      ///////////////////////////////////

      infile.close();   // close the file
    }


     /**
     * Method : void print()
     * 
     * Description:
     *      -  prints out the entire passed in input file
     *
     * Usage: 
     *      - use it to test that the input file was actually loaded in 
     */
    void print(){
      wordNode *temp = head;   // create a temp node that starts at head

      while(temp){             // while temp is not NULL
        cout << *temp << endl; // print the word to the terminal
        temp = temp->next;     // set temp to the next node
      }
      cout << totalWords;      // print out the total words
    }


     /**
     * Method : void findWords(string wordToFind)
     * 
     * Description:
     *      -  prints out a list of the words with matching prefixes to the word 
     *         passes through by the user
     * 
     * Parameters: 
     *      - [string] wordToFind : the string the user wants to check for similar prefixes
     *
     * Usage: 
     *      - use it to be able to find different words that match with the string passed
     */
    void findWords(string wordToFind){

      cout<<wordToFind<<endl;       // print the string being looked up
      wordNode *temp = head;        // set the temporary node = head 
      vector<string> matchingPrefix;// create a vector of strings that have matching prefixes to the word entered
      int count = 0;                // initialize the count 

      T.Start();                    // start the clock
      
      while(temp){                  // while temp is not null
        count = 0;                  // count is 0 (reset)
        
        for(int j = 0; j < wordToFind.size(); j++){ // run as many times as # of character of word passed through   
          if(temp->word[j] == wordToFind[j]){       // if character j equals wordToFind j 
            count++;                                // increment the count by 1
          }
        }
        if(count == wordToFind.size()){             // if the count is equal to the size of the word to find
          matchingPrefix.push_back(temp->word);     // they have matching prefixes and push the word onto matchingPrefix
        }
        
        temp = temp->next;                          // set the temp node to the next node in the list  
      }
      
      T.End();                                      // stop the clock

      
      if(matchingPrefix.size() < 10){                   // if the size is less than 10 
        
        for(int i = 0; i < matchingPrefix.size(); i++){ // runs based on size since size is lower than 10
          cout << matchingPrefix[i] << "  ";            // prints out however many matches there were
        }
        //printing terminal message - displays time taken in colored words to find all the words
        cout << termcolor::blue << " -> " << T.Seconds() << termcolor::reset 
            << ", "<< termcolor::red << "seconds"<< termcolor::reset << " to find " 
            << termcolor::red << matchingPrefix.size() << termcolor::reset<< " results" 
            << termcolor::reset << endl;
        ///////////////////////////
      }else{                                 // if the size is over 10
        for(int i = 0; i < 10; i++){         // run the loop ten times
          cout << matchingPrefix[i] << "  "; // print out the first ten of the matching words
        }
        //printing terminal message
        cout << termcolor::blue << " -> " << T.Seconds() << termcolor::reset 
            << ", "<< termcolor::red << "seconds"<< termcolor::reset << " to find " 
            << termcolor::red << matchingPrefix.size() << termcolor::reset<< " results" 
            << termcolor::reset << endl;
        ///////////////////////////
      }
    }
};






int main() {
  char k;
  string word = "";
  LinkedWordNodes list;
  
  cout << "This program shows the speed of loading in the entire english dictionary with a singly linked list, \n"
      << "and then using constant time to search through it with the findWords() method. (Type 'Z' to terminate the program)\n\n";

  
  list.pullInWords("dictionary.txt"); // pull in the words from the dictionary

  //runs until 'Z' is typed - processes each character entered into the terminal. 
  while ((k = getch()) != 'Z') {

    // 127 is backspace so if its hit this will take one char off of word
    if ((int)k == 127) {
        if (word.size() > 0) {
            word = word.substr(0, word.size() - 1);
        }
    } else {
        //checks for a letter
        if (!isalpha(k)) {
            cout << "Please only type letters" << endl;
            continue;
        }
        //now check to see if the letter is lowercased, if not turn it to upper case
        if ((int)k < 97) {
            k += 32;
        }
        word += k; // append char to word
    }
  
  list.findWords(word); // find the concatinated word
  
  }

  
  
  cout << "Signal Terminated: Run again to use...\n";

  return 0;


 

}
