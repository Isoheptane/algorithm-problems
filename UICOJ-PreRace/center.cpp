#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

int main() {
    string input;
    cin >> input;
    cout << input[input.length() / 2] << '\n';
    return 0;
}