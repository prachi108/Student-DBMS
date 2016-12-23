#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

struct bnode       // Structure for the node of AVL-search tree
 {
    struct bnode* left;
    struct bnode* right;
    int rn;
    int bf;
    int location;
 };
 typedef struct bnode bnode;

struct lnode        // Structure for the linked list
 {
    struct lnode* next;
    int data;
 };
 typedef struct lnode lnode; 
 
 struct node       // Structure for simply storing 2 values namely rollno and location
 {
    int rn;
    int location;
 };
 typedef struct node node;
  

struct student      // Structure to store the entire detail of a student
 {
    char name[20];
    int rollno;
    char address[30];
    float marks;
};
typedef struct student st;

                                   // Function declarations
int bin_delete(bnode**,int);
int bin_insert(bnode**,node);
int bin_traverse(bnode*,int);
void close(bnode**,lnode**);
void delete(bnode**,lnode**);
void display(bnode*);
void insert(bnode**,lnode**);
int link_delete(lnode**);
int link_insert(lnode**,int);
void preorder(bnode*);
void update(bnode*);
void append(bnode**);
void right_rotation(bnode*);
void left_rotation(bnode*);
void balance(bnode*);
void refresh(bnode**);
void view(bnode*);
void view_all(bnode*,FILE*);
void m1(bnode*);
int security();
void security_modify();
/*
void inorder(bnode* link)
 {
 	if(link == NULL)
 	  return;
 	  
 	 inorder(link->left);
	  
	 printf("%d",link->rn);
	 
	 inorder(link->right);
	 
 }
 */	

