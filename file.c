#define	EXTERN extern
#include <pdftexd.h>
#include <sys/types.h>
#include <sys/stat.h>




FILE *
xfopen (const_string filename,  const_string mode)
{
    FILE *f;

    //assert(filename && mode);

    f = fopen(filename, mode);
    if (f == NULL)
    {

        fprintf(stderr, "File Open Failed (%s)\n", filename);
        abort();
    }

    return f;
}

int xfclose ( FILE * stream,  const_string filename )
{
	int ret = fclose(stream);	
	if(ret != 0)
	{
		fprintf(stderr, "File Close Failed %s", filename);
		abort();
	}
	return 0;
}

void
close_file (FILE *f)
{
  if (!f)
    return;
  //printf("closing %p\n",  f);
  xfclose(f, "closefile");
}







void
recorder_record_input (const_string name)
{
    
}

/* record an output file name */
void
recorder_record_output (const_string name)
{
    
}

boolean
open_input (FILE **f_ptr, int filefmt, const_string fopen_mode)
{
    string fname = NULL;


    *f_ptr = NULL;
    if (fullnameoffile)
    {
        xptrfree(fullnameoffile);
    }
    
    
    /* Look in -output-directory first, if the filename is not
       absolute.  This is because .aux and other such files will get
       written to the output directory, and we have to be able to read
       them from there.  We only look for the name as-is.  */

    if (output_directory && !kpse_absolute_p (nameoffile+1, false)) {

        fname = concat3 (output_directory, "/", nameoffile + 1);
        *f_ptr = fopen (fname, fopen_mode);

/*
    if fname is a directory, discard it.
*/
        if (*f_ptr && dir_p (fname)) {
            fclose (*f_ptr);
            *f_ptr = NULL;
        }

        if (*f_ptr) {

            xptrfree (nameoffile);
            namelength = strlen (fname);
            nameoffile = xmalloc (namelength + 2);
            strcpy (nameoffile + 1, fname);
            fullnameoffile = fname;
        } else {
            xptrfree (fname);
        }
    }

    /* No file means do the normal search. */
    if (*f_ptr == NULL) {
        /* A negative FILEFMT means don't use a path.  */
        if (filefmt < 0) {
            /* no_file_path, for BibTeX .aux files and MetaPost things.  */
            *f_ptr = fopen(nameoffile + 1, fopen_mode);
            //printf("%s\n", nameoffile);
            /* FIXME... fullnameoffile = xstrdup(nameoffile + 1); */
        } else {
            
            boolean must_exist;
            must_exist = (filefmt != kpse_tex_format || texinputtype)
                    && (filefmt != kpse_vf_format);
            fname = kpse_find_file (nameoffile + 1,
                                    (kpse_file_format_type)filefmt,
                                    must_exist);
            if (fname) {
                fullnameoffile = xstrdup(fname);
                /* If we found the file in the current directory, don't leave
                   the `./' at the beginning of `nameoffile', since it looks
                   dumb when `tex foo' says `(./foo.tex ... )'.  On the other
                   hand, if the user said `tex ./foo', and that's what we
                   opened, then keep it -- the user specified it, so we
                   shouldn't remove it.  */
                if (fname[0] == '.' && IS_DIR_SEP (fname[1])
                    && (nameoffile[1] != '.' || !IS_DIR_SEP (nameoffile[2])))
                {
                    unsigned i = 0;
                    while (fname[i + 2] != 0) {
                        fname[i] = fname[i + 2];
                        i++;
                    }
                    fname[i] = 0;
                }
                *f_ptr = xfopen (fname, fopen_mode);

                /* kpse_find_file always returns a new string. */
                xptrfree (nameoffile);
                namelength = strlen (fname);
                nameoffile = xmalloc (namelength + 2);
                strcpy (nameoffile + 1, fname);
                xptrfree (fname);
            }
        }
    }

    if (*f_ptr) {
        recorder_record_input (nameoffile + 1);

       
        if (filefmt == kpse_tfm_format) {
            tfmtemp = getc (*f_ptr);
        } else if (filefmt == kpse_ofm_format) {
            tfmtemp = getc (*f_ptr);
        }
    }            
    //printf("opening %p %s\n",  *f_ptr, nameoffile+1);
    return *f_ptr != NULL;
}

