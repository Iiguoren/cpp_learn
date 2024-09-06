#include "Sales_data.h"
#include <iostream>
#include <string>

using namespace std;
// 重载+=运算符，对sales_data对象中+=另一个对象销售量相加销售值相加
Sales_data& Sales_data::operator += (const Sales_data& rhs){
    units_sold += rhs.units_sold;
    saleprice = (rhs.saleprice * rhs.units_sold + saleprice * units_sold)
    / (rhs.units_sold + units_sold);
    if(sellingprice != 0)
        discount = saleprice / sellingprice;
    return *this;
}
// 与+=作用相同，函数形式
Sales_data& Sales_data::combine(const Sales_data& rhs){
    units_sold += rhs.units_sold;
    saleprice = (rhs.saleprice * rhs.units_sold + saleprice * units_sold) /
		(rhs.units_sold + units_sold);
    if (sellingprice != 0)
		discount = saleprice / sellingprice;
	return *this;
}

Sales_data Add(const Sales_data& lhs,
	const Sales_data& rhs)
{
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}

inline bool operator == (const Sales_data& lhs,
	const Sales_data& rhs) {

	return lhs.units_sold == rhs.units_sold &&
		lhs.sellingprice == rhs.sellingprice &&

		lhs.saleprice == rhs.saleprice &&
		lhs.isbn() == rhs.isbn();

}

inline bool compareIsbn(const Sales_data& lhs, const Sales_data rhs)
{
    return lhs.isbn() == rhs.isbn();
}

istream& operator >> (std::istream& in, Sales_data& s)
{
    in>>s.bookNo>>s.units_sold>>s.sellingprice>>s.saleprice;
    if(in && s.sellingprice!=0)
        s.discount = s.saleprice/s.sellingprice;
    else 
        s = Sales_data(); //输入错误，重置数据
    return in;
}
 ostream& kprint(ostream& out, Sales_data& s)
{

	out << "图书编号:" << s.isbn() << " " << "销售量:" << s.units_sold << " "
		<< "原始价格:" << s.sellingprice << " " << "实售价格:" << s.saleprice << " " << "折扣:" << s.discount << "\n";
	return out;

}
istream& read(std::istream& in, Sales_data& s){
    in>>s.bookNo>>s.units_sold>>s.sellingprice>>s.saleprice;
    if(in && s.sellingprice!=0)
        s.discount = s.saleprice/s.sellingprice;
    else 
        s = Sales_data(); //输入错误，重置数据
    return in;
}

ostream& operator << (std::ostream& out, const Sales_data& s){
    out << "图书编号:" << s.isbn() << " " << "销售量:" << s.units_sold << " "
		<< "原始价格:" << s.sellingprice << " " << "实售价格:" << s.saleprice << " " << "折扣:" << s.discount;
    return out;
}
