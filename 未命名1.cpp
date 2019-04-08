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
	cin >> my.x >> my.y;
	getchar();

	vector<COOR> d;
	string str;
	int i = 0;
	getline(cin,str);
    for( int i = 0; i < str.size(); i++ ) { // 输入目的地的坐标 坐标为一行 分别 x1 y1 x2 y2 。。。。 每个数字之间空格隔开 首部没有空格 尾部直接回车
        COOR t;
        int tx = 0,ty = 0;
        while(str[i] != ' ') { // x
            int m = str[i] - '0';
            tx = tx*10+m;
            i++;
        }
        i++;
        while(str[i] != ' ') { // y
            int m = str[i] - '0';
            ty = ty*10+m;
            i++;
            if(i == str.size()) break;
        }
        t.x = tx;
        t.y = ty;
        d.push_back(t);
    }

	vector< vector<COOR> > v; // 相当于一个二维数组，v[0] v[1] 。。各表示一个障碍物的坐标
	i = 0;
	while( 1 ) {
		getline(cin,str);
		if( str.length() == 0 ) break;

        vector<COOR> tmp;
		for( int j = 0; j < str.size(); j++ ) {
			COOR t;
			int tx = 0,ty = 0;
			while(str[j] != ' ') { // x
				int m = str[j] - '0';
				tx = tx*10+m;
				j++;
			}
			j++;
			while(str[j] != ' ') { // y
				int m = str[j] - '0';
				ty = ty*10+m;
				j++;
				if(j == str.size()) break;
			}
			t.x = tx;
			t.y = ty;
			tmp.push_back(t);
		}
        v.push_back(tmp);
		i++;
	}

	// 处理数据
	// 先保存自身和目的地点的连线夹角
	vector<double> b;
	for( coor t : d ) { // 范围for处理 目的地的坐标
        b.push_back(SIN(my,t));
	}

	// 处理障碍物
	vector<ANGLE> a;
    for( vector<COOR> t : v ) { // 处理障碍物的坐标
        ANGLE tmp;
        double maxt = -10, mint = 10;
        for( COOR c : t ) { // 处理一个障碍物的每个坐标 从中找出自己和障碍物每个点连线的角度最大的和最小的
            double tAngle = SIN(my,c);
            if( tAngle > maxt) maxt = tAngle;
            if( tAngle < mint) mint = tAngle;
        }
        tmp.maxAngle = maxt;
        tmp.minAngle = mint;
        a.push_back(tmp);
    }

	vector<double> yes; // 存储自身与目的地连线之间没有障碍物的连线的角度
	for( double t : b ) {
        int k = 1;
        for( ANGLE tA : a ) {
            if( t <= tA.maxAngle && t <= tA.minAngle ) k = 0;
        }
        if( k )
            yes.push_back(t);
	}

	// 输出结果
	if( yes.empty() ) cout << "No" << endl;
	for( double t : yes ) {
        cout << asin(t)*180/PI << endl;
	}

	return 0;
}
