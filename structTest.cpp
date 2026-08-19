#include <iostream>
#include <cstdint>

using namespace std;

struct Product {
    const char* name;
    double price;
};

int main() {
    Product product = {"laptop", 9999};

    uint8_t* bytes = (uint8_t*)&product;
    for(size_t i = 0; i < sizeof(product); i++) {
        printf("%02X ", bytes[i]);
    }
    cout << endl;
    char* converted = (char*)bytes;
    cout << converted << endl;
}