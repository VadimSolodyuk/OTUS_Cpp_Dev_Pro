#include "../include/bulk.hpp"

#include <iostream>
#include <fstream>
#include <ostream>
#include <ctime>
#include <string>

const std::string startOfDynamicBlock = "{";
const std::string endOfDynamicBlock = "}";

const std::vector<std::string>& Block::getCommands() const {
    return m_commands;
}

std::string& Block::getTimeReceivingFirstCommand() {
    return timeReceivingFirstCommand;
}

void Block::start() {
    int numberBlocks{0};
    std::string command;

    while(true) {
        std::cin >> command;

        if (std::cin.eof() || command == "EOF") {
            if (m_commands.size() != 0 && numberBlocks == 0) execCommands(); 
            break;
        }
        if (command == startOfDynamicBlock) {
            ++numberBlocks;
            if (numberBlocks == 1 && !m_commands.empty()) execCommands();
            continue;
        }
        if (command == endOfDynamicBlock) {
            --numberBlocks;
            if (numberBlocks < 0) {
                std::cerr << "To start a dynamic block, enter: {" << std::endl;
                numberBlocks = 0;
                continue;
            }
            if (numberBlocks == 0 && !m_commands.empty()) execCommands();
            continue;
        }
        m_commands.push_back(command);
        if (m_commands.size() == 1) {
            timeReceivingFirstCommand = std::to_string(std::time(nullptr));
        }
        if (m_commands.size() == m_blockSize && numberBlocks == 0) execCommands();
    }
}

void Block::execCommands() {
    notify();
    m_commands.clear();
}

void ConsolePrinter::update() {
    print(std::cout, commands);
    std::cout << std::endl;
}

void FilePrinter::update() {
    std::string fileName = m_fileName;
    fileName.insert(4, m_timeReceivingFirstCommand);
    std::ofstream file(fileName);
    if (!file.is_open()) std::cerr << "File opening error!" <<std::endl;
    print(file, commands);
    file.close();
}
