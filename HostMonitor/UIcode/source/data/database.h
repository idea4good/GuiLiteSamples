#ifndef DB_TREND_H_
#define DB_TREND_H_

typedef struct
{//member's order must be equal with database table colmn's
	long  time;
	short hr;
	short spo2;
	short rr;
	short pr;
	short temp;
	short nibp_sys;
	short nibp_dia;
	short nibp_mean;
}VALUE_SET;

struct sqlite3;
class c_database
{
public:
	int init();
	int read(long start_time, long end_time, VALUE_SET* data_set, int len);
	int write(VALUE_SET &data_set);

	int display_all();
	static c_database* get_instance()
	{
		static c_database s_the_db;
		return &s_the_db;
	}
private:
	sqlite3 *m_db_monitor;
	static int	m_real_data_rd_cnt;
	static int	m_real_data_rd_len;
	static int 	sql_callback_read_real_data(void *arg, int nr, char **values, char **names);
	c_database();
	c_database(const c_database&);
	c_database& operator=(const c_database&);
	~c_database();
};

#endif
