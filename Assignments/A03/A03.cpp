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
*        creates a dynamic list that can be used to push integer values
*        into a dynamically sized linked list that can push, pop, insert etc.
*
*
*  Usage:
*        use to be able to easily store integer values dynamically
*        and effeciently
* 
*  Files:            N/A
*****************************************************************************/

#include <iostream>

using namespace std;



/**
 * Node
 * 
 * Description:
 *      This struct constructs nodes that hold integer values within them
 *      and that link to other nodes using the next pointer
 * 
 * Public Methods:
 *                          Node()                        
 *                          Node(int n)
 * 
 * Usage: 
 * 
 *      Node() - constructs a new node with default value -1
 *      Node(int n) - constructs a new node with int value n 
 *      
 */

struct Node {
    int x;      // integer value associated with it
    Node *next; // the "link"
    Node() {
        x = -1;
        next = NULL;
    }
    Node(int n) {
        x = n;
        next = NULL;
    }
};


/**
 * List
 * 
 * Description:
 *      This class contains various methods to dynamically build a list
 *      of nodes that hold integer values and are singly linked
 * 
 * Public Methods:
 *                          List()                             
 *      void                Push(int val)
 *      void                Insert(int val)
 *      void                PrintTail()
 *      string              Print()
 *      int                 Pop()
 * 
 * Overloaded Operators:
 *      List operator+(const List &Rhs)     +
 *      int operator[](int index)           []
 *      friend ostream &operator<<(ostream &os, List L)    <<
 *      
 * Usage: 
 * 
 *      List() - default constructor to initialize values
 *      .Push(int val) - pushes an integer onto the back of the list
 *      .Insert(int val) - pushes an integer onto the front of the list
 *      .PrintTail() - prints the last node of the list's integer value
 *      .Print() - prints out the entire list
 *      .Pop() - not implemented
 *      +  - adds all the nodes of one list to the end of another
 *      [] - place the desired index inside of the square brackets
 *      << - allows usage of cout
 */

class List {
private:
    Node *Head;  // first value of the list
    Node *Tail;  // last value of the list
    int Size;    // the current number of nodes in the list

public:
    /**
     * Public : List()
     * 
     * Description:
     *      initializes a new list with default values
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      N/A
     */
    List() {
        Head = Tail = NULL;
        Size = 0;
    }
    

    /**
     * Public : void Push(int val)
     * 
     * Description:
     *      adds a node to the back of list with the int value = val
     * 
     * Params:
     *      [int]     :  val - integer to be added to list
     * 
     * Returns:
     *      N/A
     */
    void Push(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // If the list is empty, initialize the node as head and tail
        // otherwise push it on the back
        if (!Head && !Tail) {
            Head = Tail = Temp;
        } else {
            Tail->next = Temp;
            Tail = Temp;
        }
        // incrementing size
        Size++;
    }


    /**
     * Public : void Insert(int val)
     * 
     * Description:
     *      adds a node to the front of list with the int value = val
     * 
     * Params:
     *      [int]     :  val - integer to be added to list
     * 
     * Returns:
     *      N/A
     */
    void Insert(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // adds the value to the front of the list

        Temp->next = Head;
        Head = Temp;
        if (!Tail) {
            Tail = Head;
        }
        Size++;
    }


    /**
     * Public : void PrintTail()
     * 
     * Description:
     *      prints out the last element in the list
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      N/A
     */
    void PrintTail() {
        cout << Tail->x << endl;
    }


    /**
     * Public : string Print()
     * 
     * Description:
     *      prints the entirety of the list neatly
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      N/A
     */
    string Print() {
        Node *Temp = Head;
        string list;

        //while temp exists print out each value seperated by an arrow
        while (Temp != NULL) {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }


    // not implemented
    int Pop() {
        Size--;
        return 0; //
    }


    /**
     * Public : List operator+(const List &Rhs)
     * 
     * Description:
     *      overloaded + operator to be able to combine lists together
     * 
     * Params:
     *      must be two lists being added together
     * 
     * Returns:
     *      a new list that contains all the elements of the two added together
     */
    List operator+(const List &Rhs) {
        // Create a new list that will contain both when done
        List NewList;

        // Get a reference to beginning of local list
        Node *Temp = Head;

        // Loop through local list and Push values onto new list
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Get a reference to head of Rhs
        Temp = Rhs.Head;

        // Same as above, loop and push
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Return new concatenated version of lists
        return NewList;
    }

    /**
     * Public : int operator[](int index)
     * 
     * Description:
     *      overloaded the [] brackets to be able to access indexes more easily
     * 
     * Params:
     *      the desired values index
     * 
     * Returns:
     *      the integer associated with that index
     */
    int operator[](int index) {
        Node *Temp = Head;

        //if the index does not exist, exit and print error
        //otherwise find the value of that index and return it
        if (index >= Size) {
            cout << "Index out of bounds, exiting";
            exit(0);
        } else {

            for (int i = 0; i < index; i++) {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }


    /**
     * Public : friend ostream &operator<<(ostream &os, List L)
     * 
     * Description:
     *      overloaded the << operator to be able to use cout to print
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      the entirety of the list 
     */
    friend ostream &operator<<(ostream &os, List L) {
        os << L.Print(); //runs print method whenever list is used in ostream
        return os;
    }
};

int main(int argc, char **argv) {
    List L1;
    List L2;

    //push numbers 0-24 onto L1
    for (int i = 0; i < 25; i++) {
        L1.Push(i);
    }

    //pushes numbers 50-99 onto L2
    for (int i = 50; i < 100; i++) {
        L2.Push(i);
    }

    //printing the last value of both lists
    L1.PrintTail();
    L2.PrintTail();

    //adding both lists together and then printing the result
    List L3 = L1 + L2;
    cout << L3 << endl;

    //print the 6th value of L3
    cout << L3[5] << endl;
    return 0;
}
