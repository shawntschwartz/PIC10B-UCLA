# define EXAMPLE 2

#if EXAMPLE==1 //shallow copying is done by default
#include<iostream>

using namespace std;

class Int
{
public:
    Int() : val(0) {}
    Int(int ix) : val(ix) {}
    int get_value() const { return val; };
private:
    int val;
};

int main()
{
    Int x(5);
    Int y(6);
    
    cout << x.get_value() << endl;
    cout << y.get_value() << endl;
    
    // shallow copy
    y = x;
    
    cout << x.get_value() << endl;
    cout << y.get_value() << endl;
    
    return 0;
}
#endif // EXAMPLE==1

#if EXAMPLE==2

#include<iostream>
using namespace std;

// n-tuple cannot be resized once it is set
class Tuple
{
public:
    Tuple() : data(NULL), dsize(0) {} //empty constructor
    
    //Tuple(size_t n) : data(NULL) {};
    
    Tuple(size_t n, int val = 0)
    {
        dsize = n;
        if (dsize>0)
        {
            data = new int[dsize];
            
            for (size_t i = 0; i < dsize; i++)
            {
                data[i] = val;
            }
        }
        else
        {
            data = NULL;
        }
    }
    //impementing setters and getters
    //setter
    void set_value(size_t idx, int x) // allows us to set the ith value in the tuple
    {
        data[idx] = x;
    }
    
    //getter
    int operator()(size_t idx) const{
        return data[idx]; // returning the value (getter just copies whatever it finds)
    } // now you can do cout << endl << a(4) // getter is working
    //but if you want to do something like a(4) = 5, this is a member function operator parentheses and can do this by putting it on the left-hand size of the assignment operator if this is a member function that has the pointer
    
    //setter (difference is that it allows us to return a reference to a point in the memory in the heap)
    int & operator()(size_t idx)
    {
        //returning a reference to data[idx], not data[idx] to be able to put it on the left hand side and you can now print it
        //with a reference you can now read and write from it
        //why would you want/need a getter (setter gives me a reference, what's the point of having a getter: the const is the importance: whenever you overload parentheses or square brackets, is the const and reference differences); so, any member function that uses this operator, b/c you need const
        //whenever you have two functions, you need to have 2 version and provide them
        return data[idx];
    }
    
    void set_all_values(int x)
    {
        for (size_t i = 0; i < dsize; i++)
        {
            data[i] = x;
        }
    }
    
    int get_value(size_t idx)
    {
        return data[idx];
    }
    
    //typical copy constructor
    //we constructed an object
    Tuple(const Tuple & t)
    {
        dsize = t.size();
        if (dsize > 0)
        {
            data = new int[dsize];
            
            for (size_t i = 0; i < dsize; i++)
            {
                data[i] = t.data[i];
            }
        }
        else
        {
            data = NULL;
        }
    }
    
    size_t size() const { return dsize; }
    
    void operator=(const Tuple & t)
    {
        // first, destroy itself (remove it before we lose it)
        if (dsize != 0)
        {
            delete[] data;
            dsize = 0;
        }
        
        if (!t.empty())
        {
            data = new int[t.size()];
            dsize = t.size();
            
            // copy stuff from t
            for (size_t i = 0; i < dsize; i++)
            {
                data[i] = t.data[i];
            }
        }
    }
    
    //Destructor makes sure things are gone when we are no longer using the object
    //We create a memory leak if we remove an object during a copy:
        //by default returning a shallow copy of an object (the return returns a shallow copy)
        //so if you want to return a deep copy, you need to use a copy constructor with "return"->operator
            //allows us to return whatever is created on the copy constructor that moves properly the data, the two pointers, and the data
    
    ~Tuple()
    {
        delete[] data;
        data = NULL;
        dsize = 0;
    }
    
    void print()
    {
        cout << endl;
        
        for (size_t i = 0; i < dsize; i++)
        {
            cout << data[i] << " ";
        }
        
        cout << endl;
    }
    
    bool empty() const
    {
        if (data==NULL)
            return true;
        return false;
    }
    
private:
    int* data; //pointer to the data that will be dynamically allocated
    size_t dsize; //of the tuple
};

// another problem: with functions
Tuple get_tuple(size_t n, int val=0)
{
    Tuple t(n,val); //step 1: go to Heap (t.data->points to heap) of values of length 5; t.dsize = 5
    // by default shallow copy is returned
    // the destructor will kill the stuff in the memory
    
    return t; // return t returns only a shallow copy b/c of our destructor
    // the destructor is going to be called by default whether we like it or not
    
} //memory is deallocated (so even though we made a copy), the stuff is gone and we made only a shallow copy:
//shallow copy: "copy of t," which essentially has the fields dsize = 5 and data that still points to the same place/address in the memory.

//default params (assumes from backwards, so if you provide the first param, it knows that it's the first and the last one (or second to last), in backwards order, will be read-in last.
//indicate defaults in func prototype
int func(int x=0, int a=0);

int func(int x, int a)
{
    return x*x+a;
}


int main()
{
    {
    Tuple t;
    cout << "get tuple step: " << endl;
    t = get_tuple(5,3); // you're trying to get access to the memory that isn't there anymore
        t.print();
        

//    cout << "\nERROR WILL POPUP" << endl;
        
    Tuple t1(5,1);
    Tuple t2(5,2);
    
    t1.print();
    t2.print();
    
    // problem with shallow copy
    t2 = t1; //copying the datafields of t1 into t2. problem with pointers (int* data)
    // (1) data* will be pointing to the same place in memory, so they aren't really different
    // and (2) now lost the data that the pointer was previously pointing to so there is a memory leak
    // they point to the same data with different size variables on stack are different but point to the
    // same address
    
    // t1.set_value(0,333); // program crash b/c destructor with both pointing to the same so you can't even delete that
        // (a) memory leak, (b) point to the same data so not a real copy, and (c) the destructors don't work b/c no longer pointing to the correct location
    
    // so, to fix this, we need to overload the assignment operator
    // when the assignment operator is used, we need to do some work and actually really copy stuff (deep-copy)
    t1.print();
    t2.print();
    
    // Deep Copy: Makes a "real" copy of an object, inclduing the data created dynamically
    // Goal: t2 = t1 --> after, 2 things need to be done:
        // (1) remove the data of tuple 2
        // (2) create new array and copy data[i]
    
    // we have to explicitely say what to do (and do some work) to overload the assignment operator
    
                Tuple a(5,4);// not going to work without copy constructor
                Tuple b = a; // not going to work without copy constructor
                Tuple c(b); // not going to work without copy constructor
        
        a.print();
        b.print();
        c.print();
        //
        
    }
    
    {
        
    }
    
    return 0;
}
#endif // EXAMPLE==2


