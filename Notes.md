# Smart pointers

Documentation:  
https://en.cppreference.com/w/cpp/memory/unique_ptr  
https://en.cppreference.com/w/cpp/memory/shared_ptr  
https://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique  

Usage:

```cpp
#include <iostream>
#include <iomanip>
#include <memory>
 
struct Vec3
{
    int x, y, z;
 
    // following constructor is no longer needed since C++20
    Vec3(int x = 0, int y = 0, int z = 0) noexcept : x(x), y(y), z(z) { }
 
    friend std::ostream& operator<<(std::ostream& os, const Vec3& v) {
        return os << "{ x=" << v.x << ", y=" << v.y << ", z=" << v.z << " }";
    }
};
 
int main()
{
    // Use the default constructor.
    std::unique_ptr<Vec3> v1 = std::make_unique<Vec3>();
    // Use the constructor that matches these arguments
    std::unique_ptr<Vec3> v2 = std::make_unique<Vec3>(0,1,2);
 
    std::cout << "make_unique<Vec3>():      " << *v1 << '\n'
              << "make_unique<Vec3>(0,1,2): " << *v2 << '\n'
}
```

`unique_ptr` is a pointer to an object that may only have a single pointer. This pointer cannot be copied, and the object is deleted when the pointer is destroyed.

# Dynamic inheritance

Pointers to base classes may hold objects of derived classes.

In the example code from the repository, pointers `Person*` may point to `Student` objects.

This is useful, for example, for cases when you want to mix related types in a container, like a vector of `Person*` which may hold `Student` or `Professor` pointers.  
Another example is universal interfaces. You may define a function that takes a `QWidget*` as an argument and does something to the `QWidget`. Then, even when you create your own new widget inherited from `QWidget`, such a function would work for it.

# Virtual

When you use pointers and references to the base class to hold objects of a derived class, there may be some confusion with functions calls. If you override a base class function and make a more specific version of it in a derived class, you will potentially have access to two functions with the same name.

In the repository such a function is `calcSalary()`. If a `Professor` object is stored as a `Person*` pointer, you might want to call `Professor`'s version of `calcSalary()`. However, when the program is executing, there is only information that there is a `Person*` pointer, so the `Person`'s version of `calcSalary()` is called.

Keyword `virtual` is used for the methods to mark them as "potentially overloaded". When you call a virtual function using a pointer to the base class, the program checks that it is actually an object of the derived class and uses the `Professor`'s version of the function.

Destructors should generally be `virtual`, as for them it may be especially important to call the derived class version to prevent memory leaks.
