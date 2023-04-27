#include "queue.h"
#include <iostream>

//Source from ZyBooks textbook

Queue::Queue() {  
   head_pointer = nullptr;
   tail_pointer = nullptr;
   len = 0;
};

void Queue::push(std::string element) {  
   Node_queue* new_node = new Node_queue;
   new_node->data = element;
   new_node->next = nullptr;
   if (tail_pointer == nullptr)
   {
      head_pointer = new_node;
   }
   else
   {
      tail_pointer->next = new_node;
   }
   tail_pointer = new_node;
   len++;
}

std::string Queue::front() const {
   return head_pointer->data;
}

Node_queue* Queue::head() const {
   return head_pointer;
}

Node_queue* Queue::tail() const {
   return tail_pointer;
}

void Queue::remove() {
   Node_queue* to_delete = head_pointer;
   head_pointer = head_pointer->next;
   delete to_delete;
   len--;
   if (head_pointer == nullptr) {
      tail_pointer = nullptr;
   }
}

int Queue::size() const {
   return len;
}

