#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <sys/inotify.h>
#include <dirent.h>
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>

class WatchDogs {
private:
    int fd;
    std::string path_;
    int watch_fd;
    bool isFile = false;

    void checkPathType() {
        struct stat p_stat;
        if (stat(path_.c_str(), &p_stat) == 0) {
            if (S_ISREG(p_stat.st_mode)) {
                isFile = true;
            } else if (S_ISDIR(p_stat.st_mode)) {
                isFile = false;
            } else {
                std::cerr << "Unknown file type." << std::endl;
                std::exit(EXIT_FAILURE);
            }
        } else {
            std::cerr << "Failed to stat path: " << strerror(errno) << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    void monitoringDir() {
        DIR* dir = opendir(path_.c_str());
        if (!dir) {
            std::cerr << "Failed to open directory: " << path_ << std::endl;
            std::exit(EXIT_FAILURE);
        }

        watch_fd = inotify_add_watch(fd, path_.c_str(), IN_ALL_EVENTS);
        if (watch_fd == -1) {
            std::cerr << "Failed to watch directory: " << path_ << std::endl;
            std::exit(EXIT_FAILURE);
        }

        struct dirent* entry;
        while ((entry = readdir(dir))) {
            std::string filePath = path_ + "/" + entry->d_name;
            if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                WatchDogs subDirWathcer(filePath);
            } else if (entry->d_type == DT_REG) {
                int fil_watch_fd = inotify_add_watch(fd, filePath.c_str(), IN_ALL_EVENTS);
                if (fil_watch_fd == -1) {
                    std::cerr << "Failed to watch file: " << filePath << std::endl;
                    std::exit(EXIT_FAILURE);
                }
            }
        }
        closedir(dir);
    }

public:
    explicit WatchDogs(const std::string& path) : fd(inotify_init1(0)), path_(path) {
        if (fd == -1) {
            std::cerr << "Inotify_init1 failed" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        checkPathType();

        if (!isFile) {
            monitoringDir();
        } else {
            watch_fd = inotify_add_watch(fd, path_.c_str(), IN_MODIFY | IN_CREATE | IN_DELETE | IN_MOVE | IN_ACCESS);
            if (watch_fd == -1) {
                std::cerr << "Failed to watch file: " << path_ << std::endl;
                std::exit(EXIT_FAILURE);
            }
        }
    }

    ~WatchDogs() {
        if (fd != -1) {
            close(fd);
        }
    }

    void monitoring() {
        char buffer[PATH_MAX];

        while (true) {
            ssize_t bytesRead = read(fd, &buffer, sizeof(buffer));
            if (bytesRead == -1) {
                std::cerr << "Failed to read from file: " << path_ << std::endl;
                std::exit(EXIT_FAILURE);
            }
            for (size_t i = 0; i < bytesRead;) {
                struct inotify_event* event = (struct inotify_event*)&buffer[i];

                if (event->mask & IN_MODIFY) {
                    std::cout << "Modified: " << event->name << std::endl;
                }
                if (event->mask & IN_CREATE) {
                    std::cout << "Created: " << event->name << std::endl;
                }
                if (event->mask & IN_DELETE) {
                    std::cout << "Deleted: " << event->name << std::endl;
                }
                if (event->mask & IN_MOVE) {
                    std::cout << "Moved: " << event->name << std::endl;
                }
                if (event->mask & IN_ACCESS) {
                    std::cout << "Accessed: " << event->name << std::endl;
                }

                i += sizeof(struct inotify_event) + event->len;
            }
        }
    }
};

void testWatchDogs() {
    const std::string dirPath = "/home/robert/linux-2024-25/Demo/WatchDogs/Test";
    WatchDogs watcher(dirPath);

    std::thread monitoringThread([&watcher]() {
        watcher.monitoring();
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));

    DIR* dir = opendir(dirPath.c_str());
    if (dir == nullptr) {
        std::cerr << "Failed to open directory: " << dirPath << std::endl;
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

        std::string filePath = dirPath + "/" + entry->d_name;

        std::ofstream file(filePath, std::ios::app);
        if (file.is_open()) {
            file << "Additional content added for testing" << std::endl;
            file.close();
        } else {
            std::cerr << "Failed to open file for modification: " << filePath << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    closedir(dir);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    monitoringThread.detach();
}