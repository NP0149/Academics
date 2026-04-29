//Lab 1. Virtual box installation and adding flavours like vanilladpup,core,react os
->virtual box is a open source software and powerful for home and enterprise use.
->It is used to run more than one os at a time
->Go to Browser and type  virtual box and click on oracle Vm virtual box and download the virtual box for your pc(linux)[install .deb file]
->now install it in ubuntu by using the command:
>>sudo dpkg -i ~Downloads/virtualbox-7.1.deb
>>sudo apt -f install
and after that launch virtual box 
->Now download iso files of different flavours from their official website(reactos,coreplus,vanilladpup)
-> Now go to virtual box 
	->Click New
	->Name:Vanilladpup
	->Type:Linux
	->Version:Debian(32 bit)
	->4000MB
	->cpu:2
	and click on finish
->Now go to  settings->storage
in empty->replace it with vanilladpup.iso file by browsing it from files and enter ok
->Now start the virtual machine with falvour vanilladpup 
->The similar process will be followed for both react os and coreplus
->Virtual box is mainly used to run multiple os in single physical machine at a time



//Lab 2.Install a c/java compiler in VM created using virtual box and execute simple programs
->Open Virtual box and start react os 
->wait until the react os desktop loads
->now go to programs->accessories->Notepad
->Write a sample java/c program
	#include<stdio.h>
	 void main()
	 {
	 printf("Hello");
	 }
->Now save it with hello
->Again rename it as hello.c(as it is saved automatically as hello.txt)
->Now go to application manager
->Search for gcc (TDM-gcc)
->double click on that for installation and install the gcc compiler
-> Now go to command prompt
>>gcc --version(to check if it is installed or not)
>>gcc hello.c -o hello && hello
->The output will be displayed in command prompt

->for java:->
	public class hello{
	 public static void main(String [] args)
	 {
	  System.out.println("Hello");
	 }
	}
save it as code.java
->Now go to application manager
->search for jdk and install the package which comes first
->Now go to commands prompt
>> javac code.java
>> java code
->The output will be displayed in command prompt



//3.Install web server and setup reverse proxy with NGINX to python flask backend,nodejs backend
1.Install NGINIX
>>sudo apt update
>>sudo apt install nginx
>>sudo systemctl status nginx

2.Install python flask
>>sudo apt install python3 python3-pip -y
>>pip install flask
>>python3 -m venv venv
>>source venv/bin/activate
->Create a app.py file
	from flask import flask
	app=Flask(__name__)
	@app.route("/")
	def hello():
	 return "Hello From Flask"
	if __name__=="__main__"
	  app.run(host='127.0.0.1',port=5000)
	
3.Install node and express
>>sudo apt install nodejs npm -y
>>npm init -y
>>npm install express
->Create a index.js file
	const express=require("express");
	const app=express();
	const port=3000;
	app.get('/',(req,res)=>{
		res.send("Hello Express");
		});
->Now open one terminal and run
>>python3 app.py
>>go to web browser and type http://localhost/5000 (Hello from flask will be displayed)
>>go to another new terminal and run
>>node index.js
>>go to web browser new tab and type http://localhost/3000 (Hello express will be displayed)
4.Configure NGINX reverse proxy
>>sudo nano /etc/nginx/sites-available/default
->Replace content with this:
	server {
	listen:80;
	server_name localhost;
	
	location /flask/{
	proxy_pass http://127.0.0.1:5000/;
	proxy_set_header Host $host;
	proxy_set_header X-Real-IP $remote_addr;
	}
	
	location /node/{
	proxy_pass http://127.0.0.1:3000/;
	proxy_set_header Host $host;
	proxy_set_header X-Real-IP $remote_addr;
	}
	}
->Save and exit(ctrl+o and ctrl+x)
->In terminal
>>sudo nginx -t
>>sudo systemctl restart nginx

->Now open in browser
http://localhost/flask/->"Hello from flask"
http://localhost/node/->"Hello express"
Both backends are running behind nginx as a reverse proxy.



