#include <iostream>
#include "classes.h"

using namespace std;

void initVariables() {
    int a1; //Unint
    int a2 = 0; //Copy init //Avoid this type init
    int a3(5); //direct init
    std::string s2("C++"); //direct init

    char d1[8]; //Uninit
    char d2[8] = {"abcd"}; //Copy init
    char d3[8] = {'a','b','c','d'}; //Aggreagate init(also copy)

    //Uniform init (C++11)

    int b1{}; //Value init
    int b3{5}; //Direct init

    char e1[8]{};
    char e2[8]{"Hello"};

    int *p1 = new int{};

    char *p2 = new char[8]{};

    //char *p3 = new char[8]{"Hello"}; //TODO ask about

    //Preventing narrowing conversion

    float f1{};
    //int i1{f1}; Compiler gives error

    //Use uniform init when use user defined types mostly
    //It forces init
    // It can be used for array types with direct init
    //It prevents narrowing conversions

}

void reference(){
    int x = 10; //Referent

    int &ref = x ; //Reference

    ref = 6;

    cout << "x:" << x << " Address :" << &x << endl;
    cout << "ref:" << ref << " Address :" << &ref << endl;

    //Reference must be init when it is created
    // int &ref; // Gives compiler error
    // Cannot be null
    // Point same variable all its lifetime
    // More memory efficient than pointer
    // No dereference required like pointer

}


void constQualifier(){

    //Cannot be modified
    //Must be init

    const int CHUNK_SIZE = 512;
    //int *ptr = &CHUNK_SIZE; // Cannot be compiled
    const int *ptr = &CHUNK_SIZE;
    // *ptr = 1; WRONG

    int x = 10;
    ptr = &x; // Change address

    const int *const ptr2 = &CHUNK_SIZE;
    //ptr2 = &x; // WRONG because pointer is constant address of pointer cannot be changed

    int *const ptr3 = &x;

    *ptr3 = 7;

    int y = 5;

    //ptr3 = &y; WRONG

    const int &ref = y;
    //ref = 8; WRONG

}

void autoUsage(){

    // Must be init
    // Can be used with functions to auto infer types
    // C++11

    auto i = 10;
    auto j = 5;
    auto sum = i + j;
    auto sum2 = i + 13.4f; //Largest type is used for auto

    const int x = 10;
    auto  var = x; // New variable can be non-constant
    const auto  var2 = x; // Ensure to be constant use constant with auto

    auto &var3 = x;  // Reference is inferred as constant when variable is constant

    auto *ptr = &x;  // For pointer address of can be changed but deferenced value cannot be changed as original value

    //auto list {1,2,3,4}; Uniform init cannot be used with auto when vectoral types are initiliazed

    auto list = {1,2,3,4}; // Correct way

}

void rangeBasedForLoops(){

    // No index usage
    // Prevent access to beyond the size of array
    // No control over iteration


    int arr[] = {1,2,3,4,5};
    for (auto x : arr) { //Create copy of each element avoid that usage
        cout << x << " ";
    }
    cout << endl;
    for (auto &x : arr) { //Use with a referencing prevents copying
        cout << x << " ";
    }
    cout << endl;

}

int add(int a, int b) {
    return a + b;
}
double add(double a, double b) {
    return a + b;
}

extern "C" float add(float a,float b) {
  return  a + b;
}
void functionOverloading() {

    // Static polymorphism ( compile time )
    // Same function name but different input types
    // Return type is ignored
    // For member functions qualifiers participate in overload
    // For pointers and reference arguments qualifiers participate in overload
    // Name mangling(generating unique name by compiler) is used for function overloading

    auto sum1 = add(2,4);
    auto sum2 = add(2.3,4.5);


    // extern "C"

    // Compiler directive allows C++ functions to be called from C or other languages , it is applied on global functions and variables
    // Suppresses name mangling so can be applied only to one function in a set of overloaded functions
    // It has to be used in both declaration and header if header is not included in implementation file
    // Multiple function implementation
    /* extern "C" {
     *
     * .....
     *
     * }
     * */

}

