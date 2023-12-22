//
// Created by Enlil on 7/30/2022.
//

#include "ActionResponse.h"

namespace caepe
{

    ActionResponse::ActionResponse()
        : _message(ACTION_RESPONSE_UNDEFINED)
    {
    }

    ActionResponse::ActionResponse(const std::string &message)
        : _message(message)
    {
    }

    ActionResponse::~ActionResponse() = default;

} // caepe