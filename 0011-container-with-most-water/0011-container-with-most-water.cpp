class Solution {
public:
    int maxArea(vector<int>& height) {
        int min_height = height[0];
        int max_height = height[height.size() - 1];
        int min_idx = 0;
        int max_idx = height.size() - 1;

        if (max_height < min_height) {
            min_height = max_height;
            min_idx = max_idx;
            max_height = height[0];
            max_idx = 0;
        }

        int width = height.size() - 1; // Fixed variable name from 'w'
        int max_area = min_height * width;

        while (width > 0) {
            int idx = min_idx;
            while (idx >= 0 && idx < height.size() && height[idx] <= min_height) {
                if (min_idx < max_idx)
                    idx++;
                else
                    idx--;
                width--;
                if (width < 1)
                    break;
            }

            if (width < 1)
                break;

            if (height[idx] > max_height) {
                min_height = max_height;
                min_idx = max_idx;
                max_idx = idx;
                max_height = height[idx]; // Completed line 34
            } else {
                // Case where height[idx] is between min_height and max_height
                min_height = height[idx];
                min_idx = idx;
            }

            // Update max_area with the newly found container
            max_area = max(max_area, min_height * width);
        }

        return max_area;
    }
};
