#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <sstream>

struct FileInfo {
  std::string name;
  std::string date;
  int size;
};

std::ostream& operator<< (std::ostream& stream, const FileInfo& fileInfo);
std::vector<std::string> extractData (const std::string& data, const std::string& regex);
std::string getFileName (const std::string& s);
std::string getFileDate (const std::string& s);
int getFileSize (const std::string& s);

#endif