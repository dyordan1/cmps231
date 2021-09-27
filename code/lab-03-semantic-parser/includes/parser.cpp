#include "parser.h"

SemanticParser::SemanticParser()
{
    // Initialize the contents of your list.
}

bool SemanticParser::is_balanced(std::string code)
{
    // Implementing this algorithm is up to you.
    // Coming up with it, however - is not.
    //
    // You will:
    //   * iterate over the incoming code in order
    //   * check whether the current character is a recognized structural element:
    //     * [ { ( ] } )
    //   * only if it is - either push on the stack or compare to top of stack
    //   * a closing character will *only* ever be balanced if the top of the
    //     stack is the appropriate opening character
    //   * In the event you exhaust the entire string and you haven't found a
    //     mismatched character, the sequence is balanced.
    return true;
}