#include <iostream>
#include <cassert>
#include <vector>
#include <string>
using namespace std;
// 구슬탈출과 같은 코드 : 제한 횟수가 5로 바뀌고 , 비트마스크 k를 4진법 수 배열로 변환하는것은 동일
const int LIMIT = 5;
vector<int> gen(int k) {
    vector<int> a(LIMIT);
    for (int i=0; i<LIMIT; i++) {
        a[i] = (k&3);
        k >>= 2;
    }
    return a;
}
// 실제 보드 a를 dirs 이동배열의 이동방향 (5개) 에 따라 블록들을 이동시킨다. 
int check(vector<vector<int>> &a, vector<int> &dirs) {
  // 블록 copy
    int n = a.size();
    // pair<블록 값, 이동시 합쳐짐 여부> 저장
    vector<vector<pair<int,bool>>> d(n, vector<pair<int,bool>>(n));
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            d[i][j].first = a[i][j];
        }
    }
    // 0: down, 1: up, 2: left, 3: right
    // 초기에는 이번 이동에 대하여 모든 블록이 합쳐지지 않은 상태 
    for (int dir : dirs) {
        bool ok = false;
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                d[i][j].second = false;
            }
        }
        while (true) {
            ok = false; // 해당 이동방향을 통하여 이동하였는지 여부, 이동 안했다면 더이상 이동방향으로 움직이는 의미 X=>다음 이동 으로
            if (dir == 0) {
              // 각 방향에 따라 변경해야 하는 부분 . 아래의 경우, 아래부터 이동, 맨 밑 블록은 어차피 이동 못하므로 그 위부터 
                for (int i=n-2; i>=0; i--) {
                    for (int j=0; j<n; j++) {
                        if (d[i][j].first == 0) continue;
                        if (d[i+1][j].first == 0) { // 다음 방향 칸이 빈칸인경우 처리
                            d[i+1][j].first = d[i][j].first;
                            d[i+1][j].second = d[i][j].second;
                            d[i][j].first = 0;
                            ok = true;
                        } else if (d[i+1][j].first == d[i][j].first) { // 다음 방향칸이 빈칸이 아닌 블록 && 현재 블록과 같은값=>합친다. 
                            if (d[i][j].second == false && d[i+1][j].second == false) {
                                d[i+1][j].first *= 2;
                                d[i+1][j].second = true;
                                d[i][j].first = 0;
                                ok = true;
                            }
                        }
                    }
                }
            } else if (dir == 1) { // 위로 이동
                for (int i=1; i<n; i++) { // 위에서 두번쨰부터 
                    for (int j=0; j<n; j++) {
                        if (d[i][j].first == 0) continue;
                        if (d[i-1][j].first == 0) {
                            d[i-1][j].first = d[i][j].first;
                            d[i-1][j].second = d[i][j].second;
                            d[i][j].first = 0;
                            ok = true;
                        } else if (d[i-1][j].first == d[i][j].first) {
                            if (d[i][j].second == false && d[i-1][j].second == false) {
                                d[i-1][j].first *= 2;
                                d[i-1][j].second = true;
                                d[i][j].first = 0;
                                ok = true;
                            }
                        }
                    }
                }
            } else if (dir == 2) { //왼쪽으로 이동
                for (int j=1; j<n; j++) { //왼쪽에서 2번째부터
                    for (int i=0; i<n; i++) {
                        if (d[i][j].first == 0) continue;
                        if (d[i][j-1].first == 0) {
                            d[i][j-1].first = d[i][j].first;
                            d[i][j-1].second = d[i][j].second;
                            d[i][j].first = 0;
                            ok = true;
                        } else if (d[i][j-1].first == d[i][j].first) {
                            if (d[i][j].second == false && d[i][j-1].second == false) {
                                d[i][j-1].first *= 2;
                                d[i][j-1].second = true;
                                d[i][j].first = 0;
                                ok = true;
                            }
                        }
                    }
                }
            } else if (dir == 3) {//오른쪽으로 이동
                for (int j=n-2; j>=0; j--) { //오른쪽에서 두번쨰부터
                    for (int i=0; i<n; i++) {
                        if (d[i][j].first == 0) continue;
                        if (d[i][j+1].first == 0) {
                            d[i][j+1].first = d[i][j].first;
                            d[i][j+1].second = d[i][j].second;
                            d[i][j].first = 0;
                            ok = true;
                        } else if (d[i][j+1].first == d[i][j].first) {
                            if (d[i][j].second == false && d[i][j+1].second == false) {
                                d[i][j+1].first *= 2;
                                d[i][j+1].second = true;
                                d[i][j].first = 0;
                                ok = true;
                            }
                        }
                    }
                }
            } 
            if (ok == false) break; // 이동 하지 않았으면 더 이상 이번 이동을 할 필요 X
        }
    }
    int ans = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (ans < d[i][j].first) {
                ans = d[i][j].first;
            }
        }
    }
    return ans;
}
int main() {
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int> (n));
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cin >> a[i][j];
        }
    }
    //정답을 찾는 과정 : 모든 경우의수 1<<(2*5) => 2^10= 4^5 에 대한 비트마스크 생성하고, 
    // 각 비트마스크 값(상태)마다의 보드 최댓값을 ans와 비교한다.
    int ans = 0;
    for (int k=0; k<(1<<(LIMIT*2)); k++) {
        vector<int> dir = gen(k);
        int cur = check(a, dir);
        if (ans < cur) ans = cur;
    }
    cout << ans << '\n';
    return 0;
}