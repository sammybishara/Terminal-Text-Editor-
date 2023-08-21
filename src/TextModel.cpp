#include "TextModel.h"

TextModel :: ~TextModel() 
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
void TextModel :: AddChar(int row, int col, char ch, int screenWidth)
{  
    if (document.size() == 0) AddRow(std::string(1, ch));
    else if (document[row].size() == 0 || document[row].size() == col) document[row].push_back(ch);
    else document[row].insert(col, 1, ch);
}

// removes character 
void TextModel :: RemoveChar(int row, int col)
{
    if (document.size() == 0) return;
    else if (document[row].size() == 1) document[row].erase(0);
    else if (col >= 0 && col < document[row].size()) document[row].erase(col, 1);
}

// splits line when user hits enter 
void TextModel :: BreakLine(int row, int col)
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
void TextModel :: Mergeline(int row)
{
    std::string curString = document[row];
    document[row - 1].append(curString);
    document.erase(document.begin() + row);
}

// pastes the new row
void TextModel :: Paste(const std::string strToPaste, const int x, const int y)
{
    document[y] = document[y].insert(x, strToPaste);
}

// erases a row on screen
void TextModel :: RemoveRow(const int x, const int y, const int size)
{
    document[y].erase(x, size);
}

// returns the character count for adjusting cursors
int TextModel :: GetCharCount(int x, int y, int colSize)
{
    int index = start;
    int totalCount = x + GetTabAdjustment(y, x);

    while (index < y)
    {
        int charCount = ReplaceTabs(document[index]).size();
        totalCount += charCount;

        if (charCount % colSize > 0) totalCount -= charCount % colSize;
        index++;
    }
    return totalCount;
}

// Parses the document
std::vector<std::pair<int, std::string> > TextModel :: ParseRows(int colSize, int rowSize)
{
    std::vector<std::pair<int, std::string> > ParsedDocument;
    int count = start + 1;
    int rowsFilled = 0;

    for (unsigned int i = start; i < document.size(); ++i)
    {
        // replaces the tabs in the string for the view 
        std::string line = ReplaceTabs(document[i]);
        
        // get the amount of rows the cur line will occupy
        int rowCount = GetRowsOccupied(line, colSize);

        // if new line occupies more space than is available, break
        if (rowCount + rowsFilled > rowSize) 
        {   
            this->ended = i - 1;
            break;
        }
    
        int lineNumber = count;
        count++;
        rowsFilled += rowCount;

        // slices the line by the column size and adds them to the ParsedDocument
        while (line.size() > colSize)
        {
            ParsedDocument.push_back(std::make_pair(lineNumber, line.substr(0, colSize)));
            line = line.substr(colSize);
            lineNumber = -1;
        }
        if (document[i].size() == 0) ParsedDocument.push_back(std::make_pair(lineNumber, document[i]));
        else if (line.size() > 0) ParsedDocument.push_back(std::make_pair(lineNumber, line));
    }
    return ParsedDocument;
}

void TextModel :: MoveDown(int colSize, bool nextLine)
{
    if (ended + 1 >= document.size() && nextLine) return;

    // Get the rows occupied by the new row that is visible when the screen moves down
    int rows;
    (nextLine) ? rows = GetRowsOccupied(document[ended + 1], colSize) : rows = GetRowsOccupied(document[ended], colSize);
    // moves the start index forward until there is enough space for the rows occupied by the new line 
    while (rows > 0)
    {
        // Get the rows occupied at the start index 
        int rowCount = GetRowsOccupied(document[start], colSize);
        rows -= rowCount;
        start++;
    }
}

void TextModel :: MoveUp()
{
    if (start - 1 >= 0) start -= 1;
}

// returns the rows occupied given the column size of the screen 
int TextModel :: GetRowsOccupied(std::string &line, int colSize)
{
    if (colSize == 0) return -1;
    int rowCount = (line.size() / colSize);
    if (line.size() == 0 || line.size() % colSize != 0) rowCount++;
    return rowCount;
}

// Replaces all tabs in the given line
// if there are no alphanumeric characters before the tab, tab is replaces with 8 spaces 
// else the tab character is replaces with 1 spaces
std::string TextModel :: ReplaceTabs(const std::string &line)
{
    bool charFound = false;
    std::string lineWithoutTabs;
    for (char ch : line)
    {
        if (ch == '\t')
        {
            if (charFound) lineWithoutTabs += ' ';
            else lineWithoutTabs += "        ";
        }
        else 
        {
            if (std::isalnum(ch)) charFound = true;
            lineWithoutTabs += ch;
        }
    }
    return lineWithoutTabs;
}

// Returns Tab adjustment for on screen cursro
// If there are no alphanumeric characters before the tab characters,
// then the cursor adjustment is incremented by 7. 
int TextModel :: GetTabAdjustment(const int &row, const int &col)
{
    bool charFound = false;
    std::string line = document[row];
    int count = 0;

    for (unsigned int i = 0; i <= col; ++i)
    {
        if (line[i] == '\t' && !charFound) count += 7;
        else 
        {
            if (std::isalnum(line[i])) charFound = true;
        }
    }
    return count;
}