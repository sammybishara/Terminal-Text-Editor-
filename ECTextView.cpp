#include "ECTextView.h"

// opens the keywords file when initialized to create a set of keywords to highlight 
ECTextView :: ECTextView() : 
lineNumbersOn(false)
{
    TextImp = new ECTextViewImp();

    std::string filename = "keywords.txt";
    std::ifstream file(filename);
    std::string word;

    if (file.is_open())
    {
        while (file >> word) wordsToHighlight.insert(word);
    }
    file.close();
}

ECTextView :: ~ECTextView()
{
    delete TextImp;
}

// check if a row contains any keywords that need to be highlighted and highlights them 
void ECTextView :: AddRow(const std::string &strRow, int row)
{
    std::string word = "";

    for (int i = 0; i < strRow.size(); i++)
    {
        if (strRow[i] != ' ') word = strRow[i];
        else word = "";

        if (wordsToHighlight.find(word) != wordsToHighlight.end()) SetColor(row, i - word.size() + 1, i, TEXT_COLOR_BLUE);
    }
    TextImp->AddRow(strRow);
}

void ECTextView :: AddRows(std::vector<std::string> rows, int start)
{
    TextImp->InitRows();
    TextImp->ClearColor();

    int index = 0;
    for (auto row : rows) AddRow(row, index++);
}

void ECTextView :: AddStatusRow( const std::string &statusMsgLeft, const std::string &statusMsgRight, bool fBlackBackground )
{
    TextImp->AddStatusRow(statusMsgLeft, statusMsgRight, fBlackBackground);
}

// converts cursor positions from the controller to the view 
void ECTextView :: SetCursors(int x, int y, int charCount, int start)
{
    if (GetColNumInView() <= 0) return;

    int newY = y - start;
    int newX =  (x % GetColNumInView());

    newY += (int) charCount / GetColNumInView();

    TextImp->SetCursorX(newX);
    TextImp->SetCursorY(newY);
}


// Text View with line Numbers 
void LineNumberTextView :: AddRow(const std::string &strRow, int row)
{
    view->AddRow(strRow, row);
}

void LineNumberTextView :: AddRows(std::vector<std::string> rows, int start)
{
    view->InitRows();
    view->ClearColor();
    int index = 0;

    std::vector<std::string> embellishedDoc = Embellish(rows, GetColNumInView(), start);

    for (auto row : embellishedDoc)
    {
        AddRow(row, index++);
    }
}

std::vector<std::string> LineNumberTextView :: Embellish(std::vector<std::string> &rows, int screenWidth, int start)
{
    std::vector<std::string> embellishedDoc = view->Embellish(rows, screenWidth, start);

    bool hasLineNumber = true;
    int count = start + 1;
    unsigned int i = 0 + view->YOffset();
    unsigned int end = embellishedDoc.size() - view->YOffset();

    for (; i < end; ++i)
    {   
        std::string line = embellishedDoc[i];
        int originalSize = line.size();

        if (originalSize <= view->GetColNumInView() && hasLineNumber == true)
        {
            std::string lineNumber = std::to_string(count++);
            embellishedDoc[i] = std::string(6 - lineNumber.size(), ' ') + lineNumber + std::string(" ") + line;
            hasLineNumber = false;

        } else (embellishedDoc[i] = std::string("       ") + line);

        if (originalSize < view->GetColNumInView()) hasLineNumber = true;
    }
    return embellishedDoc;
}

void LineNumberTextView :: SetCursors(int x, int y, int charCount, int start)
{
    if (GetColNumInView() <= 0) return;

    int newY = y - start + YOffset();
    int newX =  (x % GetColNumInView()) + XOffset();

    newY += (int) charCount / GetColNumInView();

    view->SetCursorX(newX);
    view->SetCursorY(newY);
}

// Text view with Borders
void BorderTextView :: AddRow(const std::string &strRow, int row)
{
    view->AddRow(strRow, row);
}

void BorderTextView :: AddRows(std::vector<std::string> rows, int start)
{
    view->InitRows();
    view->ClearColor();

    int index = 0;
    std::vector<std::string> embellishedDoc = Embellish(rows, GetColNumInView(), start);
    for (auto row : embellishedDoc) AddRow(row, index++);
}

std::vector<std::string> BorderTextView :: Embellish(std::vector<std::string> &rows, int screenWidth, int start)
{
    std::vector<std::string> embellishedDoc = view->Embellish(rows, screenWidth, start);

    for (unsigned int i = 0; i < embellishedDoc.size(); ++i)
    {
        embellishedDoc[i] = std::string("| ") + embellishedDoc[i] + std::string(screenWidth - embellishedDoc[i].size(), ' ') + std::string(" |");
    }
    std::string verticalBorder = std::string(1, ' ') + std::string(screenWidth + 2, '-');
    embellishedDoc.insert(embellishedDoc.begin(), verticalBorder);
    embellishedDoc.push_back(verticalBorder);
    return embellishedDoc;
}

void BorderTextView :: SetCursors(int x, int y, int charCount, int start)
{
    if (GetColNumInView() <= 0) return;

    int newY = y - start + YOffset();
    int newX =  (x % GetColNumInView()) + XOffset();

    newY += (int) charCount / GetColNumInView();

    view->SetCursorX(newX);
    view->SetCursorY(newY);
}



