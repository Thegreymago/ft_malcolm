#include "../includes/ft_malcolm.h"

#define MAX_OBJECTS 10

typedef struct {
    int data;
    int marked;
} Object;

typedef struct {
    Object* objects[MAX_OBJECTS];
    int numObjects;
} GarbageCollector;

GarbageCollector gc;

void initGC() {
    gc.numObjects = 0;
}

Object* createObject(int data) {
    if (gc.numObjects >= MAX_OBJECTS) {
        printf("Error: Maximum number of objects reached.\n");
        return NULL;
    }
    
    Object* object = malloc(sizeof(Object));
    object->data = data;
    object->marked = 0;
    
    gc.objects[gc.numObjects++] = object;
    
    return object;
}

void mark(Object* object) {
    object->marked = 1;
}

void sweep() {
    for (int i = 0; i < gc.numObjects; i++) {
        if (!gc.objects[i]->marked) {
            free(gc.objects[i]);
            gc.objects[i] = NULL;
        }
    }
}

void collectGarbage() {
    for (int i = 0; i < gc.numObjects; i++) {
        if (gc.objects[i]->marked) {
            mark(gc.objects[i]);
        }
    }
    
    sweep();
}