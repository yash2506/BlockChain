//Group members:
//name: yashkumar barot student id: 991494011
//name: bimal patel student id: 991480242
//name: vishvakumar mavani student id: 991497190
//name: chintan modi student id: 991491801

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>

//structre for node creation
struct node
{
    char data[25];
    int prevHash;
    unsigned int hash;
    char timestamp[25];
    struct node *next;

};

//hash function given by Prof.Jenell
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    // adding extra () to supress CLion warning messages about
    // using the "result of an assignment as a condition w/o parentheses"
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

int main()
{
    struct node * newnode;
    struct node * start = '\0';
    struct node * t;
    int op;
    int values = 2598235;

    //it will run once and create a node with prevhash = 0.
    do
    {
        newnode = (struct node *) malloc( sizeof(struct node) );
        printf("Enter a data for block\n");
        gets(newnode->data);
        newnode->prevHash = 0;
        time_t current_time = time(NULL);
        struct tm *tm = localtime(&current_time);
        strftime(newnode->timestamp, sizeof(newnode->timestamp), "%c", tm);
        unsigned char temp[100];
        sprintf(temp,"%s%s%x",newnode->data,newnode->timestamp,newnode->prevHash);
        newnode->hash = hash(temp);

        newnode->next = '\0';
        start = newnode;



    }while (1 == 2);

  while(1)
    {
        printf("\nBlock Chain Operations \n");
        printf("\n 1. Add New Block To Chain");
        printf("\n 2. View the Chain");
        printf("\n 3. Check Chain Validity");
        printf("\n 4. Search For A Block ");
        printf("\n 5. Mine A Block");
        printf("\n 0. Exit");
        printf("\n Select you option:\n");
        scanf("%d",&op);

        switch(op)
        {
            //To exit program
            case 0:
                while(start)
                {
                    t = start;
                    start = start->next;
                    free(t);
                }
                printf("Just wanna say...Thank you jenell.\nIt was a really nice semester.");
                exit(0);
            //To create a new node
            case 1:

                newnode = (struct node *) malloc( sizeof (struct node));
                printf("Enter a data for block\n");
                fflush(stdin);
                gets(newnode->data);
                time_t current_time = time(NULL);
                struct tm *tm = localtime(&current_time);
                strftime(newnode->timestamp, sizeof(newnode->timestamp), "%c", tm);
                unsigned char temp[100];
                sprintf(temp,"%s%s%x",newnode->data,newnode->timestamp,newnode->prevHash);
                newnode->hash = hash(temp);

                newnode->next = '\0';
                t = start;
                while(t->next)
                {
                    t = t->next;
                }
                newnode->prevHash = t->hash;
                t->next = newnode;
                printf("New block has been added successfully\n");
                break;
            //To print out all nodes of chain
            case 2:
                t = start;
                int i = 0;
                while (t)
                {
                    i++;
                    printf("\nBlock %d %x",i,t->hash);
                    printf("\n\tData: %s\n\tPrevious Hash: %x\n\tTimeStamp: %s",t->data,t->prevHash,t->timestamp);
                    printf("\n\n");
                    t= t->next;
                }
                break;
                //To validate blocks in chain.
                //Is there any block whose current hash is not matching with next node prevhash then it will print out with reason.
            case 3:

                t = start;
                int j = 0;
                while (1)
                {
                    j++;
                    if(t->hash == t->next->prevHash){
                        printf("\nBlock %d & Block %d are valid Blocks.\nCheck details Below\nblock %d hash: %x || block %d prevhash: %x\n",j,j+1,j,t->hash,j+1,t->next->prevHash);

                    }else{
                        printf("\nBlock %d are not valid %d block prevhash code.\nCheck details below"
                               "\n\tblock %d hash: %x || block %d prevhash: %x\n",j,j+1,j,t->hash,j+1,t->next->prevHash);
                        printf("Reason:=>  Hash code of current block is matching with hash code of next block");
                    }
                    t= t->next;
                    if(t->next == NULL){
                        break;
                    }
                }
                printf("\nBlock verification is completed\n");
                break;
            //To search a block with its data
            //Enter a data of previously created block to search.
            case 4:

                t = start;

                char data[50];
                fflush(stdin);
                printf("Enter a data to search.\n");
                gets(data);
                int check = 0;
                while (t != NULL)
                {
                    if ( strcmp(t->data,data) == 0) {
                        check = 1;
                        printf("Block found.\n");
                        break;
                    }
                    t = t->next;
                }
                if(check == 0)
                   printf("Block didnt found.\n");
                break;

            //It will mine new block in chain with out any data in it.
            case 5:
                newnode = (struct node *) malloc( sizeof (struct node));
                strftime(newnode->timestamp, sizeof(newnode->timestamp), "%c", tm);
                strcpy(temp,"");
                values += 15;
                char str[100];
                itoa(values,str,25);
                sprintf(temp,"%s%s%x",str,newnode->timestamp,newnode->prevHash);
                newnode->hash = hash(temp);
                strcpy(newnode->data,"");
                newnode->next = '\0';
                t = start;
                while(t->next)
                {
                    t = t->next;
                }
                newnode->prevHash = t->hash;
                t->next = newnode;
                printf("New block is mined successfully in chain.");
                break;

            //In case user entered unavailable option Then this default case will fired.
            default:
                printf("Please enter a valid number for operation.\n");
                break;
        }
    }



}