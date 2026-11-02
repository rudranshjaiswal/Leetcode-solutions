int singleNumber(int* nums, int numsSize) {
    int i;
    int result = 0;
    for (i = 0; i< numsSize; i++){
        result ^= nums[i];
    }

    return result;
    
}