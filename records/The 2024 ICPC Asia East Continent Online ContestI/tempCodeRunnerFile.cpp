bool check(ll x){
    for(ll i=1;i<=n;i++){
        a[i]=A[i]>=x;
    }
    partial_sum(a+1,a+n+1,sum1+1);
    for(ll i=1;i<=n;i++){
        b[i][i]=a[i];
    }
    for(ll len=2;len<=n;len++){
        for(ll i=1,j=i+len-1;j<=n;i++,j++){
            b[i][j]=(len/2+1<=(sum1[j]-sum1[i-1]));
        }
    }
    for(ll j=1;j<=n;j++){
        for(ll i=1;i<=j;i++){
            sum2[i][j]+=sum2[i-1][j];
        }
    }
    for(ll i=1;i<=n;i++){
        c[i][i]=b[i][i];
    }
    for(ll len=2;len<=n;len++){
        for(ll i=1,j=i+len-1;j<=n;i++,j++){
            c[i][j]=c[i][j-1]+sum2[j][j]-sum2[i-1][j];
        }
    }
    ll ans=0;
    for(ll i=1;i<=n;i++){
        for(ll j=i;j<=n;j++){
            ans+=c[i][j]>=(j-i+1)*(j-i+2)/2/2+1;
        }
    }
    return ans>=n*(n+1)/2/2+1;
}