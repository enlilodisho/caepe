//
// Created by Enlil on 7/30/2022.
//

#ifndef CAEPE_ACTIONRESPONSE_H
#define CAEPE_ACTIONRESPONSE_H

#include <string>

namespace caepe
{

    const std::string ACTION_RESPONSE_UNDEFINED = "Undefined";
    [[maybe_unused]]
    const std::string ACTION_RESPONSE_NONE = "NoResponse";
    [[maybe_unused]]
    const std::string ACTION_RESPONSE_SUCCESS = "Success";

    struct ActionResponse {
        std::string _message;

        ActionResponse();
        explicit ActionResponse(const std::string &message);
    };

} // caepe

#endif //CAEPE_ACTIONRESPONSE_H
