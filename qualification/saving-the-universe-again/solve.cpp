#include <iostream>
using namespace std;
typedef unsigned long long ull;

template<typename T> void solution(ull icase, T hacks) {
    std::cout << "Case #" << icase << ": " << hacks << std::endl;
}

ull measure(string program) {
    ull d = 0;
    ull s = 1;
    for (ull i = 0; i < program.length(); ++i) {
        int c = program[i];
        if (c == 'C')
            s = 2 * s;
        else if (c == 'S')
            d = d + s;
    }
    return d;
}

string hack(string program) {
    ull i = program.length() - 1;
    ull mode = 0;
    bool s = false;
    while (i >= 0) {
        int c = program[i];
        if (mode == 0) {
            if (c == 'C')
                --i;
            else
                mode = 1;
        } else if (mode == 1) {
            if (c == 'S') {
                --i;
                s = true;
            } else {
                if (s)
                    ++i;
                mode = 2;
            }
        } else if (mode == 2) {
            if (c == 'S') {
                --i;
                mode = 3;
            } else {
                break;
            }
        } else if (mode == 3) {
            if (c == 'C') {
                program[i] = 'S';
                program[i+1] = 'C';
                break;
            } else {
                break;
            }
        }
    }
    return program;
}

void solve(ull icase, ull shield, string program) {
    ull hacks = 0;
    while (true) {
        ull damage = measure(program);
        if (damage <= shield) {
            solution(icase, hacks);
            break;
        }
        string oldprogram = program;
        program = hack(program);
        hacks = hacks + 1;
        if (program == oldprogram) {
            solution(icase, "IMPOSSIBLE");
            break;
        }
    }
}

int main() {
    ull count, icase, shield;
    string program;
    cin >> count;
    icase = 1;
    while (icase <= count) {
        cin >> shield;
        cin >> program;
        solve(icase, shield, program);
        icase = icase + 1;
    }
}
