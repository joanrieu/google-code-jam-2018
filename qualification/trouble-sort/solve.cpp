#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;

template<typename T> void solution(ull icase, T sol) {
    cout << "Case #" << icase << ": " << sol << endl;
}

void trouble(vector<ull>& numbers) {
    ull length = numbers.size();
    bool rerun;
    do {
        rerun = false;

        for (ull i = 0; i < length - 2; ++i) {
            ull a = numbers[i];
            ull b = numbers[i + 1];
            ull c = numbers[i + 2];

            if (a > c) {
                rerun = true;
                numbers[i] = c;
                numbers[i + 2] = a;
            }
        }
    } while (rerun);
}

void fastTrouble(vector<ull>& numbers) {
    vector<ull> series[2];
    ull length = numbers.size();
    series[0].reserve(length);    
    series[1].reserve(length);    
    for (ull i = 0; i < length; ++i)
        series[i % 2].push_back(numbers[i]);
    sort(series[0].begin(), series[0].end());
    sort(series[1].begin(), series[1].end());
    for (ull i = 0; i < length; ++i)
        numbers[i] = series[i % 2][i / 2];
}

void check(ull icase, vector<ull>& numbers) {
    ull col = -1;
    ull length = numbers.size();
    for (ull i = 0; i < length - 1; i++) {
        if (numbers[i] > numbers[i + 1]) {
            col = i;
            break;
        }
    }
    if (col == -1)
        solution(icase, "OK");
    else
        solution(icase, col);
}

void solve(ull icase, vector<ull>& numbers) {
    //trouble(numbers);
    fastTrouble(numbers);
    check(icase, numbers);
}

int main() {
    ull cases;
    cin >> cases;
    ull icase = 1;
    while (icase <= cases) {
        ull length;
        cin >> length;
        vector<ull> numbers;
        numbers.reserve(length);
        for (ull i = 0; i < length; ++i) {
            ull number;
            cin >> number;
            numbers.push_back(number);
        }
        solve(icase, numbers);
        icase = icase + 1;
    }
}
