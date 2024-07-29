#pragma once

#include <cstddef>
#include <map>
#include <tuple>





template<typename T, T defaultValue>
class MyMatrix {
using DataRow = std::map<size_t, T>;
public:
	struct Row {
		DataRow dataRow;
		
		const T& operator[] (size_t column) const {
			if (auto iter = dataRow.find(column); iter != dataRow.end()) {
				return iter->second;
			}
			return defaultValue;
		}

		T& operator[] (size_t column) {
			if (auto iter = dataRow.find(column); iter != dataRow.end()) {
				return iter->second;
			}
			auto pair = dataRow.emplace(column, defaultValue);
			return pair.first->second;
		}
	};
	
/////////////////////////////////////////////////////////////////TODO
	struct Iterator {
		Iterator(bool isBegin, std::map<int, Row>& data) : m_data(data) {
			if (isBegin) {
				rowIterator = m_data.begin();
				if (rowIterator != m_data.end()) {
					columnIterator = rowIterator->second.dataRow.begin();
				}
			} else {
				rowIterator = m_data.end();
			}
		}

		Iterator& operator++ () {
			if (rowIterator != m_data.end() && columnIterator != rowIterator->second.dataRow.end()) {
				++columnIterator;
				if (columnIterator == rowIterator->second.dataRow.end()) {
					++rowIterator;
					if (rowIterator != m_data.end()) {
						columnIterator = rowIterator->second.dataRow.begin();
					}
				}
			}
			return *this;
		}

		std::tuple<size_t, size_t, T> operator* () {
			return std::make_tuple(rowIterator->first, columnIterator->first, columnIterator->second);
		}

		bool operator!= (const Iterator& rhs) const {
			return rowIterator != rhs.rowIterator &&
				   columnIterator != rhs.columnIterator;
		}

		std::map<size_t, Row>& m_data;
		typename std::map<size_t, Row>::iterator rowIterator;
		typename std::map<size_t, T>::iterator columnIterator;
	};

	MyMatrix() = default;

	std::size_t size() {
		calcSize();
		return m_size;
	}

	const Row& operator[] (int row) const {
		if (auto iter = m_data.find(row); iter != m_data.end()) {
			return iter->second;
		}
		return emptyLine_;
	}

	Row& operator[] (int row) {
		return m_data[row];
	}

	Iterator begin() {
		return Iterator(true, m_data);
	}

	Iterator end() {
		return Iterator(false, m_data);
	}

private:
	void calcSize() {
		m_size = 0;
		for (auto iter = m_data.begin(); iter != m_data.end(); ++iter) {
			for (auto itt = iter->second.dataRow.begin(); itt != iter->second.dataRow.end(); ++itt) {
				m_size++;
			}
		}
	}

	mutable std::map<int, Row> m_data; 
	std::size_t m_size = 0;
	const Row emptyLine_;

	template<typename A, A>
	friend class MyMatrixProxy;
};


template<typename T, T defaultValue>
class MyMatrixProxy {
public:
	MyMatrixProxy(MyMatrix<T, defaultValue>& matrix) : matrix_(matrix) {}

	std::size_t size() {
		adjustSize();
		return matrix_.size();
	}

	const typename MyMatrix<T, defaultValue>::Row& operator[] (int row) const {
		return matrix_.operator[](row);
	}

	typename MyMatrix<T, defaultValue>::Row& operator[] (int row) {
		isSizeMaybeChanged = true;
		return matrix_.operator[](row);
	}

	typename MyMatrix<T, defaultValue>::Iterator begin() {
		adjustSize();
		return matrix_.begin();
	}

	typename MyMatrix<T, defaultValue>::Iterator end() {
		adjustSize();
		return matrix_.end();
	}

private:
	void adjustSize() {
		if (isSizeMaybeChanged) {
			for (auto iter = matrix_.m_data.begin(); iter != matrix_.m_data.end(); ) {
				for (auto itt = iter->second.dataRow.begin(); itt != iter->second.dataRow.end(); ) {
					if (itt->second != defaultValue) {
						++itt;
					} else {
						itt = iter->second.dataRow.erase(itt);
					}
				}

				if (iter->second.dataRow.empty()) {
					iter = matrix_.m_data.erase(iter);
				} else {
					++iter;
				}
			}

			isSizeMaybeChanged = false;
		}
	}

	MyMatrix<T, defaultValue>& matrix_;
	bool isSizeMaybeChanged = false;
};