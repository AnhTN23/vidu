#include"header.h"

typedef enum
{
	FALSE = 0,
	TRUE = 1
} Bool;

int main()
{
	char arr[LENGTH];
	int sizeArr = strlen(arr);
	uint32_t sum;
	Bool CHECKSUM = TRUE;
	
	FILE *ptrSREC = fopen("blinkLed.srec", "r");
	FILE *ptrOut = fopen("Output.txt", "w");
	
	while( fgets(arr, LENGTH, ptrSREC) != NULL )
	{
		sum = check_sum(arr);
		if( (sum & 0xFF) == 0xFF )
		{
			#if 0 /* put each char in string */
			int space = 0;
			for (int i = 4; i < sizeArr - 3; i++)
			{
				fputc(arr[i], ptrOut);
				if( space == 3 )
				{
					fputc(' ', ptrOut);
				}
				space++;
			}
			fputc('\n', ptrOut);
			#endif /* put each char in string */ /* NOT OK, need help! */
			
			#if 1 /* copy & put string */
			/* strncpy not copy '\0', so must add '\0' to target */
			char data[] = {0};
			strncpy(data, arr + 8, sizeArr);
			int a = strlen(data);
			data[a-3] = '\0';
			
			char address[4] = {0};
			strncpy(address, arr+4, 4);
			address[4] = '\0';
			
			char noThing[] = " ";
			char out[200];
			/* size of target (size of out) large enough to avoid memmory overflow */
			sprintf(out, "%s%s%s", address, noThing, data);
			
			printf("%s\n", data);
			fputs(out, ptrOut);
			fputc('\n', ptrOut);
			
			#endif /* copy string */
		}
		else
		{
			printf("checkSum not true: %s", arr);
		}
	}
	
	fclose(ptrSREC);
	fclose(ptrOut);
	return 0;
}

uint32_t Char2Hex(char a)
{
	switch(a)
	{
		case '1':
			return 0x01;
			break;
		case '2':
			return 0x02;
			break;
		case '3':
			return 0x03;
			break;
		case '4':
			return 0x04; 
			break;
		case '5': 
			return 0x05; 
			break;
		case '6': 
			return 0x06; 
			break;
		case '7': 
			return 0x07; 
			break;
		case '8': 
			return 0x08; 
			break;
		case '9': 
			return 0x09; 
			break;
		case 'A': 
			return 0x0A; 
			break;
		case 'B': 
			return 0x0B; 
			break;
		case 'C': 
			return 0x0C; 
			break;
		case 'D': 
			return 0x0D; 
			break;
		case 'E': 
			return 0x0E; 
			break;
		case 'F': 
			return 0x0F; 
			break;
		default : 
			return 0x00; 
			break;
	}
}

/* algorithm checksum in header.h */
uint32_t check_sum(char arr[LENGTH])
{
	int sizeArr = strlen(arr);
	int i;
	uint32_t sum = 0x00;

	for ( i = 2; i < sizeArr; i += 2)
	{
		sum += Char2Hex(arr[i+1]) + (Char2Hex(arr[i]) << 4);
	}
	return sum;
}
