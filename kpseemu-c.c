#define	EXTERN extern
#include <pdftexd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <curl/curl.h>




boolean dir_p (string fn)
{
  struct stat stats;
  return stat (fn, &stats) == 0 && S_ISDIR (stats.st_mode);
}

boolean kpse_absolute_p (const_string filename, boolean relative_ok)
{
  boolean absolute;
  boolean explicit_relative;

  absolute = IS_DIR_SEP (*filename);
  explicit_relative   = relative_ok;
  return absolute || explicit_relative;
}


void
kpse_init_prog (const_string prefix,  unsigned dpi,
                const_string mode, const_string fallback)
{
 
}

boolean kpse_in_name_ok(const_string fname)
{

  return true;
}
boolean kpse_out_name_ok(const_string fname)
{

  return true;
}

void kpse_set_program_enabled(kpse_file_format_type fmt,
                                         boolean value, kpse_src_type level)
{
  //printf("Set Program Enable fmt %d val %d lev %d\n", fmt, value, level);
}

void kpse_set_program_name (const_string argv0,
                           const_string progname)
{
  
  //printf("Set Program name Argv %s progname %s\n", argv0, progname);
}

string kpse_find_glyph(const_string passed_fontname,  unsigned int dpi, kpse_file_format_type format, void *notused)
{
  char tryname[256];
  printf("Looking for %s dpi %d format %d\n", passed_fontname, dpi, format);
  if(strlen(passed_fontname) > 128)
  {
    return NULL;
  }
  sprintf(tryname, "%s.%dpk", passed_fontname, dpi);
  return kpse_find_file(tryname, kpse_pk_format, false);
	
}

void kpse_reset_program_name (const_string progname)
{
 
  //printf("Reset Program name progname %s\n", progname);
}

#define MAXAVAILABLENAMESIZE 512
#define KPSE_BASE_URL "https://www.swiftlatex.com/dl/tex"
// #include <emscripten/fetch.h>

static size_t curl_write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

static int skpse_file_deamon_search(char* name_ret)
{
  CURL *curl;
  CURLcode curl_res;
  FILE *destfile;

  int res = 0;
  char name_copy[MAXAVAILABLENAMESIZE] = {0};
  char name_url[MAXAVAILABLENAMESIZE] = {0};

  char const *tmpfolder = getenv("TEMP");
  if (tmpfolder == 0)
      tmpfolder = "/tmp";


    //Check 404 Cache
  strcpy(name_copy, name_ret);
  snprintf(name_ret, MAXAVAILABLENAMESIZE, "%s/%s.404", tmpfolder, name_copy);
  if(access(name_ret, F_OK) != -1) {
      return -1;
  }


  //Check 200 Cache 
  snprintf(name_ret, MAXAVAILABLENAMESIZE, "%s/%s", tmpfolder, name_copy);
  if(access(name_ret, F_OK) != -1) {
      return 0;
  }

  destfile = fopen(name_ret, "wb");
  if(destfile) {
      curl = curl_easy_init();
      if(curl) {
        snprintf(name_url, MAXAVAILABLENAMESIZE, "%s/%s", KPSE_BASE_URL, name_copy);
        curl_easy_setopt(curl, CURLOPT_URL, name_url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, destfile);
        curl_res = curl_easy_perform(curl);
        if(curl_res == CURLE_OK) {
          long response_code;
          curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
          if(response_code == 200) {
            res = 0;
          } else if (response_code == 301) {
            char name_404[MAXAVAILABLENAMESIZE] = {0};
            snprintf(name_404, MAXAVAILABLENAMESIZE, "%s/%s.404", tmpfolder, name_copy);
            FILE *error404File = fopen(name_404, "wb");
            if(error404File) {
              fclose(error404File);
            }
            printf("File not exists in remote server.\n");
            res = -1;
          } else {
            printf("Server error %ld.\n", response_code);
            res = -2;
          }
        } else {
            printf("Curl perform failed\n");
            res = -3;
        }
        curl_easy_cleanup(curl);
      } 
      else {
        printf("No curl support\n");
        res = -4;
      }
      fclose(destfile);
      if(res != 0) {
        unlink(name_ret);
      }
      return res;
  } 
  else {
    printf("Unable to write file %s\n", name_ret);
    return -1;
  }


  

  
}


