//Zachary Palmer and Scott Giorlando
#ifndef __TOMBSTONES_H__
#define __TOMBSTONES_H__

template <class T> class Pointer;
template <class T> class Tombstone;

template <class T>
bool operator==(const int n, const Pointer<T>& t) { return t == n; }
template <class T>
bool operator!=(const int n, const Pointer<T>& t) { return t != n; }

//template <class T> void free(Pointer<T>& t);
using namespace std;

template <class T>
class Tombstone
{
  public:
	   int numReferences;
	   T* addressValue;
	   bool unused;
	   Tombstone<T>()
     {
        numReferences = 0;
        addressValue = NULL;
        unused = false;
     }
};

template <class T>
class Pointer
{
  public:
    Tombstone <T> *ptr;	//initialized a pointer to the tombstone

    Pointer<T>()
    { // default constructor
		    ptr = new Tombstone<T>();
        ptr->unused = false;// not inused when inistialized
	  }

    Pointer<T>(Pointer<T>& copy)
    { // copy constructor
		    if(copy.ptr->unused)
        {
			       cout << "Exception - [Dangling]\n";
              exit(1);
		    }
		    ptr = copy.ptr;
        ptr->unused = false;
		    if(ptr->numReferences != 0)
        {
             ptr->numReferences++;
        }
	  }

    Pointer<T>(T* x)
    { // bootstrapping constructor
        ptr = new Tombstone<T>();
		    ptr->addressValue = x;
        ptr->unused = false;
		    if(x == NULL)
        {
			      ptr->numReferences = 0;
		    }
        else
        {
			      ptr->numReferences = 1;
		    }
	  }

    ~Pointer<T>()
    { // destructor
		    ptr->numReferences--; // only delete one pointer
		    if(ptr->numReferences == 0 && !ptr->unused)
        {
            cout<<"Exception - [Memory Leak]\n";
            exit(1);	// if the reference counting is 0 and unused is false, that means we have a memory leak exception
        }
        ptr = NULL;
	   }

    T& operator*() const
    { // dereferencing
		    if(ptr->numReferences == 0)
        {
            cout<<"Exception - [Memory Leak]\n";
             exit(1);
		    }
		    else if(ptr->unused == true)
        {
		        cout<<"Exception - [Dangling]\n";
            exit(1);
		    }
        else
        {
            return *(ptr->addressValue);
        }

	  }

    T* operator->() const
    { // field dereferencing
		    if(ptr->numReferences==0)
        {
            cout<<"Exception - [Memory Leak]\n";
             exit(1);
		    }
		    else if(ptr->unused == true)
        {
			       cout<<"Exception - [Dangling]\n";
             exit(1);
		    }
        else
        {
            return ptr->addressValue;
        }

	}
    Pointer<T>& operator=(const Pointer<T>& t)
    { 	// assignment
        ptr->numReferences--;
        if(ptr->numReferences == 0)
        {
            cout<<"Exception - [Memory Leak]\n";
            exit(1);
		    }
		    ptr = t.ptr;
		    ptr->numReferences++;
		    if(ptr->unused)
        {
			       cout<<"Exception - [Dangling]\n";
             exit(1);
        }
		return *this;
	}

    friend void free(Pointer<T>& t)
    { // delete pointed-at object
        //cout << t.ptr->unused << endl;
        if(t.ptr->unused)
        {
             //all is already freed
        }
        else
        {
            t.ptr->unused = true;
            delete t.ptr->addressValue;
        }
    }

    // equality comparisons:
    bool operator==(const Pointer<T>& t) const{
		if(ptr->unused || (t.ptr->unused))
        {
		         cout<<"Exception - [Dangling]\n";
             exit(1);
		    }
		    else
        {
			       return ptr->addressValue == (t.ptr->addressValue);
		    }
	  }

    bool operator!=(const Pointer<T>& t) const
    {
		    if(ptr->unused || (t.ptr->unused))
        {
			       cout << "Exception - [Dangling]\n";
             exit(1);
		    }
		    else
        {
			       return ptr->addressValue != (t.ptr->addressValue);
		    }
	  }

    bool operator==(const int constInt) const
    {
        bool result;
        result = (ptr->addressValue == NULL) && (constInt == 0);
	      return result;
	  }

    bool operator!=(const int constInt) const
    {
        bool result;
        result = (ptr->addressValue == NULL) && (constInt == 0);
	      return !result;
	  }
};

#endif // __TOMBSTONES_H__
