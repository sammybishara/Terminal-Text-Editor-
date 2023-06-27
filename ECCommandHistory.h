#ifndef ECCommandHistory_h
#define ECCommandHistory_h

#include <vector>
#include "ECCommand.h"

// keeps history of all commands executed, suports redo and undo
class ECCommandHistory

{
public:
    ECCommandHistory();
    virtual ~ECCommandHistory();
    bool Undo();
    bool Redo();
    void AddCommand(ECCommand *pCmd);
    
private:
    std::vector<ECCommand *> commandHistory;
    int currentIndex;
};

#endif