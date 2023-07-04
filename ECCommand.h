
#ifndef ECCommand_h
#define ECCommand_h

#include "TextView.h"
#include "ECTextModel.h"
#include "ECCursor.h"

// command design pattern
class ECCommand
{
public:
    virtual ~ECCommand() {}
    virtual void Execute() = 0;
    virtual void UnExecute() = 0;
};

class InsertTextCommand : public ECCommand
{   
public:
    InsertTextCommand(TextView *view, ECTextModel *model, char chToInsert, Cursor *cursor) :
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
    ECTextModel *model;
    Cursor *cursor;
    char chToInsert;
    int row;
    int col;
};

class RemoveTextCommand : public ECCommand
{   
public:
    RemoveTextCommand(TextView *view, ECTextModel *model, Cursor *cursor) :
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
    ECTextModel *model;
    Cursor *cursor;
    const int row;
    int col;
    char chToRemove;
    bool ran;
};


class BreakLineCommand : public ECCommand
{
public:
    BreakLineCommand(TextView *view, ECTextModel *model, Cursor *cursor) :
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
    ECTextModel *model;
    Cursor *cursor;
    const int row;
    const int col;
};


class MergeLineCommand : public ECCommand 
{
public:
    MergeLineCommand(TextView *view, ECTextModel *model, Cursor *cursor) :
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
    ECTextModel *model;
    Cursor *cursor;
    int row;
    int col;
    bool ran;
};

class ECCommandSet : public ECCommand
{
public:
    ECCommandSet() {}

    virtual ~ECCommandSet();

    void Execute();

    void UnExecute();

    void ExecuteCmd(ECCommand *pCmd);

    int GetNumCommands() {return commands.size();}

private:
    std::vector<ECCommand *> commands;
};

#endif
 
