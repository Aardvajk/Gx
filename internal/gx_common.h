#ifndef GX__COMMON_H
#define GX__COMMON_H

template<typename T> void gx_detail_com_ptr_release(T *&ptr)
{
    if(ptr)
    {
        ptr->Release();
        ptr = nullptr;
    }
}

#endif // GX__COMMON_H
