#include "net-snmp/net-snmp-config.h"
#include "net-snmp/net-snmp-includes.h"
#include "net-snmp/agent/net-snmp-agent-includes.h"

#define MAXLEN 24
#define MAX_COLUMN 100
 
int keep_running=1;
const oid myOid[] = {1,3,6,1,4,1,9000,2,2,1};
const oid mytableOid[] = {1,3,6,1,4,1,9000,2,2,2};
typedef struct MyTable_entry_s
{
    long myTableIndex;
    int rollno;
//    int age;
//    int rank;
    int valid; // add this one to the end
}MyTable_entry;

static unsigned int para1=10845000;
MyTable_entry  localvalues[4];

netsnmp_tdata *table = NULL;

void inittabledata()
{
	int i=0;
	memset(localvalues,0,sizeof(localvalues));
	for(i=0;i<4;i++)
	{
		localvalues[i].myTableIndex=i;
		localvalues[i].rollno=5000+i;	
	}	
}

void printtabledata()
{
	int i=0;
	for(i=0;i<4;i++)
	{
		printf("i (%d) myTableIndex (%d) rollno (%d)\n",i,localvalues[i].myTableIndex,localvalues[i].rollno);
	}	
}



void initmytablevalues()
{
       printf("initmytablevalues ---entry \n");

	if ( table == NULL ) return;   // remember our "global" variable named "table"?

	// start by deleting all of the existing rows
	int cnt= netsnmp_tdata_row_count(table);
        printf("Table row count is (%d)\n",cnt);
	while ( cnt > 0 )
	{
	    netsnmp_tdata_row *row = netsnmp_tdata_row_first( table );
	    netsnmp_tdata_remove_and_delete_row( table, row );
	}

	int i=0;
	for (i=0;i<4;i++)// ...loop through all the data you want to add as rows into the table... )
	{
	    MyTable_entry *entry = SNMP_MALLOC_TYPEDEF( MyTable_entry );
	    if ( entry == NULL ) return;
	    netsnmp_tdata_row *row = netsnmp_tdata_create_row();
	    if ( row == NULL ) 
	    {
		SNMP_FREE( entry ); return;
	    }

    	    entry->myTableIndex = localvalues[i].myTableIndex; 
            entry->rollno = localvalues[i].rollno;
	//    entry->age = (i+20);
	//    entry->rank = i+10;
	    entry->valid = i;
    	    row->data = entry;
	    netsnmp_tdata_row_add_index( row, ASN_INTEGER, &(entry->myTableIndex), sizeof(entry->myTableIndex) );
	    netsnmp_tdata_add_row( table, row );
	}
       printf("initmytablevalues ---exit \n");
}


void stop_server()
{
	snmp_shutdown("mysnmpagent");
	shutdown_agent();
	keep_running=0;
	return;
}


