#include "Header.h"
using namespace std;

string getFileName (const string& s) {
  auto name = extractData(s, R"("[a-zA-Z0-9._-]+")");
  if (name.empty()) {
    throw runtime_error("File name not found in the input line.");
  }
  return name.at(0);
}

string getFileDate (const string& s) {
  auto date = extractData(s, R"(\d{2}\.\d{2}\.\d{4})");
  if (date.size() != 1) {
    throw runtime_error("File date not found or invalid in the input line.");
  }
  return date.at(0);
}

int getFileSize (const string& s) {
  auto size = extractData(s, R"((^|\s)(\d+)(\s|$))");
  if (size.size() < 1) {
    throw runtime_error("File size not found in the input line.");
  }
  return stoi(size.back());
}

vector<string> extractData (const string& data, const string& regex) {
  std::regex words_regex(regex);
  auto words_begin = sregex_iterator(data.begin(), data.end(), words_regex);
  auto words_end = sregex_iterator();
  vector<string> out;
  for (sregex_iterator i = words_begin; i != words_end; ++i) {
    out.push_back(i->str());
  }
  return out;
}

ostream& operator<< (std::ostream& stream, const FileInfo& fileInfo) {
  stream << "File Name: " << fileInfo.name;
  stream << ", Date: " << fileInfo.date;
  stream << ", Size: " << fileInfo.size << " bytes";
  return stream;
}