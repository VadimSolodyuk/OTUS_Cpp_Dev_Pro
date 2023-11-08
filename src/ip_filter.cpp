#include "lib_for_ip_filter.hpp"


int main()
{
    try
    {
        std::vector<IP> ip_pool;

        for(std::string line; std::getline(std::cin, line);) {
            auto ip = [](std::string && line) {
                return line.substr(0, line.find_first_of('\t'));
            } (std::move(line));
            ip_pool.emplace_back(std::move(ip));
        }

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(),
        [](const IP &lhs, const IP &rhs){
            return lhs.get_bytes() > rhs.get_bytes();
        });

        for(const auto &ip : ip_pool) {
            std::cout << ip.get_IP() << std::endl;
        }

        // TODO filter by first byte and output
        // ip = filter(1)
        filter_by_first_byte(ip_pool, 1, std::cout);

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        filter_by_first_and_second_byte(ip_pool, 46, 70, std::cout);        

        // TODO filter by any byte and output
        // ip = filter_any(46)
        filter_any_byte(ip_pool, 46, std::cout);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
