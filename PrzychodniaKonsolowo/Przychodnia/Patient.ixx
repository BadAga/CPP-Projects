#include <vector>
export module Patient;

import Person;
import <iostream>;
import <iomanip>;
import <string>;
import Event;

export class Patient :public Person
{
	friend class Coordinator;
	friend class MenuDoctor;
	friend class MenuPatient;
	std::string  birthday= "No data"; 
	std::string  birth_city= "No data";
	char sex = 'N';
	bool all_info = 0;
protected:
	std::vector<Event> appointments = {};
public:
	using Person::Person;

	bool Get_all_info_status()
	{
		return this->all_info;
	}
	std::string Get_Birthday()
	{
		return this->birthday;
	}
	std::string Get_Birth_city()
	{
		return this->birth_city;
	}
	std::string Get_Sex()
	{
		std::string sex_to_string;
		sex_to_string.push_back(this->sex);
		return sex_to_string;
	}
	void Set_birthday(std::string input)
	{
		this->birthday = input;
	}
	void Set_birth_city(std::string input)
	{
		this->birth_city = input;
	}
	void Set_sex(std::string input)
	{
		this->sex = input[0];
	}
	void Set_all_info_status(bool input)
	{
		this->all_info = input;
	}

	std::string Get_dir_name()
	{
		std::string dir_name, _pesel;
		dir_name = this->Person::Get_Surname();
		_pesel = this->Person::Get_Pesel();
		dir_name += _pesel.substr(7, 4);
		return dir_name;
	}

	int Get_num_of_app()
	{
		return appointments.size();
	}

	std::vector<std::string> Get_info_for_event()
	{
		std::vector<std::string> vec;
		vec.push_back(this->pesel);
		vec.push_back(this->name);
		vec.push_back(this->surname);
		return vec;
	}

	void Add_event(Event &e)
	{
		appointments.push_back(e);
	}

	void Display_all_appointments_short()
	{
		for (auto& app : this->appointments)
		{
			if (app.Get_status() == 1 || app.Get_status() == 2)
			{
				app.Display_Appointment_short();
			}
		}
	}	

	std::vector<std::vector<std::vector<std::string>>> Get_event_req_details()
	{
		std::vector<std::vector<std::vector<std::string>>> allevents = {};
		for (auto& elem : appointments)
		{
			std::vector<std::string> info, info2, info3, info4, info5, info6, info7, info8, infoNotes, infoMediction;
			info.push_back(elem.Get_date());	
			info2.push_back(elem.Get_time());			
			info3=elem.Get_pat_info();			
			info4=elem.Get_doc_info();			
			info5.push_back(std::to_string(elem.Get_duration()));			
			info6.push_back(elem.Get_ending_hour());		
			info7.push_back(elem.Get_spec());			
			info8.push_back(elem.Get_status_string());
			infoMediction.push_back(elem.Get_mediction());
			infoNotes.push_back(elem.Get_notes());

			std::vector<std::vector<std::string>> all_info  {info,info2,info3,info4,info5,info6,info7,info8,infoMediction,infoNotes };
			allevents.push_back(all_info);
		}

		return allevents;
	}

	std::vector<int> Get_doc_idexs()
	{
		std::vector<int> indexes = {};
		for (auto& req : appointments)
		{
			if (req.Get_status()==1)
			{
				int id = req.Get_doc_id()-1;
				indexes.push_back(id);
			}
		}
		return indexes;
	}


};

