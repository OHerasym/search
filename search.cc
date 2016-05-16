#include <iostream>

int search_1(int A[] , int size, int key) {
	for (int i = 0; i < size ; ++i) {
		if (A[i] ==  key) {
			return i;
		}
	}
	return -1;
}

int search_2(int A[] , int size, int key) {
	int i = 0 ;
	while(i < size) {
		if (A[i] ==  key) {
			return i;
		}
		++i;
	}
	return -1;
}


int search_3(int A[] , int size, int key) {
	A[size] = key;
	while(A[i] != key)
		++i;
	return i == size ? -1 : i ;
}


int search_4(int A[] , int size, int key) {
	if (size == 0)
		return -1;
	if (A[size-1] == key) 
		return size -1;
	int old = A[size - 1]; 
	A[size - 1] = key;
	while(A[i] != key)
		++i;
	A[size - 1] = old;
	return i == size ? -1 : i ;	
}

int main() {
	std::cout << "Hi" << std::endl;
	return 0;
}
