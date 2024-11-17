#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

/// @brief Defines the different types of tokens.
enum class TokenType {
    Keyword,
    Identifier,
    Integer,
    Float,
    String,
    Operator,
    Delimiter,
    Unknown
};

/// @brief Represents a token with its type and value.
struct Token {
    TokenType type;
    std::string value;

    Token(TokenType t, const std::string& v);
};

/// @brief Implements a lexical analyzer for tokenizing input strings.
class Lexer {
private:
    std::string input;
    size_t position;
    std::unordered_map<std::string, TokenType> keywords;

    void initKeywords();
    bool isWhitespace(char c);
    bool isAlpha(char c);
    bool isDigit(char c);
    bool isAlphaNumeric(char c);
    std::string getNextWord();
    std::string getNextNumber();

public:
    Lexer(const std::string& input);
    std::vector<Token> tokenize();
};

/// @brief Helper function to get the string representation of a token type.
/// @param type The token type.
/// @return The string representation of the token type.
std::string getTokenTypeName(TokenType type);

/// @brief Prints a vector of tokens.
/// @param tokens The vector of tokens to print.
void printTokens(const std::vector<Token>& tokens);

#endif // LEXER_H