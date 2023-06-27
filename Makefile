CC = g++
CFLAGS = -Wunused-function -O3 -std=c++11 
OBJS = ECEditorTest.cpp ECObserver2.cpp ECTextController.cpp ECTextView.cpp ECTextViewImp.cpp  ECTextModel.cpp ECCommandHistory.cpp ECCommand.cpp

all : myeditor

myeditor: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o myeditor

clean: 
	rm myeditor