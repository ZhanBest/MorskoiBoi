#include <iostream> 
#include <iomanip> 
#include <ctime> 
#include <windows.h>  

using namespace std;

void printPole(int PolePrint[10][10], bool showShips) {//Функция на ростановку кораблей
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (PolePrint[i][j] == 9) {
                cout << (char)219 << " "; // Попадание 
            }
            else if (PolePrint[i][j] == 8) {
                cout << (char)193 << " ";// Промах 
            }
            else if (showShips && PolePrint[i][j] == 1) {
                cout << (char)220 << " ";// Корабль 
            }
            else {
                cout << ". "; // Пустое место 
            }
        }
        cout << endl;
    }
}

bool shoot(int shot[10][10], int x, int y) {//Функция выстрела
    if (shot[x][y] == 1) {
        shot[x][y] = 9;
        return true;
    }
    else if (shot[x][y] == 0) {
        shot[x][y] = 8; // Промах 
        return false;
    }
    return false;
}
void setupShips(int field[10][10]) {//Фунуция по растоновке кораблей
    int shipsToPlace = 5;
    int x, y;
    while (shipsToPlace > 0) {
        x = rand() % 10;
        y = rand() % 10;
        if (field[x][y] == 0) {
            field[x][y] = 1; // корабль 
            shipsToPlace--;
        }
    }
}
int main()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);//Убирает курсор
    srand(time(NULL));
    system("color F2");
    SetConsoleTitle(L"Морской бой.");
    /*setlocale(LC_ALL, "Russian");*/
    cout << "Welcome Fuhrer. You are playing a sea battle!!!" << endl;
    cout << "Here you can play with a friend." << endl;
    cout << "Rules of the game" << endl;
    cout << "Field size - 10 * 10\n";
    cout << "The players draw lots to choose who shoots first,\n"
        << "Next, the ships are arranged randomly and each player takes turns,\n"
        << "If the player destroys the ship, he goes again.\n"
        << "Побеждает тот кто убил 5 кораблей противника.\n"
        << "Желаю удачи!\n";
    cout << endl;
    int playerField[10][10] = {};
    int enemyField[10][10] = {};
    int enemySecretField[10][10] = {};
    setupShips(playerField); // корабли игрока 
    setupShips(enemyField);  // корабли противника 
    bool gameOver = false;
    int playerHits = 0;//Количевство поподаний игрока
    int enemyHits = 0;//Количевство поподаний противника
    const int shipsToWin = 5;//Количевство кораблей для выйгрыша
    while (!gameOver) {
        int x, y;
        cout << "Your field \n";
        printPole(playerField, true);//Поле игрока
        cout << "Enemy Field \n";
        printPole(enemySecretField, false);//Поле противника
        do {
            cout << "Enter shot x coordinates: ";
            cin >> x;
            cout << "Enter the shot y coordinates: ";
            cin >> y;
        } while ((x > 9 || x < 0) && (y > 9 || y < 0));
        if (shoot(enemyField, x, y)) {//Вычтрел игрока
            cout << "Hit!" << endl;
            enemySecretField[x][y] = 9;
            playerHits++;
            if (playerHits == shipsToWin) {//Проверка победы
                cout << "You won!" << endl;
                gameOver = true;
                break;
            }
        }
        else {
            cout << "Miss!" << endl;
            enemySecretField[x][y] = 8;
        }
        do {
            x = rand() % 10;
            y = rand() % 10;
        } while (playerField[x][y] == 8 || playerField[x][y] == 9);

        if (shoot(playerField, x, y)) {//Выстрел противника
            cout << "The enemy has hit your ship!" << endl;
            enemyHits++;
            if (enemyHits == shipsToWin) {//Проверка победы
                cout << "You lose!" << endl;
                gameOver = true;
                break;
            }
        }
        else {
            cout << "The enemy missed!" << endl;
        }
    }
}