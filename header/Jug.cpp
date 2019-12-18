#include "Jug.h"
#include "iomanip"
#include <vector>

Jug::Jug(int Ca, int Cb, int N) {
    this->CapA = Ca;
    this->CapB = Cb;
    this->N = N;
    this->cfA = 1;
    this->cfB = 1;
    this->ceA = 1;
    this->ceB = 1;
    this->cpAB = 1;
    this->cpBA = 1;
    root = nullptr;
    solutionNode = nullptr;
}
Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) {
    this->CapA = Ca;
    this->CapB = Cb;
    this->N = N;
    this->cfA = cfA;
    this->cfB = cfB;
    this->ceA = ceA;
    this->ceB = ceB;
    this->cpAB = cpAB;
    this->cpBA = cpBA;
    root = nullptr;
    solutionNode = nullptr;
}

int Jug::solve(string &solution) {//USE STACK TO TRACE THE STEPS, solutionNode->par
    solution = "";
    if (!isProblemValid()) return -1;
    buildGraph();
    if (solutionNode == nullptr) return 0;
    //ELSE
    int costCount1 = 0;
    int costCount2 = 0;
    int cost1_counter = 0;
    int cost2_counter = 0;
    string method1 = "";
    string method2 = "";
    Node *prev = nullptr;
    Node *next = nullptr;
    Node *cur = nullptr;
    stack<Node *> stackNode;
    cur = solutionNode;

    while (cur != nullptr) {
        stackNode.push(cur);
        cur = cur->parent;
    }
    while (stackNode.size() > 1) {
        cost1_counter++;
        prev = stackNode.top();
        stackNode.pop();
        next = stackNode.top();
        costCount1 += getMethodCost(prev, next);
        method1 = method1 + to_string(cost1_counter) + ". "
                + getMethodString(cost1_counter, prev, next);
    }

    stackNode.pop();//pop last element in stack

    cur = secondSolution;
    while (cur != nullptr) {
        stackNode.push(cur);
        cur = cur->parent;
    }
    while (stackNode.size() > 1) {
        cost2_counter++;
        prev = stackNode.top();
        stackNode.pop();
        next = stackNode.top();
        costCount2 += getMethodCost(prev, next);
        method2 = method2 + to_string(cost2_counter) + ". "
                + getMethodString(cost2_counter, prev, next);
    }

    string msg_succ = "SUCCESS         ";
    string cost_str = "";
    solution = "\n" + msg_succ;

    if (costCount1 < costCount2) {
        solution = method1 + solution + "COST: "
                 + to_string(costCount1);
    } else {
        solution = method2 + solution + "COST: "
                 + to_string(costCount2);
    }
    return 1;
}

//FOLLOWING ARE PRIVATE MEMBERS TO BUILD TREE
void Jug::buildGraph() {//NO SOLUTION MEANS THAT EVENTUALLY ALL NEW NODES WILL BE REPEATS, SOLVE RETURN 0
    //cout << "start buildGraph" << endl;
    int c = 0;
    Node *rootNode = new Node(0, 0);

    root = rootNode;
    Node *cur = nullptr;
    string command = "";
    queue<Node *> queuebuild;
    queuebuild.push(root);
    while (!queuebuild.empty()) {
        cur = queuebuild.front();
        cur->index = c;
        //cout << "current state: " << cur->a << ", " << cur->b  << endl;
        //cout << "current index: " << cur->index  << endl << endl;
        if (nodeIsSolution(cur) && getSolutionPosition(cur) == nullptr) {
            solutionNode = cur;
        }//CUR IS THE FIRST SOLUTION WHEN BUIDLING
        else if (nodeIsSolution(cur) && getSolutionPosition(cur) != nullptr) {
            secondSolution = cur;
        }
        cur->fa = fillA(cur);
        cur->fb = fillB(cur);
        cur->ea = emptyA(cur);
        cur->eb = emptyB(cur);
        cur->pab = PourA_B(cur);
        cur->pba = PourB_A(cur);

        if (aFull(cur)) {
            cur->fa = nullptr;
            cur->pba = nullptr;
        }
        if (bFull(cur)) {
            cur->fb = nullptr;
            cur->pab = nullptr;
        }
        if (aEmpty(cur)) {
            cur->ea = nullptr;
            cur->pab = nullptr;
        }
        if (bEmpty(cur)) {
            cur->eb = nullptr;
            cur->pba = nullptr;
        }
        if (search(root, cur) || nodeIsSolution(cur)) {//FIXME
            cur->fa = nullptr;
            cur->fb = nullptr;
            cur->ea = nullptr;
            cur->eb = nullptr;
            cur->pab = nullptr;
            cur->pba = nullptr;

        }
        //checkWhichPtr_Using(cur);
        if (cur->fa != nullptr) { queuebuild.push(cur->fa); }// cout << "push cur->fa" << endl;}
        if (cur->fb != nullptr) { queuebuild.push(cur->fb); }// cout << "push cur->fb" << endl;}
        if (cur->ea != nullptr) { queuebuild.push(cur->ea); }// cout << "push cur->ea" << endl;}
        if (cur->eb != nullptr) { queuebuild.push(cur->eb); }// cout << "push cur->eb" << endl;}
        if (cur->pab != nullptr) { queuebuild.push(cur->pab); }// cout << "push cur->pab" << endl;}
        if (cur->pba != nullptr) { queuebuild.push(cur->pba); }// cout << "push cur->pba" << endl;}
        vecNodes.push_back(cur);
        queuebuild.pop();
        c++;
    }
}

