#ifndef TextView_h
#define TextView_h

#include "ECTextViewImp.h"
#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>

class TextView 
{
public:
    TextView();

    virtual ~TextView();

    // Show the view. This would enter a forever loop, until quit is set
    virtual void Show() { TextImp->Show(); }
    
    // Write the text for the entire wiindow including cursor onto console
    // Invoke this function after you make changes to your document.
    // Refreshing entire window for any document update seems excessive; but this is how the code works
    virtual void Refresh() { TextImp->Refresh(); }
    
    // Get the key last pressed. Note: call this after getting a notification from observer
    virtual int GetPressedKey() { return TextImp->GetPressedKey(); }
    
    // Call when you want to quit from the program
    virtual void Quit() { TextImp->Quit(); }

    // Clear out the content of the screen
    virtual void InitRows() { TextImp->InitRows(); }
    
    // Add an entire row to the view
    virtual void AddRow(const std::string &strRow, int row, int colorStart, int numOfLines);
    
    // ADDS an entire set of Rows
    virtual void AddRows(std::vector<std::string> rows, std::vector<int> lineNumbers);

    virtual std::vector<std::string> Embellish(std::vector<std::string> &rows, int screenWidth, std::vector<int> &lineNumbers) { return rows; }

    // Get number of rows in view
    virtual int GetRowNumInView() const { return TextImp->GetRowNumInView(); }
    
    // Get number of columns in view
    virtual int GetColNumInView() const {  return TextImp->GetColNumInView() - 1;}
    
    // Get position of the cursor: x coordinate (horonzontal); position starts from 0
    virtual int GetCursorX() const { return TextImp->GetCursorX(); }
    
    // Get position of the cursor: y coordinate (vertical)
    virtual int GetCursorY() const  { return TextImp->GetCursorY(); }

    // Sets the y position of the cursor 
    virtual void SetCursorY(int pos) { TextImp->SetCursorY(pos); }

    // Sets the x position of the cursor
    virtual void SetCursorX(int pos) { TextImp->SetCursorX(pos); }
    
    // Set the cursor position x and y coordinate
    virtual void SetCursors(int x, int y, int charCount, int start);

    // clears status rows
    virtual void ClearStatusRows() { TextImp->ClearStatusRows(); }
    
    // call to show a status row. A status row consists of two parts: the left message and the right message
    // set fBlackBackground to be true if you want to show a darkened background (for highlight)
    virtual void AddStatusRow( const std::string &statusMsgLeft, const std::string &statusMsgRight, bool fBlackBackground );
    
    // call to change the text color for a segment of row (from colBegin to colEnd)
    virtual void SetColor(int row, int colBegin, int colEnd, TEXT_COLOR clr) {  TextImp->SetColor(row, colBegin, colEnd, clr); }

    // call to clear all color settings
    virtual void ClearColor() { TextImp->ClearColor();}

    // attach observers
    virtual void Attach( ECObserver *pObs) { TextImp->Attach(pObs); }

    // remove observers 
    virtual void Detach(ECObserver *pObs) { TextImp->Detach(pObs); }

    virtual void Notify() { TextImp->Notify();}

    // offset of the cursor on the x axis 
    virtual int XOffset() { return 0;}

    // offset of the cursor on the y axis 
    virtual int YOffset() { return 0; }

    // return the special columns that the view occupies 
    virtual int GetColsOccupied() { return 0; }

    TextView* PreviousView() { return nullptr; }

private:
    ECTextViewImp *TextImp;
    std::set<std::string> wordsToHighlight;
};

// decorator class for special text views 
class TextViewDec : public TextView
{
public:
    TextViewDec(TextView *view) :
    view(view) {}

    virtual ~TextViewDec() { delete view; }

    // Show the view. This would enter a forever loop, until quit is set
    void Show() { view->Show(); }
    
    // Write the text for the entire wiindow including cursor onto console
    // Invoke this function after you make changes to your document.
    // Refreshing entire window for any document update seems excessive; but this is how the code works
    void Refresh() { view->Refresh(); }
    
    // Get the key last pressed. Note: call this after getting a notification from observer
    int GetPressedKey() { return view->GetPressedKey(); }
    
    // Call when you want to quit from the program
    void Quit() { view->Quit(); }

    // Clear out the content of the screen
    void InitRows() { view->InitRows(); }
    
    // Add an entire row to the view
    virtual void AddRow(const std::string &strRow, int row, int colorStart, int numOfLines) 
    {
        view->AddRow(strRow, row, colorStart, numOfLines);
    }
    
    // ADDS an entire set of Rows
    virtual void AddRows(std::vector<std::string> rows, std::vector<int> lineNumbers)
    {
        view->AddRows(rows, lineNumbers);
    }