void main()               
 {                              // Starting of main
 	char choice;
 	FILE *fbin;
 	FILE *fe;
 	int i;
 	node n;
 	bnode * HEAD;
 	lnode * START;
 	int check;
 	
 	check = security();
	if(check == 0)
	  {
	   printf("\n THE DATABASE HAS BEEN BLOCKED DUE TO UNAUTHORIZED USER ACCESS \n");
       getch();
       exit(0); 
      }
     else
	  {
	  	printf(" \nUSER AUTHENTICATION IS SUCCESSFULL \n ACCESS ALLOWED \n");
	  	getch();
	  } 
	
 	fflush(stdin);
 	HEAD = NULL;
 	START = NULL;
 	
 	fbin = fopen("bintree.dat","rb");
    if(fbin == NULL)
     {
       printf("Error in opening the file");
       getch();
       exit(0);
     }
       
    while(fread(&n,sizeof(n),1,fbin) == 1)
     {
       bin_insert(&HEAD,n);	
     }
    fclose(fbin); 
    
    
    fe = fopen("empty.dat","rb");
    if(fe == NULL)
     {
       printf("Error in opening the file");
       getch();
       exit(0);
     }
       
    while(fread(&i,sizeof(i),1,fe) == 1)
     {
       //printf("checking,,,,");
       link_insert(&START,i);	
     }
     
    fclose(fe); 
     
       
       do
        {
       
           printf("\n\n STUDENT DATABASE");
           printf("\n 1. Insert record");
           printf("\n 2. Append record");
           printf("\n 3. Display record");
           printf("\n 4. View All records");
           printf("\n 5. Update record");
           printf("\n 6. Delete record");
           printf("\n 7. Refresh");
           printf("\n 8. Security Modification");
           printf("\n 9. Exit");
           printf("\n\n Enter your choice :-  ");
           scanf("%c",&choice);
       
           switch(choice)
            {
              case '1':   insert(&HEAD,&START);
                         break;
              case '2':   append(&HEAD);
                         break;
              case '3':   display(HEAD);
                         break;
              case '4':   view(HEAD);
                         break;           
              case '5':   update(HEAD);
                         break;                   
              case '6':   delete(&HEAD,&START);
                         break;
              case '7':   refresh(&HEAD);
                          START = NULL;
                         break;
			  case '8':   security_modify();
			             break;			            
              case '9':   close(&HEAD,&START);
			             break;                     
              default:  printf("INVALID CHOICE");
                         getch();
                         break;
              
            }
         fflush(stdin);  
            
         }while(1); 
}                                   // End of main
 
 
 
 int security()
 {                                         
    char password[20]; 
    char user_name[20];
    char a[20];
    char b[20];
    char ch = 0;
    int count = 0;
    int c,i = 0;
  
    FILE * fsect;
   
    fsect = fopen("security.dat","rb+");
    if(fsect == NULL)
     {
       printf("Error in opening the file");
       getch();
       exit(0);
      }
            
   
     fseek(fsect,0,SEEK_SET);
     fread(&c,sizeof(int),1,fsect);
     fseek(fsect,sizeof(int),SEEK_SET); 
     fread(user_name,20 * sizeof(char),1,fsect);
     fseek(fsect,20 * sizeof(char)+sizeof(int),SEEK_SET);
     fread(password,20 * sizeof(char),1,fsect);

      fclose(fsect); 

      if( c >= 3)
       return 0;
   
     while(1)
      {
        i = 0;
		printf("\n Enter the User Name    :-   ");
        scanf("%s",a);

        printf("\n Enter the Password   :-     "); 
        while(1)
	     {
	  	   ch = getch();
	  	   if(ch == 13)
	  	      break;
	  	   printf("*");
	  	   fflush(stdin);
	       b[i] = ch;
	  	   i++;	  	
	     } 
	    b[i] = '\0'; 
	    fflush(stdin);
 
        if( strcmp(a,user_name) == 0 && strcmp(b,password) == 0)
         return 1;
        else
         {
           count++;
           printf(" \nUSER AUTHENTICATION IS UNSUCCESSFULL \n ACCESS DENIED \n");
           if(count >= 3)
            {
              fsect = fopen("security.dat","rb+");
              if(fsect == NULL)
               {
                 printf("Error in opening the file");
                 getch();
                 exit(0);
               } 	
              fseek(fsect,0,SEEK_SET);
              fwrite(&count,sizeof(int),1,fsect); 
              fclose(fsect); 
              return 0;
            }
         }
      }         
 }
 
 
 
 void security_modify()
  {
  	FILE * fsect;
  	char password[20]; 
    char user_name[20];
    char a[20];
    char b[20];
    char a1[20];
    char b1[20];
    char ch = 0;
    int i = 0;
    
    
  	fsect = fopen("security.dat","rb+");
    if(fsect == NULL)
     {
       printf("Error in opening the file");
       getch();
       exit(0);
      }
            
     fseek(fsect,sizeof(int),SEEK_SET); 
     fread(user_name,20 * sizeof(char),1,fsect);
     fseek(fsect,20 * sizeof(char)+sizeof(int),SEEK_SET);
     fread(password,20 * sizeof(char),1,fsect);

      fclose(fsect); 
      
      printf("\n Enter the current User Name    :-   ");
        scanf("%s",a);

        printf("\n Enter the current Password   :-     "); 
        while(1)
	     {
	  	   ch = getch();
	  	   if(ch == 13)
	  	      break;
	  	   printf("*");
	  	   fflush(stdin);
	       b[i] = ch;
	  	   i++;	  	
	     } 
	    b[i] = '\0'; 
	    fflush(stdin);
	    
	    if( strcmp(a,user_name) != 0 || strcmp(b,password) != 0)
	     {
	     	printf("\n Sorry! incorrect user_name or password \n access denied \n");
	     	return;
	     }
        
		printf("\n Enter the new User Name    :-   ");
        scanf("%s",a1);

        i = 0; ch = 0;
        printf("\n Enter the new Password   :-     "); 
        while(1)
         {
	       ch = getch();
	       if(ch == 13)
 	       break;
 	       printf("*");
	       fflush(stdin);
	       b1[i] = ch;
	       i++;	  	
         }  
	     b1[i] = '\0'; 
         fflush(stdin);
         		     	
  	     fsect = fopen("security.dat","rb+");
         if(fsect == NULL)
          {
            printf("Error in opening the file");
            getch();
            exit(0);
          }
       
        fseek(fsect,sizeof(int),SEEK_SET);
        fwrite(a1,20 * sizeof(char),1,fsect);
        fseek(fsect,20 * sizeof(char)+sizeof(int),SEEK_SET);
        fwrite(b1,20 * sizeof(char),1,fsect);
     
    
  fclose(fsect); 
  	
  	
  }
 
 
 int bin_insert(bnode** head,node n)
  {
  	int imbal;
 	bnode* fp = NULL;
	bnode* p = *head;
	bnode* fya = NULL;
	bnode* ya = p;
	bnode* q;
	bnode* temp;
	bnode* s;
	bnode* hold;
	bnode* link;
	
	
	while(p != NULL)
	 {
	 	if(n.rn == p->rn)
	 	  {
		    return 0;
      	  }
      	 
		if(n.rn < p->rn)
		  q = p->left;
		else
		  q = p->right;
		  
		if(q != NULL) 
		 {
		 	if(q->bf != 0)
		 	 {
		 	 	fya = p;
		 	 	ya = q;
		 	 }
		 	
		 } 
		  
		fp = p;
		p = q;		      	 	
	 	
	 }
	 
	temp = (bnode*) malloc(sizeof(bnode));
	temp->rn = n.rn;
	temp->location = n.location;
	temp->bf = 0;
	temp->left = NULL;
	temp->right = NULL;
	
	 link = *head;
      	 
	 while(link != NULL)
      {
      	 if(link->rn > n.rn)
      	  {
      	    if(link->left == NULL)
      	     {
      	       link->left = temp;
      	       break;
      	     }
		    link = link->left;
          }
		 
		 else
		  {
		  	if(link->right == NULL)
      	     {
      	       link->right = temp;
      	       break;
      	     }
		    link = link->right;	  	
		  	
		  }
		   
     }	
     
     if(link == NULL)
      {
        *head = temp;
        return 1;
      }
      	
     q = temp;
	 
	 if(n.rn < fp->rn) 
	   fp->left = q;
	 else
	   fp->right = q;
	   
	 if(n.rn < ya->rn) 
	    p = ya->left;
     else
	    p = ya->right;
		
     s = p;
	 
	 while(p != q)	
	  {
	  	 if(n.rn < p->rn)
	  	  {
	  	  	p->bf = 1;
	  	  	p = p->left;
	  	  }
	  	 else
	  	  {
	  	  	p->bf = -1;
	  	  	p = p->right;
	  	  }
	  }			   	
      
	 if(n.rn < ya->rn)
       imbal = 1;
	 else
	   imbal = -1;
	   
	 if(ya->bf == 0)
	  {
	  	 ya->bf = imbal;
	  	 return 1;	  	
	  }     	
	  
	 if(ya->bf != imbal) 
	  {
	  	ya->bf = 0;
	  	return 1;
	  }
 	
 	 if(s->bf == imbal)
      {
      	 p = s;
      	 if(imbal == 1)
           right_rotation(ya);
		 else
		   left_rotation(ya);
		   
		 ya->bf = 0;
		 s->bf = 0; 	
      } 	
 	 else
 	  {
 	  	 if(imbal == 1)
 	  	  {
 	  	  	p = s->right;
 	  	  	left_rotation(s);
 	  	  	ya->left = p;
 	  	  	right_rotation(ya);
 	  	  }
 	  	 else
 	  	  {
 	  	  	p = s->left;
 	  	  	ya->right = p;
 	  	  	right_rotation(s);
 	  	  	left_rotation(ya);	  	
 	  	  }
 	  	
 	  	 if(p->bf == 0)
 	  	  {
 	  	  	ya->bf = 0;
		    s->bf = 0;		  
 	  	  }
 	  	 else
 	  	   if(p->bf == imbal)
            {
               ya->bf = -1*imbal;
               s->bf = 0;
            } 	  	
 	  	   else
 	  	    {
 	  	       ya->bf = 0;	
 	  	       s->bf = imbal;	
 	  	    }
 	  	 
	     p->bf = 0;
 	  }
 	 
 	 if(fya == NULL)  
 	    *head = p;
 	 else
	    if(ya == fya->right) 
		  fya->right = p;
		else
		  fya->left = p;
		  
		  
     return 1; 
  	 
  	 
  }
  
  int bin_traverse(bnode* head,int rn)
   {
   	 bnode* link = head;
   	 
   	 if(link == NULL)
   	  return -1;
   	  
   	 while(link != NULL)
	  {
	  	if(link->rn > rn)
	  	 link = link->left;
	  	else
     	   if(link->rn < rn)
		     link = link->right;
		   else
		     return link->location;
		    
		    
      }
      
	  return -1;	 
   }
   
  
 int bin_delete(bnode** head,int rn)
  {
  	 bnode *link = *head;
	 bnode *plink = NULL;
	 bnode *chld = NULL;
	 bnode *ya;
	 bnode *pya;
	 bnode *temp;
	 int check = 0;
	 
	 if(*head == NULL)
	  {
	  	return 0;	  	
	  }
	  
	 if((*head)->rn == rn && (*head)->left == NULL && (*head)->right == NULL)
	  {
	  	*head = NULL;
	  	return 1;	
	  } 
	  
	 while(link) 
	  {
	  	 if(link->rn == rn)
	  	  {
	  	  	check = 1;
	  	  	break;
	  	  }
	  	 plink = link;
	  	 
	  	 if(link->rn > rn)
	  	  link = link->left;
	     else
		  link = link->right;		  	
	  }
	  
  	 if(check == 0)
      {
      	return 0;
      }  	
  	
  	 if(link->right == NULL)
      {
      	chld = link->left;
      	if(link == *head)
      	 {
      	 	*head = (*head)->left;
      	 	goto abc;
     	 }
     	 
      	if(plink->rn > link->rn) 
      	  plink->left = link->left;
	    else
		  plink->right = link->left;
		  
      }
     else
	  {
	  	 if(link->right->left == NULL)
	  	  {
	  	  	chld = link->right;
	  	  	link->right->left = link->left;
	  	  	if(link == *head)
	  	  	 {
	  	  	 	*head = link->right;
	  	  	 	goto abc;
	  	  	 }
	  	  	if(plink->rn > link->rn) 
	  	  	  plink->left = link->right;
	  	  	else
			  plink->right = link->right;  
	  	  }
	  	 else
		  {
		  	bnode* l;
		  	bnode* pl;
			chld = NULL;
			
			l = link->right->left;
			pl = link->right;
			
			while(l->left != NULL)
 		  	 {
 		  	 	pl = l;
 		  	 	l = l->left;
 		  	 }
		  	link->rn = l->rn;
		  	link->location = l->location;
		  	link->bf = l->bf;
		  	link = l;
		  	pl->left = l->right;
		  	rn = pl->rn;
		  } 
     }  
	  	
	free(link); 	
	  	
	abc:  	
	  	
	 link = *head;
	 check = 0;
	 
	 while(link != NULL)
	  {
	  	 if(link == chld)
	  	   check = 1;
		 balance(link);
		 
		 if(link->rn > rn)
           link = link->left;
		 else
		   if(link->rn < rn)
		     link = link->right;
		   else
		     break;
			  
		 if(check == 1)    		 
		  break;
	  } 	
  	
	 plink = NULL;
	 link = *head;
	 pya = NULL;
	 ya = NULL;
	 
	 while(link != NULL) 
	  {
	  	 if(link->bf == -2 || link->bf == 2)
	  	  {
	  	  	ya = link;
	  	  	pya = plink;
	  	  }
	  	
	  	if(link->rn > rn)
	  	  {
	  	  	plink = link;
	  	  	link = link->left;
	  	  }
	  	 else
	  	   if(link->rn < rn)
	  	    {
	  	      plink = link;
	  	  	  link = link->right;
	  	    }
	  	   else
			 break;  
	 }
	 
	 if(ya == NULL)
	  {
	  	return 1;
	  }
	  	
	  	
	temp = NULL;
	
	if(ya->bf == 2)   	
	 {
	 	if(ya->left->bf == 0 || ya->left->bf == 1)
	 	 {
	 	 	chld = ya->left;
	 	 	temp = ya->left;
	 	 	right_rotation(ya);
	 	 	if(ya == *head)
	 	 	  *head = temp;
	 	 	balance(ya);
	 	 	balance(temp);
	 	 	if(pya != NULL)
	 	 	 {
	 	 	 	if(pya->rn > ya->rn)
	 	 	 	  pya->left = temp;
	 	 	 	else
				  pya->right = temp;   
 	 	 	 }
	 	 	goto abc;
	 	 }
	 	
	 	if(ya->left->bf == -1)
	 	 {
	 	 	chld = ya->left->right;
	 	 	temp = ya->left->right;
	 	 	left_rotation(ya->left);
	 	 	balance(ya->left);
	 	 	balance(temp);
	 	 	ya->left = temp;
	 	 	
	 	 	right_rotation(ya);
	 	 	if(ya == *head)
	 	 	  *head = temp;
	 	 	balance(ya);
	 	 	balance(temp);
	 	 	if(pya != NULL)
	 	 	 {
	 	 	 	if(pya->rn > ya->rn)
	 	 	 	  pya->left = temp;
	 	 	 	else
				  pya->right = temp;   
	 	 	 }
	 	 	goto abc; 
	 	 }
    }
	  
	  
	  
  if(ya->bf == -2)   	
	 {
	 	if(ya->right->bf == 0 || ya->right->bf == -1)
	 	 {
	 	 	chld = ya->right;
	 	 	temp = ya->right;
	 	 	left_rotation(ya);
	 	 	if(ya == *head)
	 	 	  *head = temp;
	 	 	balance(ya);
	 	 	balance(temp);
	 	 	if(pya != NULL)
	 	 	 {
	 	 	 	if(pya->rn > ya->rn)
	 	 	 	  pya->left = temp;
	 	 	 	else
				  pya->right = temp;   
 	 	 	 }
	 	 	goto abc;
	 	 }
	 	
	 	if(ya->right->bf == 1)
	 	 {
	 	 	chld = ya->right->left;
	 	 	temp = ya->right->left;
	 	 	right_rotation(ya->right);
	 	 	balance(ya->right);
	 	 	balance(temp);
	 	    ya->right = temp;
	 	 	
	 	 	left_rotation(ya);
	 	 	if(ya == *head)
	 	 	  *head = temp;
	 	 	balance(ya);
	 	 	balance(temp);
	 	 	if(pya != NULL)
	 	 	 {
	 	 	 	if(pya->rn > ya->rn)
	 	 	 	  pya->left = temp;
	 	 	 	else
				  pya->right = temp;   
	 	 	 }
	 	 	goto abc; 
	 	 }
    }  
  	
  } 
  
  
 void balance(bnode* link)
  {
  	 int left = 0;
  	 int right = 0;
  	 
  	 bnode* ltemp = link->left;
  	 bnode* rtemp = link->right;
  	 
  	 while(ltemp != NULL)
  	  {
  	  	if(ltemp->bf == 0 || ltemp->bf == 1)
  	  	 {
  	  	 	left++;
  	  	 	ltemp = ltemp->left;
  	  	 }
  	  	else
  	  	 {
  	  	 	left++;
  	  	 	ltemp = ltemp->right;
  	  	 }
      }
  	  	
     
	 while(rtemp != NULL)
  	  {
  	  	if(rtemp->bf == 0 || rtemp->bf == 1)
  	  	 {
  	  	 	right++;
  	  	 	rtemp = rtemp->left;
  	  	 }
  	  	else
  	  	 {
  	  	 	right++;
  	  	 	rtemp = rtemp->right;
  	  	 }
      }  	  	
  	  	
  	 link->bf = left - right;
	 return;   	  	
  	
  } 
  
  
  void right_rotation(bnode* p)
 {
 	bnode* q;
 	bnode* hold;
 	
 	q = p->left;
 	hold = q->right;
 	q->right = p;
 	p->left = hold;
	 return; 	
 }
 
 
