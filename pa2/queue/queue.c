#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// LINKED LIST IMPLEMENTATION OF QUEUE

// queue needed for level order traversal
typedef struct QueueNode QueueNode;
struct QueueNode {
    unsigned char data;
    struct QueueNode* next; // pointer to next node in linked list
};
struct Queue {
    struct QueueNode* front; // front (head) of the queue
    struct QueueNode* back; // back (tail) of the queue
};

typedef struct Queue Queue;

// Append the new node to the back of the queue
void enqueue ( Queue* queue, unsigned char data ) {
    QueueNode* queueNode = malloc(sizeof(QueueNode));
    queueNode -> data = data;
    queueNode -> next = NULL; // At back of the queue, there is no next node.

    if (queue->back==NULL) { // If the Queue is currently empty
        queue->front = queueNode;
        queue->back = queueNode;
    } else {
        queue->back->next = queueNode;
        queue->back = queueNode;
    }

    return;
}

// Remove a QueueNode from the front of the Queue
unsigned char dequeue ( Queue* queue ) {

    if (queue->front==NULL) { // If the Queue is currently empty
        return '\0';
    } else {

        // The QueueNode at front of the queue to be removed
        QueueNode* temp = queue->front;
        unsigned char data = temp->data;

        queue->front = temp->next;
        if (queue->back==temp) { // If the Queue will become empty
            queue->back = NULL;
        }

        free(temp);
        return data;
    }
}

int main(int argc, char* argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    Queue queue = { .front = NULL, .back = NULL };

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
