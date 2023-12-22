//
// Created by Enlil on 7/29/2022.
//

#ifndef CAEPE_ACTION_H
#define CAEPE_ACTION_H

#include "ActionResponseContainer.h"
#include "Result.h"

#include <memory>
#include <string>

namespace caepe {

    class Action
    {
    private:
        const std::string _name;
        std::shared_ptr<ActionResponseContainer> _responseContainer; // do not create copies!!

    public:
        explicit Action(const std::string& name);
        virtual ~Action();

        Result setResponseContainer(std::shared_ptr<ActionResponseContainer> responseContainer);

        [[nodiscard]]
        const std::string& getName() const;
        Result getResponse(ActionResponse &actionResponse) const;

        [[nodiscard]]
        bool isResponseSet() const;
    };

} // caepe

#endif //CAEPE_ACTION_H
