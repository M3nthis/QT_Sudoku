#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , grid(nullptr)
    , validator(nullptr)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    grid_initialization();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete validator;
    validator = nullptr;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            delete grid[i][j];
            grid[i][j] = nullptr;
        }
        delete[] grid[i];
        grid[i] = nullptr;
    }
    delete[] grid;
    grid = nullptr;
}

void MainWindow::grid_initialization(){
    QList<QLineEdit*> gridCells = ui->frameEditText->findChildren<QLineEdit*>();
    QListIterator<QLineEdit*> iCells(gridCells);

    validator = new QIntValidator(1, 9, this);
    grid = new QLineEdit **[9];
    for(unsigned int i = 0; i < 9; i++){
        grid[i] = new QLineEdit*[9];
        for(unsigned j = 0; j < 9; j++){
            QLineEdit* cell = iCells.next();
            cell->setValidator(validator);
            cell->setMaxLength(1);
            grid[i][j] = cell; // Salvo puntatore alla cella
        }
    }
}

bool MainWindow::solve_sudoku(unsigned int col, unsigned int row){

    if (col >= 9)
    {
        ++row;
        col = 0;
        if (row >= 9)
        {
            return true;
        }
    }

    if (grid[row][col]->text() != "")
        return solve_sudoku(col + 1, row);

    // NUMERI SCELTI PER LA CASELLA (PARTE DA 1)
    for (int i = 1; i < 10; i++)
    {
        if (isSafe(row, col, i))
        {
            //int oldNumber = board[row][col];
            QString sNum = QString::number(i);
            grid[row][col]->setText(sNum);

            if (solve_sudoku(col + 1, row)) // PASSO RICORSIVO
                return true;

            grid[row][col]->setText(""); // BACKTRACK
        }
    }

    return false;
}

bool MainWindow::solve_sudoku(int **tmp_grid,unsigned int col, unsigned int row){
    if (col >= 9)
    {
        ++row;
        col = 0;
        if (row >= 9)
        {
            return true;
        }
    }

    if (tmp_grid[row][col] > 0)
        return solve_sudoku(tmp_grid, col + 1, row);

    // NUMERI SCELTI PER LA CASELLA (PARTE DA 1)
    for (int i = 1; i < 10; i++)
    {
        if (isSafe(tmp_grid, row, col, i))
        {
            tmp_grid[row][col] = i;

            if (solve_sudoku(tmp_grid, col + 1, row)) // PASSO RICORSIVO
                return true;

            tmp_grid[row][col] = 0; // BACKTRACK
        }
    }

    return false;
}

bool MainWindow::isSafe(const int row, const int col, const int num){
    int i, j;
    QString sNum = QString::number(num);

    for (i = 0; i < 9; i++)
        if (grid[row][i]->text() == sNum)
            return false;

    for (i = 0; i < 9; i++)
        if (grid[i][col]->text() == sNum)
            return false;

    int rowLevel = row / 3;
    int colLevel = col / 3;
    for (i = rowLevel * 3; i < (rowLevel * 3) + 3; i++)
    {
        for (j = colLevel * 3; j < (colLevel * 3) + 3; j++)
        {
            if (grid[i][j]->text() == sNum)
                return false;
        }
    }
    return true;
}

bool MainWindow::isSafe(int **tmp_grid, const int row, const int col, const int num){
    int i, j;

    for (i = 0; i < 9; i++)
        if (tmp_grid[row][i] == num)
            return false;

    for (i = 0; i < 9; i++)
        if (tmp_grid[i][col] == num)
            return false;

    int rowLevel = row / 3;
    int colLevel = col / 3;
    for (i = rowLevel * 3; i < (rowLevel * 3) + 3; i++)
    {
        for (j = colLevel * 3; j < (colLevel * 3) + 3; j++)
        {
            if (tmp_grid[i][j] == num)
                return false;
        }
    }
    return true;
}

