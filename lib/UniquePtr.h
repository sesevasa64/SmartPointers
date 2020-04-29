//
// Created by sesev on 28.04.2020.
//

#ifndef SMARTPOINTERS_UNIQUEPTR_H
#define SMARTPOINTERS_UNIQUEPTR_H

template<typename T>
class UniquePtr {
private:
    T* data;
public:
    UniquePtr<T>() : data(new T) {}
    explicit UniquePtr<T>(T* source) : data(source) {}
    ~UniquePtr<T>() {
        if(data) {
            std::cout << "Calls destructor with value: " << *data << std::endl;
            delete data;
        }
    }
    T* Get() const {
        return data;
    }
    void Reset(T* source = nullptr) {
        std::cout << "Deleting data with value: " << *data << std::endl;
        if(data) {
            delete data;
        }
        data = source;
    }
    T* Release() {
        T* temp = data;
        data = nullptr;
        return temp;
    }
    UniquePtr<T>(const UniquePtr<T>& obj) = delete;
    UniquePtr<T>& operator=(UniquePtr<T> const &) = delete;
    UniquePtr<T>(UniquePtr<T>&& obj) noexcept : data(std::exchange(obj.data, nullptr))  {}
    UniquePtr<T>& operator=(UniquePtr<T>&& obj) noexcept {
        std::swap(data, obj.data);
        return *this;
    }
    T& operator*()  const {
        return *data;
    }
    T* operator->() const {
        return data;
    }
    explicit operator bool() const {
        return data;
    }
};

template<typename T, typename... Args>
UniquePtr<T> makeUnique(Args&&... args)
{
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

#endif //SMARTPOINTERS_UNIQUEPTR_H
