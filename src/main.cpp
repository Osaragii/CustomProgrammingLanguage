#include"lexer.h"

int main() {
    std::string input = "int main() { return 0; }";
    Lexer lexer(input);
    std::vector<Token> tokens = lexer.tokenize();
    printTokens(tokens);
    return 0;
}