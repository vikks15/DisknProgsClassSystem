#pragma once
#include "dbtable.h"

using namespace std;

class ProgProducts{
private:
	string name;
	int size;
public:
	string get_paramName();
	string set_paramName();

	int get_paramSize();
	int set_paramSize();
};

class Disk{
private:

	int totalSize;
	int curSize;
	DBtable prog; //list of programms on disk
public:
	string name;
	Disk(){};
	Disk(string& n, int& s1, int& s2)//constructor from name and size
	{
		name=n;
		totalSize=s1;
		curSize=s2;
	};
	~Disk(){};

	void getProgList(DBTableSet& mySet)
	{
		string name, filename;
		filename=(*this).name+"Prog.txt";
		mySet[filename].printTable();

	}

	void addDisk(DBTableSet& mySet)
	{
		string name, filename;
		filename = (*this).name+"Prog.txt";
		ofstream fout1 (filename); //make disk file
		fout1<<"1.Name|String|2.Size|Int";
		fout1.close();

		ofstream fout2 ("DisksInfo.txt", ios_base::app);
		fout2<<endl<<(*this).name<<"|"<<totalSize<<"|"<<curSize;
		fout2.close();

		ofstream fout3 ("disks.txt", ios_base::app);
		fout3<<endl<<filename;
		fout3.close();

		mySet.dbset.erase("DisksInfo.txt");
		mySet.addToSet("DisksInfo.txt");
		mySet.addToSet(filename);


	}
	void recordProg();
	void delProg();
	//void getProgByName();
};

int menu1()
{
	int number = 0;
	cout<<"1 - Вывести базу данных"<<endl;
	cout<<"2 - Вывести список дисков"<<endl;
	cout<<"3 - Вывести список программных продуктов на диске"<<endl;
	cout<<"4 - Объединить 2 диска"<<endl;
	cout<<"5 - Очистить диск"<<endl;
	cout<<"6 - Удалить программный продукт"<<endl;
	cout<<"7 - Добавить новый программный продукт"<<endl;
	cout<<"8 - Добавить новый диск"<<endl;
	cout<<"9 - Информация о программных продуктах"<<endl;
	cout<<"10 - Выйти"<<endl;
	cin>>number;

	cin.clear();
	cin.ignore(256,'\n');
	return number;
}

int diskSearch(string& nam, vector <Disk>& d)
{

	for(int i = 0; i<d.size(); i++)
	{
		if(d[i].name==nam) return i;
	}

	return -1;
}