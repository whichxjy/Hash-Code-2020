#ifndef _LIBRARY_HPP_
#define _LIBRARY_HPP_

#include <queue>
#include "Book.hpp"

struct Library {
private:
    // max heap for books
    std::function<bool(Book, Book)> cmp = [](const Book& lhs, const Book& rhs) -> bool {
        return lhs.score < rhs.score;
    };
public:
    int index;
    int signup_day;
    int scan_num;
    std::priority_queue<Book, std::vector<Book>, decltype(cmp)> books;

    Library() = default;
    Library(int index, int signup_day, int scan_num)
    : index(index), signup_day(signup_day), scan_num(scan_num), books(cmp) {}
};

#endif