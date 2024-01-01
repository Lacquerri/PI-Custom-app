#include <iostream>
using namespace std;
class tile
{
public:
    bool isMined;
    int area;
    bool isCovered;
    bool isFlagged;
    tile() {
        isMined = false;
        area = 0;
        isCovered = true;
        isFlagged = false;
    }
};