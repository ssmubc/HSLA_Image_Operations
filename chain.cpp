#include "chain.h"
#include <cmath>
#include <iostream>


// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() {
  /* your code here */
  // Calls upon clear so we do not have a memory leak
  clear();
}

/**
 * Inserts a new node after the node pointed to by p in the
 * chain (so p->next is the new node) and returns a pointer to
 * the newly created node.
 * If p is NULL, inserts a new head node to the chain.
 * This function **SHOULD** create a new Node and increase length_.
 *
 * @param p = The new node should be pointed to by p->next.
 *            If p is NULL, the new node becomes the head of the chain.
 * @param ndata = The data to be inserted.
 */
Chain::Node * Chain::insertAfter(Node * p, const Block &ndata) {
  /* your code here */
  //return nullptr;
  Node* newNode = new Node(ndata);
  length_++;

  if (p == NULL) {
    newNode->next = head_;
    // checks condition of whether the head pointer was null or not and if there was then maintains doubly linked lis
    if (head_ != NULL) {
      head_->prev = newNode;
    }
    head_ = newNode;
    return newNode;
  } else {
    newNode->next = p->next;
    newNode->prev = p;

    if (p->next != NULL) {
      p->next->prev = newNode;
    }
    p->next = newNode;
    return newNode;
  }
}

/**
 * Swaps the position in the chain of the two nodes pointed to
 * by p and q.
 * If p or q is NULL or p==q, do nothing.
 * Change the chain's head pointer if necessary.
 */
void Chain::swap(Node *p, Node *q) {
  /* your code here */

  if (p == NULL || q == NULL || p == q) {
    return;
  }

  // case when p and q are adjacent
 

  if (p->next == q) {
    Node* temp2 = q->next;
    q->next = p;
    Node* temp = p->prev;
    p->prev = q;
    q->prev = temp;
    p->next = temp2;
  } else if (q->next == p) {
    Node* temp = p->next;
    Node* temp2 = q->prev;
    p->next = q;
    q->prev = p;
    q->next = temp;
    p->prev = temp2;
  }

  else {
    Node* pPrev = p->prev;
    Node* pNext = p->next;
    p->next = q->next;
    p->prev = q->prev;
    q->prev = pPrev;
    q->next = pNext;
  }
  // changing the previous pointers of the next nodes for p and q
  if (p->next != NULL) {
    p->next->prev = p;
  }
  if (q->next != NULL) {
    q->next->prev = q;
  }

  // changing the next pointers of the previous nodes for p and q
  if (p->prev != NULL) {
    p->prev->next = p;
  } else {
    head_ = p;
  }

  if (q->prev != NULL) {
    q->prev->next = q;
  } else {
    head_ = q;
  }

}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear() {
  /* your code here */
  Node* curr = head_;
  while (curr) {
    Node* next = curr->next;
    delete curr;
    curr = next;
  }
  head_ = NULL;
  length_ = 0;
}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other) {
  /* your code here */
  // first free any dynamically allocated memory with the current object
  clear();
  Node* curr = other.head_;
  Node* prev = NULL;

  // iterates until curr == NULL
  while (curr != NULL) {
    Node* newNode = new Node(curr->data);
    // checks if the current node is in the chain of other and if it is not then it sets head to newNode.
    if (!head_) {
      head_ = newNode;
    }
    // the bottom if condition only runs after the first iteration. 
    if (prev != NULL) {
      prev->next = newNode;
      newNode->prev = prev;
    }
    prev = newNode;
    curr = curr->next;
  }
  length_ = other.length_;
}

/* Modifies the current chain:
 * 1) Find the node with the first (leftmost) block in the unscrambled
 *    image and move it to the head of the chain.
 *	This block is the one whose closest match (to the left) is the
 *	largest.  That is, the distance (using distanceTo) to this block
 *	is big for all other blocks.
 *	For each block B, find the distanceTo B from every other block
 *	and take the minimum of these distances as B's "value".
 *	Choose the block B with the maximum value over all blocks and
 *	swap its node to the head of the chain.
 *
 * 2) Starting with the (just found) first block B, find the node with
 *    the block that is the closest match to follow B (to the right)
 *    among the remaining blocks, move (swap) it to follow B's node,
 *    then repeat to unscramble the chain/image.
 */


double Chain::getValue(const Node* p) {
  double currValue = head_->data.distanceTo(p->data);

  Node* nextNode = head_->next;
  while (nextNode != NULL) {
    if (nextNode == p) {
      nextNode = nextNode->next;
      continue;
    }
    double dist = nextNode->data.distanceTo(p->data);
    if (dist < currValue) {
      currValue = dist;
    }
    nextNode = nextNode->next;
  }
  return currValue;

}

Chain::Node* Chain::findLeftMostBlock() {
  Node * rsf = head_;
  if (head_ == NULL) {
    return head_;

  }
  Node * curr = head_->next;
  double rsfValue = getValue(head_);
  double value = 0;
  if (curr != NULL) {
    value = getValue(curr);
  } 
  

  while (curr != NULL) {
    value = getValue(curr);
    if (value > rsfValue) {
      rsf = curr;
      rsfValue = value;
    }
    curr = curr->next;
  }
  return rsf;
}

Chain::Node* Chain::findAdjacentBlock(const Node* p) {
  if (p->next == NULL) {
    return NULL;
  }
  Node* curr = p->next->next;
  double rsf = p->data.distanceTo(p->next->data);
  Node * curr2 = p->next;

  while (curr != NULL) {
    double value = p->data.distanceTo(curr->data);
    if (value < rsf) {
      rsf = value;
      curr2 = curr;
    }
    curr = curr->next;
  }
  return curr2;
}

void Chain::unscramble() {
  /* your code here */
  Node * leftBlock = findLeftMostBlock();
  swap(head_, leftBlock);
  Node* curr = leftBlock;
  

  while (curr != NULL) {
    Node* adj = findAdjacentBlock(curr);
    swap(curr->next, adj);
    curr = adj;
  }
}

