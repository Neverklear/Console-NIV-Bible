# Bible App

A friendly, console-based Bible application written in C++ that lets you explore Bible passages via a local SQLite database.

## Overview

The Bible App allows you to search for Bible verses, words, phrases, chapters, or entire books using a SQLite database (BibleData.db). The application uses the SQLite Modern C++ library for database interaction and features warm aesthetics with decorative headers, ANSI color codes, and pagination to improve readability.

## Features

- **Verse Search:** Retrieve a specific verse by entering the book name, chapter number, and verse number.
- **Word Search:** Find all verses containing a specific word.
- **Phrase Search:** Search for verses that include a particular phrase.
- **Chapter Search:** Display all verses from a given chapter.
- **Book Search:** Display the entire content of a book.
- **Friendly Interface:** Enjoy a warm, inviting interface with clear prompts and decorative headers.
- **Pagination:** Long outputs are paginated so you can read through them comfortably.

## Database Schema

The application uses a SQLite database (BibleData.db) with the following structure:

### Books Table
- **id** (INTEGER, Primary Key)
- **name** (TEXT): The name of the book (e.g., "John").
- **testament** (TEXT): Indicates "Old" or "New" Testament.

### verses Table
- **book_id** (INTEGER): Foreign key referencing Books(id).
- **chapter** (INTEGER): The chapter number.
- **verse** (INTEGER): The verse number.
- **text** (TEXT): The verse's text.

*Note: Please ensure your CSV data is cleaned up prior to importing to avoid formatting issues.*

## Prerequisites

- **Compiler:** A C++ compiler with C++11 support (e.g., g++, clang, MSVC).
- **Libraries:** SQLite3 and [SQLite Modern C++](https://github.com/SqliteModernCpp/sqlite_modern_cpp).
- **Database:** A pre-populated BibleData.db following the schema above.

## Installation & Build Instructions

1. **Clone the Repository:**

   git clone <your-repo-url>
   cd BibleApp

2. **Setup Dependencies:**

   Make sure the SQLite Modern C++ library is available in your include path. Refer to the SQLite Modern C++ GitHub page for details.

3. **Compile the Application:**

   For example, using g++:

   g++ -std=c++11 -I/path/to/sqlite_modern_cpp/include -o BibleApp main.cpp -lsqlite3

   Adjust the include path and linker options as necessary.

## Usage

Run the compiled executable:

   ./BibleApp

Follow the prompts to search for verses, words, phrases, chapters, or books. The app displays results in a paginated format; press Enter when prompted to view the next section.

## Visual Enhancements

The app uses ANSI escape sequences for colors and decorative headers to create a warm, inviting atmosphere. Friendly messages and clear formatting enhance the overall user experience.

## Contributing

Contributions, bug reports, and suggestions are welcome! Please open an issue or submit a pull request with your ideas.

## License

This project is licensed under the MIT License. See the LICENSE file for details.
