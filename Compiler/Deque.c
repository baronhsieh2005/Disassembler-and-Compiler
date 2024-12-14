/*
 * Copyright ©2024 Travis McGaha.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Pennsylvania
 * CIS 2400 for use solely during Fall Semester 2024 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <stdio.h>
#include <stdlib.h>

#include "Deque.h"


///////////////////////////////////////////////////////////////////////////////
// Deque implementation.

Deque* Deque_Allocate() {
    Deque *deque = malloc(sizeof(Deque));
    if (deque == NULL) {
      return NULL; 
    }
    deque->front = NULL;
    deque->back = NULL;
    deque->num_elements = 0;
    return deque; 
}

void Deque_Free(Deque *dq) {
    DequeNode *curr = dq->front;
    while (curr != NULL) {
        DequeNode *next_node = curr->next;
        free(curr);
        curr = next_node;
    }
    free(dq);
}

int Deque_Size(Deque *dq) {
    return dq->num_elements;
}

void Deque_Push_Front(Deque *dq, rat_num payload) {
    DequeNode *node = malloc(sizeof(DequeNode));
    if (node == NULL) {
      return;
    }
    node->payload = payload;
    node->prev = NULL;
    node->next = dq->front;
    if (dq->front != NULL) {
        dq->front->prev = node;
    } else {
        dq->back = node;
    }
    dq->front = node;
    dq->num_elements++;
}

bool Deque_Pop_Front(Deque *dq, rat_num *payload_ptr) {
    if (dq->front == NULL) {
        return false;
    }
    DequeNode *head = dq->front;
    *payload_ptr = (head->payload);
    dq->front = head->next;
    if (dq->front != NULL) {
        dq->front->prev = NULL;
    } else {
        dq->back = NULL;
    }
    free(head);
    dq->num_elements--;
    return true;
}

bool Deque_Peek_Front(Deque *dq, rat_num *payload_ptr) {
    if (dq->front == NULL) {
        return false;
    }
    *payload_ptr = (dq->front->payload);
    return true;
}

void Deque_Push_Back(Deque *dq, rat_num payload) {
    DequeNode *node = malloc(sizeof(DequeNode));
    if (node == NULL) {
      return;
    }
    node->payload = payload;
    node->prev = dq->back;
    node->next = NULL;
    if (dq->back != NULL) {
        dq->back->next = node;
    } else {
        dq->front = node;
    }
    dq->back = node;
    dq->num_elements++;
}

bool Deque_Pop_Back(Deque *dq, rat_num* payload_ptr) {
    if (dq->back == NULL) {
        return false;
    }
    DequeNode *tail = dq->back;
    *payload_ptr = (tail->payload);
    dq->back = tail->prev;
    if (dq->back != NULL) {
        dq->back->next = NULL;
    } else {
        dq->front = NULL;
    }
    free(tail);
    dq->num_elements--;
    return true;
}

bool Deque_Peek_Back(Deque *dq, rat_num *payload_ptr) {
    if (dq->back == NULL) {
        return false;
    }
    *payload_ptr = (dq->back->payload);
    return true;
}

// TODO: The rest of the Deque functions described in Deque.h

///////////////////////////////////////////////////////////////////////////////
// DQIterator implementation.

DQIterator* DQIterator_Allocate(Deque *dq) {
    DQIterator *iterator = malloc(sizeof(DQIterator));
    if (iterator == NULL) {
        return NULL;
    }
    iterator->deque = dq;
    iterator->node = dq->front;
    return iterator;
}

void DQIterator_Free(DQIterator *iter) {
    free(iter);
}

bool DQIterator_IsValid(DQIterator *iter) {
    return (iter->node != NULL);
}

bool DQIterator_Next(DQIterator *iter) {
    if (iter->node == NULL) {
        return false;
    }
    iter->node = iter->node->next;
    return DQIterator_IsValid(iter);
}

void DQIterator_Get(DQIterator *iter, rat_num *payload) {
    *payload = iter->node->payload;
}

bool DQIterator_Remove(DQIterator *iter) {
    Deque *dq = iter->deque;
    DequeNode *curr = iter->node;

    if (curr->prev != NULL) {
        curr->prev->next = curr->next;
    } else {
        dq->front = curr->next;
    }

    if (curr->next != NULL) {
        curr->next->prev = curr->prev;
        iter->node = curr->next;
    } else {
        dq->back = curr->prev;
        iter->node = curr->prev;
    }
    
    free(curr);
    dq->num_elements--;

    return iter->node != NULL;
}


void DQIterator_Rewind(DQIterator *iter) {
    iter->node = iter->deque->front;
}

// TODO: The rest of the DQIterator functions described in Deque.h
