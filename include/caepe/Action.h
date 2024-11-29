//
// Created by Enlil on 7/29/2022.
//

#ifndef CAEPE_ACTION_H
#define CAEPE_ACTION_H

#include "ActionResponseContainer.h"
#include "Result.h"

#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace caepe {

    class Action
    {
    public:
        using Parameter = std::variant<int, float, double, char, std::string>;

        explicit Action(const std::string& name);
        Action(const std::string& name, const std::vector<Parameter>& params);
        virtual ~Action();

        Result setResponseContainer(std::shared_ptr<ActionResponseContainer> responseContainer);

        [[nodiscard]]
        const std::string& getName() const;
        [[nodiscard]]
        const std::vector<Parameter>& getParameters() const;
        Result getResponse(ActionResponse &actionResponse) const;

        [[nodiscard]]
        bool isResponseSet() const;

    private:
        const std::string _name;
        std::vector<Parameter> _parameters;
        std::shared_ptr<ActionResponseContainer> _responseContainer; // do not create copies!!
    };

} // caepe

#endif //CAEPE_ACTION_H
