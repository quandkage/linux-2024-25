#pragma once

#include <optional>
#include <string>
#include <unistd.h>
#include <vector>

class Argument
{
public:
    std::optional<std::string> m_flag;
    std::optional<std::string> m_value;

    explicit Argument(std::optional<std::string> flag, std::optional<std::string> value = {})
        : m_flag(std::move(flag)), m_value(std::move(value)) {}
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
        optopt = 0;
        optind = 1;
        int optResult = 0;

        while ((optResult = getopt(m_argc, m_argv, options)) != -1)
        {
            std::string flag(1, static_cast<char>(optResult));
            if (optarg != nullptr)
            {
                m_args.emplace_back(flag, std::string(optarg));
            }
            else
            {
                m_args.emplace_back(flag);
            }
        }
    }

    class Iterator
    {
    private:
        Argument* m_arr;

    public:
        explicit Iterator(Argument* arr) : m_arr(arr) {}

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