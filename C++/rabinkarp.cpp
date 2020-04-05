#include<bits/stdc++.h>
//#define endl '\n'
#define ll long long
#define mod 1000000007
using namespace std;

int c[100000];

int power(int base,int exponent)
{
    if (exponent == 0) return 1;
    int temp = power(base, exponent/2);
    if (exponent % 2 == 0)
        return (temp * temp)%mod;
    else
        return (base * temp * temp)%mod;
}

int rabin_karp(string txt,string pat){
    int k=0,t=txt[0],p=pat[0],a=pat.length(),b=txt.length(),flag=0,x=power(10,a-1);
    for(int i=1;i<a;i++){
        p=10*p+pat[i];p=p%mod;
        t=10*t+txt[i];t=t%mod;
    }
    for(int i=0;i<=b-a;i++){
        flag=0;
        if(p==t){
            for(int j=0;j<a;j++){
                if(pat[j]!=txt[i+j]){
                    flag=1;
                    break;
                }
            }
            if(!flag){
                c[k]=i;
                k++;
            }
        }
        if(i<b-a){
            t=(t-txt[i]*x)*10+txt[i+a];t=t%mod;
            if(t<0) t+=mod;
        }
    }
    return k;
}

int main(){
    string pat,txt;
    cout<<"enter text"<<endl;
    getline(cin,txt);
    cout<<"enter pattern"<<endl;
    getline(cin,pat);
    int n=rabin_karp(txt,pat);
    if(n==0) cout<<"pattern not found"<<endl;
    else cout<<"pattern found at"<<endl;
    for(int i=0;i<n;i++) cout<<c[i]<<" ";
    cout<<endl;
    return 0;
}
