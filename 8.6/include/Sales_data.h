#pragma once // 防止多次编译
#include <iostream>
#include <string>
using namespace std;
class Sales_data {

public:
    //Sales_data() = default; //显示声明一个默认构造函数

    // 构造函数
    Sales_data(const string& book, unsigned num, 
		double sellp,double salep) :bookNo(book),
		units_sold(num),sellingprice(sellp)
		,saleprice(salep) {
		if (sellingprice)
			discount = saleprice / sellingprice;
		cout << "该构造函数接受书号、销售量、原价、实际售价四个信息" << endl;
	}
    // 委托构造函数
    Sales_data() :Sales_data("", 0, 0, 0) {
		cout << "该构造函数无须接受任何信息" << endl;
    }
    Sales_data(const string& book) : Sales_data(book, 0, 0, 0){
        cout << "接受书号信息" << endl;
    }

    Sales_data(istream& is) : Sales_data() {
        read(is, *this);
        cout << "该构造函数接受用户输入信息" << endl;
    }

    Sales_data& operator += (const Sales_data&);
	Sales_data& combine(const Sales_data& rhs);

	std::string isbn() const { return bookNo; };

    // 友元函数
	friend std::istream& operator >> (std::istream&, Sales_data&);
	// 友元函数
	friend std::ostream& operator << (std::ostream&, const Sales_data&);
	// 友元函数
	//friend bool operator < (const Sales_data&, const Sales_data&);
	
	// 友元函数
	friend bool operator == (const Sales_data&, const Sales_data&);


	friend istream& read(istream&, Sales_data&);

	friend Sales_data Add(const Sales_data& lhs,const Sales_data& rhs);
	
	friend ostream& kprint(ostream&,  Sales_data&);


private:

	string bookNo;//书籍编号，隐式初始化为空串
	unsigned units_sold = 0;// 销售量，显式初始化为0
	double sellingprice = 0.0;// 原始价格，显式初始化为 0.0
	double saleprice = 0.0;//实售价格，显式初始化为0.0
	double discount = 0.0;// 折扣，显式初始化为 0.0 
};

inline bool compareIsbn(const Sales_data& lhs, 
    const Sales_data& rhs)
{
    return lhs.isbn() == rhs.isbn();
};
