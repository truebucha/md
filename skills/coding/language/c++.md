
#variables naming

I use:

* m for members
* c for constants/readonlys
* p for pointer (and pp for pointer to pointer)
* v for volatile
* s for static
* i for indexes and iterators
* e for events
* w for witnesses
* r for reducers

# Good links

<https://www.geeksforgeeks.org/copy-constructor-in-cpp/>

<https://docs.microsoft.com/en-us/cpp/cpp/how-to-create-and-use-shared-ptr-instances?view=vs-2019>

# Interesting things

## Templates

<https://www.codeproject.com/Articles/257589/An-Idiots-Guide-to-Cplusplus-Templates-Part-1#DefArgClassTempl>

## Inheritance

### copy constructor

<https://www.geeksforgeeks.org/copy-constructor-in-cpp/>

### class variables 

in case you define same class member variable as in base class -> there will be 2 instances, one in the base class, one in the derived class.

pointer to the base class will return instance in the base class, pointer to the derived class will return instance of the derived class.

### class functions

in case you define overriden function in a base class without "virtual" keyword -> there will be two instances of such func

one in the base class, one in the derived class.

pointer to the base class will call instance of the base class, pointer to the derived class will call instance of the derived class.

the better way is to use "virtual" in the base class and "override" in the derived class. "override" will fail compiler in case function in a base class not defined with "virtual".

### slicing 

```
  Derived derived;

 vector<Base> vect;
 vect.push_back(derived);
 vect[0].identify();  // <= calls Base class identify func;
```

<https://stackoverflow.com/questions/8777724/store-derived-class-objects-in-base-class-variables>

You are storing object of Derived class in an vector which is supposed to store objects of Base class, this leads to Object slicing and the derived class specific members of the object being stored get sliced off, thus the object stored in the vector just acts as object of Base class.

Solution:

You should store pointer to object of Base class in the vector:

`vector<Base*>`





