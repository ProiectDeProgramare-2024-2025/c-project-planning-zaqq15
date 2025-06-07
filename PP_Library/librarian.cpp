#include "Book.h"
#include "Loan.h"
#include "FileManager.h"
#include "Colors.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void printUsage() {
    std::cout << Colors::CYAN << Colors::BOLD << "Library Management System - Librarian" << Colors::RESET << std::endl;
    std::cout << Colors::WHITE << "Usage:" << Colors::RESET << std::endl;
    std::cout << "  " << Colors::GREEN << "./librarian view inventory" << Colors::RESET << " - View all books" << std::endl;
    std::cout << "  " << Colors::GREEN << "./librarian add book <isbn> <title> <author> <quantity>" << Colors::RESET << " - Add new book" << std::endl;
    std::cout << "  " << Colors::GREEN << "./librarian delete book <isbn>" << Colors::RESET << " - Delete book by ISBN" << std::endl;
    std::cout << "  " << Colors::GREEN << "./librarian modify book <isbn> <new_quantity>" << Colors::RESET << " - Update book quantity" << std::endl;
    std::cout << "  " << Colors::GREEN << "./librarian view loans" << Colors::RESET << " - View all loans" << std::endl;
}

void viewInventory() {
    try {
        std::vector<Book> books = FileManager::loadLibrary();
        
        if (books.empty()) {
            std::cout << Colors::YELLOW << "No books in inventory." << Colors::RESET << std::endl;
            return;
        }
        
        std::cout << Colors::CYAN << Colors::BOLD << "=== LIBRARY INVENTORY ===" << Colors::RESET << std::endl;
        std::cout << Colors::WHITE << "ISBN\t\tTitle\t\tAuthor\t\tQuantity" << Colors::RESET << std::endl;
        std::cout << Colors::WHITE << "------------------------------------------------------------" << Colors::RESET << std::endl;
        
        for (const auto& book : books) {
            std::cout << Colors::GREEN << book.getIsbn() << "\t\t"
                      << book.getTitle() << "\t\t"
                      << book.getAuthor() << "\t\t"
                      << book.getQuantity() << Colors::RESET << std::endl;
        }
        
        std::cout << Colors::BLUE << "Total books: " << books.size() << Colors::RESET << std::endl;
    } catch (const std::exception& e) {
        std::cout << Colors::RED << "Error viewing inventory: " << e.what() << Colors::RESET << std::endl;
    }
}

