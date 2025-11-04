#include <iostream>
#include <fstream> // Додано для роботи з файлами
#include <cstring>
#include <iomanip>
using namespace std;

struct Price {
    char productName[30];    // Назва товару
    char manufacturer[30];  // Назва фірми-виробника
    float cost;              // Вартість товару в грн.
    int size[5];             // Розміри (масив з 5 елементів)
};

void saveToFile(const Price products[], int N, const char* filename); // Прототип функції

int main() {

    const int N = 8;
    Price products[N];

    // --- Введення даних ---
    cout << "Введіть дані про " << N << " товарів:\n";
    for (int i = 0; i < N; ++i) {
        cout << "\nТовар №" << i + 1 << ":\n";

        // Очищення буфера перед першим cin.getline (на випадок попереднього числового вводу)
        if (i == 0) cin.ignore(1000, '\n'); 

        cout << "Назва товару: ";
        cin.getline(products[i].productName, sizeof(products[i].productName));

        cout << "Фірма-виробник: ";
        cin.getline(products[i].manufacturer, sizeof(products[i].manufacturer));

        cout << "Вартість (грн): ";
        cin >> products[i].cost;

        cout << "Введіть 5 розмірів (через пробіл): ";
        for (int j = 0; j < 5; ++j) {
            cin >> products[i].size[j];
        }

        
        cin.ignore(1000, '\n');
    }

    for (int i = 0; i < N - 1; ++i) {
        int idxMax = i;
        for (int j = i + 1; j < N; ++j) {
            if (products[j].cost > products[idxMax].cost) {
                idxMax = j;
            }
        }
        if (idxMax != i) {
            Price tmp = products[i];
            products[i] = products[idxMax];
            products[idxMax] = tmp;
        }
    }

    saveToFile(products, N, "results.txt");
    cout << "\n✅ Відсортовані дані успішно записано у файл **results.txt**.\n";

    cout << "\nВідсортований список товарів за спаданням вартості:\n";

    cout << fixed << setprecision(2); 
    for (int i = 0; i < N; ++i) {
        cout << i + 1 << ". " << products[i].productName
             << " | " << products[i].manufacturer
             << " | " << products[i].cost << " грн\n";
    }

    char searchName[30];
    int searchSize;
    cout << "\nВведіть назву товару для пошуку: ";
    cin.getline(searchName, sizeof(searchName));

    cout << "Введіть розмір для пошуку (ціле число): ";
    cin >> searchSize;

    bool found = false;
    for (int i = 0; i < N; ++i) {
        if (strcmp(products[i].productName, searchName) == 0) {
            for (int j = 0; j < 5; ++j) {
                if (products[i].size[j] == searchSize) {
                    cout << "\nЗнайдено товар:\n";
                    cout << "Назва: " << products[i].productName << endl;
                    cout << "Виробник: " << products[i].manufacturer << endl;
                    cout << "Вартість: " << products[i].cost << " грн\n";
                    cout << "Розміри: ";
                    for (int k = 0; k < 5; ++k) cout << products[i].size[k] << " ";
                    cout << endl;
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
    }

    if (!found) {
        cout << "\nТовар із заданою назвою і розміром не знайдено.\n";
    }

    return 0;
}

void saveToFile(const Price products[], int N, const char* filename) {
    ofstream outFile(filename);

    if (!outFile.is_open()) {
        cerr << "Помилка: Не вдалося відкрити/створити файл " << filename << " для запису.\n";
        return;
    }


    outFile << "--- Список товарів (відсортовано за спаданням вартості) ---\n";
    outFile << left << setw(3) << "#"
            << setw(30) << "Назва товару"
            << setw(30) << "Виробник"
            << setw(10) << "Вартість"
            << "Розміри\n";
    outFile << string(75, '-') << "\n";
    
    
    outFile << fixed << setprecision(2);

    for (int i = 0; i < N; ++i) {
        outFile << left << setw(3) << i + 1
                << setw(30) << products[i].productName
                << setw(30) << products[i].manufacturer
                << setw(10) << products[i].cost; // Вартість


        for (int j = 0; j < 5; ++j) {
            outFile << products[i].size[j] << (j < 4 ? " " : "");
        }
        outFile << "\n";
    }

    outFile.close();
}