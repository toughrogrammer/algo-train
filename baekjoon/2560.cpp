#include <iostream>
#include <deque>
 
#define MAX_N 1010010
#define MOD 1000
 
using namespace std;
 
int arr[MAX_N];
 
 
int main() {
    int a, b, d, N;
    cin >> a >> b >> d >> N;
 
    arr[0] = 1;

    for (int i = 0; i <= d; i ++) {
        for (int future = i + a; future < i + b; future ++) {
            arr[future] = (arr[future] + arr[i]) % MOD;
        }
    }

    int next = 0;
    for (int i = d + 1 - b + 1; i <= d + 1 - a; i ++) {
        next = (next + arr[i]) % MOD;
    }

    for (int i = d + 1; i <= N; i ++) {
        arr[i] = next;

        if ((next + arr[i - a + 1] - arr[i - b + 1]) < 0) {
            next = (next + arr[i - a + 1] - arr[i - b + 1] + MOD) % MOD;
        } else {
            next = (next + arr[i - a + 1] - arr[i - b + 1]) % MOD;
        }
    }

    int sum = 0;
    for (int i = N - d + 1; i <= N; i ++) {
        sum = (sum + arr[i]) % MOD;
    }
 
    cout << sum << endl;
 
    return 0;
}