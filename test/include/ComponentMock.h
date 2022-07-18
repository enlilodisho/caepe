//
// Created by Enlil on 7/15/2022.
//

#ifndef CAEPE_COMPONENTMOCK_H
#define CAEPE_COMPONENTMOCK_H

#include <caepe/Component.h>
#include <caepe/Event.h>

#include <vector>
#include <utility>
#include <mutex>

class ComponentMock : public caepe::Component
{
private:
    long _ranOnStart = 0;
    long _ranOnLoop = 0;
    long _ranOnEnd = 0;

    std::vector<std::pair<Component*, std::shared_ptr<const caepe::Event>>> _receivedEvents;
    std::mutex _mtx;

protected:
    void onStart() override
    {
        _ranOnStart++;
    }

    void onEvent(Component &sender, std::shared_ptr<const caepe::Event> event) override
    {
        std::lock_guard lock(_mtx);
        _receivedEvents.emplace_back(&sender, std::move(event));
    }

    void onLoop() override
    {
        _ranOnLoop++;
    }

    void onEnd() override
    {
        _ranOnEnd++;
    }

public:
    explicit ComponentMock(const std::string& name) : caepe::Component(name)
    {
    }

    [[nodiscard]]
    long getOnStartRunCount() const
    {
        return _ranOnStart;
    }

    [[nodiscard]]
    long getOnLoopRunCount() const
    {
        return _ranOnLoop;
    }

    [[nodiscard]]
    long getOnEndRunCount() const
    {
        return _ranOnEnd;
    }

    [[nodiscard]]
    std::vector<std::pair<Component*, std::shared_ptr<const caepe::Event>>> getReceivedEvents()
    {
        std::lock_guard lock(_mtx);
        auto v = std::move(_receivedEvents);
        _receivedEvents = std::vector<std::pair<Component*, std::shared_ptr<const caepe::Event>>>();
        return std::move(v);
    }
};

#endif //CAEPE_COMPONENTMOCK_H