void left_rotation(bnode* p)
 {
 	bnode* q;
 	bnode* hold;
 	
 	q = p->right;
 	hold = q->left;
 	q->left = p;
 	p->right = hold;
	 return; 	
 } 
  
  
  int link_insert(lnode**start,int loc)
   {
   	
   	lnode* temp;
   	lnode *link = *start;
   	
   	temp = (lnode*) malloc(sizeof(lnode));
    temp->data = loc;
    temp->next = NULL;
    
   	if(*start == NULL)
   	 {
   	   *start = temp;   	 	
   	   return 1;
   	 }
   	 
   	while(link->next != NULL )
   	   link = link->next;
		  
	link->next = temp;
	return 1;  	 
   	 
   }  
   
  int link_delete(lnode** start) 
   {
   	  lnode* link = *start;
   	  int loc;
   	  
   	  if(*start == NULL)
        return -1;
        
      if(link->next == NULL) 
	   {
	   	  loc = link->data;
		  free(link);
		  *start = NULL;
		  return loc;
	   } 
	   
	   loc = link->data;
	   *start = link->next;
	   free(link);
	   return loc;	
      		   	
   }
  
  void insert(bnode** head,lnode** start)
  {
  	FILE *fp;
  	int loc,pos;
  	int check,no;
  	st s;
  	node n;
  	char ch;
  	
  	
  	 printf("Enter Student's Name : ");
     fflush(stdin);
     gets(s.name);
     printf("Enter Student's RollNO : ");
     no = 0;
     s.rollno = 0;
      while(1)
	  {
	  	ch = getch();
	  	fflush(stdin);
	  	if(ch>47 && ch<58)
	  	 {
	  	 	no = ch - 48;
	  	 	printf("%d",no);
	  	 	s.rollno = s.rollno*10+no;
	  	 }
	  	else
	  	 {
	  	 	if(ch == 13 && s.rollno != 0)
	  	     break;
	  	 }
	  	
	  } 
     printf("\nEnter Student's Address : ");
     fflush(stdin);
     gets(s.address);
     printf("Enter Student's Marks : ");
     fflush(stdin);
      no = 0;
     s.marks = 0;
      while(1)
	  {
	  	ch = getch();
	  	if(ch>47 && ch<58)
	  	 {
	  	 	no = ch - 48;
	  	 	printf("%d",no);
	  	 	s.marks = s.marks*10+no;
	  	 }
	  	else
	  	 {
	  	 	if(ch == 13 && s.marks != 0)
	  	     break;
			fflush(stdin);
	  	 	
	  	 }
	  	
	  } 
	  
     
     check = bin_traverse(*head,s.rollno);
     if(check >= 0)
     {
     	printf("\n Sorry! Record already exists");
     	getch();
     	return;
     }
     
     loc = link_delete(start);
     
     if(loc < 0)
      {
      	fp = fopen("student.dat","ab+");
        if(fp == NULL)
        {
          printf("Error in opening the file");
          getch();
          return;
        }
        
        fseek(fp,0,SEEK_END);
        pos = (int) ftell(fp);
        fwrite(&s,sizeof(s),1,fp);
        fclose(fp);
      }
     else
      {
      	fp = fopen("student.dat","rb+");
        if(fp == NULL)
        {
          printf("Error in opening the file");
          getch();
          return;
        }
         pos = loc;
        fseek(fp,loc,SEEK_SET);
        fwrite(&s,sizeof(s),1,fp);
        fclose(fp); 
      	
      }
      
     n.rn = s.rollno;
	 n.location = pos; 
     check = bin_insert(head,n);
     
     printf("\n Record added successfully");
	 getch();
	 return;
 }
 
 
 void append(bnode** head)
  {
  	FILE *fp;
  	int pos;
  	int check,no;
  	st s;
  	node n;
  	char ch;
  	
  	
  	 printf("Enter Student's Name : ");
     fflush(stdin);
     gets(s.name);
     printf("Enter Student's RollNO : ");
     no = 0;
     s.rollno = 0;
      while(1)
	  {
	  	ch = getch();
	  	if(ch>47 && ch<58)
	  	 {
	  	 	no = ch - 48;
	  	 	printf("%d",no);
	  	 	s.rollno = s.rollno*10+no;
	  	 }
	  	else
	  	 {
	  	 	if(ch == 13 && s.rollno != 0)
	  	     break;
			fflush(stdin);
	  	 	
	  	 }
	  	
	  } 
	  
     printf("\nEnter Student's Address : ");
     fflush(stdin);
     gets(s.address);
     printf("Enter Student's Marks : ");
     fflush(stdin);
      no = 0;
     s.marks = 0;
      while(1)
	  {
	  	ch = getch();
	  	if(ch>47 && ch<58)
	  	 {
	  	 	no = ch - 48;
	  	 	printf("%d",no);
	  	 	s.marks = s.marks*10+no;
	  	 }
	  	else
	  	 {
	  	 	if(ch == 13 && s.marks != 0)
	  	     break;
			fflush(stdin);
	  	 	
	  	 }
	  	
	  } 
     
     check = bin_traverse(*head,s.rollno);
     if(check >= 0)
     {
     	printf("\n Sorry! Record already exists");
     	getch();
     	return;
     }
     
      	fp = fopen("student.dat","ab+");
        if(fp == NULL)
        {
          printf("Error in opening the file");
          getch();
          return;
        }
        
        fseek(fp,0,SEEK_END);
        pos = (int) ftell(fp);
        
        fwrite(&s,sizeof(s),1,fp);
        fclose(fp);
      
      
     n.rn = s.rollno;
	 n.location = pos; 
     check = bin_insert(head,n);
     
     printf("\n Record added successfully");
	 getch();
	 return;
 }


 void delete(bnode** head,lnode** start)
 {
 	int rn,check,loc;
 	
 	
 	printf("Enter the rollno of the student whose record is to be deleted");
    scanf("%d",&rn);
    
     check = bin_traverse(*head,rn);
     if(check == -1)
     {
     	printf("Sorry! No Record exists with this rollno");
     	getch();
     	return;
     }
     
	 loc = check;
	 
	 check = bin_delete(head,rn);
	    
 	 check = link_insert(start,loc);
 	 
 	 printf("Record deleted successfully");
 	 getch();
 	 return;
 }      
     
     
