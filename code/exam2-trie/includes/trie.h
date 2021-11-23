#include <string>
#include "node.h"

class TrieInspector;

// A class that represents a (prefix) trie. For this implementation, we will
// only implement an insert and "find" method, where the find will search for
// prefix matches and return them all alphabetically.
class Trie
{
public:
    Trie()
    {
        // Unlike a BST - a trie must always have a root - otherwise we'd need
        // to keep track of a list of nodes that are all the possible starting
        // letters, in which case it would be a trie forest :)
        // The actual value of root is irrelevant - we should never use it.
        root = new node('\0');
    }
    ~Trie()
    {
        // Just like in BST - we're deleting the root and letting that trickle.
        delete root;
    }

    // Insert a word into the trie.
    void insert(std::string value)
    {
        _insert(root, value);
    }

    // Find all words in the trie that match the given prefix.
    std::vector<std::string> complete(std::string prefix) const
    {
        return _find_with_prefix(root, prefix);
    }

    // Debug utility to stringify the tree.
    std::string to_string()
    {
        return root->to_string("");
    }

private:
    node *root;
    // For (bad) tests
    friend TrieInspector;

    // Internal method to add a string to a trie node.
    void _insert(node* tree, std::string value)
    {
        // Implement this.
    }

    // Internal method to find a prefix starting at a trie node.
    std::vector<std::string> _find_with_prefix(node* tree, std::string prefix) const
    {
        // Implement this.
        return {};
    }

    // Fetch all words starting one level deeper than the provided node.
    std::vector<std::string> _get_all_after_node(node* tree) const
    {
        // This one is done for you, since it can be tricky.
        std::vector<std::string> results;
        for (auto child : tree->get_children())
        {
            // For each child of the given root - we check the value.
            char next = child->get_value();
            if (next == '\0')
            {
                // If the *next* node has '\0', the *given* node is the end of
                // a word. The empty string here will be prefixed at the caller
                // to make the word.
                results.push_back("");
                continue;
            }

            // We recursively call the completion method at the child as well.
            for (auto res : _get_all_after_node(child))
            {
                // Each grandchild word returned, prepended with the child value
                // makes a child word.
                results.push_back(next + res);
            }
        }
        return results;
    }
};