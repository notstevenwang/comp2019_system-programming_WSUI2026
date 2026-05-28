#include <stdio.h>
#include <stdlib.h>

/* Comparison function for sorting integers in descending order */
int compare(const void *x, const void *y) {
    int intx = *((int*)x);
    int inty = *((int*)y);

    /* return the result of the comparison value, insert you code here */
    return inty - intx; 

    /* if want to descending if x > y then we change inty - intx because if it returns negative, then x should come first before y (qsort logic) */

}

int main() {
    int arrint[] = {16, 5, 8, 1, 3, 2};
    int n = 6;

    printf("The array: \n");
	/* print the array, insert you code here*/

    for (int i = 0; i < n; i++){
        printf("%d ", arrint[i]);
    }
    printf("\n");

    /* Sort the array using qsort(), insert you code here */

    qsort(arrint, n, sizeof(int), compare);

    /*
    What qsort will do is first take the arrint[0] as x and arrint[1] as y
    Then it will put it inside compare, and see the return.
    If the return is negative, then the x is first before y
    if the return is positive, then the y is first before x
    */

    printf("The sorted array: \n");

    /* print the sorted array, insert you code here*/

     for (int i = 0; i < n; i++){
        printf("%d ", arrint[i]);
    }
    printf("\n");

    return 0;
}