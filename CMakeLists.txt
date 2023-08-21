cmake_minimum_required(VERSION 3.0)
project(TerminalTextEditor)

# Sets the version of c++ to use 
set(CMAKE_CXX_STANDARD 11)

# Add source files
add_executable(editor src/Command.cpp src/CommandHistory.cpp src/Cursor.cpp src/ECTextViewImp.cpp src/Main.cpp src/Observer2.cpp src/TextController.cpp src/TextModel.cpp src/TextView.cpp)

# include header files in the include directory
target_include_directories(editor PUBLIC include)
