#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <unistd.h>
#include <Mmsystem.h>
#include<conio.h>
#include <string.h>
#include <ctype.h>
#include <curl/curl.h>
//for linking gcc -o qanda qanda.c -lcurl -lwinmm
#define ALIAS "random_str"
#define MAX_WORD_LENGTH 100
#define FILENAME "C:\\Users\\kaushik\\OneDrive\\Desktop\\c program project\\out.wav.txt"

//int main(int argc,char *argv[])
void calling_mic()
{
	char mci_command[100];
	char ReturnString[300];
	int mci_error;
	FILE *fp;

	sprintf(mci_command, "open new type waveaudio alias %s", ALIAS);
	mci_error = mciSendString(mci_command, ReturnString, sizeof(ReturnString), NULL);

	// set the time format
	sprintf(mci_command,"set %s time format ms", ALIAS);    // just set time format
	mci_error = mciSendString(mci_command, ReturnString, sizeof(ReturnString), NULL);

	// start recording
	sprintf(mci_command, "record %s notify", ALIAS);
	mci_error = mciSendString(mci_command, ReturnString, sizeof(ReturnString), NULL);

	printf("Now on air, press a key too stop...\n");
    Sleep(5000);

	//stop recording
	sprintf(mci_command,"stop %s", ALIAS);
	mci_error = mciSendString(mci_command, ReturnString, sizeof(ReturnString), NULL);

	// save the file
	sprintf(mci_command, "save %s %s", ALIAS, "random1.wav");
	mci_error = mciSendString(mci_command, ReturnString, sizeof(ReturnString), NULL);

	// close the device
	sprintf(mci_command,"close %s", ALIAS);
	mci_error = mciSendString(mci_command, ReturnString, sizeof(ReturnString), NULL);

	freopen("NUL", "w", stdout);  //Redirect stdout to the null device
    freopen("NUL", "w", stderr);  // Redirect stderr to the null device

	system("wsl  ffmpeg -i random1.wav -acodec pcm_s16le -ac 1 -ar 16000 out.wav -y ");
	//system("main.exe -otxt out.wav");
	fp = popen("wsl curl --location --request POST \"https://centralindia.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=en-US&format=detailed\""
           " --header \"Ocp-Apim-Subscription-Key: e650cf7f3f8e4b4f9721a05039ca6091\""
           " --header \"Content-Type: audio/wav\""
           " --data-binary \"@/mnt/c/Users/kaushik/OneDrive/Desktop/c program project/out.wav\""
           " --output response.json"
           " && wsl jq -r '.NBest[0].Display' response.json > output.txt","w");
	if (fp == NULL) {
        // Error occurred while executing the command
    }
	pclose(fp); 


	freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);

}

void tts(const char* text){
	char command[5000];
    snprintf(command, sizeof(command), "curl --location --request POST \"https://centralindia.tts.speech.microsoft.com/cognitiveservices/v1\" --header \"Ocp-Apim-Subscription-Key: e650cf7f3f8e4b4f9721a05039ca6091\" --header \"Content-Type: application/ssml+xml\" --header \"X-Microsoft-OutputFormat: audio-16khz-128kbitrate-mono-mp3\" --header \"User-Agent: curl\" --data-raw \"<speak version='1.0' xml:lang='en-US'><voice xml:lang='en-US' xml:gender='female' name='en-IN-NeerjaNeural'>%s </voice></speak>\" --output output123.mp3", text);

    system(command);

    // Specify the path to the MP3 file
    const char* filePath = "C:\\Users\\kaushik\\OneDrive\\Desktop\\c program project\\output123.mp3";

    // Open the MP3 file
    MCI_OPEN_PARMS openParams = { 0 };
    openParams.lpstrDeviceType = "mpegvideo";
    openParams.lpstrElementName = filePath;

    if (mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD_PTR)&openParams) != 0) {
        printf("Failed to open the MP3 file.\n");
        //return 1;
    }

    // Play the MP3 file
    MCI_PLAY_PARMS playParams = { 0 };
    playParams.dwCallback = (DWORD_PTR)GetConsoleWindow();

    if (mciSendCommand(openParams.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)&playParams) != 0) {
        printf("Failed to play the MP3 file.\n");
        //return 1;
    }

    // Get the length of the audio file
    MCI_STATUS_PARMS statusParams = { 0 };
    statusParams.dwItem = MCI_STATUS_LENGTH;

    if (mciSendCommand(openParams.wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&statusParams) != 0) {
        printf("Failed to get the audio file length.\n");
        //return 1;
    }

    // Convert the length to milliseconds
    DWORD audioLength = statusParams.dwReturn;
    DWORD audioDuration = audioLength / 1000;

    //printf("Audio file duration: %u seconds\n", audioDuration);

	audioDuration*=1000;

    // Wait until the playback is finished
    Sleep(audioDuration);  // Adjust the duration as needed

    // Close the MP3 file
    MCI_GENERIC_PARMS closeParams = { 0 };

    if (mciSendCommand(openParams.wDeviceID, MCI_CLOSE, 0, (DWORD_PTR)&closeParams) != 0) {
        printf("Failed to close the MP3 file.\n");
        //return 1;
    }

}

void run_python(const char* sentence) {

    char command[200];
    sprintf(command, "C:/Users/kaushik/AppData/Local/Microsoft/WindowsApps/python3.10.exe \"c:/Users/kaushik/OneDrive/Desktop/c program project/gptgo.py\" \"%s\" > outputgptgo.txt", sentence);
    system(command);
}

//calling_mic();

int main() {
    int a=0;
    while (a==0) {
        calling_mic();

        FILE *file;
        char filename[] = "output.txt"; 

        // Open the file in read mode
        file = fopen(filename, "r");

        // Check if the file exists and can be opened
        if (file == NULL) {
            printf("Error opening the file.\n");
            return 1;
        }

        // Get the file size
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        fseek(file, 0, SEEK_SET);

        // Allocate memory to store the file content
        char *file_content = (char *)malloc(file_size + 1); // +1 for null terminator

        if (file_content == NULL) {
            printf("Memory allocation error.\n");
            fclose(file);
            return 1;
        }

        // Read the entire file content into the variable
        size_t bytes_read = fread(file_content, 1, file_size, file);

        if (bytes_read != file_size) {
            printf("Error reading the file.\n");
            free(file_content);
            fclose(file);
            return 1;
        }

        // Null-terminate the string
        file_content[file_size] = '\0';

        // Close the file
        fclose(file);


        run_python(file_content);

        // Don't forget to free the allocated memory when you're done
        free(file_content);
    }

    return 0;
}
