#include <iostream>
#include <clocale>
#include <string>
#include <fstream>
#include <vector>
#include <regex>

using namespace std;

struct FileInfo {
    string name;
    string date;
    int size;
};

std::ostream& operator<<(std::ostream& stream, const FileInfo& fileInfo);
static vector<string> extractData(const string& data, const string& regex);
static string getFileName(string s);
static string getFileDate(string s);
static int getFileSize(string s);

int main() {
    ifstream ist("file.txt");

    vector<FileInfo> files;
    string s;

    while (getline(ist, s)) {

        files.push_back({ getFileName(s), getFileDate(s), getFileSize(s) });
    }

    for (const auto& item : files) {
        cout << item << "\n";
    }
}

string getFileName(string s) {
    auto name = extractData(s, R"("[a-zA-Z0-9._-]+")");  // Предполагаем, что название файла содержит буквы, цифры, ".", "_" или "-"
    if (name.empty()) {
        throw runtime_error("File name not found in the input line.");
    }
    return name.at(0);
}

string getFileDate(string s) {
    auto date = extractData(s, R"(\d{2}.\d{2}.\d{4})");  // Формат даты: YYYY-MM-DD
    if (date.size() != 1) {
        throw runtime_error("File date not found or invalid in the input line.");
    }
    return date.at(0);
}

int getFileSize(string s) {
    auto size = extractData(s, R"(\b\d+\b)");  // Целое число для размера файла
    if (size.size() < 1) {
        throw runtime_error("File size not found in the input line.");
    }
    return stoi(size.back());  // Предполагаем, что последнее число — это размер
}

vector<string> extractData(const string& data, const string& regex) {
    std::regex words_regex(regex);
    auto words_begin = sregex_iterator(data.begin(), data.end(), words_regex);
    auto words_end = sregex_iterator();

    vector<string> out;
    for (sregex_iterator i = words_begin; i != words_end; ++i) {
        out.push_back(i->str());
    }
    return out;
}

std::ostream& operator<<(std::ostream& stream, const FileInfo& fileInfo) {
    stream << "File Name: " << fileInfo.name;
    stream << ", Date: " << fileInfo.date;
    stream << ", Size: " << fileInfo.size << " bytes";
    return stream;
}