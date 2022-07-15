//
// Created by Enlil on 7/15/2022.
//

#ifndef CAEPE_RESULT_H
#define CAEPE_RESULT_H

#include <string>

namespace caepe {

    enum ResultValue
    {
        RESULT_OK,
        RESULT_ERROR
    };

    struct Result
    {
    private:
        ResultValue _value;
        std::string _message;

    public:
        explicit Result(ResultValue value);
        Result(ResultValue value, std::string message);

        Result& operator+=(const Result& other);

        [[nodiscard]]
        bool isSuccess() const;

        [[nodiscard]]
        const ResultValue& getValue() const;

        [[nodiscard]]
        const std::string& getMessage() const;
    };

} // caepe

#endif //CAEPE_RESULT_H
