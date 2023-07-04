
#ifndef ECOBSERVER2_H
#define ECOBSERVER2_H


#include "ECObserver.h"
#include "ECTextController.h"

// observer class for adding text
class AddTextObserver : public ECObserver
{

public:
    AddTextObserver(ECTextCtrl *ctrl) : 
    ctrl(ctrl) {}

    virtual ~AddTextObserver() {}

    virtual void Update();

private:
    ECTextCtrl *ctrl;
};

// observer class for removing text
class RemoveTextObserver : public ECObserver 
{
public:
    RemoveTextObserver(ECTextCtrl *ctrl):
    ctrl(ctrl) {}
    
    virtual ~RemoveTextObserver() {}
        
    virtual void Update();
private:
    ECTextCtrl *ctrl;
};
// observer class for moving cursor horizontal
class MoveCursorHorizonal : public ECObserver
{
public:
    MoveCursorHorizonal(ECTextCtrl *ctrl) :
    ctrl(ctrl) {}

    virtual ~MoveCursorHorizonal(){}

    virtual void Update();

private:
    ECTextCtrl *ctrl;
};

// observer class for moving cursor vertical
class MoveCursorVertical : public ECObserver
{
public:
    MoveCursorVertical(ECTextCtrl *ctrl) :
    ctrl(ctrl) {}

    virtual ~MoveCursorVertical() {}

    virtual void Update();

private:
    ECTextCtrl *ctrl;
};

// observer class for breaking a line
class BreakLine : public ECObserver
{
public:
    BreakLine(ECTextCtrl *ctrl) :
    ctrl(ctrl) {}

    virtual ~BreakLine() {}

    virtual void Update();

private:
    ECTextCtrl *ctrl;
};

// observer class for changing mode between edit and command mode 
class ChangeMode : public ECObserver
{
public: 
    ChangeMode(ECTextCtrl *ctrl) :
    ctrl(ctrl) {}

    virtual ~ChangeMode() {}

    virtual void Update();

private:
    ECTextCtrl *ctrl;
};


// Observer for undoing commands
class UndoObserver : public ECObserver
{
public:
    UndoObserver(ECTextCtrl *ctrl) :
    ctrl(ctrl) {}

    virtual ~UndoObserver() {}


    virtual void Update();

private:
    ECTextCtrl *ctrl;
};


//observer for redoing commands
class RedoObserver : public ECObserver
{
public: 
    RedoObserver(ECTextCtrl *ctrl) :
    ctrl(ctrl) {}

    virtual ~RedoObserver() {}

    virtual void Update();

private:
    ECTextCtrl *ctrl;
};


class AddLineObserver : public ECObserver
{
public:
    AddLineObserver(ECTextCtrl *ctrl) :
    ctrl(ctrl) {}

    virtual ~AddLineObserver() {}

    virtual void Update();

private:
    ECTextCtrl *ctrl;
};

class AddBorderObserver : public ECObserver
{
public:
    AddBorderObserver(ECTextCtrl *ctrl) :
    ctrl(ctrl) {}

    virtual ~AddBorderObserver() {}

    virtual void Update();

private:
    ECTextCtrl *ctrl;
};

class ResizeObserver : public ECObserver
{
public:
    ResizeObserver(ECTextCtrl *ctrl) :
    ctrl(ctrl) {}

    virtual ~ResizeObserver() {}

    virtual void Update();

private:
    ECTextCtrl *ctrl;
};

// observer that calls the copy method of the controller
// only coppies when in command mode 
class CopyObserver : public ECObserver
{
public:
    CopyObserver(ECTextCtrl *ctrl) :
    ctrl(ctrl) {}

    virtual ~CopyObserver() {}

    virtual void Update();

private:
    ECTextCtrl *ctrl;
};
#endif