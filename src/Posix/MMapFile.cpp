#if defined(_WIN32)
#error "mmap_posix.cpp should not be built on Windows"
#endif

#include <hgl/io/MMapFile.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>
#include <string>

namespace hgl
{
    class MMapFileImpl {
    public:
        int fd = -1;
    };

    MMapFile::MMapFile(const std::string& filename, size_t size, bool readOnly)
        : data_(nullptr), size_(size)
    {
        int flags = readOnly ? O_RDONLY : O_RDWR;
        MMapFileImpl* impl = new MMapFileImpl();
        impl_ = impl;
        impl->fd = open(filename.c_str(), flags, 0666);
        if (impl->fd < 0) {
            delete impl;
            throw std::runtime_error("Failed to open file");
        }

        off_t fileSize = lseek(impl->fd, 0, SEEK_END);
        if (fileSize < (off_t)size) {
            if (ftruncate(impl->fd, size) != 0) {
                close(impl->fd);
                delete impl;
                throw std::runtime_error("Failed to extend file");
            }
        }

        int prot = readOnly ? PROT_READ : (PROT_READ | PROT_WRITE);
        data_ = mmap(nullptr, size, prot, MAP_SHARED, impl->fd, 0);
        if (data_ == MAP_FAILED) {
            close(impl->fd);
            delete impl;
            throw std::runtime_error("Failed to mmap file");
        }

        (void)impl; // already stored in impl_
    }

    MMapFile::~MMapFile()
    {
        auto impl = reinterpret_cast<MMapFileImpl*>(impl_);
        if (data_) munmap(data_, size_);
        if (impl) {
            if (impl->fd >= 0) close(impl->fd);
            delete impl;
        }
    }

    void* MMapFile::data() { return data_; }
    size_t MMapFile::size() const { return size_; }
}//namespace hgl
