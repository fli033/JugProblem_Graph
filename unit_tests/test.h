#include "../header/Jug.h"
#include "gtest/gtest.h"

TEST(test, t1) {
    Jug jug(23, 76, 55);
    string a = "";
    jug.solve(a);
    cout << a << endl;
}

TEST(test, t2) {
    Jug bomb(3, 5, 4, 1, 2, 1, 2, 1, 2);
    string a = "";
    bomb.solve(a);
    cout << a << endl;
}