#include <vector>
#include <filesystem>

export module Register;
import <iostream>;
import <iomanip>;
import <string>;

import Validator;
import Patient;
import Doctor;
import FileManager;


namespace fs = std::filesystem;
export class Register
{
public:
	static int Register_in(std::vector <std::shared_ptr<Doctor>>& docs, std::vector <std::shared_ptr<Patient>>& patients, std::vector <std::string>& pat_info_pac)
	{
		bool verify_pesel = 0, verify_login = 0, verify_password = 0;
		std::cout << std::endl;
		std::cout << std::setw(50) << "Register" << std::endl;
		std::cout << std::endl;

		if (Ask_to_Log_in())
		{
			return 0;
		}
		else
		{
			std::cout << std::endl;
			std::cout << std::setw(30) << "Enter your PESEL: ";
			bool good_pesel = 0;
			std::string input_pesel;

			do {
				getline(std::cin, input_pesel);
				std::cout << std::endl;
				if (Validator::Valid_string(input_pesel))
				{
					if (Validator::Valid_number(input_pesel))
					{
						if (Validator::Validate_Pesel_Registration(input_pesel))
						{
							good_pesel = 1;
						}
					}
				}
				if (!good_pesel)
				{
					std::cout << std::setw(50) << "~Please enter your PESEL in correct format:";
				}
			} while (good_pesel == 0);

			if (Validator::Check_if_entered_pat_pesel_exists(patients, input_pesel)|| Validator::Check_if_created_doctor_account_pesel(docs,input_pesel))
			{
				std::cout << std::setw(50) << "~You already have an account" << std::endl;
				return -1;
			}

			else
			{
				std::cout << std::setw(29) << "Enter your login:";
				bool good_login = 0;
				std::string input_login;

				do {
					getline(std::cin, input_login);
					std::cout << std::endl;
					if (Validator::Valid_string(input_login))
					{
						if (Validator::Check_if_unique_login(docs, patients, input_login))
						{
							good_login = 1;
						}
						else
						{
							std::cout << std::setw(70) << "~Sorry, this login is already taken, please enter different one: ";
						}
					}
					else
					{
						std::cout << std::setw(50) << "~Please enter your login in correct format:";
					}
				} while (good_login == 0);

				std::cout << std::setw(30) << "Enter your password:";
				bool good_password = 0;
				std::string input_password;

				do {
					getline(std::cin, input_password);
					std::cout << std::endl;
					if (Validator::Valid_string(input_password))
					{
						good_password = 1;
					}
					else
					{
						std::cout << std::setw(50) << "~Please enter your password in correct format:";
					}
				} while (good_password == 0);
				Save_user_input_registration(pat_info_pac, input_pesel, input_login, input_password);
				std::cout << std::setw(50) << "Registration completed" << std::endl;
				return 1;
			}
		}
	}

	static void Log_in(std::vector <std::string>& user_info_pac)
	{
		std::cout << std::endl;
		std::cout << std::setw(50) << "Log into Your Account" << std::endl;
		std::cout << std::endl;
		std::cout << std::setw(30) << "Enter your login:";
		
		bool good_login = 0;
		std::string input_login;

		do {
			getline(std::cin, input_login);
			std::cout << std::endl;
			if (Validator::Valid_string(input_login))
			{
				good_login = 1;
			}
			else
			{
				std::cout << std::setw(50) << "~Please enter your login in correct format:";
			}
		} while (good_login == 0);

		std::cout << std::endl;
		std::cout << std::endl;

		std::cout << std::setw(30) << "Enter your password:";
		
		bool good_password = 0;
		std::string input_password;

		do {
			getline(std::cin, input_password);
			std::cout << std::endl;
			if (Validator::Valid_string(input_password))
			{
				good_password = 1;
			}
			else
			{
				std::cout << std::setw(50) << "~Please enter your password in correct format:";
			}
		} while (good_password == 0);

		std::cout << std::endl;
		if (user_info_pac.size() == 0)
		{
			user_info_pac.push_back(input_login);
			user_info_pac.push_back(input_password);
		}
		else
		{
			user_info_pac.clear();
			user_info_pac.push_back(input_login);
			user_info_pac.push_back(input_password);
		}
	}

