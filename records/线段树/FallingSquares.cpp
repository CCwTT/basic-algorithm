//https://leetcode.cn/problems/falling-squares/
//@@@
//seg,discretization
typedef int ll;
class segment_tree{
public:
    ll n;
    vector<ll> mx,rstval;
    vector<bool> rst;

    segment_tree(ll sz):n(sz-1),mx(sz<<2),rst(sz<<2),rstval(sz<<2) {}

    void up(ll p){
        mx[p]=max(mx[p<<1],mx[p<<1|1]);
    }

    void rst_update(ll p,ll l,ll r,ll v){
        mx[p]=v;
        rst[p]=true;
        rstval[p]=v;
    }

    void down(ll p,ll l,ll r){
        ll m=l+r>>1;
        if(rst[p]){
            rst_update(p<<1,l,m,rstval[p]);
            rst_update(p<<1|1,m+1,r,rstval[p]);
            rst[p]=false;
        }
    }

    void update(ll p,ll l,ll r,ll x,ll y,ll v){
        if(x<=l&&r<=y){
            rst_update(p,l,r,v);
            return;
        }
        ll m=l+r>>1;
        down(p,l,r);
        if(x<=m) update(p<<1,l,m,x,y,v);
        if(y>m) update(p<<1|1,m+1,r,x,y,v);
        up(p); 
    }

    void updateHeight(ll p,ll l,ll r,ll x,ll y,ll v){
        ll prevmx=query(p,l,r,x,y);
        update(p,l,r,x,y,prevmx+v);
    }

    ll query(ll p,ll l,ll r,ll x,ll y){
        if(x<=l&&r<=y){
            return mx[p];
        }
        ll m=l+r>>1;
        down(p,l,r);
        ll res=INT_MIN;
        if(x<=m) res=max(res,query(p<<1,l,m,x,y));
        if(y>m) res=max(res,query(p<<1|1,m+1,r,x,y));
        return res;
    }
};



class Discretizer{
public:
    vector<ll> disc;
    Discretizer() {}

    void insert(ll x){
        disc.push_back(x);
    }

    ll discretize(){
        sort(disc.begin(),disc.end());
        disc.erase(unique(disc.begin(),disc.end()),disc.end());
        return disc.size();
    }

    ll query(ll x){
        return lower_bound(disc.begin(),disc.end(),x)-disc.begin()+1;
    }
};

class Solution {
public:
    vector<ll> fallingSquares(vector<vector<ll>>& positions) {
        ll n=positions.size();
        Discretizer disc;
        for(auto& position:positions){
            ll L=position[0];
            ll len=position[1];
            ll R=L+len-1;
            disc.insert(L);
            disc.insert(R);
        }
        n=disc.discretize();
        segment_tree seg(n+1);
        vector<ll> ans;
        for(auto& position:positions){
            ll L=position[0];
            ll len=position[1];
            ll R=L+len-1;
            seg.updateHeight(1,1,seg.n,disc.query(L),disc.query(R),len);
            ans.push_back(seg.query(1,1,seg.n,1,n));
        }
        return ans;
    }
};