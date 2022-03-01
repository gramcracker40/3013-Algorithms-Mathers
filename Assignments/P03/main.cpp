/*****************************************************************************
*                    
*  Author:           Garrett Mathers
*  Email:            garrett.mathers@gmail.com
*  Label:            Dictionary Lookup Example Of Trie Da
*  Title:            Program 3 - Processing in Trie Tree Time
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
 * TrieNode
 * 
 * Description:
 *      The nodes that the Trie class uses to process the data pulled in. 
 * 
 * Public Methods:
 *      - TrieNode() creates a new TrieNode and initializes all children to null
 * 
 * Usage: 
 * 
 *      - Used as the data for the Trie class. 
 */
struct TrieNode{
  bool isWord;                   // set to false by default
  TrieNode* children[26];        // set of children of the node

  TrieNode(){
    isWord = false;              // set to false initially but can change
    for(int i =0; i < 26; i++){  // initialize all to null
      children[i] = nullptr;     
    }
  }

};


 /**CLASS:
 *
 * Trie
 * 
 * Description:
 *      This class allows for log(n) lookup times and in some cases even faster
 *      among a tree of listed out 'characters' or TrieNode's that link together
 *      as children of eachother to let us go directly to the spot where the prefix
 *      ends. The fewer matches, the faster the program gets. 
 * 
 * Public Methods:
 *      - Trie()  default constructor to initialize an object of this class. 
 *      - void insert(string word) - inserts a string into the tree of TrieNode's
 *      - void loadInInputFile(string inputF)  - loads in an input file of strings directly to the tree
 *      - TrieNode* findMatches(string word) - pass through a string and it will print all the words 
 *           with matching prefixes in the tree
 *      - void findWords(TrieNode* start, string const& currStr) - recursive function that searches the tree
 *      - void printMatches() - simply prints out all the matches from the vector
 * 
 * Usage: 
 * 
 *      - programming for a fast effective lookup speed on a huge Trie
 *        of strings pushed with a string or using the LoadInInputFile() method. 
 */
class Trie{
  private:
    TrieNode* root;              // dummy value that is the start of the trie
    ifstream input;              // the input file passed through to loadInInputFile()
    vector<string> matches;      // vector of all the matches, refreshed each iteration call
    Timer T;                     // the timer that times the time it takes to find matches
public:
    /**
     * Constructor : Trie(){
     * 
     * Description:
     *      - default constructor, intializing key values
    */
    Trie(){
      root = new TrieNode();     // initializing the root to a dummy TrieNode
    }


    /**
     * Method : void insert(string word)
     * 
     * Description:
     *      -  insert a specific string stemming from the root of the class
     * 
     * Parameters: 
     *      - [string] word: the value of the string you desire to insert. 
     *
     * Usage: 
     *      - inserting words into the trie to be processed on a trie look up speed 
    */
    void insert(string word){
      TrieNode* curr = root;     // initializing an iterative node
      
      for(int i = 0; i < word.length(); i++){              // loop through the word char by char
        int index = word[i] - 'a'; 
        if (curr->children[index] == nullptr){             // if the path doesn't exist
          curr->children[index] = new TrieNode();          // add the character to the path
        }
        curr = curr->children[index];                      // move to the next trie node in children
      }
      curr->isWord = true;                                 // since we know this is the last letter added isWord is now true
    }


    /**
     * Method : void loadInInputFile(string inputF)
     * 
     * Description:
     *      - insert all strings from an input file 
     * 
     * Parameters: 
     *      - [string] inputF: the file name
     *
     * Usage: 
     *      - load in an entire input file into a Trie data structure
    */
    void loadInInputFile(string inputF){
      input.open(inputF);   // opening the input file
      string word;          // declaring the placeholder value for passing through strings

      T.Start();            // starting the timer to see how fast the input file is loaded in 
      while(!input.eof()){  // while the file is not empty
        input >> word;      // pull in the word
        insert(word);       // insert the word (line by line)
      }
      T.End();              // stop the timer

      //printing terminal message on how fast the input file was pulled in 
      cout << "It took "
           << termcolor::green << T.MilliSeconds() << termcolor::reset << termcolor::red 
           << " milliseconds "<< termcolor::reset 
           << "to load in all the words from the english dictionary...\n"; 
      ///////////////////////////////////
      
      input.close(); // close the input file
    }


