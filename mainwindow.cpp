#include "mainwindow.h"
#include "ui_mainwindow.h"
#define Path_To_DB "contactBook.sqlite"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myDB = QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName(Path_To_DB);

    QFileInfo check(Path_To_DB);

    if(check.isFile())
    {
        if(myDB.open())
        {
            ui->label_3->setText("[+] Connected to the database file.");
        }
    }
    else
    {
        ui->label_3->setText("[+] Database file not exits.");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->label_3->setText("[+]Status.....:(");
}

void MainWindow::on_pushButton_clicked()
{
    QString user, pass;
    user = ui->lineEdit->text();
    pass = ui->lineEdit_2->text();

    if(!myDB.open())
    {
        ui->label_3->setText("[+] No Connection to DB :(");
    }
    else
    {
        QSqlQuery qry;
        if(qry.exec("select username,password,role from userList where username=\'"+ user + "\' and password=\'" + pass + "\'"))
        {
            if(qry.next())
            {
                ui->label_3->setText("[+] Valid Username and Password");
                QString msg = "Username = "+ qry.value(0).toString() +" Password = "+qry.value(1).toString() + " Role = "+qry.value(2).toString();
                QMessageBox::information(this,"Login successfull",msg);
            }
            else
            {
                ui->label_3->setText("[+] Username or Password not valid.");
            }
        }

    }


}