void addBook(const std::string& isbn, const std::string& title, const std::string& author, int quantity) {
    try {
        if (isbn.empty() || title.empty() || author.empty() || quantity < 0) {
            std::cout << Colors::RED << "Error: Invalid book data provided." << Colors::RESET << std::endl;
            return;
        }
        
        std::vector<Book> books = FileManager::loadLibrary();
        
        // Check if book already exists
        auto it = std::find_if(books.begin(), books.end(),
                              [&isbn](const Book& book) { return book.getIsbn() == isbn; });
        
        if (it != books.end()) {
            // Update existing book quantity
            it->setQuantity(it->getQuantity() + quantity);
            std::cout << Colors::YELLOW << "Book already exists. Updated quantity to: " 
                      << it->getQuantity() << Colors::RESET << std::endl;
        } else {
            // Add new book
            books.emplace_back(isbn, title, author, quantity);
            std::cout << Colors::GREEN << "Book added successfully!" << Colors::RESET << std::endl;
        }
        
        if (FileManager::saveLibrary(books)) {
            std::cout << Colors::GREEN << "Library updated successfully." << Colors::RESET << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << Colors::RED << "Error adding book: " << e.what() << Colors::RESET << std::endl;
    }
}

void deleteBook(const std::string& isbn) {
    try {
        std::vector<Book> books = FileManager::loadLibrary();
        
        auto it = std::find_if(books.begin(), books.end(),
                              [&isbn](const Book& book) { return book.getIsbn() == isbn; });
        
        if (it != books.end()) {
            books.erase(it);
            std::cout << Colors::GREEN << "Book deleted successfully!" << Colors::RESET << std::endl;
            
            if (FileManager::saveLibrary(books)) {
                std::cout << Colors::GREEN << "Library updated successfully." << Colors::RESET << std::endl;
            }
        } else {
            std::cout << Colors::RED << "Error: Book with ISBN " << isbn << " not found." << Colors::RESET << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << Colors::RED << "Error deleting book: " << e.what() << Colors::RESET << std::endl;
    }
}

void modifyBook(const std::string& isbn, int newQuantity) {
    try {
        if (newQuantity < 0) {
            std::cout << Colors::RED << "Error: Quantity cannot be negative." << Colors::RESET << std::endl;
            return;
        }
        
        std::vector<Book> books = FileManager::loadLibrary();
        
        auto it = std::find_if(books.begin(), books.end(),
                              [&isbn](const Book& book) { return book.getIsbn() == isbn; });
        
        if (it != books.end()) {
            int oldQuantity = it->getQuantity();
            it->setQuantity(newQuantity);
            std::cout << Colors::GREEN << "Book quantity updated from " << oldQuantity 
                      << " to " << newQuantity << Colors::RESET << std::endl;
            
            if (FileManager::saveLibrary(books)) {
                std::cout << Colors::GREEN << "Library updated successfully." << Colors::RESET << std::endl;
            }
        } else {
            std::cout << Colors::RED << "Error: Book with ISBN " << isbn << " not found." << Colors::RESET << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << Colors::RED << "Error modifying book: " << e.what() << Colors::RESET << std::endl;
    }
}

void viewLoans() {
    try {
        std::vector<Loan> loans = FileManager::loadLoans();
        
        if (loans.empty()) {
            std::cout << Colors::YELLOW << "No loan records found." << Colors::RESET << std::endl;
            return;
        }
        
        std::cout << Colors::CYAN << Colors::BOLD << "=== LOAN RECORDS ===" << Colors::RESET << std::endl;
        
        for (const auto& loan : loans) {
            std::cout << Colors::WHITE << "User: " << Colors::GREEN << loan.getUser() << Colors::RESET;
            std::cout << Colors::WHITE << " | Date: " << Colors::BLUE << loan.getLoanDate().toString() << Colors::RESET << std::endl;
            
            for (const auto& book : loan.getBorrowedBooks()) {
                std::cout << "  - " << Colors::YELLOW << book.getIsbn() << " (Qty: " << book.getQuantity() << ")" << Colors::RESET << std::endl;
            }
            std::cout << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << Colors::RED << "Error viewing loans: " << e.what() << Colors::RESET << std::endl;
    }
}

int main(int argc, char* argv[]) {
    try {
        if (argc < 3) {
            printUsage();
            return 1;
        }
        
        std::string command = argv[1];
        std::string action = argv[2];
        
        if (command == "view" && action == "inventory") {
            viewInventory();
        }
        else if (command == "add" && action == "book" && argc == 7) {
            std::string isbn = argv[3];
            std::string title = argv[4];
            std::string author = argv[5];
            int quantity = std::stoi(argv[6]);
            addBook(isbn, title, author, quantity);
        }
        else if (command == "delete" && action == "book" && argc == 4) {
            std::string isbn = argv[3];
            deleteBook(isbn);
        }
        else if (command == "modify" && action == "book" && argc == 5) {
            std::string isbn = argv[3];
            int quantity = std::stoi(argv[4]);
            modifyBook(isbn, quantity);
        }
        else if (command == "view" && action == "loans") {
            viewLoans();
        }
        else {
            std::cout << Colors::RED << "Error: Invalid command or insufficient arguments." << Colors::RESET << std::endl;
            printUsage();
            return 1;
        }
        
    } catch (const std::exception& e) {
        std::cout << Colors::RED << "Error: " << e.what() << Colors::RESET << std::endl;
        return 1;
    }
    
    return 0;
}