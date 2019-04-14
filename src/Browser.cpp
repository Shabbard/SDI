#include "Browser.h"
#include <iostream>

void Browser::display()
{
   
   std::cout << "ID" << "\t\t\t"<< current->data->ID << std::endl;
	std::cout << "Status" << "\t\t\t"<< current->data->Status << std::endl;
	std::cout << "Title" << "\t\t\t"<< current->data->Title << std::endl;
	std::cout << "Keywords"<< "\t\t";
	for(std::vector<std::string>::iterator it = current->data->KeyWords.begin(); it != current->data->KeyWords.end(); it++)
	{
		std::cout << *it << ",";
	}
	std::cout << std::endl;
	std::cout << "Summary" << "\t\t\t"<< current->data->Summary << std::endl;
	std::cout << "Genre"<< "\t\t\t";
	for(std::vector<std::string>::iterator it = current->data->Genre.begin(); it != current->data->Genre.end(); it++)
	{
		std::cout << *it << ",";
	}
	std::cout << std::endl;
	std::cout << "Release_Date" << "\t\t"<< current->data->ReleaseDate << std::endl;
	std::cout << "Filming_Loc"<< "\t\t";
	for(std::vector<std::string>::iterator it = current->data->Filming_Locations.begin(); it != current->data->Filming_Locations.end(); it++)
	{
		std::cout << *it << ",";
	}
	std::cout << std::endl;
	std::cout << "Runtime" << "\t\t\t"<< current->data->Runtime << std::endl;
	std::cout << "Language"<< "\t\t";
	for(std::vector<std::string>::iterator it = current->data->Languages.begin(); it != current->data->Languages.end(); it++)
	{
		std::cout << *it << ",";
	}
	std::cout << std::endl;
	std::cout << "Weekly Ticket Sales" << "\t" << current->data->WeeklyTicketSales << std::endl;
   	std::cout << "Crew Member ID's" << "\t";
	for(std::vector<Crew>::iterator it = current->data->CrewMembers.begin(); it != current->data->CrewMembers.end(); it++)
	{
      Crew temp = *it;
		std::cout << temp.ID << ",";
	}
	std::cout << std::endl;
   std::cout << std::endl;
}

void Browser::display_crew()
{

   std::cout << "___________________________________\n" << std::endl;
   std::cout << "            Crew Members             " << "\n"<< std::endl;
   std::cout << " ID             Name            Job" << std::endl;
   for(std::vector<Crew>::iterator it = current->data->CrewMembers.begin(); it != current->data->CrewMembers.end(); it++)
	{
      Crew temp;
      temp = *it;   
      std::cout << "- " <<temp.ID<< "\t"<< temp.Name << "\t\t" << temp.Job << std::endl;
	}
   std::cout << "\n";
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

   if(current->back != nullptr)
   {
      current = current->back;
   }
   else
   {
      current = current->next;
   }
}
