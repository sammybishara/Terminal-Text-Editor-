#include "Command.h"

void InsertTextCommand :: Execute()
{
    // adds character to the new model, clears view and updates it
    model->addChar(row, col, chToInsert, view->GetColNumInView(), view->GetCursorY());
    // std::vector<std::string> rows = model->ParseRows(view->GetColNumInView(), view->GetRowNumInView());

    std::pair<std::vector<std::string>, std::vector<int> > pair = model->ParseRows(view->GetColNumInView(), view->GetRowNumInView());
    std::vector<std::string> rows = pair.first;
    std::vector<int> lineNumbers = pair.second;
    view->AddRows(rows, lineNumbers);
}

// removes the character that was inserted
void InsertTextCommand :: UnExecute()
{
    model->removeChar(row, col);
    // std::vector<std::string> rows = model->ParseRows(view->GetColNumInView(), view->GetRowNumInView());
    std::pair<std::vector<std::string>, std::vector<int> > pair = model->ParseRows(view->GetColNumInView(), view->GetRowNumInView());
    std::vector<std::string> rows = pair.first;   
    std::vector<int> lineNumbers = pair.second;
    view->AddRows(rows, lineNumbers);
    
    // if y is in the current row and x is greater than size of current row, change x to size of the current row
    if (cursor->GetCursorY() == row && cursor->GetCursorX() > model->GetRow(row).size()) cursor->SetCursorX(model->GetRow(row).size());
    int charCount = model->GetCharCount(cursor->GetCursorX(), cursor->GetCursorY(), view->GetColNumInView());
    view->SetCursors(cursor->GetCursorX(), cursor->GetCursorY(), charCount, model->GetStart());
}

// saves old character to be removed  and removes char and updates view with current text  
void RemoveTextCommand :: Execute()
{
    chToRemove = model->GetRow(row)[col - 1];
    model->removeChar(row, col - 1);

    // std::vector<std::string> rows = model->ParseRows(view->GetColNumInView(), view->GetRowNumInView());
    std::pair<std::vector<std::string>, std::vector<int> > pair = model->ParseRows(view->GetColNumInView(), view->GetRowNumInView());
    std::vector<std::string> rows = pair.first;
    std::vector<int> lineNumbers = pair.second;
    view->AddRows(rows, lineNumbers);

    // if this command is being redone and y is in the current row and x is greater than size of current row, change x to size of the row 
    if (ran == true && cursor->GetCursorY() == row && cursor->GetCursorX() > model->GetRow(row).size()) cursor->SetCursorX(model->GetRow(row).size());
    else if (ran == false) ran = true;
}

// undo method that inserts the character that was removed 
void RemoveTextCommand :: UnExecute()
{
    model->addChar(row, col - 1, chToRemove, view->GetColNumInView(), view->GetCursorY());
    // std::vector<std::string> rows = model->ParseRows(view->GetColNumInView(), view->GetRowNumInView());
    std::pair<std::vector<std::string>, std::vector<int> > pair = model->ParseRows(view->GetColNumInView(), view->GetRowNumInView());
    std::vector<std::string> rows = pair.first;
    std::vector<int> lineNumbers = pair.second;
    view->AddRows(rows, lineNumbers);
}

// breaks the line and updates the model 
void BreakLineCommand :: Execute()
{
    model->breakLine(row, col);
    // std::vector<std::string> rows = model->ParseRows(view->GetColNumInView(), view->GetRowNumInView());
    std::pair<std::vector<std::string>, std::vector<int> > pair = model->ParseRows(view->GetColNumInView(), view->GetRowNumInView());
    std::vector<std::string> rows = pair.first;
    std::vector<int> lineNumbers = pair.second;
    view->AddRows(rows, lineNumbers); 
}

// redo command that merges the broken line 
void BreakLineCommand :: UnExecute()
{
    // if cursor is in the row that is about to be undone, move it to the size of the previous row before undoing 
    if (cursor->GetCursorY() == row + 1)
    {
        cursor->SetCursorY(row);
        cursor->SetCursorX(model->GetRow(cursor->GetCursorY()).size());
    }

    int charCount = model->GetCharCount(cursor->GetCursorX(), cursor->GetCursorY(), view->GetColNumInView());
    view->SetCursors(cursor->GetCursorX(), cursor->GetCursorY(), charCount, model->GetStart());
    
    model->mergeline(row + 1);
    // std::vector<std::string> rows = model->ParseRows(view->GetColNumInView(), view->GetRowNumInView());
    std::pair<std::vector<std::string>, std::vector<int> > pair = model->ParseRows(view->GetColNumInView(), view->GetRowNumInView());
    std::vector<std::string> rows = pair.first;
    std::vector<int> lineNumbers = pair.second;
    view->AddRows(rows, lineNumbers);
}


void MergeLineCommand :: Execute()
{
    // if function was already ran once check if it is in the current row before merging, if it is move it to the end of the previous row 
    if (ran == true && cursor->GetCursorY() == row)
    {
        cursor->SetCursorY(row - 1);
        cursor->SetCursorX(model->GetRow(cursor->GetCursorY()).size());
    }
    else if (ran == false) ran = true;

    col = model->GetRow(row - 1).size();
    model->mergeline(row);

    // std::vector<std::string> rows = model->ParseRows(view->GetColNumInView(), view->GetRowNumInView());
    std::pair<std::vector<std::string>, std::vector<int> > pair = model->ParseRows(view->GetColNumInView(), view->GetRowNumInView());
    std::vector<std::string> rows = pair.first;
    std::vector<int> lineNumbers;
    view->AddRows(rows, lineNumbers);
}

void MergeLineCommand :: UnExecute()
{
    model->breakLine(row - 1, col);

    // std::vector<std::string> rows = model->ParseRows(view->GetColNumInView(), view->GetRowNumInView());
    std::pair<std::vector<std::string>, std::vector<int> > pair = model->ParseRows(view->GetColNumInView(), view->GetRowNumInView());
    std::vector<std::string> rows = pair.first;
    std::vector<int> lineNumbers = pair.second;
    view->AddRows(rows, lineNumbers);
}

void PasteCommand :: Execute()
{
    model->Paste(strToPaste, col, row);
    std::pair<std::vector<std::string>, std::vector<int> > pair = model->ParseRows(view->GetColNumInView(), view->GetRowNumInView());
    view->AddRows(pair.first, pair.second);
}

void PasteCommand :: UnExecute()
{
    model->RemoveRow(col, row, strToPaste.size());
    auto pair = model->ParseRows(view->GetColNumInView(), view->GetRowNumInView());
    view->AddRows(pair.first, pair.second);
}

CommandSet :: ~CommandSet()
{  
    for (unsigned int i = 0; i < commands.size(); ++i) delete commands[i];
    commands.clear();
}

// Executes all commands from beginning to end 
void CommandSet :: Execute()
{   
    for (auto command : commands) command->Execute();
}

// redos each command from back to front 
void CommandSet :: UnExecute()
{
    for (auto it = commands.rbegin(); it != commands.rend(); it++) (*it)->UnExecute();
}

// adds a new command to the set of commands 
void CommandSet :: ExecuteCmd(Command *pCmd)
{
    pCmd->Execute();
    commands.push_back(pCmd);
}