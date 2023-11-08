#include "lib_for_ip_filter.hpp"

#include <gtest/gtest.h>
#include <fstream>

struct class_IP : public testing::Test{
    std::string str_ip{"0.1.2.3"};
    std::array<uint8_t, 4> expect_bytes {0,1,2,3};
    IP ip{str_ip};
};

TEST_F(class_IP, get_bytes){
    ASSERT_EQ(ip.get_bytes(), expect_bytes);
}
TEST_F(class_IP, get_byte){
    for(int b{1}; b < 5; ++b){
        ASSERT_EQ(ip.get_byte(b), b-1);
    }
}
TEST_F(class_IP, get_IP){
    ASSERT_EQ(ip.get_IP(), str_ip);
}

struct filter_IP : public testing::Test{
    std::stringstream ip_stream;
    std::vector<IP> ip_pool;
    std::vector<std::string> IP_after_filter{};

    std::vector<std::string> expect_IP_with_first_byte_1 {
        "1.231.69.33","1.87.203.225","1.70.44.170","1.29.168.152",
        "1.1.234.8"
    };
    std::vector<std::string> expect_IP_with_first_byte_46_and_second_byte_70 {
        "46.70.225.39","46.70.147.26","46.70.113.73","46.70.29.76"
    };
    std::vector<std::string> expect_IP_with_any_byte_46 {
        "186.204.34.46","186.46.222.194","185.46.87.231","185.46.86.132",
        "185.46.86.131","185.46.86.131","185.46.86.22","185.46.85.204",
        "185.46.85.78","68.46.218.208","46.251.197.23","46.223.254.56",
        "46.223.254.56","46.182.19.219","46.161.63.66","46.161.61.51",
        "46.161.60.92","46.161.60.35","46.161.58.202","46.161.56.241",
        "46.161.56.203","46.161.56.174","46.161.56.106","46.161.56.106",
        "46.101.163.119","46.101.127.145","46.70.225.39","46.70.147.26",
        "46.70.113.73", "46.70.29.76","46.55.46.98","46.49.43.85",
        "39.46.86.85","5.189.203.46"
    };

    void SetUp() override{
        std::ifstream list_IP("ip_filter.tsv");
        if (!list_IP.is_open()){
            std::cerr << "Failed to open file <ip_filter.tsv>" << '\n';
            return;
        }
        for(std::string line; std::getline(list_IP, line);) {
            auto ip = [](std::string && line) {
                return line.substr(0, line.find_first_of('\t'));
            } (std::move(line));
            ip_pool.emplace_back(std::move(ip));
        }
        std::sort(ip_pool.begin(), ip_pool.end(),
        [](const IP &lhs, const IP &rhs){
            return lhs.get_bytes() > rhs.get_bytes();
        });
    }
};

TEST_F(filter_IP, filter_by_first_byte){
    filter_by_first_byte(ip_pool, 1, ip_stream);
    for(std::string line; std::getline(ip_stream, line);) {
        [this](std::string & line) {
            IP_after_filter.emplace_back(line);
        }(line);
    }
    
    ASSERT_EQ(IP_after_filter.size(), expect_IP_with_first_byte_1.size());
    EXPECT_EQ(IP_after_filter, expect_IP_with_first_byte_1);
}

TEST_F(filter_IP, filter_by_first_and_second_byte){
    filter_by_first_and_second_byte(ip_pool, 46, 70, ip_stream);
    for(std::string line; std::getline(ip_stream, line);) {
        [this](std::string & line) {
            IP_after_filter.emplace_back(line);
        }(line);
    }
    
    ASSERT_EQ(IP_after_filter.size(), expect_IP_with_first_byte_46_and_second_byte_70.size());
    EXPECT_EQ(IP_after_filter, expect_IP_with_first_byte_46_and_second_byte_70);
}

TEST_F(filter_IP, filter_any_byte){
    filter_any_byte(ip_pool, 46, ip_stream);
    for(std::string line; std::getline(ip_stream, line);) {
        [this](std::string & line) {
            IP_after_filter.emplace_back(line);
        }(line);
    }
    
    ASSERT_EQ(IP_after_filter.size(), expect_IP_with_any_byte_46.size());
    EXPECT_EQ(IP_after_filter, expect_IP_with_any_byte_46);
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
