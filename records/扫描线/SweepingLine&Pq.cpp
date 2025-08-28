//https://leetcode.cn/problems/minimum-interval-to-include-each-query/
//@@@
//line sweeping,priority queue,offline
class Solution{
public:
    vector<int> minInterval(vector<vector<int>>&intervals,vector<int>&queries){
        int n=intervals.size();
        int m=queries.size();
        sort(intervals.begin(),intervals.end());
        vector<pair<int,int>> Queries(m);
        for(int i=0;i<m;i++){
            Queries[i]={queries[i],i};
        }
        sort(Queries.begin(),Queries.end());
        auto cmp=[](const pair<int,int>&u,const pair<int,int>&v)->bool{
            return u.first>v.first;
        };
        priority_queue<pair<int,int>,vector<pair<int,int>>,decltype(cmp)> pq;
        vector<int> ans(m);
        for(int i=0,j=0;i<m;i++){
            while(j<n&&intervals[j][0]<=Queries[i].first){
                pq.push({intervals[j][1]-intervals[j][0]+1,intervals[j][1]});
                j++;
            }
            while(!pq.empty()&&pq.top().second<Queries[i].first){
                pq.pop();
            }
            if(!pq.empty()){
                ans[Queries[i].second]=pq.top().first;
            }else{
                ans[Queries[i].second]=-1;
            }
        }
        return ans;
    }
};