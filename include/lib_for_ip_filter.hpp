#pragma once

#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>


class IP {
    std::array<uint8_t, 4> bytes{};

    public:
    IP () = default;
    explicit IP (std::string &str);
    explicit IP (std::string &&str);

    decltype(bytes) get_bytes() const;

    uint8_t get_byte(size_t index) const;
    
    std::string get_IP() const;
};

void filter_by_first_byte(const std::vector<IP> &ip_pool, uint8_t first_byte, std::ostream &os);

void filter_by_first_and_second_byte(
    const std::vector<IP> &ip_pool, uint8_t first_byte, uint8_t second_byte, std::ostream &os);

void filter_any_byte(const std::vector<IP> &ip_pool, uint8_t any_byte, std::ostream &os);