#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef struct wifi { // wifi에 관한 구조체 멤버 
	char ssid[20];
	char password[50];
	
	void setSsid(void); // SSID를 설정하는 함수 
	void setPassword(void); // 패스워드를 설정하는 함수 
	void clearBuffer(void); // password 버퍼를 비워주는 함수 
	bool checkPassword(void); // password 길이를 체크하는 함수 
	void makeBatch(void); // 배치파일을 만드는 함수 
}wifi;
wifi user;

bool check; // 패스워드 길이 조건을 판별하기 위한 변수 (checkPassword에서 사용) 

int main(void)
{	
	user.setSsid();
	user.setPassword();
	user.makeBatch();
	
	printf("\n\t완성되었습니다. 현재 디렉토리에 두 파일이 추가되었습니다.\n");
	
	printf("\n\t\t┌──────────┐");
	printf("\n\t\t│ 와이파이 켜기.bat  │");
	printf("\n\t\t│ 와이파이 끄기.bat  │");
	printf("\n\t\t└──────────┘"); 
	
	printf("\n\n\t와이파이 이름 : %s", user.ssid);
	printf("\n\t비밀번호      : %s\n\n\t", user.password);
	
	system("pause");
	return 0;
}

void wifi::setSsid(void)
{
	printf("\n\t노트북으로 와이파이존을 만들기 위한 프로그램입니다.");
	printf("\n\n\t네트워크 이름 [띄어쓰기 불가] : ");
	gets(user.ssid);
}

void wifi::setPassword(void)
{
	while(1)
	{
		user.clearBuffer(); // 계속해서 문자열을 입력시킬 경우가 필요하기 때문에, 항상 비워둠 
		
		system("cls");
		printf("\n\t노트북으로 와이파이존을 만들기 위한 프로그램입니다.");
		printf("\n\n\t네트워크 이름 [띄어쓰기 불가] : %s", user.ssid); // 현재까지 입력상태를 표기하기 위함 
		printf("\n\t설정할 비밀번호 [8자리 이상] : ");
		scanf("%s", user.password);
		
		if(user.checkPassword()) break; // 비밀번호 체크에서 true(정상) 반환되면 break 
		else
		{
			printf("\t비밀번호는 8자리 이상이어야 합니다.\n\n\t");
			
			system("pause");
		}
	}
}

void wifi::clearBuffer(void)
{
	for(int i = 0; i < strlen(user.password); i++)
	{
		user.password[i] = 0;
	}
}

bool wifi::checkPassword(void)
{	
	if(strlen(user.password) < 8) // 비밀번호가 8자리 미만이면 
	{
		return false; // false를 반환 
	}
	return true; // 비밀번호가 8자리 이상이면 true 반환 
}

void wifi::makeBatch(void)
{
	FILE *wifion = fopen("와이파이 켜기.bat", "w");
	FILE *wifioff = fopen("와이파이 끄기.bat", "w");
	
	fprintf(wifion, "netsh wlan set hostednetwork mode=allow ssid=%s key=%s\n", user.ssid, user.password);
	fprintf(wifion, "netsh wlan start hostednetwork\n");
	fprintf(wifion, "pause");
	fclose(wifion);
	
	fprintf(wifioff, "netsh wlan stop hostednetwork\n");
	fprintf(wifioff, "pause");
	fclose(wifioff);
}
