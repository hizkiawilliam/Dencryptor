#include <stdio.h> 
#include <windows.h>
#include <stdlib.h>
#include "header.h"
#include "link.h"

void admin();
void admin_menu();
void help();
void encrypt_menu();
char *encrypt(char input[100], int code);
char *decrypt(char input[100], int code);
void decrypt_menu();
void en_file();
void de_file();
void menu();
void printd(char* x, int y);

typedef struct Node Node;
typedef Node *NodePtr;
NodePtr stackPtr = NULL; // points to stack top


int main()
{
	FILE *fp;												//deklarasi sebuah pointer dari tipe file	
    fp=fopen("account.txt","a+");
    char data[50];
    char pass[50];
    while(fscanf(fp,"%s %s\n",data, pass)!=EOF){ //baca dari txt
    	push( &stackPtr, decrypt(data,2), pass); // push semua isi txt ke stackPtr setelah didecrypt
	}
	reverse(&stackPtr); // perlu direverse, karena stack akan terbalik setiap pembacaan
	system("COLOR 0A");
	Sleep(50);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("                                            ");
	printd("WELCOME TO DENCRYPTER v3.0",30);
	Sleep(500);
	printf("\n\n\t\t\t\t\t ");
    system("pause");
	admin();   
}

//=====================================================================================// void admin
void admin()
{
	system("cls");
	char code[50] = {"admin"};
	char admin_code[50] = {"888"};
	char ext[50] = {"exit"};
	char input[50],pass[50];
	printf("Input User Account      :");
	scanf("%s", input);
	printf("Input Your Password     :");
	scanstr(pass);
	if((strcmp(input,code)==0)&&(strcmp(pass,admin_code)==0)){
		printf("\nAdmin login\n");
		Sleep(500);
		admin_menu();
	}
	else if(search(stackPtr,input,pass)==1){
		printf("\nUser login");
		Sleep(500);
		menu();
	}
	else if(strcmp(input,ext)==0){
		exit(0);
	}
	else{
		printf("\nYou don't have access. Input 'exit' to exit.\n");
		system("pause");
		admin();
	}
}

//=====================================================================================// void admin menu
void admin_menu()
{
	FILE *fp;												//deklarasi sebuah pointer dari tipe file	
    fp=fopen("account.txt","a+");
    char data[50];
	system("cls");											//clear screen setiap pemanggilan fungsi menu
	header_admin();
	int choice; // user's menu choice 
	char value[50], pass[50]; // char input by user 
	instructions(); // display the menu. location = link.h
	switch( getch() ) {
		// push value onto stack
		case '1':
			printf( "\n\t\t\t\tEnter a name: " );
			scanf( "%s", value );
			printf( "\t\t\t\tEnter pass: " );
			scanf( "%s", pass );
			searchUser( stackPtr, value)? printf("\t\t\t\t%s already exists!\n",value) : push(&stackPtr,value,pass);
			printStack( stackPtr );
			printStackFile( stackPtr );
			printf("\t\t\t\t");
			system("pause");
			fclose(fp);
			break;
		// pop value 
		case '2':
			// if queue is not empty 
			if ( !isEmpty( stackPtr ) ) {
			pop(&stackPtr);
			} // end if
			printStack( stackPtr );
			printStackFile( stackPtr );
			printf("\t\t\t\t");
			system("pause");
			break;
		case '3':
			printf( "\n\t\t\t\tEnter a name: " );
			scanf( "%s", value );
			searchUser( stackPtr, value)? printf("\t\t\t\t%s found\n",value) : printf("\t\t\t\t%s not found\n",value);
			printf("\t\t\t\t");
			system("pause");
			break;
		case '4':
			printf("\n"); printStack( stackPtr );
			printf("\t\t\t\t");
			system("pause");
			break;
		case '5':
			printStackFile( stackPtr );
			menu();
		case '6':
			printStackFile( stackPtr );
        	admin();
        case '7':
        	printStackFile( stackPtr );
        	exit(0);
		default:
			printf( "\n\t\t\t\tInvalid choice.\n\n" );
			admin_menu();
			break;
	
	} // end while
	admin_menu();
}

