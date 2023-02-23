export module MenuDoc;
import Menu;
import <iostream>;
import <iomanip>;
import <string>;

import Doctor;
import Coordinator;
import Validator;
import TimeManager;
import Event;
export class MenuDoctor :public Menu
{
	int stage = 0;
	std::shared_ptr<Doctor> doc;
	Coordinator cor;
public:

	MenuDoctor(std::shared_ptr<Doctor> _doc)
	{
		this->stage = 0;
		doc = _doc;
	}
	MenuDoctor(std::shared_ptr<Doctor> _doc,Coordinator& _cor)
	{
		this->stage = 0;
		doc = _doc;
		cor = _cor;
	}

	void Get_Main_Header()
	{
		std::cout << std::endl;
		std::cout << std::setw(45) <<"dr "<< doc->Person::Get_Name() << " " << doc->Person::Get_Surname() << std::endl;
	}

	void Main_agenda()
	{
		doc->schedule->Display_current_week();
		std::cout << std::endl;
		std::cout << std::setw(150) << "~To get more information about this week click 'W'";
		std::cout << std::endl;
		std::cout << std::setw(106) << "____________________________________________________________________________________________________________________________________________" << std::endl;
	}

	void Main_Show_diff_week()
	{
		std::cout << std::endl;
		std::cout << std::setw(150) << "~To display another week click 'D'";
		std::cout << std::endl;
		std::cout << std::setw(106) << "____________________________________________________________________________________________________________________________________________" << std::endl;
	}

	void Display_diff_week()
	{
		bool stop = 0;
		int counter = 1;
		int max_counter = doc->schedule->Get_num_of_weeks()-1;
		while (stop==0&&counter!= max_counter)
		{
			doc->schedule->Display_nth_week(counter);
			int answer = Ask_what_to_do_with_week();
			if (answer == 0)//display another week click 'D'
			{
				counter++;
			}
			else if (answer==1)//To see details of this week 
			{
				system("CLS"); //cleans console
				doc->schedule->Show_nth_week_in_details(counter);
				
				//after displaying goes back to main
				stop = 1;
			}
			else if (answer==2)//Go to main
			{
				stop = 1;
			}			
		}
	}

	int Ask_what_to_do_with_week()
	{
		std::cout << std::endl;
		std::cout << std::setw(150) << "~To display another week click 'D'" << std::endl;
		std::cout << std::setw(150) << "~To see details of this week click 'A'" << std::endl;
		std::cout << std::setw(150) << "~Go to main? Click 'M'" << std::endl;
		std::cout << std::setw(106) << "____________________________________________________________________________________________________________________________________________" << std::endl;
		int answer = Menu::Choose_option(std::vector<std::string>{"D", "A", "M"});
		return answer;

	}


	void Main_appointment_alert() //to do: more information
	{
		this->Appointment_alert();
		std::cout << std::setw(150) << "~To get more information about this click 'A'";
		std::cout << std::endl;
		std::cout << std::setw(106) << "____________________________________________________________________________________________________________________________________________" << std::endl;
	}

	void Main_schedule_event() //done
	{
		std::cout << std::endl;
		std::cout << std::setw(150) << "~To schedule an event click 'S'";
		std::cout << std::endl;
		std::cout << std::setw(106) << "____________________________________________________________________________________________________________________________________________" << std::endl;
	}

	void Main_add_appointment_description()
	{
		std::cout << std::endl;
		std::cout << std::setw(150) << "~To add appointment description (perscription/notes) click 'P'";
		std::cout << std::endl;
		std::cout << std::setw(106) << "____________________________________________________________________________________________________________________________________________" << std::endl;
	}

	void Main_log_out() //done
	{
		std::cout << std::setw(150) << "~To LOG OUT click 'X'";
		std::cout << std::endl;
		std::cout << std::setw(106) << "____________________________________________________________________________________________________________________________________________" << std::endl;
	}

