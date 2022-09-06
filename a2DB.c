#include <stdio.h>
#include <ctype.h> // for tolower
#include <string.h>
#include <stdlib.h>

#define SIZE 30
#define fieldLength 200

#define optimalH 120
#define optimalL 80

struct db_type
{
   char name[fieldLength];
   
   int age;

   float high;
   float low;
   float risk;
};

 

char prompt_menu(void);
void enterNew(struct db_type * pArr[]);  
void init_list(struct db_type * pArr[]); 
void displayDB(struct db_type * pArr[]);   
void sort(struct db_type * pArr[]);
void swap(struct db_type * pArr[]); 
void removeRecord(struct db_type * pArr[]);
void clearDB(struct db_type * pArr[]);



int main(int argc, char *argv[])
{
    
    struct db_type * db_pArr[SIZE];  // main db storage

    init_list(db_pArr);  // set to NULL
    
    char choice;
    for(; ;){
      choice = prompt_menu();
      switch (choice)
      {
         case 'n': enterNew(db_pArr); break;
         case 'd': displayDB(db_pArr); break;
        
         case 's': sort(db_pArr); break;
	   
         case 'c': clearDB(db_pArr); break;  
        
         case 'p': swap(db_pArr); break;
         case 'r': removeRecord(db_pArr);break;
         
         case 'q': exit(1); // terminate the whole program
       }
	
     }
     return 0;
}


char prompt_menu(void){
  char s[80];
  while(1){
    printf("\n-----------------------------------------------------------------\n");
    printf("|    %-20s","(N)ew record");
    printf("%-20s","(R)emove record");
    printf("Swa(p) records\t|\n");
    printf("|    %-20s","(S)ort database");
    printf("%-20s","(C)lear database");
    printf("(D)isplay db\t|\n");
  
   // printf("|    %-20s","(L)oad disk");
   // printf("%-20s","(W)rite disk");
   // printf("(E)mpty disk\t|\n");
  
   
    printf("|    %-20s","(Q)uit");
    printf("*Case Insensitive*\t\t\t|\n");
    printf("-----------------------------------------------------------------\n");
    printf("choose one: ");
  
    fgets(s,50, stdin); // \n added
    //scanf("%s", s);  
    if (strlen(s) == 2 && strchr("edlsuqrcwnvpr", tolower(*s))) 
       return tolower(*s); // s[0], return the first character of s  
    //else
    printf("not a valid input!\n");
	 
 }
}

void init_list(struct db_type *pArr[])
{
  int t;
  for (t = 0; t < SIZE; t++)
  {
    pArr[t] = NULL;
  }
}

void clearDB(struct db_type *pArr[])
{
  char c3[3];
  printf("are you sure to clear db? (y) or (n)? ");

  fgets(c3, 3, stdin);

  // complete the function by calling init_list();
  if (c3[0] == 'y')
  {
    init_list(pArr);
  }
}

/* input items into the db */
void enterNew(struct db_type *pArr[SIZE])
{
  // create space in memory for new struct and go to next avaliable entry in list
  int i = 0;
  struct db_type *newP = malloc(sizeof(struct db_type));
  while (i < SIZE && pArr[i] != NULL)
  {
    i++;
  }
  if (i < SIZE)
  {

    //prompt user for info to enter
    char name[fieldLength];
    int age;
    float highBP;
    float lowBP;
    float risk;
    printf("name: ");              //note you cant use scanf for name since it will stop reading on whitespace
    fgets(name, fieldLength, stdin); //fgets adds \n at the end so remove it
    name[strlen(name) - 1] = '\0';
    printf("age: ");
    scanf("%d", &age);
    printf("high bp: ");
    scanf("%f", &highBP);
    printf("low bp: ");
    scanf("%f", &lowBP);
    getchar();

    //entering patient info (except risk factor)
    strcpy(newP->name, name);
    newP->age = age;
    newP->high = highBP;
    newP->low = lowBP;
    //calculate and enter risk
    if (highBP <= optimalH && lowBP <= optimalL)
    {
      risk = 0;
    }
    else if ((highBP <= optimalH || lowBP <= optimalL) && ((highBP - optimalH) <= 10 || (lowBP - optimalL) <= 10))
    {
      risk = 1;
    }
    else if (((highBP - optimalH) <= 10) && ((lowBP - optimalL) <= 10))
    {
      risk = 2;
    }
    else if ((highBP <= optimalH || lowBP <= optimalL) && ((highBP - optimalH) <= 20 || (lowBP - optimalL) <= 20))
    {
      risk = 3;
    }
    else if (((highBP - optimalH) <= 20) && ((lowBP - optimalL) <= 20))
    {
      risk = 4;
    }
    else
    {
      risk = 5;
    }
    if (age > 50)
    {
      if (risk > 0)
      {
        risk += 0.5;
      }
    }
    newP->risk = risk;

    //adding new patient to list
    pArr[i] = newP;
  }
}

