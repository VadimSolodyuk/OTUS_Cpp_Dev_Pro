#pragma once

#include "Observer.hpp"

#include <cstddef>
#include <vector>
#include <string>


class Block : public BaseObserved {
    std::vector<std::string> m_commands;
    size_t m_blockSize;
    std::string timeReceivingFirstCommand;
    
    void execCommands();
public:
    explicit Block(size_t blockSize) : m_blockSize(blockSize) {}
    const std::vector<std::string>& getCommands() const;
    std::string& getTimeReceivingFirstCommand();
    void start();
};



class BlockPrinter : public Observer {
protected:
    template <typename Output, typename Commands>
    void print(Output& output, const Commands& commands) const {
        if (commands.size() == 0) return;
        output << "bulk: ";
        for(const auto& command: commands) {
            if (command == commands[0]) {
                output << command; 
            } else output << ", " << command;
        };
    }
};

class ConsolePrinter : public BlockPrinter {
    const std::vector<std::string>& commands;
public:    
    explicit ConsolePrinter(const std::vector<std::string>& cmd) : commands(cmd) {}
    ~ConsolePrinter()=default;

    void update() override;
};

class FilePrinter : public BlockPrinter {
    const std::vector<std::string>& commands;
    std::string& m_timeReceivingFirstCommand;
    std::string m_fileName{"bulk.log"};
public:
    FilePrinter(const std::vector<std::string>& cmd, std::string& timeReceivingFirstCommand)
        : commands(cmd), m_timeReceivingFirstCommand(timeReceivingFirstCommand) {
    }
    ~FilePrinter() = default;

    void update() override;
};
