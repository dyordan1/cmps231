#include <fstream>
#include <memory>
#include <iostream>
#include "trie.h"

using namespace std;

enum Mode {
    INTERACTIVE = 1,
    // Both small and large tree use the data from this github repo:
    // https://github.com/dwyl/english-words
    SMALL_DICT = 2,
    LARGE_DICT = 3
};

// Switch this constant to change the program behavior
// You must run make again :)
const Mode MODE = Mode::INTERACTIVE;

// Creates a trie out of a file. A good opportunity for you to learn about smart
// pointers... or just treat this as returning Trie* and ignore that part.
unique_ptr<Trie> _trie_from_file(string filename) {
    auto t = make_unique<Trie>();
    ifstream words_file(filename);
    std::string word;
    while (std::getline(words_file, word))
    {
        t->insert(word);
    }
    // When a unique_ptr is moved (like in a return), it transfers ownership.
    return t;
}

// Creates a trie out of user input. Collects words until empty string is given.
unique_ptr<Trie> _trie_from_input() {
    auto t = make_unique<Trie>();
    string word;
    do {
        cout << "Enter word to add to trie or press enter to stop:";
        std::getline (std::cin, word);
        if (!word.empty()) {
            t->insert(word);
        }
    } while (!word.empty());
    return t;
}

// Queries a given trie with words given by the user.
void _query_trie(const Trie& t) {
    string word;
    do {
        cout << "Enter prefix to search trie or press enter to stop:";
        std::getline (std::cin, word);
        if (!word.empty()) {
            for (auto word : t.complete(word)) {
                cout << word << endl;
            }
        }
    } while (!word.empty());
}

int main()
{
    unique_ptr<Trie> t;
    switch (MODE) {
        case INTERACTIVE:
            t = _trie_from_input();
            cout << "Resulting tree:" << endl << t->to_string();
            _query_trie(*t);
            break;
        case LARGE_DICT:
            t = _trie_from_file("../words_alpha.txt");
            _query_trie(*t);
            break;
        case SMALL_DICT:
            t = _trie_from_file("../words_alpha_short.txt");
            _query_trie(*t);
            break;
    }

    // If you did decide to learn about smart pointers... notice how we never
    // need to delete t? That's why they're called smart!
}