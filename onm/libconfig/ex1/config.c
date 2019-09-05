/*config.c*/
/*
To compile : gcc -o config config.c -lconfig
To run     : ./config
*/

#include "config.h"
#include <libconfig.h>
#include <stdio.h>

//Global parameters
char filename[12]="config.txt";
config_t cfg;
config_setting_t *setting;
//

void setGlobalConfig(global_config_t *t)
{
	setting=config_lookup(&cfg,"global_config.name");
	config_setting_set_string(setting,"newname");
	setting=config_lookup(&cfg,"global_config.location");
	config_setting_set_string(setting,"newlocation");
	setting=config_lookup(&cfg,"global_config.para1");
	config_setting_set_int(setting,t->para1);
	setting=config_lookup(&cfg,"global_config.para2");
	config_setting_set_int(setting,t->para2);
	setting=config_lookup(&cfg,"global_config.para3");
	config_setting_set_int(setting,t->para3);
	setting=config_lookup(&cfg,"global_config.timers");
	int i=0;
	for (i=0;i<4;i++)
	{
		config_setting_set_int_elem(setting,i,t->timers[i]);				
	}	
}
void populateGlobalConfig(global_config_t *old,global_config_t *n)
{
	//strcpy(n->dev_name,"newname");
	//strcpy(n->dev_location,"newloc");
	n->para1=old->para1+10;
	n->para2=old->para2+10;
	n->para3=old->para3+10;
	int i=0;
	for (i=0;i<4;i++)		
		n->timers[i]=old->timers[i]+10;	
}

void writeGlobalConfigtoFile(global_config_t *t)
{
}

void getGlobalConfig(global_config_t *t)
{
	setting=config_lookup(&cfg,"global_config");
	if(!config_setting_lookup_string(setting,"name",&t->dev_name))	
		printf("Error : device name not found\n");
	if(!config_setting_lookup_string(setting,"location",&t->dev_location)	)
		printf("Error : device location not found\n");
	if(!config_setting_lookup_int(setting,"para1",&t->para1))
		printf("Error : Para1 not found\n");
	if(!config_setting_lookup_int(setting,"para2",&t->para2))
		printf("Error : Para2 not found\n");
	if(!config_setting_lookup_int(setting,"para3",&t->para3))
		printf("Error : Para3  not found\n");
	
	setting=config_lookup(&cfg,"global_config.timers");
	int i=0;
	for (i=0;i<4;i++)
	{
		int x= config_setting_get_int_elem(setting,i);		
		t->timers[i]=x;
	}	
}

void printGlobalConfig(global_config_t *t)
{
	printf("\n*********global_config***********\n");
	printf("device-Name (%s)\nlocation (%s) \npara1 (%d)\npara2 (%d)\npara3 (%d)\n",t->dev_name,t->dev_location,t->para1,t->para2,t->para3);	
	int i=0;
	for (i=0;i<4;i++)
	{
		printf("timers[%d] = (%d)\n",i,t->timers[i]);
	}	
	printf("************************************");
}

void getDeviceDetails(device_details_t *tmp)
{
	setting=config_lookup(&cfg,"device_details");
	if(!config_setting_lookup_string(setting,"Manufacturer-Name",&tmp->mfg_name))	
		printf("Error : Manufacture name not found\n");
	if(!config_setting_lookup_string(setting,"Serial-No",&tmp->serial_no)	)
		printf("Error : Serial no not found\n");
	if(!config_setting_lookup_string(setting,"Model-No",&tmp->model_no))
		printf("Error : Model number ot found\n");
}

void printDeviceDetails(device_details_t *tmp)
{
	printf("\n*********device_details***********\n");
	printf("Manufacturer-Name (%s)\nSerial No (%s) \nModel No (%s)\n",tmp->mfg_name,tmp->serial_no,tmp->model_no);	
	printf("************************************");
}


int main()
{
device_details_t mydevice_details;
global_config_t  global_config,new_global_config;
config_init(&cfg);
if(!config_read_file(&cfg,filename))
{
    printf("config_read_Fille error..Hence exiting the program \n");
    config_destroy(&cfg);
}

getDeviceDetails(&mydevice_details);
printDeviceDetails(&mydevice_details);
getGlobalConfig(&global_config);
printGlobalConfig(&global_config);
populateGlobalConfig(&global_config,&new_global_config);
setGlobalConfig(&new_global_config);
config_write_file(&cfg,"config.txt");
config_destroy(&cfg);
}
