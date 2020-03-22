# DLL使用说明

## 使用方法

- 将`lib`文件夹的所有文件复制到项目代码所在文件夹
- 在需要使用到`DLL`的所有`.cpp`文件中添加：
    - `include "GeometryCore.h"`
    - `#pragma comment(lib,"GeometryCore.lib")`

## 导出类说明

- 关于类的使用说明建议写在了最后。

### 异常类

```c++
/*
 * 坐标范围异常，即大于100000或小于-100000
*/
class CoordinateRangeException : public exception {
public:
	CoordinateRangeException();
	CoordinateRangeException(string msg);
	~CoordinateRangeException() throw();
	virtual const char* what() const throw ();
private:
	string message;
};

/*
 * Line型坐标重合冲突异常，即x1==x2 && y1==y2
*/
class CoordinateCoincidenceException : public exception {
public:
	CoordinateCoincidenceException();
	CoordinateCoincidenceException(string msg);
	~CoordinateCoincidenceException() throw();
	virtual const char* what() const throw ();
private:
	string message;
};

/*
 * Line型几何对象冲突异常（存在重合）
 *       直线      射线      线段    
 * 直线   x         x         x
 * 射线   x         o         o
 * 线段   x         o         o
*/
class LineCoincidenceException : public exception {
public:
	LineCoincidenceException();
	LineCoincidenceException(string msg);
	~LineCoincidenceException() throw();
	virtual const char* what() const throw ();
	Line coincidence;
private:
	string message;
};

/*
 * Circle型几何对象冲突异常（重合）
*/
class CircleCoincidenceException : public exception {
public:
	CircleCoincidenceException();
	CircleCoincidenceException(string msg);
	~CircleCoincidenceException() throw();
	virtual const char* what() const throw ();
	Circle coincidence;
private:
	string message;
};

/*
 * Circle型几何对象参数非法异常（半径为负数）
*/
class NegativeRadiusException : public exception {
public:
	NegativeRadiusException();
	NegativeRadiusException(string msg);
	~NegativeRadiusException() throw();
	virtual const char* what() const throw ();
private:
	string message;
};

/*
 * 未定义的Line型的具体类型未知异常（不用管）
*/
class UndefinedLineException : public exception {
public:
	UndefinedLineException();
	UndefinedLineException(string msg);
	~UndefinedLineException() throw();
	virtual const char* what() const throw ();
private:
	string message;
};

/*
 * 
 * 不存在的几何对象异常，在remove函数使用时有可能跑出
*/
class ObjectNotFoundException : public exception {
public:
	ObjectNotFoundException();
	ObjectNotFoundException(string msg);
	~ObjectNotFoundException() throw();
	virtual const char* what() const throw ();
private:
	string message;
};

//-------------------------------------------------------------------------------------

/*
 * 输入object类型不对，用于命令行输入处理
*/
class WrongFormatException : public exception {
public:
	WrongFormatException();
	WrongFormatException(string msg);
	~WrongFormatException() throw();
	virtual const char* what() const throw ();
private:
	string message;
};
```

### 几何对象类

```c++

/*
 * 直线类
*/
class Line {
private:
	void get_coincident_check_bounding();
public:
	long long x_min, x_max, y_min, y_max;   // 不用管
	long long x1, y1, x2, y2;               // 四个坐标值
	long long a, b, c;                      // ax + by + c = 0
	int type;                               // 直线 or 线段 or 射线，详见constant.h
	LineKey k;                              // 不用管
	Line();
	Line(long long x1, long long y1, long long x2, long long y2, int type);
	friend bool line_coincident(Line &l1, Line &l2);                    // 用于检查两条Line是否存在重合
};

class Circle {
public:
	long long a, b, r;
	Circle();
	Circle(long long aa, long long bb, long long cc);
};
```

```c++
class Point {
public:
	double x;
	double y;
	Point();
	Point(double a, double b);
	bool point_equals(const Point &b) const;
};
```

### 容器类

```c++
class GeometryFactory{
public:
	PointMap points;						// 交点集合<无理数点，点存在于多少几何对象上>
	LineMap lines;												// <k&b, <ID, Lines>>
	CircleSet circles;											// <Circles>
	IdLineMap line_ids;											// <ID, Line>
	IdCircleMap circle_ids;										// <ID, Circle>
	int line_counter = 1;										// Line ID 累加器
	int circle_counter = 0;										// Circle ID 累加器
	void line_line_intersect(Line &l1, Line &l2);				// 线线交点
	void line_circle_intersect(Line &l1, Circle &c1);			// 线圆交点
	void circle_circle_intersect(Circle &c1, Circle &c2);		// 圆圆交点
	inline void increase_point(Point* p);	//  ..
	inline void decrease_point(Point* p);	//  ..
	void removeLine(Line &l);									// 移除Line对象
	void removeCircle(Circle &c);								// 移除Circle对象
	inline bool point_on_line(Point *p, Line &l);
	inline bool point_on_circle(Point *p, Circle &c);
	inline bool point_in_line_range(double x, double y, Line &l);
    //------------------------------------------------------------------------------------------------------------------
    // 上述函数其实为内部函数，为了单元测试方便设成了public，下边的函数才是对外的接口
public:
	GeometryFactory();
	/* Modification */
	int addLine(int type, long long x1, long long x2, long long y1, long long y2);		// 添加直线，传入四个参数，其中type详见constant.h， 返回值为id，会抛出各种异常
	int addCircle(long long x, long long y, long long r);							    // 添加圆， 返回值为id，会抛出各种异常
	void remove(int id);										                        // 删除几何对象，传入参数为id
	/* Query */
	Line getLine(int id);										                        // 获取已经添加的直线，传入参数为id
	Circle getCircle(int id);									                        // 获取已添加的原，传入参数为id
	vector<Point> getPoints();									                        // 获取所有的交点
	int getPointsCount();										                        // 获取交点总数
	int addObjectFromFile(string & message);							                // 解析文件内的一行输入，如“L 0 0 1 1”或“C 0 0 3”，会抛出各种异常
};
```

### 常数

```c++
#define DOUBLE_INFINITE_LINE 1  // 直线
#define SINGLE_INFINITE_LINE 2  // 射线
#define LIMITED_LINE 3          // 线段
#define MAX_RANGE 100000        // 最大范围
#define MIN_RANGE -100000       // 最小范围
```

### 使用说明建议

- 需要新建容器类对象，并往对象中add各种参数添加直线，圆等
- 在addLine调用时，有一个参数为type，该参数代表线的种类，例如`DOUBLI_INIFINITE_LINE`为直线
- 在add操作结束后会返回该几何对象的id，在add操作进行时会抛出各种异常
- 容器具有解析字符串功能，详见addObjectFromFile接口，可以解析一行的输入
- `Line` `Circle` `Point`这三个几何对象类一般不需要构造，直接通过从容器中get出来即可，这三个类只是一个信息封装类，可以告知几何对象的信息，没有其他多余的功能。