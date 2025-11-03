#include <iostream>
#include <fstream> 
#include <iomanip> 
#include <numeric> 

using namespace std;

int main() {
  
    ifstream inputFile("number.txt"); // 1-й спосіб відкриття файлу для читання [cite: 19]

    if (!inputFile) {
        cerr << "Не вдалося відкрити файл 'number.txt' для читання." << endl;
        return 1; // Завершення програми з кодом помилки
    }

    int number;
    int even_sum = 0;   // Сума парних чисел
    int even_count = 0; // Кількість парних чисел

    while (inputFile >> number) {
        if (number % 2 == 0) {
            even_sum += number; // Накопичення суми
            even_count++;       // Збільшення лічильника
        }
    }

    inputFile.close();

    cout << "--- Обробка файлу 'number.txt' ---" << endl;

    if (even_count > 0) {
        double average = (double)even_sum / even_count;

        cout << "Сума парних чисел: " << even_sum << endl;
        cout << "Кількість парних чисел: " << even_count << endl;
   
        cout << "Середнє арифметичне парних чисел: " << fixed << setprecision(2) << average << endl;
    } else {
        cout << "У файлі не знайдено парних чисел." << endl;
    }

    return 0;
}