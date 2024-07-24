#pragma once

#include <memory>
#include <list>


class Observer {
public:    
    virtual ~Observer() = default;
    virtual void update() = 0;
};

class ObserverForTests : public Observer {
public:    
    virtual ~ObserverForTests() = default;
    virtual void update() override {}
};


class Observed {
public:
    virtual ~Observed() = default;
    virtual void addObserver(const std::shared_ptr<Observer> &observer) = 0;
    virtual void notify() = 0;
};

class BaseObserved : public Observed {
    std::list <std::weak_ptr<Observer>> _observers;
public:
    virtual ~BaseObserved() = default;

    void addObserver(const std::shared_ptr<Observer> &observer) override {
        _observers.emplace_front(observer);
    }

    void notify() override {
        auto iter = _observers.begin();
        while(iter != _observers.end()) {
            auto ptr = iter->lock();
            if (ptr) {  
                ptr->update();
                ++iter;
            } else {
                _observers.erase(iter++);
            } 
        }
    }
};