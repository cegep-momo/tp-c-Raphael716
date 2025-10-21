#include "book.h"

// Constructeurs
Book::Book() {
    title = "";
    author = "";
    isbn = "";
    isAvailable = true;
    borrowerName = "";
}

Book::Book(const string& iTitle, const string& iAuthor, const string& iIsbn) {
    title = iTitle;
    author = iAuthor;
    isbn = iIsbn;
    isAvailable = true;
    borrowerName = "";
}


