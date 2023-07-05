
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

class InsertTextCommand : public Command 
{   
public:
    InsertTextCommand(TextView *view, TextModel *model, char chToInsert, Cursor *cursor) :
    view(view),
    model(model),
    chToInsert(chToInsert),
    row(cursor->GetCursorY()),
    col(cursor->GetCursorX()),
    cursor(cursor) {}

    virtual ~InsertTextCommand() {}

    virtual void Execute();

    virtual void UnExecute();

private:
    TextView *view;
    TextModel *model;
    Cursor *cursor;
    char chToInsert;
    int row;
    int col;
};

class RemoveTextCommand : public Command 
{   
public:
    RemoveTextCommand(TextView *view, TextModel *model, Cursor *cursor) :
    view(view),
    model(model),
    row(cursor->GetCursorY()),
    col(cursor->GetCursorX()),
    cursor(cursor),
    ran(false) {}

    virtual ~RemoveTextCommand() {}

    virtual void Execute();

    virtual void UnExecute();

private:
    TextView *view;
    TextModel *model;
    Cursor *cursor;
    const int row;
    int col;
    char chToRemove;
    bool ran;
};


class BreakLineCommand : public Command 
{
public:
    BreakLineCommand(TextView *view, TextModel *model, Cursor *cursor) :
    view(view),
    model(model),
    row(cursor->GetCursorY()), 
    col(cursor->GetCursorX()),
    cursor(cursor) {}

    virtual ~BreakLineCommand() {}

    virtual void Execute();

    virtual void UnExecute();

private:
    TextView *view;
    TextModel *model;
    Cursor *cursor;
    const int row;
    const int col;
};


class MergeLineCommand : public  Command 
{
public:
    MergeLineCommand(TextView *view, TextModel *model, Cursor *cursor) :
    view(view),
    model(model),
    row(cursor->GetCursorY()),
    cursor(cursor),
    ran(false) {}


    virtual ~MergeLineCommand() {}

    virtual void Execute();

    virtual void UnExecute();

private:
    TextView *view;
    TextModel *model;
    Cursor *cursor;
    int row;
    int col;
    bool ran;
};

class CommandSet : public Command 
{
public:
    CommandSet() {}

    virtual ~CommandSet();

    void Execute();

    void UnExecute();

    void ExecuteCmd( Command *pCmd);

    int GetNumCommands() {return commands.size();}

private:
    std::vector< Command *> commands;
};

#endif
 
