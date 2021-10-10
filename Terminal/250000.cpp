

#include <iostream>
#include <fstream>
#include <string>


using namespace std;

int timecheck(int* zaryad, int* Poryadok, int* Blatnie, int value, int num, int Slots_Count, int time)
{
	//num = num - 1;
	int kolvo = 0;
	if (zaryad[num] == 100)
		return 0;
	int x = (100 - zaryad[num]) / 20;
	if ((value < 80) or (Blatnie[num] == 1))
	{
		if (x * 20 + zaryad[num] < 100)
			return x + 1;
		else
			return x;
		
	}
	else
	{
		return (19 - time + x);
	}
}


bool check(int* arr, int elem)
{
	for (int i = 0; i < sizeof(arr); i++)
		if (elem == arr[i])
			return true;
	return false;
}

int* station(int value, int Slots_Count, int *arr, int *prev_por, int *blatnie, int* got_ind)
{
	int kolvo;
	int* ret_arr = new int[Slots_Count];
	
	for (int i = 0; i < Slots_Count; i++)
		ret_arr[i] = 0;

	if (value < 80)
		kolvo = Slots_Count;
	else if (value >= 98)
		kolvo = 0;
	else
		kolvo = (100 - value) / 3.75;


	//cout << endl << "kol-vo = " << kolvo << endl;
	int temp;
	for (int i = 0; i < Slots_Count - 1; i++) {
		for (int j = 0; j < Slots_Count - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {

				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;

				temp = prev_por[j];
				prev_por[j] = prev_por[j + 1];
				prev_por[j + 1] = temp;
			}
		}
	}
	
	//блатные
	int count = 0;
	for (int i = 0; i < Slots_Count; i++)
	{
		if (blatnie[i] == 1)
		{
			if (arr[i] < 100)
			{
				ret_arr[i] = 1;
				count++;
			}
		}
	}

	if (kolvo > count) //если остались слоты 
	{
		kolvo = kolvo - count;
		while (kolvo > 0)
		{
			for (int i = 0; i < Slots_Count; i++) //А чел уже не заряжен?
			{
				if (arr[i] > 100)
					arr[i] = 100;

				if (arr[i] == 100)
				{
					ret_arr[i] = 2;
					kolvo--;
					if (got_ind == 0)
					{
						got_ind[i] = 1; //зарядился челик
						//if (kolvo < 8) kolvo++;
					}
				}
			}
		

			for (int i = 0; i < Slots_Count; i++)//заряжаем челов
			{
				if (kolvo == 0) break;
				if (ret_arr[prev_por[i]] == 0) //челу надо?
				{
					ret_arr[prev_por[i]] = 1;

					kolvo--;
				}
				//else if ((ret_arr[i] == 2) and (got_ind[i] == 0))
					//if (kolvo < 8) kolvo++;
			}
			/*for (int i = 0; i < Slots_Count; i++) // ручная зарядка
				if (ret_arr[i] == 1)
					arr[i] += 2;*/



		} 
		
	}
	for (int i = 0; i < Slots_Count; i++) // ручная зарядка
	{
		if (arr[i] == 100)
			ret_arr[i] = 2;
		if (ret_arr[i] == 1)
			arr[i] += 20;
	}
	for (int i = 0; i < Slots_Count; i++)
		if (arr[i] > 100)
			arr[i] = 100;
	/*for (int i = 0; i < Slots_Count; i++)
	{
		if (arr[i] == 100)
		{
			ret_arr[i] = 0;
			if (kolvo < Slots_Count)
			kolvo++;
		}
	}*/


	//Заполнение дефолтных
	/*for (int i = 0; i < kolvo - count; i++)
		if (ret_arr[prev_por[i]] == 1)
			kolvo++;
		else
			ret_arr[prev_por[i]] = 1;*/

	return ret_arr;
}





