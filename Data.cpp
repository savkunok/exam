#include <iostream>
#include <fstream>
#include <exception>
#include <vector>

class Data
{
public:
	void binWrite(std::string fileName, std::vector<Data>& airport);
	Data(int day, int month, int year) :
		_day(day), _month(month), _year(year){}

	friend std::ostream& operator<<(std::ostream& stream, Data& data)
	{
		stream <<  data._day << "." << data._month << "." << data._year << std::endl;
		return stream;
	}

	friend std::istream& operator>>(std::istream& stream, Data& data)
	{
		stream >> data._day >> data._month >> data._year;
		return stream;
	}

	void WriteToBin(std::ofstream& stream)
	{
		stream.write((char*)&_day, sizeof(_day));
		stream.write((char*)&_month, sizeof(_month));
		stream.write((char*)&_year, sizeof(_year));
	}

	void ReadFromBin(std::ifstream& stream)
	{
		stream.read((char*)&_day, sizeof(_day));
		stream.read((char*)&_month, sizeof(_month));
		stream.read((char*)&_year, sizeof(_year));
	}

	static int SearchSpringData(std::string fileName )
	{
		std::ifstream binFile(fileName, std::ios::binary);
		int count=0;
		Data tmp(0, 0, 0);
		for (int i = 0; i < 5; i++)
		{
			tmp.ReadFromBin(binFile);
			if ( tmp._month >2 && tmp._month <6 )
				count++;

		}
		binFile.close();
		return count;
	}

	void SetDay(int day)
	{
		this->_day = day;
	}

	void SetMonth(int month)
	{
		this->_month = month;
	}

	void SetYear(int year)
	{
		this->_year = year;
	}

private:
	int _day;
	int _month;
	int _year;
};



void binWrite(std::string fileName, std::vector<Data>& data);

void binRead(std::string fileName, std::vector<Data>& data);


int main()
{

    std::vector<Data> dati{
		Data(10,3,2022),
		Data(24,1,2023),
		Data(4,12,2022),
		Data(25,10,2023),
		Data(20,9,2022),
		Data(30,5,2022)
	};

			binWrite("binFile.bin", dati);
		
			binRead("binFile.bin", dati);
            int a=Data::SearchSpringData("binFile.bin");
			std::cout<< a <<std::endl;
	
}


void binWrite(std::string fileName, std::vector<Data>& data)
{
	std::cout << "Write to " << fileName + ':' << std::endl << std::endl;
	try
	{
		std::ofstream binFile(fileName, std::ios::binary);
		for (int i = 0; i < data.size(); i++)
		{
			data[i].WriteToBin(binFile);
		}
		binFile.close();
		for (int i = 0; i < data.size(); i++)
		{
			std::cout << data[i];
		}
		std::cout << std::endl << "------------------------------" << std::endl;
	}
	catch (std::exception& exception)
	{
		std::cout << exception.what();
	}
}

void binRead(std::string fileName, std::vector<Data>& data)
{
	std::cout << "Read from " << fileName + ':' << std::endl << std::endl;
	try
	{
		std::ifstream binFile(fileName, std::ios::binary);
		for (int i = 0; i < data.size(); i++)
		{
			data[i].ReadFromBin(binFile);
		}
		binFile.close();
		for (int i = 0; i < data.size(); i++)
		{
			std::cout << data[i];
		}
		std::cout << std::endl << "------------------------------" << std::endl;
	}
	catch (std::exception& exception)
	{
		std::cout << exception.what();
	}
}
