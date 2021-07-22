#include <stdio.h>
#include <stdlib.h>
#define Maxsize 100

typedef int Data;

typedef struct {
    int n;
    int size;
    Data * a; 
}Stack;

Stack * stack_create(int size)
{
	Stack *stack = malloc(sizeof(Stack));
	stack->a = malloc(sizeof(Data) * size);
	stack->size = size;
	stack->n = 0;
	return stack;
}

void stack_push(Stack * s, Data x)
{
	if(s->n <= s->size)
		s->a = realloc(s->a, (++(s->size)) * sizeof(Data));
	s->a[(s->n)++] = x;
}

Data stack_pop(Stack * s)
{
	if(s->n > 0)
		return s->a[--(s->n)];
	else
	{
		//printf("Stack underflow");
		return 0;
	}
}

Data stack_get(Stack * s)
{
	return s->a[s->n - 1];
}

void stack_print(Stack * s)
{
	if(s->n == 0)
		printf("Empty stack");
	else
	{
		for(int i = 0; i < s->n; i++)
			printf("%d ", s->a[i]);
	}
	printf("\n");
}

int stack_size(Stack * s)
{
	return s->n;
}

int  stack_is_empty(Stack * s)
{
	if(s->n == 0)
		return 1;
	else
		return 0;
}

void stack_clear(Stack * s)
{
	free(s->a);
}

void stack_destroy(Stack * s)
{
	free(s->a);
	free(s);
	s = NULL;
}

int Calculate(char *s)
{
	Stack *stack = stack_create(Maxsize);
	char *p = s;
	
	while(*p != '\0')
	{
		char x;
		switch(*p)
		{
			case '+':
				stack_push(stack, stack_pop(stack) + stack_pop(stack));
				break;
			case '-':
				x = stack_pop(stack);
				stack_push(stack, stack_pop(stack) - x);
				break;
			case '*':
				stack_push(stack, stack_pop(stack) * stack_pop(stack));
				break;
			case '/':
				x = stack_pop(stack);
				stack_push(stack, stack_pop(stack) / x);
				break;
			default:
				stack_push(stack, *p - '0');
				break;
		}
		p++;
		stack_print(stack);
	}
	
	return stack_pop(stack);
}

int main()
{
	char *s = (char *)malloc(sizeof(char) * Maxsize);
	scanf("%s", s);
	
	printf("%d", Calculate(s));
	return 0;
}