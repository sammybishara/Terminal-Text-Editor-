#include "ECTextController.h"

// reads the lines from the given file and uploads it to document and view
ECTextCtrl :: ECTextCtrl(TextView *textView, ECTextModel *textModel, const std::string filename) :
model(textModel),
mode(COMMAND_MODE),
file(filename),
cmdSet(NULL),
lineNumbers(false),
borders(false)
{
    view = new TextViewDec(textView);
    commandH = new ECCommandHistory();
    cursor = new Cursor();
    // add a status bar
    view->AddStatusRow("COMMAND MODE", "", false);
    ReadFromFile();
}

void ECTextCtrl :: ReadFromFile()
{
    std::ifstream infile(file);
    std::string line;
    
    if (infile.is_open())
    {
        while (std::getline(infile, line)) model->addRow(line);
        RefreshText();
        infile.close();
    }
}

ECTextCtrl :: ~ECTextCtrl()
{
    delete view;
    delete commandH;
    delete cursor;
    // if there is an empty command set delete it
    if (cmdSet != nullptr) 
    {
        delete cmdSet;
        cmdSet = NULL;
    } 
}

// creates and executes a new add text command and moves cursor to the right 
void ECTextCtrl :: addChar(char ch)
{
    InsertTextCommand *addText = new InsertTextCommand(view, model, ch, cursor);
    cmdSet->ExecuteCmd(addText);

    // moves cursor by 1
    cursor->SetCursorX(cursor->GetCursorX() + 1);
    RefreshCursor();
}

void ECTextCtrl :: Delete()
{
    int x = cursor->GetCursorX();
    int y = cursor->GetCursorY();

    if (x == 0 && y == 0) return;
    // moves cursor for backspace merge line if current column is 0 and row is not row 0, does nothing if cursor is at 0, 0
    else if (x == 0 && y != 0) mergeLine(); 
    else removeChar();
}

void ECTextCtrl :: removeChar()
{
    RemoveTextCommand *rText = new RemoveTextCommand(view, model, cursor);
    cmdSet->ExecuteCmd(rText);
    
    // sets cursor back by one 
    cursor->SetCursorX(cursor->GetCursorX() - 1);
    RefreshCursor();
}

// moves the cursor left 
void ECTextCtrl :: moveLeft()
{
    // checks if cursor is not at beginning of row, else move left
    if (model->GetSize() == 0) return;
    if (cursor->GetCursorX() > 0) cursor->SetCursorX(cursor->GetCursorX() - 1);
    RefreshCursor();
}

// moves cursor right 
void ECTextCtrl :: moveRight()
{
    if (model->GetSize() == 0) return;
    // checks if cursor is not greater than size() of current row, else move right 
    if (cursor->GetCursorX() < model->GetRow(cursor->GetCursorY()).size()) cursor->SetCursorX(cursor->GetCursorX() + 1);
    RefreshCursor();
}

// moves cursor down
void ECTextCtrl :: moveDown()
{
    if (model->GetSize() == 0) return;


    int rows = model->GetRowsOccupied(cursor->GetCursorY(), view->GetColNumInView());
    // moves y down if possible, checks if x is greater than new row's size, if it set it to the size of the new row
    if (cursor->GetCursorY() + 1 < model->GetSize()) cursor->SetCursorY(cursor->GetCursorY() + 1);
    if (model->GetRow(cursor->GetCursorY()).size() < cursor->GetCursorX()) cursor->SetCursorX(model->GetRow(cursor->GetCursorY()).size());

    std::pair<std::vector<std::string>, std::vector<int> > pair = model->ParseRows(view->GetColNumInView(), view->GetRowNumInView());
    std::vector<std::string> currentRows = pair.first;

    if (currentRows.size() - 1 - view->YOffset() - rows < view->GetCursorY() && cursor->GetCursorY() < model->GetSize() - 1) 
    {
        model->MoveDown(view->GetColNumInView());
        RefreshText();
    }
    RefreshCursor();
}

// moves cursor up 
void ECTextCtrl :: moveUp()
{   
    if (model->GetSize() == 0 ) return;

    int pos = view->GetCursorY();
    // moves y up if possible, checks if x is greater than new row's size, it it is, set it to the size of the new row
    if (cursor->GetCursorY() > 0) cursor->SetCursorY(cursor->GetCursorY() - 1);
    if (model->GetRow(cursor->GetCursorY()).size() < cursor->GetCursorX()) cursor->SetCursorX(model->GetRow(cursor->GetCursorY()).size());

    if (view->GetCursorY() == 0 + view->YOffset()) 
    {
        model->MoveUp();
        RefreshText();
    }
    RefreshCursor();
}

// breaks line when user hits enter 
void ECTextCtrl :: breakLine()
{
    BreakLineCommand *breakL = new BreakLineCommand(view, model, cursor);
    cmdSet->ExecuteCmd(breakL);

    // moves cursor to the beginning of the new row
    cursor->SetCursorY(cursor->GetCursorY() + 1);
    cursor->SetCursorX(0);
    RefreshCursor();
}


// merges line with previous line when backspace is hit and column is 0 
void ECTextCtrl :: mergeLine()
{
    int newX = model->GetRow(cursor->GetCursorY() - 1).size();
    MergeLineCommand *mergeC = new MergeLineCommand(view, model, cursor);
    cmdSet->ExecuteCmd(mergeC);

    // moves cursor to the end of the previous row before the merge 
    cursor->SetCursorY(cursor->GetCursorY() - 1);
    cursor->SetCursorX(newX);
    RefreshCursor();
}

// changes mode to the oposite mode 
void ECTextCtrl :: changeMode(int newMode)
{
    mode = newMode;
    view->ClearStatusRows();
    // changes the status row to match the mode that it is in
    if (mode == EDIT_MODE) 
    {   
        // creates a new set of commands if edit mode is entered, changes status row
        cmdSet = new ECCommandSet();
        view->AddStatusRow("-- INSERT --", "", false);
    }
    else 
    {
        view->AddStatusRow("COMMAND MODE", "", false);
        // if the current set of commands is not empty, add the command set, else delete the pointer 
        if (cmdSet->GetNumCommands() > 0) commandH->AddCommand(cmdSet);
        else delete cmdSet;
        cmdSet = NULL;
    }
}

void ECTextCtrl :: ToggleLineNumbers()
{
    if (dynamic_cast<LineNumberTextView*>(view)) 
    {
        view = view->PreviousView();
        lineNumbers = false;
        RefreshText();
        RefreshCursor();   
    }
    else if (!lineNumbers) 
    {
        view = new LineNumberTextView(view);
        lineNumbers = true;
        RefreshText();
        RefreshCursor();
    }
}

void ECTextCtrl :: ToggleBorder()
{
    if (dynamic_cast<BorderTextView*>(view)) 
    {
        view = view->PreviousView();
        borders = false;
        RefreshText();
        RefreshCursor();
    }
    else if (!borders) 
    {
        view = new BorderTextView(view);
        borders = true;
        RefreshText();
        RefreshCursor();
    }
}

void ECTextCtrl :: RefreshText()
{
   std::pair<std::vector<std::string>, std::vector<int> > pair = model->ParseRows(view->GetColNumInView(), view->GetRowNumInView());
   view->AddRows(pair.first, pair.second);
}

void ECTextCtrl :: RefreshCursor()
{
    int charCount = model->GetCharCount(cursor->GetCursorX(), cursor->GetCursorY(), view->GetColNumInView());
    view->SetCursors(cursor->GetCursorX(), cursor->GetCursorY(), charCount, model->GetStart()); 
}

