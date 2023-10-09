# règle implicite
%: %.c
	gcc -Wall -o $@ $@.c
	
# règles spécifiques
projet: projet.c
	gcc -Wall -o $@ $@.c -lm