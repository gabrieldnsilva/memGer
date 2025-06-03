#include "page_replacement.h"

SimulationResult simulate_fifo(int references[], int num_references, int num_frames)
{
    SimulationResult result = {0};
    int pages[MAX_PAGES];
    int next_frame = 0;

    for (int i = 0; i < num_frames; i++)
    {
        pages[i] = -1;
    }

    printf("\n=== Simulação FIFO ===\n");
    printf("Frames: %d\n", num_frames);
    printf("Referências: ");

    for (int i = 0; i < num_references; i++)
    {
        printf("%d ", references[i]);
    }
    printf("\n\n");

    for (int i = 0; i < num_references; i++)
    {
        int page = references[i];
        bool page_found = false;

        for (int j = 0; j < num_frames; j++)
        {
            if (pages[j] == page)
            {
                page_found = true;
                break;
            }
        }

        if (page_found)
        {
            printf("Passo %d: Página %d (HIT) -> ", i + 1, page);
        }
        else
        {
            pages[next_frame] = page;
            next_frame = (next_frame + 1) % num_frames;
            result.page_faults++;

            printf("Passo %d: Página %d (FAULT) -> ", i + 1, page);
        }

        print_pages_state(pages, num_frames, i + 1);
    }

    result.num_frames = num_frames;
    for (int i = 0; i < num_frames; i++)
    {
        result.final_pages[i] = pages[i];
    }

    return result;
}