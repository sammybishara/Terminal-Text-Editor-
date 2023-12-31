
#ifndef TEXTCONTROLLER_H
#define TEXTCONTROLLER_H

#include "TextView.h"
#include "TextModel.h"
#include "CommandHistory.h"
#include "Command.h"
#include <fstream>
#include <string>
#include "Cursor.h"
#include <utility>

class ECTextCtrl;


enum Mode 
{
    COMMAND_MODE,
    EDIT_MODE
};

class TextCtrl 
{
public:
    TextCtrl(TextView *textView, TextModel *textModel, const std::string filename);
   
    virtual ~TextCtrl();

    // controller recieves key from view and returns it
    int GetPressedKey() {return view->GetPressedKey();}

    // shows the display
    void Show(){ view->Show();}

    // add a character
    void AddChar(const char ch);

    // Refreshs the cursors
    void RefreshText();

    // Refreshes the text 
    void RefreshCursor();

    // function that decides whether to delete a character or merge a line
    void Delete(); 

    // function for coppying the current row of the cursor 
    void Copy();

    // function for pasting the copied row 
    void Paste();

    // moves the cursour left
    void MoveLeft();

    // moves the cursor right
    void MoveRight();

    // moves the cursor down
    void MoveDown();

    // moves the cursor up
    void MoveUp();

    // splits the current Line into 2
    void BreakLine();
    // changes current mode to either command mode or edit mode 
    void ChangeMode(int newMode);

    int GetMode() {return mode;}

    // undo last command
    void Undo();

    // redo last command that was undone 
    void Redo();

    // Toggles the line numbers
    void ToggleLineNumbers();

    // Toggles the boarders
    void ToggleBorder();

    // Calls the cursor object to convert the document cursors to on screen cursors
    std::pair<int, int> ConvertCursor();

private:
    // removes a char
    void RemoveChar();
    // merges the current line with the line directly before it 
    void MergeLine();
    void ReadFromFile();
    // scrolls the page up
    void ScrollUp();
    // scrolls the page down
    void ScrollDown(bool nextLine);

    TextView *view;
    TextModel *model;
    CommandHistory *commandH;
    CommandSet *cmdSet;
    Cursor *cursor;
    int mode;
    std::string file;
    std::string copiedLine;
    bool lineNumbers;
    bool borders;
};

#endif
