#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();
        
        // Step 1: Build the adjacency list and calculate in-degrees for topological sort
        // We pre-filter edges that go to/from offline nodes to save time.
        struct Edge {
            int to, cost;
        };
        vector<vector<Edge>> adj(n);
        for (const auto& e : edges) {
            int u = e[0], v = e[1], cost = e[2];
            if (online[u] && online[v]) {
                adj[u].push_back({v, cost});
            }
        }

        // Find topological order of the DAG
        vector<int> inDegree(n, 0);
        for (int u = 0; u < n; ++u) {
            for (const auto& edge : adj[u]) {
                inDegree[edge.to]++;
            }
        }

        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (inDegree[i] == 0) q.push(i);
        }

        vector<int> topoOrder;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topoOrder.push_back(u);
            for (const auto& edge : adj[u]) {
                if (--inDegree[edge.to] == 0) {
                    q.push(edge.to);
                }
            }
        }

        // Helper function to check if a minimum edge cost of 'mid' is possible
        auto check = [&](int mid) -> bool {
            // dp[i] stores the minimum total cost to reach node i from node 0
            // using only edges with cost >= mid
            vector<long long> dp(n, -1); 
            dp[0] = 0;

            for (int u : topoOrder) {
                if (dp[u] == -1) continue; // Node u is unreachable from 0 under current constraints
                
                for (const auto& edge : adj[u]) {
                    if (edge.cost >= mid) {
                        if (dp[edge.to] == -1 || dp[u] + edge.cost < dp[edge.to]) {
                            dp[edge.to] = dp[u] + edge.cost;
                        }
                    }
                }
            }
            return dp[n - 1] != -1 && dp[n - 1] <= k;
        };

        // Step 2: Binary Search over the range of possible edge costs
        int low = 0, high = 1e9, ans = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (check(mid)) {
                ans = mid;       // Try to find a larger minimum edge cost
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return ans;
    }
};