bool Jug::isProblemValid() {
    //VALID IF 0 < Ca ≤ Cb and N ≤ Cb ≤ 1000
    //cout << "start isProblemValid" << endl;
    bool valid = false;
    if (CapA > 0 && CapA <= CapB && N <= CapB && CapB <= 1000) {
        valid = true;
    }
    //cout << "end isProblemValid" << endl;
    return valid;
}//used in +solve function. CHECK PRE CONDITIONS. IF INVALID, SOLVE RETURNS -1
bool Jug::nodeIsSolution(Node *n) {
    // cout << "n->a: " << n->a << endl;
    // cout << "n->b: " << n->b << endl;

    /*
    if (n->a == 0 && n->b == N) {
        return true;
    }
    return false;
     */

    return (n->a == this->N || n->b == this->N);

}//check after each node is made

Node *Jug::getSolutionPosition(Node *excludeNode) {
    if (solutionNode == nullptr) {
        return nullptr;
    }
    queue<Node *> myQ;
    Node *cur = nullptr;

    myQ.push(root);
    while (!myQ.empty()) {
        cur = myQ.front();
        if (cur == excludeNode) {}
        else {
            /*
            if (cur->a == 0 && cur->b == N){
                return cur;
            }
             */
            if (cur->a == this->N || cur->b == this->N) {
                return cur;
            }
        }
        if (cur->fa != nullptr) myQ.push(cur->fa);
        if (cur->fb != nullptr) myQ.push(cur->fb);
        if (cur->ea != nullptr) myQ.push(cur->ea);
        if (cur->eb != nullptr) myQ.push(cur->eb);
        if (cur->pab != nullptr) myQ.push(cur->pab);
        if (cur->pba != nullptr) myQ.push(cur->pba);

        myQ.pop();
    }
    return nullptr;
}

bool Jug::solutionExists() {
    if (solutionNode != nullptr) return true;
    else return false;
}//check after built graph

bool Jug::search(Node *rootNode, Node *excludeNode) {
    int limit = excludeNode->index;
    if (excludeNode == root) {
        return false;
    }
    for (int i = 0; i < limit - 1; i++) {
        if (vecNodes.at(i)->a == excludeNode->a && vecNodes.at(i)->b == excludeNode->b) {
            return true;
        }
    }
    return false;
}//IF NODE EXISTS, THEN ALL PTRS OF THE NEW NODE IS NULL

bool Jug::aEmpty(Node *n) {
    return (n->a == 0);
}//Empty_A = NULL, Pour_A-B = NULL
bool Jug::aFull(Node *n) {
    return (n->a == CapA);
}//Fill_A = NULL, Pour_B-A = NULL
bool Jug::bEmpty(Node *n) {
    return (n->b == 0);
}//Empty_B = NULL, Pour_B-A = NULL
bool Jug::bFull(Node *n) {
    return (n->b == CapB);
}//Fill_B = NULL, Pour_B-A = NULL

Node *Jug::fillA(Node *n) {//PARENT OF THE NEW PTS IS SET TO N
    Node *faNode = new Node(n->a, n->b);
    faNode->a = CapA;
    faNode->parent = n;
    return faNode;
}