//4.Installation of Eclipse and simulating cloudsim scenario
->Open https://www/eclipse.org/downloads/packages
->download Linux x84-64/Arch64/risc v64
->Now open terminal
>>cd Downloads
>>tar -xvf eclipse
>>cd eclipse -installer
>> ./eclipse -inst
>>Download eclipse JDE for java developers 2025-26
>>Install and launch it
->Open github.com/cloudslab/cloudsim/releases
->Downlaod cloudsim 5.0 Zip and cloudsim 7.0.1 zip
>>Extract Zip files
>>Import in eclipse app 
>>Run any of the sample example code
1.Addition
		package org.cloudbus.cloudsim.examples;

		import java.util.ArrayList;
		import java.util.Calendar;
		import java.util.List;

		import org.cloudbus.cloudsim.Cloudlet;
		import org.cloudbus.cloudsim.CloudletSchedulerTimeShared;
		import org.cloudbus.cloudsim.Datacenter;
		import org.cloudbus.cloudsim.DatacenterBroker;
		import org.cloudbus.cloudsim.DatacenterCharacteristics;
		import org.cloudbus.cloudsim.Host;
		import org.cloudbus.cloudsim.Pe;
		import org.cloudbus.cloudsim.Storage;
		import org.cloudbus.cloudsim.UtilizationModelFull;
		import org.cloudbus.cloudsim.Vm;
		import org.cloudbus.cloudsim.VmAllocationPolicySimple;
		import org.cloudbus.cloudsim.VmSchedulerTimeShared;
		import org.cloudbus.cloudsim.core.CloudSim;
		import org.cloudbus.cloudsim.provisioners.BwProvisionerSimple;
		import org.cloudbus.cloudsim.provisioners.PeProvisionerSimple;
		import org.cloudbus.cloudsim.provisioners.RamProvisionerSimple;

		public class CloudSimSimpleAddition {
		    public static void main(String[] args) {
			try {
			    // 1. Initialize CloudSim
			    int num_user = 1;
			    Calendar calendar = Calendar.getInstance();
			    boolean trace_flag = false;
			    CloudSim.init(num_user, calendar, trace_flag);

			    // 2. Create Datacenter
			    Datacenter datacenter = createDatacenter("Datacenter_0");

			    // 3. Create Broker
			    DatacenterBroker broker = createBroker();
			    int brokerId = broker.getId();

			    // 4. Create one VM
			    List<Vm> vmlist = new ArrayList<>();
			    Vm vm = new Vm(
				0, brokerId, 1000, 1, 512, 1000, 10000,
				"Xen", new CloudletSchedulerTimeShared()
			    );
			    vmlist.add(vm);
			    broker.submitVmList(vmlist);

			    // 5. Create Cloudlets representing numbers
			    List<Cloudlet> cloudletList = new ArrayList<>();
			    long[] numbers = { 10, 20, 30, 40, 50, 60 };

			    for (int i = 0; i < numbers.length; i++) {
				Cloudlet cloudlet = new Cloudlet(
				    i, numbers[i], 1, 300, 300,
				    new UtilizationModelFull(),
				    new UtilizationModelFull(),
				    new UtilizationModelFull()
				);
				cloudlet.setUserId(brokerId);
				cloudlet.setVmId(0);
				cloudletList.add(cloudlet);
			    }

			    // Print numbers before addition
			    System.out.println("Numbers for addition:");
			    for (Cloudlet c : cloudletList) {
				System.out.print(c.getCloudletLength() + " ");
			    }

			    // 6. Perform Addition
			    long sum = 0;
			    for (Cloudlet c : cloudletList) {
				sum += c.getCloudletLength();
			    }

			    System.out.println("\n\nSum of numbers = " + sum);

			    // Optional: Submit and simulate
			    broker.submitCloudletList(cloudletList);
			    CloudSim.startSimulation();
			    CloudSim.stopSimulation();

			} catch (Exception e) {
			    e.printStackTrace();
			}
		    }

		    // ---------- Helper Methods ----------
		    private static Datacenter createDatacenter(String name) {
			List<Host> hostList = new ArrayList<>();
			List<Pe> peList = new ArrayList<>();

			peList.add(new Pe(0, new PeProvisionerSimple(1000)));
			hostList.add(new Host(
			    0,
			    new RamProvisionerSimple(2048),
			    new BwProvisionerSimple(10000),
			    1000000,
			    peList,
			    new VmSchedulerTimeShared(peList)
			));

			DatacenterCharacteristics characteristics = new DatacenterCharacteristics(
			    "x86", "Linux", "Xen", hostList,
			    10.0, 3.0, 0.05, 0.001, 0.0
			);

			Datacenter datacenter = null;
			try {
			    datacenter = new Datacenter(
				name,
				characteristics,
				new VmAllocationPolicySimple(hostList),
				new java.util.LinkedList<Storage>(),
				0
			    );
			} catch (Exception e) {
			    e.printStackTrace();
			}

			return datacenter;
		    }

		    private static DatacenterBroker createBroker() {
			DatacenterBroker broker = null;
			try {
			    broker = new DatacenterBroker("Broker");
			} catch (Exception e) {
			    e.printStackTrace();
			}
			return broker;
		    }
		}
