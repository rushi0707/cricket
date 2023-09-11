#include<iostream>
#include<string.h>
#include<conio.h>
using namespace std;
char* show_status(int i)
{
	switch(i)
	{
		case 0: return "";
		case 1: return "not out";
		case 2: return "bold out";
		case 3: return "caught out";
		case 4: return " run out";
		default: return "unknown";
	}
	return "unknown";
}
class team
{
	string team_name;
	string p_name[12];
	int p_run[12];
	int p_status[12];
	int p_ball[12];
	int p_num = 11;
	int extra_run;
	public:
		team();
		
		void init();
		string get_name(int i)
		{
			return p_name[i];
		}
		int get_run(int i)
		{
			return p_run[i];
		}
		int get_status(int i)
		{
			return p_status[i];
		}
		int get_extra()
		{
			return extra_run;
		}
		int get_ball(int i)
		{
			return p_ball[i];
		}
		string get_team_name()
		{
			return team_name;
		}
		int get_total();
		void add_runs(int,int);
		void set_status(int player,int status)
		{
			p_status[player] = status;
		}
		void set_out(int,int,int);
		void set_ball(int player)
		{
			p_ball[player]++;
		}
		void set_extra(int run)
		{
			extra_run += run;
		}
};
team :: team()
{
	for(int i=1;i<=11;i++)
	{
		p_name[i] = "Player";
		p_run[i] = 0;
		p_status[i] = 0;
		p_ball[i] = 0;
	}
	extra_run = 0;
}
void team :: init()
{
	cout<<"enter the team name:";
	cin>>team_name;
	cout<<"Enter the number of players:"<<p_num<<endl;
	cout<<"Enter the name of players:\n";
	for(int i =1;i<=11;i++)
	{
		cout<<"Player "<<i<<"Name:";
		cin>>p_name[i];
		p_run[i] = 0;
		p_status[i] = 0;
	}
}
void team :: add_runs(int player_num,int run)
{
	p_run[player_num] += run;
	get_total();
}
int team :: get_total()
{
	int local_total = 0;
	for(int i =1;i<=11;i++)
	{
		local_total +=p_run[i];
	}
	local_total += extra_run;
	return local_total;
}
void team :: set_out(int out_player,int type,int new_player)
{
	p_status[out_player] = type;
	p_status[new_player] = 1;
}
class score : public team
{
	int player1 = 0,player2 = 0,ball_count = 0,over = 0,max_over,out,max_out =10;
	int extra;
	public:
		score();
		void show();
		void choose();
		void dot_ball();
		void add_run();
		void wicket();
		void extra1();
		void over_complete();
};
score :: score()
{
	max_out = 10;
	init();
	cout<<"Enter the number of overs:";
	cin>>max_over;
	cout<<"Choose opening batsmans:";
	while(1)
	{
		cin>>player1;
		set_status(player1,1);
		cin>>player2;
		set_status(player2,1);
		if(player1>11 || player2>11 || player1 == player2)
			cout<<"invalid entry.";
		else 
			break;
	}
}
void score :: show()
{
	cout<<get_team_name();
	cout<<" Score:\n";
	for(int i =1;i<=11;i++)
	{
		cout<<get_name(i)<<"  ";
		cout<<show_status(get_status(i))<<"  ";
		cout<<get_run(i)<<"  ";
		if(get_status(i))
			cout<<"("<<get_ball(i)<<")"<<"  ";
			
		cout<<endl;
	}
	cout<<"Extra:";
	cout<<get_extra()<<"\n\n";
	cout<<"Over: "<<over<<"."<<ball_count;
	cout<<"\nWicket: "<<out;
	cout<<"\nTotal score: ";
	cout<<get_total()<<endl;
	
	if(ball_count<= 6 && over!=max_over)
	{	choose();	}
}
void score::choose()
{
	cout<<"\nChoose option:\n";                  
  	cout<<"\nDot Ball 1  Add Run 2  Extra 3  Wicket 4  Exit 10: ";                    
	int option;
	cin>>option;
	
	switch (option)
	{
    	case 1:    	dot_ball(); 
			  		break;
    	case 2:     add_run();  
			 		break;
    	case 3:    	extra1();  
			 		break;
    	case 4:    	wicket();  
			 		break;
    	case 10:  	return;
    	default:	cout<<"\nInvalid input\n"; 
	 
		dot_ball();
    }
}

void score::dot_ball()
{
	cout<<"             Dot Ball              \n";
	ball_count++;
	set_ball(player1);
	if(ball_count==6)
	{	
		over_complete();
		return;
	}
	
	show();
}	
void score::extra1()
{
	cout<<"             Extra Run              \n";
	cout<<"Extra?  ";
	cin>>extra;
	set_extra(extra);
	show();
}
void score::add_run()
{
	cout<<"             Add Run              \n";
	cout<<"Runs?  ";
	int runs;
	ball_count++;
	set_ball(player1);
	cin>>runs;
	add_runs(player1,runs);
	
	if(runs==1||runs==3)
	{
		//change position of batsman
	    int temp = player1;
	    player1=player2;
	    player2=temp;
	}
	
	if(ball_count==6)
	{
		over_complete();
		return;
	}
	
	show();
}
void score::over_complete()
{
	cout<<"           Over Complete\n";
	over++;
	ball_count=0;
	//change the position of batsman
	int temp = player1;
	player1=player2;
	player2=temp;
	
	if(over==max_over)
	{
		cout<<"           Inning Complete\n";
		show();
	}
	else 
		show();
	
}

void score::wicket()
{
	int o_type,new_player;
	cout<<"           Wicket\n";
	cout<<"\nOut type? (Bold-1 Caught-2 Run_out-3 )  ";
	cin>>o_type;
	out++;
	ball_count++;
	set_ball(player1);
	
	if(out==max_out)
	{
		cout<<"           Inning Complete\n";
		show();
		return;
	}
	
	cout<<"\nNew Batsmans no: ";
	cin>>new_player;
	set_out(player1,o_type+1,new_player);
	player1=new_player;
	
	if(ball_count==6)
	{
		over_complete();
		return;
	}
	
	show();
}
int main()
{
	score ms;
	ms.show();
	return 0;
}
