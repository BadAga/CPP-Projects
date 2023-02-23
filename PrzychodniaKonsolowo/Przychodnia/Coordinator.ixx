#include <vector>
//#include<iterator> 
export module Coordinator;

import <iostream>;
import <iomanip>;
import <string>;

import Patient;
import Doctor;
import TimeManager;
import Validator;
import FileManager;
export class Coordinator
{
	std::shared_ptr<std::vector< std::shared_ptr<Doctor>>> ptr_to_docs;

	std::shared_ptr<std::vector< std::shared_ptr<Patient>>> ptr_to_pats;

public:

	Coordinator()
	{
		ptr_to_docs = nullptr;
		ptr_to_pats = nullptr;
	}

	Coordinator(std::vector< std::shared_ptr<Doctor>>& docs, std::vector< std::shared_ptr<Patient>>& pats)
	{
		ptr_to_docs = make_shared< std::vector< std::shared_ptr<Doctor>> >(docs);
		ptr_to_pats = make_shared<  std::vector< std::shared_ptr<Patient>> >(pats);
	}
	
	void Start()
	{
		Notify_all_doctors_about_requests();
		Change_appointments_status_if_in_past();
	}

	static std::vector<std::string> Get_vec_of_specialities()
	{
		std::vector<std::string>  vec;
		vec.push_back("General Practicioner");
		vec.push_back("Dentist");
		vec.push_back("Dermatologist");
		vec.push_back("Gynecologist");
		vec.push_back("Ophthamologist");
		vec.push_back("General Surgeon");
		vec.push_back("Urologist");
		vec.push_back("Allergist");
		vec.push_back("Cardiologist");
		vec.push_back("Psychiarist");
		vec.push_back("Clinical Nutritionist");
		vec.push_back("Oncologist");
		vec.push_back("Pediatritian");
		vec.push_back("Physiotherapist");
		return vec;
	}

	std::vector<int> Find_all_doctors_id_of_given_speciality(std::string& speciality)
	{
		std::string spec=speciality;
		std::vector<int> right_docs = {};
		if (speciality == "General Practicioner")
		{
			spec = "GP";
		}
		else if (speciality == "Clinical Nutritionist")
		{
			spec = "CN";
		}
		else if (speciality == "General Surgeon")
		{
			spec = "GS";
		}
		for (auto& doc : *ptr_to_docs)
		{
			if (doc->Get_Specialization() == spec)
			{
				right_docs.push_back(doc->Person::Get_id());
			}
		}
		return right_docs;
	}

	void Display_all_docs_of_given_id(std::vector<int> &_ids)
	{
		for (auto& doc : *ptr_to_docs)
		{
			for (auto& id : _ids)
			{
				if (doc->Person::Get_id() == id)
				{
					doc->Display();
					break;
				}
			}
		}
	}

	std::vector<std::string> Get_available_appointments_in_date(int& doc_id,std::string& date)
	{
		std::vector<std::string> times = (*ptr_to_docs)[doc_id]->schedule->Get_vec_of_appointments(date);
		return times;
	}

	std::vector<std::string> Get_doc_info_for_appointment(int& index)
	{
		return (*ptr_to_docs)[index]->Get_info_for_event();
	}

	void Notify_all_doctors_about_requests()
	{
		for (auto& pat : *ptr_to_pats)
		{
			if (pat->Get_num_of_app() != 0)
			{
				std::string pat_pesel = pat->Person::Get_Pesel();
				std::vector<int> indexes_of_docs_to_notify = pat->Get_doc_idexs();
				for (auto& id : indexes_of_docs_to_notify)
				{
					Add_request_to_doc(id, pat_pesel);
				}
			}			
		}
	}

	void Add_request_to_doc(int& index,std::string pat_pesel)
	{
		(*ptr_to_docs)[index]->Add_app_request(pat_pesel);
	}

	std::string Get_doc_spec(int& index)
	{
		return (*ptr_to_docs)[index]->Get_Specialization();
	}

	void Display_all_appointment_request_for_specific_doc(int doc_id,std::vector<std::string> pat_pesels)
	{
		int counter = 0;
		for (std::string& pesel : pat_pesels)
		{
			for (auto& pat : *ptr_to_pats)
			{
				if (pat->Person::Get_Pesel() == pesel)
				{
					for (auto& req : pat->appointments)
					{
						if (req.Get_doc_id() == doc_id&&req.Get_status()==1)
						{
							counter++;
							std::cout << counter << ".";
							std::cout << req.Get_pat_info()[1] << " " << req.Get_pat_info()[2] << " requests appointment on "
								<< req.Get_date() << " at " << req.Get_time() << std::endl;
						}
					}
					break;
				}
			}

		}
	}

