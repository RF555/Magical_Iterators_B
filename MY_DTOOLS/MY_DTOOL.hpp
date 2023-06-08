#ifndef MY_D_TOOL_H
#define MY_D_TOOL_H


// Text formatting macros:
#define CYAN_BOLD "\033[1;36m"
#define GREY "\033[0;37m"
#define GREEN "\033[0;32m"
#define PURPLE "\033[0;35m"
#define RED_BOLD "\x1b[1;31m"
#define RESET "\x1b[0m"


// general debugging:
#define DEF_INPUT(_input) GREY << _input << " " <<
#define DEF_DEBUG_INPUT(_input) CYAN_BOLD << "[DEBUG]: " << DEF_INPUT(_input)
#define DEF_DEBUG CYAN_BOLD << "\n[DEBUG]: " <<
#define DEF_FUNC PURPLE << "Func: " << GREEN << __func__ << "" <<
#define DEF_FILE_LINE RESET << " " << __FILE__ << ":" << __LINE__ << ":"

#define DEBUG_INPUT(_input) std::cout << DEF_DEBUG_INPUT(_input) DEF_FUNC DEF_FILE_LINE << std::endl;
#define DEBUG std::cout << DEF_DEBUG DEF_FUNC DEF_FILE_LINE << std::endl;


// exception/throw debugging:
#define DEF_EXCEPTION CYAN_BOLD << "[DEBUG]: " << RED_BOLD << "EXCEPTION THROWN:" <<

#define DEBUG_EXCEPTION(func) { \
    try {\
        func;\
    } catch (std::exception &ex) { \
        std::cout << DEF_EXCEPTION DEF_FILE_LINE << endl; \
        cout << "\t" << ex.what() << endl;\
        throw ex;\
    }\
}


// C try:

//#define GET_TYPE(X) _Generic((X), int: %d , \
//                              double: %d , \
//                              float: %f , \
//                              char[]: %s )

//#define DEF_DEBUG_INPUT CYAN_BOLD "[DEBUG_INPUT]: "
//#define DEF_INPUT(_action, _var) GREY GET_TYPE(_action) GET_TYPE(_var)
//#define DEF_FUNC "\t" PURPLE "Func: " GREEN __func__
//#define DEF_FILE_LINE RESET "\n\t\"" __FILE__ "\": Line: " __LINE__ "\n"
//#define DEBUG_INPUT(action, var) printf(DEF_DEBUG_INPUT DEF_INPUT(action, var) DEF_FUNC DEF_FILE_LINE, action, var);


#endif //MY_D_TOOL_H
