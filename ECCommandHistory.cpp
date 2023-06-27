#include "ECCommandHistory.h"

ECCommandHistory :: ECCommandHistory() : currentIndex(-1)
{
}

ECCommandHistory :: ~ECCommandHistory()
{

    for(unsigned int i =0; i < commandHistory.size(); ++i)
    {
        delete commandHistory[i];
    }
    commandHistory.clear();
    currentIndex = -1;
}

bool ECCommandHistory :: Undo()
{
    if( currentIndex < 0  )
    {
        return false;
    }
    commandHistory[currentIndex]->UnExecute();
    --currentIndex;
    return true;
}

bool ECCommandHistory :: Redo()
{
    if( currentIndex >= (int)commandHistory.size()-1  )
    {
        return false;
    }
    ++currentIndex;
    commandHistory[currentIndex]->Execute();
    return true;
}


void ECCommandHistory :: AddCommand( ECCommand *pCmd )
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