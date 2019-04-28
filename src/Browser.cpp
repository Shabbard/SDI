#include "Browser.h"
#include <iostream>
#include <fstream>

Browser::~Browser()
{
   setHead();
   Node* temp;
   while (current->next != nullptr)
	{
      temp = current;
      delete temp->data;
      temp->data  = nullptr;
      current = current->next;
      if (temp->back)
      {
         temp->back = nullptr;
      }
      if (temp->next)
      {
         temp->next = nullptr;
      }
      delete temp;
    }
   temp = current;
   delete temp->data;
   temp->data  = nullptr;
   current = current->next;
   if (temp->back)
   {
      temp->back = nullptr;
   }
   if (temp->next)
   {
      temp->next = nullptr;
   }
   delete current;
   delete tail;
   delete head;
   current = nullptr;
   head = nullptr;
   tail = nullptr;
}

void Browser::insert(FilmProject* new_data)
{
   if(current == nullptr || current->next == nullptr)
   {
      insert_tail(new_data);
   }
   else if(current->back == nullptr)
   {
      insert_head(new_data);
   }
   else
   {
      auto new_node = new Node();
      new_node->data  = new_data;
      new_node->next = current->next; 
      new_node->back = current; 

      current->next = new_node;
      new_node->next->back = new_node;
   }
}

void Browser::insert_tail(FilmProject* new_data)
{
   auto new_node = new Node();
   new_node->data = new_data;
   new_node->next = nullptr; 
   new_node->back = tail;   
   
   if(tail !=  nullptr)
   {
      tail->next = new_node;
   }
   if (tail == nullptr)
   {
       head = new_node;
       current = head;
   }
   tail = new_node; 
}

void Browser::insert_head(FilmProject* new_data)
{
   auto new_node = new Node();
   new_node->data  = new_data;
   new_node->next = head; 
   new_node->back = nullptr;   
   
   if(head !=  nullptr)
   {
      head->back = new_node ;
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
   }
   else
   {
      std::cout << "This is the last item in the list\n" << std::endl;
   }
}

void Browser::previousNode()
{
   if (current->back != nullptr)
   {
      current = current->back;
   }
   else
   {
      std::cout << "This is the first item in the list\n" << std::endl;
   }
}

void Browser::delete_current()
{
   if (current->back == nullptr)
   {
      current->next->back = nullptr;
      
   }
   else if (current->next == nullptr)
   {
      current->back->next = nullptr;
   }
   else
   {
      current->back->next = current->next;
      current->next->back = current->back;
   }
  
   delete current->data;

   if(current->back == nullptr)
   {
      current = current->next;
      head = current;
   }
   else if(current->next == nullptr)
   {
      current = current->back;
      tail = current;
   }
   else
   {
      current = current->next;
   }
   time_t now = time(0);
	char* dt = ctime(&now);

	std::ofstream logFile2;
	logFile2.open("../data/logFile.txt", std::ios_base::app);
	logFile2 << dt << " - Project Deleted! \r\n ";
   logFile2.close();
}

void Browser::insertionSort() 
{ 
   struct Node* sorted = NULL;

	while (current != NULL) {

		struct Node* next = current->next;
      current->back = current->next = NULL;

		sortedInsert(&sorted, current);
		current = next;
	}

	head = sorted;
    current = head;
} 

void Browser::sortedInsert(struct Node** head_ref, struct Node* newNode) 
{ 
  if (*head_ref == NULL)
		*head_ref = newNode;

	else if ((*head_ref)->data->ID >= newNode->data->ID) 
   {
		newNode->next = *head_ref;
		newNode->next->back = newNode;
      *head_ref = newNode;
	}
	else 
   {
		current = *head_ref;
      while (current->next != NULL && current->next->data->ID < newNode->data->ID)

		current = current->next;
		newNode->next = current->next;

		if (current->next != NULL)
			newNode->next->back = newNode;

		current->next = newNode;
		newNode->back = current;
	}
} 
