#include <string>

class SemanticParser
{
public:
    SemanticParser();

    // Call this method to parse the provided code
    static bool is_balanced(std::string code);

private:
    // add any private members you think are necessary.
    //
    // I highly recommend making a separate stack class and writing the tests
    // to validate its behavior - maintaining an array in this class is "easier"
    // but will likely hide a bug in your stack implementation that you will
    // believe to be a bug in your parsing. You have been warned.
};