void memoryAllocation() {
    // C memory management functions
    int *p = (int*) malloc(sizeof(int));
    int *c = (int *) calloc(1,sizeof(int));
    p = (int *)realloc(c,sizeof(int) * 4);
    free(p);

    // C ++ new and delete operator

    int *p1 = new int;
    delete p1;
    p1 = nullptr; // prevent dangling pointer issue

    int *c1 = new int[5];
    delete []c1;

    /*
     - Malloc is function but new is operator
     - Malloc requires size during allocation but new ascertained size from type
     - Malloc cannot initialize memory(calloc can be) but new can initialize memory
     - Malloc cannot call constructors but new can call
     - Malloc returns void pointer that needs to be tpe casted but new returns correct type of pointer
     - Malloc cannot be customized but new can be customized through the operator overloading
     - Malloc return null on failure but new throws an exception
     */

}

void constructorAndDestructor(){

    //Constructor can be overloaded in class, if parameterized constructor is defined by developer compiler cannot synthesize default constructor
    // Destructor cannot be overloaded
    Car::showCount();
    Car car;
    Car car2(4);
    Car::showCount();

    const Car car3;
    //car3.FillFuel(4); If state is updated by member function, constant object cannot allow this behaviour
    car3.Dashboard(); // But if function is qualified with const keyword and its behaviour does not affect state of object can be used
}
void copyConstructor(){
    // If not declared manually ,compiler synthesis it

    //Shallow copy
    int *p1 = new int(5);
    int *p2 = p1;

    //Deep copy
    int *p3 = new int(*p1);

    Integer i(5);
    Integer i2(i);

    cout << i.getValue() << endl;
    cout << i2.getValue() << endl;

    /*
     * Rule of 3
     * All should be defined if a user implements any of them
     * Destructor
     * Copy Constructor
     * Copy assigment operator
     *
     * This will be due to allocation of some resource in a constructor (such as int pointer in Integer class)
     * Destructor will free the resource
     * Copy constructor will perform a deep copy
     * Copy assigment operation will also perform a deep copy
     *
     * Lack of implementation of any these functions in this condition can lead to memory leaks
     * */


}

namespace LRValueAndRValueRef {

    /*
     * L value has name but R value does not
     * All variables are L values but R value is a temporary value
     * L values can be assigned to values but R values cannot
     * Some expressions return L value and some of them R value
     * L value persist beyond the expression but R value does not
     * Functions that return by reference return L value but functions return by value return R value
     * */

    //Return r-value
    int Add(int x, int y){
        return  x+y;
    }

    // Return l-value
    int & Transform(int &x){
        x*=x;
        return x;
    }

    void assigmentExample() {

        //x,y & z are l-values, 5,10 & 8 are r-values
        int x = 5;
        int y = 10;
        int z = 8;

        int result = (x+y) * z;  // returns r-value

        ++x = 6; //Returns l-value

    }

    void rValueReference(){
        /*
      * R-value references created to temporary
      * Represents a temporary
      * Created with && operator
      * Cannot point to l-values
      * R-value references always bind to temporaries (r-values)
      * L-value references always bind to l-values
      *
      * */

        int &&r1 = 10; // R value reference is assign to temporary

        int &&r2 = Add(3,4); // Add function return r value ,so it can be used only in right-hand side of assigment operator and can be assigned to R-value reference or l-value

        int x = 0;
        // int && r3 = x; Cannot assign l-value to r-value reference

        int &ref = Transform(x); // L-value can assigned to l-value reference
        const int &ref2 = 3;  // R-value can also be assigned to l-value reference

    }

}

namespace CopyMoveSemantics{

    /// Copy-Move Semantics
    /*
     * Copy is implemented through copy constructor
     * Copy of the object state is created
     * Wasteful in case copy is created from a temporary
     * Move can be used for transferring to new object without copying the temporary object
     * */

    /*
     * In move operation new object created from temporary object with shallow copy, that means new object use and stole the resources of temporary object.
     * For detecting temporary objects we can implement constructor that accepts an R-value references (Move constructor)
     * After move operation temporary object resources assign to null pointer and wait to freed by user.
     * If user try to access underlying resources of temporary object after move operation, program will crash
     * If user re-initialize temporary object with new memory allocation and assigment after move then object can be used in program
     * */

