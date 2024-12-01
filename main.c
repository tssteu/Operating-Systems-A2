#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>

#define NUM_ITERATIONS 1000000

// Hilfsfunktion für Zeitdifferenz in Nanosekunden
uint64_t time_diff_ns(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
}

int main() {
    struct timespec start, end;
    uint64_t min_latency = UINT64_MAX, max_latency = 0, total_latency = 0;
    uint64_t latencies[NUM_ITERATIONS];

    for (int i = 0; i < NUM_ITERATIONS; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start); // Startzeit
        getpid();                              // Einfacher System-Call
        clock_gettime(CLOCK_MONOTONIC, &end);   // Endzeit

        uint64_t latency = time_diff_ns(start, end);
        latencies[i] = latency;

        if (latency < min_latency) min_latency = latency;
        if (latency > max_latency) max_latency = latency;
        total_latency += latency;
    }

    double avg_latency = (double)total_latency / NUM_ITERATIONS;

    printf("Minimale Latenz: %lu ns\n", min_latency);
    printf("Maximale Latenz: %lu ns\n", max_latency);
    printf("Durchschnittliche Latenz: %.2f ns\n", avg_latency);

    return 0;
}
