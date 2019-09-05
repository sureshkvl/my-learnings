Robot Framework - Begineers Guide
=================================

Contents:
----
1. Introduction

	a. What is Robotframework
	
	b. Features 
	
	c. How to install
	
2. Writing the Test case

	a. Test case format
	
	b. Simple Test cases
	
	c. UI Test cases (Selenium)
	
	d. REST API Test cases
	
	e. others

3. Execute the Test Cases 

	a. Simple
	
	b. TAG 
	
	c. Suite
	
4. Advanced Features


1.Introduction
----

***a.What is Robotframework***

	It is a Generic Test Automation Framework.  It uses  Keyword Driven testing methodology.
	Released as Opensource (Apache Licence), Supported by Nokia Siemens.

	Test case can be written in PLAIN TEXT format.  

	Example:
	
	```
	Open a Browser
	Click Register Button
	```

***b.Features***

	From the Tester perspective,

	a. Excellent Test Report in HTML Format.
	b. Detailled Logging is supported (Execution Time can be measured)
	c. Easy to Write the test case  (Plain Text Model)
	d. Supports many inbuild libary (String, OS, etc)
	d. Supports third party library (Seleinum, REST API, SSH)
	f. Support of Executing the full set or sub set of the test cases.
	g. No need to Learn another Scripting language.

***c.How To Install***

In ubuntu 14.04 Desktop,
	
	sudo apt-get install python-pip
	
	sudo pip install robotframewok
	
Install the required third party library, such as 
	
	sudo pip install robotframework-selenium2library

Verify the installation

	$ pybot --version



2. Writing the Test case
-----
***a. Test case format***

GuideLines:

  1. Test cases are  written in a tabular format. 

  2.'#' is used to comment a Line

  3.Test case consists of multiple sections, such as "Settings","Variables","Keywords","Test Cases". 

	```
	Settings -   used as Global settings such as Loading the library.
	Variables -  used to declare the variables
	Keywords -   place for defining the custom keywords 
	Test Cases - test case which is getting executed by the user.
	```

  4.Each Section Line will begin with *** and end with  ***

  5.Varibles will be declared and used in ${variable_name} format.

  6.
   In the below example, Seleinum Library is used in this example
   The following actions are performed.
	   1.  Run the Firefox Browser
	   2.  Open the Rediff.Com page.
	
	```
	*** Settings ***
	Library           Selenium2Library
	
	*** Variables ***
	${URL}		Rediff.com
	${BROWSER}	Firefox


	*** Keywords ***
	Open Browser To Login Page
		Open Browser   ${URL}		${BROWSER}

	*** Test Cases ***
	Test Case 1
		Open Browser To Login Page
	```

	save the above test cases in text format, and run as below

	pybot test1.txt
	Note : This example is present in the examples folder (File name : test1.txt)


***b. Simple Test cases***

In this section, we will write simple testcases to demonstrate the  Robot framework inbuild library functionlities.

Robots standard library includes the followng,
	Builtin,Collections,String, Telnet,OperatingSystem, Dialogs, Process, DateTime,etc.


Example2:


In this below example, we will demonstrate the  'variable assignement', 'argument passing',and 'return value'

```
*** Settings ***


*** Variables ***
${var1}		10
${var2}		20

*** Keywords ***
Add Example
	[Arguments]    ${element1}    ${element2}
	${result}=   Evaluate   ${element1}+${element2}
	Return from Keyword    ${result}


*** Test Cases ***
Test2 Return Example
	${result}=   Add Example  ${var1}   ${var2}
	Log  ${result}
```

Execution:

pybot test2.txt

Note : This example is present in the examples folder (File name : test1.txt)





Example3:


In this below example, we will demonstrate the  'get the value of the variable '.

${var3}=  ${var2} --- This syntax is  not allowed in Robot framework, instead of 
we should use  as below,
${var3}=  Get Variable Value   ${var2}


```
*** Settings ***


*** Variables ***
${var1}		10
${var2}		20

*** Keywords ***

*** Test Cases ***
Test3 Copy Example
	Log   ${var1}
	Log   ${var2}
	${var3}=   Get Variable Value
	Log   ${var3}
```

Execution:

pybot test3.txt

Note : This example is present in the examples folder (File name : test3.txt)


Example4:
In this below example we will demostrate the List(Array) operations

```
*** Settings ***
*** Variables ***
*** Keywords ***
*** Test Cases ***
List Example
	@{list1}=	Create list 	1	2	3	4
	Append To list 	 	${list1}   5
	@{list2}	Create List     a  b  c  d
	${list3}=	Combine Lists	${list1}	${list2}

	${temp}=   Get From List   ${list3}   0
	${index}=	Get Index From List  ${list3}  5
	Log  ${temp}
	Log  ${index}
```

Execution:

pybot test4.txt

Note : This example is present in the examples folder (File name : test4.txt)



Example4:
In this below example we will demostrate the For Loop operations

```
*** Settings ***
*** Variables ***
*** Keywords ***
*** Test Cases ***
For Loop Example
	@{VALUES}=   Create list 		Test1   Test2     Test3    CONTINUE   Test4    Exit     Test5
	:FOR  ${var}   in   @{VALUES}
	\    Continue For Loop If    '${var}' == 'CONTINUE'
	\	 Run Keyword If		'${var}' == 'EXIT'   Exit For Loop
	\	 Log  ${var}
```

Execution:

pybot test5.txt

Note : This example is present in the examples folder (File name : test5.txt)
















