#ifndef CommandHistory_h
#define CommandHistory_h

#include <vector>
#include "Command.h"

// keeps history of all commands executed, suports redo and undo
class CommandHistory

{
public:
    CommandHistory();
    virtual ~CommandHistory();
    bool Undo();
    bool Redo();
    void AddCommand(Command *pCmd);
    
private:
    std::vector<Command *> commandHistory;
    int currentIndex;
};

#endif