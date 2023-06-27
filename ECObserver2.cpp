#include "ECObserver2.h"
#include <iostream>

using namespace std;

void AddTextObserver :: Update() 
{
    char ch = static_cast<char>(ctrl->GetPressedKey()); 
    
    if ((ch >= ' ' && ch <= '~' ) && ctrl->getMode() == EDIT_MODE) ctrl->addChar(ch);
}

void RemoveTextObserver :: Update()
{
    if (ctrl->GetPressedKey() == BACKSPACE && ctrl->getMode() == EDIT_MODE) ctrl->Delete();
}

void MoveCursorHorizonal :: Update()
{
    if (ctrl->GetPressedKey() == ARROW_LEFT) ctrl->moveLeft();
    else if (ctrl->GetPressedKey() == ARROW_RIGHT) ctrl->moveRight();
}

void MoveCursorVertical :: Update()
{
    if (ctrl->GetPressedKey() == ARROW_UP) ctrl->moveUp();
    else if (ctrl->GetPressedKey() == ARROW_DOWN) ctrl->moveDown();
}

void BreakLine :: Update()
{
    if (ctrl->GetPressedKey() == ENTER && ctrl->getMode() == EDIT_MODE) ctrl->breakLine();
}

void ChangeMode :: Update()
{
    char ch = ctrl->GetPressedKey();

    if (ctrl->GetPressedKey() == ESC && ctrl->getMode() == EDIT_MODE) ctrl->changeMode(COMMAND_MODE);
    else if (ch == 'i' && ctrl->getMode() == COMMAND_MODE) ctrl->changeMode(EDIT_MODE);
}

void UndoObserver :: Update()
{
    if (ctrl->getMode() == COMMAND_MODE && ctrl->GetPressedKey() == CTRL_Z) ctrl->Undo();
}

void RedoObserver :: Update()
{
    if (ctrl->getMode() == COMMAND_MODE && ctrl->GetPressedKey() == CTRL_Y) ctrl->Redo();
}


void AddLineObserver :: Update()
{
    if (ctrl->GetPressedKey() == CTRL_L ) ctrl->ToggleLineNumbers();
}

void AddBorderObserver :: Update()
{
    if (ctrl->GetPressedKey() == CTRL_B) ctrl->ToggleBorder();
}

//TODO
void ResizeObserver :: Update()
{
}

