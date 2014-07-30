/*
simulates keyboard input into the BaldiSync window and activates the Text-To-Speech part of that program
Author: Chris Garman at Lehigh University
*/



#include <string>
//#include <X11/Xlib.h>
//#include <X11/keysym.h>
//#include  <X11/extensions/XTest.h>
//#include <unistd.h>
// Because the SendInput function is only supported in
// Windows 2000 and later, WINVER needs to be set as
// follows so that SendInput gets defined when windows.h
// is included below.
#define WINVER 0x0500
#include <windows.h>
#include <wchar.h>
#include <stdlib.h>

extern "C"{


	__declspec(dllexport) int typeInBaldi(char* phrase)
	{
		INPUT ip;
		//setup for generic keyboard event
		ip.type = INPUT_KEYBOARD;
		ip.ki.wScan = 0;
		ip.ki.time = 0;
		ip.ki.dwExtraInfo = 0;
	
		HWND hWnd = ::FindWindow(NULL, L"bsync - Baldi with natural speech"); //must specify the window name to switch to for typing here
		if (hWnd) {
			//sets the focus to the baldi sync window (have cursor in textbox for tts)
			::SetForegroundWindow(hWnd);
			::SetFocus(hWnd);

		}

		std::string str;

		//selects a voice to use, don't need these if you just want the default voice
		std::string startTags = "<SABLE><SPEAKER NAME='mwm2tll'> "; //mwm2tll is an english female voice
		std::string endTags = " </SPEAKER></SABLE>";


		//sends start tags
		for(int i = 0; (unsigned int)i < startTags.size(); i++){
		
			if(isalpha(startTags[i])){

			
				ip.ki.wVk = VK_SHIFT; 
				ip.ki.dwFlags = 0; //0 for key press
				SendInput(1, &ip, sizeof(INPUT));
			
				ip.ki.wVk = startTags[i]; 
				ip.ki.dwFlags = 0; //0 for key press
				SendInput(1, &ip, sizeof(INPUT));
			
				ip.ki.wVk = startTags[i]; 
				ip.ki.dwFlags = KEYEVENTF_KEYUP; //key release
				SendInput(1, &ip, sizeof(INPUT));
			
				ip.ki.wVk = VK_SHIFT; 
				ip.ki.dwFlags = KEYEVENTF_KEYUP; //key release
				SendInput(1, &ip, sizeof(INPUT));

			}
			else if(startTags[i] == '='){
				ip.ki.wVk = VK_OEM_PLUS; //corresponds to equal (shift OEM_PLUS would be a +)
				ip.ki.dwFlags = 0; //0 for key press
				SendInput(1, &ip, sizeof(INPUT));
			
				ip.ki.wVk = VK_OEM_PLUS; 
				ip.ki.dwFlags = KEYEVENTF_KEYUP; 
				SendInput(1, &ip, sizeof(INPUT));
			}
			else if(startTags[i] == '<'){
				//shift comma yields a <
				ip.ki.wVk = VK_SHIFT; 
				ip.ki.dwFlags = 0; //0 for key press
				SendInput(1, &ip, sizeof(INPUT));
			
				ip.ki.wVk = VK_OEM_COMMA; 
				ip.ki.dwFlags = 0; //0 for key press
				SendInput(1, &ip, sizeof(INPUT));
			
				ip.ki.wVk = VK_OEM_COMMA; 
				ip.ki.dwFlags = KEYEVENTF_KEYUP; 
				SendInput(1, &ip, sizeof(INPUT));
			
				ip.ki.wVk = VK_SHIFT; 
				ip.ki.dwFlags = KEYEVENTF_KEYUP; 
				SendInput(1, &ip, sizeof(INPUT));
			}
			else if(startTags[i] == '>'){
				//key sequence to simulate >
				ip.ki.wVk = VK_SHIFT; 
				ip.ki.dwFlags = 0; //0 for key press
				SendInput(1, &ip, sizeof(INPUT));
			
				ip.ki.wVk = VK_OEM_PERIOD; 
				ip.ki.dwFlags = 0; //0 for key press
				SendInput(1, &ip, sizeof(INPUT));
			
				ip.ki.wVk = VK_OEM_PERIOD; 
				ip.ki.dwFlags = KEYEVENTF_KEYUP; 
				SendInput(1, &ip, sizeof(INPUT));

				ip.ki.wVk = VK_SHIFT; 
				ip.ki.dwFlags = KEYEVENTF_KEYUP; 
				SendInput(1, &ip, sizeof(INPUT));
	
			}
			 else{
				 if(startTags[i] == '\''){
					//everything in single quotes needs to be lower case for
					//the number for voice selection to be correct
			
					ip.ki.wVk = VK_OEM_7; //For the US standard keyboard, the 'single-quote/double-quote' key 
					ip.ki.dwFlags = 0; //0 for key press
					SendInput(1, &ip, sizeof(INPUT));
			
					ip.ki.wVk = VK_OEM_7; //For the US standard keyboard, the 'single-quote/double-quote' key 
					ip.ki.dwFlags = KEYEVENTF_KEYUP; 
					SendInput(1, &ip, sizeof(INPUT));
			

					 i++;
					 while(startTags[i] != '\''){

						ip.ki.wVk = toupper(startTags[i]); //toupper for lowercase letters for ascii value to correspond to proper VK value
						ip.ki.dwFlags = 0; //0 for key press
						SendInput(1, &ip, sizeof(INPUT));
			
						ip.ki.wVk = toupper(startTags[i]); 
						ip.ki.dwFlags = KEYEVENTF_KEYUP; 
						SendInput(1, &ip, sizeof(INPUT));

						 i++;
					 }

					ip.ki.wVk = VK_OEM_7; //For the US standard keyboard, the 'single-quote/double-quote' key 
					ip.ki.dwFlags = 0; //0 for key press
					SendInput(1, &ip, sizeof(INPUT));
			
					ip.ki.wVk = VK_OEM_7; //For the US standard keyboard, the 'single-quote/double-quote' key 
					ip.ki.dwFlags = KEYEVENTF_KEYUP; 
					SendInput(1, &ip, sizeof(INPUT));
				 }
				 else{
					//sends all other characters besides alphas and >

					ip.ki.wVk = toupper(startTags[i]); 
					ip.ki.dwFlags = 0; //0 for key press
					SendInput(1, &ip, sizeof(INPUT));
			
					ip.ki.wVk = toupper(startTags[i]); 
					ip.ki.dwFlags = KEYEVENTF_KEYUP; 
					SendInput(1, &ip, sizeof(INPUT));
				 }
			 }
		
		}


		//display message sent from external program (must be alphanumeric characters only)
		 for(int i=0;phrase[i]!=0;i++){

			ip.ki.wVk = toupper(phrase[i]); 
			ip.ki.dwFlags = 0; //0 for key press
			SendInput(1, &ip, sizeof(INPUT));
			
			ip.ki.wVk = toupper(phrase[i]); 
			ip.ki.dwFlags = KEYEVENTF_KEYUP; 
			SendInput(1, &ip, sizeof(INPUT));

		 }

		//send the end tags
		 for(int i = 0; (unsigned int)i < endTags.size(); i++){
			 if(isalpha(endTags[i])){

				ip.ki.wVk = VK_SHIFT; 
				ip.ki.dwFlags = 0; //0 for key press
				SendInput(1, &ip, sizeof(INPUT));
			
				ip.ki.wVk = endTags[i]; 
				ip.ki.dwFlags = 0; //0 for key press
				SendInput(1, &ip, sizeof(INPUT));
			
				ip.ki.wVk = endTags[i]; 
				ip.ki.dwFlags = KEYEVENTF_KEYUP; 
				SendInput(1, &ip, sizeof(INPUT));
			
				ip.ki.wVk = VK_SHIFT; 
				ip.ki.dwFlags = KEYEVENTF_KEYUP; 
				SendInput(1, &ip, sizeof(INPUT));

			 }
			 else if(endTags[i] == '<'){
				ip.ki.wVk = VK_SHIFT; 
				ip.ki.dwFlags = 0; //0 for key press
				SendInput(1, &ip, sizeof(INPUT));
			
				ip.ki.wVk = VK_OEM_COMMA; 
				ip.ki.dwFlags = 0; //0 for key press
				SendInput(1, &ip, sizeof(INPUT));
			
				ip.ki.wVk = VK_OEM_COMMA; 
				ip.ki.dwFlags = KEYEVENTF_KEYUP; 
				SendInput(1, &ip, sizeof(INPUT));
			
				ip.ki.wVk = VK_SHIFT; 
				ip.ki.dwFlags = KEYEVENTF_KEYUP; 
				SendInput(1, &ip, sizeof(INPUT));
			}
			else if(endTags[i] == '>'){
				ip.ki.wVk = VK_SHIFT; 
				ip.ki.dwFlags = 0; //0 for key press
				SendInput(1, &ip, sizeof(INPUT));
			
				ip.ki.wVk = VK_OEM_PERIOD; 
				ip.ki.dwFlags = 0; //0 for key press
				SendInput(1, &ip, sizeof(INPUT));
			
				ip.ki.wVk = VK_OEM_PERIOD; 
				ip.ki.dwFlags = KEYEVENTF_KEYUP; 
				SendInput(1, &ip, sizeof(INPUT));
			
				ip.ki.wVk = VK_SHIFT; 
				ip.ki.dwFlags = KEYEVENTF_KEYUP; 
				SendInput(1, &ip, sizeof(INPUT));
			}
			 else if(endTags[i] == '/'){
			
				ip.ki.wVk = VK_DIVIDE; 
				ip.ki.dwFlags = 0; //0 for key press
				SendInput(1, &ip, sizeof(INPUT));
			
				ip.ki.wVk = VK_DIVIDE; 
				ip.ki.dwFlags = KEYEVENTF_KEYUP; 
				SendInput(1, &ip, sizeof(INPUT));

			}
			else{
				//displays all other characters besides alphas and >

				ip.ki.wVk = endTags[i]; 
				ip.ki.dwFlags = 0; //0 for key press
				SendInput(1, &ip, sizeof(INPUT));
			
				ip.ki.wVk = endTags[i]; 
				ip.ki.dwFlags = KEYEVENTF_KEYUP; 
				SendInput(1, &ip, sizeof(INPUT));

			 }
		
		 }

		//send an enter
	
		ip.ki.wVk = VK_RETURN; 
		ip.ki.dwFlags = 0; //0 for key press
		SendInput(1, &ip, sizeof(INPUT));
			
		ip.ki.wVk = VK_RETURN; 
		ip.ki.dwFlags = KEYEVENTF_KEYUP; 
		SendInput(1, &ip, sizeof(INPUT));
	
		return 0;
	}

}

