#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
    unsigned char data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* back;
} Queue;

// Append the new node to the back of the queue
// I'll explain why the ** format is archaic and why we can go with return here
// show what happens on the stack and on the heap
Queue enqueue (Queue queue, unsigned char data)
{
    Node* node = malloc(sizeof(Node));
    node -> data = data;
    node -> next = NULL;

    if (queue.back==NULL) {
        queue.back = node;
        queue.front = node;
        return queue;
    } else {
        queue.back->next = node;
        queue.back = node;
    }

    return queue;
}

// Remove node from the front of the queue
unsigned char dequeue ( Queue* queue ){
    if(queue->front != NULL){
        char data = queue->front->data;
        Node* temp = queue->front;
        queue->front = queue->front -> next;
        if (queue->back==temp) {
            queue->back = NULL;
        }
        free(temp);
        return data;
    }
    else {
        return '\0';
    }
}

int main(int argc, char* argv[])
{

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    Queue* queue = malloc(sizeof(Queue));
    queue->front = queue->back = NULL;

    char buff[8];
    while ( fscanf(fp, "%s", buff) != -1 ) {

        if ( strcmp(buff,"ENQUEUE")==0 ) {
            fscanf(fp, "%s", buff);
            *queue = enqueue(*queue, atoi(buff));
        } else if ( strcmp(buff,"DEQUEUE")==0 ) {
            dequeue(queue);
        } else {
            printf("UNEXPECTED INPUT\n");
            return EXIT_FAILURE;
        }
    }


    while (queue->front) {
      unsigned char data = dequeue(queue);
      printf( "%d ", data );
    }

    free (queue);
    fclose(fp);
    return EXIT_SUCCESS;
}
