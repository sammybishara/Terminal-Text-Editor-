#include "TextView.h"

// opens the keywords file when initialized to create a set of keywords to highlight 
TextView :: TextView()
{
    TextImp = new ECTextViewImp();

    std::string filename = "keywords.txt";
    std::ifstream file(filename);
    std::string word;

    if (file.is_open())
    {
        while (file >> word) wordsToHighlight.insert(word);
        file.close();
    }
}

TextView :: ~TextView()
{
    delete TextImp;
}

// check if a row contains any keywords that need to be highlighted and highlights them 
void TextView :: AddRow(const std::string &strRow, int row, int colorStart)
{
    std::string word = "";

    for (int i = 0; i < strRow.size(); i++)
    {
        if (strRow[i] != ' ') word += strRow[i];
        else word = "";

        if (wordsToHighlight.find(word) != wordsToHighlight.end()) TextImp->SetColor(row, i - word.size() + 1, i, TEXT_COLOR_BLUE);
    }
    TextImp->AddRow(strRow);
}

void TextView :: AddRows(std::vector<std::string> rows, std::vector<int> lineNumbers)
{
    int index = 0;
    for (auto row : rows) AddRow(row, index++, 0);
}

void TextView :: AddStatusRow( const std::string &statusMsgLeft, const std::string &statusMsgRight, bool fBlackBackground )
{
    TextImp->AddStatusRow(statusMsgLeft, statusMsgRight, fBlackBackground);
}

// highlights the line numbers
void LineNumberTextView :: AddRow(const std::string &strRow, int row, int colorStart)
{
    if (colorStart != -1) TextViewDec::SetColor(row, colorStart, colorStart + 6, TEXT_COLOR_MAGENTA);
    TextViewDec::AddRow(strRow, row, colorStart + 7);
}

void LineNumberTextView :: AddRows(std::vector<std::string> rows, std::vector<int> lineNumbers)
{
    int index = 0;
    std::vector<std::string> embellishedDoc = Embellish(rows, GetColNumInView(), lineNumbers);
    for (auto row : embellishedDoc) AddRow(row, index++, 0);
}

std::vector<std::string> LineNumberTextView :: Embellish(std::vector<std::string> &rows, int screenWidth, std::vector<int> &lineNumbers)
{
    std::vector<std::string> embellishedDoc = TextViewDec::Embellish(rows, screenWidth, lineNumbers);

    if (embellishedDoc.size() != lineNumbers.size()) return embellishedDoc;

    for (unsigned int i = 0; i < lineNumbers.size(); ++i)
    {
       if (lineNumbers[i] == -1 ) embellishedDoc[i] = std::string("       ") + embellishedDoc[i];
       else
       {
            std::string lineNumber = std::to_string(lineNumbers[i]);
            embellishedDoc[i] = std::string(6 - lineNumber.size(), ' ') + lineNumber + std::string(" ") + embellishedDoc[i];
       }
    }
    return embellishedDoc;
}

// Text view with Borders
void BorderTextView :: AddRow(const std::string &strRow, int row, int colorStart)
{
    if (colorStart != -1) TextViewDec::AddRow(strRow, row, colorStart + 2);
    else TextViewDec::AddRow(strRow, row, -1);
}
void BorderTextView :: AddRows(std::vector<std::string> rows, std::vector<int> lineNumbers)
{
    int index = 0;
    std::vector<std::string> embellishedDoc = Embellish(rows, GetColNumInView(), lineNumbers);
    // signals add row to color entire top portion of boarder
    for (std::string row : embellishedDoc) AddRow(row, index++, 0);
}

std::vector<std::string> BorderTextView :: Embellish(std::vector<std::string> &rows, int screenWidth, std::vector<int> &lineNumbers)
{
    std::vector<std::string> embellishedDoc = TextViewDec::Embellish(rows, screenWidth, lineNumbers);
    screenWidth += TextViewDec::GetColsOccupied();

    for (std::string &row : embellishedDoc)
    {
        row = std::string("| ") + row + std::string(screenWidth - (int)row.size(), ' ') + (" |");
    }
    // add boarders
    std::string topBoarder(screenWidth + 4, '_');
    std::string bottomBoarder(screenWidth + 4, '-');
    embellishedDoc.insert(embellishedDoc.begin(), topBoarder);
    embellishedDoc.push_back(bottomBoarder);
    // adjusts line numbers for boarders
    lineNumbers.insert(lineNumbers.begin(), -1);
    lineNumbers.push_back(-1);
    
    return embellishedDoc;
}



