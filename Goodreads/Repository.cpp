#include "Repository.h"
template<typename T>
void Repository<T>::addElement(std::shared_ptr<T> element) {
	elements.push_back(element);
}
template<typename T>
std::shared_ptr<T> Repository<T>::operator[](size_t index) const {
	return elements[index];
}
template<typename T>
size_t Repository<T>::size() const {
	return elements.size();
}