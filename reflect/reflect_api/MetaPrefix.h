#pragma once
/**
 * @brief REFLECT_GEN 宏,仅用作生成metainfo
 * 
 */
#ifdef REFLECT_GEN
#define CField(X) int generated_field_##X;
#define CClass int generated_class;
#define CMethod(X) int generated_method_##X;
#endif
#ifndef REFLECT_GEN
/**
 * @brief macro for field
 * 
 */
#define CField(X)
/**
 * @brief macro for class
 * 
 */
#define CClass
/**
 * @brief macro for method
 * 
 */
#define CMethod(X)
#endif