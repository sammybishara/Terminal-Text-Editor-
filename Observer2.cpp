#include "Observer2.h"
#include <iostream>

using namespace std;

void AddTextObserver :: Update() 
{
    char ch = ctrl->GetPressedKey(); 
    if ((ch >= ' ' && ch <= '~')  && ctrl->GetMode() == EDIT_MODE) ctrl->AddChar(ch);
}

void RemoveTextObserver :: Update()
{
    if (ctrl->GetPressedKey() == BACKSPACE && ctrl->GetMode() == EDIT_MODE) ctrl->Delete();
}

void MoveCursorHorizonal :: Update()
{
    if (ctrl->GetPressedKey() == ARROW_LEFT) ctrl->MoveLeft();
    else if (ctrl->GetPressedKey() == ARROW_RIGHT) ctrl->MoveRight();
}

void MoveCursorVertical :: Update()
{
    if (ctrl->GetPressedKey() == ARROW_UP) ctrl->MoveUp();
    else if (ctrl->GetPressedKey() == ARROW_DOWN) ctrl->MoveDown();
}

void BreakLine :: Update()
{
    if (ctrl->GetPressedKey() == ENTER && ctrl->GetMode() == EDIT_MODE) ctrl->BreakLine();
}

void ChangeMode :: Update()
{
    char ch = ctrl->GetPressedKey();

    if (ctrl->GetPressedKey() == ESC && ctrl->GetMode() == EDIT_MODE) ctrl->ChangeMode(COMMAND_MODE);
    else if (ch == 'i' && ctrl->GetMode() == COMMAND_MODE) ctrl->ChangeMode(EDIT_MODE);
}

void UndoObserver :: Update()
{
    if (ctrl->GetMode() == COMMAND_MODE && ctrl->GetPressedKey() == CTRL_Z) ctrl->Undo();
}

void RedoObserver :: Update()
{
    if (ctrl->GetMode() == COMMAND_MODE && ctrl->GetPressedKey() == CTRL_Y) ctrl->Redo();
}

void AddLineObserver :: Update()
{
    if (ctrl->GetPressedKey() == CTRL_L ) ctrl->ToggleLineNumbers();
}

void AddBorderObserver :: Update()
{
    if (ctrl->GetPressedKey() == CTRL_B) ctrl->ToggleBorder();
}

void CopyObserver :: Update() 
{
    if (ctrl->GetPressedKey() == CTRL_C && ctrl->GetMode() == COMMAND_MODE) ctrl->Copy();
}

void PasteObserver :: Update()
{
    if (ctrl->GetPressedKey() == CTRL_V && ctrl->GetMode() == COMMAND_MODE) ctrl->Paste();
}