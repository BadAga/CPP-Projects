#include <iostream>
#include <string> 
#include <stdlib.h>
#include <algorithm>
#include <cstdio>
#include <iterator>
#include <ranges>
#include <vector>
export module Cifer;


export class Cifer
{
public:
    static void display_vec(std::vector<std::string> v)
    {
        for (auto& elem : v)
        {
            std::cout << elem;
        }
        std::cout << std::endl;
    }
	static std::vector<std::string> Make_vec(std::string pesel)
    {
        std::vector<std::string> v;
        for (auto& elem : pesel)
        {
            std::string dig;
            dig += elem;
            v.push_back(dig);
        }
        return v;
    }
    static std::vector<std::string> Make_encrypted_vec(std::string encrypted, std::string digits)
    {
        std::vector<std::string> v;
        std::string num_of_dig;
        int index_of_encrypted = 0;
        for (int i=0;i< digits.size();i++)
        {
            num_of_dig = digits[i];
            int num = std::stoi(num_of_dig);
            std::string encryptedt_one_dig;
            for (int j = 0; j < num; j++)
            {
                
                encryptedt_one_dig += encrypted[index_of_encrypted];
                index_of_encrypted++;
            }
            v.push_back(encryptedt_one_dig);
            // index_of_encrypted++;
        }
        return v;
    }
    static std::string Make_string_from_vec(std::vector<std::string> vec)
    {
        std::string str;
        for (auto& elem : vec)
        {
            str += elem;
        }
        return str;
    }
    static int Get_last_digit(int num)
    {
        std::string str = std::to_string(num);
        char l_digit = str[str.size() - 1];
        return l_digit - '0';
    }
    static std::string Encrypt_stage1(std::string pesel)
    {
        //Int_to_ascii_str
        int digit = int(pesel[0]);
        std::string str = std::to_string(digit);
        return str;
    }
    static std::vector<std::string> Encrypt_stage2(std::vector<std::string> vec, int key)
    {
        //add_key
        auto keying = std::views::transform(vec, [&key](std::string ascii)
            {
                int dig = stoi(ascii);
                dig += Get_last_digit(key);
                std::string str = std::to_string(dig);
                return str;
            });
        std::vector<std::string> v(keying.begin(), keying.end());

        return v;
    }
    static std::vector<std::string>  Encrypt_pesel(std::string str,int no_user)
    {
        std::vector<std::string> out, out2;
        std::vector<std::string> v = Make_vec(str);

        std::ranges::copy(std::views::transform(v, Encrypt_stage1), std::back_inserter(out));

        out2 = Encrypt_stage2(out, no_user);

        return out2;
    }
    static std::vector<std::string> Decrypt_stage1(std::vector<std::string>&vec, int key)
    {
        //substracting_key
        auto keying = std::views::transform(vec, [&key](std::string encrypted)
            {
                int dig = stoi(encrypted);
                dig -= Get_last_digit(key);
                std::string str = std::to_string(dig);
                return str;
            });
        std::vector<std::string> v(keying.begin(), keying.end());

        return v;
    }
    static std::string Decrypt_stage2(std::string ascii)
    {
        //ascii_str to int
        int ascii_value =std::stoi(ascii);
        char c = ascii_value;
        std::string digit;
        digit += c;
        return digit;
    }
  
    static std::string Decrypt_pesel(std::vector<std::string> v, int no_user)
    {
        std::vector<std::string> out, out2;
                
        out = Decrypt_stage1(v, no_user);
        std::ranges::copy(std::views::transform(out, Decrypt_stage2), std::back_inserter(out2));
        return Make_string_from_vec(out2);
    }
    static std::string Get_number_of_digits_in_number(std::vector<std::string> encrypted_vec)
    {
        std::string str_numbs;
        for (auto& elem : encrypted_vec)
        {
            int size = elem.size();
            str_numbs += std::to_string(size);
        }
        return str_numbs;
    }
};