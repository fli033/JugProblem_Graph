#ifndef JUG_H
#define JUG_H
#include <string>
#include <iostream>
#include <queue>//used in bool search & void BuildGraph
#include <stack>//use in int solve
#include <vector>
#define SIZE_CHOICE_ARR 6

//CANNOT STACK PARENT POINTERS 3/9/19


using namespace std;

class Node{
    friend class Jug;
private:
    int a;
    int b;
    Node* fa;//fill a
    Node* fb;//fill b
    Node* ea;//empty a
    Node* eb;//empty b
    Node* pab;//pour a into b
    Node* pba;//pour b into a
    Node* parent;
    int index;
public:
    Node(int aVal, int bVal){//Node after_FA_Node = new Node(calculated_A_val, calculated_B_val);
        a = aVal;
        b = bVal;
        index = 0;
        fa = nullptr;
        fb = nullptr;
        ea = nullptr;
        eb = nullptr;
        pab = nullptr;
        pba = nullptr;
        parent = nullptr;
    }
};
class Jug {
    public:
        Jug(int, int, int);
        Jug(int,int,int,int,int,int,int,int,int);

        //solve is used to check input and find the solution if one exists
        //returns -1 if invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string &solution);//A solution is a sequence of steps that leaves jug A empty, and exactly N gallons in jug B
    private:
        int CapA;
        int CapB;
        int N;
        int cfA;
        int cfB;
        int ceA;
        int ceB;
        int cpAB;
        int cpBA;
        Node* root;
        Node* solutionNode;
        Node* secondSolution;
        vector<Node*> vecNodes;
        //string arr_choice[SIZE_CHOICE_ARR];

    private:
        void buildGraph();
        bool isProblemValid();//used in +solve function
        bool solutionExists();//check after built graph
        bool nodeIsSolution(Node*);//check after each node is made
        Node* getSolutionPosition(Node* excludeNode);
        bool search(Node*, Node* temp);//search in the graph for a node with same values. done before adding new node
        bool aEmpty(Node*);//Empty_A = NULL, Pour_A-B = NULL
        bool aFull(Node*);//Fill_A = NULL, Pour_B-A = NULL
        bool bEmpty(Node*);//Empty_B = NULL, Pour_B-A = NULL
        bool bFull(Node*);//Fill_B = NULL, Pour_B-A = NULL

        void TraverseGraph(Node*);//Breadth First Search starting at root
        Node* fillA(Node*);
        Node* fillB(Node*);
        Node* emptyA(Node*);
        Node* emptyB(Node*);
        Node* PourA_B(Node*);
        Node* PourB_A(Node*);
        string getMethodString(int num, Node* prev, Node* curr);
        int getMethodCost(Node* prev, Node* curr);
        //void checkWhichPtr_Using (Node*); USED FOR TEST
};

#endif // JUG_H
