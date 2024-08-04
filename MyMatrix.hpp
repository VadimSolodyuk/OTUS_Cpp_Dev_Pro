#pragma once

#include <algorithm>
#include <cstddef>
#include <map>
#include <memory>
#include <tuple>
#include <iostream>

template<typename T, T defaultValue> class MyMatrix {
	MyMatrix() = default;
public:
	~MyMatrix() = default;
	
	class Iterator;
	using Iterator = MyMatrix<T, defaultValue>::Iterator;

	struct DataRow;
	using IteratorDataRow = typename std::map<size_t, T>::iterator;

	using SetDataRow = std::map<size_t, DataRow>;
	using IteratorSetDataRow = typename std::map<size_t, DataRow>::iterator;
	
	template<typename A, A> friend class Matrix;


	static std::shared_ptr<MyMatrix<T, defaultValue>> create() {
		auto myMatrix = std::shared_ptr<MyMatrix<T, defaultValue>>(new MyMatrix<T, defaultValue>{});
		return myMatrix;
	}

	struct DataRow {
		std::map<size_t, T> dataRow;

		T& operator[](const size_t& column){	
			if (dataRow.count(column) != 0) {
				return dataRow.at(column);
			} 
			auto pair = dataRow.emplace(column, defaultValue); 				
			return pair.first->second; 
		}

		const size_t size() {
			if (dataRow.empty()) return 0;
			// for (auto it : dataRow) {
			for (auto it = dataRow.begin(); it != dataRow.end();) {
std::cout << "DataRow.size" << std::endl;
				if (it->second == defaultValue) {
					dataRow.erase(it++);
					if (dataRow.empty()) break;
				}
				++it;
			}
			return dataRow.size();
		}		

		auto begin() {return dataRow.begin();}
		auto end() {return dataRow.end();}
	};

	class Iterator {
		SetDataRow& _matrix;
		IteratorSetDataRow iteratorSetDataRow {_matrix.begin()}; 
		IteratorDataRow iteratorDataRow {_matrix.begin()->second.begin()}; 
	public:
		Iterator(SetDataRow& matrix) : _matrix(matrix) {};
		Iterator& begin() {
			iteratorSetDataRow = _matrix.begin(); 
			iteratorDataRow = _matrix.begin()->second.begin(); 
			return *this;
		}
		Iterator& end() {
			iteratorSetDataRow = _matrix.end(); 
			iteratorDataRow = _matrix.end()->second.end(); 
			return *this;
		}
		auto operator*() const {
std::cout << "operator*" << std::endl;
			return std::make_tuple
				(
					iteratorSetDataRow->first,
					iteratorDataRow->first,
					iteratorDataRow->second
				);
	    }
		bool operator!=(const Iterator& rhs) const {
			return 
				this->iteratorDataRow != rhs.iteratorDataRow
				&&
				this->iteratorSetDataRow != rhs.iteratorSetDataRow;
		}
		bool operator==(const Iterator& rhs) const {
			return 
				this->iteratorDataRow == rhs.iteratorDataRow
				&&
				this->iteratorSetDataRow == rhs.iteratorSetDataRow;
		}
		Iterator& operator++() {
			++iteratorDataRow;
			if (iteratorDataRow == iteratorSetDataRow->second.end()) {
				++iteratorSetDataRow;
				iteratorDataRow = iteratorSetDataRow->second.begin();
				if (*this == this->end()) return *this;
			};
			return *this;
		}
	};	

	DataRow& operator[](size_t row) {return m_matrix[row];}

	Iterator begin() {return Iterator(m_matrix);}
	Iterator end() {
		Iterator iterator(m_matrix);
		iterator.end();
		return iterator;
	}
	
	const size_t size() {
		size_t size{};
		std::for_each(m_matrix.begin(), m_matrix.end(),
			[&size](auto x){size += x.second.size();}
		);
		return size;
	}
private:
	SetDataRow m_matrix; 
};


template<typename T, T defaultValue> class Matrix {
	using MatrixMy = MyMatrix<T,defaultValue>; 
	std::shared_ptr<MatrixMy> m_myMayrixPrt;
	MatrixMy m_matrix;
public:
	Matrix() {
		m_myMayrixPrt = MatrixMy::create();
		m_matrix = *m_myMayrixPrt.get();
	}

	std::size_t size() {return m_matrix.size();}

	auto& operator[] (size_t row) {return m_matrix[row];}

	auto begin() {
		size();
		return m_matrix.begin();
	}

	auto end() {
		size();
		return m_matrix.end();
	}
};