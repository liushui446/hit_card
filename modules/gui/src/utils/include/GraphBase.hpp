#ifndef _GRAPHBASE_HPP_
#define _GRAPHBASE_HPP_

/* ���õĳ������� */
const double INF_AOI = 1E200;
const double EP_AOI = 1E-10;
const int MAXV_AOI = 300;
const double PI_AOI = 3.14159265358979323846;

// ��ɫ
enum class ColorEx
{
	None,
	Red,
	Blue,
	Green,
	Gray
};

enum class FlagEx
{
	None,
	High,
	Low
};

//��
struct PointEx {
	double x;
	double y;
	PointEx(double a = 0, double b = 0) {
		x = a;
		y = b;
	}
};

// �߶�
struct LineSegment {
	PointEx startPoint;
	PointEx endPoint;
	LineSegment(PointEx a, PointEx b) {
		startPoint = a;
		endPoint = b;
	}
	LineSegment() {
	}
};

struct LINESEG {
	double bRatio; //����
	bool bDraw;//�Ƿ����
	bool bSelLine;//�Ƿ�ѡ����
	ColorEx bColor;
	FlagEx bFlag;
	LineSegment* seg;
	LINESEG() {
		bRatio = 0.0;
		bDraw = false;
		bSelLine = false;
		bColor = ColorEx::None;
		bFlag = FlagEx::None;
		seg = new LineSegment;
	}
	~LINESEG()
	{
		if (this->seg != nullptr)
		{
			delete seg;
		}
	}
};

//ֱ��
//ֱ�ߵĽ������� a*x+b*y+c=0  Ϊͳһ��ʾ��Լ�� a >= 0 
struct Beeline
{
	double a;
	double b;
	double c;
	Beeline(double d1 = 1, double d2 = -1, double d3 = 0) {
		a = d1; b = d2; c = d3;
	}
};
//
//double dist(PointEx p1, PointEx p2);
//
//double dotMultiply(PointEx p1, PointEx p2, PointEx p0);
//
//double relation(PointEx p, LineSegment l);
//
//PointEx perpendicular(PointEx p, LineSegment l);
//
//double pToLinesegDist(PointEx p, LineSegment l, PointEx& np);

/************************************************************************/
/* ��Ļ�������                                                           */
/************************************************************************/
//1.��������֮�������
double dist(PointEx p1, PointEx p2);

//2.�ж��������Ƿ��غ�
bool equalPoint(PointEx p1, PointEx p2);

//3.r=multiply(sp,ep,op),�õ�(sp->op)��(ep->op)�Ĳ�� 
//r > 0��ep��ʸ��opsp����ʱ�뷽��
//r = 0��opspep���㹲�ߣ�
//r < 0��ep��ʸ��opsp��˳ʱ�뷽��
double multiply(PointEx sp, PointEx ep, PointEx op);

/*4.r=dotmultiply(p1,p2,op),�õ�ʸ��(p1-op)��(p2-op)�ĵ�����������ʸ��������ʸ��
r<0����ʸ���н�Ϊ��ǣ�
r=0����ʸ���н�Ϊֱ�ǣ�
r>0����ʸ���н�Ϊ�۽�*/
double dotMultiply(PointEx p1, PointEx p2, PointEx p0);

/*5.�жϵ�p�Ƿ����߶�l��
������(p���߶�l���ڵ�ֱ����) && (��p�����߶�lΪ�Խ��ߵľ�����)*/
bool online(LineSegment l, PointEx p);

//6.���ص�p�Ե�oΪԲ����ʱ����תd(��λ������)�����ڵ�λ��
PointEx rotate(PointEx o, double d, PointEx p);

/*7. ���ض�����o�㣬��ʼ��Ϊos����ֹ��Ϊoe�ļн�(��λ������)
�Ƕ�С��pi��������ֵ
�Ƕȴ���pi�����ظ�ֵ
�����������߶�֮��ļн�
ԭ��
r = dotmultiply(s,e,o) / (dist(o,s)*dist(o,e))
r'= multiply(s,e,o)

r >= 1	angle = 0;
r <= -1	angle = -PI
-1<r<1 && r'>0	angle = arccos(r)
-1<r<1 && r'<=0	angle = -arccos(r)
*/
double angle(PointEx o, PointEx s, PointEx e);


/************************************************************************/
/* �߶μ�ֱ�ߵĻ�������                                         */
/************************************************************************/

