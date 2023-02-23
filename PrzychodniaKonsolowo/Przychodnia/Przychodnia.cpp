#include <stdlib.h>
#include <filesystem>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <cstdio>
#include <iterator>
#include <ranges>

import <iostream>;


import Doctor;
import Patient;
import Register;
import Menu;
import Person;
import Validator;
import MenuPat;
import MenuDoc;
import FileManager;
import Cifer;
import Event;
import Schedule;
import TimeManager;
import Coordinator;
namespace fs = std::filesystem;
int main()
{
  
   
    std::vector< std::shared_ptr<Doctor>> docs;
    std::vector< std::shared_ptr<Patient>> pats;
   
    FileManager::Start(docs,pats);
    Coordinator cord(docs, pats);
    cord.Start();
    
   

    bool exit = 0;
    while (!exit)
    {
        std::vector <std::string > pat_inputs_reg, pat_inputs_more_info, user_inputs_log;
        int registration = Register::Register_in(docs, pats, pat_inputs_reg);
        int get_info = 0, log_in = 0;
        int index_d = 0, index_p = 0;
        if (registration == 1)//positive registration
        {
            fs::path data("Data");
            if (Validator::Check_if_doc(docs, pat_inputs_reg[0])) // [0]-->pesel [1]-->login [2]-->password [3]-->doc/pat
            {
                pat_inputs_reg.push_back("doctor");
                Register::Add_login_password_doc(docs, pat_inputs_reg);

                std::string file = "loging_doc.txt";
                Register::Update_doc_logging_info(data, file, docs);

                std::cout << std::setw(70) << "~Please log in to your account" << std::endl;
                system("pause");
                system("CLS"); //cleans console
                log_in = 1;
            }
            else
            {
                pat_inputs_reg.push_back("patient");
                Register::Create_new_patient_shell(pats, pat_inputs_reg);
                std::string file = "users_pat.txt"; //filename of file  to be updated, 1:deleted 2:created 3:updated info saved into a file
                Register::Update_patient_shell_file(data, file, pats);
                get_info = 1;
            }
        }
        else if (registration == -1)//already has an account
        {
            system("CLS");
            std::cout << std::endl;
            if (Register::Ask_to_Log_in())
            {
                system("CLS");
                log_in = 1;
            }
            else
            {
                system("CLS");
                std::cout << std::endl;
                if (Register::Ask_to_Exit())
                {
                    exit = 1;
                }
            }
        }
        else //wants to log in
        {
            system("CLS"); //cleans console

            log_in = 1;
        }
        if (log_in) 
        {
          
            bool exists_in_database = 0, is_doc = 0,sucessful_log_in=0;
            while (sucessful_log_in == 0)
            {
                Register::Log_in(user_inputs_log); //[0] --> login [1]-->password
                index_p = Register::Get_pat_index(user_inputs_log[0], pats);
                if (index_p != -1)
                {
                    exists_in_database = 1;

                    if (pats[index_p]->Person::Check_password(user_inputs_log[1])) //1 if correct
                    {
                        sucessful_log_in = 1;
                        if (pats[index_p]->Get_all_info_status() == 0)
                        {
                            get_info = 1;
                        }
                        else
                        {
                            std::shared_ptr<MenuPatient> menu(new MenuPatient(pats[index_p], cord));
                            menu->Main();
                            if ((menu->Menu::Get_exit()) == 1)
                            {
                                exit = 1;
                            }
                            else if ((menu->Menu::Get_exit()) == -1)
                            {
                                system("CLS"); //cleans console
                            }
                        }
                    }
                    else
                    {
                        std::cout << std::setw(70) << "~Wrong password, please try again"<<std::endl;
                        system("pause");
                        system("CLS"); //cleans console
                    }
                }
                else
                {
                    index_d = Register::Get_doc_index(user_inputs_log[0], docs);
                    if (index_d != -1)
                    {
                        is_doc = 1;
                        exists_in_database = 1;
                        if (docs[index_d]->Person::Check_password(user_inputs_log[1])) //1 if correct
                        {
                            sucessful_log_in = 1;
                            std::shared_ptr<MenuDoctor> menu(new MenuDoctor(docs[index_d],cord));
                            menu->Main();
                            if ((menu->Menu::Get_exit()) == 1)
                            {
                                exit = 1;
                            }
                            else if ((menu->Menu::Get_exit()) == -1)
                            {
                                system("CLS"); //cleans console
                            }
                        }
                        else
                        {
                            std::cout << std::setw(50) << "wrong password, please try again";
                            system("pause");
                            system("CLS"); //cleans console
                            
                        }
                    }
                }
                if (exists_in_database == 0)
                {
                    std::cout << std::setw(50) << "~No user found" << std::endl;
                    //czy chce zamknąć czy jeszcze raz się zalogować
                    system("pause");
                    system("CLS"); //cleans console
                    break;
                }
            }
        }
        if (get_info == 1)
        {
            system("CLS"); //cleans console
            fs::path data("Data");
            std::string file = "users_pat_info.txt"; //filename of file  to be updated, 1:deleted 2:created 3:updated info saved into a file
            Menu::Get_full_info(pat_inputs_more_info);
            std::string login;
            if (log_in == 1) //z logowania
            {
                login = user_inputs_log[0];
            }
            else //z 
            {
                login = pat_inputs_reg[1]; // [0]-->pesel [1]-->login [2]-->password [3]-->doc/pat
            }
            Register::Update_patient_account(pats, login, pat_inputs_more_info);
            Register::Update_pat_info_file(data, file, pats);
            system("CLS"); //cleans console
            std::cout << std::setw(50) << "Now log into your account" << std::endl;
            system("pause");
            system("CLS"); //cleans console
            
        }
    }
    FileManager::Create_patients_folders(pats);
    FileManager::Save_appointment_request(pats);
    FileManager::Update_Schedules(docs);
}
