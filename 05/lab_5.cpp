//#include <iostream>
//#include <sstream>
//
//#include "lab_5.h"
//
//#define checkEqual(x, y) do { if ((x) != (y)) { std::cout << "at line " << __LINE__ << ": " << (x) << " != " << (y) << '\n'; }; } while(0)
//#define checkTrue(cond) do { if (!(cond)) std::cout << "at line " << __LINE__ << ": " << #cond << '\n'; } while(0)
//
//
//
//int main()
//{
//    Data x = { 1, true, 2 };
//
//    std::stringstream s1;
//
//    Serializer serializer(s1);
//    checkTrue(serializer.save(x) == Error::NoError);
//
//    Data y = { 0, false, 0 };
//
//    Deserializer d1(s1);
//    checkTrue(d1.load(y) == Error::NoError);
//
//    checkEqual(x.a, y.a);
//    checkEqual(x.b, y.b);
//    checkEqual(x.c, y.c);
//
//    auto s2 = std::stringstream("");
//    Deserializer d2(s2);
//    checkTrue(d2.load(y) == Error::CorruptedArchive);
//
//    auto s3 = std::stringstream("1 2 3");
//    Deserializer d3(s3);
//    checkTrue(d3.load(y) == Error::CorruptedArchive);
//
//    auto s4 = std::stringstream("false 1");
//    Deserializer d4(s4);
//    checkTrue(d4.load(y) == Error::CorruptedArchive);
//
//    Data z = { 0, true, 0 };
//
//    auto s5 = std::stringstream("100 false 500");
//    Deserializer d5(s5);
//    checkTrue(d5.load(z) == Error::NoError);
//
//    checkEqual(z.a, 100);
//    checkEqual(z.b, false);
//    checkEqual(z.c, 500);
//
//    return 0;
//}