    std::vector<std::string> Embellish(std::vector<std::string> &rows, int screenWidth, std::vector<int> &lineNumbers) 
    {
        return view->Embellish(rows, screenWidth, lineNumbers);
    }

    // Get number of rows in view
    virtual int GetRowNumInView() const { return view->GetRowNumInView(); }
    
    // Get number of columns in view
    virtual int GetColNumInView() const {  return view->GetColNumInView(); }
    
    // Get position of the cursor: x coordinate (horonzontal); position starts from 0
    int GetCursorX() const { return view->GetCursorX(); }
    
    // Get position of the cursor: y coordinate (vertical)
    int GetCursorY() const  { return view->GetCursorY(); }

    void SetCursorY(int pos) { view->SetCursorY(pos); }

    void SetCursorX(int pos) { view->SetCursorX(pos); }
    
    // Set the cursor position x and y coordinate
    void SetCursors(int x, int y, int charCount, int start) { view->SetCursors(x, y, charCount, start); }

    // clears status rows
    void ClearStatusRows() { view->ClearStatusRows(); }
    
    // call to show a status row. A status row consists of two parts: the left message and the right message
    // set fBlackBackground to be true if you want to show a darkened background (for highlight)
    void AddStatusRow( const std::string &statusMsgLeft, const std::string &statusMsgRight, bool fBlackBackground )
    {
        view->AddStatusRow(statusMsgLeft, statusMsgRight, fBlackBackground);
    }
    
    // call to change the text color for a segment of row (from colBegin to colEnd)
    void SetColor(int row, int colBegin, int colEnd, TEXT_COLOR clr) {  view->SetColor(row, colBegin, colEnd, clr); }

    // call to clear all color settings
    void ClearColor() { view->ClearColor();}

    // attach observers
    void Attach( ECObserver *pObs) { view->Attach(pObs); }

    // remove observers 
    void Detach(ECObserver *pObs) { view->Detach(pObs); }

    void Notify() { view->Notify();}

    TextView* PreviousView() { return view; }

    int XOffset() { return view->XOffset(); }

    int YOffset() { return view->YOffset(); }

    // Returns the number of special columns that are occupied by the view 
    virtual int GetColsOccupied() { return view->GetColsOccupied(); }

private:
    TextView *view;
};

// decorator class to add line numbers to the view 
class LineNumberTextView : public TextViewDec 
{
public:
    LineNumberTextView(TextView *view) :
    TextViewDec(view) {}

    ~LineNumberTextView() {}

    // Add an entire row to the view
    void AddRow(const std::string &strRow, int row, int colorStart, int numOfLines);
    
    // ADDS an entire set of Rows
    void AddRows(std::vector<std::string> rows, std::vector<int> lineNumbers);

    std::vector<std::string> Embellish(std::vector<std::string> &rows, int screenWidth, std::vector<int> &lineNumbers);

    // Get number of rows in view
    int GetRowNumInView() const { return TextViewDec::GetRowNumInView(); }
    
    // Get number of columns in view
    int GetColNumInView() const {  return TextViewDec::GetColNumInView() - 7; }
    
    // Set the cursor position x and y coordinate
    void SetCursors(int x, int y, int charCount, int start);

    int XOffset() { return TextViewDec::XOffset() + 7;}

    int YOffset() { return TextViewDec::YOffset(); }

    // Returns the number of special columns that are occupied by the view 
    int GetColsOccupied() { return TextViewDec::GetColsOccupied() + 7; }
};

// Text View with a border 
class BorderTextView : public TextViewDec
{
public:
    BorderTextView( TextView *view) :
    TextViewDec(view) {}

    ~BorderTextView() {}
    
    // Add an entire row to the view
    void AddRow(const std::string &strRow, int row, int colorStart, int numOfLines);
    
    // ADDS an entire set of Rows
    void AddRows(std::vector<std::string> rows, std::vector<int> lineNumbers);

    std::vector<std::string> Embellish(std::vector<std::string> &rows, int screenWidth, std::vector<int> &lineNumbers);

    // Get number of rows in view
    int GetRowNumInView() const { return TextViewDec::GetRowNumInView() - 2; }
    
    // Get number of columns in view
    int GetColNumInView() const {  return TextViewDec::GetColNumInView() - 4; }

    // Set the cursor position x and y coordinate
    void SetCursors(int x, int y, int charCount, int start);

    int XOffset() { return TextViewDec::XOffset() + 2;}

    int YOffset() { return TextViewDec::YOffset() + 1; }

    // returns the number of special columns that are occupied by the view 
    int GetColsOccupied() { return TextViewDec::GetColsOccupied() + 4; }

private:
    TextView *view;
};

#endif







