#include "net-snmp/net-snmp-config.h"
#include "net-snmp/net-snmp-includes.h"
#include "net-snmp/agent/net-snmp-agent-includes.h"

#define MAXLEN 24
 
int keep_running=1;

const oid para1oid[] = {1,3,6,1,4,1,9000,2,2,1};
const oid para2oid[] = {1,3,6,1,4,1,9000,2,2,2} ;
const oid para3oid[] = {1,3,6,1,4,1,9000,2,2,3} ;
//const oid para4oid[] = {1,3,6,1,4,1,9000,2,2,2} ;
//const oid para5oid[] = {1,3,6,1,4,1,9000,2,2,2} ;

static unsigned int para1=100;
static unsigned int para2=200;
static unsigned int para3=300;
//static char para3[16];


void stop_server()
{
	snmp_shutdown("mysnmpagent");
	shutdown_agent();
	keep_running=0;
	return;
}

int para1_handler( struct netsnmp_mib_handler_s *handler,struct netsnmp_handler_registration_s *reginfo,struct netsnmp_agent_request_info_s *reqinfo,struct netsnmp_request_info_s *requests)
{
	printf("para1_handler called\n");
	int ii=0;	
	for(ii=0;ii<requests->requestvb->name_length-1;ii++)
		printf("%d\n",*(requests->requestvb->name+ii));

	//unsigned long type=ASN_INTEGER;
	switch(reqinfo->mode)
	{
	case MODE_GET:
		{
    		printf("para1 Mode_get called value (%d)\n",para1);
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
		printf("para1 Mode_set called value (%d)\n",para1);

		//memcpy(&para1,varval,*varlen);
		//snmp_set_var_typed_value(requests->requestvb,ASN_INTEGER,(unsigned char *)value,length);
		return SNMP_ERR_NOERROR;
	default:
		return SNMP_ERR_NOERROR;
	}
}


int para2_handler( struct netsnmp_mib_handler_s *handler,struct netsnmp_handler_registration_s *reginfo,struct netsnmp_agent_request_info_s *reqinfo,struct netsnmp_request_info_s *requests)
{
        printf("para2_handler called\n");
        int ii=0;
        for(ii=0;ii<requests->requestvb->name_length-1;ii++)
                printf("%d\n",*(requests->requestvb->name+ii));

        //unsigned long type=ASN_INTEGER;
        switch(reqinfo->mode)
        {
        case MODE_GET:
                {
                printf("para2 Mode_get called value (%d)\n",para2);
                int length=sizeof(int);
                unsigned char value[MAXLEN];
                memset(value,0,sizeof(value));
                memcpy(value,&para2,sizeof(para2));
                snmp_set_var_typed_value(requests->requestvb,ASN_INTEGER,(unsigned char *)value,length);
                return SNMP_ERR_NOERROR;
                }
        case MODE_SET_RESERVE1:
                //printf("Mode set called\n");
                printf("%d %d \n",requests->requestvb->val.string,requests->requestvb->val_len);
                memcpy(&para2,requests->requestvb->val.string,requests->requestvb->val_len);
                printf("para2 Mode_set called value (%d)\n",para2);

                //memcpy(&para1,varval,*varlen);
                //snmp_set_var_typed_value(requests->requestvb,ASN_INTEGER,(unsigned char *)value,length);
                return SNMP_ERR_NOERROR;
        default:
                return SNMP_ERR_NOERROR;
        }
}

int para3_handler( struct netsnmp_mib_handler_s *handler,struct netsnmp_handler_registration_s *reginfo,struct netsnmp_agent_request_info_s *reqinfo,struct netsnmp_request_info_s *requests)
{
        printf("para3_handler called\n");
        int ii=0;
        for(ii=0;ii<requests->requestvb->name_length-1;ii++)
                printf("%d\n",*(requests->requestvb->name+ii));

        //unsigned long type=ASN_INTEGER;
        switch(reqinfo->mode)
        {
        case MODE_GET:
                {
                printf("para3 Mode_get called value (%d)\n",para3);
                int length=sizeof(int);
                unsigned char value[MAXLEN];
                memset(value,0,sizeof(value));
                memcpy(value,&para3,sizeof(para3));
                snmp_set_var_typed_value(requests->requestvb,ASN_INTEGER,(unsigned char *)value,length);
                return SNMP_ERR_NOERROR;
                }
        case MODE_SET_RESERVE1:
                //printf("Mode set called\n");
                printf("%d %d \n",requests->requestvb->val.string,requests->requestvb->val_len);
                memcpy(&para3,requests->requestvb->val.string,requests->requestvb->val_len);
                printf("para3 Mode_set called value (%d)\n",para3);

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
	reg=netsnmp_create_handler_registration("para1oid",para1_handler,para1oid,OID_LENGTH(para1oid),HANDLER_CAN_RWRITE);
	netsnmp_register_handler(reg);
	printf("Register my oid %s\n",para1oid);
        reg=netsnmp_create_handler_registration("para2oid",para2_handler,para2oid,OID_LENGTH(para2oid),HANDLER_CAN_RWRITE);
        netsnmp_register_handler(reg);
        printf("Register my oid %s\n",para2oid);
        reg=netsnmp_create_handler_registration("para3oid",para3_handler,para3oid,OID_LENGTH(para3oid),HANDLER_CAN_RWRITE);
        netsnmp_register_handler(reg);
        printf("Register my oid %s\n",para3oid);

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
