#ifndef LOAN_H
#define LOAN_H

#include "Book.h"
#include "Date.h"
#include <vector>
#include <string>

class Loan {
private:
    std::string user;
    std::vector<Book> borrowedBooks;
    Date loanDate;

public:
    // Constructors
    Loan();
    Loan(const std::string& user, const std::vector<Book>& borrowedBooks, const Date& loanDate);
    
    // Getters
    std::string getUser() const;
    std::vector<Book> getBorrowedBooks() const;
    Date getLoanDate() const;
    
    // Setters
    void setUser(const std::string& user);
    void setBorrowedBooks(const std::vector<Book>& borrowedBooks);
    void setLoanDate(const Date& loanDate);
    
    // Utility methods
    void addBook(const Book& book);
    std::string toString() const;
    bool isValid() const;
};

#endif