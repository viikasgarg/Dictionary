#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define WORDLEN 50
#define MEANLEN 300

struct node {
    char word[WORDLEN];
    char meaning[MEANLEN];
    struct node *next;
};
typedef struct node NODE;

NODE *HEAD;
int no_words = 0;

void loadDict(char *filename){
/*dictionary to load data from text file */
    char line[WORDLEN+MEANLEN];
    char delimiter[] = "\t\t";
    FILE *fl = fopen(filename,"r");
    NODE *wordnode;
    while(fgets(line,sizeof(line),fl) != NULL) {
        wordnode = (NODE *) malloc(sizeof(NODE));
        strcpy(wordnode->word, strtok(line,delimiter));
        strcpy(wordnode->meaning, strtok(NULL,delimiter));
        wordnode->next = HEAD;
        HEAD = wordnode;
        no_words++;
    }
    return;
}

void saveDict(){
    /* place for persistent storage */
    char filename[50];
    printf("Please Enter Filename : ");
    fflush(stdin);
    scanf("%s",filename);
    NODE *TEMP = HEAD;
    FILE *fl = fopen(filename,"w");
    while(TEMP!= NULL){
        fprintf(fl,"%s\t\t%s\n",TEMP->word,TEMP->meaning);
        TEMP = TEMP->next;
    }
    fclose(fl);
}

void insertWord(){
    /* insert word in wordlist */
    char word[WORDLEN];
    char meaning[MEANLEN];

    printf("Word: ");
    fflush(stdin);
    scanf("%s",word);

    printf("Meaning: ");
    fflush(stdin);
    scanf("%s",meaning);
    NODE *wordnode = (NODE *) malloc(sizeof(NODE));
    strcpy(wordnode->word,word);
    strcpy(wordnode->meaning,meaning);
    wordnode->next = HEAD;
    HEAD = wordnode;
    no_words++;
}

void searchWord(){
/* search word in wordlist */
    char word[WORDLEN];
    NODE *TEMP = HEAD;

    printf("Enter the word to search: ");
    fflush(stdin);
    scanf("%s",word);
    while(TEMP!= NULL){
        if (strcmp(word,TEMP->word) == 0){
            printf("Meaning: %s\n",TEMP->meaning);
            return;
        }
        TEMP = TEMP->next;
    }
    printf("Searched word %s not found in dictionary",word);
    return;
}

void printDic(){
/* search word in wordlist */
    char word[WORDLEN];
    NODE *TEMP = HEAD;

    int count=1;
    printf("*********************************************\n");
    if(no_words > 0){
        printf("Count) Word : Meaning\n");
    }
    while(TEMP!= NULL && count<=no_words){
        printf("%d) %s : %s\n",count++,TEMP->word,TEMP->meaning);
        TEMP = TEMP->next;
    }

    if(no_words <= 0) {
        printf("Dictionary is Empty :( \n");
    }
    printf("*********************************************\n");
    return;
}

void about(){
    static char const about_text[] = "\n\
    *********************************************************\n\
    Dictionary: This is simple linked list based dictionary  \n\
    developed by Reema Garg as MCA Data Structure Project \n \
    *********************************************************\n\n";
    printf("%s",about_text);
}

void main(int argc, char *argv[]){
    static char const menu[] = "\n\
    *********************************************\n\
    Dictionary: Please select following options: \n\
    1) To insert Word in dictionary \n\
    2) To search word in dictionary \n\
    3) Print dictionary \n\
    4) About Project \n\
    5) Save Data and exit \n\
    *******************************************\n\n";
    int option;
    if(argc < 1){
        printf("\nUSAGE: prompt> dictionary datafile\n");
        exit(-1);
    }
    else{
        loadDict(argv[1]);
    }
    while(1){
        printf("%s",menu);
        fflush(stdin);
        scanf("%d",&option);
        switch(option){
            case 1:
                insertWord();
                continue;
            case 2:
                searchWord();
                continue;
            case 3:
                printDic();
                continue;
            case 4:
                about();
                continue;
            case 5:
                saveDict();
                exit(0);
            default:
                printf("\n Please select only from above options\n");
        }
    }
}
