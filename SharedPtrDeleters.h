#ifndef SHARED_PTR_DELETERS_H_INCLUDED
#define SHARED_PTR_DELETERS_H_INCLUDED

///deleters for shared ptrs.  When the default behavior of delete(ptr) is not desirable.

///deletes arrays allocated with new[]
template <class T>
struct ArrayDeleter
{

    void operator()(T* ptr)
    {
        delete[] ptr;
    }

};

///does not delete anything
template <class T>
struct NoopDeleter
{

    void operator()(T*)
    {
    }

};


///deletes ptrs allocated with malloc()
template <class T>
struct FreeDeleter
{
    void operator()(T* ptr)
    {
        free(ptr);
    }
};


#endif // SHARED_PTR_DELETERS_H_INCLUDED
