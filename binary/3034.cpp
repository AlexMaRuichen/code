#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
class AngryCows
{
	int num;
	int ans;
	vector <int> bak;
	bool check(int mid)
	{
		int last=0,ans=0;
		for(int i=0;i<bak.size();i++)
			if(bak[i]-bak[last]>mid)
				last=i,++ans;
		++ans;
		return ans<=num;
	}
public:
	int solve(int n,int k,vector <int> &pos)
	{
		sort(pos.begin(),pos.end());
		bak=pos;
		num=k;
		int l=pos[0],r=pos[n-1],mid;
		while(l<r)
		{
			mid=l+r>>1;
			if(check(mid<<1))
				r=mid;
			else
				l=mid+1;
		}
		return l;
	}
}cls;
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	vector <int> pos(n);
	for(int i=0;i<n;i++)
		scanf("%d",&pos[i]);
	printf("%d\n",cls.solve(n,k,pos));
}