2.Sorting
		package org.cloudbus.cloudsim.examples;

		import java.util.ArrayList;
		import java.util.Calendar;
		import java.util.Collections;
		import java.util.List;

		import org.cloudbus.cloudsim.Cloudlet;
		import org.cloudbus.cloudsim.CloudletSchedulerTimeShared;
		import org.cloudbus.cloudsim.Datacenter;
		import org.cloudbus.cloudsim.DatacenterBroker;
		import org.cloudbus.cloudsim.DatacenterCharacteristics;
		import org.cloudbus.cloudsim.Host;
		import org.cloudbus.cloudsim.Pe;
		import org.cloudbus.cloudsim.Storage;
		import org.cloudbus.cloudsim.UtilizationModelFull;
		import org.cloudbus.cloudsim.Vm;
		import org.cloudbus.cloudsim.VmAllocationPolicySimple;
		import org.cloudbus.cloudsim.VmSchedulerTimeShared;
		import org.cloudbus.cloudsim.core.CloudSim;
		import org.cloudbus.cloudsim.provisioners.BwProvisionerSimple;
		import org.cloudbus.cloudsim.provisioners.PeProvisionerSimple;
		import org.cloudbus.cloudsim.provisioners.RamProvisionerSimple;

		public class CloudSimSimpleSorting {
		    public static void main(String[] args) {
			try {
			    // 1. Initialize CloudSim
			    int num_user = 1;
			    Calendar calendar = Calendar.getInstance();
			    boolean trace_flag = false;
			    CloudSim.init(num_user, calendar, trace_flag);

			    // 2. Create Datacenter
			    Datacenter datacenter = createDatacenter("Datacenter_0");

			    // 3. Create Broker
			    DatacenterBroker broker = createBroker();
			    int brokerId = broker.getId();

			    // 4. Create one VM
			    List<Vm> vmlist = new ArrayList<>();
			    Vm vm = new Vm(
				0, brokerId, 1000, 1, 512, 1000, 10000,
				"Xen", new CloudletSchedulerTimeShared()
			    );
			    vmlist.add(vm);
			    broker.submitVmList(vmlist);

			    // 5. Create Cloudlets representing numbers
			    List<Cloudlet> cloudletList = new ArrayList<>();
			    long[] numbers = { 42, 7, 19, 3, 88, 21 };

			    for (int i = 0; i < numbers.length; i++) {
				Cloudlet cloudlet = new Cloudlet(
				    i, numbers[i], 1, 300, 300,
				    new UtilizationModelFull(),
				    new UtilizationModelFull(),
				    new UtilizationModelFull()
				);
				cloudlet.setUserId(brokerId);
				cloudlet.setVmId(0);
				cloudletList.add(cloudlet);
			    }

			    // Print numbers before sorting
			    System.out.println("Numbers before sorting:");
			    for (Cloudlet c : cloudletList) {
				System.out.print(c.getCloudletLength() + " ");
			    }

			    // 6. Sort numbers in ascending order
			    Collections.sort(cloudletList, (c1, c2) ->
				Long.compare(c1.getCloudletLength(), c2.getCloudletLength())
			    );

			    // Print numbers after sorting
			    System.out.println("\n\nNumbers after sorting:");
			    for (Cloudlet c : cloudletList) {
				System.out.print(c.getCloudletLength() + " ");
			    }

			    // Optional: Run simulation
			    broker.submitCloudletList(cloudletList);
			    CloudSim.startSimulation();
			    CloudSim.stopSimulation();

			} catch (Exception e) {
			    e.printStackTrace();
			}
		    }

		    // ---------- Helper Methods ----------
		    private static Datacenter createDatacenter(String name) {
			List<Host> hostList = new ArrayList<>();
			List<Pe> peList = new ArrayList<>();

			peList.add(new Pe(0, new PeProvisionerSimple(1000)));
			hostList.add(new Host(
			    0,
			    new RamProvisionerSimple(2048),
			    new BwProvisionerSimple(10000),
			    1000000,
			    peList,
			    new VmSchedulerTimeShared(peList)
			));

			DatacenterCharacteristics characteristics = new DatacenterCharacteristics(
			    "x86", "Linux", "Xen", hostList,
			    10.0, 3.0, 0.05, 0.001, 0.0
			);

			Datacenter datacenter = null;
			try {
			    datacenter = new Datacenter(
				name,
				characteristics,
				new VmAllocationPolicySimple(hostList),
				new java.util.LinkedList<Storage>(),
				0
			    );
			} catch (Exception e) {
			    e.printStackTrace();
			}

			return datacenter;
		    }

		    private static DatacenterBroker createBroker() {
			DatacenterBroker broker = null;
			try {
			    broker = new DatacenterBroker("Broker");
			} catch (Exception e) {
			    e.printStackTrace();
			}
			return broker;
		    }
		}
