#include "Book.h"
#include <sstream>

// Constructors
Book::Book() : isbn(""), title(""), author(""), quantity(0) {}

Book::Book(const std::string& isbn, const std::string& title, const std::string& author, int quantity)
    : isbn(isbn), title(title), author(author), quantity(quantity) {}

// Getters
std::string Book::getIsbn() const { return isbn; }
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
int Book::getQuantity() const { return quantity; }

// Setters
void Book::setIsbn(const std::string& isbn) { this->isbn = isbn; }
void Book::setTitle(const std::string& title) { this->title = title; }
void Book::setAuthor(const std::string& author) { this->author = author; }
void Book::setQuantity(int quantity) { this->quantity = quantity; }

// Utility methods
std::string Book::toString() const {
    std::ostringstream oss;
    oss << isbn << " " << title << " " << author << " " << quantity;
    return oss.str();
}

bool Book::isValid() const {
    return !isbn.empty() && !title.empty() && !author.empty() && quantity >= 0;
}