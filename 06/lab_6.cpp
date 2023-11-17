#include "lab_6.h"
#include <exception>

int main() {
    std::ostringstream ss;
    Formatter formatter = Formatter(ss);
    std::string a = "{0}, {1}, {0asdf}";
    try {
        std::string f_s = formatter.format(a, 0, 1);
        std::cout << f_s;
    }
    catch (BadFormatIdxException& exception) {
        std::cerr << exception.what();
    }

    return 0;
}