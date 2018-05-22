#include<iostream>
using namespace std;
int main()
{
	int x1,x2,x3,y1,y2,y3;
	while(cin>>x1>>y1>>x2>>y2>>x3>>y3&&(x1||x2||x3||y1||y2||y3))
	{
		int i=(x2-x1)*(y3-y1)-(x3-x1)*(y2-y1);
		if(i<0) cout<<"1"<<endl;
		else cout<<"0"<<endl;
	}
	return 0;
}
