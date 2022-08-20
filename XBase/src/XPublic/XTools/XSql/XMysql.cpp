/**
*  @file XMysql.cpp
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

#include "XMysql.h"

#include <thread>
#include <functional>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/parameter_metadata.h>

using namespace sql;
using namespace std;

/**
 * @brief 数据库相关命名空间
 * 
 */
namespace XSQLTOOL
{   
    XConnection::XConnection()
    {
        m_driver = sql::mysql::get_mysql_driver_instance();
        if (nullptr == m_driver)
        {
            XLOG_ERROR("dirver is nullptr.");
        }
    }

    XConnection::~XConnection()
    {
        if (m_con != nullptr)
        {
            if (m_con->isClosed())
            {
                m_con->close();
            }
            delete m_con;
            m_con = nullptr;
        }
        m_driver = nullptr;
    }
        
    int XConnection::connect(string ip, int port, string username, string password, string dbname)
    {
        string _str_address = ip + ":" + to_string(port);
        try
        {
            m_con = m_driver->connect(_str_address, username, password);
        }
        catch (sql::SQLException &e) {
            XLOG_ERROR("connect fail. message: %s, adress: %s", e.what(), _str_address.c_str());
        }
        
        if (nullptr == m_con || m_con->isClosed())
        {
            XLOG_ERROR("can't connect mysql with ip: %s, port: %d, username: %s", ip.c_str(), port, username.c_str());
            return 1;
        }

        // 选择数据库
        m_con->setSchema(dbname);

        return 0;
    }


    void XConnection::refreshAliveTime()
    {
        m_alivetime = clock();
    }

    clock_t XConnection::getAliveTime()
    {
        return clock() - m_alivetime;
    }

    bool XConnection::isConnected()
    {
        if (nullptr != m_con)
        {
            return !m_con->isClosed();
        }
        return false;
    }

    int XConnection::autoCommit(bool auto_commit)
    {
        if (!isConnected()) {
            XLOG_ERROR("set auto commit fail, connection is close.");
            return 1;
        }

        try {
            m_con->setAutoCommit(auto_commit);
        }
        catch (sql::SQLException &e) {
            XLOG_ERROR("set auto commit fail. message: %s", e.what());
            return 2;
        }
        return 0;
    }

    int XConnection::commit()
    {
        if (!isConnected()) {
            XLOG_ERROR("commit fail, connection is close.");
            return 1;
        }

        try {
            m_con->commit();
        }
        catch (sql::SQLException &e) {
            XLOG_ERROR("commit fail. message: %s", e.what());
            return 2;
        }
        return 0;
    }
        
    int XConnection::createSavePoint(const std::string& name, sql::Savepoint* point)
    {
        if (!isConnected()) {
            XLOG_ERROR("create savePoint fail, connection is close.");
            return 1;
        }

        try {
            sql::SQLString savePointName(name);
            point = m_con->setSavepoint(savePointName);
        }
        catch (sql::SQLException &e) {
            XLOG_ERROR("create savePoint fail. message: %s", e.what());
            point = nullptr;
            return 2;
        }

        return 0;
    }

    int XConnection::rollbackSavePoint(sql::Savepoint* point)
    {
        if (!isConnected()) {
            XLOG_ERROR("rollback savePoint fail, connection is close.");
            return 1;
        }

        if (nullptr == point) {
            XLOG_ERROR("savePoint is nullptr.");
            return 3;
        }

        try {
            m_con->rollback(point);
        }
        catch (sql::SQLException &e) {
            XLOG_ERROR("rollback savePoint fail. message: %s", e.what());
            return 2;
        }

        return 0;
    }

    int XConnection::releaseSavePoint(sql::Savepoint* point)
    {
        if (!isConnected()) {
            XLOG_ERROR("release savePoint fail, connection is close.");
            return 1;
        }

        if (nullptr == point) {
            XLOG_ERROR("savePoint is nullptr.");
            return 3;
        }

        int _i_return = 0;
        try {
            m_con->releaseSavepoint(point);
        }
        catch (sql::SQLException &e) {
            XLOG_ERROR("release savePoint fail. message: %s", e.what());
            _i_return = 2;
        }

        delete point;

        return _i_return;
    }

