from selenium import webdriver
import sys


reload(sys) 
sys.setdefaultencoding('utf-8') 

browser = webdriver.Chrome()
browser.get('http://www.lydsy.com/JudgeOnline/loginpage.php')
username = browser.find_element_by_xpath("//input[@name='user_id']")
username.clear()
username.send_keys("I_Love_CA")
password = browser.find_element_by_xpath("//input[@name='password']")
password.clear()
password.send_keys("2333333")
browser.find_element_by_xpath("//input[@name='submit']").click()


for i in range(1000, 5000):
    out = '%d' %i
    url = "http://www.lydsy.com/JudgeOnline/problem.php?id=" + out
    outt = out + ".html"
    output = open(outt, "w")
    browser.get(url)
    output.write(browser.page_source)
    output.close()
    print i

# http://creativecommons.org/licenses/by-nc-sa/4.0/
