/**
    step 1: Get the filesize. You need to know that before calling mmap, but you can also mmap a subset only.
    
    Step 2: Open the file. Keep in mind you can’t use the fopen() function directly (you could use fileno() on the FILE object) because you need the file descriptor! In this case we’re using O_RDONLY because we want to mmap() read-only.
    
    Step 3: Call mmap() with those parameters:
    
    NULL: Let the kernel decide which address to mmap at. This is the recommended address parameter.
    
    filesize: The size of the file. For readonly-mmap only values <= the real filesize make sense.
    
    PROT_READ: Map the file read-only (in other words, use read-only page protection)
    
    MAP_PRIVATE: Usually this means don’t write changes to the mmaped memory back to the file, but we mapped it readonly anyway, so using this or MAP_SHARED does’t make any noticeable difference.
    
    MAP_POPULATE: Let the kernel preload parts of the file. This is a performance optimization. There is no absolute need to use this.
    
    fd: The unix file descriptor to map (if you have a FILE*, you can get the descriptor number using fileno()). Must be opened * 0: The offset from the beginning of the file. 0 because we want to map the entire file
    
    For a detailed mmap() reference, see the Opengroup page on mmap
**/

#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <assert.h>

size_t getFilesize(const char* filename) {
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}

int main(int argc, char** argv) {
    size_t filesize = getFilesize(argv[1]);
    //Open file
    if(argc<2){
        printf("Usage: ./mmap_test filename\n");
        return -1;
    }
    int fd = open(argv[1], O_RDONLY, 0);
    assert(fd != -1);
    //Execute mmap
    void* mmappedData = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, 0);
    assert(mmappedData != MAP_FAILED);
    //Write the mmapped data to stdout (= FD #1)
    write(1, mmappedData, filesize);
    //Cleanup
    int rc = munmap(mmappedData, filesize);
    assert(rc == 0);
    close(fd);
}
