#include <gtest/gtest.h>
#include <utility>

//template <class T>
//inline typename std::remove_reference<T>::type&&
//move(T&& t) noexcept
//{
   //typedef typename std::remove_reference<T>::type To;
   //return static_cast<To&&>(t);
//}

//template <class T>
//inline T&& forward(typename std::remove_reference<T>::type& t) noexcept
//{
   //return static_cast<T&&>(t);
//}

//template <class T>
//inline decltype(auto) move(T&& t) noexcept
//{
   //return static_cast<std::remove_reference_t<T>&&>(t);
//}

//template <class T>
//inline T&& forward(std::remove_reference_t<T>& t) noexcept
//{
   //return static_cast<T&&>(t);
//}
