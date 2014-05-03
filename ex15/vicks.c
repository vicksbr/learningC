#include <stdio.h>

int main(int argc, char *argv[]) {

	int x[] = {10,20,30};
	char *y[] = {"tempo","dinheiro","foda"}; 

	char teste = 'A';
	char *p_teste = "Palavra complexa";


	printf("%d\n",x[0]);
	printf("%s\n",y[0]);

	int *z; 
	
	z = x;

	printf("%d\n",*z);
	printf("%d\n",*(z+1));
	printf("%d\n",*(z+2));


	printf("%d\n",z[1]);

	for (z = x; (z-x) < 3; z++)
		printf("%d -",*z);


	int *a; 
	int *b;
	int c = 60;

    b = &c;
	*b = 80;
	a = b;

	printf("%d\n",*a);

	char *pp;
	for (pp = p_teste; (pp-p_teste) < 17; pp++) { 

		printf("%c",*pp);

	}


	return 0;


}