#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
void ULListStr::push_back(const std::string& val) 
{
  if (head_ == NULL) { //if linked list is empty, create new node
    Item* newItem = new Item;
    head_ = newItem; tail_ = newItem; //set head and tail to new node
    newItem -> val[0] = val; //add new item to the front
    newItem -> first = 0; newItem -> last = 1; //set first to 0th index and last to 1st index
    size_ += 1;
  }
  else if (tail_ -> last < ARRSIZE) { //if there's space to put in the back
    tail_ -> val[tail_ -> last] = val; 
    tail_ -> last += 1; //move last over to next
    size_ += 1;
  }
  else { //if no space, and new Item is needed to be created
    Item* newItem = new Item;
    newItem -> val[0] = val;
    newItem -> first = 0; newItem -> last = 1; 
    newItem -> prev = tail_; //set prev to previous last item
    tail_ -> next = newItem; //set previous last node next space to newItem
    tail_ = newItem;
    size_ += 1;
  }
}

void ULListStr::push_front(const std::string& val) 
{
  if (head_ == NULL) { //if linked list is empty, create new node
    Item* newItem = new Item;
    head_ = newItem; tail_ = newItem; //set head and tail to new node
    newItem->val[ARRSIZE - 1] = val; //add new item to the back
    head_->first = ARRSIZE - 1; //set first to last index
    tail_->last = ARRSIZE; //set last to one beyond last index
    size_ += 1;
  }
  else if (head_->first > 0) { //if there's still space
    head_->first -= 1; //move first over to previous
    head_->val[head_->first] = val;
    size_ += 1;
  }
  else { //if no space, and new Item is needed to be created
    Item* newItem = new Item;
    newItem->val[ARRSIZE - 1] = val; //put value in the back of the array
    newItem->first = ARRSIZE - 1; 
    newItem->last = ARRSIZE;
    newItem->next = head_; //set next to head's current first item
    head_->prev = newItem; //set previous last node next space to newItem
    head_ = newItem;
    size_ += 1;
  }
}

void ULListStr::pop_back()
{
  if (head_ == NULL) { //if linked list is empty, there's nothing to pop back
    return;
  }
  else if (tail_->last - tail_->first > 1) { //if the array is not empty, just delete last element
    tail_->last -= 1;
  }
  else { 
    if (head_ == tail_) { //if only one node, delete the node
      delete tail_;
      head_ = NULL; tail_ = NULL;
    }
    else { //delete the full node if it contains only one element
      Item* tmp = tail_;
      tail_ = tail_->prev;
      tail_->next = NULL;
      delete tmp;
    }
  }
  size_ -= 1;
}


void ULListStr::pop_front()
{
  if (head_ == NULL) { //if linked list is empty, there's nothing to pop front
    return;
  }
  else if (head_->last - head_->first > 1) { //if the array is not empty, just delete first element 
    head_->first += 1;
  }
  else { 
    if (head_ == tail_) { //if only one node, delete the node
      delete head_;
      head_ = NULL; tail_ = NULL;
    }
    else { //delete the full node if it contains only one element
      Item* tmp = head_;
      head_ = head_->next;
      head_->prev = NULL;
      delete tmp;
    }
  }
  size_ -= 1;
}



std::string const & ULListStr::back() const //works
{
  return tail_ -> val[tail_ -> last -1];
}

std::string const & ULListStr::front() const //works
{
  return head_ -> val[head_ -> first];
}

/** 
  * Returns a pointer to the item at index, loc,
  *  if loc is valid and NULL otherwise
  *   - MUST RUN in O(n) 
  */
std::string* ULListStr::getValAtLoc(size_t loc) const 
{
  Item* found = head_;

  while (found != NULL) { //go through each node to see how many elements there are total, to see if you can find item at loc
    size_t totalElements = found->last - found->first; //find total num of elements in the list

    if (loc < totalElements) { //if loc is within the current node
      return &(found->val[found->first + loc]); //return the value at the loc in node
    }

    loc -= totalElements; //subtract num elements in node from loc
    found = found->next; //move to next node
  }

  return NULL; //if not found, return NULL
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
