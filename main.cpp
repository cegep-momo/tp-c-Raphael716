#include <iostream>
#include <limits>
#include <string>

#include "library.h"
#include "filemanager.h"
#include "validators.h"

using namespace std;

static string trimString(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

void clearScreen() {
    system("cls || clear");
}

void pauseForInput() {
    cout << "\nAppuyez sur Entrée pour continuer...";
    cin.ignore();
    cin.get();
}

void displayMenu() {
    cout << "\n=== SYSTÈME DE GESTION DE BIBLIOTHÈQUE PERSONNELLE ===\n";
    cout << "1.  Ajouter un Livre\n";
    cout << "2.  Supprimer un Livre\n";
    cout << "3.  Rechercher des Livres par Titre\n";
    cout << "4.  Rechercher des Livres par Auteur\n";
    cout << "5.  Afficher Tous les Livres\n";
    cout << "6.  Afficher les Livres Disponibles\n";
    cout << "7.  Ajouter un Utilisateur\n";
    cout << "8.  Afficher Tous les Utilisateurs\n";
    cout << "9.  Emprunter un Livre\n";
    cout << "10. Retourner un Livre\n";
    cout << "11. Statistiques de la Bibliothèque\n";
    cout << "12. Sauvegarder les Données\n";
    cout << "13. Créer une Sauvegarde\n";
    cout << "14. Exporter Livres en CSV\n";
    cout << "15. Importer Livres depuis CSV\n";
    cout << "16. Exporter Utilisateurs en CSV\n";
    cout << "17. Importer Utilisateurs depuis CSV\n";
    cout << "0.  Quitter\n";
    cout << "======================================================\n";
    cout << "Entrez votre choix : ";
}

string getInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

int main() {
    Library library;
    FileManager fileManager;
    
    // Load existing data
    cout << "Chargement des données de la bibliothèque...\n";
    fileManager.loadLibraryData(library);
    
    int choice;
    bool running = true;
    
    while (running) {
        displayMenu();
        
        if (!(cin >> choice)) {
            cout << "Saisie invalide. Veuillez entrer un nombre.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pauseForInput();
            continue;
        }
        cin.ignore(); // Clear newline from buffer
        
        switch (choice) {
            case 1: { // Add Book
                string title;
                do {
                    title = getInput("Entrez le titre du livre : ");
                    if (!isNonEmptyTitle(title)) cout << "Titre invalide. Veuillez réessayer.\n";
                } while (!isNonEmptyTitle(title));

                string author;
                do {
                    author = getInput("Entrez l'auteur du livre : ");
                    if (!isValidName(author)) cout << "Nom d'auteur invalide. Veuillez utiliser des lettres, espaces, - ou '.\n";
                } while (!isValidName(author));

                string isbn;
                do {
                    isbn = getInput("Entrez l'ISBN du livre : ");
                    if (!isValidISBN(isbn)) cout << "ISBN invalide. Doit contenir 10 ou 13 chiffres (les tirets sont autorises).\n";
                    else if (library.findBookByISBN(isbn)) {
                        cout << "Erreur : Un livre avec l'ISBN " << isbn << " existe déjà.\n";
                        isbn.clear();
                    }
                } while (!isValidISBN(isbn));

                Book newBook(title, author, isbn);
                library.addBook(newBook);
                cout << "Livre ajouté avec succès !\n";
                pauseForInput();
                break;
            }
            
            case 2: { // Remove Book
                string isbn;
                do {
                    isbn = getInput("Entrez l'ISBN du livre à supprimer : ");
                    if (!isValidISBN(isbn)) cout << "ISBN invalide.\n";
                } while (!isValidISBN(isbn));

                if (library.removeBook(isbn)) cout << "Livre supprimé avec succès !\n";
                else cout << "Livre non trouvé.\n";
                pauseForInput();
                break;
            }
            
            case 3: { // Search by Title
                string title = getInput("Entrez le titre à rechercher : ");
                auto results = library.searchBooksByTitle(title);
                
                if (results.empty()) {
                    cout << "Aucun livre trouvé avec ce titre.\n";
                } else {
                    cout << "\n=== RÉSULTATS DE RECHERCHE ===\n";
                    for (size_t i = 0; i < results.size(); ++i) {
                        cout << "\nRésultat " << (i + 1) << " :\n";
                        cout << results[i]->toString() << "\n";
                        cout << "-----------------------------\n";
                    }
                }
                pauseForInput();
                break;
            }
            
            case 4: { // Search by Author
                string author = getInput("Entrez l'auteur à rechercher : ");
                auto results = library.searchBooksByAuthor(author);
                
                if (results.empty()) {
                    cout << "Aucun livre trouvé de cet auteur.\n";
                } else {
                    cout << "\n=== RÉSULTATS DE RECHERCHE ===\n";
                    for (size_t i = 0; i < results.size(); ++i) {
                        cout << "\nRésultat " << (i + 1) << " :\n";
                        cout << results[i]->toString() << "\n";
                        cout << "-----------------------------\n";
                    }
                }
                pauseForInput();
                break;
            }
            
            case 5: // Display All Books
                library.displayAllBooks();
                pauseForInput();
                break;
            
            case 6: // Display Available Books
                library.displayAvailableBooks();
                pauseForInput();
                break;
            
            case 7: { // Add User
                string name;
                do {
                    name = getInput("Entrez le nom de l'utilisateur : ");
                    if (!isValidName(name)) cout << "Nom invalide.\n";
                } while (!isValidName(name));

                string userId;
                do {
                    userId = getInput("Entrez l'ID de l'utilisateur (ex: USR001) : ");
                    if (!isValidUserId(userId)) cout << "ID invalide. Format attendu: USR suivi de chiffres.\n";
                    else if (library.findUserById(userId)) {
                        cout << "Erreur : Un utilisateur avec l'ID " << userId << " existe déjà.\n";
                        userId.clear();
                    }
                } while (!isValidUserId(userId));

                User newUser(name, userId);
                library.addUser(newUser);
                cout << "Utilisateur ajouté avec succès !\n";
                pauseForInput();
                break;
            }
            
            case 8: // Display All Users
                library.displayAllUsers();
                pauseForInput();
                break;
            
            case 9: { // Check Out Book
                string isbn;
                do {
                    isbn = getInput("Entrez l'ISBN du livre à emprunter : ");
                    if (!isValidISBN(isbn)) cout << "ISBN invalide.\n";
                } while (!isValidISBN(isbn));

                string userId;
                do {
                    userId = getInput("Entrez l'ID de l'utilisateur : ");
                    if (!isValidUserId(userId)) cout << "ID utilisateur invalide.\n";
                } while (!isValidUserId(userId));

                if (library.checkOutBook(isbn, userId)) cout << "Livre emprunté avec succès !\n";
                else cout << "Erreur : Impossible d'emprunter le livre. Vérifiez l'ISBN, l'ID utilisateur et la disponibilité du livre.\n";
                pauseForInput();
                break;
            }
            
            case 10: { // Return Book
                string isbn;
                do {
                    isbn = getInput("Entrez l'ISBN du livre à retourner : ");
                    if (!isValidISBN(isbn)) cout << "ISBN invalide.\n";
                } while (!isValidISBN(isbn));

                if (library.returnBook(isbn)) cout << "Livre retourné avec succès !\n";
                else cout << "Erreur : Impossible de retourner le livre. Vérifiez l'ISBN et que le livre est bien emprunté.\n";
                pauseForInput();
                break;
            }
            
            case 11: { // Library Statistics
                cout << "\n=== STATISTIQUES DE LA BIBLIOTHÈQUE ===\n";
                cout << "Total des Livres : " << library.getTotalBooks() << "\n";
                cout << "Livres Disponibles : " << library.getAvailableBookCount() << "\n";
                cout << "Livres Empruntés : " << library.getCheckedOutBookCount() << "\n";
                cout << "Total des Utilisateurs : " << library.getAllUsers().size() << "\n";
                pauseForInput();
                break;
            }
            
            case 12: { // Save Data
                if (fileManager.saveLibraryData(library)) {
                    cout << "Données de la bibliothèque sauvegardées avec succès !\n";
                } else {
                    cout << "Erreur lors de la sauvegarde des données de la bibliothèque.\n";
                }
                pauseForInput();
                break;
            }
            
            case 13: { // Create Backup
                fileManager.createBackup();
                pauseForInput();
                break;
            }

            case 14: {
                {
                    string filename = trimString(getInput("Nom du fichier CSV pour export (ex: books_export.csv) : "));
                    if (filename.empty()) {
                        filename = "books_export.csv";
                        cout << "Aucun nom fourni. Utilisation de : " << filename << "\n";
                    }
                    cout << "Ecriture dans le fichier : '" << filename << "'...\n";
                    if (fileManager.exportBooksCSV(library, filename)) cout << "Export CSV livres réussi.\n";
                    else cout << "Erreur lors de l'export CSV livres.\n";
                }
                pauseForInput();
                break;
            }

            case 15: {
                {
                    string filename = trimString(getInput("Nom du fichier CSV à importer (ex: books_import.csv) : "));
                    if (filename.empty()) {
                        cout << "Aucun nom fourni. Annulation de l'import.\n";
                    } else {
                        cout << "Lecture depuis le fichier : '" << filename << "'...\n";
                        if (fileManager.importBooksCSV(library, filename)) cout << "Import CSV livres terminé.\n";
                        else cout << "Erreur lors de l'import CSV livres.\n";
                    }
                }
                pauseForInput();
                break;
            }

            case 16: {
                {
                    string filename = trimString(getInput("Nom du fichier CSV pour export utilisateurs (ex: users_export.csv) : "));
                    if (filename.empty()) {
                        filename = "users_export.csv";
                        cout << "Aucun nom fourni. Utilisation de : " << filename << "\n";
                    }
                    cout << "Ecriture dans le fichier : '" << filename << "'...\n";
                    if (fileManager.exportUsersCSV(library, filename)) cout << "Export CSV utilisateurs réussi.\n";
                    else cout << "Erreur lors de l'export CSV utilisateurs.\n";
                }
                pauseForInput();
                break;
            }

            case 17: {
                {
                    string filename = trimString(getInput("Nom du fichier CSV utilisateurs à importer (ex: users_import.csv) : "));
                    if (filename.empty()) {
                        cout << "Aucun nom fourni. Annulation de l'import.\n";
                    } else {
                        cout << "Lecture depuis le fichier : '" << filename << "'...\n";
                        if (fileManager.importUsersCSV(library, filename)) cout << "Import CSV utilisateurs terminé.\n";
                        else cout << "Erreur lors de l'import CSV utilisateurs.\n";
                    }
                }
                pauseForInput();
                break;
            }
            
            case 0: // Exit
                cout << "Sauvegarde des données avant la fermeture...\n";
                fileManager.saveLibraryData(library);
                cout << "Merci d'avoir utilisé le Système de Gestion de Bibliothèque Personnelle !\n";
                running = false;
                break;
            
            default:
                cout << "Choix invalide. Veuillez réessayer.\n";
                pauseForInput();
                break;
        }
    }
    
    return 0;
}