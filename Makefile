CC = g++
CFLAGS = -Wunused-function -O3 -std=c++11 
OBJS = Main.cpp Observer2.cpp TextController.cpp TextView.cpp ECTextViewImp.cpp  TextModel.cpp CommandHistory.cpp Command.cpp Cursor.cpp

all : myeditor

myeditor: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o myeditor

clean: 
	rm myeditor