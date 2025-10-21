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

// Getters
string Book::getTitle() const {
    return title;
}

string Book::getAuthor() const {
    return author;
}

string Book::getISBN() const {
    return isbn;
}

bool Book::getAvailability() const {
    return isAvailable;
}

string Book::getBorrowerName() const {
    return borrowerName;
}