3.subtraction
		package org.cloudbus.cloudsim.examples;

		import java.util.ArrayList;
		import java.util.Calendar;
		import java.util.List;

		import org.cloudbus.cloudsim.Cloudlet;
		import org.cloudbus.cloudsim.CloudletSchedulerTimeShared;
		import org.cloudbus.cloudsim.Datacenter;
		import org.cloudbus.cloudsim.DatacenterBroker;
		import org.cloudbus.cloudsim.DatacenterCharacteristics;
		import org.cloudbus.cloudsim.Host;
		import org.cloudbus.cloudsim.Pe;
		import org.cloudbus.cloudsim.Storage;
		import org.cloudbus.cloudsim.UtilizationModelFull;
		import org.cloudbus.cloudsim.Vm;
		import org.cloudbus.cloudsim.VmAllocationPolicySimple;
		import org.cloudbus.cloudsim.VmSchedulerTimeShared;
		import org.cloudbus.cloudsim.core.CloudSim;
		import org.cloudbus.cloudsim.provisioners.BwProvisionerSimple;
		import org.cloudbus.cloudsim.provisioners.PeProvisionerSimple;
		import org.cloudbus.cloudsim.provisioners.RamProvisionerSimple;

		public class CloudSimSimpleSubtraction {

		    public static void main(String[] args) {
			try {
			    // 1. Initialize CloudSim
			    int num_user = 1; // number of users
			    Calendar calendar = Calendar.getInstance();
			    boolean trace_flag = false; // mean trace events
			    CloudSim.init(num_user, calendar, trace_flag);

			    // 2. Create Datacenter
			    Datacenter datacenter = createDatacenter("Datacenter_0");

			    // 3. Create Broker
			    DatacenterBroker broker = createBroker();
			    int brokerId = broker.getId();

			    // 4. Create VM list
			    List<Vm> vmlist = new ArrayList<>();
			    Vm vm = new Vm(0, brokerId, 1000, 1, 512, 1000, 10000,
				    "Xen", new CloudletSchedulerTimeShared());
			    vmlist.add(vm);
			    broker.submitVmList(vmlist);

			    // 5. Perform subtraction operation
			    int num1 = 50;
			    int num2 = 25;
			    int result = num1 - num2;

			    System.out.println("========= CloudSim Subtraction Example =========");
			    System.out.println("Number 1: " + num1);
			    System.out.println("Number 2: " + num2);
			    System.out.println("Subtraction (num1 - num2) = " + result);

			    // 6. Create Cloudlet list (optional just for structure)
			    List<Cloudlet> cloudletList = new ArrayList<>();
			    Cloudlet cloudlet = new Cloudlet(0, 4000, 1, 300, 300,
				    new UtilizationModelFull(),
				    new UtilizationModelFull(),
				    new UtilizationModelFull());
			    cloudlet.setUserId(brokerId);
			    cloudlet.setVmId(0);
			    cloudletList.add(cloudlet);

			    broker.submitCloudletList(cloudletList);

			    // 7. Start Simulation
			    CloudSim.startSimulation();
			    CloudSim.stopSimulation();

			    System.out.println("===============================================");
			    System.out.println("CloudSim Subtraction Example Finished!");
			} catch (Exception e) {
			    e.printStackTrace();
			}
		    }

		    // ---------- Helper Methods ----------
		    private static Datacenter createDatacenter(String name) {
			List<Host> hostList = new ArrayList<>();
			List<Pe> peList = new ArrayList<>();

			peList.add(new Pe(0, new PeProvisionerSimple(1000))); // CPU with 1000 MIPS
			hostList.add(new Host(0,
				new RamProvisionerSimple(2048),
				new BwProvisionerSimple(10000),
				1000000,
				peList,
				new VmSchedulerTimeShared(peList)));

			DatacenterCharacteristics characteristics = new DatacenterCharacteristics(
				"x86", "Linux", "Xen", hostList,
				10.0, 3.0, 0.05, 0.001, 0.0);

			Datacenter datacenter = null;
			try {
			    datacenter = new Datacenter(
				    name,
				    characteristics,
				    new VmAllocationPolicySimple(hostList),
				    new java.util.LinkedList<Storage>(),
				    0);
			} catch (Exception e) {
			    e.printStackTrace();
			}
			return datacenter;
		    }

		    private static DatacenterBroker createBroker() {
			DatacenterBroker broker = null;
			try {
			    broker = new DatacenterBroker("Broker");
			} catch (Exception e) {
			    e.printStackTrace();
			}
			return broker;
		    }
		}
