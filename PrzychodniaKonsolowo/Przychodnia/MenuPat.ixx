export module MenuPat;

import Menu;
import <iostream>;
import <iomanip>;
import <string>;

import Patient;
import Validator;
import Coordinator;
import TimeManager;
import Event;
export class MenuPatient :public Menu
{
	std::shared_ptr<Patient> pat;
	Coordinator cor;	
public:	
	MenuPatient(std::shared_ptr<Patient> _pat)
	{
		this->stage = 0;
		pat = _pat;
	}
	MenuPatient(std::shared_ptr<Patient> _pat,Coordinator& _cor)
	{
		this->stage = 0;
		pat = _pat;
		cor = _cor;
	}

	void Get_Main_Header()
	{
		std::cout << std::endl;
		std::cout << std::setw(45)<< pat->Person::Get_Name()<<" "<<pat->Person::Get_Surname() << std::endl;
		std::cout << std::setw(90) << "---------------------------------------------------------------------------" << std::endl;
	}

	void Main_event_remainder() 
	{
		std::cout << std::setw(30) << "Upcoming appointments:";
		std::cout << std::endl;
		pat->Display_all_appointments_short();
		std::cout << std::endl;
		std::cout << std::setw(82) << "~To get more information about appointments click 'Y'";
		std::cout << std::endl;
		std::cout << std::setw(89) << "---------------------------------------------------------------------------" << std::endl;
	}

	void Main_prescription_alert() //make i make sanse
	{
		std::cout << std::endl;
		int counter = 0;
		if (pat->appointments.size() != 0)
		{
			for (auto& app : pat->appointments)
			{
				if (app.Get_status() == 3 && app.Get_mediction().size() != 0)
				{
					counter++;
				}
			}		
		}
		if (counter != 0)
		{
			std::cout << std::setw(34) << "PRESCRIPTION ALERT! You have "<<counter<<" perscription/s available" << std::endl;
		}
		else
		{
			std::cout << std::setw(34) << "No perscription available" << std::endl;
		}
		std::cout << std::setw(82) << "~To get more information about this click 'P'" << std::endl;
		
		std::cout << std::setw(89) << "---------------------------------------------------------------------------" << std::endl;
	}

	void Main_book_appointment()
	{
		std::cout << std::setw(89) << "~To book doctor appointment click 'B'";
		std::cout << std::endl;
		std::cout << std::setw(89) << "---------------------------------------------------------------------------" << std::endl;
		
	}

	void Main_exit()
	{
		std::cout << std::setw(89) << "~To EXIT click 'E'";
		std::cout << std::endl;
		std::cout << std::setw(89) << "---------------------------------------------------------------------------" << std::endl;
	}

	void Get_medical_history()
	{
		std::cout << std::endl;
		std::cout << std::setw(89) << "~To get your medical history record click 'R'";
		std::cout << std::endl;
		std::cout << std::setw(89) << "---------------------------------------------------------------------------" << std::endl;
	}

	void Main_log_out()
	{
		std::cout << std::setw(89) << "~LOG out click 'X'";
		std::cout << std::endl;
		std::cout << std::setw(89) << "---------------------------------------------------------------------------" << std::endl;
	}

	void Main()
	{
		system("CLS");
		this->Get_Main_Header();
		this->Main_event_remainder();
		this->Main_prescription_alert();
		this->Main_book_appointment();
		this->Get_medical_history();
		this->Main_log_out();
		this->Main_exit();
		int next=Menu::Choose_option(std::vector<std::string>{"Y", "P", "B", "R", "X","E"});
		this->Display_next_menu_choice_in_main(next);
	}

