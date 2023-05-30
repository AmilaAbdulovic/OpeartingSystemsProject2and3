# OpeartingSystems2023

Team members: Amila Abdulović, Anđela Jeftović


#Project 2
Understanding mmap and munmap System Calls:
The mmap and munmap system calls are used for memory mapping in Linux-based operating systems.
mmap: This system call is used to map files or devices into memory, as well as to create anonymous memory mappings. It allows you to request a range of memory from the operating system, which can be used for various purposes like reading/writing files, sharing memory between processes, or creating shared memory regions. The mmap system call takes several arguments, including the desired address range, size, protection flags, file descriptor, offset, and more.

munmap: This system call is used to unmap previously mapped memory. It deallocates the memory region previously mapped using mmap. The munmap system call takes the starting address of the memory region and the size as its arguments.

Writing a C Program to Measure Memory Usage:
You can use the following steps to write a simple C program that measures memory usage using ps or the proc file system:
Start a long-duration process (e.g., pause for user input or sleep).
Use the ps command with suitable options, such as ps -o vsz,rss to measure the virtual memory size (VSZ) and resident set size (RSS) of the process. The VSZ represents the total virtual memory allocated to the process, while RSS indicates the physical RAM pages allocated to the process.
Access the proc file system, typically located in /proc/<process_id>, to view various pieces of the memory image of the process.
Memory Mapping an Empty Page and Measuring Memory Usage:
To memory map an empty page from the OS, you can modify your program as follows:
Add the necessary headers: #include <sys/mman.h> and #include <fcntl.h>.
Use the mmap system call to request an anonymous page of memory using MAP_PRIVATE mode. The mmap call might look like this:
c
Copy code
void *addr = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
Pause the program or put it to sleep again.
Measure the virtual and physical memory consumed by the process using ps or the proc file system.
Observe the changes in memory usage compared to before the memory mapping.
Writing Data into the Memory Mapped Page and Measuring Memory Usage:
To write data into the memory mapped page and measure memory usage, you can modify your program further:
Write some data into the memory mapped page using regular pointer operations. For example:
c
Copy code
char *data = (char *)addr;
data[0] = 'A'; // Writing data to the memory mapped page
Pause the program or put it to sleep again.
Measure the virtual and physical memory consumed by the process using ps or the proc file system.
Observe the changes in memory usage compared to when the memory mapping contained an empty page.
Explanation:
When you memory map an empty page using mmap, you request a page-sized memory region from the OS. Initially, this memory region is not backed by any file on disk. Therefore, the memory consumption in terms of physical RAM (RSS) might not change significantly because the page is allocated lazily. However, the virtual memory size (VSZ) of the process will increase to accommodate the new mapped page.

When you write data into the memory mapped page, you are modifying the content of that page. As a result, the page becomes dirty, and the operating system assigns physical RAM to hold
