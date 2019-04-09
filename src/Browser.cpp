#include "Browser.h"
#include <iostream>

void Browser::display()
{
   class Browser* ptr;
   ptr = head;
   while (ptr != NULL) { 
      std::cout << ptr->data.Title <<" "; 
      ptr = ptr->next; 
   } 
}

void Browser::insert(Film new_data)
{
   struct Browser* new_node = (struct Browser*) malloc(sizeof(class Browser));
   new_node->data  = new_data; 
   new_node->previous = NULL; 
   new_node->next = head;     
   if(head !=  NULL) 
      head->previous = new_node ;     
   head = new_node; 
}