void close(bnode** head,lnode** start)
 {
 	FILE *fbin;
 	FILE *fe;
 	int check = 1;
 	lnode *llink = *start;
 	
 	fe = fopen("empty.dat","wb+");
    if(fe == NULL)
     {
        printf("Error in opening the file");
        getch();
        exit(0);
     }
     
     fseek(fe,0,SEEK_SET);
     while(llink != NULL)
      {
       fwrite(llink,sizeof(lnode),1,fe);
       llink = llink->next;
      }
     
	 
	 fclose(fe);
	 
	  
     fbin = fopen("bintree.dat","wb+");
    if(fbin == NULL)
     {
        printf("Error in opening the file");
        getch();
        exit(0);
     }
     
    fclose(fbin); 
    preorder(*head);
    exit(0); 
            
}     
     
     
 void preorder(bnode* x)    
  {
  	   FILE *fbin;
	   node n;
		
	   if(x == NULL)
        return;
        
       fbin = fopen("bintree.dat","ab+");
       if(fbin == NULL)
        {
          printf("Error in opening the file");
          getch();
          exit(0);
        } 
	   n.rn = x->rn;
	   n.location = x->location;	
	   fwrite(&n,sizeof(n),1,fbin);  
	   fclose(fbin);
    

      if(x->left!=NULL)
        preorder(x->left);

      if(x->right!=NULL)
        preorder(x->right);
  	
  }   
  
  
