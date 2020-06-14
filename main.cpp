#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void textGenerator();

void frequencyAnalysis();

void findCorrectCipher();

void userCipher(const string &cipher);


int main() {

//        textGenerator();
//    frequencyAnalysis();
//  userCipher("dEemntu");

    //userCipher("nuEemtd");
    userCipher("utmEnde");

    findCorrectCipher();
    return 0;
}

void textGenerator() {
    srand(time(NULL));
    ofstream chiperedText;
    chiperedText.open("files/ciphered.txt");
    string message = "www.yousolvedit.se";
    //part 1
    string cipher1 = "dEemntu";
    int cipherCount = 0;
    int len = cipher1.length();
    vector<string> part1{"I am sorry, but frequency analysis is not the correct way to solve this problem.",
                         "But you did find this clue: Try looking for a url in the text."};
    for (auto const &line: part1) {
        for (auto chr: line) {
            int charAsInt = (int) chr;
            charAsInt = charAsInt ^ cipher1[cipherCount % len];
            chiperedText << charAsInt << " ";
            cipherCount++;
        }
        chiperedText << endl;
    }
    string cipher2 = "nuEemtd";
    string cipher3 = "utmEnde";
    ifstream shuffledChars("files/shuffledchars.txt");
    string line;
    string answer = "www.correctanswer.se";
    int answerCount = 0;
    int lineCount = 0;


    while (getline(shuffledChars, line)) {
        if (lineCount < 10) {
            if (lineCount == 5) {
                string clue1 = "wdufdfhgdksghdwww.theurlisnothorizontal.sehfkdsjlldskfdrdfkd";
                for (auto chr :clue1) {
                    int charAsInt = (int) chr;
                    charAsInt = charAsInt ^ cipher2[cipherCount % len];
                    chiperedText << charAsInt << " ";
                    cipherCount++;
                }
            } else {
                for (auto chr : line) {
                    int charAsInt = (int) chr;
                    charAsInt = charAsInt ^ cipher1[cipherCount % len];
                    chiperedText << charAsInt << " ";
                    cipherCount++;
                }
            }
        } else {
            for (int i = 0; i < line.length(); i++) {
                if (answerCount < answer.size() && lineCount > 15 && i == 5) {
                    int charAsInt = (int) answer[answerCount];
                    charAsInt = charAsInt ^ cipher3[cipherCount % len];
                    chiperedText << charAsInt << " ";
                    cipherCount++;
                    answerCount++;

                } else {
                    int charAsInt = (int) line[i];
                    charAsInt = charAsInt ^ cipher1[cipherCount % len];
                    chiperedText << charAsInt << " ";
                    cipherCount++;
                }
            }
        }
        chiperedText << endl;
        lineCount++;
    }

    shuffledChars.close();
    chiperedText.close();
}

void frequencyAnalysis() {
    ifstream inputCiphers("files/PossibleCiphers.txt");
    string line;
    vector<string> possibleCiphers;
    while (getline(inputCiphers, line)) {
        possibleCiphers.emplace_back(line);
    }
    inputCiphers.close();

    int charCount = 0;
    int eCount = 0;
    for (auto cipher : possibleCiphers) {
        ifstream inputFile("files/ciphered.txt");
        int cipherCount = 0;
        int cipherLength = cipher.length();

        string tempLine;
        while (getline(inputFile, tempLine)) {
            stringstream ss(tempLine);
            std::string token;

            while (std::getline(ss, token, ' ')) {
                charCount++;
                int i = stoi(token);
                char maybeE = i ^cipher[cipherCount % cipherLength];
                if (maybeE == 'e') {
                    eCount++;
                }
                cipherCount++;
            }

        }
        double ratio = ((double) eCount) / ((double) charCount);
        if (ratio > 0.1) {
            cout << cipher << " " << eCount << " " << charCount << " " << ratio << endl;
        }

        charCount = 0;
        eCount = 0;
        inputFile.close();
    }
}

void userCipher(const string &cipher) {
    ifstream inputFile("files/ciphered.txt");
    string tempLine;
    int cipherCount = 0;
    int cipherLength = cipher.length();
    while (getline(inputFile, tempLine)) {
        stringstream ss(tempLine);
        std::string token;

        while (std::getline(ss, token, ' ')) {

            int i = stoi(token);
            char chr = i ^cipher[cipherCount % cipherLength];
            cout << chr;
            cipherCount++;
        }
        cout << endl;
    }
    inputFile.close();
}


void findCorrectCipher() {

    ifstream inputCiphers("files/PossibleCiphers.txt");
    string line;
    vector<string> possibleCiphers;
    while (getline(inputCiphers, line)) {
        possibleCiphers.emplace_back(line);
    }

    char c;

    for (auto cipher : possibleCiphers) {
        ifstream inputFile("files/ciphered.txt");
        vector<vector<char> > matrix;
        int cipherCounter = 0;
        int len = cipher.length();
        string tempLine;
        // I have to read this split by space.

        while (getline(inputFile, tempLine)) {

            stringstream ss(tempLine);
            std::string token;
            vector<int> ints;
            while (std::getline(ss, token, ' ')) {
                ints.push_back(stoi(token));
            }
            vector<char> chars;
            for (int i: ints) {
                c = i ^ cipher[cipherCounter % len];
                cipherCounter++;
                chars.emplace_back(c);
            }
            matrix.emplace_back(chars);

        }

        inputFile.close();

        bool foundWWW = false;
        bool foundSE = false;
        bool foundHorizontal = false;
        int iIdx = 0;
        int jIdx = 0;
        for (int i = 0; i < matrix.size(); i++) { // rows
            for (int j = 0; j < matrix[i].size(); j++) { // columns

                if (j + 4 < matrix[i].size() && matrix[i][j] == 'w' && matrix[i][j + 1] == 'w' &&
                    matrix[i][j + 2] == 'w' && matrix[i][j + 3] == '.') {
                    foundHorizontal = true;
                    iIdx = i;
                    jIdx = j;
                }

                if (i + 4 < matrix.size() && matrix[i][j] == 'w' && matrix[i + 1][j] == 'w' &&
                    matrix[i + 2][j] == 'w' && matrix[i + 3][j] == '.') {
                    foundWWW = true;
                    iIdx = i;
                    jIdx = j;
                }
                if (i + 2 < matrix.size() && matrix[i][j] == '.' && matrix[i + 1][j] == 's' &&
                    matrix[i + 2][j] == 'e') {
                    foundSE = true;
                }
            }
        }

        if (foundHorizontal) {
            cout << iIdx << " " << jIdx << " horizontal: " << cipher << endl;
        }

        if (foundWWW) {
            cout << iIdx << " " << jIdx << " vertical: " << cipher << endl;
        }
    }
}