#include <vector>

export module Person;

import <iostream>;
import <iomanip>;
import <string>;
import Cifer;

export class Person
{
	friend class Doctor;
	friend class Patient;
protected:
	std::string name;
	std::string surname;
	std::string pesel; 
	std::string login;
	std::string password;
	std::vector <std::string> encrypted_password = {};
	int id = 0;

public:
	Person() :name("No data"), surname("No data"), pesel("No data"), login("No data"), password("No data") {}

	Person(std::string _login, std::string _password, std::string _pesel)
		:name("No data"), surname("No data"), pesel(_pesel), login(_login), password(_password) {}

	Person(std::string _login,  std::string _pesel)
		:name("No data"), surname("No data"), pesel(_pesel), login(_login), password("No data") {}

	inline Person(std::string _name, std::string _surname, std::string _pesel, std::string _login, std::string _password)
		: name(_name), surname(_surname), pesel(_pesel), login(_login), password(_password) {}

	std::string Get_Name()
	{
		return this->name;
	}
	std::string Get_Surname()
	{
		return this->surname;
	}
	std::string Get_Pesel()
	{
		return this->pesel;
	}
	std::string Get_Login()
	{
		return this->login;
	}
	std::string Get_Password()
	{
		return this->password;
	}
	int Get_id()
	{
		return this->id;
	}
	std::vector <std::string> Get_Encrypted_password()
	{
		return this->encrypted_password;
	}
	void Set_id(int _id)
	{
		this->id = _id;
	}
	void Set_Name(std::string _name)
	{
		this->name = _name;
	}
	void Set_Surname(std::string _surname)
	{
		this->surname = _surname;
	}
	void Set_Login(std::string _login)
	{
		this->login = _login;
	}
	void Set_Password(std::string _password)
	{
		this->password = _password;
	}

	void Set_Encrypted_password(std::vector <std::string> _encrypted)
	{
		this->encrypted_password = _encrypted;
	}
	
	void Decrypt_and_set_password()
	{
		this->Set_Password(Cifer::Decrypt_pesel(encrypted_password, id));
	}
	
	void Encrypt_and_set_encrypted_password()
	{
		this->Set_Encrypted_password(Cifer::Encrypt_pesel(this->password,this->id));
	}
	
	bool Check_password(std::string &pass)
	{
		if (pass == this->password)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	virtual std::vector<std::string> Get_info_for_event()
	{
		std::vector<std::string> info = {};
		return info;
	}
};


