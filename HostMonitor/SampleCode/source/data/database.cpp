#include "core_include/api.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "database.h"
#include "sqlite3.h"

//#define DATA_BASE_PATH	"/data/monitor.db"
#define DATA_BASE_PATH	":memory:"

static char sql_create_real_data_table[] =
		"create table table_real_data("
		"TIME INTEGER,"
		"HR INTEGER,"
		"SPO2 INTEGER,"
		"RR INTEGER,"
		"PR INTEGER,"
		"TEMP INTEGER,"
		"NIBP_SYS INTEGER,"
		"NIBP_DIA INTEGER,"
		"NIBP_MEAN INTEGER)";

int c_database::m_real_data_rd_cnt;
int c_database::m_real_data_rd_len;

int c_database::sql_callback_read_real_data(void *arg, int nr, char **values, char **names)
{
	VALUE_SET* data_set = (VALUE_SET*)arg;
	int i = 0;
	if((m_real_data_rd_cnt < m_real_data_rd_len) && data_set)
	{
		data_set[m_real_data_rd_cnt].time = atoi(values[i++]);
		data_set[m_real_data_rd_cnt].hr = atoi(values[i++]);
		data_set[m_real_data_rd_cnt].spo2 = atoi(values[i++]);
		data_set[m_real_data_rd_cnt].rr = atoi(values[i++]);
		data_set[m_real_data_rd_cnt].pr = atoi(values[i++]);
		data_set[m_real_data_rd_cnt].temp = atoi(values[i++]);
		data_set[m_real_data_rd_cnt].nibp_sys = atoi(values[i++]);
		data_set[m_real_data_rd_cnt].nibp_dia = atoi(values[i++]);
		data_set[m_real_data_rd_cnt].nibp_mean = atoi(values[i++]);
		if(i > nr)
		{
			ASSERT(FALSE);
		}
	}
	//printf("%s,%s,%s,%s,%s,%s\n",values[0],values[1],values[2],values[3],values[4],values[5]);
	//fflush(stdout);
	m_real_data_rd_cnt++;
	return 0;
}

c_database::c_database()
{
	m_db_monitor = NULL;
}

c_database::~c_database()
{
	if(m_db_monitor)
	{
		sqlite3_close(m_db_monitor);
	}
}

int c_database::read(long start_time, long end_time, VALUE_SET* data_set, int len)
{
	char sql_buf[256];
	if(start_time > end_time)
	{
		ASSERT(FALSE);
	}
	m_real_data_rd_cnt = 0;
	m_real_data_rd_len = len;
	memset(sql_buf, 0, sizeof(sql_buf));
	sprintf(sql_buf,
			"select * from table_real_data where TIME between %lu and %lu",
			start_time,
			end_time);
	if(sqlite3_exec(m_db_monitor, sql_buf, sql_callback_read_real_data, data_set, NULL))
	{
		ASSERT(FALSE);
	}
	return ((m_real_data_rd_cnt < m_real_data_rd_len) ? m_real_data_rd_cnt : m_real_data_rd_len);
}

int c_database::write(VALUE_SET &data_set)
{
	//printf("wr time:%d\n",timer);
	//fflush(stdout);
	char sql_buf[256];
    memset(sql_buf, 0, sizeof(sql_buf));
    sprintf(sql_buf,
    		"insert into table_real_data values(%d,%d,%d,%d,%d,%d,%d,%d,%d)",
    		data_set.time,
    		data_set.hr,
    		data_set.spo2,
    		data_set.rr,
    		data_set.pr,
    		data_set.temp,
    		data_set.nibp_sys,
    		data_set.nibp_dia,
    		data_set.nibp_mean);
	if(sqlite3_exec(m_db_monitor, sql_buf, NULL, NULL, NULL))
	{
		ASSERT(FALSE);
	}
	return 0;
}

int c_database::display_all()
{
	if(sqlite3_exec(m_db_monitor, "select * from table_real_data", sql_callback_read_real_data, NULL, NULL))
	{
		ASSERT(FALSE);
	}
	return 0;
}

int c_database::init()
{
	int ret = -1;
	if(sqlite3_open(DATA_BASE_PATH, &m_db_monitor))
	{
		ASSERT(FALSE);
	}
	ret = sqlite3_exec(m_db_monitor,sql_create_real_data_table, NULL, NULL, NULL);
	if(ret !=0 && ret !=1)
	{
		ASSERT(FALSE);
	}
	return 0;
}
