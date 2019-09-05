#include "net-snmp/net-snmp-config.h"
#include "net-snmp/net-snmp-includes.h"
#include "net-snmp/agent/net-snmp-agent-includes.h"

#define MAXLEN 24
 
int keep_running=1;
const oid myOid[] = {1,3,6,1,4,1,9000,2,2,1};
static unsigned int para1=10845000;

void stop_server()
{
	snmp_shutdown("mysnmpagent");
	shutdown_agent();
	keep_running=0;
	return;
}

int MY_MIB_handler( struct netsnmp_mib_handler_s *handler,struct netsnmp_handler_registration_s *reginfo,struct netsnmp_agent_request_info_s *reqinfo,struct netsnmp_request_info_s *requests)
{
	printf("MY_MIB_handler called\n");
	int ii=0;	
	for(ii=0;ii<requests->requestvb->name_length-1;ii++)
		printf("%d\n",*(requests->requestvb->name+ii));

	//unsigned long type=ASN_INTEGER;
	switch(reqinfo->mode)
	{
	case MODE_GET:
		{
    		printf("Mode_get called value (%d)\n",para1);
		int length=sizeof(int);
		unsigned char value[MAXLEN];
		memset(value,0,sizeof(value));
		memcpy(value,&para1,sizeof(para1));	
		snmp_set_var_typed_value(requests->requestvb,ASN_INTEGER,(unsigned char *)value,length);
		return SNMP_ERR_NOERROR;
		}
	case MODE_SET_RESERVE1:
    		//printf("Mode set called\n");
		printf("%d %d \n",requests->requestvb->val.string,requests->requestvb->val_len);
		memcpy(&para1,requests->requestvb->val.string,requests->requestvb->val_len);
		printf("Mode_get called value (%d)\n",para1);

		//memcpy(&para1,varval,*varlen);
		//snmp_set_var_typed_value(requests->requestvb,ASN_INTEGER,(unsigned char *)value,length);
		return SNMP_ERR_NOERROR;
	default:
		return SNMP_ERR_NOERROR;
	}
}


void init_mysnmpagent()
{
	netsnmp_handler_registration *reg;
	reg=netsnmp_create_handler_registration("mytestoid",MY_MIB_handler,myOid,OID_LENGTH(myOid),HANDLER_CAN_RWRITE);
	netsnmp_register_handler(reg);
	printf("Register my oid %s\n",myOid);
}


void main()
{
	int retries=0;
	if(netsnmp_ds_set_boolean(NETSNMP_DS_APPLICATION_ID,NETSNMP_DS_AGENT_ROLE,1))
	{

            printf("netsnmp_ds_set_boolean failed");
            return;
	}

	//initialize the agent
	while(0!=init_agent("mysnmpagent"))
	{
	     printf("init_agent failed\n");
	     sleep(1);
	}
	netsnmp_ds_set_int(NETSNMP_DS_APPLICATION_ID,NETSNMP_DS_AGENT_AGENTX_PING_INTERVAL,5);

	//mib initialization code
	init_mysnmpagent();
	init_snmp("mysnmpagent");
	keep_running=1;
	printf("My agent starting...\n");
	while(keep_running)
	{
	  if(-1==agent_check_and_process(1))
	     printf("agent_check_and process failed\n");
	}
	stop_server();
	return;
}
