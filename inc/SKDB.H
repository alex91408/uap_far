#define FUNC_IMPORT _declspec(dllimport)

extern "C"
{
	FUNC_IMPORT int OpenDatabase(char * lpDsn ,char * lpUID, char * lpPWD);
	FUNC_IMPORT int CloseDatabase();
	FUNC_IMPORT int AddNewRecorder(char * lpTableName , char * lpFields , char * lpValue);
	FUNC_IMPORT int UpdateRecorder(char * lpTableName , char * lpData , char * lpWhere);
	FUNC_IMPORT int DeleteRecorder(char * lpTableName , char * lpWhere);
	FUNC_IMPORT int SelectRecorder(char * lpFileds , char * lpTableName , char * lpWhere , char * lpSort);
	FUNC_IMPORT int CleanSelectResult();
	FUNC_IMPORT int FirstData();
	FUNC_IMPORT int LastData();
	FUNC_IMPORT int NextData();
	FUNC_IMPORT int PrevData();
	FUNC_IMPORT int MoveTo(long mIndex);
	FUNC_IMPORT unsigned long GetDataCount();
	FUNC_IMPORT int GetData(char * lpFieldName,char * buff, int bufflen);
	FUNC_IMPORT int BeEOF();
	FUNC_IMPORT int BeBOF();
	FUNC_IMPORT int GetErrorMessage(char * Msg , int len);
}