int main()
{
	int mashNum;
	int Slots_Count = 9;
	int* got_ind = new int[Slots_Count];
	int* Poryadok = new int[Slots_Count];
	for (int i = 0; i < Slots_Count; i++)
	{
		Poryadok[i] = i;
		got_ind[i] = 0;
	}

	int* Blatnie = new int[Slots_Count];
	int* FileArray = new int[Slots_Count];
	int* StationArray = new int[Slots_Count];
	char ch[4];
	int value, status, kol = 0;
	setlocale(LC_ALL, "rus");
	ifstream fin1("grafiki.txt");
	
	
	/*fin2 >> ch;
	kol = stoi(ch);
	for (int i = 0; i < kol; i++)
	{
		fin2 >> ch;
		FileArray[i] = stoi(ch);
	}
	for (int i = 0; i < kol; i++)
	{
		fin2 >> ch;
		Blatnie[i] = stoi(ch);
	}*/
	

	/*cout << "FileArray: " << endl;
	for (int i = 0; i < kol; i++)
		cout << FileArray[i] << " ";

	cout << "blatnie: " << endl;
	for (int i = 0; i < kol; i++)
		cout << Blatnie[i] << " ";*/

	fin1 >> ch; 
	value = stoi(ch);
	int x;
	cout << "Вы хотите знать время зарядки? (1 - да, 2 - нет) >> ";
	cin >> x;
	

	int kolich = 0;
	while (value != 0)
	{
		ifstream fin2("station.txt");
		fin2 >> ch;
		kol = stoi(ch);
		for (int i = 0; i < kol; i++)
		{
			fin2 >> ch;
			FileArray[i] = stoi(ch);
		}
		for (int i = 0; i < kol; i++)
		{
			fin2 >> ch;
			Blatnie[i] = stoi(ch);
		}
		fin2.close();

		/*cout << "FileArray: " << endl;
		for (int i = 0; i < kol; i++)
			cout << FileArray[i] << " ";

		cout << "blatnie: " << endl;
		for (int i = 0; i < kol; i++)
			cout << Blatnie[i] << " ";*/


		//cout <<"Часы: " << kolich << endl;
		if (kolich == 24)
			kolich = 0;
		kolich++;

		fin1 >> ch;
		value = stoi(ch);
		//cout << "value:" << value << endl;
		if (x == 1)
		{
			cout << "Введите номер вашей машины (число от 1 до 9) >> ";
			cin >> mashNum;
			mashNum--;
			if (Blatnie[mashNum] == 1)
				cout << "Вы приобрели ускоренную зарядку"<< endl;
			else
				cout << "У вас стоит режим медленной зарядки " << endl;
			cout << "Уровень заряда вашей машины: " << FileArray[mashNum] << "%" << endl;
			cout << "Примерное время ожидания: " << timecheck(FileArray, Poryadok, Blatnie, value, mashNum, Slots_Count, kolich) << " часа" << endl;
		}
		StationArray = station(value, Slots_Count, FileArray, Poryadok, Blatnie, got_ind);
		
		int temp;
		for (int i = 0; i < Slots_Count - 1; i++) {
			for (int j = 0; j < Slots_Count - i - 1; j++) {
				if (Poryadok[j] > Poryadok[j + 1]) {

					temp = Poryadok[j];
					Poryadok[j] = Poryadok[j + 1];
					Poryadok[j + 1] = temp;

					temp = FileArray[j];
					FileArray[j] = FileArray[j + 1];
					FileArray[j + 1] = temp;

					temp = StationArray[j];
					StationArray[j] = StationArray[j + 1];
					StationArray[j + 1] = temp;
				}
			}
		}

		//for (int i = 0; i < Slots_Count; i++)
			//cout << StationArray[i] << " ";
		
		//cout << endl;
		//for (int i = 0; i < Slots_Count; i++)
			//cout << FileArray[i] << " ";

		//cout << endl;
		//for (int i = 0; i < Slots_Count; i++)
		//	cout << Poryadok[i] << " ";

		

	}
	fin1.close();
	return 0;
}
