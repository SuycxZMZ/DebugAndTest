#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <filesystem>  // C++17 or later

namespace fs = std::filesystem;

// 单词库
std::vector<std::string> wordPool = {"hello", "world", "hadoop", "mapreduce", 
                                     "c++", "linux", "distributed", "thread", 
                                     "mutex", "programming"};

std::string generateRandomLine(int minWords = 3, int maxWords = 7) {
    int numWords = minWords + rand() % (maxWords - minWords + 1);
    std::string line;
    for (int i = 0; i < numWords; ++i) {
        line += wordPool[rand() % wordPool.size()] + " ";
    }
    line.pop_back();  // 去掉最后一个空格
    return line;
}

void createWordFiles(const std::string &directory, int numFiles = 10, int linesPerFile = 10) {
    // 创建目录
    fs::create_directory(directory);

    // 生成文件
    for (int i = 1; i <= numFiles; ++i) {
        std::string filename = directory + "/file" + std::to_string(i) + ".txt";
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            for (int j = 0; j < linesPerFile; ++j) {
                outFile << generateRandomLine() << "\n";
            }
            outFile.close();
            std::cout << "Generated " << filename << std::endl;
        } else {
            std::cerr << "Error opening file: " << filename << std::endl;
        }
    }
}

int main() {
    srand(time(0));  // 初始化随机数种子

    std::string directory = "./wordFiles";
    createWordFiles(directory);

    return 0;
}
