#include "lexer.h"

using namespace std;

Token::Token(TokenType t, const string& v) : type(t), value(v) { }

Lexer::Lexer(const string& input) : input(input), position(0) {
    initKeywords();
}

void Lexer::initKeywords() {
    keywords["int"] = TokenType::Keyword;
    keywords["float"] = TokenType::Keyword;
    keywords["string"] = TokenType::Keyword;
    keywords["if"] = TokenType::Keyword;
    keywords["else"] = TokenType::Keyword;
    keywords["while"] = TokenType::Keyword;
    keywords["for"] = TokenType::Keyword;
    keywords["switch"] = TokenType::Keyword;
    keywords["case"] = TokenType::Keyword;
    keywords["default"] = TokenType::Keyword;
    keywords["break"] = TokenType::Keyword;
    keywords["continue"] = TokenType::Keyword;
    keywords["return"] = TokenType::Keyword;
    keywords["void"] = TokenType::Keyword;
}

bool Lexer::isWhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool Lexer::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool Lexer::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Lexer::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}

string Lexer::getNextWord() {
    size_t start = position;
    while (position < input.length() && isAlphaNumeric(input[position])) {
        position++;
    }
    return input.substr(start, position - start);
}

string Lexer::getNextNumber() {
    size_t start = position;
    bool isFloat = false;
    while (position < input.length() && (isDigit(input[position]) || input[position] == '.')) {
        if (input[position] == '.') {
            isFloat = true;
        }
        position++;
    }
    return input.substr(start, position - start);
}

vector<Token> Lexer::tokenize() {
    vector<Token> tokens;
    while (position < input.length()) {
        char c = input[position];
        if (isWhitespace(c)) {
            position++;
        } else if (isAlpha(c)) {
            string word = getNextWord();
            TokenType type = keywords.find(word) != keywords.end() ? keywords[word] : TokenType::Identifier;
            tokens.push_back(Token(type, word));
        } else if (isDigit(c)) {
            string number = getNextNumber();
            TokenType type = number.find('.') != string::npos ? TokenType::Float : TokenType::Integer;
            tokens.push_back(Token(type, number));
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
            tokens.push_back(Token(TokenType::Operator, string(1, c)));
            position++;
        } else if (c == '(' || c == ')' || c == ':' || c == '[' || c == ']') {
            tokens.push_back(Token(TokenType::Delimiter, string(1, c)));
            position++;
        } else {
            tokens.push_back(Token(TokenType::Unknown, string(1, c)));
            position++;
        }
    }
    return tokens;
}

string getTokenTypeName(TokenType type) {
    switch (type) {
        case TokenType::Keyword: return "keyword";
        case TokenType::Identifier: return "identifier";
        case TokenType::Integer: return "integer";
        case TokenType::Float: return "float";
        case TokenType::String: return "string";
        case TokenType::Operator: return "operator";
        case TokenType::Delimiter: return "delimiter";
        case TokenType::Unknown: return "unknown";
        default: return "unknown";
    }
}

void printTokens(const vector<Token>& tokens) {
    for (const auto& token : tokens) {
        cout << "Token: " << getTokenTypeName(token.type) << ", Value: " << token.value << endl;
    }
}