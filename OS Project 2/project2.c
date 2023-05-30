#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

void print_memory_usage() {
    FILE* status_file = fopen("/proc/self/status", "r");
    char line[128];

    printf("Memory Usage:\n");
    while (fgets(line, sizeof(line), status_file)) {
        if (strncmp(line, "VmSize:", 7) == 0 || strncmp(line, "VmRSS:", 6) == 0) {
            printf("%s", line);
        }
    }

    fclose(status_file);
}

int main() {
    printf("Running program...\n");

    // Print initial memory usage
    print_memory_usage();

    // Pause the program for a while
    sleep(10);

    // Print memory usage after sleeping
    print_memory_usage();

    // Map an empty page from the OS
    size_t page_size = getpagesize();
    void* mapped_page = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (mapped_page == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    printf("Mapped an empty page from the OS.\n");

    // Pause the program again
    sleep(10);

    // Print memory usage after mapping a page
    print_memory_usage();

    // Write some data into the memory mapped page
    char* data = (char*)mapped_page;
    data[0] = 'H';
    data[1] = 'i';
    data[2] = '!';

    printf("Wrote data into the memory mapped page.\n");

    // Pause the program once more
    sleep(10);

    // Print memory usage after writing data
    print_memory_usage();

    // Unmap the memory page
    if (munmap(mapped_page, page_size) == -1) {
        perror("munmap failed");
        return 1;
    }

    printf("Unmapped the memory page.\n");

    // Pause the program for the last time
    sleep(10);

    // Print final memory usage
    print_memory_usage();

    return 0;
}