#include <iostream>
//#include "classes.h"
//#include <memory>
//#include <string>
//#include "vector"
//#include "OOP/Inheritance/Animal.h"
//#include "OOP/Polymorphism/Checking.h"
//#include "OOP/Polymorphism/Transaction.h"
//#include "OOP/Creational Design Patterns/singleton.h"
//#include <list>
//#include "OOP/Creational Design Patterns/factory.h"
//#include "OOP/Creational Design Patterns/parameterisedFactory.h"
//#include "OOP/Creational Design Patterns/objectPool.h"
//#include "OOP/Creational Design Patterns/abstractFactory.h"
//#include "OOP/Creational Design Patterns/prototype.h"
#include "OOP/Creational Design Patterns/builder.h"


//using namespace std;
//
//void initVariables() {
//    int a1; //Unint
//    int a2 = 0; //Copy init //Avoid this type init
//    int a3(5); //direct init
//    std::string s2("C++"); //direct init
//
//    char d1[8]; //Uninit
//    char d2[8] = {"abcd"}; //Copy init
//    char d3[8] = {'a','b','c','d'}; //Aggreagate init(also copy)
//
//    //Uniform init (C++11)
//
//    int b1{}; //Value init
//    int b3{5}; //Direct init
//
//    char e1[8]{};
//    char e2[8]{"Hello"};
//
//    int *p1 = new int{};
//
//    char *p2 = new char[8]{};
//
//    //char *p3 = new char[8]{"Hello"}; //TODO ask about
//
//    //Preventing narrowing conversion
//
//    float f1{};
//    //int i1{f1}; Compiler gives error
//
//    //Use uniform init when use user defined types mostly
//    //It forces init
//    // It can be used for array types with direct init
//    //It prevents narrowing conversions
//
//}
//
//void reference(){
//    int x = 10; //Referent
//
//    int &ref = x ; //Reference
//
//    ref = 6;
//
//    cout << "x:" << x << " Address :" << &x << endl;
//    cout << "ref:" << ref << " Address :" << &ref << endl;
//
//    //Reference must be init when it is created
//    // int &ref; // Gives compiler error
//    // Cannot be null
//    // Point same variable all its lifetime
//    // More memory efficient than pointer
//    // No dereference required like pointer
//
//}
//
//
//void constQualifier(){
//
//    //Cannot be modified
//    //Must be init
//
//    const int CHUNK_SIZE = 512;
//    //int *ptr = &CHUNK_SIZE; // Cannot be compiled
//    const int *ptr = &CHUNK_SIZE;
//    // *ptr = 1; WRONG
//
//    int x = 10;
//    ptr = &x; // Change address
//
//    const int *const ptr2 = &CHUNK_SIZE;
//    //ptr2 = &x; // WRONG because pointer is constant address of pointer cannot be changed
//
//    int *const ptr3 = &x;
//
//    *ptr3 = 7;
//
//    int y = 5;
//
//    //ptr3 = &y; WRONG
//
//    const int &ref = y;
//    //ref = 8; WRONG
//
//}
//
//void autoUsage(){
//
//    // Must be init
//    // Can be used with functions to auto infer types
//    // C++11
//
//    auto i = 10;
//    auto j = 5;
//    auto sum = i + j;
//    auto sum2 = i + 13.4f; //Largest type is used for auto
//
//    const int x = 10;
//    auto  var = x; // New variable can be non-constant
//    const auto  var2 = x; // Ensure to be constant use constant with auto
//
//    auto &var3 = x;  // Reference is inferred as constant when variable is constant
//
//    auto *ptr = &x;  // For pointer address of can be changed but deferenced value cannot be changed as original value
//
//    //auto list {1,2,3,4}; Uniform init cannot be used with auto when vectoral types are initiliazed
//
//    auto list = {1,2,3,4}; // Correct way
//
//}
//
//void rangeBasedForLoops(){
//
//    // No index usage
//    // Prevent access to beyond the size of array
//    // No control over iteration
//
//
//    int arr[] = {1,2,3,4,5};
//    for (auto x : arr) { //Create copy of each element avoid that usage
//        cout << x << " ";
//    }
//    cout << endl;
//    for (auto &x : arr) { //Use with a referencing prevents copying
//        cout << x << " ";
//    }
//    cout << endl;
//
//}
//
//int add(int a, int b) {
//    return a + b;
//}
//double add(double a, double b) {
//    return a + b;
//}
//
//extern "C" float add(float a,float b) {
//  return  a + b;
//}
//void functionOverloading() {
//
//    // Static polymorphism ( compile time )
//    // Same function name but different input types
//    // Return type is ignored
//    // For member functions qualifiers participate in overload
//    // For pointers and reference arguments qualifiers participate in overload
//    // Name mangling(generating unique name by compiler) is used for function overloading
//
//    auto sum1 = add(2,4);
//    auto sum2 = add(2.3,4.5);
//
//
//    // extern "C"
//
//    // Compiler directive allows C++ functions to be called from C or other languages , it is applied on global functions and variables
//    // Suppresses name mangling so can be applied only to one function in a set of overloaded functions
//    // It has to be used in both declaration and header if header is not included in implementation file
//    // Multiple function implementation
//    /* extern "C" {
//     *
//     * .....
//     *
//     * }
//     * */
//
//}
//
//void memoryAllocation() {
//    // C memory management functions
//    int *p = (int*) malloc(sizeof(int));
//    int *c = (int *) calloc(1,sizeof(int));
//    p = (int *)realloc(c,sizeof(int) * 4);
//    free(p);
//
//    // C ++ new and delete operator
//
//    int *p1 = new int;
//    delete p1;
//    p1 = nullptr; // prevent dangling pointer issue
//
//    int *c1 = new int[5];
//    delete []c1;
//
//    /*
//     - Malloc is function but new is operator
//     - Malloc requires size during allocation but new ascertained size from type
//     - Malloc cannot initialize memory(calloc can be) but new can initialize memory
//     - Malloc cannot call constructors but new can call
//     - Malloc returns void pointer that needs to be tpe casted but new returns correct type of pointer
//     - Malloc cannot be customized but new can be customized through the operator overloading
//     - Malloc return null on failure but new throws an exception
//     */
//
//}
//
//void constructorAndDestructor(){
//
//    //Constructor can be overloaded in class, if parameterized constructor is defined by developer compiler cannot synthesize default constructor
//    // Destructor cannot be overloaded
//    Car::showCount();
//    Car car;
//    Car car2(4);
//    Car::showCount();
//
//    const Car car3;
//    //car3.FillFuel(4); If state is updated by member function, constant object cannot allow this behaviour
//    car3.Dashboard(); // But if function is qualified with const keyword and its behaviour does not affect state of object can be used
//}
//void copyConstructor(){
//    // If not declared manually ,compiler synthesis it
//
//    //Shallow copy
//    int *p1 = new int(5);
//    int *p2 = p1;
//
//    //Deep copy
//    int *p3 = new int(*p1);
//
//    Integer i(5);
//    Integer i2(i);
//
//    cout << i.getValue() << endl;
//    cout << i2.getValue() << endl;
//
//    /*
//     * Rule of 3
//     * All should be defined if a user implements any of them
//     * Destructor
//     * Copy Constructor
//     * Copy assigment operator
//     *
//     * This will be due to allocation of some resource in a constructor (such as int pointer in Integer class)
//     * Destructor will free the resource
//     * Copy constructor will perform a deep copy
//     * Copy assigment operation will also perform a deep copy
//     *
//     * Lack of implementation of any these functions in this condition can lead to memory leaks
//     * */
//
//
//}
//
//namespace LRValueAndRValueRef {
//
//    /*
//     * L value has name but R value does not
//     * All variables are L values but R value is a temporary value
//     * L values can be assigned to values but R values cannot
//     * Some expressions return L value and some of them R value
//     * L value persist beyond the expression but R value does not
//     * Functions that return by reference return L value but functions return by value return R value
//     * */
//
//    //Return r-value
//    int Add(int x, int y){
//        return  x+y;
//    }
//
//    // Return l-value
//    int & Transform(int &x){
//        x*=x;
//        return x;
//    }
//
//    void assigmentExample() {
//
//        //x,y & z are l-values, 5,10 & 8 are r-values
//        int x = 5;
//        int y = 10;
//        int z = 8;
//
//        int result = (x+y) * z;  // returns r-value
//
//        ++x = 6; //Returns l-value
//
//    }
//
//    void rValueReference(){
//        /*
//      * R-value references created to temporary
//      * Represents a temporary
//      * Created with && operator
//      * Cannot point to l-values
//      * R-value references always bind to temporaries (r-values)
//      * L-value references always bind to l-values
//      *
//      * */
//
//        int &&r1 = 10; // R value reference is assign to temporary
//
//        int &&r2 = Add(3,4); // Add function return r value ,so it can be used only in right-hand side of assigment operator and can be assigned to R-value reference or l-value
//
//        int x = 0;
//        // int && r3 = x; Cannot assign l-value to r-value reference
//
//        int &ref = Transform(x); // L-value can assigned to l-value reference
//        const int &ref2 = 3;  // R-value can also be assigned to l-value reference
//
//    }
//
//}
//
//namespace CopyMoveSemantics{
//
//    /// Copy-Move Semantics
//    /*
//     * Copy is implemented through copy constructor
//     * Copy of the object state is created
//     * Wasteful in case copy is created from a temporary
//     * Move can be used for transferring to new object without copying the temporary object
//     * */
//
//    /*
//     * In move operation new object created from temporary object with shallow copy, that means new object use and stole the resources of temporary object.
//     * For detecting temporary objects we can implement constructor that accepts an R-value references (Move constructor)
//     * After move operation temporary object resources assign to null pointer and wait to freed by user.
//     * If user try to access underlying resources of temporary object after move operation, program will crash
//     * If user re-initialize temporary object with new memory allocation and assigment after move then object can be used in program
//     * */
//
//    Integer Add(const Integer &a , const Integer &b){
//        Integer temp;
//        temp.setValue(a.getValue()+ b.getValue());
//        return temp; // This return value type temporary object
//    }
//
//    void copySemantic(){
//
//        Integer a(1),b(3);
//        a.setValue(Add(a,b).getValue()); // So for setting value temporary object has to be copied because function requires l-value (waste)
//    }
//
//    /// RULE OF 5
//    /*
//     *
//     * If  a class has ownership semantics, then you must provide a user defined : destructor, copy constructor, copy assigment operator, move constructor, move assignment operator
//     * If only provide a constructor, then compiler automatically synthesize these operators
//     * If a copy constructor or copy assignment operator is defined by user, then move operations will be deleted. Move operations must have to be defined by user
//     * The defining of destructor create same affect like copy constructor, move operations become deleted
//     * If a move constructor or operator is defined by user, then all these constructors will be deleted except destructor.
//     * If deleted constructors are not going to be defined in custom implementation by user, user can use default specifier to call compiler to synthesize these automatically
//     * Example : Integer & operator=(Integer&&)=default; // Create synthetic operations by compiler, but they are also considered as user-defined constructors
//     *
//     *
//        Custom	            Copy Constructor    Copy Assignment    Move Constructor    Move Assignment    Destructor
//        Copy constructor	Custom	            =default	       =delete	           =delete	          =default
//        Copy assignment	    =default	        Custom	           =delete	           =delete	          =default
//        Move constructor	=delete	            =delete	           Custom	           =delete	          =default
//        Move assignment	    =delete	            =delete	           =delete	           Custom	          =default
//        Destructor	        =default	        =default	       =delete	           =delete	          Custom
//        None	            =default	        =default	       =default            =default	          =default
//
//    */
//
//    /// COPY ELISION
//
//    /*
//     * Compiler can omit move or copy operations when if needed to avoid create unnecessary objects.
//     * For elision, class must have move and copy constructors
//     * */
//
//    /// STD::MOVE
//
//    void forceCopyToMove(){
//
//        Integer a(1);
//        auto b(a); //It invokes copy constructor because "a" is l-value
//
//        auto c(std::move(a)); // It invokes move constructor because std::move cast "a" to r-value reference (static_cast<Integer &&>(a))
//
//        //cout << a.getValue() << endl; It will crash the program
//
//        a.setValue(5); // Create new resources for object and assign new value
//        cout << a.getValue() << endl; // It will not crash
//
//
//    }
//
//}
//
//namespace OperatorOverloading {
//
//
//        /*
//         * Associativity, precedence & arity (operand count) does not change
//         * Operator functions should be non-static (except for new & delete)
//         * One argument should be user defined type
//         * Global overload if first operand is primitive type
//         * Not all operators can be overloaded (., ?:, .*, sizeof, #)
//         * Cannot define new operators
//         *
//         * */
//
//        /*
//         * Integer class has member function that overload "+" operator as "Integer operator +(const Integer & a)const"
//         * "Integer operator +(const Integer & a)const" is a class member as a function called unary operator overloading that takes only one argument
//         *
//         */
//
//        void operatorOverloadingUnary() {
//
//            Integer a(1),b(3);
//            Integer sum = a + b;
//            cout << sum.getValue() << endl;
//        }
//
//        /*
//        * Global function that overload "-" operator as "Integer operator -(const Integer &a, const Integer &b)"
//        * "Integer operator -(const Integer &a, const Integer &b)" is global function called binary operator overloading that takes two arguments
//        *
//        */
//
//        Integer operator -(const Integer &a, const Integer &b) {
//            Integer temp;
//            temp.setValue(a.getValue() - b.getValue());
//            return temp;
//        }
//
//        void operatorOverloadingBinary() {
//
//            Integer a(1),b(3);
//            Integer sum = b - a;
//            cout << sum.getValue() << endl;
//
//        }
//
//        /*
//         * If same operator is overloaded in both global and class scope compiler complains about ambiguous overload and cannot compile the code
//         *
//         *
//         * */
//
//        void overloadPostPreIncrement(){
//
//            Integer a(1),b(3);
//            Integer sum = a + b;
//
//            cout << (sum++).getValue() << endl; //Temporary object is created
//            cout << (++sum).getValue() << endl; // It returns l-value by reference, is more efficient than post-increment
//
//        }
//
//
//        // Global operator overloading function to sum int + Integer
//        Integer operator+(int x,Integer & y){
//            Integer sum;
//            sum.setValue(x + y.getValue());
//            return  sum;
//        }
//
//        ostream & operator<<(ostream & out,const Integer &a){
//            out << a.getValue();
//            return out;
//        }
//
//        istream & operator>>(istream & input,Integer &a){
//            int x;
//            input >> x;
//            a.setValue(x);
//            return input;
//        }
//
//        void globalOverloadsAndAutoTypeConversion(){
//
//            Integer a(1),b(3);
//            //Integer sum1 = a + 5; //a.operator+(5) 5 is automatically cast to Integer type but cannot use with type conversion operator
//            Integer sum2 = 5 + a; //5.oprator+(a) is invalid because 5 is not an Integer type so global operator overloading function has to be defined to be valid expression
//
//            //Works with "ostream & operator<<(ostream & out,const Integer &a)" function
//            cout << sum2 << endl; //ostream operator overloaded in own class so if we add new behaviour for custom class, we have to create global overload
//
//            //Works with "istream & operator>>(istream & input,Integer &a)" function
//            cin >> a;
//            cout << a << endl;
//
//        }
//
//}
//
//namespace TypeConversion {
//
//    void primitiveToPrimitiveTypes(){
//
//        int a = 5, b=2;
//        float f = a / b; //data precision loss
//        cout << f << endl;
//        float f2 = static_cast<float>(a) / b;
//        cout << f2 << endl;
//
//        char *p = (char*) &a; // It does not check casting operation is valid cast
//        //char * p2 = static_cast<char *>(a) // static_cast validate cast and compiler gives error
//        char *p2 = reinterpret_cast<char *>(a); //If you know what you are doing then use reinterpret cast to conversion between incompatible types
//        // C style cast can discard qualifiers and it causes bugs but reinterpret cast does not discard qualifiers
//        const int x = 1;
//        int *p3 = (int *)&x; // Discard qualifier const
//        //int *p4 = reinterpret_cast<int *>(&x); It does not allow to cast by compiler because const qualifier is required
//        int *p4 = const_cast<int *>(&x); //It cast to desired type with preserving const qualifier
//    }
//
//    void Print(Integer a){ //const Integer &a also works
//
//    }
//
//    void primitiveToUserType(){
//
//        //Parameterized constructors can take a role in type conversion
//        Integer a1{5}; // Explicitly type conversion
//        Integer a2 = 5; // Implicitly type conversion (search for suitable constructor and init object)
//
//        Print(5); // Implicitly type conversion (search for suitable constructor and init object)
//
//        a1 = 7; //Match with move assignment then parameterized constructor called then move operation proceed
//
//        /*
//         * If parameterized constructor declared with explicit keyword all implicitly type conversions are not allowed
//         * explicit Integer(int value){...}
//         * */
//    }
//
//    void userTypeToPrimitiveType(){
//        /*
//         * Primitive to user defined type conversion can be implemented with type operators
//         * Exp : operator int()
//         * */
//        Integer a1{5};
//        int x = a1;
//
//        // If type operator is declared with explicit keyword then cast conversion functions must be used
//        // Exp: int x = static_cast<int>(a1);
//    }
//
//
//    void userTypeToUserType(){
//        Product p{5};
//        Integer id = p.GetInteger(); //Custom function can be implemented for type conversion
//
//        //However, more proper way is to use type conversion operator
//        id = p;
//
//        if (id == p){ // Also use type conversion operator to compare
//            cout << "Id Match with the product" << endl;
//        }
//    }
//
//
//}
//
//namespace SmartPointers{
//
//    Integer * getPointer(int value){
//        Integer *p = new Integer{value};
//        return  p;
//    }
//    void Display(Integer *p){
//        if(!p){
//            return;
//        }
//        cout << p->getValue() << endl;
//    }
//
//    void Store(std::unique_ptr<Integer> p){
//        cout << "Stroing data into a file" << p->getValue() << endl;
//    }
//
//    void Store2(std::unique_ptr<Integer> &p){
//        cout << "Stroing data into a file" << p->getValue() << endl;
//    }
//
//    void uniquePointer(){
//        std::unique_ptr<Integer> p {getPointer(5)}; // Create unique pointer
//        if(p == nullptr){
//            //p = new Integer{5}; // p is not pointer so it cannot be initialize assigment operator
//            p.reset(new Integer{5}); // If re-initialize pointer use reset
//        }
//        p->setValue(100);
//        Display(p.get()); // Get() method access underlying pointer under unique pointer object
//        //delete p; Deleting pointer is accepted but p is not a pointer , it is an unique pointer object cannot be deleted like that
//        p = nullptr; // This assigment invoke operator overloading in unique pointer class and assign null pointer to underlying pointer in unique pointer object (like calling delete on pointer)
//        p.reset(new Integer{});
//        *p = __LINE__; // De-referencing operator overloaded to access value of underlying pointer
//        Display(p.get());
//        // Unique pointer does not need to be deleted, it uses RAII and object lifespan is end with scope and de-constructor is called
//        // Store(p); // It does not work because copy constructor is deleted for unique pointer class
//        Store(std::move(p)); // Unique pointer cannot be copied but it can be moved with move constructor
//        //After move operation ownership of underlying pointer is moved to underlying pointer of function input object and start lifecycle of itself
//        //So accessing after move operation is not allowed, if we use pointer again we have to call reset function
//        p.reset(new Integer{10});
//        Store2(p); // If function takes input by reference, std::move does not need to be used and after store function p can be used without reset also
//        *p = 20;
//
//    }
//
//    /*
//     * If object have dependency on other object pointer unique pointer cannot be used
//     * Project and employees is one of the example of this hierarchy , employees have a Project pointer
//     * When first employee use project pointer takes the ownership of underlying pointer of Project object
//     * So Project pointer is moved to pointer that under Employee object and become useless
//     * Unique pointers cannot be shared , they are only moved so shared pointer can be used for this architecture
//     * Shared pointer keep share count of pointer, when holder release shared pointer decremented this count when is shared incremented
//     * If shard pointer reference count become zero, destructor called to release the underlying pointer
//     *
//     * */
//    void showInfo(std::shared_ptr<Employee> &emp){
//        cout << "Employee project info" << endl;
//        emp->getProject()->showProjectDetails();
//    }
//    void sharedPointer(){
//
//
//        std::shared_ptr<Project> project{new Project{}};
//        project->setName("Video Decoder");
//        std::shared_ptr<Employee> e1 {new Employee{}};
//        e1->setProject(project);
//        std::shared_ptr<Employee> e2 {new Employee{}};
//        e2->setProject(project);
//        std::shared_ptr<Employee> e3 {new Employee{}};
//        e3->setProject(project);
//
//        cout << "Reference count:" << project.use_count() << endl;
//
//        showInfo(e1);
//        showInfo(e2);
//        showInfo(e3);
//        project->showProjectDetails();
//        e1 = nullptr;
//        e2 = nullptr;
//        e3 = nullptr;
//
//        cout << "Reference count:" << project.use_count() << endl;
//
//    }
//    /*
//     * If we want to share pointer between objects and objects have to know original underlying memory is freed
//     *  shared_pointer cannot be handle this situation because of reference counter keeps memory until reach to zero
//     *  So weak pointer can be used for this scenario, weak pointer is used with shared pointer
//     *  It points to control block of shared pointer, multiple shared pointers can point to same control block
//     *  If underlying pointer of shared  memory is released and counter becomes zero , weak pointer checks this with expired() method
//     *  If we want to access underlying pointer of shared pointer that weak pointer points to
//     *  we cannot access directly, instead we use lock() method to increment counter(create shared pointer from source) and get the address of memory for use
//     *  Weak pointer also is useful for circular references between classes
//     *
//     *
//     * */
//    void weakPointer() {
//        Printer printer;
//        int num {};
//        cin >> num;
//        std::shared_ptr<int> p{new int{num}};
//        printer.setValue(p);
//        if(*p > 10){
//            p = nullptr;
//        }
//        printer.print();
//    }
//
//    /*
//     * Smart pointers call the destructor end of the scope and it calls the delete method
//     * For using new operator, it works fine but for custom memory allocation or descriptor causes undefined behaviour
//     * It may not be release or handle memory properly
//     * When it calls delete method it invokes deleter callback mechanism, if we want to handle
//     * custom memory management behaviour, we can define custom deleter and provide to smart pointer
//     *
//     * */
//
//    struct Free{
//        void operator()(int *p){
//            free(p);
//            cout << "Pointer freed" << endl;
//        }
//    }; // Can be used as deleter without members over function objects
//
//    void MallocFree(int *p){
//        free(p);
//        cout << "Pointer freed" << endl;
//    } // Can be used as deleter over function pointer
//    void deleter(){
//
//        std::unique_ptr<int,Free> p {(int*) malloc(4),Free{}};
//        std::unique_ptr<int,void (*)(int *)> p1 {(int*) malloc(4), MallocFree};
//        std::shared_ptr<int> p2 {(int*) malloc(4), MallocFree}; //Shared pointer does not require type of deleter
//        *p = 100;
//        *p1 = 200;
//        cout << *p << endl;
//        cout << *p1 << endl;
//    }
//
//    void dynamicArrays(){
//        std::unique_ptr<int> p{new int[5]{1,2,3,4,5}}; //Cannot access with array subscript also deleter cannot delete this in proper way
//        //p[0] = 10;
//        p.get()[0] = 10; // It works but ugly
//        // Use int[] instead of expression that above
//        std::unique_ptr<int[]> p1{new int[5]{1,2,3,4,5}}; //It works with array brackets also it calls right delete method for array
//        p1[0] = 10;
//
//        //std::shared_ptr<int[]> p2{new int[5]{1,2,3,4,5}}; This usage becomes with C++17
//    }
//
//    void makeFunctions(){
//
//        /*
//         * Equivalent of std::unique_ptr<int> p{ new int{5} }
//         * For shared pointer use make_shared
//         * Dynamic array creation with make_shared is came with C++20
//         * If you use custom deleter, make functions cannot be used
//         * */
//         auto p = std::make_unique<int>(5);
//         auto car = std::make_unique<Car>(20.0,5); //As a variadic function can take multiple arguments
//
//         auto dynamicArray = std::make_unique<int[]>(5); //Can create dynamic array but cannot initialized
//
//         auto p1 = std::make_shared<int>(5);
//
//    }
//
//}
//
//namespace AdvancedDataTypes{
//
//    enum Color{
//        RED,
//        GREEN,
//        BLUE
//    };
//
//    enum class Light : char{ //Scoped enum for global conflict, also type of the enum can be defined
//        RED = 99,
//        GREEN,
//        YELLOW
//    };
//
//    void enums(){
//        /*
//         * Created with restricted range of values, called symbolic constants or enumerators
//         * Can implicitly convert to an integer but not the other way around
//         * Default value starts from 0, but user can assign any value
//         * */
//
//        Color c = RED;
//        // c = 1; // Compile error, it can be casted with static_cast
//        c = static_cast<Color>(2);
//
//        int x = GREEN; //Implicit conversion to integer
//
//        Light l = Light::GREEN; //Scoped enum variable
//
//        int y = static_cast<int>(Light::YELLOW); // Scoped enum does not use implicit conversion, static cast must be used
//
//    }
//
//}
//
//namespace STL{
//
//    void stdString(){
//
//        //Initialize & assign
//        std::string s = "Hello";
//        s = "Hello";
//
//        //Access
//        s[0] = 'W';
//        char ch = s[1];
//        cout << s << endl;
//        cin >> s;
//        std::getline(cin,s);
//
//        //Size
//        s.length();
//
//        //Insert & Concatenate
//
//        std::string s1{"Hello"}, s2{"World"};
//        s = s1 + s2;
//        s+=s1;
//        s.insert(6,"Test");
//
//        //Comparison
//        if(s1!=s2){
//
//        }
//
//        //Removal
//        s.erase();
//        s.erase(0,5);
//        s.clear();
//
//        //Search
//
//        auto pos = s.find("World",0);
//        if(pos != std::string::npos){
//            cout << "Found" << endl;
//        }
//
//
//
//    }
//}
//
//namespace Templates{
//
//    /*
//     *  Generalizes software components
//     *  Operate of any kind of data
//     *  High performance algorithms & classes
//     *  They are generated at compile time
//     *
//     * */
//
//    //Template function is just blueprint, without invoking for any type compiler does not implicitly instantiate corresponding function
//    template<typename T>
//    T Max(T x, T y){
//        return x > y ? x: y;
//    }
//
//    //Explicit instantiation for Max char
//    template char Max(char x, char y);
//
//    //Explicit Specialization for char array comparison
//    //It has to be defined in definition file(cpp)
//    template<> const char *Max<const char *>(const char *x,const char *y){
//        return strcmp(x,y) > 0 ? x :y;
//    }
//
//    //Non-type Template Arguments
//    //Arguments cannot be modified in template function
//    template<int size>
//    void Print(){
//        cout << size << endl;
//    }
//    template<typename T,int size>
//    T Sum(T(&arr)[size]){
//        T sum{};
//        for (int i = 0; i < size; ++i) {
//            sum += arr[i];
//        }
//        return sum;
//    }
//
//    void templateExamples() {
//        auto num = Max(3.3f,5.8f);
//        auto num2 = Max(38,12);
//        cout << num << endl;
//        cout << num2 << endl;
//
//        //Different primitives types as arguments
//        Max(static_cast<float>(3),5.5f);
//        Max<double>(5,6.5);
//
//        //Instantiate Max template for integer type
//        int(*pfn)(int,int) = Max;
//
//        const char *b {"B"};
//        const char *a {"A"};
//
//        auto s = Max(a,b);
//        cout << s << endl;
//
//        int i = 3;
//        Print<3>();
//        //Print<i>(); Does not work because this specified in compile time
//        Print<sizeof(i)>(); //It works because sizeof is compile time function
//
//        int arr[]{1,3,5,7,9};
//        int sum = Sum(arr);
//        cout << sum << endl;
//
//    }
//
//    void perfectForwarding(){
//        // Use std::forward for preserving r or l value type in template member functions that calls constructors
//        //TODO fix this
////        auto product = Product{"Cheese",Integer{245}};
//
//    }
//
//    void Print(){
//
//    }
//    //Template parameter pack
//    template<typename T,typename...Params>
//    //Function parameter pack
//    void Print(T &&a,Params&&... args){
//
//        cout << a;
//        if(sizeof...(args)!=0){
//            cout << ",";
//        }
//        Print(std::forward<Params>(args)...);
//    }
//
//    void variadicTemplates(){
//        Print(1,2,4.5,"4");
//    }
//
//    template<typename T,int size>
//    class Stack{
//        T m_Buffer[size];
//        int m_top{-1};
//
//        public:
//            Stack() = default;
//            void push(const T &element){
//                m_Buffer[++m_top] = element;
//            }
//            void pop();
//            const T& top() const{
//                return m_Buffer[m_top];
//            }
//            bool isEmpty(){
//                return m_top == -1;
//            }
//            static Stack create(); //Short hand notation
//    };
//    template<typename T,int size>
//    void Stack<T,size>::pop() {
//        --m_top;
//    }
//    template<typename T,int size>
//    Stack<T,size> Stack<T,size>::create() {
//        return Stack<T,size> ();
//    }
//
//    void classTemplates(){
//        Stack<float,10> s;
//        s.push(1);
//        s.push(2.4);
//        s.push(5);
//        while (!s.isEmpty()){
//            cout << s.top() << endl;
//            s.pop();
//        }
//    }
//
//    template<typename T>
//    class PrettyPrinter{
//        T* m_data;
//        public:
//
//            PrettyPrinter(T *data):m_data(data){}
//            void print(){
//                cout << "{" << *m_data << "}" << endl;
//            }
//            T *getData(){
//                return m_data;
//            }
//
//    };
//
//    template<>
//    void PrettyPrinter<std::vector<int>>::print() {
//        cout << "{";
//        for (const auto &x:*m_data) {
//            cout << x;
//        }
//        cout << "}" << endl;
//    }
//    void classTemplateExplicit(){
//        std::vector<int> v{1,2,3,4,5};
//        PrettyPrinter<std::vector<int>> pv(&v);
//        pv.print();
//
//    }
//    template<typename T>
//    class SmartPointer{
//        T *ptr;
//        public:
//        SmartPointer(T *ptr):ptr(ptr){
//
//        }
//        T *operator ->(){
//            return ptr;
//        }
//        T & operator *(){
//            return *ptr;
//        }
//        ~SmartPointer(){
//            delete ptr;
//        }
//    };
//    template<typename T>
//    class SmartPointer<T[]>{
//        T *ptr;
//    public:
//        SmartPointer(T *ptr):ptr(ptr){
//
//        }
//        T &operator[](int index){
//            return ptr[index];
//        }
//        ~SmartPointer(){
//            delete[] ptr;
//        }
//    };
//    void partialSpecializationTemplates(){
//        SmartPointer<int[]> p{new int[5]};
//        p[0] = 5;
//        cout << p[0] << endl;
//    }
//
//
//    typedef unsigned int UINT; //Typedef make alias to unsigned int as UINT
//    using INT16 = short; //Type alias is C11 feature acts as typedef definitions
//
//    using PFN = const char*(*)(int); //Type alias for function pointer
//    void showError(PFN pfn){
//
//    }
//
//    template<typename T>
//    using Names = std::vector<std::list<T>>; //Alias Templates
//
//}
//
//namespace OOP{
//
//    void inheritance(){
//
//        /*
//         * Dog is derived from Animal base class
//         * Dog has same member attributes and methods from Animal class
//         * Dog class can own custom methods and also it can change behaviour of inherited functions that belongs to base class
//         *
//         * */
//        //TODO try to use parameterized constructor of base class
//        Dog d;
//        d.eat(); //Dog class change the base class eat method
//        d.run(); //Use same behaviour of parent class
//        d.speak();
//
//        /*
//         * Access modifiers are public,private and protected
//         * Public members are accessible from outside and inside of class
//         * Private members are accessible from inside of class
//         * Protected members are accessible from inside and child classes of class
//         *
//         * If child class is inherited from base class with public access modifier:
//         * (: Public) Child class access public and protected members of base class but cannot access private members
//         * (: Private) Child class inherit members of base class  as private members,
//         * private members of base class is not still accessible but other members are accessible only inside of child class
//         * (:Protected) Child class inherit members of base class as protected members,
//         * private members of base class is not still accessible but other members are accessible  inside of child class and inside of child of child class
//         *
//         * */
//
//        /*
//         * Constructors execute from base to child
//         * Destructors execute from child to base
//         * If class is specified with final keyword, it cannot be inherited by other classes
//         * If base class member method is specified with final keyword, it cannot be override by child classes
//         * */
//    }
//
//    void virtualMechanism(){
//
//        /*
//         * Virtual keyword in base class make the child class can overriding base class functions and
//         * these functions can be called from child class object in form of base class
//         *
//         * */
//        Checking ch("Bob", 100, 50);
//        Transact(&ch);
//    }
//
//#pragma region Override
//    class Document { //Abstract class
//    public:
//        virtual void Serialize(float version) = 0; //Pure virtual function
//    };
//    class Text : public Document {
//    public:
//        void Serialize(float version)override final{
//            std::cout << "Text::Serialize" << std::endl;
//        }
//    };
//    class RichText : public Text {
//    public:
//        //Cannot override because the function is final in base
//        /*void Serialize(float version)override {
//            std::cout << "RichText::Serialize" << std::endl;
//        }*/
//    };
//
//    class XML : public Document {
//    public:
//        void Serialize(float version)override {
//            std::cout << "XML::Serialize" << std::endl;
//        }
//    };
//
//    void Write(Document *p) {
//        p->Serialize(1.1f);
//    }
//
//    void overrideKeyword(){
//        /*
//         * When a child class override the virtual base class method, it may use wrong signature.
//         * For preventing that when create a new override class, function can be specified with override specifier
//         * That specifier prevents bugs that caused by wrong signature
//         *
//         * */
//
//        XML xml;
//        Write(&xml);
//
//        /*
//         * Document class is abstract class that has at least one pure virtual function
//         * Can contain other members(data,non-virtual functions, etc.)
//         * It cannot be instantiated,but used through a pointer or reference
//         * Establishes a contract with clients
//         * Used for creating interface
//         *
//         * */
//
//        /*
//         * Pure virtual function does not have an implementation(optional)
//         * Cannot be invoked directly(can invoked from derived classes)
//         * No entry in vtable
//         * Must be overridden by the derived classes
//         * */
//
//    }
//
//    void objectSlicing(){
//
//        /*
//       * With upcasting member methods of child class can be invoked from base class pointer
//       * For upcasting base class object has to be pointer to object
//       *
//       * */
//        Checking ch("Melik",100,50);
//        Account *account = &ch; //Upcasting child object to base class object
//
//        /*
//         * Compiler removes some part of an object, it is named as object slicing
//         * Occurs when child object is assigned to a concrete base class object;
//         * Compiler removes part of an object because of preventing memory corruption
//         * */
//        Checking ch2("Melik",150,50);
//        Account account2 = ch; //Object slicing
//
//        /*
//         * If base class object is assigned to pointer of  child class,
//         * casting method has to be applied
//         * This method is named as down casting
//         * */
//        Checking *ch3 = static_cast<Checking *>(account); //down cast
//
//        //Typeid works only when there is a virtual function in the base class because it works at compile time
//        if(typeid(*account) == typeid(Checking)){ //Check original upcasted object before down casted to specific child type
//            Checking *ch3 = static_cast<Checking *>(account);
//        }
//
//        Checking *ch4 = dynamic_cast<Checking *>(account); //Behave like typeid checking check object can be down casted or not
//        if(ch4 != nullptr){
//
//        }
//
//        Checking &ch5 = dynamic_cast<Checking &>(*account); //For reference if cast cannot be performed throws BAD CAST error
//    }
//
//    class Stream{
//        std::string fileName;
//    public:
//        Stream(const std::string &filename):fileName(filename){
//            cout << "Stream(const std::string&)" << endl;
//        }
//        const std::string & getFilename()const {
//
//            return fileName;
//        }
//        ~Stream(){
//            cout << "~Stream()" << endl;
//        }
//    };
//    class OutputStream : virtual public Stream{
//        std::ostream  &out;
//    public:
//        OutputStream(std::ostream &o,const std::string &filename):out(o), Stream(filename){
//            cout << "OutputStream" << endl;
//        }
//        std::ostream & operator <<(const std::string &data){
//            out << data;
//            return out;
//        }
//        ~OutputStream(){
//            cout << "~OutputStream" << endl;
//        }
//    };
//    class InputStream: virtual public Stream{
//        std::istream  &in;
//    public:
//        InputStream(std::istream &i,const std::string &filename):in(i),Stream(filename){
//            cout << "InputStream" << endl;
//        }
//        std::istream & operator >>(std::string &data){
//            in >> data;
//            return in;
//        }
//        ~InputStream(){
//            cout << "~InputStream" << endl;
//        }
//    };
//    class IOStream:public InputStream,public OutputStream{
//    public:
//        IOStream(const std::string &filename):InputStream(std::cin,filename),OutputStream(std::cout,filename), Stream(filename){
//            cout << "IOStream" << endl;
//        }
//
//        ~IOStream(){
//            cout << "~IOStream" << endl;
//        }
//    };
//
//    void multipleInheritance(){
//        IOStream stream("doc.txt");
//        std::string data;
//        stream >> data;
//        stream << data;
//        stream << stream.getFilename() << endl;
//    }
//}



