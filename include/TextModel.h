
#ifndef MODEL_H
#define MODEL_H

#include "ECTextViewImp.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <math.h>
#include <cctype>
#include <utility>


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

    // Adds a character 
    void AddChar(int row, int col, char ch, int screenWidth);

    // Removes a character 
    void RemoveChar(int row, int col);

    // Breaks the line 
    void BreakLine(int row, int col);

    // Merges two lines together for backspace 
    void Mergeline(int row);

    // Pastes the given row into the x and y position
    void Paste(const std::string strToPaste, const int x, const int y);

    // Remove a row or portion of a row 
    void RemoveRow(const int x, const int y, const int size);

    // Returns character count for converting to screen cursor
    int GetCharCount(int x, int y, int colSize);

    // Parses the document to fit the screen  
    std::vector<std::pair<int, std::string> > ParseRows(int colSize, int rowSize);

    // returns the current row
    std::string GetRow(int row) {return document[row];}

    // Returns the count of lines in the orignal document (no parsing)
    int GetSize() { return document.size();}

    void MoveDown(int colSize, bool nextLine);

    void MoveUp();

    unsigned int GetStart() {return start;}

    unsigned int GetEnd() {return ended;}

    int GetRowsOccupied(std::string &line, int colSize);

    // Replaces all tabs in the string
    // If there are no alphanumeric characters before the tab characters, 
    // tab is replaced with 8 spaces, else the tab is replaced with a single space
    std::string ReplaceTabs(const std::string &line);

    // Returns Tab adjustment for on screen cursro
    // If there are no alphanumeric characters before the tab characters,
    // then the cursor adjustment is incremented by 7. 
    int GetTabAdjustment(const int &row, const int &col);


private:
    std::vector<std::string> document;
    std::string filename;
    unsigned int start;
    unsigned int ended;
};

#endif