#include "Book.h"
#include "Loan.h"
#include "FileManager.h"
#include "Colors.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

void printUsage() {
    std::cout << Colors::CYAN << Colors::BOLD << "Library Management System - Reader" << Colors::RESET << std::endl;
    std::cout << Colors::WHITE << "Usage:" << Colors::RESET << std::endl;
    std::cout << "  " << Colors::GREEN << "./reader search title <title>" << Colors::RESET << " - Search books by title" << std::endl;
    std::cout << "  " << Colors::GREEN << "./reader search author <author>" << Colors::RESET << " - Search books by author" << std::endl;
    std::cout << "  " << Colors::GREEN << "./reader add to cart <isbn> <quantity>" << Colors::RESET << " - Add book to cart" << std::endl;
    std::cout << "  " << Colors::GREEN << "./reader remove from cart <isbn>" << Colors::RESET << " - Remove book from cart" << std::endl;
    std::cout << "  " << Colors::GREEN << "./reader view cart" << Colors::RESET << " - View books in cart" << std::endl;
    std::cout << "  " << Colors::GREEN << "./reader borrow books <username>" << Colors::RESET << " - Confirm borrowing" << std::endl;
}

void searchByTitle(const std::string& title) {
    try {
        std::vector<Book> books = FileManager::loadLibrary();
        std::vector<Book> results;
        
        for (const auto& book : books) {
            if (book.getTitle().find(title) != std::string::npos) {
                results.push_back(book);
            }
        }
        
        if (results.empty()) {
            std::cout << Colors::YELLOW << "No books found with title containing: " << title << Colors::RESET << std::endl;
            return;
        }
        
        std::cout << Colors::CYAN << Colors::BOLD << "=== SEARCH RESULTS (Title: " << title << ") ===" << Colors::RESET << std::endl;
        std::cout << Colors::WHITE << "ISBN\t\tTitle\t\tAuthor\t\tQuantity" << Colors::RESET << std::endl;
        std::cout << Colors::WHITE << "------------------------------------------------------------" << Colors::RESET << std::endl;
        
        for (const auto& book : results) {
            std::cout << Colors::GREEN << book.getIsbn() << "\t\t"
                      << book.getTitle() << "\t\t"
                      << book.getAuthor() << "\t\t"
                      << book.getQuantity() << Colors::RESET << std::endl;
        }
        
        std::cout << Colors::BLUE << "Found " << results.size() << " book(s)." << Colors::RESET << std::endl;
    } catch (const std::exception& e) {
        std::cout << Colors::RED << "Error searching by title: " << e.what() << Colors::RESET << std::endl;
    }
}

void searchByAuthor(const std::string& author) {
    try {
        std::vector<Book> books = FileManager::loadLibrary();
        std::vector<Book> results;
        
        for (const auto& book : books) {
            if (book.getAuthor().find(author) != std::string::npos) {
                results.push_back(book);
            }
        }
        
        if (results.empty()) {
            std::cout << Colors::YELLOW << "No books found by author containing: " << author << Colors::RESET << std::endl;
            return;
        }
        
        std::cout << Colors::CYAN << Colors::BOLD << "=== SEARCH RESULTS (Author: " << author << ") ===" << Colors::RESET << std::endl;
        std::cout << Colors::WHITE << "ISBN\t\tTitle\t\tAuthor\t\tQuantity" << Colors::RESET << std::endl;
        std::cout << Colors::WHITE << "------------------------------------------------------------" << Colors::RESET << std::endl;
        
        for (const auto& book : results) {
            std::cout << Colors::GREEN << book.getIsbn() << "\t\t"
                      << book.getTitle() << "\t\t"
                      << book.getAuthor() << "\t\t"
                      << book.getQuantity() << Colors::RESET << std::endl;
        }
        
        std::cout << Colors::BLUE << "Found " << results.size() << " book(s)." << Colors::RESET << std::endl;
    } catch (const std::exception& e) {
        std::cout << Colors::RED << "Error searching by author: " << e.what() << Colors::RESET << std::endl;
    }
}

