//https://leetcode.cn/problems/the-skyline-problem/
//@@@
//line sweeping,discretization,pq
class Discretizer{
public:
    vector<int> disc;
    Discretizer() {}

    void insert(int x){
        disc.push_back(x);
    }

    int discretize(){
        sort(disc.begin(),disc.end());
        disc.erase(unique(disc.begin(),disc.end()),disc.end());
        return disc.size();
    }

    int query(int x){
        return lower_bound(disc.begin(),disc.end(),x)-disc.begin();
    }
};

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        int n = buildings.size();
        Discretizer disc;
        for(auto& building:buildings){
            disc.insert(building[0]);
            disc.insert(building[1]);
            disc.insert(building[1]-1);
        }
        int m=disc.discretize();
        for(auto& building:buildings){
            building[0]=disc.query(building[0]);
            building[1]=disc.query(building[1]-1);
        }
        priority_queue<pair<int,int>> pq;
        vector<int> height(m,0);
        for(int i=0,j=0;i<m;i++){
            while(j<n&&buildings[j][0]<=i){
                pq.push({buildings[j][2],buildings[j][1]});
                j++;
            }
            while(!pq.empty()&&pq.top().second<i){
                pq.pop();
            }
            if(!pq.empty()){
                height[i]=pq.top().first;
            }
        }
        vector<vector<int>> ans;
        for(int i=0,lastval=0;i<m;i++){
            if(lastval!=height[i]){
                ans.push_back({disc.disc[i],height[i]});
            }
            lastval=height[i];
        }
        return ans;
    }
};
    
    
    
    