4.Multiplication
		package org.cloudbus.cloudsim.examples;

		import java.util.ArrayList;
		import java.util.Calendar;
		import java.util.List;

		import org.cloudbus.cloudsim.*;
		import org.cloudbus.cloudsim.core.CloudSim;
		import org.cloudbus.cloudsim.provisioners.*;

		public class CloudSimSimpleMultiplication {

		    public static void main(String[] args) {
			try {
			    // 1. Initialize CloudSim
			    int numUser = 1;
			    Calendar calendar = Calendar.getInstance();
			    boolean traceFlag = false;
			    CloudSim.init(numUser, calendar, traceFlag);

			    // 2. Create Datacenter
			    Datacenter datacenter = createDatacenter("Datacenter_0");

			    // 3. Create Broker
			    DatacenterBroker broker = createBroker();
			    int brokerId = broker.getId();

			    // 4. Create one VM
			    List<Vm> vmlist = new ArrayList<>();
			    Vm vm = new Vm(
				    0, brokerId, 1000, 1, 512, 1000, 10000,
				    "Xen", new CloudletSchedulerTimeShared()
			    );
			    vmlist.add(vm);
			    broker.submitVmList(vmlist);

			    // 5. Numbers to multiply
			    int num1 = 12;
			    int num2 = 7;
			    int result = num1 * num2;

			    System.out.println("First number: " + num1);
			    System.out.println("Second number: " + num2);
			    System.out.println("Result of multiplication: " + result);

			    // 6. Run the simulation (optional)
			    CloudSim.startSimulation();
			    CloudSim.stopSimulation();

			} catch (Exception e) {
			    e.printStackTrace();
			}
		    }

		    // ------------------------ Helper Methods ------------------------

		    private static Datacenter createDatacenter(String name) {
			List<Host> hostList = new ArrayList<>();
			List<Pe> peList = new ArrayList<>();

			peList.add(new Pe(0, new PeProvisionerSimple(1000)));
			hostList.add(new Host(
				0,
				new RamProvisionerSimple(2048),
				new BwProvisionerSimple(10000),
				1000000,
				peList,
				new VmSchedulerTimeShared(peList)
			));

			DatacenterCharacteristics characteristics = new DatacenterCharacteristics(
				"x86", "Linux", "Xen", hostList, 10.0,
				3.0, 0.05, 0.001, 0.0
			);

			Datacenter datacenter = null;
			try {
			    datacenter = new Datacenter(
				    name, characteristics,
				    new VmAllocationPolicySimple(hostList),
				    new ArrayList<Storage>(), 0
			    );
			} catch (Exception e) {
			    e.printStackTrace();
			}

			return datacenter;
		    }

		    private static DatacenterBroker createBroker() {
			DatacenterBroker broker = null;
			try {
			    broker = new DatacenterBroker("Broker");
			} catch (Exception e) {
			    e.printStackTrace();
			}
			return broker;
		    }
		}
