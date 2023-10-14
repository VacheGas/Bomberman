#pragma once

#include <mutex>

template <typename T>
class Singleton {
protected:
    Singleton() = default;
    virtual ~Singleton() = default;

public:
 static T* getInstance() { std::call_once(_initInstanceFlag, Singleton::init); }

private:
    static void init() { 
        _instance = new T{}; 
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    static std::once_flag _initInstanceFlag;
    static T* _instance;
};

template <typename T>
std::once_flag Singleton<T>::_initInstanceFlag;

template <typename T>
T* Singleton<T>::_instance {nullptr};