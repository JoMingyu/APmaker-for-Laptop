#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef struct wifi { // wifi�� ���� ����ü ��� 
	char ssid[20];
	char password[50];
	
	void setSsid(void); // SSID�� �����ϴ� �Լ� 
	void setPassword(void); // �н����带 �����ϴ� �Լ� 
	void clearBuffer(void); // password ���۸� ����ִ� �Լ� 
	bool checkPassword(void); // password ���̸� üũ�ϴ� �Լ� 
	void makeBatch(void); // ��ġ������ ����� �Լ� 
}wifi;
wifi user;

bool check; // �н����� ���� ������ �Ǻ��ϱ� ���� ���� (checkPassword���� ���) 

int main(void)
{	
	user.setSsid();
	user.setPassword();
	user.makeBatch();
	
	printf("\n\t�ϼ��Ǿ����ϴ�. ���� ���丮�� �� ������ �߰��Ǿ����ϴ�.\n");
	
	printf("\n\t\t������������������������");
	printf("\n\t\t�� �������� �ѱ�.bat  ��");
	printf("\n\t\t�� �������� ����.bat  ��");
	printf("\n\t\t������������������������"); 
	
	printf("\n\n\t�������� �̸� : %s", user.ssid);
	printf("\n\t��й�ȣ      : %s\n\n\t", user.password);
	
	system("pause");
	return 0;
}

void wifi::setSsid(void)
{
	printf("\n\t��Ʈ������ ������������ ����� ���� ���α׷��Դϴ�.");
	printf("\n\n\t��Ʈ��ũ �̸� [���� �Ұ�] : ");
	gets(user.ssid);
}

void wifi::setPassword(void)
{
	while(1)
	{
		user.clearBuffer(); // ����ؼ� ���ڿ��� �Է½�ų ��찡 �ʿ��ϱ� ������, �׻� ����� 
		
		system("cls");
		printf("\n\t��Ʈ������ ������������ ����� ���� ���α׷��Դϴ�.");
		printf("\n\n\t��Ʈ��ũ �̸� [���� �Ұ�] : %s", user.ssid); // ������� �Է»��¸� ǥ���ϱ� ���� 
		printf("\n\t������ ��й�ȣ [8�ڸ� �̻�] : ");
		scanf("%s", user.password);
		
		if(user.checkPassword()) break; // ��й�ȣ üũ���� true(����) ��ȯ�Ǹ� break 
		else
		{
			printf("\t��й�ȣ�� 8�ڸ� �̻��̾�� �մϴ�.\n\n\t");
			
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
	if(strlen(user.password) < 8) // ��й�ȣ�� 8�ڸ� �̸��̸� 
	{
		return false; // false�� ��ȯ 
	}
	return true; // ��й�ȣ�� 8�ڸ� �̻��̸� true ��ȯ 
}

void wifi::makeBatch(void)
{
	FILE *wifion = fopen("�������� �ѱ�.bat", "w");
	FILE *wifioff = fopen("�������� ����.bat", "w");
	
	fprintf(wifion, "netsh wlan set hostednetwork mode=allow ssid=%s key=%s\n", user.ssid, user.password);
	fprintf(wifion, "netsh wlan start hostednetwork\n");
	fprintf(wifion, "pause");
	fclose(wifion);
	
	fprintf(wifioff, "netsh wlan stop hostednetwork\n");
	fprintf(wifioff, "pause");
	fclose(wifioff);
}
