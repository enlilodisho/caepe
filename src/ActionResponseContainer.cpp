//
// Created by Enlil on 7/31/2022.
//

#include "ActionResponseContainer.h"

namespace caepe {

    Result ActionResponseContainer::setActionResponse(std::unique_ptr<ActionResponse> actionResponse)
    {
        if (_actionResponse)
        {
            return { RESULT_ERROR, "Action response is already set." };
        }
        _actionResponse = std::move(actionResponse);
        return Result(RESULT_OK);
    }

    const ActionResponse *ActionResponseContainer::getActionResponse() const
    {
        return _actionResponse.get();
    }

    bool ActionResponseContainer::isResponseSet() const
    {
        if (_actionResponse)
        {
            return true;
        }
        return false;
    }

} // caepe