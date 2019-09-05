
typedef struct device_details_s
{
	const char *mfg_name;
	const char *serial_no;
	const char *model_no;
}device_details_t;

typedef struct global_config_s
{
const char *dev_name;
const char *dev_location;
int para1;
int para2;
int para3;
int timers[4];
}global_config_t;

void getGlobalConfig(global_config_t *);
void getDeviceDetails(device_details_t *);
