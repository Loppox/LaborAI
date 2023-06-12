#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lin_list {
    char *payload;
    struct lin_list *next;
    int count;
} LinListCell, *LinList_p;

LinList_p findCell(LinList_p anchor, char *payload) {
    LinList_p curr = anchor->next;
    LinList_p prev = anchor;
    if(anchor->next == NULL){
        return anchor;
    }
    while (curr->next != NULL) {
        if (strcmp(curr->payload, payload) == 0) {
            anchor->count += 1;
            prev->next = curr->next;
            curr = curr->next;
            anchor = prev;
            //printf("Double");
        }
        curr = curr->next;
        prev = prev->next;
    }
    return anchor;
}

LinList_p countInput(LinList_p anchor) {
    LinList_p curr = anchor;
    while (curr->next != NULL) {
        curr->count = 1;
        curr = findCell(curr, curr->payload);
        curr = curr->next;
    }
    return anchor;
}

void printList(LinList_p anchor) {
    LinList_p curr = anchor;

    while (curr->next != NULL) {
        printf("%s: %d\n", curr->payload, curr->count);
        curr = curr->next;
    }
}

int main(int argc, char *argv[]) {
    LinList_p anchor = malloc(sizeof(LinListCell));
    LinList_p curr = anchor;
    curr->next = NULL;

    argc = 6;
    argv[0] = 0;
    argv[1] = "agc";
    argv[2] = "agc";
    argv[3] = "abc";
    argv[4] = "agc";
    argv[5] = "hfs";

    printf("Before:\n");
    for (int i = 1; i < argc; i++) {
        printf("%s\n", argv[i]);
        curr->payload = malloc(strlen(argv[i]) + 1);
        strcpy(curr->payload, argv[i]);

        curr->next = malloc(sizeof(LinListCell));
        curr = curr->next;
        curr->next = NULL;
    }

    anchor = countInput(anchor);

    printf("After:\n");
    printList(anchor);

    // Speicher freigeben
    curr = anchor;
    while (curr->next != NULL) {
        LinList_p temp = curr;
        curr = curr->next;
        free(temp->payload);
        free(temp);
    }
    //free(anchor);

    return 0;
}
