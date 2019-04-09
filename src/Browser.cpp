#include "Browser.h"
#include <iostream>

void Browser::display()
{
   std::cout << current->data << std::endl;  
}

void Browser::insert(int new_data)
{
   struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
   new_node->data  = new_data; 
   new_node->next = NULL; 
   new_node->previous = tail;   

   
   if(tail !=  NULL)
   {
      tail->next = new_node ;
   }
   if (tail == NULL)
   {
       head = new_node;
       current = head;
   }
   tail = new_node; 
}

void Browser::nextNode()
{
   if (current->next != NULL)
   {
      current = current->next;
   }
   else
   {
      std::cout << "This is the last item in the list";
   }
}

void Browser::previousNode()
{
   if (current->previous != NULL)
   {
      current = current->previous;
   }
   else
   {
      std::cout << "This is the first item in the list";
   }
}
