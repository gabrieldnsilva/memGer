#include "page_replacement.h"

int main(void)
{
    int choice;
    int references[MAX_REFERENCES];
    int num_references;
    int num_frames;
    SimulationResult result_fifo, result_lru;

    printf("Bem-vindo ao Simulador de Algoritmos de Substituição de Página!\n");

    do
    {
        show_menu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\n--- Simulação FIFO ---\n");
            get_references(references, &num_references);
            num_frames = get_num_frames();

            result_fifo = simulate_fifo(references, num_references, num_frames);
            print_simulation_summary(result_fifo, "FIFO");
            break;

        case 2:
            printf("\n--- Simulação LRU ---\n");
            get_references(references, &num_references);
            num_frames = get_num_frames();

            result_lru = simulate_lru(references, num_references, num_frames);
            print_simulation_summary(result_lru, "LRU");
            break;

        case 3:
            printf("\n--- Comparação FIFO vs LRU ---\n");
            get_references(references, &num_references);
            num_frames = get_num_frames();

            result_fifo = simulate_fifo(references, num_references, num_frames);
            print_simulation_summary(result_fifo, "FIFO");

            result_lru = simulate_lru(references, num_references, num_frames);
            print_simulation_summary(result_lru, "LRU");

            printf("=== COMPARAÇÃO ===\n");
            printf("FIFO: %d page faults\n", result_fifo.page_faults);
            printf("LRU:  %d page faults\n", result_lru.page_faults);

            if (result_fifo.page_faults < result_lru.page_faults)
            {
                printf("FIFO teve melhor desempenho!\n");
            }
            else if (result_lru.page_faults < result_fifo.page_faults)
            {
                printf("LRU teve melhor desempenho!\n");
            }
            else
            {
                printf("Ambos tiveram o mesmo desempenho!\n");
            }
            break;

        case 4:
            printf("\n--- Casos de Teste Acadêmicos ---\n");
            run_test_cases();
            break;

        case 5:
            printf("Obrigado por usar o simulador!\n");
            break;

        default:
            printf("Opção inválida! Tente novamente.\n");
            break;
        }

        if (choice != 5)
        {
            printf("\nPressione Enter para continuar...");
            getchar(); // Limpa buffer
            getchar(); // Espera Enter
        }

    } while (choice != 5);

    return 0;
}