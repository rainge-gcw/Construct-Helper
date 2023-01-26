/*-------------- ॐ --------------*/
#include<bits/stdc++.h>
#define int long long int
#define mod 1000000007
#define endl '\n'
#define pb push_back
#define vi vector<int>
#define vvi vector<vector<int>>
#define vpi vector<pair<int,int>>
#define mp make_pair
const int N = 1e5+10;
bool prime[1000000];
using namespace std;

int apowb(int a,int n)
{
	if(n<0)
	{
		n=abs(n);
		a=1/a;
	}
	int ans=1;
	while(n>0)
	{
		if(n&1)
		{
			ans=(ans*a)%mod;
			n--;
		}
		else 
		{
			a=(a*a)%mod;
			n>>=1;
		}
	}
	return ans;
}
int maxonesubstr(string s)
{
	int len=0;
	int ans=0;
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='0')
		len=0;
		else
		{
			len++;
			ans=max(ans,len);
		}
	}
	return ans;
}
void yes()
{
	cout<<"YES"<<endl;
}
void no()
{
	cout<<"NO"<<endl;
}
int maxzerosubstr(string s)
{
	int len=0;
	int ans=0;
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='1')
		len=0;
		else
		{
			len++;
			ans=max(ans,len);
		}
	}
	return ans;
}
int decimaltoany(int n,int b)
{
	int ans=0;
	int i=0;
	while(n)
	{
		 int rem=n%b;
		n/=b;
		ans+=rem*apowb(10LL,i);
		i++;
	}
	return ans;
}
void seive()
{
	memset(prime,true,sizeof(prime));
	prime[0]=prime[1]=false;
	for(int i=2;i*i<=1000000;i++)
	{
		if(prime[i]==true)
		{
			for(int j=i*i;j<=1000000;j+=i)
			{
				prime[j]=false;
			}
		}
	}
}
signed main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int t=1;
	cin>>t;
	while(t--)
	{
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		if(a==0)
		{
			cout<<1<<endl;
			continue;
		}
		int ans=a;
		int mini=min(b,c);
		ans+=2*mini;
		b-=mini;
		c-=mini;
		ans+=min(a+1,b+c+d);
		cout<<ans<<endl;
	}
	return(0);
}
/*-------------- ॐ --------------*/