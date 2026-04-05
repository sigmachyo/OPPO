#include "Header.h"
#include <gtest/gtest.h>
using namespace std;

TEST(GetFileNameTest, BasicTest) {
  EXPECT_EQ(getFileName("\"data.csv\" 1024 10.31.2024"), "\"data.csv\"");
  EXPECT_EQ(getFileName("10.30.2024 402342 \"report.pdf\""), "\"report.pdf\"");
  EXPECT_EQ(getFileName("\"report.pdf\" 4096 12.30.2024"), "\"report.pdf\"");
  EXPECT_THROW(getFileName("10.30.2024 402342"), runtime_error);
}

TEST(GetFileDateTest, BasicTest) {
  EXPECT_EQ(getFileDate("\"data.csv\" 1024 10.31.2024"), "10.31.2024");
  EXPECT_EQ(getFileDate("10.30.2024 402342 \"report.pdf\""), "10.30.2024");
  EXPECT_EQ(getFileDate("\"report.pdf\" 4096 12.30.2024"), "12.30.2024");
  EXPECT_THROW(getFileDate("\"data.csv\" 1024"), runtime_error);
}

TEST(GetFileSizeTest, BasicTest) {
  EXPECT_EQ(getFileSize("\"data.csv\" 1024 10.31.2024"), 1024);
  EXPECT_EQ(getFileSize("10.30.2024 402342 \"report.pdf\""), 402342);
  EXPECT_EQ(getFileSize("\"report.pdf\" 4096 12.30.2024"), 4096);
  EXPECT_THROW(getFileSize("\"report.pdf\" 10.30.2024"), runtime_error);
}

TEST(ExtractDataTest, BasicTest) {
  vector<string> dates = extractData("10.31.2024 10.30.2024", R"(\d{2}\.\d{2}\.\d{4})");
  EXPECT_EQ(dates.size(), 2);
  EXPECT_EQ(dates[0], "10.31.2024");
  EXPECT_EQ(dates[1], "10.30.2024");
  
  vector<string> names = extractData("\"data.csv\" \"report.pdf\"", R"("[a-zA-Z0-9._-]+")");
  EXPECT_EQ(names.size(), 2);
  EXPECT_EQ(names[0], "\"data.csv\"");
  EXPECT_EQ(names[1], "\"report.pdf\"");
  
  vector<string> sizes = extractData("1024 402342 4096", R"(\b\d+\b)");
  EXPECT_EQ(sizes.size(), 3);
  EXPECT_EQ(sizes[0], "1024");
  EXPECT_EQ(sizes[1], "402342");
  EXPECT_EQ(sizes[2], "4096");
}

TEST(OutputOperatorTest, BasicTest) {
  FileInfo fileInfo = {"data.csv", "10.31.2024", 1024};
  stringstream ss;
  ss << fileInfo;
  EXPECT_EQ(ss.str(), "File Name: data.csv, Date: 10.31.2024, Size: 1024 bytes");
  
  fileInfo = {"report.pdf", "12.30.2024", 4096};
  ss.str("");
  ss << fileInfo;
  EXPECT_EQ(ss.str(), "File Name: report.pdf, Date: 12.30.2024, Size: 4096 bytes");
}