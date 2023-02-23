#include <vector>
#include <utility>
export module Schedule;

import <iostream>;
import <iomanip>;
import <string>;

import Event;
import TimeManager;

export class Day
{
private:
	std::string date = "";
	std::vector<Event> events = {};
	
public:
	Day(std::string _date)
	{
		date = _date;
	}

	std::string Get_date()
	{
		return date;
	}

	void Display_hours_agenda(int index)
	{
		int now = events.size() - 1;
		if (now < index)
		{
			std::cout << "                   |";			               
		}				     
		else
		{
			std::cout  <<"    "<<  events[index].Get_time() << "-" << events[index].Get_ending_hour() << "    ";
			std::cout << "|";
		}

	}

	void Display_type_agenda(int index)
	{
		int now = events.size() - 1;
		if (now < index)
		{
			std::cout << "                   |";
		}
		else
		{
			std::cout << std::setw(19) << events[index].Get_type();
			std::cout << "|";
		}
	}

	void Display_date_agenda()
	{
		std::cout << "     " << Get_date() << "     | ";
	}

	void Add_event(Event& e)
	{
		if (events.size() == 0)
		{
			events.push_back(e);
		}
		else
		{
			bool inserted = 0;
			auto it = events.begin();
			for (Event& _event : events)
			{
				if ((TimeManager::Return_earlier_time(_event.Get_time(), e.Get_time())) == e.Get_time())
				{
					events.insert(it, e);
					inserted = 1;
					break;
				}				
				it++;
			}
			if (!inserted)
			{
				events.push_back(e);
			}
		}
	}

	int Get_num_of_events()
	{
		return events.size() ;
	}

	//returns how many minutes in day doctor is not free 
	int taken_minutes()
	{
		int m = 0;
		if (events.size() == 0)
		{
			return 0;
		}
		else
		{
			for (auto& _event : events)
			{
				m += _event.Get_duration();
			}
		}
		return m;
	}

	std::vector<std::string> available_pat_appointments_hour()
	{
		//pat. appointment can start at 8 and end at 18
		std::string time = "08:00";
		std::vector<std::string> available_times = {};
		if (events.size() == 0)
		{
			while (time != "18:00")
			{
				available_times.push_back(time);
				std::string time_added = TimeManager::Add_minutes_to_time(time, 30);
				time = time_added;
			}
		}
		else
		{
			std::vector< std::pair <std::string, bool>> schedule_in_quaters;
			while (time != "18:00")
			{
				bool availabilty = 1;
				for (auto& ev : events)
				{
					std::string start_ev = ev.Get_time();
					std::string stop_ev = ev.Get_ending_hour();
					std::string time_added = TimeManager::Add_minutes_to_time(time, 15);
					if (TimeManager::Return_earlier_time(time_added, start_ev) == time_added)
					{
						break;
					}
					else					
					{
						if (time_added == start_ev)
						{
							availabilty = 1;
						}
						else if (time == start_ev)
						{
							availabilty = 0;
						}
						else if ((TimeManager::Return_earlier_time(time, start_ev) == time) && (TimeManager::Return_earlier_time(time_added, start_ev) == time_added))
						{
							availabilty = 0;
						}
						else if ((TimeManager::Return_earlier_time(time, stop_ev) == time) && (TimeManager::Return_earlier_time(time_added, stop_ev) == time_added))
						{
							availabilty = 0;
						}
						else if (time == stop_ev)
						{
							availabilty = 1;
						}
						else if (time_added == stop_ev)
						{
							availabilty = 1;
						}
					}
				}
				std::pair <std::string, bool > quarter = std::make_pair(time, availabilty);
				schedule_in_quaters.push_back(quarter);
				std::string time_added = TimeManager::Add_minutes_to_time(time, 30);
				time = time_added;
			}
			for (int i = 0; i < schedule_in_quaters.size(); i++)
			{
				if (schedule_in_quaters[i].second)
				{
					if (i != schedule_in_quaters.size() - 1)
					{
						if (schedule_in_quaters[i + 1].second)
						{
							available_times.push_back(schedule_in_quaters[i].first);
						}
					}
				}
			}
		}
		return available_times;
	}

