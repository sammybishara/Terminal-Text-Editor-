
#ifndef MODEL_H
#define MODEL_H

#include "ECTextViewImp.h"
#include <iostream>
#include <fstream>


class ECTextModel 
{

public:

    ECTextModel(const std::string filename) :
    filename(filename),
    start(0),
    ended(-1)
    {
    }

    virtual ~ECTextModel();

    // updates the document and calls the controller to display
    void addRow(const std::string row) { document.push_back(row); }

    // clears the document 
    void Clear() { document.clear(); }

    // add a character 
    void addChar(int row, int col, char ch, int screenWidth, int cursorY);

    // removes a character 
    void removeChar(int row, int col);

    // breaks the line 
    void breakLine(int row, int col);

    // merges two lines together for backspace 
    void mergeline(int row);

    // returns character count for converting to screen cursor
    int GetCharCount(int x, int y, int colSize);

    // Parses the document to fit the screen  
    std::vector<std::string> ParseRows(int colSize, int rowSize);

    // returns the current row
    std::string GetRow(int row) {return document[row];}

    int GetSize() { return document.size();}

    void MoveDown(int colSize);

    void MoveUp();

    int GetStart() {return start;}

    int GetRowsOccupied(int lineNum, int colSize);

private:
    std::vector<std::string> document;
    std::string filename;
    int start;
    int ended;
};

#endif