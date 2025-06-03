#include "page_replacement.h"

SimulationResult simulate_lru(int references[], int num_references, int num_frames)
{
    SimulationResult result = {0};
    int pages[MAX_PAGES];
    int last_used[MAX_PAGES];

    for (int i = 0; i < num_frames; i++)
    {
        pages[i] = -1;
        last_used[i] = -1;
    }

    printf("\n=== Simulação LRU ===\n");
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
        int page_index = -1;

        for (int j = 0; j < num_frames; j++)
        {
            if (pages[j] == page)
            {
                page_found = true;
                page_index = j;
                break;
            }
        }

        if (page_found)
        {
            last_used[page_index] = i;
            printf("Passo %d: Página %d (HIT)  -> ", i + 1, page);
        }
        else
        {
            int lru_index = 0;

            for (int j = 1; j < num_frames; j++)
            {
                if (last_used[j] < last_used[lru_index])
                {
                    lru_index = j;
                }
            }

            pages[lru_index] = page;
            last_used[lru_index] = i;
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