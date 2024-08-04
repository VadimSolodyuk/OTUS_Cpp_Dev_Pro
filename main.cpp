#include "MyMatrix.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <ostream>


int main() {
	// auto matrix = MyMatrix<int>::create();
	
	// {
	// 	auto matrixPtr = MyMatrix<int, -1>::create();
	// 	auto matrix = *matrixPtr.get();
	// 	assert(matrix.size() == 0);
	// 	auto a = matrix[0][0];
	// std::cout << a << std::endl;
		// assert(a == -1);
		// assert(matrix.size() == 0);
		// matrix[100][100] = 314;
	// std::cout << matrix[100][100] << std::endl;

		// assert(matrix[100][100] == 314);
		// std::cout << matrix[100][100] << std::endl;
		// std::cout << matrix.size() << std::endl;

		// assert(matrix.size() == 1);	//
	// 	assert(matrix.size() == 2);
		// matrix[1][1] = -1;
		// assert(matrix[1][1] == -1);
		// assert(matrix.size() == 2);
		// auto a = matrix.size();
	// }

	{
	// 	// бесконечная матрица int заполнена значениями -1
		Matrix<int, -1> matrix;
		assert(matrix.size() == 0); // все ячейки свободны
		auto a = matrix[0][0];
		assert(a == -1);
		assert(matrix.size() == 0);
		matrix[100][100] = 314;
		assert(matrix[100][100] == 314);
		assert(matrix.size() == 1);
		matrix[99][100] = 314;
	std::cout << matrix.size() << std::endl;
		std::for_each(matrix.begin(), matrix.end(),
			[](auto it){
				auto [x, y, v] = it;
	std::cout << x << y << v << std::endl;
			}
		);
		// выведется одна строка
		// 100100314
		// for(auto c: matrix)
		// {
		// int x;
		// int y;
		// int v;
		// std::tie(x, y, v) = c;
		// stdW::cout << x << y << v << std::endl;
		// }
	}
	// std::cout << matrix[100][100] << matrix.size() << std::endl;

	// {
	// 	Matrix<int, 0> matrix;
	// // 	MyMatrixProxy proxy(matrix);

	// 	for (int i = 0; i < 10; i++) {
	// 		matrix[i][i] = i;
	// 	}
	// 	for (int i = 0; i < 10; i++) {
	// 		matrix[i][9 - i] = 9 - i;
	// 	}
	// 	std::cout << matrix.size() << std::endl;

	// }
	// 	for (int r = 1; r < 9; r++) {
	// 		for (int c = 1; c < 9; c++) {
	// 			std::cout << proxy[r][c] << ' ';
	// 		}
	// 		std::cout << "\b " << std::endl;
	// 	}

	// 	std::cout << proxy.size() << std::endl;

	// 	for (const auto& [x, y, value] : proxy) {
	// 		std::cout << "(" << x << "," << y << "): " << value << std::endl;
	// 	}
};