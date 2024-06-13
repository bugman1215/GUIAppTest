#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    loadStyleSheet();
    setupUI();
// connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(performCalculation()));
    connect(ui->calculateButton, SIGNAL(clicked()), this, SLOT(performCalculation()));
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::clearHistory);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::loadStyleSheet() {
    QFile file("style.qss");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        QString stylesheet = stream.readAll();
        setStyleSheet(stylesheet);
        file.close();
    }
}

void MainWindow::setupUI() {
    ui->comboBox->addItem("+");
    ui->comboBox->addItem("-");
    ui->comboBox->addItem("*");
    ui->comboBox->addItem("/");
    ui->historyTable->setColumnCount(4);
    QStringList headers{"Input 1", "Operator", "Input 2", "Result"};
    ui->historyTable->setHorizontalHeaderLabels(headers);
}

void MainWindow::performCalculation() {
    bool ok1, ok2;
    double num1 = ui->input1->text().toDouble(&ok1);
    double num2 = ui->input2->text().toDouble(&ok2);
    double result = 0;
    QString op = ui->comboBox->currentText();

    if (!ok1 || !ok2) {
        QMessageBox::warning(this, "Input Error", "Please enter valid numbers.");
        return;
    }

    if (op == "+") result = num1 + num2;
    else if (op == "-") result = num1 - num2;
    else if (op == "*") result = num1 * num2;
    else if (op == "/") result = (num2 != 0) ? num1 / num2 : std::numeric_limits<double>::infinity();

    ui->resultLabel->setText("Result: " + QString::number(result));
    updateHistory(num1, num2, op, result);
}

void MainWindow::updateHistory(double num1, double num2, const QString &op, double result) {
    int row = ui->historyTable->rowCount();
    ui->historyTable->insertRow(row);
    ui->historyTable->setItem(row, 0, new QTableWidgetItem(QString::number(num1)));
    ui->historyTable->setItem(row, 1, new QTableWidgetItem(op));
    ui->historyTable->setItem(row, 2, new QTableWidgetItem(QString::number(num2)));
    ui->historyTable->setItem(row, 3, new QTableWidgetItem(QString::number(result)));
}
void MainWindow::clearHistory() {
    ui->historyTable->setRowCount(0);
}
