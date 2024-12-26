#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <iostream>
#include <dirent.h>
#include <stack>
#include <string>
#include <utility>

class Directory {
private:
    std::string m_path;

public:
    explicit Directory(std::string path);

    class RecursiveDirectoryIterator {
    private:
        std::stack<std::pair<DIR*, std::string>> m_dirStack;
        dirent* m_entry;

        void open_dir(const std::string& path);

        void next_entry();

    public:
        explicit RecursiveDirectoryIterator(const std::string& path);

        std::string operator*() const;

        RecursiveDirectoryIterator& operator++();

        [[nodiscard]] std::string getName() const;

        bool operator!=(const RecursiveDirectoryIterator& other) const;
    };

    [[nodiscard]] RecursiveDirectoryIterator begin() const;

    [[nodiscard]] RecursiveDirectoryIterator end() const;

};

#endif

