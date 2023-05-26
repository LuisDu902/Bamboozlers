#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define BIT(n) (1<<(n))

char *byte2bin(uint8_t n, char *binstr) 
{
    // one element per bit (0/1)
    uint8_t binary[8];

    int i = 0;
    for(i = 0; i < 8; i++) {
        binary[i] = n % 2;
        n = n / 2;
    }

    // printing binary array in reverse order
    for (int j = 7, k= 0; j >= 0; j--, k++)
        sprintf(binstr + k, "%d", binary[j]);
        
	return binstr;
}

void print_usage(char *name) {
	printf("Usage: %s <action> <byte> <bit no>\n", name);
	printf("\tWhere: <action> one of 'h'|'l'|'r'|'s'|'t'\n"
		"\t\t <byte> 8-bit integer in hexadecimal\n"
		"\t\t <bit no> of bit to operate on\n");
}

int main(int argc, char *argv[])
{
	char a;	// action: 'h', 'l', 'r', 's', 't'
	unsigned long n; // value to convert must be smaller than 256
	int bit; // bit to operate on: must be between 0 an 7
    char binary[9]; // array for binary representation of n,
					//  remember that in C strings are terminated with a 0
 
	// Validate command line arguments
	if (argc != 4 ){
        print_usage("bitwise");
        printf("Number of arguments should be 3\n");
        return EXIT_FAILURE;
    }

    a = *(argv[1]);

   
    if (!((a == 'h') ||(a == 'l') || (a == 'r') ||(a == 's') || (a == 't'))){
        print_usage("bitwise");
        printf("First argument error\n");
        return EXIT_FAILURE;
    }

    n = strtoul(argv[2],NULL,16);

    if (n > 255){
        print_usage("bitwise");
        printf("Second argument error\n");
        return EXIT_FAILURE;
    }

    bit = atoi(argv[3]);
   
    if (((bit < 0 || bit > 7))){
        print_usage("bitwise");
        printf("Third argument error\n");
        return EXIT_FAILURE;
    }

   

	// Print to stdout the binary representation of n
	
    char* b = byte2bin(n,binary);
    printf("Binary representation of %ld: %s\n",n,b);

	// Do what the user asked and print the result

    switch (a)
    {
    case 'h' :
        if (n & BIT(bit))
            printf("True! The bit %d is indeed 1!\n", bit);
        else
            printf("False! The bit %d is not 1!\n", bit);
        break;
    
    case 'l':
        if (n & BIT(bit))
            printf("False! The bit %d is not 0!\n", bit);
        else
            printf("True! The bit %d is indeed 0!\n", bit);
        break;

    case 'r':
        n &= ~BIT(bit);
        printf("Binary representation after reseting bit %d: %s\n",bit,byte2bin(n,binary));
        break;

    case 's':
        n |= BIT(bit);
        printf("Binary representation after setting bit %d to 1: %s\n",bit,byte2bin(n,binary));
        break;

    case 't':
        n ^= BIT(bit);
        printf("Binary representation after toggling bit %d: %s\n",bit,byte2bin(n,binary));
        break;
    }

    return 0;
}