#include "BibleApp.h"
#include <limits>

// ANSI escape codes definitions
const std::string RESET = "\033[0m";
const std::string BOLD = "\033[1m";
const std::string YELLOW = "\033[33m";
const std::string CYAN = "\033[36m";
const std::string GREEN = "\033[32m";

// Displays a decorative header with a warm welcome message.
void displayHeader() {
    std::cout << BOLD << YELLOW;
    std::cout << "=======================================" << std::endl;
    std::cout << "   Welcome to the Bible App" << std::endl;
    std::cout << "   May peace and wisdom be with you" << std::endl;
    std::cout << "=======================================" << std::endl;
    std::cout << RESET << std::endl;
}

// Displays the main introduction and menu header.
void intro() {
    displayHeader();
    std::cout << CYAN << "Please select an option:" << RESET << std::endl;
    std::cout << "1. Search for a verse" << std::endl;
    std::cout << "2. Search for a word" << std::endl;
    std::cout << "3. Search for a phrase" << std::endl;
    std::cout << "4. Search for a chapter" << std::endl;
    std::cout << "5. Search for a book" << std::endl << std::endl;
}

// Helper function to pause output for pagination.
void pauseForPagination() {
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void searchVerse() {
    std::cout << "Please enter the book name" << std::endl;
    std::string book;
    std::cin >> book;
    std::cout << "Please enter the chapter number" << std::endl;
    int chapter;
    std::cin >> chapter;
    std::cout << "Please enter the verse number" << std::endl;
    int verse;
    std::cin >> verse;

    std::string dbFile = "BibleData.db";
    try {
        sqlite::database db(dbFile);
        std::string query = "SELECT v.text FROM verses v JOIN Books b ON v.book_id = b.id "
            "WHERE b.name = '" + book + "' AND v.chapter = " + std::to_string(chapter) +
            " AND v.verse = " + std::to_string(verse);
        for (auto row : db << query) {
            std::string verseText;
            row >> verseText;
            std::cout << GREEN << verseText << RESET << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "SQLite exception: " << e.what() << std::endl;
    }
}

void searchWord() {
    std::cout << "Please enter the word you would like to search for" << std::endl;
    std::string word;
    std::cin >> word;

    std::string dbFile = "BibleData.db";
    try {
        sqlite::database db(dbFile);
        std::string query = "SELECT b.name, v.chapter, v.verse, v.text FROM verses v "
            "JOIN Books b ON v.book_id = b.id "
            "WHERE v.text LIKE '%" + word + "%' "
            "ORDER BY b.name, v.chapter, v.verse";
        int lineCount = 0;
        const int pageSize = 5;
        for (auto row : db << query) {
            std::string book;
            int chapter, verse;
            std::string verseText;
            row >> book >> chapter >> verse >> verseText;
            std::cout << GREEN << book << " " << chapter << ":" << verse << " - "
                << verseText << RESET << std::endl << std::endl;
            lineCount++;
            if (lineCount % pageSize == 0) {
                pauseForPagination();
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "SQLite exception: " << e.what() << std::endl;
    }
}

void searchPhrase() {
    std::cout << "Please enter the phrase you would like to search for" << std::endl;
    std::string phrase;
    std::cin.ignore(); // Clear leftover newline
    std::getline(std::cin, phrase);

    std::string dbFile = "BibleData.db";
    try {
        sqlite::database db(dbFile);
        std::string query = "SELECT b.name, v.chapter, v.verse, v.text FROM verses v "
            "JOIN Books b ON v.book_id = b.id "
            "WHERE v.text LIKE '%" + phrase + "%' "
            "ORDER BY b.name, v.chapter, v.verse";
        int lineCount = 0;
        const int pageSize = 5;
        for (auto row : db << query) {
            std::string book;
            int chapter, verse;
            std::string verseText;
            row >> book >> chapter >> verse >> verseText;
            std::cout << GREEN << book << " " << chapter << ":" << verse << " - "
                << verseText << RESET << std::endl << std::endl;
            lineCount++;
            if (lineCount % pageSize == 0) {
                pauseForPagination();
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "SQLite exception: " << e.what() << std::endl;
    }
}

void searchChapter() {
    std::cout << "Please enter the book name" << std::endl;
    std::string book;
    std::cin >> book;
    std::cout << "Please enter the chapter number" << std::endl;
    int chapter;
    std::cin >> chapter;

    std::string dbFile = "BibleData.db";
    try {
        sqlite::database db(dbFile);
        std::string query = "SELECT v.verse, v.text FROM verses v "
            "JOIN Books b ON v.book_id = b.id "
            "WHERE b.name = '" + book + "' AND v.chapter = " + std::to_string(chapter) +
            " ORDER BY v.verse";
        int lineCount = 0;
        const int pageSize = 5;
        for (auto row : db << query) {
            int verse;
            std::string verseText;
            row >> verse >> verseText;
            std::cout << GREEN << "Verse " << verse << ": " << verseText << RESET << std::endl << std::endl;
            lineCount++;
            if (lineCount % pageSize == 0) {
                pauseForPagination();
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "SQLite exception: " << e.what() << std::endl;
    }
}

void searchBook() {
    std::cout << "Please enter the book name" << std::endl;
    std::string book;
    std::cin >> book;

    std::string dbFile = "BibleData.db";
    try {
        sqlite::database db(dbFile);
        std::string query = "SELECT v.chapter, v.verse, v.text FROM verses v "
            "JOIN Books b ON v.book_id = b.id "
            "WHERE b.name = '" + book + "' "
            "ORDER BY v.chapter, v.verse";
        int lineCount = 0;
        const int pageSize = 5;
        for (auto row : db << query) {
            int chapter, verse;
            std::string verseText;
            row >> chapter >> verse >> verseText;
            std::cout << GREEN << "Chapter " << chapter << ", Verse " << verse << ": "
                << verseText << RESET << std::endl << std::endl;
            lineCount++;
            if (lineCount % pageSize == 0) {
                pauseForPagination();
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "SQLite exception: " << e.what() << std::endl;
    }
}

void menu() {
    int choice;
    std::cin >> choice;
    switch (choice) {
    case 1:
        searchVerse();
        break;
    case 2:
        searchWord();
        break;
    case 3:
        searchPhrase();
        break;
    case 4:
        searchChapter();
        break;
    case 5:
        searchBook();
        break;
    default:
        std::cout << "Invalid choice" << std::endl;
        break;
    }
}
