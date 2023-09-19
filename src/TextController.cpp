#include "TextController.h"

// reads the lines from the given file and uploads it to document and view
TextCtrl :: TextCtrl(TextView *textView, TextModel *textModel, const std::string filename) :
model(textModel),
mode(COMMAND_MODE),
file(filename),
cmdSet(NULL),
lineNumbers(false),
borders(false)
{
    view = new TextViewDec(textView);
    commandH = new CommandHistory();
    cursor = new Cursor();
    // add a status bar
    view->AddStatusRow("COMMAND MODE", "", false);
    ReadFromFile();
}

void TextCtrl :: ReadFromFile()
{
    std::ifstream infile(file);
    std::string line;
    // Retrieves all rows from the given file name, adds it to the view and closes orignal file
    if (infile.is_open())
    {
        while (std::getline(infile, line)) model->AddRow(line);
        RefreshText();
        infile.close();
    }
}

TextCtrl :: ~TextCtrl()
{
    delete commandH;
    delete cursor;

    // if there is an empty command set delete it
    if (cmdSet != nullptr) 
    {
        delete cmdSet;
        cmdSet = NULL;
    } 
    // delete all textview objects that were created 
    while (view != nullptr)
    {
        TextView *prev = view->PreviousView();
        delete view;
        view = prev;
    }
}

// creates and executes a new add text command and moves cursor to the right 
void TextCtrl :: AddChar(const char ch)
{
    InsertTextCommand *addText = new InsertTextCommand(view, model, ch, cursor);
    cmdSet->ExecuteCmd(addText);
    RefreshText();

    // retrive on screen cursors
    int x, y;
    std::tie(y, x) = ConvertCursor();

    // if cursor is at the bottom right corner Scroll the view down to show the continued portion of the wrapped line
    if (view->GetRowNumInView() - 1  == y  && x == view->GetColNumInView() - 1) ScrollDown(false);
    // moves cursor right over by 1
    MoveRight();
}

void TextCtrl :: Delete()
{
    int x = cursor->GetCursorX();
    int y = cursor->GetCursorY();

    if (x == 0 && y == 0) return;
    // moves cursor for backspace merge line if current column is 0 and row is not row 0, does nothing if cursor is at 0, 0
    else if (x == 0 && y != 0) MergeLine(); 
    else RemoveChar();
}

void TextCtrl :: Copy()
{
    std::string fullRow = model->GetRow(cursor->GetCursorY());
    // gets starting point of the current row where the cursor is postioned and copies the row
    int pos = cursor->GetCursorX() - view->GetCursorX();
    copiedLine = fullRow.substr(pos, view->GetColNumInView());
}

// creates a new paste command and pastes it to the view
void TextCtrl :: Paste()
{
    cmdSet = new CommandSet();
    PasteCommand *paste = new PasteCommand(view, model, cursor, copiedLine);
    RefreshText();
    cmdSet->ExecuteCmd(paste);
    commandH->AddCommand(cmdSet);
    cmdSet = NULL;
    RefreshText();
    RefreshCursor();
}

void TextCtrl :: RemoveChar()
{
    RemoveTextCommand *rText = new RemoveTextCommand(view, model, cursor);
    cmdSet->ExecuteCmd(rText);
    RefreshText();
    // sets cursor left by one
    MoveLeft();
}

// moves the cursor left 
void TextCtrl :: MoveLeft()
{
    // checks if cursor is not at beginning of row, else move left
    if (cursor->GetCursorX() > 0) cursor->DecrementX();
    RefreshCursor();
}

// moves cursor right 
void TextCtrl :: MoveRight()
{
    if (model->GetSize() == 0) return;
    int y = cursor->GetCursorY();
    std::string curRow = model->GetRow(y);
    // checks if cursor is not greater than size() of current row, else move right 
    if (cursor->GetCursorX() < curRow.size()) cursor->IncrementX();
    RefreshCursor();
}