Node *Jug::fillB(Node *n) {
    Node *fbNode = new Node(n->a, n->b);
    fbNode->b = CapB;
    fbNode->parent = n;
    return fbNode;
}

Node *Jug::emptyA(Node *n) {
    Node *eaNode = new Node(n->a, n->b);
    eaNode->a = 0;
    eaNode->parent = n;
    return eaNode;
}

Node *Jug::emptyB(Node *n) {
    Node *ebNode = new Node(n->a, n->b);
    ebNode->b = 0;
    ebNode->parent = n;
    return ebNode;
}

Node *Jug::PourA_B(Node *n) {
    Node *pabNode = new Node(n->a, n->b);
    int space_left_B = CapB - n->b;
    if (space_left_B >= n->a) {
        pabNode->a = 0;
        pabNode->b += n->a;
    }//A can be all poured into B
    else {//A CAN BE ALL POURED OUT TO B
        int amount_left_A = n->a - space_left_B;
        pabNode->a = amount_left_A;
        pabNode->b = CapB;
    }//A have some remain after filling B up
    pabNode->parent = n;
    return pabNode;
}

Node *Jug::PourB_A(Node *n) {
    Node *pbaNode = new Node(n->a, n->b);
    int space_in_A = CapA - pbaNode->a;
    if (pbaNode->b <= space_in_A) {
        pbaNode->a += pbaNode->b;
        pbaNode->b = 0;
    } else {
        pbaNode->b -= space_in_A;
        pbaNode->a = CapA;
    }
    pbaNode->parent = n;
    return pbaNode;
}

/*
 * separate helper for getMethodString
 */
void fillBlank(string& str, int length, bool isStep) {
    string space = "";
    int spaceLength = length - str.length();
    if (isStep) spaceLength = 5;
    for (int i = 0; i < spaceLength; i++) {
        space += " ";
    }
    str += space;
    return;
}

string Jug::getMethodString(int num, Node *prev, Node *curr) {
    string command = "";
    string step = "";
    string cost = "";

    if (num < 10) step += " ";
    if (num < 100) step += "  ";

    if (curr == prev->fa) {
        step += "FILL    A";
        cost = to_string(this->cfA);
    }
    if (curr == prev->fb) {
        step += "FILL    B";
        cost += to_string(this->cfB);
    }
    if (curr == prev->ea) {
        step += "EMPTY   A";
        cost = to_string(this->ceA);
    }
    if (curr == prev->eb) {
        step += "EMPTY   B";
        cost = to_string(this->ceB);
    }
    if (curr == prev->pab) {
        step += "POUR A->B";
        cost = to_string(this->cpAB);
    }
    if (curr == prev->pba) {
        step += "POUR B->A";
        cost = to_string(this->cpBA);
    }
    fillBlank(step, 20, true);
    fillBlank(cost, 10, false);

    command = step + cost + "(" + to_string(curr->a) + ", " + to_string(curr->b) + ")\n";
    return command;
}

int Jug::getMethodCost(Node *prev, Node *curr) {
    int cost = 0;
    if (curr == prev->fa) cost = cfA;
    if (curr == prev->fb) cost = cfB;
    if (curr == prev->ea) cost = ceA;
    if (curr == prev->eb) cost = ceB;
    if (curr == prev->pab) cost = cpAB;
    if (curr == prev->pba) cost = cpBA;
    return cost;
}

/*
void Jug::checkWhichPtr_Using(Node* cur){
    //cout << "------------------" << endl;
    //cout << "current Node has: " << endl;
    if (cur->fa != nullptr) cout << " fa, (" << cur->fa->a << ", " << cur->fa->b << ")" << endl;
    if (cur->fb != nullptr) cout << " fb, (" << cur->fb->a << ", " << cur->fb->b << ")" << endl;
    if (cur->ea != nullptr) cout << " ea, (" << cur->ea->a << ", " << cur->ea->b << ")" << endl;
    if (cur->eb != nullptr) cout << " eb, (" << cur->eb->a << ", " << cur->eb->b << ")" << endl;
    if (cur->pab != nullptr) cout << " pab, (" << cur->pab->a << ", " << cur->pab->b << ")" << endl;
    if (cur->pba != nullptr) cout << " pba, (" << cur->pba->a << ", " << cur->pba->b << ")" << endl;
    //cout << "------------------" << endl << endl;
}
*/
