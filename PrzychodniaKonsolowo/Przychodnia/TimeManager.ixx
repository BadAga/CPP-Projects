#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <chrono>
#include <time.h>
#include <string>
export module TimeManager;
import <iostream>;

export class TimeManager
{
public:
	static std::string Get_current_date()
	{
		const std::chrono::time_point<std::chrono::system_clock> now{ std::chrono::system_clock::now() };

		const std::chrono::year_month_day ymd{ std::chrono::floor<std::chrono::days>(now) };
		int y = static_cast<int>(ymd.year());
		int m = (int)(static_cast<unsigned>(ymd.month()));
		int d = (int)(static_cast<unsigned>(ymd.day()));
		std::string date, year = std::to_string(y);
		if (d < 10)
		{
			date = "0" + std::to_string(d);
		}
		else
		{
			date = std::to_string(d);
		}
		if (m < 10)
		{
			date += ".0" + std::to_string(m);
		}
		else
		{
			date += "." + std::to_string(m);
		}
		date += ".";
		date.push_back(year[2]);
		date.push_back(year[3]);

		return date;
	}

	static std::string Get_current_time()
	{
		time_t rawtime;
		struct tm* timeinfo;

		time(&rawtime);
		timeinfo = localtime(&rawtime);
		int h= timeinfo->tm_hour;
		timeinfo = localtime(&rawtime);
		int m = timeinfo->tm_min;
		std::string time = "";
		if (h < 10)
		{
			time += "0";
		}
		time += std::to_string(h)+":";
		if (m < 10)
		{
			time += "0";
		}
		time += std::to_string(m);
		return time;
		
	}

	static int Get_num_of_days_in_month(std::string month_num)
	{
		if (month_num == "01" || month_num == "03" || month_num == "05" || month_num == "07" || month_num == "08" || month_num == "10" || month_num == "12")
		{
			return 31;
		}
		else if (month_num == "02")
		{
			return 29;
		}
		else
		{
			return 30;
		}

	}

	static int Get_num_of_days_in_month(int month_num)
	{
		if (month_num == 1 || month_num ==3|| month_num ==5 || month_num == 7 || month_num == 8 || month_num ==10 || month_num ==12)
		{
			return 31;
		}
		else if (month_num == 2)
		{
			return 29;
		}
		else
		{
			return 30;
		}

	}

	static int Get_current_weekday_num()
	{
		
		time_t rawtime;
		struct tm* timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		std::string timein = asctime(timeinfo);
		std::string day = timein.substr(0, 3);

		// Sat Sun Mon Tue Wed Thu Fri
		if (day == "Mon")
		{
			return 0;
		}
		else if (day == "Tue")
		{
			return 1;
		}
		else if (day == "Wed")
		{
			return 2;
		}
		else if (day == "Thu")
		{
			return 3;
		}
		else if (day == "Fri")
		{
			return 4;
		}
		else if (day == "Sat")
		{
			return 5;
		}
		else
		{
			return 6;
		}
		
	}

	static std::string Add_3_months(std::string date)
	{
		std::string month = date.substr(3, 2);
		std::string ending_date=date;
		char first = month[0];
		char second = month[1];
		int num_f = first - 48;
		int num_s = second - 48;
		num_s += 3;
		if (num_s<10)
		{
			
			ending_date[4] = num_s+'0';
		}
		else if (num_s > 12)
		{
			num_f = 0;
			num_s -= 12;
			
			ending_date[3] = num_f + '0';
			ending_date[4] = num_s + '0';
			
		}
		else
		{
			num_f = 1;
			num_s -= 10;
			ending_date[3] = num_f + '0';
			ending_date[4] = num_s + '0';
		}
		return ending_date;
	}

	static std::string Get_first_day_of_current_week_date()
	{
		std::string date = Get_current_date();
		int day_of_week = Get_current_weekday_num();
		return Substract_days_from_date(date, day_of_week);
	}

	static std::string Substract_days_from_date(std::string date, int num) //within same year; max num=30
	{
		int d = 10 * (date[0] - 48) + date[1] - 48;
		int m = 10 * (date[3] - 48) + date[4] - 48;
		
		int days_in_prev_month = 1;
		int decrement = 1;		
		
		if ((d - num) > 0)
		{
			d = d - num;
		}
		else //05.05-5 lub 05.05-10
		{
			int prev = d-num;
			while (prev <= 0)
			{
				days_in_prev_month = Get_num_of_days_in_month(m - decrement);
				prev = days_in_prev_month +prev;
				m -= 1;
				decrement++;
			}
			d = prev;
		}
		std::string sub_date=date;

		sub_date[0] = '0' + d / 10;
		while (d >= 0)
		{
			d -= 10;
		}
		d += 10;
		sub_date[1] = '0' + d ;
		
		sub_date[3] = '0' + m / 10;
		if (m < 10)
		{
			sub_date[4] = '0' +m;
		}
		else
		{
			sub_date[4] = '0' + m - 10;
		}
		return sub_date;
	}

	static std::string Add_days_to_date(std::string date, int num)
	{
		int d = 10 * (date[0] - 48) + date[1] - 48;
		int m = 10 * (date[3] - 48) + date[4] - 48;

		int days_current_month = Get_num_of_days_in_month(m);
		int increment = 1;
		int days_in_next_month;

		if ((num + d) <= days_current_month)
		{
			d = d + num;
		}
		else
		{
			int temp= num-(days_current_month - d);
			days_in_next_month = Get_num_of_days_in_month(m + increment);
			m++;
			while (temp > days_in_next_month )
			{
				
				temp = temp-days_in_next_month ;
				m ++;		
				days_in_next_month = Get_num_of_days_in_month(m);
			}
			d = temp;
		}

		std::string add_date = date;

		add_date[0] = '0' + d / 10;
		while (d >= 0)
		{
			d -= 10;
		}
		d += 10;
		add_date[1] = '0' + d;

		add_date[3] = '0' + m / 10;
		if (m < 10)
		{
			add_date[4] = '0' + m;
		}
		else
		{
			add_date[4] = '0' + m - 10;
		}
		return add_date;
	}