// moves cursor down
void TextCtrl :: MoveDown()
{
    if (model->GetSize() == 0) return;

    int endOfPage = model->GetEnd();
    // moves y down if possible, checks if x is greater than new row's size, if it set it to the size of the new row
    if (cursor->GetCursorY() + 1 < model->GetSize()) cursor->SetCursorY(cursor->GetCursorY() + 1);
    if (model->GetRow(cursor->GetCursorY()).size() < cursor->GetCursorX()) cursor->SetCursorX(model->GetRow(cursor->GetCursorY()).size());

    if (cursor->GetCursorY() > endOfPage) ScrollDown(true);
    RefreshCursor();
}

void TextCtrl :: ScrollDown(bool nextLine)
{
    model->MoveDown(view->GetColNumInView(), nextLine);
    RefreshText();
}

// moves cursor up 
void TextCtrl :: MoveUp()
{   
    if (model->GetSize() == 0 ) return;

    int startOfPage = model->GetStart();
    // moves y up if possible, checks if x is greater than new row's size, it it is, set it to the size of the new row
    if (cursor->GetCursorY() > 0) cursor->SetCursorY(cursor->GetCursorY() - 1);
    if (model->GetRow(cursor->GetCursorY()).size() < cursor->GetCursorX()) cursor->SetCursorX(model->GetRow(cursor->GetCursorY()).size());

    if (cursor->GetCursorY() < startOfPage) 
    {
        model->MoveUp();
        RefreshText();
    }
    RefreshCursor();
}

// breaks line when user hits enter 
void TextCtrl :: BreakLine()
{
    BreakLineCommand *breakL = new BreakLineCommand(view, model, cursor);
    cmdSet->ExecuteCmd(breakL);
    RefreshText();
    // moves cursor to the beginning of the new row below
    cursor->SetCursorX(0);
    MoveDown();
}


// merges line with previous line when backspace is hit and column is 0 
void TextCtrl :: MergeLine()
{
    int newX = model->GetRow(cursor->GetCursorY() - 1).size();
    MergeLineCommand *mergeC = new MergeLineCommand(view, model, cursor);
    cmdSet->ExecuteCmd(mergeC);
    RefreshText();
    // moves cursor to the end of the previous row before the merge 
    cursor->SetCursorX(newX);
    MoveUp();
}

// changes mode to the oposite mode 
void TextCtrl :: ChangeMode(int newMode)
{
    mode = newMode;
    view->ClearStatusRows();
    // changes the status row to match the mode that it is in
    if (mode == EDIT_MODE) 
    {   
        // creates a new set of commands if edit mode is entered, changes status row
        cmdSet = new CommandSet();
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

void TextCtrl :: Undo()
{
    commandH->Undo();
    RefreshText();
}

void TextCtrl :: Redo()
{
    commandH->Redo();
    RefreshText();
}

// toggles between line numbers
void TextCtrl :: ToggleLineNumbers()
{
    if (dynamic_cast<LineNumberTextView*>(view)) 
    {
        TextView *previousView = view->PreviousView();
        delete view;
        view = previousView;
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

// toggle betweens boarder 
void TextCtrl :: ToggleBorder()
{
    if (dynamic_cast<BorderTextView*>(view)) 
    {
        TextView *previousView = view->PreviousView();
        delete view;
        view = previousView;
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

// Parses the rows and adds the rows to the view. Color is cleared and then view is refreshed
void TextCtrl :: RefreshText()
{
    auto parsedDoc = model->ParseRows(view->GetColNumInView(), view->GetRowNumInView());
    view->InitRows();
    view->ClearColor();
    view->AddRows(parsedDoc);
    view->Refresh();
}

// Screen Cursors are recalculated and set in the view
void TextCtrl :: RefreshCursor()
{
    std::pair<int, int> pos = ConvertCursor();
    view->SetCursorY(pos.first);
    view->SetCursorX(pos.second);
    view->Refresh();
}

// Gets the current positions from the cursor
std::pair<int, int> TextCtrl :: ConvertCursor()
{
    int charCount = model->GetCharCount(cursor->GetCursorX(), cursor->GetCursorY(), view->GetColNumInView());
    return cursor->ConvertCursors(charCount, view->GetColNumInView(), model->GetStart(), view->YOffset(), view->XOffset(), model->GetTabAdjustment(cursor->GetCursorY(), cursor->GetCursorX())); 
}

