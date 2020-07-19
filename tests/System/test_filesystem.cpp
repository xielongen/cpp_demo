//
// Created by x on 19-12-5.
//
#include <gtest/gtest.h>
#include <iostream>
#include <filesystem>
#include <regex>

namespace fs = std::filesystem;

TEST(C11, FILESYSTEM) {
    std::string strPath = "/home/x";
    std::regex fileSuffix("(.*)");// *.jpg, *.png

    for (
        auto &DirectoryIter:fs::directory_iterator(strPath)) {
        auto filepath = DirectoryIter.path();
        auto filename = filepath.filename();

        if (std::regex_match(filename.string(), fileSuffix)) {
            std::cout << filepath << std::endl;
        }
    }
}
