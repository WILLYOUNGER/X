/**
*  @file XMysql.h
*  @brief    mysql数据库封装类
*  Details.
*
*  @author   wangxinxiao
*  @email    wxx1035@163.com
*  @version  1.0.0.0
*  @date     2022/8/18
*
*  Change History :
*  <Date>     | <Version> | <Author>       | <Description>
*  2022/8/18 | 1.0.0.0  | wangxinxiao      | Create file
*-
*/
#ifndef X_PUBLIC_TOOLS_SQL_MYSQL_H
#define X_PUBLIC_TOOLS_SQL_MYSQL_H

#include <ctime>
#include <mutex>
#include <memory.h>

#include <jdbc/mysql_connection.h>
#include <jdbc/mysql_driver.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/prepared_statement.h>

#include "XLog.h"
#include "XBaseStruct.h"
#include "XLock.h"

/**
 * @brief 数据库相关命名空间
 * 
 */
namespace XSQLTOOL
{   
    class XConnection;

    typedef std::shared_ptr<XConnection> XConnectionPtr;

    class XConnection : public noncopyable
    {
        public:
            XConnection();
            ~XConnection();
        
        /**
         * @brief 连接数据库
         * 
         * @param ip 
         * @param port 
         * @param username 
         * @param password 
         * @param dbname 
         * @return 
         *  <em> 0 <em> 连接成功
         *  <em> 1 <em> 连接失败
         *  <em> 2 <em> 数据库不存在
         */
        int connect(std::string ip, int port, std::string username, std::string password, std::string dbname);

        // 刷新连接的起始空闲时刻
        // 记录每个队列的空闲时间，缓解服务器资源，在入队时
        void refreshAliveTime();

        // 返回连接空闲的时长
        clock_t getAliveTime();

        // 是否连接上
        bool isConnected();

        /**
         * @brief 设置是否自动提交事务
         * 
         * @param auto_commit 
         * @return int 
         *  <em> 0 <em> 成功
         *  <em> 1 <em> 未连接上数据库
         *  <em> 2 <em> 出错了
         */
        int autoCommit(bool auto_commit);
        
        /**
         * @brief 提交事务
         * 
         * @return int 
         *  <em> 0 <em> 成功
         *  <em> 1 <em> 未连接上数据库
         *  <em> 2 <em> 出错了
         */
        int commit();
        
        /**
         * @brief 创建一个保存点
         * 
         * @param name 保存点名称
         * @return int
         *  <em> 0 <em> 正常
         *  <em> 1 <em> 未连接上数据库
         *  <em> 2 <em> 出错了
         */
        int createSavePoint(const std::string& name, sql::Savepoint* point);

        /**
         * @brief 回滚到一个保存点
         * 
         * @param point 
         * @return int  
         *  <em> 0 <em> 正常
         *  <em> 1 <em> 未连接上数据库
         *  <em> 2 <em> 出错了
         *  <em> 3 <em> 保存点为空
         */
        int rollbackSavePoint(sql::Savepoint* point);

        /**
         * @brief 释放保存点， 必须调用(内存泄漏)
         * 
         * @param point 
         * @return int 
         *  <em> 0 <em> 正常
         *  <em> 1 <em> 未连接上数据库
         *  <em> 2 <em> 出错了
         *  <em> 3 <em> 保存点为空
         */
        int releaseSavePoint(sql::Savepoint* point);

        /**
         * @brief 更新操作 insert、delete、update
         * 参数: setXXX(index, data), index是从1开始
         * 
         * @param sql 
         * @param prepCallBack 
         * @param exceptionCallBack 
         * @return int 
         *  <em> -1 <em> 未连接上数据库
         *  <em> -2 <em> 出错了
         *  <em> 0 <em> 没有变化
         *  <em> 1 - ... <em> 受影响的行
         */
        int executeUpdate(const std::string& sql,
            std::function<void (sql::PreparedStatement* stmt)> prepCallBack,
            std::function<void (sql::SQLException &e)> exceptionCallBack);

        /**
         * @brief 查询操作 select
         * 参数: setXXX(index, data), index是从1开始
         * 
         * @param sql 
         * @param prepCallBack 
         * @param resultCallBack 
         * @param exceptionCallBack 
         * @return int 
         *  <em> 0 <em> 正常
         *  <em> 1 <em> 未连接上数据库
         *  <em> 2 <em> 出错了
         */
        int executeQuery(const std::string& sql,
            std::function<void (sql::PreparedStatement* stmt)> prepCallBack,
            std::function<void (sql::ResultSet* result)> resultCallBack,
            std::function<void (sql::SQLException &e)> exceptionCallBack);

    private:
        sql::mysql::MySQL_Driver *m_driver { nullptr };
        sql::Connection *m_con { nullptr }; // 表示和MySQL Server的一条连接
        clock_t m_alivetime; // 记录进入空闲状态后的起始存活时刻（即在队列中出现的时刻）
    };

    class XConnectionPool
    {
    public:
        ~XConnectionPool();
        // 获取连接池对象实例（懒汉式单例模式，在获取实例时才实例化对象）
        static XConnectionPool* getInstance();

        /**
         * @brief 从连接池中获取一个可用的空闲连接
         * 
         * @return XConnectionPtr 
         *  返回nullptr 获取失败
         */
        XConnectionPtr getConnection();

        // 设置数据库连接信息
        void init(std::string ip, int port, std::string username, std::string password, std::string dbname, int initSize = 5, int maxSize = 10, int maxIdleTime = 60, int connectionTimeout = 10);
    private:
        XConnectionPool();

        /**
         * @brief 运行在独立的线程中，专门负责
         * 需要绑定this指针
         */
        void produceConnectionTask();

        // 扫描超过maxIdleTime时间的空闲连接，进行对于连接的回收
        void scannerConnectionTask();

private:
        std::string m_str_ip;                    // MySQL的ip地址
        int m_short_port;          // MySQL的端口号，默认为3306
        std::string m_str_userName;              // MySQL登陆用户名
        std::string m_str_password;              // MySQL登陆密码
        std::string m_str_dbname;                // 连接的数据库名称
        int m_i_initSize;              // 连接池的最大初始连接量
        int m_i_maxSize;               // 连接池的最大连接量
        int m_i_maxIdleTime;           // 连接池的最大空闲时间
        int m_i_connectionTimeout;     // 连接池获取连接的超时时间

        //是否初始化
        bool m_b_isInit { false };

        // 存储MySQL连接的队列
        XBlockQueue<XConnection*> * m_queueXConPtr_connection_ptr;

        // 记录connection连接的总数量
        unsigned int m_uI_connectionNum;

        Locker m_locker_queue;
        Cond m_cond_queue;
    };

    #define XMYSQLLINSTANCE() XConnectionPool::getInstance()
};



#endif //X_PUBLIC_TOOLS_SQL_MYSQL_H