string kpse_find_file(const_string name, kpse_file_format_type format,  boolean must_exist)
{
    if(name == NULL)
    {
      return NULL;
    }

    if(strlen(name) > MAXAVAILABLENAMESIZE/2)
    {
      printf("This file name is too long, skpse would not be able to handle it");
      return NULL;
    }

    string patched_name = xmalloc(MAXAVAILABLENAMESIZE);



    memset(patched_name, 0, MAXAVAILABLENAMESIZE);
    strcat(patched_name, name);
    
    


   if(strrchr(patched_name, '.') == NULL)
   {
      printf("extending the extension");
   		#define PREFIXPATH(path) //Todo if there is confusion, we can enforce matching the prefix
    	#define SUFFIX(suf) strcat(patched_name, suf); 
	    switch (format)
	    { 
        case kpse_gf_format:
          PREFIXPATH("fonts/gf/");
          SUFFIX (".gf");
          break;
        case kpse_pk_format:
          PREFIXPATH("fonts/pk/");
          SUFFIX (".pk");
          break;
        case kpse_tfm_format:
          PREFIXPATH("fonts/tfm/");
          SUFFIX (".tfm");
          break;
        case kpse_afm_format:
          PREFIXPATH("fonts/atm/");
          SUFFIX (".afm");
          break;
        case kpse_base_format:
          SUFFIX (".base");
          break;
        case kpse_bib_format:
          PREFIXPATH("bibtex/bib/");
          SUFFIX (".bib");
          break;
        case kpse_bst_format:
          PREFIXPATH("bibtex/bst/");
          SUFFIX (".bst");
          break;
        case kpse_fontmap_format:
          PREFIXPATH("fonts/map/");
          SUFFIX (".map");
          break;
        case kpse_mem_format:
          SUFFIX (".mem");
          break;
        case kpse_mf_format:
          SUFFIX (".mf");
          break;
        case kpse_mft_format:
          PREFIXPATH("mft/")
          SUFFIX (".mft");
          break;
        case kpse_mfpool_format:
          SUFFIX (".pool");
          break;
        case kpse_mp_format:
          SUFFIX (".mp");
          break;
        case kpse_mppool_format:
          SUFFIX (".pool");
          break;
        case kpse_ocp_format:
          SUFFIX (".ocp");
          break;
        case kpse_ofm_format:
          SUFFIX (".ofm");
          break;
        case kpse_opl_format:
          SUFFIX (".opl");
          break;
        case kpse_otp_format:
          SUFFIX (".otp");
          break;
        case kpse_ovf_format:
          SUFFIX (".ovf");
          break;
        case kpse_ovp_format:
          SUFFIX (".ovp");
          break;
        case kpse_pict_format:
          SUFFIX (".esp");
          break;
        case kpse_tex_format:
          SUFFIX (".tex");
          break;
        case kpse_texpool_format:
          SUFFIX (".pool");
          break;
        case kpse_texsource_format:
          SUFFIX (".dtx");
          break;
        case kpse_type1_format:
          SUFFIX (".pfa");
          break;
        case kpse_vf_format:
          PREFIXPATH("fonts/vf/");
          SUFFIX (".vf");
          break;
        case kpse_ist_format:
          SUFFIX (".ist");
          break;
        case kpse_truetype_format:
          SUFFIX (".ttf");
          break;
        case kpse_type42_format:
          SUFFIX (".t42");
          break;
        case kpse_miscfonts_format:
          break;
        case kpse_enc_format:
          PREFIXPATH('fonts/enc/pdftex/');
          SUFFIX (".enc");
          break;
        case kpse_cmap_format:
          PREFIXPATH("fonts/cmap/");
          break;
        case kpse_sfd_format:
          SUFFIX (".sfd");
          break;
        case kpse_opentype_format:
          SUFFIX (".otf");
          break;
        case kpse_pdftex_config_format:
          break;
        case kpse_lig_format:
          SUFFIX (".lig");
          break;
        case kpse_texmfscripts_format:
          break;
        case kpse_fea_format:
          SUFFIX (".fea");
          break;
        case kpse_cid_format:
          SUFFIX (".cid");
          break;
        case kpse_mlbib_format:
          SUFFIX (".mlbib");
          break;
        case kpse_mlbst_format:
          SUFFIX (".mlbst");
          break;
        case kpse_ris_format:
          SUFFIX (".ris");
          break;
        case kpse_bltxml_format:
          SUFFIX (".bltxml");
          break;
        case kpse_fmt_format:
          SUFFIX (".fmt");
          break;
        default:
          printf("Unknown Kpse Format %d fixme\n", format);
          break;
  		}
  		#undef SUFFIX
		#undef PREFIXPATH
   }
   
 
  if(patched_name[0] == '/' || access(patched_name, F_OK) != -1) //If it is absolute path or it is already exists based on the current directory, copy & return
  {
      return patched_name;
  }


  //printf("I am looking for %s\n", patched_name);

  if(skpse_file_deamon_search(patched_name) == 0) //Nope Try download it //Now we can ask for help to download the file
  {
    	return patched_name;
  }

  xptrfree(patched_name); //We try out bese, just leave it
  return NULL;
    
}


