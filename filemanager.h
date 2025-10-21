#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

#include "library.h"

using namespace std;

class FileManager {
private:
    string booksFileName;
    string usersFileName;

public:
    // Constructor
    FileManager(const string& booksFile = "books.txt", 
                const string& usersFile = "users.txt");
    
    // File operations
    bool saveLibraryData(Library& library);
    bool loadLibraryData(Library& library);
    
    // Individual file operations
    bool saveBooksToFile(Library& library);
    bool saveUsersToFile(Library& library);
    bool loadBooksFromFile(Library& library);
    bool loadUsersFromFile(Library& library);
 
    bool exportBooksCSV(Library& library, const std::string& filename);
    bool importBooksCSV(Library& library, const std::string& filename);
    bool exportUsersCSV(Library& library, const std::string& filename);
    bool importUsersCSV(Library& library, const std::string& filename);
    
    // Utility methods
    bool fileExists(const string& filename);
    void createBackup();
};

#endif
