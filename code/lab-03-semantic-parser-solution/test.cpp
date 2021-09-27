#define CATCH_CONFIG_MAIN

#include <sstream>
#include "catch.hpp"
#include "parser.h"

using namespace std;

TEST_CASE("Can detect balancing at one level")
{
    REQUIRE(SemanticParser::is_balanced("()"));
    REQUIRE(SemanticParser::is_balanced("{}"));
    REQUIRE(SemanticParser::is_balanced("[]"));
    REQUIRE(!SemanticParser::is_balanced("(}"));
    REQUIRE(!SemanticParser::is_balanced("(]"));
    REQUIRE(!SemanticParser::is_balanced("{)"));
    REQUIRE(!SemanticParser::is_balanced("{]"));
    REQUIRE(!SemanticParser::is_balanced("[)"));
    REQUIRE(!SemanticParser::is_balanced("[}"));
}

TEST_CASE("Can detect missing character at one level")
{
    REQUIRE(!SemanticParser::is_balanced("("));
    REQUIRE(!SemanticParser::is_balanced(")"));
    REQUIRE(!SemanticParser::is_balanced("{"));
    REQUIRE(!SemanticParser::is_balanced("}"));
    REQUIRE(!SemanticParser::is_balanced("["));
    REQUIRE(!SemanticParser::is_balanced("]"));
}

TEST_CASE("Can detect balancing with a multi-root statement")
{
    REQUIRE(SemanticParser::is_balanced("()()()"));
    REQUIRE(SemanticParser::is_balanced("{}{}{}"));
    REQUIRE(SemanticParser::is_balanced("[][][]"));
    REQUIRE(SemanticParser::is_balanced("(){}[]"));
    REQUIRE(!SemanticParser::is_balanced("[)()()"));
    REQUIRE(!SemanticParser::is_balanced("()(}()"));
    REQUIRE(!SemanticParser::is_balanced("()()(}"));
}

TEST_CASE("Can detect balancing with arbitrary characters")
{
    REQUIRE(SemanticParser::is_balanced("if (some expression) { do a thing; }"));
    REQUIRE(!SemanticParser::is_balanced("if (some expression { do a thing; }"));
    REQUIRE(!SemanticParser::is_balanced("if (some expression) { do a thing;"));

    // This builds a string that will most certainly push you over a memory
    // limit if you save every single character.
    stringstream ss;
    ss << "if (";
    string allowed_characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i=0; i<100000000; i++) {
        ss << allowed_characters[rand() % allowed_characters.size()];
    }
    ss << ") { do a thing; }";
    REQUIRE(SemanticParser::is_balanced(ss.str()));
}

TEST_CASE("Can detect nested balancing")
{
    REQUIRE(SemanticParser::is_balanced("(())"));
    REQUIRE(SemanticParser::is_balanced("({})"));
    REQUIRE(SemanticParser::is_balanced("([])"));
    REQUIRE(SemanticParser::is_balanced("{()}"));
    REQUIRE(SemanticParser::is_balanced("{{}}"));
    REQUIRE(SemanticParser::is_balanced("{[]}"));
    REQUIRE(SemanticParser::is_balanced("[()]"));
    REQUIRE(SemanticParser::is_balanced("[{}]"));
    REQUIRE(SemanticParser::is_balanced("[[]]"));
    REQUIRE(!SemanticParser::is_balanced("((})"));
    REQUIRE(!SemanticParser::is_balanced("({])"));
    REQUIRE(!SemanticParser::is_balanced("([})"));
    REQUIRE(!SemanticParser::is_balanced("{(]}"));
    REQUIRE(!SemanticParser::is_balanced("{{)}"));
    REQUIRE(!SemanticParser::is_balanced("{[)}"));
    REQUIRE(!SemanticParser::is_balanced("[(}]"));
    REQUIRE(!SemanticParser::is_balanced("[{)]"));
    REQUIRE(!SemanticParser::is_balanced("[[}]"));
}

TEST_CASE("Can detect missing character with nesting")
{
    REQUIRE(!SemanticParser::is_balanced("())"));
    REQUIRE(!SemanticParser::is_balanced("(})"));
    REQUIRE(!SemanticParser::is_balanced("(])"));
    REQUIRE(!SemanticParser::is_balanced("{)}"));
    REQUIRE(!SemanticParser::is_balanced("{}}"));
    REQUIRE(!SemanticParser::is_balanced("{]}"));
    REQUIRE(!SemanticParser::is_balanced("[)]"));
    REQUIRE(!SemanticParser::is_balanced("[}]"));
    REQUIRE(!SemanticParser::is_balanced("[]]"));
    REQUIRE(!SemanticParser::is_balanced("(()"));
    REQUIRE(!SemanticParser::is_balanced("({}"));
    REQUIRE(!SemanticParser::is_balanced("([]"));
    REQUIRE(!SemanticParser::is_balanced("{()"));
    REQUIRE(!SemanticParser::is_balanced("{{}"));
    REQUIRE(!SemanticParser::is_balanced("{[]"));
    REQUIRE(!SemanticParser::is_balanced("[()"));
    REQUIRE(!SemanticParser::is_balanced("[{}"));
    REQUIRE(!SemanticParser::is_balanced("[[]"));
}

TEST_CASE("Can detect nested balancing with arbitrary characters")
{
    REQUIRE(SemanticParser::is_balanced("if (a) {switch(b) {if(c){d}}}"));

    // Why not some JavaScript?
    string multiline_statement =
        "(function ($) {"
            "$(\"#message\").text(\"Code like it's 1999\");"
        "})(jQuery);";
    REQUIRE(SemanticParser::is_balanced(multiline_statement));

    string multiline_unbalanced_statement =
        "(function ($) {"
            "$(\"#message\").text(\"We'd never miss a bracket!\");"
        ")(jQuery);";
    REQUIRE(!SemanticParser::is_balanced(multiline_unbalanced_statement));
}

TEST_CASE("Is a cat balanced?")
{
    string kitty_cat =
        "   |\\--/|"
        "   | ,_, |"
        "   \\_`_/-..----."
        " ___/ `   ' ,""+ \\"
        "(__...'   __\\   |`.___.';"
        "  (_,...'(_,.`__)/'.....+";
    REQUIRE(!SemanticParser::is_balanced(kitty_cat));
}