/* remove an existing item from the db */
void removeRecord(struct db_type *pArr[])
{
  char nameR[fieldLength];
  printf("enter full name to remove: ");
  fgets(nameR, fieldLength, stdin);
  nameR[strlen(nameR) - 1] = '\0';
  //have to use fgets since scanf does not work with whitespaces (such as ' ')

  //remove name if possible
  int i = 0;
  int removed = 0;
  while (i < SIZE && pArr[i] != NULL)
  {
    if (strcmp(pArr[i]->name, nameR) == 0)
    {
      pArr[i] = NULL;
      removed = 1;
      break;
    }
    i++;
  }

  //display result to user
  if (removed)
  {
    //push back all enteries after removed one by 1
    while (i + 1 < SIZE && pArr[i + 1] != NULL)
    {
      pArr[i] = pArr[i + 1];
      i++;
    }
    pArr[i] = NULL; //to elimnate the duplicate entry by pushing evrything back 1 (last entry will be a dup)
    printf("record [%s] removed successfully.\n", nameR);
  }
  else
  {
    printf("record not found\n");
  }
}

/* display all records. Generate output with the same formaing as the sample output 
 use \t to align well
*/
void displayDB(struct db_type *pArr[])
{
  int i = 0;
  printf("===============================\n");
  while (i < SIZE && pArr[i] != NULL)
  {
    printf("\nname:\t%s\nage:\t%d\nbp:\t%.2f  %.2f\nrisk:\t%.1f\n", pArr[i]->name, pArr[i]->age, pArr[i]->high, pArr[i]->low, pArr[i]->risk);
    i++;
  }
  printf("========== %d records ==========\n\n", i);
}

/* swap the adjacent records */
void swap(struct db_type *pArr[])
{
  int i = 0;
  while (i + 1 < SIZE && (pArr[i] != NULL && pArr[i+1] != NULL)){
    struct db_type *temp = pArr[i];
    pArr[i] = pArr[i+1];
    pArr[i+1] = temp;
    i= i+2;
  }
}

// sort the record, either by name or risk factor, prompt use for choice
void sort(struct db_type *pArr[]) //sort using buble sort
{

  printf("sort by name (n) or risk (r)? ");
  char c[3];
  fgets(c, 3, stdin);

  //find out which index is the last non null entry at
  int n = 0;
  while (n < SIZE && pArr[n] != NULL){
    n++;
  }

  //sort using bubble sort
  if (c[0] == 'n')
  {
    int i;
    for (i = 0; i <= n - 2; i++)
    {
      int j;
      for (j = n - 1; j >= i + 1; j--)
      {
        if (strcmp((pArr[j] -> name), (pArr[j-1] -> name)) < 0){
          struct db_type *temp = pArr[j];
          pArr[j] = pArr[j-1];
          pArr[j-1] = temp;
        }
      }
    }
  }
  else if (c[0] == 'r')
  {
    int i;
    for (i = 0; i <= n - 2; i++){
      int j;
      for (j = n - 1; j >= i + 1; j--){
        if ((pArr[j] -> risk) < (pArr[j-1] -> risk)){
          struct db_type *temp = pArr[j];
          pArr[j] = pArr[j-1];
          pArr[j-1] = temp;
        }
      }
    }
  }

}
