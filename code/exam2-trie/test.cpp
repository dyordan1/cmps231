#define CATCH_CONFIG_MAIN

#include <set>
#include "catch.hpp"
#include "trie.h"

using namespace std;

// This is generally bad... but I'm grading you so I must do some
// "implementation checks". This breaks abstraction and is bad - don't do
// stuff like this in real tests.
class TrieInspector {
public:
    static bool has_repeat_nodes(const Trie& t)
    {
        return has_repeat_nodes(t.root);
    }
    static bool has_path(const Trie& t, string word) {
        return has_path(t.root, word);
    }

private:
    static bool has_repeat_nodes(node* n)
    {
        std::set<char> seen;
        for (auto child : n->get_children())
        {
            if (seen.find(child->get_value()) != seen.end())
            {
                return true;
            }

            seen.insert(child->get_value());
        }

        return false;
    }
    static bool has_path(node* n, string word) {
        while (!word.empty() && n != nullptr) {
            n = n->find_child_with_value(word[0]);
            word = word.substr(1);
        }

        if (n == nullptr) {
            // Incomplete path
            return false;
        }

        return n->find_child_with_value('\0') != nullptr;
    }
};

TEST_CASE("Make Trie")
{
    Trie t;

    // Get everything
    REQUIRE(t.complete("").empty());
}

/// ============
/// INSERT TESTS
/// ============

TEST_CASE("Insert - Branching")
{
    Trie t;
    t.insert("potato");
    t.insert("passenger");
    t.insert("tomato");
    t.insert("pan");
    t.insert("pass");
    t.insert("asparagus");

    REQUIRE(!TrieInspector::has_repeat_nodes(t));
}

TEST_CASE("Insert - Existence")
{
    Trie t;
    t.insert("potato");
    t.insert("passenger");
    t.insert("tomato");
    t.insert("pan");
    t.insert("pass");
    t.insert("asparagus");

    // has_path asserts:
    // * the string of characters exists in trie
    // * there is a terminator as the last node.
    REQUIRE(TrieInspector::has_path(t, "potato"));
    REQUIRE(TrieInspector::has_path(t, "passenger"));
    REQUIRE(TrieInspector::has_path(t, "tomato"));
    REQUIRE(TrieInspector::has_path(t, "pan"));
    REQUIRE(TrieInspector::has_path(t, "pass"));
    REQUIRE(TrieInspector::has_path(t, "asparagus"));
}

/// ==============
/// COMPLETE TESTS
/// ==============

TEST_CASE("Complete - Full word")
{
    Trie t;
    t.insert("potato");
    t.insert("passenger");
    t.insert("tomato");
    t.insert("pan");
    t.insert("pass");
    t.insert("asparagus");

    auto complete = t.complete("potato");
    REQUIRE(complete.size() == 1);
    REQUIRE(complete[0] == "potato");
}

TEST_CASE("Complete - No match")
{
    Trie t;
    t.insert("potato");
    t.insert("passenger");
    t.insert("tomato");
    t.insert("pan");
    t.insert("pass");
    t.insert("asparagus");

    REQUIRE(t.complete("burrito").empty());
}

TEST_CASE("Complete - Close no match")
{
    Trie t;
    t.insert("potato");
    t.insert("passenger");
    t.insert("tomato");
    t.insert("pan");
    t.insert("pass");
    t.insert("asparagus");

    REQUIRE(t.complete("potata").empty());
}

TEST_CASE("Complete - Partial match")
{
    Trie t;
    t.insert("potato");
    t.insert("passenger");
    t.insert("tomato");
    t.insert("pan");
    t.insert("pass");
    t.insert("asparagus");

    auto complete = t.complete("pot");
    REQUIRE(complete.size() == 1);
    REQUIRE(complete[0] == "potato");
}

TEST_CASE("Complete - Multiple matches")
{
    Trie t;
    t.insert("potato");
    t.insert("passenger");
    t.insert("tomato");
    t.insert("pan");
    t.insert("pass");
    t.insert("asparagus");

    auto complete = t.complete("pass");
    REQUIRE(complete.size() == 2);
    REQUIRE(complete[0] == "pass");
    REQUIRE(complete[1] == "passenger");
}

TEST_CASE("Complete - All matches")
{
    Trie t;
    t.insert("potato");
    t.insert("passenger");
    t.insert("tomato");
    t.insert("pan");
    t.insert("pass");
    t.insert("asparagus");

    // Get everything
    auto complete = t.complete("");
    REQUIRE(complete.size() == 6);
    // If you're curious - set "sorts" everything for you at each level
    // So these must come in alpha order :)
    REQUIRE(complete[0] == "asparagus");
    REQUIRE(complete[1] == "pan");
    REQUIRE(complete[2] == "pass");
    REQUIRE(complete[3] == "passenger");
    REQUIRE(complete[4] == "potato");
    REQUIRE(complete[5] == "tomato");
}