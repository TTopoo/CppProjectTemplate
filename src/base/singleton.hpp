#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include "lock.hpp"
#include <cstdlib>
#include <new>

template<typename T, bool LongLifeTime = false>
class Singleton;

template<typename T>
class Singleton<T, false>
{
public:
    template<typename... Args>
    static T &instance(Args &&...args)
    {
        static T obj(std::forward<Args>(args)...);
        return obj;
    }

protected:
    Singleton() = default;
    virtual ~Singleton() {}

private:
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton &operator=(Singleton &&) = delete;
};

template<typename T>
class Singleton<T, true>
{
public:
    template<typename... Args>
    static T &instance(Args &&...args)
    {
        if (!p_instance)
        {
            // DCL
            lock.lock();

            if (!p_instance)
            {
                destroyed ? on_dead_reference(std::forward<Args>(args)...) : create(std::forward<Args>(args)...);
            }

            lock.unlock();
        }

        return *p_instance;
    }

private:
    template<typename... Args>
    static void create(Args &&...args)
    {
        static T obj(std::forward<Args>(args)...);
        p_instance = &obj;
    }

    template<typename... Args>
    static void on_dead_reference(Args &&...args)
    {
        create(std::forward<Args>(args)...);
        new (p_instance) T(std::forward<Args>(args)...);
        std::atexit(kill_singleton);
        destroyed = false;
    }

    static void kill_singleton()
    {
        p_instance->~T();
    }

    Singleton(const Singleton &);
    Singleton &operator=(const Singleton &);
    Singleton(Singleton &&);
    Singleton &operator=(Singleton &&);

    static SpinLock lock;

protected:
    Singleton() = default;
    virtual ~Singleton()
    {
        p_instance = nullptr;
        destroyed = true;
    }

    static T *p_instance;
    static bool destroyed;
};

template<typename T>
T *Singleton<T, true>::p_instance = nullptr;
template<typename T>
bool Singleton<T, true>::destroyed = false;
template<typename T>
SpinLock Singleton<T, true>::lock;

#endif // SINGLETON_HPP
