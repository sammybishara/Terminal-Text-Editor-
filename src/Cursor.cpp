#include "Cursor.h"

std::pair<int, int> Cursor :: ConvertCursors(int charCount, int colSize, int start, int yOffset, int xOffset, int tabAdjustment)
{
    if (colSize <= 0) return std::make_pair(-1, -1);
    // start of document is substracted from current y to adjust for on screen row indexs
    int newY = y - start;
    // tab adjustment is added to x and performed the modulo operation to get the current onscreen x position
    int newX =  ((x + tabAdjustment) % colSize) + xOffset;

    newY += (int) charCount / colSize;
    newY += yOffset;

    return std::make_pair(newY, newX);
}