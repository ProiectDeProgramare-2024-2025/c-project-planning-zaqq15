#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Book.h"
#include "Loan.h"
#include <vector>
#include <string>
#include <map>

class FileManager {
public:
    // Library file operations
    static std::vector<Book> loadLibrary();
    static bool saveLibrary(const std::vector<Book>& books);
    
    // Cart file operations
    static std::map<std::string, int> loadCart();
    static bool saveCart(const std::map<std::string, int>& cart);
    static bool clearCart();
    
    // Loans file operations
    static std::vector<Loan> loadLoans();
    static bool saveLoan(const Loan& loan);
    
    // Utility functions
    static bool fileExists(const std::string& filename);
    static void createEmptyFile(const std::string& filename);
    
private:
    static const std::string LIBRARY_FILE;
    static const std::string CART_FILE;
    static const std::string LOANS_FILE;
};

#endif