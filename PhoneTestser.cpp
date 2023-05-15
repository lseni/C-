
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

void addRecord();
void showRecord();
void searchRecord();
void modifyRecord();
void deleteRecord();

class record
{
	char name[20];
	int phone;
public:
	void get(void);
	void show(void);
	int getPhone();
};

int main()
{
	char choice;
	
	cout.setf(ios::fixed | ios::showpoint);
	cout << setprecision(2);
	do
	{
		system("cls");
		cout << "-------------------------------------------\n";
		cout << "1. Add Telephone Record\n";
		cout << "2. Show Records\n";
		cout << "3. Search Telephone Records\n";
		cout << "4. Modify Record\n";
		cout << "5. Delete Record\n";
		cout << "6. EXIT\n";
		cout << "-------------------------------------------\n";
		cout << "Enter the number : ";
		cin >> choice;
		system("cls");
		
		switch (choice)
		{
			case '1':	addRecord(); 
						break;
			case '2':	showRecord(); 
						break;
			case '3':	searchRecord(); 
						break;
			case '4':	modifyRecord(); 
						break;
			case '5':	deleteRecord(); 
						break;
			case '6':	exit(0);
			default:	cout << "Error.";
 
		}
	} while (choice != '7');
 
	return 0;
}

void record::get(void)
{
	cout << "Enter the name: ";
	cin.ignore();
	cin.getline(name, 20);
	cout << "Enter the phone number: ";
	cin >> phone;
}
 
 
void record::show()
{
	cout << "Name: " << name;
	cout << "\nPhone Number: " << phone;
}
 
int record::getPhone()
{
	return phone;
}

void addRecord()
{
	record person;
	ofstream outFile;
	outFile.open("record.dat", ios::binary | ios::app);
	person.get();
	outFile.write(reinterpret_cast<char *> (&person), sizeof(record));
	outFile.close();
	cout << "\nAdded.";
	cin.ignore();
	cin.get();
}

void showRecord()
{
	record person;
	ifstream inFile;
	inFile.open("record.dat", ios::binary);
	if (!inFile)
	{
		cout << "Error!";
		cin.ignore();
		cin.get();
		return;
	}
	cout << "Show Record";
	cout << "\n*********************************\n";
	while (inFile.read(reinterpret_cast<char *> (&person), sizeof(record)))
	{
		person.show();
		cout << "\n----------------------------------\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}

void searchRecord()
{
	int i;
	cout << " Enter the phone number: "; 
	cin >> i;
	
	record person;
	ifstream inFile;
	inFile.open("record.dat", ios::binary);
	if (!inFile)
	{
		cout << "Error!";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag = false;
	while (inFile.read(reinterpret_cast<char *> (&person), sizeof(record)))
	{
		if (person.getPhone() == i)
		{
			cout << "**********************************\n";
            person.show();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false)
		cout << "No Record.";
	cin.ignore();
	cin.get();
}
 
void modifyRecord()
{
	int i;
	cout << "Enter the phone number: "; 
	cin >> i;
	
	bool found = false;
	record person;
	fstream File;
	File.open("record.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "Error!";
		cin.ignore();
		cin.get();
		return;
	}
	while (!File.eof() && found == false)
	{
 
		File.read(reinterpret_cast<char *> (&person), sizeof(record));
		if (person.getPhone() == i)
		{
			person.show();
			cout << "\n\n**********************************\n";
			cout << "Enter the Record.\n" << endl;
			person.get();
			int pos = (-1)*static_cast<int>(sizeof(person));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *> (&person), sizeof(record));
			cout << "\nModified.";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "No Record.";
	cin.ignore();
	cin.get();
}

void deleteRecord()
{
	int i;
	cout << "Enter the phone number: "; 
	cin >> i;
	
	record person;
	ifstream inFile;
	inFile.open("record.dat", ios::binary);
	if (!inFile)
	{
		cout << "Error!";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("file.dat", ios::out);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char *> (&person), sizeof(record)))
	{
		if (person.getPhone() != i)
		{
			outFile.write(reinterpret_cast<char *> (&person), sizeof(record));
		}
	}
	outFile.close();
	inFile.close();
	remove("record.dat");
	rename("file.dat", "record.dat");
	cout << "\nDeleted.";
	cin.ignore();
	cin.get();
}
 
