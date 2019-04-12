#include "Browser.h"
#include <iostream>

void Browser::display()
{
   //std::cout << current->data.Title << std::endl;  
   std::cout << current->data->Title << std::endl;  
}

void Browser::insert(Film* new_data)
{
   if(current == nullptr || current->next == nullptr)
   {
      insert_tail(new_data);
   }
   else if(current->previous == nullptr)
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

void Browser::insert_tail(Film* new_data)
{
   struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
   new_node->data  = new_data;
   new_node->next = nullptr; 
   new_node->previous = tail;   
   
   if(tail !=  nullptr)
   {
      tail->next = new_node ;
   }
   if (tail == nullptr)
   {
       head = new_node;
       current = head;
   }
   tail = new_node; 
}

void Browser::insert_head(Film* new_data)
{
   struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
   new_node->data  = new_data;
   new_node->next = head; 
   new_node->previous = nullptr;   
   
   if(head !=  nullptr)
   {
      head->previous = new_node ;
   }
   if (head == nullptr)
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
   if (current->next != nullptr)
   {
      current = current->next;
      std::cout << "gone to next node, current node title: " << current->data->Title << std::endl;
   }
   else
   {
      std::cout << "This is the last item in the list" << std::endl;
   }
}

void Browser::previousNode()
{
   if (current->previous != nullptr)
   {
      current = current->previous;
      std::cout << "gone to previous node, current node title: " << current->data->Title << std::endl;
   }
   else
   {
      std::cout << "This is the first item in the list" << std::endl;
   }
}

void Browser::delete_current()
{
   if (current->previous == nullptr)
   {
      current->next->previous = nullptr;
   }
   else if (current->next == nullptr)
   {
      current->previous->next = nullptr;
   }
   else
   {
      current->previous->next = current->next;
      current->next->previous = current->previous;
   }
  
   delete current->data;

   if(current->previous != nullptr)
   {
      current = current->previous;
   }
   else
   {
      current = current->next;
   }
}