	void Go_back_to_main()
	{
		system("pause");
		system("CLS"); //cleans console
		this->Decrement_stage();
		this->Main();
	}
	/*
	after user chooses option (from 1 to num of options see:Main()) adequete function is being called, after all possible options function Go_to_main() 
	is being called except in exit program option
	*/
	void Display_next_menu_choice_in_main(int& next)
	{

		if (next == 0)//------------------------->upcoming event
		{
			system("CLS"); //cleans console
			this->Increment_stage();
			Upcoming_Event_Patient();
			Go_back_to_main();
		}
		else if (next == 1)//--------------------->perscription alert
		{
			system("CLS"); //cleans console
			this->Increment_stage();
			this->Perscription_alert();
			Go_back_to_main();
		}
		else if (next == 2)//--------------------->booking appointment
		{
			system("CLS"); //cleans console
			this->Increment_stage();
			Booking_Appointment();
			Go_back_to_main();
		}
		else if (next == 3)//---------------------->medical record
		{
			system("CLS"); //cleans console
			this->Increment_stage();
			this->Display_Medical_Record();
			Go_back_to_main();
		}
		else if (next == 4)//////////////////////////////////--> log out
		{
			system("CLS"); //cleans console
			this->Menu::Set_exit(-1);

		}
		else if (next == 5)//////////////////////////////////--> exit
		{
			system("CLS"); //cleans console

			this->Menu::Set_exit(1);

		}
	}

	 std::string Choosing_speciality()
	{
		std::vector<std::string> specialities = Coordinator::Get_vec_of_specialities();
		for (int i = 0; i < specialities.size(); i++)
		{
			std::cout << std::setw(52) << i + 1 << ". " << specialities[i] << std::endl;
		}
		std::cout << std::endl;
		std::cout << std::setw(73) << "Choose speciality/ expertise by entering adequate number: ";
		std::string input,spec;
		bool good_input=0;
		do
		{
			getline(std::cin, input);
			std::cout << std::endl;
			if (Validator::Valid_number(input) && Validator::Valid_string(input))
			{
				if (std::stoi(input) >= 1 && std::stoi(input) <= 14)
				{
					good_input = 1;
				}
				else
				{
					std::cout << std::setw(72) << "~Wrong input. Input number must be between 1 and 14. Try again: "; 
				}
			}
			else
			{
				std::cout << std::setw(72) << "~Wrong input. Input must be a number.Try again: ";
			}
		} while (good_input == 0);
		spec = specialities[std::stoi(input) - 1];
		return spec;
	}
	 
