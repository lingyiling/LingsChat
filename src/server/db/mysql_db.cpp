#include "mysql_db.hpp"
#include <muduo/base/Logging.h>

// 数据配置信息
static string server = "127.0.0.1";
static string user = "root";
static string password = "P8tK3pPg9Vylm4ES";
static string dbname = "chat";

// 初始化数据库连接
MySQL::MySQL()
{
	_conn = mysql_init(nullptr);
}

// 释放连接资源
MySQL::~MySQL()
{
	if (_conn != nullptr) { mysql_close(_conn); }
}

// 连接数据库
bool MySQL::connect()
{
	MYSQL *p = mysql_real_connect(_conn, server.c_str(), user.c_str(),
		password.c_str(), dbname.c_str(), 3306, nullptr, 0);
	if (p != nullptr)
	{
		// C和C++代码默认的编码字符是ASCII，如果不设置，则从MySQL上拉下来的中文显示为？
		mysql_query(_conn, "set names gbk");
		LOG_INFO << "connect mysql success!";
	}
	else
	{
		LOG_INFO << "connect mysql failed!";
		return false;
	}

	// return p;
	return true;
}

// 更新操作
bool MySQL::update(string sql)
{
	if (mysql_query(_conn, sql.c_str()))
	{
		LOG_INFO << __FILE__ << ":" << __LINE__ << ":" << sql << "更新失败！";
		return false;
	}

	return true;
}

// 查询操作
MYSQL_RES* MySQL::query(string sql)
{
	if (mysql_query(_conn, sql.c_str()))
	{
		LOG_INFO << __FILE__ << ":" << __LINE__ << ":" << sql << "查询失败！";
		return nullptr;
	}

	return mysql_use_result(_conn);
}

// 获取MySQL连接
MYSQL* MySQL::get_connection()
{
	return _conn;
}