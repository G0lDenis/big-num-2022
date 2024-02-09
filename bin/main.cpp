#include "lib/number.h"
#include <iostream>

int main() {
    uint2022_t value1 = from_uint((uint32_t) 23);
    std::cout << value1 << std::endl;
    uint2022_t value2 = from_string("123555555555550000055555534555555555555");
    std::cout << value2 << std::endl;
    auto valx = from_string("2147483647");
    std::cout << valx << std::endl;
    std::cout << ((value1 == value2) == 0) << std::endl;
    std::cout << ((from_string("23") == from_uint(23)) == 1) << std::endl;
    std::cout << ((from_string("24") == from_uint(23)) == 0) << std::endl;
    std::cout << ((from_string("24") > from_string("23122222222222222222222")) == 0) << std::endl;
    std::cout << ((from_string("24") < from_string("23122222222222222222222")) == 1) << std::endl;
    std::cout << ((from_string("23") != from_string("23")) == 0) << std::endl;
    std::cout << (from_uint(2147483647) == from_string("2147483647")) << std::endl;
    auto valx1 = from_string("405272312330606683982498447530407677486444946329741977764879002871583477858493");
    auto valx2 = (from_string("405272312330606683982498447530407677486444946329741974138101544027695953739965") +
                  from_string("3626777458843887524118528"));
    std::cout << valx1 << std::endl;
    std::cout << valx2 << std::endl;
    std::cout << (valx1 * valx2) << std::endl;
    std::cout << (from_string("1024") * from_uint(1)) << std::endl;
    std::cout << (from_string("99999999999999999999") / (uint32_t) 4) << std::endl;
    std::cout << (from_string("99999999994654999999") / from_string("2136435766676676463")) << std::endl;
    try {
        std::cout << (from_string("123") / from_string("0"));
    }
    catch (std::invalid_argument inv_ar) {
        std::cout << "Division by zero";
    }
    return 0;
}
