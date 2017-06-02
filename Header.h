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

	void addToDisk(vector <Disk>& vect)
	{
		ofstream fout("DisksInfo.txt", ios_base::app);
		for(int i = 0; i<vect.size(); i++)
		{
			fout<<endl<<vect[i].name<<"|"<<vect[i].totalSize<<"|"<<vect[i].curSize;
		}
		fout.close();
	}

	void clean(DBTableSet& set)
	{
		string name, filename;
		filename = (*this).name+"Prog.txt";
		ofstream fout;
		fout.open(filename);
		fout<<"1.Name|String|2.Size|Int";
		fout.close();
		(*this).curSize = (*this).totalSize; //clean free space in vector
	}
	void del(DBTableSet& set)
	{
		string filename = (*this).name+"Prog.txt";

		if(set[filename].data.size()!=0)
		{
			cout<<"Перед тем как удалить диск нужно его очистить."<<endl;
			return;
		}
		remove(filename.c_str());

	}
	void addNewDisk(DBTableSet& mySet)
	{
		string name, filename;
		filename = (*this).name+"Prog.txt";
		ofstream fout;

		fout.open(filename); //make disk file
		fout<<"1.Name|String|2.Size|Int";
		fout.close();

		fout.open("DisksInfo.txt", ios_base::app);
		fout<<endl<<(*this).name<<"|"<<totalSize<<"|"<<curSize;
		fout.close();

		fout.open("disks.txt", ios_base::app);
		fout<<endl<<filename;
		fout.close();

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
	cout<<"2 - Вывести список дисков и информацию о них"<<endl;
	cout<<"3 - Вывести список программных продуктов на диске"<<endl;
	cout<<"4 - Объединить 2 диска"<<endl;
	cout<<"5 - Очистить диск"<<endl;
	cout<<"6 - Удалить диск"<<endl;
	cout<<"7 - Удалить программный продукт"<<endl;
	cout<<"8 - Добавить новый программный продукт"<<endl;
	cout<<"9 - Добавить новый диск"<<endl;
	cout<<"10 - Информация о программных продуктах"<<endl;
	cout<<"11 - Выйти"<<endl;
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