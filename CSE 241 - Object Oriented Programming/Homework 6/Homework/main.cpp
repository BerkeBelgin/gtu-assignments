#include <iostream>
#include "GTUVector.h"
#include "GTUVector.cpp"
#include "GTUSet.h"
#include "GTUSet.cpp"
#include "GTUIterator.h"
#include "GTUIterator.cpp"
#include "GTUIteratorConst.h"
#include "GTUIteratorConst.cpp"

using namespace gtu;

template<class T, class V>
constexpr T find(T first, T last, const V& value)
{
    for (; first != last; ++first) {
        if (*first == value) {
            return first;
        }
    }
    return last;
}

template<class T, class V>
constexpr T find_if(T first, T last, V p)
{
    for (; first != last; ++first) {
        if (p(*first)) {
            return first;
        }
    }
    return last;
}

template<class T, class F>
constexpr F for_each(T first, T last, F f)
{
    for (; first != last; ++first) {
        f(*first);
    }
    return f;
}

int main(){
	//test
	
	GTUVector<int> test1;
	GTUIterator<int> test1_iter = test1.begin();
	
	test1.insert(test1_iter, 7);
	test1_iter++;
	for(int i = 0; i < test1.max_size(); i++) std::cout << test1[i] << " ";
	std::cout << std::endl;
	
	test1.insert(test1_iter, 3);
	test1_iter++;
	for(int i = 0; i < test1.max_size(); i++) std::cout << test1[i] << " ";
	std::cout << std::endl;
	
	test1.insert(test1_iter, 6);
	test1_iter++;
	for(int i = 0; i < test1.max_size(); i++) std::cout << test1[i] << " ";
	std::cout << std::endl;
	
	test1.insert(test1_iter, 9);
	test1_iter++;
	for(int i = 0; i < test1.max_size(); i++) std::cout << test1[i] << " ";
	std::cout << std::endl;
	
	test1.insert(test1_iter, 8);
	test1_iter++;
	for(int i = 0; i < test1.max_size(); i++) std::cout << test1[i] << " ";
	std::cout << std::endl;
	
	test1.insert(test1_iter, 5);
	test1_iter++;
	for(int i = 0; i < test1.max_size(); i++) std::cout << test1[i] << " ";
	std::cout << std::endl;
	
	test1.insert(test1_iter, 1);
	test1_iter++;
	for(int i = 0; i < test1.max_size(); i++) std::cout << test1[i] << " ";
	std::cout << std::endl;
	
	test1.insert(test1_iter, 2);
	test1_iter++;
	for(int i = 0; i < test1.max_size(); i++) std::cout << test1[i] << " ";
	std::cout << std::endl;
	
	test1.insert(test1_iter, 4);
	for(int i = 0; i < test1.max_size(); i++) std::cout << test1[i] << " ";
	std::cout << std::endl;
	
	std::cout << test1.size() << std::endl;
	std::cout << test1.max_size() << std::endl;
	
	test1_iter = test1.begin();
	
	test1.earse(test1_iter);
	test1.earse(test1_iter);
	test1.earse(test1_iter);
	test1.earse(test1_iter);
	test1.earse(test1_iter);
	test1.earse(test1_iter);
	test1.earse(test1_iter);
	test1.earse(test1_iter);
	test1.earse(test1_iter);
	test1.earse(test1_iter);
	test1.earse(test1_iter);
	test1.earse(test1_iter);
	
	for(int i = 0; i < test1.max_size(); i++) std::cout << test1[i] << " ";
	std::cout << std::endl;
	
	std::cout << test1.size() << std::endl;
	std::cout << test1.max_size() << std::endl;
	
	if(test1.empty())std::cout << "EMPTY!" << std::endl;
}
