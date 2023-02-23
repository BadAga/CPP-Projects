#include <vector>
#include <chrono>
//#include <ranges>
//#include <algorithm>
//#include <cstdio>
//#include <iterator>
export module Validator;

import <iostream>;
import <string>;
import <iomanip>;
import <regex>;


import Patient;
import Doctor;


export class Validator
{
public:
	static bool Validate_Pesel_Registration(std::string input)
	{
		if (input.size() != 11)  //sprawdzanie d³ugoœci
		{

			std::cout << std::setw(50) << "INVALID INPUT: Entered number is not a PESEL. PESEL has 11 digits" << std::endl;
			return 0;
		}

		if (Valid_number(input) == 0)
		{
			std::cout << std::setw(60) << "INVALID INPUT: PESEL can only have digits" << std::endl;
			return 0;
		}
		if (Pesel_control_num(input) != (input[10]-'0'))
		{
			std::cout << std::setw(50) << "INVALID INPUT: Incorecct PESEL" << std::endl;
			return 0;
		}
		return 1;

	}

	static bool Valid_number(std::string& str)
	{

		if (str.find_first_not_of("0123456789") == std::string::npos)
		{
			return 1;
		}

		std::cout << std::setw(50) << "INVALID INPUT: Not a number" << std::endl;
		return 0;


	}

	static bool Valid_string(std::string& str) //no spaces
	{
		if (str.size() == 0)
		{
			std::cout << std::setw(50) << "INVALID INPUT: No input" << std::endl;
			
			return 0;
		}
		if (str.find_first_of(' ') == std::string::npos)
		{
			return 1;
		}
		
		std::cout << std::setw(50) << "INVALID INPUT: No whitespaces" << std::endl;
		return 0;

	}

	static bool Check_string_with_only_letters(std::string& str)
	{
		std::string lowerd_str=str;
		for (int i=0; i<lowerd_str.size();i++)
		{
			lowerd_str[i] = tolower(lowerd_str[i]);
		}

		if (lowerd_str.find_first_not_of("qwertyuiopasdfghjklzxcvbnm") == std::string::npos)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	static bool Check_string_with_space(std::string& str)
	{
		if (str.size() == 0)
		{
			std::cout << std::setw(50) << "INVALID INPUT: No input" << std::endl;

			return 0;
		}
		std::string lowerd_str = str;
		for (int i = 0; i < lowerd_str.size(); i++)
		{
			lowerd_str[i] = tolower(lowerd_str[i]);
		}
		if (lowerd_str.find_first_not_of("qwertyuiopasdfghjklzxcvbnm -.") == std::string::npos) //cities can have dots and dashes
		{
			return 1;
		}

		std::cout << std::setw(50) << "INVALID INPUT: Only letters, dots and dashes are in valid input" << std::endl;
		return 0;
	}
	
	static bool Check_date_format(std::string& str)
	{
		if (str.size() != 8)
		{
			return 0;
		}
		else
		{
			//date format accepted: DD-MM-YY or DD.MM.YY
			std::regex date_format("(([0-2]{1}\\d{1})|(3{1}[0-1]{1}))(-|.)((0{1}\\d{1})|(1{1}[0-2]{1}))(-|.)\\d{2}");
			return Validator::Find_Matches(str, date_format);
		}
	}

	static bool Check_time_format(std::string& str)
	{
		
		if (str.size() != 5)
		{
			return 0;
		}
		else
		{
			//date format accepted: HH:MM
			std::regex time_format("(0[0-9]|1\\d|2[0-3]):[0-5]\\d");
			return Validator::Find_Matches(str, time_format);
		}
	}

	static bool Find_Matches(std::string text, std::regex reg)
	{
		std::sregex_iterator curr_match(text.begin(), text.end(), reg);
		std::sregex_iterator last_match;
		int counter = 0;
		while (curr_match != last_match)
		{
			std::smatch match = *curr_match;
			curr_match++;
			counter++;
		}
		if (counter == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}

	static int Pesel_control_num(std::string& input)
	{
		int importance[10] = { 1,3,7,9,1,3,7,9,1,3 };
		int control_sum = 0;
		for (int i = 0; i < (input.size() - 1); i++)
		{
			int digit = input[i] - '0';
			int control_ratio = digit * importance[i];
			control_sum += control_ratio;
		}
		int M = control_sum % 10;
		if (M == 0)
		{
			return 0;
		}
		int control_num = 10 - M;
		return control_num;
	}

	static bool Check_if_entered_pat_pesel_exists( std::vector<std::shared_ptr<Patient>>& database_pats, std::string & pesel)
	{
		for (auto& elem : database_pats)
		{
			if (elem->Person::Get_Pesel() == pesel)
			{
				return 1;
			}
		}
		return 0;
	}
	//checks if the entered pesel is 
	//1)in doctors database
	//2)if pesel is doctors than if such doctor is already registered (has set login and pesel) than resturns 1, otherwise 0
	static bool Check_if_created_doctor_account_pesel(std::vector <std::shared_ptr<Doctor>>& docs, std::string& pesel)
	{
		for (auto& elem : docs)
		{
			if (elem->Person::Get_Pesel() == pesel)
			{
				if (elem->Person::Get_Login()!= "No data" )
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}
		return 0;
	}
	
	static bool Check_if_doc(std::vector <std::shared_ptr<Doctor>>& docs, std::string& user_pesel)
	{
		for (auto& doc : docs)
		{
			if (doc->Person::Get_Pesel() == user_pesel)
			{
				return 1;
			}
		}
		return 0;
	}

	static bool Check_if_unique_login(std::vector <std::shared_ptr<Doctor>>& docs, std::vector<std::shared_ptr<Patient>>& pats, std::string& input_login)
	{
		for (auto& elem : docs)
		{			
			if (elem->Person::Get_Login() == input_login)
			{
				return 0;
			}
		}
		
		for (auto& elem : pats)
		{
			if (elem->Person::Get_Login() == input_login)
			{
				return 0;
			}
		}
		return 1;
	}	

};