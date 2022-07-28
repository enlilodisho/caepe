//
// Created by Enlil on 7/15/2022.
//
#include "Result.h"

namespace caepe
{

    Result::Result(ResultValue value)
        : Result(value, "") {}

    Result::Result(ResultValue value, std::string message)
        : _value(value), _message(std::move(message)) {}

    Result& Result::operator+=(const Result& other)
    {
        if (_value == RESULT_OK && other._value == RESULT_ERROR)
        {
            _value = RESULT_ERROR;
        }
        if (other._message.length() > 0)
        {
            if (_message.length() > 0)
            {
                _message += "\n" + other._message;
            }
            else
            {
                _message = other._message;
            }
        }
        return *this;
    }

    bool Result::isSuccess() const
    {
        return _value == RESULT_OK;
    }

    const ResultValue& Result::getValue() const
    {
        return _value;
    }

    const std::string& Result::getMessage() const
    {
        return _message;
    }

} // caepe