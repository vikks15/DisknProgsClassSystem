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
	cout<<"nameee "<<myDisks[1].name;

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
				for(int i = 0; i < set["DisksInfo.txt"].data.size(); i++) cout<<(char*)set["DisksInfo.txt"].data[i]["1.Name"]<<endl;
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
				newDisk.addDisk(set);
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