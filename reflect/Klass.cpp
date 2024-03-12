#include "Klass.h"
#include "BaseType.h"

Klass Klass::boolKlass("bool",true,sizeof(bool));

Klass Klass::i8Klass("i8",true,sizeof(i8));
Klass Klass::i16Klass("i16",true,sizeof(i16));
Klass Klass::i32Klass("i32",true,sizeof(i32));
Klass Klass::i64Klass("i64",true,sizeof(i64));

Klass Klass::u8Klass("u8",true,sizeof(u8));
Klass Klass::u16Klass("u16",true,sizeof(u16));
Klass Klass::u32Klass("u32",true,sizeof(u32));
Klass Klass::u64Klass("u64",true,sizeof(u64));

Klass Klass::f32Klass("f32",true,sizeof(f32));
Klass Klass::f64Klass("f64",true,sizeof(f64));