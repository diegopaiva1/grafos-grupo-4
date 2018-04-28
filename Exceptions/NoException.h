#ifndef NOEXCEPTION_H
#define NOEXCEPTION_H

#include <iostream>
#include <exception>
#include <string>

class NoException : public std::exception
{
    private:
        std::string _msg;
    public:
        NoException(const std::string& msg) : _msg(msg) {}
        virtual const char* what() const noexcept override
        {
            return _msg.c_str();
        }
};

#endif // NOEXCEPTION_H
