#include <iostream>
#include <stdlib.h>
#include <math.h>

#define MAP_WIDTH 1024
#define MAP_HEIGHT 1024

using namespace std;


int population_map[2000][2000];
int max_count = -99999;
int answer_x, answer_y;

bool logging = false;

void init() {
    for( int i = 0; i < 2000; i ++ ) {
        for( int j = 0; j < 2000; j ++ ) {
            population_map[i][j] = 0;
        }
    }
    
    max_count = -99999;
    answer_x = 0;
    answer_y = 0;
}

int count_line_horizontal(int sx, int sy, int dx) {
    int count = 0;
    for( int i = sx; i <= dx; i ++ ) {
        if( i < 0 || i > MAP_HEIGHT ) {
            continue;
        }
        count += population_map[sy][i];
    }
    
    return count;
}

int count_line_vertical(int sx, int sy, int dy) {
    if( logging ) {
        // printf("count_line_vertical - sx : %d, sy : %d, dy : %d\n", sx, sy, dy);
    }
    
    int count = 0;
    for( int i = sy; i <= dy; i ++ ) {
        if( i < 0 || i > MAP_HEIGHT || sx < 0 || sx > MAP_WIDTH ) {
            continue;
        }
        
        if( logging && population_map[i][sx] != 0 ) {
            // printf("population_map[%d][%d] = %d\n", i, sx, population_map[i][sx]);
        }
        count += population_map[i][sx];
    }
    
    return count;
}

int count_rect(int sx, int sy, int ex, int ey) {
    // printf("count_rect : (%d, %d), (%d, %d)\n", sx, sy, ex, ey);
    
    int count = 0;

    for( int i = sy; i <= ey; i ++ ) {
        if( i < 0 || i > MAP_HEIGHT ) {
            continue;
        }
        
        for( int j = sx; j <= ex; j ++ ) {
            if( j < 0 || j > MAP_WIDTH ) {
                continue;
            }
            
            count += population_map[i][j];
        }
    }
    
    return count;
}

int set_bound(int n) {
    if( n < 0 ) {
        return 0;
    }
    if( n > MAP_WIDTH ) {
        return MAP_WIDTH;
    }
    
    return n;
}

void renewal_max(int count, int x, int y) {
    if( max_count < count ) {
        max_count = count;
        answer_x = x;
        answer_y = y;
        
        // printf("max 갱신 : %d (%d, %d)\n", count, x, y);
    }
}

void solve() {
    int min_x = 9999, min_y = 9999;
    int max_x = -9999, max_y = -9999;
    int d, n;
    cin >> d;
    cin >> n;
    for(int i = 0; i < n; i++ ) {
        int x, y, p;
        cin >> x >> y >> p;
        population_map[y][x] = p;
        
        min_x = min_x > x ? x : min_x;
        min_y = min_y > y ? y : min_y;
        
        max_x = max_x > x ? max_x : x;
        max_y = max_y > y ? max_y : y;
    }
    
    min_x = 0;
    min_y = 0;
    max_x = MAP_WIDTH;
    max_y = MAP_HEIGHT;
    
    int tmp, i, j, sx, sy, dx, dy;
    int count = 0;
    for( i = min_y; i <= max_y - d; i ++ ) {
        j = min_x;
        sx = j - d;
        sy = i - d;
        dx = j + d;
        dy = i + d;
        count = count_rect(sx, sy, dx, dy);
        renewal_max(count, j, i);
        if( count == max_count ) {
            // printf("(%d, %d) to (%d, %d) : %d\n", sx, sy, dx, dy, count);
        }
        
        for( j = min_x; j <= max_x - d; j ++ ) {
            // logging = false;
            
            // printf("(%3d, %3d)\n", j, i);
            sx = j - d;
            sy = i - d;
            dy = i + d;
            tmp = count_line_vertical(sx, sy, dy) * -1;
            count += tmp;
            // printf("count : %d, tmp : %d :: sub - sx : %d, sy : %d, dy : %d\n", count, tmp, sx, sy, dy);
            
            sx = j + d + 1;
            sy = i - d;
            dy = i + d;
            tmp = count_line_vertical(sx, sy, dy);
            count += tmp;
            // printf("count : %d, tmp : %d :: add - sx : %d, sy : %d, dy : %d\n", count, tmp, sx, sy, dy);
            
            renewal_max(count, j + 1, i);
            if( count == max_count ) {
                // logging = true;
                // printf("x : %d, y : %d\n", j, i);
                sx = j - d;
                sy = i - d;
                dy = i + d;
                tmp = count_line_vertical(sx, sy, dy) * -1;
                // printf("count : %d, tmp : %d :: sub - sx : %d, sy : %d, dy : %d\n", count, tmp, sx, sy, dy);
                sx = j + d + 1;
                sy = i - d;
                dy = i + d;
                tmp = count_line_vertical(sx, sy, dy);
                // printf("count : %d, tmp : %d :: add - sx : %d, sy : %d, dy : %d\n", count, tmp, sx, sy, dy);
            }
        }
    }
    
    
    cout << answer_x << ' ' << answer_y << ' ' << max_count << endl;
}

int main() {
    int n;
    cin >> n;
    
    for( int i = 0; i < n; i ++ ) {
        init();
        solve();
    }
    
    return 0;
}