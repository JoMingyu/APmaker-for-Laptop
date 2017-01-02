#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef struct wifi { // struct members for wifi
	char ssid[20];
	char password[50];
	
	void setSsid(void); // function that setting ssid
	void setPassword(void); // function that setting password
	void clearBuffer(void); // function that clear buffer
	bool checkPassword(void); // function that check length of password 
	void makeBatch(void); // function that make batch file
}wifi;
wifi user;

bool check; // uses checkPassword function, variable that check password length

int main(void) {	
	user.setSsid();
	user.setPassword();
	user.makeBatch();
	
	printf("\n\tSuccess. Added this two files in current directory.\n");
	
	printf("\n\t\t忙式式式式式式式忖");
	printf("\n\t\t弛 Wifi On.bat  弛");
	printf("\n\t\t弛 Wifi Off.bat 弛");
	printf("\n\t\t戌式式式式式式式戎"); 
	
	printf("\n\n\tWifi SSID : %s", user.ssid);
	printf("\n\tPassword  : %s\n\n\t", user.password);
	
	system("pause");
	return 0;
}

void wifi::setSsid(void) {
	printf("\n\tProgram to make AP with laptop.");
	printf("\n\n\tSSID [Without Spacing] : ");
	gets(user.ssid);
}

void wifi::setPassword(void) {
	while(!user.checkPassword()) {
		user.clearBuffer(); // always clear the buffer because continue to enter a string
		
		system("cls");
		printf("\n\tProgram to make AP with laptop.");
		printf("\n\n\tSSID [Without Spacing] : %s", user.ssid); // write input state
		printf("\n\tPassword [8 digits or higher] : ");
		scanf("%s", user.password);
		
		if(!user.checkPassword()) {
			printf("\tPassword must be greater than 8 digits.\n\n\t");
			
			system("pause");
		}
	}
}

void wifi::clearBuffer(void) {
	for(int i = 0; i < strlen(user.password); i++) {
		user.password[i] = 0;
	}
}

bool wifi::checkPassword(void) {	
	if(strlen(user.password) < 8) {// if password is less than 8 digits
		return false;
	}
	else return true;
}

void wifi::makeBatch(void) {
	FILE *wifion = fopen("Wifi On.bat", "w");
	FILE *wifioff = fopen("WIfi Off.bat", "w");
	
	fprintf(wifion, "netsh wlan set hostednetwork mode=allow ssid=%s key=%s\n", user.ssid, user.password);
	fprintf(wifion, "netsh wlan start hostednetwork\n");
	fprintf(wifion, "pause");
	fclose(wifion);
	
	fprintf(wifioff, "netsh wlan stop hostednetwork\n");
	fprintf(wifioff, "pause");
	fclose(wifioff);
}


