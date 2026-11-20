class Solution {
public:
    vector<int> constructRectangle(int area) {
        int w,l;
        for ( w = sqrt(area); w >= 1; w-- )
        {
            if (area % w == 0){
                l = area / w;
                return{l,w};

            }
        }   
    return {area, 1};
    }
};