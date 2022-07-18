//
// Created by Enlil on 7/15/2022.
//

#ifndef CAEPE_COMPONENT_H
#define CAEPE_COMPONENT_H

#include "Result.h"
#include "Event.h"

#include <string>
#include <thread>
#include <memory>
#include <mutex>
#include <queue>
#include <utility>

namespace caepe {

    class Component {
    private:
        std::unique_ptr<std::thread> _thread;
        bool _started = false;
        std::mutex _startStopMtx;

        std::queue<std::pair<Component*, std::shared_ptr<const Event>>> _pendingEvents;
        std::mutex _eventsMtx;

        void componentThread();

    protected:
        virtual void onStart();
        virtual void onEvent(Component &sender, std::shared_ptr<const Event> event);
        virtual void onLoop();
        virtual void onEnd();

    public:
        const std::string _name;

        explicit Component(std::string name);
        ~Component();

        Result start();
        Result stop();
        Result addEvent(Component *sender, std::shared_ptr<const Event> event);

        [[nodiscard]]
        bool isStarted() const;
    };

} // caepe

#endif //CAEPE_COMPONENT_H
