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
    print_memory_usage();

    sleep(10);

    
    print_memory_usage();

   
    size_t page_size = getpagesize();
    void* mapped_page = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (mapped_page == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    printf("Mapped an empty page from the OS.\n");

    
    sleep(10);

    
    print_memory_usage();

    
    char* data = (char*)mapped_page;
    data[0] = 'H';
    data[1] = 'i';
    data[2] = '!';

    printf("Wrote data into the memory mapped page.\n");

    sleep(10);
    
    print_memory_usage();

  
    if (munmap(mapped_page, page_size) == -1) {
        perror("munmap failed");
        return 1;
    }

    printf("Unmapped the memory page.\n");

 
    sleep(10);

    print_memory_usage();

    return 0;
}
