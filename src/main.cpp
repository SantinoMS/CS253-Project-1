#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string encrypt(string plaintext, int key);
string decrypt(string ciphertext, int key);
void encryptFile(string inputFileName, string outputFileName, int key);
void decryptFile(string inputFileName, string outputFileName, int key);

int main() {
    int choice;
    string inputFile, outputFile;
    int key;

    cout << "1. Encrypt a file\n";
    cout << "2. Decrypt a file\n";
    cout << "Enter your choice: ";
    cin >> choice;

    cout << "Enter the input file name: ";
    cin >> inputFile;
    cout << "Enter the output file name: ";
    cin >> outputFile;
    cout << "Enter the encryption/decryption key (positive non-zero integer): ";
    cin >> key;

    if (choice == 1) {
        encryptFile(inputFile, outputFile, key);
    } else if (choice == 2) {
        decryptFile(inputFile, outputFile, key);
    } else {
        cout << "Invalid choice." << endl;
    }

    return 0;
}

string encrypt(string plaintext, int key) {
    string encryptedText = "";
    const int ROW = key, COL = (plaintext.size()+key-1)/key;
    unsigned char table [ROW][COL];
    memset(table, '\0', sizeof(table));

    for (int i=0; i<plaintext.size(); i++) {
        int row = i / COL, col = i % COL;
        unsigned char c = plaintext[i] + key;
        table[row][col] = c;
    }
    int count = 0;
    for (int i=0; i<COL; i++) {
        for (int j=0; j<ROW; j++) {
            if (count < plaintext.size()) {
                encryptedText += table[j][i];
                count++;
            }
        }
    }
    return encryptedText;
}

string decrypt(string ciphertext, int key) {
    string decryptedText = "";
    const int ROW = key, COL = (ciphertext.size()+key-1)/key;
    unsigned char table [ROW][COL];
    memset(table, '\0', sizeof(table));

    int n = 0;
    for (int i=0; i<COL; i++) {
        for (int j=0; j<ROW; j++) {
            if (n < ciphertext.size()) {
                table[j][i] = ciphertext[n]-key;
                n++;
            }
        }
    }
    for (int i = 0; i<ciphertext.size(); i++) {
        int row = i / COL, col = i % COL;
        decryptedText += (char)table[row][col];
    }
    return decryptedText;
}

void encryptFile(string inputFileName, string outputFileName, int key) {
    ifstream inputFile(inputFileName, ios::binary);
    ofstream outputFile(outputFileName + ".txt", ios::binary);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    string plaintext((istreambuf_iterator<char>(inputFile)),
                     istreambuf_iterator<char>());
    
    string encrypted = encrypt(plaintext, key);
    outputFile.write(encrypted.c_str(), encrypted.size());

    inputFile.close();
    outputFile.close();
}

void decryptFile(string inputFileName, string outputFileName, int key) {
    ifstream inputFile(inputFileName + ".txt", ios::binary);
    ofstream outputFile(outputFileName + ".txt", ios::binary);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    string ciphertext((istreambuf_iterator<char>(inputFile)),
                      istreambuf_iterator<char>());
    
    string decrypted = decrypt(ciphertext, key);
    outputFile.write(decrypted.c_str(), decrypted.size());

    inputFile.close();
    outputFile.close();
}