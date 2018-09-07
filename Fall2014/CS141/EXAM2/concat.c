char* concat(char *a, char *b){
	
	int count = 0;
	int count2 = 0;
	while(a[count] != '\0'){

		count++;

	}

	while(b[count2] != '\0'){

		count2++;
	}

	int total = count + count2;

	char *out = malloc(total*(sizeof(char)));

	count = 0;
	count2 = 0;

	while(a[count] != '\0'){

		out[count] = a[count];

		count++;

	}

	while(b[count2] != '\0'){

		out[count2 + count] = b[count2];

		count2++;
	}

	return out;
}