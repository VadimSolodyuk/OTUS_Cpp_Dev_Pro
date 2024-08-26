#include "include/bulk.hpp"

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>



int main(int argc, char const *argv[])
{   
    if (argc < 2 || !std::atoi(argv[1]) || std::atoi(argv[1]) <= 0) {
        std::cerr << "After the program name, specify the argument - block size [1...)" << std::endl;
        return -1;
    }
    size_t blockSize = std::stoi(argv[1]) ;
    Block block(blockSize);

    auto consolePrinter = std::make_shared<ConsolePrinter>(block.getCommands());
    auto filePrinter =
        std::make_shared<FilePrinter>(block.getCommands(), block.getTimeReceivingFirstCommand());

    block.addObserver(consolePrinter);
    block.addObserver(filePrinter);
    block.start();
}