//=====================================================================================// menu
void menu() 
{ 
	system("cls");											//clear screen setiap pemanggilan fungsi menu
    header();												//memanggil fungsi header
	header_menu();											//memanggil fungsi header menu
    printf("\t\t\t\t\t==============================\n");
    printf("\t\t\t\t\t| 1. Encrypt                 |\n");
    printf("\t\t\t\t\t| 2. Decrypt                 |\n");
    printf("\t\t\t\t\t| 3. Encrypt from file       |\n");
    printf("\t\t\t\t\t| 4. Decrypt from file       |\n");
    printf("\t\t\t\t\t| 5. Help                    |\n");
    printf("\t\t\t\t\t| 6. Exit                    |\n");
    printf("\t\t\t\t\t==============================\n");
    printf("\t\t\t\t\tSelect Your Choice : ");
  	switch(getch())		
    {
    case '1':
        encrypt_menu();	
        break;
    case '2':
        decrypt_menu();								
        break;
    case '3':
        en_file();
        break;
    case '4':
        de_file();
        break;
    case '5':
    	help();
    	break;
    case '6':
        exit(0);								
    default:									
    	printf("\n\n\t\t\t\t\tWrong input!\n");
    	printf("\t\t\t\t\tPlease input choice between 1 to 6 only!\n\n");
    	printf("\t\t\t\t\t");
    	system("pause");
		menu();
    }
}

//=====================================================================================// void encrypt
void encrypt_menu()
{ 
	system("cls");									
    header();
    header_menu_encrypt();
	char input[100], output[100], c;
	memset(output, 0, 100);
	int i,j,code; 
	printf("\t\t\t\tInput chiper code : ");
  	switch(getch())		
    {
	    case '1':
	    	code = 1;
	        break;
	    case '2':
	    	code = 2;
	        break;								
	    default:									
	    	printf("\n\n\t\t\t\tWrong input!\n");
	    	printf("\t\t\t\tPlease input choice between 1 or 2 only!\n\n");
	    	printf("\t\t\t\t");
	    	system("pause");
			menu();
    }
    printf("%d",code);	
    printf("\n\t\t\t\tInput message	  : ");				
    scanf("%s", &input);
    strcpy(output,encrypt(input,code));
	printf("\t\t\t\tEncrypted message : ");
	for(i=0;output[i]!='\0';i++)
	{
		printf("%c",output[i]);
	}
	printf("\n\n\t\t\t\t");
    system("pause");
    menu();
}

//=====================================================================================// void decrypt
void decrypt_menu()
{
	system("cls");									
    header();
    header_menu_decrypt();
	char input[100], lowered[100], output[100], c;
	memset(output, 0, 100);
	int i,j,code; 
	printf("\t\t\t\tInput chiper code : ");
  	switch(getch())		
    {
	    case '1':
	    	code = 1;
	        break;
	    case '2':
	    	code = 2;
	        break;								
	    default:									
	    	printf("\n\n\t\t\t\tWrong input!\n");
	    	printf("\t\t\t\tPlease input choice between 1 or 2 only!\n\n");
	    	printf("\t\t\t\t");
	    	system("pause");
			menu();
    }
    printf("%d",code);	
    printf("\n\t\t\t\tInput message	  : ");				
    scanf("%s", &input);
    strcpy(output,decrypt(input,code));
	printf("\t\t\t\tDecrypted message : ");
	for(i=0;output[i]!='\0';i++)
	{
		printf("%c",output[i]);
	}
	printf("\n\n\t\t\t\t");
    system("pause");
    menu();
}

