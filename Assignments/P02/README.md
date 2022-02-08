## P02 - LinkedWordNodes
### Garrett Mathers
### Description:

Uses a double linked list to link a large number of "wordNodes"
that contain actual strings passed in through an input file of
words seperated by spaces or lines. It then uses a string comparison
method to look up all potential matches from the list of words passed
through from the input file. It will give time on how fast they are 
processed and how many matches each prefix passed through has in the
english language.

### Files

|   #   | File     | Description                      |
| :---: | -------- | -------------------------------- |
|   1   | [main.cpp](main.cpp) | The cpp file associated . |
|   2   | [getch.hpp](getch.hpp) | a hpp file associated . |
|   3   | [termcolor.hpp]([termcolor.hpp) | a hpp file associated . |
|   4   | [timer.hpp](timer.hpp) | a hpp file associated . |
|   5   | [dictionary.txt](dictionary.txt) | The txt file associated . |

### Instructions

- All non standard libraries are listed in the top of the cpp file
- Start on main and read the description at the top, it will get you going

### Example Command

- LinkedWordNodes listOfWords; 
- listOfWords.pullInWords(string inputFileName)
- listOfWords.findWords(string wordToFind) - find the matches to the string passed through
