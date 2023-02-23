export module Doctor;

import Person;
import <iostream>;
import <iomanip>;
import <string>;

import Event;
import Schedule;

export class Doctor :public Person
{
	friend class MenuDoctor;
	friend class FileManager;
	friend class Coordinator;
	int workhours_weekly=0;
	std::vector<std::string> appointment_request = {}; //patients pesel
	std::string specialization="No data";
protected:
	std::shared_ptr<Schedule> schedule = nullptr;
public:
	using Person::Person;
	Doctor(std::string _pesel, std::string _name, std::string _surname, int _workhours_weekly, std::string _specialization)
	{
		this->name = _name;
		this->surname = _surname;
		this->pesel = _pesel;
		this->login = "No data";
		this->password = "No data";
		this->workhours_weekly = _workhours_weekly;
		this->specialization= _specialization;
	}
	
	void Set_Workhours(int _num)
	{
		this->workhours_weekly = _num;
	}

	void Set_Specialization(std::string spec)
	{
		this->specialization = spec;
	}

	int Get_Workhours()
	{
		return this->workhours_weekly;
	}

	std::string Get_Specialization()
	{
		return this->specialization;
	}

	std::string Get_dir_name()
	{
		std::string dir_name,_pesel;
		dir_name = this->Person::Get_Surname();
		_pesel= this->Person::Get_Pesel();
		dir_name += _pesel.substr(7, 4);
		dir_name += ".txt";
		return dir_name;
	}

	void Connect_schedule(std::shared_ptr<Schedule> _schedule)
	{
		schedule = _schedule;
	}

	void Display()
	{
		std::cout << std::setw(40)<<this->Person::Get_id() << ". dr "<< this->name << " " << this->surname <<  std::endl;
	}
	
	std::vector<std::string> Get_vec_with_doc_info_4_event()
	{
		std::vector<std::string> vec;
		vec.push_back(std::to_string(this->Person::Get_id()));
		vec.push_back(this->Person::Get_Name());
		vec.push_back(this->Person::Get_Surname());
		return vec;
	}
	
	std::vector<std::string> Get_info_for_event()
	{
		std::vector<std::string> vec;
		vec.push_back(std::to_string(this->id));
		vec.push_back(this->name);
		vec.push_back(this->surname);
		return vec;
	}

	bool Check_if_has_time_in_week(int& index_of_week)
	{
		if ( (this->Get_Workhours() * 60) <(schedule->Taken_minutes_in_week(index_of_week)))
		{
			return 0;
		}
		return 1;
	}

	void Add_app_request(std::string& pat_pesel)
	{
		appointment_request.push_back(pat_pesel);
	}

	int Get_number_of_requests()
	{
		return appointment_request.size();
	}

	std::vector<std::vector<std::vector<std::string>>> Get_schedule_details()
	{
		return schedule->Get_schedule_details();
	}
	
	
};
