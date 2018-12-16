#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct list
{
    char *word;
    struct list *next;
} *less3=NULL, *more3=NULL;

int main(int argc, char const *argv[])
{
    void listInit(const char *);
    void outstd();
    void outinfile(const char *);
    
    listInit(argv[1]);
    outstd();
    outinfile(argv[2]);
    
    return 1;
}




void push1(char *buffer)
{
    struct list *p;

    
    p=more3;
    more3 = (struct list*)malloc(sizeof(struct list));
    more3->next = p;
    
    more3->word = (char*)malloc(sizeof(char)*(strlen(buffer)+1));  //Аллоцируем память
    
    strcpy(more3->word, buffer);
}

void pop1()
{
    struct list *p;
    printf("%s\n", more3->word);
    p = more3;
    more3 = more3->next;
    free(p->word);
    free(p);
    return;
    
}

void outstd()
{
    while (more3 != NULL)
        pop1();
}

void push2(char *buffer)
{
    struct list *p;
    
    p=less3;
    less3 = (struct list*)malloc(sizeof(struct list));
    less3->next = p;
    
    
    
    less3->word = (char*)malloc(sizeof(char)*(strlen(buffer)+1));  //Аллоцируем память
    
   strcpy(less3->word, buffer);
    
}

void pop2(FILE *fp)
{
    struct list *p;
    fprintf(fp,"%s\n", more3->word);
    p = more3;
    more3 = more3->next;
    free(p->word);
    free(p);
    return;
}

void outinfile(const char *path)
{
    FILE *fp;
    
    if ((fp = fopen(path, "w")) == NULL)
    {
        printf("Ошибка открытия файла.\n");
        exit(-3);
    }
    
    while (less3 != NULL)
        pop2(fp);
}

int issep(char c)
{//Проверка, является ли символ разделяющим
    
    if (c == ' ' || c == '\n' || c == '\t')
        return 1;
    return 0;
}

char *getWordfrom(FILE *fp) {
    static char buffer[64];
    int i = 1;
    
    while ( issep(buffer[0] = fgetc(fp)) );
    
    if ( buffer[0] == EOF )
        return NULL;
    
    while ( ! issep(buffer[i] = fgetc(fp)) )
        i++;
    
    buffer[i] = '\0';
    
    return buffer;
}

void listInit(const char *path)
{
  FILE *fp;
  char *temp;
  
  if ((fp = fopen(path, "r")) == NULL)
    {
        printf("Ошибка открытия файла.\n");
        exit(-3);
    }
    temp = getWordfrom(fp);
    while (temp != NULL)
    {
        if (strlen(temp) >=3)
            push1(temp);
        else
            push2(temp);
    }
}




