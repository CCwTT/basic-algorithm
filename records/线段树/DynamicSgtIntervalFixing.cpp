//https://leetcode.cn/problems/count-integers-in-intervals/
//@@@
//dynamic seg
//no need for lazy update (interval fixing)
//New!What's interval fixing?
//When an interval is updated,next time it or its child interval is updated,nothing changes.I call the phenomemon interval fixing.
typedef long long ll;
class CountIntervals {
public:
	ll n,lim,tail;
	vector<ll> le,ri,sum;

    CountIntervals() {
        n=1e9;
        lim=700000;
        tail=1;
        le.assign(lim,0);
	    ri.assign(lim,0);
	    sum.assign(lim,0); 
    }

	void up(ll p){
		sum[p]=sum[le[p]]+sum[ri[p]];
	}

	void update(ll p,ll l,ll r,ll x,ll y){
		if(sum[p]==r-l+1) return; //This exact line is the core of interval fixing branch proneness.
		if(x<=l&&r<=y){
			sum[p]=r-l+1;
			return;
		}
		ll m=l+r>>1;
		if(x<=m){
			if(le[p]==0) le[p]=++tail;
			update(le[p],l,m,x,y);
		}
		if(y>m){
			if(ri[p]==0) ri[p]=++tail;
			update(ri[p],m+1,r,x,y);
		}
		up(p);
	}

	void add(ll l,ll r){
		update(1,1,n,l,r);
	}
    
    int count() {
        return sum[1];
    }
};

/**
 * Your CountIntervals object will be instantiated and called as such:
 * CountIntervals* obj = new CountIntervals();
 * obj->add(left,right);
 * int param_2 = obj->count();
 */