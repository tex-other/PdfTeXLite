#define	EXTERN /* Instantiate data from pdftexd.h here.  */

#include <pdftexd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <md5.h>
string fullnameoffile;
string output_directory;
int ac;
char **av;
int tfmtemp;
int texinputtype;
int kpse_make_tex_discard_errors;
string translate_filename;
const_string c_job_name;
char start_time_str[32];
char *last_source_name;
int last_lineno;
const char *ptexbanner = "PDFTeX Lite";
const char *DEFAULT_FMT_NAME = " pdflatexlite.fmt";
const char *DEFAULT_DUMP_NAME = "pdflatexlite";
string versionstring = " (3.1415926)";
char bootstrapcmd[64] = {};
int exit_code;
static char *cstrbuf = NULL;
static int allocsize;

string
concat3 (const_string s1,  const_string s2,  const_string s3)
{
  int s2l = s2 ? strlen (s2) : 0;
  int s3l = s3 ? strlen (s3) : 0;
  string answer
      = (string) xmalloc (strlen(s1) + s2l + s3l + 1);
  strcpy (answer, s1);
  if (s2) strcat (answer, s2);
  if (s3) strcat (answer, s3);

  return answer;
}










integer
zround (double r)
{
  integer i;
  if (r > 2147483647.0)
    i = 2147483647;
  else if (r < -2147483647.0)
    i = -2147483647;
  else if (r >= 0.0)
    i = (integer)(r + 0.5);
  else
    i = (integer)(r - 0.5);

  return i;
}





#  define MAX_CSTRING_LEN     1024 * 1024
char *makecstring(integer s)
{
    
    char *p;
    static int allocsize;
    int allocgrow, i, l = strstart[s + 1] - strstart[s];
    if ((unsigned)(l + 1) > (unsigned)(MAX_CSTRING_LEN)){
    	fprintf(stderr, "buffer overflow at file %s, line %d", __FILE__,  __LINE__ ); abort();
    }
    
    if (cstrbuf == NULL) {
        allocsize = l + 1;
        cstrbuf = xmallocarray(char, allocsize);
    } else if (l + 1 > allocsize) {
        allocgrow = allocsize * 0.2;
        if (l + 1 - allocgrow > allocsize)
            allocsize = l + 1;
        else if (allocsize < MAX_CSTRING_LEN - allocgrow)
            allocsize += allocgrow;
        else
            allocsize = MAX_CSTRING_LEN;
        cstrbuf = xreallocarray(cstrbuf, char, allocsize);
    }
    p = cstrbuf;
    for (i = 0; i < l; i++)
        *p++ = strpool[i + strstart[s]];
    *p = 0;
    return cstrbuf;
}

 int runsystem(const char *noused)
{
  printf("Attempting %s\n", noused);
	return 0;
}


void
topenin (void)
{
 
    buffer[first] = 0; 
    char *ptr = bootstrapcmd;
    int k = first;
    while (*ptr) {
        buffer[k++] = *(ptr++);
    }
    buffer[k++] = ' ';
    buffer[k] = 0;
    bootstrapcmd[0] = 0;
    for (last = first; buffer[last]; ++last);

   
}


void
get_seconds_and_micros (integer *seconds,  integer *micros)
{

  struct timeval tv;
  gettimeofday(&tv, NULL);
  *seconds = tv.tv_sec;
  *micros  = tv.tv_usec;


}


void maketimestr(char* time_str)
{
		time_t start_time = time((time_t *) NULL);
		struct tm lt;
		lt = *localtime(&start_time);
		size_t size = strftime(time_str, 31, "D:%Y%m%d%H%M%S", &lt);

		if (size == 0) {
	        time_str[0] = '\0';
	        return;
	    }

	    if (time_str[14] == '6') {
	        time_str[14] = '5';
	        time_str[15] = '9';
	        time_str[16] = '\0';    /* for safety */
	    }

	    time_str[size++] = 'Z';
	    time_str[size] = 0;
}