	void Main_exit() //done
	{
		std::cout << std::setw(150) << "~To EXIT click 'E'";
		std::cout << std::endl;
		std::cout << std::setw(106) << "____________________________________________________________________________________________________________________________________________" << std::endl;
	}

	
	void Main()
	{
		system("CLS");
		this->Get_Main_Header();
		this->Main_agenda();
		this->Main_Show_diff_week();
		this->Main_add_appointment_description();
		this->Main_appointment_alert();
		this->Main_schedule_event();
		this->Main_log_out();
		this->Main_exit();
		int next = Menu::Choose_option(std::vector<std::string>{"W", "A", "S", "X", "E","D","P"});
		this->Display_next_menu_choice_in_main(next);
	}

	void Display_next_menu_choice_in_main(int& next)
	{
		if (next == 0) ///more info about week -->done
		{
			system("CLS"); //cleans console
			this->Increment_stage();
			doc->schedule->Show_nth_week_in_details(0);
			Go_back_to_main();
		}
		else if (next == 1) //appointment alert	-->done	
		{
			system("CLS"); //cleans console
			this->Increment_stage();
			Appointment_more_info();
			Go_back_to_main();
		}
		else if (next == 2) //schedule event -->done
		{
			system("CLS"); 
			this->Increment_stage();
			Schedule_Event();
		}
		else if (next == 3)//log out -->done
		{
			system("CLS"); //cleans console

			this->Menu::Set_exit(-1);
		}
		else if (next == 4)//exit -->done
		{
			system("CLS"); //cleans console
			this->Menu::Set_exit(1);
		}
		else if (next == 5)//display another week -->done
		{		
			system("CLS");
			this->Increment_stage();
			this->Display_diff_week();
			Go_back_to_main();
		}	
		else if (next == 6)//adding perscription/ notes
		{
			system("CLS");
			this->Increment_stage();
			this->Add_medication_notes_to_pat_app();
			Go_back_to_main();
		}
	}

	void Go_back_to_main()
	{
		system("pause");
		system("CLS"); //cleans console
		this->Decrement_stage();
		this->Main();
	}


	void Schedule_Event()
	{
		std::cout << std::endl;
		std::cout << std::setw(52) << "Scheduling event" << std::endl;
		std::cout << std::setw(83) << "---------------------------------------------------------------------" << std::endl;

		std::string chosen_date = Choosing_date();

		std::string chosen_time = Choose_time();

		int duration = Choose_Duration();

		std::cout << std::setw(83) << "---------------------------------------------------------------------" << std::endl;

		std::string type = Choose_event_type();

		std::string notes = Choose_notes();

		std::cout << std::setw(83) << "---------------------------------------------------------------------" << std::endl;

		Create_Event(chosen_date, chosen_time, type, notes, duration);
		std::cout << std::setw(52) << "~Event created successfully" << std::endl;

		Go_back_to_main();
	}

	std::string Choosing_date(bool accept_going_back=0)
	{
		std::cout << std::setw(64) << "Enter event's date: ";
		std::string input;
		bool good_input = 0;
		do
		{
			getline(std::cin, input);
			std::cout << std::endl;
			if (Validator::Valid_string(input))
			{
				if (Validator::Check_date_format(input))
				{
					if (accept_going_back == 0)
					{
						if (TimeManager::Check_if_date_is_not_past(input))
						{
							if (TimeManager::Check_if_date_is_no_farther_than_3_months_away(input))
							{
								good_input = 1;
							}
							else
							{
								std::cout << std::setw(72) << "~Wrong input. Date can't be farther than 3 months away. Try again: ";
							}
						}
						else
						{
							std::cout << std::setw(72) << "~Wrong input. We can't go back in time. Try again: ";
						}
					}
					else
					{
						if (TimeManager::Check_if_date_is_no_farther_than_3_months_away(input))
						{
							good_input = 1;
						}
						else
						{
							std::cout << std::setw(72) << "~Wrong input. Date can't be farther than 3 months away. Try again: ";
						}
					}
				}
				else
				{
					std::cout << std::setw(72) << "~Wrong input. Date must be in correct format: DD-MM-YY or DD.MM.YY. Try again: ";
				}
			}
			else
			{
				std::cout << std::setw(72) << "~Wrong input. Input can not be empty. Try again: ";
			}
		} while (good_input == 0);
		return input;
	}

