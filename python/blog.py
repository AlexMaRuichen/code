import webbrowser as web  
import time  
import os  
  
cnt = 1  
while 1:
	while cnt <= 9:  
		web.open_new_tab('http://blog.csdn.net/make_it_for_good/article/details/52584916');
		cnt += 1  
		time.sleep(1)  
	else:  
		os.system('killall chrome')
		cnt=0  