/* �жϵ����߶εĹ�ϵ,��;�ܹ㷺
�������Ǹ�������Ĺ�ʽд�ģ�P�ǵ�C���߶�AB����ֱ�ߵĴ���

AC dot AB
r =     ---------
||AB||^2
(Cx-Ax)(Bx-Ax) + (Cy-Ay)(By-Ay)
= -------------------------------
L^2

r has the following meaning:

r=0      P = A
r=1      P = B
r<0		 P is on the backward extension of AB
r>1      P is on the forward extension of AB
0<r<1	 P is interior to AB
*/
double relation(PointEx p, LineSegment l);

// ���C���߶�AB����ֱ�ߵĴ��� P 
PointEx perpendicular(PointEx p, LineSegment l);

/* ���p���߶�l����̾���,�������߶��Ͼ�õ�����ĵ�np
ע�⣺np���߶�l�ϵ���p����ĵ㣬��һ���Ǵ��� */
double pToLinesegDist(PointEx p, LineSegment l, PointEx& np);

// ���p���߶�l����ֱ�ߵľ���,��ע�Ȿ�������ϸ�����������  
double pToLDist(PointEx p, LineSegment l);

// ����㵽ֱ�ߵľ���
// p ��Ŀ���
// sp �� ep �ֱ���ֱ���������յ�
double pToLDist(const PointEx& p, const PointEx& sp, const PointEx& ep);

/* ����㵽���߼����������,�����������.
ע�⣺���õ���ptolineseg()���� */
double pToPointSet(int vcount, PointEx pointset[], PointEx p, PointEx& q);

/* �ж�Բ�Ƿ��ڶ������.ptolineseg()������Ӧ��2 */
bool circleInsidePolygon(int vcount, PointEx center, double radius, PointEx polygon[]);

/* ��������ʸ��l1��l2�ļнǵ�����(-1 --- 1)ע�⣺������������нǵĻ���ע�ⷴ���Һ����Ķ������Ǵ� 0��pi */
double cosine(LineSegment l1, LineSegment l2);

// �����߶�l1��l2֮��ļн� ��λ������ ��Χ(-pi��pi) 
double lsAngle(LineSegment l1, LineSegment l2);

// ����߶�u��v�ཻ(�����ཻ�ڶ˵㴦)ʱ������true 
//
//�ж�P1P2����Q1Q2�������ǣ�( P1 - Q1 ) �� ( Q2 - Q1 ) * ( Q2 - Q1 ) �� ( P2 - Q1 ) >= 0��
//�ж�Q1Q2����P1P2�������ǣ�( Q1 - P1 ) �� ( P2 - P1 ) * ( P2 - P1 ) �� ( Q2 - P1 ) >= 0��
bool intersect(LineSegment u, LineSegment v);

//  (�߶�u��v�ཻ)&&(���㲻��˫���Ķ˵�) ʱ����true    
bool intersectA(LineSegment u, LineSegment v);

// �߶�v����ֱ�����߶�u�ཻʱ����true���������ж��߶�u�Ƿ�����߶�v  
bool intersectL(LineSegment u, LineSegment v);

// ������֪�������꣬����������ֱ�߽������̣� a*x+b*y+c = 0  (a >= 0)  
Beeline makeLine(PointEx p1, PointEx p2);

// ����ֱ�߽������̷���ֱ�ߵ�б��k,ˮƽ�߷��� 0,��ֱ�߷��� 1e200 
double slope(Beeline l);

// ����ֱ�ߵ���б��alpha ( 0 - pi) 
double alpha(Beeline l);

// ���p����ֱ��l�ĶԳƵ�  
PointEx symmetry(Beeline l, PointEx p);

// �������ֱ�� l1(a1*x+b1*y+c1 = 0), l2(a2*x+b2*y+c2 = 0)�ཻ������true���ҷ��ؽ���p  
bool lineIntersect(Beeline l1, Beeline l2, PointEx& p);

// ����߶�l1��l2�ཻ������true�ҽ�����(inter)���أ����򷵻�false 
bool intersection(LineSegment l1, LineSegment l2, PointEx& inter);

/************************************************************************/
/* ����γ����㷨
/************************************************************************/
//������ر�˵�����������ζ���Ҫ����ʱ������


/*
����ֵ������Ķ�����Ǽ򵥶���Σ�����true
Ҫ �����붥�����а���ʱ������
˵ �����򵥶���ζ��壺
1��ѭ�������������߶ζԵĽ�������֮�乲�еĵ�����
2�������ڵ��߶β��ཻ
������Ĭ�ϵ�һ�������Ѿ�����
*/
bool isSimple(int vcount, PointEx polygon[]);

// ����ֵ��������˳�򷵻ض���ζ����͹�����жϣ�bc[i]=1,iff:��i��������͹���� 
void checkConvex(int vcount, PointEx polygon[], bool bc[]);

// ����ֵ�������polygon��͹�����ʱ������true  
bool isConvex(int vcount, PointEx polygon[]);

