#include "../include/my_allocator.hpp"
#include "../include/my_vectorContainer.hpp"

#include <map>
#include <iostream>

long double fact(int n) {
    if(n == 0)
        return 1;
    return n * fact(n-1);
};

int main (int, char*[]){

    try {

        auto map_with_default_allocator = [](){
            std::map<int, int> map;
            for(int i{}; i < 10; ++i){
                map.emplace(i, fact(i));
            }
            return map;
        }();

        auto map_with_my_allocator = [](){
            std::map<int, int, std::less<key_t>, my_allocator<std::pair<const int, int>, 10 > > map;
            for(int i{}; i < 10; ++i){
                map.emplace(i, fact(i));
            }
            return map;
        }();

        std::cout << "Сontents of the container 'map_with_my_allocator'\n";   
        for(const auto & d : map_with_my_allocator){
            std::cout << d.first << " " << d.second << "\n";
        }; 
        std::cout << "\n";
        
        auto my_vector_with_default_allocator = [](){
            vectorContainer<int> my_vector;
            for(int i{}; i < 10; ++i){
                my_vector.push_back(i);
            }
            return my_vector;
        }();

        auto my_vector_with_my_allocator = [](){
            vectorContainer<int, my_allocator<int, 22> > my_vector;
            for(int i{0}; i < 10; ++i){
                my_vector.push_back(i);
            }
            return my_vector;
        }();

        std::cout << "Сontents of the container " << "'my_vector_with_my_allocator':\n";
        for(const auto & d : my_vector_with_my_allocator){
            std::cout << d << "\n";
        }; 

    } catch (std::exception & ex) {
        std::cerr << ex.what() << std::endl;
    }
    return 0;
}