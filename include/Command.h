
#ifndef Command_h
#define Command_h

#include "TextView.h"
#include "TextModel.h"
#include "Cursor.h"

// command design pattern
class Command
{
public:
    virtual ~Command() {}
    virtual void Execute() = 0;
    virtual void UnExecute() = 0;
};

// command to insert a character 
class InsertTextCommand : public Command 
{   
public:
    InsertTextCommand(TextView* const view, TextModel* const model, const char chToInsert, Cursor* const cursor) :
    view(view),
    model(model),
    chToInsert(chToInsert),
    row(cursor->GetCursorY()),
    col(cursor->GetCursorX()),
    cursor(cursor) {}

    virtual ~InsertTextCommand() {}

    void Execute();

    void UnExecute();

private:
    void AdjustCursor();
    TextView* const view;
    TextModel* const model;
    Cursor* const cursor;
    const char chToInsert;
    const int row;
    const int col;
};

class RemoveTextCommand : public Command 
{   
public:
    RemoveTextCommand(TextView* const view, TextModel* const model, Cursor* const cursor) :
    view(view),
    model(model),
    row(cursor->GetCursorY()),
    col(cursor->GetCursorX()),
    cursor(cursor),
    ran(false) {}

    ~RemoveTextCommand() {}

    void Execute();

    void UnExecute();

private:
    void AdjustCursor();
    TextView* const view;
    TextModel* const model;
    Cursor* const cursor;
    const int row;
    const int col;
    char chToRemove;
    bool ran;
};


class BreakLineCommand : public Command 
{
public:
    BreakLineCommand(TextView* const view, TextModel* const model, Cursor* const cursor) :
    view(view),
    model(model),
    row(cursor->GetCursorY()), 
    col(cursor->GetCursorX()),
    cursor(cursor) {}

    ~BreakLineCommand() {}

    void Execute();

    void UnExecute();

private:
    void AdjustCursor();
    TextView* const view;
    TextModel* const model;
    Cursor* const cursor;
    const int row;
    const int col;
};


class MergeLineCommand : public Command 
{
public:
    MergeLineCommand(TextView* const view, TextModel* const model, Cursor* const cursor) :
    view(view),
    model(model),
    row(cursor->GetCursorY()),
    cursor(cursor),
    ran(false) {}

    ~MergeLineCommand() {}

    void Execute();

    void UnExecute();

private:
    void AdjustCursor();
    TextView* const view;
    TextModel* const model;
    Cursor* const cursor;
    const int row;
    int col;
    bool ran;
};

class PasteCommand : public Command
{
public:
    PasteCommand(TextView* const view, TextModel* const model, Cursor* const cursor, const std::string strToPaste) :
    view(view),
    model(model),
    strToPaste(strToPaste),
    cursor(cursor),
    row(cursor->GetCursorY()),
    col(cursor->GetCursorX()) {}

    virtual ~PasteCommand() {}

    virtual void Execute();

    virtual void UnExecute();

private:
    void AdjustCursor();
    TextView* const view;
    TextModel* const model;
    Cursor* const cursor;
    const int row;
    const int col;
    const std::string strToPaste;
};

class CommandSet : public Command 
{
public:
    CommandSet() {}

    virtual ~CommandSet();

    void Execute();

    void UnExecute();

    void Refresh() {}

    void ExecuteCmd( Command *pCmd);

    int GetNumCommands() {return commands.size();}

private:
    std::vector< Command *> commands;
};

#endif
 
