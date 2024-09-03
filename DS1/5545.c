#include <stdio.h>
#include <stdlib.h>

void print_binary_char(char c)
{
    int i;
    signed int binC;
    binC = (signed int)c;
    for (i=8; i>=0; i--)
    {
        printf("%d",( ( binC & (1 << i) ) ? 1 : 0) );

    }
}
/*using bitwise operators to print the binary by shifting all bits to the left by number
of specified bits and checking the first bit each time

 */
void question1()
{
    printf("printing from -16 to 15 in binary\n");
    char c;
    for(c=-16; c<16; c++)
    {
        printf("%d\t", c);
        print_binary_char(c);
        printf("\n");
    }
}
/*
 *
 */
union ftoh
{
    float fnum;
    unsigned int hnum;
};
void print_binary_float(float f)
{
    union ftoh ufh;
    ufh.fnum = f;
    printf("hex: 0x%x" ,ufh.hnum);
    /*PUT YOUR CODE HERE*/
}
/* creating a union to get a float and then use it as unsigned int and
printing it as hexadecimal using %x as format specifier in printf() statement.

 */
void question2()
{
    float numbers[] = {0.0f, 1.0f, 2.0f, 0.1f};
    int count = sizeof(numbers) / sizeof(numbers[0]);
    int i;

    for(i=0; i<count; i++)
    {
        printf("%.2f is represented as: ", numbers[i]);
        print_binary_float(numbers[i]);
        printf("\n");
    }
}
/*
 *
 */
union xo {
float f;
int i;
};

float get_smallest_positive_float()
{
    union xo rep;
 rep.i= 00000000100000000000000000000001;
 printf("The smallest positive 'float' is: %e\n", rep.f);
    return 0;
}
/*
 *
 */
int get_double_epsilon()
{
   double eps = 1.0f;
    while ((double)(1 + eps/2.0 )!= 1)
 {
     eps /= 2.0;
}
eps*=2.0;
 printf("Epsilon for 'double' is: %e\n", eps);
         return 0;
}
/*
 *
 */
 typedef union {
double f;
struct {
    unsigned long double mantisa : 52;
    unsigned long exponent:11;
    unsigned long sign : 1;
  } fs;

} expo;

int get_longdouble_exponent_bias()
{
    expo ldub;

ldub.f = 00111111100000000000000000000000;


    return ldub.fs.exponent;
}
/*
 *
 */
void question3()
{
    get_smallest_positive_float();
    get_double_epsilon();
    printf("'long double' has a bias of %x for its exponent\n", get_longdouble_exponent_bias());

}
/*
 *
 */
int get_command()
{
    int choice;
    printf("\n\n");
    printf("*********************************************\n");
    printf("* Enter 1 for Signed Integer Representation *\n");
    printf("* Enter 2 for Floating-Point Endianness     *\n");
    printf("* Enter 3 for Floating-Point Representation *\n");
    printf("* Enter anything else to exit               *\n");
    printf("*********************************************\n");
    printf("Your choice: ");
    scanf("%d", &choice);
    fseek(stdin, 0, SEEK_END);
    printf("\n");
    return choice;
}
/*
 *
 */
main()
{

    while(1)
    {
        switch(get_command())
        {
        case 1:
            question1();
            break;
        case 2:
            question2();
            break;
        case 3:
            question3();
            break;
        default:
            printf("Invalid Choice. Exiting...\n");
            exit(1);
        }
    }
    return 0;
}