5.Division
		package org.cloudbus.cloudsim.examples;

		import java.util.ArrayList;
		import java.util.Calendar;
		import java.util.List;

		import org.cloudbus.cloudsim.*;
		import org.cloudbus.cloudsim.core.CloudSim;
		import org.cloudbus.cloudsim.provisioners.*;

		public class CloudSimSimpleDivision {

		    public static void main(String[] args) {
			try {
			    // 1. Initialize CloudSim
			    int numUser = 1;
			    Calendar calendar = Calendar.getInstance();
			    boolean traceFlag = false;
			    CloudSim.init(numUser, calendar, traceFlag);

			    // 2. Create Datacenter
			    Datacenter datacenter = createDatacenter("Datacenter_0");

			    // 3. Create Broker
			    DatacenterBroker broker = createBroker();
			    int brokerId = broker.getId();

			    // 4. Create one VM
			    List<Vm> vmlist = new ArrayList<>();
			    Vm vm = new Vm(
				    0, brokerId, 1000, 1, 512, 1000, 10000,
				    "Xen", new CloudletSchedulerTimeShared()
			    );
			    vmlist.add(vm);
			    broker.submitVmList(vmlist);

			    // 5. Numbers for division
			    double num1 = 56;
			    double num2 = 8;

			    System.out.println("First number: " + num1);
			    System.out.println("Second number: " + num2);

			    if (num2 != 0) {
				double result = num1 / num2;
				System.out.println("Result of division: " + result);
			    } else {
				System.out.println("Error: Division by zero is not allowed!");
			    }

			    // 6. Run simulation (optional)
			    CloudSim.startSimulation();
			    CloudSim.stopSimulation();

			} catch (Exception e) {
			    e.printStackTrace();
			}
		    }

		    // ------------------------ Helper Methods ------------------------

		    private static Datacenter createDatacenter(String name) {
			List<Host> hostList = new ArrayList<>();
			List<Pe> peList = new ArrayList<>();

			peList.add(new Pe(0, new PeProvisionerSimple(1000)));
			hostList.add(new Host(
				0,
				new RamProvisionerSimple(2048),
				new BwProvisionerSimple(10000),
				1000000,
				peList,
				new VmSchedulerTimeShared(peList)
			));

			DatacenterCharacteristics characteristics = new DatacenterCharacteristics(
				"x86", "Linux", "Xen", hostList, 10.0,
				3.0, 0.05, 0.001, 0.0
			);

			Datacenter datacenter = null;
			try {
			    datacenter = new Datacenter(
				    name, characteristics,
				    new VmAllocationPolicySimple(hostList),
				    new ArrayList<Storage>(), 0
			    );
			} catch (Exception e) {
			    e.printStackTrace();
			}

			return datacenter;
		    }

		    private static DatacenterBroker createBroker() {
			DatacenterBroker broker = null;
			try {
			    broker = new DatacenterBroker("Broker");
			} catch (Exception e) {
			    e.printStackTrace();
			}
			return broker;
		    }
		}

->Run this codes in eclipse such that the output will be displayed.


//5.File transfering from one virtual machine to another virtual machine
->Lets tranfer files from coreplus to vanilladpup
First start both machines in 2 tabs simultaneously
In Vanilladpup
->Go to command prompt
>>ifconfig

