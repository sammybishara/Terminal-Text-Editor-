#include "ECTextModel.h"

ECTextModel :: ~ECTextModel() 
{

    // writes to given file the document before being destroyed 
    std::ofstream file(filename);

    if (file.is_open())
    {
        for (auto line : document) file << line << std::endl;
        file.close();
    }
}

// adds character 
void ECTextModel :: addChar(int row, int col, char ch, int screenWidth, int cursorY)
{   
    if (document.size() == 0) addRow(std::string(1, ch));
    else if (document[row].size() == 0 || document[row].size() == col) document[row].push_back(ch);
    else document[row].insert(col, 1, ch);
}

// removes character 
void ECTextModel :: removeChar(int row, int col)
{
    if (document.size() == 0) return;
    else if (document[row].size() == 1) document[row].erase(0);
    else if (col >= 0 && col < document[row].size()) document[row].erase(col, 1);
}

// splits line when user hits enter 
void ECTextModel :: breakLine(int row, int col)
{

    if (document.size() == 0) document.push_back(std::string());

    std::string curLine = document[row];

    if (curLine.size() == 0) document.insert(document.begin() + row + 1, std::string());
    else
    {
        std::string newCurLine = curLine.substr(0, col);
        std::string nextLine = curLine.substr(col, curLine.length() - col);
        document[row] = newCurLine;
        document.insert(document.begin() + row + 1, nextLine);
    }
}
// merges two lines together 
void ECTextModel :: mergeline(int row)
{
    std::string curString = document[row];
    document[row - 1].append(curString);
    document.erase(document.begin() + row);
}

int ECTextModel :: GetCharCount(int x, int y, int colSize)
{
    int index = start;
    int charCount = x;

    while (index < y)
    {
        charCount += document[index].size();

        if (document[index].size() % colSize > 0) charCount -= document[index].size() % colSize;
        index++;
    }
    return charCount;
}


std::vector<std::string> ECTextModel :: ParseRows(int colSize, int rowSize)
{
    // parses rows if there is a column and row limit, splits the lines until the screen is full 
    int rowsFilled = 0;
    std::string line;

    std::vector<std::string> ParsedDocument;

    for (unsigned int i = start; i < document.size(); ++i)
    {
        line = document[i];

        // get the amount of rows a line will occupy
        int rowCount = (int) line.size() / colSize;
        if (line.size() == 0 || line.size() % colSize > 0) rowCount++;

        if (rowCount + rowsFilled > rowSize) 
            {   
                ended = i - 1;
                break;
            }
        rowsFilled += rowCount;

        // parse the rows for the column size
        while (line.size() > colSize)
        {
            ParsedDocument.push_back(line.substr(0, colSize));
            line = line.substr(colSize, line.length() - colSize + 1);
        }
        if ((document[i].size() == 0 && line.size() == 0) || line.size() > 0) ParsedDocument.push_back(line);
    }
    return ParsedDocument;
}

void ECTextModel :: MoveDown(int colSize)
{
    if (ended + 1 >= document.size()) return;

    std::string nextLine = document[ended + 1];


    int rows = (int) nextLine.size() / colSize;
    if (nextLine.size() == 0 || nextLine.size() % colSize > 0) rows++;


    while (rows > 0)
    {
        int rowCount = (int) document[start].size() / colSize;
        if (document[start].size() == 0 || document[start].size() % colSize > 0) rowCount++;

        rows -= rowCount;
        start++;
    }
}


void ECTextModel :: MoveUp()
{
    if (start - 1 >= 0) start -= 1;
}


int ECTextModel :: GetRowsOccupied(int lineNum, int colSize)
{

    if (colSize == 0) return -1;

    std::string line = document[lineNum];
    int rowCount = (int) line.size() / colSize;
    if (line.size() == 0 || line.size() % colSize) rowCount++;


    return rowCount;

}