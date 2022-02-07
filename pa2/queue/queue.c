#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node Node;
struct Node {
    unsigned char data;
    Node* next;
};

typedef struct Queue {
    Node* front;
    Node* back;
} Queue;

// Append the new node to the back of the queue
void enqueue ( Queue* queue, unsigned char data ) {
    Node* node = malloc(sizeof(Node));
    node -> data = data;
    node -> next = NULL;

    if (queue->back==NULL) {
        queue->back = node;
        queue->front = node;
    } else {
        queue->back->next = node;
        queue->back = node;
    }

    return;
}

// Remove node from the front of the queue
unsigned char dequeue ( Queue* queue ) {
    if (queue->front != NULL) {
        Node* temp = queue->front;
        char data = temp->data;
        queue->front = temp->next;
        if (queue->back==temp) { // if this was the last node in queue
            queue->back = NULL;
        }
        free(temp);
        return data;
    } else {
        return '\0';
    }
}

int main(int argc, char* argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    Queue queue;
    queue.front = queue.back = NULL;

    char buff[8];
    while ( fscanf(fp, "%s", buff) != -1 ) {

        if ( strcmp(buff,"ENQUEUE")==0 ) {
            fscanf(fp, "%s", buff);
            enqueue(&queue, atoi(buff));
        } else if ( strcmp(buff,"DEQUEUE")==0 ) {
            dequeue(&queue); // discard the return
        } else {
            printf("UNEXPECTED INPUT\n");
            return EXIT_FAILURE;
        }
    }


    while (queue.front) {
        unsigned char data = dequeue(&queue);
        printf( "%d\n", data );
    }

    fclose(fp);
    return EXIT_SUCCESS;
}
