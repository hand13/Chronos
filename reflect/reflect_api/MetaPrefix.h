#pragma once
#ifdef REFLECT_GEN
#define CField(X) int generated_field_##X;
#define CClass int generated_class;
#define CMethod(X) int generated_method_##X;
#endif
#ifndef REFLECT_GEN
#define CField(X)
#define CClass
#define CMethod(X)
#endif