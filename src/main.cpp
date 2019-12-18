#include <iostream>
#include <iomanip>
#include "../header/Jug.h"

using namespace std;

Jug* setJugStats();

int main() {
    //FIX BUILD GRAPH
    string solution = "";
    Jug* jug = setJugStats();

    if (jug->solve(solution) != 1) {
        cout << "No Solution" << endl;
    } else {
        cout << left << setw(20) << "METHOD" << left << setw(10) << "COST" << "STATUS" << endl;
        cout << solution << endl << endl;
    }

    return 0;
}

Jug* setJugStats() {
    int aVol = 0, bVol = 0, target = 0;
    char choice;
    Jug* jug = nullptr;

    cout << "Solve The Jug Problem With The Cheapest Cost" << endl;
    cout << "the bigger jug has to be bigger than the target volume and less than 1000" << endl << endl;

    cout << "Enter small jug's volume: ";
    cin >> aVol;
    cout << "Enter big jug's volume: ";
    cin >> bVol;
    cout << "Enter target volume: ";
    cin >> target;

    cout << endl;
    cout << "Change the costs of steps? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        int cfA = 0, cfB = 0, ceA = 0, ceB = 0, cpAB = 0, cpBA = 0;
        cout << "Enter cost for fill A: ";
        cin >> cfA;
        cout << "Enter cost for fill B: ";
        cin >> cfB;
        cout << "Enter cost for empty A: ";
        cin >> ceA;
        cout << "Enter cost for empty B: ";
        cin >> ceB;
        cout << "Enter cost for pour A->B: ";
        cin >> cpAB;
        cout << "Enter cost for pour b->A: ";
        cin >> cpBA;
        jug = new Jug(aVol, bVol, target, cfA, cfB, ceA, ceB, cpAB, cpBA);
    } else {
        jug = new Jug(aVol, bVol, target, 1, 1, 1, 1, 1, 1);
        // cost to: fillA, fillB, emptyA, emptyB, pourA->B, pourB->A
    }
    cout << endl;
    cout << "Jug A volume: " << aVol << endl;
    cout << "Jug B volume: " << bVol << endl;
    cout << "target: " << target << endl << endl;
    return jug;
}