#include <vector>

export module Event;

import <iostream>;
import <iomanip>;
import <string>;
export class Event
{
	friend class Doctor;
	friend class Patient;
	friend class MenuPat;
	friend class MenuDoc;

	std::string hour = "";
	std::string date = "";
	int status = 1; // 1=issued 2=confirmed 3=compleated -1=cancelled 
	std::string specialization;
	std::string notes = "";
	std::string medication = "";
	std::string type = "No spec. type";
	int duration = 0; //in minutes
	std::string ending_hour = "";

protected:
	std::vector<std::string> doc_info = {}; //[0]->id [1]->name [2]->surname
	std::vector<std::string> pat_info = {}; //[0]->pesel [1]->name [2]->surname
public:
	Event()
	{
		this->specialization = "";
	}
	Event(std::vector<std::string> _doc_info, std::vector<std::string> _pat_info)
	{
		this->doc_info = _doc_info;
		this->pat_info = _pat_info;
	}
	//setters
	void Set_date(std::string _date)
	{
		date = _date;
	}

	void Set_hour(std::string _hour)
	{
		hour = _hour;
	}

	void Set_specialization(std::string _spec)
	{
		specialization = _spec;
	}

	void Set_notes(std::string _notes)
	{
		notes = _notes;
	}

	void Set_medication(std::string _meds)
	{
		medication = _meds;
	}

	void Set_doc_info(std::vector<std::string> _doc_info)
	{
		this->doc_info = _doc_info;
	}

	void Set_pat_info(std::vector<std::string> _pat_info)
	{
		this->pat_info = _pat_info;
	}

	void Set_type(std::string _type)
	{
		this->type = _type;
	}	

	void Set_duration(int minutes)
	{
		duration = minutes;
	}

	void Set_duration(std::string& minutes)
	{
		int d = std::stoi(minutes);
		duration = d;
	}

	void Set_ending_hour(std::string ending_h)
	{
		ending_hour = ending_h;
	}

	void Set_status(int _s)
	{
		this->status = _s;
	}

	//getters
	std::string Get_date()
	{
		return this->date;
	}

	std::string Get_time()
	{
		return this->hour;
	}

	std::string Get_type()
	{
		return this->type;
	}

	std::string Get_spec()
	{
		return this->specialization;
	}

	std::string Get_status_string()
	{
		return std::to_string(status);
	}

	int Get_status()
	{
		return status;
	}

	std::string Get_ending_hour()
	{
		return this->ending_hour;
	}

	std::string Get_pat_pesel()
	{
		return pat_info[0];
	}

	int Get_doc_id()
	{
		int id= std::stoi(doc_info[0]);
		return id;
	}

	std::vector<std::string> Get_doc_info()
	{
		return this->doc_info;
	}

	std::vector<std::string> Get_pat_info()
	{
		return this->pat_info;
	}

	int Get_duration()
	{
		return this->duration;
	}

	std::string Get_notes()
	{
		return this->notes;
	}

	std::string Get_mediction()
	{
		return this->medication;
	}

	std::string Get_month()
	{
		if (date.size() != 0)
		{ //dd.mm.yy
			std::string month = date.substr(3, 2);
			return month;
		}
		return "";
	}

	//
	std::string Show_status()
	{
		if (this->status == 1)
		{
			return "issued";
		}
		else if (this->status == 2)
		{
			return "confirmed";
		}
		else if (this->status == 3)
		{
			return "completed";
		}
		else if (this->status == -1)
		{
			return "cancelled";
		}
		else
		{
			return "unknown status";
		}
	}

	void Clear()
	{
		hour = "";
		date = "";
		int status = 1; //0=empty (for schedule) 1=issued 2=confirmed 3=compleated -1=cancelled -2=reschedule request 
		specialization = "";
		notes = "";
		medication = "";
		type = "";
	}

	void Display_Appointment()
	{
		std::cout << "APPOINTMENT DETAILS: " << this->specialization << " appointment" << std::endl;
		std::cout << "-DATE:" << this->date << "  TIME:" << this->hour<<"-"<<this->ending_hour << std::endl;
		std::cout << "\tPATIENT'S INFO:" << std::endl;
		std::cout <<  "\t-NAME:" << this->pat_info[1] <<" "<< this->pat_info[2] << std::endl;
		std::cout << "\t-PESEL:" << this->pat_info[0] << std::endl;
		std::cout <<  "DOCTORS'S INFO:" << this->doc_info[1] <<" "<< this->doc_info[2] << std::endl;
		std::cout <<  "\t-notes:" << this->notes << std::endl;
		std::cout <<"\t-medication:" << this->medication <<std::endl;
		std::cout << "\t-Appointment status: " << Show_status() << std::endl;
		std::cout <<"_______________________________________________"<< std::endl;
	}

	void Display_Event()
	{
		std::cout <<  "EVENT DETAILS: " << this->type<<std::endl;
		std::cout << "-DATE:" << this->date << "  TIME:" << this->hour << "-" << this->ending_hour << std::endl;
		std::cout << "\t-notes:" << this->notes << std::endl;
		std::cout << "________________________________________________" << std::endl;
	}

	void Display_Appointment_short()
	{
		std::cout << std::setw(20)<< "+(" << this->date << " at " << this->hour << ") " << this->specialization << " appointment "
			<< "(" << this->Show_status() << ")" << std::endl;
	}
	
	
	
};