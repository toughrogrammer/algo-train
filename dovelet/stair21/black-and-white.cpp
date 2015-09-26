#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
 
#define MAX_POINTS 101
#define INFINITE 99999
 
using namespace std;
 
class Pair {
public:
    int start, end, height;
 
    Pair(int start, int end) {
        this->start = start;
        this->end = end;
    }
 
    bool operator<(const Pair &rhs) const {
        return (this->start < rhs.start);
    }
};
 
vector<int> points;
bool pairable[MAX_POINTS][MAX_POINTS];
int calc[MAX_POINTS][MAX_POINTS];
int height_map[MAX_POINTS][MAX_POINTS];
vector<Pair> trace_map[MAX_POINTS][MAX_POINTS];
 
bool valid(int start, int end) {
    // 일단 짝수개여야 하고
    if( (start - end) % 2 == 0 ) {
        return false;
    }
 
    // 색깔 갯수 쌍 맞는지 체크
    int black = 0, white = 0;
    for( int k = start; k <= end; k ++ ) {
        if( points[k] == 0 ) {
            white ++;
        } else {
            black ++;
        }
    }
 
    return white == black;
}
 
int get_max_height_of_section(int start, int end) {
    int height = 0;
    for( int i = start; i <= end; i ++ ) {
        for( int j = start + 1; j <= end; j ++ ) {
            if( height_map[i][j] > height ) {
                height = height_map[i][j];
            }
        }
    }
 
    return height;
}
 
int check_additional_height(int start, int end) {
    int arr[101];
    for( int i = 0; i <= 100; i ++ ) {
        arr[i] = 0;
    }
 
    for( int i = start; i <= end; i ++ ) {
        for( int j = i; j <= end; j ++ ) {
            if( calc[i][j] != INFINITE ) {
                arr[i] = 1;
                arr[j] = 1;
            }
        }
    }
 
    int count = 0;
    for( int i = start; i <= end; i ++ ) {
        if( arr[i] ) {
            count++;
        }
    }
    // printf("check_additional_height - (%d, %d) = %d\n", start, end, count);
    if( count == end - start + 1 ) {
        return 0;
    }
 
    return 1;
}
 
bool all_points_connected(int start, int end) {
    int arr[101];
    for( int i = 0; i <= 100; i ++ ) {
        arr[i] = 0;
    }
 
    for( int i = start; i <= end; i ++ ) {
        for( int j = i; j <= end; j ++ ) {
            if( calc[i][j] != INFINITE ) {
                arr[i] = 1;
                arr[j] = 1;
            }
        }
    }
 
    for( int i = start; i <= end; i ++ ) {
        if( arr[i] == 0 ) {
            return false;
        }
    }
 
    return true;
}
 
int calc_line_length(int start, int end, int max_height) {
    return max_height * 2 + (end - start);
}
 
void push_back_vector(vector<Pair> &dest, const vector<Pair> &src) {
    int size = src.size();
    for( int i = 0; i < size; i ++ ) {
        dest.push_back(src[i]);
    }
}
 
void solve() {
    int diagonal, i, j, k;
    int length = points.size();
 
    // pair가 맞춰지는지 배열을 계산
    for( i = 1; i <= length; i ++ ) {
        for( j = i; j <= length; j ++ ) {
            pairable[i][j] = valid(i, j);
            calc[i][j] = INFINITE;
        }
    }
 
    for( diagonal = 1; diagonal <= length; diagonal+=2 ) {
        for( i = 1; i < length - diagonal; i++ ) { 
            j = i + diagonal;
            if( ! valid(i, j) ) {
                continue;
            }
 
            bool flag = false;
            if( all_points_connected(i, j) ) {
                int max_height = get_max_height_of_section(i, j);
                int additional = check_additional_height(i, j);
                int v = calc[i+1][j-1] + calc_line_length(i, j, max_height + additional);
                if( calc[i][j] > v ) {
                    calc[i][j] = v;
                    height_map[i][j] = max_height + additional;
 
                    if( additional ) {
                        push_back_vector(trace_map[i][j], trace_map[i+1][j-1]);
                        trace_map[i][j].push_back(Pair(i, j));
                    } else {
                        flag = true;
                    }
                }
            }
 
            for( k = i; k <= j; k ++ ) {
                if( ! valid(i, k) || ! valid(k+1, j) ) {
                    continue;
                }
 
                int left = calc[i][k];
                left = left == INFINITE ? 0 : left;
                int right = calc[k+1][j];
                right = right == INFINITE ? 0 : right;
 
                int max_height = get_max_height_of_section(i, j);
                int additional = check_additional_height(i, j);
                int result;
                if( additional ) {
                    result = calc[i+1][j-1] + calc_line_length(i, j, max_height + additional);
                } else {
                    result = left + right;
                }
                if( calc[i][j] > result ) {
                    calc[i][j] = result;
                    height_map[i][j] = max_height + additional;
 
                    if( j - i == 1 ) {
                        trace_map[i][j].push_back(Pair(i, j));
                    } else {
                        if( additional ) {
                            push_back_vector(trace_map[i][j], trace_map[i+1][j-1]);
                            trace_map[i][j].push_back(Pair(i, j));
                        } else {
                            push_back_vector(trace_map[i][j], trace_map[i][k]);
                            push_back_vector(trace_map[i][j], trace_map[k+1][j]);
                        }
                    }
 
                    // printf("i:%3d j:%3d k:%3d result:%3d\n", i, j, k, result);
                    flag = false;
                }
            }
 
            if( flag ) {
                push_back_vector(trace_map[i][j], trace_map[i+1][j-1]);
                trace_map[i][j].push_back(Pair(i, j));
            }
        }
    }
}
 
int main(int argc, char const *argv[]) {
    int n;
 
    cin >> n;
    points.resize(n + 1);
    for( int i = 1; i <= n; i ++ ) {
        char c;
        cin >> c;
        points[i] = c - '0';
    }
 
    solve();
 
    // for( int i = 0; i <= n; i ++ ) {
    //  printf("%6d", i);
    // }
    // printf("\n");
    // for( int i = 1; i <= n; i ++ ) {
    //  printf("%6d", i);
    //  for( int j = 1; j <= n; j++ ) {
    //      printf("%6d", calc[i][j]);
    //  }
    //  printf("\n");
    // }
    // cout << endl;
 
    cout << calc[1][n] << endl;
 
    vector<Pair> &vec = trace_map[1][n];
    sort(vec.begin(), vec.end());
 
    for( int i = 0; i < vec.size(); i++ ) {
        Pair p = vec[i];
        printf("%d %d\n", p.start, p.end);
    }
 
    return 0;
}