void initstarttime()
{
	if(start_time_str[0] == '\0')
	{
		maketimestr(start_time_str);
	}
}


void convertStringToHexString(const char *in, char *out, int lin)
{
    int i, j, k;
    char buf[3];
    j = 0;
    for (i = 0; i < lin; i++) {
        k = snprintf(buf, sizeof(buf),
                     "%02X", (unsigned int) (unsigned char) in[i]);
        out[j++] = buf[0];
        out[j++] = buf[1];
    }
    out[j] = '\0';
}


void
calledit (packedASCIIcode *filename,
          poolpointer fnstart,
          integer fnlength,
          integer linenumber)
{
  
  for (int i = 1; i <= inopen; i++)
    xfclose (inputfile[i], "inputfile");

  exit (1);
}

void
readtcxfile (void)
{

}

void
recorder_change_filename (string new_name)
{

}


void
get_date_and_time (integer *minutes,  integer *day,
                   integer *month,  integer *year)
{
  struct tm *tmptr;

    
    /* whether the envvar was not set (usual case) or invalid,
       use current time.  */
   time_t myclock = time ((time_t *) 0);
   tmptr = localtime (&myclock);

  

  *minutes = tmptr->tm_hour * 60 + tmptr->tm_min;
  *day = tmptr->tm_mday;
  *month = tmptr->tm_mon + 1;
  *year = tmptr->tm_year + 1900;
}




strnumber
getjobname(strnumber name)
{
    strnumber ret = name;
    if (c_job_name != NULL)
      ret = maketexstring(c_job_name);
    return ret;
}

strnumber
makefullnamestring(void)
{
  return maketexstring(fullnameoffile);
}

char *makecfilename(integer s)
{
    char *name = makecstring(s);
    char *p = name;
    char *q = name;

    while (*p) {
        if (*p != '"')
            *q++ = *p;
        p++;
    }
    *q = '\0';
    return name;
}


void getcreationdate(void)
{
    size_t len;

    initstarttime();
    /* put creation date on top of string pool and update poolptr */
    len = strlen(start_time_str);
    if ((unsigned) (poolptr + len) >= (unsigned) (poolsize)) {
        poolptr = poolsize;
        /* error by str_toks that calls str_room(1) */
        return;
    }
    memcpy(&strpool[poolptr], start_time_str, len);
    poolptr += len;
}


void getfilemoddate(integer s)
{
    struct stat file_data;

    const_string orig_name = makecfilename(s);

    char *file_name = kpse_find_tex(orig_name);
    if (file_name == NULL) {
        return;                 /* empty string */
    }
    if (! kpse_in_name_ok(file_name)) {
       return;                  /* no permission */
    }

    recorder_record_input(file_name);
    /* get file status */

    if (stat(file_name, &file_data) == 0) {

        size_t len;
        char time_str[32];
        maketimestr(time_str);
        len = strlen(time_str);
        if ((unsigned) (poolptr + len) >= (unsigned) (poolsize)) {
            poolptr = poolsize;
            /* error by str_toks that calls str_room(1) */
        } else {
            memcpy(&strpool[poolptr], time_str, len);
            poolptr += len;
        }
    }
    /* else { errno contains error code } */

    xptrfree(file_name);
}


void getfilesize(integer s)
{
    struct stat file_data;
    int i;


    char *file_name = kpse_find_tex(makecfilename(s));

    if (file_name == NULL) {
        return;                 /* empty string */
    }
    if (! kpse_in_name_ok(file_name)) {
       return;                  /* no permission */
    }

    recorder_record_input(file_name);
    /* get file status */

    if (stat(file_name, &file_data) == 0) {

        size_t len;
        char buf[20];
        /* st_size has type off_t */
        i = snprintf(buf, sizeof(buf),
                     "%lu", (long unsigned int) file_data.st_size);
        len = strlen(buf);
        if ((unsigned) (poolptr + len) >= (unsigned) (poolsize)) {
            poolptr = poolsize;
            /* error by str_toks that calls str_room(1) */
        } else {
            memcpy(&strpool[poolptr], buf, len);
            poolptr += len;
        }
    }
    /* else { errno contains error code } */

    xptrfree(file_name);
}


