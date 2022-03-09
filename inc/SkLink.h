#define FUNC_IMPORT _declspec(dllimport)

extern "C"
{
FUNC_IMPORT int OpenDatabase(char * lpDsn ,char * lpUID, char * lpPWD);
FUNC_IMPORT int CloseDatabase();
FUNC_IMPORT int ConDatabase(char * lpDsn ,char * lpUID, char * lpPWD, int curr);
FUNC_IMPORT int DisconDatabase(int curr);
FUNC_IMPORT int AddNewRecorder(char * lpTableName , char * lpFields , char * lpValue);
FUNC_IMPORT int UpdateRecorder(char * lpTableName , char * lpData , char * lpWhere);
FUNC_IMPORT int DeleteRecorder(char * lpTableName , char * lpWhere);
FUNC_IMPORT int SelectRecorder(char * lpFileds , char * lpTableName , char * lpWhere , char * lpSort);
FUNC_IMPORT int CleanSelectResult(int curLoc);
FUNC_IMPORT int FirstData(int curLoc);
FUNC_IMPORT int LastData(int curLoc);
FUNC_IMPORT int NextData(int curLoc);
FUNC_IMPORT int PrevData(int curLoc);
FUNC_IMPORT int MoveTo(long mIndex, int curLoc);
FUNC_IMPORT unsigned long GetDataCount(int curLoc);
FUNC_IMPORT int GetData(char * lpFieldName,char * buff, int bufflen, int curLoc);
FUNC_IMPORT int GetDataByIndex(short mIndex ,char * buff, int bufflen, int curLoc);
FUNC_IMPORT int BeEOF(int curLoc);
FUNC_IMPORT int BeBOF(int curLoc); 
FUNC_IMPORT short GetODBCFieldCount();
FUNC_IMPORT int GetODBCFieldName(short Index , char * FieldName , unsigned int bufflen);
FUNC_IMPORT int OpenDatabaseEx(char * lpConnectionString);
FUNC_IMPORT int GetErrorMessage(char * Msg , int len);
FUNC_IMPORT int ExecuteSQL(char *sqlstr);
}