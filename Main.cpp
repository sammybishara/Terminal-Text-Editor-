
#include <iostream>
#include "Observer2.h"
#include "ECTextViewImp.h"

using namespace  std;


int main(int argc, char *argv[])
{
    if (argc < 2) 
    {
        cout << "Error: no file name given!" << endl;
        return 1;
    }

    std::string filename((argv[1]));

    TextView *wnd = new TextView();
    TextModel model(filename);
    TextCtrl controller(wnd, &model, filename);

    // observer for adding characters
    AddTextObserver addText(&controller);
    wnd->Attach(&addText);

    //observer for deleting characters
    RemoveTextObserver removeTxt(&controller);
    wnd->Attach(&removeTxt);

    // observer for horizonal cursor movement
    MoveCursorHorizonal horizonalMovement(&controller);
    wnd->Attach(&horizonalMovement);

    // observer for vertical cursor movement
    MoveCursorVertical vertialMovement(&controller);
    wnd->Attach(&vertialMovement);

    // observer for breaking a line
    BreakLine bl(&controller);
    wnd->Attach(&bl);

    // observer for changing between command and edit mode 
    ChangeMode change(&controller);
    wnd->Attach(&change);

    // observer for undoing commands
    UndoObserver undo(&controller);
    wnd->Attach(&undo);

    RedoObserver redo(&controller);
    wnd->Attach(&redo);

    AddLineObserver addL(&controller);
    wnd->Attach(&addL);

    AddBorderObserver addB(&controller);
    wnd->Attach(&addB);

    CopyObserver copy(&controller);
    wnd->Attach(&copy);

    // intializes observer for pasting
    PasteObserver paste(&controller);
    wnd->Attach(&paste);

    controller.Show();

    return 0;
}










