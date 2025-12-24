/* Valgrind can be used to find some common memory errors. This program allocates two 512-byte blocks of memory and then sets the pointer to the second block 
to the first block. As a result, the address of the second block is lost, causing a memory leak. 
Also, 512 10-byte blocks of memory are never freed. This memory is allocated by the call to the get_mem routine */ 

  #include <stdlib.h>
  #include <stdio.h>
  void get_mem()
  {
    char *ptr;
    ptr = (char *) malloc (10);   /* memory not freed */
  }
  int main(void)
  {
   char *ptr1, *ptr2;
   int i;
   ptr1 = (char *) malloc (512);
   ptr2 = (char *) malloc (512);
   ptr2 = ptr1;
   free(ptr2);
   free(ptr1);
   for ( i = 0; i < 512; i++) {
       get_mem();
     }
 }
