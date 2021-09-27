#include "parser.h"

bool SemanticParser::is_opening_character(char candidate) {
    return candidate == '(' || candidate == '{' || candidate == '[';
}

bool SemanticParser::is_closing_character(char candidate) {
    return candidate == ')' || candidate == '}' || candidate == ']';
}

bool SemanticParser::are_complimentary_characters(char opening, char closing) {
    return (opening == '(' && closing == ')')
            || (opening == '{' && closing == '}')
            || (opening == '[' && closing == ']');
}

bool SemanticParser::is_balanced(std::string code) {
    SimpleCharStack stack;

    for (int i = 0; i < code.size(); i++) {
        if (is_opening_character(code[i])) {
            stack.push(code[i]);
        } else if (is_closing_character(code[i])) {
            if (!are_complimentary_characters(stack.peek(), code[i])) {
                return false;
            }

            stack.pop();
        }
    }

    return stack.size() == 0;
}

void SemanticParser::SimpleCharStack::push(char item) {
    stack[stack_size++] = item;
}

char SemanticParser::SimpleCharStack::pop() {
    return stack[--stack_size];
}

char SemanticParser::SimpleCharStack::peek() {
    return stack[stack_size-1];
}

int SemanticParser::SimpleCharStack::size() {
    return stack_size;
}