//=====================================================================================// void encrypt from file
void en_file()
{
	system("cls");									
    header();
    printf("\t\t\t\t      =================================\n");
    printf("\t\t\t\t      |          File Encrypt         |\n");
    printf("\t\t\t\t      =================================\n\n");
	FILE *fptr1, *fptr2; 
    char filename[100], c;
	int i; 
    printf("\t\t\t\tEnter the filename to open for reading : "); 
    scanf("%s", filename); 
  	
    // Open one file for reading 
    fptr1 = fopen(filename, "r"); 
    if (fptr1 == NULL) 
    { 
        printf("\t\t\t\tCannot open file %s \n", filename);
        printf("\n\n\t\t\t\t");
    	system("pause");
        menu(); 
    } 
  
    printf("\t\t\t\tEnter the filename to open for writing : "); 
    scanf("%s", filename); 
  
    // Open another file for writing 
    fptr2 = fopen(filename, "w"); 
    if (fptr2 == NULL) 
    { 
        printf("\t\t\t\tCannot open file %s \n", filename); 
        printf("\n\n\t\t\t\t");
    	system("pause");
        menu(); 
    } 
  
    // Read contents from file 
    c = fgetc(fptr1); 
    while (c != EOF) 
    { 
    	for(i=0; i<56; i++){
    		if(c==low[i]){
    			c=chip3[i];
			}
		}
        fputc(c, fptr2); 
        c = fgetc(fptr1); 
    } 
  
    printf("\n\t\t\t\tContents encrypted to %s", filename); 
  
    fclose(fptr1); 
    fclose(fptr2); 
    printf("\n\n\t\t\t\t");
    system("pause");
    menu();
}

//=====================================================================================// void decrypt from file
void de_file()
{
	system("cls");									
    header();
    printf("\t\t\t\t      =================================\n");
    printf("\t\t\t\t      |          File Decrypt         |\n");
    printf("\t\t\t\t      =================================\n\n");
	FILE *fptr1, *fptr2; 
    char filename[100], c;
	int i; 
    printf("\t\t\t\tEnter the filename to open for reading : "); 
    scanf("%s", filename); 
  	
    // Open one file for reading 
    fptr1 = fopen(filename, "r"); 
    if (fptr1 == NULL) 
    { 
        printf("\t\t\t\tCannot open file %s ", filename); 
        printf("\n\n\t\t\t\t");
    	system("pause");
        menu(); 
    } 
  
    printf("\t\t\t\tEnter the filename to open for writing : "); 
    scanf("%s", filename); 
  
    // Open another file for writing 
    fptr2 = fopen(filename, "w"); 
    if (fptr2 == NULL) 
    { 
        printf("\t\t\t\tCannot open file %s ", filename); 
        printf("\n\n\t\t\t\t");
        system("pause");
        menu(); 
    } 
  
    // Read contents from file 
    c = fgetc(fptr1); 
    while (c != EOF) 
    { 
    	for(i=0; i<56; i++){
    		if(c==chip3[i]){
    			c=low[i];
			}
		}
        fputc(c, fptr2); 
        c = fgetc(fptr1); 
    } 
  
    printf("\n\t\t\t\tContents decrypted to %s", filename); 
    fclose(fptr1); 
    fclose(fptr2);
    printf("\n\n\t\t\t\t");
    system("pause");
	menu(); 
}

//=====================================================================================// void help
void help()
{
	system("cls");	
	header();
	printf("\t\t\t\t      =================================\n");
    printf("\t\t\t\t      |           Help Menu           |\n");
    printf("\t\t\t\t      =================================\n\n");	
    printf("Before using this program, it's better to know its use and how to use this program.\n\n");
    printf("There are two type of encryption/decryption: \n\n");
    printf("1. Message (Menu 1 & 2) \n");
    printf("   In this type of choice, you'll be asked to input chiper code, each will result in different chiper. \n");
    printf("   If you use chipper code 1, to descript it, you need to input chiper code 1 too when decrypting. \n");
    printf("   This applies for chipper 2. So if you're giving a code 2 message, tell your reciever to input code 2. \n");
    printf("   IMPORTANT!!! Message encryption/decryption has a rule you need to comply with: LETTERS ONLY (upper and lower) \n\n");
    printf("2. File (Menu 3 & 4) \n");
    printf("   In this type of choice, you'll be asked to input your file name. \n");
    printf("   Your file can't be in seperate folder, it needs to be in the same folder. \n");
    printf("   You'll then be asked of a new file where you want to save the encryption/descryption file. \n");
    printf("   Same condition applies, that file will be located at the same folder. \n");
    printf("   IMPORTANT!!! File must be filled with LOWERCASE LETTERS ONLY, otherwise, the result will be damaged or this \n");
    printf("   program will not work. \n");
	getch();
    menu();
}

//=====================================================================================// void print delay
void printd(char* x, int y)
{
	int i;
	for(i=0;i<strlen(x);i++)
	{
		printf("%c",x[i]);
		Sleep(y);
	}
}
