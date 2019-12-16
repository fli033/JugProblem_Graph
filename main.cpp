#include <iostream>
#include "Jug.h"

using namespace std;

int main()
{
    //FIX BUILD GRAPH
{
   string solution;
   Jug head(12, 17, 14, 1, 1, 1, 1, 1, 1);
   //(SMALL VOLUME, LARGE VOLUME, TARGET VOLUME)
   if (head.solve(solution) != 1) {
      cout << "Error 3" << endl;
   }
   cout << solution << endl << endl;
}
}
