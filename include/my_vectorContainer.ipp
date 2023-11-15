template <typename T, class Allocator>
vectorContainer<T, Allocator>::vectorContainer () {
    m_data = std::allocator_traits<Allocator>::allocate(m_allocator, m_capacity);
};

template <typename T, class Allocator>
vectorContainer<T, Allocator>::vectorContainer(const T data) {
    m_data = std::allocator_traits<Allocator>::allocate(m_allocator, m_capacity);
    std::allocator_traits<Allocator>::construct(m_allocator, m_data + m_size, data);
    ++m_size;
}

template <typename T, class Allocator>
vectorContainer<T, Allocator>::vectorContainer(const vectorContainer& vector) {
    if (!vector.getSize())
        return;
    m_size = vector.m_size;
    m_capacity = vector.m_capacity;
    m_data = std::allocator_traits<Allocator>::allocate(m_allocator, m_capacity);
    std::copy(vector.m_data, vector.m_data + vector.m_size * sizeof(T), this->m_data);
}

template <typename T, class Allocator>
vectorContainer<T, Allocator>& vectorContainer<T, Allocator>::operator=(const vectorContainer& vector) {
    if (this->getSize() == vector.getSize()) {
        if (m_data == vector.m_data) 
            return *this;
    }
    if (m_size > 0) 
        std::allocator_traits<Allocator>::deallocate(m_allocator, m_data, 0);
    m_size = vector.m_size;
    m_capacity = vector.m_capacity;
    m_data = std::allocator_traits<Allocator>::allocate(m_allocator, m_capacity);
    std::copy(vector.m_data, vector.m_data + vector.m_size * sizeof(T), this->m_data);
    return *this;
}

template <typename T, class Allocator>
T& vectorContainer<T, Allocator>::operator[](const size_t index) const {
    if (index > m_size-1) throw std::invalid_argument 
        (R"(Error "Index out of range!" in the function vectorContainer::operator[])");
    return m_data[index];   
}

template <typename T, class Allocator>
void vectorContainer<T, Allocator>::push_back(const T value)  {
    if (m_size == m_capacity) {
        m_capacity = m_capacity * 2 + 1;
        m_new_data = std::allocator_traits<Allocator>::allocate(m_allocator, m_capacity);
        std::memcpy(m_new_data, m_data, m_size * sizeof(T));
        std::swap(m_new_data, m_data);
        std::allocator_traits<Allocator>::deallocate(m_allocator, m_new_data, m_capacity);
    }
    std::allocator_traits<Allocator>::construct(m_allocator, m_data + m_size, value);
    ++m_size;
};

template <typename T, class Allocator>
size_t vectorContainer<T, Allocator>::getSize() const  {
    return m_size;
}

template <typename T, class Allocator>
size_t vectorContainer<T, Allocator>::getCapaciti() const  {
    return m_capacity;
}

template <typename T, class Allocator>
const char* vectorContainer<T, Allocator>::getName() const  {
    return R"(vectorContainer)"; 
}

template <typename T, class Allocator>
vectorContainer<T, Allocator>::iterator::iterator (T* data, const size_t index) { 
    m_index = index;
    m_dataIterator = data;
    m_iterator = &m_dataIterator[m_index];            
}   

template <typename T, class Allocator>
typename vectorContainer<T, Allocator>::iterator& vectorContainer<T, Allocator>::iterator::operator++() {
    ++m_index;
    m_iterator = &m_dataIterator[m_index];
    return *this;
}

template <typename T, class Allocator>
typename vectorContainer<T, Allocator>::iterator& vectorContainer<T, Allocator>::iterator::operator--() {
    --m_index;
    m_iterator = &m_dataIterator[m_index];
    return *this;
}

template <typename T, class Allocator>
typename vectorContainer<T, Allocator>::iterator& vectorContainer<T, Allocator>::iterator::operator+(const size_t rhs) {
    m_index += rhs;
    m_iterator = &m_dataIterator[m_index];
    return *this;
}

template <typename T, class Allocator>
typename vectorContainer<T, Allocator>::iterator& vectorContainer<T, Allocator>::iterator::operator-(const size_t rhs) {
    m_index -= rhs;
    m_iterator = &m_dataIterator[m_index];
    return *this;
}

template <typename T, class Allocator>
bool vectorContainer<T, Allocator>::iterator::operator==(const iterator& rhs) const {
    if (m_iterator == rhs.m_iterator)
        return true; 
    return false;
}

template <typename T, class Allocator>
bool vectorContainer<T, Allocator>::iterator::operator!=(const iterator& rhs) const {
    if (m_iterator != rhs.m_iterator)
        return true; 
    return false;
}

template <typename T, class Allocator>
T& vectorContainer<T, Allocator>::iterator::operator*() const {
    return *m_iterator;
}

template <typename T, class Allocator>
size_t vectorContainer<T, Allocator>::iterator::getIndex() const {
    return m_index;
}

template <typename T, class Allocator>
typename vectorContainer<T, Allocator>::iterator vectorContainer<T, Allocator>::begin() {
    const size_t index{0};
    return iterator(m_data, index);
}  

template <typename T, class Allocator>
typename vectorContainer<T, Allocator>::iterator vectorContainer<T, Allocator>::end()  {
    return iterator(m_data, (m_size));
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const vectorContainer<T>& vector) {
    const size_t i{0};
    os << vector[i];
    return os;
}