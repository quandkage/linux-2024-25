#include "Directory.h"


Directory::Directory(std::string path) : m_path(std::move(path)) {}

//private nested Function
void Directory::RecursiveDirectoryIterator::open_dir(const std::string& path) {
    DIR* dir = opendir(path.c_str());
    if (dir) {
        m_dirStack.emplace(dir, path);
        // m_dirStack.push(std::make_pair(dir, path));
    }
}

void Directory::RecursiveDirectoryIterator::next_entry() {
    while (!m_dirStack.empty()) {
        m_entry = readdir(m_dirStack.top().first);
        if (m_entry) {
            std::string dirName = m_entry->d_name;
            if (dirName != "." && dirName != "..") {
                if (m_entry->d_type == DT_DIR) {
                    open_dir(m_dirStack.top().second + "/" + dirName);
                }
                return;
            }
        } else {
            closedir(m_dirStack.top().first);
            m_dirStack.pop();
        }
    }
    m_entry = nullptr;
}

//public nested

Directory::RecursiveDirectoryIterator::RecursiveDirectoryIterator(const std::string& path) : m_entry(nullptr) {
    open_dir(path);
    next_entry();
}

std::string Directory::RecursiveDirectoryIterator::operator*() const {
    return getName();
}

Directory::RecursiveDirectoryIterator &Directory::RecursiveDirectoryIterator::operator++() {
    next_entry();
    return *this;
}

std::string Directory::RecursiveDirectoryIterator::getName() const {
    return m_entry ? m_entry->d_name : "";
}

Directory::RecursiveDirectoryIterator Directory::begin() const {
    return RecursiveDirectoryIterator(m_path);
}

Directory::RecursiveDirectoryIterator Directory::end() const {
    return RecursiveDirectoryIterator("");
}

bool Directory::RecursiveDirectoryIterator::operator!=(const RecursiveDirectoryIterator &other) const {
    return m_entry != other.m_entry;
}






