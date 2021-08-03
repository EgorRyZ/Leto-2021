#include <stdio.h>
#include <stdlib.h>

#define HASHSIZE 101
#define MAXWORD 100

struct node
{
    char *word;
    struct node *next;
};

struct node *hashtab[HASHSIZE];

unsigned int hash(char *word);

struct node *creat_node(struct node *p, char *word);

struct node *add_to_list(struct node *p, char *word);

void print_list(struct node *p);

void print_tab();

void delete_node(struct node **p);

void delete_list(struct node **p);

void delete_tab();

int read_word(char *word, FILE *fromfile);

int isnt_word(int c);

int str_compare(char *str1, char *str2);

char *str_copy(char *str);

int str_length(char *str);

int main()
{
    FILE *fromfile = fopen("C://C/Leto2021/prjct2/rand-text.txt", "r");
    char *word = (char *)malloc(sizeof(char) * MAXWORD);
    int c;
    do
    {
        c = read_word(word, fromfile);
        unsigned int hsh = hash(word);
        hashtab[hsh] = add_to_list(hashtab[hsh], word);
    }
    while(c != EOF);
    
    print_tab();
    delete_tab();
    free(word);
    fclose(fromfile);
    return 0;
}

unsigned int hash(char *word)
{
    unsigned int t, h = 0;
    while((t = *(word++)) != '\0')
        h += t;
    return h % HASHSIZE;
}

struct node *creat_node(struct node *p, char *word)
{
    p = (struct node *)malloc(sizeof(struct node));
    p->word = str_copy(word);
    p->next = NULL;
    return p;
}

struct node *add_to_list(struct node *p, char *word)
{
    if(p == NULL)
        p = creat_node(p, word);
    else if(str_compare(word, p->word) != 0)
        p->next = add_to_list(p->next, word);
    
    return p;
}

void print_list(struct node *p) 
{
    if(p->next != NULL)
    {
        printf(" %s ", p->word);
        print_list(p->next);
    }
    else
        printf(" %s ", p->word);
}

void print_tab()
{
    for(int i = 0; i < HASHSIZE; i++)
        if(hashtab[i] != NULL)
        {
            printf("\n----------------------", i);
            printf("\nHASH : %d\n", i);
            print_list(hashtab[i]);
        }
}

void delete_node(struct node **p)
{
    free((*p)->word);
    free(*p);
    *p = NULL;
}

void delete_list(struct node **p)
{
    struct node *t = NULL;
    while((*p)->next != NULL)
    {
        t = (*p)->next;
        delete_node(p);
        *p = t;
    }
    delete_node(p);
}

void delete_tab()
{
    for(int i = 0; i < HASHSIZE; i++)
        if(hashtab[i] != NULL)
            delete_list(&hashtab[i]);
}

int read_word(char *word, FILE *fromfile)
{
	int c;
	while(isnt_word(c = getc(fromfile)))
        if(c == EOF)
            return EOF;
	
	do
 		*(word++) = c;
    while(!isnt_word(c = getc(fromfile)));
    *word = '\0';
    
	if(c == EOF)
		return EOF;
	return 0;
}

int isnt_word(int c)
{
    switch(c)
    {
        case ' ':
        case '\n':
        case '\t':
        case '.':
        case ',':
        case '?':
        case '!':
        case '\'':
        case '\"':
        case ';':
        case '-':
        case ':':
        case '\\':
        case '/':
        case '‘':
        case '’':
        case EOF:
            return 1;
        default:
            return 0;
    }
}

int str_compare(char *str1, char *str2)
{
	while(*str1 == *str2)
	{
		if (*str1 == '\0')
            return 0;
		str1++;
		str2++;
	}
    return *str1 - *str2;
}

char *str_copy(char *str)
{
	int len = str_length(str);
	char *p = (char *)malloc((len + 1) * sizeof(char));
	while(*str != '\0')
		*(p++) = *(str++);
	*p = '\0';
	return p - len;
}

int str_length(char *str)
{
	int count = 0;
	while(*(str++) != '\0')
		count++;
	return count;
}





