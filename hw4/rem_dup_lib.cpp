#include "rem_dup_lib.h"

void removeConsecutive(Item* head)
{
    if(head == nullptr || (head->next == nullptr)) // base case
    {
        return;
    }
    if(head->val == head->next->val)
    {
        Item* following = head->next;
        head->next = head->next->next;
        delete following;
        removeConsecutive(head);
    }
    else
    {
        removeConsecutive(head->next);   
    }
}

Item* concatenate(Item* head1, Item* head2)
{
    if((head1 == nullptr && head2 == nullptr)) // base case
    {
        return nullptr;
    }
    if(head2 != nullptr && head1 == nullptr)
    {
        Item* list2 = new Item(head2->val, concatenate(head1, head2->next));
        return list2;
    }
    else
    {
        Item* list1 = new Item(head1->val, concatenate(head1->next,head2));
        return list1;
    }
}

Item* append(Item* head, int newval) // added helper function to append new items
{
    if(head == nullptr) // base case
    {
        Item* newitem = new Item(newval, nullptr);
        return newitem;
    }
    head->next = append(head->next, newval);
    return head;
}

void delete_list(Item* head) // added helper function to delete list
{
    if(head == nullptr) // base case
    {
        return;
    }
    delete_list(head->next);
    delete head;
}