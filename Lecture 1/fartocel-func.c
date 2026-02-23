 #include <stdio.h>
 int celc(int);
 main()
 {
         int temp;

         printf("\nPlease enter temp F ");
         scanf("%d", &temp);

         printf("\n%dF to centigrade is %dC\n", temp, celc(temp));
         exit(0);
 }
 int celc(int f)
 {
         return 5*(f - 32)/9;

 }

