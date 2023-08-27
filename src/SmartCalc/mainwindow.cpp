#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_leftBracket, SIGNAL(clicked()), this,
          SLOT(add_chars()));
  connect(ui->pushButton_rightBracket, SIGNAL(clicked()), this,
          SLOT(add_chars()));

  connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(add_chars()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(add_chars()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::add_chars() {
  QPushButton *button = (QPushButton *)sender();
  ui->expressionLine->setText(ui->expressionLine->text() + button->text());
}

void MainWindow::on_pushButton_clear_clicked() {
  ui->expressionLine->clear();
  ui->resultLine->clear();
}

void MainWindow::on_pushButton_equal_clicked() {
  ui->widget->clearGraphs();
  QByteArray ba = ui->expressionLine->text().toLocal8Bit();
  char *str = ba.data();
  char input_str[256] = {0};
  int i;
  for (i = 0; i < 255 && *str; i++) {
    input_str[i] = *str;
    str++;
  }
  double result = 0;

  char x_str[256] = {0};
  QByteArray ba2 = ui->doubleSpinBox_xvalue->text().toLocal8Bit();
  char *str2 = ba2.data();
  for (i = 0; i < 255 && *str2; i++) {
    x_str[i] = *str2;
    str2++;
  }

  int status = calculator(input_str, &result, x_str);
  if (status == INCORRECT_EXPRESSION) {
    ui->resultLine->setText("Invalid expression");
  } else {
    if (status == UNDEFINED) {
      ui->resultLine->setText("Undefined");
    } else {
      QString new_line = QString::number(result, 'g', 15);
      ui->resultLine->setText(new_line);
    }

    if (ui->checkBox_graph->isChecked()) {
      drawPlot(input_str);
    }
  }
}

void MainWindow::on_pushButton_clicked() {
  ui->expressionLine->setText(ui->resultLine->text());
}

void MainWindow::on_pushButton_delete_clicked() {
  QString str = ui->expressionLine->text();
  str.chop(1);
  ui->expressionLine->setText(str);
}

void MainWindow::drawPlot(char *expression) {
  struct node *expression_list = NULL;
  struct node *rpn = NULL;
  if (parse_expression(expression, &expression_list) == OK) {
    translate_to_RPN(expression_list, &rpn);
  }

  double xBegin = (ui->doubleSpinBox_xmin->text()).toDouble();
  double xEnd = (ui->doubleSpinBox_xmax->text()).toDouble();
  int N = 1e6;
  double h = (xEnd - xBegin) / N;

  if (ui->checkBox_autosetY->isChecked()) {
    autoset_y_axis(rpn, xBegin, xEnd, h);
  }

  ui->widget->xAxis->setRange(xBegin, xEnd);
  ui->widget->yAxis->setRange((ui->doubleSpinBox_ymin->text()).toDouble(),
                              (ui->doubleSpinBox_ymax->text()).toDouble());
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");

  int graphs_number = 0;
  for (double X = xBegin; X <= xEnd; X += h) {
    double Y = 0;
    int status = calculate(rpn, X, &Y);
    if (status == OK) {
      x.push_back(X);
      y.push_back(Y);
    } else if (!x.empty()) {
      ui->widget->addGraph();
      ui->widget->graph(graphs_number)->addData(x, y);
      x.clear();
      y.clear();
      graphs_number++;
    }
  }
  ui->widget->addGraph();
  if (!x.empty()) {
    ui->widget->graph(graphs_number)->addData(x, y);
  }
  ui->widget->replot();

  x.clear();
  y.clear();
}

void MainWindow::autoset_y_axis(struct node *rpn, double xBegin, double xEnd,
                                double h) {
  double ymax = -1e6, ymin = 1e6;
  for (double X = xBegin; X <= xEnd; X += h) {
    double Y = 0;
    int status = calculate(rpn, X, &Y);
    if (status == OK) {
      if (Y < ymin) {
        ymin = Y;
      }
      if (Y > ymax) {
        ymax = Y;
      }
    }
  }
  if (ymin < -1e6) {
    ymin = -1e6;
  }
  if (ymax > 1e6) {
    ymax = 1e6;
  }
  if (ymin > ymax) {
    ymin = -1e6;
    ymax = 1e6;
  }
  if (fabs(ymax - ymin) < 1e-2) {
    ymin = ymin - 0.01;
    ymax = ymax + 0.01;
  }
  ui->doubleSpinBox_ymin->setValue(ymin - 0.2 * fabs(ymax - ymin));
  ui->doubleSpinBox_ymax->setValue(ymax + 0.2 * fabs(ymax - ymin));
}
