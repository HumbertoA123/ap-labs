//strlib

int str_len(char *str) {
	int i = 0;

	while(str[i] != '\0') {
		i++;
	}
	
	return i;
}

char* stradd(char *origin, char *addition) {

	int size1 = str_len(origin);
	int size2 = str_len(addition);

	for(int i = 0; i < (size1 + size2); i++) {
		origin[size1 + i] = addition[i];
	}

	return origin;
}

int strfind(char *origin, char *substr) {

	int j = -1;

	for(int i = 0; origin[i] != '\0'; i++) {

		if(substr[j] == '\0') {
			return 1;
		}
		else if(substr[j] == origin[i]) {
			j++;
		}
		else {
			j = -1;
		}

	}

	if(substr[j] == '\0') {
		return 1;
	}

	return 0;
}

