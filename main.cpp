#include "MyMatrix.hpp"

#include <cassert>
#include <iostream>


int main() {
	{
		MyMatrix<int, -1> matrix;
		assert(matrix.size() == 0);
		auto a = matrix[0][0];
		assert(a == -1);
		assert(matrix.size() == 1);
		matrix[100][100] = 314;
		assert(matrix[100][100] == 314);
		assert(matrix.size() == 2);
		matrix[100][100] = -1;
		assert(matrix[100][100] == -1);
		assert(matrix.size() == 2);
	}

	{
		MyMatrix<int, -2> matrix;
		MyMatrixProxy proxy(matrix);
		assert(proxy.size() == 0); // все ячейки свободны
		auto a = proxy[0][0];
		assert(a == -2);
		assert(proxy.size() == 0);
		proxy[100][100] = 314;
		assert(proxy[100][100] == 314);
		assert(proxy.size() == 1);
		proxy[100][100] = -2;
		assert(proxy[100][100] == -2);
		assert(proxy.size() == 0);
	}
	
	{
		MyMatrix<int, 0> matrix;
		MyMatrixProxy proxy(matrix);

		for (int i = 0; i < 10; i++) {
			proxy[i][i] = i;
		}
		for (int i = 0; i < 10; i++) {
			proxy[i][9 - i] = 9 - i;
		}

		for (int r = 1; r < 9; r++) {
			for (int c = 1; c < 9; c++) {
				std::cout << proxy[r][c] << ' ';
			}
			std::cout << "\b " << std::endl;
		}

		std::cout << proxy.size() << std::endl;

		for (const auto& [x, y, value] : proxy) {
			std::cout << "(" << x << "," << y << "): " << value << std::endl;
		}
	}
}