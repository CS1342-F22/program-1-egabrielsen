#include <iostream>
#include <string>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::string;

enum CHOICE { QUIT, DECIMAL_TO_BINARY, BINARY_TO_DECIMAL };

// Function Definitions
// flow functions
CHOICE get_choice();

void display_options();

void encode_or_decode(CHOICE choice);

void encode();

void decode();

// utility functions
int binary_to_decimal(int);

int decimal_to_binary(int);

/**
 * Starting point
 * @return
 */
int main() {
    CHOICE choice;

    do {
        choice = get_choice();

        if (choice == QUIT) {
            cout << "\nThank you!!" << endl;
            continue;
        }

        encode_or_decode(choice);
    } while (choice != QUIT);

    return 0;
}

/**
 * Decision on which operation to perform
 * @param choice
 */
void encode_or_decode(CHOICE choice) {
    switch (choice) {
        case DECIMAL_TO_BINARY:
            encode();
            break;
        case BINARY_TO_DECIMAL:
            decode();
            break;
        default:
            std::cerr << "invalid choice" << endl;
    }
}

/**
 * Convert string into series of bytes
 */
void encode() {
    cout << "\nEnter a sentence to be encoded (ending in a period): ";

    string word;
    getline(cin, word);

    cout << "\nEncoded String: ";
    // parse each letter from word
    for (char c: word) {
        int c_number = static_cast<int>(c);
        int binary = decimal_to_binary(c_number);
        cout << binary << " ";
    }

    cout << endl
         << endl;
}

/**
 * Decode the bytes and convert to string
 */
void decode() {
    int value;
    string decodedString;

    cout << "\nEnter a series of bytes to decode: ";

    do {
        // read in byte
        cin >> value;

        // if value read is a period (in binary), stop decoding
        if (value == 101110) {
            decodedString += (char) (binary_to_decimal(value));
            break;
        }

        decodedString += (char) (binary_to_decimal(value));
    } while (value != 0);

    cout << "\nDecoded String: ";
    cout << decodedString << endl
         << endl;
}

/**
 * Converts a binary number to a decimal number
 * @param binary_number
 * @return
 */
int binary_to_decimal(int binary_number) {
    int decimal{0};
    int position{0};
    while (binary_number != 0) {
        int remainder = binary_number % 10;

        decimal += remainder * std::pow(2, position);
        binary_number /= 10;
        position++;
    }

    return decimal;
}

/**
 * convert decimal number to binary number
 * @param decimal
 * @return
 */
int decimal_to_binary(int decimal) {
    int binary{0};
    int i{1};
    while (decimal != 0) {
        int remainder = decimal % 2;
        binary += remainder * i;
        decimal /= 2;
        i *= 10;
    }

    return binary;
}

/**
 * Read in the choice from the console. Handle any errors
 * @return a CHOICE enum
 */
CHOICE get_choice() {
    int choice;
    do {
        display_options();
        cin >> choice;

        cin.ignore();
        cin.clear();

        // if correct choice, break from error sequence
        if (choice >= 0 && choice <= 2) {
            return static_cast<CHOICE>(choice);
        }

        cout << "\nERROR: You selected an invalid choice, please try again\n"
             << endl;
    } while (choice < 0 || choice > 2);
}

/**
 * Display the list of options
 */
void display_options() {
    cout << "Please select an option: " << endl;
    cout << "1) Encode a sentence" << endl;
    cout << "2) Decode binary" << endl;
    cout << "0) Quit" << endl;
    cout << "Select Choice (1, 2, or 0): ";
}