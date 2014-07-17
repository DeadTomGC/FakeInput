#import time
#import os
import sys
import ctypes
lib=ctypes.CDLL('FakeInputWin')
             
#message passed to this should be the correct key code


def speak(key):
    #time.sleep(3) #3 second delay
    if(key in phrases):
        lib.typeInBaldi(phrases[key])
        #os.system('TestFakeInputWin "' + phrases[key] + '"')
    
def addPhrase(key, phrase):
    phrases[key] = phrase
 
                
phrases = {"right": "I am moving to your right"}
phrases["left"] = "I am moving to your left"
phrases["hello"] = "Hello there"
phrases["queryUser"] = "What would you like me to do"
phrases["bye"] = "Good bye"

#while True:
    #read message
    #message = sys.stdin.readline()
    
    #action
    #if message in phrases:
        #speak(message)
speak("right")   
    #sleep to end of time
    