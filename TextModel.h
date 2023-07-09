
#ifndef MODEL_H
#define MODEL_H

#include "ECTextViewImp.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <math.h>


class TextModel 
{

public:

    TextModel(const std::string filename) :
    filename(filename),
    start(0),
    ended(0)
    {
    }

    virtual ~TextModel();

    // updates the document and calls the controller to display
    void AddRow(const std::string row) { document.push_back(row); }

    // clears the document 
    void Clear() { document.clear(); }

    // add a character 
    void AddChar(int row, int col, char ch, int screenWidth);

    // removes a character 
    void RemoveChar(int row, int col);

    // breaks the line 
    void BreakLine(int row, int col);

    // merges two lines together for backspace 
    void Mergeline(int row);

    // Paste the given row into the x and y position
    void Paste(const std::string strToPaste, const int x, const int y);

    // Remove a row or portion of a row 
    void RemoveRow(const int x, const int y, const int size);

    // returns character count for converting to screen cursor
    int GetCharCount(int x, int y, int colSize);

    // Parses the document to fit the screen  
    std::pair<std::vector<std::string>, std::vector<int> > ParseRows(int colSize, int rowSize);

    // returns the current row
    std::string GetRow(int row) {return document[row];}

    int GetSize() { return document.size();}

    void MoveDown(int colSize, bool nextLine);

    void MoveUp();

    unsigned int GetStart() {return start;}

    unsigned int GetEnd() {return ended;}

    int GetRowsOccupied(int lineNum, int colSize);


private:
    std::vector<std::string> document;
    std::string filename;
    unsigned int start;
    unsigned int ended;
};

#endif