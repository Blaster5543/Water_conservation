#ifndef QUEUE_H
#define QUEUE_H
#include <string>

//Source from ZyBooks textbook

struct Node_queue {
    std::string data;
    Node_queue* next;
};

//Queue implementation as a linked list.
class Queue {
public:  
   //Queue constructor
   Queue();

   /**
      Adds an element to the tail of the queue.
      @param element the element to add
   */
   void push(std::string element);

   /**
      Yields the element from the head of the queue.
      @return the head element
   */
   std::string front() const;

   //Gets the next element's data
   Node_queue* head() const;

   //Gets the last element's data
   Node_queue* tail() const;

   /**
      Removes the element from the head of the queue.
   */
   void remove();

   /**
      Yields the number of elements in this queue.
      @return the size
   */
   int size() const;
 
private:  
   Node_queue* head_pointer;
   Node_queue* tail_pointer;
   int len;
};

#endif
