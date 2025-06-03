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
    printf("║ 4. Executar casos de teste acadêmicos     ║\n");
    printf("║ 5. Sair                                   ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    printf("Escolha uma opção: ");
}

void run_test_cases(void)
{
    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║        CASOS DE TESTE ACADÊMICOS          ║\n");
    printf("╚════════════════════════════════════════════╝\n\n");

    printf("Executando os casos de teste mencionados no README...\n\n");

    test_classic_sequence();
    printf("\n" + "─" * 50 + "\n");

    test_belady_anomaly();
    printf("\n" + "─" * 50 + "\n");

    test_locality_reference();

    printf("\n✅ Todos os casos de teste foram executados!\n");
}

void test_classic_sequence(void)
{
    printf("🧪 TESTE 1: Sequência Clássica\n");
    printf("Demonstra comportamento típico dos algoritmos\n\n");

    int references[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int num_references = 20;
    int num_frames = 3;

    run_comparison_test(references, num_references, num_frames, "Sequência Clássica");
}

void test_belady_anomaly(void)
{
    printf("🧪 TESTE 2: Anomalia de Belady (FIFO)\n");
    printf("Demonstra que FIFO pode ter MAIS faults com MAIS frames!\n\n");

    int references[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int num_references = 12;

    printf("🔍 Testando com 3 frames:\n");
    run_comparison_test(references, num_references, 3, "Belady com 3 frames");

    printf("\n🔍 Testando com 4 frames:\n");
    run_comparison_test(references, num_references, 4, "Belady com 4 frames");

    printf("\n💡 OBSERVAÇÃO: Note que FIFO pode ter mais faults com 4 frames do que com 3!\n");
    printf("   Isso é a famosa 'Anomalia de Belady' - um comportamento contraintuitivo.\n");
}

void test_locality_reference(void)
{
    printf("🧪 TESTE 3: Localidade de Referência\n");
    printf("Demonstra como LRU se beneficia da localidade temporal\n\n");

    int references[] = {1, 1, 1, 2, 2, 2, 3, 3, 3, 1, 1, 1};
    int num_references = 12;
    int num_frames = 2;

    run_comparison_test(references, num_references, num_frames, "Localidade de Referência");

    printf("\n💡 OBSERVAÇÃO: LRU geralmente se sai melhor quando há localidade temporal,\n");
    printf("   pois páginas recém-usadas têm maior probabilidade de serem usadas novamente.\n");
}

void run_comparison_test(int references[], int num_references, int num_frames, const char *test_name)
{
    printf("📊 Executando: %s\n", test_name);
    printf("Referências: ");
    for (int i = 0; i < num_references; i++)
    {
        printf("%d ", references[i]);
    }
    printf("\nFrames: %d\n", num_frames);

    SimulationResult result_fifo = simulate_fifo(references, num_references, num_frames);
    SimulationResult result_lru = simulate_lru(references, num_references, num_frames);

    printf("\n📈 RESULTADO DO TESTE: %s\n", test_name);
    printf("┌─────────────┬─────────────┐\n");
    printf("│ Algoritmo   │ Page Faults │\n");
    printf("├─────────────┼─────────────┤\n");
    printf("│ FIFO        │     %2d      │\n", result_fifo.page_faults);
    printf("│ LRU         │     %2d      │\n", result_lru.page_faults);
    printf("└─────────────┴─────────────┘\n");

    if (result_fifo.page_faults < result_lru.page_faults)
    {
        printf("🏆 FIFO foi mais eficiente neste caso!\n");
    }
    else if (result_lru.page_faults < result_fifo.page_faults)
    {
        printf("🏆 LRU foi mais eficiente neste caso!\n");
    }
    printf("\n");
}
printf("🔄 Ambos os algoritmos tiveram o mesmo número de page faults.\n");
}
else
{
    printf("🤝 Ambos algoritmos tiveram o mesmo desempenho!\n");
}
}