	 std::string Choosing_date()
	{
		std::cout << std::setw(64) << "Enter appointment's date: ";
		std::string input;
		bool good_input = 0;
		do
		{
			getline(std::cin, input);
			std::cout << std::endl;
			if ( Validator::Valid_string(input))
			{
				if (Validator::Check_date_format(input))
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

	 int Choose_doctor(std::string &chosen_spec)
	 {
		std::vector<int> ids= cor.Find_all_doctors_id_of_given_speciality(chosen_spec);
		cor.Display_all_docs_of_given_id(ids);
		std::cout << std::endl << std::setw(72) << "Choose doctor by entering adequate number: " ;
		std::string input;
		int in=0;
		bool good_input = 0;
		do
		{
			getline(std::cin, input);			
			if (Validator::Valid_number(input) && Validator::Valid_string(input))
			{
				in = std::stoi(input);
				for (auto& id : ids)
				{
					if (in == id )
					{
						good_input = 1;
						break;
					}
				}
				if (good_input==0)
				{
					std::cout << std::endl;
					std::cout << std::setw(72) << "~Wrong input. Input must be a number one of the above. Try again: ";
				}
			}
			else
			{
				std::cout << std::endl;
				std::cout << std::setw(72) << "~Wrong input. Input must be a number. Try again: ";
			}
		} while (good_input == 0);
	
		return in;
	 }
	 
	 int Choose_appointment(int vec_size)
	 {
		 std::cout << std::endl << std::setw(72) << "Choose appointment time by entering adequate number: ";
		 std::string input;
		 int in = 0;
		 bool good_input = 0;
		 do
		 {
			 getline(std::cin, input);
			 if (Validator::Valid_number(input) && Validator::Valid_string(input))
			 {
				 in = std::stoi(input);
				 if (in > 0 && in <= vec_size)
				 {
					 good_input = 1;
				 }
				 else
				 {
					 std::cout << std::endl;
					 std::cout << std::setw(72) << "~Wrong input. Input must be a number one of the above. Try again: ";
				 }
			 }
			 else
			 {
				 std::cout << std::endl;
				 std::cout << std::setw(72) << "~Wrong input. Input must be a number. Try again: ";
			 }
		 } while (good_input == 0);

		 return in;
	 }

	 void Display_appointments(std::vector<std::string>& apps)
	 {
		 int counter = 1;
		 for (auto& ap : apps)
		 {
			 std::cout << std::setw(40) <<counter<<". "<< ap << "-" << TimeManager::Add_minutes_to_time(ap, 30) << std::endl;
			 counter++;
		 }
	 }

	 void Create_appointment(std::string date,std::string hour,int doc_index)
	 {
		 Event e;
		 e.Set_date(date);
		 e.Set_hour(hour);
		 e.Set_pat_info(pat->Get_info_for_event());
		 e.Set_doc_info(cor.Get_doc_info_for_appointment(doc_index));
		 e.Set_duration(30);
		 e.Set_ending_hour(TimeManager::Add_minutes_to_time(hour, 30));
		 e.Set_specialization(cor.Get_doc_spec(doc_index));		 
		 e.Set_type("Patient appoint.");
		 pat->Add_event(e);
		 cor.Add_request_to_doc(doc_index, e.Get_pat_pesel());
	 }

	 void Booking_Appointment()
	{
		std::cout << std::endl;
		std::cout << std::setw(52) << "BOOKING" << std::endl;
		std::cout << std::setw(83) << "---------------------------------------------------------------------" << std::endl;
		std::cout << std::endl;
		std::string chosen_spec = Choosing_speciality();

		std::cout << std::setw(83) << "---------------------------------------------------------------------" << std::endl;
		std::string chosen_date = Choosing_date(); 
		std::cout << std::setw(83) << "---------------------------------------------------------------------" << std::endl;
		
		int chosen_id=Choose_doctor(chosen_spec);
		
		int doc_index_in_database=chosen_id - 1;
		std::vector<std::string> av_app=cor.Get_available_appointments_in_date(doc_index_in_database, chosen_date);
		Display_appointments(av_app);
		std::cout << std::setw(83) << "---------------------------------------------------------------------" << std::endl;
		int chosen_app_time=Choose_appointment(av_app.size());
		Create_appointment(chosen_date, av_app[chosen_app_time - 1], doc_index_in_database);
		std::cout << std::setw(83) << "---------------------------------------------------------------------" << std::endl;
		std::cout << std::setw(72) << "Your doctor will confirm your booking in a few days" << std::endl;
	}

	 /*
	 displays only confirmed and issued appointments 
	 */
	 void Upcoming_Event_Patient()
	 {
		 if (pat->appointments.size() == 0)
		 {
			 std::cout << "no appointments" << std::endl;
		 }
		 for (auto& app : pat->appointments)
		 {
			 if (app.Get_status() == 1 || app.Get_status() == 2)
			 {
				 app.Display_Appointment();
			 }
		 }
	 }
	 /*
	 displays all appointments throught patients history
	 */
	 void Display_Medical_Record() 
	{
		 std::cout << "\tUpcoming appointments:: " << std::endl<< std::endl;
		 if (pat->appointments.size() == 0)
		 {
			 std::cout << "no appointments" << std::endl;
		 }
		 else
		 {
			 for (auto& app : pat->appointments)
			 {
				 if (app.Get_status() == 1 || app.Get_status() == 2)
				 {
					 app.Display_Appointment();
				 }
			 }
			 std::cout << std::endl << "~You'll find your medical history file in " << pat->Get_dir_name() << " directory" << std::endl;
		 }
	}

	 /*
	 displays all perscriptions in compleated appointments throught patients history
	 */
	 void Perscription_alert()
	 {
		 if (pat->appointments.size() != 0)
		 {
			 std::cout << std::setw(30) << "AVAILABLE PERSCRIPTIONS:" << std::endl;
			 std::cout << "_____________________________________________________________________" << std::endl;
			 for (auto& app : pat->appointments)
			 {
				 //status: 1 = issued 2 = confirmed 3 = compleated - 1 = cancelled
				 if (app.Get_status() == 3 && app.Get_mediction().size() != 0)
				 {					
					 std::cout << "Perscription: " << app.Get_mediction() << std::endl;
					 app.Display_Event();
				 }
			 }
		 }
		 else
		 {
			 std::cout << std::setw(52) << "~there are no perscriptions yet" << std::endl;
		 }
	 }
};