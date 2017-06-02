#include "Header.h"

int main()
{
	system("chcp 1251 > nul");

	vector <Disk> myDisks;
	vector <ProgProducts> diskProgs;
	DBTableSet set;
	set.readSet("disks.txt");

	string name;
	int size;
	int s, curS;
	//----------------------add disks to vector---------------------------------
	for(int i = 0; i<set["DisksInfo.txt"].data.size(); i++)
	{
		name = (char*)set["DisksInfo.txt"].data[i]["1.Name"];
		s = *(int*)set["DisksInfo.txt"].data[i]["2.TotalSize"];
		curS = *(int*)set["DisksInfo.txt"].data[i]["3.CurSize"];
		myDisks.push_back(Disk(name,s,curS));
	}
	//-------------------------------------------------------------------------

	while(true)
	{
		switch(menu1())
		{
		case 1:
			{
				set.printSet();
				break;
			}
		case 2:
			{
				set["DisksInfo.txt"].printTable();
				break;
			}
		case 3:
			{

				cout<<"Введите имя диска: ";
				getline(cin,name);
				int find = diskSearch(name,myDisks);
				if(find==-1) 
				{
					cout<<"Такого диска нет в базе";
					break;
				}
				myDisks[find].getProgList(set);
				break;
			}
		case 5:
			{
				cout<<"Введите имя диска: ";
				getline(cin,name);
				int find = diskSearch(name,myDisks);
				if(find==-1) 
				{
					cout<<"Такого диска нет в базе";
					break;
				}

				myDisks[find].clean(set);//clean in file and in vector

				ofstream fout("DisksInfo.txt");
				fout<<"1.Name|String|2.TotalSize|Int|3.CurSize|Int";
				fout.close();

				myDisks[find].addToDisk(myDisks); //change info of free space
				break;
			}
		case 6:
			{
				string filename;
				cout<<"Введите имя диска: ";
				getline(cin,name);
				int find = diskSearch(name,myDisks);
				if(find==-1) 
				{
					cout<<"Такого диска нет в базе";
					break;
				}
				myDisks[find].del(set);
				myDisks.erase(myDisks.begin()+find); //delete from vector

				ofstream fout;
				fout.open("DisksInfo.txt");
				fout<<"1.Name|String|2.TotalSize|Int|3.CurSize|Int";
				fout.close();
				myDisks[find-1].addToDisk(myDisks); //rewrite disks info

				fout.open("disks.txt");
				for(int i = 0; i<myDisks.size(); i++)
				{
					filename = myDisks[i].name+"Prog.txt";
					fout<<filename<<endl;
				}
				break;
			}
		case 8:
			{
				cout<<"Введите имя диска: ";
				getline(cin,name);

				int find = diskSearch(name,myDisks);
				if(find!=-1) 
				{
					cout<<"Такой диск уже существует. Введите другое имя диска."<<endl;
					break;
				}

				cout<<"Введите размер диска (в Гб): ";
				cin>>size;
				Disk newDisk(name,size,size);
				newDisk.addNewDisk(set);
				myDisks.push_back(newDisk);

				cout<<"try "<<newDisk.name<<"=="<<myDisks[2].name;

				break;
			}
		}

		system("pause");
		system("cls");
	}
	return 0;
}