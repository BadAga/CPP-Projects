#include <vector>
#include <filesystem>
#include <fstream>
export module FileManager;

import <iostream>;
import <iomanip>;
import <string>;


import Validator;
import Patient;
import Doctor;
import Cifer;
import Schedule;
import TimeManager;

namespace fs = std::filesystem;
export class FileManager
{
public:
    static void Start(std::vector< std::shared_ptr<Doctor>>& docs, std::vector< std::shared_ptr<Patient>>& pats)
    {
        FileManager::Make_doctor_vec(docs);
        FileManager::Make_patients_vec(pats);
        FileManager::Fill_existing_patients_with_info(pats);
        FileManager::Fill_docs_with_logging_info(docs);
        FileManager::Read_Schedules(docs);
        FileManager::Read_app_req_all(pats);
    }

	static void Make_doctor_vec(std::vector< std::shared_ptr<Doctor>>& docs)
	{
		fs::path data_input("Data");
        if (fs::exists(data_input))
        {
            std::ofstream ofStream;
            std::ifstream ifStream;
            std::stringstream ss;
            std::string line;
            for (auto& file : fs::directory_iterator(data_input))
            {
                if (file.path().filename() == "pesel_doc.txt")
                {
                    int counter = 0;
                    ifStream.open(file);
                    while (std::getline(ifStream, line))
                    {
                        std::stringstream ss;
                        ss << line;
                        std::string name, surname, pesel, workhours, spec;
                        counter++;
                        while (ss >> name >> surname >> pesel >> workhours >> spec)
                        {
                            int h = std::stoi(workhours);
                            std::shared_ptr<Doctor> doc(new Doctor(pesel, name, surname, h, spec));
                            doc->Person::Set_id(counter);
                            docs.push_back(doc);
                            std::shared_ptr<Schedule> schedule(new Schedule(h));
                            schedule->Create_prototype();
                            doc->Connect_schedule(schedule);
                        }
                        ss.clear();
                    }
                    ifStream.clear();
                    ifStream.close();
                }
            }
        }
        else
        {
            std::cout << "!!!! Dir with doctors information does not exist !!!!" << std::endl;
        }
	} //updated to encrypted password
    //updated to encrypted password
    static void Fill_docs_with_logging_info(std::vector< std::shared_ptr<Doctor>>& docs) 
    {
        fs::path data_input("Data");
        if (fs::exists(data_input))
        {
            std::ofstream ofStream;
            std::ifstream ifStream;
            std::stringstream ss;
            std::string line;
            for (auto& file : fs::directory_iterator(data_input))
            {
                if (file.path().filename() == "loging_doc.txt")
                {
                    ifStream.open(file);
                  
                    while (std::getline(ifStream, line))
                    {
                        std::stringstream ss;
                        ss << line;
                         //std::string pesel, login, password;
                        std::string pesel, login, password, digits;
                        
                        while (ss >> pesel >> login >> password>> digits)
                        {
                            for (auto& doc : docs)
                            {
                                if (doc->Person::Get_Pesel() == pesel)
                                {
                                    doc->Person::Set_Login(login);
                                    //doc->Person::Set_Password(password);
                                    std::vector<std::string> encrypted_vec = Cifer::Make_encrypted_vec(password, digits);
                                    doc->Person::Set_Encrypted_password(encrypted_vec);
                                    doc->Person::Decrypt_and_set_password();
                                }
                            }
                        }
                        ss.clear();
                    }
                    ifStream.clear();
                    ifStream.close();
                }
            }
        }
    }  //updated to encrypted password
    //updated to encrypted password
    static void Make_patients_vec(std::vector< std::shared_ptr<Patient>>& pats) 
    {
        fs::path data_input("Data");
        if (fs::exists(data_input))
        {
            std::ofstream ofStream;
            std::ifstream ifStream;
            std::stringstream ss;
            std::string line;
            for (auto& file : fs::directory_iterator(data_input))
            {
                if (file.path().filename() == "users_pat.txt")
                {
                    int counter = 0;
                    ifStream.open(file);

                    while (std::getline(ifStream, line))
                    {
                        std::stringstream ss;
                        ss << line;
                        //std::string pesel, login, password;
                        std::string pesel, login, password, digits;

                        while (ss >> pesel >> login >> password >> digits)
                        {
                            counter++;
                            std::shared_ptr<Patient> pat(new Patient(login, pesel));
                            pat->Person::Set_id(counter);
                            std::vector<std::string> encrypted_vec = Cifer::Make_encrypted_vec(password, digits);
                            pat->Person::Set_Encrypted_password(encrypted_vec);
                            pat->Person::Decrypt_and_set_password();

                            pats.push_back(pat);

                        }
                        ss.clear();
                    }
                    ifStream.clear();
                    ifStream.close();
                }
            }
        }
        else
        {
            std::cout << "!!!! Dir with patients account information does not exist !!!!" << std::endl;
        }
    } //updated to encrypted password
    ////updated to encrypted password
    static void Fill_existing_patients_with_info(std::vector< std::shared_ptr<Patient>>& pats)
    {
        fs::path data_input("Data");
        if (fs::exists(data_input))
        {
            std::ofstream ofStream;
            std::ifstream ifStream;
            std::stringstream ss;
            std::string line;
            for (auto& file : fs::directory_iterator(data_input))
            {
                if (file.path().filename() == "users_pat_info.txt")
                {
                    ifStream.open(file);
                    while (std::getline(ifStream, line))
                    {
                        std::stringstream ss;
                        ss << line;
                        std::string pesel, name, surname, bday_date, b_city, sex;

                        while (ss >> pesel >> name >> surname >> bday_date >> b_city >> sex)
                        {
                            for (auto& elem : pats)
                            {
                                if (elem->Person::Get_Pesel() == pesel)
                                {
                                    elem->Person::Set_Name(name);
                                    elem->Person::Set_Surname(surname);
                                    elem->Set_birthday(bday_date);
                                    elem->Set_birth_city(b_city);
                                    elem->Set_sex(sex);
                                    elem->Set_all_info_status(1);
                                }
                            }
                        }
                        ss.clear();
                    }
                    ifStream.clear();
                    ifStream.close();
                }
            }
        }
    }

