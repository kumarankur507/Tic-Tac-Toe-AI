#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define clrscr() system("cls");
vector< vector< char>> arr(4, vector< char> (4));

const int space = 45, new_ln = 10, delay = 501;

pair< int , pair<int, int>> mmin(vector< vector< char>>, int);

pair< int , pair<int, int>> mmax(vector< vector< char>>, int);

void init_board()
{
	for(int i = 1; i <= 3; ++ i)
		for(int j = 1; j <= 3; ++ j)
		    arr[i][j]=' ';
}

void end()
{
	char s;
	cin >> s;
	if(s == 'y' || s=='Y')	;
	else exit(0);	
}

void print_spaces(int x)
{
	for(int i = 0; i < x; ++i)
		cout << ' ';
}

void print_board()
{
	clrscr();
	
	for(int i = 0; i < 5; ++ i)	cout << "\n";
	
	print_spaces(space - 8);
	cout << "-----        -----          -----   _   \n";
	
	print_spaces(space - 8);
	cout << "  |  .  __     |  _    __     |  _ |_  \n";
	
	print_spaces(space - 8);
	cout << "  |  | |__     | |_|_ |__     | |_||_ \n\n";
	
	print_spaces(space - 8);
	cout << "                    by Ankur Kumar\n\n";
	
	print_spaces(space - 4);
	cout << "Press R to Reset at any Move";
	
	for(int i = 0; i < 5; ++ i)	cout << "\n";
	
	print_spaces(space);
	cout << "   1   2   3 \n";
	
	print_spaces(space);
	cout << "1  " << arr[1][1] << " | " << arr[1][2] << " | " << arr[1][3] << " \n";
	
	print_spaces(space);
	cout << "  ---|---|---\n";
	
	print_spaces(space);
	cout << "2  " << arr[2][1] << " | " << arr[2][2]<<" | " << arr[2][3] << " \n";
	
	print_spaces(space);
	cout << "  ---|---|---\n";
	
	print_spaces(space);
	cout << "3  " << arr[3][1] << " | " << arr[3][2] << " | " << arr[3][3] << " \n";
}

bool is_won(vector<vector<char>> a,char ch)
{
	
	for(int i = 1; i <=3 ; ++ i)
	{
		int cnt = 0;
		for(int j = 1; j <=3; ++j)
			cnt += (a[i][j] == ch);
		if(cnt == 3)
			return 1;
	}
	
	for(int i = 1; i <=3 ; ++ i)
	{
		int cnt = 0;
		for(int j = 1; j <=3; ++j)
			cnt += (a[j][i] == ch);
		if(cnt == 3)
			return 1;
	}
	
	int cnt = 0;
	for(int i = 1; i <= 3; ++ i)
		cnt += (a[i][i] == ch);
	
	if(cnt == 3)
			return 1;
			
	cnt = 0;
	for(int i = 1; i <= 3; ++ i)
		cnt += (a[i][4 - i] == ch);
	
	if(cnt == 3)
			return 1;
	return 0;
			
}


pair< int , pair<int, int> > mmin(vector<vector<char>> a,int cnt) //o ki turn
{
	if(cnt == 0)
		return {-5000 , {-1, - 1}};
		
	int mn = 1000;
	pair<int,int> p = {-1, -1};
	for(int i = 1; i <= 3; ++ i)
	{
		for(int j = 1; j <= 3; ++j)
			if(a[i][j] == ' ')
			{
				if(p.first == -1)
					p = {i, j};
				vector<vector<char>> temp = a;
				temp[i][j] = 'o';
				
				if(is_won(temp, 'o'))
					return {cnt * -1, {i , j}};
				
				// else if(is_won(temp, 'x'))
				// {
				// 	if(cnt * 1 < mn)
				// 	{
				// 		mn = cnt * 1;
				// 		p = {i, j};
				// 	}
				// }
					
				else if(mmax(temp, cnt -1).first < mn)
				{
					mn = mmax(temp, cnt -1).first;
					p = {i, j};
				}
			}
	}
	return {mn, p};
}

pair< int , pair<int, int> > mmax(vector<vector<char>> a,int cnt) //x ki turn 
{
	if(cnt == 0)
		return {5000 , {-1, - 1}};
		
	int mx = - 1000;
	pair<int,int> p = {-1, -1};
	for(int i = 1; i <= 3; ++ i)
	{
		for(int j = 1; j <= 3; ++j)
			if(a[i][j] == ' ')
			{
				if(p.first == -1)
					p = {i, j};
				vector<vector<char>> temp = a;
				temp[i][j] = 'x';
				
				if(is_won(temp, 'x'))
					return {cnt , {i , j}};
				
				// else if(is_won(temp, 'o'))
				// {
				// 	if(cnt * -1 > mx)
				// 	{
				// 		mx = (cnt) * -1;
				// 		p = {i, j};
				// 	}
				// }
					
				else if(mmin(temp, cnt - 1).first > mx)
				{
					mx = mmin(temp, cnt - 1).first;
					p = {i, j};
				}
			}
	}
	return {mx, p};
}


int computer()
{
	clrscr();	
	int cnt = 0;
	
	for(int i = 1; i <= 3; ++i)
		for(int j = 1; j <= 3; ++j)
			cnt += (arr[i][j] == ' '); 
	
	pair<int, pair<int,int>> pos = mmax(arr, cnt); 
	
	arr[pos.second.first][pos.second.second] = 'x';
	print_board();
	
	if(pos.first == cnt)
	{	
		cout << "\n";
		print_spaces(space);
		cout << " Computer Won! ";
		return 1;
	}
	
	return 0;
	
}


int main(){
    start:

    init_board();
    int x,y;
    for (int i=0;i<=9;i=i+2){
        print_board();
        print_spaces(space);
        cout<<"Your Turn: ";
        bool valid = false;
        int cha=3;
        while ((!valid)&&(cha)){
            char ch;
            cin>>ch;
            
            if (ch=='R'||ch=='r') goto start;
            cin>>y;
            x=ch-'0';

            if (x>=1&&x<4&&y>=1&&y<4&&arr[x][y]==' '){
                valid=true;
                arr[x][y]='o';
            }
            else{
                cha--;
                if (cha==0){
                    print_board();
                    cout<<endl;
                    print_spaces(space-5);
                    cout<<"Too many incorrent attempts!"<<endl;
                    print_spaces(space);
                    cout<<"Try Again (Y/N)? ";
                    end();
                    goto start; 
                }

                print_board();
			
				cout<<endl;
				print_spaces(space);	
				cout << "Invalid Move!"<<endl;
				
				print_spaces(space);
				cout << " Try Again"<<endl;
				
				print_spaces(space - 1);
				cout << cha << (cha == 1 ? " Chance" : " Chances") << " left:";
            }

        }
        print_board();
		if(i == 8)	
		{
			print_board();
			cout <<endl;
			
			print_spaces(space);
			cout << "  Match Drawn"<<endl<<endl;
			
			print_spaces(space);
			cout << "Try Again(y/n)? ";
		
			end();
			goto start;
		}

        if(computer()==1)
		{
			cout << "\n";
			print_spaces(space);
			cout << "Try Again(y/n)? ";
			
			end();
			
			goto start;
		}
    }
    return 0;
}