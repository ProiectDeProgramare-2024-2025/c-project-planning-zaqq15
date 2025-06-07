#include "FileManager.h"
#include "Colors.h"
#include <fstream>
#include <iostream>
#include <sstream>

const std::string FileManager::LIBRARY_FILE = "library.txt";
const std::string FileManager::CART_FILE = "cart.txt";
const std::string FileManager::LOANS_FILE = "loans.txt";

std::vector<Book> FileManager::loadLibrary() {
    std::vector<Book> books;
    std::ifstream file(LIBRARY_FILE);
    
    if (!file.is_open()) {
        std::cout << Colors::YELLOW << "Warning: Library file not found. Creating new one." << Colors::RESET << std::endl;
        createEmptyFile(LIBRARY_FILE);
        return books;
    }
    
    try {
        int numBooks;
        file >> numBooks;
        file.ignore(); // Ignore newline after number
        
        for (int i = 0; i < numBooks; i++) {
            std::string line;
            if (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string isbn, title, author;
                int quantity;
                
                if (iss >> isbn >> title >> author >> quantity) {
                    books.emplace_back(isbn, title, author, quantity);
                }
            }
        }
    } catch (const std::exception& e) {
        std::cout << Colors::RED << "Error reading library file: " << e.what() << Colors::RESET << std::endl;
    }
    
    file.close();
    return books;
}

bool FileManager::saveLibrary(const std::vector<Book>& books) {
    try {
        std::ofstream file(LIBRARY_FILE);
        if (!file.is_open()) {
            std::cout << Colors::RED << "Error: Cannot open library file for writing." << Colors::RESET << std::endl;
            return false;
        }
        
        file << books.size() << std::endl;
        for (const auto& book : books) {
            file << book.toString() << std::endl;
        }
        
        file.close();
        return true;
    } catch (const std::exception& e) {
        std::cout << Colors::RED << "Error saving library file: " << e.what() << Colors::RESET << std::endl;
        return false;
    }
}

std::map<std::string, int> FileManager::loadCart() {
    std::map<std::string, int> cart;
    std::ifstream file(CART_FILE);
    
    if (!file.is_open()) {
        return cart; // Empty cart if file doesn't exist
    }
    
    try {
        std::string isbn;
        int quantity;
        while (file >> isbn >> quantity) {
            cart[isbn] = quantity;
        }
    } catch (const std::exception& e) {
        std::cout << Colors::RED << "Error reading cart file: " << e.what() << Colors::RESET << std::endl;
    }
    
    file.close();
    return cart;
}

bool FileManager::saveCart(const std::map<std::string, int>& cart) {
    try {
        std::ofstream file(CART_FILE);
        if (!file.is_open()) {
            std::cout << Colors::RED << "Error: Cannot open cart file for writing." << Colors::RESET << std::endl;
            return false;
        }
        
        for (const auto& item : cart) {
            file << item.first << " " << item.second << std::endl;
        }
        
        file.close();
        return true;
    } catch (const std::exception& e) {
        std::cout << Colors::RED << "Error saving cart file: " << e.what() << Colors::RESET << std::endl;
        return false;
    }
}

bool FileManager::clearCart() {
    try {
        std::ofstream file(CART_FILE, std::ofstream::trunc);
        file.close();
        return true;
    } catch (const std::exception& e) {
        std::cout << Colors::RED << "Error clearing cart file: " << e.what() << Colors::RESET << std::endl;
        return false;
    }
}

std::vector<Loan> FileManager::loadLoans() {
    std::vector<Loan> loans;
    std::ifstream file(LOANS_FILE);
    
    if (!file.is_open()) {
        return loans; // Empty loans if file doesn't exist
    }
    
    try {
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            
            std::istringstream iss(line);
            std::string username, dateStr;
            iss >> username >> dateStr;
            
            // Parse date (assuming format dd/mm/yyyy)
            Date loanDate;
            // Simple parsing - you could make this more robust
            
            Loan loan;
            loan.setUser(username);
            loan.setLoanDate(Date::getCurrentDate()); // Simplified
            
            loans.push_back(loan);
        }
    } catch (const std::exception& e) {
        std::cout << Colors::RED << "Error reading loans file: " << e.what() << Colors::RESET << std::endl;
    }
    
    file.close();
    return loans;
}

bool FileManager::saveLoan(const Loan& loan) {
    try {
        std::ofstream file(LOANS_FILE, std::ios::app);
        if (!file.is_open()) {
            std::cout << Colors::RED << "Error: Cannot open loans file for writing." << Colors::RESET << std::endl;
            return false;
        }
        
        file << loan.toString();
        file.close();
        return true;
    } catch (const std::exception& e) {
        std::cout << Colors::RED << "Error saving loan: " << e.what() << Colors::RESET << std::endl;
        return false;
    }
}

bool FileManager::fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

void FileManager::createEmptyFile(const std::string& filename) {
    std::ofstream file(filename);
    if (filename == LIBRARY_FILE) {
        file << "0" << std::endl;
    }
    file.close();
}