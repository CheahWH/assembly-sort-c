#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void sorter ( long* list, long count, long opcode )
{
    asm (
    "movq %0, %%rax;"
    "movq %1, %%rcx;"
    "movq %2, %%rbx;"

    "movq $0, %%rdx;"
    "dec %%rcx;"

    "main_loop: "

        "movq %%rdx, %%rsi;"
        "inc %%rsi;"

        "second_loop: "

            "movq (%%rax, %%rdx, 8 ), %%r10;"
            "movq (%%rax, %%rsi, 8), %%r11;"
            "cmp  $2, %%rbx;"
            "je descending;"
            "jl ascending;"
        "ascending: "
            "cmp %%r10 ,%%r11;"
            "jl sort;"
            "jmp LOOP_S1;"

        "descending: "
            "cmp %%r10, %%r11;"
            "jg sort;"
            "jmp LOOP_S1;"

        "sort: "
            "xchg %%r11, %%r10;"
            "movq %%r10, (%%rax, %%rdx, 8);"
            "movq %%r11, (%%rax, %%rsi, 8);"

        "LOOP_S1: "
            "inc %%rsi;"
            "cmp %%rsi, %%rcx;"
            "jge second_loop;"

    "inc %%rdx;"
    "cmp %%rdx, %%rcx;"
    "jg main_loop;"

    :
    : "m"(list), "m"(count), "m"(opcode)
    :
    );
}

int main(int argc, char** argv)
{
	long numlist[1000], asc;
	FILE *fptr;

	long i = 0;

	if (argc != 3)
	{
		printf("Usage: %s filename asc_des\n", argv[0]);
		return 1;
	}

	asc = atol (argv[2]);
	asc = (asc == 1) ? 1 : 2;

	printf("\n");

	fptr = fopen((argv[1]), "rtc");
	if (fptr == NULL)
      printf( "File %s was not opened\n",argv[1] );
	else
   {
      /* Set pointer to beginning of file: */
      fseek( fptr, 0L, SEEK_SET );

      /* Read data from file: */
	  while (fscanf(fptr, "%ld", &numlist[i]) != EOF)
	  {
          printf( "%ld ", numlist[i] );
		  i++;
	  }

      printf( "\n\nNumber of integer = %ld\n", i );
      printf( "Ascend_or_Descend = %ld\n\n", asc );
      fclose( fptr );
    }

   sorter(numlist, i, asc);

   for (int j = 0; j < i; j++)
          printf( "%ld ", numlist[j] );

   printf("\n");

   return 0;
}






