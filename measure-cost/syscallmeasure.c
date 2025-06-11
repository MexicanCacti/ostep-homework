#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main() {
    struct timespec start, end;
    int fd = open("test.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    char buffer[10];
    ssize_t bytes_read;
    double total = 0;
    int amount = 100;
    for (int i = 0; i < amount; ++i) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        bytes_read = read(fd, buffer, 0);  // 0-byte read
        clock_gettime(CLOCK_MONOTONIC, &end);

        if (bytes_read < 0) {
            perror("read");
            break;
        }

        double elapsed = (end.tv_sec - start.tv_sec) +
                         (end.tv_nsec - start.tv_nsec) / 1e9;
        total += elapsed;
        printf("Bytes read: %zd, Elapsed time: %.9f seconds\n", bytes_read, elapsed);
        usleep(100000);  // sleep 100ms
    }

    printf("Average time taken: %.9f microseconds\n", (total/ amount) * 1e6);


    close(fd);
    return 0;
}
