#ifndef PRECISION_LITERALS_DEFINITIONS_H__
#define PRECISION_LITERALS_DEFINITIONS_H__

#include "Precision_Default.h"

Precision::Int operator"" _Precision_Int(char const *const, size_t);
Precision::Int operator"" _Precision_Int_E(char const *const, size_t);
Precision::Int operator"" _Precision_Int(unsigned long long);


Precision::Float operator"" _Precision_Float(char const *const, size_t);
Precision::Float operator"" _Precision_Float_E(char const *const, size_t);
Precision::Float operator"" _Precision_Float(long double);
Precision::Float operator"" _Precision_Float(unsigned long long);


inline Precision::UInt operator"" _Precision_UInt(char const *const, size_t);
inline Precision::UInt operator"" _Precision_UInt_E(char const *const, size_t);
inline Precision::UInt operator"" _Precision_UInt(unsigned long long);


inline Precision::UFloat operator"" _Precision_UFloat(char const *const, size_t);
inline Precision::UFloat operator"" _Precision_UFloat_E(char const *const, size_t);
inline Precision::UFloat operator"" _Precision_UFloat(unsigned long long);
inline Precision::UFloat operator"" _Precision_UFloat(long double);

#endif