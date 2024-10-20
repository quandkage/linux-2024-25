#pragma once

#include <optional>
#include <string>
#include <unistd.h>
#include <vector>
#include <stdexcept>

class Argument
{
public:
    char m_flag;
    std::optional<std::string> m_value;

    explicit Argument(char flag, std::optional<std::string> value = {})
        : m_flag(flag), m_value(std::move(value)) {}
};

class ArgumentParser
{
private:
    int m_argc;
    char** m_argv;
    std::vector<Argument> m_args;

public:
    ArgumentParser(int count, char** list, const char* options) : m_argc(count), m_argv(list)
    {
        opterr = 0;
        int optResult;

        while ((optResult = getopt(m_argc, m_argv, options)) != -1)
        {
            if (optarg != nullptr)
            {
                m_args.emplace_back(optResult, std::string(optarg));
            }
            else
            {
                m_args.emplace_back(optResult);
            }
        }
    }

    class Iterator
    {
    private:
        Argument* m_arr;

    public:
        Iterator(Argument* arr) : m_arr(arr) {}

        Argument* operator->() const { return m_arr; }

        Argument& operator*() const { return *m_arr; }

        Iterator operator++()
        {
            m_arr++;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator tmp = *this;
            m_arr++;
            return tmp;
        }

        bool operator!=(const Iterator& s) const { return m_arr != s.m_arr; }
    };

    Iterator begin()
    {
        return Iterator(m_args.data());
    }

    Iterator end()
    {
        return Iterator(m_args.data() + m_args.size());
    }
};
