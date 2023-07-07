#include "Cursor.h"

std::pair<int, int> Cursor :: ConvertCursors(int charCount, int colSize, int start, int yOffset, int xOffset)
{
    if (colSize <= 0) return std::make_pair(-1, -1);

    int newY = y - start + yOffset;
    int newX =  (x % colSize) + xOffset;

    newY += (int) charCount / colSize;

    return std::make_pair(newY, newX);
}