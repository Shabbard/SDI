#include "Browser.h"
#include <iostream>

void Browser::display()
{
   class Browser* ptr;
   ptr = head;
   while (ptr != NULL) { 
      std::cout << ptr->Data <<" "; 
      ptr = ptr->next; 
   } 
}

void Browser::insert(Film new_data)
{
   struct Browser* new_node = (struct Browser*) malloc(sizeof(class Browser)); 
   new_node-> Data = new_data; 
   new_node-> next = head; 
   head = new_node; 
}