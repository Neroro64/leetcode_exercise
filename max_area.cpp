class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int max_area = 0;
        int m = grid.size();
        int n = grid[0].size();
        
        for (int i = 0; i < m; ++i){
            for (int j = 0; j < n; ++j){
                int area = 0;
                search(grid, &area, i, j, m, n);    
            }
        }
        return max_area;
    }
    
    void search(vector<vector<int>> &grid, int *area, int i, int j, int m, int n){
        if (grid[i][j] == 0 || i < 0 ||i >= m || j < 0 || j >= n)
            return;
        else {
            ++*area;
            grid[i][j] = 0;
            
            // left
            search(grid, area, i, j-1, m, n);
            // right 
            search(grid, area, i, j+1, m, n);
            // up 
            search(grid, area, i-1, j, m, n);
            // down
            search(grid, area, i+1, j, m, n);
        }
    }
};