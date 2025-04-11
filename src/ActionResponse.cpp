//
// Created by Enlil on 7/30/2022.
//

#include "ActionResponse.h"

namespace caepe
{

    ActionResponse::ActionResponse()
        : _message(ActionResponse::UNDEFINED)
    {
    }

    ActionResponse::ActionResponse(const std::string &message)
        : _message(message)
    {
    }

    ActionResponse::ActionResponse(const std::string &message, std::any data)
        : _message(message), _data(std::move(data))
    {
    }

    ActionResponse::~ActionResponse() = default;

    const std::string& ActionResponse::getMessage() const
    {
        return _message;
    }

    bool ActionResponse::hasData() const
    {
        return _data.has_value();
    }

    const std::type_info& ActionResponse::getDataType() const
    {
        return _data.type();
    }

} // caepe