    int XConnection::executeUpdate(const std::string& sql,
            std::function<void (sql::PreparedStatement* stmt)> prepCallBack,
            std::function<void (sql::SQLException &e)> exceptionCallBack)
    {
        if (!isConnected()) {
            XLOG_ERROR("executeUpdate fail, connection is close.");
            return -1;
        }

        int _i_rowAffected = -2;
        sql::PreparedStatement* _prepStmt_temp = NULL;

        try {
            do
            {
                sql::SQLString sqlString(sql);
                _prepStmt_temp = m_con->prepareStatement(sqlString);
                if (nullptr == _prepStmt_temp) {
                    _i_rowAffected = -2;
                    break;
                }

                ParameterMetaData* _paramMetaData_temp = _prepStmt_temp->getParameterMetaData();
                if (_paramMetaData_temp) {
                    if (_paramMetaData_temp->getParameterCount() > 0) {
                        if (prepCallBack) {
                            prepCallBack(_prepStmt_temp);
                        }
                    }
                }

                _i_rowAffected = _prepStmt_temp->executeUpdate(); // 插入数据
            } while (false);
        }
        catch (sql::SQLException &e)
        {
            XLOG_ERROR("executeUpdate fail. message: %s", e.what());
            if (exceptionCallBack) {
                exceptionCallBack(e);
            }
        }

        if (_prepStmt_temp) {
            try {
                _prepStmt_temp->close();
            }
            catch (sql::SQLException &e) {
                XLOG_ERROR("close stmt fail. message: %s", e.what());
            }
            delete _prepStmt_temp;
        }

        return _i_rowAffected;
    }

    int XConnection::executeQuery(const std::string& sql,
            std::function<void (sql::PreparedStatement* stmt)> prepCallBack,
            std::function<void (sql::ResultSet* result)> resultCallBack,
            std::function<void (sql::SQLException &e)> exceptionCallBack)
    {
        if (!isConnected()) {
            XLOG_ERROR("executeQuery fail, connection is close.");
            return 1;
        }

        int _i_return = 2;
        sql::PreparedStatement* _prepStmt_temp = NULL;
        sql::ResultSet* _setRes_res = NULL;

        try {
            do
            {
                sql::SQLString sqlString(sql);
                _prepStmt_temp = m_con->prepareStatement(sqlString);
                if (NULL == _prepStmt_temp) {
                    _i_return = 2;
                    break;
                }

                if (prepCallBack) {
                    sql::ParameterMetaData* _paramMetaData_temp = _prepStmt_temp->getParameterMetaData();
                    if (_paramMetaData_temp && _paramMetaData_temp->getParameterCount() > 0) {
                        prepCallBack(_prepStmt_temp);
                    }
                }

                _setRes_res = _prepStmt_temp->executeQuery(); // 查询数据
                if (NULL == _setRes_res) {
                    _i_return = 2;
                    break;
                }

                if (resultCallBack) {
                    sql::ResultSetMetaData* _setRes_temp = _prepStmt_temp->getMetaData();
                    if (_setRes_temp && _setRes_temp->getColumnCount() > 0) {
                        resultCallBack(_setRes_res);
                    }
                }
                
                _i_return = 0;
            } while (false);
        }
        catch (sql::SQLException &e)
        {
            XLOG_ERROR("executeQuery fail. message: %s", e.what());
            if (exceptionCallBack) {
                exceptionCallBack(e);
            }
        }

        if (_prepStmt_temp) {
            try {
                _prepStmt_temp->close();
            }
            catch (sql::SQLException &e) {
                XLOG_ERROR("close stmt fail. message: %s", e.what());
            }
            delete _prepStmt_temp;
        }
        if (_setRes_res) {
            try {
                _setRes_res->close();
            }
            catch (sql::SQLException &e) {
                XLOG_ERROR("close stmt res fail. message: %s", e.what());
            }
            delete _setRes_res;
        }

        return _i_return;
    }

    XConnectionPool::XConnectionPool()
    {
        m_b_isInit = false;
    }
    
    XConnectionPool* XConnectionPool::getInstance()
    {
        static XConnectionPool _connectionPool_instance;
        return &_connectionPool_instance;
    }

