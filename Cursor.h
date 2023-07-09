

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

    void SetCursorX(unsigned int newX) { x = newX;}

    void SetCursorY(unsigned int newY) { y = newY;}

    void IncrementY() { y += 1;}

    void IncrementX() { x += 1; }

    int GetCursorX() {return x;}

    int GetCursorY() { return y;}


    std::pair<int, int> ConvertCursors(int charCount, int colSize, int start, int yOffset, int xOffset);

private:
    unsigned int x;
    unsigned int y;
};




#endif