#include "CommandHistory.h"

CommandHistory :: CommandHistory() : currentIndex(-1)
{
}

CommandHistory :: ~CommandHistory()
{

    for(unsigned int i =0; i < commandHistory.size(); ++i)
    {
        delete commandHistory[i];
    }
    commandHistory.clear();
    currentIndex = -1;
}

bool CommandHistory :: Undo()
{
    if( currentIndex < 0  )
    {
        return false;
    }
    commandHistory[currentIndex]->UnExecute();
    --currentIndex;
    return true;
}

bool CommandHistory :: Redo()
{
    if( currentIndex >= (int)commandHistory.size()-1  )
    {
        return false;
    }
    ++currentIndex;
    commandHistory[currentIndex]->Execute();
    return true;
}


void CommandHistory :: AddCommand( Command *pCmd )
{
    // clear up all cmds from current pos to end
    if( currentIndex >= -1 )
    {
        int szList = commandHistory.size();
        for(unsigned int i=currentIndex+1; i<szList; ++i)
        {
            delete commandHistory.back();
            commandHistory.pop_back();
        }
    }
    commandHistory.push_back(pCmd);
    ++currentIndex;
}