	void Get_day_event_details(std::vector<std::vector<std::vector<std::string>>>& storage)
	{
		for (auto& elem : events)
		{
			std::vector<std::string> info, info2, info3, infoNotes;
			info.push_back(elem.Get_date());
			info.push_back(elem.Get_time());

			info2.push_back(std::to_string(elem.Get_duration()));

			info3.push_back(elem.Get_type());
			std::vector<std::vector<std::string>> all_from_one_event;
			infoNotes.push_back(elem.Get_notes());
			if (elem.Get_type() != "Patient appoint.")
			{
				all_from_one_event = { info,info2,info3,infoNotes };
			}
			else
			{
				std::vector<std::string> info4, info5,infoMediction,infoStatus;
				info4.push_back(elem.Get_pat_pesel());
				info5.push_back(elem.Get_pat_info()[1]);
				info5.push_back(elem.Get_pat_info()[2]);
				infoMediction.push_back(elem.Get_mediction());
				infoStatus.push_back(elem.Get_status_string());
				all_from_one_event = { info,info2,info3,infoNotes,info4,info5,infoMediction,infoStatus };
			}
			storage.push_back(all_from_one_event);
		}
	}

	void Display_detailed_day()
	{
		if (events.size() == 0)
		{
			std::cout << std::setw(25) << "nothing today :)" << std::endl;
		}
		else
		{
			for (auto& _event : events)
			{
				if (_event.Get_type() == "Patient appoint.")
				{
					_event.Display_Appointment();
				}
				else
				{
					_event.Display_Event();
				}
			}
		}
	}

	std::string Add_description(std::string& perscription, std::string& notes, std::string& time)
	{
		for (auto& ev : events)
		{
			if (ev.Get_type() == "Patient appoint.")
			{
				std::string ev_start,ev_end;
				ev_start = ev.Get_time();
				ev_end = ev.Get_ending_hour();
				if ((TimeManager::Return_earlier_time(ev_start, time) == ev_start) && (TimeManager::Return_earlier_time(time, ev_end) == time))
				{
					ev.Set_notes(notes);
					ev.Set_medication(perscription);
					return ev.Get_pat_pesel();					
				}
			}
		}
		std::cout << std::setw(30) << "COM: You don't have any patient appointments at that time" << std::endl;
		return "";
	}
};

export class Schedule
{
protected:
	std::string current_date;
	int hours_weekly = 0;
	std::vector< std::vector<Day>> weeks;
public:
	Schedule()
	{
		current_date = TimeManager::Get_current_date();
	}

	Schedule(int& hours)
	{
		current_date = TimeManager::Get_current_date();
		hours_weekly = hours;
	}

	void Set_hours_weekly(int& hours)
	{
		hours_weekly = hours;
	}

	int Get_num_of_weeks()
	{
		return weeks.size();
	}

	void Create_prototype()
	{
		std::string ending_date = TimeManager::Add_3_months(current_date);
		std::string date_of_start_week = TimeManager::Get_first_day_of_current_week_date();
		bool last_week = 0;
		while (last_week==0)
		{
			std::vector<Day> week;
			for (int i = 0; i < 7; i++)
			{
				std::string date = TimeManager::Add_days_to_date(date_of_start_week, i);
				Day d (date);
				week.push_back(d);
				if (d.Get_date() == ending_date)
				{
					last_week = 1;
				}
			}
			this->weeks.push_back(week);
			date_of_start_week = TimeManager::Add_days_to_date(date_of_start_week, 7);
		}
	}

	void Update_curr_date()
	{
		current_date = TimeManager::Get_current_date();
	}

	void Display_week_header()
	{
		std::cout << std::setw(20) <<  std::left << "Weekly agenda:"<<std::endl;
		std::cout << std::setw(106) << "____________________________________________________________________________________________________________________________________________" << std::endl;
		std::cout << std::setw(106) << "|      MONDAY       |      TUESEDAY     |     WEDNESDAY     |      THURSDAY     |      FRIDAY       |      SATURDAY     |       SUNDAY      |" << std::endl;
		std::cout << std::setw(106) << "| ----------------  | ----------------  | ----------------  | ----------------  | ----------------  | ----------------  | ----------------  |" << std::endl;
	}

