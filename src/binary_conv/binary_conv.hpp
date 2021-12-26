#pragma once

template <class T>
union DSet{
  T v;
  char c[sizeof(T)];
};