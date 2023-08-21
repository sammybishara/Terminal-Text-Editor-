
#ifndef OBSERVER2_H
#define OBSERVER2_H


#include "ECObserver.h"
#include "TextController.h"

// observer class for adding text
class AddTextObserver : public ECObserver
{

public:
    AddTextObserver(TextCtrl *ctrl) : 
    ctrl(ctrl) {}

    virtual ~AddTextObserver() {}

    virtual void Update();

private:
    TextCtrl *ctrl;
};

// observer class for removing text
class RemoveTextObserver : public ECObserver 
{
public:
    RemoveTextObserver(TextCtrl *ctrl):
    ctrl(ctrl) {}
    
    virtual ~RemoveTextObserver() {}
        
    virtual void Update();

private:
    TextCtrl *ctrl;
};
// observer class for moving cursor horizontal
class MoveCursorHorizonal : public ECObserver
{
public:
    MoveCursorHorizonal(TextCtrl *ctrl) :
    ctrl(ctrl) {}

    virtual ~MoveCursorHorizonal(){}

    virtual void Update();

private:
    TextCtrl *ctrl;
};

// observer class for moving cursor vertical
class MoveCursorVertical : public ECObserver
{
public:
    MoveCursorVertical(TextCtrl *ctrl) :
    ctrl(ctrl) {}

    virtual ~MoveCursorVertical() {}

    virtual void Update();

private:
    TextCtrl *ctrl;
};

// observer class for breaking a line
class BreakLine : public ECObserver
{
public:
    BreakLine(TextCtrl *ctrl) :
    ctrl(ctrl) {}

    virtual ~BreakLine() {}

    virtual void Update();

private:
    TextCtrl *ctrl;
};

// observer class for changing mode between edit and command mode 
class ChangeMode : public ECObserver
{
public: 
    ChangeMode(TextCtrl *ctrl) :
    ctrl(ctrl) {}

    virtual ~ChangeMode() {}

    virtual void Update();

private:
    TextCtrl *ctrl;
};


// Observer for undoing commands
class UndoObserver : public ECObserver
{
public:
    UndoObserver(TextCtrl *ctrl) :
    ctrl(ctrl) {}

    virtual ~UndoObserver() {}


    virtual void Update();

private:
    TextCtrl *ctrl;
};


//observer for redoing commands
class RedoObserver : public ECObserver
{
public: 
    RedoObserver(TextCtrl *ctrl) :
    ctrl(ctrl) {}

    virtual ~RedoObserver() {}

    virtual void Update();

private:
    TextCtrl *ctrl;
};


class AddLineObserver : public ECObserver
{
public:
    AddLineObserver(TextCtrl *ctrl) :
    ctrl(ctrl) {}

    virtual ~AddLineObserver() {}

    virtual void Update();

private:
    TextCtrl *ctrl;
};

class AddBorderObserver : public ECObserver
{
public:
    AddBorderObserver(TextCtrl *ctrl) :
    ctrl(ctrl) {}

    virtual ~AddBorderObserver() {}

    virtual void Update();

private:
    TextCtrl *ctrl;
};

// observer that calls the copy method of the controller
// only coppies when in command mode 
class CopyObserver : public ECObserver
{
public:
    CopyObserver(TextCtrl *ctrl) :
    ctrl(ctrl) {}

    virtual ~CopyObserver() {}

    virtual void Update();

private:
    TextCtrl *ctrl;
};

// Observer for pasting the row that is currently coppied 
class PasteObserver : public ECObserver
{
public:
    PasteObserver(TextCtrl *ctrl) :
    ctrl(ctrl) {}

    virtual ~PasteObserver() {}

    virtual void Update();

private:
    TextCtrl *ctrl;
};

#endif