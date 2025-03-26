#include <iostream>
#include <string>
#include <limits>   // Needed for pagination (cin.ignore)
#include "sqlite_modern_cpp.h"
using namespace std;

// Helper function to pause output every few lines
void pauseForPagination() {
    cout << "Press Enter twice to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void intro() {
    cout << "Welcome to the Bible App" << endl;
    cout << "Please select an option" << endl;
    cout << "1. Search for a verse" << endl;
    cout << "2. Search for a word" << endl;
    cout << "3. Search for a phrase" << endl;
    cout << "4. Search for a chapter" << endl;
    cout << "5. Search for a book" << endl << endl;
}

void searchVerse() {
    cout << "Please enter the book name" << endl;
    string book;
    cin >> book;
    cout << "Please enter the chapter number" << endl;
    int chapter;
    cin >> chapter;
    cout << "Please enter the verse number" << endl;
    int verse;
    cin >> verse;

    string dbFile = "BibleData.db";
    try {
        sqlite::database db(dbFile);
        // Updated query: Use the proper tables and columns (v.text for the verse)
        // and join Books (b) with verses (v)
        string query = "SELECT v.text FROM verses v JOIN Books b ON v.book_id = b.id "
            "WHERE b.name = '" + book + "' AND v.chapter = " + to_string(chapter) +
            " AND v.verse = " + to_string(verse);
        for (auto row : db << query) {
            string verseText;
            row >> verseText;
            cout << verseText << endl;
        }
    }
    catch (const std::exception& e) {
        cerr << "SQLite exception: " << e.what() << endl;
    }
}

void searchWord() {
    cout << "Please enter the word you would like to search for" << endl;
    string word;
    cin >> word;

    string dbFile = "BibleData.db";
    try {
        sqlite::database db(dbFile);
        // Updated query: We join Books and verses, search in v.text,
        // and order results by book, chapter, then verse for consistency.
        string query = "SELECT b.name, v.chapter, v.verse, v.text FROM verses v "
            "JOIN Books b ON v.book_id = b.id "
            "WHERE v.text LIKE '%" + word + "%' "
            "ORDER BY b.name, v.chapter, v.verse";
        int lineCount = 0;
        const int pageSize = 5;  // Adjust the page size as needed
        for (auto row : db << query) {
            string book;
            int chapter, verse;
            string verseText;
            row >> book >> chapter >> verse >> verseText;
            cout << book << " " << chapter << ":" << verse << " - " << verseText << endl << endl;
            lineCount++;
            // Pause after every 'pageSize' results for pagination.
            if (lineCount % pageSize == 0) {
                pauseForPagination();
            }
        }
    }
    catch (const std::exception& e) {
        cerr << "SQLite exception: " << e.what() << endl;
    }
}

void searchPhrase() {
    cout << "Please enter the phrase you would like to search for" << endl;
    string phrase;
    cin.ignore(); // Clear the newline left in the input buffer.
    getline(cin, phrase);

    string dbFile = "BibleData.db";
    try {
        sqlite::database db(dbFile);
        // Similar to searchWord but using a phrase with potential spaces,
        // and ordering for consistent output.
        string query = "SELECT b.name, v.chapter, v.verse, v.text FROM verses v "
            "JOIN Books b ON v.book_id = b.id "
            "WHERE v.text LIKE '%" + phrase + "%' "
            "ORDER BY b.name, v.chapter, v.verse";
        int lineCount = 0;
        const int pageSize = 5;
        for (auto row : db << query) {
            string book;
            int chapter, verse;
            string verseText;
            row >> book >> chapter >> verse >> verseText;
            cout << book << " " << chapter << ":" << verse << " - " << verseText << endl << endl;
            lineCount++;
            if (lineCount % pageSize == 0) {
                pauseForPagination();
            }
        }
    }
    catch (const std::exception& e) {
        cerr << "SQLite exception: " << e.what() << endl;
    }
}

void searchChapter() {
    cout << "Please enter the book name" << endl;
    string book;
    cin >> book;

    cout << "Please enter the chapter number" << endl;
    int chapter;
    cin >> chapter;

    string dbFile = "BibleData.db";
    try {
        sqlite::database db(dbFile);

        // Key change: Use CAST(v.chapter AS INTEGER) in the WHERE clause.
        // This ensures that if v.chapter is stored as text (or with extra spaces),
        // it is compared numerically so that only rows with the exact chapter number are returned.
        string query = "SELECT v.verse, v.text FROM verses v "
                       "JOIN Books b ON v.book_id = b.id "
                       "WHERE b.name = '" + book + "' AND CAST(v.chapter AS INTEGER) = " + to_string(chapter) +
                       " ORDER BY v.verse";
        int lineCount = 0;
        const int pageSize = 5;
        for (auto row : db << query) {
            int verse;
            string verseText;
            row >> verse >> verseText;
            cout << "Verse " << verse << ": " << verseText << endl << endl;
            lineCount++;
            if (lineCount % pageSize == 0) {
                // Pause to let the user read the output page by page.
                pauseForPagination();
            }
        }
    } catch (const std::exception& e) {
        cerr << "SQLite exception: " << e.what() << endl;
    }
}

void searchBook() {
    cout << "Please enter the book name" << endl;
    string book;
    cin >> book;

    string dbFile = "BibleData.db";
    try {
        sqlite::database db(dbFile);
        // For an entire book, order by chapter and verse to maintain proper order.
        string query = "SELECT v.chapter, v.verse, v.text FROM verses v "
            "JOIN Books b ON v.book_id = b.id "
            "WHERE b.name = '" + book + "' "
            "ORDER BY v.chapter, v.verse";
        int lineCount = 0;
        const int pageSize = 5;
        for (auto row : db << query) {
            int chapter, verse;
            string verseText;
            row >> chapter >> verse >> verseText;
            cout << "Chapter " << chapter << ", Verse " << verse << ": " << verseText << endl << endl;
            lineCount++;
            if (lineCount % pageSize == 0) {
                pauseForPagination();
            }
        }
    }
    catch (const std::exception& e) {
        cerr << "SQLite exception: " << e.what() << endl;
    }
}

void menu() {
    int choice;
    cin >> choice;
    cout << endl;
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
        cout << "Invalid choice" << endl;
        break;
    }
}

int main() {
    intro();
    menu();
    return 0;
}