bool MainWindow::thereAreInvalidCharacters()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            QString num = grid[i][j]->text();
            if (num != "")
            {
                for (int colIndex = 0; colIndex < j; colIndex++)
                    if (grid[i][colIndex]->text() == num)
                        return true;
                for (int colIndex = j + 1; colIndex < 9; colIndex++)
                    if (grid[i][colIndex]->text() == num)
                        return true;

                for (int rowIndex = 0; rowIndex < i; rowIndex++)
                    if (grid[rowIndex][j]->text() == num)
                        return true;
                for (int rowIndex = i + 1; rowIndex < 9; rowIndex++)
                    if (grid[rowIndex][j]->text() == num)
                        return true;

                int rowLevel = i / 3;
                int colLevel = j / 3;
                int count = 0;
                for (int cellsIndex = rowLevel * 3; cellsIndex < (rowLevel * 3) + 3; cellsIndex++)
                {
                    for (int k = colLevel * 3; k < (colLevel * 3) + 3; k++)
                    {
                        if (grid[cellsIndex][k]->text() == num)
                            count++;
                    }
                }
                if (count > 1)
                    return true;
            }
        }
    }
    return false;
}

bool MainWindow::thereAreInvalidCharacters(int **tmp_grid)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            int num = tmp_grid[i][j];
            if (num > 0)
            {
                for (int colIndex = 0; colIndex < j; colIndex++)
                    if (tmp_grid[i][colIndex] == num)
                        return true;
                for (int colIndex = j + 1; colIndex < 9; colIndex++)
                    if (tmp_grid[i][colIndex] == num)
                        return true;

                for (int rowIndex = 0; rowIndex < i; rowIndex++)
                    if (tmp_grid[rowIndex][j] == num)
                        return true;
                for (int rowIndex = i + 1; rowIndex < 9; rowIndex++)
                    if (tmp_grid[rowIndex][j] == num)
                        return true;

                int rowLevel = i / 3;
                int colLevel = j / 3;
                int count = 0;
                for (int cellsIndex = rowLevel * 3; cellsIndex < (rowLevel * 3) + 3; cellsIndex++)
                {
                    for (int k = colLevel * 3; k < (colLevel * 3) + 3; k++)
                    {
                        if (tmp_grid[cellsIndex][k] == num)
                            count++;
                    }
                }
                if (count > 1)
                    return true;
            }
        }
    }
    return false;
}

void MainWindow::reset_grid(){
    for(unsigned int i = 0; i < 9; i++){
        for(unsigned int j = 0; j < 9; j++){
            grid[i][j]->setText("");
        }
    }
}

void MainWindow::on_button_resolve_clicked()
{
    if(thereAreInvalidCharacters() || !solve_sudoku(0,0)){
        showError();
    }
}

void MainWindow::on_button_reset_clicked()
{
    reset_grid();
    changeCellsReadStatus(false);
    ui->labelError->setText("");
}

void MainWindow::on_button_step_clicked()
{
    int **tmp_grid = new int *[9];
    for (int i = 0; i < 9; i++)
    {
        tmp_grid[i] = new int[9];
        for (int j = 0; j < 9; j++)
            if(grid[i][j]->text() == "")
                tmp_grid[i][j] = 0;
            else
                tmp_grid[i][j] = grid[i][j]->text().toInt();
    }


    if (thereAreInvalidCharacters(tmp_grid) || !solve_sudoku(tmp_grid, 0, 0))
    {
        showError();
    }else{
        int row, col;
        bool found = false;
        // Prima cella libera
        for (int i = 0; i < 9; i++){
            if(!found){
                for (int j = 0; j < 9; j++){
                    if(grid[i][j]->text() == ""){
                        row = i;
                        col = j;
                        found = true;
                        break;
                    }
                }
            }
        }
        // Aggiungi singolo valore nella griglia
        if(found)
            grid[row][col]->setText(QString::number(tmp_grid[row][col]));
    }

    // Clean Heap
    for (int i = 0; i < 9; i++)
    {
        delete[] tmp_grid[i];
        tmp_grid[i] = nullptr;
    }
    delete[] tmp_grid;
    tmp_grid = nullptr;
}

void MainWindow::showError(){
    ui->labelError->setText("Errore nella risoluzione");
    changeCellsReadStatus(true);
}

void MainWindow::changeCellsReadStatus(bool status){
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++){
            grid[i][j]->setReadOnly(status);
        }
    }
}
