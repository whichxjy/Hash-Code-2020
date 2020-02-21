#ifndef _BOOK_HPP_
#define _BOOK_HPP_

struct Book {
    int index;
    int score;

    Book(int index, int score) : index(index), score(score) {}
};

#endif