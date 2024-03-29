#include "pch.h"
#include "AnSensorFromConf.h"
#include "DirtWork.h"

CAnSensor CAnSensor::MakeSensor(std::string &line, BOOL &simple) {
	this->NumberWrite(IDFind(line));
	if (simple) this->ObjWrite(simpleMake(line), simpleMake(line));
	else
		this->ObjWrite(this->NameFind(line), this->TypeFind(line));
	return *this;
}

int CAnSensor::IDFind(std::string &line) {
	int NewID = 0, pos_1 = 0, pos_2 = 0;
	pos_1 = line.find_first_of("1234567890", 2);
	pos_2 = line.find_first_not_of("1234567890", pos_1);
	for (int i = pos_2 - 1; i > pos_1 - 1; i--) {
		NewID += MakeNumber(line[i])*pow(10, pos_2 - 1 - i);
	}
	return NewID;
}

std::string CAnSensor::simpleMake(std::string &line) {
	int pos_1, pos_2;
	pos_1 = line.find("//") + 3;
	std::string ex = line.substr(pos_1);
	pos_1 = line.find("(") + 1;
	pos_2 = line.find(")");
	if (line[pos_1] == '�') {
		Unit = '�';
		return ex;
	}
	else if (line[pos_1] == '�') {
		Unit = '�';
		return ex;
	}
	else if (line.substr(pos_1, pos_2 - pos_1) == "���.�") {
		Unit = "���.�";
		return ex;
	}
	else if (line.substr(pos_1, pos_2 - pos_1) == "���.�") {
		Unit = "���.�";
		return ex;
	}
	else if (line[pos_1] == '�') {
		Unit = '�';
		return ex;
	}
	else if (pos_1 == 0 || pos_1 == -1) {
		Unit = 'X';
		return ex;
	}
}

std::string CAnSensor::NameFind(std::string &line) {
	int pos_1, pos_2;
	pos_1 = line.find("//") + 3;
	pos_2 = line.find(". ", pos_1);
	if (pos_2 == -1) pos_2 = line.find_first_of(" ", pos_1);
	return line.substr(pos_1, pos_2 - pos_1);
}

std::string CAnSensor::TypeFind(std::string &line) {
	int pos_1, pos_2, pos_ex1, pos_ex2;
	pos_1 = line.find("(") + 1;
	pos_2 = line.find(")");
	std::string ex;
	pos_ex1 = line.find(". ", line.find("//") + 3);
	if (pos_1 == 0) ex = line.substr(pos_ex1);
	else ex = line.substr(pos_ex1+2, pos_1-2);
	if (line[pos_1] == '�') {
		Unit = '�';
		return "��� "+ex;
	}
	else if (line[pos_1] == '�') {
		Unit = '�';
		return "���������� "+ex;
	}
	else if (line.substr(pos_1,pos_2-pos_1) == "���.�") {
		Unit = "���.�";
		return "�������� �������� "+ex;
	}
	else if (line.substr(pos_1, pos_2 - pos_1) == "���.�") {
		Unit = "���.�";
		return "������ �������� "+ex;
	}
	else if (line[pos_1] == '�') {
		Unit = '�';
		return "����������� "+ex;
	}
	else if (pos_1 == 0  || pos_1 == 1) {
		Unit = 'X';
		if (line.find_last_of("R") != -1) {
			Unit = "���";
			return "������������� " + line.substr(line.find_last_of("R"));
		}
		else return line.substr(line.find_last_of("."));
	}
}
void CAnSensor::NumberWrite(int NewID) {
	ID = NewID;
	numOfSensor_1 = ID - 1;
}
void CAnSensor::ObjWrite(std::string &Name, std::string &Type) {
	Name_obj = Name;
	Type_obj = Type;
}

int CAnSensor::GetID() const {
	return this->ID;
}
int CAnSensor::GetNum_1() const {
	return this->numOfSensor_1;
}

std::string CAnSensor::GetName()const {
	return this->Name_obj;
}
std::string CAnSensor::GetType() const {
	return this->Type_obj;
}
CAnSensor::CAnSensor(int NewID) : Name_obj(" "), Type_obj(" "), Sourse(""), Unit("")  {
	ID = NewID;
	numOfSensor_1 = ID - 1;

}
CAnSensor::CAnSensor() : Name_obj(" "), Type_obj(" "), Sourse(""), Unit("") {
	ID = 0;
	numOfSensor_1 = 0;
}
std::string CAnSensor::GetUnit() const {
	return this->Unit;
}