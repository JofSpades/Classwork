#include <stdio.h>
#include <stdlib.h>

int main(){

char buf[200];

char *word1 = "Holy"; 

char *word2 = "Moly";

char *word3 = "\n";

sprintf(buf, "%s%s%s", word1, word3, word2); 

printf("%s\n", buf);

}