#define DIGEST_SIZE 16
#define FILE_BUF_SIZE 1024

void getmd5sum(strnumber s, boolean file)
{
    md5_state_t state;
    md5_byte_t digest[DIGEST_SIZE];
    char outbuf[2 * DIGEST_SIZE + 1];
    int len = 2 * DIGEST_SIZE;


    if (file) {
        char file_buf[FILE_BUF_SIZE];
        int read = 0;
        FILE *f;
        char *file_name;


        file_name = kpse_find_tex(makecfilename(s));

        if (file_name == NULL) {
            return;             /* empty string */
        }
        if (! kpse_in_name_ok(file_name)) {
           return;              /* no permission */
        }

        /* in case of error the empty string is returned,
           no need for xfopen that aborts on error.
         */
        f = fopen(file_name, FOPEN_RBIN_MODE);
        if (f == NULL) {
            xptrfree(file_name);
            return;
        }
        recorder_record_input(file_name);
        md5_init(&state);
        while ((read = fread(&file_buf, sizeof(char), FILE_BUF_SIZE, f)) > 0) {
            md5_append(&state, (const md5_byte_t *) file_buf, read);
        }
        md5_finish(&state, digest);
        fclose(f);

        xptrfree(file_name);
    } else {
        /* s contains the data */
        md5_init(&state);

        md5_append(&state,
                   (md5_byte_t *) &strpool[strstart[s]],
                   strstart[s + 1] - strstart[s]);
        md5_finish(&state, digest);
    }

    if (poolptr + len >= poolsize) {
        /* error by str_toks that calls str_room(1) */
        return;
    }
    convertStringToHexString((char *) digest, outbuf, DIGEST_SIZE);

    memcpy(&strpool[poolptr], outbuf, len);
    poolptr += len;

}


void getfiledump(integer s, int offset, int length)
{
    FILE *f;
    int read, i;
    poolpointer data_ptr;
    poolpointer data_end;
    char *file_name;

    if (length == 0) {
        /* empty result string */
        return;
    }

    if (poolptr + 2 * length + 1 >= poolsize) {
        /* no place for result */
        poolptr = poolsize;
        /* error by str_toks that calls str_room(1) */
        return;
    }


    file_name = kpse_find_tex(makecfilename(s));
    if (file_name == NULL) {
        return;                 /* empty string */
    }
    if (! kpse_in_name_ok(file_name)) {
       return;                  /* no permission */
    }

    /* read file data */
    f = fopen(file_name, FOPEN_RBIN_MODE);
    if (f == NULL) {
        xptrfree(file_name);
        return;
    }
    recorder_record_input(file_name);
    if (fseek(f, offset, SEEK_SET) != 0) {
        xptrfree(file_name);
        return;
    }

    /* there is enough space in the string pool, the read
       data are put in the upper half of the result, thus
       the conversion to hex can be done without overwriting
       unconverted bytes. */
    data_ptr = poolptr + length;
    read = fread(&strpool[data_ptr], sizeof(char), length, f);
    fclose(f);

    /* convert to hex */
    data_end = data_ptr + read;
    for (; data_ptr < data_end; data_ptr++) {
        i = snprintf((char *) &strpool[poolptr], 3,
                     "%.2X", (unsigned int) strpool[data_ptr]);

        poolptr += i;
    }

    xptrfree(file_name);
}


string
gettexstring (strnumber s)
{
  poolpointer len;
  string name;
  len = strstart[s + 1] - strstart[s];
  name = (string)xmalloc (len + 1);
  strncpy (name, (string)&strpool[strstart[s]], len);
  name[len] = 0;
  return name;
}

