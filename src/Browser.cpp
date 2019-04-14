#include "Browser.h"
#include <iostream>

void Browser::display()
{
   
   std::cout << "ID," << current->data->ID << std::endl;
	std::cout << "Status," << current->data->Status << std::endl;
	std::cout << "Title," << current->data->Title << std::endl;
	std::cout << "Keywords,";
	for(std::vector<std::string>::iterator it = current->data->KeyWords.begin(); it != current->data->KeyWords.end(); it++)
	{
		std::cout << *it << ",";
	}
	std::cout << std::endl;
	std::cout << "Summary," << current->data->Summary << std::endl;
	std::cout << "Genre,";
	for(std::vector<std::string>::iterator it = current->data->Genre.begin(); it != current->data->Genre.end(); it++)
	{
		std::cout << *it << ",";
	}
	std::cout << std::endl;
	std::cout << "Release_Date," << current->data->ReleaseDate << std::endl;
	std::cout << "Filming_Loc,";
	for(std::vector<std::string>::iterator it = current->data->Filming_Locations.begin(); it != current->data->Filming_Locations.end(); it++)
	{
		std::cout << *it << ",";
	}
	std::cout << std::endl;
	std::cout << "Runtime," << current->data->Runtime << std::endl;
	std::cout << "Language,";
	for(std::vector<std::string>::iterator it = current->data->Languages.begin(); it != current->data->Languages.end(); it++)
	{
		std::cout << *it << ",";
	}
	std::cout << std::endl;
	std::cout << "Weekly Ticket Sales," << current->data->WeeklyTicketSales << "\n" << std::endl;

}

void Browser::insert(Film* new_data)
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
      struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
      new_node->data  = new_data;
      new_node->next = current->next; 
      new_node->back = current; 

      current->next = new_node;
      new_node->next->back = new_node;
   }
}

void Browser::insert_tail(Film* new_data)
{
   struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
   new_node->data  = new_data;
   new_node->next = nullptr; 
   new_node->back = tail;   
   
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
      display();
   }
   else
   {
      std::cout << "This is the last item in the list\n" << std::endl;
      display();
   }
}

void Browser::previousNode()
{
   if (current->back != nullptr)
   {
      current = current->back;
      display();
   }
   else
   {
      std::cout << "This is the first item in the list\n" << std::endl;
      display();
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

   if(current->back != nullptr)
   {
      current = current->back;
   }
   else
   {
      current = current->next;
   }
}
