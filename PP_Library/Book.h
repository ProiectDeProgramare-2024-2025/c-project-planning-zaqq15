#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
private:
    std::string isbn;
    std::string title;
    std::string author;
    int quantity;

public:
    // Constructors
    Book();
    Book(const std::string& isbn, const std::string& title, const std::string& author, int quantity);
    
    // Getters
    std::string getIsbn() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    int getQuantity() const;
    
    // Setters
    void setIsbn(const std::string& isbn);
    void setTitle(const std::string& title);
    void setAuthor(const std::string& author);
    void setQuantity(int quantity);
    
    // Utility methods
    std::string toString() const;
    bool isValid() const;
};

#endif