static int
compare_paths (const_string p1, const_string p2)
{
  int ret;
  while (
         (((ret = (*p1 - *p2)) == 0) && (*p2 != 0))

                || (IS_DIR_SEP(*p1) && IS_DIR_SEP(*p2))) {
       p1++, p2++;
  }
  ret = (ret < 0 ? -1 : (ret > 0 ? 1 : 0));
  return ret;
}

boolean
isnewsource (strnumber srcfilename, int lineno)
{
  char *name = gettexstring(srcfilename);
  return (compare_paths(name, last_source_name) != 0 || lineno != last_lineno);
}

void
remembersourceinfo (strnumber srcfilename, int lineno)
{
  if (last_source_name)
  {
       xptrfree(last_source_name);
  }
  last_source_name = gettexstring(srcfilename);
  last_lineno = lineno;
}

poolpointer
makesrcspecial (strnumber srcfilename, int lineno)
{
  poolpointer oldpoolptr = poolptr;
  char *filename = gettexstring(srcfilename);
  /* FIXME: Magic number. */
  char buf[40];
  char *s = buf;

  /* Always put a space after the number, which makes things easier
   * to parse.
   */
  sprintf (buf, "src:%d ", lineno);

  if (poolptr + strlen(buf) + strlen(filename) >= (size_t)poolsize) {
       fprintf (stderr, "\nstring pool overflow\n"); /* fixme */
       exit (1);
  }
  s = buf;
  while (*s)
    strpool[poolptr++] = *s++;

  s = filename;
  while (*s)
    strpool[poolptr++] = *s++;

  return (oldpoolptr);
}


// int compileAPI()
// {
//          // xmeminit();
//          // tex_init();
//          // init_pdftex_lib();
//          //iniversion = 1;  
//          //strcpy(bootstrapcmd, "*pdflatex.ini");

//          strcpy(bootstrapcmd, "_input_.tex");
//          dumpname = DEFAULT_DUMP_NAME;
//          int fmtstrlen = strlen(DEFAULT_FMT_NAME);
//          TEXformatdefault = xmalloc(fmtstrlen + 2);
//          memcpy(TEXformatdefault, DEFAULT_FMT_NAME, fmtstrlen);
//          formatdefaultlength = strlen (TEXformatdefault + 1);
//          interactionoption = 1;
//          filelineerrorstylep = 0;
//          parsefirstlinep = 0;

        
//             mainbody ();

//         //Clean some rom for memory
//           // texfreemem();

         
          
//         return exit_code;    
// }



void uexit(int code)
{
    exit(code);
}

int main(int argc, char**argv)
{
  
  
   ac = argc;
   av = argv;
 //Parse Argument
   int c;
   while ((c = getopt (ac, av, "io:f:")) != -1)
      switch (c)
   {
        case 'i':
          iniversion = 1;
          break;
        case 'o':
          output_directory= optarg;
          break;
        case '?':
            fprintf (stderr,
                     "Usage: -i for iniversion, -o for output directory -f for inputfile\n");
          return 1;
        default:
          abort ();
    }




  //Now Basic Variable
 
 dumpname = DEFAULT_DUMP_NAME;
 int fmtstrlen = strlen(DEFAULT_FMT_NAME);
 TEXformatdefault = xmalloc(fmtstrlen + 2);
 memcpy(TEXformatdefault, DEFAULT_FMT_NAME, fmtstrlen);
 formatdefaultlength = strlen (TEXformatdefault + 1);
 interactionoption = 1;
 filelineerrorstylep = 0;
 parsefirstlinep = 0;

 for(; optind < argc; optind++) {
    strncpy(bootstrapcmd, argv[optind], 63);
    break;
 }

 //Go

  mainbody ();
 
  return 0;
  
}