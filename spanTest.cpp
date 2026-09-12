#include <span>
#include <iostream>
#include <string>
#include <cinttypes>
#include <vector>

using namespace std;

void processData(span<int> payload) {
    for(int data : payload) {
        cout << data << endl;
    }
}

int main() {
    vector<int> arr = {1, 2, 3, 4};

    processData(arr);
}