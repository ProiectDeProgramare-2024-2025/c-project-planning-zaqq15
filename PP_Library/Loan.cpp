#include "Loan.h"
#include <sstream>

// Constructors
Loan::Loan() : user(""), borrowedBooks(), loanDate() {}

Loan::Loan(const std::string& user, const std::vector<Book>& borrowedBooks, const Date& loanDate)
    : user(user), borrowedBooks(borrowedBooks), loanDate(loanDate) {}

// Getters
std::string Loan::getUser() const { return user; }
std::vector<Book> Loan::getBorrowedBooks() const { return borrowedBooks; }
Date Loan::getLoanDate() const { return loanDate; }

// Setters
void Loan::setUser(const std::string& user) { this->user = user; }
void Loan::setBorrowedBooks(const std::vector<Book>& borrowedBooks) { this->borrowedBooks = borrowedBooks; }
void Loan::setLoanDate(const Date& loanDate) { this->loanDate = loanDate; }

// Utility methods
void Loan::addBook(const Book& book) {
    borrowedBooks.push_back(book);
}

std::string Loan::toString() const {
    std::ostringstream oss;
    oss << user << " " << loanDate.toString() << "\n";
    for (const auto& book : borrowedBooks) {
        oss << book.getIsbn() << " " << book.getQuantity() << "\n";
    }
    return oss.str();
}

bool Loan::isValid() const {
    return !user.empty() && !borrowedBooks.empty() && loanDate.isValid();
}