#ifndef BROWSER_H
#define BROWSER_H
#include "FilmProject.h"
#pragma once

struct Node
{
    FilmProject* data;
    Node* next;
    Node* back;
};

class Browser
{
    private:
    Node* head = nullptr;
    Node* tail = nullptr;

    public:
    Node* current = nullptr;

    void insert(FilmProject* new_data);
    void display();
    void display_crew();
    void nextNode();
    void previousNode();
    void setHead();
    void setTail();
    void insert_tail(FilmProject* new_data);
    void insert_head(FilmProject* new_data);
    void delete_current();
};

#endif