    static void Delete_file(fs::path& data_dir, std::string file_to_delete)
    {
        for (auto f : fs::directory_iterator(data_dir))
        {
            std::string file_name = f.path().filename().string();
            if (file_name == file_to_delete)
            {
                fs::remove(f.path());
            }
        }
    }

    static void Create_new_file(fs::path& data_dir, std::string filename)
    {
        std::ofstream file;
        std::string where_to_create = data_dir.string();
        where_to_create += "\\" + filename;
        file.open(where_to_create);
    }

    static void Create_new_file(std::string data_dir, std::string filename)
    {
        std::ofstream file;
        data_dir += "\\" + filename;
        file.open(data_dir);
    }

    static void Write_patient_shells_into_file(fs::path& data_dir, std::string filename, std::vector< std::shared_ptr<Patient>>& pats)
    {
        std::ofstream target;
        target.open(data_dir.string() + "\\" + filename);
        for (auto& elem : pats)
        {
            target << elem->Person::Get_Pesel() << "         ";
            target << elem->Person::Get_Login() << "         ";
            //target << elem->Person::Get_Password() << "      ";
            std::string encrypted_pass, digits;
            digits = Cifer::Get_number_of_digits_in_number(elem->Person::Get_Encrypted_password());
            encrypted_pass = Cifer::Make_string_from_vec(elem->Person::Get_Encrypted_password());
            target << encrypted_pass << "    ";
            target << digits;
            target << std::endl;
            
        }

        target.close();
    }

