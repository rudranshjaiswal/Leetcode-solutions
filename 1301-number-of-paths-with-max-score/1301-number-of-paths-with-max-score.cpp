class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        int MOD = 1e9 + 7;
        
        // dp[i][j] stores {max_score, path_count}
        // Initialized to {-1, 0} where -1 means unreachable
        vector<vector<pair<int, int>>> dp(n, vector<pair<int, int>>(n, {-1, 0}));
        
        // Base case: Start at the bottom-right corner ('S')
        dp[n - 1][n - 1] = {0, 1};
        
        // Iterate backwards from the bottom-right to the top-left
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                // Skip the starting cell since it's already set
                if (i == n - 1 && j == n - 1) continue;
                
                // Skip obstacles
                if (board[i][j] == 'X') continue;
                
                int max_score = -1;
                long long total_paths = 0;
                
                // The 3 possible directions we could come from: Down, Right, Diagonal Down-Right
                int dirs[3][2] = {{1, 0}, {0, 1}, {1, 1}};
                
                for (auto& dir : dirs) {
                    int ni = i + dir[0];
                    int nj = j + dir[1];
                    
                    // Check boundaries and if the cell is reachable
                    if (ni < n && nj < n && dp[ni][nj].first != -1) {
                        int prev_score = dp[ni][nj].first;
                        int prev_count = dp[ni][nj].second;
                        
                        if (prev_score > max_score) {
                            max_score = prev_score;
                            total_paths = prev_count;
                        } else if (prev_score == max_score) {
                            total_paths = (total_paths + prev_count) % MOD;
                        }
                    }
                }
                
                // If this cell can be reached from at least one valid path
                if (max_score != -1) {
                    int cell_value = (board[i][j] == 'E') ? 0 : (board[i][j] - '0');
                    dp[i][j] = {max_score + cell_value, total_paths};
                }
            }
        }
        
        // If the top-left ('E') is unreachable, return {0, 0}
        if (dp[0][0].first == -1) {
            return {0, 0};
        }
        
        return {dp[0][0].first, dp[0][0].second};
    }
};