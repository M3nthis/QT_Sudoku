#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QIntValidator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QLineEdit ***grid;
    QIntValidator *validator;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void grid_initialization();
    bool solve_sudoku(unsigned int col, unsigned int row);
    bool solve_sudoku(int **tmp_grid, unsigned int col, unsigned int row);
    bool isSafe(const int row, const int col, const int num);
    bool isSafe(int **tmp_grid, const int row, const int col, const int num);
    void reset_grid();
    bool thereAreInvalidCharacters();
    bool thereAreInvalidCharacters(int **tmp_grid);
    void showError();
    void changeCellsReadStatus(bool status);

private slots:
    void on_button_resolve_clicked();
    void on_button_reset_clicked();
    void on_button_step_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
