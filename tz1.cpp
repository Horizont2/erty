#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

string toLowerCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

int main() {
    string inputFileName = "input.txt";
    string outputFileName = "output.txt";

    ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        cerr << "Не вдалося відкрити файл для читання: " << inputFileName << endl;
        return 1;
    }

    map<string, int> wordFrequency;

    string line, word;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        while (ss >> word) {
            word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
            word = toLowerCase(word);

            wordFrequency[word]++;
        }
    }

    inputFile.close();

    string mostFrequentWord;
    int maxFrequency = 0;
    for (const auto& [key, value] : wordFrequency) {
        if (value > maxFrequency) {
            mostFrequentWord = key;
            maxFrequency = value;
        }
    }
    cout << "Слова та їх частота:" << endl;
    for (const auto& [key, value] : wordFrequency) {
        cout << key << ": " << value << endl;
    }
    cout << "\nНайчастіше слово: " << mostFrequentWord << " (" << maxFrequency << " разів)" << endl;

    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        cerr << "Не вдалося відкрити файл для запису: " << outputFileName << endl;
        return 1;
    }

    outputFile << "Слова та їх частота:" << endl;
    for (const auto& [key, value] : wordFrequency) {
        outputFile << key << ": " << value << endl;
    }
    outputFile << "\nНайчастіше слово: " << mostFrequentWord << " (" << maxFrequency << " разів)" << endl;

    outputFile.close();

    cout << "Результати записані у файл: " << outputFileName << endl;

    return 0;
}
