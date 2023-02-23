#include <vector>
export module Menu;

import <iostream>;
import <iomanip>;
import <string>;

import Validator;
import Doctor;
import Patient;

export class Menu
{
	friend class MenuPatient;
	friend class MenuDoctor;
protected:
	int stage = 0;
	int exit = 0; //1 if wants to exit program //-1 if wants to log out
	public:
	Menu() 
	{
		stage = 0;
	}
	Menu(int s) : stage(s) {};
	 void Increment_stage()
	{
		stage++;
	}
	 void Decrement_stage()
	 {
		 stage--;
	 }
	static void Get_full_info(std::vector <std::string>& pat_inputs_more_info) //to do: zrobic sprawdzania sensowne
	{
		std::cout << std::endl;
		std::cout << std::setw(85) << "In order to create an account successfully, enter answers to those questions" << std::endl;
		std::cout << std::endl;
		std::cout << std::setw(35) << "Name:";
		bool good_name = 0;
		std::string input_name;
		do {
			getline(std::cin, input_name);
			std::cout << std::endl;
			if (Validator::Valid_string(input_name)&& Validator::Check_string_with_only_letters(input_name))
			{
				good_name = 1;
			}
			else
			{
				std::cout << std::setw(50) << "~Please enter your name in correct format (only English letters):";
			}
		} while (good_name == 0);
		std::cout << std::endl;

		std::cout << std::setw(35) << "Surname:";

		bool good_surname = 0;
		std::string input_surname;
		do {
			getline(std::cin, input_surname);
			std::cout << std::endl;
			if (Validator::Valid_string(input_surname) && Validator::Check_string_with_only_letters(input_surname))
			{
				good_surname = 1;
			}
			else
			{
				std::cout << std::setw(50) << "~Please enter your surname in correct format (only English letters):";
			}
		} while (good_surname == 0);
		std::cout << std::endl;
		std::cout << std::setw(35) << "Date of birth:";
		bool good_date = 0;
		std::string input_date;
		do {
			getline(std::cin, input_date);
			std::cout << std::endl;
			if (Validator::Valid_string(input_date)&& Validator::Check_date_format(input_date))
			{
				good_date = 1;
			}
			else
			{
				std::cout << std::setw(50) << "~Please enter your date of birth in correct format (DD-MM-YY or DD.MM.YY) :";
			}
		} while (good_date == 0);
		std::cout << std::endl;

		std::cout << std::setw(35) << "City of birth:";
		
		bool good_city = 0;
		std::string input_city;
		do {
			getline(std::cin, input_city);
			std::cout << std::endl;
			if (Validator::Check_string_with_space(input_city))
			{
				good_city = 1;
			}
			else
			{
				std::cout << std::setw(50) << "~Please enter your city of birth in correct format:";
			}
		} while (good_city == 0);
		std::cout << std::endl;
		std::cout << std::setw(35) << "Sex ('F' for female 'M' for male):";
		bool good_gender = 0;
		std::string input_gender;
		do {
			getline(std::cin, input_gender);
			std::cout << std::endl;
			if (input_gender=="M"|| input_gender == "F")
			{
				good_gender = 1;
			}
			else
			{
				std::cout << std::setw(50) << "~Please enter your date of birth in correct format ('F' for female 'M' for male):";
			}
		} while (good_gender == 0);
		std::cout << std::endl;
		
		pat_inputs_more_info.push_back(input_name);
		pat_inputs_more_info.push_back(input_surname);
		pat_inputs_more_info.push_back(input_date);
		pat_inputs_more_info.push_back(input_city);
		pat_inputs_more_info.push_back(input_gender);

	}

	static int Choose_option(std::vector<std::string> options)
	{
		std::cout << std::setw(89)<<std::right << "~Choice:";
		std::string input;
		int index = 0;
		bool good_input = 0;
		do
		{
			getline(std::cin, input);
			if (input.size() == 1)
			{
				char big = toupper(input[0]);
				input[0] = big;
				for (auto& option : options)
				{
					if (option == input)
					{
						good_input = 1;
						break;
					}
					index++;
				}
				if (good_input == 0)
				{
					std::cout << std::endl;
					std::cout << std::setw(72) << "~Wrong input. Try again: ";
				}
			}
			else
			{
				std::cout << std::endl;
				std::cout << std::setw(72) << "~Wrong input. Try again: ";
			}
		} while (good_input == 0);
		
		return index;
	}

	int Get_exit()
	{
		return this->exit;
	}

	void Set_exit(int ex)
	{
		this->exit = ex;
	}

	virtual void Display_next_menu_choice_in_main(int& next) {}

	virtual std::string Choosing_date() { return ""; }
};