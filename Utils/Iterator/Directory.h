#include <iostream>
#include <dirent.h>
#include <stack>
#include <string>
#include <utility>

class Directory {
private:
    std::string m_path;

public:
    explicit Directory(std::string path) : m_path(std::move(path)) {}

    class RecursiveDirectoryIterator {
    private:
        std::stack<DIR*> m_dirStack;
        std::stack<std::string> m_pathStack;
        dirent* m_entry;

        void open_dir(const std::string& path) {
            DIR* dir = opendir(path.c_str());
            if (dir) {
                m_dirStack.push(dir);
                m_pathStack.push(path);
            }
        }

        void next_dir() {
            while (!m_dirStack.empty()) {
                m_entry = readdir(m_dirStack.top());
                if (m_entry) {
                    std::string dirName = m_entry->d_name;
                    if (dirName != "." && dirName != "..") {
                        if (m_entry->d_type == DT_DIR) {
                            open_dir(m_pathStack.top() + "/" + dirName);
                        }
                        return;
                    }
                } else {
                    closedir(m_dirStack.top());
                    m_dirStack.pop();
                    m_pathStack.pop();
                }
            }
            m_entry = nullptr;
        }

    public:
        explicit RecursiveDirectoryIterator(const std::string& path) : m_entry(nullptr) {
            open_dir(path);
            next_dir();
        }

        const dirent* operator*() const {
            return m_entry;
        }

        RecursiveDirectoryIterator& operator++() {
            next_dir();
            return *this;
        }
        std::string getName() const {
            return m_entry ? m_entry->d_name : "";
        }
        bool operator!=(const RecursiveDirectoryIterator& other) const {
            return m_entry != other.m_entry;
        }
    };

    RecursiveDirectoryIterator begin() const {
        return RecursiveDirectoryIterator(m_path);
    }

    RecursiveDirectoryIterator end() const {
        return RecursiveDirectoryIterator("");
    }
};

