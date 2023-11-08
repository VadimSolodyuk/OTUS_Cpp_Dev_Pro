#include "lib_for_ip_filter.hpp"


IP::IP (std::string &str) {
        auto d = ".";
        auto stop = str.find_first_of(d);
        decltype(stop) start = 0;
        size_t byte = 0;
        
        while(stop != std::string::npos) {
            bytes.at(byte) = (std::stoi(str.substr(start, stop - start)));
            start = stop + 1;
            stop = str.find_first_of(d, start);
            ++byte;
        }
        bytes.at(byte) = (std::stoi(str.substr(start)));
}

IP::IP (std::string &&str) {
        auto d = ".";
        auto stop = str.find_first_of(d);
        decltype(stop) start = 0;
        size_t byte = 0;
        
        while(stop != std::string::npos) {
            bytes.at(byte) = (std::stoi(str.substr(start, stop - start)));
            start = stop + 1;
            stop = str.find_first_of(d, start);
            ++byte;
        }
        bytes.at(byte) = (std::stoi(str.substr(start)));
}

std::array<uint8_t, 4> IP::get_bytes() const {
    return bytes;
}

uint8_t IP::get_byte(size_t index) const {
    return bytes.at(index-1);
}

std::string IP::get_IP() const {
    std::string IP{};
    for (size_t byte{0}; byte < 4; ++byte){
        if(byte != 0){
            IP += '.';
        }
        IP += (std::to_string(bytes.at(byte)));
    }
    return IP;
}

void filter_by_first_byte(const std::vector<IP> &ip_pool, uint8_t first_byte, std::ostream &os){
    auto it = std::find_if(crbegin(ip_pool), crend(ip_pool),
        [&first_byte](const IP &ip){
            return ip.get_byte(1) != first_byte; } 
    );
    if(it == ip_pool.rend())
        return;
    auto n = ip_pool.size() + (std::crbegin(ip_pool) - it);
    std::for_each(ip_pool.begin() + n, ip_pool.end(), 
        [&os](const IP &ip){os << ip.get_IP() << std::endl; } 
    );
}

void filter_by_first_and_second_byte(
    const std::vector<IP> &ip_pool, uint8_t first_byte, uint8_t second_byte, std::ostream &os)
{
    auto it_first = std::find_if(cbegin(ip_pool), cend(ip_pool),
        [&first_byte, &second_byte](const IP &ip){
            return ip.get_byte(1) == first_byte && ip.get_byte(2) == second_byte; } 
    );
    if(it_first == ip_pool.end()) 
        return;
    auto it_last = std::find_if(it_first + 1, cend(ip_pool),
        [&first_byte, &second_byte](const IP &ip){
            return ip.get_byte(1) != first_byte || ip.get_byte(2) != second_byte; } 
    );
    if(it_last == ip_pool.end()){
        std::for_each(it_first, ip_pool.cend(), 
        [&os](const IP &ip){os << ip.get_IP() << '\n';} 
        );
        return;
    }
    std::for_each(it_first, it_last, 
    [&os](const IP &ip){os << ip.get_IP() << '\n';} 
    );
}

void filter_any_byte(const std::vector<IP> &ip_pool, uint8_t any_byte, std::ostream &os){
    for(const auto &ip : ip_pool){
        for(const auto &byte : ip.get_bytes()){
            if(byte == any_byte){
                os << ip.get_IP() << std::endl;
                break;
            }
        }
    }
}