#include <stdio.h>
#include <stdlib.h>
#define MAXWORD 100

struct vertex
{
	int count;
	char *word;
	struct vertex *left;
	struct vertex *right;
};

int read_word(char *word, FILE *fromfile);

int isnt_word(int c);

struct vertex *add_to_tree(struct vertex *p, char *word);

struct vertex *create_vertex(struct vertex *p, char *word);

void tree_print(struct vertex *p);

void delete_vertex(struct vertex **p);

void delete_tree(struct vertex **p);

int str_compare(char *str1, char *str2);

char *str_copy(char *str);

int str_length(char *str);

int main()
{
    FILE *fromfile = fopen("C:/C/Leto2021/rand-text.txt", "r");
	struct vertex *root = NULL;
	char *word = (char *)malloc(MAXWORD * sizeof(char));
	int c;
	do
	{
		c = read_word(word, fromfile);
		root = add_to_tree(root, word);
	}
	while(c != EOF);
	tree_print(root);
	delete_tree(&root);
    
	return 0;
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
        case '’':
        case EOF:
            return 1;
        default:
            return 0;
    }
}

struct vertex *add_to_tree(struct vertex *p, char *word)
{
	int c;
	if(p == NULL)
		p = create_vertex(p, word);
	else if((c = str_compare(word, p->word)) == 0) 
		p->count++;
	else if(c < 0)
		p->left = add_to_tree(p->left, word);
	else
		p->right = add_to_tree(p->right, word);
	
	return p;
}

struct vertex *create_vertex(struct vertex *p, char *word)
{
	p = (struct vertex *)malloc(sizeof(struct vertex));
	p->word = str_copy(word);
	p->count = 1;
	p->left = p->right = NULL;
	
	return p;
}

void delete_vertex(struct vertex **p)
{
    struct vertex *t = *p;
    free((*p)->word);
    free(*p);
    *p = NULL;
}

void delete_tree(struct vertex **p)
{
    if((*p)->left != NULL)
        delete_tree(&((*p)->left));
    if((*p)->right != NULL)
        delete_tree(&((*p)->right));
    delete_vertex(p);
}

void tree_print(struct vertex *p)
{
	if(p != NULL)
	{
		tree_print(p->left);
        printf(" %s (%d) ", p->word, p->count);
        tree_print(p->right);
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




