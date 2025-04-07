#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;


#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
#define EOF_TOKEN -1
#define SEMICOLON 27
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

int charClass;
char nextChar;
string lexeme;
int nextToken;
ifstream inputFile;

void addChar() {
    lexeme += nextChar;
}

void getChar() {
    if (inputFile.get(nextChar)) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    } else {
        charClass = EOF_TOKEN;
    }
}

void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}

int lookup(char ch) {
    switch (ch) {
         case ';':
            addChar();
            nextToken = SEMICOLON;
            break;
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+':
            addChar();
            nextToken = ADD_OP;
            break;
        case '-':
            addChar();
            nextToken = SUB_OP;
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
        case '=':
            addChar();
            nextToken = ASSIGN_OP;
            break;
        default:
            addChar();
            nextToken = EOF_TOKEN;
            break;
    }
    return nextToken;
}

int lex() {
    lexeme = "";
    getNonBlank();

    switch (charClass) {
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = IDENT;
            break;
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;
        case UNKNOWN:
            nextToken = lookup(nextChar);
            getChar();
            break;
        case EOF_TOKEN:
            nextToken = EOF_TOKEN;
            lexeme = "EOF";
            break;
    }

    
     cout << "Next token is: " << nextToken << ", Next lexeme is: " << lexeme << endl;

     return nextToken;
}


int main() {
    inputFile.open("input.in");
    if (!inputFile) {
        cerr << "ERROR - cannot open input.in" << endl;
        return 1;
    } else {
     }

    getChar();
    do {
        lex();
    } while (nextToken != EOF_TOKEN);

    inputFile.close();
    return 0;
}
