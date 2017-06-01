#include "Header.h"

int main()
{
	system("chcp 1251 > nul");

	DBTableSet set;
	set.readSet("disks.txt");
	cout<<endl;

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
				Disk temp;
				temp.getProgList(set);
				break;
			}
		case 8:
			{
				Disk temp;
				temp.addDisk(set);
				break;
			}
		}

		system("pause");
		system("cls");
	}
	return 0;
}