    Integer Add(const Integer &a , const Integer &b){
        Integer temp;
        temp.setValue(a.getValue()+ b.getValue());
        return temp; // This return value type temporary object
    }

    void copySemantic(){

        Integer a(1),b(3);
        a.setValue(Add(a,b).getValue()); // So for setting value temporary object has to be copied because function requires l-value (waste)
    }

    /// RULE OF 5
    /*
     *
     * If  a class has ownership semantics, then you must provide a user defined : destructor, copy constructor, copy assigment operator, move constructor, move assignment operator
     * If only provide a constructor, then compiler automatically synthesize these operators
     * If a copy constructor or copy assignment operator is defined by user, then move operations will be deleted. Move operations must have to be defined by user
     * The defining of destructor create same affect like copy constructor, move operations become deleted
     * If a move constructor or operator is defined by user, then all these constructors will be deleted except destructor.
     * If deleted constructors are not going to be defined in custom implementation by user, user can use default specifier to call compiler to synthesize these automatically
     * Example : Integer & operator=(Integer&&)=default; // Create synthetic operations by compiler, but they are also considered as user-defined constructors
     *
     *
        Custom	            Copy Constructor    Copy Assignment    Move Constructor    Move Assignment    Destructor
        Copy constructor	Custom	            =default	       =delete	           =delete	          =default
        Copy assignment	    =default	        Custom	           =delete	           =delete	          =default
        Move constructor	=delete	            =delete	           Custom	           =delete	          =default
        Move assignment	    =delete	            =delete	           =delete	           Custom	          =default
        Destructor	        =default	        =default	       =delete	           =delete	          Custom
        None	            =default	        =default	       =default            =default	          =default

    */

    /// COPY ELISION

    /*
     * Compiler can omit move or copy operations when if needed to avoid create unnecessary objects.
     * For elision, class must have move and copy constructors
     * */

    /// STD::MOVE

    void forceCopyToMove(){

        Integer a(1);
        auto b(a); //It invokes copy constructor because "a" is l-value

        auto c(std::move(a)); // It invokes move constructor because std::move cast "a" to r-value reference (static_cast<Integer &&>(a))

        //cout << a.getValue() << endl; It will crash the program

        a.setValue(5); // Create new resources for object and assign new value
        cout << a.getValue() << endl; // It will not crash


    }

}

namespace OperatorOverloading {

        /*
         * Integer class has member function that overload "+" operator as "Integer operator +(const Integer & a)const"
         * "Integer operator +(const Integer & a)const" is a class member as a function called unary operator overloading that takes only one argument
         *
         */

        void operatorOverloadingUnary() {

            Integer a(1),b(3);
            Integer sum = a + b;
            cout << sum.getValue() << endl;
        }

        /*
        * Global function that overload "-" operator as "Integer operator -(const Integer &a, const Integer &b)"
        * "Integer operator -(const Integer &a, const Integer &b)" is global function called binary operator overloading that takes two arguments
        *
        */

        Integer operator -(const Integer &a, const Integer &b) {
            Integer temp;
            temp.setValue(a.getValue() - b.getValue());
            return temp;
        }

        void operatorOverloadingBinary() {

            Integer a(1),b(3);
            Integer sum = b - a;
            cout << sum.getValue() << endl;

        }

        /*
         * If same operator is overloaded in both global and class scope compiler complains about ambiguous overload and cannot compile the code
         *
         *
         * */

        void overloadPostPreIncrement(){

            Integer a(1),b(3);
            Integer sum = a + b;

            cout << (sum++).getValue() << endl; //Temporary object is created
            cout << (++sum).getValue() << endl; // It returns l-value by reference, is more efficient than post-increment

        }

}



int main() {
    initVariables();
    reference();
    constQualifier();
    autoUsage();
    rangeBasedForLoops();
    functionOverloading();
    memoryAllocation();
    constructorAndDestructor();
    copyConstructor();
    LRValueAndRValueRef::assigmentExample();
    LRValueAndRValueRef::rValueReference();
    CopyMoveSemantics::copySemantic();
    CopyMoveSemantics::forceCopyToMove();
    OperatorOverloading::operatorOverloadingUnary();
    OperatorOverloading::operatorOverloadingBinary();
    OperatorOverloading::overloadPostPreIncrement();



    return 0;
}
