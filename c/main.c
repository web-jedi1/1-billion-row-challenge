#include <stdlib.h>
#include <stdio.h>
//{Abha=-23.0/18.0/59.2, Abidjan=-16.2/26.0/67.3, Abéché=-10.0/29.4/69.0, Accra=-10.1/26.4/66.4, Addis Ababa=-23.7/16.0/67.0, Adelaide=-27.8/17.3/58.5, ...} <min>/<mean>/<max>

//  Manta;-13.0
//  El Fula;2.2
//  Shannon;-10.9
//  Kamen’-Rybolov;-50.7
//  Rishra;99.1
//  Bandarbeyla;-71.0
//  Inowrocław;76.9
//  Kaita;69.6
//  Cartavio;-60.0
//  Ettaiyāpuram;-51.2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OKAY(MSG, ...) printf("[+] -> " MSG "\n", ##__VA_ARGS__)
#define INFO(MSG, ...) printf("[i] -> " MSG "\n", ##__VA_ARGS__)
#define WARN(MSG, ...) printf("[-] -> " MSG "\n", ##__VA_ARGS__)

const char *file = "/home/manfred/dev/1-billion-row-challenge/data/measurements.txt";

typedef struct data_node {
    float temp;
    char city[50];
    struct data_node *next;
} data_node;

// Function to create a new data node
data_node *new_node(const char* city, float temp) {
    data_node *node = (data_node *)malloc(sizeof(data_node));
    if (node == NULL) {
        WARN("Memory allocation failed.");
        return NULL;
    }
    strncpy(node->city, city, sizeof(node->city) - 1);
    node->city[sizeof(node->city) - 1] = '\0';
    node->temp = temp;
    node->next = NULL;
    return node;
}

// Function to insert a new node at the beginning of the list
void add_node(data_node **head, const char* city, float temp) {
    data_node *new = new_node(city, temp);
    if (new != NULL) {
        new->next = *head;
        *head = new;
    }
}

// Function to print the linked list
void print_data(data_node *head) {
    data_node *current = head;
    while (current != NULL) {
        printf("City: %s, Temp: %.2f\n", current->city, current->temp);
        current = current->next;
    }
}

int main() {
    int c = 0;
    data_node *head = NULL;
    INFO("Reading from file: %s", file);

    FILE *fptr;
    fptr = fopen(file, "r");

    if (fptr == NULL) {
        WARN("Error opening file %s", file);
        return 1;
    }

    INFO("Opened file at %p", (void*)fptr);
    
    char city[50]; // Temporary variable to store city name
    float temp;    // Temporary variable to store temperature

    // Loop to read data from file and add nodes to the linked list
    while (fscanf(fptr, "%49[^;];%f", city, &temp) == 2 && c <= 10) {
        add_node(&head, city, temp);
        c++;
    }

    fclose(fptr);

    // Print the linked list
    print_data(head);

    // Free memory allocated for the linked list
    data_node *current = head;
    while (current != NULL) {
        data_node *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}

