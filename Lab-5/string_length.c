#include <stdio.h>
#include <string.h>
int main() {
	char input[99];
	int conventionalLength;
	int manualLength;	
    	printf("Enter the string:\n");
    	scanf("%s",input);
    	printf("string entered: %s\n",input);
    		for(int i=0;i<99;i++){
	        	if(input[i]=='\0'){
                		break;
            		}
            		manualLength++;
    		}
    	conventionalLength=strlen(input);
    	printf("Length of the string without standard functions: %d\n", manualLength);
    	printf("Length of the string with standard functions: %d\n",conventionalLength);
    	return 0;
}


