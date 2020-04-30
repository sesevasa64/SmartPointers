//
// Created by sesev on 30.04.2020.
//

#ifndef SMARTPOINTERS_SHAREDPTR_H
#define SMARTPOINTERS_SHAREDPTR_H

#include <iostream>
#include <utility>

template<typename T>
class SharedPtr {
private:
    T* data;
    int* ref;
public:
    SharedPtr<T>() : data(nullptr), ref(new int(1)) {}
    explicit SharedPtr<T>(T* data) : data(data), ref(new int(1)) {}
    SharedPtr<T>(SharedPtr<T>& obj) : data(obj.data) {
        ref = obj.ref;
        *ref += 1;
    }
    SharedPtr<T>(SharedPtr<T>&& obj) noexcept :
            data(std::exchange(obj.data, nullptr)),
            ref(std::exchange(obj.ref, new int(1))) {}
    ~SharedPtr() {
        *ref -= 1;
        std::cout << "Calls destructor";
        if(*ref == 0) {
            if(data) {
                std::cout << " with value: " << *data << std::endl;
                delete data;
            }
            delete ref;
        }
        else {
            std::cout << std::endl;
        }
    }
    SharedPtr<T>& operator=(const SharedPtr<T>& obj) {
        if(this != &obj) {
            *ref -= 1;
            if(ref == 0) {
                if(data) {
                    delete data;
                }
                delete ref;
            }
            data = obj.data;
            ref = obj.ref;
            *ref += 1;
        }
        return *this;
    }
    SharedPtr<T>& operator=(SharedPtr<T>&& obj) noexcept {
        std::swap(data, obj.data);
        std::swap(ref, obj.ref);
        return *this;
    }
    bool operator==(UniquePtr<T>& obj) {
        return data == obj.data;
    }
    bool operator!=(UniquePtr<T>& obj) {
        return data != obj.data;
    }
    void Reset(T* source = nullptr) {
        *ref -= 1;
        if(*ref == 0) {
            if(data) {
                std::cout << "Deleting data with value: " << data << std::endl;
                delete data;
            }
            delete ref;
        }
        ref = new int(1);
        data = source;
    }
    int useCount() {
        //return data ? *ref : 0;
        return *ref - !data;
    }
    bool Unique() {
        return useCount() == 1;
    }
    T* Get() const {
        return data;
    }
    void swap(SharedPtr<T>& obj) {
        std::swap(data, obj.data);
        std::swap(ref, obj.ref);
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
class SharedPtr<T[]> {
private:
    T* data;
    int* ref;
public:
    SharedPtr<T[]>() : data(nullptr), ref(new int(1)) {}
    explicit SharedPtr<T[]>(T data[]) : data(data), ref(new int(1)) {}
    SharedPtr<T[]>(SharedPtr<T[]>& obj) : data(obj.data) {
        ref = obj.ref;
        *ref += 1;
    }
    SharedPtr<T[]>(SharedPtr<T[]>&& obj) noexcept :
            data(std::exchange(obj.data, nullptr)),
            ref(std::exchange(obj.ref, new int(1))) {}
    ~SharedPtr() {
        *ref -= 1;
        std::cout << "Calls destructor";
        if(*ref == 0) {
            if(data) {
                std::cout << " with value: " << *data << std::endl;
                delete data;
            }
            delete ref;
        }
        else {
            std::cout << std::endl;
        }
    }
    SharedPtr<T[]>& operator=(const SharedPtr<T[]>& obj) {
        if(this != &obj) {
            *ref -= 1;
            if(ref == 0) {
                if(data) {
                    delete data;
                }
                delete ref;
            }
            data = obj.data;
            ref = obj.ref;
            *ref += 1;
        }
        return *this;
    }
    SharedPtr<T[]>& operator=(SharedPtr<T[]>&& obj) noexcept {
        std::swap(data, obj.data);
        std::swap(ref, obj.ref);
        return *this;
    }
    T& operator[](size_t index) {
        return data[index];
    }
    bool operator==(SharedPtr<T[]>& obj) {
        return data == obj.data;
    }
    bool operator!=(SharedPtr<T[]>& obj) {
        return data != obj.data;
    }
    void Reset(T* source = nullptr) {
        *ref -= 1;
        if(*ref == 0) {
            if(data) {
                std::cout << "Deleting data with value: " << data << std::endl;
                delete data;
            }
            delete ref;
        }
        ref = new int(1);
        data = source;
    }
    int useCount() {
        //return data ? *ref : 0;
        return *ref - !data;
    }
    bool Unique() {
        return useCount() == 1;
    }
    T* Get() const {
        return data;
    }
    void swap(SharedPtr<T[]>& obj) {
        std::swap(data, obj.data);
        std::swap(ref, obj.ref);
    }
    explicit operator bool() const {
        return data;
    }
};

template <typename T>
struct makeSharedHelper {
    typedef SharedPtr<T> SharedPtr;

    template <typename... Args>
    static inline SharedPtr make(Args&&... args) {
        return SharedPtr(new T(std::forward<Args>(args)...));
    }
};

template<typename T, std::size_t N>
struct makeSharedHelper<T[N]> {
    typedef SharedPtr<T[]> SharedPtr;

    template<typename... Args>
    static inline SharedPtr make(Args &&... args) {
        static_assert(N >= sizeof...(Args),
                      "For make_unique<T[N]> N must be as largs as the number of arguments");
        return SharedPtr(new T[N]{std::forward<Args>(args)...});
    }
};

template<typename T>
struct makeSharedHelper<T[]> {
    typedef SharedPtr<T[]> SharedPtr;

    template <typename... Args>
    static inline SharedPtr make(Args&&... args) {
        return SharedPtr(new T[sizeof...(Args)]{std::forward<Args>(args)...});
    }
};

template <typename T, typename... Args>
inline typename makeSharedHelper<T>::SharedPtr
makeShared(Args&&... args) {
    return makeSharedHelper<T>::make(std::forward<Args>(args)...);
}

#endif //SMARTPOINTERS_SHAREDPTR_H
