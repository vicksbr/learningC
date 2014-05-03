#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person { 

	char *name;
	int  age; 
	int  height;
	int  weight;

}Person;	

typedef struct Person person;




person *Person_Create(char *name,int age,int height,int weight) { 

	struct Person *who = malloc(sizeof(struct Person));
	assert(who != NULL);

	who->name = strdup(name);
	who->age  = age;
	who->height = height;
	who->weight = weight;

	return who;

}

void Person_print(struct Person *who) {

	printf("\tName: %s\n", who->name);
    printf("\tAge: %d\n", who->age);
    printf("\tHeight: %d\n", who->height);
    printf("\tWeight: %d\n", who->weight);

}


int main(int argc, char *argv[]) { 


	struct Person *joe = Person_Create(
			"Joe Alex", 32, 64, 140);
	struct Person *frank = Person_Create(
            "Frank Blank", 20, 72, 180);


	printf("Joe is at memory location %p:\n", joe);
	Person_print(joe);

	printf("Frank is at memory location %p:\n", frank);
    Person_print(frank);

    
	int *pointer[] = {10,20,30};
	int x = 10;
	//pointer = &x;
	//*pointer = 20;
	
	printf("valor %d:\n",*(pointer+2));
	//printf("valor do ponteiro é %d\n",*pointer);
	printf("o valor da variavel é %d\n",x);




	return 0;


}