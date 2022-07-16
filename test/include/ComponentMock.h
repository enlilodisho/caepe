//
// Created by Enlil on 7/15/2022.
//

#ifndef CAEPE_COMPONENTMOCK_H
#define CAEPE_COMPONENTMOCK_H

#include <caepe/Component.h>

class ComponentMock : public caepe::Component
{
private:
    long _ranOnStart = 0;
    long _ranOnLoop = 0;
    long _ranOnEnd = 0;

public:
    explicit ComponentMock(const std::string& name) : caepe::Component(name)
    {
    }

    void onStart() override
    {
        _ranOnStart++;
    }

    void onLoop() override
    {
        _ranOnLoop++;
    }

    void onEnd() override
    {
        _ranOnEnd++;
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
};

#endif //CAEPE_COMPONENTMOCK_H
