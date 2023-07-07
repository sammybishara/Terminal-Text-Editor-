

#ifndef ECCursor_h
#define ECCursor_h

#include<utility>


// cursor class for managing the docs x and y positions 
class Cursor
{
public:
    Cursor() :
    x(0),
    y(0) {}

    virtual ~Cursor() {}

    void SetCursorX(int newX) { x = newX;}

    void SetCursorY(int newY) { y = newY;}

    int GetCursorX() {return x;}

    int GetCursorY() { return y;}

    std::pair<int, int> ConvertCursors(int charCount, int colSize, int start, int yOffset, int xOffset);

private:
    int x;
    int y;
};




#endif