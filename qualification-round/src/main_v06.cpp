#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include "Book.hpp"
#include "Library.hpp"

int main(int argc, char* argv[]) {
    // try to get file name
    if (argc != 3) {
        std::cerr << "Fail to get file name." << std::endl;
        return EXIT_FAILURE;
    }

    // file to open
    const std::string input_filename = argv[1];
    // file to write
    const std::string output_filename = argv[2];

    std::ifstream infile(input_filename);
    std::ofstream outfile(output_filename);

    // Check if the file is open
    if (!infile.is_open() || !outfile.is_open()) {
        std::cerr << "Fail to open the file." << std::endl;
    }

    // ================================================================================

    int book_num;
    int library_num;
    int day_num;

    infile >> book_num >> library_num >> day_num;

    // read scores

    std::vector<int> scores;

    for (int i = 0; i < book_num; i++) {
        int score;
        infile >> score;
        scores.push_back(score);
    }

    // read libraries

    auto lib_cmp = [](const Library& lhs, const Library& rhs) -> bool {
        if (lhs.signup_day != rhs.signup_day) {
            // min
            return lhs.signup_day > rhs.signup_day;
        }
        else if (lhs.scan_num != rhs.scan_num) {
            // max
            return lhs.scan_num < rhs.scan_num;
        }
        else {
            // max
            auto lhs_books = lhs.books;
            auto rhs_books = rhs.books;
            while (!lhs_books.empty() && !rhs_books.empty()) {
                if (lhs_books.top().score != rhs_books.top().score) {
                    return lhs_books.top().score < rhs_books.top().score;
                }
                else {
                    lhs_books.pop();
                    rhs_books.pop();
                }
            }
            return true;
        }
    };

    std::priority_queue<Library, std::vector<Library>, decltype(lib_cmp)> libs(lib_cmp);

    for (int i = 0; i < library_num; i++) {
        int book_num_in_library;
        int signup_day;
        int scan_num;

        infile >> book_num_in_library >> signup_day >> scan_num;

        Library lib(i, signup_day, scan_num);

        for (int j = 0; j < book_num_in_library; j++) {
            int book_id;
            infile >> book_id;
            lib.books.emplace(book_id, scores[book_id]);
        }

        libs.emplace(lib);
    }

    // ================================================================================

    int signup_day_todo = -1;

    std::vector<Library> signuped_libs;
    std::unordered_set<int> selected_book_ids;

    // lib id -> scanned book ids
    std::unordered_map<int, std::vector<int>> scanned;

    // day by day
    for (int day = 0; day < day_num; day++) {
        // signup
        if (signup_day_todo == -1) {
            // init
            if (!libs.empty()) {
                signup_day_todo = libs.top().signup_day;
            }
        }
        else if (signup_day_todo == 0) {
            if (!libs.empty()) {
                // signup finished
                signuped_libs.push_back(libs.top());
                libs.pop();

                if (!libs.empty()) {
                    signup_day_todo = libs.top().signup_day;
                }
            }
        }

        if (signup_day_todo > 0) {
            signup_day_todo -= 1;
        }

        // scan books (for each signuped libs)
        for (auto& lib : signuped_libs) {
            int scanned_num = 0;
            // when there are still books to scan
            while (!lib.books.empty() && scanned_num < lib.scan_num) {
                // choose the book with max score
                Book curr_book = lib.books.top();
                lib.books.pop();

                // check if current book is already selected
                if (selected_book_ids.find(curr_book.index) != selected_book_ids.end()) {
                    // already selected
                    continue;
                }
                else {
                    // scan curr book
                    scanned[lib.index].push_back(curr_book.index);
                    selected_book_ids.emplace(curr_book.index);
                    scanned_num += 1;
                }
            }
        }
    }

    // ================================================================================

    // result

    int signuped_libs_size = signuped_libs.size();

    std::ostringstream lib_result;

    for (const auto& lib : signuped_libs) {
        if (scanned[lib.index].size() == 0) {
            signuped_libs_size -= 1;
        }
        else {
            lib_result << lib.index << " " << scanned[lib.index].size() << std::endl;
            for (const int book_id : scanned[lib.index]) {
                lib_result << book_id << " ";
            }
            lib_result << std::endl;
        }
    }

    outfile << signuped_libs_size << std::endl;
    outfile << lib_result.str();

    // ================================================================================

    // Close the file
    infile.close();
    outfile.close();
}