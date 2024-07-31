#pragma once

#include <algorithm>
#include <cstddef>
#include <map>
#include <memory>
#include <tuple>

template<typename T> class MyMatrix {
	MyMatrix() = default;
public:
	
	class Iterator;
	// friend class Iterator;
	using Iterator = MyMatrix<T>::Iterator;

	using DataRow = std::map<size_t, T>;
	using IteratorDataRow = typename std::map<size_t, T>::iterator;

	using SetDataRow = std::map<size_t, DataRow>;
	using IteratorSetDataRow = typename std::map<size_t, DataRow>::iterator;
	
	template<typename A, A> friend class Matrix;

	~MyMatrix() = default;

	static std::shared_ptr<MyMatrix<T>> create() {
		auto myMatrix = std::shared_ptr<MyMatrix<T>>(new MyMatrix<T>{});
		return myMatrix;
	}
	class Iterator : public std::iterator_traits<std::forward_iterator_tag> {
		SetDataRow& _matrix;
		IteratorSetDataRow iteratorSetDataRow {_matrix.begin()}; 
		IteratorDataRow iteratorDataRow {_matrix.begin()->second.begin()}; 
	public:
		Iterator(SetDataRow& matrix) : _matrix(matrix) {};
		Iterator& begin() {
			iteratorSetDataRow = _matrix.begin(); 
			iteratorDataRow = _matrix.begin()->second.begin(); 
			return this;
		}
		Iterator& end() {
			iteratorSetDataRow = _matrix.end(); 
			iteratorDataRow = _matrix.end()->second.end(); 
			return this;
		}
		auto operator*() const {
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
				if (this == this->end()) return this;
			};
			return this;
		}
	};	

	DataRow& operator[](size_t row) {return m_matrix[row];}
	const DataRow& operator[](size_t row) const {return m_matrix[row];}


	Iterator begin() {return Iterator(m_matrix);}
	Iterator end() {
		Iterator iterator(m_matrix);
		iterator.end();
		return iterator;
	}
	
	std::size_t size() {
		size_t size{};
		std::for_each(m_matrix.begin(), m_matrix.end(),
			[&size](auto &x){size += x.second.size();}
		);
		return size;
	}
private:
	SetDataRow m_matrix; 
};


template<typename T, T defaultValue> class Matrix {
	using MatrixMy = MyMatrix<T>; 
	std::shared_ptr<MatrixMy> m_myMayrixPrt;
	MatrixMy m_myMayrix;
public:
	Matrix() {
		m_myMayrixPrt = MatrixMy::create();
		m_myMayrix = *m_myMayrixPrt.get();
	}

	std::size_t size() {return m_myMayrix.size();}

// 	auto& operator[] (size_t row) {return m_myMayrix[row];}
	const auto& operator[] (size_t row) const { return m_myMayrix.operator[](row);}

// // 	const typename MyMatrix<T, defaultValue>::Row& operator[] (int row) const {
// // 		return matrix_.operator[](row);
// // 	}

// // 	typename MyMatrix<T, defaultValue>::Row& operator[] (int row) {
// // 		isSizeMaybeChanged = true;
// // 		return matrix_.operator[](row);
// // 	}

// 	auto begin() {return m_myMayrix.begin();}


// // 	typename MyMatrix<T, defaultValue>::Iterator begin() {
// // 		adjustSize();
// // 		return matrix_.begin();
// // 	}

// 	auto end() {return m_myMayrix.end();}

// // 	typename MyMatrix<T, defaultValue>::Iterator end() {
// // 		adjustSize();
// // 		return matrix_.end();
// // 	}

// // private:
// // 	void adjustSize() {
// // 		if (isSizeMaybeChanged) {
// // 			for (auto iter = matrix_.m_data.begin(); iter != matrix_.m_data.end(); ) {
// // 				for (auto itt = iter->second.dataRow.begin(); itt != iter->second.dataRow.end(); ) {
// // 					if (itt->second != defaultValue) {
// // 						++itt;
// // 					} else {
// // 						itt = iter->second.dataRow.erase(itt);
// // 					}
// // 				}

// 				if (iter->second.dataRow.empty()) {
// 					iter = matrix_.m_data.erase(iter);
// 				} else {
// 					++iter;
// 				}
// 			}

// 			isSizeMaybeChanged = false;
// 		}
// 	}
};