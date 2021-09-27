#include <string>

class SemanticParser
{
public:
    // Returns true if the brackets in the given expression are balanced
    static bool is_balanced(std::string code);

private:
    // A helper class to maintain apropriate abstraction.
    // This could just as easily be a public class in a dependency lib - in
    // fact, that would make it testable, and thus more desirable!
    class SimpleCharStack {
    public:
        // Adds a single character to the stack.
        void push(char element);

        // Removes the top of the stack.
        char pop();

        // Takes a look at the top of the stack, *without* modifying it.
        char peek();

        // Returns the size of the stack.
        int size();

    private:
        // The stack contents.
        char stack[100];

        // The stack size.
        int stack_size = 0;
    };

    // Returns true if the given character is one of ( [ {
    static bool is_opening_character(char candidate);

    // Returns true if the given character is one of ) ] }
    static bool is_closing_character(char candidate);
    
    // Returns true if the given characters are matching - i.e. [ and ], etc.
    static bool are_complimentary_characters(char opening, char closing);
};