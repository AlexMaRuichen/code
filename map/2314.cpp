#include <stdio.h>
#include <string.h>
#include <queue>
#include <set>
using namespace std;
int w[3];
int h[3];
int sx[3];
int sy[3];
bool a[3][10][10];
int dx[]={-1,1,0,0};
int dy[]={0,0,-1,1};
struct state
{
	state(int d):d(d)
	{
		for(int i=2;i>=0;i--) 
		{
			sx[i]-=sx[0];
			sy[i]-=sy[0];
		}
		memcpy(ssx,sx,sizeof(ssx));
		memcpy(ssy,sy,sizeof(ssy));
	}
	state(const state& st) 
	{
		d=st.d;
		memcpy(ssx,st.ssx,sizeof(ssx));
		memcpy(ssy,st.ssy,sizeof(ssy));
	}
	state& operator=(const state& st)
	{
		d=st.d;
		memcpy(ssx,st.ssx,sizeof(ssx));
		memcpy(ssy,st.ssy,sizeof(ssy));
		return *this;
	}
	void unpack() 
	{
		memcpy(sx,ssx,sizeof(ssx));
		memcpy(sy,ssy,sizeof(ssy));
	}
	bool operator<(const state& st) const
	{
		int r=memcmp(ssx,st.ssx,sizeof(ssx));
		if(!r) 
			r=memcmp(ssy,st.ssy,sizeof(ssy));
		return r<0;
	}
	int d;
	int ssx[3];
	int ssy[3];
};
bool intersect(int i,int j)
{
	return sx[i]<sx[j]+w[j] && sx[j]<sx[i]+w[i] && sy[i]<sy[j]+h[j] && sy[j]<sy[i]+h[i];
}
bool check()
{
	for(int i=0;i<3;i++) 
	{
		if(sx[i]<-20 || sx[i] > 20 || sy[i]<-20 || sy[i] > 20)
			return false;
		for(int j=i+1;j<3;j++) 
			for(int x=0;x<w[i];x++) 
				for(int y=0;y<h[i];y++)
				{
					if(!a[i][x][y]) 
						continue;
					int nx=sx[i]+x-sx[j],ny=sy[i]+y-sy[j];
					if(nx<0 || nx>=w[j] || ny<0 || ny>=h[j] ||!a[j][nx][ny]) 
						continue;
					return false;
				}
	}
	return true;
}
queue<state> q;
set<state> v;
int main() 
{
	int n[3];
	scanf("%d%d%d",&n[0],&n[1],&n[2]);
	for(int i=0;i<3;i++)
	{
		int mx=10,my=10;
		int gx=0,gy=0;
		for(int j=0;j<n[i];j++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			a[i][x][y]=true;
			mx=min(mx,x);my=min(my,y);
			gx=max(gx,x+1);gy=max(gy,y+1);
		}
		w[i]=gx-mx;h[i]=gy-my;
		for(int x=mx;x<10;x++)
			for(int y=my;y<10;y++)
			{
				a[i][x-mx][y-my]=a[i][x][y];
				if(mx || my) 
					a[i][x][y]=false;
			}
		sx[i]=mx;
		sy[i]=my;
	}

	q.push(state(0));
	while(!q.empty())
	{
		state st=q.front();
		q.pop();
		st.unpack();
		if(!intersect(0,1) && !intersect(0,2) && !intersect(1,2))
		{
			printf("%d\n",st.d);
			return 0;
		}
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<4;j++) 
			{
				st.unpack();
				sx[i]+=dx[j];
				sy[i]+=dy[j];
				state nst=state(st.d+1);
				if(v.insert(nst).second && check()) 
					q.push(nst);
			}
		}
	}
	printf("-1\n");
}