    shared_ptr<XConnection> XConnectionPool::getConnection()
    {
        XConnection*_connection_res_ptr = nullptr;
        if (m_b_isInit)
        {
            m_locker_queue.lock();
            if (!m_queueXConPtr_connection_ptr->pop(_connection_res_ptr, m_i_connectionTimeout))
            {
                XLOG_ERROR("Failed to get connection:got idle connection timeout.");
                return nullptr;
            }

            // 消费者取出一个连接之后，通知生产者，生产者检查队列，如果为空则生产
            m_cond_queue.broadcast();
            m_locker_queue.unlock();

            XConnectionPtr _XConnection_conn_ptr(_connection_res_ptr, [&](XConnection* con)
            {
                if (con != nullptr)
                {
                    m_locker_queue.lock();
                    con->refreshAliveTime(); //在归还回空闲连接队列之前要记录一下连接开始空闲的时刻
                    m_queueXConPtr_connection_ptr->push(con);
                    m_locker_queue.unlock();
                }  
            });

            return _XConnection_conn_ptr;
        }
        return nullptr;
    }

    XConnectionPool::~XConnectionPool()
    {

    }
    
    void XConnectionPool::init(string ip, int port, string username, string password, 
    string dbname, int initSize, int maxSize, int maxIdleTime, int connectionTimeout)
    {
        m_b_isInit = true;
        m_str_ip = ip;
        m_short_port = port;
        m_str_userName = username;
        m_str_password = password;
        m_str_dbname = dbname;

        m_i_initSize = initSize;
        m_i_maxSize = maxSize;
        m_i_maxIdleTime = maxIdleTime;
        m_i_connectionTimeout = connectionTimeout;

        m_queueXConPtr_connection_ptr = new XBlockQueue<XConnection*>(m_i_maxSize);

        // 创建初始数量的连接
        for (int i = 0; i < m_i_initSize; ++i)
        {
            XConnection* _XConnection_conn_ptr = new XConnection();
            _XConnection_conn_ptr->connect(m_str_ip, m_short_port, m_str_userName, m_str_password, m_str_dbname);
            _XConnection_conn_ptr->refreshAliveTime(); // 记录连接的起始空闲时刻
            m_queueXConPtr_connection_ptr->push(_XConnection_conn_ptr);
            m_uI_connectionNum++;
        }

        // 启动一个新的线程，作为连接的生产者
        thread _thread_produce(std::bind(&XConnectionPool::produceConnectionTask, this));
        _thread_produce.detach(); 

        // 启动一个新的定时线程，扫描超过maxIdleTime时间的空闲连接，并对其进行回收
        thread _thread_scanner(std::bind(&XConnectionPool::produceConnectionTask, this));
        _thread_scanner.detach();
    }

    void XConnectionPool::produceConnectionTask()
    {
        for (;;)
        {
            while (!m_queueXConPtr_connection_ptr->empty())
            {
                if (!m_cond_queue.wait(m_locker_queue.get()))
                {
                    m_locker_queue.unlock();
                }
                // 队列非空时，此处生产线程进入等待状态
            }
            m_locker_queue.lock();
            // 连接数量没有到达上限，继续创建新的连接
            if (m_uI_connectionNum < m_i_maxSize)
            {
                XConnection* _XConnection_conn_ptr = new XConnection();
                _XConnection_conn_ptr->connect(m_str_ip, m_short_port, m_str_userName, m_str_password, m_str_dbname);
                _XConnection_conn_ptr->refreshAliveTime(); // 记录连接的起始空闲时刻
                m_queueXConPtr_connection_ptr->push(_XConnection_conn_ptr);
                m_uI_connectionNum++;
            }
            
            m_locker_queue.unlock();
        }
    }
    
    void XConnectionPool::scannerConnectionTask()
    {
        for (;;)
        {
            // 通过sleep实现定时效果
            this_thread::sleep_for(chrono::seconds(m_i_maxIdleTime));
            m_locker_queue.lock();
            // 扫描整个队列，释放多余的连接
            while (m_uI_connectionNum > m_i_initSize)
            {
                XConnection* _connection_temp; 
                if (m_queueXConPtr_connection_ptr->front(_connection_temp))
                {
                    if (_connection_temp->getAliveTime() >= (m_i_maxIdleTime * 1000))
                    {
                        m_queueXConPtr_connection_ptr->pop(_connection_temp);
                        m_uI_connectionNum--;
                    }
                    else
                    {
                        // 队头的连接没有超过_maxIdleTime，其它连接肯定也没有
                        break;
                    }
                }
            }
            m_locker_queue.unlock();
        }
    }

};