void addToCart(const std::string& isbn, int quantity) {
    try {
        if (quantity <= 0) {
            std::cout << Colors::RED << "Error: Quantity must be positive." << Colors::RESET << std::endl;
            return;
        }
        
        // Check if book exists in library
        std::vector<Book> books = FileManager::loadLibrary();
        auto bookIt = std::find_if(books.begin(), books.end(),
                                  [&isbn](const Book& book) { return book.getIsbn() == isbn; });
        
        if (bookIt == books.end()) {
            std::cout << Colors::RED << "Error: Book with ISBN " << isbn << " not found in library." << Colors::RESET << std::endl;
            return;
        }
        
        if (bookIt->getQuantity() < quantity) {
            std::cout << Colors::RED << "Error: Not enough books available. Available: " 
                      << bookIt->getQuantity() << Colors::RESET << std::endl;
            return;
        }
        
        // Load current cart and add book
        std::map<std::string, int> cart = FileManager::loadCart();
        
        if (cart.find(isbn) != cart.end()) {
            cart[isbn] += quantity;
            std::cout << Colors::YELLOW << "Updated quantity in cart. New quantity: " << cart[isbn] << Colors::RESET << std::endl;
        } else {
            cart[isbn] = quantity;
            std::cout << Colors::GREEN << "Book added to cart successfully!" << Colors::RESET << std::endl;
        }
        
        if (FileManager::saveCart(cart)) {
            std::cout << Colors::GREEN << "Cart updated successfully." << Colors::RESET << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << Colors::RED << "Error adding to cart: " << e.what() << Colors::RESET << std::endl;
    }
}

void removeFromCart(const std::string& isbn) {
    try {
        std::map<std::string, int> cart = FileManager::loadCart();
        
        if (cart.find(isbn) != cart.end()) {
            cart.erase(isbn);
            std::cout << Colors::GREEN << "Book removed from cart successfully!" << Colors::RESET << std::endl;
            
            if (FileManager::saveCart(cart)) {
                std::cout << Colors::GREEN << "Cart updated successfully." << Colors::RESET << std::endl;
            }
        } else {
            std::cout << Colors::RED << "Error: Book with ISBN " << isbn << " not found in cart." << Colors::RESET << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << Colors::RED << "Error removing from cart: " << e.what() << Colors::RESET << std::endl;
    }
}

void viewCart() {
    try {
        std::map<std::string, int> cart = FileManager::loadCart();
        
        if (cart.empty()) {
            std::cout << Colors::YELLOW << "Cart is empty." << Colors::RESET << std::endl;
            return;
        }
        
        std::vector<Book> books = FileManager::loadLibrary();
        
        std::cout << Colors::CYAN << Colors::BOLD << "=== YOUR CART ===" << Colors::RESET << std::endl;
        std::cout << Colors::WHITE << "ISBN\t\tTitle\t\tAuthor\t\tQuantity" << Colors::RESET << std::endl;
        std::cout << Colors::WHITE << "------------------------------------------------------------" << Colors::RESET << std::endl;
        
        for (const auto& cartItem : cart) {
            auto bookIt = std::find_if(books.begin(), books.end(),
                                      [&cartItem](const Book& book) { return book.getIsbn() == cartItem.first; });
            
            if (bookIt != books.end()) {
                std::cout << Colors::GREEN << bookIt->getIsbn() << "\t\t"
                          << bookIt->getTitle() << "\t\t"
                          << bookIt->getAuthor() << "\t\t"
                          << cartItem.second << Colors::RESET << std::endl;
            }
        }
        
        std::cout << Colors::BLUE << "Total items in cart: " << cart.size() << Colors::RESET << std::endl;
    } catch (const std::exception& e) {
        std::cout << Colors::RED << "Error viewing cart: " << e.what() << Colors::RESET << std::endl;
    }
}

void borrowBooks(const std::string& username) {
    try {
        if (username.empty()) {
            std::cout << Colors::RED << "Error: Username cannot be empty." << Colors::RESET << std::endl;
            return;
        }
        
        std::map<std::string, int> cart = FileManager::loadCart();
        
        if (cart.empty()) {
            std::cout << Colors::YELLOW << "Cart is empty. Nothing to borrow." << Colors::RESET << std::endl;
            return;
        }
        
        // Load library and update quantities
        std::vector<Book> books = FileManager::loadLibrary();
        std::vector<Book> borrowedBooks;
        
        for (const auto& cartItem : cart) {
            auto bookIt = std::find_if(books.begin(), books.end(),
                                      [&cartItem](const Book& book) { return book.getIsbn() == cartItem.first; });
            
            if (bookIt != books.end()) {
                if (bookIt->getQuantity() >= cartItem.second) {
                    bookIt->setQuantity(bookIt->getQuantity() - cartItem.second);
                    borrowedBooks.emplace_back(cartItem.first, bookIt->getTitle(), 
                                             bookIt->getAuthor(), cartItem.second);
                } else {
                    std::cout << Colors::RED << "Error: Not enough copies of " << bookIt->getTitle() 
                              << " available." << Colors::RESET << std::endl;
                    return;
                }
            }
        }
        
        // Create loan record
        Loan loan(username, borrowedBooks, Date::getCurrentDate());
        
        // Save everything
        if (FileManager::saveLibrary(books) && 
            FileManager::saveLoan(loan) && 
            FileManager::clearCart()) {
            
            std::cout << Colors::GREEN << Colors::BOLD << "Books borrowed successfully!" << Colors::RESET << std::endl;
            std::cout << Colors::BLUE << "Loan created for user: " << username << Colors::RESET << std::endl;
            std::cout << Colors::BLUE << "Date: " << Date::getCurrentDate().toString() << Colors::RESET << std::endl;
            std::cout << Colors::YELLOW << "Please return the books on time!" << Colors::RESET << std::endl;
        } else {
            std::cout << Colors::RED << "Error: Failed to complete borrowing process." << Colors::RESET << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << Colors::RED << "Error borrowing books: " << e.what() << Colors::RESET << std::endl;
    }
}

int main(int argc, char* argv[]) {
    try {
        if (argc < 3) {
            printUsage();
            return 1;
        }
        
        std::string command = argv[1];
        
        if (command == "search" && argc == 4) {
            std::string type = argv[2];
            std::string query = argv[3];
            
            if (type == "title") {
                searchByTitle(query);
            } else if (type == "author") {
                searchByAuthor(query);
            } else {
                std::cout << Colors::RED << "Error: Invalid search type. Use 'title' or 'author'." << Colors::RESET << std::endl;
                printUsage();
                return 1;
            }
        }
        else if (command == "add" && argc == 6) {
            if (std::string(argv[2]) == "to" && std::string(argv[3]) == "cart") {
                std::string isbn = argv[4];
                int quantity = std::stoi(argv[5]);
                addToCart(isbn, quantity);
            } else {
                std::cout << Colors::RED << "Error: Invalid command format." << Colors::RESET << std::endl;
                printUsage();
                return 1;
            }
        }
        else if (command == "remove" && argc == 5) {
            if (std::string(argv[2]) == "from" && std::string(argv[3]) == "cart") {
                std::string isbn = argv[4];
                removeFromCart(isbn);
            } else {
                std::cout << Colors::RED << "Error: Invalid command format." << Colors::RESET << std::endl;
                printUsage();
                return 1;
            }
        }
        else if (command == "view" && argc == 3) {
            if (std::string(argv[2]) == "cart") {
                viewCart();
            } else {
                std::cout << Colors::RED << "Error: Invalid view command." << Colors::RESET << std::endl;
                printUsage();
                return 1;
            }
        }
        else if (command == "borrow" && argc == 4) {
            if (std::string(argv[2]) == "books") {
                std::string username = argv[3];
                borrowBooks(username);
            } else {
                std::cout << Colors::RED << "Error: Invalid borrow command." << Colors::RESET << std::endl;
                printUsage();
                return 1;
            }
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