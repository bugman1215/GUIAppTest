#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QTableWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void performCalculation();
    void updateHistory(double num1, double num2, const QString &op, double result);
    void clearHistory();

private:
    void setupUI();
    void loadStyleSheet();

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

