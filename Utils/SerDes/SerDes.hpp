#pragma once
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <type_traits>
#include <sys/mman.h>
#include <cstring>


template <class T>
class SerDes {
private:
    int fd_ = - 1;
    void* data_ = MAP_FAILED;
    size_t size_;
public:

    SerDes(const std::string& fl, size_t size) {
        fd_ = open(fl.c_str(), O_RDWR | O_CREAT, 0666);
        if (fd_ == -1) {
            throw std::runtime_error("file el ches karum baces...");
        }
        if (ftruncate(fd_, size) == -1) {
            std::cerr << "Hopar jan chenq karecel file-d resize anenq" << std::endl;
            close(fd_);
            throw std::runtime_error("Nerox Mecutyun");
        }

        data_ = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0);
        if (data_ == MAP_FAILED) {
            std::cerr << "Hopar jan chgitem xi chkarecanq mapping anenq, de kneres patahuma" << std::endl;
            close(fd_);
            throw std::runtime_error("Myus Kyanqum kstacvi");
        }
    }

    ~SerDes() {
        if (data_ != MAP_FAILED) {
            munmap(data_, size_);
        }
        if (fd_ != -1) {
            close(fd_);
        }
    }

    void* getData() {
        return data_;
    }

    int getFd() const {
        return fd_;
    }
};

template <typename T>
void serialize(const T& obj, const std::string& name) {
    static_assert(std::is_trivially_copyable_v<T>, "Axper asecinq Trivially Copyable (maqur hayerenov)");

    SerDes<T> mmHopar(name, sizeof(T));

    std::memcpy(mmHopar.getData(), &obj, sizeof(T));
}
template <typename T>
void deserialize(T& obj, const std::string& name) {
    static_assert(std::is_trivially_copyable_v<T>, "Chem jogum xi es noncopyable - y deserialize anum kam aveli hzor harc xi ?");

    SerDes<T> mmHopar(name, sizeof(T));

    std::memcpy(&obj, mmHopar.getData(), sizeof(T));
}
