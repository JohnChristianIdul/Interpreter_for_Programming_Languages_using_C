#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define MAX_LENGTH 100

// Token types
typedef enum {
    TOKEN_IDENTIFIER, // 0
    TOKEN_NUMBER, // 1
    TOKEN_DELIMITER, // 2
    TOKEN_OPERATOR, // 3
    TOKEN_KEYWORD, // 4
    TOKEN_UNKNOWN // 5
} TokenType;

typedef struct {
    TokenType type;
    char *value;
    int line;
    int column;
} Token;

// Function to check for a delimiter
int isDelimiter(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r'
           || ch == '{' || ch == '}' || ch == '[' || ch == ']' || ch =='(' || ch == ')'
           || ch == ',' || ch == ';' || ch == ':' || ch == '.' || ch == '\'' || ch == '\"'
           || ch == '\\' || ch == '#' || ch == '<' || ch == '>' || ch == '&' || ch == '|'
           || ch == '~' || ch == '?' || ch == '!' || ch == '@' || ch == '$' || ch == '%';
}

// Function to check for a valid operator
bool isOperator(char chr) {
    return (chr == '+' || chr == '-' || chr == '*'
            || chr == '/' || chr == '>' || chr == '<'
            || chr == '=');
}

// Function to check for a valid identifier
bool isValidIdentifier(char* str) {
    return (isalpha(str[0]) || str[0] == '_');
}

// Function to check for a keyword
bool isKeyword(char* str) {
    const char* keywords[] = { "if", "else", "for", "while", "int", "float", "return",
                               "break", "continue", "case", "char", "do", "double",
                               "switch", "default" };
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Function to tokenize the input source code
Token* lex(char *input) {
    Token *tokens = malloc(sizeof(Token) * strlen(input)); // Allocate memory for tokens
    int tokenIndex = 0;
    int inputLength = strlen(input);

    int i = 0;
    while (i < inputLength) {
        // Tokenizing delimiters
        if (isDelimiter(input[i])) {
            char *value = malloc(2);
            value[0] = input[i];
            value[1] = '\0';
            tokens[tokenIndex].type = TOKEN_DELIMITER;
            tokens[tokenIndex].value = value;
            tokenIndex++;
            i++;
            continue;
        }

        // Tokenizing identifiers and keywords
        if (isalpha(input[i]) || input[i] == '_') {
            int start = i;
            while (isalnum(input[i]) || input[i] == '_') {
                i++;
            }
            int length = i - start;
            char *value = malloc(length + 1);
            strncpy(value, input + start, length);
            value[length] = '\0';
            if (isKeyword(value)) {
                tokens[tokenIndex].type = TOKEN_KEYWORD;
            } else {
                tokens[tokenIndex].type = TOKEN_IDENTIFIER;
            }
            tokens[tokenIndex].value = value;
            tokenIndex++;
            continue;
        }

        // Tokenizing numbers
        if (isdigit(input[i])) {
            int start = i;
            while (isdigit(input[i])) {
                i++;
            }
            int length = i - start;
            char *value = malloc(length + 1);
            strncpy(value, input + start, length);
            value[length] = '\0';
            tokens[tokenIndex].type = TOKEN_NUMBER;
            tokens[tokenIndex].value = value;
            tokenIndex++;
            continue;
        }

        // Tokenizing operators
        if (isOperator(input[i])) {
            char *value = malloc(2);
            value[0] = input[i];
            value[1] = '\0';
            tokens[tokenIndex].type = TOKEN_OPERATOR;
            tokens[tokenIndex].value = value;
            tokenIndex++;
            i++;
            continue;
        }
    }

    // Add termination token
    tokens[tokenIndex].type = TOKEN_UNKNOWN;
    tokens[tokenIndex].value = NULL;

    return tokens;
}


int main() {
    // Input 01
    char lex_input[MAX_LENGTH] = "int a = b + c";
    printf("For Expression \"%s\":\n", lex_input);
    Token* tokens = lex(lex_input);
    for (int i = 0; tokens[i].type != TOKEN_UNKNOWN; i++) {
        printf("Token type: %d, Value: %s\n", tokens[i].type, tokens[i].value);
        free(tokens[i].value); // Free memory allocated for token value
    }
    free(tokens); // Free memory allocated for tokens
    printf("\n");

    // Input 02
    char lex_input01[MAX_LENGTH] = "int x=ab+bc+30+switch+ 0y ";
    printf("For Expression \"%s\":\n", lex_input01);
    tokens = lex(lex_input01);
    for (int i = 0; tokens[i].type != TOKEN_UNKNOWN; i++) {
        printf("Token type: %d, Value: %s\n", tokens[i].type, tokens[i].value);
        free(tokens[i].value); // Free memory allocated for token value
    }
    free(tokens); // Free memory allocated for tokens

    // Input 03
    char lex_input02[MAX_LENGTH] = "int if else = v +c ";
    printf("For Expression \"%s\":\n", lex_input02);
    tokens = lex(lex_input02);
    for (int i = 0; tokens[i].type != TOKEN_UNKNOWN; i++) {
        printf("Token type: %d, Value: %s\n", tokens[i].type, tokens[i].value);
        free(tokens[i].value); // Free memory allocated for token value
    }
    free(tokens); // Free memory allocated for tokens

    // Input 03
    char lex_input03[MAX_LENGTH] = "int if else = v +c \\ @ # / \\ \" \'";
    printf("For Expression \"%s\":\n", lex_input03);
    tokens = lex(lex_input03);
    for (int i = 0; tokens[i].type != TOKEN_UNKNOWN; i++) {
        printf("Token type: %d, Value: %s\n", tokens[i].type, tokens[i].value);
        free(tokens[i].value); // Free memory allocated for token value
    }
    free(tokens); // Free memory allocated for tokens

    return 0;
}