int main() {
//    initVariables();
//    reference();
//    constQualifier();
//    autoUsage();
//    rangeBasedForLoops();
//    functionOverloading();
//    memoryAllocation();
//    constructorAndDestructor();
//    copyConstructor();
//    LRValueAndRValueRef::assigmentExample();
//    LRValueAndRValueRef::rValueReference();
//    CopyMoveSemantics::copySemantic();
//    CopyMoveSemantics::forceCopyToMove();
//    OperatorOverloading::operatorOverloadingUnary();
//    OperatorOverloading::operatorOverloadingBinary();
//    OperatorOverloading::overloadPostPreIncrement();
//    OperatorOverloading::globalOverloadsAndAutoTypeConversion();
//    TypeConversion::primitiveToPrimitiveTypes();
//    TypeConversion::primitiveToUserType();
//    TypeConversion::userTypeToPrimitiveType();
//    TypeConversion::userTypeToUserType();
//    SmartPointers::uniquePointer();
//    SmartPointers::sharedPointer();
//    SmartPointers::weakPointer();
//    SmartPointers::deleter();
//    SmartPointers::dynamicArrays();
//    SmartPointers::makeFunctions();
//    AdvancedDataTypes::enums();
//    Templates::templateExamples();
//    Templates::perfectForwarding();
//    Templates::variadicTemplates();
//    Templates::classTemplateExplicit();
//    Templates::partialSpecializationTemplates();
//    loggerExample();

//    Factory::executeSample();
//    ParameterisedFactory::executeSample();
//    ObjectPoolMethod::executeSample();
//    AbstractFactoryMethod::executeBasicSample();
//    AbstractFactoryMethod::executeDatabaseSample();
//     PrototypeMethod::executeBasicExample();
    //PrototypeMethod::executeGameExample();
    //BuilderPattern::executeBasicExample();
    BuilderPattern::executeFileExample();
    return 0;
}
