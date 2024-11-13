#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

//defines the different types of tokens
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

//represents a token with its type and value
struct Token {
    TokenType type;
    string value;

    Token(TokenType t, const string& v) : type(t), value(v) {
    };
};

//implements lexical analyser
class Lexer {
private:
    string input;
    size_t position;
    unordered_map<string, TokenType> keywords;


    /**
     * Initializes the keywords map with the known keywords
     */
    void initKeywords() {
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

    
    /// @brief Returns true if character is a whitespace.
    ///
    /// Checks if character is a whitespace.
    ///
    /// @param c The character to check.
    ///
    /// @return True if character is a whitespace, else false.
    bool isWhitespace(char c) {
        return c == ' ' || c == '\t' || c == '\n' || c == '\r';
    }

    /// @brief Returns true if character is an alphabet or a digit.
    ///
    /// Checks if the character is either an uppercase or lowercase alphabet letter
    /// or a digit (0-9).
    ///
    /// @param c The character to check.
    ///
    /// @return True if character is an alphabet letter or digit, else false.
    bool isAlpha(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
    }

    /// @brief Checks if character is a digit (0-9).
    ///
    /// Returns true if character is a digit, else false.
    ///
    /// @param c The character to check.
    ///
    /// @return True if character is a digit, else false.
    bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    /// @brief Checks if character is alphanumeric.
    ///
    /// Returns true if character is either an alphabet letter or digit (0-9).
    ///
    /// @param c The character to check.
    ///
    /// @return True if character is alphanumeric, else false.
    bool isAlphaNumeric(char c) {
        return isAlpha(c) || isDigit(c);
    }

    /// @brief Extracts the next alphanumeric word from the input string.
    ///
    /// Scans the input string starting from the current position and extracts
    /// the next sequence of alphanumeric characters, updating the position
    /// to point to the first non-alphanumeric character after the word.
    ///
    /// @return The next alphanumeric word from the input string.
    string getNextWord() {
        size_t start = position;
        while (position < input.length() && isAlphaNumeric(input[position])) {
            position++;
        }
        return input.substr(start, position - start);
    }

    /// @brief Extracts the next numeric value from the input string.
    ///
    /// Scans the input string starting from the current position and extracts
    /// the next sequence of digits, including a decimal point if present,
    /// treating it as a floating-point number. Updates the position to
    /// point to the first non-digit character after the number.
    ///
    /// @return The next numeric value from the input string as a string.
    string getNextNumber() {
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

    public:
    /// @brief Constructor for Lexer.
    ///
    /// Initializes the lexer with the given input string and initializes
    /// the position to 0.
    ///
    /// @param input The string to be lexically analyzed.
    Lexer(const string& input) : input(input), position(0) {
        initKeywords();
    }

    /// @brief Tokenizes the input string into a sequence of Tokens.
    ///
    /// Scans the input string and breaks it up into a sequence of Tokens,
    /// where each Token represents a single lexical unit such as a keyword,
    /// identifier, string literal, numeric literal, or symbol.
    ///
    /// @return A vector of Tokens representing the input string.
    ///
    vector<Token> tokenize() {
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
                TokenType type = TokenType::Integer;
                if (number.find('.') != string::npos) {
                    type = TokenType::Float;
                
                tokens.push_back(Token(type, number));
            } else {
                position++;
            }
            
        }
            // Identify Arithmetic Operators
            else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '//' || c == '%') {
                tokens.push_back(Token(TokenType::Operator, string(1, c)));
                position++;
            }

            /// @brief Handles delimiters such as parentheses, colons, and brackets.
            ///
            /// If the current character is a delimiter, adds a Token of type
            /// delimiter to the list of tokens and increments the position by 1.
            ///
            /// @note The colons are handled separately because we want to
            ///       distinguish between the `:` and `::` tokens.
            else if (c == '(' || c == ')' || c == ':' || c == ':3' || c == '[' || c == ']') {
                tokens.push_back(Token(TokenType::Delimiter, string(1, c)));
                position++;
            }
            else {
                tokens.push_back(Token(TokenType::Unknown, string(1, c)));
                position++;
            }
            return tokens;
    }
};

/**
 * @brief Returns a string representing the given TokenType.
 *
 * @param type The TokenType to get the string for.
 *
 * @return A string representing the given TokenType.
 */
string getTokenTypeName(TokenType type) {
    switch (type) {
        case TokenType::Keyword:
            return "keyword";
        case TokenType::Identifier:
            return "identifier";
        case TokenType::Integer:
            return "integer";
        case TokenType::Float:
            return "float";
        case TokenType::String:
            return "string";
        case TokenType::Operator:
            return "operator";
        case TokenType::Delimiter:
            return "delimiter";
        case TokenType::Unknown:
            return "unknown";
        default:
            return "unknown";
    }
}


/**
 * @brief Prints the given tokens to the console.
 *
 * Iterates over the given vector of tokens and prints each one to the console
 * with its type and value.
 *
 * @param tokens The vector of tokens to be printed.
 */
void printTokens(const vector<Token>& tokens) {
    for (const auto& token : tokens) {
        cout << "Token: " << getTokenTypeName(token.type) << ", Value: " << token.value << endl;
    }
}
/**
 * @brief Main entry point of the program.
 *
 * Demonstrates how to use the Lexer class by tokenizing a simple C++ program
 * and printing the resulting tokens.
 */

/**
 * @brief Main entry point of the program.
 *
 * Demonstrates how to use the Lexer class by tokenizing a simple C++ program
 * and printing the resulting tokens.
 *
 * @code
 * int main() {
 *     string input = "int main() { return 0; }";
 *     Lexer lexer(input);
 *     vector<Token> tokens = lexer.tokenize();
 *     printTokens(tokens);
 *     return 0;
 * }
 * @endcode
 */
int main() {
    string input = "int main() { return 0; }";
    Lexer lexer(input);
    vector<Token> tokens = lexer.tokenize();
    printTokens(tokens);
    return 0;
    }
};