void view(bnode* x)
 {
 	FILE *fp;
 	if(x == NULL)
 	 {
 	 	printf("Database is empty");
 	 	return;
 	 }
 	 
 	fp = fopen("student.dat","rb+");
	 	  if(fp == NULL)
           {
             printf("Error in opening the file");
             getch();
             exit(0);
           }
    view_all(x,fp);       
	fclose(fp);	   
		    
 }



 void view_all(bnode* x,FILE* fp)
  {
	   node n;
	   st s;
		
	   if(x == NULL)
        return;

      if(x->left!=NULL)
        view_all(x->left,fp);
        
        
      fseek(fp,x->location,SEEK_SET);   
		  fread(&s,sizeof(s),1,fp);
		  
	   printf("\n STUDENT'S RECORD \n");
       printf("\nStudent Name : %s",s.name);
       printf("\n Student Rollno : %d",s.rollno);
       printf("\n Student Address : %s",s.address);
       printf("\n Student Marks : %f",s.marks);  
        

      if(x->right!=NULL)
        view_all(x->right,fp); 
  }
  	
 void display(bnode *head) 
  {
  	int rn,check,loc,no;
  	FILE *fp;
  	st s;
  	char ch;
  	
     printf("Enter Student's RollNO : ");
     no = 0;
     rn = 0;
      while(1)
	  {
	  	ch = getch();
	  	fflush(stdin);
	  	if(ch>47 && ch<58)
	  	 {
	  	 	no = ch - 48;
	  	 	printf("%d",no);
	  	 	rn = rn*10+no;
	  	 }
	  	else
	  	 {
	  	 	if(ch == 13 && rn != 0)
	  	     break;
	  	 }
	  	
	  } 
	 
    if(rn < 1)
     check = 0;
    else
	 {
	 	loc = bin_traverse(head,rn);
	 	if(loc != -1)
	 	 {
	 	  fp = fopen("student.dat","rb+");
	 	  if(fp == NULL)
           {
             printf("Error in opening the file");
             getch();
             exit(0);
           }
		  fseek(fp,loc,SEEK_SET);   
		  fread(&s,sizeof(s),1,fp);
		  fclose(fp);
          check = 1;
         }
         else
           check = 0;
	
	 } 
	 
     if(check == 0)
      {
      	printf("\n Sorry! record not found");
        getch();
        return;
      }
      
       printf("\n STUDENT'S RECORD \n");
       printf("\nStudent Name : %s",s.name);
       printf("\n Student Rollno : %d",s.rollno);
       printf("\n Student Address : %s",s.address);
       printf("\n Student Marks : %f",s.marks);
       
       getch();
       return;  
  
  }	
  	
  	
 void update(bnode* head) 
  {
  	int rn,check,loc,no;
  	FILE *fp;
  	st s;
  	char ch;
  	
  	printf("Enter Student's RollNO : ");
     no = 0;
     rn = 0;
      while(1)
	  {
	  	ch = getch();
	  	if(ch>47 && ch<58)
	  	 {
	  	 	no = ch - 48;
	  	 	printf("%d",no);
	  	 	rn = rn*10+no;
	  	 }
	  	else
	  	 {
	  	 	if(ch == 13 && rn != 0)
	  	     break;
			fflush(stdin);
	  	 	
	  	 }
	  	
	  } 
    
    if(rn < 1)
     check = 0;
    else
	 {
	 	loc = bin_traverse(head,rn);
	 	if(loc != -1)
	 	 {
	 	 	
	 	 	 printf("\nEnter Student's Name : ");
             fflush(stdin);
             gets(s.name);
             printf("Enter Student's Address : ");
             fflush(stdin);
             gets(s.address);
             printf("Enter Student's Marks : ");
             fflush(stdin);
             no = 0;
             s.marks = 0;
             while(1)
	          {
	  	        ch = getch();
	         	if(ch>47 && ch<58)
	  	         {
	  	 	       no = ch - 48;
	  	 	       printf("%d",no);
	  	 	       s.marks = s.marks*10+no;
	  	         }
	  	        else
	  	         {
	  	           if(ch == 13 && s.marks != 0)
	  	           break;
			       fflush(stdin);
	  	 	     }
	  	
	          } 
             
			 s.rollno = rn;
             
	 	     fp = fopen("student.dat","rb+");
	 	     if(fp == NULL)
              {
                printf("Error in opening the file");
                getch();
                exit(0);
              }
		     fseek(fp,loc,SEEK_SET);   
		     fwrite(&s,sizeof(s),1,fp);
		     fclose(fp);
             check = 1;
            }
        else
          check = 0;
	
	 } 
	 
     if(check == 0)
      {
      	printf("\nSorry! record not found");
        getch();
        return;
      }
      
      printf("\nRecord updated successfully");
	  getch();
	  return;     
       
  }	
  	
  void refresh(bnode** head)
   {
   	  FILE *fbin;
      FILE *fe;
      FILE *fp;
    
     fp = fopen("student.dat","wb+");
     if(fp == NULL)
      {
        printf("Error in opening the file");
        getch();
        exit(0);
      }
      fclose(fp);
    
     fe = fopen("empty.dat","wb+");
     if(fe == NULL)
      {
        printf("Error in opening the file");
        getch();
        exit(0);
      }
       fseek(fe,0,SEEK_SET);
     fclose(fe);

    
	fbin = fopen("bintree.dat","wb+");
    if(fbin == NULL)
     {
        printf("Error in opening the file");
        getch();
        exit(0);
     }
      fseek(fbin,0,SEEK_SET);
     fclose(fbin);
     
     m1(*head);    
     *head = NULL;
     printf("The entire previously existing database has been cleared");
     getch();
   	 return;   	
   	
   }
   
 void m1(bnode* link)
  {
    if(link == NULL)
	 return;
	 
	m1(link->left);
	
	m1(link->right);
	
	free(link);   	
  
  }
  
  	
  	