	int Get_max_num_of_events_in_week(int index)
	{
		int max = 0;
		for (auto& day : weeks[index])
		{
			if (day.Get_num_of_events() > max)
			{
				max = day.Get_num_of_events();
			}
		}
		return max;
	}

	void Display_current_week()
	{
		Display_nth_week(0);
	}

	std::string Get_weekday_names(int num)
	{
		if (num == 1)
		{
			return "MONDAY";
		}
		else if (num == 2)
		{
			return "TUESEDAY";
		}
		else if (num == 3)
		{
			return "WEDNESDAY";
		}
		else if (num == 4)
		{
			return "THURSDAY";
		}
		else if (num == 5)
		{
			return "FRIDAY";
		}
		else if (num == 6)
		{
			return "SATURDAY";
		}
		else if (num == 7)
		{
			return "SUNDAY";
		}
		
	}

	void Display_nth_week(int n)
	{
		system("CLS"); //cleans console
		Display_week_header();
		std::cout << "| ";
		for (auto& day : weeks[n])
		{
			day.Display_date_agenda();
		}
		std::cout << std::endl;
		std::cout << std::setw(106) << "| ----------------  | ----------------  | ----------------  | ----------------  | ----------------  | ----------------  | ----------------  |" << std::endl;

		int max = Get_max_num_of_events_in_week(n);
		for (int i = 0; i < max; i++)
		{
			std::cout << "|";
			for (auto& day : weeks[n])
			{
				day.Display_hours_agenda(i);
			}
			std::cout << std::endl;

			std::cout << "|";
			for (auto& day : weeks[n]) 
			{
				day.Display_type_agenda(i);
			}
			std::cout << std::endl;

			std::cout << std::setw(106) << "| ----------------  | ----------------  | ----------------  | ----------------  | ----------------  | ----------------  | ----------------  |" << std::endl;
		}
	}

	void Add_event(Event&e)
	{
		for (auto& week : weeks)
		{
			for (auto& day : week)
			{
				if (day.Get_date() == e.Get_date())
				{
					day.Add_event(e);
					break;
				}
			}
		}
	}

	void Show_nth_week_in_details(int n)
	{
		int counter = 1;
		for (auto& day : weeks[n])
		{                             
			std::cout <<"////////////////////////////////////////////////" <<  " --> " << day.Get_date()<< " ("<<Get_weekday_names(counter)<<")" << std::endl << std::endl;
			day.Display_detailed_day();
			counter++;
		}
	}
	
	//returns index of week where passed date is
	int Get_week_of_such_date(std::string _date)
	{		
		int counter = 0; 
		bool found = 0;
		for (auto& week : weeks)
		{
			for (auto& day : week)
			{
				if (day.Get_date() == _date)
				{
					return counter;
				}
			}
			counter++;
		}
		return counter;
	}

	int Taken_minutes_in_week(int& index_of_week)
	{
		int m = 0;
		for (auto& day : weeks[index_of_week])
		{
			m += day.taken_minutes();
		}
		return m;
	}

	std::vector<std::string> Get_vec_of_appointments(std::string& date)
	{
		std::vector<std::string> vec = {};
		int index_of_week = Get_week_of_such_date(date);
			for (auto& day : weeks[index_of_week])
			{
				if (day.Get_date() == date)
				{
					vec=day.available_pat_appointments_hour();
					return vec;
				}
			}		
			return vec;
	}

	std::vector<std::vector<std::vector<std::string>>> Get_schedule_details()
	{
		std::vector<std::vector<std::vector<std::string>>> allevents = {};
		for (auto& week : weeks)
		{
			for (auto& day : week)
			{
				day.Get_day_event_details(allevents);
			}
		}

		return allevents;
	}

	std::string Add_description_to_appointment_at_time(std::string& date, std::string& time,int& doc_id, std::string& perscription, std::string& notes )
	{
		for (auto& week : weeks)
		{
			for (auto& day : week)
			{
				if (day.Get_date() == date)
				{
					return day.Add_description(perscription, notes, time);
				}
			}
		}
		return "";
	}
};