#include "Browser.h"
#include <iostream>

void Browser::display()
{
   std::cout << current->data << std::endl;  
}

void Browser::insert(int new_data)
{
   struct Browser* new_node = (struct Browser*) malloc(sizeof(class Browser));
   new_node->data  = new_data; 

   new_node->next = NULL; 
   new_node->previous = tail;   
   
   if(tail !=  NULL)
   {
      tail->next = new_node ; 
   } 
   tail = new_node; 

}