// ���ض�������(signed)�����붥�㰴��ʱ������ʱ��������ֵ�����򷵻ظ�ֵ 
double areaOfPolygon(int vcount, PointEx polygon[]);

// ������붥�㰴��ʱ�����У�����true 
bool isConterClock(int vcount, PointEx polygon[]);

// ��һ���ж϶���ζ������з���ķ���  
bool isCcwize(int vcount, PointEx polygon[]);

/********************************************************************************************
���߷��жϵ�q������polygon��λ�ù�ϵ��Ҫ��polygonΪ�򵥶���Σ�������ʱ������
������ڶ�����ڣ�   ����0
������ڶ���α��ϣ� ����1
������ڶ�����⣺	����2
*********************************************************************************************/
int insidePolygon(int vcount, PointEx Polygon[], PointEx q);

//��q��͹�����polygon��ʱ������true��ע�⣺�����polygonһ��Ҫ��͹�����  
bool insideConvexPolygon(int vcount, PointEx polygon[], PointEx q); // �����������Σ� 

/**********************************************
Ѱ��͹����graham ɨ�跨
PointSetΪ����ĵ㼯��
chΪ�����͹���ϵĵ㼯��������ʱ�뷽������;
nΪPointSet�еĵ����Ŀ
lenΪ�����͹���ϵĵ�ĸ���
**********************************************/
void grahamScan(PointEx PointSet[], PointEx ch[], int n, int& len);

// ���������㼯͹�ǣ�����˵��ͬgraham�㷨    
void convexClosure(PointEx PointSet[], PointEx ch[], int n, int& len);
/*********************************************************************************************
�ж��߶��Ƿ��ڼ򵥶������(ע�⣺����������͹����Σ�������㷨���Ի���)
��Ҫ����һ���߶ε������˵㶼�ڶ�����ڣ�
��Ҫ���������߶κͶ���ε����б߶����ڽ���
��;��	1. �ж������Ƿ��ڼ򵥶������
2. �жϼ򵥶�����Ƿ�����һ���򵥶������
**********************************************************************************************/
bool linesegInsidePolygon(int vcount, PointEx polygon[], LineSegment l);

/*********************************************************************************************
������򵥶����polygon������
��Ҫ�������漸��������
void addPosPart(); �����ұ���������
void addNegPart(); ���������������
void addRegion(); �����������
��ʹ�øó���ʱ�������xtr,ytr,wtr,xtl,ytl,wtl���ȫ�ֱ����Ϳ���ʹ��Щ��������ʽ�õ�����,
��Ҫע�⺯���������͵���Ҫ����Ӧ�仯
**********************************************************************************************/
void addPosPart(double x, double y, double w, double& xtr, double& ytr, double& wtr);

void addNegPart(double x, double y, double w, double& xtl, double& ytl, double& wtl);

void addRegion(double x1, double y1, double x2, double y2, double& xtr, double& ytr, double& wtr, double& xtl, double& ytl, double& wtl);

PointEx cgSimple(int vcount, PointEx polygon[]);

// ��͹����ε�����,Ҫ���������ΰ���ʱ������ 
PointEx gravityCenter(int vcount, PointEx polygon[]);


/************************************************
����һ�򵥶���Σ��ҳ�һ���϶��ڸö�����ڵĵ�
����1	��ÿ�������������һ��͹����
����2	��������>=4�ļ򵥶����������һ���Խ���
����	�� x���������С�ĵ�϶���͹����
y���������С�ĵ�϶���͹����
************************************************/
PointEx aPointInsidepoly(int vcount, PointEx polygon[]);

/***********************************************************************************************
��Ӷ������һ��p������һ���򵥶���ε�����,������ڷ����е�,����rp�������е�,lp�����е�
ע�⣺p��һ��Ҫ�ڶ������ ,���붥����������ʱ������
ԭ ��	������ڶ�����ڿ϶�������;͹�������Ψһ�������е�,������ξͿ����ж����������е�;
���polygon��͹����Σ��е�ֻ������ֻҪ�ҵ��Ϳ���,���Ի�����㷨
����ǰ�����λ���һ���㷨�������:���󰼶���ε�͹��,Ȼ����͹��������
/***********************************************************************************************/
void pointTangentpoly(int vcount, PointEx polygon[], PointEx p, PointEx& rp, PointEx& lp);

// ��������polygon�ĺ˴��ڣ�����true�����غ��ϵ�һ��p.���㰴��ʱ�뷽������  
bool coreExist(int vcount, PointEx polygon[], PointEx& p);


