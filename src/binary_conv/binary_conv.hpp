#pragma once

template <class T>
char* binary_conv(T in) {
  size_t size = sizeof(in);
  char* out = new char[size];
  for (size_t i = 0; i < size; i++) {
    T temp = in >> 8 * (size - 1 - i);
    out[i] = (char)temp;
  }
  return out;
}