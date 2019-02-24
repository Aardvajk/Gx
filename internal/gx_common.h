#ifndef GX_COMMON_H
#define GX_COMMON_H

template<typename T> void gx_detail_com_ptr_release(T *&ptr)
{
    if(ptr)
    {
        ptr->Release();
        ptr = nullptr;
    }
}

#endif // GX_COMMON_H
