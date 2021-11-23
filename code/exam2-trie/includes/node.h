#include <set>
#include <string>
#include <sstream>
#include <vector>

// Utility struct used to compare node* to chars and to each other.
// This needs to be templated due to the circular dependency with node.
// This is an example of SFINAE to the rescue, even though it's a very simple
// case of it :)
template <typename T>
struct CompareValue
{
    using is_transparent = void;

    bool operator()(T* const& lhs, T* const& rhs) const
    {
        return lhs->value < rhs->value;
    }

    bool operator()(const char& lhs, T* const& rhs) const
    {
        return lhs < rhs->value;
    }

    bool operator()(T* const& lhs, const char& rhs) const
    {
        return lhs->value < rhs;
    }
};

// A class representing a single node in a Trie.
class node
{
public:
    node(char value) : value(value) {}

    // Just like with BST, we recursively free memory at each node.
    ~node()
    {
        for (auto child : children) {
            delete child;
        }
    }

    // Adds an already constructed child.
    // Note this will take ownership of the given node - i.e. you should *not*
    // delete the passed value at any point.
    void add_child(node* child)
    {
        children.insert(child);
    }

    // Returns the child with the provided char value, if one exists.
    // Otherwise, returns nullptr.
    node* find_child_with_value(char value)
    {
        #if __cplusplus >= 201300
        auto found = children.find(value);
        #else
        // Prior to C++14, we need to use a temporary node to find the value.
        node* tmp = new node(value);
        auto found = children.find(tmp);
        delete tmp;
        #endif

        if (found == children.end())
        {
            return nullptr;
        }

        return *found;
    }

    // const accessors for traversal
    const char get_value() { return value; }
    const std::set<node*, CompareValue<node>> get_children() { return children; }

    // Utility function to convert the node to string for debugging.
    // You don't really need to care about how this works but you're welcome to
    // investigate.
    std::string to_string(std::string indent)
    {
        std::ostringstream output;
        output << indent;

        // "collate" chains of characters with no branching.
        auto branch = this;
        output << indent;
        while (branch->children.size() == 1)
        {
          auto out_val = (branch->value == 0 ? "\\0" : std::string(1, branch->value));
          output << out_val;
          branch = *branch->children.begin();
        }
        
        auto out_val = (branch->value == 0 ? "\\0" : std::string(1, branch->value));
        output << out_val << std::endl;
      
        for (auto child : branch->children)
        {
            output << child->to_string("  " + indent);
        }

        return output.str();
    }

private:
    // We are making value private this time - we want to only access nodes via
    // find_child_with_value to prevent duplicates.
    char value;
    // But... we want our compare utility to have access to it.
    friend CompareValue<node>;

    // Don't be too alarmed by this definition...
    // Fundamentally, this is a set<node*> - meaning it stores node* values in a
    // tree. CompareValue simply defines how to compare the items to define
    // "smaller" and gives us the utility of using .find with char type.
    // Finally, decltype just means "the type of this thing" - which we pass
    // as a template argument to std::set.
    std::set<node*, CompareValue<node>> children;
};