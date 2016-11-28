#include <iostream>
#include <stdexcept>

template <class T>
class shared{
public:
    shared(); /*strong*/
    shared(T* ptr ); /*strong*/
    shared(const shared &); /*noexcept*/
    shared(shared &&); /* noexcept */
    ~shared();/*noexcept */
    auto operator=(const shared &) /*noexcept*/ -> shared&;
    auto operator=(shared &&) /*noexcept*/ -> shared&;
    auto operator*() const /* strong */ -> T&;
    auto operator->() const /* strong */-> T*;
    auto use_count() const /*noexcept*/ -> size_t ;
    auto reset(T *tmp) /* strong */ -> void;
    auto swap(shared &ptr) /*noexcept*/ -> void;
    auto get()const /*noexcept*/ -> T*;
private:

    T *ptr;
    size_t *counter;
};

template <class T>
shared<T>::shared()
        :   ptr(nullptr),
            counter(nullptr)
{
    ;
}


template <typename T, class ...Args>
auto make_shared( Args && ...args ) -> shared<T>
{
    return shared<T>( new T( std::forward<Args>(args)... ) );
}

template <class T>
shared<T>::shared(T *tmp)
    :   ptr(tmp),
        counter(new size_t(1))
{
    ;
}

template <class T>
shared<T>::shared(const shared &other)
        :   ptr(other.ptr),
            counter(other.counter)
{
    if (counter != nullptr) {
        ++(*counter);
    }
}

template <class T>
shared<T>::shared(shared<T> &&other)
    :   ptr(other.ptr),
        counter(other.counter)
{
    other.counter = nullptr;
    other.ptr = nullptr;
}


template <class T>
shared<T>::~shared() {
    if (counter != nullptr)
    {
        if (*counter == 1) {
            delete ptr;
            delete counter;
        }      else{
            --(*counter);
        };
    }
}

template <class T>
auto shared<T>::operator=(const shared &other) -> shared & {
    if (this != &other)
    {
        (shared<T>(other)).swap(*this);
    }
    return *this;
}

template <class T>
auto shared<T>::operator=(shared &&other) -> shared & {
    if (this != &other) {
        shared<T> tmp(std::move(other));
        this->swap(tmp);
    }
    return *this;
}

template <class T>
void shared<T>::reset(T *tmp) {
    if (ptr != tmp) {
        if (*counter == 1) {
            delete ptr;
            delete counter;
        } else {
            --(*counter);
        }
        ptr = tmp;
        if (ptr != nullptr) {
            counter = new size_t(1);
        } else {
            counter = nullptr;
        }
    }
}
template <class T>
auto shared<T>::get() const-> T * {
    return ptr;
}

template <class T>
auto shared<T>::swap(shared &other) -> void {
    std::swap(ptr, other.ptr);
    std::swap(counter, other.counter);
}

template <class T>
auto shared<T>::operator*() const -> T& {
    if (!ptr) {
        throw std::logic_error("error: ptr = nullptr");
    }
    return *ptr;
}

template <typename T>
auto shared<T>::use_count() const -> size_t {
    if  (counter != nullptr) {
        return *counter;
    }
    else {
        return 0;
    }
}

template <class T>
auto shared<T>::operator->() const -> T* {
    if (!ptr) {
        throw std::logic_error("error: ptr = nullptr");
    }
    return ptr;
}
