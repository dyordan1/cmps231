#include <iostream>
#include <string>
#include "parser.h"

using namespace std;
int main()
{
    cout << "Type an expression (one line only):" << endl;
    
    string code;
    getline (cin, code);
    cout << "That expression " << (SemanticParser::is_balanced(code) ? "is" : "is not") << " balanced." << endl;
}