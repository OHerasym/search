#include <iostream>
#include <vector>

int search_1(std::vector<int> A , int key) {
	for (int i = 0; i < A.size() ; ++i) {
		if (A[i] ==  key) {
			return i;
		}
	}
	return -1;
}

int search_2(std::vector<int> A , int key) {
	int i = 0 ;
	while(i < A.size()) {
		if (A[i] ==  key) {
			return i;
		}
		++i;
	}
	return -1;
}


int search_3(std::vector<int> A , int key) {
	A.reserve(A.size()+1);
	A[A.size()] = key;
	int i = 0;
	while(A[i] != key)
		++i;
	return i == A.size() ? -1 : i ;
}


int search_4(std::vector<int> A , int key) {
	if (A.size() == 0)
		return -1;
	if (A[A.size()-1] == key) 
		return A.size() -1;
	int old = A[A.size() - 1]; 
	A[A.size() - 1] = key;
	int i = 0;
	while(A[i] != key)
		++i;
	A[A.size() - 1] = old;
	return i == A.size() ? -1 : i ;	
}

bool test(int expected, int (* func) (std::vector<int> , int ),
	      std::vector<int> input, int key) {
	return func(input, key) == expected;
}  

bool test_all(int (* func) (std::vector<int>, int )) {
    const int undefined_key = 0;
	std::vector<int> simple_array({1, 2 , 3 ,4, 5 , 6 , 7 , 8 , 10});

	std::cout << (test(-1, func, simple_array, undefined_key) ? "PASS" : "FAIL") << std::endl;
    std::cout << (test(0, func, {5}, 5) ? "PASS" : "FAIL") << std::endl;
    std::cout << (test(-1, func, {5}, 1) ? "PASS" : "FAIL") << std::endl;
    std::cout << (test(0, func, {1,2} ,1 ) ? "PASS" : "FAIL") << std::endl;
    std::cout << (test(1, func, {1,2} ,2 ) ? "PASS" : "FAIL") << std::endl;
    std::cout << (test(-1, func, {1,2} ,3 ) ? "PASS" : "FAIL") << std::endl;
    std::cout << (test(1, func, {1,2} ,2 ) ? "PASS" : "FAIL") << std::endl;
}



int main() {
	test_all(search_1);

	
	
	return 0;
}

