#include <stdio.h>

typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;

typedef enum {ERROR = 0, OPERATOR, VALUE, EOLN, QUIT, HELP} tokenType;

typedef struct tokenStruct
{
	tokenType type;
	char      op;
	int       val;
	struct tokenStruct* down;

} TOKEN;

void pushC(TOKEN** head, char in);

void pushV(TOKEN** head, int in);

void pop(TOKEN** head);

int isSEmpty(TOKEN* head);

char frontO(TOKEN* head);

int frontV(TOKEN* head);

int eval(int x, char op, int y);

void popAndEval(TOKEN** operators, TOKEN** values);
