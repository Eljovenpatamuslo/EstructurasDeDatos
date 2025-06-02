#include <stdio.h>
#include <stdlib.h>


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
typedef struct _ListNode {
    int val;
    struct _ListNode *next;
} ListNode;

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* aux = l1;
    ListNode* aux2 = l2;
    int valor1 = 0;
    int valor2 = 0;
    for(int mult = 1; aux != NULL; aux = aux->next,mult*=10){
        valor1 += aux->val*mult;
    }
    for(int mult = 1; aux2 != NULL;aux2 = aux2->next,mult*=10){
        valor2 += aux2->val*mult;
    }
    int final = valor1+valor2;

    ListNode* resultado = malloc(sizeof(ListNode));
    
}

int main(){
    
}