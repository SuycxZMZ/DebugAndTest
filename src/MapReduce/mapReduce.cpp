#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <thread>
#include <mutex>
#include <filesystem>
#include "../threadPool/threadPool.h"

namespace fs = std::filesystem;
std::mutex mutex; // 用于保护共享数据的互斥锁

// Map函数，处理单个文件
std::map<std::string, int> Map(const std::string &filename) {
    std::map<std::string, int> wordCount;
    std::ifstream infile(filename);
    std::string line;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string word;
        while (iss >> word) {
            wordCount[word]++;
        }
    }

    return wordCount;
}

// 线程处理函数
void MapTask(const std::string &filename, std::vector<std::map<std::string, int>> &intermediate) {
    std::map<std::string, int> localWordCount = Map(filename);

    // 加锁后添加到共享容器
    std::lock_guard<std::mutex> lock(mutex);
    intermediate.push_back(localWordCount);
}

// Reduce函数，汇总所有Map任务的结果
std::map<std::string, int> Reduce(const std::vector<std::map<std::string, int>> &intermediate) {
    std::map<std::string, int> finalWordCount;
    for (const auto &wordMap : intermediate) {
        for (const auto &entry : wordMap) {
            finalWordCount[entry.first] += entry.second;
        }
    }
    return finalWordCount;
}

int main() {
    std::string directory = "./wordFiles";  // 指定文件夹路径
    std::vector<std::map<std::string, int>> intermediate;
    sylar::threadpool executer(6);
    // std::vector<std::thread> threads;

    // 遍历目录中的所有文件
    for (const auto &entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().string();
            executer.commit(std::bind(MapTask, filename, std::ref(intermediate)));
            // threads.emplace_back(MapTask, filename, std::ref(intermediate));
        }
    }

    std::this_thread::sleep_for(std::chrono::seconds(10));
    // 执行Reduce任务
    std::map<std::string, int> result = Reduce(intermediate);

    // 输出结果
    for (const auto &entry : result) {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }

    return 0;
}

