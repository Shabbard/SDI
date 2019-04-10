#include "Browser.h"
#include <iostream>

void Browser::display()
{
   std::cout << current->data << std::endl;  
}

void Browser::insert(int new_data) // all of these insert functions could probably do with refactoring, will do later
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


void Browser::insert_tail(int new_data)
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

void Browser::insert_head(int new_data)
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

void Browser::nextNode()
{
   if (current->next != NULL)
   {
      current = current->next;
      std::cout << "gone to next node" << std::endl;
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
      std::cout << "gone to previous node, current node data: " + current->data << std::endl;
   }
   else
   {
      std::cout << "This is the first item in the list";
   }
}

void Browser::delete_current()
{
   current->previous->next = current->next;
   current->next->previous = current->previous;

   Node* temp = current;

   delete current;

   if(temp->previous != NULL)
   {
      current = temp->previous;
   }
   else
   {
      current = temp->next;
   }

   std::cout << "Successfully deleted node with data: " + temp->data << std::endl;

   temp = NULL;  

}
