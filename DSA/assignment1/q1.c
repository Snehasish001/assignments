#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define MAX 20

typedef struct Array{
    int* arr;
    int n;
}Array;

Array create(int n) {
    Array ptr;
    ptr.arr = (int*)malloc(n * sizeof(int));

    if (ptr.arr == NULL) {
        printf("Memory allocation failed.\n");
        ptr.n = 0;
        return ptr;
    }

    ptr.n = n;
    printf("Generating random elements : ");

    for (int i = 0; i < ptr.n; i++) {
        ptr.arr[i] = rand() % 900 + 100;
        printf("%d ", ptr.arr[i]);
    }

    printf("\nArray created successfully.\n");
    return ptr;
}

void display(Array ptr) {
    if (ptr.arr == NULL || ptr.n == 0) {
        printf("Array is Empty.\n");
        return;
    }

    printf("[ ");
    for (int i = 0; i < ptr.n; i++)
        printf("%d ", ptr.arr[i]);
    printf("]\n");
}

int count(Array ptr) {
    return ptr.n;
}

void reverse(Array *ptr) {
    if (ptr->arr == NULL || ptr->n == 0) {
        printf("Array is Empty.\n");
        return;
    }

    int i = 0, j = ptr->n - 1;

    while (i < j) {
        int temp = ptr->arr[i];
        ptr->arr[i] = ptr->arr[j];
        ptr->arr[j] = temp;
        i++;
        j--;
    }

    printf("Successfully reversed.\n");
}

Array indexOf(Array ptr, int target) {
    Array pos = {NULL,0};

    if (ptr.arr == NULL || ptr.n == 0) {
        printf("Array is Empty.\n");
        return pos;
    }

    pos.arr = (int *)malloc(ptr.n * sizeof(int));

    if (pos.arr == NULL)
        return pos;

    for (int i = 0; i < ptr.n; i++) {
        if (ptr.arr[i] == target) {
            pos.arr[pos.n] = i;
            pos.n++;
        }
    }

    if (pos.n == 0) {
        free(pos.arr);
        pos.arr = NULL;
    } else {
        int *temp = realloc(pos.arr, pos.n * sizeof(int));
        if (temp != NULL)
            pos.arr = temp;
    }

    return pos;
}

int getElement(Array ptr, int idx) {
    if (ptr.arr == NULL)
        return -1;

    if (idx < 0 || idx >= ptr.n)
        return -2;

    return ptr.arr[idx];
}

Array insert(Array ptr, int val) {
    if (ptr.arr == NULL || ptr.n == 0) {
        ptr.arr = (int *)malloc(sizeof(int));
        if (ptr.arr == NULL)
            return ptr;

        ptr.arr[0] = val;
        ptr.n = 1;
    } else {
        int *temp = realloc(ptr.arr, (ptr.n + 1) * sizeof(int));
        if (temp == NULL) {
            printf("Memory allocation failed.\n");
            return ptr;
        }

        ptr.arr = temp;
        ptr.arr[ptr.n] = val;
        ptr.n++;
    }

    printf("Successfully Inserted.\n");
    return ptr;
}

Array delete(Array ptr, int *val) {
    if (ptr.arr == NULL || ptr.n == 0) {
        printf("Array is Empty.\n");
        return ptr;
    }

    *val = ptr.arr[ptr.n - 1];

    if (ptr.n == 1) {
        free(ptr.arr);
        ptr.arr = NULL;
        ptr.n = 0;
    } else {
        ptr.n--;
        int *temp = realloc(ptr.arr, ptr.n * sizeof(int));
        if (temp != NULL)
            ptr.arr = temp;
    }

    return ptr;
}

Array merge(Array *ptr1, Array *ptr2) {
    Array new = {NULL,0};

    if (ptr1->arr == NULL && ptr2->arr == NULL)
        return new;

    if (ptr1->arr == NULL)
        return *ptr2;

    if (ptr2->arr == NULL)
        return *ptr1;

    new.n = ptr1->n + ptr2->n;
    int *temp = realloc(ptr1->arr, new.n * sizeof(int));

    if (temp == NULL) {
        printf("Merge failed.\n");
        new.n = 0;
        return new;
    }

    new.arr = temp;

    for (int i = 0; i < ptr2->n; i++)
        new.arr[ptr1->n + i] = ptr2->arr[i];

    ptr1->arr = NULL;
    ptr1->n = 0;

    ptr2->arr = NULL;
    ptr2->n = 0;

    printf("Merge Done.\n");
    return new;
}

void split(Array *ptr1, Array *ptr2, int idx) {
    if (ptr1->arr == NULL) {
        printf("Array is Empty.\n");
        return;
    }

    if (idx < 0 || idx >= ptr1->n) {
        printf("Invalid Index.\n");
        return;
    }

    ptr2->n = ptr1->n - idx;
    ptr2->arr = (int *)malloc(ptr2->n * sizeof(int));

    if (ptr2->arr == NULL)
        return;

    for (int i = 0; i < ptr2->n; i++)
        ptr2->arr[i] = ptr1->arr[idx + i];

    ptr1->n = idx;
    int *temp = realloc(ptr1->arr, ptr1->n * sizeof(int));

    if (temp != NULL || ptr1->n == 0)
        ptr1->arr = temp;
}

void sort(Array *ptr) {
    if (ptr->arr == NULL || ptr->n == 0)
        return;

    for (int i = 1; i < ptr->n; i++) {
        int key = ptr->arr[i];
        int j = i - 1;

        while (j >= 0 && ptr->arr[j] > key) {
            ptr->arr[j + 1] = ptr->arr[j];
            j--;
        }
        ptr->arr[j + 1] = key;
    }
}

