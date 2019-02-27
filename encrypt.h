#include <string.h>

char up[56] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_!@#$%^&*()_+{}|:<>?";
char low[56] = "abcdefghijklmnopqrstuvwxyz0123456789_!@#$%^&*()_+{}|:<>?";
char chip1[56] = "paosidufygthrjekwlqmznxbcv1029384756_+-)(*&^%$#@!{<}>|:?";
char chip2[56] = "zamlxsnkcdbjvfghqpwoeiruty5647382910_!+@_#)$(%*^&{?|<:>}";
char chip3[56] = "QAZWSXEDCRFVTGBYHNUJMIKOLP0123457689_!@#$%^&*()_+{}|:<>?";
char chip4[56] = "BYHNUJMDCRFVIQAZWSXETGKOLP0123457689_!@#$%^&*()_+{}|:<>?";

char *encrypt(char input[100], int code)
{
	int i,j;
	static char output[100], lowered[100];
	memset(output, 0, 100);
	memset(lowered, 0, 100);
	for(i=0;input[i]!='\0';i++)
    { 
    	for(j=0; j<56; j++){
    		if(input[i]==up[j]){
    			lowered[i]=low[j];
			}
			else if(input[i]==low[j]){
    			lowered[i]=low[j];
			}
		}
	}
	//chipering
	for(i=0;lowered[i]!='\0';i++){ 
    	for(j=0; j<56; j++){
    		if(lowered[i]==low[j]){
    			if (code == 1){
    				output[i]=chip1[j];
				}
    			else if (code == 2){
    				output[i]=chip2[j];
				}
				else if (code == 4){
    				output[i]=chip4[j];
				}
			}
		}
	}
	return output;
}

char *decrypt(char input[100], int code)
{
	int i,j;
	static char output[100], lowered[100];
	memset(output, 0, 100);
	memset(lowered, 0, 100);
	for(i=0;input[i]!='\0';i++)
    { 
    	for(j=0; j<56; j++){
    		if(input[i]==up[j]){
    			lowered[i]=low[j];
			}
			else if(input[i]==low[j]){
    			lowered[i]=low[j];
			}
		}
	}
	
	for(i=0;lowered[i]!='\0';i++)
    { 
    	for(j=0; j<56; j++){
    		if (code == 1){
    			if(lowered[i]==chip1[j]){
    				output[i]=low[j];
				}
			}	
			else if (code == 2){
				if(lowered[i]==chip2[j]){
    				output[i]=low[j];
				}	
			}
			else if (code == 4){
				if(lowered[i]==chip4[j]){
    				output[i]=low[j];
				}	
			}
		}
	}
	return output;
}

char *scanstr(char text[])
{
	char ch;
	int i = 0;
	while(1)
	{
		ch = getch();
		if(ch==13)
	    {
	    	break;
	    }
	    else if(ch==8)
	    {
	    	if(i>0)
	    	{
	    		i--;
	        	printf("\b ");
	        	text[i] = ch;	
			}
			else
			{
				continue;
			}
	    }
	    else
	    {
	        text[i] = ch;
			i++;	
			ch = '*';
		}
		printf("%c",ch);
	}
	text[i] = '\0';
	return text;
}