    static void Write_docs_logging_info(fs::path& data_dir, std::string filename, std::vector <std::shared_ptr<Doctor>>& docs)
    {
        std::ofstream target;
        target.open(data_dir.string() + "\\" + filename);
        for (auto& elem : docs)
        {
            target << elem->Person::Get_Pesel() << "     ";
            if (elem->Person::Get_Login() != "No data")
            {
                target << elem->Person::Get_Login() << "     ";
                std::string encrypted_pass, digits;
                digits = Cifer::Get_number_of_digits_in_number(elem->Person::Get_Encrypted_password());
                encrypted_pass = Cifer::Make_string_from_vec(elem->Person::Get_Encrypted_password());
                target << encrypted_pass << "    ";
                target << digits;
                target << std::endl;
            }
            else
            target << std::endl;
        }

        target.close();
    }

    static void Write_pats_full_info(fs::path& data_dir, std::string filename, std::vector< std::shared_ptr<Patient>>& pats)
    {
        std::ofstream target;
        target.open(data_dir.string() + "\\" + filename);
        for (auto& elem : pats)
        {
            if (elem->Get_all_info_status() == 1)
            {
                target << elem->Person::Get_Pesel() << "     ";
                target << elem->Person::Get_Name() << "     ";
                target << elem->Person::Get_Surname() << "     ";
                target << elem->Get_Birthday() << "     ";
                target << elem->Get_Birth_city() << "     ";
                target << elem->Get_Sex() << "     ";
                target << std::endl;
            }
        }
        target.close();
    }

   
    static void Create_patients_folders(std::vector< std::shared_ptr<Patient>>& pats)
    {        
        for (auto& pat : pats)
        {
            Create_dir_for_pat(pat->Get_dir_name());
        }
    }

    static void Create_dir_for_pat(std::string dir_name)
    {
        std::string path = "Patients";
        path += ("/" + dir_name);
        
        if (fs::exists(path))
        {
        }
        else
        {
            fs::create_directories(path);
            Create_new_file(path, "Appointments.txt");
        }

    }

   
    static void Save_appointment_request( std::vector< std::shared_ptr<Patient>>& pats)
    {
        for (auto& pat : pats)
        {
            std::vector<std::vector<std::vector<std::string>>> info = pat->Get_event_req_details();
            Update_appointment_request(pat->Get_dir_name(),info);
        }
       
    }

    static void Update_appointment_request(std::string dir_name, std::vector<std::vector<std::vector<std::string>>>&info)
    {
        std::string path = "Patients";
        path += ("/" + dir_name); //try with "\\"
        fs::path where_path(path);
        Delete_file(where_path, "Appointments.txt");
        Create_new_file(where_path, "Appointments.txt");
        Write_into_file_appointment_details(path, info);
    }

    static void Write_into_file_appointment_details(std::string path,std::vector<std::vector<std::vector<std::string>>>& info)
    {
        std::ofstream target;
        target.open(path + "\\" + "Appointments.txt");
        for (auto& app : info)
        {
            for (auto& info : app)
            {
                for (auto& data : info)
                {
                    target << data << " ";
                }
                target << std::endl;
            }
            target << "---";
            target << std::endl;
        }
        target.close();
    }

   
    static void Read_app_req_all(std::vector< std::shared_ptr<Patient>>& pats)
    {
        for (auto& pat : pats)
        {
            std::string name = pat->Get_dir_name();
            std::vector<Event> vec= Read_app_req_each(name);
            for (Event& ev : vec)
            {
                pat->Add_event(ev);
            }
        }
    }