int mytable_handler( netsnmp_mib_handler *handler, netsnmp_handler_registration *reginfo, netsnmp_agent_request_info *reqinfo, netsnmp_request_info *requests )
{
    printf("mytable_handler ---entry \n");
    netsnmp_request_info *request;
    //if ( reqinfo->mode != MODE_GET ) return SNMP_ERR_NOERROR;
    switch(reqinfo->mode)
    {
    case MODE_GET:            
            printf("mytable_handler ---MODE_GET called \n");                     
	    for (request = requests; request; request = request->next )
	    {	
	        MyTable_entry *table_entry  = (MyTable_entry*)netsnmp_tdata_extract_entry( request );
        	netsnmp_table_request_info *table_info = netsnmp_extract_table_info( request );
	
	        if ( table_entry == NULL ) 
		{ 
			netsnmp_set_request_error( reqinfo, request, SNMP_NOSUCHINSTANCE); 		
			continue; 
		}

	        switch ( table_info->colnum )
        	{
	            // ...this is similar to non-table situations, eg:
	            case 1:
	                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER, table_entry->myTableIndex ); 				break;
		    case 2:
	                snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER, table_entry->rollno ); break;
        		  /*  case 3:
        	        snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER, table_entry->age ); break;
		    case 4:
        	        snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER, table_entry->rank ); break;
       		     */
       		     default: netsnmp_set_request_error(reqinfo, request, SNMP_NOSUCHOBJECT );
        	}
    	    }
            break;
    case MODE_SET_RESERVE1:
	    printf("mytable_handler ---MODE_SET called \n");                     
	    for (request = requests; request; request = request->next )
	    {	
            printf("mytable_handler ---inside request for loop  \n");                     
	        MyTable_entry *table_entry  = (MyTable_entry*)netsnmp_tdata_extract_entry( request );
        	netsnmp_table_request_info *table_info = netsnmp_extract_table_info( request );
	
	        if ( table_entry == NULL ) 
		{ 
			netsnmp_set_request_error( reqinfo, request, SNMP_NOSUCHINSTANCE); 		
			continue; 
		}

	        switch ( table_info->colnum )
        	{
	            // ...this is similar to non-table situations, eg:
	            case 1:
                        printf("case1 called (%d)\n",table_entry->myTableIndex);
	                //snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER, table_entry->myTableIndex );
				printf("%s\n",request->requestvb->val.string);
				break;
		    case 2:
	                //snmp_set_var_typed_integer( request->requestvb, ASN_INTEGER, table_entry->rollno ); break;
                        printf("case2 called index (%d) rollno (%d)\n",table_entry->myTableIndex,table_entry->rollno);
                        printf("%d len %d\n",requests->requestvb->val.string,requests->requestvb->val_len);
        		break;  
       		     default: 
			   printf("default case called\n");
                          netsnmp_set_request_error(reqinfo, request, SNMP_NOSUCHOBJECT );
                        break;
        	}
    	    }
                break;
    default:
            break;
    }
    printf("mytable_handler ---exit \n");
    return SNMP_ERR_NOERROR;
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


void tableregistration()
{
       printf("tableregistration ---entry \n");
	char *name="mytable";
	table = netsnmp_tdata_create_table( name, 0 );

	netsnmp_handler_registration *reg;
	netsnmp_iterator_info *info;
	netsnmp_table_registration_info *table_info;

	info = SNMP_MALLOC_TYPEDEF(netsnmp_iterator_info);
	info->get_first_data_point=NULL;
	info->get_next_data_point=NULL;

	table_info=SNMP_MALLOC_TYPEDEF(netsnmp_table_registration_info);
	netsnmp_table_helper_add_indexes(table_info,ASN_INTEGER,0);
	table_info->min_column=1;
	table_info->max_column=MAX_COLUMN;

	reg=netsnmp_create_handler_registration(name,mytable_handler,mytableOid,OID_LENGTH(myOid),HANDLER_CAN_RWRITE);
	netsnmp_tdata_register( reg, table, table_info );
       printf("initmytablevalues ---entry \n");

}

void scalarregistration()
{
	netsnmp_handler_registration *reg;
	reg=netsnmp_create_handler_registration("mytestoid",MY_MIB_handler,myOid,OID_LENGTH(myOid),HANDLER_CAN_RWRITE);
	netsnmp_register_handler(reg);
	printf("Register my oid %s\n",myOid);
}

void init_mysnmpagent()
{
	scalarregistration();
	tableregistration();
}


void main()
{

inittabledata();
printtabledata();

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
//	netsnmp_ds_set_int(NETSNMP_DS_APPLICATION_ID,NETSNMP_DS_NT_AGENTX_PING_INTERVAL,5);

	//mib initialization code
	init_mysnmpagent();
	init_snmp("mysnmpagent");
	keep_running=1;
	printf("My agent starting...\n");
	initmytablevalues();
	while(keep_running)
	{
	  if(-1==agent_check_and_process(1))
	     printf("agent_check_and process failed\n");
	}
	stop_server();
	return;
}