	std::string Choose_time()
	{
		std::cout << std::setw(64) << "Enter event's time: ";
		std::string input;
		bool good_input = 0;
		do
		{
			getline(std::cin, input);
			std::cout << std::endl;
			if (Validator::Valid_string(input))
			{
				if (Validator::Check_time_format(input))
				{
					good_input = 1;
				}
				else
				{
					std::cout << std::setw(72) << "~Wrong input. Date must be in correct format:HH:MM. Try again: ";
				}
			}
			else
			{
				std::cout << std::setw(72) << "~Wrong input. Input can not be empty. Try again: ";
			}
		} while (good_input == 0);
		return input;
	}

	std::string Choose_event_type()
	{
		std::cout << std::setw(64) << "Enter event's type: ";
		
		std::string type;
		
			getline(std::cin, type);
			std::cout << std::endl;
		
		return type;
	}

	int Choose_Duration()
	{
		std::cout << std::setw(64) << "Enter event's duration (in minutes): ";
		std::string input;
		int duration;
		bool good_input = 0;
		do
		{
			getline(std::cin, input);
			std::cout << std::endl;
			if (Validator::Valid_number(input) && Validator::Valid_string(input))
			{
				duration = std::stoi(input);
				good_input = 1;
			}
			else
			{
				std::cout << std::setw(72) << "~Wrong input. Input must be a number.Try again: ";
			}
		} while (good_input == 0);

		return duration;
	}

	std::string Choose_notes()
	{
		std::cout << std::setw(64) << "Any notes? : ";

		std::string notes;

		getline(std::cin, notes);
		std::cout << std::endl;

		return notes;
	}

	std::string Choose_meds()
	{
		std::cout << std::setw(64) << "Medication : ";

		std::string meds;

		getline(std::cin, meds);
		std::cout << std::endl;

		return meds;
	}

	void Create_Event(std::string& date,std::string& time,std::string &type,std::string &notes,int & duration)
	{
		Event e;
		e.Set_date(date);
		e.Set_hour(time);
		e.Set_duration(duration);
		e.Set_ending_hour(TimeManager::Add_minutes_to_time(time, duration));
		e.Set_type(type);
		e.Set_notes(notes);
		Add_Event(e);
	}

	void Add_Event(Event&e)
	{
		doc->schedule->Add_event(e);
	}


	void Appointment_alert()
	{
		int number = doc->Get_number_of_requests();
		if (number == 0)
		{
			std::cout << std::endl;
			std::cout << std::setw(24) << "no appointment requests yet"  ;
			std::cout << std::endl;
		}
		else
		{
			std::cout << std::endl;
			std::cout << std::setw(24) << "APPOINTMENT ALERT! " << number<< " appointment request/s have been issued";
			std::cout << std::endl;
		}
	}

	void Appointment_more_info()
	{
		int number = doc->Get_number_of_requests();
		if (number == 0)
		{
			std::cout << std::endl;
			std::cout << std::setw(24) << "no appointment requests yet";
			std::cout << std::endl;
		}
		else
		{
			std::cout << std::endl;
			std::cout << std::setw(24) << "You have" << number << " appointment request/s"<<std::endl; 
			std::cout << std::endl;
			
			cor.Display_all_appointment_request_for_specific_doc(doc->Person::Get_id(),doc->appointment_request);
			std::cout << std::setw(24) << "\tChoose appointment request to change it's status: ";
			int chosen_request = Coordinator::Choose_number_from_range(number);	
			cor.Change_status(doc->Person::Get_id(), doc->appointment_request, chosen_request);
		}
	}

	
	void Add_medication_notes_to_pat_app()
	{
		std::cout << std::endl;
		std::cout << std::setw(52) << "Perscription and notes setter" << std::endl;
		std::cout << std::setw(83) << "---------------------------------------------------------------------" << std::endl;
		std::string chosen_date = Choosing_date(1);

		std::string chosen_time = Choose_time();
		std::string notes = Choose_notes();
		std::string meds = Choose_meds();

		cor.Add_description_to_appointment(doc->Get_id(), chosen_date, chosen_time, meds, notes);

	}
};