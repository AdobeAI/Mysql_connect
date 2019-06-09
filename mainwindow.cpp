#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdlib.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::string server = "127.0.0.1:3306";
    std::string username = "root";
    std::string password = "b19970716";

    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::PreparedStatement *pstmt;

    try {
       driver = get_driver_instance();
       con = driver->connect(server, username, password);
       con->setAutoCommit(false);   //如果連接處於自動認可模式，則它的所有 SQL 陳述式都會當做個別交易來執行及認可。
                                //否則，它的 SQL 陳述式會分組成許多交易，這些交易會透過 commit 方法或 rollback 方法的呼叫來結束。
                                //根據預設，新的連接會處於自動認可模式。
       con->setSchema("Minesweeper");
    } catch (sql::SQLException e) {
       std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
       system("pause");
       exit(1);
    }

   try {
       pstmt = con->prepareStatement("INSERT INTO game_record (player_name, score) VALUES (?,?)");
       pstmt->setString(1, "brian");
       pstmt->setDateTime(2, "200s");
       std::cout << pstmt->executeUpdate() << std::endl;
       con->commit();
   } catch (sql::SQLException e) {
        std::cout << "Could not insert to server. Error message: " << e.what() << std::endl;
   }

    pstmt->close();
    delete pstmt;

}

MainWindow::~MainWindow()
{
    delete ui;
}
