////
//// Created by x on 19-12-3.
////
//
//// 这是一个标准的 C 函数
//const char* greet()
//{
//    return "Hello, world";
//}
//
//// 使用如下代码对上述函数进行包装
//#include <boost/python.hpp>
//BOOST_PYTHON_MODULE(hello_ext)
//{
//    using namespace boost::python;
//    def("greet", greet);
//}
//
//// 以下是调用该模块的 Python 代码
