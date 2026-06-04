#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int cof;
    int pwr;
    char var;
    struct Node *next;
} Node;

// Insert term in descending power order
Node* insertTerm(Node* head, int cof, int pwr, char var) {
    if (cof == 0) return head;

    Node *newNode, *temp, *prev;

    temp = head;
    while (temp != NULL) {
        if (temp->pwr == pwr) {
            temp->cof += cof;

            if (temp->cof == 0) {
                if (temp == head) {
                    head = head->next;
                    free(temp);
                } else {
                    prev->next = temp->next;
                    free(temp);
                }
            }
            return head;
        }
        prev = temp;
        temp = temp->next;
    }
    newNode = (Node*)malloc(sizeof(Node));
    newNode->cof = cof;
    newNode->pwr = pwr;
    newNode->var = var;
    newNode->next = NULL;

    if (head == NULL || pwr > head->pwr) {
        newNode->next = head;
        return newNode;
    }
    temp = head;

    while (temp->next != NULL && temp->next->pwr > pwr) {
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;

    return head;
}

// Create polynomial
Node* createPoly() {
    int n;
    printf("Enter number of terms: ");
    scanf("%d", &n);

    Node* head = NULL;

    for (int i = 0; i < n; i++) {
        int cof, pwr;
        printf("\nTerm %d\n", i + 1);

        printf("Coefficient: ");
        scanf("%d", &cof);
        
        printf("Power: ");
        scanf("%d", &pwr);
        head = insertTerm(head, cof, pwr, 'x');
    }

    return head;
}

// Display polynomial
void display(Node* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }
    Node* temp = head;
    int first = 1;

    while (temp != NULL) {
        if (!first && temp->cof > 0) printf(" + ");
        if (temp->cof < 0) printf(" - ");

        int coef = temp->cof < 0 ? -temp->cof : temp->cof;
        printf("%d%c^%d", coef, temp->var, temp->pwr);
        first = 0;
        temp = temp->next;
    }
    printf("\n");
}

// Addition
Node* add(Node* p1, Node* p2) {
    Node* res = NULL;
    while (p1 != NULL) {
        res = insertTerm(res, p1->cof, p1->pwr, p1->var);
        p1 = p1->next;
    }
    while (p2 != NULL) {
        res = insertTerm(res, p2->cof, p2->pwr, p2->var);
        p2 = p2->next;
    }
    return res;
}

// Subtraction
Node* sub(Node* p1, Node* p2) {
    Node* res = NULL;
    while (p1 != NULL) {
        res = insertTerm(res, p1->cof, p1->pwr, p1->var);
        p1 = p1->next;
    }
    while (p2 != NULL) {
        res = insertTerm(res, -p2->cof, p2->pwr, p2->var);
        p2 = p2->next;
    }
    return res;
}

// Multiplication
Node* mul(Node* p1, Node* p2) {
    Node* res = NULL;
    Node* t1 = p1;

    while (t1 != NULL) {

        Node* t2 = p2;
        while (t2 != NULL) {
            int coef = t1->cof * t2->cof;
            int power = t1->pwr + t2->pwr;
            res = insertTerm(res, coef, power, 'x');
            t2 = t2->next;
        }
        t1 = t1->next;
    }

    return res;
}

// Free list
void freeList(Node* head) {
    Node* temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {

    Node *p1 = NULL, *p2 = NULL, *result = NULL;

    int choice;

    do {
        printf("\n===== POLYNOMIAL MENU =====\n");
        printf("1. Create Polynomial 1\n");
        printf("2. Create Polynomial 2\n");
        printf("3. Display Polynomials\n");
        printf("4. Add\n");
        printf("5. Subtract (P1 - P2)\n");
        printf("6. Multiply\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            freeList(p1);
            p1 = createPoly();
            break;

        case 2:
            freeList(p2);
            p2 = createPoly();
            break;

        case 3:
            printf("\nP1 = ");
            display(p1);

            printf("P2 = ");
            display(p2);
            break;

        case 4:
            freeList(result);
            result = add(p1, p2);

            printf("\nP1 + P2 = ");
            display(result);
            break;

        case 5:
            freeList(result);
            result = sub(p1, p2);

            printf("\nP1 - P2 = ");
            display(result);
            break;

        case 6:
            freeList(result);
            result = mul(p1, p2);

            printf("\nP1 * P2 = ");
            display(result);
            break;

        case 0:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice!\n");
        }

    } while (choice != 0);

    freeList(p1);
    freeList(p2);
    freeList(result);

    return 0;
}