void
setupboundvariable (integer *var, const_string var_name, integer dflt)
{
  
  *var = dflt;


  if(strcmp(var_name, "main_memory") == 0)
  {
    *var = 5000000;
  }
  else if (strcmp(var_name, "extra_mem_top") == 0)
  {
    *var = 0;
  }
  else if (strcmp(var_name, "extra_mem_bot") == 0)
  {
    *var = 0;
  }
  else if (strcmp(var_name, "pool_size") == 0)
  {
    *var = 6250000;
  }
  else if (strcmp(var_name, "string_vacancies") == 0)
  {
    *var = 90000;
  }
  else if (strcmp(var_name, "pool_free") == 0)
  {
    *var = 47500;
  }
  else if (strcmp(var_name, "max_strings") == 0)
  {
    *var = 500000;
  }
  else if (strcmp(var_name, "font_mem_size") == 0)
  {
    *var = 8000000;
  }
  else if (strcmp(var_name, "font_max") == 0)
  {
    *var = 9000;
  }
  else if (strcmp(var_name, "trie_size") == 0)
  {
    *var = 1000000;
  }
  else if (strcmp(var_name, "hyph_size") == 0)
  {
    *var = 8191;
  }
  else if (strcmp(var_name, "buf_size") == 0)
  {
    *var = 200000;
  }
  else if (strcmp(var_name, "nest_size") == 0)
  {
    *var = 500;
  }
  else if (strcmp(var_name, "max_in_open") == 0)
  {
    *var = 15;
  }
  else if (strcmp(var_name, "param_size") == 0)
  {
    *var = 10000;
  }
  else if (strcmp(var_name, "save_size") == 0)
  {
    *var = 100000;
  }
  else if (strcmp(var_name, "stack_size") == 0)
  {
    *var = 5000;
  }
  else if (strcmp(var_name, "dvi_buf_size") == 0)
  {
    *var = 16384;
  }
  else if (strcmp(var_name, "error_line") == 0)
  {
    *var = 79;
  }
  else if (strcmp(var_name, "half_error_line") == 0)
  {
    *var = 50;
  }
  else if (strcmp(var_name, "max_print_line") == 0)
  {
    *var = 79;
  }
  else if (strcmp(var_name, "hash_extra") == 0)
  {
    *var = 600000;
  }

}