/************************************************************************/
/* Բ�Ļ�������                                                                     */
/************************************************************************/
/******************************************************************************
����ֵ	�� ��p��Բ��(�����߽�)ʱ������true
��;	�� ��ΪԲΪ͹���������жϵ㼯�����ߣ�������Ƿ���Բ��ʱ��
ֻ��Ҫ��һ�жϵ��Ƿ���Բ�ڼ��ɡ�
*******************************************************************************/
bool pointInCircle(PointEx o, double r, PointEx p);

/******************************************************************************
�� ;	���󲻹��ߵ�����ȷ��һ��Բ
�� ��	��������p1,p2,p3
����ֵ	��������㹲�ߣ�����false����֮������true��Բ����q���أ��뾶��r����
*******************************************************************************/
bool coCircle(PointEx p1, PointEx p2, PointEx p3, PointEx& q, double& r);

/************************************************************************/
/* ���εĻ�������                                                      */
/************************************************************************/
/*
˵������Ϊ���ε������ԣ������㷨���Ի���
1.�жϾ����Ƿ������
ֻҪ�жϸõ�ĺ�������������Ƿ���ھ��ε����ұߺ����±�֮�䡣
2.�ж��߶Ρ����ߡ�������Ƿ��ھ�����
��Ϊ�����Ǹ�͹��������ֻҪ�ж����ж˵��Ƿ��ھ����оͿ����ˡ�
3.�ж�Բ�Ƿ��ھ�����
Բ�ھ����еĳ�Ҫ�����ǣ�Բ���ھ�������Բ�İ뾶С�ڵ���Բ�ĵ������ıߵľ������Сֵ��
*/
// ��֪���ε���������(a,b,c)��������ĸ�����d������. ע�⣺��֪�������������������� 
PointEx rect4th(PointEx a, PointEx b, PointEx c);

//��Բ��ϵ�� 
/* ��Բ��
���룺 return 1��
���У� return 2��
�ཻ�� return 3��
���У� return 4��
�ں��� return 5��
*/
int circleRelation(PointEx p1, double r1, PointEx p2, double r2);

//�ж�Բ�Ƿ��ھ����ڣ�
// �ж�Բ�Ƿ��ھ����ڣ��Ǿͷ���true�������ˮƽ�������ĸ����������Ͽ�ʼ��˳ʱ�����У� 
// ����ptoldist�������ڵ�4ҳ 
bool circleRecRelation(PointEx pc, double r, PointEx pr1, PointEx pr2, PointEx pr3, PointEx pr4);

//�㵽ƽ��ľ��룺 
//�㵽ƽ��ľ���,ƽ����һ��ʽ��ʾax+by+cz+d=0 
double p2PlaneDist(double x, double y, double z, double a, double b, double c, double d);

//���Ƿ���ֱ��ͬ�ࣺ
//�������Ƿ���ֱ��ͬ�࣬���򷵻�true 
bool sameSide(PointEx p1, PointEx p2, Beeline line);

//���淴���ߣ�
// ��֪�����ߡ����棬�����ߡ� 
// a1,b1,c1Ϊ����ֱ�߷���(a1 x + b1 y + c1 = 0 ,��ͬ)ϵ��;  
//a2,b2,c2Ϊ�����ֱ�߷���ϵ��;  
//a,b,cΪ�����ֱ�߷���ϵ��. 
// �����з���ģ�ʹ��ʱע�⣺���������:<-b2,a2>�����������:<b,-a>. 
// ��Ҫ���ǽ���п��ܻ���"negative zeros" 
void reflect(double a1, double b1, double c1, double a2, double b2, double c2, double& a, double& b, double& c);

//���ΰ����� 
// ����2��C��D���Ƿ���1��A��B����
bool r2Inr1(double A, double B, double C, double D);

//��Բ���㣺 
// ��Բ�Ѿ��ཻ�����У� 
void  c2Point(PointEx p1, double r1, PointEx p2, double r2, PointEx& rp1, PointEx& rp2);

//Բ��ֱ�߹�ϵ�� 
//0----���� 1----���� 2----�ཻ 
int clPoint(PointEx p, double r, double a, double b, double c, PointEx& rp1, PointEx& rp2);

//����Բ�� 
void inCircle(PointEx p1, PointEx p2, PointEx p3, PointEx& rp, double& r);

//���е㣺 
// p---Բ�����꣬ r---Բ�뾶�� sp---Բ��һ�㣬 rp1,rp2---�е����� 
void cutPoint(PointEx p, double r, PointEx sp, PointEx& rp1, PointEx& rp2);

//�߶ε��������� 
/* l2��l1����/�ҷ���l1Ϊ��׼�ߣ�
����	0	�� �غϣ�
����	1	�� ������
����	�C1 �� ������
*/
int rotat(LineSegment l1, LineSegment l2);
#endif