    /**
     * Method : TrieNode* findMatches(string word)
     * 
     * Description:
     *      - insert a string into the find matches function and it will print off
     *          a list of words that match the prefix passed through
     * 
     * Parameters: 
     *      - [string] word: the word or prefix to be searched
     *
     * Usage: 
     *      - use to see if a certain string exists within the trie structure 
    */
    TrieNode* findMatches(string word){
      TrieNode* curr = root;  
      cout << "Word being searched: " << word << endl; 

      for(int i = 0; i < word.length(); i++){  // iterate to the prefix in the tree
        if(!curr->children[word[i] - 'a']){    // if the path doesn't exist
          return NULL;                         // simply return (nothing)
        }else{                                 // if it does
          curr = curr->children[word[i] - 'a'];// iterate through further
        }                                     
      }
      if(curr == nullptr){      // if tree is empty
        return NULL;            // return NULL, will tell us if empty
      }

      T.Start();             // timer to see how fast the recursion runs
      findWords(curr, word); // start the recursion where curr ended after its iterations
      T.End();
      
      printMatches(); 
      cout << termcolor::blue << " -> " << T.Seconds() << termcolor::reset 
            << ", "<< termcolor::red << "seconds"<< termcolor::reset << " to find " 
            << termcolor::red << matches.size() << termcolor::reset<< " results" 
            << termcolor::reset << endl << endl;
        ///////////////////////////
      
      matches.clear();  // clearing the vector to allow it to identify new matches each keystroke
      return curr;      // tells us if there's no matches
    }


    /**
     * Method : void findWords(TrieNode* start, string const& currStr)
     * 
     * Description:
     *      - recursive function that is able to start at the trie node passed
     *         through the parameter set and recursively find all words that stem
     *         from it. 
     * 
     * Parameters: 
     *      - [TrieNode*] start: the node passed through from findMatches that the
     *           recursive function should start from the find the words
     *
     * Usage: 
     *      - used in coordination with findMatches to make using the class super easy 
    */
    void findWords(TrieNode* start, string const& currStr){
      
      if(start->isWord){            // if the current TrieNode is a word
        matches.push_back(currStr); // push the current string prefix into matches
      }
      for(int i = 0; i < 26; i++){  // loop through each potential child 
        char c = 'a' + i;           // c = the position in the loop + 'a' (2 + 'a' = 'c')
        if(start->children[i]){     // if the child exists
          findWords(start->children[i], currStr + c); // run the recursion with the child
          // and c added onto the current prefix. this will iterate each TrieNode* underneath start
        }
      }
    }


     /**
     * Method : void printMatches()
     * 
     * Description:
     *      - prints out a vector of strings stored within the class object
     * 
     * Usage: 
     *      - prints out the contents of the matches stored and found.  
    */
    void printMatches(){
      if(matches.size() < 10){ // if the size is less than 10 run a loop on each element
        for(int i = 0; i < matches.size(); i++){
          cout << matches[i];
          if(i != 9)  
            cout << "->";
        }
      }else{                   // if the size if over 10 just run print the first 10 items
        for(int i = 0; i < 10; i++){
          cout << matches[i]; 
          if(i != 9)
            cout << "->"; 
        }
      }   
    }
};

int main(){
  Trie Data;        // primary object
  string word = ""; // the string that is built with 'k'
  char k;           // what getch holds the keystroke within
  TrieNode* ret;    // what we hold our findMatches() within
  
  // simple introduction message to tell what the program does and is for
  cout << "This program shows the speed of loading in the entire english dictionary with a Trie data structure, \n"
      << "and then using log(n) time to search through it with the findWords() method. (Type 'Z' to terminate the program)\n\n";

  // loads in the entire english dictionary from dictionairy.txt
  Data.loadInInputFile("dictionary.txt");

  //runs until 'Z' is typed - processes each character entered into the terminal. 
  while ((k = getch()) != 'Z') {

    // 127 is backspace so if its hit this will take one char off of word
    if ((int)k == 127) {
        if (word.size() > 0) {
          word = word.substr(0, word.size() - 1);
          cout << word << endl;
          ret = Data.findMatches(word);
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
        ret = Data.findMatches(word); // find the concatinated word
    } 
  // if no TrieNode is returned then print out the message
  if(!ret)
    cout << "No Matches!!!!! please 'back up'" << endl; 
  }
}
