#include "book.h"
#include <sstream>

// Constructeurs
Book::Book() 
{
    title = "";
    author = "";
    isbn = "";
    isAvailable = true;
    borrowerName = "";
}

Book::Book(const string& iTitle, const string& iAuthor, const string& iIsbn) 
{
    title = iTitle;
    author = iAuthor;
    isbn = iIsbn;
    isAvailable = true;
    borrowerName = "";
}

// Getters
string Book::getTitle() const 
{
    return title;
}

string Book::getAuthor() const 
{
    return author;
}

string Book::getISBN() const 
{
    return isbn;
}

bool Book::getAvailability() const 
{
    return isAvailable;
}

string Book::getBorrowerName() const 
{
    return borrowerName;
}

// Setters
void Book::setTitle(const string& iTitle) 
{
    title = iTitle;
}

void Book::setAuthor(const string& iAuthor) 
{
    author = iAuthor;
}

void Book::setISBN(const string& iIsbn) 
{
    isbn = iIsbn;
}

void Book::setAvailability(bool iAvailable) 
{
    isAvailable = iAvailable;
    if (iAvailable) {
        borrowerName = "";
    }
}

void Book::setBorrowerName(const string& iName) 
{
    borrowerName = iName;
    if (!iName.empty()) {
        isAvailable = false;
    }
}

// Méthodes
void Book::checkOut(const string& iBorrower) 
{
    if (!iBorrower.empty()) {
        borrowerName = iBorrower;
        isAvailable = false;
    }
}

void Book::returnBook() 
{
    borrowerName = "";
    isAvailable = true;
}

string Book::toString() const 
{
    std::ostringstream oss;
    oss << "Titre : " << title << "\n"
        << "Auteur : " << author << "\n"
        << "ISBN : " << isbn << "\n"
        << "Disponible : " << (isAvailable ? "Oui" : "Non") << "\n";
    if (!isAvailable) {
        oss << "Emprunteur : " << borrowerName << "\n";
    }
    return oss.str();
}

