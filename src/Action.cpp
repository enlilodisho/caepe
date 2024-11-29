//
// Created by Enlil on 7/29/2022.
//

#include "Action.h"

namespace caepe {

    Action::Action(const std::string& name)
        : _name(name)
    {
    }

    Action::Action(const std::string& name, const std::vector<Action::Parameter>& params)
            : _name(name), _parameters(params)
    {
    }

    Action::~Action() = default;

    Result Action::setResponseContainer(std::shared_ptr<ActionResponseContainer> responseContainer)
    {
        if (_responseContainer)
        {
            if (responseContainer.get() == _responseContainer.get())
            {
                return { RESULT_OK, "Action already had this response container set." };
            }
            return {RESULT_ERROR, "Action response container is already set."};
        }
        _responseContainer = std::move(responseContainer);
        return Result(RESULT_OK);
    }

    const std::string& Action::getName() const
    {
        return _name;
    }

    const std::vector<Action::Parameter>& Action::getParameters() const
    {
        return _parameters;
    }

    Result Action::getResponse(ActionResponse &actionResponse) const
    {
        if (_responseContainer)
        {
            if (_responseContainer->getActionResponse())
            {
                actionResponse = *_responseContainer->getActionResponse();
                return Result(RESULT_OK);
            }
            return {RESULT_ERROR, "Response container is empty."};
        }
        return {RESULT_ERROR, "Action is missing response container."};
    }

    bool Action::isResponseSet() const
    {
        if (_responseContainer)
        {
            if (_responseContainer->getActionResponse())
            {
                return true;
            }
        }
        return false;
    }

} // caepe