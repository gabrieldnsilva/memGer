#include "page_replacement.h"

void print_pages_state(int pages[], int num_frames, int step)
{
    printf("Step %d - Frames: [", step);
    for (int i = 0; i < num_frames; i++)
    {
        if (pages[i] == -1)
        {
            printf(" - ");
        }
        else
        {
            printf(" %d ", pages[i]);
        }
        if (i < num_frames - 1)
            printf("|");
    }
    printf("]\n");
}

void print_simulation_summary(SimulationResult result, const char *algorithm_name)
{
    printf("\n=== Resumo da Simulação %s ===\n", algorithm_name);
    printf("Total de page faults: %d\n", result.page_faults);
    printf("Estado final das páginas: [");
    for (int i = 0; i < result.num_frames; i++)
    {
        if (result.final_pages[i] == -1)
        {
            printf(" - ");
        }
        else
        {
            printf(" %d ", result.final_pages[i]);
        }
        if (i < result.num_frames - 1)
            printf("|");
    }
    printf("]\n\n");
}

void get_references(int references[], int *num_references)
{
    printf("Digite o número de referências de página (máx %d): ", MAX_REFERENCES);
    scanf("%d", num_references);

    // Validação adicional
    if (*num_references <= 0)
    {
        printf("Número inválido! Usando 1 referência.\n");
        *num_references = 1;
    }

    if (*num_references > MAX_REFERENCES)
    {
        *num_references = MAX_REFERENCES;
        printf("Limitado a %d referências.\n", MAX_REFERENCES);
    }

    printf("Digite as %d referências de página separadas por espaço: ", *num_references);
    for (int i = 0; i < *num_references; i++)
    {
        scanf("%d", &references[i]);
        // Validação para páginas negativas
        if (references[i] < 0)
        {
            printf("Página negativa detectada, convertendo para valor absoluto.\n");
            references[i] = abs(references[i]);
        }
    }
}

int get_num_frames(void)
{
    int num_frames;
    printf("Digite o número de frames de memória (máx %d): ", MAX_PAGES);
    scanf("%d", &num_frames);

    // Validação adicional
    if (num_frames <= 0)
    {
        printf("Número inválido! Usando 1 frame.\n");
        num_frames = 1;
    }

    if (num_frames > MAX_PAGES)
    {
        num_frames = MAX_PAGES;
        printf("Limitado a %d frames.\n", MAX_PAGES);
    }

    return num_frames;
}

void show_menu(void)
{
    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║     SIMULADOR DE SUBSTITUIÇÃO DE PÁGINA   ║\n");
    printf("╠════════════════════════════════════════════╣\n");
    printf("║ 1. Algoritmo FIFO                         ║\n");
    printf("║ 2. Algoritmo LRU                          ║\n");
    printf("║ 3. Comparar ambos os algoritmos           ║\n");
    printf("║ 4. Sair                                   ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    printf("Escolha uma opção: ");
}
