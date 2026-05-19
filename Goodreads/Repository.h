#pragma once
#include <vector>
#include <memory>
template<typename T>
class Repository {
private:
	std::vector<std::shared_ptr<T>> elements;
public:
	void addElement(std::shared_ptr<T> element);
	void removeElement(size_t index);
	std::shared_ptr<T> operator[](size_t index) const;
	size_t size() const;
};