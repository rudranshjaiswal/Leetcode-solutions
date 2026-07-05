class Solution {
public:
    int maxDigitRange(std::vector<int>& nums) {
        int max_range = -1;
        int sum = 0;

        for (int num : nums) {
            int temp = num;
            int min_digit = 9;
            int max_digit = 0;

            // Extract digits to find min and max
            while (temp > 0) {
                int digit = temp % 10;
                min_digit = std::min(min_digit, digit);
                max_digit = std::max(max_digit, digit);
                temp /= 10;
            }

            int current_range = max_digit - min_digit;

            // Update max range and sum accordingly
            if (current_range > max_range) {
                max_range = current_range;
                sum = num; // Start a new sum for the new maximum range
            } else if (current_range == max_range) {
                sum += num; // Accumulate if it matches the maximum range
            }
        }

        return sum;
    }
};