#include<stdio.h>
#include<conio.h>

main()
 {
 	
   char password[20];
   char user_name[20];
   int count;

   FILE * fsect;


   fsect = fopen("security.dat","rb+");
    if(fsect == NULL)
     {
       printf("Error in opening the file");
       getch();
       exit(0);
     }
       
     
        fseek(fsect,0,SEEK_SET);
        fread(&count,sizeof(int),1,fsect);
        fseek(fsect,sizeof(int),SEEK_SET);
        fread(user_name,20 * sizeof(char),1,fsect);
        fseek(fsect,20 * sizeof(char)+sizeof(int),SEEK_SET);
        fread(password,20 * sizeof(char),1,fsect);
     
        if(count >= 3)
         {    
         	count = 0; 
         	fseek(fsect,0,SEEK_SET);
            fwrite(&count,sizeof(int),1,fsect);
            fseek(fsect,sizeof(int),SEEK_SET);
            fwrite(user_name,20 * sizeof(char),1,fsect);
            fseek(fsect,20 * sizeof(char)+sizeof(int),SEEK_SET);
            fwrite(password,20 * sizeof(char),1,fsect);
         }
    
  fclose(fsect); 
  
  printf("Unblocked successfully");	
 	
 getch();	
 	
 	 
 }
