#ifndef ECCursor_h
#define ECCursor_h

#include<utility>

// Cursor class for managing the models x and y positions 
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

    void DecrementY() { y -= 1;}

    void DecrementX() { x -= 1;}

    int GetCursorX() {return x;}

    int GetCursorY() { return y;}

    // Converts the x and y cursor used to index the document into the onscreen cursors
    std::pair<int, int> ConvertCursors(int charCount, int colSize, int start, int yOffset, int xOffset, int tabAdjustment);

private:
    unsigned int x;
    unsigned int y;
};
#endif