	void Change_status(int doc_id, std::vector<std::string> pat_pesels,int chosen_req)
	{
		int counter = 0;
		int counter_pesel_app_req = 0;
		for (std::string& pesel : pat_pesels)
		{
			for (auto& pat : *ptr_to_pats)
			{
				if (pat->Person::Get_Pesel() == pesel)
				{
					for (auto& req : pat->appointments)
					{
						if (req.Get_doc_id() == doc_id && req.Get_status() == 1)
						{
							counter++;
							if (counter == chosen_req)//confirmed
							{
								//ask what to do with req;
								int what_to_do=Do_smth_with_req();
								
								if (what_to_do == 1)
								{
									//if accepted change status
									req.Set_status(2);
									//if accepted remove pesel from appointments
									int index = doc_id - 1;
									(* ptr_to_docs)[index]->appointment_request.erase((*ptr_to_docs)[index]->appointment_request.begin() + counter_pesel_app_req);
									//if accepted add to schedule
									(* ptr_to_docs)[index]->schedule->Add_event(req);
								}
								else //denied
								{
									req.Set_status(-1);
								}
								std::cout << std::endl;
								std::cout << std::setw(40) << "Status have been changed successfully" << std::endl;
							}
						}
					}
					break;
				}
			}
			counter_pesel_app_req++;
		}
	}

	int  Do_smth_with_req()
	{
		std::cout << "\tChoose what to do with request by entering adequete number (1.Confirm 2.Decline) : " ;
		int what_to_do;
		return  what_to_do = Choose_number_from_range(3);
	}

	static int Choose_number_from_range(int max, int min = 1)
	{
		std::string input;
		int num;
		bool good_input = 0;
		do
		{
			getline(std::cin, input);
			std::cout << std::endl;
			if (Validator::Valid_number(input) && Validator::Valid_string(input))
			{
				num = std::stoi(input);
				if (num >= min && num <= max)
				{
					good_input = 1;
					return num;
				}
				else
				{
					std::cout << std::setw(72) << "~Wrong input. Input must be between " << min << "-" << max << ". Try again : ";
				}
			}
			else
			{
				std::cout << std::setw(72) << "~Wrong input. Input must be a number.Try again: ";
			}
		} while (good_input == 0);
	}

	void Add_description_to_appointment(int doctor_id,std::string date,std::string time, std::string perscription = "", std::string notes = "")
	{
		for (auto& doc : *ptr_to_docs)
		{
			if (doc->Get_id() == doctor_id)
			{
				std::string pat_pesel = doc->schedule->Add_description_to_appointment_at_time(date, time, doctor_id, perscription, notes);
				if (pat_pesel.size() != 0)
				{
					std::cout<< std::setw(30) << "Patient's appointment prescription/ notes set succesfully" << std::endl;
					this->Notify_pat_about_description_added(pat_pesel, doctor_id, date, time, perscription, notes );
				}
				break;
			}
		}
	}

	void Notify_pat_about_description_added(std::string pat_pesel, int& doc_id, std::string& date, std::string& time, std::string& perscription , std::string& notes )
	{
		for (auto& pat : *ptr_to_pats)
		{
			if (pat->Person::Get_Pesel() == pat_pesel)
			{
				for (auto& app : pat->appointments)
				{
					std::string ev_start = app.Get_time();
					std::string ev_end = app.Get_ending_hour();
					if ((TimeManager::Return_earlier_time(ev_start, time) == ev_start) && (TimeManager::Return_earlier_time(time, ev_end) == time)&&(doc_id==app.Get_doc_id()))
					{
						app.Set_notes(notes);
						app.Set_medication(perscription);

						break;
					}
				}				
			}
		}
	}

	void Change_appointments_status_if_in_past()
	{
		for (auto& pat : *ptr_to_pats)
		{
			for (auto& app : pat->appointments)
			{
				std::string app_date = app.Get_date();
				if (TimeManager::Return_earlier_date(app_date, TimeManager::Get_current_date()) == app_date)
				{
					if (app.Get_status() == 2)
					{
						app.Set_status(3);
					}
					else if (app.Get_status() == 1)
					{
						app.Set_status(-1);
					}					
				}
			}
		}
	}
};



