/* 

输入数据 (输入数据都在int范围中)
第一行 自己坐标
第二行 三个目的点坐标 x1 y1 x2 y2 x3 y3
以下每行 都有四个坐标 代表障碍物  空行结束输入 

基本思想： 
	从自身出发，分别根据坐标计算出自己与障碍物的各个点的连线与x轴的夹角，也就是正弦值 
	也算出自身和目的地坐标连线的夹角，通过夹角的比较来确定自身和目的地的
	连线之间是否有障碍物 
*/ 
#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#define SIN(a,b) (double)(b.y-a.y)/(double)sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y))
#define PI 3.1415926
using namespace std;

typedef struct coor { // 用来存储坐标 
	int x,y; 
}COOR;

typedef struct angle { // 用来存储每个障碍物与自身的最大夹角和最小夹角 
	double maxAngle;
	double minAngle;
}ANGLE;


int main(void)
{
	// 输入数据和储存数据 
	COOR my;
	COOR d1,d2,d3;

	cin >> my.x >> my.y;
	cin >> d1.x >> d1.y >> d2.x >> d2.y >> d3.x >> d3.y;
	getchar(); // 吸收换行符 
	
	vector<COOR> v;
	string str;
	while( 1 ) {
		getline(cin,str);
		if( str.length() == 0 ) break;
		for( int i = 0; i < str.length(); i += 4 ) {
			COOR t;
			t.x = str[i] - '0';
			t.y = str[i+2] - '0';
			v.push_back(t);
		}
	}
	
	// 处理数据
	// 先保存自身和三个目的地点的连线夹角
	double a1,a2,a3;
	a1 = SIN(my,d1);
	a2 = SIN(my,d2);
	a3 = SIN(my,d3);
	
	// 处理障碍物
	vector<ANGLE> a; 
	for( int i = 0; i < v.size(); i += 4 ) { // 找出每个障碍物的最大最小角度 存到a中 
		ANGLE tmp;
		double t1,t2,t3,t4;
		t1 = SIN(my,v[i]); 
		t2 = SIN(my,v[i+1]);
		t3 = SIN(my,v[i+2]);
		t4 = SIN(my,v[i+3]);
		tmp.maxAngle = max(max(t1,t2),max(t3,t4));
		tmp.minAngle = min(min(t1,t2),min(t3,t4));
		a.push_back(tmp);
	}
	int k1 = 1,k2 = 1,k3 = 1; // 标记 代表自身与三个目的地之间有无障碍物 
	for( int i = 0; i < a.size(); ++i ) {
		if( a[i].maxAngle >= a1 && a[i].minAngle <= a1 ) k1 = 0;
		if( a[i].maxAngle >= a2 && a[i].minAngle <= a2 ) k2 = 0; 
		if( a[i].maxAngle >= a3 && a[i].minAngle <= a3 ) k3 = 0; 
	}
	
	// 输出结果
	if(k1) cout << "a1 " << asin(a1)*180/PI << endl;
	if(k2) cout << "a2 " << asin(a2)*180/PI << endl;
	if(k3) cout << "a3 " << asin(a3)*180/PI << endl; 
	
	if( !( k1 || k2 || k3 ) ) cout << "No" << endl; // 三个都有障碍物 
	
	return 0;
}