In Coreplus
->Go to command prompt
>>ifconfig

If both the ip adresses are same (Now follow the process)
->Go to settings->Network and set Host-only-adapter for both vanilla and core and restart machines
In vanilladpup(change ip to 192.168.56.101)
>>sudo ifconfig eth0 192.168.56.101 netmask 255.255.255.0 up
In coreplus(change ip to 192.168.56.102)
>>sudo ifconfig eth0 192.168.56.102 netmask 255.255.255.0 up

Now the ip adresses of both are changed

In coreplus
>>ping 192.168.56.101
In Vanilladpup
>>ping 192.168.56.102
 check there is a connection between 2 machines. and press ctrl+c in both vm's
 
 In coreplus
 >>echo "Hello Varshini" >app.txt (creating a file with data)
 >>ls (to check the file is created or not)
 >>nc 192.168.56.101 1234<app.txt (core is ready to send file)
 
 In vanilla
 >>nc -l -p 1234 >received_app.txt(vanilla is ready to receive)
 
 In coreplus again enter
 >>nc 192.168.56.101 1234<app.txt
 
 >>In vanilladpup 
 Open a new terminal
 >>cat received_app.txt 
 The content will be displayed in vanilladpup
 Therefore app.txt is transfered from core to vanilladpup.
 
 //6.Refer observation for create and deploy hello world application on google cloud

 sudo ip address add 192.168.56.1/24 dev enp0s3

tar -czvf foldername.tar.gz foldername
tar -xzvf foldername.tar.gz for uncompressing


FIBONACCI NUMBER
n = int(input("Enter number of terms: "))

a, b = 0, 1

if n <= 0:
    print("Please enter a positive number")
else:
    print("Fibonacci Series:", end=" ")
    for i in range(n):
        print(a, end=" ")
        a, b = b, a + b

PALINDROME NUMBER

import string

def is_palindrome(text):
    # Convert to lowercase
    text = text.lower()
    
    # Remove spaces and punctuation
    text = ''.join(char for char in text if char.isalnum())
    
    # Check palindrome
    return text == text[::-1]

# Main program
user_input = input("Enter a word, number, or sentence: ")

if is_palindrome(user_input):
    print("It is a Palindrome")
else:
    print("It is NOT a Palindrome")

FACTORIAL

num = int(input("Enter a number: "))

fact = 1

if num < 0:
    print("Factorial does not exist for negative numbers")
elif num == 0:
    print("Factorial of 0 is 1")
else:
    for i in range(1, num + 1):
        fact *= i
    print("Factorial of", num, "is", fact)



PRIME NUMBER

def is_prime(num):
    if num <= 1:
        return False
    for i in range(2, int(num**0.5) + 1):
        if num % i == 0:
            return False
    return True

num = int(input("Enter a number: "))

if is_prime(num):
    print(num, "is a Prime number")
else:
    print(num, "is NOT a Prime number")

PRIME NUMBER IN RANGE

start = int(input("Enter start of range: "))
end = int(input("Enter end of range: "))

print("Prime numbers between", start, "and", end, "are:")

for num in range(start, end + 1):
    if num > 1:  # Prime numbers are greater than 1
        for i in range(2, int(num**0.5) + 1):
            if num % i == 0:
                break
        else:
            print(num, end=" ")
ARMSTRONG

num = int(input("Enter a number: "))

# Convert number to string to count digits
power = len(str(num))

sum_of_digits = 0
temp = num

while temp > 0:
    digit = temp % 10
    sum_of_digits += digit ** power
    temp //= 10

if sum_of_digits == num:
    print(num, "is an Armstrong number")
else:
    print(num, "is NOT an Armstrong number")

REVERSE NUMBER

num = int(input("Enter a number: "))
rev = 0

while num > 0:
    digit = num % 10
    rev = rev * 10 + digit
    num //= 10

print("Reversed Number:", rev)


mv file1 file2 file3 destination_folder/
📝 Summary (Very Clean)
Task	Command
Create mount folder	sudo mkdir /mnt/share
Mount shared folder	sudo mount -t vboxsf VM_Shared /mnt/share
Check files	ls /mnt/share