boolean
open_output (FILE **f_ptr, const_string fopen_mode)
{
    string fname;
    boolean absolute = kpse_absolute_p(nameoffile+1, false);

    /* If we have an explicit output directory, use it. */
    if (output_directory && !absolute) {
        fname = concat3(output_directory, "/", nameoffile + 1);
    } else {
        fname = nameoffile + 1;
    }

    /* Is the filename openable as given?  */
    *f_ptr = fopen (fname, fopen_mode);

    
    /* If this succeeded, change nameoffile accordingly.  */
    if (*f_ptr) {
        if ((char*)fname != (char*)nameoffile + 1) {
            xptrfree (nameoffile);
            namelength = strlen (fname);
            nameoffile = xmalloc (namelength + 2);
            strcpy (nameoffile + 1, fname);
        }
        recorder_record_output (fname);
    }
    if ((char*)fname != (char*)nameoffile + 1)
    {
        xptrfree(fname);
    }
    return *f_ptr != NULL;
}

boolean
input_line (FILE *f)
{
  int i = EOF;

  /* Recognize either LF or CR as a line terminator.  */




  last = first;
  while (last < bufsize && (i = getc (f)) != EOF && i != '\n' && i != '\r')
    buffer[last++] = i;

  if (i == EOF && errno != EINTR && last == first)
    return false;

  /* We didn't get the whole line because our buffer was too small.  */
  if (i != EOF && i != '\n' && i != '\r') {
    fprintf (stderr, "! Unable to read an entire line---bufsize=%u.\n",
                     (unsigned) bufsize);
    abort();
  }

  buffer[last] = ' ';
  if (last >= maxbufstack)
    maxbufstack = last;

  /* If next char is LF of a CRLF, read it.  */
  if (i == '\r') {
    while ((i = getc (f)) == EOF && errno == EINTR)
      ;
    if (i != '\n')
      ungetc (i, f);
  }
  
  
  while (last > first && buffer[last - 1] == ' ')
    --last;


  return true;
}


void xfseek (FILE *fp, long offset, int wherefrom, const_string filename)
{
	int ret = fseek(fp, offset, wherefrom);
	if(ret != 0)
	{
		fprintf(stderr, "File Seek Failed %s", filename);
		abort();
	}
	
}

long
xftell (FILE *f,  const_string filename)
{
    long where = ftell (f);

    if (where < 0)
    {
		fprintf(stderr, "File Tell Failed %s", filename);
		abort();
	}

    return where;
}


long
xftello (FILE *f,  const_string filename)
{
    long where = ftello (f);

    if (where < 0)
    {
		fprintf(stderr, "File Tello Failed %s", filename);
		abort();
	}

    return where;
}

void
xfseeko (FILE *f,  off_t offset,  int wherefrom,  const_string filename)
{
  if (fseeko (f, offset, wherefrom) != 0) {
        fprintf(stderr, "File fseeko Failed (%s)", filename);
		    abort();
  }
}

void do_undump (char *p, int item_size, int nitems, FILE *in_file)
{
	if (fread (p, item_size, nitems, in_file) != (size_t) nitems)
	{
		fprintf(stderr, "Could not undump %d %d-byte item(s) from %s",
            nitems, item_size, nameoffile+1);
		abort();
	}
}

void do_dump (char *p, int item_size, int nitems,  FILE *out_file)
{
	 if (fwrite (p, item_size, nitems, out_file) != nitems)
	 {
	 	fprintf (stderr, "! Could not write %d %d-byte item(s) to %s.\n",
               nitems, item_size, nameoffile+1);
	 	abort();
	 }
}

boolean
eof (FILE *file)
{
  register int c;

  /* If FILE doesn't exist, return true. This happens, for example,
     when a user does `mft foo.mf' -- there's no change file,
     so we never open it, so we end up calling this with a null pointer. */
  if (!file)
    return true;
    
  /* Maybe we're already at the end?  */
  if (feof (file))
    return true;

  if ((c = getc (file)) == EOF)
    return true;

  /* We weren't at the end.  Back up.  */
  (void) ungetc (c, file);

  return false;
}

boolean bibopenout (FILE **f_ptr,  const_string name)
{

    *f_ptr = fopen (name, "wb");
    //printf("opening %p %s \n", *f_ptr, name);
    return *f_ptr != NULL;
    
}
boolean bibopenin (FILE **f_ptr, int local, const_string name)
{
  //printf("a request %s %d\n", name, local);
  if(local == -1)
  {
      *f_ptr = fopen (name, "rb");
      //printf("opening %p %s \n", *f_ptr, name);
      return *f_ptr != NULL;
  }
  else
  {
      char *tmpname = kpse_find_file (name, (kpse_file_format_type)local,
                                    false);
      if(tmpname == NULL)
        return false;

      *f_ptr = fopen (tmpname, "r");
      free(tmpname);
      //printf("opening %s %p\n", name, *f_ptr);
      return *f_ptr != NULL;
  }
}
