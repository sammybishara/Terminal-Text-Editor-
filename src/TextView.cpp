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
void TextView :: AddRow(const std::string &strRow, int row, int colorStart, int lineNumber)
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

void TextView :: AddRows(std::vector<std::pair<int, std::string> > rows)
{
    int index = 0;
    for (auto row : rows) AddRow(row.second, index++, 0, row.first);
}

void TextView :: AddStatusRow( const std::string &statusMsgLeft, const std::string &statusMsgRight, bool fBlackBackground )
{
    TextImp->AddStatusRow(statusMsgLeft, statusMsgRight, fBlackBackground);
}

// highlights the line numbers
void LineNumberTextView :: AddRow(const std::string &strRow, int row, int colorStart, int lineNumber)
{
    if (lineNumber != -1) TextViewDec::SetColor(row, colorStart, colorStart + 6, TEXT_COLOR_MAGENTA);
    TextViewDec::AddRow(strRow, row, colorStart + 7, lineNumber);
}

void LineNumberTextView :: AddRows(std::vector<std::pair<int, std::string> > rows)
{
    int index = 0;
    std::vector<std::pair<int, std::string> > embellishedDoc = Embellish(rows, GetColNumInView());
    for (auto row : embellishedDoc) AddRow(row.second, index++, 0, row.first);
}

std::vector<std::pair<int, std::string> > LineNumberTextView :: Embellish(std::vector<std::pair<int, std::string> > &rows, int screenWidth)
{
    std::vector<std::pair<int, std::string> > embellishedDoc = TextViewDec::Embellish(rows, screenWidth);

    for (unsigned int i = 0; i < embellishedDoc.size(); ++i)
    {
       if (embellishedDoc[i].first == -1 ) embellishedDoc[i].second = std::string("       ") + embellishedDoc[i].second;
       else
       {
            std::string lineNumber = std::to_string(embellishedDoc[i].first);
            embellishedDoc[i].second = std::string(6 - lineNumber.size(), ' ') + lineNumber + std::string(" ") + embellishedDoc[i].second;
       }
    }
    return embellishedDoc;
}

// Text view with Borders
void BorderTextView :: AddRow(const std::string &strRow, int row, int colorStart, int lineNumber)
{
    if (lineNumber != -1) TextViewDec::AddRow(strRow, row, colorStart + 2, lineNumber);
    else TextViewDec::AddRow(strRow, row, -1, lineNumber);
}

void BorderTextView :: AddRows(std::vector<std::pair<int, std::string> > rows)
{
    int index = 0;
    std::vector<std::pair<int, std::string> > embellishedDoc = Embellish(rows, GetColNumInView());
    // signals add row to color entire top portion of boarder
    for (auto row : embellishedDoc) AddRow(row.second, index++, 0, row.first);
}

std::vector<std::pair<int, std::string> > BorderTextView :: Embellish(std::vector<std::pair<int, std::string> > &rows, int screenWidth)
{
    std::vector<std::pair<int, std::string> > embellishedDoc = TextViewDec::Embellish(rows, screenWidth);
    screenWidth += TextViewDec::GetColsOccupied();

    for (auto &row : embellishedDoc)
    {
        row.second = std::string("| ") + row.second + std::string(screenWidth - (int)row.second.size(), ' ') + (" |");
    }
    // add boarders
    std::string topBoarder(screenWidth + 4, '_');
    std::string bottomBoarder(screenWidth + 4, '-');
    embellishedDoc.insert(embellishedDoc.begin(), std::make_pair(-1, topBoarder));
    embellishedDoc.push_back(std::make_pair(-1, bottomBoarder));
    
    return embellishedDoc;
}



