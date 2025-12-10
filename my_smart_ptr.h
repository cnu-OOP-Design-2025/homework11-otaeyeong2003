#pragma once


template<typename T>
class my_shared_ptr {
private:
    T* ptr;
    size_t* refCount;

public:
    // 생성자
    explicit my_shared_ptr(T* p = nullptr) : ptr(p), refCount(new size_t(1)) {}

    // 복사 생성자
    my_shared_ptr(const my_shared_ptr& other) : ptr(other.ptr), refCount(other.refCount) {
        // TODO
        if (refCount) {
            (*refCount)++;
        }
    }

    // 대입 연산자
    my_shared_ptr& operator=(const my_shared_ptr& other) {
        if (this != &other) {
            release();
            // TODO
            ptr = other.ptr;
            refCount = other.refCount;
            if (refCount) (*refCount)++;
        }
        return *this;
    }

    // 소멸자
    ~my_shared_ptr() { release(); }

    // 참조 해제
    void release() {
        // TODO
        if (refCount) {
            (*refCount)--;
            if (*refCount == 0) {
                delete ptr;
                delete refCount;
            }
        }
        ptr = nullptr;
        refCount = nullptr;
    }

    // 접근 연산자
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    size_t use_count() const { 
        if (refCount) return *refCount;
        return 0;
    }

    T* get() const { return ptr; }

    void reset(T* p = nullptr) {
        release();
        ptr = p;
        refCount = new size_t(1);
    }
};


template <typename T>
class my_unique_ptr {
private:
    T* ptr;
public:
    explicit my_unique_ptr(T* p = nullptr) : ptr(p) {}

    ~my_unique_ptr() {
        delete ptr;
    }

    my_unique_ptr(const my_unique_ptr&) = delete;
    my_unique_ptr& operator=(const my_unique_ptr&) = delete;

    // 이동 생성자
    my_unique_ptr(my_unique_ptr&& other) noexcept : ptr(nullptr) {
        // 그냥 가져오고 other 비워버림
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    // 이동 대입 연산자
    my_unique_ptr& operator=(my_unique_ptr&& other) noexcept {
        if (this != &other) {
            // TODO
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    T* get() const { return ptr; }

    T* release() {
        // TODO
        T* tmp = ptr;
        ptr = nullptr;
        return tmp;
    }

    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
};
