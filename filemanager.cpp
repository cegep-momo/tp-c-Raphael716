#include <fstream>
#include <iostream>
#include <filesystem>
#include "filemanager.h"

using namespace std;

// Constructor
FileManager::FileManager(const string& booksFile, const string& usersFile)
    : booksFileName(booksFile), usersFileName(usersFile) {}

// Save all library data
bool FileManager::saveLibraryData(Library& library) {
    return saveBooksToFile(library) && saveUsersToFile(library);
}

// Load all library data
bool FileManager::loadLibraryData(Library& library) {
    bool booksLoaded = loadBooksFromFile(library);
    bool usersLoaded = loadUsersFromFile(library);
    return booksLoaded || usersLoaded; // Return true if at least one file was loaded
}

// Save books to file
bool FileManager::saveBooksToFile(Library& library) {
    ofstream file(booksFileName);
    if (!file.is_open()) {
        cout << "Erreur : Impossible d'ouvrir " << booksFileName << " en écriture.\n";
        return false;
    }
    
    auto books = library.getAllBooks();
    for (Book* book : books) {
        file << book->toFileFormat() << "\n";
    }
    
    file.close();
    return true;
}

// Save users to file
bool FileManager::saveUsersToFile(Library& library) {
    ofstream file(usersFileName);
    if (!file.is_open()) {
        cout << "Erreur : Impossible d'ouvrir " << usersFileName << " en écriture.\n";
        return false;
    }
    
    auto users = library.getAllUsers();
    for (User* user : users) {
        file << user->toFileFormat() << "\n";
    }
    
    file.close();
    return true;
}

// Load books from file
bool FileManager::loadBooksFromFile(Library& library) {
    ifstream file(booksFileName);
    if (!file.is_open()) {
        cout << "Aucun fichier de livres existant trouvé. Démarrage avec une bibliothèque vide.\n";
        return false;
    }
    
    string line;
    int count = 0;
    while (getline(file, line)) {
        if (!line.empty()) {
            Book book;
            book.fromFileFormat(line);
            library.addBook(book);
            count++;
        }
    }
    
    file.close();
    cout << "Chargé " << count << " livre(s) depuis le fichier.\n";
    return true;
}

// Load users from file
bool FileManager::loadUsersFromFile(Library& library) {
    ifstream file(usersFileName);
    if (!file.is_open()) {
        cout << "Aucun fichier d'utilisateurs existant trouvé. Démarrage sans utilisateurs enregistrés.\n";
        return false;
    }
    
    string line;
    int count = 0;
    while (getline(file, line)) {
        if (!line.empty()) {
            User user;
            user.fromFileFormat(line);
            library.addUser(user);
            count++;
        }
    }
    
    file.close();
    cout << "Chargé " << count << " utilisateur(s) depuis le fichier.\n";
    return true;
}

// Check if file exists
bool FileManager::fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

// Create backup
void FileManager::createBackup() {
    if (fileExists(booksFileName)) {
        filesystem::copy_file(booksFileName, booksFileName + ".backup");
    }
    
    if (fileExists(usersFileName)) {
        filesystem::copy_file(usersFileName, usersFileName + ".backup");
    }
    
    cout << "Fichiers de sauvegarde créés.\n";
}

bool FileManager::exportBooksCSV(Library& library, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Erreur : impossible d'ouvrir " << filename << " en écriture.\n";
        return false;
    }
    auto books = library.getAllBooks();
    file << "Titre;Auteur;ISBN;Disponible;Emprunteur\n";
    for (auto b : books) {
        file << b->getTitle() << ";" << b->getAuthor() << ";" << b->getISBN() << ";" << (b->getAvailability() ? "1" : "0") << ";" << b->getBorrowerName() << "\n";
    }
    file.close();
    return true;
}

bool FileManager::importBooksCSV(Library& library, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Erreur : impossible d'ouvrir " << filename << " en lecture.\n";
        return false;
    }
    string line;
    bool first = true;
    int count = 0;
    while (getline(file, line)) {
        if (first) { first = false; continue; }
        if (line.empty()) continue;
        // split by ;
        vector<string> parts;
        size_t pos = 0;
        while (pos <= line.size()) {
            size_t p = line.find(';', pos);
            if (p == string::npos) p = line.size();
            parts.push_back(line.substr(pos, p - pos));
            pos = p + 1;
        }
        if (parts.size() < 3) continue;
        string title = parts[0];
        string author = parts[1];
        string isbn = parts[2];
        Book b(title, author, isbn);
        if (parts.size() >= 4) {
            if (parts[3] == "0") b.setAvailability(false);
            else b.setAvailability(true);
        }
        if (parts.size() >= 5) b.setBorrowerName(parts[4]);
        library.addBook(b);
        count++;
    }
    file.close();
    cout << "Importé " << count << " livre(s) depuis CSV.\n";
    return true;
}

bool FileManager::exportUsersCSV(Library& library, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Erreur : impossible d'ouvrir " << filename << " en écriture.\n";
        return false;
    }
    auto users = library.getAllUsers();
    file << "Nom;ID;Emprunts\n";
    for (auto u : users) {
        file << u->getName() << ";" << u->getUserId() << ";";
        auto borrowed = u->getBorrowedBooks();
        for (size_t i = 0; i < borrowed.size(); ++i) {
            file << borrowed[i];
            if (i + 1 < borrowed.size()) file << ",";
        }
        file << "\n";
    }
    file.close();
    return true;
}

bool FileManager::importUsersCSV(Library& library, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Erreur : impossible d'ouvrir " << filename << " en lecture.\n";
        return false;
    }
    string line;
    bool first = true;
    int count = 0;
    while (getline(file, line)) {
        if (first) { first = false; continue; }
        if (line.empty()) continue;
        vector<string> parts;
        size_t pos = 0;
        while (pos <= line.size()) {
            size_t p = line.find(';', pos);
            if (p == string::npos) p = line.size();
            parts.push_back(line.substr(pos, p - pos));
            pos = p + 1;
        }
        if (parts.size() < 2) continue;
        string name = parts[0];
        string id = parts[1];
        User u(name, id);
        if (parts.size() >= 3 && !parts[2].empty()) {
            size_t p = 0;
            string s = parts[2];
            while (p <= s.size()) {
                size_t q = s.find(',', p);
                if (q == string::npos) q = s.size();
                string isbn = s.substr(p, q - p);
                if (!isbn.empty()) u.borrowBook(isbn);
                p = q + 1;
            }
        }
        library.addUser(u);
        count++;
    }
    file.close();
    cout << "Importé " << count << " utilisateur(s) depuis CSV.\n";
    return true;
}