#ifndef PAGE_REPLACEMENT_H
#define PAGE_REPLACEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PAGES 10
#define MAX_REFERENCES 100

typedef struct
{
    int page_faults;
    int num_frames;
    int final_pages[MAX_PAGES];
} SimulationResult;

// Protótipos das funções
SimulationResult simulate_fifo(int references[], int num_references, int num_frames);
SimulationResult simulate_lru(int references[], int num_references, int num_frames);

// Funções Auxiliares

void print_pages_state(int pages[], int num_frames, int step);
void print_simulation_summary(SimulationResult result, const char *algorithm_name);
void get_references(int references[], int *num_references);
int get_num_frames(void);
void show_menu(void);

// Funções para casos de teste
void run_test_cases(void);
void test_classic_sequence(void);
void test_belady_anomaly(void);
void test_locality_reference(void);
void run_comparison_test(int references[], int num_references, int num_frames, const char *test_name);

#endif // PAGE_REPLACEMENT_H