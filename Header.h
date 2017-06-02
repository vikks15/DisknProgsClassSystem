#pragma once
#include "dbtable.h"

using namespace std;

class ProgProducts{
private:

	int size;
public:
	string name;
	ProgProducts(string& n, int& s1)
	{
		name = n;
		size = s1;
	};
	~ProgProducts(){};

	void del(DBTableSet& set, vector <ProgProducts>& vect)
	{
		string dname, pname, filename;
		int num=-1;
		cout<<"Введите имя диска: ";
		getline(cin,dname);
		progsToVector(set,vect,dname);
		filename=dname+"Prog.txt";

		cout<<"Введите имя удаляеммой программы: ";
		getline(cin,pname);
		for(int i = 0; i<vect.size(); i++)
		{
			if(vect[i].name == pname) num=i;
		}

		if(num==-1)
		{
			cout<<"Такой программы нет на диске.";
			return;
		}

		vect.erase(vect.begin()+num);

		ofstream fout;
		fout.open(filename);
		fout<<"1.Name|String|2.TotalSize|Int|3.CurSize|Int";

		//fout.open(filename, ios_base::app);
		for(int i = 0; i<vect.size(); i++)
		{
			fout<<endl<<vect[i].name<<"|"<<vect[i].size;
		}
		fout.close();

	}
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

	void addToDisk(vector <Disk>& vect, const string& filename)
	{
		ofstream fout(filename, ios_base::app);
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
		set.dbset.erase(filename);

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

void progsToVector(DBTableSet& set, vector <ProgProducts>& vect, string& dname)
{
	int s;
	string filename=dname+"Prog.txt";
	for(int i = 0; i<set[filename].data.size(); i++)
	{
		dname = (char*)set[filename].data[i]["1.Name"];
		s = *(int*)set[filename].data[i]["2.Size"];
		vect.push_back(ProgProducts(dname,s));
	}
}