	static int Get_pat_index(std::string login, std::vector <std::shared_ptr<Patient>>& patients)
	{
		int counter = 0;
		for (auto& pat : patients)
		{
			if (login==pat->Person::Get_Login())
			{
				return counter;
			}
			counter++;
		}
		return -1;
	}
	static int Get_doc_index(std::string login, std::vector <std::shared_ptr<Doctor>>& docs)
	{
		int counter = 0;
		for (auto& doc : docs)
		{
			if (login == doc->Person::Get_Login())
			{
				return counter;
			}
			counter++;
		}
		return -1;
	}

	static bool Ask_to_Log_in()
	{
		std::cout << std::setw(70) << "Already have an account? Click 'L' to log in: " ;
		//
		std::string skip_registration_input;
		getline(std::cin, skip_registration_input);
		std::cout << std::endl;
		if (skip_registration_input == "L")
		{
			return 1;
		}
		else
		{
			return 0;
		}
		
	}

	static bool Ask_to_Exit()
	{
		std::cout << std::setw(70) << "Do you want to exit? Click 'E' to exit" << std::endl;
		
		std::string exit_input;
		getline(std::cin, exit_input);
		if (exit_input == "E")
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	static void Save_user_input_registration(std::vector <std::string > &pat_info_pac, std::string& user_pesel,
		std::string& user_login, std::string& user_password)
	{
		pat_info_pac.push_back(user_pesel);
		pat_info_pac.push_back(user_login)  ;
		pat_info_pac.push_back( user_password);
	}

	//funcion seves user input after positive registration (pesel, login, password) and adds to database of patients
	//patient has only pesel, login, password, other atributes has to add later -->Menu::Get_Info(...)
	static void Create_new_patient_shell(std::vector <std::shared_ptr<Patient>>& pats, std::vector <std::string >& pat_info_pac)
	{
		// [0]-->pesel [1]-->login [2]-->password [3]-->doc/pat
		std::shared_ptr<Patient> pat(new Patient(pat_info_pac[1], pat_info_pac[2], pat_info_pac[0]));
		pat->Person::Set_id(pats.size() + 1);
		pat->Person::Encrypt_and_set_encrypted_password();
		pats.push_back(pat);
	}

	static void Update_patient_shell_file(fs::path& data_dir, std::string filename, std::vector< std::shared_ptr<Patient>>& pats)
	{
		FileManager::Delete_file(data_dir, filename);
		FileManager::Create_new_file(data_dir, filename);
		FileManager::Write_patient_shells_into_file(data_dir, filename, pats);
		
	}

	static void Update_doc_logging_info(fs::path& data_dir, std::string filename, std::vector <std::shared_ptr<Doctor>>& docs)
	{
		FileManager::Delete_file(data_dir, filename);
		FileManager::Create_new_file(data_dir, filename);
		FileManager::Write_docs_logging_info(data_dir, filename, docs);
	}

	static void Update_pat_info_file(fs::path& data_dir, std::string filename, std::vector <std::shared_ptr<Patient>>& pats)
	{
		FileManager::Delete_file(data_dir, filename);
		FileManager::Create_new_file(data_dir, filename);
		FileManager::Write_pats_full_info(data_dir, filename, pats);
	}
	static void Add_login_password_doc(std::vector <std::shared_ptr<Doctor>>& docs, std::vector <std::string >& pat_info_pac)
	{
		// [0]-->pesel [1]-->login [2]-->password [3]-->doc/pat
		std::string user_pesel = pat_info_pac[0];
		for (auto& doc : docs)
		{
			if (doc->Person::Get_Pesel() == user_pesel)
			{
				doc->Person::Set_Login(pat_info_pac[1]);
				doc->Person::Set_Password(pat_info_pac[2]);
				doc->Person::Encrypt_and_set_encrypted_password();
			}
		}
	}

	static void Update_patient_account(std::vector <std::shared_ptr<Patient>>& pats,std::string login, std::vector <std::string >& pat_all_info_pac)
	{
		std::string pat_login = login;
		for (auto& pat : pats)
		{
			if (pat->Person::Get_Login() == pat_login)
			{
				if (pat_all_info_pac.size() == 5)
				{
					pat->Person::Set_Name(pat_all_info_pac[0]);
					pat->Person::Set_Surname(pat_all_info_pac[1]);
					pat->Set_birthday(pat_all_info_pac[2]);
					pat->Set_birth_city(pat_all_info_pac[3]);
					pat->Set_sex(pat_all_info_pac[4]);
					pat->Set_all_info_status(1);
				}
				else
				{
					std::cout << "Answers in get_all_info were not saved" << std::endl;
				}
				break;
			}
		}
	}
};