	static std::string Return_earlier_time(std::string lft, std::string rht)
	{
		//HH:mm
		int hour_lft, hour_rht;
		int minutes_lft, minutes_rht;
		std::string earlier;

		hour_lft = 10 * (lft[0] - '0') + (lft[1] - '0');
		hour_rht= 10 * (rht[0] - '0') + (rht[1] - '0');

		minutes_lft=10 * (lft[3] - '0') + (lft[4] - '0');
		minutes_rht= 10 * (rht[3] - '0') + (rht[4] - '0');
		
		if (hour_lft > hour_rht)
		{
			earlier = rht;
			return earlier;
		}
		else if (hour_lft == hour_rht)
		{
			if (minutes_lft > minutes_rht)
			{
				earlier = rht;
				return earlier;
			}
			else if (minutes_lft == minutes_rht)
			{
				earlier = lft;
				return earlier;
			}
			else
			{
				earlier = lft;
				return earlier;
			}
		}
		else
		{
			earlier = lft;
			return earlier;
		}

	}

	static std::string Return_earlier_date(std::string lft, std::string rht)
	{
		//01/02/23
		int d_lft = 10 * (lft[0] - 48) + lft[1] - 48;
		int m_lft = 10 * (lft[3] - 48) + lft[4] - 48;
		int y_lft = 10 * (lft[6] - 48) + lft[7] - 48;

		int d_rht = 10 * (rht[0] - 48) + rht[1] - 48;
		int m_rht = 10 * (rht[3] - 48) + rht[4] - 48;
		int y_rht = 10 * (rht[6] - 48) + rht[7] - 48;
		
		if (y_rht > y_lft) //../22 ../25
		{
			return lft;
		}
		else if (y_rht < y_lft)//../27 ../25
		{
			return rht;
		}
		else /// ../22 ../22
		{
			if (m_lft < m_rht) //.../02/22  .../06/22
			{
				return lft;
			}
			else if (m_lft > m_rht)//.../09/22  .../06/22
			{
				return rht;
			}
			else//.../06/22  .../06/22
			{
				if (d_lft < d_rht)//.12/06/22  .25/06/22
				{
					return lft;
				}
				else if (d_lft > d_rht)
				{
					return rht;
				}
				else
				{
					return rht;
				}
			}
		}


	}

	static int Get_Duration(std::string& lft, std::string& rht)
	{
		int hour_lft, hour_rht;
		int minutes_lft, minutes_rht;
		int duration = 0;
		std::string earlier= Return_earlier_time(lft,rht);

		hour_lft = 10 * (lft[0] - '0') + (lft[1] - '0');
		hour_rht = 10 * (rht[0] - '0') + (rht[1] - '0');

		minutes_lft = 10 * (lft[3] - '0') + (lft[4] - '0');
		minutes_rht = 10 * (rht[3] - '0') + (rht[4] - '0');
		if (earlier == lft) //  12:13 10:23
		{
			duration = (hour_rht - hour_lft) * 60 + minutes_rht - minutes_lft;
		}
		else // 15:23 11:34
		{
			duration = (hour_lft - hour_rht) * 60 + minutes_lft - minutes_rht;
		}
		return duration;
	}

	static std::string Add_minutes_to_time(std::string& time,int minutes)
	{
		std::string ending_time;

		int hour_b;
		int minutes_b;
		hour_b = 10 * (time[0] - '0') + (time[1] - '0');
		minutes_b = 10 * (time[3] - '0') + (time[4] - '0');

		if ((minutes_b + minutes) < 60)
		{
			//12:50
			minutes_b = minutes_b + minutes; //08 15 56
			ending_time = time;
			ending_time[3] = (minutes_b / 10) + '0';
			ending_time[4] = (minutes_b-((minutes_b / 10)*10)) + '0';
		}
		else
		{
			//12:15+180
			while ((minutes_b + minutes) > 59)
			{
				minutes -= 60;
				hour_b++;
			}
			minutes_b = minutes_b + minutes; //08 15 56
			ending_time = time;
			ending_time[0] = (hour_b / 10) + '0';
			ending_time[1] = (hour_b - ((hour_b / 10) * 10)) + '0';
			ending_time[3] = (minutes_b / 10) + '0';
			ending_time[4] = (minutes_b - ((minutes_b / 10) * 10)) + '0';
		}
		return ending_time;
	}

	static bool Check_if_date_is_not_past(std::string& entered)  //0 if in past
	{
		std::string curr = TimeManager::Get_current_date();
		
		if (entered == curr)
		{
			return 1;
		}
		else if (Return_earlier_date(entered, curr) == entered)
		{
			return 0;
		}
		return 1;
	}

	static bool Check_if_time_is_not_past(std::string& entered)  //0 if in past
	{
		std::string curr = TimeManager::Get_current_time();
		
		if (Return_earlier_time(entered, curr) == entered)
		{
			return 0;
		}
		return 1;
	}

	static bool Check_if_date_is_no_farther_than_3_months_away(std::string& entered)
	{
		std::string curr = TimeManager::Get_current_date();
		std::string boundry = TimeManager::Add_3_months(curr);
		if (boundry == entered)
		{
			return 1;
		}
		else if (Return_earlier_date(boundry,entered) == boundry)
		{
			return 0;
		}
		return 1;
	}
};