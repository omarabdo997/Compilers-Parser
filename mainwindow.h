#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QFileInfo>
#include "rectangle.h"
#include "ellipse.h"
#include <unordered_map>
#include <QMessageBox>
#include "token.h"
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;

struct node{
    node* left;
    node* right;
    node* next;
    QString type;
    QString name;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadButton_clicked();

    void on_parseButton_clicked();

    void on_actionNew_triggered();

    void on_actionExit_triggered();

    void on_codeListRadioButton_clicked();

    void on_tokensListRadioButton_clicked();

    void on_loadCodeButton_clicked();

    void on_tokensListEdit_textChanged();

    void on_scanButton_clicked();

private:
    Ui::MainWindow *ui;
    QString styleSheet(QString path);
    QGraphicsScene* scene;
    QString fileDir = "";
    QString scannerData = "";
    QString parseData = "";
    template<class Shape>
    void makeLine(Shape *a, Shape *b)
    {
        QColor orange(230, 126, 34);
        QPen outlinePen(orange);
        outlinePen.setWidth(1);
        if(a->getYCord() == b->getYCord()) {
            scene->addLine(a->getXCord()+100, a->getYCord()+30, b->getXCord(), b->getYCord()+30, outlinePen);
            return;
        }
        scene->addLine(a->getXCord()+50, a->getYCord()+60, b->getXCord()+50, b->getYCord(), outlinePen);
    }
    template<class Shape1, class Shape2>
    void makeLine(Shape1 *a, Shape2 *b)
    {
        QColor orange(230, 126, 34);
        QPen outlinePen(orange);
        if(a->getYCord() == b->getYCord()) {
            scene->addLine(a->getXCord()+100, a->getYCord()+30, b->getXCord(), b->getYCord()+30, outlinePen);
            return;
        }
        scene->addLine(a->getXCord()+50, a->getYCord()+60, b->getXCord()+50, b->getYCord(), outlinePen);
    }
    template <class Node>
    void draw(Node* root, unordered_map<int, int>&m, int level = 0, Rectangle* parentR=nullptr, Ellipse* parentC=nullptr) {
        Rectangle* r = nullptr;
        Ellipse* c = nullptr;
        if(root == nullptr) {
            return;
        }
        if(root->type == "if" or root->type == "read" or root->type == "write" or root->type == "repeat" or root->type == "assign") {
            r = new Rectangle(m[level],level*120,root->type, root->name);
            scene->addItem(r);
            if(parentR!=nullptr) {
                makeLine(parentR, r);
            }
            if(parentC!=nullptr) {
                makeLine(parentC, r);
            }
        }
        else {
            c = new Ellipse(m[level],level*120,root->type, root->name);
            scene->addItem(c);
            if(parentR!=nullptr) {
                makeLine(parentR, c);
            }
            if(parentC!=nullptr) {
                makeLine(parentC, c);
            }
        }

        m[level]+=200;
        draw(root->left, m, level+1, r, c);
        draw(root->right, m, level+1, r, c);
        draw(root->next, m, level, r, c);

    }
};
#endif // MAINWINDOW_H
