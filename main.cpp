#include <iostream>
#include <vector>

using namespace std;

/*
 *檢查目前皇后的行，正對角線，反對角線是否有其他皇后存在，如果有回傳false，否則回傳true
 */
template <class T>
bool check(T &visited, int x, int y, int size) {
    return !visited[1][x] && !visited[2][x - y + size] && !visited[3][x + y];
}

/*
 * 利用回溯法來放置每列的皇后
 */
template <class T, class L>
void backtracking(T &tmp, T &res, L &visited, int m, int n, int size, int endSize, int depth) {
    //皇后已達最大值，剪枝
	if (res.size() == endSize)
		return;
	
	//當n等於depth時，表示走到底了，剪枝
	if (n == depth) {
        //如果tmp長於res，則更新res
    	if (tmp.size() > res.size()) {
            res.clear();

            for (auto v : tmp)
                res.push_back(v);
        }

        return;
    }

    //如果第depth烈沒有回後，則利用for迴圈放置第depth列第i行的皇后，並利用回溯法往下一列遞迴
	if (!visited[0][depth]) {
        for (int i = 0; i < m; i ++) {
            if (check(visited, i, depth, size)) {
                //將皇后放置的位置存至tmp
                tmp.push_back(vector<int>{i, depth});

                /*將目前皇后所在的行，正對角線，反對角線標示
                *因一列只會放一個皇后，故不需更改列的値
                */
                visited[1][i] = true; visited[2][i - depth + size] = true; visited[3][i + depth] = true;
                
                //進入下一列的遞迴
                backtracking(tmp, res, visited, m, n, size, endSize, depth + 1);

                //撤銷選擇
                tmp.pop_back();
                visited[1][i] = false; visited[2][i - depth + size] = false; visited[3][i + depth] = false;
            }
        }
    }

    //以不更改第depth列的狀態繼續往下一列遞迴
    backtracking(tmp, res, visited, m, n, size, endSize, depth + 1);
}

int main(void) {
    int m, n, k, x, y;
    cin >> m >> n >> k;

    //size用來配置visited子陣列的空間，endSize來判定皇后是否放到最大值
    int size = m > n ? m : n, endSize = m > n ? n - k: m - k;

    //tmp來暫存，為回溯法的選擇列表，res則來存取可存放罪的皇后的結果
    vector<vector<int>> tmp, res;

    //存取列，行，正對角線與反對角線，若該線上已存在皇后，則設為true，預設為false
    vector<vector<bool>> visited(4, vector<bool>(size * 2, false));

    //輸入預設的皇后位置
    for (int i = 0; i < k; i ++) {
        cin >> x >> y;

        //先將預設的皇后所在的列，行，正對角線與反對角線標示，x-y因有可能是負數，故加上size使其恆為正
        visited[0][y] = true; visited[1][x] = true; visited[2][x - y + size] = true; visited[3][x + y] = true;
    }

    //開始遞迴
    backtracking(tmp, res, visited, m, n, size, endSize, 0);

    //輸出長度
    cout << res.size() << endl; 
    
    //輸出皇后座標
    for (auto v : res)
        cout << v[0] << " " << v[1] << endl;
}
