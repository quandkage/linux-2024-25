#pragma once
#include <iostream>
#include <sys/inotify.h>
#include <unistd.h>
#include <fcntl.h>

void wathcer(const std::string& path) {
    int fd = inotify_init();
    if (fd == -1) {
        std::cerr << "ERROR: inotify_init() failed" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    int dWatcher = inotify_add_watch(fd, path.c_str(), IN_CREATE | IN_MODIFY | IN_DELETE  | IN_ATTRIB | IN_MOVE);
    if (dWatcher == -1) {
        std::cerr << "ERROR: inotify_add_watch() failed" << std::endl;
        close(fd);
        std::exit(EXIT_FAILURE);
    }

    char buf[8192];

    while (true) {
        ssize_t n = read(fd, buf, sizeof(buf));
        if (n == -1) {
            std::cerr << "ERROR: read() failed" << std::endl;
            break;
        }

        ssize_t i = 0;
        while (i < n) {
            struct inotify_event *event = (struct inotify_event*)&buf[i];
            if (event->mask & IN_CREATE) {
                std::cout << "File Created" << event->name << std::endl;
            }
            else if (event->mask & IN_MODIFY) {
                std::cout << "File Modified" << event->name << std::endl;
            }
            else if (event->mask & IN_DELETE) {
                std::cout << "File Deleted" << event->name << std::endl;
            }
            else if (event->mask & IN_ATTRIB) {
                std::cout << "File Attributes" << event->name << std::endl;
            }
            else if (event->mask & IN_MOVE) {
                std::cout << "File Moved" << event->name << std::endl;
            }
            i += sizeof(struct inotify_event) + event->len;
        }
    }
    close(fd);
}