#include<stdio.h>
#include<stdlib.h>
#include<string.h>

double vald;
float  valf;
char   valc;
class D myD;

struct mystruct {
   float f;
   double d;
   long l;
   short s;
   int i;
   char c;
};

	/* function prototype */
float total (float,float) ;
float product(float , float  ) ;

	/* class with overloaded methods */
class A {
int a, aa;
int aaa;
	/* add parameters */
   void add(int a, int aa) {
      printf("%d\n", a+ aa);
   }
	// add class variables
   void add() {
      printf("%d\n", a + aa);
   }
};

	// simple function outside of a class 
float product(float a, float b) {
   return( a*b );
}


	/* class with no methods */
class B {
long b;
short c;
};

	/* class with no variables */
class C{
   void add(int a, int b) {
      printf("%d\n", a+b);
   }
	// create a class inside the method
   void makeObject() {
      int a, b;
      class B myB1;
         a = 7;
         myB1.b = 3;
         myB1.c = 10;
         printf("output should be 20: %d", a + (int)myB1.b +myB1.c); 

		/* call the method inside the class */
         ptintf("output should be 3: ");
         a = 1; b = 2;
         add(a, b);}};

class D
{
int a,b, c;
   void seta(int val ) {
      a = val;
   }
   void setb(int val ){
      b = val;
   }
   void setc (int val) {
      c = val;
   }
   int geta() {
      return(a);
   }
   int getb (){
      return( b);
   }
   int getc () {
      return( c );
   }
   void math() {
   int result;
      result = a + b* c /a;
   }
};

class
E {
   float
      abc = 1.2;

   struct mystruct *  method()
   {
   struct mystruct *ptr;
      int z = 3;
      int kk;
      z++;
      printf("output should be 4 1.200000 : %d %f\n", z, abc);

      ptr = malloc(sizeof(struct mystruct));
      return(ptr);
   };
   
};


