//@@@
deque<ll> dq;
for(ll i=0;i<n;i++){
    while(!dq.empty()&&a[dq.back()]<=a[i]){
        dq.pop_back();
    }
    dq.push_back(i);
    while(dq.front()<=i-k){
        dq.pop_front();
    }

    ...
    
}



	
