// Расчетная работа
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <stack>
using namespace std;

int main() {
	int kolver;
	char st[51];
	char* temp = NULL;
	char* token, f_input[]="input.txt";
	long siztime;

	// Открытие файла для ввода
	ifstream fin(f_input);
	if (!fin) {

		cout << "File " << f_input << " open error" << endl;
		system("pause");
		return 1;
	}//*/
	fin.getline(st, 50);

	// Выделяем первое число 
	temp = strtok_s(st, " ", &token);

	// Количество наших любимых вершин нашего любимого графа:)
	kolver = atoi(temp);
	
	vector<vector<int>>matsm(kolver, vector<int>(kolver));

	// Текущее местоположение в файле
	fin.getline(st, 50);
	siztime = fin.tellg();

	// Заполнение матрицы смежности
	for (int i = 0; i < kolver; i++) {

		// Передвинули на правильное местоположение
		fin.seekg(siztime, ios::beg);

		fin.getline(st, 50);
		fin.clear();
		siztime = fin.tellg();

		// Выделяем первое число 
		temp = strtok_s(st, " ", &token);

		for (int j = 0; j < kolver; j++) {
			// Выделяем числа по очереди
			temp = strtok_s(NULL, " ", &token);
			if (!temp)
				break;

			matsm[i][j] = atoi(temp);
		}
	}
	
	fin.close();

	// Вывод матрицы
	cout << "The matrix is.." << endl;
	cout << "   ";
	for (int i = 0; i < kolver; i++) {
		cout <<setw(3)<< i+1;
	}
	cout << endl;

	for (int i = 0; i < kolver; i++) {
		cout << setw(3) << i + 1;
		for (int j = 0; j < kolver; j++) {
		    cout <<setw(3)<< matsm[i][j];
		}
		cout << endl;
	}

	char f_output[] = "output.txt";
	// Открытие файла для вывода
	ofstream fout(f_output);
	if (!fout) {

		cout << "File " << f_output << " create error" << endl;
		system("pause");
		return 2;
	}
	
	// Проверка, связный ли граф
	vector<bool>possibility(kolver, false);
	stack<int>smversteck;
	int k = 0;

	smversteck.push(0);
	while (!smversteck.empty()) {

		int vernow = smversteck.top();  // Достаем вершину
		smversteck.pop();  // Удаляем вершину

		if (!possibility[vernow]) {
			possibility[vernow] = true;  // Обозначаем вершину как пройденную

			for (int i = 0; i < kolver; i++) {

				if (matsm[vernow][i]) {
					smversteck.push(i);  // Помещаем в стек вершины графа, с которой у данной есть ребра
				}

			}
		}
		
	}
			
	// Если граф несвязный, вывод сообщения
	for (int i = 0; i < kolver; i++) {
		if (!possibility[i]) {
			cout << "Impossible" << endl;
			fout << "Impossible";

			system("pause");
			return 0;
		}
	}

	// Подсчет количества ребер графа
	int kolreb = 0;

	for (int i = 0; i < kolver; i++) {
		for (int j = i; j < kolver; j++) {

				if (matsm[i][j]) {
						kolreb++;
				}
		}
	}

	int kol = kolreb - (kolver - 1);

	fout << kol;
	cout << endl << "kol = " << kol << endl;

	fout.close();

	system("pause");
}
