#pragma once

#include <cstddef>
#include <iterator>
#include <map>
#include <memory>
#include <tuple>


template<typename T> class MyMatrix {
	MyMatrix() = default;
public:
	~MyMatrix() = default;
	
	using DataRow = std::map<size_t, T>;
	using IteratorDataRow = typename std::map<size_t, T>::iterator;

	using SetDataRow = std::map<size_t, DataRow>;
	using IteratorSetDataRow = typename std::map<size_t, DataRow>::iterator;
	
	template<typename A, A> friend class MyMatrixProxy;

	std::shared_ptr<MyMatrix<T>> create() {
		auto myMatrix = std::shared_ptr<MyMatrix<T>>();
		return myMatrix;
	};

//	TODO
	class Iterator : public std::iterator_traits<std::forward_iterator_tag> {
		using Iter = typename MyMatrix<T>::Iterator;
		SetDataRow& _matrix;
		IteratorSetDataRow iteratorSetDataRow {_matrix.begin()}; 
		IteratorDataRow iteratorDataRow {_matrix.begin()->second.begin()}; 
	public:
		Iterator(SetDataRow& matrix) : _matrix(matrix) {};
		
		Iter& begin() {
			iteratorSetDataRow = _matrix.begin(); 
			iteratorDataRow = _matrix.begin()->second.begin(); 
			return this;
		}
		
		Iter& end() {
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

		bool operator!=(const Iter& rhs) const {
			return 
				this->iteratorDataRow != rhs.iteratorDataRow
				&&
				this->iteratorSetDataRow != rhs.iteratorSetDataRow;
		}

		bool operator==(const Iter& rhs) const {
			return 
				this->iteratorDataRow == rhs.iteratorDataRow
				&&
				this->iteratorSetDataRow == rhs.iteratorSetDataRow;
		}

		Iter& operator++() {
			++iteratorDataRow;
			if (iteratorDataRow == iteratorSetDataRow->second.end()) {
				++iteratorSetDataRow;
				iteratorDataRow = iteratorSetDataRow->second.begin();
				if (this == this->end()) return this;
			};
			return this;
		}
	};	
	friend class MyMatrix<T>::Iterator;

	// std::size_t size() {
	// 	calcSize();
	// 	return m_size;
	// }

// 	const Row& operator[] (int row) const {
// 		if (auto iter = m_data.find(row); iter != m_data.end()) {
// 			return iter->second;
// 		}
// 		return emptyLine_;
// 	}

// 	Row& operator[] (int row) {
// 		return m_data[row];
// 	}

// 	Iterator begin() {
// 		return Iterator(true, m_data);
// 	}

// 	Iterator end() {
// 		return Iterator(false, m_data);
// 	}

// 	void calcSize() {
// 		m_size = 0;
// 		for (auto iter = m_data.begin(); iter != m_data.end(); ++iter) {
// 			for (auto itt = iter->second.dataRow.begin(); itt != iter->second.dataRow.end(); ++itt) {
// 				m_size++;
// 			}
// 		}
// 	}
private:

	SetDataRow m_matrix; 
	std::size_t m_size = 0;
};


// template<typename T, T defaultValue>
// class MyMatrixProxy {
// public:
// 	MyMatrixProxy(MyMatrix<T, defaultValue>& matrix) : matrix_(matrix) {}

// 	std::size_t size() {
// 		adjustSize();
// 		return matrix_.size();
// 	}

// 	const typename MyMatrix<T, defaultValue>::Row& operator[] (int row) const {
// 		return matrix_.operator[](row);
// 	}

// 	typename MyMatrix<T, defaultValue>::Row& operator[] (int row) {
// 		isSizeMaybeChanged = true;
// 		return matrix_.operator[](row);
// 	}

// 	typename MyMatrix<T, defaultValue>::Iterator begin() {
// 		adjustSize();
// 		return matrix_.begin();
// 	}

// 	typename MyMatrix<T, defaultValue>::Iterator end() {
// 		adjustSize();
// 		return matrix_.end();
// 	}

// private:
// 	void adjustSize() {
// 		if (isSizeMaybeChanged) {
// 			for (auto iter = matrix_.m_data.begin(); iter != matrix_.m_data.end(); ) {
// 				for (auto itt = iter->second.dataRow.begin(); itt != iter->second.dataRow.end(); ) {
// 					if (itt->second != defaultValue) {
// 						++itt;
// 					} else {
// 						itt = iter->second.dataRow.erase(itt);
// 					}
// 				}

// 				if (iter->second.dataRow.empty()) {
// 					iter = matrix_.m_data.erase(iter);
// 				} else {
// 					++iter;
// 				}
// 			}

// 			isSizeMaybeChanged = false;
// 		}
// 	}

// 	MyMatrix<T, defaultValue>& matrix_;
// 	bool isSizeMaybeChanged = false;
// };