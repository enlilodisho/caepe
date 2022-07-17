//
// Created by Enlil on 7/15/2022.
//

#ifndef CAEPE_COMPONENT_H
#define CAEPE_COMPONENT_H

#include "Result.h"

#include <string>
#include <thread>
#include <memory>
#include <mutex>

namespace caepe {

    class Component {
    private:
        std::unique_ptr<std::thread> _thread;
        bool _started = false;
        std::mutex _mtx;

        void componentThread();

    protected:
        virtual void onStart();
        virtual void onLoop();
        virtual void onEnd();

    public:
        const std::string _name;

        explicit Component(std::string name);
        ~Component();

        Result start();
        Result stop();

        [[nodiscard]]
        bool isStarted() const;
    };

} // caepe

#endif //CAEPE_COMPONENT_H
