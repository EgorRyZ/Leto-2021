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

int read_word(char *word);

int is_space(int c);

struct vertex *bintree(struct vertex *p, char *word);

struct vertex *create_vertex(struct vertex *p, char *word);

void tree_print(struct vertex *p);

int str_compare(char *str1, char *str2);

char *str_copy(char *str);

int str_length(char *str);

int main()
{
	struct vertex *root = NULL;
	char *word = malloc(MAXWORD * sizeof(char));
	while(read_word(word) != EOF)
		root = bintree(root, word);
	tree_print(root);
	
	return 0;
}

int read_word(char *word)
{
	int c;
	char *w = word;
	while(!is_space(c = getchar()))
		*(w++) = c;
	if(c == EOF)
		return EOF;
	*(w++) = '\0';
	return 0;
}

int is_space(int c)
{
	if(c == ' ' || c == '\n' || c == EOF)
		return 1;
	return 0;
}

struct vertex *bintree(struct vertex *p, char *word)
{
	int c;
	if(p == NULL)
		p = create_vertex(p, word);
	else if((c = str_compare(word, p->word)) == 0) 
		p->count++;
	else if(c < 0)
		p->left = bintree(p->left, word);
	else
		p->right = bintree(p->right, word);
	
	return p;
}

struct vertex *create_vertex(struct vertex *p, char *word)
{
	p = malloc(sizeof(struct vertex));
	p->word = malloc(str_length(word) * sizeof(char));
	p->word = str_copy(word);
	p->count = 1;
	p->left = p->right = NULL;
	
	return p;
}

void tree_print(struct vertex *p)
{
	if(p != NULL)
	{
		tree_print(p->left);
        printf("%4d %s\n", p->count, p->word);
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
	char *p = malloc(len * sizeof(char));
	char *t = str;
	while(*t != '\0')
		*(p++) = *(t++);
	*p = '\0';
	return p - len;
}

int str_length(char *str)
{
	int count = 0;
	char *p = str;
	while(*(p++) != '\0')
		count++;
	return count;
}




