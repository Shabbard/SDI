#include "Browser.h"
#include <iostream>

void Browser::display()
{
   std::cout << current->data.Title << std::endl;  
}

void Browser::insert(Film new_data)
{
   if(current == NULL || current->next == NULL)
   {
      insert_tail(new_data);
   }
   else if(current->previous == NULL)
   {
      insert_head(new_data);
   }
   else
   {
      struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
      new_node->data  = new_data;
      new_node->next = current->next; 
      new_node->previous = current; 

      current->next = new_node;
      new_node->next->previous = new_node;
   }
}


void Browser::insert_tail(Film new_data)
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

void Browser::insert_head(Film new_data)
{
   struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
   new_node->data  = new_data;
   new_node->next = head; 
   new_node->previous = NULL;   
   
   if(head !=  NULL)
   {
      head->previous = new_node ;
   }
   if (head == NULL)
   {
       tail = new_node;
       current = head;
   }
   head = new_node; 
}

void Browser::setHead()
{
   current = head;
}

void Browser::setTail()
{
   current = tail;
}

void Browser::nextNode()
{
   if (current->next != NULL)
   {
      current = current->next;
      std::cout << "gone to next node, current node title: " << current->data.Title << std::endl;
   }
   else
   {
      std::cout << "This is the last item in the list" << std::endl;
   }
}

void Browser::previousNode()
{
   if (current->previous != NULL)
   {
      current = current->previous;
      std::cout << "gone to previous node, current node title: " << current->data.Title << std::endl;
   }
   else
   {
      std::cout << "This is the first item in the list" << std::endl;
   }
}

void Browser::delete_current()
{
   if (current->previous == NULL)
   {
      current->next->previous = NULL;
   }
   else if (current->next == NULL)
   {
      current->previous->next = NULL;
   }
   else
   {
      current->previous->next = current->next;
      current->next->previous = current->previous;
   }
  
   Node* temp = NULL;
   temp = current;
   
   current->data.~Film();
   delete current;

   if(temp->previous != NULL)
   {
      current = temp->previous;
   }
   else
   {
      current = temp->next;
   }

   //std::cout << "Successfully deleted node with title: " << temp->data.Title << std::endl;

   temp = NULL;  

}
