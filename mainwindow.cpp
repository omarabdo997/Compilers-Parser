#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet(styleSheet(":/style/style/style.css"));
    this->setWindowTitle("Parser");
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->errorLabel->setHidden(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::styleSheet(QString path)
{
    QFile file(path);
         if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
             return "";

    QTextStream out(&file);
    return out.readAll();
}


void MainWindow::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
          tr("Open Text File"), "/home/omar", tr("Text files (*.txt)"));
    if(fileName != ""){
       QFile file(fileName);
       QFileInfo info = file;
       if(info.suffix() != "txt"){
           ui->errorLabel->setText("You must select a txt file!");
           ui->errorLabel->setHidden(false);
           return;
       }
       if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
           ui->errorLabel->setText("An error occured could not open file!");
           ui->errorLabel->setHidden(false);
           return;
       }
       QTextStream out(&file);
       ui->tokensListEdit->setPlainText(out.readAll());
       ui->errorLabel->setHidden(true);
       return;
    }
    ui->errorLabel->setText("No file is selected!");
    ui->errorLabel->setHidden(false);
    return;
}

void MainWindow::on_parseButton_clicked()
{
    scene->clear();
    node* root = new node{nullptr, nullptr, nullptr, "read", "(x)"};
    node* node1 = new node{nullptr, nullptr, nullptr, "if"};
    root->next = node1;
    node* node2 = new node{nullptr, nullptr, nullptr, "op", "(<)"};
    node2->left = new node{nullptr, nullptr, nullptr, "const", "(0)"};
    node2->right = new node{nullptr, nullptr, nullptr, "id", "(x)"};
    node1->left = node2;
    node* node3 = new node{nullptr, nullptr, nullptr, "assign", "(fact)"};
    node1->right = node3;
    node3->left = new node{nullptr, nullptr, nullptr, "const", "(1)"};
    node* repeat = new node{nullptr, nullptr, nullptr, "repeat"};
    node3->next = repeat;
    node* write = new node{nullptr, nullptr, nullptr, "write"};
    repeat->next = write;
    write->left = new node{nullptr, nullptr, nullptr, "id", "(fact)"};
    node* assignFact = new node{nullptr, nullptr, nullptr, "assign", "(fact)"};
    node* factOp = new node{nullptr, nullptr, nullptr, "op", "(*)"};
    factOp->left = new node{nullptr, nullptr, nullptr, "id", "(fact)"};
    factOp->right = new node{nullptr,nullptr,nullptr, "id", "(x)"};
    assignFact->left = factOp;
    repeat->left = assignFact;
    node* assignX = new node{nullptr, nullptr, nullptr, "assign","(x)"};
    assignFact->next = assignX;
    node* subOp = new node{nullptr, nullptr, nullptr, "op", "(-)"};
    subOp->left = new node{nullptr, nullptr, nullptr, "id", "(x)"};
    subOp->right = new node{nullptr, nullptr, nullptr, "const", "(1)"};
    assignX->left = subOp;
    node* equalOp = new node{nullptr, nullptr, nullptr, "op", "(=)"};
    equalOp->left = new node{nullptr, nullptr, nullptr, "id", "(x)"};
    equalOp->right = new node{nullptr, nullptr, nullptr, "const", "(0)"};
    repeat->right = equalOp;
    unordered_map<int, int>m;

    draw(root, m);
}

void MainWindow::on_actionNew_triggered()
{
    int answer = QMessageBox::warning(this,"Start New Parser", "Are you sure you want to start a new parser?", QMessageBox::Yes | QMessageBox::Cancel);
    if(answer == QMessageBox::Yes)
    {
        ui->errorLabel->setHidden(true);
        ui->tokensListEdit->clear();
        scene->clear();
    }

}

void MainWindow::on_actionExit_triggered()
{
    int answer = QMessageBox::warning(this,"Quit Application", "Are you sure you want to quit?", QMessageBox::Yes | QMessageBox::Cancel);
    if(answer == QMessageBox::Yes)
    {
        QApplication::quit();
    }

}
