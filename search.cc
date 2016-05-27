#include <iostream>
#include <vector>
#include <cassert>
#include <iomanip>
#include <algorithm>

using namespace std;

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

// bool test(int expected, int (* func) (std::vector<int> , int ),
// 	      std::vector<int> input, int key) {
// 	return func(input, key) == expected;
// }  

// bool test_all(int (* func) (std::vector<int>, int )) {
//     const int undefined_key = 0;
// 	std::vector<int> simple_array({1, 2 , 3 ,4, 5 , 6 , 7 , 8 , 10});

// 	std::cout << (test(-1, func, simple_array, undefined_key) ? "PASS" : "FAIL") << std::endl;
//     std::cout << (test(0, func, {5}, 5) ? "PASS" : "FAIL") << std::endl;
//     std::cout << (test(-1, func, {5}, 1) ? "PASS" : "FAIL") << std::endl;
//     std::cout << (test(0, func, {1,2} ,1 ) ? "PASS" : "FAIL") << std::endl;
//     std::cout << (test(1, func, {1,2} ,2 ) ? "PASS" : "FAIL") << std::endl;
//     std::cout << (test(-1, func, {1,2} ,3 ) ? "PASS" : "FAIL") << std::endl;
//     std::cout << (test(1, func, {1,2} ,2 ) ? "PASS" : "FAIL") << std::endl;
// }

template <class T, class TFunc, class P1, class P2>
void test(T expected, TFunc f, P1 p1, P2 p2)
{
	auto result = f(p1, p2);

    cout << "testing: " << expected
          << " f( " << p1 << ", " << result << endl;

	if (expected != result)
	{
		cout << "Error: " << "\nexpected : " << expected 
        //<< " != f(" << p1 << "," << p2 << ")" 
        << " got" << result<<  endl;
		// assert(false);
	}
    cout << "\nok" << endl;
}

ostream& operator<<(ostream& o, const vector<int>& v)
{
    o << "{";
    for(auto x : v)
        o << x << ", ";
    o << "}";
    return o;
}

template <class TFunc>
void test_binary_search(TFunc binary_search_impl)
{
	typedef vector<int> Vector;
	int key = 42;
	auto adaptor = [binary_search_impl](Vector& v, int key) {
		auto result =  binary_search_impl(v.begin(), v.end(), key);
		return result == v.end() ? -1 : result - v.begin();
	};
	test(-1, adaptor, Vector(), key);

	test(-1, adaptor, Vector(), key);
	test(0, adaptor, Vector({42}), key);

	test(-1, adaptor, Vector({1, 2}), key);
	test(1, adaptor, Vector({1, 42}), key);
	test(0, adaptor, Vector({42, 100}), key);

	// key not in array
	test(-1, adaptor, Vector({1,2,3,5,41}), key);
	test(-1, adaptor, Vector({43,45,67,100}), key);
	test(-1, adaptor, Vector({3,5,41,43,45,67}), key);

	// key in array
	test(3, adaptor, Vector({43,45,67,100}), key);
	test(0, adaptor, Vector({43,45,67,100}), key);
	test(3, adaptor, Vector({43,45,67,100}), key);

	//binary search specific
	test(3, adaptor, Vector({3,5,41,42,45,67}), key);
	test(2, adaptor, Vector({3,5,42,45,67}), key);

    // more then key
    test(1, adaptor, Vector({key, key}), key);
    test(3, adaptor, Vector({1,2,key, key}), key);
    test(4, adaptor, Vector({1,2,3,key, key}), key);
    test(1, adaptor, Vector({key, key, key + 1, key + 10}), key);

}

template <class TIter, class T>
TIter binary_search_1(TIter begin, TIter end, T key)
{
	assert(std::is_sorted(begin, end));
	auto size = end - begin;
	if (size == 0)
	{
		return end;
	}
	if(size == 1) {
		return (*begin) == key ? begin : end;
	}
	auto m = begin + (end - begin) / 2;

	if(key < *m) {
		auto r = binary_search_1(begin, m, key);
		return m == r ? end : r;
	} else {
		return binary_search_1(m, end, key);
	}
}


template <class TIter, class T>
TIter binary_search_2(TIter begin, TIter end, T key)
{
    assert(std::is_sorted(begin, end));
    auto size = end - begin;
    if (size == 0)
    {
        return end;
    }
    if(size == 1) {
        return (*begin) == key ? begin : end;
    }

    assert(size > 1);

    auto m = begin + (end - begin) / 2;

// [begin m) [m] (m end)
    if(key < *m) { // [begin, m)
        auto r = binary_search_2(begin, m, key);
        return m == r ? end : r;
    } else if(*m < key) { // [m+1, end) 
        return binary_search_2(m, end, key);
    } else { // *m == key
        return m;
    }
}

void test_all_binary_searches()
{
    typedef std::vector<int> Vec;
	test_binary_search(binary_search_1<Vec::iterator, int>);
    cout << "==============================" << endl;
    test_binary_search(binary_search_2<Vec::iterator, int>);
    cout << "rara" << endl;
}

int main() {
    cout << "123123" << endl;
	test_all_binary_searches();

	
	
	return 0;
}

