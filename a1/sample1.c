
struct A {
	int a;
	
}
int a(int b);~~void print1(int a) {
		// print parameter - local to the function
      printf("output should be 1: %d\n", a);
   }
void print2() {
		// create a local variable
      int a = 2;
		// print local variable
      printf("output should be 2: %d\n", a);
   }
void print3() {
		// there is a class variable named a so
		// assign value to it and print the class variable
      a = 3;
      printf("output should be 3: %d\n", a);
   }

struct B {
	double ar;
	float test;
	
}
void print4() {
		// there is no class variable named a so print global variable
      printf("output should be 4: %d\n", a);
   }
