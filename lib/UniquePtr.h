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

template<typename T>
class UniquePtr<T[]> {
private:
    T* data;
public:
    UniquePtr<T[]>() : data(nullptr) {}
    explicit UniquePtr<T[]>(T source[]) : data(source) {}
    ~UniquePtr<T[]>() {
        if(data) {
            std::cout << "Calls destructor with value: " << data << std::endl;
            delete[] data;
        }
    }
    T* Get() const {
        return data;
    }
    void Reset(T* source = nullptr) {
        std::cout << "Deleting data with value: " << data << std::endl;
        if(data) {
            delete[] data;
        }
        data = source;
    }
    T* Release() {
        T* temp = data;
        data = nullptr;
        return temp;
    }
    UniquePtr<T[]>(const UniquePtr<T[]>& obj) = delete;
    UniquePtr<T[]>& operator=(UniquePtr<T[]> const &) = delete;
    T& operator[](size_t index) {
        return data[index];
    }
    UniquePtr<T[]>(UniquePtr<T[]>&& obj) noexcept : data(std::exchange(obj.data, nullptr))  {}
    UniquePtr<T[]>& operator=(UniquePtr<T[]>&& obj) noexcept {
        std::swap(data, obj.data);
        return *this;
    }
    explicit operator bool() const {
        return data;
    }
};

// Если честно, то я не очень понимаю как работает код ниже,
// но я как-то смог написать создание массива с заданным размером

/*template<typename T, typename... Args>
UniquePtr<T> makeUnique(Args&&... args)
{
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

template<typename T, size_t N>
UniquePtr<T[]> makeUnique()
{
    return UniquePtr<T[]>(new T[N]);
}*/

template <typename T>
struct makeUniqueHelper {
    typedef UniquePtr<T> UniquePtr;

    template <typename... Args>
    static inline UniquePtr make(Args&&... args) {
        return UniquePtr(new T(std::forward<Args>(args)...));
    }
};

/*template<typename T, std::size_t N>
struct makeUniqueHelper<T[N]> {
    typedef UniquePtr<T[]> UniquePtr;

    template<typename... Args>
    static inline UniquePtr make(Args &&... args) {
        static_assert(N >= sizeof...(Args),
                      "For make_unique<T[N]> N must be as largs as the number of arguments");
        return UniquePtr(new T[N]{std::forward<Args>(args)...});
    }
};

template<typename T>
struct makeUniqueHelper<T[]> {
    typedef UniquePtr<T[]> UniquePtr;

    template <typename... Args>
    static inline UniquePtr make(Args&&... args) {
        return UniquePtr(new T[sizeof...(Args)]{std::forward<Args>(args)...});
    }
};*/

template<typename T>
struct makeUniqueHelper<T[]> {
    typedef UniquePtr<T[]> UniquePtr;

    template <typename... Args>
    static inline UniquePtr make(size_t size) {
        return UniquePtr(new T[size]);
    }
};

template <typename T, typename... Args>
inline typename makeUniqueHelper<T>::UniquePtr
makeUnique(Args&&... args) {
    return makeUniqueHelper<T>::make(std::forward<Args>(args)...);
}

#endif //SMARTPOINTERS_UNIQUEPTR_H