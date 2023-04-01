#include <stdio.h>
#include <stdlib.h>
#define NUM_PAGES 9
#define MEMORY_SIZE 3

typedef struct
{
    int value;
    struct Node *next;
} Node;

Node *createNode(int node_value)
{
    Node *node = malloc(sizeof(Node));
    node->value = node_value;
    node->next = NULL;
    return node;
}

typedef struct
{
    Node *begin;
    Node *end;
} Queue;

Queue *init_queue()
{
    Queue *queue = malloc(sizeof(Queue));
    queue->begin = NULL;
    queue->end = NULL;
    return queue;
}

void free_queue(Queue *queue)
{
    Node *actual = queue->begin;
    Node *previous = NULL;

    while (actual != NULL)
    {
        previous = actual;
        actual = actual->next;
        free(previous);
    }
    free(queue);
}

int is_empty_queue(Queue *queue)
{
    return queue->begin == NULL;
}

void enqueue(Queue *queue, int value)
{
    Node *new_node = createNode(value);
    if (is_empty_queue(queue))
    {
        queue->begin = new_node;
        queue->end = new_node;
    }
    else
    {

        (queue->end)->next = new_node; // prev last node.next = new node
        queue->end = new_node;
    }
}

int dequeue(Queue *queue)
{
    if (!is_empty_queue(queue))
    {
        Node *removed_node = queue->begin;
        int removed_value = removed_node->value;
        queue->begin = removed_node->next;

        if (queue->begin == NULL)
            queue->end == NULL;

        free(removed_node);
        return removed_value;
    }
    return -1;
}

int already_in_queue(Queue *queue, int value){
    Node * actual = queue->begin;
    while(actual->next != NULL)
    {
        if (actual->value == value){
            return 1;
        }
        actual = actual->next;
    }
    return 0;
}

int main()
{
    int requested_pages[NUM_PAGES];
    int memory_frames[MEMORY_SIZE];
    int memory_free_space = MEMORY_SIZE;
    Queue *queue = init_queue();

    printf("Requested Pages: [");
    for (int i = 0; i < NUM_PAGES; i++)
    {
        requested_pages[i] = rand() % 10;
        printf("%d ", requested_pages[i]);
    }
    printf("]\n");

    // para cada pagina requisitada adiciona na memoria se ela nao estiver cheia
    for (int page = 0; page < NUM_PAGES; page++)
    {       

        if (memory_free_space != 0)
        {
            enqueue(queue, requested_pages[page]);
            memory_frames[page] = requested_pages[page];
            printf("Pagina adicionada em memoria: %d\n", memory_frames[page]);
            memory_free_space--;
            printf("Memória:[ ");
            for (int i = 0; i < MEMORY_SIZE; i++)
            {                
                printf("%d ", memory_frames[i]);
            }
            printf("]\n\n");
        }
        else
        {
            /*  se memoria estiver cheia, desenfileira, retira a pagina
                com mesmo numero que o item desenfileirado da memoria,
                enfileira novo valor e depois coloca o numero no mesmo
                indice que o outro estava.
            */
            printf("Tentando adicionar página %d\n", requested_pages[page]);

            if(already_in_queue(queue, requested_pages[page]) == 1)
            {
                printf("Memória:[ ");
                for (int i = 0; i < MEMORY_SIZE; i++)
                {
                    printf("%d ", memory_frames[i]);
                }
                printf("]\n");
                printf("Página %d já esta em memória. Skipped\n\n", requested_pages[page]);
                continue;
            }

            int dequeued = dequeue(queue);
            int page_index;

            for (int i = 0; i < MEMORY_SIZE; i++)
            {
                if (memory_frames[i] == dequeued)
                {
                    page_index = i;
                }
            }
            printf("Page Fault.\nPagina removida da memória: %d\n", dequeued);
            
            enqueue(queue, requested_pages[page]);
            memory_frames[page_index] = requested_pages[page];
            
            printf("Pagina adicionada em memoria: %d\n", requested_pages[page]);
            printf("Memory:[ ");
            for (int i = 0; i < MEMORY_SIZE; i++)
            {
                printf("%d ", memory_frames[i]);
            }
            printf("]\n\n");
        }   
    }
    free_queue(queue);
    return 0;
}