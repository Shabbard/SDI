#include "Film.h"

struct Node
{
    int data = 0;
    Node* next;
    Node* previous;
};

class Browser
{
    public:
    Node* head = NULL;
    Node* tail = NULL;
    Node* current = NULL;

    void insert(int new_data);
    void display();
    void nextNode();
    void previousNode();

};


