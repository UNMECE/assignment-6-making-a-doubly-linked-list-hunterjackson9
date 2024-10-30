#include <coordinate.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>

void add_coordinate(Coordinate* list_end, float x, float y) {
    static int id = 0;
    Coordinate* new_coord = (Coordinate*)malloc(sizeof(Coordinate));
    new_coord->x = x;
    new_coord->y = y;
    new_coord->coord_id = id++;
    new_coord->next = NULL;
    new_coord->previous = list_end;

    if (list_end) {
        list_end->next = new_coord;
    }
}

void forward_display(Coordinate* list_beginning) {
    Coordinate* temp = list_beginning;
    while (temp) {
        printf("Coordinate ID: %d, x: %.2f, y: %.2f\n", temp->coord_id, temp->x, temp->y);
        temp = temp->next;
    }
}

void backward_display(Coordinate* list_end) {
    Coordinate* temp = list_end;
    while (temp) {
        printf("Coordinate ID: %d, x: %.2f, y: %.2f\n", temp->coord_id, temp->x, temp->y);
        temp = temp->previous;
    }
}

void delete_coordinate(Coordinate* list_beginning, int coord_id_to_delete) {
    Coordinate* temp = list_beginning;
    while (temp && temp->coord_id != coord_id_to_delete) {
        temp = temp->next;
    }
    if (temp) {
        if (temp->previous) {
            temp->previous->next = temp->next;
        }
        if (temp->next) {
            temp->next->previous = temp->previous;
        }
        free(temp);
    }
}

int list_length(Coordinate* list_beginning) {
    int length = 0;
    Coordinate* temp = list_beginning;
    while (temp) {
        length++;
        temp = temp->next;
    }
    return length;
}

void closest_to(Coordinate* list_beginning, float x, float y) {
    Coordinate* temp = list_beginning;
    Coordinate* closest = NULL;
    float min_distance = FLT_MAX;

    while (temp) {
        float distance = sqrt(pow(temp->x - x, 2) + pow(temp->y - y, 2));
        if (distance < min_distance) {
            min_distance = distance;
            closest = temp;
        }
        temp = temp->next;
    }

    if (closest) {
        printf("Closest coordinate to (%.2f, %.2f) is ID %d with distance %.2f\n", x, y, closest->coord_id, min_distance);
    }
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_coordinates>\n", argv[0]);
        return 1;
    }

    int num_coords = atoi(argv[1]);
    Coordinate* list_beginning = NULL;
    Coordinate* list_end = NULL;

    for (int i = 0; i < num_coords; i++) {
        float x = (float)rand() / RAND_MAX * 100;
        float y = (float)rand() / RAND_MAX * 100;
        add_coordinate(list_end, x, y);
        if (i == 0) {
            list_beginning = list_end; // Set beginning if it's the first element
        }
    }

    printf("Forward Display:\n");
    forward_display(list_beginning);

    printf("Backward Display:\n");
    backward_display(list_end);

    delete_coordinate(list_beginning, 0); // Example deletion
    printf("After Deletion:\n");
    forward_display(list_beginning);

    closest_to(list_beginning, 50.0, 50.0); // Example closest_to

    return 0;
}
