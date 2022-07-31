//
// Created by Enlil on 7/30/2022.
//

#ifndef CAEPE_ACTIONRESPONSECONTAINER_H
#define CAEPE_ACTIONRESPONSECONTAINER_H

#include "ActionResponse.h"
#include "Result.h"

#include <memory>

namespace caepe
{

    class ActionResponseContainer
    {
    private:
        std::unique_ptr<ActionResponse> _actionResponse;

    public:
        Result setActionResponse(std::unique_ptr<ActionResponse> actionResponse);
        [[nodiscard]]
        const ActionResponse* getActionResponse() const;
        [[nodiscard]]
        bool isResponseSet() const;
    };

} // caepe

#endif //CAEPE_ACTIONRESPONSECONTAINER_H
