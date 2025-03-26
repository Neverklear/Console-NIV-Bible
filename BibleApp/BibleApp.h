#ifndef BIBLEAPP_H
#define BIBLEAPP_H

#include <iostream>
#include <string>
#include "sqlite_modern_cpp.h"

// ANSI escape codes declarations for styling output
extern const std::string RESET;
extern const std::string BOLD;
extern const std::string YELLOW;
extern const std::string CYAN;
extern const std::string GREEN;

// Function declarations
void displayHeader();
void intro();
void pauseForPagination();
void searchVerse();
void searchWord();
void searchPhrase();
void searchChapter();
void searchBook();
void menu();

#endif // BIBLEAPP_H