int main()
{
    srand(time(NULL));

    Array ptr[MAX];
    for(int i=0;i<MAX;i++){
        ptr[i].arr=NULL;
        ptr[i].n=0;
    }

    int current=-1;
    int total=0;
    bool run=true;

    while(run)
    {
        printf("\n=========================================\n");
        if(current==-1)
            printf("Current Array : None\n");
        else
            printf("Current Array : A%d (Size=%d)\n",current,ptr[current].n);
        printf("Total Arrays  : %d/%d\n",total,MAX);
        printf("=========================================\n");

        printf("1. Create New Array\n");
        printf("2. Switch Current Array\n");
        printf("3. Display Current\n");
        printf("4. Count\n");
        printf("5. Reverse\n");
        printf("6. Index Of\n");
        printf("7. Get Element\n");
        printf("8. Insert\n");
        printf("9. Delete Element\n");
        printf("10. Merge With Another Array\n");
        printf("11. Split Current Array\n");
        printf("12. Sort\n");
        printf("13. Display All Arrays\n");
        printf("14. Delete Current Array Entirely\n");
        printf("15. Exit\n");
        printf("Choice : ");

        int ch;
        if(scanf("%d",&ch) != 1) break;

        if(ch!=1 && ch!=2 && ch!=13 && ch!=15 && current==-1){
            printf("No active array. Create one first.\n");
            continue;
        }

        switch(ch)
        {
        case 1:{
            if(total==MAX){ printf("Maximum arrays reached.\n"); break; }
            int n;
            printf("Size : ");
            scanf("%d",&n);
            ptr[total]=create(n);
            current=total;
            total++;
            
            printf("Resulting Array A%d: ", current);
            display(ptr[current]);
            break;
        }

        case 2:{
            if(total==0){ printf("No arrays.\n"); break; }
            printf("Existing Arrays\n");
            for(int i=0;i<total;i++)
                printf("A%d (Size=%d)\n",i,ptr[i].n);
            printf("Choose : ");
            scanf("%d",&current);
            if(current<0||current>=total){
                printf("Invalid.\n");
                current=0;
            }
            break;
        }

        case 3: display(ptr[current]); break;
        case 4: printf("Count = %d\n",count(ptr[current])); break;
        case 5: 
            display(ptr[current]);
            reverse(&ptr[current]); 
            display(ptr[current]);
            break;

        case 6:{
            int t;
            printf("Target : ");
            scanf("%d",&t);
            Array pos=indexOf(ptr[current],t);
            if (pos.arr != NULL) {
                printf("Found at indexes: ");
                display(pos);
            }else if (pos.arr == NULL && ptr[current].arr != NULL) {
                printf("Item Not Found.\n");
            }
            free(pos.arr);
            break;
        }

        case 7:{
            int idx;
            printf("Index : ");
            scanf("%d",&idx);
            int x=getElement(ptr[current],idx);
            if(x==-1) printf("Array Empty\n");
            else if(x==-2) printf("Index Out of Bound\n");
            else printf("Element=%d\n",x);
            break;
        }

        case 8:{
            int v;
            printf("Value : ");
            scanf("%d",&v);
            ptr[current]=insert(ptr[current],v);
            display(ptr[current]);
            break;
        }

        case 9:{
            int v=-1;
            ptr[current]=delete(ptr[current],&v);
            if(v!=-1) printf("Deleted=%d\n",v);
            display(ptr[current]);
            break;
        }

        case 10:{
            int other;
            printf("Merge with Array : ");
            scanf("%d",&other);
            if(other<0||other>=total||other==current){ printf("Invalid.\n"); break; }
            
            ptr[current]=merge(&ptr[current],&ptr[other]);
            for(int i = other; i < total - 1; i++) {
                ptr[i] = ptr[i+1];
            }
            total--;
            if(current > other) {
                current--;
            }
            printf("Merged Array A%d: ", current);
            display(ptr[current]);
            break;
        }

        case 11:{
            if(total==MAX){ printf("Maximum arrays reached.\n"); break; }
            int idx;
            printf("Split Index : ");
            scanf("%d",&idx);
            
            if (idx < 0 || idx >= ptr[current].n) {
                printf("Invalid Index.\n");
                break;
            }
            
            split(&ptr[current],&ptr[total],idx);
            int split_index = total;
            total++;
            printf("Split Result -> A%d (Original Left): ", current);
            display(ptr[current]);
            printf("Split Result -> A%d (New Right): ", split_index);
            display(ptr[split_index]);
            
            current = split_index;
            break;
        }

        case 12:
            sort(&ptr[current]);
            display(ptr[current]);
            break;

        case 13:
            for(int i=0;i<total;i++){
                printf("A%d : ",i);
                display(ptr[i]);
            }
            break;

        case 14:
            free(ptr[current].arr);
            for(int i = current; i < total - 1; i++) {
                ptr[i] = ptr[i+1];
            }
            ptr[total-1].arr = NULL;
            ptr[total-1].n = 0;
            
            total--;
            printf("Current array deleted completely.\n");
            
            if(total == 0) {
                current = -1;
            } else if (current >= total) {
                current = total - 1;
            }
            break;

        default:
            run=false;
            printf("Exiting Program...\n");
        }
    }

    for(int i=0;i<MAX;i++)
        free(ptr[i].arr);

    return 0;
}