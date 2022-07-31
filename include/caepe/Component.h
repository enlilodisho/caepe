//
// Created by Enlil on 7/15/2022.
//

#ifndef CAEPE_COMPONENT_H
#define CAEPE_COMPONENT_H

#include "Result.h"
#include "Event.h"
#include "Action.h"
#include "ActionResponseContainer.h"

#include <string>
#include <thread>
#include <memory>
#include <mutex>
#include <queue>
#include <vector>
#include <utility>
#include <tuple>

namespace caepe {

    class Component {
    private:
        std::unique_ptr<std::thread> _thread;
        bool _started = false;
        std::mutex _startStopMtx;

        std::queue<std::pair<Component*, std::shared_ptr<Action>>> _pendingActions;
        std::vector<std::tuple<std::shared_ptr<Action>, std::shared_ptr<ActionResponseContainer>, long>> _pendingActionResponses;
        std::queue<std::pair<Component*, std::shared_ptr<const Event>>> _pendingEvents;
        std::mutex _actionsMtx;
        std::mutex _eventsMtx;

        void componentThread();

    protected:
        virtual void onStart();
        virtual void onLoop();
        virtual void onAction(Component &sender, std::shared_ptr<Action> action,
                              std::shared_ptr<ActionResponseContainer> responseContainer);
        virtual void onEvent(Component &sender, std::shared_ptr<const Event> event);
        virtual void onEnd();

    public:
        const std::string _name;

        explicit Component(std::string name);
        ~Component();

        Result start();
        Result stop();

        [[maybe_unused]]
        Result receiveAction(Component *sender, std::unique_ptr<Action> action,
                             std::shared_ptr<Action> &out_action);
        [[maybe_unused]]
        Result receiveEvent(Component *sender, std::shared_ptr<const Event> event);

        [[nodiscard]]
        bool isStarted() const;
    };

} // caepe

#endif //CAEPE_COMPONENT_H