    static std::vector<Event>  Read_app_req_each(std::string& dir_name)
    {
       std::vector<Event> vec;
       std::string path = "Patients";
        path += ("/" + dir_name); 
        fs::path data_input(path);
        if (fs::exists(data_input))
        {
            std::ofstream ofStream;
            std::ifstream ifStream;
            std::stringstream ss;
            std::string line;
            
            std::string f_name = "Appointments.txt";
            for (auto& file : fs::directory_iterator(data_input))
            {
                if (file.path().filename() == f_name)
                {
                    ifStream.open(file);
                    Event e;                   
                    int counter = 0;
                    std::vector<std::string> pat_info;
                    std::vector<std::string> doc_info;
                    while (std::getline(ifStream, line))
                    {
                        std::stringstream ss;
                        ss << line;
                        e.Set_type("Patient appoint.");
                        if (line!="---")
                        {
                            counter++;
                            if (counter == 1) //date
                            {
                                std::string data, date;
                                while (ss >> data)
                                {
                                    date += data + " ";
                                }
                                date.pop_back();
                                e.Set_date(date);
                            }
                            else if (counter == 2)//time
                            {
                                std::string data, hour;
                                while (ss >> data)
                                {
                                    hour += data + " ";
                                }
                                hour.pop_back();
                                e.Set_hour(hour);

                            }
                            else if (counter == 3)//pat info
                            {
                                std::string pesel, name, surname;
                                while (ss >> pesel>> name>> surname)
                                {
                                    pat_info.push_back(pesel);
                                    pat_info.push_back(name);
                                    pat_info.push_back(surname);
                                    e.Set_pat_info(pat_info);
                                }
                            }
                            else if (counter == 4) //doc info
                            {
                                std::string id, name, surname;
                                while (ss >> id >> name >> surname)
                                {
                                    doc_info.push_back(id);
                                    doc_info.push_back(name);
                                    doc_info.push_back(surname);
                                    e.Set_doc_info(doc_info);
                                }
                            }
                            else if (counter == 5) //duration
                            {
                                e.Set_duration(line);
                            }
                            else if (counter == 6) //ending hour
                            {
                                std::string data, hour;
                                while (ss >> data)
                                {
                                    hour += data + " ";
                                }
                                hour.pop_back();
                                e.Set_ending_hour(hour);

                            }
                            else if (counter == 7) //spec
                            {
                                std::string data, spec;
                                while (ss >> data)
                                {
                                    spec += data + " ";
                                }
                                spec.pop_back();
                                e.Set_specialization(spec);

                            }
                            else if (counter == 8) //status
                            {
                                int status = std::stoi(line);
                                e.Set_status(status);                                  
                            }
                            else if (counter == 9) //meds
                            {
                                std::string data, medication="";
                                while (ss >> data)
                                {
                                    medication += (data + " ");
                                }
                                if (medication.size() != 0)
                                {
                                    medication.pop_back();
                                }                                
                                e.Set_medication(medication);

                            }
                            else if (counter == 10) //notes
                            {
                                std::string data, notes="";
                                while (ss >> data)
                                {
                                    notes += (data + " ");                                    
                                }    
                                if (notes.size() != 0)
                                {
                                    notes.pop_back();
                                }
                                e.Set_notes(notes);
                              
                            }
                        }
                        else
                        {
                        vec.push_back(e);
                        pat_info.clear();
                        doc_info.clear();
                        e.Clear();
                        counter = 0;
                        }
                      
                        ss.clear();
                    }
                    ifStream.clear();
                    ifStream.close();
                }
            }
        }
        else
        {
           
        }
        return vec;
    }

    
    static void Read_Schedules(std::vector< std::shared_ptr<Doctor>>& docs)
    {
        fs::path data_input("Schedules");
        if (fs::exists(data_input))
        {
            std::ofstream ofStream;
            std::ifstream ifStream;
            std::stringstream ss;
            std::string line;
            for (auto& doc : docs)
            {
                std::string f_name = doc->Get_dir_name();
                //std::cout << f_name << std::endl;
                for (auto& file : fs::directory_iterator(data_input))
                {

                    if (file.path().filename() == f_name)
                    {

                        ifStream.open(file);
                        Event e;
                        int counter = 0;
                        std::vector<std::string> pat_info;
                        while (std::getline(ifStream, line))
                        {
                            std::stringstream ss;
                            ss << line;
                            std::string date, time, type, pat_pesel, pat_name, pat_surname;
                            if (line != "---")
                            {
                                counter++;
                                if (counter == 1) //date and time
                                {
                                    while (ss >> date >> time)
                                    {
                                        e.Set_date(date);
                                        e.Set_hour(time);
                                    }
                                }
                                else if (counter == 2) //duration
                                {
                                    int duration = std::stoi(line);
                                    e.Set_duration(duration);
                                    std::string starting_h = e.Get_time();
                                    //also setting ending hour
                                    std::string ending_h = TimeManager::Add_minutes_to_time(starting_h, duration);
                                    e.Set_ending_hour(ending_h);

                                }
                                else if (counter == 3) //type
                                {
                                    std::string data, type;
                                    while (ss >> data)
                                    {
                                        type += data + " ";
                                    }
                                    type.pop_back();
                                    e.Set_type(type);

                                }
                                else if (counter == 4) //notes
                                {
                                    std::string data, notes;
                                    while (ss >> data)
                                    {
                                        notes+=( data + " ");                                    
                                    }
                                    if (notes.size() != 0)
                                    {
                                        notes.pop_back();
                                    }
                                    e.Set_notes(notes);
                                }
                                else if (counter == 5)//pat info (pesel)
                                {
                                    while (ss >> pat_pesel)
                                    {
                                        pat_info.push_back(pat_pesel);
                                    }
                                }
                                else if (counter == 6)//pat info (name,surname)
                                {
                                    while (ss >> pat_name >> pat_surname)
                                    {
                                        pat_info.push_back(pat_name);
                                        pat_info.push_back(pat_surname);
                                    }
                                }
                               
                                else if (counter == 7) //mediction
                                {
                                    std::string data, medication="";
                                    while (ss >> data)
                                    {
                                        medication += (data + " ");
                                    }
                                    if (medication.size() != 0)
                                    {
                                        medication.pop_back();
                                    }
                                    e.Set_medication(medication);
                                }
                                else if (counter == 8) //status
                                {
                                    int status = std::stoi(line);
                                    e.Set_status(status);
                                }

                                if (e.Get_type() == "Patient appoint.")
                                {
                                    e.Set_pat_info(pat_info);
                                }
                            }
                            else
                            {
                                counter = 0;
                                e.Set_doc_info(doc->Get_vec_with_doc_info_4_event());
                                doc->schedule->Add_event(e);

                                pat_info.clear();
                                e.Clear();
                            }
                            ss.clear();
                        }
                        ifStream.clear();
                        ifStream.close();
                    }
                }
            }

        }
        else
        {
            std::cout << "!!!! Dir with doctors information does not exist !!!!" << std::endl;
        }
    }

    static void Update_Schedules(std::vector< std::shared_ptr<Doctor>>& docs)
    {
        for (auto& doc : docs)
        {
            Update_single_schedule(doc->Get_dir_name(), doc->Get_schedule_details());
        }
    }

    static void Update_single_schedule(std::string schedule_name, std::vector<std::vector<std::vector<std::string>>> info)
    {
        std::string path = "Schedules";
        fs::path where_path(path);
        Delete_file(where_path, schedule_name);
        Create_new_file(where_path, schedule_name);
        Write_Schedule(path,schedule_name, info);
    }

    static void Write_Schedule(std::string &path, std::string schedule_name,std::vector<std::vector<std::vector<std::string>>>& info)
    {
        std::ofstream target;
        target.open(path + "\\" + schedule_name);
        for (auto& ev : info)
        {
            for (auto& info : ev)
            {
                for (auto& data : info)
                {
                    target << data << " ";
                }
                target << std::endl;
            }
            target << "---";
            target << std::endl;
        }
        target.close();
    }



};