#include <iostream>
#include <clocale>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <algorithm>
#include <map>

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
    setlocale(LC_ALL, "ru");
    ifstream ist("file.txt");
    if (!ist) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    vector<FileInfo> files;
    string s;

    while (getline(ist, s)) {
        files.push_back({ getFileName(s), getFileDate(s), getFileSize(s) });
    }


    sort(files.begin(), files.end(), [](const FileInfo& a, const FileInfo& b) {
        return (a.date == b.date) ? (a.size < b.size) : (a.date < b.date);
        });

    for (const auto& item : files) {
        cout << item << "\n";
    }

    // Подсчёт общего размера файлов для каждой уникальной даты
    map<string, int> totalSizeByDate;
    for (const auto& item : files) {
        totalSizeByDate[item.date] += item.size;
    }

    cout << "\nОбщий размер файлов по каждой дате:\n";
    for (const auto& item : totalSizeByDate) {
        cout << "Дата: " << item.first << ", Общий размер: " << item.second << " байт\n";
    }

    return 0;
}


string getFileName(string s) {
    auto name = extractData(s, R"("[a-zA-Z0-9._-]+")");
    if (name.empty()) {
        throw runtime_error("File name not found in the input line.");
    }
    return name.at(0);
}

string getFileDate(string s) {
    auto date = extractData(s, R"(\d{2}.\d{2}.\d{4})");
    if (date.size() != 1) {
        throw runtime_error("File date not found or invalid in the input line.");
    }
    int x = 0;
    return date.at(0);
}

int getFileSize(string s) {
    auto size = extractData(s, R"(\b\d+\b)");
    if (size.size() < 1) {
        throw runtime_error("File size not found in the input line.");
    }

    return stoi(size.back());
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

ostream& operator<<(std::ostream& stream, const FileInfo& fileInfo) {
    stream << "File Name: " << fileInfo.name;
    stream << ", Date: " << fileInfo.date;
    stream << ", Size: " << fileInfo.size << " bytes";
    return stream;
}
