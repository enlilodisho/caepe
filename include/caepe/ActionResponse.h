//
// Created by Enlil on 7/30/2022.
//

#ifndef CAEPE_ACTIONRESPONSE_H
#define CAEPE_ACTIONRESPONSE_H

#include <any>
#include <string>
#include <typeinfo>

namespace caepe
{
    class ActionResponse {
    private:
        std::string _message;
        std::any _data;

    public:
        inline static const std::string UNDEFINED = "Undefined";
        inline static const std::string NONE = "NoResponse";
        [[maybe_unused]]
        inline static const std::string SUCCESS = "Success";
        [[maybe_unused]]
        inline static const std::string FAILURE = "Failure";

        ActionResponse();
        explicit ActionResponse(const std::string &message);
        ActionResponse(const std::string &message, std::any data);
        virtual ~ActionResponse();

        [[nodiscard]]
        const std::string& getMessage() const;

        [[nodiscard]]
        bool hasData() const;

        [[nodiscard]]
        const std::type_info& getDataType() const;

        template <typename T>
        bool getData(T& outData) const
        {
            if (_data.type() == typeid(T))
            {
                outData = std::any_cast<T>(_data);
                return true;
            }
            return false;
        }

    };

} // caepe

#endif //CAEPE_ACTIONRESPONSE_H
