
#ifndef ECTextController_h
#define ECTextController_h

#include "ECTextView.h"
#include "ECTextModel.h"
#include "ECCommandHistory.h"
#include "ECCommand.h"
#include <fstream>
#include <string>
#include "ECCursor.h"

class ECTextCtrl;


enum Mode 
{
    COMMAND_MODE,
    EDIT_MODE
};

class ECTextCtrl 
{
public:
    ECTextCtrl(ECTextView *textView, ECTextModel *textModel, const std::string filename);
   
    virtual ~ECTextCtrl();

    // controller recieves key from view and returns it
    int GetPressedKey() {return view->GetPressedKey();}

    // shows the display
    void Show(){ view->Show();}

    // add a character
    void addChar(char ch);

    // Refreshs the cursors
    void RefreshText();

    // Refreshes the text 
    void RefreshCursor();

    // function that decides whether to delete a character or merge a line
    void Delete(); 

    // moves the cursour left
    void moveLeft();

    // moves the cursor right
    void moveRight();

    // moves the cursor down
    void moveDown();

    // moves the cursor up
    void moveUp();

    // splits the current Line into 2
    void breakLine();
    // changes current mode to either command mode or edit mode 
    void changeMode(int newMode);

    int getMode() {return mode;}

    // undo last command
    void Undo() { commandH->Undo(); }

    // redo last command that was undone 
    void Redo() { commandH->Redo();}

    void ToggleLineNumbers();

    void ToggleBorder();

private:
    // removes a char
    // method is private since delete will call it if it decides delete is possible 
    void removeChar();
    // merges the current line with the line directly before it 
    void mergeLine();

    void ReadFromFile();

    ECTextView *view;
    ECTextModel *model;
    ECCommandHistory *commandH;
    ECCommandSet *cmdSet;
    Cursor *cursor;
    int mode;
    std::string file;
    bool lineNumbers;
    bool borders;
};

#endif
