#define EXTERN extern
#include "pdftexd.h"

void 
println ( void ) 
{
  println_regmem 
  switch ( selector ) 
  {case 19 : 
    {
      putc ('\n',  stdout );
      putc ('\n',  logfile );
      termoffset = 0 ;
      fileoffset = 0 ;
    } 
    break ;
  case 18 : 
    {
      putc ('\n',  logfile );
      fileoffset = 0 ;
    } 
    break ;
  case 17 : 
    {
      putc ('\n',  stdout );
      termoffset = 0 ;
    } 
    break ;
  case 16 : 
  case 20 : 
  case 21 : 
    ;
    break ;
    default: 
    putc ('\n',  writefile [selector ]);
    break ;
  } 
} 
void 
zprintchar ( ASCIIcode s ) 
{
  /* 10 */ printchar_regmem 
  if ( s == eqtb [29323 ].cint ) {
      
    if ( selector < 20 ) 
    {
      println () ;
      return ;
    } 
  } 
  switch ( selector ) 
  {case 19 : 
    {
      putc ( Xchr (s ),  stdout );
      putc ( Xchr (s ),  logfile );
      incr ( termoffset ) ;
      incr ( fileoffset ) ;
      if ( termoffset == maxprintline ) 
      {
	putc ('\n',  stdout );
	termoffset = 0 ;
      } 
      if ( fileoffset == maxprintline ) 
      {
	putc ('\n',  logfile );
	fileoffset = 0 ;
      } 
    } 
    break ;
  case 18 : 
    {
      putc ( Xchr (s ),  logfile );
      incr ( fileoffset ) ;
      if ( fileoffset == maxprintline ) 
      println () ;
    } 
    break ;
  case 17 : 
    {
      putc ( Xchr (s ),  stdout );
      incr ( termoffset ) ;
      if ( termoffset == maxprintline ) 
      println () ;
    } 
    break ;
  case 16 : 
    ;
    break ;
  case 20 : 
    if ( tally < trickcount ) 
    trickbuf [tally % errorline ]= s ;
    break ;
  case 21 : 
    {
      if ( poolptr < poolsize ) 
      {
	strpool [poolptr ]= s ;
	incr ( poolptr ) ;
      } 
    } 
    break ;
    default: 
    putc ( Xchr (s ),  writefile [selector ]);
    break ;
  } 
  incr ( tally ) ;
} 
void 
zprint ( integer s ) 
{
  /* 10 */ print_regmem 
  poolpointer j  ;
  integer nl  ;
  if ( s >= strptr ) 
  s = 261 ;
  else if ( s < 256 ) {
      
    if ( s < 0 ) 
    s = 261 ;
    else {
	
      if ( selector > 20 ) 
      {
	printchar ( s ) ;
	return ;
      } 
      if ( ( s == eqtb [29323 ].cint ) ) {
	  
	if ( selector < 20 ) 
	{
	  println () ;
	  return ;
	} 
      } 
      nl = eqtb [29323 ].cint ;
      eqtb [29323 ].cint = -1 ;
      j = strstart [s ];
      while ( j < strstart [s + 1 ]) {
	  
	printchar ( strpool [j ]) ;
	incr ( j ) ;
      } 
      eqtb [29323 ].cint = nl ;
      return ;
    } 
  } 
  j = strstart [s ];
  while ( j < strstart [s + 1 ]) {
      
    printchar ( strpool [j ]) ;
    incr ( j ) ;
  } 
} 
void 
zslowprint ( integer s ) 
{
  slowprint_regmem 
  poolpointer j  ;
  if ( ( s >= strptr ) || ( s < 256 ) ) 
  print ( s ) ;
  else {
      
    j = strstart [s ];
    while ( j < strstart [s + 1 ]) {
	
      print ( strpool [j ]) ;
      incr ( j ) ;
    } 
  } 
} 
void 
zprintnl ( strnumber s ) 
{
  printnl_regmem 
  if ( ( ( termoffset > 0 ) && ( odd ( selector ) ) ) || ( ( fileoffset > 0 ) 
  && ( selector >= 18 ) ) ) 
  println () ;
  print ( s ) ;
} 
void 
zprintesc ( strnumber s ) 
{
  printesc_regmem 
  integer c  ;
  c = eqtb [29319 ].cint ;
  if ( c >= 0 ) {
      
    if ( c < 256 ) 
    print ( c ) ;
  } 
  slowprint ( s ) ;
} 
void 
zprintthedigs ( eightbits k ) 
{
  printthedigs_regmem 
  while ( k > 0 ) {
      
    decr ( k ) ;
    if ( dig [k ]< 10 ) 
    printchar ( 48 + dig [k ]) ;
    else printchar ( 55 + dig [k ]) ;
  } 
} 
void 
zprintint ( longinteger n ) 
{
  printint_regmem 
  unsigned char k  ;
  longinteger m  ;
  k = 0 ;
  if ( n < 0 ) 
  {
    printchar ( 45 ) ;
    if ( n > -100000000L ) 
    n = - (integer) n ;
    else {
	
      m = -1 - n ;
      n = m / 10 ;
      m = ( m % 10 ) + 1 ;
      k = 1 ;
      if ( m < 10 ) 
      dig [0 ]= m ;
      else {
	  
	dig [0 ]= 0 ;
	incr ( n ) ;
      } 
    } 
  } 
  do {
      dig [k ]= n % 10 ;
    n = n / 10 ;
    incr ( k ) ;
  } while ( ! ( n == 0 ) ) ;
  printthedigs ( k ) ;
} 
void 
zprintcs ( integer p ) 
{
  printcs_regmem 
  if ( p < 514 ) {
      
    if ( p >= 257 ) {
	
      if ( p == 513 ) 
      {
	printesc ( 576 ) ;
	printesc ( 577 ) ;
	printchar ( 32 ) ;
      } 
      else {
	  
	printesc ( p - 257 ) ;
	if ( eqtb [27738 + p - 257 ].hh .v.RH == 11 ) 
	printchar ( 32 ) ;
      } 
    } 
    else if ( p < 1 ) 
    printesc ( 578 ) ;
    else print ( p - 1 ) ;
  } 
  else if ( ( ( p >= 26627 ) && ( p <= 30176 ) ) || ( p > eqtbtop ) ) 
  printesc ( 578 ) ;
  else if ( ( hash [p ].v.RH >= strptr ) ) 
  printesc ( 579 ) ;
  else {
      
    if ( ( p >= 15526 ) && ( p < 17626 ) ) 
    printesc ( prim [p - 15526 ].v.RH - 1 ) ;
    else printesc ( hash [p ].v.RH ) ;
    printchar ( 32 ) ;
  } 
} 
void 
zsprintcs ( halfword p ) 
{
  sprintcs_regmem 
  if ( p < 514 ) {
      
    if ( p < 257 ) 
    print ( p - 1 ) ;
    else if ( p < 513 ) 
    printesc ( p - 257 ) ;
    else {
	
      printesc ( 576 ) ;
      printesc ( 577 ) ;
    } 
  } 
  else if ( ( p >= 15526 ) && ( p < 17626 ) ) 
  printesc ( prim [p - 15526 ].v.RH - 1 ) ;
  else printesc ( hash [p ].v.RH ) ;
} 
void 
zprintfilename ( integer n , integer a , integer e ) 
{
  printfilename_regmem 
  boolean mustquote  ;
  poolpointer j  ;
  mustquote = false ;
  if ( a != 0 ) 
  {
    j = strstart [a ];
    while ( ( ! mustquote ) && ( j < strstart [a + 1 ]) ) {
	
      mustquote = strpool [j ]== 32 ;
      incr ( j ) ;
    } 
  } 
  if ( n != 0 ) 
  {
    j = strstart [n ];
    while ( ( ! mustquote ) && ( j < strstart [n + 1 ]) ) {
	
      mustquote = strpool [j ]== 32 ;
      incr ( j ) ;
    } 
  } 
  if ( e != 0 ) 
  {
    j = strstart [e ];
    while ( ( ! mustquote ) && ( j < strstart [e + 1 ]) ) {
	
      mustquote = strpool [j ]== 32 ;
      incr ( j ) ;
    } 
  } 
  if ( mustquote ) 
  printchar ( 34 ) ;
  if ( a != 0 ) 
  {register integer for_end; j = strstart [a ];for_end = strstart [a + 1 
  ]- 1 ; if ( j <= for_end) do 
    if ( strpool [j ]!= 34 ) 
    print ( strpool [j ]) ;
  while ( j++ < for_end ) ;} 
  if ( n != 0 ) 
  {register integer for_end; j = strstart [n ];for_end = strstart [n + 1 
  ]- 1 ; if ( j <= for_end) do 
    if ( strpool [j ]!= 34 ) 
    print ( strpool [j ]) ;
  while ( j++ < for_end ) ;} 
  if ( e != 0 ) 
  {register integer for_end; j = strstart [e ];for_end = strstart [e + 1 
  ]- 1 ; if ( j <= for_end) do 
    if ( strpool [j ]!= 34 ) 
    print ( strpool [j ]) ;
  while ( j++ < for_end ) ;} 
  if ( mustquote ) 
  printchar ( 34 ) ;
} 
void 
zprintsize ( integer s ) 
{
  printsize_regmem 
  if ( s == 0 ) 
  printesc ( 432 ) ;
  else if ( s == 16 ) 
  printesc ( 433 ) ;
  else printesc ( 434 ) ;
} 
void 
zprintwritewhatsit ( strnumber s , halfword p ) 
{
  printwritewhatsit_regmem 
  printesc ( s ) ;
  if ( mem [p + 1 ].hh .v.LH < 16 ) 
  printint ( mem [p + 1 ].hh .v.LH ) ;
  else if ( mem [p + 1 ].hh .v.LH == 16 ) 
  printchar ( 42 ) ;
  else printchar ( 45 ) ;
} 
void 
zprintsanum ( halfword q ) 
{
  printsanum_regmem 
  halfword n  ;
  if ( mem [q ].hh.b0 < 32 ) 
  n = mem [q + 1 ].hh .v.RH ;
  else {
      
    n = mem [q ].hh.b0 % 16 ;
    q = mem [q ].hh .v.RH ;
    n = n + 16 * mem [q ].hh.b0 ;
    q = mem [q ].hh .v.RH ;
    n = n + 256 * ( mem [q ].hh.b0 + 16 * mem [mem [q ].hh .v.RH ].hh.b0 
    ) ;
  } 
  printint ( n ) ;
} 
void 
zprintcsnames ( integer hstart , integer hfinish ) 
{
  printcsnames_regmem 
  integer c, h  ;
  fprintf ( stderr , "%s%ld%s%ld%c\n",  "fmtdebug:csnames from " , (long)hstart , " to " , (long)hfinish ,   ':' ) ;
  {register integer for_end; h = hstart ;for_end = hfinish ; if ( h <= 
  for_end) do 
    {
      if ( hash [h ].v.RH > 0 ) 
      {
	{register integer for_end; c = strstart [hash [h ].v.RH ];
	for_end = strstart [hash [h ].v.RH + 1 ]- 1 ; if ( c <= for_end) 
	do 
	  {
	    putbyte ( strpool [c ], stderr ) ;
	  } 
	while ( c++ < for_end ) ;} 
	{ putc ( '|' ,  stderr );  putc ( '\n',  stderr ); }
      } 
    } 
  while ( h++ < for_end ) ;} 
} 
void 
printfileline ( void ) 
{
  printfileline_regmem 
  integer level  ;
  level = inopen ;
  while ( ( level > 0 ) && ( fullsourcefilenamestack [level ]== 0 ) ) decr ( 
  level ) ;
  if ( level == 0 ) 
  printnl ( 264 ) ;
  else {
      
    printnl ( 345 ) ;
    print ( fullsourcefilenamestack [level ]) ;
    print ( 58 ) ;
    if ( level == inopen ) 
    printint ( line ) ;
    else printint ( linestack [level + 1 ]) ;
    print ( 646 ) ;
  } 
} 
#ifdef TEXMF_DEBUG
#endif /* TEXMF_DEBUG */
void 
jumpout ( void ) 
{
  jumpout_regmem 
  closefilesandterminate () ;
  {
    fflush ( stdout ) ;
    readyalready = 0 ;
    if ( ( history != 0 ) && ( history != 1 ) ) 
    uexit ( 1 ) ;
    else uexit ( 0 ) ;
  } 
} 
void 
error ( void ) 
{
  /* 22 10 */ error_regmem 
  ASCIIcode c  ;
  integer s1, s2, s3, s4  ;
  if ( history < 2 ) 
  history = 2 ;
  printchar ( 46 ) ;
  showcontext () ;
  if ( ( haltonerrorp ) ) 
  {
    history = 3 ;
    jumpout () ;
  } 
  if ( interaction == 3 ) 
  while ( true ) {
      
    lab22: clearforerrorprompt () ;
    {
      ;
      print ( 266 ) ;
      terminput () ;
    } 
    if ( last == first ) 
    return ;
    c = buffer [first ];
    if ( c >= 97 ) 
    c = c - 32 ;
    switch ( c ) 
    {case 48 : 
    case 49 : 
    case 50 : 
    case 51 : 
    case 52 : 
    case 53 : 
    case 54 : 
    case 55 : 
    case 56 : 
    case 57 : 
      if ( deletionsallowed ) 
      {
	s1 = curtok ;
	s2 = curcmd ;
	s3 = curchr ;
	s4 = alignstate ;
	alignstate = 1000000L ;
	OKtointerrupt = false ;
	if ( ( last > first + 1 ) && ( buffer [first + 1 ]>= 48 ) && ( 
	buffer [first + 1 ]<= 57 ) ) 
	c = c * 10 + buffer [first + 1 ]- 48 * 11 ;
	else c = c - 48 ;
	while ( c > 0 ) {
	    
	  gettoken () ;
	  decr ( c ) ;
	} 
	curtok = s1 ;
	curcmd = s2 ;
	curchr = s3 ;
	alignstate = s4 ;
	OKtointerrupt = true ;
	{
	  helpptr = 2 ;
	  helpline [1 ]= 279 ;
	  helpline [0 ]= 280 ;
	} 
	showcontext () ;
	goto lab22 ;
      } 
      break ;
	;
#ifdef TEXMF_DEBUG
    case 68 : 
      {
	debughelp () ;
	goto lab22 ;
      } 
      break ;
#endif /* TEXMF_DEBUG */
    case 69 : 
      if ( baseptr > 0 ) 
      {
	editnamestart = strstart [inputstack [baseptr ].namefield ];
	editnamelength = strstart [inputstack [baseptr ].namefield + 1 ]- 
	strstart [inputstack [baseptr ].namefield ];
	editline = line ;
	jumpout () ;
      } 
      break ;
    case 72 : 
      {
	if ( useerrhelp ) 
	{
	  giveerrhelp () ;
	  useerrhelp = false ;
	} 
	else {
	    
	  if ( helpptr == 0 ) 
	  {
	    helpptr = 2 ;
	    helpline [1 ]= 281 ;
	    helpline [0 ]= 282 ;
	  } 
	  do {
	      decr ( helpptr ) ;
	    print ( helpline [helpptr ]) ;
	    println () ;
	  } while ( ! ( helpptr == 0 ) ) ;
	} 
	{
	  helpptr = 4 ;
	  helpline [3 ]= 283 ;
	  helpline [2 ]= 282 ;
	  helpline [1 ]= 284 ;
	  helpline [0 ]= 285 ;
	} 
	goto lab22 ;
      } 
      break ;
    case 73 : 
      {
	beginfilereading () ;
	if ( last > first + 1 ) 
	{
	  curinput .locfield = first + 1 ;
	  buffer [first ]= 32 ;
	} 
	else {
	    
	  {
	    ;
	    print ( 278 ) ;
	    terminput () ;
	  } 
	  curinput .locfield = first ;
	} 
	first = last ;
	curinput .limitfield = last - 1 ;
	return ;
      } 
      break ;
    case 81 : 
    case 82 : 
    case 83 : 
      {
	errorcount = 0 ;
	interaction = 0 + c - 81 ;
	print ( 273 ) ;
	switch ( c ) 
	{case 81 : 
	  {
	    printesc ( 274 ) ;
	    decr ( selector ) ;
	  } 
	  break ;
	case 82 : 
	  printesc ( 275 ) ;
	  break ;
	case 83 : 
	  printesc ( 276 ) ;
	  break ;
	} 
	print ( 277 ) ;
	println () ;
	fflush ( stdout ) ;
	return ;
      } 
      break ;
    case 88 : 
      {
	interaction = 2 ;
	jumpout () ;
      } 
      break ;
      default: 
      ;
      break ;
    } 
    {
      print ( 267 ) ;
      printnl ( 268 ) ;
      printnl ( 269 ) ;
      if ( baseptr > 0 ) 
      print ( 270 ) ;
      if ( deletionsallowed ) 
      printnl ( 271 ) ;
      printnl ( 272 ) ;
    } 
  } 
  incr ( errorcount ) ;
  if ( errorcount == 100 ) 
  {
    printnl ( 265 ) ;
    history = 3 ;
    jumpout () ;
  } 
  if ( interaction > 0 ) 
  decr ( selector ) ;
  if ( useerrhelp ) 
  {
    println () ;
    giveerrhelp () ;
  } 
  else while ( helpptr > 0 ) {
      
    decr ( helpptr ) ;
    printnl ( helpline [helpptr ]) ;
  } 
  println () ;
  if ( interaction > 0 ) 
  incr ( selector ) ;
  println () ;
} 
void 
zfatalerror ( strnumber s ) 
{
  fatalerror_regmem 
  normalizeselector () ;
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 264 ) ;
    print ( 287 ) ;
  } 
  {
    helpptr = 1 ;
    helpline [0 ]= s ;
  } 
  {
    if ( interaction == 3 ) 
    interaction = 2 ;
    if ( logopened ) 
    error () ;
	;
#ifdef TEXMF_DEBUG
    if ( interaction > 0 ) 
    debughelp () ;
#endif /* TEXMF_DEBUG */
    history = 3 ;
    jumpout () ;
  } 
} 
void 
zoverflow ( strnumber s , integer n ) 
{
  overflow_regmem 
  normalizeselector () ;
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 264 ) ;
    print ( 288 ) ;
  } 
  print ( s ) ;
  printchar ( 61 ) ;
  printint ( n ) ;
  printchar ( 93 ) ;
  {
    helpptr = 2 ;
    helpline [1 ]= 289 ;
    helpline [0 ]= 290 ;
  } 
  {
    if ( interaction == 3 ) 
    interaction = 2 ;
    if ( logopened ) 
    error () ;
	;
#ifdef TEXMF_DEBUG
    if ( interaction > 0 ) 
    debughelp () ;
#endif /* TEXMF_DEBUG */
    history = 3 ;
    jumpout () ;
  } 
} 
void 
zconfusion ( strnumber s ) 
{
  confusion_regmem 
  normalizeselector () ;
  if ( history < 2 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 291 ) ;
    } 
    print ( s ) ;
    printchar ( 41 ) ;
    {
      helpptr = 1 ;
      helpline [0 ]= 292 ;
    } 
  } 
  else {
      
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 293 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 294 ;
      helpline [0 ]= 295 ;
    } 
  } 
  {
    if ( interaction == 3 ) 
    interaction = 2 ;
    if ( logopened ) 
    error () ;
	;
#ifdef TEXMF_DEBUG
    if ( interaction > 0 ) 
    debughelp () ;
#endif /* TEXMF_DEBUG */
    history = 3 ;
    jumpout () ;
  } 
} 
boolean 
initterminal ( void ) 
{
  /* 10 */ register boolean Result; initterminal_regmem 
  topenin () ;
  if ( last > first ) 
  {
    curinput .locfield = first ;
    while ( ( curinput .locfield < last ) && ( buffer [curinput .locfield ]
    == ' ' ) ) incr ( curinput .locfield ) ;
    if ( curinput .locfield < last ) 
    {
      Result = true ;
      return Result ;
    } 
  } 
  while ( true ) {
      
    ;
    Fputs ( stdout ,  "**" ) ;
    fflush ( stdout ) ;
    if ( ! inputln ( stdin , true ) ) 
    {
      putc ('\n',  stdout );
      fprintf ( stdout , "%s\n",  "! End of file on the terminal... why?" ) ;
      Result = false ;
      return Result ;
    } 
    curinput .locfield = first ;
    while ( ( curinput .locfield < last ) && ( buffer [curinput .locfield ]
    == 32 ) ) incr ( curinput .locfield ) ;
    if ( curinput .locfield < last ) 
    {
      Result = true ;
      return Result ;
    } 
    fprintf ( stdout , "%s\n",  "Please type the name of your input file." ) ;
  } 
  return Result ;
} 
strnumber 
makestring ( void ) 
{
  register strnumber Result; makestring_regmem 
  if ( strptr == maxstrings ) 
  overflow ( 260 , maxstrings - initstrptr ) ;
  incr ( strptr ) ;
  strstart [strptr ]= poolptr ;
  Result = strptr - 1 ;
  return Result ;
} 
boolean 
zstreqbuf ( strnumber s , integer k ) 
{
  /* 45 */ register boolean Result; streqbuf_regmem 
  poolpointer j  ;
  boolean result  ;
  j = strstart [s ];
  while ( j < strstart [s + 1 ]) {
      
    if ( strpool [j ]!= buffer [k ]) 
    {
      result = false ;
      goto lab45 ;
    } 
    incr ( j ) ;
    incr ( k ) ;
  } 
  result = true ;
  lab45: Result = result ;
  return Result ;
} 
boolean 
zstreqstr ( strnumber s , strnumber t ) 
{
  /* 45 */ register boolean Result; streqstr_regmem 
  poolpointer j, k  ;
  boolean result  ;
  result = false ;
  if ( ( strstart [s + 1 ]- strstart [s ]) != ( strstart [t + 1 ]- 
  strstart [t ]) ) 
  goto lab45 ;
  j = strstart [s ];
  k = strstart [t ];
  while ( j < strstart [s + 1 ]) {
      
    if ( strpool [j ]!= strpool [k ]) 
    goto lab45 ;
    incr ( j ) ;
    incr ( k ) ;
  } 
  result = true ;
  lab45: Result = result ;
  return Result ;
} 
strnumber 
zsearchstring ( strnumber search ) 
{
  /* 40 */ register strnumber Result; searchstring_regmem 
  strnumber result  ;
  strnumber s  ;
  integer len  ;
  result = 0 ;
  len = ( strstart [search + 1 ]- strstart [search ]) ;
  if ( len == 0 ) 
  {
    result = 345 ;
    goto lab40 ;
  } 
  else {
      
    s = search - 1 ;
    while ( s > 255 ) {
	
      if ( ( strstart [s + 1 ]- strstart [s ]) == len ) {
	  
	if ( streqstr ( s , search ) ) 
	{
	  result = s ;
	  goto lab40 ;
	} 
      } 
      decr ( s ) ;
    } 
  } 
  lab40: Result = result ;
  return Result ;
} 
strnumber 
slowmakestring ( void ) 
{
  /* 10 */ register strnumber Result; slowmakestring_regmem 
  strnumber s  ;
  strnumber t  ;
  t = makestring () ;
  s = searchstring ( t ) ;
  if ( s > 0 ) 
  {
    {
      decr ( strptr ) ;
      poolptr = strstart [strptr ];
    } 
    Result = s ;
    return Result ;
  } 
  Result = t ;
  return Result ;
} 
void 
zprinttwo ( integer n ) 
{
  printtwo_regmem 
  n = abs ( n ) % 100 ;
  printchar ( 48 + ( n / 10 ) ) ;
  printchar ( 48 + ( n % 10 ) ) ;
} 
void 
zprinthex ( integer n ) 
{
  printhex_regmem 
  unsigned char k  ;
  k = 0 ;
  printchar ( 34 ) ;
  do {
      dig [k ]= n % 16 ;
    n = n / 16 ;
    incr ( k ) ;
  } while ( ! ( n == 0 ) ) ;
  printthedigs ( k ) ;
} 
void 
zprintromanint ( integer n ) 
{
  /* 10 */ printromanint_regmem 
  poolpointer j, k  ;
  nonnegativeinteger u, v  ;
  j = strstart [262 ];
  v = 1000 ;
  while ( true ) {
      
    while ( n >= v ) {
	
      printchar ( strpool [j ]) ;
      n = n - v ;
    } 
    if ( n <= 0 ) 
    return ;
    k = j + 2 ;
    u = v / ( strpool [k - 1 ]- 48 ) ;
    if ( strpool [k - 1 ]== 50 ) 
    {
      k = k + 2 ;
      u = u / ( strpool [k - 1 ]- 48 ) ;
    } 
    if ( n + u >= v ) 
    {
      printchar ( strpool [k ]) ;
      n = n + u ;
    } 
    else {
	
      j = j + 2 ;
      v = v / ( strpool [j - 1 ]- 48 ) ;
    } 
  } 
} 
void 
printcurrentstring ( void ) 
{
  printcurrentstring_regmem 
  poolpointer j  ;
  j = strstart [strptr ];
  while ( j < poolptr ) {
      
    printchar ( strpool [j ]) ;
    incr ( j ) ;
  } 
} 
void 
terminput ( void ) 
{
  terminput_regmem 
  integer k  ;
  fflush ( stdout ) ;
  if ( ! inputln ( stdin , true ) ) 
  fatalerror ( 263 ) ;
  termoffset = 0 ;
  decr ( selector ) ;
  if ( last != first ) 
  {register integer for_end; k = first ;for_end = last - 1 ; if ( k <= 
  for_end) do 
    print ( buffer [k ]) ;
  while ( k++ < for_end ) ;} 
  println () ;
  incr ( selector ) ;
} 
void 
zinterror ( integer n ) 
{
  interror_regmem 
  print ( 286 ) ;
  printint ( n ) ;
  printchar ( 41 ) ;
  error () ;
} 
void 
normalizeselector ( void ) 
{
  normalizeselector_regmem 
  if ( logopened ) 
  selector = 19 ;
  else selector = 17 ;
  if ( jobname == 0 ) 
  openlogfile () ;
  if ( interaction == 0 ) 
  decr ( selector ) ;
} 
void 
pauseforinstructions ( void ) 
{
  pauseforinstructions_regmem 
  if ( OKtointerrupt ) 
  {
    interaction = 3 ;
    if ( ( selector == 18 ) || ( selector == 16 ) ) 
    incr ( selector ) ;
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 296 ) ;
    } 
    {
      helpptr = 3 ;
      helpline [2 ]= 297 ;
      helpline [1 ]= 298 ;
      helpline [0 ]= 299 ;
    } 
    deletionsallowed = false ;
    error () ;
    deletionsallowed = true ;
    interrupt = 0 ;
  } 
} 
integer 
zhalf ( integer x ) 
{
  register integer Result; half_regmem 
  if ( odd ( x ) ) 
  Result = ( x + 1 ) / 2 ;
  else Result = x / 2 ;
  return Result ;
} 
scaled 
zrounddecimals ( smallnumber k ) 
{
  register scaled Result; rounddecimals_regmem 
  integer a  ;
  a = 0 ;
  while ( k > 0 ) {
      
    decr ( k ) ;
    a = ( a + dig [k ]* 131072L ) / 10 ;
  } 
  Result = ( a + 1 ) / 2 ;
  return Result ;
} 
void 
zprintscaled ( scaled s ) 
{
  printscaled_regmem 
  scaled delta  ;
  if ( s < 0 ) 
  {
    printchar ( 45 ) ;
    s = - (integer) s ;
  } 
  printint ( s / 65536L ) ;
  printchar ( 46 ) ;
  s = 10 * ( s % 65536L ) + 5 ;
  delta = 10 ;
  do {
      if ( delta > 65536L ) 
    s = s - 17232 ;
    printchar ( 48 + ( s / 65536L ) ) ;
    s = 10 * ( s % 65536L ) ;
    delta = delta * 10 ;
  } while ( ! ( s <= delta ) ) ;
} 
scaled 
zmultandadd ( integer n , scaled x , scaled y , scaled maxanswer ) 
{
  register scaled Result; multandadd_regmem 
  if ( n < 0 ) 
  {
    x = - (integer) x ;
    n = - (integer) n ;
  } 
  if ( n == 0 ) 
  Result = y ;
  else if ( ( ( x <= ( maxanswer - y ) / n ) && ( - (integer) x <= ( maxanswer 
  + y ) / n ) ) ) 
  Result = n * x + y ;
  else {
      
    aritherror = true ;
    Result = 0 ;
  } 
  return Result ;
} 
scaled 
zxovern ( scaled x , integer n ) 
{
  register scaled Result; xovern_regmem 
  boolean negative  ;
  negative = false ;
  if ( n == 0 ) 
  {
    aritherror = true ;
    Result = 0 ;
    texremainder = x ;
  } 
  else {
      
    if ( n < 0 ) 
    {
      x = - (integer) x ;
      n = - (integer) n ;
      negative = true ;
    } 
    if ( x >= 0 ) 
    {
      Result = x / n ;
      texremainder = x % n ;
    } 
    else {
	
      Result = - (integer) ( ( - (integer) x ) / n ) ;
      texremainder = - (integer) ( ( - (integer) x ) % n ) ;
    } 
  } 
  if ( negative ) 
  texremainder = - (integer) texremainder ;
  return Result ;
} 
scaled 
zxnoverd ( scaled x , integer n , integer d ) 
{
  register scaled Result; xnoverd_regmem 
  boolean positive  ;
  nonnegativeinteger t, u, v  ;
  if ( x >= 0 ) 
  positive = true ;
  else {
      
    x = - (integer) x ;
    positive = false ;
  } 
  t = ( x % 32768L ) * n ;
  u = ( x / 32768L ) * n + ( t / 32768L ) ;
  v = ( u % d ) * 32768L + ( t % 32768L ) ;
  if ( u / d >= 32768L ) 
  aritherror = true ;
  else u = 32768L * ( u / d ) + ( v / d ) ;
  if ( positive ) 
  {
    Result = u ;
    texremainder = v % d ;
  } 
  else {
      
    Result = - (integer) u ;
    texremainder = - (integer) ( v % d ) ;
  } 
  return Result ;
} 
halfword 
zbadness ( scaled t , scaled s ) 
{
  register halfword Result; badness_regmem 
  integer r  ;
  if ( t == 0 ) 
  Result = 0 ;
  else if ( s <= 0 ) 
  Result = 10000 ;
  else {
      
    if ( t <= 7230584L ) 
    r = ( t * 297 ) / s ;
    else if ( s >= 1663497L ) 
    r = t / ( s / 297 ) ;
    else r = t ;
    if ( r > 1290 ) 
    Result = 10000 ;
    else Result = ( r * r * r + 131072L ) / 262144L ;
  } 
  return Result ;
} 
integer 
zmakefrac ( integer p , integer q ) 
{
  register integer Result; makefrac_regmem 
  integer f  ;
  integer n  ;
  boolean negative  ;
  integer becareful  ;
  if ( p >= 0 ) 
  negative = false ;
  else {
      
    p = - (integer) p ;
    negative = true ;
  } 
  if ( q <= 0 ) 
  {
	;
#ifdef TEXMF_DEBUG
    if ( q == 0 ) 
    confusion ( 47 ) ;
#endif /* TEXMF_DEBUG */
    q = - (integer) q ;
    negative = ! negative ;
  } 
  n = p / q ;
  p = p % q ;
  if ( n >= 8 ) 
  {
    aritherror = true ;
    if ( negative ) 
    Result = -2147483647L ;
    else Result = 2147483647L ;
  } 
  else {
      
    n = ( n - 1 ) * 268435456L ;
    f = 1 ;
    do {
	becareful = p - q ;
      p = becareful + p ;
      if ( p >= 0 ) 
      f = f + f + 1 ;
      else {
	  
	f = f + f ;
	p = p + q ;
      } 
    } while ( ! ( f >= 268435456L ) ) ;
    becareful = p - q ;
    if ( becareful + p >= 0 ) 
    incr ( f ) ;
    if ( negative ) 
    Result = - (integer) ( f + n ) ;
    else Result = f + n ;
  } 
  return Result ;
} 
integer 
ztakefrac ( integer q , integer f ) 
{
  register integer Result; takefrac_regmem 
  integer p  ;
  boolean negative  ;
  integer n  ;
  integer becareful  ;
  if ( f >= 0 ) 
  negative = false ;
  else {
      
    f = - (integer) f ;
    negative = true ;
  } 
  if ( q < 0 ) 
  {
    q = - (integer) q ;
    negative = ! negative ;
  } 
  if ( f < 268435456L ) 
  n = 0 ;
  else {
      
    n = f / 268435456L ;
    f = f % 268435456L ;
    if ( q <= 2147483647L / n ) 
    n = n * q ;
    else {
	
      aritherror = true ;
      n = 2147483647L ;
    } 
  } 
  f = f + 268435456L ;
  p = 134217728L ;
  if ( q < 1073741824L ) 
  do {
      if ( odd ( f ) ) 
    p = ( p + q ) / 2 ;
    else p = ( p ) / 2 ;
    f = ( f ) / 2 ;
  } while ( ! ( f == 1 ) ) ;
  else do {
      if ( odd ( f ) ) 
    p = p + ( q - p ) / 2 ;
    else p = ( p ) / 2 ;
    f = ( f ) / 2 ;
  } while ( ! ( f == 1 ) ) ;
  becareful = n - 2147483647L ;
  if ( becareful + p > 0 ) 
  {
    aritherror = true ;
    n = 2147483647L - p ;
  } 
  if ( negative ) 
  Result = - (integer) ( n + p ) ;
  else Result = n + p ;
  return Result ;
} 
integer 
zmlog ( integer x ) 
{
  register integer Result; mlog_regmem 
  integer y, z  ;
  integer k  ;
  if ( x <= 0 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 300 ) ;
    } 
    printscaled ( x ) ;
    print ( 301 ) ;
    {
      helpptr = 2 ;
      helpline [1 ]= 302 ;
      helpline [0 ]= 303 ;
    } 
    error () ;
    Result = 0 ;
  } 
  else {
      
    y = 1302456860L ;
    z = 6581195L ;
    while ( x < 1073741824L ) {
	
      x = x + x ;
      y = y - 93032639L ;
      z = z - 48782L ;
    } 
    y = y + ( z / 65536L ) ;
    k = 2 ;
    while ( x > 1073741828L ) {
	
      z = ( ( x - 1 ) / twotothe [k ]) + 1 ;
      while ( x < 1073741824L + z ) {
	  
	z = ( z + 1 ) / 2 ;
	k = k + 1 ;
      } 
      y = y + speclog [k ];
      x = x - z ;
    } 
    Result = y / 8 ;
  } 
  return Result ;
} 
integer 
zabvscd ( integer a , integer b , integer c , integer d ) 
{
  /* 10 */ register integer Result; abvscd_regmem 
  integer q, r  ;
  if ( a < 0 ) 
  {
    a = - (integer) a ;
    b = - (integer) b ;
  } 
  if ( c < 0 ) 
  {
    c = - (integer) c ;
    d = - (integer) d ;
  } 
  if ( d <= 0 ) 
  {
    if ( b >= 0 ) {
	
      if ( ( ( a == 0 ) || ( b == 0 ) ) && ( ( c == 0 ) || ( d == 0 ) ) ) 
      {
	Result = 0 ;
	return Result ;
      } 
      else {
	  
	Result = 1 ;
	return Result ;
      } 
    } 
    if ( d == 0 ) {
	
      if ( a == 0 ) 
      {
	Result = 0 ;
	return Result ;
      } 
      else {
	  
	Result = -1 ;
	return Result ;
      } 
    } 
    q = a ;
    a = c ;
    c = q ;
    q = - (integer) b ;
    b = - (integer) d ;
    d = q ;
  } 
  else if ( b <= 0 ) 
  {
    if ( b < 0 ) {
	
      if ( a > 0 ) 
      {
	Result = -1 ;
	return Result ;
      } 
    } 
    if ( c == 0 ) 
    {
      Result = 0 ;
      return Result ;
    } 
    else {
	
      Result = -1 ;
      return Result ;
    } 
  } 
  while ( true ) {
      
    q = a / d ;
    r = c / b ;
    if ( q != r ) {
	
      if ( q > r ) 
      {
	Result = 1 ;
	return Result ;
      } 
      else {
	  
	Result = -1 ;
	return Result ;
      } 
    } 
    q = a % d ;
    r = c % b ;
    if ( r == 0 ) {
	
      if ( q == 0 ) 
      {
	Result = 0 ;
	return Result ;
      } 
      else {
	  
	Result = 1 ;
	return Result ;
      } 
    } 
    if ( q == 0 ) 
    {
      Result = -1 ;
      return Result ;
    } 
    a = b ;
    b = q ;
    c = d ;
    d = r ;
  } 
  return Result ;
} 
void 
newrandoms ( void ) 
{
  newrandoms_regmem 
  unsigned char k  ;
  integer x  ;
  {register integer for_end; k = 0 ;for_end = 23 ; if ( k <= for_end) do 
    {
      x = randoms [k ]- randoms [k + 31 ];
      if ( x < 0 ) 
      x = x + 268435456L ;
      randoms [k ]= x ;
    } 
  while ( k++ < for_end ) ;} 
  {register integer for_end; k = 24 ;for_end = 54 ; if ( k <= for_end) do 
    {
      x = randoms [k ]- randoms [k - 24 ];
      if ( x < 0 ) 
      x = x + 268435456L ;
      randoms [k ]= x ;
    } 
  while ( k++ < for_end ) ;} 
  jrandom = 54 ;
} 
void 
zinitrandoms ( integer seed ) 
{
  initrandoms_regmem 
  integer j, jj, k  ;
  unsigned char i  ;
  j = abs ( seed ) ;
  while ( j >= 268435456L ) j = ( j ) / 2 ;
  k = 1 ;
  {register integer for_end; i = 0 ;for_end = 54 ; if ( i <= for_end) do 
    {
      jj = k ;
      k = j - k ;
      j = jj ;
      if ( k < 0 ) 
      k = k + 268435456L ;
      randoms [( i * 21 ) % 55 ]= j ;
    } 
  while ( i++ < for_end ) ;} 
  newrandoms () ;
  newrandoms () ;
  newrandoms () ;
} 
integer 
zunifrand ( integer x ) 
{
  register integer Result; unifrand_regmem 
  integer y  ;
  if ( jrandom == 0 ) 
  newrandoms () ;
  else decr ( jrandom ) ;
  y = takefrac ( abs ( x ) , randoms [jrandom ]) ;
  if ( y == abs ( x ) ) 
  Result = 0 ;
  else if ( x > 0 ) 
  Result = y ;
  else Result = - (integer) y ;
  return Result ;
} 
integer 
normrand ( void ) 
{
  register integer Result; normrand_regmem 
  integer x, u, l  ;
  do {
      do { if ( jrandom == 0 ) 
      newrandoms () ;
      else decr ( jrandom ) ;
      x = takefrac ( 112429L , randoms [jrandom ]- 134217728L ) ;
      if ( jrandom == 0 ) 
      newrandoms () ;
      else decr ( jrandom ) ;
      u = randoms [jrandom ];
    } while ( ! ( abs ( x ) < u ) ) ;
    x = makefrac ( x , u ) ;
    l = 139548960L - mlog ( u ) ;
  } while ( ! ( abvscd ( 1024 , l , x , x ) >= 0 ) ) ;
  Result = x ;
  return Result ;
} 
#ifdef TEXMF_DEBUG
void 
zprintword ( memoryword w ) 
{
  printword_regmem 
  printint ( w .cint ) ;
  printchar ( 32 ) ;
  printscaled ( w .cint ) ;
  printchar ( 32 ) ;
  printscaled ( round ( 65536L * w .gr ) ) ;
  println () ;
  printint ( w .hh .v.LH ) ;
  printchar ( 61 ) ;
  printint ( w .hh.b0 ) ;
  printchar ( 58 ) ;
  printint ( w .hh.b1 ) ;
  printchar ( 59 ) ;
  printint ( w .hh .v.RH ) ;
  printchar ( 32 ) ;
  printint ( w .qqqq .b0 ) ;
  printchar ( 58 ) ;
  printint ( w .qqqq .b1 ) ;
  printchar ( 58 ) ;
  printint ( w .qqqq .b2 ) ;
  printchar ( 58 ) ;
  printint ( w .qqqq .b3 ) ;
} 
#endif /* TEXMF_DEBUG */
void 
zshowtokenlist ( integer p , integer q , integer l ) 
{
  /* 10 */ showtokenlist_regmem 
  integer m, c  ;
  ASCIIcode matchchr  ;
  ASCIIcode n  ;
  matchchr = 35 ;
  n = 48 ;
  tally = 0 ;
  while ( ( p != -268435455L ) && ( tally < l ) ) {
      
    if ( p == q ) 
    {
      firstcount = tally ;
      trickcount = tally + 1 + errorline - halferrorline ;
      if ( trickcount < errorline ) 
      trickcount = errorline ;
    } 
    if ( ( p < himemmin ) || ( p > memend ) ) 
    {
      printesc ( 314 ) ;
      return ;
    } 
    if ( mem [p ].hh .v.LH >= 4095 ) 
    printcs ( mem [p ].hh .v.LH - 4095 ) ;
    else {
	
      m = mem [p ].hh .v.LH / 256 ;
      c = mem [p ].hh .v.LH % 256 ;
      if ( mem [p ].hh .v.LH < 0 ) 
      printesc ( 633 ) ;
      else switch ( m ) 
      {case 1 : 
      case 2 : 
      case 3 : 
      case 4 : 
      case 7 : 
      case 8 : 
      case 10 : 
      case 11 : 
      case 12 : 
	print ( c ) ;
	break ;
      case 6 : 
	{
	  print ( c ) ;
	  print ( c ) ;
	} 
	break ;
      case 5 : 
	{
	  print ( matchchr ) ;
	  if ( c <= 9 ) 
	  printchar ( c + 48 ) ;
	  else {
	      
	    printchar ( 33 ) ;
	    return ;
	  } 
	} 
	break ;
      case 13 : 
	{
	  matchchr = c ;
	  print ( c ) ;
	  incr ( n ) ;
	  printchar ( n ) ;
	  if ( n > 57 ) 
	  return ;
	} 
	break ;
      case 14 : 
	if ( c == 0 ) 
	print ( 634 ) ;
	break ;
	default: 
	printesc ( 633 ) ;
	break ;
      } 
    } 
    p = mem [p ].hh .v.RH ;
  } 
  if ( p != -268435455L ) 
  printesc ( 428 ) ;
} 
void 
runaway ( void ) 
{
  runaway_regmem 
  halfword p  ;
  if ( scannerstatus > 1 ) 
  {
    switch ( scannerstatus ) 
    {case 2 : 
      {
	printnl ( 648 ) ;
	p = defref ;
      } 
      break ;
    case 3 : 
      {
	printnl ( 649 ) ;
	p = memtop - 3 ;
      } 
      break ;
    case 4 : 
      {
	printnl ( 650 ) ;
	p = memtop - 4 ;
      } 
      break ;
    case 5 : 
      {
	printnl ( 651 ) ;
	p = defref ;
      } 
      break ;
    } 
    printchar ( 63 ) ;
    println () ;
    showtokenlist ( mem [p ].hh .v.RH , -268435455L , errorline - 10 ) ;
  } 
} 
halfword 
getavail ( void ) 
{
  register halfword Result; getavail_regmem 
  halfword p  ;
  p = avail ;
  if ( p != -268435455L ) 
  avail = mem [avail ].hh .v.RH ;
  else if ( memend < memmax ) 
  {
    incr ( memend ) ;
    p = memend ;
  } 
  else {
      
    decr ( himemmin ) ;
    p = himemmin ;
    if ( himemmin <= lomemmax ) 
    {
      runaway () ;
      overflow ( 304 , memmax + 1 - memmin ) ;
    } 
  } 
  mem [p ].hh .v.RH = -268435455L ;
	;
#ifdef STAT
  incr ( dynused ) ;
#endif /* STAT */
  Result = p ;
  return Result ;
} 
void 
zflushlist ( halfword p ) 
{
  flushlist_regmem 
  halfword q, r  ;
  if ( p != -268435455L ) 
  {
    r = p ;
    do {
	q = r ;
      r = mem [r ].hh .v.RH ;
	;
#ifdef STAT
      decr ( dynused ) ;
#endif /* STAT */
    } while ( ! ( r == -268435455L ) ) ;
    mem [q ].hh .v.RH = avail ;
    avail = p ;
  } 
} 
halfword 
zgetnode ( integer s ) 
{
  /* 40 10 20 */ register halfword Result; getnode_regmem 
  halfword p  ;
  halfword q  ;
  integer r  ;
  integer t  ;
  lab20: p = rover ;
  do {
      q = p + mem [p ].hh .v.LH ;
    while ( ( mem [q ].hh .v.RH == 268435455L ) ) {
	
      t = mem [q + 1 ].hh .v.RH ;
      if ( q == rover ) 
      rover = t ;
      mem [t + 1 ].hh .v.LH = mem [q + 1 ].hh .v.LH ;
      mem [mem [q + 1 ].hh .v.LH + 1 ].hh .v.RH = t ;
      q = q + mem [q ].hh .v.LH ;
    } 
    r = q - s ;
    if ( r > p + 1 ) 
    {
      mem [p ].hh .v.LH = r - p ;
      rover = p ;
      goto lab40 ;
    } 
    if ( r == p ) {
	
      if ( mem [p + 1 ].hh .v.RH != p ) 
      {
	rover = mem [p + 1 ].hh .v.RH ;
	t = mem [p + 1 ].hh .v.LH ;
	mem [rover + 1 ].hh .v.LH = t ;
	mem [t + 1 ].hh .v.RH = rover ;
	goto lab40 ;
      } 
    } 
    mem [p ].hh .v.LH = q - p ;
    p = mem [p + 1 ].hh .v.RH ;
  } while ( ! ( p == rover ) ) ;
  if ( s == 1073741824L ) 
  {
    Result = 268435455L ;
    return Result ;
  } 
  if ( lomemmax + 2 < himemmin ) {
      
    if ( lomemmax + 2 <= membot + 268435455L ) 
    {
      if ( himemmin - lomemmax >= 1998 ) 
      t = lomemmax + 1000 ;
      else t = lomemmax + 1 + ( himemmin - lomemmax ) / 2 ;
      p = mem [rover + 1 ].hh .v.LH ;
      q = lomemmax ;
      mem [p + 1 ].hh .v.RH = q ;
      mem [rover + 1 ].hh .v.LH = q ;
      if ( t > membot + 268435455L ) 
      t = membot + 268435455L ;
      mem [q + 1 ].hh .v.RH = rover ;
      mem [q + 1 ].hh .v.LH = p ;
      mem [q ].hh .v.RH = 268435455L ;
      mem [q ].hh .v.LH = t - lomemmax ;
      lomemmax = t ;
      mem [lomemmax ].hh .v.RH = -268435455L ;
      mem [lomemmax ].hh .v.LH = -268435455L ;
      rover = q ;
      goto lab20 ;
    } 
  } 
  overflow ( 304 , memmax + 1 - memmin ) ;
  lab40: mem [r ].hh .v.RH = -268435455L ;
	;
#ifdef STAT
  varused = varused + s ;
#endif /* STAT */
  Result = r ;
  return Result ;
} 
void 
zfreenode ( halfword p , halfword s ) 
{
  freenode_regmem 
  halfword q  ;
  mem [p ].hh .v.LH = s ;
  mem [p ].hh .v.RH = 268435455L ;
  q = mem [rover + 1 ].hh .v.LH ;
  mem [p + 1 ].hh .v.LH = q ;
  mem [p + 1 ].hh .v.RH = rover ;
  mem [rover + 1 ].hh .v.LH = p ;
  mem [q + 1 ].hh .v.RH = p ;
	;
#ifdef STAT
  varused = varused - s ;
#endif /* STAT */
} 
halfword 
newnullbox ( void ) 
{
  register halfword Result; newnullbox_regmem 
  halfword p  ;
  p = getnode ( 7 ) ;
  mem [p ].hh.b0 = 0 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].cint = 0 ;
  mem [p + 2 ].cint = 0 ;
  mem [p + 3 ].cint = 0 ;
  mem [p + 4 ].cint = 0 ;
  mem [p + 5 ].hh .v.RH = -268435455L ;
  mem [p + 5 ].hh.b0 = 0 ;
  mem [p + 5 ].hh.b1 = 0 ;
  mem [p + 6 ].gr = 0.0 ;
  Result = p ;
  return Result ;
} 
halfword 
newrule ( void ) 
{
  register halfword Result; newrule_regmem 
  halfword p  ;
  p = getnode ( 4 ) ;
  mem [p ].hh.b0 = 2 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].cint = -1073741824L ;
  mem [p + 2 ].cint = -1073741824L ;
  mem [p + 3 ].cint = -1073741824L ;
  Result = p ;
  return Result ;
} 
halfword 
znewligature ( internalfontnumber f , quarterword c , halfword q ) 
{
  register halfword Result; newligature_regmem 
  halfword p  ;
  p = getnode ( 2 ) ;
  mem [p ].hh.b0 = 6 ;
  mem [p + 1 ].hh.b0 = f ;
  mem [p + 1 ].hh.b1 = c ;
  mem [p + 1 ].hh .v.RH = q ;
  mem [p ].hh.b1 = 0 ;
  Result = p ;
  return Result ;
} 
halfword 
znewligitem ( quarterword c ) 
{
  register halfword Result; newligitem_regmem 
  halfword p  ;
  p = getnode ( 2 ) ;
  mem [p ].hh.b1 = c ;
  mem [p + 1 ].hh .v.RH = -268435455L ;
  Result = p ;
  return Result ;
} 
halfword 
newdisc ( void ) 
{
  register halfword Result; newdisc_regmem 
  halfword p  ;
  p = getnode ( 2 ) ;
  mem [p ].hh.b0 = 7 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].hh .v.LH = -268435455L ;
  mem [p + 1 ].hh .v.RH = -268435455L ;
  Result = p ;
  return Result ;
} 
halfword 
znewmath ( scaled w , smallnumber s ) 
{
  register halfword Result; newmath_regmem 
  halfword p  ;
  p = getnode ( 2 ) ;
  mem [p ].hh.b0 = 9 ;
  mem [p ].hh.b1 = s ;
  mem [p + 1 ].cint = w ;
  Result = p ;
  return Result ;
} 
halfword 
znewspec ( halfword p ) 
{
  register halfword Result; newspec_regmem 
  halfword q  ;
  q = getnode ( 4 ) ;
  mem [q ]= mem [p ];
  mem [q ].hh .v.RH = -268435455L ;
  mem [q + 1 ].cint = mem [p + 1 ].cint ;
  mem [q + 2 ].cint = mem [p + 2 ].cint ;
  mem [q + 3 ].cint = mem [p + 3 ].cint ;
  Result = q ;
  return Result ;
} 
halfword 
znewparamglue ( smallnumber n ) 
{
  register halfword Result; newparamglue_regmem 
  halfword p  ;
  halfword q  ;
  p = getnode ( 2 ) ;
  mem [p ].hh.b0 = 10 ;
  mem [p ].hh.b1 = n + 1 ;
  mem [p + 1 ].hh .v.RH = -268435455L ;
  q = eqtb [26628 + n ].hh .v.RH ;
  mem [p + 1 ].hh .v.LH = q ;
  incr ( mem [q ].hh .v.RH ) ;
  Result = p ;
  return Result ;
} 
halfword 
znewglue ( halfword q ) 
{
  register halfword Result; newglue_regmem 
  halfword p  ;
  p = getnode ( 2 ) ;
  mem [p ].hh.b0 = 10 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].hh .v.RH = -268435455L ;
  mem [p + 1 ].hh .v.LH = q ;
  incr ( mem [q ].hh .v.RH ) ;
  Result = p ;
  return Result ;
} 
halfword 
znewskipparam ( smallnumber n ) 
{
  register halfword Result; newskipparam_regmem 
  halfword p  ;
  tempptr = newspec ( eqtb [26628 + n ].hh .v.RH ) ;
  p = newglue ( tempptr ) ;
  mem [tempptr ].hh .v.RH = -268435455L ;
  mem [p ].hh.b1 = n + 1 ;
  Result = p ;
  return Result ;
} 
halfword 
znewkern ( scaled w ) 
{
  register halfword Result; newkern_regmem 
  halfword p  ;
  p = getnode ( 2 ) ;
  mem [p ].hh.b0 = 11 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].cint = w ;
  Result = p ;
  return Result ;
} 
halfword 
znewpenalty ( integer m ) 
{
  register halfword Result; newpenalty_regmem 
  halfword p  ;
  p = getnode ( 2 ) ;
  mem [p ].hh.b0 = 12 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].cint = m ;
  Result = p ;
  return Result ;
} 
#ifdef TEXMF_DEBUG
void 
zcheckmem ( boolean printlocs ) 
{
  /* 31 32 */ checkmem_regmem 
  halfword p, q  ;
  boolean clobbered  ;
  {register integer for_end; p = memmin ;for_end = lomemmax ; if ( p <= 
  for_end) do 
    freearr [p ]= false ;
  while ( p++ < for_end ) ;} 
  {register integer for_end; p = himemmin ;for_end = memend ; if ( p <= 
  for_end) do 
    freearr [p ]= false ;
  while ( p++ < for_end ) ;} 
  p = avail ;
  q = -268435455L ;
  clobbered = false ;
  while ( p != -268435455L ) {
      
    if ( ( p > memend ) || ( p < himemmin ) ) 
    clobbered = true ;
    else if ( freearr [p ]) 
    clobbered = true ;
    if ( clobbered ) 
    {
      printnl ( 305 ) ;
      printint ( q ) ;
      goto lab31 ;
    } 
    freearr [p ]= true ;
    q = p ;
    p = mem [q ].hh .v.RH ;
  } 
  lab31: ;
  p = rover ;
  q = -268435455L ;
  clobbered = false ;
  do {
      if ( ( p >= lomemmax ) || ( p < memmin ) ) 
    clobbered = true ;
    else if ( ( mem [p + 1 ].hh .v.RH >= lomemmax ) || ( mem [p + 1 ].hh 
    .v.RH < memmin ) ) 
    clobbered = true ;
    else if ( ! ( ( mem [p ].hh .v.RH == 268435455L ) ) || ( mem [p ].hh 
    .v.LH < 2 ) || ( p + mem [p ].hh .v.LH > lomemmax ) || ( mem [mem [p + 
    1 ].hh .v.RH + 1 ].hh .v.LH != p ) ) 
    clobbered = true ;
    if ( clobbered ) 
    {
      printnl ( 306 ) ;
      printint ( q ) ;
      goto lab32 ;
    } 
    {register integer for_end; q = p ;for_end = p + mem [p ].hh .v.LH - 1 
    ; if ( q <= for_end) do 
      {
	if ( freearr [q ]) 
	{
	  printnl ( 307 ) ;
	  printint ( q ) ;
	  goto lab32 ;
	} 
	freearr [q ]= true ;
      } 
    while ( q++ < for_end ) ;} 
    q = p ;
    p = mem [p + 1 ].hh .v.RH ;
  } while ( ! ( p == rover ) ) ;
  lab32: ;
  p = memmin ;
  while ( p <= lomemmax ) {
      
    if ( ( mem [p ].hh .v.RH == 268435455L ) ) 
    {
      printnl ( 308 ) ;
      printint ( p ) ;
    } 
    while ( ( p <= lomemmax ) && ! freearr [p ]) incr ( p ) ;
    while ( ( p <= lomemmax ) && freearr [p ]) incr ( p ) ;
  } 
  if ( printlocs ) 
  {
    printnl ( 309 ) ;
    {register integer for_end; p = memmin ;for_end = lomemmax ; if ( p <= 
    for_end) do 
      if ( ! freearr [p ]&& ( ( p > waslomax ) || wasfree [p ]) ) 
      {
	printchar ( 32 ) ;
	printint ( p ) ;
      } 
    while ( p++ < for_end ) ;} 
    {register integer for_end; p = himemmin ;for_end = memend ; if ( p <= 
    for_end) do 
      if ( ! freearr [p ]&& ( ( p < washimin ) || ( p > wasmemend ) || 
      wasfree [p ]) ) 
      {
	printchar ( 32 ) ;
	printint ( p ) ;
      } 
    while ( p++ < for_end ) ;} 
  } 
  {register integer for_end; p = memmin ;for_end = lomemmax ; if ( p <= 
  for_end) do 
    wasfree [p ]= freearr [p ];
  while ( p++ < for_end ) ;} 
  {register integer for_end; p = himemmin ;for_end = memend ; if ( p <= 
  for_end) do 
    wasfree [p ]= freearr [p ];
  while ( p++ < for_end ) ;} 
  wasmemend = memend ;
  waslomax = lomemmax ;
  washimin = himemmin ;
} 
#endif /* TEXMF_DEBUG */
#ifdef TEXMF_DEBUG
void 
zsearchmem ( halfword p ) 
{
  searchmem_regmem 
  integer q  ;
  {register integer for_end; q = memmin ;for_end = lomemmax ; if ( q <= 
  for_end) do 
    {
      if ( mem [q ].hh .v.RH == p ) 
      {
	printnl ( 310 ) ;
	printint ( q ) ;
	printchar ( 41 ) ;
      } 
      if ( mem [q ].hh .v.LH == p ) 
      {
	printnl ( 311 ) ;
	printint ( q ) ;
	printchar ( 41 ) ;
      } 
    } 
  while ( q++ < for_end ) ;} 
  {register integer for_end; q = himemmin ;for_end = memend ; if ( q <= 
  for_end) do 
    {
      if ( mem [q ].hh .v.RH == p ) 
      {
	printnl ( 310 ) ;
	printint ( q ) ;
	printchar ( 41 ) ;
      } 
      if ( mem [q ].hh .v.LH == p ) 
      {
	printnl ( 311 ) ;
	printint ( q ) ;
	printchar ( 41 ) ;
      } 
    } 
  while ( q++ < for_end ) ;} 
  {register integer for_end; q = 1 ;for_end = 27688 ; if ( q <= for_end) do 
    {
      if ( eqtb [q ].hh .v.RH == p ) 
      {
	printnl ( 571 ) ;
	printint ( q ) ;
	printchar ( 41 ) ;
      } 
    } 
  while ( q++ < for_end ) ;} 
  if ( saveptr > 0 ) 
  {register integer for_end; q = 0 ;for_end = saveptr - 1 ; if ( q <= 
  for_end) do 
    {
      if ( savestack [q ].hh .v.RH == p ) 
      {
	printnl ( 625 ) ;
	printint ( q ) ;
	printchar ( 41 ) ;
      } 
    } 
  while ( q++ < for_end ) ;} 
  {register integer for_end; q = 0 ;for_end = hyphsize ; if ( q <= for_end) 
  do 
    {
      if ( hyphlist [q ]== p ) 
      {
	printnl ( 1346 ) ;
	printint ( q ) ;
	printchar ( 41 ) ;
      } 
    } 
  while ( q++ < for_end ) ;} 
} 
#endif /* TEXMF_DEBUG */
void 
zpdferror ( strnumber t , strnumber p ) 
{
  pdferror_regmem 
  normalizeselector () ;
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 264 ) ;
    print ( 1016 ) ;
  } 
  if ( t != 0 ) 
  {
    print ( 286 ) ;
    print ( t ) ;
    print ( 41 ) ;
  } 
  print ( 646 ) ;
  print ( p ) ;
  {
    if ( interaction == 3 ) 
    interaction = 2 ;
    if ( logopened ) 
    error () ;
	;
#ifdef TEXMF_DEBUG
    if ( interaction > 0 ) 
    debughelp () ;
#endif /* TEXMF_DEBUG */
    history = 3 ;
    jumpout () ;
  } 
} 
void 
zpdfwarning ( strnumber t , strnumber p , boolean prependnl , boolean appendnl 
) 
{
  pdfwarning_regmem 
  if ( interaction == 3 ) 
  ;
  if ( prependnl ) 
  println () ;
  print ( 1017 ) ;
  if ( t != 0 ) 
  {
    print ( 286 ) ;
    print ( t ) ;
    print ( 41 ) ;
  } 
  print ( 646 ) ;
  print ( p ) ;
  if ( appendnl ) 
  println () ;
  if ( history == 0 ) 
  history = 1 ;
} 
void 
zpdfosgetosbuf ( integer s ) 
{
  pdfosgetosbuf_regmem 
  integer a  ;
  if ( s > suppdfosbufsize - pdfptr ) 
  overflow ( 1018 , pdfosbufsize ) ;
  if ( pdfptr + s > pdfosbufsize ) 
  {
    a = 0.2 * pdfosbufsize ;
    if ( pdfptr + s > pdfosbufsize + a ) 
    pdfosbufsize = pdfptr + s ;
    else if ( pdfosbufsize < suppdfosbufsize - a ) 
    pdfosbufsize = pdfosbufsize + a ;
    else pdfosbufsize = suppdfosbufsize ;
    pdfosbuf = xreallocarray ( pdfosbuf , eightbits , pdfosbufsize ) ;
    pdfbuf = pdfosbuf ;
    pdfbufsize = pdfosbufsize ;
  } 
} 
void 
removelastspace ( void ) 
{
  removelastspace_regmem 
  if ( ( pdfptr > 0 ) && ( pdfbuf [pdfptr - 1 ]== 32 ) ) 
  decr ( pdfptr ) ;
} 
void 
zpdfprintoctal ( integer n ) 
{
  pdfprintoctal_regmem 
  unsigned char k  ;
  k = 0 ;
  do {
      dig [k ]= n % 8 ;
    n = n / 8 ;
    incr ( k ) ;
  } while ( ! ( n == 0 ) ) ;
  if ( k == 1 ) 
  {
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 48 ;
	incr ( pdfptr ) ;
      } 
    } 
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 48 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
  if ( k == 2 ) 
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 48 ;
      incr ( pdfptr ) ;
    } 
  } 
  while ( k > 0 ) {
      
    decr ( k ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 48 + dig [k ];
	incr ( pdfptr ) ;
      } 
    } 
  } 
} 
void 
zpdfprintchar ( internalfontnumber f , integer c ) 
{
  pdfprintchar_regmem 
  pdfmarkchar ( f , c ) ;
  if ( ( c <= 32 ) || ( c == 92 ) || ( c == 40 ) || ( c == 41 ) || ( c > 127 ) 
  ) 
  {
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 92 ;
	incr ( pdfptr ) ;
      } 
    } 
    pdfprintoctal ( c ) ;
  } 
  else {
      
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= c ;
      incr ( pdfptr ) ;
    } 
  } 
} 
void 
zpdfprint ( strnumber s ) 
{
  pdfprint_regmem 
  poolpointer j  ;
  integer c  ;
  j = strstart [s ];
  while ( j < strstart [s + 1 ]) {
      
    c = strpool [j ];
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= c ;
	incr ( pdfptr ) ;
      } 
    } 
    incr ( j ) ;
  } 
} 
boolean 
zstrinstr ( strnumber s , strnumber r , integer i ) 
{
  /* 45 */ register boolean Result; strinstr_regmem 
  poolpointer j, k  ;
  Result = false ;
  if ( ( strstart [s + 1 ]- strstart [s ]) < i + ( strstart [r + 1 ]- 
  strstart [r ]) ) 
  return Result ;
  j = i + strstart [s ];
  k = strstart [r ];
  while ( ( j < strstart [s + 1 ]) && ( k < strstart [r + 1 ]) ) {
      
    if ( strpool [j ]!= strpool [k ]) 
    return Result ;
    incr ( j ) ;
    incr ( k ) ;
  } 
  Result = true ;
  return Result ;
} 
void 
zpdfprintint ( longinteger n ) 
{
  pdfprintint_regmem 
  integer k  ;
  longinteger m  ;
  k = 0 ;
  if ( n < 0 ) 
  {
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 45 ;
	incr ( pdfptr ) ;
      } 
    } 
    if ( n > -100000000L ) 
    n = - (integer) n ;
    else {
	
      m = -1 - n ;
      n = m / 10 ;
      m = ( m % 10 ) + 1 ;
      k = 1 ;
      if ( m < 10 ) 
      dig [0 ]= m ;
      else {
	  
	dig [0 ]= 0 ;
	incr ( n ) ;
      } 
    } 
  } 
  do {
      dig [k ]= n % 10 ;
    n = n / 10 ;
    incr ( k ) ;
  } while ( ! ( n == 0 ) ) ;
  {
    if ( pdfosmode && ( k + pdfptr > pdfbufsize ) ) 
    pdfosgetosbuf ( k ) ;
    else if ( ! pdfosmode && ( k > pdfbufsize ) ) 
    overflow ( 999 , pdfopbufsize ) ;
    else if ( ! pdfosmode && ( k + pdfptr > pdfbufsize ) ) 
    pdfflush () ;
  } 
  while ( k > 0 ) {
      
    decr ( k ) ;
    {
      pdfbuf [pdfptr ]= 48 + dig [k ];
      incr ( pdfptr ) ;
    } 
  } 
} 
void 
zpdfprinttwo ( integer n ) 
{
  pdfprinttwo_regmem 
  n = abs ( n ) % 100 ;
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 48 + ( n / 10 ) ;
      incr ( pdfptr ) ;
    } 
  } 
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 48 + ( n % 10 ) ;
      incr ( pdfptr ) ;
    } 
  } 
} 
strnumber 
ztokenstostring ( halfword p ) 
{
  register strnumber Result; tokenstostring_regmem 
  if ( selector == 21 ) 
  pdferror ( 1019 , 1020 ) ;
  oldsetting = selector ;
  selector = 21 ;
  showtokenlist ( mem [p ].hh .v.RH , -268435455L , poolsize - poolptr ) ;
  selector = oldsetting ;
  lasttokensstring = makestring () ;
  Result = lasttokensstring ;
  return Result ;
} 
scaled 
zdividescaled ( scaled s , scaled m , integer dd ) 
{
  register scaled Result; dividescaled_regmem 
  scaled q, r  ;
  integer sign, i  ;
  sign = 1 ;
  if ( s < 0 ) 
  {
    sign = - (integer) sign ;
    s = - (integer) s ;
  } 
  if ( m < 0 ) 
  {
    sign = - (integer) sign ;
    m = - (integer) m ;
  } 
  if ( m == 0 ) 
  pdferror ( 1021 , 1022 ) ;
  else if ( m >= ( 2147483647L / 10 ) ) 
  pdferror ( 1021 , 1023 ) ;
  q = s / m ;
  r = s % m ;
  {register integer for_end; i = 1 ;for_end = dd ; if ( i <= for_end) do 
    {
      q = 10 * q + ( 10 * r ) / m ;
      r = ( 10 * r ) % m ;
    } 
  while ( i++ < for_end ) ;} 
  if ( 2 * r >= m ) 
  {
    incr ( q ) ;
    r = r - m ;
  } 
  scaledout = sign * ( s - ( r / tenpow [dd ]) ) ;
  Result = sign * q ;
  return Result ;
} 
scaled 
zroundxnoverd ( scaled x , integer n , integer d ) 
{
  register scaled Result; roundxnoverd_regmem 
  boolean positive  ;
  nonnegativeinteger t, u, v  ;
  if ( x >= 0 ) 
  positive = true ;
  else {
      
    x = - (integer) x ;
    positive = false ;
  } 
  t = ( x % 32768L ) * n ;
  u = ( x / 32768L ) * n + ( t / 32768L ) ;
  v = ( u % d ) * 32768L + ( t % 32768L ) ;
  if ( u / d >= 32768L ) 
  aritherror = true ;
  else u = 32768L * ( u / d ) + ( v / d ) ;
  v = v % d ;
  if ( 2 * v >= d ) 
  incr ( u ) ;
  if ( positive ) 
  Result = u ;
  else Result = - (integer) u ;
  return Result ;
} 
void 
zappenddestname ( strnumber s , integer n ) 
{
  appenddestname_regmem 
  integer a  ;
  if ( pdfdestnamesptr == supdestnamessize ) 
  overflow ( 1063 , destnamessize ) ;
  if ( pdfdestnamesptr == destnamessize ) 
  {
    a = 0.2 * destnamessize ;
    if ( destnamessize < supdestnamessize - a ) 
    destnamessize = destnamessize + a ;
    else destnamessize = supdestnamessize ;
    destnames = xreallocarray ( destnames , destnameentry , destnamessize ) ;
  } 
  destnames [pdfdestnamesptr ].objname = s ;
  destnames [pdfdestnamesptr ].objnum = n ;
  incr ( pdfdestnamesptr ) ;
} 
void 
zpdfcreateobj ( integer t , integer i ) 
{
  /* 30 */ pdfcreateobj_regmem 
  integer a, p, q  ;
  if ( sysobjptr == supobjtabsize ) 
  overflow ( 1064 , objtabsize ) ;
  if ( sysobjptr == objtabsize ) 
  {
    a = 0.2 * objtabsize ;
    if ( objtabsize < supobjtabsize - a ) 
    objtabsize = objtabsize + a ;
    else objtabsize = supobjtabsize ;
    objtab = xreallocarray ( objtab , objentry , objtabsize ) ;
  } 
  incr ( sysobjptr ) ;
  objptr = sysobjptr ;
  objtab [objptr ].int0 = i ;
  objtab [objptr ].int2 = -2 ;
  objtab [objptr ].int4 = 0 ;
  avlputobj ( objptr , t ) ;
  if ( t == 1 ) 
  {
    p = headtab [t ];
    if ( ( p == 0 ) || ( objtab [p ].int0 < i ) ) 
    {
      objtab [objptr ].int1 = p ;
      headtab [t ]= objptr ;
    } 
    else {
	
      while ( p != 0 ) {
	  
	if ( objtab [p ].int0 < i ) 
	goto lab30 ;
	q = p ;
	p = objtab [p ].int1 ;
      } 
      lab30: objtab [q ].int1 = objptr ;
      objtab [objptr ].int1 = p ;
    } 
  } 
  else if ( t != 0 ) 
  {
    objtab [objptr ].int1 = headtab [t ];
    headtab [t ]= objptr ;
    if ( ( t == 5 ) && ( i < 0 ) ) 
    appenddestname ( - (integer) objtab [objptr ].int0 , objptr ) ;
  } 
} 
integer 
pdfnewobjnum ( void ) 
{
  register integer Result; pdfnewobjnum_regmem 
  pdfcreateobj ( 0 , 0 ) ;
  Result = objptr ;
  return Result ;
} 
void 
zpdfosswitch ( boolean pdfos ) 
{
  pdfosswitch_regmem 
  if ( pdfos && pdfosenable ) 
  {
    if ( ! pdfosmode ) 
    {
      pdfopptr = pdfptr ;
      pdfptr = pdfosptr ;
      pdfbuf = pdfosbuf ;
      pdfbufsize = pdfosbufsize ;
      pdfosmode = true ;
    } 
  } 
  else {
      
    if ( pdfosmode ) 
    {
      pdfosptr = pdfptr ;
      pdfptr = pdfopptr ;
      pdfbuf = pdfopbuf ;
      pdfbufsize = pdfopbufsize ;
      pdfosmode = false ;
    } 
  } 
} 
void 
zpdfosprepareobj ( integer i , integer pdfoslevel ) 
{
  pdfosprepareobj_regmem 
  pdfosswitch ( ( pdfoslevel > 0 ) && ( fixedpdfobjcompresslevel >= pdfoslevel 
  ) ) ;
  if ( pdfosmode ) 
  {
    if ( pdfoscurobjnum == 0 ) 
    {
      pdfoscurobjnum = pdfnewobjnum () ;
      decr ( objptr ) ;
      incr ( pdfoscntr ) ;
      pdfosobjidx = 0 ;
      pdfptr = 0 ;
    } 
    else incr ( pdfosobjidx ) ;
    objtab [i ].int3 = pdfosobjidx ;
    objtab [i ].int2 = pdfoscurobjnum ;
    pdfosobjnum [pdfosobjidx ]= i ;
    pdfosobjoff [pdfosobjidx ]= pdfptr ;
  } 
  else {
      
    objtab [i ].int2 = ( pdfgone + pdfptr ) ;
    objtab [i ].int3 = -1 ;
  } 
} 
void 
zpdfbeginobj ( integer i , integer pdfoslevel ) 
{
  pdfbeginobj_regmem 
  checkpdfminorversion () ;
  pdfosprepareobj ( i , pdfoslevel ) ;
  if ( ! pdfosmode ) 
  {
    pdfprintint ( i ) ;
    {
      pdfprint ( 1065 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
  } 
  else if ( eqtb [29333 ].cint == 0 ) 
  {
    pdfprint ( 1066 ) ;
    pdfprintint ( i ) ;
    {
      pdfprint ( 1065 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
  } 
} 
void 
zpdfnewobj ( integer t , integer i , integer pdfos ) 
{
  pdfnewobj_regmem 
  pdfcreateobj ( t , i ) ;
  pdfbeginobj ( objptr , pdfos ) ;
} 
void 
pdfendobj ( void ) 
{
  pdfendobj_regmem 
  if ( pdfosmode ) 
  {
    if ( pdfosobjidx == pdfosmaxobjs - 1 ) 
    pdfoswriteobjstream () ;
  } 
  else {
      
    pdfprint ( 1067 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
} 
void 
zpdfbegindict ( integer i , integer pdfoslevel ) 
{
  pdfbegindict_regmem 
  checkpdfminorversion () ;
  pdfosprepareobj ( i , pdfoslevel ) ;
  if ( ! pdfosmode ) 
  {
    pdfprintint ( i ) ;
    {
      pdfprint ( 1065 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
  } 
  else if ( eqtb [29333 ].cint == 0 ) 
  {
    pdfprint ( 1066 ) ;
    pdfprintint ( i ) ;
    {
      pdfprint ( 1065 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
  } 
  {
    pdfprint ( 1068 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
} 
void 
zpdfnewdict ( integer t , integer i , integer pdfos ) 
{
  pdfnewdict_regmem 
  pdfcreateobj ( t , i ) ;
  pdfbegindict ( objptr , pdfos ) ;
} 
void 
pdfenddict ( void ) 
{
  pdfenddict_regmem 
  if ( pdfosmode ) 
  {
    {
      pdfprint ( 1013 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
    if ( pdfosobjidx == pdfosmaxobjs - 1 ) 
    pdfoswriteobjstream () ;
  } 
  else {
      
    {
      pdfprint ( 1013 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
    {
      pdfprint ( 1067 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
  } 
} 
void 
pdfoswriteobjstream ( void ) 
{
  pdfoswriteobjstream_regmem 
  halfword i, j, p, q  ;
  if ( pdfoscurobjnum == 0 ) 
  return ;
  p = pdfptr ;
  i = 0 ;
  j = 0 ;
  while ( i <= pdfosobjidx ) {
      
    pdfprintint ( pdfosobjnum [i ]) ;
    pdfprint ( 32 ) ;
    pdfprintint ( pdfosobjoff [i ]) ;
    if ( j == 9 ) 
    {
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
      j = 0 ;
    } 
    else {
	
      pdfprint ( 32 ) ;
      incr ( j ) ;
    } 
    incr ( i ) ;
  } 
  pdfbuf [pdfptr - 1 ]= 10 ;
  q = pdfptr ;
  pdfbegindict ( pdfoscurobjnum , 0 ) ;
  {
    pdfprint ( 1069 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
  pdfprint ( 1070 ) ;
  {
    pdfprintint ( pdfosobjidx + 1 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
  pdfprint ( 1071 ) ;
  {
    pdfprintint ( q - p ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
  pdfbeginstream () ;
  {
    if ( pdfosmode && ( q - p + pdfptr > pdfbufsize ) ) 
    pdfosgetosbuf ( q - p ) ;
    else if ( ! pdfosmode && ( q - p > pdfbufsize ) ) 
    overflow ( 999 , pdfopbufsize ) ;
    else if ( ! pdfosmode && ( q - p + pdfptr > pdfbufsize ) ) 
    pdfflush () ;
  } 
  i = p ;
  while ( i < q ) {
      
    {
      pdfbuf [pdfptr ]= pdfosbuf [i ];
      incr ( pdfptr ) ;
    } 
    incr ( i ) ;
  } 
  i = 0 ;
  while ( i < p ) {
      
    q = i + pdfbufsize ;
    if ( q > p ) 
    q = p ;
    {
      if ( pdfosmode && ( q - i + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( q - i ) ;
      else if ( ! pdfosmode && ( q - i > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( q - i + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    while ( i < q ) {
	
      {
	pdfbuf [pdfptr ]= pdfosbuf [i ];
	incr ( pdfptr ) ;
      } 
      incr ( i ) ;
    } 
  } 
  pdfendstream () ;
  pdfoscurobjnum = 0 ;
} 
halfword 
zappendptr ( halfword p , integer i ) 
{
  register halfword Result; appendptr_regmem 
  halfword q  ;
  Result = p ;
  {
    q = avail ;
    if ( q == -268435455L ) 
    q = getavail () ;
    else {
	
      avail = mem [q ].hh .v.RH ;
      mem [q ].hh .v.RH = -268435455L ;
	;
#ifdef STAT
      incr ( dynused ) ;
#endif /* STAT */
    } 
  } 
  mem [q ].hh .v.LH = i ;
  mem [q ].hh .v.RH = -268435455L ;
  if ( p == -268435455L ) 
  {
    Result = q ;
    return Result ;
  } 
  while ( mem [p ].hh .v.RH != -268435455L ) p = mem [p ].hh .v.RH ;
  mem [p ].hh .v.RH = q ;
  return Result ;
} 
halfword 
zpdflookuplist ( halfword p , integer i ) 
{
  register halfword Result; pdflookuplist_regmem 
  Result = -268435455L ;
  while ( p != -268435455L ) {
      
    if ( mem [p ].hh .v.LH == i ) 
    {
      Result = p ;
      return Result ;
    } 
    p = mem [p ].hh .v.RH ;
  } 
  return Result ;
} 
halfword 
zprevrightmost ( halfword s , halfword e ) 
{
  register halfword Result; prevrightmost_regmem 
  halfword p  ;
  Result = -268435455L ;
  p = s ;
  if ( p == -268435455L ) 
  return Result ;
  while ( mem [p ].hh .v.RH != e ) {
      
    p = mem [p ].hh .v.RH ;
    if ( p == -268435455L ) 
    return Result ;
  } 
  Result = p ;
  return Result ;
} 
void 
zpdfcheckobj ( integer t , integer n ) 
{
  pdfcheckobj_regmem 
  integer k  ;
  k = headtab [t ];
  while ( ( k != 0 ) && ( k != n ) ) k = objtab [k ].int1 ;
  if ( k == 0 ) 
  pdferror ( 1758 , 1784 ) ;
} 
integer 
zfindobj ( integer t , integer i , boolean byname ) 
{
  register integer Result; findobj_regmem 
  Result = avlfindobj ( t , i , byname ) ;
  return Result ;
} 
void 
zflushstr ( strnumber s ) 
{
  flushstr_regmem 
  if ( ( s == strptr - 1 ) ) 
  {
    decr ( strptr ) ;
    poolptr = strstart [strptr ];
  } 
} 
integer 
zgetobj ( integer t , integer i , boolean byname ) 
{
  register integer Result; getobj_regmem 
  integer r  ;
  strnumber s  ;
  if ( byname > 0 ) 
  {
    s = tokenstostring ( i ) ;
    r = findobj ( t , s , true ) ;
  } 
  else {
      
    s = 0 ;
    r = findobj ( t , i , false ) ;
  } 
  if ( r == 0 ) 
  {
    if ( byname > 0 ) 
    {
      pdfcreateobj ( t , - (integer) s ) ;
      s = 0 ;
    } 
    else pdfcreateobj ( t , i ) ;
    r = objptr ;
    if ( t == 5 ) 
    objtab [r ].int4 = -268435455L ;
  } 
  if ( s != 0 ) 
  flushstr ( s ) ;
  Result = r ;
  return Result ;
} 
integer 
getmicrointerval ( void ) 
{
  register integer Result; getmicrointerval_regmem 
  integer s, m  ;
  secondsandmicros ( s , m ) ;
  if ( ( s - epochseconds ) > 32767 ) 
  Result = 2147483647L ;
  else if ( ( microseconds > m ) ) 
  Result = ( ( s - 1 - epochseconds ) * 65536L ) + ( ( ( m + 1000000L - 
  microseconds ) / ((double) 100 ) ) * 65536L ) / ((double) 10000 ) ;
  else Result = ( ( s - epochseconds ) * 65536L ) + ( ( ( m - microseconds ) 
  / ((double) 100 ) ) * 65536L ) / ((double) 10000 ) ;
  return Result ;
} 
void 
zprintfontidentifier ( internalfontnumber f ) 
{
  printfontidentifier_regmem 
  if ( pdffontblink [f ]== 0 ) 
  printesc ( hash [17626 + f ].v.RH ) ;
  else printesc ( hash [17626 + pdffontblink [f ]].v.RH ) ;
  if ( eqtb [29351 ].cint > 0 ) 
  {
    print ( 286 ) ;
    print ( fontname [f ]) ;
    if ( fontsize [f ]!= fontdsize [f ]) 
    {
      print ( 64 ) ;
      printscaled ( fontsize [f ]) ;
      print ( 312 ) ;
    } 
    print ( 41 ) ;
  } 
  else if ( pdffontexpandratio [f ]!= 0 ) 
  {
    print ( 286 ) ;
    if ( pdffontexpandratio [f ]> 0 ) 
    print ( 43 ) ;
    printint ( pdffontexpandratio [f ]) ;
    print ( 41 ) ;
  } 
} 
void 
zshortdisplay ( integer p ) 
{
  shortdisplay_regmem 
  integer n  ;
  while ( p > memmin ) {
      
    if ( ( p >= himemmin ) ) 
    {
      if ( p <= memend ) 
      {
	if ( mem [p ].hh.b0 != fontinshortdisplay ) 
	{
	  if ( ( mem [p ].hh.b0 > fontmax ) ) 
	  printchar ( 42 ) ;
	  else printfontidentifier ( mem [p ].hh.b0 ) ;
	  printchar ( 32 ) ;
	  fontinshortdisplay = mem [p ].hh.b0 ;
	} 
	print ( mem [p ].hh.b1 ) ;
      } 
    } 
    else switch ( mem [p ].hh.b0 ) 
    {case 0 : 
    case 1 : 
    case 3 : 
    case 8 : 
    case 4 : 
    case 5 : 
    case 13 : 
      print ( 313 ) ;
      break ;
    case 2 : 
      printchar ( 124 ) ;
      break ;
    case 10 : 
      if ( mem [p + 1 ].hh .v.LH != membot ) 
      printchar ( 32 ) ;
      break ;
    case 9 : 
      if ( mem [p ].hh.b1 >= 4 ) 
      print ( 313 ) ;
      else printchar ( 36 ) ;
      break ;
    case 6 : 
      shortdisplay ( mem [p + 1 ].hh .v.RH ) ;
      break ;
    case 7 : 
      {
	shortdisplay ( mem [p + 1 ].hh .v.LH ) ;
	shortdisplay ( mem [p + 1 ].hh .v.RH ) ;
	n = mem [p ].hh.b1 ;
	while ( n > 0 ) {
	    
	  if ( mem [p ].hh .v.RH != -268435455L ) 
	  p = mem [p ].hh .v.RH ;
	  decr ( n ) ;
	} 
      } 
      break ;
      default: 
      ;
      break ;
    } 
    p = mem [p ].hh .v.RH ;
  } 
} 
void 
zprintfontandchar ( integer p ) 
{
  printfontandchar_regmem 
  if ( p > memend ) 
  printesc ( 314 ) ;
  else {
      
    if ( ( mem [p ].hh.b0 > fontmax ) ) 
    printchar ( 42 ) ;
    else printfontidentifier ( mem [p ].hh.b0 ) ;
    printchar ( 32 ) ;
    print ( mem [p ].hh.b1 ) ;
  } 
} 
void 
zprintmark ( integer p ) 
{
  printmark_regmem 
  printchar ( 123 ) ;
  if ( ( p < himemmin ) || ( p > memend ) ) 
  printesc ( 314 ) ;
  else showtokenlist ( mem [p ].hh .v.RH , -268435455L , maxprintline - 10 ) 
  ;
  printchar ( 125 ) ;
} 
void 
zprintruledimen ( scaled d ) 
{
  printruledimen_regmem 
  if ( ( d == -1073741824L ) ) 
  printchar ( 42 ) ;
  else printscaled ( d ) ;
} 
void 
zprintglue ( scaled d , integer order , strnumber s ) 
{
  printglue_regmem 
  printscaled ( d ) ;
  if ( ( order < 0 ) || ( order > 3 ) ) 
  print ( 315 ) ;
  else if ( order > 0 ) 
  {
    print ( 316 ) ;
    while ( order > 1 ) {
	
      printchar ( 108 ) ;
      decr ( order ) ;
    } 
  } 
  else if ( s != 0 ) 
  print ( s ) ;
} 
void 
zprintspec ( integer p , strnumber s ) 
{
  printspec_regmem 
  if ( ( p < memmin ) || ( p >= lomemmax ) ) 
  printchar ( 42 ) ;
  else {
      
    printscaled ( mem [p + 1 ].cint ) ;
    if ( s != 0 ) 
    print ( s ) ;
    if ( mem [p + 2 ].cint != 0 ) 
    {
      print ( 317 ) ;
      printglue ( mem [p + 2 ].cint , mem [p ].hh.b0 , s ) ;
    } 
    if ( mem [p + 3 ].cint != 0 ) 
    {
      print ( 318 ) ;
      printglue ( mem [p + 3 ].cint , mem [p ].hh.b1 , s ) ;
    } 
  } 
} 
void 
zprintfamandchar ( halfword p ) 
{
  printfamandchar_regmem 
  printesc ( 484 ) ;
  printint ( mem [p ].hh.b0 ) ;
  printchar ( 32 ) ;
  print ( mem [p ].hh.b1 ) ;
} 
void 
zprintdelimiter ( halfword p ) 
{
  printdelimiter_regmem 
  integer a  ;
  a = mem [p ].qqqq .b0 * 256 + mem [p ].qqqq .b1 ;
  a = a * 4096 + mem [p ].qqqq .b2 * 256 + mem [p ].qqqq .b3 ;
  if ( a < 0 ) 
  printint ( a ) ;
  else printhex ( a ) ;
} 
void 
zprintsubsidiarydata ( halfword p , ASCIIcode c ) 
{
  printsubsidiarydata_regmem 
  if ( ( poolptr - strstart [strptr ]) >= depththreshold ) 
  {
    if ( mem [p ].hh .v.RH != 0 ) 
    print ( 319 ) ;
  } 
  else {
      
    {
      strpool [poolptr ]= c ;
      incr ( poolptr ) ;
    } 
    tempptr = p ;
    switch ( mem [p ].hh .v.RH ) 
    {case 1 : 
      {
	println () ;
	printcurrentstring () ;
	printfamandchar ( p ) ;
      } 
      break ;
    case 2 : 
      showinfo () ;
      break ;
    case 3 : 
      if ( mem [p ].hh .v.LH == -268435455L ) 
      {
	println () ;
	printcurrentstring () ;
	print ( 1261 ) ;
      } 
      else showinfo () ;
      break ;
      default: 
      ;
      break ;
    } 
    decr ( poolptr ) ;
  } 
} 
void 
zprintstyle ( integer c ) 
{
  printstyle_regmem 
  switch ( c / 2 ) 
  {case 0 : 
    printesc ( 1262 ) ;
    break ;
  case 1 : 
    printesc ( 1263 ) ;
    break ;
  case 2 : 
    printesc ( 1264 ) ;
    break ;
  case 3 : 
    printesc ( 1265 ) ;
    break ;
    default: 
    print ( 1266 ) ;
    break ;
  } 
} 
void 
zprintskipparam ( integer n ) 
{
  printskipparam_regmem 
  switch ( n ) 
  {case 0 : 
    printesc ( 393 ) ;
    break ;
  case 1 : 
    printesc ( 394 ) ;
    break ;
  case 2 : 
    printesc ( 395 ) ;
    break ;
  case 3 : 
    printesc ( 396 ) ;
    break ;
  case 4 : 
    printesc ( 397 ) ;
    break ;
  case 5 : 
    printesc ( 398 ) ;
    break ;
  case 6 : 
    printesc ( 399 ) ;
    break ;
  case 7 : 
    printesc ( 400 ) ;
    break ;
  case 8 : 
    printesc ( 401 ) ;
    break ;
  case 9 : 
    printesc ( 402 ) ;
    break ;
  case 10 : 
    printesc ( 403 ) ;
    break ;
  case 11 : 
    printesc ( 404 ) ;
    break ;
  case 12 : 
    printesc ( 405 ) ;
    break ;
  case 13 : 
    printesc ( 406 ) ;
    break ;
  case 14 : 
    printesc ( 407 ) ;
    break ;
  case 15 : 
    printesc ( 408 ) ;
    break ;
  case 16 : 
    printesc ( 409 ) ;
    break ;
  case 17 : 
    printesc ( 410 ) ;
    break ;
    default: 
    print ( 411 ) ;
    break ;
  } 
} 
void 
zshownodelist ( integer p ) 
{
  /* 10 */ shownodelist_regmem 
  integer n  ;
  real g  ;
  if ( ( poolptr - strstart [strptr ]) > depththreshold ) 
  {
    if ( p > -268435455L ) 
    print ( 319 ) ;
    return ;
  } 
  n = 0 ;
  while ( p > memmin ) {
      
    println () ;
    printcurrentstring () ;
    if ( p > memend ) 
    {
      print ( 320 ) ;
      return ;
    } 
    incr ( n ) ;
    if ( n > breadthmax ) 
    {
      print ( 321 ) ;
      return ;
    } 
    if ( ( p >= himemmin ) ) 
    printfontandchar ( p ) ;
    else switch ( mem [p ].hh.b0 ) 
    {case 0 : 
    case 1 : 
    case 13 : 
      {
	if ( mem [p ].hh.b0 == 0 ) 
	printesc ( 104 ) ;
	else if ( mem [p ].hh.b0 == 1 ) 
	printesc ( 118 ) ;
	else printesc ( 326 ) ;
	print ( 327 ) ;
	printscaled ( mem [p + 3 ].cint ) ;
	printchar ( 43 ) ;
	printscaled ( mem [p + 2 ].cint ) ;
	print ( 328 ) ;
	printscaled ( mem [p + 1 ].cint ) ;
	if ( mem [p ].hh.b0 == 13 ) 
	{
	  if ( mem [p ].hh.b1 != 0 ) 
	  {
	    print ( 286 ) ;
	    printint ( mem [p ].hh.b1 + 1 ) ;
	    print ( 330 ) ;
	  } 
	  if ( mem [p + 6 ].cint != 0 ) 
	  {
	    print ( 331 ) ;
	    printglue ( mem [p + 6 ].cint , mem [p + 5 ].hh.b1 , 0 ) ;
	  } 
	  if ( mem [p + 4 ].cint != 0 ) 
	  {
	    print ( 332 ) ;
	    printglue ( mem [p + 4 ].cint , mem [p + 5 ].hh.b0 , 0 ) ;
	  } 
	} 
	else {
	    
	  g = mem [p + 6 ].gr ;
	  if ( ( g != 0.0 ) && ( mem [p + 5 ].hh.b0 != 0 ) ) 
	  {
	    print ( 333 ) ;
	    if ( mem [p + 5 ].hh.b0 == 2 ) 
	    print ( 334 ) ;
	    if ( fabs ( g ) > 20000.0 ) 
	    {
	      if ( g > 0.0 ) 
	      printchar ( 62 ) ;
	      else print ( 335 ) ;
	      printglue ( 20000 * 65536L , mem [p + 5 ].hh.b1 , 0 ) ;
	    } 
	    else printglue ( round ( 65536L * g ) , mem [p + 5 ].hh.b1 , 0 ) 
	    ;
	  } 
	  if ( mem [p + 4 ].cint != 0 ) 
	  {
	    print ( 329 ) ;
	    printscaled ( mem [p + 4 ].cint ) ;
	  } 
	  if ( ( eTeXmode == 1 ) ) {
	      
	    if ( ( mem [p ].hh.b0 == 0 ) && ( ( mem [p ].hh.b1 ) == 2 ) ) 
	    print ( 2006 ) ;
	  } 
	} 
	{
	  {
	    strpool [poolptr ]= 46 ;
	    incr ( poolptr ) ;
	  } 
	  shownodelist ( mem [p + 5 ].hh .v.RH ) ;
	  decr ( poolptr ) ;
	} 
      } 
      break ;
    case 2 : 
      {
	printesc ( 336 ) ;
	printruledimen ( mem [p + 3 ].cint ) ;
	printchar ( 43 ) ;
	printruledimen ( mem [p + 2 ].cint ) ;
	print ( 328 ) ;
	printruledimen ( mem [p + 1 ].cint ) ;
      } 
      break ;
    case 3 : 
      {
	printesc ( 337 ) ;
	printint ( mem [p ].hh.b1 ) ;
	print ( 338 ) ;
	printscaled ( mem [p + 3 ].cint ) ;
	print ( 339 ) ;
	printspec ( mem [p + 4 ].hh .v.RH , 0 ) ;
	printchar ( 44 ) ;
	printscaled ( mem [p + 2 ].cint ) ;
	print ( 340 ) ;
	printint ( mem [p + 1 ].cint ) ;
	{
	  {
	    strpool [poolptr ]= 46 ;
	    incr ( poolptr ) ;
	  } 
	  shownodelist ( mem [p + 4 ].hh .v.LH ) ;
	  decr ( poolptr ) ;
	} 
      } 
      break ;
    case 8 : 
      switch ( mem [p ].hh.b1 ) 
      {case 0 : 
	{
	  printwritewhatsit ( 1713 , p ) ;
	  printchar ( 61 ) ;
	  printfilename ( mem [p + 1 ].hh .v.RH , mem [p + 2 ].hh .v.LH , 
	  mem [p + 2 ].hh .v.RH ) ;
	} 
	break ;
      case 1 : 
	{
	  printwritewhatsit ( 673 , p ) ;
	  printmark ( mem [p + 1 ].hh .v.RH ) ;
	} 
	break ;
      case 2 : 
	printwritewhatsit ( 1714 , p ) ;
	break ;
      case 3 : 
	{
	  printesc ( 1715 ) ;
	  printmark ( mem [p + 1 ].hh .v.RH ) ;
	} 
	break ;
      case 4 : 
	{
	  printesc ( 1717 ) ;
	  printint ( mem [p + 1 ].hh .v.RH ) ;
	  print ( 1865 ) ;
	  printint ( mem [p + 1 ].hh.b0 ) ;
	  printchar ( 44 ) ;
	  printint ( mem [p + 1 ].hh.b1 ) ;
	  printchar ( 41 ) ;
	} 
	break ;
      case 6 : 
	{
	  printesc ( 1718 ) ;
	  switch ( mem [p + 1 ].hh .v.LH ) 
	  {case 0 : 
	    ;
	    break ;
	  case 1 : 
	    print ( 994 ) ;
	    break ;
	  case 2 : 
	    print ( 1866 ) ;
	    break ;
	    default: 
	    confusion ( 1867 ) ;
	    break ;
	  } 
	  printmark ( mem [p + 1 ].hh .v.RH ) ;
	} 
	break ;
      case 38 : 
	{
	  printesc ( 1868 ) ;
	  printint ( mem [p + 1 ].hh .v.RH ) ;
	  switch ( mem [p + 1 ].hh .v.LH ) 
	  {case 0 : 
	    print ( 1869 ) ;
	    break ;
	  case 1 : 
	    print ( 1870 ) ;
	    break ;
	  case 2 : 
	    print ( 1871 ) ;
	    break ;
	  case 3 : 
	    print ( 1872 ) ;
	    break ;
	    default: 
	    confusion ( 1128 ) ;
	    break ;
	  } 
	  if ( mem [p + 1 ].hh .v.LH <= 1 ) 
	  printmark ( mem [p + 2 ].hh .v.RH ) ;
	} 
	break ;
      case 39 : 
	{
	  printesc ( 1719 ) ;
	  printmark ( mem [p + 1 ].hh .v.RH ) ;
	} 
	break ;
      case 40 : 
	{
	  printesc ( 1720 ) ;
	} 
	break ;
      case 41 : 
	{
	  printesc ( 1721 ) ;
	} 
	break ;
      case 8 : 
	{
	  printesc ( 1723 ) ;
	  if ( pdfmem [objtab [mem [p + 1 ].hh .v.LH ].int4 + 1 ]> 0 ) 
	  {
	    if ( pdfmem [objtab [mem [p + 1 ].hh .v.LH ].int4 + 2 ]!= 
	    -268435455L ) 
	    {
	      print ( 1873 ) ;
	      printmark ( pdfmem [objtab [mem [p + 1 ].hh .v.LH ].int4 + 
	      2 ]) ;
	    } 
	    print ( 1874 ) ;
	  } 
	  if ( pdfmem [objtab [mem [p + 1 ].hh .v.LH ].int4 + 3 ]> 0 ) 
	  print ( 1875 ) ;
	  printmark ( pdfmem [objtab [mem [p + 1 ].hh .v.LH ].int4 + 0 ]
	  ) ;
	} 
	break ;
      case 10 : 
	{
	  printesc ( 1725 ) ;
	  print ( 40 ) ;
	  printscaled ( pdfmem [objtab [mem [p + 4 ].hh .v.LH ].int4 + 1 
	  ]) ;
	  printchar ( 43 ) ;
	  printscaled ( pdfmem [objtab [mem [p + 4 ].hh .v.LH ].int4 + 2 
	  ]) ;
	  print ( 328 ) ;
	  printscaled ( pdfmem [objtab [mem [p + 4 ].hh .v.LH ].int4 + 0 
	  ]) ;
	} 
	break ;
      case 12 : 
	{
	  printesc ( 1727 ) ;
	  print ( 40 ) ;
	  printscaled ( pdfmem [objtab [mem [p + 4 ].hh .v.LH ].int4 + 1 
	  ]) ;
	  printchar ( 43 ) ;
	  printscaled ( pdfmem [objtab [mem [p + 4 ].hh .v.LH ].int4 + 2 
	  ]) ;
	  print ( 328 ) ;
	  printscaled ( pdfmem [objtab [mem [p + 4 ].hh .v.LH ].int4 + 0 
	  ]) ;
	} 
	break ;
      case 13 : 
	{
	  printesc ( 1728 ) ;
	  print ( 40 ) ;
	  printruledimen ( mem [p + 2 ].cint ) ;
	  printchar ( 43 ) ;
	  printruledimen ( mem [p + 3 ].cint ) ;
	  print ( 328 ) ;
	  printruledimen ( mem [p + 1 ].cint ) ;
	  printmark ( mem [p + 5 ].hh .v.LH ) ;
	} 
	break ;
      case 14 : 
	{
	  printesc ( 1729 ) ;
	  print ( 40 ) ;
	  printruledimen ( mem [p + 2 ].cint ) ;
	  printchar ( 43 ) ;
	  printruledimen ( mem [p + 3 ].cint ) ;
	  print ( 328 ) ;
	  printruledimen ( mem [p + 1 ].cint ) ;
	  if ( mem [p + 5 ].hh .v.LH != -268435455L ) 
	  {
	    print ( 1873 ) ;
	    printmark ( mem [p + 5 ].hh .v.LH ) ;
	  } 
	  print ( 1876 ) ;
	  if ( mem [mem [p + 5 ].hh .v.RH ].hh.b0 == 3 ) 
	  {
	    print ( 1877 ) ;
	    printmark ( mem [mem [p + 5 ].hh .v.RH + 2 ].hh .v.LH ) ;
	  } 
	  else {
	      
	    if ( mem [mem [p + 5 ].hh .v.RH + 1 ].hh .v.LH != -268435455L 
	    ) 
	    {
	      print ( 1875 ) ;
	      printmark ( mem [mem [p + 5 ].hh .v.RH + 1 ].hh .v.LH ) ;
	    } 
	    switch ( mem [mem [p + 5 ].hh .v.RH ].hh.b0 ) 
	    {case 1 : 
	      {
		if ( mem [mem [p + 5 ].hh .v.RH ].hh.b1 > 0 ) 
		{
		  print ( 1878 ) ;
		  printmark ( mem [mem [p + 5 ].hh .v.RH ].hh .v.RH ) ;
		} 
		else {
		    
		  print ( 1879 ) ;
		  printint ( mem [mem [p + 5 ].hh .v.RH ].hh .v.RH ) ;
		} 
	      } 
	      break ;
	    case 0 : 
	      {
		print ( 994 ) ;
		printint ( mem [mem [p + 5 ].hh .v.RH ].hh .v.RH ) ;
		printmark ( mem [mem [p + 5 ].hh .v.RH + 2 ].hh .v.LH ) ;
	      } 
	      break ;
	    case 2 : 
	      {
		if ( mem [mem [p + 5 ].hh .v.RH ].hh.b1 > 0 ) 
		{
		  print ( 1880 ) ;
		  printmark ( mem [mem [p + 5 ].hh .v.RH ].hh .v.RH ) ;
		} 
		else {
		    
		  print ( 1881 ) ;
		  printint ( mem [mem [p + 5 ].hh .v.RH ].hh .v.RH ) ;
		} 
	      } 
	      break ;
	      default: 
	      pdferror ( 1882 , 1883 ) ;
	      break ;
	    } 
	  } 
	} 
	break ;
      case 15 : 
	printesc ( 1730 ) ;
	break ;
      case 17 : 
	{
	  printesc ( 1732 ) ;
	  if ( mem [p + 5 ].hh.b1 > 0 ) 
	  {
	    print ( 1884 ) ;
	    printmark ( mem [p + 5 ].hh .v.RH ) ;
	  } 
	  else {
	      
	    print ( 1885 ) ;
	    printint ( mem [p + 5 ].hh .v.RH ) ;
	  } 
	  print ( 32 ) ;
	  switch ( mem [p + 5 ].hh.b0 ) 
	  {case 0 : 
	    {
	      print ( 1828 ) ;
	      if ( mem [p + 6 ].hh .v.LH != -268435455L ) 
	      {
		print ( 1886 ) ;
		printint ( mem [p + 6 ].hh .v.LH ) ;
	      } 
	    } 
	    break ;
	  case 5 : 
	    print ( 1830 ) ;
	    break ;
	  case 6 : 
	    print ( 1831 ) ;
	    break ;
	  case 4 : 
	    print ( 1832 ) ;
	    break ;
	  case 2 : 
	    print ( 1833 ) ;
	    break ;
	  case 3 : 
	    print ( 1834 ) ;
	    break ;
	  case 7 : 
	    {
	      print ( 1835 ) ;
	      print ( 40 ) ;
	      printruledimen ( mem [p + 2 ].cint ) ;
	      printchar ( 43 ) ;
	      printruledimen ( mem [p + 3 ].cint ) ;
	      print ( 328 ) ;
	      printruledimen ( mem [p + 1 ].cint ) ;
	    } 
	    break ;
	  case 1 : 
	    print ( 1836 ) ;
	    break ;
	    default: 
	    print ( 1887 ) ;
	    break ;
	  } 
	} 
	break ;
      case 18 : 
      case 19 : 
	{
	  if ( mem [p ].hh.b1 == 18 ) 
	  printesc ( 1733 ) ;
	  else printesc ( 1734 ) ;
	  print ( 40 ) ;
	  printruledimen ( mem [p + 2 ].cint ) ;
	  printchar ( 43 ) ;
	  printruledimen ( mem [p + 3 ].cint ) ;
	  print ( 328 ) ;
	  printruledimen ( mem [p + 1 ].cint ) ;
	  if ( mem [p + 6 ].hh .v.LH != -268435455L ) 
	  {
	    print ( 1873 ) ;
	    printmark ( mem [p + 6 ].hh .v.LH ) ;
	  } 
	  if ( mem [p + 5 ].hh.b1 > 0 ) 
	  {
	    print ( 1884 ) ;
	    printmark ( mem [p + 5 ].hh .v.RH ) ;
	  } 
	  else {
	      
	    print ( 1885 ) ;
	    printint ( mem [p + 5 ].hh .v.RH ) ;
	  } 
	} 
	break ;
      case 20 : 
	printesc ( 1735 ) ;
	break ;
      case 21 : 
	printesc ( 1736 ) ;
	break ;
      case 34 : 
	printesc ( 1737 ) ;
	break ;
      case 35 : 
	{
	  printesc ( 1738 ) ;
	  printchar ( 32 ) ;
	  printspec ( mem [p + 1 ].hh .v.LH , 0 ) ;
	  printchar ( 32 ) ;
	  printspec ( mem [p + 2 ].cint , 0 ) ;
	} 
	break ;
      case 36 : 
	{
	  printesc ( 1739 ) ;
	  printchar ( 32 ) ;
	  printint ( mem [p + 1 ].cint ) ;
	} 
	break ;
      case 43 : 
	printesc ( 1754 ) ;
	break ;
      case 44 : 
	printesc ( 1755 ) ;
	break ;
      case 45 : 
	printesc ( 1756 ) ;
	break ;
	default: 
	print ( 1888 ) ;
	break ;
      } 
      break ;
    case 10 : 
      if ( mem [p ].hh.b1 >= 100 ) 
      {
	printesc ( 345 ) ;
	if ( mem [p ].hh.b1 == 101 ) 
	printchar ( 99 ) ;
	else if ( mem [p ].hh.b1 == 102 ) 
	printchar ( 120 ) ;
	print ( 346 ) ;
	printspec ( mem [p + 1 ].hh .v.LH , 0 ) ;
	{
	  {
	    strpool [poolptr ]= 46 ;
	    incr ( poolptr ) ;
	  } 
	  shownodelist ( mem [p + 1 ].hh .v.RH ) ;
	  decr ( poolptr ) ;
	} 
      } 
      else {
	  
	printesc ( 341 ) ;
	if ( mem [p ].hh.b1 != 0 ) 
	{
	  printchar ( 40 ) ;
	  if ( mem [p ].hh.b1 < 98 ) 
	  printskipparam ( mem [p ].hh.b1 - 1 ) ;
	  else if ( mem [p ].hh.b1 == 98 ) 
	  printesc ( 342 ) ;
	  else printesc ( 343 ) ;
	  printchar ( 41 ) ;
	} 
	if ( mem [p ].hh.b1 != 98 ) 
	{
	  printchar ( 32 ) ;
	  if ( mem [p ].hh.b1 < 98 ) 
	  printspec ( mem [p + 1 ].hh .v.LH , 0 ) ;
	  else printspec ( mem [p + 1 ].hh .v.LH , 344 ) ;
	} 
      } 
      break ;
    case 40 : 
      {
	printesc ( 322 ) ;
	printscaled ( mem [p + 1 ].cint ) ;
	if ( mem [p ].hh.b1 == 0 ) 
	print ( 323 ) ;
	else print ( 324 ) ;
      } 
      break ;
    case 11 : 
      if ( mem [p ].hh.b1 != 99 ) 
      {
	printesc ( 322 ) ;
	if ( mem [p ].hh.b1 != 0 ) 
	printchar ( 32 ) ;
	printscaled ( mem [p + 1 ].cint ) ;
	if ( mem [p ].hh.b1 == 2 ) 
	print ( 347 ) ;
      } 
      else {
	  
	printesc ( 348 ) ;
	printscaled ( mem [p + 1 ].cint ) ;
	print ( 344 ) ;
      } 
      break ;
    case 9 : 
      if ( mem [p ].hh.b1 > 1 ) 
      {
	if ( odd ( mem [p ].hh.b1 ) ) 
	printesc ( 349 ) ;
	else printesc ( 350 ) ;
	if ( mem [p ].hh.b1 > 8 ) 
	printchar ( 82 ) ;
	else if ( mem [p ].hh.b1 > 4 ) 
	printchar ( 76 ) ;
	else printchar ( 77 ) ;
      } 
      else {
	  
	printesc ( 351 ) ;
	if ( mem [p ].hh.b1 == 0 ) 
	print ( 352 ) ;
	else print ( 353 ) ;
	if ( mem [p + 1 ].cint != 0 ) 
	{
	  print ( 354 ) ;
	  printscaled ( mem [p + 1 ].cint ) ;
	} 
      } 
      break ;
    case 6 : 
      {
	printfontandchar ( p + 1 ) ;
	print ( 355 ) ;
	if ( mem [p ].hh.b1 > 1 ) 
	printchar ( 124 ) ;
	fontinshortdisplay = mem [p + 1 ].hh.b0 ;
	shortdisplay ( mem [p + 1 ].hh .v.RH ) ;
	if ( odd ( mem [p ].hh.b1 ) ) 
	printchar ( 124 ) ;
	printchar ( 41 ) ;
      } 
      break ;
    case 12 : 
      {
	printesc ( 356 ) ;
	printint ( mem [p + 1 ].cint ) ;
      } 
      break ;
    case 7 : 
      {
	printesc ( 357 ) ;
	if ( mem [p ].hh.b1 > 0 ) 
	{
	  print ( 358 ) ;
	  printint ( mem [p ].hh.b1 ) ;
	} 
	{
	  {
	    strpool [poolptr ]= 46 ;
	    incr ( poolptr ) ;
	  } 
	  shownodelist ( mem [p + 1 ].hh .v.LH ) ;
	  decr ( poolptr ) ;
	} 
	{
	  strpool [poolptr ]= 124 ;
	  incr ( poolptr ) ;
	} 
	shownodelist ( mem [p + 1 ].hh .v.RH ) ;
	decr ( poolptr ) ;
      } 
      break ;
    case 4 : 
      {
	printesc ( 359 ) ;
	if ( mem [p + 1 ].hh .v.LH != 0 ) 
	{
	  printchar ( 115 ) ;
	  printint ( mem [p + 1 ].hh .v.LH ) ;
	} 
	printmark ( mem [p + 1 ].hh .v.RH ) ;
      } 
      break ;
    case 5 : 
      {
	printesc ( 360 ) ;
	if ( mem [p ].hh.b1 != 0 ) 
	print ( 361 ) ;
	{
	  {
	    strpool [poolptr ]= 46 ;
	    incr ( poolptr ) ;
	  } 
	  shownodelist ( mem [p + 1 ].cint ) ;
	  decr ( poolptr ) ;
	} 
      } 
      break ;
    case 14 : 
      printstyle ( mem [p ].hh.b1 ) ;
      break ;
    case 15 : 
      {
	printesc ( 599 ) ;
	{
	  strpool [poolptr ]= 68 ;
	  incr ( poolptr ) ;
	} 
	shownodelist ( mem [p + 1 ].hh .v.LH ) ;
	decr ( poolptr ) ;
	{
	  strpool [poolptr ]= 84 ;
	  incr ( poolptr ) ;
	} 
	shownodelist ( mem [p + 1 ].hh .v.RH ) ;
	decr ( poolptr ) ;
	{
	  strpool [poolptr ]= 83 ;
	  incr ( poolptr ) ;
	} 
	shownodelist ( mem [p + 2 ].hh .v.LH ) ;
	decr ( poolptr ) ;
	{
	  strpool [poolptr ]= 115 ;
	  incr ( poolptr ) ;
	} 
	shownodelist ( mem [p + 2 ].hh .v.RH ) ;
	decr ( poolptr ) ;
      } 
      break ;
    case 16 : 
    case 17 : 
    case 18 : 
    case 19 : 
    case 20 : 
    case 21 : 
    case 22 : 
    case 23 : 
    case 24 : 
    case 27 : 
    case 26 : 
    case 29 : 
    case 28 : 
    case 30 : 
    case 31 : 
      {
	switch ( mem [p ].hh.b0 ) 
	{case 16 : 
	  printesc ( 1267 ) ;
	  break ;
	case 17 : 
	  printesc ( 1268 ) ;
	  break ;
	case 18 : 
	  printesc ( 1269 ) ;
	  break ;
	case 19 : 
	  printesc ( 1270 ) ;
	  break ;
	case 20 : 
	  printesc ( 1271 ) ;
	  break ;
	case 21 : 
	  printesc ( 1272 ) ;
	  break ;
	case 22 : 
	  printesc ( 1273 ) ;
	  break ;
	case 23 : 
	  printesc ( 1274 ) ;
	  break ;
	case 27 : 
	  printesc ( 1275 ) ;
	  break ;
	case 26 : 
	  printesc ( 1276 ) ;
	  break ;
	case 29 : 
	  printesc ( 614 ) ;
	  break ;
	case 24 : 
	  {
	    printesc ( 608 ) ;
	    printdelimiter ( p + 4 ) ;
	  } 
	  break ;
	case 28 : 
	  {
	    printesc ( 580 ) ;
	    printfamandchar ( p + 4 ) ;
	  } 
	  break ;
	case 30 : 
	  {
	    printesc ( 1277 ) ;
	    printdelimiter ( p + 1 ) ;
	  } 
	  break ;
	case 31 : 
	  {
	    if ( mem [p ].hh.b1 == 0 ) 
	    printesc ( 1278 ) ;
	    else printesc ( 1279 ) ;
	    printdelimiter ( p + 1 ) ;
	  } 
	  break ;
	} 
	if ( mem [p ].hh.b0 < 30 ) 
	{
	  if ( mem [p ].hh.b1 != 0 ) {
	      
	    if ( mem [p ].hh.b1 == 1 ) 
	    printesc ( 1280 ) ;
	    else printesc ( 1281 ) ;
	  } 
	  printsubsidiarydata ( p + 1 , 46 ) ;
	} 
	printsubsidiarydata ( p + 2 , 94 ) ;
	printsubsidiarydata ( p + 3 , 95 ) ;
      } 
      break ;
    case 25 : 
      {
	printesc ( 1282 ) ;
	if ( mem [p + 1 ].cint == 1073741824L ) 
	print ( 1283 ) ;
	else printscaled ( mem [p + 1 ].cint ) ;
	if ( ( mem [p + 4 ].qqqq .b0 != 0 ) || ( mem [p + 4 ].qqqq .b1 != 
	0 ) || ( mem [p + 4 ].qqqq .b2 != 0 ) || ( mem [p + 4 ].qqqq .b3 
	!= 0 ) ) 
	{
	  print ( 1284 ) ;
	  printdelimiter ( p + 4 ) ;
	} 
	if ( ( mem [p + 5 ].qqqq .b0 != 0 ) || ( mem [p + 5 ].qqqq .b1 != 
	0 ) || ( mem [p + 5 ].qqqq .b2 != 0 ) || ( mem [p + 5 ].qqqq .b3 
	!= 0 ) ) 
	{
	  print ( 1285 ) ;
	  printdelimiter ( p + 5 ) ;
	} 
	printsubsidiarydata ( p + 2 , 92 ) ;
	printsubsidiarydata ( p + 3 , 47 ) ;
      } 
      break ;
      default: 
      print ( 325 ) ;
      break ;
    } 
    p = mem [p ].hh .v.RH ;
  } 
} 
void 
zshowbox ( halfword p ) 
{
  showbox_regmem 
  depththreshold = eqtb [29299 ].cint ;
  breadthmax = eqtb [29298 ].cint ;
  if ( breadthmax <= 0 ) 
  breadthmax = 5 ;
  if ( poolptr + depththreshold >= poolsize ) 
  depththreshold = poolsize - poolptr - 1 ;
  shownodelist ( p ) ;
  println () ;
} 
void 
zdeletetokenref ( halfword p ) 
{
  deletetokenref_regmem 
  if ( mem [p ].hh .v.LH == -268435455L ) 
  flushlist ( p ) ;
  else decr ( mem [p ].hh .v.LH ) ;
} 
void 
zdeleteglueref ( halfword p ) 
{
  deleteglueref_regmem 
  if ( mem [p ].hh .v.RH == -268435455L ) 
  freenode ( p , 4 ) ;
  else decr ( mem [p ].hh .v.RH ) ;
} 
void 
zflushnodelist ( halfword p ) 
{
  /* 30 */ flushnodelist_regmem 
  halfword q  ;
  while ( p != -268435455L ) {
      
    q = mem [p ].hh .v.RH ;
    if ( ( p >= himemmin ) ) 
    {
      mem [p ].hh .v.RH = avail ;
      avail = p ;
	;
#ifdef STAT
      decr ( dynused ) ;
#endif /* STAT */
    } 
    else {
	
      switch ( mem [p ].hh.b0 ) 
      {case 0 : 
      case 1 : 
      case 13 : 
	{
	  flushnodelist ( mem [p + 5 ].hh .v.RH ) ;
	  freenode ( p , 7 ) ;
	  goto lab30 ;
	} 
	break ;
      case 2 : 
	{
	  freenode ( p , 4 ) ;
	  goto lab30 ;
	} 
	break ;
      case 3 : 
	{
	  flushnodelist ( mem [p + 4 ].hh .v.LH ) ;
	  deleteglueref ( mem [p + 4 ].hh .v.RH ) ;
	  freenode ( p , 5 ) ;
	  goto lab30 ;
	} 
	break ;
      case 8 : 
	{
	  switch ( mem [p ].hh.b1 ) 
	  {case 0 : 
	    freenode ( p , 3 ) ;
	    break ;
	  case 1 : 
	  case 3 : 
	    {
	      deletetokenref ( mem [p + 1 ].hh .v.RH ) ;
	      freenode ( p , 2 ) ;
	      goto lab30 ;
	    } 
	    break ;
	  case 2 : 
	  case 4 : 
	    freenode ( p , 2 ) ;
	    break ;
	  case 6 : 
	    {
	      deletetokenref ( mem [p + 1 ].hh .v.RH ) ;
	      freenode ( p , 2 ) ;
	    } 
	    break ;
	  case 38 : 
	    {
	      if ( mem [p + 1 ].hh .v.LH <= 1 ) 
	      {
		deletetokenref ( mem [p + 2 ].hh .v.RH ) ;
		freenode ( p , 3 ) ;
	      } 
	      else freenode ( p , 2 ) ;
	    } 
	    break ;
	  case 39 : 
	    {
	      deletetokenref ( mem [p + 1 ].hh .v.RH ) ;
	      freenode ( p , 2 ) ;
	    } 
	    break ;
	  case 40 : 
	    {
	      freenode ( p , 2 ) ;
	    } 
	    break ;
	  case 41 : 
	    {
	      freenode ( p , 2 ) ;
	    } 
	    break ;
	  case 8 : 
	    freenode ( p , 2 ) ;
	    break ;
	  case 10 : 
	    freenode ( p , 5 ) ;
	    break ;
	  case 12 : 
	    freenode ( p , 5 ) ;
	    break ;
	  case 13 : 
	    {
	      deletetokenref ( mem [p + 5 ].hh .v.LH ) ;
	      freenode ( p , 7 ) ;
	    } 
	    break ;
	  case 14 : 
	    {
	      if ( mem [p + 5 ].hh .v.LH != -268435455L ) 
	      deletetokenref ( mem [p + 5 ].hh .v.LH ) ;
	      {
		if ( mem [mem [p + 5 ].hh .v.RH + 2 ].hh .v.RH == 
		-268435455L ) 
		{
		  if ( mem [mem [p + 5 ].hh .v.RH ].hh.b0 == 3 ) 
		  deletetokenref ( mem [mem [p + 5 ].hh .v.RH + 2 ].hh 
		  .v.LH ) ;
		  else {
		      
		    if ( mem [mem [p + 5 ].hh .v.RH + 1 ].hh .v.LH != 
		    -268435455L ) 
		    deletetokenref ( mem [mem [p + 5 ].hh .v.RH + 1 ].hh 
		    .v.LH ) ;
		    if ( mem [mem [p + 5 ].hh .v.RH ].hh.b0 == 0 ) 
		    deletetokenref ( mem [mem [p + 5 ].hh .v.RH + 2 ].hh 
		    .v.LH ) ;
		    else if ( mem [mem [p + 5 ].hh .v.RH ].hh.b1 > 0 ) 
		    deletetokenref ( mem [mem [p + 5 ].hh .v.RH ].hh .v.RH 
		    ) ;
		  } 
		  freenode ( mem [p + 5 ].hh .v.RH , 3 ) ;
		} 
		else decr ( mem [mem [p + 5 ].hh .v.RH + 2 ].hh .v.RH ) ;
	      } 
	      freenode ( p , 7 ) ;
	    } 
	    break ;
	  case 15 : 
	    freenode ( p , 2 ) ;
	    break ;
	  case 17 : 
	    {
	      if ( mem [p + 5 ].hh.b1 > 0 ) 
	      deletetokenref ( mem [p + 5 ].hh .v.RH ) ;
	      freenode ( p , 7 ) ;
	    } 
	    break ;
	  case 18 : 
	  case 19 : 
	    {
	      if ( mem [p + 5 ].hh.b1 > 0 ) 
	      deletetokenref ( mem [p + 5 ].hh .v.RH ) ;
	      if ( mem [p + 6 ].hh .v.LH != -268435455L ) 
	      deletetokenref ( mem [p + 6 ].hh .v.LH ) ;
	      freenode ( p , 7 ) ;
	    } 
	    break ;
	  case 20 : 
	    freenode ( p , 2 ) ;
	    break ;
	  case 21 : 
	    freenode ( p , 2 ) ;
	    break ;
	  case 34 : 
	    freenode ( p , 2 ) ;
	    break ;
	  case 35 : 
	    {
	      deleteglueref ( mem [p + 1 ].hh .v.LH ) ;
	      freenode ( p , 3 ) ;
	    } 
	    break ;
	  case 36 : 
	    freenode ( p , 2 ) ;
	    break ;
	  case 43 : 
	    freenode ( p , 2 ) ;
	    break ;
	  case 44 : 
	    freenode ( p , 2 ) ;
	    break ;
	  case 45 : 
	    freenode ( p , 2 ) ;
	    break ;
	    default: 
	    confusion ( 1890 ) ;
	    break ;
	  } 
	  goto lab30 ;
	} 
	break ;
      case 10 : 
	{
	  {
	    if ( mem [mem [p + 1 ].hh .v.LH ].hh .v.RH == -268435455L ) 
	    freenode ( mem [p + 1 ].hh .v.LH , 4 ) ;
	    else decr ( mem [mem [p + 1 ].hh .v.LH ].hh .v.RH ) ;
	  } 
	  if ( mem [p + 1 ].hh .v.RH != -268435455L ) 
	  flushnodelist ( mem [p + 1 ].hh .v.RH ) ;
	} 
	break ;
      case 11 : 
      case 9 : 
      case 12 : 
	;
	break ;
      case 40 : 
	{
	  {
	    mem [mem [p + 2 ].hh .v.LH ].hh .v.RH = avail ;
	    avail = mem [p + 2 ].hh .v.LH ;
	;
#ifdef STAT
	    decr ( dynused ) ;
#endif /* STAT */
	  } 
	  freenode ( p , 3 ) ;
	  goto lab30 ;
	} 
	break ;
      case 6 : 
	flushnodelist ( mem [p + 1 ].hh .v.RH ) ;
	break ;
      case 4 : 
	deletetokenref ( mem [p + 1 ].hh .v.RH ) ;
	break ;
      case 7 : 
	{
	  flushnodelist ( mem [p + 1 ].hh .v.LH ) ;
	  flushnodelist ( mem [p + 1 ].hh .v.RH ) ;
	} 
	break ;
      case 5 : 
	flushnodelist ( mem [p + 1 ].cint ) ;
	break ;
      case 14 : 
	{
	  freenode ( p , 3 ) ;
	  goto lab30 ;
	} 
	break ;
      case 15 : 
	{
	  flushnodelist ( mem [p + 1 ].hh .v.LH ) ;
	  flushnodelist ( mem [p + 1 ].hh .v.RH ) ;
	  flushnodelist ( mem [p + 2 ].hh .v.LH ) ;
	  flushnodelist ( mem [p + 2 ].hh .v.RH ) ;
	  freenode ( p , 3 ) ;
	  goto lab30 ;
	} 
	break ;
      case 16 : 
      case 17 : 
      case 18 : 
      case 19 : 
      case 20 : 
      case 21 : 
      case 22 : 
      case 23 : 
      case 24 : 
      case 27 : 
      case 26 : 
      case 29 : 
      case 28 : 
	{
	  if ( mem [p + 1 ].hh .v.RH >= 2 ) 
	  flushnodelist ( mem [p + 1 ].hh .v.LH ) ;
	  if ( mem [p + 2 ].hh .v.RH >= 2 ) 
	  flushnodelist ( mem [p + 2 ].hh .v.LH ) ;
	  if ( mem [p + 3 ].hh .v.RH >= 2 ) 
	  flushnodelist ( mem [p + 3 ].hh .v.LH ) ;
	  if ( mem [p ].hh.b0 == 24 ) 
	  freenode ( p , 5 ) ;
	  else if ( mem [p ].hh.b0 == 28 ) 
	  freenode ( p , 5 ) ;
	  else freenode ( p , 4 ) ;
	  goto lab30 ;
	} 
	break ;
      case 30 : 
      case 31 : 
	{
	  freenode ( p , 4 ) ;
	  goto lab30 ;
	} 
	break ;
      case 25 : 
	{
	  flushnodelist ( mem [p + 2 ].hh .v.LH ) ;
	  flushnodelist ( mem [p + 3 ].hh .v.LH ) ;
	  freenode ( p , 6 ) ;
	  goto lab30 ;
	} 
	break ;
	default: 
	confusion ( 362 ) ;
	break ;
      } 
      freenode ( p , 2 ) ;
      lab30: ;
    } 
    p = q ;
  } 
} 
halfword 
zcopynodelist ( halfword p ) 
{
  register halfword Result; copynodelist_regmem 
  halfword h  ;
  halfword q  ;
  halfword r  ;
  unsigned char words  ;
  h = getavail () ;
  q = h ;
  while ( p != -268435455L ) {
      
    words = 1 ;
    if ( ( p >= himemmin ) ) 
    r = getavail () ;
    else switch ( mem [p ].hh.b0 ) 
    {case 0 : 
    case 1 : 
    case 13 : 
      {
	r = getnode ( 7 ) ;
	mem [r + 6 ]= mem [p + 6 ];
	mem [r + 5 ]= mem [p + 5 ];
	mem [r + 5 ].hh .v.RH = copynodelist ( mem [p + 5 ].hh .v.RH ) ;
	words = 5 ;
      } 
      break ;
    case 2 : 
      {
	r = getnode ( 4 ) ;
	words = 4 ;
      } 
      break ;
    case 3 : 
      {
	r = getnode ( 5 ) ;
	mem [r + 4 ]= mem [p + 4 ];
	incr ( mem [mem [p + 4 ].hh .v.RH ].hh .v.RH ) ;
	mem [r + 4 ].hh .v.LH = copynodelist ( mem [p + 4 ].hh .v.LH ) ;
	words = 4 ;
      } 
      break ;
    case 8 : 
      switch ( mem [p ].hh.b1 ) 
      {case 0 : 
	{
	  r = getnode ( 3 ) ;
	  words = 3 ;
	} 
	break ;
      case 1 : 
      case 3 : 
	{
	  r = getnode ( 2 ) ;
	  incr ( mem [mem [p + 1 ].hh .v.RH ].hh .v.LH ) ;
	  words = 2 ;
	} 
	break ;
      case 2 : 
      case 4 : 
	{
	  r = getnode ( 2 ) ;
	  words = 2 ;
	} 
	break ;
      case 6 : 
	{
	  r = getnode ( 2 ) ;
	  incr ( mem [mem [p + 1 ].hh .v.RH ].hh .v.LH ) ;
	  words = 2 ;
	} 
	break ;
      case 38 : 
	{
	  if ( mem [p + 1 ].hh .v.LH <= 1 ) 
	  {
	    r = getnode ( 3 ) ;
	    incr ( mem [mem [p + 2 ].hh .v.RH ].hh .v.LH ) ;
	    words = 3 ;
	  } 
	  else {
	      
	    r = getnode ( 2 ) ;
	    words = 2 ;
	  } 
	} 
	break ;
      case 39 : 
	{
	  r = getnode ( 2 ) ;
	  incr ( mem [mem [p + 1 ].hh .v.RH ].hh .v.LH ) ;
	  words = 2 ;
	} 
	break ;
      case 40 : 
	{
	  r = getnode ( 2 ) ;
	  words = 2 ;
	} 
	break ;
      case 41 : 
	{
	  r = getnode ( 2 ) ;
	  words = 2 ;
	} 
	break ;
      case 8 : 
	{
	  r = getnode ( 2 ) ;
	  words = 2 ;
	} 
	break ;
      case 10 : 
	{
	  r = getnode ( 5 ) ;
	  words = 5 ;
	} 
	break ;
      case 12 : 
	{
	  r = getnode ( 5 ) ;
	  words = 5 ;
	} 
	break ;
      case 13 : 
	{
	  r = getnode ( 7 ) ;
	  incr ( mem [mem [p + 5 ].hh .v.LH ].hh .v.LH ) ;
	  words = 7 ;
	} 
	break ;
      case 14 : 
	{
	  r = getnode ( 7 ) ;
	  mem [r + 2 ].cint = mem [p + 2 ].cint ;
	  mem [r + 3 ].cint = mem [p + 3 ].cint ;
	  mem [r + 1 ].cint = mem [p + 1 ].cint ;
	  mem [r + 5 ].hh .v.LH = mem [p + 5 ].hh .v.LH ;
	  if ( mem [r + 5 ].hh .v.LH != -268435455L ) 
	  incr ( mem [mem [r + 5 ].hh .v.LH ].hh .v.LH ) ;
	  mem [r + 5 ].hh .v.RH = mem [p + 5 ].hh .v.RH ;
	  incr ( mem [mem [r + 5 ].hh .v.RH + 2 ].hh .v.RH ) ;
	  mem [r + 6 ].cint = mem [p + 6 ].cint ;
	} 
	break ;
      case 15 : 
	r = getnode ( 2 ) ;
	break ;
      case 17 : 
	{
	  r = getnode ( 7 ) ;
	  if ( mem [p + 5 ].hh.b1 > 0 ) 
	  incr ( mem [mem [p + 5 ].hh .v.RH ].hh .v.LH ) ;
	  words = 7 ;
	} 
	break ;
      case 18 : 
      case 19 : 
	{
	  r = getnode ( 7 ) ;
	  if ( mem [p + 5 ].hh.b1 > 0 ) 
	  incr ( mem [mem [p + 5 ].hh .v.RH ].hh .v.LH ) ;
	  if ( mem [p + 6 ].hh .v.LH != -268435455L ) 
	  incr ( mem [mem [p + 6 ].hh .v.LH ].hh .v.LH ) ;
	  words = 7 ;
	} 
	break ;
      case 20 : 
	r = getnode ( 2 ) ;
	break ;
      case 21 : 
	r = getnode ( 2 ) ;
	break ;
      case 34 : 
	r = getnode ( 2 ) ;
	break ;
      case 35 : 
	{
	  incr ( mem [mem [p + 1 ].hh .v.LH ].hh .v.RH ) ;
	  r = getnode ( 3 ) ;
	  words = 3 ;
	} 
	break ;
      case 36 : 
	r = getnode ( 2 ) ;
	break ;
      case 43 : 
	r = getnode ( 2 ) ;
	break ;
      case 44 : 
	r = getnode ( 2 ) ;
	break ;
      case 45 : 
	r = getnode ( 2 ) ;
	break ;
	default: 
	confusion ( 1889 ) ;
	break ;
      } 
      break ;
    case 10 : 
      {
	r = getnode ( 2 ) ;
	incr ( mem [mem [p + 1 ].hh .v.LH ].hh .v.RH ) ;
	mem [r + 1 ].hh .v.LH = mem [p + 1 ].hh .v.LH ;
	mem [r + 1 ].hh .v.RH = copynodelist ( mem [p + 1 ].hh .v.RH ) ;
      } 
      break ;
    case 11 : 
    case 9 : 
    case 12 : 
      {
	r = getnode ( 2 ) ;
	words = 2 ;
      } 
      break ;
    case 40 : 
      {
	r = getnode ( 3 ) ;
	{
	  mem [r + 2 ].hh .v.LH = avail ;
	  if ( mem [r + 2 ].hh .v.LH == -268435455L ) 
	  mem [r + 2 ].hh .v.LH = getavail () ;
	  else {
	      
	    avail = mem [mem [r + 2 ].hh .v.LH ].hh .v.RH ;
	    mem [mem [r + 2 ].hh .v.LH ].hh .v.RH = -268435455L ;
	;
#ifdef STAT
	    incr ( dynused ) ;
#endif /* STAT */
	  } 
	} 
	mem [mem [r + 2 ].hh .v.LH ].hh.b0 = mem [mem [p + 2 ].hh .v.LH 
	].hh.b0 ;
	mem [mem [r + 2 ].hh .v.LH ].hh.b1 = mem [mem [p + 2 ].hh .v.LH 
	].hh.b1 ;
	words = 2 ;
      } 
      break ;
    case 6 : 
      {
	r = getnode ( 2 ) ;
	mem [r + 1 ]= mem [p + 1 ];
	mem [r + 1 ].hh .v.RH = copynodelist ( mem [p + 1 ].hh .v.RH ) ;
      } 
      break ;
    case 7 : 
      {
	r = getnode ( 2 ) ;
	mem [r + 1 ].hh .v.LH = copynodelist ( mem [p + 1 ].hh .v.LH ) ;
	mem [r + 1 ].hh .v.RH = copynodelist ( mem [p + 1 ].hh .v.RH ) ;
      } 
      break ;
    case 4 : 
      {
	r = getnode ( 2 ) ;
	incr ( mem [mem [p + 1 ].hh .v.RH ].hh .v.LH ) ;
	words = 2 ;
      } 
      break ;
    case 5 : 
      {
	r = getnode ( 2 ) ;
	mem [r + 1 ].cint = copynodelist ( mem [p + 1 ].cint ) ;
      } 
      break ;
      default: 
      confusion ( 363 ) ;
      break ;
    } 
    while ( words > 0 ) {
	
      decr ( words ) ;
      mem [r + words ]= mem [p + words ];
    } 
    mem [q ].hh .v.RH = r ;
    q = r ;
    p = mem [p ].hh .v.RH ;
  } 
  mem [q ].hh .v.RH = -268435455L ;
  q = mem [h ].hh .v.RH ;
  {
    mem [h ].hh .v.RH = avail ;
    avail = h ;
	;
#ifdef STAT
    decr ( dynused ) ;
#endif /* STAT */
  } 
  Result = q ;
  return Result ;
} 
void 
zprintmode ( integer m ) 
{
  printmode_regmem 
  if ( m > 0 ) 
  switch ( m / ( 103 ) ) 
  {case 0 : 
    print ( 364 ) ;
    break ;
  case 1 : 
    print ( 365 ) ;
    break ;
  case 2 : 
    print ( 366 ) ;
    break ;
  } 
  else if ( m == 0 ) 
  print ( 367 ) ;
  else switch ( ( - (integer) m ) / ( 103 ) ) 
  {case 0 : 
    print ( 368 ) ;
    break ;
  case 1 : 
    print ( 369 ) ;
    break ;
  case 2 : 
    print ( 370 ) ;
    break ;
  } 
} 
void 
zprintinmode ( integer m ) 
{
  printinmode_regmem 
  if ( m > 0 ) 
  switch ( m / ( 103 ) ) 
  {case 0 : 
    print ( 371 ) ;
    break ;
  case 1 : 
    print ( 372 ) ;
    break ;
  case 2 : 
    print ( 373 ) ;
    break ;
  } 
  else if ( m == 0 ) 
  print ( 374 ) ;
  else switch ( ( - (integer) m ) / ( 103 ) ) 
  {case 0 : 
    print ( 375 ) ;
    break ;
  case 1 : 
    print ( 376 ) ;
    break ;
  case 2 : 
    print ( 377 ) ;
    break ;
  } 
} 
void 
pushnest ( void ) 
{
  pushnest_regmem 
  if ( nestptr > maxneststack ) 
  {
    maxneststack = nestptr ;
    if ( nestptr == nestsize ) 
    overflow ( 378 , nestsize ) ;
  } 
  nest [nestptr ]= curlist ;
  incr ( nestptr ) ;
  curlist .headfield = getavail () ;
  curlist .tailfield = curlist .headfield ;
  curlist .pgfield = 0 ;
  curlist .mlfield = line ;
  curlist .eTeXauxfield = -268435455L ;
} 
void 
popnest ( void ) 
{
  popnest_regmem 
  {
    mem [curlist .headfield ].hh .v.RH = avail ;
    avail = curlist .headfield ;
	;
#ifdef STAT
    decr ( dynused ) ;
#endif /* STAT */
  } 
  decr ( nestptr ) ;
  curlist = nest [nestptr ];
} 
void 
showactivities ( void ) 
{
  showactivities_regmem 
  integer p  ;
  short m  ;
  memoryword a  ;
  halfword q, r  ;
  integer t  ;
  nest [nestptr ]= curlist ;
  printnl ( 345 ) ;
  println () ;
  {register integer for_end; p = nestptr ;for_end = 0 ; if ( p >= for_end) 
  do 
    {
      m = nest [p ].modefield ;
      a = nest [p ].auxfield ;
      printnl ( 379 ) ;
      printmode ( m ) ;
      print ( 380 ) ;
      printint ( abs ( nest [p ].mlfield ) ) ;
      if ( m == 104 ) {
	  
	if ( nest [p ].pgfield != 8585216L ) 
	{
	  print ( 381 ) ;
	  printint ( nest [p ].pgfield % 65536L ) ;
	  print ( 382 ) ;
	  printint ( nest [p ].pgfield / 4194304L ) ;
	  printchar ( 44 ) ;
	  printint ( ( nest [p ].pgfield / 65536L ) % 64 ) ;
	  printchar ( 41 ) ;
	} 
      } 
      if ( nest [p ].mlfield < 0 ) 
      print ( 383 ) ;
      if ( p == 0 ) 
      {
	if ( memtop - 2 != pagetail ) 
	{
	  printnl ( 1388 ) ;
	  if ( outputactive ) 
	  print ( 1389 ) ;
	  showbox ( mem [memtop - 2 ].hh .v.RH ) ;
	  if ( pagecontents > 0 ) 
	  {
	    printnl ( 1390 ) ;
	    printtotals () ;
	    printnl ( 1391 ) ;
	    printscaled ( pagesofar [0 ]) ;
	    r = mem [memtop ].hh .v.RH ;
	    while ( r != memtop ) {
		
	      println () ;
	      printesc ( 337 ) ;
	      t = mem [r ].hh.b1 ;
	      printint ( t ) ;
	      print ( 1392 ) ;
	      if ( eqtb [29375 + t ].cint == 1000 ) 
	      t = mem [r + 3 ].cint ;
	      else t = xovern ( mem [r + 3 ].cint , 1000 ) * eqtb [29375 + 
	      t ].cint ;
	      printscaled ( t ) ;
	      if ( mem [r ].hh.b0 == 1 ) 
	      {
		q = memtop - 2 ;
		t = 0 ;
		do {
		    q = mem [q ].hh .v.RH ;
		  if ( ( mem [q ].hh.b0 == 3 ) && ( mem [q ].hh.b1 == mem 
		  [r ].hh.b1 ) ) 
		  incr ( t ) ;
		} while ( ! ( q == mem [r + 1 ].hh .v.LH ) ) ;
		print ( 1393 ) ;
		printint ( t ) ;
		print ( 1394 ) ;
	      } 
	      r = mem [r ].hh .v.RH ;
	    } 
	  } 
	} 
	if ( mem [memtop - 1 ].hh .v.RH != -268435455L ) 
	printnl ( 384 ) ;
      } 
      showbox ( mem [nest [p ].headfield ].hh .v.RH ) ;
      switch ( abs ( m ) / ( 103 ) ) 
      {case 0 : 
	{
	  printnl ( 385 ) ;
	  if ( a .cint <= eqtb [29919 ].cint ) 
	  print ( 386 ) ;
	  else printscaled ( a .cint ) ;
	  if ( nest [p ].pgfield != 0 ) 
	  {
	    print ( 387 ) ;
	    printint ( nest [p ].pgfield ) ;
	    if ( nest [p ].pgfield != 1 ) 
	    print ( 388 ) ;
	    else print ( 389 ) ;
	  } 
	} 
	break ;
      case 1 : 
	{
	  printnl ( 390 ) ;
	  printint ( a .hh .v.LH ) ;
	  if ( m > 0 ) {
	      
	    if ( a .hh .v.RH > 0 ) 
	    {
	      print ( 391 ) ;
	      printint ( a .hh .v.RH ) ;
	    } 
	  } 
	} 
	break ;
      case 2 : 
	if ( a .cint != -268435455L ) 
	{
	  print ( 392 ) ;
	  showbox ( a .cint ) ;
	} 
	break ;
      } 
    } 
  while ( p-- > for_end ) ;} 
} 
void 
zprintparam ( integer n ) 
{
  printparam_regmem 
  switch ( n ) 
  {case 0 : 
    printesc ( 440 ) ;
    break ;
  case 1 : 
    printesc ( 441 ) ;
    break ;
  case 2 : 
    printesc ( 442 ) ;
    break ;
  case 3 : 
    printesc ( 443 ) ;
    break ;
  case 4 : 
    printesc ( 444 ) ;
    break ;
  case 5 : 
    printesc ( 445 ) ;
    break ;
  case 6 : 
    printesc ( 446 ) ;
    break ;
  case 7 : 
    printesc ( 447 ) ;
    break ;
  case 8 : 
    printesc ( 448 ) ;
    break ;
  case 9 : 
    printesc ( 449 ) ;
    break ;
  case 10 : 
    printesc ( 450 ) ;
    break ;
  case 11 : 
    printesc ( 451 ) ;
    break ;
  case 12 : 
    printesc ( 452 ) ;
    break ;
  case 13 : 
    printesc ( 453 ) ;
    break ;
  case 14 : 
    printesc ( 454 ) ;
    break ;
  case 15 : 
    printesc ( 455 ) ;
    break ;
  case 16 : 
    printesc ( 456 ) ;
    break ;
  case 17 : 
    printesc ( 457 ) ;
    break ;
  case 18 : 
    printesc ( 458 ) ;
    break ;
  case 19 : 
    printesc ( 459 ) ;
    break ;
  case 20 : 
    printesc ( 460 ) ;
    break ;
  case 21 : 
    printesc ( 461 ) ;
    break ;
  case 22 : 
    printesc ( 462 ) ;
    break ;
  case 23 : 
    printesc ( 463 ) ;
    break ;
  case 24 : 
    printesc ( 464 ) ;
    break ;
  case 25 : 
    printesc ( 465 ) ;
    break ;
  case 26 : 
    printesc ( 466 ) ;
    break ;
  case 27 : 
    printesc ( 467 ) ;
    break ;
  case 28 : 
    printesc ( 468 ) ;
    break ;
  case 29 : 
    printesc ( 469 ) ;
    break ;
  case 30 : 
    printesc ( 470 ) ;
    break ;
  case 31 : 
    printesc ( 471 ) ;
    break ;
  case 32 : 
    printesc ( 472 ) ;
    break ;
  case 33 : 
    printesc ( 473 ) ;
    break ;
  case 34 : 
    printesc ( 474 ) ;
    break ;
  case 35 : 
    printesc ( 475 ) ;
    break ;
  case 36 : 
    printesc ( 476 ) ;
    break ;
  case 37 : 
    printesc ( 477 ) ;
    break ;
  case 38 : 
    printesc ( 478 ) ;
    break ;
  case 39 : 
    printesc ( 479 ) ;
    break ;
  case 40 : 
    printesc ( 480 ) ;
    break ;
  case 41 : 
    printesc ( 481 ) ;
    break ;
  case 42 : 
    printesc ( 482 ) ;
    break ;
  case 43 : 
    printesc ( 483 ) ;
    break ;
  case 44 : 
    printesc ( 484 ) ;
    break ;
  case 45 : 
    printesc ( 485 ) ;
    break ;
  case 46 : 
    printesc ( 486 ) ;
    break ;
  case 47 : 
    printesc ( 487 ) ;
    break ;
  case 48 : 
    printesc ( 488 ) ;
    break ;
  case 49 : 
    printesc ( 489 ) ;
    break ;
  case 50 : 
    printesc ( 490 ) ;
    break ;
  case 51 : 
    printesc ( 491 ) ;
    break ;
  case 52 : 
    printesc ( 492 ) ;
    break ;
  case 53 : 
    printesc ( 493 ) ;
    break ;
  case 54 : 
    printesc ( 494 ) ;
    break ;
  case 55 : 
    printesc ( 495 ) ;
    break ;
  case 56 : 
    printesc ( 496 ) ;
    break ;
  case 57 : 
    printesc ( 497 ) ;
    break ;
  case 58 : 
    printesc ( 498 ) ;
    break ;
  case 59 : 
    printesc ( 499 ) ;
    break ;
  case 78 : 
    printesc ( 500 ) ;
    break ;
  case 60 : 
    printesc ( 501 ) ;
    break ;
  case 61 : 
    printesc ( 502 ) ;
    break ;
  case 62 : 
    printesc ( 503 ) ;
    break ;
  case 63 : 
    printesc ( 504 ) ;
    break ;
  case 64 : 
    printesc ( 505 ) ;
    break ;
  case 65 : 
    printesc ( 506 ) ;
    break ;
  case 66 : 
    printesc ( 507 ) ;
    break ;
  case 67 : 
    printesc ( 508 ) ;
    break ;
  case 68 : 
    printesc ( 509 ) ;
    break ;
  case 69 : 
    printesc ( 510 ) ;
    break ;
  case 70 : 
    printesc ( 511 ) ;
    break ;
  case 71 : 
    printesc ( 512 ) ;
    break ;
  case 72 : 
    printesc ( 513 ) ;
    break ;
  case 73 : 
    printesc ( 514 ) ;
    break ;
  case 74 : 
    printesc ( 515 ) ;
    break ;
  case 75 : 
    printesc ( 516 ) ;
    break ;
  case 76 : 
    printesc ( 517 ) ;
    break ;
  case 77 : 
    printesc ( 518 ) ;
    break ;
  case 79 : 
    printesc ( 519 ) ;
    break ;
  case 80 : 
    printesc ( 520 ) ;
    break ;
  case 81 : 
    printesc ( 521 ) ;
    break ;
  case 82 : 
    printesc ( 522 ) ;
    break ;
  case 83 : 
    printesc ( 523 ) ;
    break ;
  case 84 : 
    printesc ( 524 ) ;
    break ;
  case 85 : 
    printesc ( 525 ) ;
    break ;
  case 86 : 
    printesc ( 526 ) ;
    break ;
  case 87 : 
    printesc ( 527 ) ;
    break ;
  case 88 : 
    printesc ( 528 ) ;
    break ;
  case 89 : 
    printesc ( 529 ) ;
    break ;
  case 90 : 
    printesc ( 530 ) ;
    break ;
  case 91 : 
    printesc ( 1953 ) ;
    break ;
  case 92 : 
    printesc ( 1954 ) ;
    break ;
  case 93 : 
    printesc ( 1955 ) ;
    break ;
  case 94 : 
    printesc ( 1956 ) ;
    break ;
  case 95 : 
    printesc ( 1957 ) ;
    break ;
  case 96 : 
    printesc ( 1958 ) ;
    break ;
  case 97 : 
    printesc ( 1959 ) ;
    break ;
  case 98 : 
    printesc ( 1960 ) ;
    break ;
  case 99 : 
    printesc ( 1961 ) ;
    break ;
  case 100 : 
    printesc ( 2001 ) ;
    break ;
    default: 
    print ( 531 ) ;
    break ;
  } 
} 
void 
begindiagnostic ( void ) 
{
  begindiagnostic_regmem 
  oldsetting = selector ;
  if ( ( eqtb [29303 ].cint <= 0 ) && ( selector == 19 ) ) 
  {
    decr ( selector ) ;
    if ( history == 0 ) 
    history = 1 ;
  } 
} 
void 
zenddiagnostic ( boolean blankline ) 
{
  enddiagnostic_regmem 
  printnl ( 345 ) ;
  if ( blankline ) 
  println () ;
  selector = oldsetting ;
} 
void 
zprintlengthparam ( integer n ) 
{
  printlengthparam_regmem 
  switch ( n ) 
  {case 0 : 
    printesc ( 535 ) ;
    break ;
  case 1 : 
    printesc ( 536 ) ;
    break ;
  case 2 : 
    printesc ( 537 ) ;
    break ;
  case 3 : 
    printesc ( 538 ) ;
    break ;
  case 4 : 
    printesc ( 539 ) ;
    break ;
  case 5 : 
    printesc ( 540 ) ;
    break ;
  case 6 : 
    printesc ( 541 ) ;
    break ;
  case 7 : 
    printesc ( 542 ) ;
    break ;
  case 8 : 
    printesc ( 543 ) ;
    break ;
  case 9 : 
    printesc ( 544 ) ;
    break ;
  case 10 : 
    printesc ( 545 ) ;
    break ;
  case 11 : 
    printesc ( 546 ) ;
    break ;
  case 12 : 
    printesc ( 547 ) ;
    break ;
  case 13 : 
    printesc ( 548 ) ;
    break ;
  case 14 : 
    printesc ( 549 ) ;
    break ;
  case 15 : 
    printesc ( 550 ) ;
    break ;
  case 16 : 
    printesc ( 551 ) ;
    break ;
  case 17 : 
    printesc ( 552 ) ;
    break ;
  case 18 : 
    printesc ( 553 ) ;
    break ;
  case 19 : 
    printesc ( 554 ) ;
    break ;
  case 20 : 
    printesc ( 555 ) ;
    break ;
  case 21 : 
    printesc ( 556 ) ;
    break ;
  case 22 : 
    printesc ( 557 ) ;
    break ;
  case 23 : 
    printesc ( 558 ) ;
    break ;
  case 24 : 
    printesc ( 559 ) ;
    break ;
  case 25 : 
    printesc ( 560 ) ;
    break ;
  case 26 : 
    printesc ( 561 ) ;
    break ;
  case 27 : 
    printesc ( 562 ) ;
    break ;
  case 28 : 
    printesc ( 563 ) ;
    break ;
  case 29 : 
    printesc ( 564 ) ;
    break ;
  case 30 : 
    printesc ( 565 ) ;
    break ;
  case 31 : 
    printesc ( 566 ) ;
    break ;
  case 32 : 
    printesc ( 567 ) ;
    break ;
  case 33 : 
    printesc ( 568 ) ;
    break ;
    default: 
    print ( 569 ) ;
    break ;
  } 
} 
void 
zprintcmdchr ( quarterword cmd , halfword chrcode ) 
{
  printcmdchr_regmem 
  integer n  ;
  switch ( cmd ) 
  {case 1 : 
    {
      print ( 635 ) ;
      print ( chrcode ) ;
    } 
    break ;
  case 2 : 
    {
      print ( 636 ) ;
      print ( chrcode ) ;
    } 
    break ;
  case 3 : 
    {
      print ( 637 ) ;
      print ( chrcode ) ;
    } 
    break ;
  case 6 : 
    {
      print ( 638 ) ;
      print ( chrcode ) ;
    } 
    break ;
  case 7 : 
    {
      print ( 639 ) ;
      print ( chrcode ) ;
    } 
    break ;
  case 8 : 
    {
      print ( 640 ) ;
      print ( chrcode ) ;
    } 
    break ;
  case 9 : 
    print ( 641 ) ;
    break ;
  case 10 : 
    {
      print ( 642 ) ;
      print ( chrcode ) ;
    } 
    break ;
  case 11 : 
    {
      print ( 643 ) ;
      print ( chrcode ) ;
    } 
    break ;
  case 12 : 
    {
      print ( 644 ) ;
      print ( chrcode ) ;
    } 
    break ;
  case 75 : 
  case 76 : 
    if ( chrcode < 26646 ) 
    printskipparam ( chrcode - 26628 ) ;
    else if ( chrcode < 26902 ) 
    {
      printesc ( 412 ) ;
      printint ( chrcode - 26646 ) ;
    } 
    else {
	
      printesc ( 413 ) ;
      printint ( chrcode - 26902 ) ;
    } 
    break ;
  case 72 : 
    if ( chrcode >= 27173 ) 
    {
      printesc ( 427 ) ;
      printint ( chrcode - 27173 ) ;
    } 
    else switch ( chrcode ) 
    {case 27159 : 
      printesc ( 414 ) ;
      break ;
    case 27160 : 
      printesc ( 415 ) ;
      break ;
    case 27161 : 
      printesc ( 416 ) ;
      break ;
    case 27162 : 
      printesc ( 417 ) ;
      break ;
    case 27163 : 
      printesc ( 418 ) ;
      break ;
    case 27164 : 
      printesc ( 419 ) ;
      break ;
    case 27165 : 
      printesc ( 420 ) ;
      break ;
    case 27166 : 
      printesc ( 421 ) ;
      break ;
    case 27172 : 
      printesc ( 1952 ) ;
      break ;
    case 27168 : 
      printesc ( 423 ) ;
      break ;
    case 27169 : 
      printesc ( 424 ) ;
      break ;
    case 27170 : 
      printesc ( 425 ) ;
      break ;
    case 27171 : 
      printesc ( 426 ) ;
      break ;
      default: 
      printesc ( 422 ) ;
      break ;
    } 
    break ;
  case 73 : 
    if ( chrcode < 29375 ) 
    printparam ( chrcode - 29274 ) ;
    else {
	
      printesc ( 533 ) ;
      printint ( chrcode - 29375 ) ;
    } 
    break ;
  case 74 : 
    if ( chrcode < 29921 ) 
    printlengthparam ( chrcode - 29887 ) ;
    else {
	
      printesc ( 570 ) ;
      printint ( chrcode - 29921 ) ;
    } 
    break ;
  case 45 : 
    printesc ( 580 ) ;
    break ;
  case 90 : 
    printesc ( 581 ) ;
    break ;
  case 40 : 
    printesc ( 582 ) ;
    break ;
  case 41 : 
    printesc ( 583 ) ;
    break ;
  case 77 : 
    printesc ( 593 ) ;
    break ;
  case 61 : 
    printesc ( 584 ) ;
    break ;
  case 42 : 
    printesc ( 606 ) ;
    break ;
  case 16 : 
    printesc ( 585 ) ;
    break ;
  case 109 : 
    printesc ( 576 ) ;
    break ;
  case 88 : 
    printesc ( 590 ) ;
    break ;
  case 101 : 
    printesc ( 591 ) ;
    break ;
  case 102 : 
    printesc ( 592 ) ;
    break ;
  case 15 : 
    printesc ( 586 ) ;
    break ;
  case 92 : 
    printesc ( 587 ) ;
    break ;
  case 67 : 
    printesc ( 577 ) ;
    break ;
  case 62 : 
    printesc ( 588 ) ;
    break ;
  case 64 : 
    printesc ( 32 ) ;
    break ;
  case 104 : 
    if ( chrcode == 0 ) 
    printesc ( 589 ) ;
    else printesc ( 923 ) ;
    break ;
  case 32 : 
    printesc ( 594 ) ;
    break ;
  case 36 : 
    printesc ( 595 ) ;
    break ;
  case 39 : 
    if ( chrcode == 0 ) 
    printesc ( 596 ) ;
    else printesc ( 573 ) ;
    break ;
  case 37 : 
    printesc ( 337 ) ;
    break ;
  case 44 : 
    printesc ( 47 ) ;
    break ;
  case 18 : 
    {
      printesc ( 359 ) ;
      if ( chrcode > 0 ) 
      printchar ( 115 ) ;
    } 
    break ;
  case 46 : 
    printesc ( 597 ) ;
    break ;
  case 17 : 
    printesc ( 598 ) ;
    break ;
  case 54 : 
    printesc ( 599 ) ;
    break ;
  case 91 : 
    printesc ( 600 ) ;
    break ;
  case 34 : 
    printesc ( 601 ) ;
    break ;
  case 65 : 
    printesc ( 602 ) ;
    break ;
  case 105 : 
    if ( chrcode == 0 ) 
    printesc ( 603 ) ;
    else printesc ( 573 ) ;
    break ;
  case 55 : 
    printesc ( 342 ) ;
    break ;
  case 63 : 
    printesc ( 604 ) ;
    break ;
  case 66 : 
    printesc ( 608 ) ;
    break ;
  case 96 : 
    if ( chrcode == 0 ) 
    printesc ( 609 ) ;
    else printesc ( 2016 ) ;
    break ;
  case 0 : 
    printesc ( 610 ) ;
    break ;
  case 98 : 
    printesc ( 611 ) ;
    break ;
  case 80 : 
    printesc ( 607 ) ;
    break ;
  case 84 : 
    switch ( chrcode ) 
    {case 27158 : 
      printesc ( 605 ) ;
      break ;
    case 27429 : 
      printesc ( 2052 ) ;
      break ;
    case 27430 : 
      printesc ( 2053 ) ;
      break ;
    case 27431 : 
      printesc ( 2054 ) ;
      break ;
    case 27432 : 
      printesc ( 2055 ) ;
      break ;
    } 
    break ;
  case 111 : 
    if ( chrcode == 0 ) 
    printesc ( 612 ) ;
    else if ( chrcode == 1 ) 
    printesc ( 1991 ) ;
    else printesc ( 1992 ) ;
    break ;
  case 71 : 
    {
      printesc ( 427 ) ;
      if ( chrcode != membot ) 
      printsanum ( chrcode ) ;
    } 
    break ;
  case 38 : 
    printesc ( 360 ) ;
    break ;
  case 33 : 
    if ( chrcode == 0 ) 
    printesc ( 613 ) ;
    else switch ( chrcode ) 
    {case 6 : 
      printesc ( 2002 ) ;
      break ;
    case 7 : 
      printesc ( 2003 ) ;
      break ;
    case 10 : 
      printesc ( 2004 ) ;
      break ;
      default: 
      printesc ( 2005 ) ;
      break ;
    } 
    break ;
  case 56 : 
    printesc ( 614 ) ;
    break ;
  case 35 : 
    printesc ( 615 ) ;
    break ;
  case 13 : 
    printesc ( 676 ) ;
    break ;
  case 106 : 
    if ( chrcode == 0 ) 
    printesc ( 711 ) ;
    else if ( chrcode == 2 ) 
    printesc ( 2014 ) ;
    else printesc ( 712 ) ;
    break ;
  case 112 : 
    {
      switch ( ( chrcode % 5 ) ) 
      {case 1 : 
	printesc ( 714 ) ;
	break ;
      case 2 : 
	printesc ( 715 ) ;
	break ;
      case 3 : 
	printesc ( 716 ) ;
	break ;
      case 4 : 
	printesc ( 717 ) ;
	break ;
	default: 
	printesc ( 713 ) ;
	break ;
      } 
      if ( chrcode >= 5 ) 
      printchar ( 115 ) ;
    } 
    break ;
  case 89 : 
    {
      if ( ( chrcode < membot ) || ( chrcode > membot + 19 ) ) 
      cmd = ( mem [chrcode ].hh.b0 / 16 ) ;
      else {
	  
	cmd = chrcode - membot ;
	chrcode = -268435455L ;
      } 
      if ( cmd == 0 ) 
      printesc ( 533 ) ;
      else if ( cmd == 1 ) 
      printesc ( 570 ) ;
      else if ( cmd == 2 ) 
      printesc ( 412 ) ;
      else printesc ( 413 ) ;
      if ( chrcode != -268435455L ) 
      printsanum ( chrcode ) ;
    } 
    break ;
  case 79 : 
    if ( chrcode == 1 ) 
    printesc ( 751 ) ;
    else printesc ( 750 ) ;
    break ;
  case 82 : 
    if ( chrcode == 0 ) 
    printesc ( 752 ) ;
    else if ( chrcode == 2 ) 
    printesc ( 1997 ) ;
    else printesc ( 753 ) ;
    break ;
  case 83 : 
    if ( chrcode == 1 ) 
    printesc ( 754 ) ;
    else if ( chrcode == 3 ) 
    printesc ( 755 ) ;
    else printesc ( 756 ) ;
    break ;
  case 70 : 
    switch ( chrcode ) 
    {case 0 : 
      printesc ( 757 ) ;
      break ;
    case 1 : 
      printesc ( 758 ) ;
      break ;
    case 2 : 
      printesc ( 759 ) ;
      break ;
    case 4 : 
      printesc ( 760 ) ;
      break ;
    case 3 : 
      printesc ( 1949 ) ;
      break ;
    case 20 : 
      printesc ( 1950 ) ;
      break ;
    case 21 : 
      printesc ( 1976 ) ;
      break ;
    case 22 : 
      printesc ( 1977 ) ;
      break ;
    case 23 : 
      printesc ( 1978 ) ;
      break ;
    case 24 : 
      printesc ( 1979 ) ;
      break ;
    case 25 : 
      printesc ( 1980 ) ;
      break ;
    case 28 : 
      printesc ( 1981 ) ;
      break ;
    case 29 : 
      printesc ( 1982 ) ;
      break ;
    case 30 : 
      printesc ( 1983 ) ;
      break ;
    case 31 : 
      printesc ( 1984 ) ;
      break ;
    case 32 : 
      printesc ( 1985 ) ;
      break ;
    case 33 : 
      printesc ( 1986 ) ;
      break ;
    case 34 : 
      printesc ( 1987 ) ;
      break ;
    case 39 : 
      printesc ( 2028 ) ;
      break ;
    case 40 : 
      printesc ( 2029 ) ;
      break ;
    case 41 : 
      printesc ( 2030 ) ;
      break ;
    case 42 : 
      printesc ( 2031 ) ;
      break ;
    case 26 : 
      printesc ( 2035 ) ;
      break ;
    case 27 : 
      printesc ( 2036 ) ;
      break ;
    case 35 : 
      printesc ( 2037 ) ;
      break ;
    case 36 : 
      printesc ( 2038 ) ;
      break ;
    case 37 : 
      printesc ( 2039 ) ;
      break ;
    case 38 : 
      printesc ( 2040 ) ;
      break ;
    case 6 : 
      printesc ( 762 ) ;
      break ;
    case 7 : 
      printesc ( 763 ) ;
      break ;
    case 8 : 
      printesc ( 764 ) ;
      break ;
    case 9 : 
      printesc ( 765 ) ;
      break ;
    case 10 : 
      printesc ( 766 ) ;
      break ;
    case 11 : 
      printesc ( 767 ) ;
      break ;
    case 12 : 
      printesc ( 768 ) ;
      break ;
    case 13 : 
      printesc ( 769 ) ;
      break ;
    case 14 : 
      printesc ( 770 ) ;
      break ;
    case 15 : 
      printesc ( 771 ) ;
      break ;
    case 16 : 
      printesc ( 772 ) ;
      break ;
    case 17 : 
      printesc ( 773 ) ;
      break ;
    case 18 : 
      printesc ( 774 ) ;
      break ;
    case 19 : 
      printesc ( 775 ) ;
      break ;
      default: 
      printesc ( 761 ) ;
      break ;
    } 
    break ;
  case 110 : 
    switch ( chrcode ) 
    {case 0 : 
      printesc ( 834 ) ;
      break ;
    case 1 : 
      printesc ( 835 ) ;
      break ;
    case 2 : 
      printesc ( 836 ) ;
      break ;
    case 3 : 
      printesc ( 837 ) ;
      break ;
    case 4 : 
      printesc ( 838 ) ;
      break ;
    case 5 : 
      printesc ( 867 ) ;
      break ;
    case 6 : 
      printesc ( 839 ) ;
      break ;
    case 7 : 
      printesc ( 840 ) ;
      break ;
    case 8 : 
      printesc ( 841 ) ;
      break ;
    case 9 : 
      printesc ( 842 ) ;
      break ;
    case 10 : 
      printesc ( 843 ) ;
      break ;
    case 11 : 
      printesc ( 844 ) ;
      break ;
    case 12 : 
      printesc ( 845 ) ;
      break ;
    case 16 : 
      printesc ( 846 ) ;
      break ;
    case 17 : 
      printesc ( 847 ) ;
      break ;
    case 13 : 
      printesc ( 848 ) ;
      break ;
    case 14 : 
      printesc ( 849 ) ;
      break ;
    case 15 : 
      printesc ( 850 ) ;
      break ;
    case 20 : 
      printesc ( 851 ) ;
      break ;
    case 21 : 
      printesc ( 852 ) ;
      break ;
    case 22 : 
      printesc ( 853 ) ;
      break ;
    case 23 : 
      printesc ( 854 ) ;
      break ;
    case 24 : 
      printesc ( 855 ) ;
      break ;
    case 25 : 
      printesc ( 856 ) ;
      break ;
    case 26 : 
      printesc ( 857 ) ;
      break ;
    case 27 : 
      printesc ( 858 ) ;
      break ;
    case 28 : 
      printesc ( 859 ) ;
      break ;
    case 18 : 
      printesc ( 860 ) ;
      break ;
    case 19 : 
      printesc ( 861 ) ;
      break ;
    case 29 : 
      printesc ( 862 ) ;
      break ;
    case 30 : 
      printesc ( 863 ) ;
      break ;
    case 31 : 
      printesc ( 865 ) ;
      break ;
    case 32 : 
      printesc ( 866 ) ;
      break ;
      default: 
      printesc ( 864 ) ;
      break ;
    } 
    break ;
  case 107 : 
    {
      if ( chrcode >= 32 ) 
      printesc ( 923 ) ;
      switch ( chrcode % 32 ) 
      {case 1 : 
	printesc ( 906 ) ;
	break ;
      case 2 : 
	printesc ( 907 ) ;
	break ;
      case 3 : 
	printesc ( 908 ) ;
	break ;
      case 4 : 
	printesc ( 909 ) ;
	break ;
      case 5 : 
	printesc ( 910 ) ;
	break ;
      case 6 : 
	printesc ( 911 ) ;
	break ;
      case 7 : 
	printesc ( 912 ) ;
	break ;
      case 8 : 
	printesc ( 913 ) ;
	break ;
      case 9 : 
	printesc ( 914 ) ;
	break ;
      case 10 : 
	printesc ( 915 ) ;
	break ;
      case 11 : 
	printesc ( 916 ) ;
	break ;
      case 12 : 
	printesc ( 917 ) ;
	break ;
      case 13 : 
	printesc ( 918 ) ;
	break ;
      case 14 : 
	printesc ( 919 ) ;
	break ;
      case 15 : 
	printesc ( 920 ) ;
	break ;
      case 16 : 
	printesc ( 921 ) ;
	break ;
      case 21 : 
	printesc ( 922 ) ;
	break ;
      case 17 : 
	printesc ( 2017 ) ;
	break ;
      case 18 : 
	printesc ( 2018 ) ;
	break ;
      case 19 : 
	printesc ( 2019 ) ;
	break ;
      case 20 : 
	printesc ( 2020 ) ;
	break ;
      case 22 : 
	printesc ( 2021 ) ;
	break ;
      case 23 : 
	printesc ( 2022 ) ;
	break ;
	default: 
	printesc ( 905 ) ;
	break ;
      } 
    } 
    break ;
  case 108 : 
    if ( chrcode == 2 ) 
    printesc ( 924 ) ;
    else if ( chrcode == 4 ) 
    printesc ( 925 ) ;
    else printesc ( 926 ) ;
    break ;
  case 4 : 
    if ( chrcode == 256 ) 
    printesc ( 1300 ) ;
    else {
	
      print ( 1304 ) ;
      print ( chrcode ) ;
    } 
    break ;
  case 5 : 
    if ( chrcode == 257 ) 
    printesc ( 1301 ) ;
    else printesc ( 1302 ) ;
    break ;
  case 81 : 
    switch ( chrcode ) 
    {case 0 : 
      printesc ( 1378 ) ;
      break ;
    case 1 : 
      printesc ( 1379 ) ;
      break ;
    case 2 : 
      printesc ( 1380 ) ;
      break ;
    case 3 : 
      printesc ( 1381 ) ;
      break ;
    case 4 : 
      printesc ( 1382 ) ;
      break ;
    case 5 : 
      printesc ( 1383 ) ;
      break ;
    case 6 : 
      printesc ( 1384 ) ;
      break ;
      default: 
      printesc ( 1385 ) ;
      break ;
    } 
    break ;
  case 14 : 
    if ( chrcode == 1 ) 
    printesc ( 1431 ) ;
    else printesc ( 349 ) ;
    break ;
  case 26 : 
    switch ( chrcode ) 
    {case 4 : 
      printesc ( 1432 ) ;
      break ;
    case 0 : 
      printesc ( 1433 ) ;
      break ;
    case 1 : 
      printesc ( 1434 ) ;
      break ;
    case 2 : 
      printesc ( 1435 ) ;
      break ;
      default: 
      printesc ( 1436 ) ;
      break ;
    } 
    break ;
  case 27 : 
    switch ( chrcode ) 
    {case 4 : 
      printesc ( 1437 ) ;
      break ;
    case 0 : 
      printesc ( 1438 ) ;
      break ;
    case 1 : 
      printesc ( 1439 ) ;
      break ;
    case 2 : 
      printesc ( 1440 ) ;
      break ;
      default: 
      printesc ( 1441 ) ;
      break ;
    } 
    break ;
  case 28 : 
    printesc ( 343 ) ;
    break ;
  case 29 : 
    printesc ( 322 ) ;
    break ;
  case 30 : 
    printesc ( 348 ) ;
    break ;
  case 21 : 
    if ( chrcode == 1 ) 
    printesc ( 1459 ) ;
    else printesc ( 1460 ) ;
    break ;
  case 22 : 
    if ( chrcode == 1 ) 
    printesc ( 1461 ) ;
    else printesc ( 1462 ) ;
    break ;
  case 20 : 
    switch ( chrcode ) 
    {case 0 : 
      printesc ( 429 ) ;
      break ;
    case 1 : 
      printesc ( 1463 ) ;
      break ;
    case 2 : 
      printesc ( 1464 ) ;
      break ;
    case 3 : 
      printesc ( 1373 ) ;
      break ;
    case 4 : 
      printesc ( 1465 ) ;
      break ;
    case 5 : 
      printesc ( 1375 ) ;
      break ;
      default: 
      printesc ( 1466 ) ;
      break ;
    } 
    break ;
  case 31 : 
    if ( chrcode == 100 ) 
    printesc ( 1468 ) ;
    else if ( chrcode == 101 ) 
    printesc ( 1469 ) ;
    else if ( chrcode == 102 ) 
    printesc ( 1470 ) ;
    else printesc ( 1467 ) ;
    break ;
  case 43 : 
    if ( chrcode == 0 ) 
    printesc ( 1487 ) ;
    else if ( chrcode == 1 ) 
    printesc ( 1486 ) ;
    else printesc ( 1488 ) ;
    break ;
  case 25 : 
    if ( chrcode == 10 ) 
    printesc ( 1500 ) ;
    else if ( chrcode == 11 ) 
    printesc ( 1499 ) ;
    else printesc ( 1498 ) ;
    break ;
  case 23 : 
    if ( chrcode == 1 ) 
    printesc ( 1502 ) ;
    else printesc ( 1501 ) ;
    break ;
  case 24 : 
    if ( chrcode == 1 ) 
    printesc ( 1504 ) ;
    else if ( chrcode == 2 ) 
    printesc ( 2050 ) ;
    else if ( chrcode == 3 ) 
    printesc ( 2051 ) ;
    else printesc ( 1503 ) ;
    break ;
  case 47 : 
    if ( chrcode == 1 ) 
    printesc ( 45 ) ;
    else printesc ( 357 ) ;
    break ;
  case 48 : 
    if ( chrcode == 1 ) 
    printesc ( 1536 ) ;
    else printesc ( 1535 ) ;
    break ;
  case 50 : 
    switch ( chrcode ) 
    {case 16 : 
      printesc ( 1267 ) ;
      break ;
    case 17 : 
      printesc ( 1268 ) ;
      break ;
    case 18 : 
      printesc ( 1269 ) ;
      break ;
    case 19 : 
      printesc ( 1270 ) ;
      break ;
    case 20 : 
      printesc ( 1271 ) ;
      break ;
    case 21 : 
      printesc ( 1272 ) ;
      break ;
    case 22 : 
      printesc ( 1273 ) ;
      break ;
    case 23 : 
      printesc ( 1274 ) ;
      break ;
    case 26 : 
      printesc ( 1276 ) ;
      break ;
      default: 
      printesc ( 1275 ) ;
      break ;
    } 
    break ;
  case 51 : 
    if ( chrcode == 1 ) 
    printesc ( 1280 ) ;
    else if ( chrcode == 2 ) 
    printesc ( 1281 ) ;
    else printesc ( 1537 ) ;
    break ;
  case 53 : 
    printstyle ( chrcode ) ;
    break ;
  case 52 : 
    switch ( chrcode ) 
    {case 1 : 
      printesc ( 1556 ) ;
      break ;
    case 2 : 
      printesc ( 1557 ) ;
      break ;
    case 3 : 
      printesc ( 1558 ) ;
      break ;
    case 4 : 
      printesc ( 1559 ) ;
      break ;
    case 5 : 
      printesc ( 1560 ) ;
      break ;
      default: 
      printesc ( 1555 ) ;
      break ;
    } 
    break ;
  case 49 : 
    if ( chrcode == 30 ) 
    printesc ( 1277 ) ;
    else if ( chrcode == 1 ) 
    printesc ( 1279 ) ;
    else printesc ( 1278 ) ;
    break ;
  case 93 : 
    if ( chrcode == 1 ) 
    printesc ( 1580 ) ;
    else if ( chrcode == 2 ) 
    printesc ( 1581 ) ;
    else if ( chrcode == 8 ) 
    printesc ( 1594 ) ;
    else printesc ( 1582 ) ;
    break ;
  case 97 : 
    if ( chrcode == 0 ) 
    printesc ( 1583 ) ;
    else if ( chrcode == 1 ) 
    printesc ( 1584 ) ;
    else if ( chrcode == 2 ) 
    printesc ( 1585 ) ;
    else printesc ( 1586 ) ;
    break ;
  case 94 : 
    if ( chrcode != 0 ) 
    printesc ( 1604 ) ;
    else printesc ( 1603 ) ;
    break ;
  case 95 : 
    switch ( chrcode ) 
    {case 0 : 
      printesc ( 1605 ) ;
      break ;
    case 1 : 
      printesc ( 1606 ) ;
      break ;
    case 2 : 
      printesc ( 1607 ) ;
      break ;
    case 3 : 
      printesc ( 1608 ) ;
      break ;
    case 4 : 
      printesc ( 1609 ) ;
      break ;
    case 5 : 
      printesc ( 1610 ) ;
      break ;
    case 7 : 
      printesc ( 1612 ) ;
      break ;
      default: 
      printesc ( 1611 ) ;
      break ;
    } 
    break ;
  case 68 : 
    {
      printesc ( 585 ) ;
      printhex ( chrcode ) ;
    } 
    break ;
  case 69 : 
    {
      printesc ( 598 ) ;
      printhex ( chrcode ) ;
    } 
    break ;
  case 85 : 
    if ( chrcode == 27738 ) 
    printesc ( 435 ) ;
    else if ( chrcode == 28762 ) 
    printesc ( 439 ) ;
    else if ( chrcode == 27994 ) 
    printesc ( 436 ) ;
    else if ( chrcode == 28250 ) 
    printesc ( 437 ) ;
    else if ( chrcode == 28506 ) 
    printesc ( 438 ) ;
    else printesc ( 534 ) ;
    break ;
  case 86 : 
    printsize ( chrcode - 27690 ) ;
    break ;
  case 99 : 
    if ( chrcode == 1 ) 
    printesc ( 1359 ) ;
    else printesc ( 1347 ) ;
    break ;
  case 78 : 
    switch ( chrcode ) 
    {case 0 : 
      printesc ( 1632 ) ;
      break ;
    case 1 : 
      printesc ( 1633 ) ;
      break ;
    case 2 : 
      printesc ( 1634 ) ;
      break ;
    case 3 : 
      printesc ( 1635 ) ;
      break ;
    case 4 : 
      printesc ( 1636 ) ;
      break ;
    case 5 : 
      printesc ( 1637 ) ;
      break ;
    case 7 : 
      printesc ( 1638 ) ;
      break ;
    case 8 : 
      printesc ( 1639 ) ;
      break ;
    case 9 : 
      printesc ( 1640 ) ;
      break ;
    case 10 : 
      printesc ( 1641 ) ;
      break ;
    case 11 : 
      printesc ( 1642 ) ;
      break ;
    case 6 : 
      printesc ( 1643 ) ;
      break ;
    } 
    break ;
  case 87 : 
    {
      print ( 1650 ) ;
      slowprint ( fontname [chrcode ]) ;
      if ( fontsize [chrcode ]!= fontdsize [chrcode ]) 
      {
	print ( 890 ) ;
	printscaled ( fontsize [chrcode ]) ;
	print ( 312 ) ;
      } 
    } 
    break ;
  case 100 : 
    switch ( chrcode ) 
    {case 0 : 
      printesc ( 274 ) ;
      break ;
    case 1 : 
      printesc ( 275 ) ;
      break ;
    case 2 : 
      printesc ( 276 ) ;
      break ;
      default: 
      printesc ( 1651 ) ;
      break ;
    } 
    break ;
  case 60 : 
    if ( chrcode == 0 ) 
    printesc ( 1653 ) ;
    else printesc ( 1652 ) ;
    break ;
  case 58 : 
    if ( chrcode == 0 ) 
    printesc ( 1654 ) ;
    else printesc ( 1655 ) ;
    break ;
  case 57 : 
    if ( chrcode == 27994 ) 
    printesc ( 1661 ) ;
    else printesc ( 1662 ) ;
    break ;
  case 19 : 
    switch ( chrcode ) 
    {case 1 : 
      printesc ( 1664 ) ;
      break ;
    case 2 : 
      printesc ( 1665 ) ;
      break ;
    case 3 : 
      printesc ( 1666 ) ;
      break ;
    case 4 : 
      printesc ( 1988 ) ;
      break ;
    case 5 : 
      printesc ( 1990 ) ;
      break ;
    case 6 : 
      printesc ( 1993 ) ;
      break ;
      default: 
      printesc ( 1663 ) ;
      break ;
    } 
    break ;
  case 103 : 
    print ( 1673 ) ;
    break ;
  case 113 : 
  case 114 : 
  case 115 : 
  case 116 : 
    {
      n = cmd - 113 ;
      if ( mem [mem [chrcode ].hh .v.RH ].hh .v.LH == 3585 ) 
      n = n + 4 ;
      if ( odd ( n / 4 ) ) 
      printesc ( 1594 ) ;
      if ( odd ( n ) ) 
      printesc ( 1580 ) ;
      if ( odd ( n / 2 ) ) 
      printesc ( 1581 ) ;
      if ( n > 0 ) 
      printchar ( 32 ) ;
      print ( 1674 ) ;
    } 
    break ;
  case 117 : 
    printesc ( 1675 ) ;
    break ;
  case 59 : 
    switch ( chrcode ) 
    {case 0 : 
      printesc ( 1713 ) ;
      break ;
    case 1 : 
      printesc ( 673 ) ;
      break ;
    case 2 : 
      printesc ( 1714 ) ;
      break ;
    case 3 : 
      printesc ( 1715 ) ;
      break ;
    case 4 : 
      printesc ( 1716 ) ;
      break ;
    case 5 : 
      printesc ( 1717 ) ;
      break ;
    case 13 : 
      printesc ( 1728 ) ;
      break ;
    case 23 : 
      printesc ( 1741 ) ;
      break ;
    case 17 : 
      printesc ( 1732 ) ;
      break ;
    case 15 : 
      printesc ( 1730 ) ;
      break ;
    case 20 : 
      printesc ( 1735 ) ;
      break ;
    case 25 : 
      printesc ( 1744 ) ;
      break ;
    case 32 : 
      printesc ( 1751 ) ;
      break ;
    case 26 : 
      printesc ( 1743 ) ;
      break ;
    case 22 : 
      printesc ( 1740 ) ;
      break ;
    case 6 : 
      printesc ( 1718 ) ;
      break ;
    case 38 : 
      printesc ( 1128 ) ;
      break ;
    case 39 : 
      printesc ( 1719 ) ;
      break ;
    case 40 : 
      printesc ( 1720 ) ;
      break ;
    case 41 : 
      printesc ( 1721 ) ;
      break ;
    case 27 : 
      printesc ( 1745 ) ;
      break ;
    case 28 : 
      printesc ( 1746 ) ;
      break ;
    case 24 : 
      printesc ( 1742 ) ;
      break ;
    case 7 : 
      printesc ( 1722 ) ;
      break ;
    case 16 : 
      printesc ( 1731 ) ;
      break ;
    case 8 : 
      printesc ( 1723 ) ;
      break ;
    case 10 : 
      printesc ( 1725 ) ;
      break ;
    case 12 : 
      printesc ( 1727 ) ;
      break ;
    case 21 : 
      printesc ( 1736 ) ;
      break ;
    case 34 : 
      printesc ( 1737 ) ;
      break ;
    case 36 : 
      printesc ( 1739 ) ;
      break ;
    case 35 : 
      printesc ( 1738 ) ;
      break ;
    case 14 : 
      printesc ( 1729 ) ;
      break ;
    case 19 : 
      printesc ( 1734 ) ;
      break ;
    case 18 : 
      printesc ( 1733 ) ;
      break ;
    case 29 : 
      printesc ( 1747 ) ;
      break ;
    case 30 : 
      printesc ( 1748 ) ;
      break ;
    case 9 : 
      printesc ( 1724 ) ;
      break ;
    case 11 : 
      printesc ( 1726 ) ;
      break ;
    case 31 : 
      printesc ( 1749 ) ;
      break ;
    case 33 : 
      printesc ( 1750 ) ;
      break ;
    case 42 : 
      printesc ( 1753 ) ;
      break ;
    case 37 : 
      printesc ( 1752 ) ;
      break ;
    case 43 : 
      printesc ( 1754 ) ;
      break ;
    case 44 : 
      printesc ( 1755 ) ;
      break ;
    case 45 : 
      printesc ( 1756 ) ;
      break ;
      default: 
      print ( 1757 ) ;
      break ;
    } 
    break ;
    default: 
    print ( 645 ) ;
    break ;
  } 
} 
#ifdef STAT
void 
zshoweqtb ( halfword n ) 
{
  showeqtb_regmem 
  if ( n < 1 ) 
  printchar ( 63 ) ;
  else if ( ( n < 26628 ) || ( ( n > 30176 ) && ( n <= eqtbtop ) ) ) 
  {
    sprintcs ( n ) ;
    printchar ( 61 ) ;
    printcmdchr ( eqtb [n ].hh.b0 , eqtb [n ].hh .v.RH ) ;
    if ( eqtb [n ].hh.b0 >= 113 ) 
    {
      printchar ( 58 ) ;
      showtokenlist ( mem [eqtb [n ].hh .v.RH ].hh .v.RH , -268435455L , 
      32 ) ;
    } 
  } 
  else if ( n < 27158 ) {
      
    if ( n < 26646 ) 
    {
      printskipparam ( n - 26628 ) ;
      printchar ( 61 ) ;
      if ( n < 26643 ) 
      printspec ( eqtb [n ].hh .v.RH , 312 ) ;
      else printspec ( eqtb [n ].hh .v.RH , 344 ) ;
    } 
    else if ( n < 26902 ) 
    {
      printesc ( 412 ) ;
      printint ( n - 26646 ) ;
      printchar ( 61 ) ;
      printspec ( eqtb [n ].hh .v.RH , 312 ) ;
    } 
    else {
	
      printesc ( 413 ) ;
      printint ( n - 26902 ) ;
      printchar ( 61 ) ;
      printspec ( eqtb [n ].hh .v.RH , 344 ) ;
    } 
  } 
  else if ( n < 29274 ) {
      
    if ( ( n == 27158 ) || ( ( n >= 27429 ) && ( n < 27433 ) ) ) 
    {
      printcmdchr ( 84 , n ) ;
      printchar ( 61 ) ;
      if ( eqtb [n ].hh .v.RH == -268435455L ) 
      printchar ( 48 ) ;
      else if ( n > 27158 ) 
      {
	printint ( mem [eqtb [n ].hh .v.RH + 1 ].cint ) ;
	printchar ( 32 ) ;
	printint ( mem [eqtb [n ].hh .v.RH + 2 ].cint ) ;
	if ( mem [eqtb [n ].hh .v.RH + 1 ].cint > 1 ) 
	printesc ( 428 ) ;
      } 
      else printint ( mem [eqtb [27158 ].hh .v.RH ].hh .v.LH ) ;
    } 
    else if ( n < 27173 ) 
    {
      printcmdchr ( 72 , n ) ;
      printchar ( 61 ) ;
      if ( eqtb [n ].hh .v.RH != -268435455L ) 
      showtokenlist ( mem [eqtb [n ].hh .v.RH ].hh .v.RH , -268435455L , 
      32 ) ;
    } 
    else if ( n < 27433 ) 
    {
      printesc ( 427 ) ;
      printint ( n - 27173 ) ;
      printchar ( 61 ) ;
      if ( eqtb [n ].hh .v.RH != -268435455L ) 
      showtokenlist ( mem [eqtb [n ].hh .v.RH ].hh .v.RH , -268435455L , 
      32 ) ;
    } 
    else if ( n < 27689 ) 
    {
      printesc ( 429 ) ;
      printint ( n - 27433 ) ;
      printchar ( 61 ) ;
      if ( eqtb [n ].hh .v.RH == -268435455L ) 
      print ( 430 ) ;
      else {
	  
	depththreshold = 0 ;
	breadthmax = 1 ;
	shownodelist ( eqtb [n ].hh .v.RH ) ;
      } 
    } 
    else if ( n < 27738 ) 
    {
      if ( n == 27689 ) 
      print ( 431 ) ;
      else if ( n < 27706 ) 
      {
	printesc ( 432 ) ;
	printint ( n - 27690 ) ;
      } 
      else if ( n < 27722 ) 
      {
	printesc ( 433 ) ;
	printint ( n - 27706 ) ;
      } 
      else {
	  
	printesc ( 434 ) ;
	printint ( n - 27722 ) ;
      } 
      printchar ( 61 ) ;
      printesc ( hash [17626 + eqtb [n ].hh .v.RH ].v.RH ) ;
    } 
    else if ( n < 28762 ) 
    {
      if ( n < 27994 ) 
      {
	printesc ( 435 ) ;
	printint ( n - 27738 ) ;
      } 
      else if ( n < 28250 ) 
      {
	printesc ( 436 ) ;
	printint ( n - 27994 ) ;
      } 
      else if ( n < 28506 ) 
      {
	printesc ( 437 ) ;
	printint ( n - 28250 ) ;
      } 
      else {
	  
	printesc ( 438 ) ;
	printint ( n - 28506 ) ;
      } 
      printchar ( 61 ) ;
      printint ( eqtb [n ].hh .v.RH ) ;
    } 
    else {
	
      printesc ( 439 ) ;
      printint ( n - 28762 ) ;
      printchar ( 61 ) ;
      printint ( eqtb [n ].hh .v.RH ) ;
    } 
  } 
  else if ( n < 29887 ) 
  {
    if ( n < 29375 ) 
    printparam ( n - 29274 ) ;
    else if ( n < 29631 ) 
    {
      printesc ( 533 ) ;
      printint ( n - 29375 ) ;
    } 
    else {
	
      printesc ( 534 ) ;
      printint ( n - 29631 ) ;
    } 
    printchar ( 61 ) ;
    printint ( eqtb [n ].cint ) ;
  } 
  else if ( n <= 30176 ) 
  {
    if ( n < 29921 ) 
    printlengthparam ( n - 29887 ) ;
    else {
	
      printesc ( 570 ) ;
      printint ( n - 29921 ) ;
    } 
    printchar ( 61 ) ;
    printscaled ( eqtb [n ].cint ) ;
    print ( 312 ) ;
  } 
  else printchar ( 63 ) ;
} 
#endif /* STAT */
halfword 
zidlookup ( integer j , integer l ) 
{
  /* 40 */ register halfword Result; idlookup_regmem 
  integer h  ;
  integer d  ;
  halfword p  ;
  halfword k  ;
  h = buffer [j ];
  {register integer for_end; k = j + 1 ;for_end = j + l - 1 ; if ( k <= 
  for_end) do 
    {
      h = h + h + buffer [k ];
      while ( h >= 8501 ) h = h - 8501 ;
    } 
  while ( k++ < for_end ) ;} 
  p = h + 514 ;
  while ( true ) {
      
    if ( hash [p ].v.RH > 0 ) {
	
      if ( ( strstart [hash [p ].v.RH + 1 ]- strstart [hash [p ].v.RH ]
      ) == l ) {
	  
	if ( streqbuf ( hash [p ].v.RH , j ) ) 
	goto lab40 ;
      } 
    } 
    if ( hash [p ].v.LH == 0 ) 
    {
      if ( nonewcontrolsequence ) 
      p = 26627 ;
      else {
	  
	if ( hash [p ].v.RH > 0 ) 
	{
	  if ( hashhigh < hashextra ) 
	  {
	    incr ( hashhigh ) ;
	    hash [p ].v.LH = hashhigh + 30176 ;
	    p = hashhigh + 30176 ;
	  } 
	  else {
	      
	    do {
		if ( ( hashused == 514 ) ) 
	      overflow ( 574 , 15000 + hashextra ) ;
	      decr ( hashused ) ;
	    } while ( ! ( hash [hashused ].v.RH == 0 ) ) ;
	    hash [p ].v.LH = hashused ;
	    p = hashused ;
	  } 
	} 
	{
	  if ( poolptr + l > poolsize ) 
	  overflow ( 259 , poolsize - initpoolptr ) ;
	} 
	d = ( poolptr - strstart [strptr ]) ;
	while ( poolptr > strstart [strptr ]) {
	    
	  decr ( poolptr ) ;
	  strpool [poolptr + l ]= strpool [poolptr ];
	} 
	{register integer for_end; k = j ;for_end = j + l - 1 ; if ( k <= 
	for_end) do 
	  {
	    strpool [poolptr ]= buffer [k ];
	    incr ( poolptr ) ;
	  } 
	while ( k++ < for_end ) ;} 
	hash [p ].v.RH = makestring () ;
	poolptr = poolptr + d ;
	;
#ifdef STAT
	incr ( cscount ) ;
#endif /* STAT */
      } 
      goto lab40 ;
    } 
    p = hash [p ].v.LH ;
  } 
  lab40: Result = p ;
  return Result ;
} 
halfword 
zprimlookup ( strnumber s ) 
{
  /* 40 */ register halfword Result; primlookup_regmem 
  integer h  ;
  halfword p  ;
  halfword k  ;
  integer j, l  ;
  if ( s <= 255 ) 
  {
    if ( s < 0 ) 
    {
      p = 0 ;
      goto lab40 ;
    } 
    else p = ( s % 1777 ) + 1 ;
  } 
  else {
      
    j = strstart [s ];
    if ( s == strptr ) 
    l = ( poolptr - strstart [strptr ]) ;
    else l = ( strstart [s + 1 ]- strstart [s ]) ;
    h = strpool [j ];
    {register integer for_end; k = j + 1 ;for_end = j + l - 1 ; if ( k <= 
    for_end) do 
      {
	h = h + h + strpool [k ];
	while ( h >= 1777 ) h = h - 1777 ;
      } 
    while ( k++ < for_end ) ;} 
    p = h + 1 ;
  } 
  while ( true ) {
      
    if ( prim [p ].v.RH > 256 ) 
    {
      if ( ( strstart [prim [p ].v.RH + 0 ]- strstart [prim [p ].v.RH - 
      1 ]) == l ) {
	  
	if ( streqstr ( prim [p ].v.RH - 1 , s ) ) 
	goto lab40 ;
      } 
    } 
    else if ( prim [p ].v.RH == 1 + s ) 
    goto lab40 ;
    if ( prim [p ].v.LH == 0 ) 
    {
      if ( nonewcontrolsequence ) 
      p = 0 ;
      else {
	  
	if ( prim [p ].v.RH > 0 ) 
	{
	  do {
	      if ( ( primused == 1 ) ) 
	    overflow ( 575 , 2100 ) ;
	    decr ( primused ) ;
	  } while ( ! ( prim [primused ].v.RH == 0 ) ) ;
	  prim [p ].v.LH = primused ;
	  p = primused ;
	} 
	prim [p ].v.RH = s + 1 ;
      } 
      goto lab40 ;
    } 
    p = prim [p ].v.LH ;
  } 
  lab40: Result = p ;
  return Result ;
} 
#ifdef STAT
void 
zrestoretrace ( halfword p , strnumber s ) 
{
  restoretrace_regmem 
  begindiagnostic () ;
  printchar ( 123 ) ;
  print ( s ) ;
  printchar ( 32 ) ;
  showeqtb ( p ) ;
  printchar ( 125 ) ;
  enddiagnostic ( false ) ;
} 
#endif /* STAT */
void 
zprintgroup ( boolean e ) 
{
  /* 10 */ printgroup_regmem 
  switch ( curgroup ) 
  {case 0 : 
    {
      print ( 1962 ) ;
      return ;
    } 
    break ;
  case 1 : 
  case 14 : 
    {
      if ( curgroup == 14 ) 
      print ( 1963 ) ;
      print ( 1964 ) ;
    } 
    break ;
  case 2 : 
  case 3 : 
    {
      if ( curgroup == 3 ) 
      print ( 1965 ) ;
      print ( 1466 ) ;
    } 
    break ;
  case 4 : 
    print ( 1375 ) ;
    break ;
  case 5 : 
    print ( 1465 ) ;
    break ;
  case 6 : 
  case 7 : 
    {
      if ( curgroup == 7 ) 
      print ( 1966 ) ;
      print ( 1967 ) ;
    } 
    break ;
  case 8 : 
    print ( 414 ) ;
    break ;
  case 10 : 
    print ( 1968 ) ;
    break ;
  case 11 : 
    print ( 337 ) ;
    break ;
  case 12 : 
    print ( 614 ) ;
    break ;
  case 9 : 
  case 13 : 
  case 15 : 
  case 16 : 
    {
      print ( 351 ) ;
      if ( curgroup == 13 ) 
      print ( 1969 ) ;
      else if ( curgroup == 15 ) 
      print ( 1970 ) ;
      else if ( curgroup == 16 ) 
      print ( 1971 ) ;
    } 
    break ;
  } 
  print ( 1972 ) ;
  printint ( curlevel ) ;
  printchar ( 41 ) ;
  if ( savestack [saveptr - 1 ].cint != 0 ) 
  {
    if ( e ) 
    print ( 380 ) ;
    else print ( 1973 ) ;
    printint ( savestack [saveptr - 1 ].cint ) ;
  } 
} 
#ifdef STAT
void 
zgrouptrace ( boolean e ) 
{
  grouptrace_regmem 
  begindiagnostic () ;
  printchar ( 123 ) ;
  if ( e ) 
  print ( 1974 ) ;
  else print ( 1975 ) ;
  printgroup ( e ) ;
  printchar ( 125 ) ;
  enddiagnostic ( false ) ;
} 
#endif /* STAT */
boolean 
pseudoinput ( void ) 
{
  register boolean Result; pseudoinput_regmem 
  halfword p  ;
  integer sz  ;
  fourquarters w  ;
  halfword r  ;
  last = first ;
  p = mem [pseudofiles ].hh .v.LH ;
  if ( p == -268435455L ) 
  Result = false ;
  else {
      
    mem [pseudofiles ].hh .v.LH = mem [p ].hh .v.RH ;
    sz = mem [p ].hh .v.LH ;
    if ( 4 * sz - 3 >= bufsize - last ) 
    {
      curinput .locfield = first ;
      curinput .limitfield = last - 1 ;
      overflow ( 258 , bufsize ) ;
    } 
    last = first ;
    {register integer for_end; r = p + 1 ;for_end = p + sz - 1 ; if ( r <= 
    for_end) do 
      {
	w = mem [r ].qqqq ;
	buffer [last ]= w .b0 ;
	buffer [last + 1 ]= w .b1 ;
	buffer [last + 2 ]= w .b2 ;
	buffer [last + 3 ]= w .b3 ;
	last = last + 4 ;
      } 
    while ( r++ < for_end ) ;} 
    if ( last >= maxbufstack ) 
    maxbufstack = last + 1 ;
    while ( ( last > first ) && ( buffer [last - 1 ]== 32 ) ) decr ( last ) 
    ;
    freenode ( p , sz ) ;
    Result = true ;
  } 
  return Result ;
} 
void 
pseudoclose ( void ) 
{
  pseudoclose_regmem 
  halfword p, q  ;
  p = mem [pseudofiles ].hh .v.RH ;
  q = mem [pseudofiles ].hh .v.LH ;
  {
    mem [pseudofiles ].hh .v.RH = avail ;
    avail = pseudofiles ;
	;
#ifdef STAT
    decr ( dynused ) ;
#endif /* STAT */
  } 
  pseudofiles = p ;
  while ( q != -268435455L ) {
      
    p = q ;
    q = mem [p ].hh .v.RH ;
    freenode ( p , mem [p ].hh .v.LH ) ;
  } 
} 
void 
groupwarning ( void ) 
{
  groupwarning_regmem 
  integer i  ;
  boolean w  ;
  baseptr = inputptr ;
  inputstack [baseptr ]= curinput ;
  i = inopen ;
  w = false ;
  while ( ( grpstack [i ]== curboundary ) && ( i > 0 ) ) {
      
    if ( eqtb [29369 ].cint > 0 ) 
    {
      while ( ( inputstack [baseptr ].statefield == 0 ) || ( inputstack [
      baseptr ].indexfield > i ) ) decr ( baseptr ) ;
      if ( inputstack [baseptr ].namefield > 17 ) 
      w = true ;
    } 
    grpstack [i ]= savestack [saveptr ].hh .v.RH ;
    decr ( i ) ;
  } 
  if ( w ) 
  {
    printnl ( 2024 ) ;
    printgroup ( true ) ;
    print ( 2025 ) ;
    println () ;
    if ( eqtb [29369 ].cint > 1 ) 
    showcontext () ;
    if ( history == 0 ) 
    history = 1 ;
  } 
} 
void 
ifwarning ( void ) 
{
  ifwarning_regmem 
  integer i  ;
  boolean w  ;
  baseptr = inputptr ;
  inputstack [baseptr ]= curinput ;
  i = inopen ;
  w = false ;
  while ( ifstack [i ]== condptr ) {
      
    if ( eqtb [29369 ].cint > 0 ) 
    {
      while ( ( inputstack [baseptr ].statefield == 0 ) || ( inputstack [
      baseptr ].indexfield > i ) ) decr ( baseptr ) ;
      if ( inputstack [baseptr ].namefield > 17 ) 
      w = true ;
    } 
    ifstack [i ]= mem [condptr ].hh .v.RH ;
    decr ( i ) ;
  } 
  if ( w ) 
  {
    printnl ( 2024 ) ;
    printcmdchr ( 107 , curif ) ;
    if ( ifline != 0 ) 
    {
      print ( 1994 ) ;
      printint ( ifline ) ;
    } 
    print ( 2025 ) ;
    println () ;
    if ( eqtb [29369 ].cint > 1 ) 
    showcontext () ;
    if ( history == 0 ) 
    history = 1 ;
  } 
} 
void 
filewarning ( void ) 
{
  filewarning_regmem 
  halfword p  ;
  quarterword l  ;
  quarterword c  ;
  integer i  ;
  p = saveptr ;
  l = curlevel ;
  c = curgroup ;
  saveptr = curboundary ;
  while ( grpstack [inopen ]!= saveptr ) {
      
    decr ( curlevel ) ;
    printnl ( 2026 ) ;
    printgroup ( true ) ;
    print ( 2027 ) ;
    curgroup = savestack [saveptr ].hh.b1 ;
    saveptr = savestack [saveptr ].hh .v.RH ;
  } 
  saveptr = p ;
  curlevel = l ;
  curgroup = c ;
  p = condptr ;
  l = iflimit ;
  c = curif ;
  i = ifline ;
  while ( ifstack [inopen ]!= condptr ) {
      
    printnl ( 2026 ) ;
    printcmdchr ( 107 , curif ) ;
    if ( iflimit == 2 ) 
    printesc ( 926 ) ;
    if ( ifline != 0 ) 
    {
      print ( 1994 ) ;
      printint ( ifline ) ;
    } 
    print ( 2027 ) ;
    ifline = mem [condptr + 1 ].cint ;
    curif = mem [condptr ].hh.b1 ;
    iflimit = mem [condptr ].hh.b0 ;
    condptr = mem [condptr ].hh .v.RH ;
  } 
  condptr = p ;
  iflimit = l ;
  curif = c ;
  ifline = i ;
  println () ;
  if ( eqtb [29369 ].cint > 1 ) 
  showcontext () ;
  if ( history == 0 ) 
  history = 1 ;
} 
void 
zdeletesaref ( halfword q ) 
{
  /* 10 */ deletesaref_regmem 
  halfword p  ;
  smallnumber i  ;
  smallnumber s  ;
  decr ( mem [q + 1 ].hh .v.LH ) ;
  if ( mem [q + 1 ].hh .v.LH != -268435455L ) 
  return ;
  if ( mem [q ].hh.b0 < 32 ) {
      
    if ( mem [q + 2 ].cint == 0 ) 
    s = 3 ;
    else return ;
  } 
  else {
      
    if ( mem [q ].hh.b0 < 64 ) {
	
      if ( mem [q + 1 ].hh .v.RH == membot ) 
      deleteglueref ( membot ) ;
      else return ;
    } 
    else if ( mem [q + 1 ].hh .v.RH != -268435455L ) 
    return ;
    s = 2 ;
  } 
  do {
      i = mem [q ].hh.b0 % 16 ;
    p = q ;
    q = mem [p ].hh .v.RH ;
    freenode ( p , s ) ;
    if ( q == -268435455L ) 
    {
      saroot [i ]= -268435455L ;
      return ;
    } 
    {
      if ( odd ( i ) ) 
      mem [q + ( i / 2 ) + 1 ].hh .v.RH = -268435455L ;
      else mem [q + ( i / 2 ) + 1 ].hh .v.LH = -268435455L ;
      decr ( mem [q ].hh.b1 ) ;
    } 
    s = 9 ;
  } while ( ! ( mem [q ].hh.b1 > 0 ) ) ;
} 
#ifdef STAT
void 
zshowsa ( halfword p , strnumber s ) 
{
  showsa_regmem 
  smallnumber t  ;
  begindiagnostic () ;
  printchar ( 123 ) ;
  print ( s ) ;
  printchar ( 32 ) ;
  if ( p == -268435455L ) 
  printchar ( 63 ) ;
  else {
      
    t = ( mem [p ].hh.b0 / 16 ) ;
    if ( t < 4 ) 
    printcmdchr ( 89 , p ) ;
    else if ( t == 4 ) 
    {
      printesc ( 429 ) ;
      printsanum ( p ) ;
    } 
    else if ( t == 5 ) 
    printcmdchr ( 71 , p ) ;
    else printchar ( 63 ) ;
    printchar ( 61 ) ;
    if ( t == 0 ) 
    printint ( mem [p + 2 ].cint ) ;
    else if ( t == 1 ) 
    {
      printscaled ( mem [p + 2 ].cint ) ;
      print ( 312 ) ;
    } 
    else {
	
      p = mem [p + 1 ].hh .v.RH ;
      if ( t == 2 ) 
      printspec ( p , 312 ) ;
      else if ( t == 3 ) 
      printspec ( p , 344 ) ;
      else if ( t == 4 ) {
	  
	if ( p == -268435455L ) 
	print ( 430 ) ;
	else {
	    
	  depththreshold = 0 ;
	  breadthmax = 1 ;
	  shownodelist ( p ) ;
	} 
      } 
      else if ( t == 5 ) 
      {
	if ( p != -268435455L ) 
	showtokenlist ( mem [p ].hh .v.RH , -268435455L , 32 ) ;
      } 
      else printchar ( 63 ) ;
    } 
  } 
  printchar ( 125 ) ;
  enddiagnostic ( false ) ;
} 
#endif /* STAT */
void 
zsasave ( halfword p ) 
{
  sasave_regmem 
  halfword q  ;
  quarterword i  ;
  if ( curlevel != salevel ) 
  {
    if ( saveptr > maxsavestack ) 
    {
      maxsavestack = saveptr ;
      if ( maxsavestack > savesize - 7 ) 
      overflow ( 616 , savesize ) ;
    } 
    savestack [saveptr ].hh.b0 = 4 ;
    savestack [saveptr ].hh.b1 = salevel ;
    savestack [saveptr ].hh .v.RH = sachain ;
    incr ( saveptr ) ;
    sachain = -268435455L ;
    salevel = curlevel ;
  } 
  i = mem [p ].hh.b0 ;
  if ( i < 32 ) 
  {
    if ( mem [p + 2 ].cint == 0 ) 
    {
      q = getnode ( 2 ) ;
      i = 96 ;
    } 
    else {
	
      q = getnode ( 3 ) ;
      mem [q + 2 ].cint = mem [p + 2 ].cint ;
    } 
    mem [q + 1 ].hh .v.RH = -268435455L ;
  } 
  else {
      
    q = getnode ( 2 ) ;
    mem [q + 1 ].hh .v.RH = mem [p + 1 ].hh .v.RH ;
  } 
  mem [q + 1 ].hh .v.LH = p ;
  mem [q ].hh.b0 = i ;
  mem [q ].hh.b1 = mem [p ].hh.b1 ;
  mem [q ].hh .v.RH = sachain ;
  sachain = q ;
  incr ( mem [p + 1 ].hh .v.LH ) ;
} 
void 
zsadestroy ( halfword p ) 
{
  sadestroy_regmem 
  if ( mem [p ].hh.b0 < 64 ) 
  deleteglueref ( mem [p + 1 ].hh .v.RH ) ;
  else if ( mem [p + 1 ].hh .v.RH != -268435455L ) {
      
    if ( mem [p ].hh.b0 < 80 ) 
    flushnodelist ( mem [p + 1 ].hh .v.RH ) ;
    else deletetokenref ( mem [p + 1 ].hh .v.RH ) ;
  } 
} 
void 
zsadef ( halfword p , halfword e ) 
{
  sadef_regmem 
  incr ( mem [p + 1 ].hh .v.LH ) ;
  if ( mem [p + 1 ].hh .v.RH == e ) 
  {
	;
#ifdef STAT
    if ( eqtb [29365 ].cint > 0 ) 
    showsa ( p , 618 ) ;
#endif /* STAT */
    sadestroy ( p ) ;
  } 
  else {
      
	;
#ifdef STAT
    if ( eqtb [29365 ].cint > 0 ) 
    showsa ( p , 619 ) ;
#endif /* STAT */
    if ( mem [p ].hh.b1 == curlevel ) 
    sadestroy ( p ) ;
    else sasave ( p ) ;
    mem [p ].hh.b1 = curlevel ;
    mem [p + 1 ].hh .v.RH = e ;
	;
#ifdef STAT
    if ( eqtb [29365 ].cint > 0 ) 
    showsa ( p , 620 ) ;
#endif /* STAT */
  } 
  deletesaref ( p ) ;
} 
void 
zsawdef ( halfword p , integer w ) 
{
  sawdef_regmem 
  incr ( mem [p + 1 ].hh .v.LH ) ;
  if ( mem [p + 2 ].cint == w ) 
  {
	;
#ifdef STAT
    if ( eqtb [29365 ].cint > 0 ) 
    showsa ( p , 618 ) ;
#endif /* STAT */
  } 
  else {
      
	;
#ifdef STAT
    if ( eqtb [29365 ].cint > 0 ) 
    showsa ( p , 619 ) ;
#endif /* STAT */
    if ( mem [p ].hh.b1 != curlevel ) 
    sasave ( p ) ;
    mem [p ].hh.b1 = curlevel ;
    mem [p + 2 ].cint = w ;
	;
#ifdef STAT
    if ( eqtb [29365 ].cint > 0 ) 
    showsa ( p , 620 ) ;
#endif /* STAT */
  } 
  deletesaref ( p ) ;
} 
void 
zgsadef ( halfword p , halfword e ) 
{
  gsadef_regmem 
  incr ( mem [p + 1 ].hh .v.LH ) ;
	;
#ifdef STAT
  if ( eqtb [29365 ].cint > 0 ) 
  showsa ( p , 621 ) ;
#endif /* STAT */
  sadestroy ( p ) ;
  mem [p ].hh.b1 = 1 ;
  mem [p + 1 ].hh .v.RH = e ;
	;
#ifdef STAT
  if ( eqtb [29365 ].cint > 0 ) 
  showsa ( p , 620 ) ;
#endif /* STAT */
  deletesaref ( p ) ;
} 
void 
zgsawdef ( halfword p , integer w ) 
{
  gsawdef_regmem 
  incr ( mem [p + 1 ].hh .v.LH ) ;
	;
#ifdef STAT
  if ( eqtb [29365 ].cint > 0 ) 
  showsa ( p , 621 ) ;
#endif /* STAT */
  mem [p ].hh.b1 = 1 ;
  mem [p + 2 ].cint = w ;
	;
#ifdef STAT
  if ( eqtb [29365 ].cint > 0 ) 
  showsa ( p , 620 ) ;
#endif /* STAT */
  deletesaref ( p ) ;
} 
void 
sarestore ( void ) 
{
  sarestore_regmem 
  halfword p  ;
  do {
      p = mem [sachain + 1 ].hh .v.LH ;
    if ( mem [p ].hh.b1 == 1 ) 
    {
      if ( mem [p ].hh.b0 >= 32 ) 
      sadestroy ( sachain ) ;
	;
#ifdef STAT
      if ( eqtb [29311 ].cint > 0 ) 
      showsa ( p , 623 ) ;
#endif /* STAT */
    } 
    else {
	
      if ( mem [p ].hh.b0 < 32 ) {
	  
	if ( mem [sachain ].hh.b0 < 32 ) 
	mem [p + 2 ].cint = mem [sachain + 2 ].cint ;
	else mem [p + 2 ].cint = 0 ;
      } 
      else {
	  
	sadestroy ( p ) ;
	mem [p + 1 ].hh .v.RH = mem [sachain + 1 ].hh .v.RH ;
      } 
      mem [p ].hh.b1 = mem [sachain ].hh.b1 ;
	;
#ifdef STAT
      if ( eqtb [29311 ].cint > 0 ) 
      showsa ( p , 624 ) ;
#endif /* STAT */
    } 
    deletesaref ( p ) ;
    p = sachain ;
    sachain = mem [p ].hh .v.RH ;
    if ( mem [p ].hh.b0 < 32 ) 
    freenode ( p , 3 ) ;
    else freenode ( p , 2 ) ;
  } while ( ! ( sachain == -268435455L ) ) ;
} 
void 
znewsavelevel ( groupcode c ) 
{
  newsavelevel_regmem 
  if ( saveptr > maxsavestack ) 
  {
    maxsavestack = saveptr ;
    if ( maxsavestack > savesize - 7 ) 
    overflow ( 616 , savesize ) ;
  } 
  if ( ( eTeXmode == 1 ) ) 
  {
    savestack [saveptr + 0 ].cint = line ;
    incr ( saveptr ) ;
  } 
  savestack [saveptr ].hh.b0 = 3 ;
  savestack [saveptr ].hh.b1 = curgroup ;
  savestack [saveptr ].hh .v.RH = curboundary ;
  if ( curlevel == 255 ) 
  overflow ( 617 , 255 ) ;
  curboundary = saveptr ;
  curgroup = c ;
	;
#ifdef STAT
  if ( eqtb [29366 ].cint > 0 ) 
  grouptrace ( false ) ;
#endif /* STAT */
  incr ( curlevel ) ;
  incr ( saveptr ) ;
} 
void 
zeqdestroy ( memoryword w ) 
{
  eqdestroy_regmem 
  halfword q  ;
  switch ( w .hh.b0 ) 
  {case 113 : 
  case 114 : 
  case 115 : 
  case 116 : 
    deletetokenref ( w .hh .v.RH ) ;
    break ;
  case 119 : 
    deleteglueref ( w .hh .v.RH ) ;
    break ;
  case 120 : 
    {
      q = w .hh .v.RH ;
      if ( q != -268435455L ) 
      freenode ( q , mem [q ].hh .v.LH + mem [q ].hh .v.LH + 1 ) ;
    } 
    break ;
  case 121 : 
    flushnodelist ( w .hh .v.RH ) ;
    break ;
  case 71 : 
  case 89 : 
    if ( ( w .hh .v.RH < membot ) || ( w .hh .v.RH > membot + 19 ) ) 
    deletesaref ( w .hh .v.RH ) ;
    break ;
    default: 
    ;
    break ;
  } 
} 
void 
zeqsave ( halfword p , quarterword l ) 
{
  eqsave_regmem 
  if ( saveptr > maxsavestack ) 
  {
    maxsavestack = saveptr ;
    if ( maxsavestack > savesize - 7 ) 
    overflow ( 616 , savesize ) ;
  } 
  if ( l == 0 ) 
  savestack [saveptr ].hh.b0 = 1 ;
  else {
      
    savestack [saveptr ]= eqtb [p ];
    incr ( saveptr ) ;
    savestack [saveptr ].hh.b0 = 0 ;
  } 
  savestack [saveptr ].hh.b1 = l ;
  savestack [saveptr ].hh .v.RH = p ;
  incr ( saveptr ) ;
} 
void 
zeqdefine ( halfword p , quarterword t , halfword e ) 
{
  /* 10 */ eqdefine_regmem 
  if ( ( eTeXmode == 1 ) && ( eqtb [p ].hh.b0 == t ) && ( eqtb [p ].hh 
  .v.RH == e ) ) 
  {
	;
#ifdef STAT
    if ( eqtb [29365 ].cint > 0 ) 
    restoretrace ( p , 618 ) ;
#endif /* STAT */
    eqdestroy ( eqtb [p ]) ;
    return ;
  } 
	;
#ifdef STAT
  if ( eqtb [29365 ].cint > 0 ) 
  restoretrace ( p , 619 ) ;
#endif /* STAT */
  if ( eqtb [p ].hh.b1 == curlevel ) 
  eqdestroy ( eqtb [p ]) ;
  else if ( curlevel > 1 ) 
  eqsave ( p , eqtb [p ].hh.b1 ) ;
  eqtb [p ].hh.b1 = curlevel ;
  eqtb [p ].hh.b0 = t ;
  eqtb [p ].hh .v.RH = e ;
	;
#ifdef STAT
  if ( eqtb [29365 ].cint > 0 ) 
  restoretrace ( p , 620 ) ;
#endif /* STAT */
} 
void 
zeqworddefine ( halfword p , integer w ) 
{
  /* 10 */ eqworddefine_regmem 
  if ( ( eTeXmode == 1 ) && ( eqtb [p ].cint == w ) ) 
  {
	;
#ifdef STAT
    if ( eqtb [29365 ].cint > 0 ) 
    restoretrace ( p , 618 ) ;
#endif /* STAT */
    return ;
  } 
	;
#ifdef STAT
  if ( eqtb [29365 ].cint > 0 ) 
  restoretrace ( p , 619 ) ;
#endif /* STAT */
  if ( xeqlevel [p ]!= curlevel ) 
  {
    eqsave ( p , xeqlevel [p ]) ;
    xeqlevel [p ]= curlevel ;
  } 
  eqtb [p ].cint = w ;
	;
#ifdef STAT
  if ( eqtb [29365 ].cint > 0 ) 
  restoretrace ( p , 620 ) ;
#endif /* STAT */
} 
void 
zgeqdefine ( halfword p , quarterword t , halfword e ) 
{
  geqdefine_regmem 
	;
#ifdef STAT
  if ( eqtb [29365 ].cint > 0 ) 
  restoretrace ( p , 621 ) ;
#endif /* STAT */
  {
    eqdestroy ( eqtb [p ]) ;
    eqtb [p ].hh.b1 = 1 ;
    eqtb [p ].hh.b0 = t ;
    eqtb [p ].hh .v.RH = e ;
  } 
	;
#ifdef STAT
  if ( eqtb [29365 ].cint > 0 ) 
  restoretrace ( p , 620 ) ;
#endif /* STAT */
} 
void 
zgeqworddefine ( halfword p , integer w ) 
{
  geqworddefine_regmem 
	;
#ifdef STAT
  if ( eqtb [29365 ].cint > 0 ) 
  restoretrace ( p , 621 ) ;
#endif /* STAT */
  {
    eqtb [p ].cint = w ;
    xeqlevel [p ]= 1 ;
  } 
	;
#ifdef STAT
  if ( eqtb [29365 ].cint > 0 ) 
  restoretrace ( p , 620 ) ;
#endif /* STAT */
} 
void 
zsaveforafter ( halfword t ) 
{
  saveforafter_regmem 
  if ( curlevel > 1 ) 
  {
    if ( saveptr > maxsavestack ) 
    {
      maxsavestack = saveptr ;
      if ( maxsavestack > savesize - 7 ) 
      overflow ( 616 , savesize ) ;
    } 
    savestack [saveptr ].hh.b0 = 2 ;
    savestack [saveptr ].hh.b1 = 0 ;
    savestack [saveptr ].hh .v.RH = t ;
    incr ( saveptr ) ;
  } 
} 
void 
unsave ( void ) 
{
  /* 30 */ unsave_regmem 
  halfword p  ;
  quarterword l  ;
  halfword t  ;
  boolean a  ;
  a = false ;
  if ( curlevel > 1 ) 
  {
    decr ( curlevel ) ;
    while ( true ) {
	
      decr ( saveptr ) ;
      if ( savestack [saveptr ].hh.b0 == 3 ) 
      goto lab30 ;
      p = savestack [saveptr ].hh .v.RH ;
      if ( savestack [saveptr ].hh.b0 == 2 ) 
      {
	t = curtok ;
	curtok = p ;
	if ( a ) 
	{
	  p = getavail () ;
	  mem [p ].hh .v.LH = curtok ;
	  mem [p ].hh .v.RH = curinput .locfield ;
	  curinput .locfield = p ;
	  curinput .startfield = p ;
	  if ( curtok < 768 ) {
	      
	    if ( curtok < 512 ) 
	    decr ( alignstate ) ;
	    else incr ( alignstate ) ;
	  } 
	} 
	else {
	    
	  backinput () ;
	  a = ( eTeXmode == 1 ) ;
	} 
	curtok = t ;
      } 
      else if ( savestack [saveptr ].hh.b0 == 4 ) 
      {
	sarestore () ;
	sachain = p ;
	salevel = savestack [saveptr ].hh.b1 ;
      } 
      else {
	  
	if ( savestack [saveptr ].hh.b0 == 0 ) 
	{
	  l = savestack [saveptr ].hh.b1 ;
	  decr ( saveptr ) ;
	} 
	else savestack [saveptr ]= eqtb [26627 ];
	if ( ( p < 29274 ) || ( p > 30176 ) ) {
	    
	  if ( eqtb [p ].hh.b1 == 1 ) 
	  {
	    eqdestroy ( savestack [saveptr ]) ;
	;
#ifdef STAT
	    if ( eqtb [29311 ].cint > 0 ) 
	    restoretrace ( p , 623 ) ;
#endif /* STAT */
	  } 
	  else {
	      
	    eqdestroy ( eqtb [p ]) ;
	    eqtb [p ]= savestack [saveptr ];
	;
#ifdef STAT
	    if ( eqtb [29311 ].cint > 0 ) 
	    restoretrace ( p , 624 ) ;
#endif /* STAT */
	  } 
	} 
	else if ( xeqlevel [p ]!= 1 ) 
	{
	  eqtb [p ]= savestack [saveptr ];
	  xeqlevel [p ]= l ;
	;
#ifdef STAT
	  if ( eqtb [29311 ].cint > 0 ) 
	  restoretrace ( p , 624 ) ;
#endif /* STAT */
	} 
	else {
	    
	;
#ifdef STAT
	  if ( eqtb [29311 ].cint > 0 ) 
	  restoretrace ( p , 623 ) ;
#endif /* STAT */
	} 
      } 
    } 
    lab30: 
	;
#ifdef STAT
    if ( eqtb [29366 ].cint > 0 ) 
    grouptrace ( true ) ;
#endif /* STAT */
    if ( grpstack [inopen ]== curboundary ) 
    groupwarning () ;
    curgroup = savestack [saveptr ].hh.b1 ;
    curboundary = savestack [saveptr ].hh .v.RH ;
    if ( ( eTeXmode == 1 ) ) 
    decr ( saveptr ) ;
  } 
  else confusion ( 622 ) ;
} 
void 
preparemag ( void ) 
{
  preparemag_regmem 
  if ( ( magset > 0 ) && ( eqtb [29291 ].cint != magset ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 626 ) ;
    } 
    printint ( eqtb [29291 ].cint ) ;
    print ( 627 ) ;
    printnl ( 628 ) ;
    {
      helpptr = 2 ;
      helpline [1 ]= 629 ;
      helpline [0 ]= 630 ;
    } 
    interror ( magset ) ;
    geqworddefine ( 29291 , magset ) ;
  } 
  if ( ( eqtb [29291 ].cint <= 0 ) || ( eqtb [29291 ].cint > 32768L ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 631 ) ;
    } 
    {
      helpptr = 1 ;
      helpline [0 ]= 632 ;
    } 
    interror ( eqtb [29291 ].cint ) ;
    geqworddefine ( 29291 , 1000 ) ;
  } 
  magset = eqtb [29291 ].cint ;
} 
void 
ztokenshow ( halfword p ) 
{
  tokenshow_regmem 
  if ( p != -268435455L ) 
  showtokenlist ( mem [p ].hh .v.RH , -268435455L , 10000000L ) ;
} 
void 
printmeaning ( void ) 
{
  printmeaning_regmem 
  printcmdchr ( curcmd , curchr ) ;
  if ( curcmd >= 113 ) 
  {
    printchar ( 58 ) ;
    println () ;
    tokenshow ( curchr ) ;
  } 
  else if ( ( curcmd == 112 ) && ( curchr < 5 ) ) 
  {
    printchar ( 58 ) ;
    println () ;
    tokenshow ( curmark [curchr ]) ;
  } 
} 
void 
showcurcmdchr ( void ) 
{
  showcurcmdchr_regmem 
  integer n  ;
  integer l  ;
  halfword p  ;
  begindiagnostic () ;
  printnl ( 123 ) ;
  if ( curlist .modefield != shownmode ) 
  {
    printmode ( curlist .modefield ) ;
    print ( 646 ) ;
    shownmode = curlist .modefield ;
  } 
  printcmdchr ( curcmd , curchr ) ;
  if ( eqtb [29367 ].cint > 0 ) {
      
    if ( curcmd >= 107 ) {
	
      if ( curcmd <= 108 ) 
      {
	print ( 646 ) ;
	if ( curcmd == 108 ) 
	{
	  printcmdchr ( 107 , curif ) ;
	  printchar ( 32 ) ;
	  n = 0 ;
	  l = ifline ;
	} 
	else {
	    
	  n = 1 ;
	  l = line ;
	} 
	p = condptr ;
	while ( p != -268435455L ) {
	    
	  incr ( n ) ;
	  p = mem [p ].hh .v.RH ;
	} 
	print ( 647 ) ;
	printint ( n ) ;
	printchar ( 41 ) ;
	if ( l != 0 ) 
	{
	  print ( 1994 ) ;
	  printint ( l ) ;
	} 
      } 
    } 
  } 
  printchar ( 125 ) ;
  enddiagnostic ( false ) ;
} 
void 
showcontext ( void ) 
{
  /* 30 */ showcontext_regmem 
  unsigned char oldsetting  ;
  integer nn  ;
  boolean bottomline  ;
  integer i  ;
  integer j  ;
  integer l  ;
  integer m  ;
  integer n  ;
  integer p  ;
  integer q  ;
  baseptr = inputptr ;
  inputstack [baseptr ]= curinput ;
  nn = -1 ;
  bottomline = false ;
  while ( true ) {
      
    curinput = inputstack [baseptr ];
    if ( ( curinput .statefield != 0 ) ) {
	
      if ( ( curinput .namefield > 19 ) || ( baseptr == 0 ) ) 
      bottomline = true ;
    } 
    if ( ( baseptr == inputptr ) || bottomline || ( nn < eqtb [29328 ].cint 
    ) ) 
    {
      if ( ( baseptr == inputptr ) || ( curinput .statefield != 0 ) || ( 
      curinput .indexfield != 3 ) || ( curinput .locfield != -268435455L ) ) 
      {
	tally = 0 ;
	oldsetting = selector ;
	if ( curinput .statefield != 0 ) 
	{
	  if ( curinput .namefield <= 17 ) {
	      
	    if ( ( curinput .namefield == 0 ) ) {
		
	      if ( baseptr == 0 ) 
	      printnl ( 652 ) ;
	      else printnl ( 653 ) ;
	    } 
	    else {
		
	      printnl ( 654 ) ;
	      if ( curinput .namefield == 17 ) 
	      printchar ( 42 ) ;
	      else printint ( curinput .namefield - 1 ) ;
	      printchar ( 62 ) ;
	    } 
	  } 
	  else if ( curinput .indexfield != inopen ) 
	  {
	    printnl ( 655 ) ;
	    printint ( linestack [curinput .indexfield + 1 ]) ;
	  } 
	  else {
	      
	    printnl ( 655 ) ;
	    printint ( line ) ;
	  } 
	  printchar ( 32 ) ;
	  {
	    l = tally ;
	    tally = 0 ;
	    selector = 20 ;
	    trickcount = 1000000L ;
	  } 
	  if ( buffer [curinput .limitfield ]== eqtb [29322 ].cint ) 
	  j = curinput .limitfield ;
	  else j = curinput .limitfield + 1 ;
	  if ( j > 0 ) 
	  {register integer for_end; i = curinput .startfield ;for_end = j - 
	  1 ; if ( i <= for_end) do 
	    {
	      if ( i == curinput .locfield ) 
	      {
		firstcount = tally ;
		trickcount = tally + 1 + errorline - halferrorline ;
		if ( trickcount < errorline ) 
		trickcount = errorline ;
	      } 
	      print ( buffer [i ]) ;
	    } 
	  while ( i++ < for_end ) ;} 
	} 
	else {
	    
	  switch ( curinput .indexfield ) 
	  {case 0 : 
	    printnl ( 656 ) ;
	    break ;
	  case 1 : 
	  case 2 : 
	    printnl ( 657 ) ;
	    break ;
	  case 3 : 
	    if ( curinput .locfield == -268435455L ) 
	    printnl ( 658 ) ;
	    else printnl ( 659 ) ;
	    break ;
	  case 4 : 
	    printnl ( 660 ) ;
	    break ;
	  case 5 : 
	    {
	      println () ;
	      printcs ( curinput .namefield ) ;
	    } 
	    break ;
	  case 6 : 
	    printnl ( 661 ) ;
	    break ;
	  case 7 : 
	    printnl ( 662 ) ;
	    break ;
	  case 8 : 
	    printnl ( 663 ) ;
	    break ;
	  case 9 : 
	    printnl ( 664 ) ;
	    break ;
	  case 10 : 
	    printnl ( 665 ) ;
	    break ;
	  case 11 : 
	    printnl ( 666 ) ;
	    break ;
	  case 12 : 
	    printnl ( 667 ) ;
	    break ;
	  case 13 : 
	    printnl ( 668 ) ;
	    break ;
	  case 14 : 
	    printnl ( 669 ) ;
	    break ;
	  case 19 : 
	    printnl ( 670 ) ;
	    break ;
	  case 20 : 
	    printnl ( 671 ) ;
	    break ;
	    default: 
	    printnl ( 63 ) ;
	    break ;
	  } 
	  {
	    l = tally ;
	    tally = 0 ;
	    selector = 20 ;
	    trickcount = 1000000L ;
	  } 
	  if ( curinput .indexfield < 5 ) 
	  showtokenlist ( curinput .startfield , curinput .locfield , 100000L 
	  ) ;
	  else showtokenlist ( mem [curinput .startfield ].hh .v.RH , 
	  curinput .locfield , 100000L ) ;
	} 
	selector = oldsetting ;
	if ( trickcount == 1000000L ) 
	{
	  firstcount = tally ;
	  trickcount = tally + 1 + errorline - halferrorline ;
	  if ( trickcount < errorline ) 
	  trickcount = errorline ;
	} 
	if ( tally < trickcount ) 
	m = tally - firstcount ;
	else m = trickcount - firstcount ;
	if ( l + firstcount <= halferrorline ) 
	{
	  p = 0 ;
	  n = l + firstcount ;
	} 
	else {
	    
	  print ( 277 ) ;
	  p = l + firstcount - halferrorline + 3 ;
	  n = halferrorline ;
	} 
	{register integer for_end; q = p ;for_end = firstcount - 1 ; if ( q 
	<= for_end) do 
	  printchar ( trickbuf [q % errorline ]) ;
	while ( q++ < for_end ) ;} 
	println () ;
	{register integer for_end; q = 1 ;for_end = n ; if ( q <= for_end) 
	do 
	  printchar ( 32 ) ;
	while ( q++ < for_end ) ;} 
	if ( m + n <= errorline ) 
	p = firstcount + m ;
	else p = firstcount + ( errorline - n - 3 ) ;
	{register integer for_end; q = firstcount ;for_end = p - 1 ; if ( q 
	<= for_end) do 
	  printchar ( trickbuf [q % errorline ]) ;
	while ( q++ < for_end ) ;} 
	if ( m + n > errorline ) 
	print ( 277 ) ;
	incr ( nn ) ;
      } 
    } 
    else if ( nn == eqtb [29328 ].cint ) 
    {
      printnl ( 277 ) ;
      incr ( nn ) ;
    } 
    if ( bottomline ) 
    goto lab30 ;
    decr ( baseptr ) ;
  } 
  lab30: curinput = inputstack [inputptr ];
} 
void 
zbegintokenlist ( halfword p , quarterword t ) 
{
  begintokenlist_regmem 
  {
    if ( inputptr > maxinstack ) 
    {
      maxinstack = inputptr ;
      if ( inputptr == stacksize ) 
      overflow ( 672 , stacksize ) ;
    } 
    inputstack [inputptr ]= curinput ;
    incr ( inputptr ) ;
  } 
  curinput .statefield = 0 ;
  curinput .startfield = p ;
  curinput .indexfield = t ;
  if ( t >= 5 ) 
  {
    incr ( mem [p ].hh .v.LH ) ;
    if ( t == 5 ) 
    curinput .limitfield = paramptr ;
    else {
	
      curinput .locfield = mem [p ].hh .v.RH ;
      if ( eqtb [29304 ].cint > 1 ) 
      {
	begindiagnostic () ;
	printnl ( 345 ) ;
	switch ( t ) 
	{case 14 : 
	  printesc ( 359 ) ;
	  break ;
	case 20 : 
	  printesc ( 673 ) ;
	  break ;
	  default: 
	  printcmdchr ( 72 , t + 27153 ) ;
	  break ;
	} 
	print ( 634 ) ;
	tokenshow ( p ) ;
	enddiagnostic ( false ) ;
      } 
    } 
  } 
  else curinput .locfield = p ;
} 
void 
endtokenlist ( void ) 
{
  endtokenlist_regmem 
  if ( curinput .indexfield >= 3 ) 
  {
    if ( curinput .indexfield <= 4 ) 
    flushlist ( curinput .startfield ) ;
    else {
	
      deletetokenref ( curinput .startfield ) ;
      if ( curinput .indexfield == 5 ) 
      while ( paramptr > curinput .limitfield ) {
	  
	decr ( paramptr ) ;
	flushlist ( paramstack [paramptr ]) ;
      } 
    } 
  } 
  else if ( curinput .indexfield == 1 ) {
      
    if ( alignstate > 500000L ) 
    alignstate = 0 ;
    else fatalerror ( 674 ) ;
  } 
  {
    decr ( inputptr ) ;
    curinput = inputstack [inputptr ];
  } 
  {
    if ( interrupt != 0 ) 
    pauseforinstructions () ;
  } 
} 
void 
backinput ( void ) 
{
  backinput_regmem 
  halfword p  ;
  while ( ( curinput .statefield == 0 ) && ( curinput .locfield == -268435455L 
  ) && ( curinput .indexfield != 2 ) ) endtokenlist () ;
  p = getavail () ;
  mem [p ].hh .v.LH = curtok ;
  if ( curtok < 768 ) {
      
    if ( curtok < 512 ) 
    decr ( alignstate ) ;
    else incr ( alignstate ) ;
  } 
  {
    if ( inputptr > maxinstack ) 
    {
      maxinstack = inputptr ;
      if ( inputptr == stacksize ) 
      overflow ( 672 , stacksize ) ;
    } 
    inputstack [inputptr ]= curinput ;
    incr ( inputptr ) ;
  } 
  curinput .statefield = 0 ;
  curinput .startfield = p ;
  curinput .indexfield = 3 ;
  curinput .locfield = p ;
} 
void 
backerror ( void ) 
{
  backerror_regmem 
  OKtointerrupt = false ;
  backinput () ;
  OKtointerrupt = true ;
  error () ;
} 
void 
inserror ( void ) 
{
  inserror_regmem 
  OKtointerrupt = false ;
  backinput () ;
  curinput .indexfield = 4 ;
  OKtointerrupt = true ;
  error () ;
} 
void 
beginfilereading ( void ) 
{
  beginfilereading_regmem 
  if ( inopen == maxinopen ) 
  overflow ( 675 , maxinopen ) ;
  if ( first == bufsize ) 
  overflow ( 258 , bufsize ) ;
  incr ( inopen ) ;
  {
    if ( inputptr > maxinstack ) 
    {
      maxinstack = inputptr ;
      if ( inputptr == stacksize ) 
      overflow ( 672 , stacksize ) ;
    } 
    inputstack [inputptr ]= curinput ;
    incr ( inputptr ) ;
  } 
  curinput .indexfield = inopen ;
  sourcefilenamestack [curinput .indexfield ]= 0 ;
  fullsourcefilenamestack [curinput .indexfield ]= 0 ;
  eofseen [curinput .indexfield ]= false ;
  grpstack [curinput .indexfield ]= curboundary ;
  ifstack [curinput .indexfield ]= condptr ;
  linestack [curinput .indexfield ]= line ;
  curinput .startfield = first ;
  curinput .statefield = 1 ;
  curinput .namefield = 0 ;
} 
void 
endfilereading ( void ) 
{
  endfilereading_regmem 
  first = curinput .startfield ;
  line = linestack [curinput .indexfield ];
  if ( ( curinput .namefield == 18 ) || ( curinput .namefield == 19 ) ) 
  pseudoclose () ;
  else if ( curinput .namefield > 17 ) 
  aclose ( inputfile [curinput .indexfield ]) ;
  {
    decr ( inputptr ) ;
    curinput = inputstack [inputptr ];
  } 
  decr ( inopen ) ;
} 
void 
clearforerrorprompt ( void ) 
{
  clearforerrorprompt_regmem 
  while ( ( curinput .statefield != 0 ) && ( curinput .namefield == 0 ) && ( 
  inputptr > 0 ) && ( curinput .locfield > curinput .limitfield ) ) 
  endfilereading () ;
  println () ;
} 
void 
checkoutervalidity ( void ) 
{
  checkoutervalidity_regmem 
  halfword p  ;
  halfword q  ;
  if ( scannerstatus != 0 ) 
  {
    deletionsallowed = false ;
    if ( curcs != 0 ) 
    {
      if ( ( curinput .statefield == 0 ) || ( curinput .namefield < 1 ) || ( 
      curinput .namefield > 17 ) ) 
      {
	p = getavail () ;
	mem [p ].hh .v.LH = 4095 + curcs ;
	begintokenlist ( p , 3 ) ;
      } 
      curcmd = 10 ;
      curchr = 32 ;
    } 
    if ( scannerstatus > 1 ) 
    {
      runaway () ;
      if ( curcs == 0 ) 
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 683 ) ;
      } 
      else {
	  
	curcs = 0 ;
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 684 ) ;
	} 
      } 
      p = getavail () ;
      switch ( scannerstatus ) 
      {case 2 : 
	{
	  print ( 690 ) ;
	  mem [p ].hh .v.LH = 637 ;
	} 
	break ;
      case 3 : 
	{
	  print ( 691 ) ;
	  mem [p ].hh .v.LH = partoken ;
	  longstate = 115 ;
	} 
	break ;
      case 4 : 
	{
	  print ( 692 ) ;
	  mem [p ].hh .v.LH = 637 ;
	  q = p ;
	  p = getavail () ;
	  mem [p ].hh .v.RH = q ;
	  mem [p ].hh .v.LH = 19610 ;
	  alignstate = -1000000L ;
	} 
	break ;
      case 5 : 
	{
	  print ( 693 ) ;
	  mem [p ].hh .v.LH = 637 ;
	} 
	break ;
      } 
      begintokenlist ( p , 4 ) ;
      print ( 685 ) ;
      sprintcs ( warningindex ) ;
      {
	helpptr = 4 ;
	helpline [3 ]= 686 ;
	helpline [2 ]= 687 ;
	helpline [1 ]= 688 ;
	helpline [0 ]= 689 ;
      } 
      error () ;
    } 
    else {
	
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 677 ) ;
      } 
      printcmdchr ( 107 , curif ) ;
      print ( 678 ) ;
      printint ( skipline ) ;
      {
	helpptr = 3 ;
	helpline [2 ]= 679 ;
	helpline [1 ]= 680 ;
	helpline [0 ]= 681 ;
      } 
      if ( curcs != 0 ) 
      curcs = 0 ;
      else helpline [2 ]= 682 ;
      curtok = 19613 ;
      inserror () ;
    } 
    deletionsallowed = true ;
  } 
} 
void 
getnext ( void ) 
{
  /* 20 25 21 26 40 10 */ getnext_regmem 
  integer k  ;
  halfword t  ;
  unsigned char cat  ;
  ASCIIcode c, cc  ;
  unsigned char d  ;
  lab20: curcs = 0 ;
  if ( curinput .statefield != 0 ) 
  {
    lab25: if ( curinput .locfield <= curinput .limitfield ) 
    {
      curchr = buffer [curinput .locfield ];
      incr ( curinput .locfield ) ;
      lab21: curcmd = eqtb [27738 + curchr ].hh .v.RH ;
      switch ( curinput .statefield + curcmd ) 
      {case 10 : 
      case 26 : 
      case 42 : 
      case 27 : 
      case 43 : 
	goto lab25 ;
	break ;
      case 1 : 
      case 17 : 
      case 33 : 
	{
	  if ( curinput .locfield > curinput .limitfield ) 
	  curcs = 513 ;
	  else {
	      
	    lab26: k = curinput .locfield ;
	    curchr = buffer [k ];
	    cat = eqtb [27738 + curchr ].hh .v.RH ;
	    incr ( k ) ;
	    if ( cat == 11 ) 
	    curinput .statefield = 17 ;
	    else if ( cat == 10 ) 
	    curinput .statefield = 17 ;
	    else curinput .statefield = 1 ;
	    if ( ( cat == 11 ) && ( k <= curinput .limitfield ) ) 
	    {
	      do {
		  curchr = buffer [k ];
		cat = eqtb [27738 + curchr ].hh .v.RH ;
		incr ( k ) ;
	      } while ( ! ( ( cat != 11 ) || ( k > curinput .limitfield ) ) ) 
	      ;
	      {
		if ( buffer [k ]== curchr ) {
		    
		  if ( cat == 7 ) {
		      
		    if ( k < curinput .limitfield ) 
		    {
		      c = buffer [k + 1 ];
		      if ( c < 128 ) 
		      {
			d = 2 ;
			if ( ( ( ( c >= 48 ) && ( c <= 57 ) ) || ( ( c >= 97 ) 
			&& ( c <= 102 ) ) ) ) {
			    
			  if ( k + 2 <= curinput .limitfield ) 
			  {
			    cc = buffer [k + 2 ];
			    if ( ( ( ( cc >= 48 ) && ( cc <= 57 ) ) || ( ( cc 
			    >= 97 ) && ( cc <= 102 ) ) ) ) 
			    incr ( d ) ;
			  } 
			} 
			if ( d > 2 ) 
			{
			  if ( c <= 57 ) 
			  curchr = c - 48 ;
			  else curchr = c - 87 ;
			  if ( cc <= 57 ) 
			  curchr = 16 * curchr + cc - 48 ;
			  else curchr = 16 * curchr + cc - 87 ;
			  buffer [k - 1 ]= curchr ;
			} 
			else if ( c < 64 ) 
			buffer [k - 1 ]= c + 64 ;
			else buffer [k - 1 ]= c - 64 ;
			curinput .limitfield = curinput .limitfield - d ;
			first = first - d ;
			while ( k <= curinput .limitfield ) {
			    
			  buffer [k ]= buffer [k + d ];
			  incr ( k ) ;
			} 
			goto lab26 ;
		      } 
		    } 
		  } 
		} 
	      } 
	      if ( cat != 11 ) 
	      decr ( k ) ;
	      if ( k > curinput .locfield + 1 ) 
	      {
		curcs = idlookup ( curinput .locfield , k - curinput .locfield 
		) ;
		curinput .locfield = k ;
		goto lab40 ;
	      } 
	    } 
	    else {
		
	      if ( buffer [k ]== curchr ) {
		  
		if ( cat == 7 ) {
		    
		  if ( k < curinput .limitfield ) 
		  {
		    c = buffer [k + 1 ];
		    if ( c < 128 ) 
		    {
		      d = 2 ;
		      if ( ( ( ( c >= 48 ) && ( c <= 57 ) ) || ( ( c >= 97 ) 
		      && ( c <= 102 ) ) ) ) {
			  
			if ( k + 2 <= curinput .limitfield ) 
			{
			  cc = buffer [k + 2 ];
			  if ( ( ( ( cc >= 48 ) && ( cc <= 57 ) ) || ( ( cc >= 
			  97 ) && ( cc <= 102 ) ) ) ) 
			  incr ( d ) ;
			} 
		      } 
		      if ( d > 2 ) 
		      {
			if ( c <= 57 ) 
			curchr = c - 48 ;
			else curchr = c - 87 ;
			if ( cc <= 57 ) 
			curchr = 16 * curchr + cc - 48 ;
			else curchr = 16 * curchr + cc - 87 ;
			buffer [k - 1 ]= curchr ;
		      } 
		      else if ( c < 64 ) 
		      buffer [k - 1 ]= c + 64 ;
		      else buffer [k - 1 ]= c - 64 ;
		      curinput .limitfield = curinput .limitfield - d ;
		      first = first - d ;
		      while ( k <= curinput .limitfield ) {
			  
			buffer [k ]= buffer [k + d ];
			incr ( k ) ;
		      } 
		      goto lab26 ;
		    } 
		  } 
		} 
	      } 
	    } 
	    curcs = 257 + buffer [curinput .locfield ];
	    incr ( curinput .locfield ) ;
	  } 
	  lab40: curcmd = eqtb [curcs ].hh.b0 ;
	  curchr = eqtb [curcs ].hh .v.RH ;
	  if ( curcmd >= 115 ) 
	  checkoutervalidity () ;
	} 
	break ;
      case 14 : 
      case 30 : 
      case 46 : 
	{
	  curcs = curchr + 1 ;
	  curcmd = eqtb [curcs ].hh.b0 ;
	  curchr = eqtb [curcs ].hh .v.RH ;
	  curinput .statefield = 1 ;
	  if ( curcmd >= 115 ) 
	  checkoutervalidity () ;
	} 
	break ;
      case 8 : 
      case 24 : 
      case 40 : 
	{
	  if ( curchr == buffer [curinput .locfield ]) {
	      
	    if ( curinput .locfield < curinput .limitfield ) 
	    {
	      c = buffer [curinput .locfield + 1 ];
	      if ( c < 128 ) 
	      {
		curinput .locfield = curinput .locfield + 2 ;
		if ( ( ( ( c >= 48 ) && ( c <= 57 ) ) || ( ( c >= 97 ) && ( c 
		<= 102 ) ) ) ) {
		    
		  if ( curinput .locfield <= curinput .limitfield ) 
		  {
		    cc = buffer [curinput .locfield ];
		    if ( ( ( ( cc >= 48 ) && ( cc <= 57 ) ) || ( ( cc >= 97 ) 
		    && ( cc <= 102 ) ) ) ) 
		    {
		      incr ( curinput .locfield ) ;
		      if ( c <= 57 ) 
		      curchr = c - 48 ;
		      else curchr = c - 87 ;
		      if ( cc <= 57 ) 
		      curchr = 16 * curchr + cc - 48 ;
		      else curchr = 16 * curchr + cc - 87 ;
		      goto lab21 ;
		    } 
		  } 
		} 
		if ( c < 64 ) 
		curchr = c + 64 ;
		else curchr = c - 64 ;
		goto lab21 ;
	      } 
	    } 
	  } 
	  curinput .statefield = 1 ;
	} 
	break ;
      case 16 : 
      case 32 : 
      case 48 : 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 264 ) ;
	    print ( 694 ) ;
	  } 
	  {
	    helpptr = 2 ;
	    helpline [1 ]= 695 ;
	    helpline [0 ]= 696 ;
	  } 
	  deletionsallowed = false ;
	  error () ;
	  deletionsallowed = true ;
	  goto lab20 ;
	} 
	break ;
      case 11 : 
	{
	  curinput .statefield = 17 ;
	  curchr = 32 ;
	} 
	break ;
      case 6 : 
	{
	  curinput .locfield = curinput .limitfield + 1 ;
	  curcmd = 10 ;
	  curchr = 32 ;
	} 
	break ;
      case 22 : 
      case 15 : 
      case 31 : 
      case 47 : 
	{
	  curinput .locfield = curinput .limitfield + 1 ;
	  goto lab25 ;
	} 
	break ;
      case 38 : 
	{
	  curinput .locfield = curinput .limitfield + 1 ;
	  curcs = parloc ;
	  curcmd = eqtb [curcs ].hh.b0 ;
	  curchr = eqtb [curcs ].hh .v.RH ;
	  if ( curcmd >= 115 ) 
	  checkoutervalidity () ;
	} 
	break ;
      case 2 : 
	incr ( alignstate ) ;
	break ;
      case 18 : 
      case 34 : 
	{
	  curinput .statefield = 1 ;
	  incr ( alignstate ) ;
	} 
	break ;
      case 3 : 
	decr ( alignstate ) ;
	break ;
      case 19 : 
      case 35 : 
	{
	  curinput .statefield = 1 ;
	  decr ( alignstate ) ;
	} 
	break ;
      case 20 : 
      case 21 : 
      case 23 : 
      case 25 : 
      case 28 : 
      case 29 : 
      case 36 : 
      case 37 : 
      case 39 : 
      case 41 : 
      case 44 : 
      case 45 : 
	curinput .statefield = 1 ;
	break ;
	default: 
	;
	break ;
      } 
    } 
    else {
	
      curinput .statefield = 33 ;
      if ( curinput .namefield > 17 ) 
      {
	incr ( line ) ;
	first = curinput .startfield ;
	if ( ! forceeof ) {
	    
	  if ( curinput .namefield <= 19 ) 
	  {
	    if ( pseudoinput () ) 
	    firmuptheline () ;
	    else if ( ( eqtb [27172 ].hh .v.RH != -268435455L ) && ! eofseen 
	    [curinput .indexfield ]) 
	    {
	      curinput .limitfield = first - 1 ;
	      eofseen [curinput .indexfield ]= true ;
	      begintokenlist ( eqtb [27172 ].hh .v.RH , 19 ) ;
	      goto lab20 ;
	    } 
	    else forceeof = true ;
	  } 
	  else {
	      
	    if ( inputln ( inputfile [curinput .indexfield ], true ) ) 
	    firmuptheline () ;
	    else if ( ( eqtb [27172 ].hh .v.RH != -268435455L ) && ! eofseen 
	    [curinput .indexfield ]) 
	    {
	      curinput .limitfield = first - 1 ;
	      eofseen [curinput .indexfield ]= true ;
	      begintokenlist ( eqtb [27172 ].hh .v.RH , 19 ) ;
	      goto lab20 ;
	    } 
	    else forceeof = true ;
	  } 
	} 
	if ( forceeof ) 
	{
	  if ( eqtb [29369 ].cint > 0 ) {
	      
	    if ( ( grpstack [inopen ]!= curboundary ) || ( ifstack [inopen 
	    ]!= condptr ) ) 
	    filewarning () ;
	  } 
	  if ( curinput .namefield >= 19 ) 
	  {
	    printchar ( 41 ) ;
	    decr ( openparens ) ;
	    fflush ( stdout ) ;
	  } 
	  forceeof = false ;
	  endfilereading () ;
	  checkoutervalidity () ;
	  goto lab20 ;
	} 
	if ( ( eqtb [29322 ].cint < 0 ) || ( eqtb [29322 ].cint > 255 ) ) 
	decr ( curinput .limitfield ) ;
	else buffer [curinput .limitfield ]= eqtb [29322 ].cint ;
	first = curinput .limitfield + 1 ;
	curinput .locfield = curinput .startfield ;
      } 
      else {
	  
	if ( ! ( curinput .namefield == 0 ) ) 
	{
	  curcmd = 0 ;
	  curchr = 0 ;
	  return ;
	} 
	if ( inputptr > 0 ) 
	{
	  endfilereading () ;
	  goto lab20 ;
	} 
	if ( selector < 18 ) 
	openlogfile () ;
	if ( interaction > 1 ) 
	{
	  if ( ( eqtb [29322 ].cint < 0 ) || ( eqtb [29322 ].cint > 255 ) 
	  ) 
	  incr ( curinput .limitfield ) ;
	  if ( curinput .limitfield == curinput .startfield ) 
	  printnl ( 697 ) ;
	  println () ;
	  first = curinput .startfield ;
	  {
	    ;
	    print ( 42 ) ;
	    terminput () ;
	  } 
	  curinput .limitfield = last ;
	  if ( ( eqtb [29322 ].cint < 0 ) || ( eqtb [29322 ].cint > 255 ) 
	  ) 
	  decr ( curinput .limitfield ) ;
	  else buffer [curinput .limitfield ]= eqtb [29322 ].cint ;
	  first = curinput .limitfield + 1 ;
	  curinput .locfield = curinput .startfield ;
	} 
	else fatalerror ( 698 ) ;
      } 
      {
	if ( interrupt != 0 ) 
	pauseforinstructions () ;
      } 
      goto lab25 ;
    } 
  } 
  else if ( curinput .locfield != -268435455L ) 
  {
    t = mem [curinput .locfield ].hh .v.LH ;
    curinput .locfield = mem [curinput .locfield ].hh .v.RH ;
    if ( t >= 4095 ) 
    {
      curcs = t - 4095 ;
      curcmd = eqtb [curcs ].hh.b0 ;
      curchr = eqtb [curcs ].hh .v.RH ;
      if ( curcmd >= 115 ) {
	  
	if ( curcmd == 118 ) 
	{
	  curcs = mem [curinput .locfield ].hh .v.LH - 4095 ;
	  curinput .locfield = -268435455L ;
	  curcmd = eqtb [curcs ].hh.b0 ;
	  curchr = eqtb [curcs ].hh .v.RH ;
	  if ( curcmd > 102 ) 
	  {
	    curcmd = 0 ;
	    curchr = 257 ;
	  } 
	} 
	else checkoutervalidity () ;
      } 
    } 
    else {
	
      curcmd = t / 256 ;
      curchr = t % 256 ;
      switch ( curcmd ) 
      {case 1 : 
	incr ( alignstate ) ;
	break ;
      case 2 : 
	decr ( alignstate ) ;
	break ;
      case 5 : 
	{
	  begintokenlist ( paramstack [curinput .limitfield + curchr - 1 ], 
	  0 ) ;
	  goto lab20 ;
	} 
	break ;
	default: 
	;
	break ;
      } 
    } 
  } 
  else {
      
    endtokenlist () ;
    goto lab20 ;
  } 
  if ( curcmd <= 5 ) {
      
    if ( curcmd >= 4 ) {
	
      if ( alignstate == 0 ) 
      {
	if ( ( scannerstatus == 4 ) || ( curalign == -268435455L ) ) 
	fatalerror ( 674 ) ;
	curcmd = mem [curalign + 5 ].hh .v.LH ;
	mem [curalign + 5 ].hh .v.LH = curchr ;
	if ( curcmd == 63 ) 
	begintokenlist ( memtop - 10 , 2 ) ;
	else begintokenlist ( mem [curalign + 2 ].cint , 2 ) ;
	alignstate = 1000000L ;
	goto lab20 ;
      } 
    } 
  } 
} 
void 
firmuptheline ( void ) 
{
  firmuptheline_regmem 
  integer k  ;
  curinput .limitfield = last ;
  if ( eqtb [29302 ].cint > 0 ) {
      
    if ( interaction > 1 ) 
    {
      ;
      println () ;
      if ( curinput .startfield < curinput .limitfield ) 
      {register integer for_end; k = curinput .startfield ;for_end = 
      curinput .limitfield - 1 ; if ( k <= for_end) do 
	print ( buffer [k ]) ;
      while ( k++ < for_end ) ;} 
      first = curinput .limitfield ;
      {
	;
	print ( 699 ) ;
	terminput () ;
      } 
      if ( last > first ) 
      {
	{register integer for_end; k = first ;for_end = last - 1 ; if ( k <= 
	for_end) do 
	  buffer [k + curinput .startfield - first ]= buffer [k ];
	while ( k++ < for_end ) ;} 
	curinput .limitfield = curinput .startfield + last - first ;
      } 
    } 
  } 
} 
void 
gettoken ( void ) 
{
  gettoken_regmem 
  nonewcontrolsequence = false ;
  getnext () ;
  nonewcontrolsequence = true ;
  if ( curcs == 0 ) 
  curtok = ( curcmd * 256 ) + curchr ;
  else curtok = 4095 + curcs ;
} 
void 
macrocall ( void ) 
{
  /* 10 22 30 31 40 */ macrocall_regmem 
  halfword r  ;
  halfword p  ;
  halfword q  ;
  halfword s  ;
  halfword t  ;
  halfword u, v  ;
  halfword rbraceptr  ;
  smallnumber n  ;
  halfword unbalance  ;
  halfword m  ;
  halfword refcount  ;
  smallnumber savescannerstatus  ;
  halfword savewarningindex  ;
  ASCIIcode matchchr  ;
  savescannerstatus = scannerstatus ;
  savewarningindex = warningindex ;
  warningindex = curcs ;
  refcount = curchr ;
  r = mem [refcount ].hh .v.RH ;
  n = 0 ;
  if ( eqtb [29304 ].cint > 0 ) 
  {
    begindiagnostic () ;
    println () ;
    printcs ( warningindex ) ;
    tokenshow ( refcount ) ;
    enddiagnostic ( false ) ;
  } 
  if ( mem [r ].hh .v.LH == 3585 ) 
  r = mem [r ].hh .v.RH ;
  if ( mem [r ].hh .v.LH != 3584 ) 
  {
    scannerstatus = 3 ;
    unbalance = 0 ;
    longstate = eqtb [curcs ].hh.b0 ;
    if ( longstate >= 115 ) 
    longstate = longstate - 2 ;
    do {
	mem [memtop - 3 ].hh .v.RH = -268435455L ;
      if ( ( mem [r ].hh .v.LH > 3583 ) || ( mem [r ].hh .v.LH < 3328 ) ) 
      s = -268435455L ;
      else {
	  
	matchchr = mem [r ].hh .v.LH - 3328 ;
	s = mem [r ].hh .v.RH ;
	r = s ;
	p = memtop - 3 ;
	m = 0 ;
      } 
      lab22: gettoken () ;
      if ( curtok == mem [r ].hh .v.LH ) 
      {
	r = mem [r ].hh .v.RH ;
	if ( ( mem [r ].hh .v.LH >= 3328 ) && ( mem [r ].hh .v.LH <= 3584 
	) ) 
	{
	  if ( curtok < 512 ) 
	  decr ( alignstate ) ;
	  goto lab40 ;
	} 
	else goto lab22 ;
      } 
      if ( s != r ) {
	  
	if ( s == -268435455L ) 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 264 ) ;
	    print ( 732 ) ;
	  } 
	  sprintcs ( warningindex ) ;
	  print ( 733 ) ;
	  {
	    helpptr = 4 ;
	    helpline [3 ]= 734 ;
	    helpline [2 ]= 735 ;
	    helpline [1 ]= 736 ;
	    helpline [0 ]= 737 ;
	  } 
	  error () ;
	  goto lab10 ;
	} 
	else {
	    
	  t = s ;
	  do {
	      { 
	      q = getavail () ;
	      mem [p ].hh .v.RH = q ;
	      mem [q ].hh .v.LH = mem [t ].hh .v.LH ;
	      p = q ;
	    } 
	    incr ( m ) ;
	    u = mem [t ].hh .v.RH ;
	    v = s ;
	    while ( true ) {
		
	      if ( u == r ) {
		  
		if ( curtok != mem [v ].hh .v.LH ) 
		goto lab30 ;
		else {
		    
		  r = mem [v ].hh .v.RH ;
		  goto lab22 ;
		} 
	      } 
	      if ( mem [u ].hh .v.LH != mem [v ].hh .v.LH ) 
	      goto lab30 ;
	      u = mem [u ].hh .v.RH ;
	      v = mem [v ].hh .v.RH ;
	    } 
	    lab30: t = mem [t ].hh .v.RH ;
	  } while ( ! ( t == r ) ) ;
	  r = s ;
	} 
      } 
      if ( curtok == partoken ) {
	  
	if ( longstate != 114 ) 
	{
	  if ( longstate == 113 ) 
	  {
	    runaway () ;
	    {
	      if ( interaction == 3 ) 
	      ;
	      if ( filelineerrorstylep ) 
	      printfileline () ;
	      else printnl ( 264 ) ;
	      print ( 727 ) ;
	    } 
	    sprintcs ( warningindex ) ;
	    print ( 728 ) ;
	    {
	      helpptr = 3 ;
	      helpline [2 ]= 729 ;
	      helpline [1 ]= 730 ;
	      helpline [0 ]= 731 ;
	    } 
	    backerror () ;
	  } 
	  pstack [n ]= mem [memtop - 3 ].hh .v.RH ;
	  alignstate = alignstate - unbalance ;
	  {register integer for_end; m = 0 ;for_end = n ; if ( m <= for_end) 
	  do 
	    flushlist ( pstack [m ]) ;
	  while ( m++ < for_end ) ;} 
	  goto lab10 ;
	} 
      } 
      if ( curtok < 768 ) {
	  
	if ( curtok < 512 ) 
	{
	  unbalance = 1 ;
	  while ( true ) {
	      
	    {
	      {
		q = avail ;
		if ( q == -268435455L ) 
		q = getavail () ;
		else {
		    
		  avail = mem [q ].hh .v.RH ;
		  mem [q ].hh .v.RH = -268435455L ;
	;
#ifdef STAT
		  incr ( dynused ) ;
#endif /* STAT */
		} 
	      } 
	      mem [p ].hh .v.RH = q ;
	      mem [q ].hh .v.LH = curtok ;
	      p = q ;
	    } 
	    gettoken () ;
	    if ( curtok == partoken ) {
		
	      if ( longstate != 114 ) 
	      {
		if ( longstate == 113 ) 
		{
		  runaway () ;
		  {
		    if ( interaction == 3 ) 
		    ;
		    if ( filelineerrorstylep ) 
		    printfileline () ;
		    else printnl ( 264 ) ;
		    print ( 727 ) ;
		  } 
		  sprintcs ( warningindex ) ;
		  print ( 728 ) ;
		  {
		    helpptr = 3 ;
		    helpline [2 ]= 729 ;
		    helpline [1 ]= 730 ;
		    helpline [0 ]= 731 ;
		  } 
		  backerror () ;
		} 
		pstack [n ]= mem [memtop - 3 ].hh .v.RH ;
		alignstate = alignstate - unbalance ;
		{register integer for_end; m = 0 ;for_end = n ; if ( m <= 
		for_end) do 
		  flushlist ( pstack [m ]) ;
		while ( m++ < for_end ) ;} 
		goto lab10 ;
	      } 
	    } 
	    if ( curtok < 768 ) {
		
	      if ( curtok < 512 ) 
	      incr ( unbalance ) ;
	      else {
		  
		decr ( unbalance ) ;
		if ( unbalance == 0 ) 
		goto lab31 ;
	      } 
	    } 
	  } 
	  lab31: rbraceptr = p ;
	  {
	    q = getavail () ;
	    mem [p ].hh .v.RH = q ;
	    mem [q ].hh .v.LH = curtok ;
	    p = q ;
	  } 
	} 
	else {
	    
	  backinput () ;
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 264 ) ;
	    print ( 719 ) ;
	  } 
	  sprintcs ( warningindex ) ;
	  print ( 720 ) ;
	  {
	    helpptr = 6 ;
	    helpline [5 ]= 721 ;
	    helpline [4 ]= 722 ;
	    helpline [3 ]= 723 ;
	    helpline [2 ]= 724 ;
	    helpline [1 ]= 725 ;
	    helpline [0 ]= 726 ;
	  } 
	  incr ( alignstate ) ;
	  longstate = 113 ;
	  curtok = partoken ;
	  inserror () ;
	  goto lab22 ;
	} 
      } 
      else {
	  
	if ( curtok == 2592 ) {
	    
	  if ( mem [r ].hh .v.LH <= 3584 ) {
	      
	    if ( mem [r ].hh .v.LH >= 3328 ) 
	    goto lab22 ;
	  } 
	} 
	{
	  q = getavail () ;
	  mem [p ].hh .v.RH = q ;
	  mem [q ].hh .v.LH = curtok ;
	  p = q ;
	} 
      } 
      incr ( m ) ;
      if ( mem [r ].hh .v.LH > 3584 ) 
      goto lab22 ;
      if ( mem [r ].hh .v.LH < 3328 ) 
      goto lab22 ;
      lab40: if ( s != -268435455L ) 
      {
	if ( ( m == 1 ) && ( mem [p ].hh .v.LH < 768 ) && ( p != memtop - 3 
	) ) 
	{
	  mem [rbraceptr ].hh .v.RH = -268435455L ;
	  {
	    mem [p ].hh .v.RH = avail ;
	    avail = p ;
	;
#ifdef STAT
	    decr ( dynused ) ;
#endif /* STAT */
	  } 
	  p = mem [memtop - 3 ].hh .v.RH ;
	  pstack [n ]= mem [p ].hh .v.RH ;
	  {
	    mem [p ].hh .v.RH = avail ;
	    avail = p ;
	;
#ifdef STAT
	    decr ( dynused ) ;
#endif /* STAT */
	  } 
	} 
	else pstack [n ]= mem [memtop - 3 ].hh .v.RH ;
	incr ( n ) ;
	if ( eqtb [29304 ].cint > 0 ) 
	{
	  begindiagnostic () ;
	  printnl ( matchchr ) ;
	  printint ( n ) ;
	  print ( 738 ) ;
	  showtokenlist ( pstack [n - 1 ], -268435455L , 1000 ) ;
	  enddiagnostic ( false ) ;
	} 
      } 
    } while ( ! ( mem [r ].hh .v.LH == 3584 ) ) ;
  } 
  while ( ( curinput .statefield == 0 ) && ( curinput .locfield == -268435455L 
  ) && ( curinput .indexfield != 2 ) ) endtokenlist () ;
  begintokenlist ( refcount , 5 ) ;
  curinput .namefield = warningindex ;
  curinput .locfield = mem [r ].hh .v.RH ;
  if ( n > 0 ) 
  {
    if ( paramptr + n > maxparamstack ) 
    {
      maxparamstack = paramptr + n ;
      if ( maxparamstack > paramsize ) 
      overflow ( 718 , paramsize ) ;
    } 
    {register integer for_end; m = 0 ;for_end = n - 1 ; if ( m <= for_end) 
    do 
      paramstack [paramptr + m ]= pstack [m ];
    while ( m++ < for_end ) ;} 
    paramptr = paramptr + n ;
  } 
  lab10: scannerstatus = savescannerstatus ;
  warningindex = savewarningindex ;
} 
void 
insertrelax ( void ) 
{
  insertrelax_regmem 
  curtok = 4095 + curcs ;
  backinput () ;
  curtok = 19616 ;
  backinput () ;
  curinput .indexfield = 4 ;
} 
void 
znewindex ( quarterword i , halfword q ) 
{
  newindex_regmem 
  smallnumber k  ;
  curptr = getnode ( 9 ) ;
  mem [curptr ].hh.b0 = i ;
  mem [curptr ].hh.b1 = 0 ;
  mem [curptr ].hh .v.RH = q ;
  {register integer for_end; k = 1 ;for_end = 8 ; if ( k <= for_end) do 
    mem [curptr + k ]= sanull ;
  while ( k++ < for_end ) ;} 
} 
void 
zfindsaelement ( smallnumber t , halfword n , boolean w ) 
{
  /* 45 46 47 48 49 10 */ findsaelement_regmem 
  halfword q  ;
  smallnumber i  ;
  curptr = saroot [t ];
  {
    if ( curptr == -268435455L ) {
	
      if ( w ) 
      goto lab45 ;
      else return ;
    } 
  } 
  q = curptr ;
  i = n / 4096 ;
  if ( odd ( i ) ) 
  curptr = mem [q + ( i / 2 ) + 1 ].hh .v.RH ;
  else curptr = mem [q + ( i / 2 ) + 1 ].hh .v.LH ;
  {
    if ( curptr == -268435455L ) {
	
      if ( w ) 
      goto lab46 ;
      else return ;
    } 
  } 
  q = curptr ;
  i = ( n / 256 ) % 16 ;
  if ( odd ( i ) ) 
  curptr = mem [q + ( i / 2 ) + 1 ].hh .v.RH ;
  else curptr = mem [q + ( i / 2 ) + 1 ].hh .v.LH ;
  {
    if ( curptr == -268435455L ) {
	
      if ( w ) 
      goto lab47 ;
      else return ;
    } 
  } 
  q = curptr ;
  i = ( n / 16 ) % 16 ;
  if ( odd ( i ) ) 
  curptr = mem [q + ( i / 2 ) + 1 ].hh .v.RH ;
  else curptr = mem [q + ( i / 2 ) + 1 ].hh .v.LH ;
  {
    if ( curptr == -268435455L ) {
	
      if ( w ) 
      goto lab48 ;
      else return ;
    } 
  } 
  q = curptr ;
  i = n % 16 ;
  if ( odd ( i ) ) 
  curptr = mem [q + ( i / 2 ) + 1 ].hh .v.RH ;
  else curptr = mem [q + ( i / 2 ) + 1 ].hh .v.LH ;
  if ( ( curptr == -268435455L ) && w ) 
  goto lab49 ;
  return ;
  lab45: newindex ( t , -268435455L ) ;
  saroot [t ]= curptr ;
  q = curptr ;
  i = n / 4096 ;
  lab46: newindex ( i , q ) ;
  {
    if ( odd ( i ) ) 
    mem [q + ( i / 2 ) + 1 ].hh .v.RH = curptr ;
    else mem [q + ( i / 2 ) + 1 ].hh .v.LH = curptr ;
    incr ( mem [q ].hh.b1 ) ;
  } 
  q = curptr ;
  i = ( n / 256 ) % 16 ;
  lab47: newindex ( i , q ) ;
  {
    if ( odd ( i ) ) 
    mem [q + ( i / 2 ) + 1 ].hh .v.RH = curptr ;
    else mem [q + ( i / 2 ) + 1 ].hh .v.LH = curptr ;
    incr ( mem [q ].hh.b1 ) ;
  } 
  q = curptr ;
  i = ( n / 16 ) % 16 ;
  lab48: newindex ( i , q ) ;
  {
    if ( odd ( i ) ) 
    mem [q + ( i / 2 ) + 1 ].hh .v.RH = curptr ;
    else mem [q + ( i / 2 ) + 1 ].hh .v.LH = curptr ;
    incr ( mem [q ].hh.b1 ) ;
  } 
  q = curptr ;
  i = n % 16 ;
  lab49: if ( t == 6 ) 
  {
    curptr = getnode ( 4 ) ;
    mem [curptr + 1 ]= sanull ;
    mem [curptr + 2 ]= sanull ;
    mem [curptr + 3 ]= sanull ;
  } 
  else {
      
    if ( t <= 1 ) 
    {
      curptr = getnode ( 3 ) ;
      mem [curptr + 2 ].cint = 0 ;
      mem [curptr + 1 ].hh .v.RH = n ;
    } 
    else {
	
      curptr = getnode ( 2 ) ;
      if ( t <= 3 ) 
      {
	mem [curptr + 1 ].hh .v.RH = membot ;
	incr ( mem [membot ].hh .v.RH ) ;
      } 
      else mem [curptr + 1 ].hh .v.RH = -268435455L ;
    } 
    mem [curptr + 1 ].hh .v.LH = -268435455L ;
  } 
  mem [curptr ].hh.b0 = 16 * t + i ;
  mem [curptr ].hh.b1 = 1 ;
  mem [curptr ].hh .v.RH = q ;
  {
    if ( odd ( i ) ) 
    mem [q + ( i / 2 ) + 1 ].hh .v.RH = curptr ;
    else mem [q + ( i / 2 ) + 1 ].hh .v.LH = curptr ;
    incr ( mem [q ].hh.b1 ) ;
  } 
} 
void 
expand ( void ) 
{
  /* 21 */ expand_regmem 
  halfword t  ;
  boolean b  ;
  halfword p, q, r  ;
  integer j  ;
  integer cvbackup  ;
  smallnumber cvlbackup, radixbackup, cobackup  ;
  halfword backupbackup  ;
  smallnumber savescannerstatus  ;
  incr ( expanddepthcount ) ;
  if ( expanddepthcount >= expanddepth ) 
  overflow ( 700 , expanddepth ) ;
  cvbackup = curval ;
  cvlbackup = curvallevel ;
  radixbackup = radix ;
  cobackup = curorder ;
  backupbackup = mem [memtop - 13 ].hh .v.RH ;
  lab21: if ( curcmd < 113 ) 
  {
    if ( eqtb [29310 ].cint > 1 ) 
    showcurcmdchr () ;
    switch ( curcmd ) 
    {case 112 : 
      {
	t = curchr % 5 ;
	if ( curchr >= 5 ) 
	scanregisternum () ;
	else curval = 0 ;
	if ( curval == 0 ) 
	curptr = curmark [t ];
	else {
	    
	  findsaelement ( 6 , curval , false ) ;
	  if ( curptr != -268435455L ) {
	      
	    if ( odd ( t ) ) 
	    curptr = mem [curptr + ( t / 2 ) + 1 ].hh .v.RH ;
	    else curptr = mem [curptr + ( t / 2 ) + 1 ].hh .v.LH ;
	  } 
	} 
	if ( curptr != -268435455L ) 
	begintokenlist ( curptr , 14 ) ;
      } 
      break ;
    case 104 : 
      if ( curchr == 0 ) 
      {
	gettoken () ;
	t = curtok ;
	gettoken () ;
	if ( curcmd > 102 ) 
	expand () ;
	else backinput () ;
	curtok = t ;
	backinput () ;
      } 
      else {
	  
	gettoken () ;
	if ( ( curcmd == 107 ) && ( curchr != 16 ) ) 
	{
	  curchr = curchr + 32 ;
	  goto lab21 ;
	} 
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 781 ) ;
	} 
	printesc ( 923 ) ;
	print ( 2023 ) ;
	printcmdchr ( curcmd , curchr ) ;
	printchar ( 39 ) ;
	{
	  helpptr = 1 ;
	  helpline [0 ]= 696 ;
	} 
	backerror () ;
      } 
      break ;
    case 105 : 
      if ( curchr == 0 ) 
      {
	savescannerstatus = scannerstatus ;
	scannerstatus = 0 ;
	gettoken () ;
	scannerstatus = savescannerstatus ;
	t = curtok ;
	backinput () ;
	if ( t >= 4095 ) 
	{
	  p = getavail () ;
	  mem [p ].hh .v.LH = 19618 ;
	  mem [p ].hh .v.RH = curinput .locfield ;
	  curinput .startfield = p ;
	  curinput .locfield = p ;
	} 
      } 
      else {
	  
	savescannerstatus = scannerstatus ;
	scannerstatus = 0 ;
	gettoken () ;
	scannerstatus = savescannerstatus ;
	if ( curcs < 514 ) 
	curcs = primlookup ( curcs - 257 ) ;
	else curcs = primlookup ( hash [curcs ].v.RH ) ;
	if ( curcs != 0 ) 
	{
	  t = eqtb [15526 + curcs ].hh.b0 ;
	  if ( t > 102 ) 
	  {
	    curcmd = t ;
	    curchr = eqtb [15526 + curcs ].hh .v.RH ;
	    curtok = ( curcmd * 256 ) + curchr ;
	    curcs = 0 ;
	    goto lab21 ;
	  } 
	  else {
	      
	    backinput () ;
	    p = getavail () ;
	    mem [p ].hh .v.LH = 19620 ;
	    mem [p ].hh .v.RH = curinput .locfield ;
	    curinput .locfield = p ;
	    curinput .startfield = p ;
	  } 
	} 
      } 
      break ;
    case 109 : 
      {
	r = getavail () ;
	p = r ;
	b = isincsname ;
	isincsname = true ;
	do {
	    getxtoken () ;
	  if ( curcs == 0 ) 
	  {
	    q = getavail () ;
	    mem [p ].hh .v.RH = q ;
	    mem [q ].hh .v.LH = curtok ;
	    p = q ;
	  } 
	} while ( ! ( curcs != 0 ) ) ;
	if ( curcmd != 67 ) 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 264 ) ;
	    print ( 707 ) ;
	  } 
	  printesc ( 577 ) ;
	  print ( 708 ) ;
	  {
	    helpptr = 2 ;
	    helpline [1 ]= 709 ;
	    helpline [0 ]= 710 ;
	  } 
	  backerror () ;
	} 
	isincsname = b ;
	j = first ;
	p = mem [r ].hh .v.RH ;
	while ( p != -268435455L ) {
	    
	  if ( j >= maxbufstack ) 
	  {
	    maxbufstack = j + 1 ;
	    if ( maxbufstack == bufsize ) 
	    overflow ( 258 , bufsize ) ;
	  } 
	  buffer [j ]= mem [p ].hh .v.LH % 256 ;
	  incr ( j ) ;
	  p = mem [p ].hh .v.RH ;
	} 
	if ( j > first + 1 ) 
	{
	  nonewcontrolsequence = false ;
	  curcs = idlookup ( first , j - first ) ;
	  nonewcontrolsequence = true ;
	} 
	else if ( j == first ) 
	curcs = 513 ;
	else curcs = 257 + buffer [first ];
	flushlist ( r ) ;
	if ( eqtb [curcs ].hh.b0 == 103 ) 
	{
	  eqdefine ( curcs , 0 , 256 ) ;
	} 
	curtok = curcs + 4095 ;
	backinput () ;
      } 
      break ;
    case 110 : 
      convtoks () ;
      break ;
    case 111 : 
      insthetoks () ;
      break ;
    case 107 : 
      conditional () ;
      break ;
    case 108 : 
      {
	if ( eqtb [29367 ].cint > 0 ) {
	    
	  if ( eqtb [29310 ].cint <= 1 ) 
	  showcurcmdchr () ;
	} 
	if ( curchr > iflimit ) {
	    
	  if ( iflimit == 1 ) 
	  insertrelax () ;
	  else {
	      
	    {
	      if ( interaction == 3 ) 
	      ;
	      if ( filelineerrorstylep ) 
	      printfileline () ;
	      else printnl ( 264 ) ;
	      print ( 927 ) ;
	    } 
	    printcmdchr ( 108 , curchr ) ;
	    {
	      helpptr = 1 ;
	      helpline [0 ]= 928 ;
	    } 
	    error () ;
	  } 
	} 
	else {
	    
	  while ( curchr != 2 ) passtext () ;
	  {
	    if ( ifstack [inopen ]== condptr ) 
	    ifwarning () ;
	    p = condptr ;
	    ifline = mem [p + 1 ].cint ;
	    curif = mem [p ].hh.b1 ;
	    iflimit = mem [p ].hh.b0 ;
	    condptr = mem [p ].hh .v.RH ;
	    freenode ( p , 2 ) ;
	  } 
	} 
      } 
      break ;
    case 106 : 
      if ( curchr == 1 ) 
      forceeof = true ;
      else if ( curchr == 2 ) 
      pseudostart () ;
      else if ( nameinprogress ) 
      insertrelax () ;
      else startinput () ;
      break ;
      default: 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 701 ) ;
	} 
	{
	  helpptr = 5 ;
	  helpline [4 ]= 702 ;
	  helpline [3 ]= 703 ;
	  helpline [2 ]= 704 ;
	  helpline [1 ]= 705 ;
	  helpline [0 ]= 706 ;
	} 
	error () ;
      } 
      break ;
    } 
  } 
  else if ( curcmd < 117 ) 
  macrocall () ;
  else {
      
    curtok = 19615 ;
    backinput () ;
  } 
  curval = cvbackup ;
  curvallevel = cvlbackup ;
  radix = radixbackup ;
  curorder = cobackup ;
  mem [memtop - 13 ].hh .v.RH = backupbackup ;
  decr ( expanddepthcount ) ;
} 
void 
getxtoken ( void ) 
{
  /* 20 30 */ getxtoken_regmem 
  lab20: getnext () ;
  if ( curcmd <= 102 ) 
  goto lab30 ;
  if ( curcmd >= 113 ) {
      
    if ( curcmd < 117 ) 
    macrocall () ;
    else {
	
      curcs = 15520 ;
      curcmd = 9 ;
      goto lab30 ;
    } 
  } 
  else expand () ;
  goto lab20 ;
  lab30: if ( curcs == 0 ) 
  curtok = ( curcmd * 256 ) + curchr ;
  else curtok = 4095 + curcs ;
} 
void 
xtoken ( void ) 
{
  xtoken_regmem 
  while ( curcmd > 102 ) {
      
    expand () ;
    getnext () ;
  } 
  if ( curcs == 0 ) 
  curtok = ( curcmd * 256 ) + curchr ;
  else curtok = 4095 + curcs ;
} 
void 
scanleftbrace ( void ) 
{
  scanleftbrace_regmem 
  do {
      getxtoken () ;
  } while ( ! ( ( curcmd != 10 ) && ( curcmd != 0 ) ) ) ;
  if ( curcmd != 1 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 739 ) ;
    } 
    {
      helpptr = 4 ;
      helpline [3 ]= 740 ;
      helpline [2 ]= 741 ;
      helpline [1 ]= 742 ;
      helpline [0 ]= 743 ;
    } 
    backerror () ;
    curtok = 379 ;
    curcmd = 1 ;
    curchr = 123 ;
    incr ( alignstate ) ;
  } 
} 
void 
scanoptionalequals ( void ) 
{
  scanoptionalequals_regmem 
  do {
      getxtoken () ;
  } while ( ! ( curcmd != 10 ) ) ;
  if ( curtok != 3133 ) 
  backinput () ;
} 
boolean 
zscankeyword ( strnumber s ) 
{
  /* 10 */ register boolean Result; scankeyword_regmem 
  halfword p  ;
  halfword q  ;
  poolpointer k  ;
  halfword savecurcs  ;
  p = memtop - 13 ;
  mem [p ].hh .v.RH = -268435455L ;
  k = strstart [s ];
  savecurcs = curcs ;
  while ( k < strstart [s + 1 ]) {
      
    getxtoken () ;
    if ( ( curcs == 0 ) && ( ( curchr == strpool [k ]) || ( curchr == 
    strpool [k ]- 32 ) ) ) 
    {
      {
	q = getavail () ;
	mem [p ].hh .v.RH = q ;
	mem [q ].hh .v.LH = curtok ;
	p = q ;
      } 
      incr ( k ) ;
    } 
    else if ( ( curcmd != 10 ) || ( p != memtop - 13 ) ) 
    {
      backinput () ;
      if ( p != memtop - 13 ) 
      begintokenlist ( mem [memtop - 13 ].hh .v.RH , 3 ) ;
      curcs = savecurcs ;
      Result = false ;
      return Result ;
    } 
  } 
  flushlist ( mem [memtop - 13 ].hh .v.RH ) ;
  Result = true ;
  return Result ;
} 
void 
muerror ( void ) 
{
  muerror_regmem 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 264 ) ;
    print ( 744 ) ;
  } 
  {
    helpptr = 1 ;
    helpline [0 ]= 745 ;
  } 
  error () ;
} 
void 
scaneightbitint ( void ) 
{
  scaneightbitint_regmem 
  scanint () ;
  if ( ( curval < 0 ) || ( curval > 255 ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 783 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 784 ;
      helpline [0 ]= 785 ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
scancharnum ( void ) 
{
  scancharnum_regmem 
  scanint () ;
  if ( ( curval < 0 ) || ( curval > 255 ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 786 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 787 ;
      helpline [0 ]= 785 ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
scanfourbitint ( void ) 
{
  scanfourbitint_regmem 
  scanint () ;
  if ( ( curval < 0 ) || ( curval > 15 ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 788 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 789 ;
      helpline [0 ]= 785 ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
scanfifteenbitint ( void ) 
{
  scanfifteenbitint_regmem 
  scanint () ;
  if ( ( curval < 0 ) || ( curval > 32767 ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 790 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 791 ;
      helpline [0 ]= 785 ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
scantwentysevenbitint ( void ) 
{
  scantwentysevenbitint_regmem 
  scanint () ;
  if ( ( curval < 0 ) || ( curval > 134217727L ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 792 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 793 ;
      helpline [0 ]= 785 ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
scanregisternum ( void ) 
{
  scanregisternum_regmem 
  scanint () ;
  if ( ( curval < 0 ) || ( curval > maxregnum ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 783 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= maxreghelpline ;
      helpline [0 ]= 785 ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
scanfourbitintor18 ( void ) 
{
  scanfourbitintor18_regmem 
  scanint () ;
  if ( ( curval < 0 ) || ( ( curval > 15 ) && ( curval != 18 ) ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 788 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 789 ;
      helpline [0 ]= 785 ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
getxorprotected ( void ) 
{
  /* 10 */ getxorprotected_regmem 
  while ( true ) {
      
    gettoken () ;
    if ( curcmd <= 102 ) 
    return ;
    if ( ( curcmd >= 113 ) && ( curcmd < 117 ) ) {
	
      if ( mem [mem [curchr ].hh .v.RH ].hh .v.LH == 3585 ) 
      return ;
    } 
    expand () ;
  } 
} 
integer 
zeffectivechar ( boolean errp , internalfontnumber f , quarterword c ) 
{
  /* 40 */ register integer Result; effectivechar_regmem 
  integer basec  ;
  integer result  ;
  result = c ;
  if ( ! mltexenabledp ) 
  goto lab40 ;
  if ( fontec [f ]>= c ) {
      
    if ( fontbc [f ]<= c ) {
	
      if ( ( fontinfo [charbase [f ]+ c ].qqqq .b0 > 0 ) ) 
      goto lab40 ;
    } 
  } 
  if ( c >= eqtb [29329 ].cint ) {
      
    if ( c <= eqtb [29330 ].cint ) {
	
      if ( ( eqtb [29018 + c ].hh .v.RH > 0 ) ) 
      {
	basec = ( eqtb [29018 + c ].hh .v.RH % 256 ) ;
	result = basec ;
	if ( ! errp ) 
	goto lab40 ;
	if ( fontec [f ]>= basec ) {
	    
	  if ( fontbc [f ]<= basec ) {
	      
	    if ( ( fontinfo [charbase [f ]+ basec ].qqqq .b0 > 0 ) ) 
	    goto lab40 ;
	  } 
	} 
      } 
    } 
  } 
  if ( errp ) 
  {
    begindiagnostic () ;
    printnl ( 978 ) ;
    print ( 2056 ) ;
    print ( c ) ;
    print ( 979 ) ;
    slowprint ( fontname [f ]) ;
    printchar ( 33 ) ;
    enddiagnostic ( false ) ;
    result = fontbc [f ];
  } 
  lab40: Result = result ;
  return Result ;
} 
integer 
ztestnoligatures ( internalfontnumber f ) 
{
  /* 10 */ register integer Result; testnoligatures_regmem 
  integer c  ;
  Result = 1 ;
  {register integer for_end; c = fontbc [f ];for_end = fontec [f ]; if ( 
  c <= for_end) do 
    if ( ( fontinfo [charbase [f ]+ c ].qqqq .b0 > 0 ) ) {
	
      if ( odd ( ( ( fontinfo [charbase [f ]+ c ].qqqq .b2 ) % 4 ) ) ) 
      {
	Result = 0 ;
	return Result ;
      } 
    } 
  while ( c++ < for_end ) ;} 
  return Result ;
} 
integer 
zgettagcode ( internalfontnumber f , eightbits c ) 
{
  register integer Result; gettagcode_regmem 
  smallnumber i  ;
  if ( ( ( fontbc [f ]<= c ) && ( c <= fontec [f ]) && ( fontinfo [
  charbase [f ]+ c ].qqqq .b0 > 0 ) ) ) 
  {
    i = ( ( fontinfo [charbase [f ]+ c ].qqqq .b2 ) % 4 ) ;
    if ( i == 1 ) 
    Result = 1 ;
    else if ( i == 2 ) 
    Result = 2 ;
    else if ( i == 3 ) 
    Result = 4 ;
    else Result = 0 ;
  } 
  else Result = -1 ;
  return Result ;
} 
void 
scanfontident ( void ) 
{
  scanfontident_regmem 
  internalfontnumber f  ;
  halfword m  ;
  do {
      getxtoken () ;
  } while ( ! ( curcmd != 10 ) ) ;
  if ( ( curcmd == 88 ) || ( curcmd == 101 ) || ( curcmd == 102 ) ) 
  f = eqtb [27689 ].hh .v.RH ;
  else if ( curcmd == 87 ) 
  f = curchr ;
  else if ( curcmd == 86 ) 
  {
    m = curchr ;
    scanfourbitint () ;
    f = eqtb [m + curval ].hh .v.RH ;
  } 
  else {
      
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 970 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 971 ;
      helpline [0 ]= 972 ;
    } 
    backerror () ;
    f = 0 ;
  } 
  curval = f ;
} 
void 
zfindfontdimen ( boolean writing ) 
{
  findfontdimen_regmem 
  internalfontnumber f  ;
  integer n  ;
  scanint () ;
  n = curval ;
  scanfontident () ;
  f = curval ;
  if ( n <= 0 ) 
  curval = fmemptr ;
  else {
      
    if ( writing && ( n <= 4 ) && ( n >= 2 ) && ( fontglue [f ]!= 
    -268435455L ) ) 
    {
      deleteglueref ( fontglue [f ]) ;
      fontglue [f ]= -268435455L ;
    } 
    if ( n > fontparams [f ]) {
	
      if ( f < fontptr ) 
      curval = fmemptr ;
      else {
	  
	do {
	    if ( fmemptr == fontmemsize ) 
	  overflow ( 977 , fontmemsize ) ;
	  fontinfo [fmemptr ].cint = 0 ;
	  incr ( fmemptr ) ;
	  incr ( fontparams [f ]) ;
	} while ( ! ( n == fontparams [f ]) ) ;
	curval = fmemptr - 1 ;
      } 
    } 
    else curval = n + parambase [f ];
  } 
  if ( curval == fmemptr ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 952 ) ;
    } 
    printesc ( hash [17626 + f ].v.RH ) ;
    print ( 973 ) ;
    printint ( fontparams [f ]) ;
    print ( 974 ) ;
    {
      helpptr = 2 ;
      helpline [1 ]= 975 ;
      helpline [0 ]= 976 ;
    } 
    error () ;
  } 
} 
void 
zscansomethinginternal ( smallnumber level , boolean negative ) 
{
  /* 10 20 */ scansomethinginternal_regmem 
  halfword m  ;
  integer n, k  ;
  halfword q, r  ;
  halfword tx  ;
  fourquarters i  ;
  integer p  ;
  lab20: m = curchr ;
  switch ( curcmd ) 
  {case 85 : 
    {
      scancharnum () ;
      if ( m == 28762 ) 
      {
	curval = eqtb [28762 + curval ].hh .v.RH ;
	curvallevel = 0 ;
      } 
      else if ( m < 28762 ) 
      {
	curval = eqtb [m + curval ].hh .v.RH ;
	curvallevel = 0 ;
      } 
      else {
	  
	curval = eqtb [m + curval ].cint ;
	curvallevel = 0 ;
      } 
    } 
    break ;
  case 71 : 
  case 72 : 
  case 86 : 
  case 87 : 
  case 88 : 
  case 101 : 
  case 102 : 
    if ( level != 5 ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 746 ) ;
      } 
      {
	helpptr = 3 ;
	helpline [2 ]= 747 ;
	helpline [1 ]= 748 ;
	helpline [0 ]= 749 ;
      } 
      backerror () ;
      {
	curval = 0 ;
	curvallevel = 1 ;
      } 
    } 
    else if ( curcmd <= 72 ) 
    {
      if ( curcmd < 72 ) {
	  
	if ( m == membot ) 
	{
	  scanregisternum () ;
	  if ( curval < 256 ) 
	  curval = eqtb [27173 + curval ].hh .v.RH ;
	  else {
	      
	    findsaelement ( 5 , curval , false ) ;
	    if ( curptr == -268435455L ) 
	    curval = -268435455L ;
	    else curval = mem [curptr + 1 ].hh .v.RH ;
	  } 
	} 
	else curval = mem [m + 1 ].hh .v.RH ;
      } 
      else curval = eqtb [m ].hh .v.RH ;
      curvallevel = 5 ;
    } 
    else {
	
      backinput () ;
      scanfontident () ;
      {
	curval = 17626 + curval ;
	curvallevel = 4 ;
      } 
    } 
    break ;
  case 73 : 
    {
      curval = eqtb [m ].cint ;
      curvallevel = 0 ;
    } 
    break ;
  case 74 : 
    {
      curval = eqtb [m ].cint ;
      curvallevel = 1 ;
    } 
    break ;
  case 75 : 
    {
      curval = eqtb [m ].hh .v.RH ;
      curvallevel = 2 ;
    } 
    break ;
  case 76 : 
    {
      curval = eqtb [m ].hh .v.RH ;
      curvallevel = 3 ;
    } 
    break ;
  case 79 : 
    if ( abs ( curlist .modefield ) != m ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 776 ) ;
      } 
      printcmdchr ( 79 , m ) ;
      {
	helpptr = 4 ;
	helpline [3 ]= 777 ;
	helpline [2 ]= 778 ;
	helpline [1 ]= 779 ;
	helpline [0 ]= 780 ;
      } 
      error () ;
      if ( level != 5 ) 
      {
	curval = 0 ;
	curvallevel = 1 ;
      } 
      else {
	  
	curval = 0 ;
	curvallevel = 0 ;
      } 
    } 
    else if ( m == 1 ) 
    {
      curval = curlist .auxfield .cint ;
      curvallevel = 1 ;
    } 
    else {
	
      curval = curlist .auxfield .hh .v.LH ;
      curvallevel = 0 ;
    } 
    break ;
  case 80 : 
    if ( curlist .modefield == 0 ) 
    {
      curval = 0 ;
      curvallevel = 0 ;
    } 
    else {
	
      nest [nestptr ]= curlist ;
      p = nestptr ;
      while ( abs ( nest [p ].modefield ) != 1 ) decr ( p ) ;
      {
	curval = nest [p ].pgfield ;
	curvallevel = 0 ;
      } 
    } 
    break ;
  case 82 : 
    {
      if ( m == 0 ) 
      curval = deadcycles ;
      else if ( m == 2 ) 
      curval = interaction ;
      else curval = insertpenalties ;
      curvallevel = 0 ;
    } 
    break ;
  case 81 : 
    {
      if ( ( pagecontents == 0 ) && ( ! outputactive ) ) {
	  
	if ( m == 0 ) 
	curval = 1073741823L ;
	else curval = 0 ;
      } 
      else curval = pagesofar [m ];
      curvallevel = 1 ;
    } 
    break ;
  case 84 : 
    {
      if ( m > 27158 ) 
      {
	scanint () ;
	if ( ( eqtb [m ].hh .v.RH == -268435455L ) || ( curval < 0 ) ) 
	curval = 0 ;
	else {
	    
	  if ( curval > mem [eqtb [m ].hh .v.RH + 1 ].cint ) 
	  curval = mem [eqtb [m ].hh .v.RH + 1 ].cint ;
	  curval = mem [eqtb [m ].hh .v.RH + curval + 1 ].cint ;
	} 
      } 
      else if ( eqtb [27158 ].hh .v.RH == -268435455L ) 
      curval = 0 ;
      else curval = mem [eqtb [27158 ].hh .v.RH ].hh .v.LH ;
      curvallevel = 0 ;
    } 
    break ;
  case 83 : 
    {
      scanregisternum () ;
      if ( curval < 256 ) 
      q = eqtb [27433 + curval ].hh .v.RH ;
      else {
	  
	findsaelement ( 4 , curval , false ) ;
	if ( curptr == -268435455L ) 
	q = -268435455L ;
	else q = mem [curptr + 1 ].hh .v.RH ;
      } 
      if ( q == -268435455L ) 
      curval = 0 ;
      else curval = mem [q + m ].cint ;
      curvallevel = 1 ;
    } 
    break ;
  case 68 : 
  case 69 : 
    {
      curval = curchr ;
      curvallevel = 0 ;
    } 
    break ;
  case 77 : 
    {
      findfontdimen ( false ) ;
      fontinfo [fmemptr ].cint = 0 ;
      {
	curval = fontinfo [curval ].cint ;
	curvallevel = 1 ;
      } 
    } 
    break ;
  case 78 : 
    {
      scanfontident () ;
      if ( m == 0 ) 
      {
	curval = hyphenchar [curval ];
	curvallevel = 0 ;
      } 
      else if ( m == 1 ) 
      {
	curval = skewchar [curval ];
	curvallevel = 0 ;
      } 
      else if ( m == 6 ) 
      {
	curval = testnoligatures ( curval ) ;
	curvallevel = 0 ;
      } 
      else {
	  
	n = curval ;
	scancharnum () ;
	k = curval ;
	switch ( m ) 
	{case 2 : 
	  {
	    curval = getlpcode ( n , k ) ;
	    curvallevel = 0 ;
	  } 
	  break ;
	case 3 : 
	  {
	    curval = getrpcode ( n , k ) ;
	    curvallevel = 0 ;
	  } 
	  break ;
	case 4 : 
	  {
	    curval = getefcode ( n , k ) ;
	    curvallevel = 0 ;
	  } 
	  break ;
	case 5 : 
	  {
	    curval = gettagcode ( n , k ) ;
	    curvallevel = 0 ;
	  } 
	  break ;
	case 7 : 
	  {
	    curval = getknbscode ( n , k ) ;
	    curvallevel = 0 ;
	  } 
	  break ;
	case 8 : 
	  {
	    curval = getstbscode ( n , k ) ;
	    curvallevel = 0 ;
	  } 
	  break ;
	case 9 : 
	  {
	    curval = getshbscode ( n , k ) ;
	    curvallevel = 0 ;
	  } 
	  break ;
	case 10 : 
	  {
	    curval = getknbccode ( n , k ) ;
	    curvallevel = 0 ;
	  } 
	  break ;
	case 11 : 
	  {
	    curval = getknaccode ( n , k ) ;
	    curvallevel = 0 ;
	  } 
	  break ;
	} 
      } 
    } 
    break ;
  case 89 : 
    {
      if ( ( m < membot ) || ( m > membot + 19 ) ) 
      {
	curvallevel = ( mem [m ].hh.b0 / 16 ) ;
	if ( curvallevel < 2 ) 
	curval = mem [m + 2 ].cint ;
	else curval = mem [m + 1 ].hh .v.RH ;
      } 
      else {
	  
	scanregisternum () ;
	curvallevel = m - membot ;
	if ( curval > 255 ) 
	{
	  findsaelement ( curvallevel , curval , false ) ;
	  if ( curptr == -268435455L ) {
	      
	    if ( curvallevel < 2 ) 
	    curval = 0 ;
	    else curval = membot ;
	  } 
	  else if ( curvallevel < 2 ) 
	  curval = mem [curptr + 2 ].cint ;
	  else curval = mem [curptr + 1 ].hh .v.RH ;
	} 
	else switch ( curvallevel ) 
	{case 0 : 
	  curval = eqtb [29375 + curval ].cint ;
	  break ;
	case 1 : 
	  curval = eqtb [29921 + curval ].cint ;
	  break ;
	case 2 : 
	  curval = eqtb [26646 + curval ].hh .v.RH ;
	  break ;
	case 3 : 
	  curval = eqtb [26902 + curval ].hh .v.RH ;
	  break ;
	} 
      } 
    } 
    break ;
  case 70 : 
    if ( m >= 4 ) {
	
      if ( m >= 37 ) 
      {
	if ( m < 38 ) 
	{
	  switch ( m ) 
	  {case 37 : 
	    scanmuglue () ;
	    break ;
	  } 
	  curvallevel = 2 ;
	} 
	else if ( m < 39 ) 
	{
	  switch ( m ) 
	  {case 38 : 
	    scannormalglue () ;
	    break ;
	  } 
	  curvallevel = 3 ;
	} 
	else {
	    
	  curvallevel = m - 39 ;
	  scanexpr () ;
	} 
	while ( curvallevel > level ) {
	    
	  if ( curvallevel == 2 ) 
	  {
	    m = curval ;
	    curval = mem [m + 1 ].cint ;
	    deleteglueref ( m ) ;
	  } 
	  else if ( curvallevel == 3 ) 
	  muerror () ;
	  decr ( curvallevel ) ;
	} 
	if ( negative ) {
	    
	  if ( curvallevel >= 2 ) 
	  {
	    m = curval ;
	    curval = newspec ( m ) ;
	    deleteglueref ( m ) ;
	    {
	      mem [curval + 1 ].cint = - (integer) mem [curval + 1 ].cint 
	      ;
	      mem [curval + 2 ].cint = - (integer) mem [curval + 2 ].cint 
	      ;
	      mem [curval + 3 ].cint = - (integer) mem [curval + 3 ].cint 
	      ;
	    } 
	  } 
	  else curval = - (integer) curval ;
	} 
	return ;
      } 
      else if ( m >= 28 ) 
      {
	switch ( m ) 
	{case 28 : 
	case 29 : 
	case 30 : 
	case 31 : 
	  {
	    scanfontident () ;
	    q = curval ;
	    scancharnum () ;
	    if ( ( fontbc [q ]<= curval ) && ( fontec [q ]>= curval ) ) 
	    {
	      i = fontinfo [charbase [q ]+ effectivechar ( true , q , 
	      curval ) ].qqqq ;
	      switch ( m ) 
	      {case 28 : 
		curval = fontinfo [widthbase [q ]+ i .b0 ].cint ;
		break ;
	      case 29 : 
		curval = fontinfo [heightbase [q ]+ ( i .b1 ) / 16 ].cint 
		;
		break ;
	      case 30 : 
		curval = fontinfo [depthbase [q ]+ ( i .b1 ) % 16 ].cint ;
		break ;
	      case 31 : 
		curval = fontinfo [italicbase [q ]+ ( i .b2 ) / 4 ].cint ;
		break ;
	      } 
	    } 
	    else curval = 0 ;
	  } 
	  break ;
	case 32 : 
	case 33 : 
	case 34 : 
	  {
	    q = curchr - 32 ;
	    scanint () ;
	    if ( ( eqtb [27158 ].hh .v.RH == -268435455L ) || ( curval <= 0 
	    ) ) 
	    curval = 0 ;
	    else {
		
	      if ( q == 2 ) 
	      {
		q = curval % 2 ;
		curval = ( curval + q ) / 2 ;
	      } 
	      if ( curval > mem [eqtb [27158 ].hh .v.RH ].hh .v.LH ) 
	      curval = mem [eqtb [27158 ].hh .v.RH ].hh .v.LH ;
	      curval = mem [eqtb [27158 ].hh .v.RH + 2 * curval - q ].cint 
	      ;
	    } 
	    curvallevel = 1 ;
	  } 
	  break ;
	case 35 : 
	case 36 : 
	  {
	    scannormalglue () ;
	    q = curval ;
	    if ( m == 35 ) 
	    curval = mem [q + 2 ].cint ;
	    else curval = mem [q + 3 ].cint ;
	    deleteglueref ( q ) ;
	  } 
	  break ;
	} 
	curvallevel = 1 ;
      } 
      else {
	  
	switch ( m ) 
	{case 4 : 
	  curval = line ;
	  break ;
	case 5 : 
	  curval = lastbadness ;
	  break ;
	case 6 : 
	  curval = 140 ;
	  break ;
	case 7 : 
	  curval = pdflastobj ;
	  break ;
	case 8 : 
	  curval = pdflastxform ;
	  break ;
	case 9 : 
	  curval = pdflastximage ;
	  break ;
	case 10 : 
	  curval = pdflastximagepages ;
	  break ;
	case 11 : 
	  curval = pdflastannot ;
	  break ;
	case 12 : 
	  curval = pdflastxpos ;
	  break ;
	case 13 : 
	  curval = pdflastypos ;
	  break ;
	case 14 : 
	  curval = pdfretval ;
	  break ;
	case 15 : 
	  curval = pdflastximagecolordepth ;
	  break ;
	case 16 : 
	  curval = getmicrointerval () ;
	  break ;
	case 18 : 
	  curval = randomseed ;
	  break ;
	case 17 : 
	  {
	    if ( shellenabledp ) 
	    {
	      if ( restrictedshell ) 
	      curval = 2 ;
	      else curval = 1 ;
	    } 
	    else curval = 0 ;
	  } 
	  break ;
	case 19 : 
	  curval = pdflastlink ;
	  break ;
	case 20 : 
	  curval = 2 ;
	  break ;
	case 21 : 
	  curval = curlevel - 1 ;
	  break ;
	case 22 : 
	  curval = curgroup ;
	  break ;
	case 23 : 
	  {
	    q = condptr ;
	    curval = 0 ;
	    while ( q != -268435455L ) {
		
	      incr ( curval ) ;
	      q = mem [q ].hh .v.RH ;
	    } 
	  } 
	  break ;
	case 24 : 
	  if ( condptr == -268435455L ) 
	  curval = 0 ;
	  else if ( curif < 32 ) 
	  curval = curif + 1 ;
	  else curval = - (integer) ( curif - 31 ) ;
	  break ;
	case 25 : 
	  if ( ( iflimit == 4 ) || ( iflimit == 3 ) ) 
	  curval = 1 ;
	  else if ( iflimit == 2 ) 
	  curval = -1 ;
	  else curval = 0 ;
	  break ;
	case 26 : 
	case 27 : 
	  {
	    scannormalglue () ;
	    q = curval ;
	    if ( m == 26 ) 
	    curval = mem [q ].hh.b0 ;
	    else curval = mem [q ].hh.b1 ;
	    deleteglueref ( q ) ;
	  } 
	  break ;
	} 
	curvallevel = 0 ;
      } 
    } 
    else {
	
      if ( curchr == 2 ) 
      curval = membot ;
      else curval = 0 ;
      tx = curlist .tailfield ;
      if ( ! ( tx >= himemmin ) ) {
	  
	if ( ( mem [tx ].hh.b0 == 9 ) && ( mem [tx ].hh.b1 == 3 ) ) 
	{
	  r = curlist .headfield ;
	  do {
	      q = r ;
	    r = mem [q ].hh .v.RH ;
	  } while ( ! ( r == tx ) ) ;
	  tx = q ;
	} 
      } 
      if ( curchr == 3 ) 
      {
	curvallevel = 0 ;
	if ( ( tx == curlist .headfield ) || ( curlist .modefield == 0 ) ) 
	curval = -1 ;
      } 
      else curvallevel = curchr ;
      if ( ! ( tx >= himemmin ) && ( curlist .modefield != 0 ) ) 
      switch ( curchr ) 
      {case 0 : 
	if ( mem [tx ].hh.b0 == 12 ) 
	curval = mem [tx + 1 ].cint ;
	break ;
      case 1 : 
	if ( mem [tx ].hh.b0 == 11 ) 
	curval = mem [tx + 1 ].cint ;
	break ;
      case 2 : 
	if ( mem [tx ].hh.b0 == 10 ) 
	{
	  curval = mem [tx + 1 ].hh .v.LH ;
	  if ( mem [tx ].hh.b1 == 99 ) 
	  curvallevel = 3 ;
	} 
	break ;
      case 3 : 
	if ( mem [tx ].hh.b0 <= 13 ) 
	curval = mem [tx ].hh.b0 + 1 ;
	else curval = 15 ;
	break ;
      } 
      else if ( ( curlist .modefield == 1 ) && ( tx == curlist .headfield ) ) 
      switch ( curchr ) 
      {case 0 : 
	curval = lastpenalty ;
	break ;
      case 1 : 
	curval = lastkern ;
	break ;
      case 2 : 
	if ( lastglue != 268435455L ) 
	curval = lastglue ;
	break ;
      case 3 : 
	curval = lastnodetype ;
	break ;
      } 
    } 
    break ;
  case 39 : 
    if ( curchr == 1 ) 
    {
      gettoken () ;
      if ( curcs < 514 ) 
      curcs = primlookup ( curcs - 257 ) ;
      else curcs = primlookup ( hash [curcs ].v.RH ) ;
      if ( curcs != 0 ) 
      {
	curcmd = eqtb [15526 + curcs ].hh.b0 ;
	curchr = eqtb [15526 + curcs ].hh .v.RH ;
	curcs = 15526 + curcs ;
	curtok = 4095 + curcs ;
      } 
      else {
	  
	curcmd = 0 ;
	curchr = 0 ;
	curtok = 19616 ;
	curcs = 15521 ;
      } 
      goto lab20 ;
    } 
    break ;
    default: 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 781 ) ;
      } 
      printcmdchr ( curcmd , curchr ) ;
      print ( 782 ) ;
      printesc ( 612 ) ;
      {
	helpptr = 1 ;
	helpline [0 ]= 780 ;
      } 
      error () ;
      if ( level != 5 ) 
      {
	curval = 0 ;
	curvallevel = 1 ;
      } 
      else {
	  
	curval = 0 ;
	curvallevel = 0 ;
      } 
    } 
    break ;
  } 
  while ( curvallevel > level ) {
      
    if ( curvallevel == 2 ) 
    curval = mem [curval + 1 ].cint ;
    else if ( curvallevel == 3 ) 
    muerror () ;
    decr ( curvallevel ) ;
  } 
  if ( negative ) {
      
    if ( curvallevel >= 2 ) 
    {
      curval = newspec ( curval ) ;
      {
	mem [curval + 1 ].cint = - (integer) mem [curval + 1 ].cint ;
	mem [curval + 2 ].cint = - (integer) mem [curval + 2 ].cint ;
	mem [curval + 3 ].cint = - (integer) mem [curval + 3 ].cint ;
      } 
    } 
    else curval = - (integer) curval ;
  } 
  else if ( ( curvallevel >= 2 ) && ( curvallevel <= 3 ) ) 
  incr ( mem [curval ].hh .v.RH ) ;
} 
void 
scanint ( void ) 
{
  /* 30 20 */ scanint_regmem 
  boolean negative  ;
  integer m  ;
  smallnumber d  ;
  boolean vacuous  ;
  boolean OKsofar  ;
  radix = 0 ;
  OKsofar = true ;
  negative = false ;
  do {
      do { getxtoken () ;
    } while ( ! ( curcmd != 10 ) ) ;
    if ( curtok == 3117 ) 
    {
      negative = ! negative ;
      curtok = 3115 ;
    } 
  } while ( ! ( curtok != 3115 ) ) ;
  lab20: if ( curtok == 3168 ) 
  {
    gettoken () ;
    if ( curtok < 4095 ) 
    {
      curval = curchr ;
      if ( curcmd <= 2 ) {
	  
	if ( curcmd == 2 ) 
	incr ( alignstate ) ;
	else decr ( alignstate ) ;
      } 
    } 
    else if ( curtok < 4352 ) 
    curval = curtok - 4096 ;
    else curval = curtok - 4352 ;
    if ( curval > 255 ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 794 ) ;
      } 
      {
	helpptr = 2 ;
	helpline [1 ]= 795 ;
	helpline [0 ]= 796 ;
      } 
      curval = 48 ;
      backerror () ;
    } 
    else {
	
      getxtoken () ;
      if ( curcmd != 10 ) 
      backinput () ;
    } 
  } 
  else if ( curtok == 19620 ) 
  {
    gettoken () ;
    if ( curcs < 514 ) 
    curcs = primlookup ( curcs - 257 ) ;
    else curcs = primlookup ( hash [curcs ].v.RH ) ;
    if ( curcs != 0 ) 
    {
      curcmd = eqtb [15526 + curcs ].hh.b0 ;
      curchr = eqtb [15526 + curcs ].hh .v.RH ;
      curcs = 15526 + curcs ;
      curtok = 4095 + curcs ;
    } 
    else {
	
      curcmd = 0 ;
      curchr = 0 ;
      curtok = 19616 ;
      curcs = 15521 ;
    } 
    goto lab20 ;
  } 
  else if ( ( curcmd >= 68 ) && ( curcmd <= 89 ) ) 
  scansomethinginternal ( 0 , false ) ;
  else {
      
    radix = 10 ;
    m = 214748364L ;
    if ( curtok == 3111 ) 
    {
      radix = 8 ;
      m = 268435456L ;
      getxtoken () ;
    } 
    else if ( curtok == 3106 ) 
    {
      radix = 16 ;
      m = 134217728L ;
      getxtoken () ;
    } 
    vacuous = true ;
    curval = 0 ;
    while ( true ) {
	
      if ( ( curtok < 3120 + radix ) && ( curtok >= 3120 ) && ( curtok <= 3129 
      ) ) 
      d = curtok - 3120 ;
      else if ( radix == 16 ) {
	  
	if ( ( curtok <= 2886 ) && ( curtok >= 2881 ) ) 
	d = curtok - 2871 ;
	else if ( ( curtok <= 3142 ) && ( curtok >= 3137 ) ) 
	d = curtok - 3127 ;
	else goto lab30 ;
      } 
      else goto lab30 ;
      vacuous = false ;
      if ( ( curval >= m ) && ( ( curval > m ) || ( d > 7 ) || ( radix != 10 ) 
      ) ) 
      {
	if ( OKsofar ) 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 264 ) ;
	    print ( 797 ) ;
	  } 
	  {
	    helpptr = 2 ;
	    helpline [1 ]= 798 ;
	    helpline [0 ]= 799 ;
	  } 
	  error () ;
	  curval = 2147483647L ;
	  OKsofar = false ;
	} 
      } 
      else curval = curval * radix + d ;
      getxtoken () ;
    } 
    lab30: ;
    if ( vacuous ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 746 ) ;
      } 
      {
	helpptr = 3 ;
	helpline [2 ]= 747 ;
	helpline [1 ]= 748 ;
	helpline [0 ]= 749 ;
      } 
      backerror () ;
    } 
    else if ( curcmd != 10 ) 
    backinput () ;
  } 
  if ( negative ) 
  curval = - (integer) curval ;
} 
void 
zscandimen ( boolean mu , boolean inf , boolean shortcut ) 
{
  /* 30 31 32 40 45 88 89 */ scandimen_regmem 
  boolean negative  ;
  integer f  ;
  integer num, denom  ;
  smallnumber k, kk  ;
  halfword p, q  ;
  scaled v  ;
  integer savecurval  ;
  f = 0 ;
  aritherror = false ;
  curorder = 0 ;
  negative = false ;
  if ( ! shortcut ) 
  {
    negative = false ;
    do {
	do { getxtoken () ;
      } while ( ! ( curcmd != 10 ) ) ;
      if ( curtok == 3117 ) 
      {
	negative = ! negative ;
	curtok = 3115 ;
      } 
    } while ( ! ( curtok != 3115 ) ) ;
    if ( ( curcmd >= 68 ) && ( curcmd <= 89 ) ) {
	
      if ( mu ) 
      {
	scansomethinginternal ( 3 , false ) ;
	if ( curvallevel >= 2 ) 
	{
	  v = mem [curval + 1 ].cint ;
	  deleteglueref ( curval ) ;
	  curval = v ;
	} 
	if ( curvallevel == 3 ) 
	goto lab89 ;
	if ( curvallevel != 0 ) 
	muerror () ;
      } 
      else {
	  
	scansomethinginternal ( 1 , false ) ;
	if ( curvallevel == 1 ) 
	goto lab89 ;
      } 
    } 
    else {
	
      backinput () ;
      if ( curtok == 3116 ) 
      curtok = 3118 ;
      if ( curtok != 3118 ) 
      scanint () ;
      else {
	  
	radix = 10 ;
	curval = 0 ;
      } 
      if ( curtok == 3116 ) 
      curtok = 3118 ;
      if ( ( radix == 10 ) && ( curtok == 3118 ) ) 
      {
	k = 0 ;
	p = -268435455L ;
	gettoken () ;
	while ( true ) {
	    
	  getxtoken () ;
	  if ( ( curtok > 3129 ) || ( curtok < 3120 ) ) 
	  goto lab31 ;
	  if ( k < 17 ) 
	  {
	    q = getavail () ;
	    mem [q ].hh .v.RH = p ;
	    mem [q ].hh .v.LH = curtok - 3120 ;
	    p = q ;
	    incr ( k ) ;
	  } 
	} 
	lab31: {
	    register integer for_end; kk = k ;for_end = 1 ; if ( kk >= 
	for_end) do 
	  {
	    dig [kk - 1 ]= mem [p ].hh .v.LH ;
	    q = p ;
	    p = mem [p ].hh .v.RH ;
	    {
	      mem [q ].hh .v.RH = avail ;
	      avail = q ;
	;
#ifdef STAT
	      decr ( dynused ) ;
#endif /* STAT */
	    } 
	  } 
	while ( kk-- > for_end ) ;} 
	f = rounddecimals ( k ) ;
	if ( curcmd != 10 ) 
	backinput () ;
      } 
    } 
  } 
  if ( curval < 0 ) 
  {
    negative = ! negative ;
    curval = - (integer) curval ;
  } 
  if ( inf ) {
      
    if ( scankeyword ( 316 ) ) 
    {
      curorder = 1 ;
      while ( scankeyword ( 108 ) ) {
	  
	if ( curorder == 3 ) 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 264 ) ;
	    print ( 801 ) ;
	  } 
	  print ( 802 ) ;
	  {
	    helpptr = 1 ;
	    helpline [0 ]= 803 ;
	  } 
	  error () ;
	} 
	else incr ( curorder ) ;
      } 
      goto lab88 ;
    } 
  } 
  savecurval = curval ;
  do {
      getxtoken () ;
  } while ( ! ( curcmd != 10 ) ) ;
  if ( ( curcmd < 68 ) || ( curcmd > 89 ) ) 
  backinput () ;
  else {
      
    if ( mu ) 
    {
      scansomethinginternal ( 3 , false ) ;
      if ( curvallevel >= 2 ) 
      {
	v = mem [curval + 1 ].cint ;
	deleteglueref ( curval ) ;
	curval = v ;
      } 
      if ( curvallevel != 3 ) 
      muerror () ;
    } 
    else scansomethinginternal ( 1 , false ) ;
    v = curval ;
    goto lab40 ;
  } 
  if ( mu ) 
  goto lab45 ;
  if ( scankeyword ( 804 ) ) 
  v = ( fontinfo [6 + parambase [eqtb [27689 ].hh .v.RH ]].cint ) ;
  else if ( scankeyword ( 805 ) ) 
  v = ( fontinfo [5 + parambase [eqtb [27689 ].hh .v.RH ]].cint ) ;
  else if ( scankeyword ( 806 ) ) 
  v = eqtb [29920 ].cint ;
  else goto lab45 ;
  {
    getxtoken () ;
    if ( curcmd != 10 ) 
    backinput () ;
  } 
  lab40: curval = multandadd ( savecurval , v , xnoverd ( v , f , 65536L ) , 
  1073741823L ) ;
  goto lab89 ;
  lab45: ;
  if ( mu ) {
      
    if ( scankeyword ( 344 ) ) 
    goto lab88 ;
    else {
	
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 801 ) ;
      } 
      print ( 807 ) ;
      {
	helpptr = 4 ;
	helpline [3 ]= 808 ;
	helpline [2 ]= 809 ;
	helpline [1 ]= 810 ;
	helpline [0 ]= 811 ;
      } 
      error () ;
      goto lab88 ;
    } 
  } 
  if ( scankeyword ( 800 ) ) 
  {
    preparemag () ;
    if ( eqtb [29291 ].cint != 1000 ) 
    {
      curval = xnoverd ( curval , 1000 , eqtb [29291 ].cint ) ;
      f = ( 1000 * f + 65536L * texremainder ) / eqtb [29291 ].cint ;
      curval = curval + ( f / 65536L ) ;
      f = f % 65536L ;
    } 
  } 
  if ( scankeyword ( 312 ) ) 
  goto lab88 ;
  if ( scankeyword ( 812 ) ) 
  {
    num = 7227 ;
    denom = 100 ;
  } 
  else if ( scankeyword ( 813 ) ) 
  {
    num = 12 ;
    denom = 1 ;
  } 
  else if ( scankeyword ( 814 ) ) 
  {
    num = 7227 ;
    denom = 254 ;
  } 
  else if ( scankeyword ( 815 ) ) 
  {
    num = 7227 ;
    denom = 2540 ;
  } 
  else if ( scankeyword ( 816 ) ) 
  {
    num = 7227 ;
    denom = 7200 ;
  } 
  else if ( scankeyword ( 817 ) ) 
  {
    num = 1238 ;
    denom = 1157 ;
  } 
  else if ( scankeyword ( 818 ) ) 
  {
    num = 14856 ;
    denom = 1157 ;
  } 
  else if ( scankeyword ( 819 ) ) 
  {
    num = 685 ;
    denom = 642 ;
  } 
  else if ( scankeyword ( 820 ) ) 
  {
    num = 1370 ;
    denom = 107 ;
  } 
  else if ( scankeyword ( 821 ) ) 
  goto lab30 ;
  else {
      
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 801 ) ;
    } 
    print ( 822 ) ;
    {
      helpptr = 6 ;
      helpline [5 ]= 823 ;
      helpline [4 ]= 824 ;
      helpline [3 ]= 825 ;
      helpline [2 ]= 809 ;
      helpline [1 ]= 810 ;
      helpline [0 ]= 811 ;
    } 
    error () ;
    goto lab32 ;
  } 
  curval = xnoverd ( curval , num , denom ) ;
  f = ( num * f + 65536L * texremainder ) / denom ;
  curval = curval + ( f / 65536L ) ;
  f = f % 65536L ;
  lab32: ;
  lab88: if ( curval >= 16384 ) 
  aritherror = true ;
  else curval = curval * 65536L + f ;
  lab30: ;
  {
    getxtoken () ;
    if ( curcmd != 10 ) 
    backinput () ;
  } 
  lab89: if ( aritherror || ( abs ( curval ) >= 1073741824L ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 826 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 827 ;
      helpline [0 ]= 828 ;
    } 
    error () ;
    curval = 1073741823L ;
    aritherror = false ;
  } 
  if ( negative ) 
  curval = - (integer) curval ;
} 
void 
zscanglue ( smallnumber level ) 
{
  /* 10 */ scanglue_regmem 
  boolean negative  ;
  halfword q  ;
  boolean mu  ;
  mu = ( level == 3 ) ;
  negative = false ;
  do {
      do { getxtoken () ;
    } while ( ! ( curcmd != 10 ) ) ;
    if ( curtok == 3117 ) 
    {
      negative = ! negative ;
      curtok = 3115 ;
    } 
  } while ( ! ( curtok != 3115 ) ) ;
  if ( ( curcmd >= 68 ) && ( curcmd <= 89 ) ) 
  {
    scansomethinginternal ( level , negative ) ;
    if ( curvallevel >= 2 ) 
    {
      if ( curvallevel != level ) 
      muerror () ;
      return ;
    } 
    if ( curvallevel == 0 ) 
    scandimen ( mu , false , true ) ;
    else if ( level == 3 ) 
    muerror () ;
  } 
  else {
      
    backinput () ;
    scandimen ( mu , false , false ) ;
    if ( negative ) 
    curval = - (integer) curval ;
  } 
  q = newspec ( membot ) ;
  mem [q + 1 ].cint = curval ;
  if ( scankeyword ( 829 ) ) 
  {
    scandimen ( mu , true , false ) ;
    mem [q + 2 ].cint = curval ;
    mem [q ].hh.b0 = curorder ;
  } 
  if ( scankeyword ( 830 ) ) 
  {
    scandimen ( mu , true , false ) ;
    mem [q + 3 ].cint = curval ;
    mem [q ].hh.b1 = curorder ;
  } 
  curval = q ;
} 
integer 
zaddorsub ( integer x , integer y , integer maxanswer , boolean negative ) 
{
  register integer Result; addorsub_regmem 
  integer a  ;
  if ( negative ) 
  y = - (integer) y ;
  if ( x >= 0 ) {
      
    if ( y <= maxanswer - x ) 
    a = x + y ;
    else {
	
      aritherror = true ;
      a = 0 ;
    } 
  } 
  else if ( y >= - (integer) maxanswer - x ) 
  a = x + y ;
  else {
      
    aritherror = true ;
    a = 0 ;
  } 
  Result = a ;
  return Result ;
} 
integer 
zquotient ( integer n , integer d ) 
{
  register integer Result; quotient_regmem 
  boolean negative  ;
  integer a  ;
  if ( d == 0 ) 
  {
    aritherror = true ;
    a = 0 ;
  } 
  else {
      
    if ( d > 0 ) 
    negative = false ;
    else {
	
      d = - (integer) d ;
      negative = true ;
    } 
    if ( n < 0 ) 
    {
      n = - (integer) n ;
      negative = ! negative ;
    } 
    a = n / d ;
    n = n - a * d ;
    d = n - d ;
    if ( d + n >= 0 ) 
    incr ( a ) ;
    if ( negative ) 
    a = - (integer) a ;
  } 
  Result = a ;
  return Result ;
} 
integer 
zfract ( integer x , integer n , integer d , integer maxanswer ) 
{
  /* 40 41 88 30 */ register integer Result; fract_regmem 
  boolean negative  ;
  integer a  ;
  integer f  ;
  integer h  ;
  integer r  ;
  integer t  ;
  if ( d == 0 ) 
  goto lab88 ;
  a = 0 ;
  if ( d > 0 ) 
  negative = false ;
  else {
      
    d = - (integer) d ;
    negative = true ;
  } 
  if ( x < 0 ) 
  {
    x = - (integer) x ;
    negative = ! negative ;
  } 
  else if ( x == 0 ) 
  goto lab30 ;
  if ( n < 0 ) 
  {
    n = - (integer) n ;
    negative = ! negative ;
  } 
  t = n / d ;
  if ( t > maxanswer / x ) 
  goto lab88 ;
  a = t * x ;
  n = n - t * d ;
  if ( n == 0 ) 
  goto lab40 ;
  t = x / d ;
  if ( t > ( maxanswer - a ) / n ) 
  goto lab88 ;
  a = a + t * n ;
  x = x - t * d ;
  if ( x == 0 ) 
  goto lab40 ;
  if ( x < n ) 
  {
    t = x ;
    x = n ;
    n = t ;
  } 
  f = 0 ;
  r = ( d / 2 ) - d ;
  h = - (integer) r ;
  while ( true ) {
      
    if ( odd ( n ) ) 
    {
      r = r + x ;
      if ( r >= 0 ) 
      {
	r = r - d ;
	incr ( f ) ;
      } 
    } 
    n = n / 2 ;
    if ( n == 0 ) 
    goto lab41 ;
    if ( x < h ) 
    x = x + x ;
    else {
	
      t = x - d ;
      x = t + x ;
      f = f + n ;
      if ( x < n ) 
      {
	if ( x == 0 ) 
	goto lab41 ;
	t = x ;
	x = n ;
	n = t ;
      } 
    } 
  } 
  lab41: if ( f > ( maxanswer - a ) ) 
  goto lab88 ;
  a = a + f ;
  lab40: if ( negative ) 
  a = - (integer) a ;
  goto lab30 ;
  lab88: {
      
    aritherror = true ;
    a = 0 ;
  } 
  lab30: Result = a ;
  return Result ;
} 
void 
scanexpr ( void ) 
{
  /* 20 22 40 */ scanexpr_regmem 
  boolean a, b  ;
  smallnumber l  ;
  smallnumber r  ;
  smallnumber s  ;
  smallnumber o  ;
  integer e  ;
  integer t  ;
  integer f  ;
  integer n  ;
  halfword p  ;
  halfword q  ;
  l = curvallevel ;
  a = aritherror ;
  b = false ;
  p = -268435455L ;
  lab20: r = 0 ;
  e = 0 ;
  s = 0 ;
  t = 0 ;
  n = 0 ;
  lab22: if ( s == 0 ) 
  o = l ;
  else o = 0 ;
  do {
      getxtoken () ;
  } while ( ! ( curcmd != 10 ) ) ;
  if ( curtok == 3112 ) 
  {
    q = getnode ( 4 ) ;
    mem [q ].hh .v.RH = p ;
    mem [q ].hh.b0 = l ;
    mem [q ].hh.b1 = 4 * s + r ;
    mem [q + 1 ].cint = e ;
    mem [q + 2 ].cint = t ;
    mem [q + 3 ].cint = n ;
    p = q ;
    l = o ;
    goto lab20 ;
  } 
  backinput () ;
  if ( o == 0 ) 
  scanint () ;
  else if ( o == 1 ) 
  scandimen ( false , false , false ) ;
  else if ( o == 2 ) 
  scannormalglue () ;
  else scanmuglue () ;
  f = curval ;
  lab40: do {
      getxtoken () ;
  } while ( ! ( curcmd != 10 ) ) ;
  if ( curtok == 3115 ) 
  o = 1 ;
  else if ( curtok == 3117 ) 
  o = 2 ;
  else if ( curtok == 3114 ) 
  o = 3 ;
  else if ( curtok == 3119 ) 
  o = 4 ;
  else {
      
    o = 0 ;
    if ( p == -268435455L ) 
    {
      if ( curcmd != 0 ) 
      backinput () ;
    } 
    else if ( curtok != 3113 ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 2033 ) ;
      } 
      {
	helpptr = 1 ;
	helpline [0 ]= 2034 ;
      } 
      backerror () ;
    } 
  } 
  aritherror = b ;
  if ( ( l == 0 ) || ( s > 2 ) ) 
  {
    if ( ( f > 2147483647L ) || ( f < -2147483647L ) ) 
    {
      aritherror = true ;
      f = 0 ;
    } 
  } 
  else if ( l == 1 ) 
  {
    if ( abs ( f ) > 1073741823L ) 
    {
      aritherror = true ;
      f = 0 ;
    } 
  } 
  else {
      
    if ( ( abs ( mem [f + 1 ].cint ) > 1073741823L ) || ( abs ( mem [f + 2 
    ].cint ) > 1073741823L ) || ( abs ( mem [f + 3 ].cint ) > 1073741823L ) 
    ) 
    {
      aritherror = true ;
      deleteglueref ( f ) ;
      f = newspec ( membot ) ;
    } 
  } 
  switch ( s ) 
  {case 0 : 
    if ( ( l >= 2 ) && ( o != 0 ) ) 
    {
      t = newspec ( f ) ;
      deleteglueref ( f ) ;
      if ( mem [t + 2 ].cint == 0 ) 
      mem [t ].hh.b0 = 0 ;
      if ( mem [t + 3 ].cint == 0 ) 
      mem [t ].hh.b1 = 0 ;
    } 
    else t = f ;
    break ;
  case 3 : 
    if ( o == 4 ) 
    {
      n = f ;
      o = 5 ;
    } 
    else if ( l == 0 ) 
    t = multandadd ( t , f , 0 , 2147483647L ) ;
    else if ( l == 1 ) 
    t = multandadd ( t , f , 0 , 1073741823L ) ;
    else {
	
      mem [t + 1 ].cint = multandadd ( mem [t + 1 ].cint , f , 0 , 
      1073741823L ) ;
      mem [t + 2 ].cint = multandadd ( mem [t + 2 ].cint , f , 0 , 
      1073741823L ) ;
      mem [t + 3 ].cint = multandadd ( mem [t + 3 ].cint , f , 0 , 
      1073741823L ) ;
    } 
    break ;
  case 4 : 
    if ( l < 2 ) 
    t = quotient ( t , f ) ;
    else {
	
      mem [t + 1 ].cint = quotient ( mem [t + 1 ].cint , f ) ;
      mem [t + 2 ].cint = quotient ( mem [t + 2 ].cint , f ) ;
      mem [t + 3 ].cint = quotient ( mem [t + 3 ].cint , f ) ;
    } 
    break ;
  case 5 : 
    if ( l == 0 ) 
    t = fract ( t , n , f , 2147483647L ) ;
    else if ( l == 1 ) 
    t = fract ( t , n , f , 1073741823L ) ;
    else {
	
      mem [t + 1 ].cint = fract ( mem [t + 1 ].cint , n , f , 1073741823L 
      ) ;
      mem [t + 2 ].cint = fract ( mem [t + 2 ].cint , n , f , 1073741823L 
      ) ;
      mem [t + 3 ].cint = fract ( mem [t + 3 ].cint , n , f , 1073741823L 
      ) ;
    } 
    break ;
  } 
  if ( o > 2 ) 
  s = o ;
  else {
      
    s = 0 ;
    if ( r == 0 ) 
    e = t ;
    else if ( l == 0 ) 
    e = addorsub ( e , t , 2147483647L , r == 2 ) ;
    else if ( l == 1 ) 
    e = addorsub ( e , t , 1073741823L , r == 2 ) ;
    else {
	
      mem [e + 1 ].cint = addorsub ( mem [e + 1 ].cint , mem [t + 1 ]
      .cint , 1073741823L , r == 2 ) ;
      if ( mem [e ].hh.b0 == mem [t ].hh.b0 ) 
      mem [e + 2 ].cint = addorsub ( mem [e + 2 ].cint , mem [t + 2 ]
      .cint , 1073741823L , r == 2 ) ;
      else if ( ( mem [e ].hh.b0 < mem [t ].hh.b0 ) && ( mem [t + 2 ]
      .cint != 0 ) ) 
      {
	mem [e + 2 ].cint = mem [t + 2 ].cint ;
	mem [e ].hh.b0 = mem [t ].hh.b0 ;
      } 
      if ( mem [e ].hh.b1 == mem [t ].hh.b1 ) 
      mem [e + 3 ].cint = addorsub ( mem [e + 3 ].cint , mem [t + 3 ]
      .cint , 1073741823L , r == 2 ) ;
      else if ( ( mem [e ].hh.b1 < mem [t ].hh.b1 ) && ( mem [t + 3 ]
      .cint != 0 ) ) 
      {
	mem [e + 3 ].cint = mem [t + 3 ].cint ;
	mem [e ].hh.b1 = mem [t ].hh.b1 ;
      } 
      deleteglueref ( t ) ;
      if ( mem [e + 2 ].cint == 0 ) 
      mem [e ].hh.b0 = 0 ;
      if ( mem [e + 3 ].cint == 0 ) 
      mem [e ].hh.b1 = 0 ;
    } 
    r = o ;
  } 
  b = aritherror ;
  if ( o != 0 ) 
  goto lab22 ;
  if ( p != -268435455L ) 
  {
    f = e ;
    q = p ;
    e = mem [q + 1 ].cint ;
    t = mem [q + 2 ].cint ;
    n = mem [q + 3 ].cint ;
    s = mem [q ].hh.b1 / 4 ;
    r = mem [q ].hh.b1 % 4 ;
    l = mem [q ].hh.b0 ;
    p = mem [q ].hh .v.RH ;
    freenode ( q , 4 ) ;
    goto lab40 ;
  } 
  if ( b ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 1622 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 2032 ;
      helpline [0 ]= 1624 ;
    } 
    error () ;
    if ( l >= 2 ) 
    {
      deleteglueref ( e ) ;
      e = membot ;
      incr ( mem [e ].hh .v.RH ) ;
    } 
    else e = 0 ;
  } 
  aritherror = a ;
  curval = e ;
  curvallevel = l ;
} 
void 
scannormalglue ( void ) 
{
  scannormalglue_regmem 
  scanglue ( 2 ) ;
} 
void 
scanmuglue ( void ) 
{
  scanmuglue_regmem 
  scanglue ( 3 ) ;
} 
halfword 
scanrulespec ( void ) 
{
  /* 21 */ register halfword Result; scanrulespec_regmem 
  halfword q  ;
  q = newrule () ;
  if ( curcmd == 35 ) 
  mem [q + 1 ].cint = 26214 ;
  else {
      
    mem [q + 3 ].cint = 26214 ;
    mem [q + 2 ].cint = 0 ;
  } 
  lab21: if ( scankeyword ( 831 ) ) 
  {
    scandimen ( false , false , false ) ;
    mem [q + 1 ].cint = curval ;
    goto lab21 ;
  } 
  if ( scankeyword ( 832 ) ) 
  {
    scandimen ( false , false , false ) ;
    mem [q + 3 ].cint = curval ;
    goto lab21 ;
  } 
  if ( scankeyword ( 833 ) ) 
  {
    scandimen ( false , false , false ) ;
    mem [q + 2 ].cint = curval ;
    goto lab21 ;
  } 
  Result = q ;
  return Result ;
} 
void 
scangeneraltext ( void ) 
{
  /* 40 */ scangeneraltext_regmem 
  unsigned char s  ;
  halfword w  ;
  halfword d  ;
  halfword p  ;
  halfword q  ;
  halfword unbalance  ;
  s = scannerstatus ;
  w = warningindex ;
  d = defref ;
  scannerstatus = 5 ;
  warningindex = curcs ;
  defref = getavail () ;
  mem [defref ].hh .v.LH = -268435455L ;
  p = defref ;
  scanleftbrace () ;
  unbalance = 1 ;
  while ( true ) {
      
    gettoken () ;
    if ( curtok < 768 ) {
	
      if ( curcmd < 2 ) 
      incr ( unbalance ) ;
      else {
	  
	decr ( unbalance ) ;
	if ( unbalance == 0 ) 
	goto lab40 ;
      } 
    } 
    {
      q = getavail () ;
      mem [p ].hh .v.RH = q ;
      mem [q ].hh .v.LH = curtok ;
      p = q ;
    } 
  } 
  lab40: q = mem [defref ].hh .v.RH ;
  {
    mem [defref ].hh .v.RH = avail ;
    avail = defref ;
	;
#ifdef STAT
    decr ( dynused ) ;
#endif /* STAT */
  } 
  if ( q == -268435455L ) 
  curval = memtop - 3 ;
  else curval = p ;
  mem [memtop - 3 ].hh .v.RH = q ;
  scannerstatus = s ;
  warningindex = w ;
  defref = d ;
} 
void 
pseudostart ( void ) 
{
  pseudostart_regmem 
  unsigned char oldsetting  ;
  strnumber s  ;
  poolpointer l, m  ;
  halfword p, q, r  ;
  fourquarters w  ;
  integer nl, sz  ;
  scangeneraltext () ;
  oldsetting = selector ;
  selector = 21 ;
  tokenshow ( memtop - 3 ) ;
  selector = oldsetting ;
  flushlist ( mem [memtop - 3 ].hh .v.RH ) ;
  {
    if ( poolptr + 1 > poolsize ) 
    overflow ( 259 , poolsize - initpoolptr ) ;
  } 
  s = makestring () ;
  strpool [poolptr ]= 32 ;
  l = strstart [s ];
  nl = eqtb [29323 ].cint ;
  p = getavail () ;
  q = p ;
  while ( l < poolptr ) {
      
    m = l ;
    while ( ( l < poolptr ) && ( strpool [l ]!= nl ) ) incr ( l ) ;
    sz = ( l - m + 7 ) / 4 ;
    if ( sz == 1 ) 
    sz = 2 ;
    r = getnode ( sz ) ;
    mem [q ].hh .v.RH = r ;
    q = r ;
    mem [q ].hh .v.LH = sz ;
    while ( sz > 2 ) {
	
      decr ( sz ) ;
      incr ( r ) ;
      w .b0 = strpool [m ];
      w .b1 = strpool [m + 1 ];
      w .b2 = strpool [m + 2 ];
      w .b3 = strpool [m + 3 ];
      mem [r ].qqqq = w ;
      m = m + 4 ;
    } 
    w .b0 = 32 ;
    w .b1 = 32 ;
    w .b2 = 32 ;
    w .b3 = 32 ;
    if ( l > m ) 
    {
      w .b0 = strpool [m ];
      if ( l > m + 1 ) 
      {
	w .b1 = strpool [m + 1 ];
	if ( l > m + 2 ) 
	{
	  w .b2 = strpool [m + 2 ];
	  if ( l > m + 3 ) 
	  w .b3 = strpool [m + 3 ];
	} 
      } 
    } 
    mem [r + 1 ].qqqq = w ;
    if ( strpool [l ]== nl ) 
    incr ( l ) ;
  } 
  mem [p ].hh .v.LH = mem [p ].hh .v.RH ;
  mem [p ].hh .v.RH = pseudofiles ;
  pseudofiles = p ;
  {
    decr ( strptr ) ;
    poolptr = strstart [strptr ];
  } 
  beginfilereading () ;
  line = 0 ;
  curinput .limitfield = curinput .startfield ;
  curinput .locfield = curinput .limitfield + 1 ;
  if ( eqtb [29368 ].cint > 0 ) 
  {
    if ( termoffset > maxprintline - 3 ) 
    println () ;
    else if ( ( termoffset > 0 ) || ( fileoffset > 0 ) ) 
    printchar ( 32 ) ;
    curinput .namefield = 19 ;
    print ( 2015 ) ;
    incr ( openparens ) ;
    fflush ( stdout ) ;
  } 
  else curinput .namefield = 18 ;
} 
halfword 
zstrtoks ( poolpointer b ) 
{
  register halfword Result; strtoks_regmem 
  halfword p  ;
  halfword q  ;
  halfword t  ;
  poolpointer k  ;
  {
    if ( poolptr + 1 > poolsize ) 
    overflow ( 259 , poolsize - initpoolptr ) ;
  } 
  p = memtop - 3 ;
  mem [p ].hh .v.RH = -268435455L ;
  k = b ;
  while ( k < poolptr ) {
      
    t = strpool [k ];
    if ( t == 32 ) 
    t = 2592 ;
    else t = 3072 + t ;
    {
      {
	q = avail ;
	if ( q == -268435455L ) 
	q = getavail () ;
	else {
	    
	  avail = mem [q ].hh .v.RH ;
	  mem [q ].hh .v.RH = -268435455L ;
	;
#ifdef STAT
	  incr ( dynused ) ;
#endif /* STAT */
	} 
      } 
      mem [p ].hh .v.RH = q ;
      mem [q ].hh .v.LH = t ;
      p = q ;
    } 
    incr ( k ) ;
  } 
  poolptr = b ;
  Result = p ;
  return Result ;
} 
halfword 
thetoks ( void ) 
{
  /* 10 */ register halfword Result; thetoks_regmem 
  unsigned char oldsetting  ;
  halfword p, q, r  ;
  poolpointer b  ;
  smallnumber c  ;
  if ( odd ( curchr ) ) 
  {
    c = curchr ;
    scangeneraltext () ;
    if ( c == 1 ) 
    Result = curval ;
    else {
	
      oldsetting = selector ;
      selector = 21 ;
      b = poolptr ;
      p = getavail () ;
      mem [p ].hh .v.RH = mem [memtop - 3 ].hh .v.RH ;
      tokenshow ( p ) ;
      flushlist ( p ) ;
      selector = oldsetting ;
      Result = strtoks ( b ) ;
    } 
    return Result ;
  } 
  getxtoken () ;
  scansomethinginternal ( 5 , false ) ;
  if ( curvallevel >= 4 ) 
  {
    p = memtop - 3 ;
    mem [p ].hh .v.RH = -268435455L ;
    if ( curvallevel == 4 ) 
    {
      q = getavail () ;
      mem [p ].hh .v.RH = q ;
      mem [q ].hh .v.LH = 4095 + curval ;
      p = q ;
    } 
    else if ( curval != -268435455L ) 
    {
      r = mem [curval ].hh .v.RH ;
      while ( r != -268435455L ) {
	  
	{
	  {
	    q = avail ;
	    if ( q == -268435455L ) 
	    q = getavail () ;
	    else {
		
	      avail = mem [q ].hh .v.RH ;
	      mem [q ].hh .v.RH = -268435455L ;
	;
#ifdef STAT
	      incr ( dynused ) ;
#endif /* STAT */
	    } 
	  } 
	  mem [p ].hh .v.RH = q ;
	  mem [q ].hh .v.LH = mem [r ].hh .v.LH ;
	  p = q ;
	} 
	r = mem [r ].hh .v.RH ;
      } 
    } 
    Result = p ;
  } 
  else {
      
    oldsetting = selector ;
    selector = 21 ;
    b = poolptr ;
    switch ( curvallevel ) 
    {case 0 : 
      printint ( curval ) ;
      break ;
    case 1 : 
      {
	printscaled ( curval ) ;
	print ( 312 ) ;
      } 
      break ;
    case 2 : 
      {
	printspec ( curval , 312 ) ;
	deleteglueref ( curval ) ;
      } 
      break ;
    case 3 : 
      {
	printspec ( curval , 344 ) ;
	deleteglueref ( curval ) ;
      } 
      break ;
    } 
    selector = oldsetting ;
    Result = strtoks ( b ) ;
  } 
  return Result ;
} 
void 
insthetoks ( void ) 
{
  insthetoks_regmem 
  mem [memtop - 12 ].hh .v.RH = thetoks () ;
  begintokenlist ( mem [memtop - 3 ].hh .v.RH , 4 ) ;
} 
void 
convtoks ( void ) 
{
  /* 10 */ convtoks_regmem 
  unsigned char oldsetting  ;
  halfword p, q  ;
  unsigned char c  ;
  smallnumber savescannerstatus  ;
  halfword savedefref  ;
  halfword savewarningindex  ;
  boolean bool  ;
  integer i  ;
  integer j  ;
  poolpointer b  ;
  strnumber s  ;
  strnumber t  ;
  strnumber u  ;
  c = curchr ;
  u = 0 ;
  switch ( c ) 
  {case 0 : 
  case 1 : 
    scanint () ;
    break ;
  case 2 : 
  case 3 : 
    {
      savescannerstatus = scannerstatus ;
      scannerstatus = 0 ;
      gettoken () ;
      scannerstatus = savescannerstatus ;
    } 
    break ;
  case 4 : 
    scanfontident () ;
    break ;
  case 5 : 
    ;
    break ;
  case 6 : 
    {
      savescannerstatus = scannerstatus ;
      savewarningindex = warningindex ;
      savedefref = defref ;
      if ( strstart [strptr ]< poolptr ) 
      u = makestring () ;
      scanpdfexttoks () ;
      warningindex = savewarningindex ;
      scannerstatus = savescannerstatus ;
      begintokenlist ( mem [defref ].hh .v.RH , 4 ) ;
      defref = savedefref ;
      if ( u != 0 ) 
      {
	decr ( strptr ) ;
	u = 0 ;
      } 
      return ;
    } 
    break ;
  case 7 : 
    ;
    break ;
  case 8 : 
    ;
    break ;
  case 9 : 
  case 10 : 
  case 11 : 
    {
      scanfontident () ;
      if ( curval == 0 ) 
      pdferror ( 590 , 868 ) ;
      if ( c != 11 ) 
      {
	pdfcheckvfcurval () ;
	if ( ! fontused [curval ]) 
	pdfinitfontcurval () ;
      } 
    } 
    break ;
  case 12 : 
    {
      scanint () ;
      if ( curval <= 0 ) 
      pdferror ( 869 , 870 ) ;
    } 
    break ;
  case 16 : 
  case 17 : 
    {
      scanregisternum () ;
      if ( curval < 256 ) 
      p = eqtb [27433 + curval ].hh .v.RH ;
      else {
	  
	findsaelement ( 4 , curval , false ) ;
	if ( curptr == -268435455L ) 
	p = -268435455L ;
	else p = mem [curptr + 1 ].hh .v.RH ;
      } 
      if ( ( p == -268435455L ) || ( mem [p ].hh.b0 != 0 ) ) 
      pdferror ( 871 , 872 ) ;
    } 
    break ;
  case 13 : 
    {
      scanint () ;
      pdfcheckobj ( 7 , curval ) ;
    } 
    break ;
  case 14 : 
    {
      savescannerstatus = scannerstatus ;
      savewarningindex = warningindex ;
      savedefref = defref ;
      if ( strstart [strptr ]< poolptr ) 
      u = makestring () ;
      scanpdfexttoks () ;
      s = tokenstostring ( defref ) ;
      deletetokenref ( defref ) ;
      defref = savedefref ;
      warningindex = savewarningindex ;
      scannerstatus = savescannerstatus ;
      b = poolptr ;
      escapestring ( strstart [s ]) ;
      mem [memtop - 12 ].hh .v.RH = strtoks ( b ) ;
      flushstr ( s ) ;
      begintokenlist ( mem [memtop - 3 ].hh .v.RH , 4 ) ;
      if ( u != 0 ) 
      {
	decr ( strptr ) ;
	u = 0 ;
      } 
      return ;
    } 
    break ;
  case 15 : 
    {
      savescannerstatus = scannerstatus ;
      savewarningindex = warningindex ;
      savedefref = defref ;
      if ( strstart [strptr ]< poolptr ) 
      u = makestring () ;
      scanpdfexttoks () ;
      s = tokenstostring ( defref ) ;
      deletetokenref ( defref ) ;
      defref = savedefref ;
      warningindex = savewarningindex ;
      scannerstatus = savescannerstatus ;
      b = poolptr ;
      escapename ( strstart [s ]) ;
      mem [memtop - 12 ].hh .v.RH = strtoks ( b ) ;
      flushstr ( s ) ;
      begintokenlist ( mem [memtop - 3 ].hh .v.RH , 4 ) ;
      if ( u != 0 ) 
      {
	decr ( strptr ) ;
	u = 0 ;
      } 
      return ;
    } 
    break ;
  case 20 : 
    {
      savescannerstatus = scannerstatus ;
      savewarningindex = warningindex ;
      savedefref = defref ;
      if ( strstart [strptr ]< poolptr ) 
      u = makestring () ;
      scanpdfexttoks () ;
      s = tokenstostring ( defref ) ;
      deletetokenref ( defref ) ;
      defref = savedefref ;
      warningindex = savewarningindex ;
      scannerstatus = savescannerstatus ;
      b = poolptr ;
      escapehex ( strstart [s ]) ;
      mem [memtop - 12 ].hh .v.RH = strtoks ( b ) ;
      flushstr ( s ) ;
      begintokenlist ( mem [memtop - 3 ].hh .v.RH , 4 ) ;
      if ( u != 0 ) 
      {
	decr ( strptr ) ;
	u = 0 ;
      } 
      return ;
    } 
    break ;
  case 21 : 
    {
      savescannerstatus = scannerstatus ;
      savewarningindex = warningindex ;
      savedefref = defref ;
      if ( strstart [strptr ]< poolptr ) 
      u = makestring () ;
      scanpdfexttoks () ;
      s = tokenstostring ( defref ) ;
      deletetokenref ( defref ) ;
      defref = savedefref ;
      warningindex = savewarningindex ;
      scannerstatus = savescannerstatus ;
      b = poolptr ;
      unescapehex ( strstart [s ]) ;
      mem [memtop - 12 ].hh .v.RH = strtoks ( b ) ;
      flushstr ( s ) ;
      begintokenlist ( mem [memtop - 3 ].hh .v.RH , 4 ) ;
      if ( u != 0 ) 
      {
	decr ( strptr ) ;
	u = 0 ;
      } 
      return ;
    } 
    break ;
  case 22 : 
    {
      b = poolptr ;
      getcreationdate () ;
      mem [memtop - 12 ].hh .v.RH = strtoks ( b ) ;
      begintokenlist ( mem [memtop - 3 ].hh .v.RH , 4 ) ;
      return ;
    } 
    break ;
  case 23 : 
    {
      savescannerstatus = scannerstatus ;
      savewarningindex = warningindex ;
      savedefref = defref ;
      if ( strstart [strptr ]< poolptr ) 
      u = makestring () ;
      scanpdfexttoks () ;
      s = tokenstostring ( defref ) ;
      deletetokenref ( defref ) ;
      defref = savedefref ;
      warningindex = savewarningindex ;
      scannerstatus = savescannerstatus ;
      b = poolptr ;
      getfilemoddate ( s ) ;
      mem [memtop - 12 ].hh .v.RH = strtoks ( b ) ;
      flushstr ( s ) ;
      begintokenlist ( mem [memtop - 3 ].hh .v.RH , 4 ) ;
      if ( u != 0 ) 
      {
	decr ( strptr ) ;
	u = 0 ;
      } 
      return ;
    } 
    break ;
  case 24 : 
    {
      savescannerstatus = scannerstatus ;
      savewarningindex = warningindex ;
      savedefref = defref ;
      if ( strstart [strptr ]< poolptr ) 
      u = makestring () ;
      scanpdfexttoks () ;
      s = tokenstostring ( defref ) ;
      deletetokenref ( defref ) ;
      defref = savedefref ;
      warningindex = savewarningindex ;
      scannerstatus = savescannerstatus ;
      b = poolptr ;
      getfilesize ( s ) ;
      mem [memtop - 12 ].hh .v.RH = strtoks ( b ) ;
      flushstr ( s ) ;
      begintokenlist ( mem [memtop - 3 ].hh .v.RH , 4 ) ;
      if ( u != 0 ) 
      {
	decr ( strptr ) ;
	u = 0 ;
      } 
      return ;
    } 
    break ;
  case 25 : 
    {
      savescannerstatus = scannerstatus ;
      savewarningindex = warningindex ;
      savedefref = defref ;
      if ( strstart [strptr ]< poolptr ) 
      u = makestring () ;
      bool = scankeyword ( 873 ) ;
      scanpdfexttoks () ;
      s = tokenstostring ( defref ) ;
      deletetokenref ( defref ) ;
      defref = savedefref ;
      warningindex = savewarningindex ;
      scannerstatus = savescannerstatus ;
      b = poolptr ;
      getmd5sum ( s , bool ) ;
      mem [memtop - 12 ].hh .v.RH = strtoks ( b ) ;
      flushstr ( s ) ;
      begintokenlist ( mem [memtop - 3 ].hh .v.RH , 4 ) ;
      if ( u != 0 ) 
      {
	decr ( strptr ) ;
	u = 0 ;
      } 
      return ;
    } 
    break ;
  case 26 : 
    {
      savescannerstatus = scannerstatus ;
      savewarningindex = warningindex ;
      savedefref = defref ;
      if ( strstart [strptr ]< poolptr ) 
      u = makestring () ;
      curval = 0 ;
      if ( ( scankeyword ( 874 ) ) ) 
      {
	scanint () ;
	if ( ( curval < 0 ) ) 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 264 ) ;
	    print ( 875 ) ;
	  } 
	  {
	    helpptr = 2 ;
	    helpline [1 ]= 876 ;
	    helpline [0 ]= 785 ;
	  } 
	  interror ( curval ) ;
	  curval = 0 ;
	} 
      } 
      i = curval ;
      curval = 0 ;
      if ( ( scankeyword ( 877 ) ) ) 
      {
	scanint () ;
	if ( ( curval < 0 ) ) 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 264 ) ;
	    print ( 878 ) ;
	  } 
	  {
	    helpptr = 2 ;
	    helpline [1 ]= 879 ;
	    helpline [0 ]= 785 ;
	  } 
	  interror ( curval ) ;
	  curval = 0 ;
	} 
      } 
      j = curval ;
      scanpdfexttoks () ;
      s = tokenstostring ( defref ) ;
      deletetokenref ( defref ) ;
      defref = savedefref ;
      warningindex = savewarningindex ;
      scannerstatus = savescannerstatus ;
      b = poolptr ;
      getfiledump ( s , i , j ) ;
      mem [memtop - 12 ].hh .v.RH = strtoks ( b ) ;
      flushstr ( s ) ;
      begintokenlist ( mem [memtop - 3 ].hh .v.RH , 4 ) ;
      if ( u != 0 ) 
      {
	decr ( strptr ) ;
	u = 0 ;
      } 
      return ;
    } 
    break ;
  case 27 : 
    {
      savescannerstatus = scannerstatus ;
      savewarningindex = warningindex ;
      savedefref = defref ;
      if ( strstart [strptr ]< poolptr ) 
      u = makestring () ;
      bool = scankeyword ( 880 ) ;
      i = -1 ;
      if ( scankeyword ( 881 ) ) 
      {
	scanint () ;
	i = curval ;
      } 
      scanpdfexttoks () ;
      s = tokenstostring ( defref ) ;
      deletetokenref ( defref ) ;
      scanpdfexttoks () ;
      t = tokenstostring ( defref ) ;
      deletetokenref ( defref ) ;
      defref = savedefref ;
      warningindex = savewarningindex ;
      scannerstatus = savescannerstatus ;
      b = poolptr ;
      matchstrings ( s , t , i , bool ) ;
      mem [memtop - 12 ].hh .v.RH = strtoks ( b ) ;
      flushstr ( t ) ;
      flushstr ( s ) ;
      begintokenlist ( mem [memtop - 3 ].hh .v.RH , 4 ) ;
      if ( u != 0 ) 
      {
	decr ( strptr ) ;
	u = 0 ;
      } 
      return ;
    } 
    break ;
  case 28 : 
    {
      scanint () ;
      if ( curval < 0 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 882 ) ;
	} 
	{
	  helpptr = 2 ;
	  helpline [1 ]= 883 ;
	  helpline [0 ]= 785 ;
	} 
	interror ( curval ) ;
	curval = 0 ;
      } 
      b = poolptr ;
      getmatch ( curval ) ;
      mem [memtop - 12 ].hh .v.RH = strtoks ( b ) ;
      begintokenlist ( mem [memtop - 3 ].hh .v.RH , 4 ) ;
      return ;
    } 
    break ;
  case 18 : 
    {
      savescannerstatus = scannerstatus ;
      savewarningindex = warningindex ;
      savedefref = defref ;
      if ( strstart [strptr ]< poolptr ) 
      u = makestring () ;
      comparestrings () ;
      defref = savedefref ;
      warningindex = savewarningindex ;
      scannerstatus = savescannerstatus ;
      if ( u != 0 ) 
      {
	decr ( strptr ) ;
	u = 0 ;
      } 
    } 
    break ;
  case 19 : 
    {
      bool = scankeyword ( 884 ) ;
      if ( scankeyword ( 885 ) ) 
      curval = 2 ;
      else if ( scankeyword ( 884 ) ) 
      curval = 1 ;
      else curval = 0 ;
      savescannerstatus = scannerstatus ;
      savewarningindex = warningindex ;
      savedefref = defref ;
      if ( strstart [strptr ]< poolptr ) 
      u = makestring () ;
      scanpdfexttoks () ;
      s = tokenstostring ( defref ) ;
      deletetokenref ( defref ) ;
      defref = savedefref ;
      warningindex = savewarningindex ;
      scannerstatus = savescannerstatus ;
      curval = newcolorstack ( s , curval , bool ) ;
      flushstr ( s ) ;
      curvallevel = 0 ;
      if ( curval < 0 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 886 ) ;
	} 
	{
	  helpptr = 2 ;
	  helpline [1 ]= 887 ;
	  helpline [0 ]= 888 ;
	} 
	error () ;
	curval = 0 ;
	if ( u != 0 ) 
	{
	  decr ( strptr ) ;
	  u = 0 ;
	} 
      } 
    } 
    break ;
  case 33 : 
    if ( jobname == 0 ) 
    openlogfile () ;
    break ;
  case 29 : 
    scanint () ;
    break ;
  case 30 : 
    ;
    break ;
  case 31 : 
    scanregisternum () ;
    break ;
  case 32 : 
    {
      scanint () ;
      pdfcheckobj ( 8 , curval ) ;
      i = pdfmem [objtab [curval ].int4 + 4 ];
      scanint () ;
      j = curval ;
      if ( ( j < 1 ) || ( j > 4 ) ) 
      pdferror ( 866 , 889 ) ;
    } 
    break ;
  } 
  oldsetting = selector ;
  selector = 21 ;
  b = poolptr ;
  switch ( c ) 
  {case 0 : 
    printint ( curval ) ;
    break ;
  case 1 : 
    printromanint ( curval ) ;
    break ;
  case 2 : 
    if ( curcs != 0 ) 
    sprintcs ( curcs ) ;
    else printchar ( curchr ) ;
    break ;
  case 3 : 
    printmeaning () ;
    break ;
  case 4 : 
    {
      print ( fontname [curval ]) ;
      if ( fontsize [curval ]!= fontdsize [curval ]) 
      {
	print ( 890 ) ;
	printscaled ( fontsize [curval ]) ;
	print ( 312 ) ;
      } 
    } 
    break ;
  case 5 : 
    print ( 256 ) ;
    break ;
  case 7 : 
    print ( 257 ) ;
    break ;
  case 8 : 
    print ( pdftexbanner ) ;
    break ;
  case 9 : 
  case 10 : 
    {
      {
	if ( pdffontnum [curval ]< 0 ) 
	ff = - (integer) pdffontnum [curval ];
	else ff = curval ;
      } 
      if ( c == 9 ) 
      printint ( objtab [pdffontnum [ff ]].int0 ) ;
      else printint ( pdffontnum [ff ]) ;
    } 
    break ;
  case 11 : 
    {
      printscaled ( fontsize [curval ]) ;
      print ( 312 ) ;
    } 
    break ;
  case 12 : 
    printint ( getobj ( 1 , curval , false ) ) ;
    break ;
  case 16 : 
    {
      p = mem [p + 5 ].hh .v.RH ;
      while ( ( p != -268435455L ) && ( ( ! ( p >= himemmin ) && ( ( mem [p ]
      .hh.b0 == 3 ) || ( mem [p ].hh.b0 == 4 ) || ( mem [p ].hh.b0 == 5 ) 
      || ( mem [p ].hh.b0 == 12 ) || ( ( mem [p ].hh.b0 == 8 ) && ( mem [
      p ].hh.b1 != 12 ) && ( mem [p ].hh.b1 != 10 ) ) || ( ( mem [p ]
      .hh.b0 == 7 ) && ( mem [p + 1 ].hh .v.LH == -268435455L ) && ( mem [p 
      + 1 ].hh .v.RH == -268435455L ) && ( mem [p ].hh.b1 == 0 ) ) || ( ( 
      mem [p ].hh.b0 == 9 ) && ( mem [p + 1 ].cint == 0 ) ) || ( ( mem [p 
      ].hh.b0 == 11 ) && ( ( mem [p + 1 ].cint == 0 ) || ( mem [p ].hh.b1 
      == 0 ) ) ) || ( ( mem [p ].hh.b0 == 10 ) && ( mem [p + 1 ].hh .v.LH 
      == membot ) ) || ( ( mem [p ].hh.b0 == 0 ) && ( mem [p + 1 ].cint == 
      0 ) && ( mem [p + 3 ].cint == 0 ) && ( mem [p + 2 ].cint == 0 ) && ( 
      mem [p + 5 ].hh .v.RH == -268435455L ) ) ) ) || ( ( ! ( p >= himemmin 
      ) ) && ( mem [p ].hh.b0 == 10 ) && ( mem [p ].hh.b1 == 8 ) ) ) ) p = 
      mem [p ].hh .v.RH ;
      if ( ( p != -268435455L ) && ( ! ( p >= himemmin ) ) && ( mem [p ]
      .hh.b0 == 40 ) && ( mem [p ].hh.b1 == 0 ) ) 
      printscaled ( mem [p + 1 ].cint ) ;
      else print ( 48 ) ;
      print ( 312 ) ;
    } 
    break ;
  case 17 : 
    {
      q = mem [p + 5 ].hh .v.RH ;
      p = prevrightmost ( q , -268435455L ) ;
      while ( ( p != -268435455L ) && ( ( ! ( p >= himemmin ) && ( ( mem [p ]
      .hh.b0 == 3 ) || ( mem [p ].hh.b0 == 4 ) || ( mem [p ].hh.b0 == 5 ) 
      || ( mem [p ].hh.b0 == 12 ) || ( ( mem [p ].hh.b0 == 8 ) && ( mem [
      p ].hh.b1 != 12 ) && ( mem [p ].hh.b1 != 10 ) ) || ( ( mem [p ]
      .hh.b0 == 7 ) && ( mem [p + 1 ].hh .v.LH == -268435455L ) && ( mem [p 
      + 1 ].hh .v.RH == -268435455L ) && ( mem [p ].hh.b1 == 0 ) ) || ( ( 
      mem [p ].hh.b0 == 9 ) && ( mem [p + 1 ].cint == 0 ) ) || ( ( mem [p 
      ].hh.b0 == 11 ) && ( ( mem [p + 1 ].cint == 0 ) || ( mem [p ].hh.b1 
      == 0 ) ) ) || ( ( mem [p ].hh.b0 == 10 ) && ( mem [p + 1 ].hh .v.LH 
      == membot ) ) || ( ( mem [p ].hh.b0 == 0 ) && ( mem [p + 1 ].cint == 
      0 ) && ( mem [p + 3 ].cint == 0 ) && ( mem [p + 2 ].cint == 0 ) && ( 
      mem [p + 5 ].hh .v.RH == -268435455L ) ) ) ) || ( ( ! ( p >= himemmin 
      ) ) && ( mem [p ].hh.b0 == 10 ) && ( mem [p ].hh.b1 == 9 ) ) ) ) p = 
      prevrightmost ( q , p ) ;
      if ( ( p != -268435455L ) && ( ! ( p >= himemmin ) ) && ( mem [p ]
      .hh.b0 == 40 ) && ( mem [p ].hh.b1 == 1 ) ) 
      printscaled ( mem [p + 1 ].cint ) ;
      else print ( 48 ) ;
      print ( 312 ) ;
    } 
    break ;
  case 13 : 
    printint ( objtab [curval ].int0 ) ;
    break ;
  case 18 : 
    printint ( curval ) ;
    break ;
  case 19 : 
    printint ( curval ) ;
    break ;
  case 29 : 
    printint ( unifrand ( curval ) ) ;
    break ;
  case 30 : 
    printint ( normrand () ) ;
    break ;
  case 31 : 
    {
      i = curval ;
      p = memtop ;
      while ( i >= mem [mem [p ].hh .v.RH ].hh.b1 ) p = mem [p ].hh 
      .v.RH ;
      if ( mem [p ].hh.b1 == i ) 
      printscaled ( mem [p + 3 ].cint ) ;
      else print ( 48 ) ;
      print ( 312 ) ;
    } 
    break ;
  case 32 : 
    {
      if ( ispdfimage ( i ) ) 
      {
	switch ( j ) 
	{case 1 : 
	  printscaled ( epdforigx ( i ) ) ;
	  break ;
	case 2 : 
	  printscaled ( epdforigy ( i ) ) ;
	  break ;
	case 3 : 
	  printscaled ( epdforigx ( i ) + imagewidth ( i ) ) ;
	  break ;
	case 4 : 
	  printscaled ( epdforigy ( i ) + imageheight ( i ) ) ;
	  break ;
	} 
      } 
      else printscaled ( 0 ) ;
      print ( 312 ) ;
    } 
    break ;
  case 33 : 
    print ( jobname ) ;
    break ;
  } 
  selector = oldsetting ;
  mem [memtop - 12 ].hh .v.RH = strtoks ( b ) ;
  begintokenlist ( mem [memtop - 3 ].hh .v.RH , 4 ) ;
} 
halfword 
zscantoks ( boolean macrodef , boolean xpand ) 
{
  /* 40 30 31 32 */ register halfword Result; scantoks_regmem 
  halfword t  ;
  halfword s  ;
  halfword p  ;
  halfword q  ;
  halfword unbalance  ;
  halfword hashbrace  ;
  if ( macrodef ) 
  scannerstatus = 2 ;
  else scannerstatus = 5 ;
  warningindex = curcs ;
  defref = getavail () ;
  mem [defref ].hh .v.LH = -268435455L ;
  p = defref ;
  hashbrace = 0 ;
  t = 3120 ;
  if ( macrodef ) 
  {
    while ( true ) {
	
      gettoken () ;
      if ( curtok < 768 ) 
      goto lab31 ;
      if ( curcmd == 6 ) 
      {
	s = 3328 + curchr ;
	gettoken () ;
	if ( curcmd == 1 ) 
	{
	  hashbrace = curtok ;
	  {
	    q = getavail () ;
	    mem [p ].hh .v.RH = q ;
	    mem [q ].hh .v.LH = curtok ;
	    p = q ;
	  } 
	  {
	    q = getavail () ;
	    mem [p ].hh .v.RH = q ;
	    mem [q ].hh .v.LH = 3584 ;
	    p = q ;
	  } 
	  goto lab30 ;
	} 
	if ( t == 3129 ) 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 264 ) ;
	    print ( 893 ) ;
	  } 
	  {
	    helpptr = 1 ;
	    helpline [0 ]= 894 ;
	  } 
	  error () ;
	} 
	else {
	    
	  incr ( t ) ;
	  if ( curtok != t ) 
	  {
	    {
	      if ( interaction == 3 ) 
	      ;
	      if ( filelineerrorstylep ) 
	      printfileline () ;
	      else printnl ( 264 ) ;
	      print ( 895 ) ;
	    } 
	    {
	      helpptr = 2 ;
	      helpline [1 ]= 896 ;
	      helpline [0 ]= 897 ;
	    } 
	    backerror () ;
	  } 
	  curtok = s ;
	} 
      } 
      {
	q = getavail () ;
	mem [p ].hh .v.RH = q ;
	mem [q ].hh .v.LH = curtok ;
	p = q ;
      } 
    } 
    lab31: {
	
      q = getavail () ;
      mem [p ].hh .v.RH = q ;
      mem [q ].hh .v.LH = 3584 ;
      p = q ;
    } 
    if ( curcmd == 2 ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 739 ) ;
      } 
      incr ( alignstate ) ;
      {
	helpptr = 2 ;
	helpline [1 ]= 891 ;
	helpline [0 ]= 892 ;
      } 
      error () ;
      goto lab40 ;
    } 
    lab30: ;
  } 
  else scanleftbrace () ;
  unbalance = 1 ;
  while ( true ) {
      
    if ( xpand ) 
    {
      while ( true ) {
	  
	getnext () ;
	if ( curcmd >= 113 ) {
	    
	  if ( mem [mem [curchr ].hh .v.RH ].hh .v.LH == 3585 ) 
	  {
	    curcmd = 0 ;
	    curchr = 257 ;
	  } 
	} 
	if ( curcmd <= 102 ) 
	goto lab32 ;
	if ( curcmd != 111 ) 
	expand () ;
	else {
	    
	  q = thetoks () ;
	  if ( mem [memtop - 3 ].hh .v.RH != -268435455L ) 
	  {
	    mem [p ].hh .v.RH = mem [memtop - 3 ].hh .v.RH ;
	    p = q ;
	  } 
	} 
      } 
      lab32: xtoken () ;
    } 
    else gettoken () ;
    if ( curtok < 768 ) {
	
      if ( curcmd < 2 ) 
      incr ( unbalance ) ;
      else {
	  
	decr ( unbalance ) ;
	if ( unbalance == 0 ) 
	goto lab40 ;
      } 
    } 
    else if ( curcmd == 6 ) {
	
      if ( macrodef ) 
      {
	s = curtok ;
	if ( xpand ) 
	getxtoken () ;
	else gettoken () ;
	if ( curcmd != 6 ) {
	    
	  if ( ( curtok <= 3120 ) || ( curtok > t ) ) 
	  {
	    {
	      if ( interaction == 3 ) 
	      ;
	      if ( filelineerrorstylep ) 
	      printfileline () ;
	      else printnl ( 264 ) ;
	      print ( 898 ) ;
	    } 
	    sprintcs ( warningindex ) ;
	    {
	      helpptr = 3 ;
	      helpline [2 ]= 899 ;
	      helpline [1 ]= 900 ;
	      helpline [0 ]= 901 ;
	    } 
	    backerror () ;
	    curtok = s ;
	  } 
	  else curtok = 1232 + curchr ;
	} 
      } 
    } 
    {
      q = getavail () ;
      mem [p ].hh .v.RH = q ;
      mem [q ].hh .v.LH = curtok ;
      p = q ;
    } 
  } 
  lab40: scannerstatus = 0 ;
  if ( hashbrace != 0 ) 
  {
    q = getavail () ;
    mem [p ].hh .v.RH = q ;
    mem [q ].hh .v.LH = hashbrace ;
    p = q ;
  } 
  Result = p ;
  return Result ;
} 
void 
zreadtoks ( integer n , halfword r , halfword j ) 
{
  /* 30 */ readtoks_regmem 
  halfword p  ;
  halfword q  ;
  integer s  ;
  smallnumber m  ;
  scannerstatus = 2 ;
  warningindex = r ;
  defref = getavail () ;
  mem [defref ].hh .v.LH = -268435455L ;
  p = defref ;
  {
    q = getavail () ;
    mem [p ].hh .v.RH = q ;
    mem [q ].hh .v.LH = 3584 ;
    p = q ;
  } 
  if ( ( n < 0 ) || ( n > 15 ) ) 
  m = 16 ;
  else m = n ;
  s = alignstate ;
  alignstate = 1000000L ;
  do {
      beginfilereading () ;
    curinput .namefield = m + 1 ;
    if ( readopen [m ]== 2 ) {
	
      if ( interaction > 1 ) {
	  
	if ( n < 0 ) 
	{
	  ;
	  print ( 345 ) ;
	  terminput () ;
	} 
	else {
	    
	  ;
	  println () ;
	  sprintcs ( r ) ;
	  {
	    ;
	    print ( 61 ) ;
	    terminput () ;
	  } 
	  n = -1 ;
	} 
      } 
      else fatalerror ( 902 ) ;
    } 
    else if ( readopen [m ]== 1 ) {
	
      if ( inputln ( readfile [m ], false ) ) 
      readopen [m ]= 0 ;
      else {
	  
	aclose ( readfile [m ]) ;
	readopen [m ]= 2 ;
      } 
    } 
    else {
	
      if ( ! inputln ( readfile [m ], true ) ) 
      {
	aclose ( readfile [m ]) ;
	readopen [m ]= 2 ;
	if ( alignstate != 1000000L ) 
	{
	  runaway () ;
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 264 ) ;
	    print ( 903 ) ;
	  } 
	  printesc ( 609 ) ;
	  {
	    helpptr = 1 ;
	    helpline [0 ]= 904 ;
	  } 
	  alignstate = 1000000L ;
	  error () ;
	} 
      } 
    } 
    curinput .limitfield = last ;
    if ( ( eqtb [29322 ].cint < 0 ) || ( eqtb [29322 ].cint > 255 ) ) 
    decr ( curinput .limitfield ) ;
    else buffer [curinput .limitfield ]= eqtb [29322 ].cint ;
    first = curinput .limitfield + 1 ;
    curinput .locfield = curinput .startfield ;
    curinput .statefield = 33 ;
    if ( j == 1 ) 
    {
      while ( curinput .locfield <= curinput .limitfield ) {
	  
	curchr = buffer [curinput .locfield ];
	incr ( curinput .locfield ) ;
	if ( curchr == 32 ) 
	curtok = 2592 ;
	else curtok = curchr + 3072 ;
	{
	  q = getavail () ;
	  mem [p ].hh .v.RH = q ;
	  mem [q ].hh .v.LH = curtok ;
	  p = q ;
	} 
      } 
      goto lab30 ;
    } 
    while ( true ) {
	
      gettoken () ;
      if ( curtok == 0 ) 
      goto lab30 ;
      if ( alignstate < 1000000L ) 
      {
	do {
	    gettoken () ;
	} while ( ! ( curtok == 0 ) ) ;
	alignstate = 1000000L ;
	goto lab30 ;
      } 
      {
	q = getavail () ;
	mem [p ].hh .v.RH = q ;
	mem [q ].hh .v.LH = curtok ;
	p = q ;
      } 
    } 
    lab30: endfilereading () ;
  } while ( ! ( alignstate == 1000000L ) ) ;
  curval = defref ;
  scannerstatus = 0 ;
  alignstate = s ;
} 
void 
passtext ( void ) 
{
  /* 30 */ passtext_regmem 
  integer l  ;
  smallnumber savescannerstatus  ;
  savescannerstatus = scannerstatus ;
  scannerstatus = 1 ;
  l = 0 ;
  skipline = line ;
  while ( true ) {
      
    getnext () ;
    if ( curcmd == 108 ) 
    {
      if ( l == 0 ) 
      goto lab30 ;
      if ( curchr == 2 ) 
      decr ( l ) ;
    } 
    else if ( curcmd == 107 ) 
    incr ( l ) ;
  } 
  lab30: scannerstatus = savescannerstatus ;
  if ( eqtb [29367 ].cint > 0 ) 
  showcurcmdchr () ;
} 
void 
zchangeiflimit ( smallnumber l , halfword p ) 
{
  /* 10 */ changeiflimit_regmem 
  halfword q  ;
  if ( p == condptr ) 
  iflimit = l ;
  else {
      
    q = condptr ;
    while ( true ) {
	
      if ( q == -268435455L ) 
      confusion ( 905 ) ;
      if ( mem [q ].hh .v.RH == p ) 
      {
	mem [q ].hh.b0 = l ;
	return ;
      } 
      q = mem [q ].hh .v.RH ;
    } 
  } 
} 
void 
conditional ( void ) 
{
  /* 10 50 */ conditional_regmem 
  boolean b  ;
  boolean e  ;
  unsigned char r  ;
  integer m, n  ;
  halfword p, q  ;
  smallnumber savescannerstatus  ;
  halfword savecondptr  ;
  smallnumber thisif  ;
  boolean isunless  ;
  if ( eqtb [29367 ].cint > 0 ) {
      
    if ( eqtb [29310 ].cint <= 1 ) 
    showcurcmdchr () ;
  } 
  {
    p = getnode ( 2 ) ;
    mem [p ].hh .v.RH = condptr ;
    mem [p ].hh.b0 = iflimit ;
    mem [p ].hh.b1 = curif ;
    mem [p + 1 ].cint = ifline ;
    condptr = p ;
    curif = curchr ;
    iflimit = 1 ;
    ifline = line ;
  } 
  savecondptr = condptr ;
  isunless = ( curchr >= 32 ) ;
  thisif = curchr % 32 ;
  switch ( thisif ) 
  {case 0 : 
  case 1 : 
    {
      {
	getxtoken () ;
	if ( curcmd == 0 ) {
	    
	  if ( curchr == 257 ) 
	  {
	    curcmd = 13 ;
	    curchr = curtok - 4096 ;
	  } 
	} 
      } 
      if ( ( curcmd > 13 ) || ( curchr > 255 ) ) 
      {
	m = 0 ;
	n = 256 ;
      } 
      else {
	  
	m = curcmd ;
	n = curchr ;
      } 
      {
	getxtoken () ;
	if ( curcmd == 0 ) {
	    
	  if ( curchr == 257 ) 
	  {
	    curcmd = 13 ;
	    curchr = curtok - 4096 ;
	  } 
	} 
      } 
      if ( ( curcmd > 13 ) || ( curchr > 255 ) ) 
      {
	curcmd = 0 ;
	curchr = 256 ;
      } 
      if ( thisif == 0 ) 
      b = ( n == curchr ) ;
      else b = ( m == curcmd ) ;
    } 
    break ;
  case 2 : 
  case 3 : 
    {
      if ( thisif == 2 ) 
      scanint () ;
      else scandimen ( false , false , false ) ;
      n = curval ;
      do {
	  getxtoken () ;
      } while ( ! ( curcmd != 10 ) ) ;
      if ( ( curtok >= 3132 ) && ( curtok <= 3134 ) ) 
      r = curtok - 3072 ;
      else {
	  
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 931 ) ;
	} 
	printcmdchr ( 107 , thisif ) ;
	{
	  helpptr = 1 ;
	  helpline [0 ]= 932 ;
	} 
	backerror () ;
	r = 61 ;
      } 
      if ( thisif == 2 ) 
      scanint () ;
      else scandimen ( false , false , false ) ;
      switch ( r ) 
      {case 60 : 
	b = ( n < curval ) ;
	break ;
      case 61 : 
	b = ( n == curval ) ;
	break ;
      case 62 : 
	b = ( n > curval ) ;
	break ;
      } 
    } 
    break ;
  case 4 : 
    {
      scanint () ;
      b = odd ( curval ) ;
    } 
    break ;
  case 5 : 
    b = ( abs ( curlist .modefield ) == 1 ) ;
    break ;
  case 6 : 
    b = ( abs ( curlist .modefield ) == 104 ) ;
    break ;
  case 7 : 
    b = ( abs ( curlist .modefield ) == 207 ) ;
    break ;
  case 8 : 
    b = ( curlist .modefield < 0 ) ;
    break ;
  case 9 : 
  case 10 : 
  case 11 : 
    {
      scanregisternum () ;
      if ( curval < 256 ) 
      p = eqtb [27433 + curval ].hh .v.RH ;
      else {
	  
	findsaelement ( 4 , curval , false ) ;
	if ( curptr == -268435455L ) 
	p = -268435455L ;
	else p = mem [curptr + 1 ].hh .v.RH ;
      } 
      if ( thisif == 9 ) 
      b = ( p == -268435455L ) ;
      else if ( p == -268435455L ) 
      b = false ;
      else if ( thisif == 10 ) 
      b = ( mem [p ].hh.b0 == 0 ) ;
      else b = ( mem [p ].hh.b0 == 1 ) ;
    } 
    break ;
  case 12 : 
    {
      savescannerstatus = scannerstatus ;
      scannerstatus = 0 ;
      getnext () ;
      n = curcs ;
      p = curcmd ;
      q = curchr ;
      getnext () ;
      if ( curcmd != p ) 
      b = false ;
      else if ( curcmd < 113 ) 
      b = ( curchr == q ) ;
      else {
	  
	p = mem [curchr ].hh .v.RH ;
	q = mem [eqtb [n ].hh .v.RH ].hh .v.RH ;
	if ( p == q ) 
	b = true ;
	else {
	    
	  while ( ( p != -268435455L ) && ( q != -268435455L ) ) if ( mem [p 
	  ].hh .v.LH != mem [q ].hh .v.LH ) 
	  p = -268435455L ;
	  else {
	      
	    p = mem [p ].hh .v.RH ;
	    q = mem [q ].hh .v.RH ;
	  } 
	  b = ( ( p == -268435455L ) && ( q == -268435455L ) ) ;
	} 
      } 
      scannerstatus = savescannerstatus ;
    } 
    break ;
  case 13 : 
    {
      scanfourbitintor18 () ;
      if ( curval == 18 ) 
      b = ! shellenabledp ;
      else b = ( readopen [curval ]== 2 ) ;
    } 
    break ;
  case 14 : 
    b = true ;
    break ;
  case 15 : 
    b = false ;
    break ;
  case 17 : 
    {
      savescannerstatus = scannerstatus ;
      scannerstatus = 0 ;
      getnext () ;
      b = ( curcmd != 103 ) ;
      scannerstatus = savescannerstatus ;
    } 
    break ;
  case 18 : 
    {
      n = getavail () ;
      p = n ;
      e = isincsname ;
      isincsname = true ;
      do {
	  getxtoken () ;
	if ( curcs == 0 ) 
	{
	  q = getavail () ;
	  mem [p ].hh .v.RH = q ;
	  mem [q ].hh .v.LH = curtok ;
	  p = q ;
	} 
      } while ( ! ( curcs != 0 ) ) ;
      if ( curcmd != 67 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 707 ) ;
	} 
	printesc ( 577 ) ;
	print ( 708 ) ;
	{
	  helpptr = 2 ;
	  helpline [1 ]= 709 ;
	  helpline [0 ]= 710 ;
	} 
	backerror () ;
      } 
      m = first ;
      p = mem [n ].hh .v.RH ;
      while ( p != -268435455L ) {
	  
	if ( m >= maxbufstack ) 
	{
	  maxbufstack = m + 1 ;
	  if ( maxbufstack == bufsize ) 
	  overflow ( 258 , bufsize ) ;
	} 
	buffer [m ]= mem [p ].hh .v.LH % 256 ;
	incr ( m ) ;
	p = mem [p ].hh .v.RH ;
      } 
      if ( m > first + 1 ) 
      curcs = idlookup ( first , m - first ) ;
      else if ( m == first ) 
      curcs = 513 ;
      else curcs = 257 + buffer [first ];
      flushlist ( n ) ;
      b = ( eqtb [curcs ].hh.b0 != 103 ) ;
      isincsname = e ;
    } 
    break ;
  case 20 : 
    b = isincsname ;
    break ;
  case 23 : 
  case 22 : 
    {
      if ( thisif == 22 ) 
      scanint () ;
      else scandimen ( false , false , false ) ;
      n = curval ;
      if ( n < 0 ) 
      n = - (integer) n ;
      do {
	  getxtoken () ;
      } while ( ! ( curcmd != 10 ) ) ;
      if ( ( curtok >= 3132 ) && ( curtok <= 3134 ) ) 
      r = curtok - 3072 ;
      else {
	  
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 931 ) ;
	} 
	printcmdchr ( 107 , thisif ) ;
	{
	  helpptr = 1 ;
	  helpline [0 ]= 932 ;
	} 
	backerror () ;
	r = 61 ;
      } 
      if ( thisif == 22 ) 
      scanint () ;
      else scandimen ( false , false , false ) ;
      if ( curval < 0 ) 
      curval = - (integer) curval ;
      switch ( r ) 
      {case 60 : 
	b = ( n < curval ) ;
	break ;
      case 61 : 
	b = ( n == curval ) ;
	break ;
      case 62 : 
	b = ( n > curval ) ;
	break ;
      } 
    } 
    break ;
  case 19 : 
    {
      scanfontident () ;
      n = curval ;
      scancharnum () ;
      if ( ( fontbc [n ]<= curval ) && ( fontec [n ]>= curval ) ) 
      b = ( fontinfo [charbase [n ]+ effectivechar ( true , n , curval ) ]
      .qqqq .b0 > 0 ) ;
      else b = false ;
    } 
    break ;
  case 16 : 
    {
      scanint () ;
      n = curval ;
      if ( eqtb [29310 ].cint > 1 ) 
      {
	begindiagnostic () ;
	print ( 933 ) ;
	printint ( n ) ;
	printchar ( 125 ) ;
	enddiagnostic ( false ) ;
      } 
      while ( n != 0 ) {
	  
	passtext () ;
	if ( condptr == savecondptr ) {
	    
	  if ( curchr == 4 ) 
	  decr ( n ) ;
	  else goto lab50 ;
	} 
	else if ( curchr == 2 ) 
	{
	  if ( ifstack [inopen ]== condptr ) 
	  ifwarning () ;
	  p = condptr ;
	  ifline = mem [p + 1 ].cint ;
	  curif = mem [p ].hh.b1 ;
	  iflimit = mem [p ].hh.b0 ;
	  condptr = mem [p ].hh .v.RH ;
	  freenode ( p , 2 ) ;
	} 
      } 
      changeiflimit ( 4 , savecondptr ) ;
      return ;
    } 
    break ;
  case 21 : 
    {
      savescannerstatus = scannerstatus ;
      scannerstatus = 0 ;
      getnext () ;
      scannerstatus = savescannerstatus ;
      if ( curcs < 514 ) 
      m = primlookup ( curcs - 257 ) ;
      else m = primlookup ( hash [curcs ].v.RH ) ;
      b = ( ( curcmd != 103 ) && ( m != 0 ) && ( curcmd == eqtb [15526 + m ]
      .hh.b0 ) && ( curchr == eqtb [15526 + m ].hh .v.RH ) ) ;
    } 
    break ;
  } 
  if ( isunless ) 
  b = ! b ;
  if ( eqtb [29310 ].cint > 1 ) 
  {
    begindiagnostic () ;
    if ( b ) 
    print ( 929 ) ;
    else print ( 930 ) ;
    enddiagnostic ( false ) ;
  } 
  if ( b ) 
  {
    changeiflimit ( 3 , savecondptr ) ;
    return ;
  } 
  while ( true ) {
      
    passtext () ;
    if ( condptr == savecondptr ) 
    {
      if ( curchr != 4 ) 
      goto lab50 ;
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 927 ) ;
      } 
      printesc ( 925 ) ;
      {
	helpptr = 1 ;
	helpline [0 ]= 928 ;
      } 
      error () ;
    } 
    else if ( curchr == 2 ) 
    {
      if ( ifstack [inopen ]== condptr ) 
      ifwarning () ;
      p = condptr ;
      ifline = mem [p + 1 ].cint ;
      curif = mem [p ].hh.b1 ;
      iflimit = mem [p ].hh.b0 ;
      condptr = mem [p ].hh .v.RH ;
      freenode ( p , 2 ) ;
    } 
  } 
  lab50: if ( curchr == 2 ) 
  {
    if ( ifstack [inopen ]== condptr ) 
    ifwarning () ;
    p = condptr ;
    ifline = mem [p + 1 ].cint ;
    curif = mem [p ].hh.b1 ;
    iflimit = mem [p ].hh.b0 ;
    condptr = mem [p ].hh .v.RH ;
    freenode ( p , 2 ) ;
  } 
  else iflimit = 2 ;
} 
void 
beginname ( void ) 
{
  beginname_regmem 
  areadelimiter = 0 ;
  extdelimiter = 0 ;
  quotedfilename = false ;
} 
boolean 
zmorename ( ASCIIcode c ) 
{
  register boolean Result; morename_regmem 
  if ( ( c == 32 ) && stopatspace && ( ! quotedfilename ) ) 
  Result = false ;
  else if ( c == 34 ) 
  {
    quotedfilename = ! quotedfilename ;
    Result = true ;
  } 
  else {
      
    {
      if ( poolptr + 1 > poolsize ) 
      overflow ( 259 , poolsize - initpoolptr ) ;
    } 
    {
      strpool [poolptr ]= c ;
      incr ( poolptr ) ;
    } 
    if ( ISDIRSEP ( c ) ) 
    {
      areadelimiter = ( poolptr - strstart [strptr ]) ;
      extdelimiter = 0 ;
    } 
    else if ( c == 46 ) 
    extdelimiter = ( poolptr - strstart [strptr ]) ;
    Result = true ;
  } 
  return Result ;
} 
void 
endname ( void ) 
{
  endname_regmem 
  strnumber tempstr  ;
  poolpointer j, s, t  ;
  boolean mustquote  ;
  if ( strptr + 3 > maxstrings ) 
  overflow ( 260 , maxstrings - initstrptr ) ;
  {
    if ( poolptr + 6 > poolsize ) 
    overflow ( 259 , poolsize - initpoolptr ) ;
  } 
  if ( areadelimiter != 0 ) 
  {
    mustquote = false ;
    s = strstart [strptr ];
    t = strstart [strptr ]+ areadelimiter ;
    j = s ;
    while ( ( ! mustquote ) && ( j < t ) ) {
	
      mustquote = strpool [j ]== 32 ;
      incr ( j ) ;
    } 
    if ( mustquote ) 
    {
      {register integer for_end; j = poolptr - 1 ;for_end = t ; if ( j >= 
      for_end) do 
	strpool [j + 2 ]= strpool [j ];
      while ( j-- > for_end ) ;} 
      strpool [t + 1 ]= 34 ;
      {register integer for_end; j = t - 1 ;for_end = s ; if ( j >= for_end) 
      do 
	strpool [j + 1 ]= strpool [j ];
      while ( j-- > for_end ) ;} 
      strpool [s ]= 34 ;
      if ( extdelimiter != 0 ) 
      extdelimiter = extdelimiter + 2 ;
      areadelimiter = areadelimiter + 2 ;
      poolptr = poolptr + 2 ;
    } 
  } 
  s = strstart [strptr ]+ areadelimiter ;
  if ( extdelimiter == 0 ) 
  t = poolptr ;
  else t = strstart [strptr ]+ extdelimiter - 1 ;
  mustquote = false ;
  j = s ;
  while ( ( ! mustquote ) && ( j < t ) ) {
      
    mustquote = strpool [j ]== 32 ;
    incr ( j ) ;
  } 
  if ( mustquote ) 
  {
    {register integer for_end; j = poolptr - 1 ;for_end = t ; if ( j >= 
    for_end) do 
      strpool [j + 2 ]= strpool [j ];
    while ( j-- > for_end ) ;} 
    strpool [t + 1 ]= 34 ;
    {register integer for_end; j = t - 1 ;for_end = s ; if ( j >= for_end) 
    do 
      strpool [j + 1 ]= strpool [j ];
    while ( j-- > for_end ) ;} 
    strpool [s ]= 34 ;
    if ( extdelimiter != 0 ) 
    extdelimiter = extdelimiter + 2 ;
    poolptr = poolptr + 2 ;
  } 
  if ( extdelimiter != 0 ) 
  {
    s = strstart [strptr ]+ extdelimiter - 1 ;
    t = poolptr ;
    mustquote = false ;
    j = s ;
    while ( ( ! mustquote ) && ( j < t ) ) {
	
      mustquote = strpool [j ]== 32 ;
      incr ( j ) ;
    } 
    if ( mustquote ) 
    {
      strpool [t + 1 ]= 34 ;
      {register integer for_end; j = t - 1 ;for_end = s ; if ( j >= for_end) 
      do 
	strpool [j + 1 ]= strpool [j ];
      while ( j-- > for_end ) ;} 
      strpool [s ]= 34 ;
      poolptr = poolptr + 2 ;
    } 
  } 
  if ( areadelimiter == 0 ) 
  curarea = 345 ;
  else {
      
    curarea = strptr ;
    strstart [strptr + 1 ]= strstart [strptr ]+ areadelimiter ;
    incr ( strptr ) ;
    tempstr = searchstring ( curarea ) ;
    if ( tempstr > 0 ) 
    {
      curarea = tempstr ;
      decr ( strptr ) ;
      {register integer for_end; j = strstart [strptr + 1 ];for_end = 
      poolptr - 1 ; if ( j <= for_end) do 
	{
	  strpool [j - areadelimiter ]= strpool [j ];
	} 
      while ( j++ < for_end ) ;} 
      poolptr = poolptr - areadelimiter ;
    } 
  } 
  if ( extdelimiter == 0 ) 
  {
    curext = 345 ;
    curname = slowmakestring () ;
  } 
  else {
      
    curname = strptr ;
    strstart [strptr + 1 ]= strstart [strptr ]+ extdelimiter - 
    areadelimiter - 1 ;
    incr ( strptr ) ;
    curext = makestring () ;
    decr ( strptr ) ;
    tempstr = searchstring ( curname ) ;
    if ( tempstr > 0 ) 
    {
      curname = tempstr ;
      decr ( strptr ) ;
      {register integer for_end; j = strstart [strptr + 1 ];for_end = 
      poolptr - 1 ; if ( j <= for_end) do 
	{
	  strpool [j - extdelimiter + areadelimiter + 1 ]= strpool [j ];
	} 
      while ( j++ < for_end ) ;} 
      poolptr = poolptr - extdelimiter + areadelimiter + 1 ;
    } 
    curext = slowmakestring () ;
  } 
} 
void 
zpackfilename ( strnumber n , strnumber a , strnumber e ) 
{
  packfilename_regmem 
  integer k  ;
  ASCIIcode c  ;
  poolpointer j  ;
  k = 0 ;
  if ( nameoffile ) 
  libcfree ( nameoffile ) ;
  nameoffile = xmallocarray ( ASCIIcode , ( strstart [a + 1 ]- strstart [a 
  ]) + ( strstart [n + 1 ]- strstart [n ]) + ( strstart [e + 1 ]- 
  strstart [e ]) + 1 ) ;
  {register integer for_end; j = strstart [a ];for_end = strstart [a + 1 
  ]- 1 ; if ( j <= for_end) do 
    {
      c = strpool [j ];
      if ( ! ( c == 34 ) ) 
      {
	incr ( k ) ;
	if ( k <= maxint ) 
	nameoffile [k ]= xchr [c ];
      } 
    } 
  while ( j++ < for_end ) ;} 
  {register integer for_end; j = strstart [n ];for_end = strstart [n + 1 
  ]- 1 ; if ( j <= for_end) do 
    {
      c = strpool [j ];
      if ( ! ( c == 34 ) ) 
      {
	incr ( k ) ;
	if ( k <= maxint ) 
	nameoffile [k ]= xchr [c ];
      } 
    } 
  while ( j++ < for_end ) ;} 
  {register integer for_end; j = strstart [e ];for_end = strstart [e + 1 
  ]- 1 ; if ( j <= for_end) do 
    {
      c = strpool [j ];
      if ( ! ( c == 34 ) ) 
      {
	incr ( k ) ;
	if ( k <= maxint ) 
	nameoffile [k ]= xchr [c ];
      } 
    } 
  while ( j++ < for_end ) ;} 
  if ( k <= maxint ) 
  namelength = k ;
  else namelength = maxint ;
  nameoffile [namelength + 1 ]= 0 ;
} 
void 
zpackbufferedname ( smallnumber n , integer a , integer b ) 
{
  packbufferedname_regmem 
  integer k  ;
  ASCIIcode c  ;
  integer j  ;
  if ( n + b - a + 5 > maxint ) 
  b = a + maxint - n - 5 ;
  k = 0 ;
  if ( nameoffile ) 
  libcfree ( nameoffile ) ;
  nameoffile = xmallocarray ( ASCIIcode , n + ( b - a + 1 ) + 5 ) ;
  {register integer for_end; j = 1 ;for_end = n ; if ( j <= for_end) do 
    {
      c = xord [ucharcast ( TEXformatdefault [j ]) ];
      if ( ! ( c == 34 ) ) 
      {
	incr ( k ) ;
	if ( k <= maxint ) 
	nameoffile [k ]= xchr [c ];
      } 
    } 
  while ( j++ < for_end ) ;} 
  {register integer for_end; j = a ;for_end = b ; if ( j <= for_end) do 
    {
      c = buffer [j ];
      if ( ! ( c == 34 ) ) 
      {
	incr ( k ) ;
	if ( k <= maxint ) 
	nameoffile [k ]= xchr [c ];
      } 
    } 
  while ( j++ < for_end ) ;} 
  {register integer for_end; j = formatdefaultlength - 3 ;for_end = 
  formatdefaultlength ; if ( j <= for_end) do 
    {
      c = xord [ucharcast ( TEXformatdefault [j ]) ];
      if ( ! ( c == 34 ) ) 
      {
	incr ( k ) ;
	if ( k <= maxint ) 
	nameoffile [k ]= xchr [c ];
      } 
    } 
  while ( j++ < for_end ) ;} 
  if ( k <= maxint ) 
  namelength = k ;
  else namelength = maxint ;
  nameoffile [namelength + 1 ]= 0 ;
} 
strnumber 
makenamestring ( void ) 
{
  register strnumber Result; makenamestring_regmem 
  integer k  ;
  poolpointer saveareadelimiter, saveextdelimiter  ;
  boolean savenameinprogress, savestopatspace  ;
  if ( ( poolptr + namelength > poolsize ) || ( strptr == maxstrings ) || ( ( 
  poolptr - strstart [strptr ]) > 0 ) ) 
  Result = 63 ;
  else {
      
    {register integer for_end; k = 1 ;for_end = namelength ; if ( k <= 
    for_end) do 
      {
	strpool [poolptr ]= xord [nameoffile [k ]];
	incr ( poolptr ) ;
      } 
    while ( k++ < for_end ) ;} 
    Result = makestring () ;
    saveareadelimiter = areadelimiter ;
    saveextdelimiter = extdelimiter ;
    savenameinprogress = nameinprogress ;
    savestopatspace = stopatspace ;
    nameinprogress = true ;
    beginname () ;
    stopatspace = false ;
    k = 1 ;
    while ( ( k <= namelength ) && ( morename ( nameoffile [k ]) ) ) incr ( 
    k ) ;
    stopatspace = savestopatspace ;
    endname () ;
    nameinprogress = savenameinprogress ;
    areadelimiter = saveareadelimiter ;
    extdelimiter = saveextdelimiter ;
  } 
  return Result ;
} 
strnumber 
zamakenamestring ( alphafile f ) 
{
  register strnumber Result; amakenamestring_regmem 
  Result = makenamestring () ;
  return Result ;
} 
strnumber 
zbmakenamestring ( bytefile f ) 
{
  register strnumber Result; bmakenamestring_regmem 
  Result = makenamestring () ;
  return Result ;
} 
strnumber 
zwmakenamestring ( wordfile f ) 
{
  register strnumber Result; wmakenamestring_regmem 
  Result = makenamestring () ;
  return Result ;
} 
void 
scanfilename ( void ) 
{
  /* 30 */ scanfilename_regmem 
  nameinprogress = true ;
  beginname () ;
  do {
      getxtoken () ;
  } while ( ! ( curcmd != 10 ) ) ;
  while ( true ) {
      
    if ( ( curcmd > 12 ) || ( curchr > 255 ) ) 
    {
      backinput () ;
      goto lab30 ;
    } 
    if ( ( curchr == 32 ) && ( curinput .statefield != 0 ) && ( curinput 
    .locfield > curinput .limitfield ) ) 
    goto lab30 ;
    if ( ! morename ( curchr ) ) 
    goto lab30 ;
    getxtoken () ;
  } 
  lab30: endname () ;
  nameinprogress = false ;
} 
void 
zpackjobname ( strnumber s ) 
{
  packjobname_regmem 
  curarea = 345 ;
  curext = s ;
  curname = jobname ;
  packfilename ( curname , curarea , curext ) ;
} 
void 
zpromptfilename ( strnumber s , strnumber e ) 
{
  /* 30 */ promptfilename_regmem 
  integer k  ;
  strnumber savedcurname  ;
  strnumber savedcurext  ;
  strnumber savedcurarea  ;
  if ( interaction == 2 ) 
  ;
  if ( s == 935 ) 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 264 ) ;
    print ( 936 ) ;
  } 
  else {
      
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 264 ) ;
    print ( 937 ) ;
  } 
  printfilename ( curname , curarea , curext ) ;
  print ( 938 ) ;
  if ( ( e == 939 ) || ( e == 345 ) ) 
  showcontext () ;
  println () ;
  printcstring ( promptfilenamehelpmsg ) ;
  if ( ( e != 345 ) ) 
  {
    print ( 940 ) ;
    print ( e ) ;
    print ( 39 ) ;
  } 
  print ( 41 ) ;
  println () ;
  printnl ( 941 ) ;
  print ( s ) ;
  if ( interaction < 2 ) 
  fatalerror ( 942 ) ;
  savedcurname = curname ;
  savedcurext = curext ;
  savedcurarea = curarea ;
  {
    ;
    print ( 646 ) ;
    terminput () ;
  } 
  {
    beginname () ;
    k = first ;
    while ( ( buffer [k ]== 32 ) && ( k < last ) ) incr ( k ) ;
    while ( true ) {
	
      if ( k == last ) 
      goto lab30 ;
      if ( ! morename ( buffer [k ]) ) 
      goto lab30 ;
      incr ( k ) ;
    } 
    lab30: endname () ;
  } 
  if ( ( ( strstart [curname + 1 ]- strstart [curname ]) == 0 ) && ( 
  curext == 345 ) && ( curarea == 345 ) ) 
  {
    curname = savedcurname ;
    curext = savedcurext ;
    curarea = savedcurarea ;
  } 
  else if ( curext == 345 ) 
  curext = e ;
  packfilename ( curname , curarea , curext ) ;
} 
void 
openlogfile ( void ) 
{
  openlogfile_regmem 
  unsigned char oldsetting  ;
  integer k  ;
  integer l  ;
  constcstring months  ;
  oldsetting = selector ;
  if ( jobname == 0 ) 
  jobname = getjobname ( 945 ) ;
  packjobname ( 946 ) ;
  recorderchangefilename ( stringcast ( nameoffile + 1 ) ) ;
  packjobname ( 947 ) ;
  while ( ! aopenout ( logfile ) ) {
      
    selector = 17 ;
    promptfilename ( 949 , 947 ) ;
  } 
  texmflogname = amakenamestring ( logfile ) ;
  selector = 18 ;
  logopened = true ;
  {
    if ( srcspecialsp || filelineerrorstylep || parsefirstlinep ) 
    fprintf ( logfile , "%s%s%s",  "This is pdfTeX, Version 3.14159265" , "-2.6" ,     "-1.40.20" ) ;
    else
    fprintf ( logfile , "%s%s%s",  "This is pdfTeX, Version 3.14159265" , "-2.6" ,     "-1.40.20" ) ;
    Fputs ( logfile ,  versionstring ) ;
    slowprint ( formatident ) ;
    print ( 950 ) ;
    printint ( eqtb [29295 ].cint ) ;
    printchar ( 32 ) ;
    months = " JANFEBMARAPRMAYJUNJULAUGSEPOCTNOVDEC" ;
    {register integer for_end; k = 3 * eqtb [29296 ].cint - 2 ;for_end = 3 
    * eqtb [29296 ].cint ; if ( k <= for_end) do 
      putc ( months [k ],  logfile );
    while ( k++ < for_end ) ;} 
    printchar ( 32 ) ;
    printint ( eqtb [29297 ].cint ) ;
    printchar ( 32 ) ;
    printtwo ( eqtb [29294 ].cint / 60 ) ;
    printchar ( 58 ) ;
    printtwo ( eqtb [29294 ].cint % 60 ) ;
    if ( ( eTeXmode == 1 ) ) 
    {
      ;
      putc ('\n',  logfile );
      Fputs ( logfile ,  "entering extended mode" ) ;
    } 
    if ( shellenabledp ) 
    {
      putc ('\n',  logfile );
      putc ( ' ' ,  logfile );
      if ( restrictedshell ) 
      {
	Fputs ( logfile ,  "restricted " ) ;
      } 
      Fputs ( logfile ,  "\\write18 enabled." ) ;
    } 
    if ( srcspecialsp ) 
    {
      putc ('\n',  logfile );
      Fputs ( logfile ,  " Source specials enabled." ) ;
    } 
    if ( filelineerrorstylep ) 
    {
      putc ('\n',  logfile );
      Fputs ( logfile ,  " file:line:error style messages enabled." ) ;
    } 
    if ( parsefirstlinep ) 
    {
      putc ('\n',  logfile );
      Fputs ( logfile ,  " %&-line parsing enabled." ) ;
    } 
    if ( translatefilename ) 
    {
      putc ('\n',  logfile );
      Fputs ( logfile ,  " (" ) ;
      fputs ( translatefilename , logfile ) ;
      putc ( ')' ,  logfile );
    } 
  } 
  if ( mltexenabledp ) 
  {
    putc ('\n',  logfile );
    Fputs ( logfile ,  "MLTeX v2.2 enabled" ) ;
  } 
  inputstack [inputptr ]= curinput ;
  printnl ( 948 ) ;
  l = inputstack [0 ].limitfield ;
  if ( buffer [l ]== eqtb [29322 ].cint ) 
  decr ( l ) ;
  {register integer for_end; k = 1 ;for_end = l ; if ( k <= for_end) do 
    print ( buffer [k ]) ;
  while ( k++ < for_end ) ;} 
  println () ;
  selector = oldsetting + 2 ;
} 
void 
startinput ( void ) 
{
  /* 30 */ startinput_regmem 
  strnumber tempstr  ;
  scanfilename () ;
  packfilename ( curname , curarea , curext ) ;
  while ( true ) {
      
    beginfilereading () ;
    texinputtype = 1 ;
    if ( kpseinnameok ( stringcast ( nameoffile + 1 ) ) && aopenin ( inputfile 
    [curinput .indexfield ], kpsetexformat ) ) 
    goto lab30 ;
    endfilereading () ;
    promptfilename ( 935 , 345 ) ;
  } 
  lab30: curinput .namefield = amakenamestring ( inputfile [curinput 
  .indexfield ]) ;
  sourcefilenamestack [inopen ]= curinput .namefield ;
  fullsourcefilenamestack [inopen ]= makefullnamestring () ;
  if ( curinput .namefield == strptr - 1 ) 
  {
    tempstr = searchstring ( curinput .namefield ) ;
    if ( tempstr > 0 ) 
    {
      curinput .namefield = tempstr ;
      {
	decr ( strptr ) ;
	poolptr = strstart [strptr ];
      } 
    } 
  } 
  if ( jobname == 0 ) 
  {
    jobname = getjobname ( curname ) ;
    openlogfile () ;
  } 
  if ( termoffset + ( strstart [fullsourcefilenamestack [inopen ]+ 1 ]- 
  strstart [fullsourcefilenamestack [inopen ]]) > maxprintline - 2 ) 
  println () ;
  else if ( ( termoffset > 0 ) || ( fileoffset > 0 ) ) 
  printchar ( 32 ) ;
  printchar ( 40 ) ;
  incr ( openparens ) ;
  slowprint ( fullsourcefilenamestack [inopen ]) ;
  fflush ( stdout ) ;
  curinput .statefield = 33 ;
  {
    line = 1 ;
    if ( inputln ( inputfile [curinput .indexfield ], false ) ) 
    ;
    firmuptheline () ;
    if ( ( eqtb [29322 ].cint < 0 ) || ( eqtb [29322 ].cint > 255 ) ) 
    decr ( curinput .limitfield ) ;
    else buffer [curinput .limitfield ]= eqtb [29322 ].cint ;
    first = curinput .limitfield + 1 ;
    curinput .locfield = curinput .startfield ;
  } 
} 
fourquarters 
zeffectivecharinfo ( internalfontnumber f , quarterword c ) 
{
  /* 10 */ register fourquarters Result; effectivecharinfo_regmem 
  fourquarters ci  ;
  integer basec  ;
  if ( ! mltexenabledp ) 
  {
    Result = fontinfo [charbase [f ]+ c ].qqqq ;
    return Result ;
  } 
  if ( fontec [f ]>= c ) {
      
    if ( fontbc [f ]<= c ) 
    {
      ci = fontinfo [charbase [f ]+ c ].qqqq ;
      if ( ( ci .b0 > 0 ) ) 
      {
	Result = ci ;
	return Result ;
      } 
    } 
  } 
  if ( c >= eqtb [29329 ].cint ) {
      
    if ( c <= eqtb [29330 ].cint ) {
	
      if ( ( eqtb [29018 + c ].hh .v.RH > 0 ) ) 
      {
	basec = ( eqtb [29018 + c ].hh .v.RH % 256 ) ;
	if ( fontec [f ]>= basec ) {
	    
	  if ( fontbc [f ]<= basec ) 
	  {
	    ci = fontinfo [charbase [f ]+ basec ].qqqq ;
	    if ( ( ci .b0 > 0 ) ) 
	    {
	      Result = ci ;
	      return Result ;
	    } 
	  } 
	} 
      } 
    } 
  } 
  Result = nullcharacter ;
  return Result ;
} 
internalfontnumber 
zreadfontinfo ( halfword u , strnumber nom , strnumber aire , scaled s ) 
{
  /* 30 11 45 */ register internalfontnumber Result; readfontinfo_regmem 
  fontindex k  ;
  boolean nametoolong  ;
  boolean fileopened  ;
  halfword lf, lh, bc, ec, nw, nh, nd, ni, nl, nk, ne, np  ;
  internalfontnumber f  ;
  internalfontnumber g  ;
  eightbits a, b, c, d  ;
  fourquarters qw  ;
  scaled sw  ;
  integer bchlabel  ;
  short bchar  ;
  scaled z  ;
  integer alpha  ;
  unsigned char beta  ;
  g = 0 ;
  fileopened = false ;
  nametoolong = ( ( strstart [nom + 1 ]- strstart [nom ]) > 255 ) || ( ( 
  strstart [aire + 1 ]- strstart [aire ]) > 255 ) ;
  if ( nametoolong ) 
  goto lab11 ;
  packfilename ( nom , aire , 345 ) ;
  if ( ! bopenin ( tfmfile ) ) 
  goto lab11 ;
  fileopened = true ;
  {
    {
      lf = tfmtemp ;
      if ( lf > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      lf = lf * 256 + tfmtemp ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    {
      lh = tfmtemp ;
      if ( lh > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      lh = lh * 256 + tfmtemp ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    {
      bc = tfmtemp ;
      if ( bc > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      bc = bc * 256 + tfmtemp ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    {
      ec = tfmtemp ;
      if ( ec > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      ec = ec * 256 + tfmtemp ;
    } 
    if ( ( bc > ec + 1 ) || ( ec > 255 ) ) 
    goto lab11 ;
    if ( bc > 255 ) 
    {
      bc = 1 ;
      ec = 0 ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    {
      nw = tfmtemp ;
      if ( nw > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      nw = nw * 256 + tfmtemp ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    {
      nh = tfmtemp ;
      if ( nh > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      nh = nh * 256 + tfmtemp ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    {
      nd = tfmtemp ;
      if ( nd > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      nd = nd * 256 + tfmtemp ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    {
      ni = tfmtemp ;
      if ( ni > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      ni = ni * 256 + tfmtemp ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    {
      nl = tfmtemp ;
      if ( nl > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      nl = nl * 256 + tfmtemp ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    {
      nk = tfmtemp ;
      if ( nk > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      nk = nk * 256 + tfmtemp ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    {
      ne = tfmtemp ;
      if ( ne > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      ne = ne * 256 + tfmtemp ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    {
      np = tfmtemp ;
      if ( np > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      np = np * 256 + tfmtemp ;
    } 
    if ( lf != 6 + lh + ( ec - bc + 1 ) + nw + nh + nd + ni + nl + nk + ne + 
    np ) 
    goto lab11 ;
    if ( ( nw == 0 ) || ( nh == 0 ) || ( nd == 0 ) || ( ni == 0 ) ) 
    goto lab11 ;
  } 
  lf = lf - 6 - lh ;
  if ( np < 7 ) 
  lf = lf + 7 - np ;
  if ( ( fontptr == fontmax ) || ( fmemptr + lf > fontmemsize ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 952 ) ;
    } 
    sprintcs ( u ) ;
    printchar ( 61 ) ;
    printfilename ( nom , aire , 345 ) ;
    if ( s >= 0 ) 
    {
      print ( 890 ) ;
      printscaled ( s ) ;
      print ( 312 ) ;
    } 
    else if ( s != -1000 ) 
    {
      print ( 953 ) ;
      printint ( - (integer) s ) ;
    } 
    print ( 962 ) ;
    {
      helpptr = 4 ;
      helpline [3 ]= 963 ;
      helpline [2 ]= 964 ;
      helpline [1 ]= 965 ;
      helpline [0 ]= 966 ;
    } 
    error () ;
    goto lab30 ;
  } 
  f = fontptr + 1 ;
  charbase [f ]= fmemptr - bc ;
  widthbase [f ]= charbase [f ]+ ec + 1 ;
  heightbase [f ]= widthbase [f ]+ nw ;
  depthbase [f ]= heightbase [f ]+ nh ;
  italicbase [f ]= depthbase [f ]+ nd ;
  ligkernbase [f ]= italicbase [f ]+ ni ;
  kernbase [f ]= ligkernbase [f ]+ nl - 256 * ( 128 ) ;
  extenbase [f ]= kernbase [f ]+ 256 * ( 128 ) + nk ;
  parambase [f ]= extenbase [f ]+ ne ;
  {
    if ( lh < 2 ) 
    goto lab11 ;
    {
      tfmtemp = getc ( tfmfile ) ;
      a = tfmtemp ;
      qw .b0 = a ;
      tfmtemp = getc ( tfmfile ) ;
      b = tfmtemp ;
      qw .b1 = b ;
      tfmtemp = getc ( tfmfile ) ;
      c = tfmtemp ;
      qw .b2 = c ;
      tfmtemp = getc ( tfmfile ) ;
      d = tfmtemp ;
      qw .b3 = d ;
      fontcheck [f ]= qw ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    {
      z = tfmtemp ;
      if ( z > 127 ) 
      goto lab11 ;
      tfmtemp = getc ( tfmfile ) ;
      z = z * 256 + tfmtemp ;
    } 
    tfmtemp = getc ( tfmfile ) ;
    z = z * 256 + tfmtemp ;
    tfmtemp = getc ( tfmfile ) ;
    z = ( z * 16 ) + ( tfmtemp / 16 ) ;
    if ( z < 65536L ) 
    goto lab11 ;
    while ( lh > 2 ) {
	
      tfmtemp = getc ( tfmfile ) ;
      tfmtemp = getc ( tfmfile ) ;
      tfmtemp = getc ( tfmfile ) ;
      tfmtemp = getc ( tfmfile ) ;
      decr ( lh ) ;
    } 
    fontdsize [f ]= z ;
    if ( s != -1000 ) {
	
      if ( s >= 0 ) 
      z = s ;
      else z = xnoverd ( z , - (integer) s , 1000 ) ;
    } 
    fontsize [f ]= z ;
  } 
  {register integer for_end; k = fmemptr ;for_end = widthbase [f ]- 1 
  ; if ( k <= for_end) do 
    {
      {
	tfmtemp = getc ( tfmfile ) ;
	a = tfmtemp ;
	qw .b0 = a ;
	tfmtemp = getc ( tfmfile ) ;
	b = tfmtemp ;
	qw .b1 = b ;
	tfmtemp = getc ( tfmfile ) ;
	c = tfmtemp ;
	qw .b2 = c ;
	tfmtemp = getc ( tfmfile ) ;
	d = tfmtemp ;
	qw .b3 = d ;
	fontinfo [k ].qqqq = qw ;
      } 
      if ( ( a >= nw ) || ( b / 16 >= nh ) || ( b % 16 >= nd ) || ( c / 4 >= 
      ni ) ) 
      goto lab11 ;
      switch ( c % 4 ) 
      {case 1 : 
	if ( d >= nl ) 
	goto lab11 ;
	break ;
      case 3 : 
	if ( d >= ne ) 
	goto lab11 ;
	break ;
      case 2 : 
	{
	  {
	    if ( ( d < bc ) || ( d > ec ) ) 
	    goto lab11 ;
	  } 
	  while ( d < k + bc - fmemptr ) {
	      
	    qw = fontinfo [charbase [f ]+ d ].qqqq ;
	    if ( ( ( qw .b2 ) % 4 ) != 2 ) 
	    goto lab45 ;
	    d = qw .b3 ;
	  } 
	  if ( d == k + bc - fmemptr ) 
	  goto lab11 ;
	  lab45: ;
	} 
	break ;
	default: 
	;
	break ;
      } 
    } 
  while ( k++ < for_end ) ;} 
  {
    {
      alpha = 16 ;
      if ( z >= 134217728L ) 
      pdferror ( 590 , 967 ) ;
      while ( z >= 8388608L ) {
	  
	z = z / 2 ;
	alpha = alpha + alpha ;
      } 
      beta = 256 / alpha ;
      alpha = alpha * z ;
    } 
    {register integer for_end; k = widthbase [f ];for_end = ligkernbase [
    f ]- 1 ; if ( k <= for_end) do 
      {
	tfmtemp = getc ( tfmfile ) ;
	a = tfmtemp ;
	tfmtemp = getc ( tfmfile ) ;
	b = tfmtemp ;
	tfmtemp = getc ( tfmfile ) ;
	c = tfmtemp ;
	tfmtemp = getc ( tfmfile ) ;
	d = tfmtemp ;
	sw = ( ( ( ( ( d * z ) / 256 ) + ( c * z ) ) / 256 ) + ( b * z ) ) / 
	beta ;
	if ( a == 0 ) 
	fontinfo [k ].cint = sw ;
	else if ( a == 255 ) 
	fontinfo [k ].cint = sw - alpha ;
	else goto lab11 ;
      } 
    while ( k++ < for_end ) ;} 
    if ( fontinfo [widthbase [f ]].cint != 0 ) 
    goto lab11 ;
    if ( fontinfo [heightbase [f ]].cint != 0 ) 
    goto lab11 ;
    if ( fontinfo [depthbase [f ]].cint != 0 ) 
    goto lab11 ;
    if ( fontinfo [italicbase [f ]].cint != 0 ) 
    goto lab11 ;
  } 
  bchlabel = 32767 ;
  bchar = 256 ;
  if ( nl > 0 ) 
  {
    {register integer for_end; k = ligkernbase [f ];for_end = kernbase [f 
    ]+ 256 * ( 128 ) - 1 ; if ( k <= for_end) do 
      {
	{
	  tfmtemp = getc ( tfmfile ) ;
	  a = tfmtemp ;
	  qw .b0 = a ;
	  tfmtemp = getc ( tfmfile ) ;
	  b = tfmtemp ;
	  qw .b1 = b ;
	  tfmtemp = getc ( tfmfile ) ;
	  c = tfmtemp ;
	  qw .b2 = c ;
	  tfmtemp = getc ( tfmfile ) ;
	  d = tfmtemp ;
	  qw .b3 = d ;
	  fontinfo [k ].qqqq = qw ;
	} 
	if ( a > 128 ) 
	{
	  if ( 256 * c + d >= nl ) 
	  goto lab11 ;
	  if ( a == 255 ) {
	      
	    if ( k == ligkernbase [f ]) 
	    bchar = b ;
	  } 
	} 
	else {
	    
	  if ( b != bchar ) 
	  {
	    {
	      if ( ( b < bc ) || ( b > ec ) ) 
	      goto lab11 ;
	    } 
	    qw = fontinfo [charbase [f ]+ b ].qqqq ;
	    if ( ! ( qw .b0 > 0 ) ) 
	    goto lab11 ;
	  } 
	  if ( c < 128 ) 
	  {
	    {
	      if ( ( d < bc ) || ( d > ec ) ) 
	      goto lab11 ;
	    } 
	    qw = fontinfo [charbase [f ]+ d ].qqqq ;
	    if ( ! ( qw .b0 > 0 ) ) 
	    goto lab11 ;
	  } 
	  else if ( 256 * ( c - 128 ) + d >= nk ) 
	  goto lab11 ;
	  if ( a < 128 ) {
	      
	    if ( k - ligkernbase [f ]+ a + 1 >= nl ) 
	    goto lab11 ;
	  } 
	} 
      } 
    while ( k++ < for_end ) ;} 
    if ( a == 255 ) 
    bchlabel = 256 * c + d ;
  } 
  {register integer for_end; k = kernbase [f ]+ 256 * ( 128 ) ;for_end = 
  extenbase [f ]- 1 ; if ( k <= for_end) do 
    {
      tfmtemp = getc ( tfmfile ) ;
      a = tfmtemp ;
      tfmtemp = getc ( tfmfile ) ;
      b = tfmtemp ;
      tfmtemp = getc ( tfmfile ) ;
      c = tfmtemp ;
      tfmtemp = getc ( tfmfile ) ;
      d = tfmtemp ;
      sw = ( ( ( ( ( d * z ) / 256 ) + ( c * z ) ) / 256 ) + ( b * z ) ) / 
      beta ;
      if ( a == 0 ) 
      fontinfo [k ].cint = sw ;
      else if ( a == 255 ) 
      fontinfo [k ].cint = sw - alpha ;
      else goto lab11 ;
    } 
  while ( k++ < for_end ) ;} 
  {register integer for_end; k = extenbase [f ];for_end = parambase [f ]
  - 1 ; if ( k <= for_end) do 
    {
      {
	tfmtemp = getc ( tfmfile ) ;
	a = tfmtemp ;
	qw .b0 = a ;
	tfmtemp = getc ( tfmfile ) ;
	b = tfmtemp ;
	qw .b1 = b ;
	tfmtemp = getc ( tfmfile ) ;
	c = tfmtemp ;
	qw .b2 = c ;
	tfmtemp = getc ( tfmfile ) ;
	d = tfmtemp ;
	qw .b3 = d ;
	fontinfo [k ].qqqq = qw ;
      } 
      if ( a != 0 ) 
      {
	{
	  if ( ( a < bc ) || ( a > ec ) ) 
	  goto lab11 ;
	} 
	qw = fontinfo [charbase [f ]+ a ].qqqq ;
	if ( ! ( qw .b0 > 0 ) ) 
	goto lab11 ;
      } 
      if ( b != 0 ) 
      {
	{
	  if ( ( b < bc ) || ( b > ec ) ) 
	  goto lab11 ;
	} 
	qw = fontinfo [charbase [f ]+ b ].qqqq ;
	if ( ! ( qw .b0 > 0 ) ) 
	goto lab11 ;
      } 
      if ( c != 0 ) 
      {
	{
	  if ( ( c < bc ) || ( c > ec ) ) 
	  goto lab11 ;
	} 
	qw = fontinfo [charbase [f ]+ c ].qqqq ;
	if ( ! ( qw .b0 > 0 ) ) 
	goto lab11 ;
      } 
      {
	{
	  if ( ( d < bc ) || ( d > ec ) ) 
	  goto lab11 ;
	} 
	qw = fontinfo [charbase [f ]+ d ].qqqq ;
	if ( ! ( qw .b0 > 0 ) ) 
	goto lab11 ;
      } 
    } 
  while ( k++ < for_end ) ;} 
  {
    {register integer for_end; k = 1 ;for_end = np ; if ( k <= for_end) do 
      if ( k == 1 ) 
      {
	tfmtemp = getc ( tfmfile ) ;
	sw = tfmtemp ;
	if ( sw > 127 ) 
	sw = sw - 256 ;
	tfmtemp = getc ( tfmfile ) ;
	sw = sw * 256 + tfmtemp ;
	tfmtemp = getc ( tfmfile ) ;
	sw = sw * 256 + tfmtemp ;
	tfmtemp = getc ( tfmfile ) ;
	fontinfo [parambase [f ]].cint = ( sw * 16 ) + ( tfmtemp / 16 ) ;
      } 
      else {
	  
	tfmtemp = getc ( tfmfile ) ;
	a = tfmtemp ;
	tfmtemp = getc ( tfmfile ) ;
	b = tfmtemp ;
	tfmtemp = getc ( tfmfile ) ;
	c = tfmtemp ;
	tfmtemp = getc ( tfmfile ) ;
	d = tfmtemp ;
	sw = ( ( ( ( ( d * z ) / 256 ) + ( c * z ) ) / 256 ) + ( b * z ) ) / 
	beta ;
	if ( a == 0 ) 
	fontinfo [parambase [f ]+ k - 1 ].cint = sw ;
	else if ( a == 255 ) 
	fontinfo [parambase [f ]+ k - 1 ].cint = sw - alpha ;
	else goto lab11 ;
      } 
    while ( k++ < for_end ) ;} 
    if ( feof ( tfmfile ) ) 
    goto lab11 ;
    {register integer for_end; k = np + 1 ;for_end = 7 ; if ( k <= for_end) 
    do 
      fontinfo [parambase [f ]+ k - 1 ].cint = 0 ;
    while ( k++ < for_end ) ;} 
  } 
  if ( np >= 7 ) 
  fontparams [f ]= np ;
  else fontparams [f ]= 7 ;
  hyphenchar [f ]= eqtb [29320 ].cint ;
  skewchar [f ]= eqtb [29321 ].cint ;
  if ( bchlabel < nl ) 
  bcharlabel [f ]= bchlabel + ligkernbase [f ];
  else bcharlabel [f ]= 0 ;
  fontbchar [f ]= bchar ;
  fontfalsebchar [f ]= bchar ;
  if ( bchar <= ec ) {
      
    if ( bchar >= bc ) 
    {
      qw = fontinfo [charbase [f ]+ bchar ].qqqq ;
      if ( ( qw .b0 > 0 ) ) 
      fontfalsebchar [f ]= 256 ;
    } 
  } 
  fontname [f ]= nom ;
  fontarea [f ]= aire ;
  fontbc [f ]= bc ;
  fontec [f ]= ec ;
  fontglue [f ]= -268435455L ;
  charbase [f ]= charbase [f ];
  widthbase [f ]= widthbase [f ];
  ligkernbase [f ]= ligkernbase [f ];
  kernbase [f ]= kernbase [f ];
  extenbase [f ]= extenbase [f ];
  decr ( parambase [f ]) ;
  fmemptr = fmemptr + lf ;
  fontptr = f ;
  g = f ;
  goto lab30 ;
  lab11: {
      
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 264 ) ;
    print ( 952 ) ;
  } 
  sprintcs ( u ) ;
  printchar ( 61 ) ;
  printfilename ( nom , aire , 345 ) ;
  if ( s >= 0 ) 
  {
    print ( 890 ) ;
    printscaled ( s ) ;
    print ( 312 ) ;
  } 
  else if ( s != -1000 ) 
  {
    print ( 953 ) ;
    printint ( - (integer) s ) ;
  } 
  if ( fileopened ) 
  print ( 954 ) ;
  else if ( nametoolong ) 
  print ( 955 ) ;
  else print ( 956 ) ;
  {
    helpptr = 5 ;
    helpline [4 ]= 957 ;
    helpline [3 ]= 958 ;
    helpline [2 ]= 959 ;
    helpline [1 ]= 960 ;
    helpline [0 ]= 961 ;
  } 
  error () ;
  lab30: if ( fileopened ) 
  bclose ( tfmfile ) ;
  Result = g ;
  return Result ;
} 
scaled 
zstorescaledf ( scaled sq , scaled z ) 
{
  register scaled Result; storescaledf_regmem 
  eightbits a, b, c, d  ;
  scaled sw  ;
  integer alpha  ;
  unsigned char beta  ;
  alpha = 16 ;
  if ( z >= 134217728L ) 
  pdferror ( 590 , 967 ) ;
  while ( z >= 8388608L ) {
      
    z = z / 2 ;
    alpha = alpha + alpha ;
  } 
  beta = 256 / alpha ;
  alpha = alpha * z ;
  if ( sq >= 0 ) 
  {
    d = sq % 256 ;
    sq = sq / 256 ;
    c = sq % 256 ;
    sq = sq / 256 ;
    b = sq % 256 ;
    sq = sq / 256 ;
    a = sq % 256 ;
  } 
  else {
      
    sq = ( sq + 1073741824L ) + 1073741824L ;
    d = sq % 256 ;
    sq = sq / 256 ;
    c = sq % 256 ;
    sq = sq / 256 ;
    b = sq % 256 ;
    sq = sq / 256 ;
    a = ( sq + 128 ) % 256 ;
  } 
  sw = ( ( ( ( ( d * z ) / 256 ) + ( c * z ) ) / 256 ) + ( b * z ) ) / beta ;
  if ( a == 0 ) 
  Result = sw ;
  else if ( a == 255 ) 
  Result = sw - alpha ;
  else pdferror ( 968 , 969 ) ;
  return Result ;
} 
void 
zcharwarning ( internalfontnumber f , eightbits c ) 
{
  charwarning_regmem 
  integer oldsetting  ;
  if ( eqtb [29309 ].cint > 0 ) 
  {
    oldsetting = eqtb [29303 ].cint ;
    if ( ( eTeXmode == 1 ) && ( eqtb [29309 ].cint > 1 ) ) 
    eqtb [29303 ].cint = 1 ;
    {
      begindiagnostic () ;
      printnl ( 978 ) ;
      print ( c ) ;
      print ( 979 ) ;
      slowprint ( fontname [f ]) ;
      printchar ( 33 ) ;
      enddiagnostic ( false ) ;
    } 
    eqtb [29303 ].cint = oldsetting ;
  } 
} 
halfword 
znewcharacter ( internalfontnumber f , eightbits c ) 
{
  /* 10 */ register halfword Result; newcharacter_regmem 
  halfword p  ;
  quarterword ec  ;
  ec = effectivechar ( false , f , c ) ;
  if ( fontbc [f ]<= ec ) {
      
    if ( fontec [f ]>= ec ) {
	
      if ( ( fontinfo [charbase [f ]+ ec ].qqqq .b0 > 0 ) ) 
      {
	p = getavail () ;
	mem [p ].hh.b0 = f ;
	mem [p ].hh.b1 = c ;
	Result = p ;
	return Result ;
      } 
    } 
  } 
  charwarning ( f , c ) ;
  Result = -268435455L ;
  return Result ;
} 
void 
dviswap ( void ) 
{
  dviswap_regmem 
  if ( dviptr > ( 2147483647L - dvioffset ) ) 
  {
    curs = -2 ;
    fatalerror ( 980 ) ;
  } 
  if ( dvilimit == dvibufsize ) 
  {
    writedvi ( 0 , halfbuf - 1 ) ;
    dvilimit = halfbuf ;
    dvioffset = dvioffset + dvibufsize ;
    dviptr = 0 ;
  } 
  else {
      
    writedvi ( halfbuf , dvibufsize - 1 ) ;
    dvilimit = dvibufsize ;
  } 
  dvigone = dvigone + halfbuf ;
} 
void 
zdvifour ( integer x ) 
{
  dvifour_regmem 
  if ( x >= 0 ) 
  {
    dvibuf [dviptr ]= x / 16777216L ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  else {
      
    x = x + 1073741824L ;
    x = x + 1073741824L ;
    {
      dvibuf [dviptr ]= ( x / 16777216L ) + 128 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
  } 
  x = x % 16777216L ;
  {
    dvibuf [dviptr ]= x / 65536L ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  x = x % 65536L ;
  {
    dvibuf [dviptr ]= x / 256 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  {
    dvibuf [dviptr ]= x % 256 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
} 
void 
zdvipop ( integer l ) 
{
  dvipop_regmem 
  if ( ( l == dvioffset + dviptr ) && ( dviptr > 0 ) ) 
  decr ( dviptr ) ;
  else {
      
    dvibuf [dviptr ]= 142 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
} 
void 
zdvifontdef ( internalfontnumber f ) 
{
  dvifontdef_regmem 
  poolpointer k  ;
  if ( f <= 256 ) 
  {
    {
      dvibuf [dviptr ]= 243 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {
      dvibuf [dviptr ]= f - 1 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
  } 
  else {
      
    {
      dvibuf [dviptr ]= 244 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {
      dvibuf [dviptr ]= ( f - 1 ) / 256 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {
      dvibuf [dviptr ]= ( f - 1 ) % 256 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
  } 
  {
    dvibuf [dviptr ]= fontcheck [f ].b0 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  {
    dvibuf [dviptr ]= fontcheck [f ].b1 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  {
    dvibuf [dviptr ]= fontcheck [f ].b2 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  {
    dvibuf [dviptr ]= fontcheck [f ].b3 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  dvifour ( fontsize [f ]) ;
  dvifour ( fontdsize [f ]) ;
  {
    dvibuf [dviptr ]= ( strstart [fontarea [f ]+ 1 ]- strstart [
    fontarea [f ]]) ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  {
    dvibuf [dviptr ]= ( strstart [fontname [f ]+ 1 ]- strstart [
    fontname [f ]]) ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  {register integer for_end; k = strstart [fontarea [f ]];for_end = 
  strstart [fontarea [f ]+ 1 ]- 1 ; if ( k <= for_end) do 
    {
      dvibuf [dviptr ]= strpool [k ];
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
  while ( k++ < for_end ) ;} 
  {register integer for_end; k = strstart [fontname [f ]];for_end = 
  strstart [fontname [f ]+ 1 ]- 1 ; if ( k <= for_end) do 
    {
      dvibuf [dviptr ]= strpool [k ];
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
  while ( k++ < for_end ) ;} 
} 
void 
zmovement ( scaled w , eightbits o ) 
{
  /* 10 40 45 2 1 */ movement_regmem 
  smallnumber mstate  ;
  halfword p, q  ;
  integer k  ;
  q = getnode ( 3 ) ;
  mem [q + 1 ].cint = w ;
  mem [q + 2 ].cint = dvioffset + dviptr ;
  if ( o == 157 ) 
  {
    mem [q ].hh .v.RH = downptr ;
    downptr = q ;
  } 
  else {
      
    mem [q ].hh .v.RH = rightptr ;
    rightptr = q ;
  } 
  p = mem [q ].hh .v.RH ;
  mstate = 0 ;
  while ( p != -268435455L ) {
      
    if ( mem [p + 1 ].cint == w ) 
    switch ( mstate + mem [p ].hh .v.LH ) 
    {case 3 : 
    case 4 : 
    case 15 : 
    case 16 : 
      if ( mem [p + 2 ].cint < dvigone ) 
      goto lab45 ;
      else {
	  
	k = mem [p + 2 ].cint - dvioffset ;
	if ( k < 0 ) 
	k = k + dvibufsize ;
	dvibuf [k ]= dvibuf [k ]+ 5 ;
	mem [p ].hh .v.LH = 1 ;
	goto lab40 ;
      } 
      break ;
    case 5 : 
    case 9 : 
    case 11 : 
      if ( mem [p + 2 ].cint < dvigone ) 
      goto lab45 ;
      else {
	  
	k = mem [p + 2 ].cint - dvioffset ;
	if ( k < 0 ) 
	k = k + dvibufsize ;
	dvibuf [k ]= dvibuf [k ]+ 10 ;
	mem [p ].hh .v.LH = 2 ;
	goto lab40 ;
      } 
      break ;
    case 1 : 
    case 2 : 
    case 8 : 
    case 13 : 
      goto lab40 ;
      break ;
      default: 
      ;
      break ;
    } 
    else switch ( mstate + mem [p ].hh .v.LH ) 
    {case 1 : 
      mstate = 6 ;
      break ;
    case 2 : 
      mstate = 12 ;
      break ;
    case 8 : 
    case 13 : 
      goto lab45 ;
      break ;
      default: 
      ;
      break ;
    } 
    p = mem [p ].hh .v.RH ;
  } 
  lab45: ;
  mem [q ].hh .v.LH = 3 ;
  if ( abs ( w ) >= 8388608L ) 
  {
    {
      dvibuf [dviptr ]= o + 3 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    dvifour ( w ) ;
    return ;
  } 
  if ( abs ( w ) >= 32768L ) 
  {
    {
      dvibuf [dviptr ]= o + 2 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    if ( w < 0 ) 
    w = w + 16777216L ;
    {
      dvibuf [dviptr ]= w / 65536L ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    w = w % 65536L ;
    goto lab2 ;
  } 
  if ( abs ( w ) >= 128 ) 
  {
    {
      dvibuf [dviptr ]= o + 1 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    if ( w < 0 ) 
    w = w + 65536L ;
    goto lab2 ;
  } 
  {
    dvibuf [dviptr ]= o ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  if ( w < 0 ) 
  w = w + 256 ;
  goto lab1 ;
  lab2: {
      
    dvibuf [dviptr ]= w / 256 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  lab1: {
      
    dvibuf [dviptr ]= w % 256 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  return ;
  lab40: mem [q ].hh .v.LH = mem [p ].hh .v.LH ;
  if ( mem [q ].hh .v.LH == 1 ) 
  {
    {
      dvibuf [dviptr ]= o + 4 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    while ( mem [q ].hh .v.RH != p ) {
	
      q = mem [q ].hh .v.RH ;
      switch ( mem [q ].hh .v.LH ) 
      {case 3 : 
	mem [q ].hh .v.LH = 5 ;
	break ;
      case 4 : 
	mem [q ].hh .v.LH = 6 ;
	break ;
	default: 
	;
	break ;
      } 
    } 
  } 
  else {
      
    {
      dvibuf [dviptr ]= o + 9 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    while ( mem [q ].hh .v.RH != p ) {
	
      q = mem [q ].hh .v.RH ;
      switch ( mem [q ].hh .v.LH ) 
      {case 3 : 
	mem [q ].hh .v.LH = 4 ;
	break ;
      case 5 : 
	mem [q ].hh .v.LH = 6 ;
	break ;
	default: 
	;
	break ;
      } 
    } 
  } 
} 
void 
zprunemovements ( integer l ) 
{
  /* 30 10 */ prunemovements_regmem 
  halfword p  ;
  while ( downptr != -268435455L ) {
      
    if ( mem [downptr + 2 ].cint < l ) 
    goto lab30 ;
    p = downptr ;
    downptr = mem [p ].hh .v.RH ;
    freenode ( p , 3 ) ;
  } 
  lab30: while ( rightptr != -268435455L ) {
      
    if ( mem [rightptr + 2 ].cint < l ) 
    return ;
    p = rightptr ;
    rightptr = mem [p ].hh .v.RH ;
    freenode ( p , 3 ) ;
  } 
} 
void 
zspecialout ( halfword p ) 
{
  specialout_regmem 
  unsigned char oldsetting  ;
  poolpointer k  ;
  if ( curh != dvih ) 
  {
    movement ( curh - dvih , 143 ) ;
    dvih = curh ;
  } 
  if ( curv != dviv ) 
  {
    movement ( curv - dviv , 157 ) ;
    dviv = curv ;
  } 
  oldsetting = selector ;
  selector = 21 ;
  showtokenlist ( mem [mem [p + 1 ].hh .v.RH ].hh .v.RH , -268435455L , 
  poolsize - poolptr ) ;
  selector = oldsetting ;
  {
    if ( poolptr + 1 > poolsize ) 
    overflow ( 259 , poolsize - initpoolptr ) ;
  } 
  if ( ( poolptr - strstart [strptr ]) < 256 ) 
  {
    {
      dvibuf [dviptr ]= 239 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {
      dvibuf [dviptr ]= ( poolptr - strstart [strptr ]) ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
  } 
  else {
      
    {
      dvibuf [dviptr ]= 242 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    dvifour ( ( poolptr - strstart [strptr ]) ) ;
  } 
  {register integer for_end; k = strstart [strptr ];for_end = poolptr - 1 
  ; if ( k <= for_end) do 
    {
      dvibuf [dviptr ]= strpool [k ];
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
  while ( k++ < for_end ) ;} 
  poolptr = strstart [strptr ];
} 
void 
zwriteout ( halfword p ) 
{
  writeout_regmem 
  unsigned char oldsetting  ;
  integer oldmode  ;
  smallnumber j  ;
  halfword q, r  ;
  integer d  ;
  boolean clobbered  ;
  integer runsystemret  ;
  q = getavail () ;
  mem [q ].hh .v.LH = 637 ;
  r = getavail () ;
  mem [q ].hh .v.RH = r ;
  mem [r ].hh .v.LH = 19617 ;
  begintokenlist ( q , 4 ) ;
  begintokenlist ( mem [p + 1 ].hh .v.RH , 20 ) ;
  q = getavail () ;
  mem [q ].hh .v.LH = 379 ;
  begintokenlist ( q , 4 ) ;
  oldmode = curlist .modefield ;
  curlist .modefield = 0 ;
  curcs = writeloc ;
  q = scantoks ( false , true ) ;
  gettoken () ;
  if ( curtok != 19617 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 1900 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 1901 ;
      helpline [0 ]= 1419 ;
    } 
    error () ;
    do {
	gettoken () ;
    } while ( ! ( curtok == 19617 ) ) ;
  } 
  curlist .modefield = oldmode ;
  endtokenlist () ;
  oldsetting = selector ;
  j = mem [p + 1 ].hh .v.LH ;
  if ( j == 18 ) 
  selector = 21 ;
  else if ( writeopen [j ]) 
  selector = j ;
  else {
      
    if ( ( j == 17 ) && ( selector == 19 ) ) 
    selector = 18 ;
    printnl ( 345 ) ;
  } 
  tokenshow ( defref ) ;
  println () ;
  flushlist ( defref ) ;
  if ( j == 18 ) 
  {
    if ( ( eqtb [29303 ].cint <= 0 ) ) 
    selector = 18 ;
    else selector = 19 ;
    if ( ! logopened ) 
    selector = 17 ;
    printnl ( 1892 ) ;
    {register integer for_end; d = 0 ;for_end = ( poolptr - strstart [
    strptr ]) - 1 ; if ( d <= for_end) do 
      {
	print ( strpool [strstart [strptr ]+ d ]) ;
      } 
    while ( d++ < for_end ) ;} 
    print ( 1893 ) ;
    if ( shellenabledp ) 
    {
      {
	if ( poolptr + 1 > poolsize ) 
	overflow ( 259 , poolsize - initpoolptr ) ;
      } 
      {
	strpool [poolptr ]= 0 ;
	incr ( poolptr ) ;
      } 
      clobbered = false ;
      {register integer for_end; d = 0 ;for_end = ( poolptr - strstart [
      strptr ]) - 1 ; if ( d <= for_end) do 
	{
	  strpool [strstart [strptr ]+ d ]= xchr [strpool [strstart [
	  strptr ]+ d ]];
	  if ( ( strpool [strstart [strptr ]+ d ]== 0 ) && ( d < ( poolptr 
	  - strstart [strptr ]) - 1 ) ) 
	  clobbered = true ;
	} 
      while ( d++ < for_end ) ;} 
      if ( clobbered ) 
      print ( 1894 ) ;
      else {
	  
	runsystemret = runsystem ( conststringcast ( addressof ( strpool [
	strstart [strptr ]]) ) ) ;
	if ( runsystemret == -1 ) 
	print ( 1895 ) ;
	else if ( runsystemret == 0 ) 
	print ( 1896 ) ;
	else if ( runsystemret == 1 ) 
	print ( 1897 ) ;
	else if ( runsystemret == 2 ) 
	print ( 1898 ) ;
      } 
    } 
    else {
	
      print ( 1899 ) ;
    } 
    printchar ( 46 ) ;
    printnl ( 345 ) ;
    println () ;
    poolptr = strstart [strptr ];
  } 
  selector = oldsetting ;
} 
void 
zoutwhat ( halfword p ) 
{
  outwhat_regmem 
  smallnumber j  ;
  unsigned char oldsetting  ;
  switch ( mem [p ].hh.b1 ) 
  {case 0 : 
  case 1 : 
  case 2 : 
    if ( ! doingleaders ) 
    {
      j = mem [p + 1 ].hh .v.LH ;
      if ( mem [p ].hh.b1 == 1 ) 
      writeout ( p ) ;
      else {
	  
	if ( writeopen [j ]) 
	aclose ( writefile [j ]) ;
	if ( mem [p ].hh.b1 == 2 ) 
	writeopen [j ]= false ;
	else if ( j < 16 ) 
	{
	  curname = mem [p + 1 ].hh .v.RH ;
	  curarea = mem [p + 2 ].hh .v.LH ;
	  curext = mem [p + 2 ].hh .v.RH ;
	  if ( curext == 345 ) 
	  curext = 939 ;
	  packfilename ( curname , curarea , curext ) ;
	  while ( ! kpseoutnameok ( stringcast ( nameoffile + 1 ) ) || ! 
	  aopenout ( writefile [j ]) ) promptfilename ( 1903 , 939 ) ;
	  writeopen [j ]= true ;
	  if ( logopened ) 
	  {
	    oldsetting = selector ;
	    if ( ( eqtb [29303 ].cint <= 0 ) ) 
	    selector = 18 ;
	    else selector = 19 ;
	    printnl ( 1904 ) ;
	    printint ( j ) ;
	    print ( 1905 ) ;
	    printfilename ( curname , curarea , curext ) ;
	    print ( 938 ) ;
	    printnl ( 345 ) ;
	    println () ;
	    selector = oldsetting ;
	  } 
	} 
      } 
    } 
    break ;
  case 3 : 
    specialout ( p ) ;
    break ;
  case 4 : 
    ;
    break ;
  case 21 : 
    {
      pdflastxpos = curh + 4736286L ;
      pdflastypos = curpageheight - curv - 4736286L ;
    } 
    break ;
    default: 
    {
      if ( ( 6 <= mem [p ].hh.b1 ) && ( mem [p ].hh.b1 <= 45 ) ) 
      pdferror ( 1838 , 1902 ) ;
      else confusion ( 1838 ) ;
    } 
    break ;
  } 
} 
halfword 
znewedge ( smallnumber s , scaled w ) 
{
  register halfword Result; newedge_regmem 
  halfword p  ;
  p = getnode ( 3 ) ;
  mem [p ].hh.b0 = 14 ;
  mem [p ].hh.b1 = s ;
  mem [p + 1 ].cint = w ;
  mem [p + 2 ].cint = 0 ;
  Result = p ;
  return Result ;
} 
halfword 
zzreverse ( halfword thisbox , halfword t , scaled * curg , real * curglue ) 
{
  /* 21 15 30 */ register halfword Result; reverse_regmem 
  halfword l  ;
  halfword p  ;
  halfword q  ;
  glueord gorder  ;
  unsigned char gsign  ;
  real gluetemp  ;
  halfword m, n  ;
  gorder = mem [thisbox + 5 ].hh.b1 ;
  gsign = mem [thisbox + 5 ].hh.b0 ;
  l = t ;
  p = tempptr ;
  m = -268435455L ;
  n = -268435455L ;
  while ( true ) {
      
    while ( p != -268435455L ) lab21: if ( ( p >= himemmin ) ) 
    do {
	f = mem [p ].hh.b0 ;
      c = mem [p ].hh.b1 ;
      curh = curh + fontinfo [widthbase [f ]+ fontinfo [charbase [f ]+ 
      effectivechar ( true , f , c ) ].qqqq .b0 ].cint ;
      q = mem [p ].hh .v.RH ;
      mem [p ].hh .v.RH = l ;
      l = p ;
      p = q ;
    } while ( ! ( ! ( p >= himemmin ) ) ) ;
    else {
	
      q = mem [p ].hh .v.RH ;
      switch ( mem [p ].hh.b0 ) 
      {case 0 : 
      case 1 : 
      case 2 : 
      case 11 : 
	rulewd = mem [p + 1 ].cint ;
	break ;
      case 10 : 
	{
	  g = mem [p + 1 ].hh .v.LH ;
	  rulewd = mem [g + 1 ].cint - *curg ;
	  if ( gsign != 0 ) 
	  {
	    if ( gsign == 1 ) 
	    {
	      if ( mem [g ].hh.b0 == gorder ) 
	      {
*                curglue = *curglue + mem [g + 2 ].cint ;
		gluetemp = mem [thisbox + 6 ].gr * *curglue ;
		if ( gluetemp > 1000000000.0 ) 
		gluetemp = 1000000000.0 ;
		else if ( gluetemp < -1000000000.0 ) 
		gluetemp = -1000000000.0 ;
*                curg = round ( gluetemp ) ;
	      } 
	    } 
	    else if ( mem [g ].hh.b1 == gorder ) 
	    {
*              curglue = *curglue - mem [g + 3 ].cint ;
	      gluetemp = mem [thisbox + 6 ].gr * *curglue ;
	      if ( gluetemp > 1000000000.0 ) 
	      gluetemp = 1000000000.0 ;
	      else if ( gluetemp < -1000000000.0 ) 
	      gluetemp = -1000000000.0 ;
*              curg = round ( gluetemp ) ;
	    } 
	  } 
	  rulewd = rulewd + *curg ;
	  if ( ( ( ( gsign == 1 ) && ( mem [g ].hh.b0 == gorder ) ) || ( ( 
	  gsign == 2 ) && ( mem [g ].hh.b1 == gorder ) ) ) ) 
	  {
	    {
	      if ( mem [g ].hh .v.RH == -268435455L ) 
	      freenode ( g , 4 ) ;
	      else decr ( mem [g ].hh .v.RH ) ;
	    } 
	    if ( mem [p ].hh.b1 < 100 ) 
	    {
	      mem [p ].hh.b0 = 11 ;
	      mem [p + 1 ].cint = rulewd ;
	    } 
	    else {
		
	      g = getnode ( 4 ) ;
	      mem [g ].hh.b0 = 4 ;
	      mem [g ].hh.b1 = 4 ;
	      mem [g + 1 ].cint = rulewd ;
	      mem [g + 2 ].cint = 0 ;
	      mem [g + 3 ].cint = 0 ;
	      mem [p + 1 ].hh .v.LH = g ;
	    } 
	  } 
	} 
	break ;
      case 6 : 
	{
	  flushnodelist ( mem [p + 1 ].hh .v.RH ) ;
	  tempptr = p ;
	  p = getavail () ;
	  mem [p ]= mem [tempptr + 1 ];
	  mem [p ].hh .v.RH = q ;
	  freenode ( tempptr , 2 ) ;
	  goto lab21 ;
	} 
	break ;
      case 9 : 
	{
	  rulewd = mem [p + 1 ].cint ;
	  if ( odd ( mem [p ].hh.b1 ) ) {
	      
	    if ( mem [LRptr ].hh .v.LH != ( 4 * ( mem [p ].hh.b1 / 4 ) + 3 
	    ) ) 
	    {
	      mem [p ].hh.b0 = 11 ;
	      incr ( LRproblems ) ;
	    } 
	    else {
		
	      {
		tempptr = LRptr ;
		LRptr = mem [tempptr ].hh .v.RH ;
		{
		  mem [tempptr ].hh .v.RH = avail ;
		  avail = tempptr ;
	;
#ifdef STAT
		  decr ( dynused ) ;
#endif /* STAT */
		} 
	      } 
	      if ( n > -268435455L ) 
	      {
		decr ( n ) ;
		decr ( mem [p ].hh.b1 ) ;
	      } 
	      else {
		  
		mem [p ].hh.b0 = 11 ;
		if ( m > -268435455L ) 
		decr ( m ) ;
		else {
		    
		  freenode ( p , 2 ) ;
		  mem [t ].hh .v.RH = q ;
		  mem [t + 1 ].cint = rulewd ;
		  mem [t + 2 ].cint = - (integer) curh - rulewd ;
		  goto lab30 ;
		} 
	      } 
	    } 
	  } 
	  else {
	      
	    {
	      tempptr = getavail () ;
	      mem [tempptr ].hh .v.LH = ( 4 * ( mem [p ].hh.b1 / 4 ) + 3 ) 
	      ;
	      mem [tempptr ].hh .v.RH = LRptr ;
	      LRptr = tempptr ;
	    } 
	    if ( ( n > -268435455L ) || ( ( mem [p ].hh.b1 / 8 ) != curdir ) 
	    ) 
	    {
	      incr ( n ) ;
	      incr ( mem [p ].hh.b1 ) ;
	    } 
	    else {
		
	      mem [p ].hh.b0 = 11 ;
	      incr ( m ) ;
	    } 
	  } 
	} 
	break ;
      case 14 : 
	confusion ( 2011 ) ;
	break ;
	default: 
	goto lab15 ;
	break ;
      } 
      curh = curh + rulewd ;
      lab15: mem [p ].hh .v.RH = l ;
      if ( mem [p ].hh.b0 == 11 ) {
	  
	if ( ( rulewd == 0 ) || ( l == -268435455L ) ) 
	{
	  freenode ( p , 2 ) ;
	  p = l ;
	} 
      } 
      l = p ;
      p = q ;
    } 
    if ( ( t == -268435455L ) && ( m == -268435455L ) && ( n == -268435455L ) 
    ) 
    goto lab30 ;
    p = newmath ( 0 , mem [LRptr ].hh .v.LH ) ;
    LRproblems = LRproblems + 10000 ;
  } 
  lab30: Result = l ;
  return Result ;
} 
void 
hlistout ( void ) 
{
  /* 21 13 14 15 22 40 */ hlistout_regmem 
  scaled baseline  ;
  scaled leftedge  ;
  scaled saveh, savev  ;
  halfword thisbox  ;
  glueord gorder  ;
  unsigned char gsign  ;
  halfword p  ;
  integer saveloc  ;
  halfword leaderbox  ;
  scaled leaderwd  ;
  scaled lx  ;
  boolean outerdoingleaders  ;
  scaled edge  ;
  halfword prevp  ;
  real gluetemp  ;
  real curglue  ;
  scaled curg  ;
  curg = 0 ;
  curglue = 0.0 ;
  thisbox = tempptr ;
  gorder = mem [thisbox + 5 ].hh.b1 ;
  gsign = mem [thisbox + 5 ].hh.b0 ;
  p = mem [thisbox + 5 ].hh .v.RH ;
  incr ( curs ) ;
  if ( curs > 0 ) 
  {
    dvibuf [dviptr ]= 141 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  if ( curs > maxpush ) 
  maxpush = curs ;
  saveloc = dvioffset + dviptr ;
  baseline = curv ;
  prevp = thisbox + 5 ;
  if ( ( eTeXmode == 1 ) ) 
  {
    {
      tempptr = getavail () ;
      mem [tempptr ].hh .v.LH = 0 ;
      mem [tempptr ].hh .v.RH = LRptr ;
      LRptr = tempptr ;
    } 
    if ( ( mem [thisbox ].hh.b1 ) == 2 ) {
	
      if ( curdir == 1 ) 
      {
	curdir = 0 ;
	curh = curh - mem [thisbox + 1 ].cint ;
      } 
      else mem [thisbox ].hh.b1 = 0 ;
    } 
    if ( ( curdir == 1 ) && ( ( mem [thisbox ].hh.b1 ) != 1 ) ) 
    {
      saveh = curh ;
      tempptr = p ;
      p = newkern ( 0 ) ;
      mem [prevp ].hh .v.RH = p ;
      curh = 0 ;
      mem [p ].hh .v.RH = reverse ( thisbox , -268435455L , curg , curglue ) 
      ;
      mem [p + 1 ].cint = - (integer) curh ;
      curh = saveh ;
      mem [thisbox ].hh.b1 = 1 ;
    } 
  } 
  leftedge = curh ;
  while ( p != -268435455L ) lab21: if ( ( p >= himemmin ) ) 
  {
    if ( curh != dvih ) 
    {
      movement ( curh - dvih , 143 ) ;
      dvih = curh ;
    } 
    if ( curv != dviv ) 
    {
      movement ( curv - dviv , 157 ) ;
      dviv = curv ;
    } 
    do {
	f = mem [p ].hh.b0 ;
      c = mem [p ].hh.b1 ;
      if ( f != dvif ) 
      {
	if ( ! fontused [f ]) 
	{
	  dvifontdef ( f ) ;
	  fontused [f ]= true ;
	} 
	if ( f <= 64 ) 
	{
	  dvibuf [dviptr ]= f + 170 ;
	  incr ( dviptr ) ;
	  if ( dviptr == dvilimit ) 
	  dviswap () ;
	} 
	else if ( f <= 256 ) 
	{
	  {
	    dvibuf [dviptr ]= 235 ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	  {
	    dvibuf [dviptr ]= f - 1 ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	} 
	else {
	    
	  {
	    dvibuf [dviptr ]= 236 ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	  {
	    dvibuf [dviptr ]= ( f - 1 ) / 256 ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	  {
	    dvibuf [dviptr ]= ( f - 1 ) % 256 ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	} 
	dvif = f ;
      } 
      if ( fontec [f ]>= c ) {
	  
	if ( fontbc [f ]<= c ) {
	    
	  if ( ( fontinfo [charbase [f ]+ c ].qqqq .b0 > 0 ) ) 
	  {
	    if ( c >= 128 ) 
	    {
	      dvibuf [dviptr ]= 128 ;
	      incr ( dviptr ) ;
	      if ( dviptr == dvilimit ) 
	      dviswap () ;
	    } 
	    {
	      dvibuf [dviptr ]= c ;
	      incr ( dviptr ) ;
	      if ( dviptr == dvilimit ) 
	      dviswap () ;
	    } 
	    curh = curh + fontinfo [widthbase [f ]+ fontinfo [charbase [f 
	    ]+ c ].qqqq .b0 ].cint ;
	    goto lab22 ;
	  } 
	} 
      } 
      if ( mltexenabledp ) 
      {
	if ( c >= eqtb [29329 ].cint ) {
	    
	  if ( c <= eqtb [29330 ].cint ) {
	      
	    if ( ( eqtb [29018 + c ].hh .v.RH > 0 ) ) 
	    {
	      basec = ( eqtb [29018 + c ].hh .v.RH % 256 ) ;
	      accentc = ( eqtb [29018 + c ].hh .v.RH / 256 ) ;
	      if ( ( fontec [f ]>= basec ) ) {
		  
		if ( ( fontbc [f ]<= basec ) ) {
		    
		  if ( ( fontec [f ]>= accentc ) ) {
		      
		    if ( ( fontbc [f ]<= accentc ) ) 
		    {
		      iac = fontinfo [charbase [f ]+ effectivechar ( true , 
		      f , accentc ) ].qqqq ;
		      ibc = fontinfo [charbase [f ]+ effectivechar ( true , 
		      f , basec ) ].qqqq ;
		      if ( ( ibc .b0 > 0 ) ) {
			  
			if ( ( iac .b0 > 0 ) ) 
			goto lab40 ;
		      } 
		    } 
		  } 
		} 
	      } 
	      begindiagnostic () ;
	      printnl ( 2057 ) ;
	      print ( c ) ;
	      print ( 1614 ) ;
	      print ( accentc ) ;
	      print ( 32 ) ;
	      print ( basec ) ;
	      print ( 979 ) ;
	      slowprint ( fontname [f ]) ;
	      printchar ( 33 ) ;
	      enddiagnostic ( false ) ;
	      goto lab22 ;
	    } 
	  } 
	} 
	begindiagnostic () ;
	printnl ( 978 ) ;
	print ( 2056 ) ;
	print ( c ) ;
	print ( 979 ) ;
	slowprint ( fontname [f ]) ;
	printchar ( 33 ) ;
	enddiagnostic ( false ) ;
	goto lab22 ;
	lab40: if ( eqtb [29309 ].cint > 99 ) 
	{
	  begindiagnostic () ;
	  printnl ( 2058 ) ;
	  print ( c ) ;
	  print ( 1614 ) ;
	  print ( accentc ) ;
	  print ( 32 ) ;
	  print ( basec ) ;
	  print ( 979 ) ;
	  slowprint ( fontname [f ]) ;
	  printchar ( 46 ) ;
	  enddiagnostic ( false ) ;
	} 
	basexheight = fontinfo [5 + parambase [f ]].cint ;
	baseslant = fontinfo [1 + parambase [f ]].cint / ((double) 65536.0 
	) ;
	accentslant = baseslant ;
	basewidth = fontinfo [widthbase [f ]+ ibc .b0 ].cint ;
	baseheight = fontinfo [heightbase [f ]+ ( ibc .b1 ) / 16 ].cint ;
	accentwidth = fontinfo [widthbase [f ]+ iac .b0 ].cint ;
	accentheight = fontinfo [heightbase [f ]+ ( iac .b1 ) / 16 ].cint 
	;
	delta = round ( ( basewidth - accentwidth ) / ((double) 2.0 ) + 
	baseheight * baseslant - basexheight * accentslant ) ;
	dvih = curh ;
	curh = curh + delta ;
	if ( curh != dvih ) 
	{
	  movement ( curh - dvih , 143 ) ;
	  dvih = curh ;
	} 
	if ( ( ( baseheight != basexheight ) && ( accentheight > 0 ) ) ) 
	{
	  curv = baseline + ( basexheight - baseheight ) ;
	  if ( curv != dviv ) 
	  {
	    movement ( curv - dviv , 157 ) ;
	    dviv = curv ;
	  } 
	  if ( accentc >= 128 ) 
	  {
	    dvibuf [dviptr ]= 128 ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	  {
	    dvibuf [dviptr ]= accentc ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	  curv = baseline ;
	} 
	else {
	    
	  if ( curv != dviv ) 
	  {
	    movement ( curv - dviv , 157 ) ;
	    dviv = curv ;
	  } 
	  if ( accentc >= 128 ) 
	  {
	    dvibuf [dviptr ]= 128 ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	  {
	    dvibuf [dviptr ]= accentc ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	} 
	curh = curh + accentwidth ;
	dvih = curh ;
	curh = curh + ( - (integer) accentwidth - delta ) ;
	if ( curh != dvih ) 
	{
	  movement ( curh - dvih , 143 ) ;
	  dvih = curh ;
	} 
	if ( curv != dviv ) 
	{
	  movement ( curv - dviv , 157 ) ;
	  dviv = curv ;
	} 
	if ( basec >= 128 ) 
	{
	  dvibuf [dviptr ]= 128 ;
	  incr ( dviptr ) ;
	  if ( dviptr == dvilimit ) 
	  dviswap () ;
	} 
	{
	  dvibuf [dviptr ]= basec ;
	  incr ( dviptr ) ;
	  if ( dviptr == dvilimit ) 
	  dviswap () ;
	} 
	curh = curh + basewidth ;
	dvih = curh ;
      } 
      lab22: prevp = mem [prevp ].hh .v.RH ;
      p = mem [p ].hh .v.RH ;
    } while ( ! ( ! ( p >= himemmin ) ) ) ;
    dvih = curh ;
  } 
  else {
      
    switch ( mem [p ].hh.b0 ) 
    {case 0 : 
    case 1 : 
      if ( mem [p + 5 ].hh .v.RH == -268435455L ) 
      curh = curh + mem [p + 1 ].cint ;
      else {
	  
	saveh = dvih ;
	savev = dviv ;
	curv = baseline + mem [p + 4 ].cint ;
	tempptr = p ;
	edge = curh + mem [p + 1 ].cint ;
	if ( curdir == 1 ) 
	curh = edge ;
	if ( mem [p ].hh.b0 == 1 ) 
	vlistout () ;
	else hlistout () ;
	dvih = saveh ;
	dviv = savev ;
	curh = edge ;
	curv = baseline ;
      } 
      break ;
    case 2 : 
      {
	ruleht = mem [p + 3 ].cint ;
	ruledp = mem [p + 2 ].cint ;
	rulewd = mem [p + 1 ].cint ;
	goto lab14 ;
      } 
      break ;
    case 8 : 
      outwhat ( p ) ;
      break ;
    case 10 : 
      {
	g = mem [p + 1 ].hh .v.LH ;
	rulewd = mem [g + 1 ].cint - curg ;
	if ( gsign != 0 ) 
	{
	  if ( gsign == 1 ) 
	  {
	    if ( mem [g ].hh.b0 == gorder ) 
	    {
	      curglue = curglue + mem [g + 2 ].cint ;
	      gluetemp = mem [thisbox + 6 ].gr * curglue ;
	      if ( gluetemp > 1000000000.0 ) 
	      gluetemp = 1000000000.0 ;
	      else if ( gluetemp < -1000000000.0 ) 
	      gluetemp = -1000000000.0 ;
	      curg = round ( gluetemp ) ;
	    } 
	  } 
	  else if ( mem [g ].hh.b1 == gorder ) 
	  {
	    curglue = curglue - mem [g + 3 ].cint ;
	    gluetemp = mem [thisbox + 6 ].gr * curglue ;
	    if ( gluetemp > 1000000000.0 ) 
	    gluetemp = 1000000000.0 ;
	    else if ( gluetemp < -1000000000.0 ) 
	    gluetemp = -1000000000.0 ;
	    curg = round ( gluetemp ) ;
	  } 
	} 
	rulewd = rulewd + curg ;
	if ( ( eTeXmode == 1 ) ) {
	    
	  if ( ( ( ( gsign == 1 ) && ( mem [g ].hh.b0 == gorder ) ) || ( ( 
	  gsign == 2 ) && ( mem [g ].hh.b1 == gorder ) ) ) ) 
	  {
	    {
	      if ( mem [g ].hh .v.RH == -268435455L ) 
	      freenode ( g , 4 ) ;
	      else decr ( mem [g ].hh .v.RH ) ;
	    } 
	    if ( mem [p ].hh.b1 < 100 ) 
	    {
	      mem [p ].hh.b0 = 11 ;
	      mem [p + 1 ].cint = rulewd ;
	    } 
	    else {
		
	      g = getnode ( 4 ) ;
	      mem [g ].hh.b0 = 4 ;
	      mem [g ].hh.b1 = 4 ;
	      mem [g + 1 ].cint = rulewd ;
	      mem [g + 2 ].cint = 0 ;
	      mem [g + 3 ].cint = 0 ;
	      mem [p + 1 ].hh .v.LH = g ;
	    } 
	  } 
	} 
	if ( mem [p ].hh.b1 >= 100 ) 
	{
	  leaderbox = mem [p + 1 ].hh .v.RH ;
	  if ( mem [leaderbox ].hh.b0 == 2 ) 
	  {
	    ruleht = mem [leaderbox + 3 ].cint ;
	    ruledp = mem [leaderbox + 2 ].cint ;
	    goto lab14 ;
	  } 
	  leaderwd = mem [leaderbox + 1 ].cint ;
	  if ( ( leaderwd > 0 ) && ( rulewd > 0 ) ) 
	  {
	    rulewd = rulewd + 10 ;
	    if ( curdir == 1 ) 
	    curh = curh - 10 ;
	    edge = curh + rulewd ;
	    lx = 0 ;
	    if ( mem [p ].hh.b1 == 100 ) 
	    {
	      saveh = curh ;
	      curh = leftedge + leaderwd * ( ( curh - leftedge ) / leaderwd ) 
	      ;
	      if ( curh < saveh ) 
	      curh = curh + leaderwd ;
	    } 
	    else {
		
	      lq = rulewd / leaderwd ;
	      lr = rulewd % leaderwd ;
	      if ( mem [p ].hh.b1 == 101 ) 
	      curh = curh + ( lr / 2 ) ;
	      else {
		  
		lx = lr / ( lq + 1 ) ;
		curh = curh + ( ( lr - ( lq - 1 ) * lx ) / 2 ) ;
	      } 
	    } 
	    while ( curh + leaderwd <= edge ) {
		
	      curv = baseline + mem [leaderbox + 4 ].cint ;
	      if ( curv != dviv ) 
	      {
		movement ( curv - dviv , 157 ) ;
		dviv = curv ;
	      } 
	      savev = dviv ;
	      if ( curh != dvih ) 
	      {
		movement ( curh - dvih , 143 ) ;
		dvih = curh ;
	      } 
	      saveh = dvih ;
	      tempptr = leaderbox ;
	      if ( curdir == 1 ) 
	      curh = curh + leaderwd ;
	      outerdoingleaders = doingleaders ;
	      doingleaders = true ;
	      if ( mem [leaderbox ].hh.b0 == 1 ) 
	      vlistout () ;
	      else hlistout () ;
	      doingleaders = outerdoingleaders ;
	      dviv = savev ;
	      dvih = saveh ;
	      curv = baseline ;
	      curh = saveh + leaderwd + lx ;
	    } 
	    if ( curdir == 1 ) 
	    curh = edge ;
	    else curh = edge - 10 ;
	    goto lab15 ;
	  } 
	} 
	goto lab13 ;
      } 
      break ;
    case 40 : 
    case 11 : 
      curh = curh + mem [p + 1 ].cint ;
      break ;
    case 9 : 
      {
	if ( ( eTeXmode == 1 ) ) 
	{
	  if ( odd ( mem [p ].hh.b1 ) ) {
	      
	    if ( mem [LRptr ].hh .v.LH == ( 4 * ( mem [p ].hh.b1 / 4 ) + 3 
	    ) ) 
	    {
	      tempptr = LRptr ;
	      LRptr = mem [tempptr ].hh .v.RH ;
	      {
		mem [tempptr ].hh .v.RH = avail ;
		avail = tempptr ;
	;
#ifdef STAT
		decr ( dynused ) ;
#endif /* STAT */
	      } 
	    } 
	    else {
		
	      if ( mem [p ].hh.b1 > 4 ) 
	      incr ( LRproblems ) ;
	    } 
	  } 
	  else {
	      
	    {
	      tempptr = getavail () ;
	      mem [tempptr ].hh .v.LH = ( 4 * ( mem [p ].hh.b1 / 4 ) + 3 ) 
	      ;
	      mem [tempptr ].hh .v.RH = LRptr ;
	      LRptr = tempptr ;
	    } 
	    if ( ( mem [p ].hh.b1 / 8 ) != curdir ) 
	    {
	      saveh = curh ;
	      tempptr = mem [p ].hh .v.RH ;
	      rulewd = mem [p + 1 ].cint ;
	      freenode ( p , 2 ) ;
	      curdir = 1 - curdir ;
	      p = newedge ( curdir , rulewd ) ;
	      mem [prevp ].hh .v.RH = p ;
	      curh = curh - leftedge + rulewd ;
	      mem [p ].hh .v.RH = reverse ( thisbox , newedge ( 1 - curdir , 
	      0 ) , curg , curglue ) ;
	      mem [p + 2 ].cint = curh ;
	      curdir = 1 - curdir ;
	      curh = saveh ;
	      goto lab21 ;
	    } 
	  } 
	  mem [p ].hh.b0 = 11 ;
	} 
	curh = curh + mem [p + 1 ].cint ;
      } 
      break ;
    case 6 : 
      {
	mem [memtop - 12 ]= mem [p + 1 ];
	mem [memtop - 12 ].hh .v.RH = mem [p ].hh .v.RH ;
	p = memtop - 12 ;
	goto lab21 ;
      } 
      break ;
    case 14 : 
      {
	curh = curh + mem [p + 1 ].cint ;
	leftedge = curh + mem [p + 2 ].cint ;
	curdir = mem [p ].hh.b1 ;
      } 
      break ;
      default: 
      ;
      break ;
    } 
    goto lab15 ;
    lab14: if ( ( ruleht == -1073741824L ) ) 
    ruleht = mem [thisbox + 3 ].cint ;
    if ( ( ruledp == -1073741824L ) ) 
    ruledp = mem [thisbox + 2 ].cint ;
    ruleht = ruleht + ruledp ;
    if ( ( ruleht > 0 ) && ( rulewd > 0 ) ) 
    {
      if ( curh != dvih ) 
      {
	movement ( curh - dvih , 143 ) ;
	dvih = curh ;
      } 
      curv = baseline + ruledp ;
      if ( curv != dviv ) 
      {
	movement ( curv - dviv , 157 ) ;
	dviv = curv ;
      } 
      {
	dvibuf [dviptr ]= 132 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      dvifour ( ruleht ) ;
      dvifour ( rulewd ) ;
      curv = baseline ;
      dvih = dvih + rulewd ;
    } 
    lab13: curh = curh + rulewd ;
    lab15: prevp = p ;
    p = mem [p ].hh .v.RH ;
  } 
  if ( ( eTeXmode == 1 ) ) 
  {
    {
      while ( mem [LRptr ].hh .v.LH != 0 ) {
	  
	if ( mem [LRptr ].hh .v.LH > 4 ) 
	LRproblems = LRproblems + 10000 ;
	{
	  tempptr = LRptr ;
	  LRptr = mem [tempptr ].hh .v.RH ;
	  {
	    mem [tempptr ].hh .v.RH = avail ;
	    avail = tempptr ;
	;
#ifdef STAT
	    decr ( dynused ) ;
#endif /* STAT */
	  } 
	} 
      } 
      {
	tempptr = LRptr ;
	LRptr = mem [tempptr ].hh .v.RH ;
	{
	  mem [tempptr ].hh .v.RH = avail ;
	  avail = tempptr ;
	;
#ifdef STAT
	  decr ( dynused ) ;
#endif /* STAT */
	} 
      } 
    } 
    if ( ( mem [thisbox ].hh.b1 ) == 2 ) 
    curdir = 1 ;
  } 
  prunemovements ( saveloc ) ;
  if ( curs > 0 ) 
  dvipop ( saveloc ) ;
  decr ( curs ) ;
} 
void 
vlistout ( void ) 
{
  /* 13 14 15 */ vlistout_regmem 
  scaled leftedge  ;
  scaled topedge  ;
  scaled saveh, savev  ;
  halfword thisbox  ;
  glueord gorder  ;
  unsigned char gsign  ;
  halfword p  ;
  integer saveloc  ;
  halfword leaderbox  ;
  scaled leaderht  ;
  scaled lx  ;
  boolean outerdoingleaders  ;
  scaled edge  ;
  real gluetemp  ;
  real curglue  ;
  scaled curg  ;
  curg = 0 ;
  curglue = 0.0 ;
  thisbox = tempptr ;
  gorder = mem [thisbox + 5 ].hh.b1 ;
  gsign = mem [thisbox + 5 ].hh.b0 ;
  p = mem [thisbox + 5 ].hh .v.RH ;
  incr ( curs ) ;
  if ( curs > 0 ) 
  {
    dvibuf [dviptr ]= 141 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  if ( curs > maxpush ) 
  maxpush = curs ;
  saveloc = dvioffset + dviptr ;
  leftedge = curh ;
  curv = curv - mem [thisbox + 3 ].cint ;
  topedge = curv ;
  while ( p != -268435455L ) {
      
    if ( ( p >= himemmin ) ) 
    confusion ( 982 ) ;
    else {
	
      switch ( mem [p ].hh.b0 ) 
      {case 0 : 
      case 1 : 
	if ( mem [p + 5 ].hh .v.RH == -268435455L ) 
	curv = curv + mem [p + 3 ].cint + mem [p + 2 ].cint ;
	else {
	    
	  curv = curv + mem [p + 3 ].cint ;
	  if ( curv != dviv ) 
	  {
	    movement ( curv - dviv , 157 ) ;
	    dviv = curv ;
	  } 
	  saveh = dvih ;
	  savev = dviv ;
	  if ( curdir == 1 ) 
	  curh = leftedge - mem [p + 4 ].cint ;
	  else curh = leftedge + mem [p + 4 ].cint ;
	  tempptr = p ;
	  if ( mem [p ].hh.b0 == 1 ) 
	  vlistout () ;
	  else hlistout () ;
	  dvih = saveh ;
	  dviv = savev ;
	  curv = savev + mem [p + 2 ].cint ;
	  curh = leftedge ;
	} 
	break ;
      case 2 : 
	{
	  ruleht = mem [p + 3 ].cint ;
	  ruledp = mem [p + 2 ].cint ;
	  rulewd = mem [p + 1 ].cint ;
	  goto lab14 ;
	} 
	break ;
      case 8 : 
	outwhat ( p ) ;
	break ;
      case 10 : 
	{
	  g = mem [p + 1 ].hh .v.LH ;
	  ruleht = mem [g + 1 ].cint - curg ;
	  if ( gsign != 0 ) 
	  {
	    if ( gsign == 1 ) 
	    {
	      if ( mem [g ].hh.b0 == gorder ) 
	      {
		curglue = curglue + mem [g + 2 ].cint ;
		gluetemp = mem [thisbox + 6 ].gr * curglue ;
		if ( gluetemp > 1000000000.0 ) 
		gluetemp = 1000000000.0 ;
		else if ( gluetemp < -1000000000.0 ) 
		gluetemp = -1000000000.0 ;
		curg = round ( gluetemp ) ;
	      } 
	    } 
	    else if ( mem [g ].hh.b1 == gorder ) 
	    {
	      curglue = curglue - mem [g + 3 ].cint ;
	      gluetemp = mem [thisbox + 6 ].gr * curglue ;
	      if ( gluetemp > 1000000000.0 ) 
	      gluetemp = 1000000000.0 ;
	      else if ( gluetemp < -1000000000.0 ) 
	      gluetemp = -1000000000.0 ;
	      curg = round ( gluetemp ) ;
	    } 
	  } 
	  ruleht = ruleht + curg ;
	  if ( mem [p ].hh.b1 >= 100 ) 
	  {
	    leaderbox = mem [p + 1 ].hh .v.RH ;
	    if ( mem [leaderbox ].hh.b0 == 2 ) 
	    {
	      rulewd = mem [leaderbox + 1 ].cint ;
	      ruledp = 0 ;
	      goto lab14 ;
	    } 
	    leaderht = mem [leaderbox + 3 ].cint + mem [leaderbox + 2 ]
	    .cint ;
	    if ( ( leaderht > 0 ) && ( ruleht > 0 ) ) 
	    {
	      ruleht = ruleht + 10 ;
	      edge = curv + ruleht ;
	      lx = 0 ;
	      if ( mem [p ].hh.b1 == 100 ) 
	      {
		savev = curv ;
		curv = topedge + leaderht * ( ( curv - topedge ) / leaderht ) 
		;
		if ( curv < savev ) 
		curv = curv + leaderht ;
	      } 
	      else {
		  
		lq = ruleht / leaderht ;
		lr = ruleht % leaderht ;
		if ( mem [p ].hh.b1 == 101 ) 
		curv = curv + ( lr / 2 ) ;
		else {
		    
		  lx = lr / ( lq + 1 ) ;
		  curv = curv + ( ( lr - ( lq - 1 ) * lx ) / 2 ) ;
		} 
	      } 
	      while ( curv + leaderht <= edge ) {
		  
		if ( curdir == 1 ) 
		curh = leftedge - mem [leaderbox + 4 ].cint ;
		else curh = leftedge + mem [leaderbox + 4 ].cint ;
		if ( curh != dvih ) 
		{
		  movement ( curh - dvih , 143 ) ;
		  dvih = curh ;
		} 
		saveh = dvih ;
		curv = curv + mem [leaderbox + 3 ].cint ;
		if ( curv != dviv ) 
		{
		  movement ( curv - dviv , 157 ) ;
		  dviv = curv ;
		} 
		savev = dviv ;
		tempptr = leaderbox ;
		outerdoingleaders = doingleaders ;
		doingleaders = true ;
		if ( mem [leaderbox ].hh.b0 == 1 ) 
		vlistout () ;
		else hlistout () ;
		doingleaders = outerdoingleaders ;
		dviv = savev ;
		dvih = saveh ;
		curh = leftedge ;
		curv = savev - mem [leaderbox + 3 ].cint + leaderht + lx ;
	      } 
	      curv = edge - 10 ;
	      goto lab15 ;
	    } 
	  } 
	  goto lab13 ;
	} 
	break ;
      case 11 : 
	curv = curv + mem [p + 1 ].cint ;
	break ;
	default: 
	;
	break ;
      } 
      goto lab15 ;
      lab14: if ( ( rulewd == -1073741824L ) ) 
      rulewd = mem [thisbox + 1 ].cint ;
      ruleht = ruleht + ruledp ;
      curv = curv + ruleht ;
      if ( ( ruleht > 0 ) && ( rulewd > 0 ) ) 
      {
	if ( curdir == 1 ) 
	curh = curh - rulewd ;
	if ( curh != dvih ) 
	{
	  movement ( curh - dvih , 143 ) ;
	  dvih = curh ;
	} 
	if ( curv != dviv ) 
	{
	  movement ( curv - dviv , 157 ) ;
	  dviv = curv ;
	} 
	{
	  dvibuf [dviptr ]= 137 ;
	  incr ( dviptr ) ;
	  if ( dviptr == dvilimit ) 
	  dviswap () ;
	} 
	dvifour ( ruleht ) ;
	dvifour ( rulewd ) ;
	curh = leftedge ;
      } 
      goto lab15 ;
      lab13: curv = curv + ruleht ;
    } 
    lab15: p = mem [p ].hh .v.RH ;
  } 
  prunemovements ( saveloc ) ;
  if ( curs > 0 ) 
  dvipop ( saveloc ) ;
  decr ( curs ) ;
} 
void 
zdvishipout ( halfword p ) 
{
  /* 30 */ dvishipout_regmem 
  integer pageloc  ;
  unsigned char j, k  ;
  poolpointer s  ;
  unsigned char oldsetting  ;
  if ( eqtb [29308 ].cint > 0 ) 
  {
    printnl ( 345 ) ;
    println () ;
    print ( 983 ) ;
  } 
  if ( termoffset > maxprintline - 9 ) 
  println () ;
  else if ( ( termoffset > 0 ) || ( fileoffset > 0 ) ) 
  printchar ( 32 ) ;
  printchar ( 91 ) ;
  j = 9 ;
  while ( ( eqtb [29375 + j ].cint == 0 ) && ( j > 0 ) ) decr ( j ) ;
  {register integer for_end; k = 0 ;for_end = j ; if ( k <= for_end) do 
    {
      printint ( eqtb [29375 + k ].cint ) ;
      if ( k < j ) 
      printchar ( 46 ) ;
    } 
  while ( k++ < for_end ) ;} 
  fflush ( stdout ) ;
  if ( eqtb [29308 ].cint > 0 ) 
  {
    printchar ( 93 ) ;
    begindiagnostic () ;
    showbox ( p ) ;
    enddiagnostic ( true ) ;
  } 
  if ( ( mem [p + 3 ].cint > 1073741823L ) || ( mem [p + 2 ].cint > 
  1073741823L ) || ( mem [p + 3 ].cint + mem [p + 2 ].cint + eqtb [29906 
  ].cint > 1073741823L ) || ( mem [p + 1 ].cint + eqtb [29905 ].cint > 
  1073741823L ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 987 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 988 ;
      helpline [0 ]= 989 ;
    } 
    error () ;
    if ( eqtb [29308 ].cint <= 0 ) 
    {
      begindiagnostic () ;
      printnl ( 990 ) ;
      showbox ( p ) ;
      enddiagnostic ( true ) ;
    } 
    goto lab30 ;
  } 
  if ( mem [p + 3 ].cint + mem [p + 2 ].cint + eqtb [29906 ].cint > maxv 
  ) 
  maxv = mem [p + 3 ].cint + mem [p + 2 ].cint + eqtb [29906 ].cint ;
  if ( mem [p + 1 ].cint + eqtb [29905 ].cint > maxh ) 
  maxh = mem [p + 1 ].cint + eqtb [29905 ].cint ;
  dvih = 0 ;
  dviv = 0 ;
  curh = eqtb [29905 ].cint ;
  dvif = 0 ;
  curhoffset = eqtb [29905 ].cint ;
  curvoffset = eqtb [29906 ].cint ;
  if ( eqtb [29910 ].cint != 0 ) 
  curpagewidth = eqtb [29910 ].cint ;
  else curpagewidth = mem [p + 1 ].cint + 2 * curhoffset + 2 * 4736286L ;
  if ( eqtb [29911 ].cint != 0 ) 
  curpageheight = eqtb [29911 ].cint ;
  else curpageheight = mem [p + 3 ].cint + mem [p + 2 ].cint + 2 * 
  curvoffset + 2 * 4736286L ;
  if ( outputfilename == 0 ) 
  {
    if ( jobname == 0 ) 
    openlogfile () ;
    packjobname ( 943 ) ;
    while ( ! bopenout ( dvifile ) ) promptfilename ( 944 , 943 ) ;
    outputfilename = bmakenamestring ( dvifile ) ;
  } 
  if ( totalpages == 0 ) 
  {
    {
      dvibuf [dviptr ]= 247 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {
      dvibuf [dviptr ]= 2 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    dvifour ( 25400000L ) ;
    dvifour ( 473628672L ) ;
    preparemag () ;
    dvifour ( eqtb [29291 ].cint ) ;
    if ( outputcomment ) 
    {
      l = strlen ( outputcomment ) ;
      {
	dvibuf [dviptr ]= l ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      {register integer for_end; s = 0 ;for_end = l - 1 ; if ( s <= for_end) 
      do 
	{
	  dvibuf [dviptr ]= outputcomment [s ];
	  incr ( dviptr ) ;
	  if ( dviptr == dvilimit ) 
	  dviswap () ;
	} 
      while ( s++ < for_end ) ;} 
    } 
    else {
	
      oldsetting = selector ;
      selector = 21 ;
      print ( 981 ) ;
      printint ( eqtb [29297 ].cint ) ;
      printchar ( 46 ) ;
      printtwo ( eqtb [29296 ].cint ) ;
      printchar ( 46 ) ;
      printtwo ( eqtb [29295 ].cint ) ;
      printchar ( 58 ) ;
      printtwo ( eqtb [29294 ].cint / 60 ) ;
      printtwo ( eqtb [29294 ].cint % 60 ) ;
      selector = oldsetting ;
      {
	dvibuf [dviptr ]= ( poolptr - strstart [strptr ]) ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      {register integer for_end; s = strstart [strptr ];for_end = poolptr 
      - 1 ; if ( s <= for_end) do 
	{
	  dvibuf [dviptr ]= strpool [s ];
	  incr ( dviptr ) ;
	  if ( dviptr == dvilimit ) 
	  dviswap () ;
	} 
      while ( s++ < for_end ) ;} 
      poolptr = strstart [strptr ];
    } 
  } 
  pageloc = dvioffset + dviptr ;
  {
    dvibuf [dviptr ]= 139 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  {register integer for_end; k = 0 ;for_end = 9 ; if ( k <= for_end) do 
    dvifour ( eqtb [29375 + k ].cint ) ;
  while ( k++ < for_end ) ;} 
  dvifour ( lastbop ) ;
  lastbop = pageloc ;
  curv = mem [p + 3 ].cint + eqtb [29906 ].cint ;
  tempptr = p ;
  if ( mem [p ].hh.b0 == 1 ) 
  vlistout () ;
  else hlistout () ;
  {
    dvibuf [dviptr ]= 140 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  incr ( totalpages ) ;
  curs = -1 ;
	;
#ifdef IPC
  if ( ipcon > 0 ) 
  {
    if ( dvilimit == halfbuf ) 
    {
      writedvi ( halfbuf , dvibufsize - 1 ) ;
      flushdvi () ;
      dvigone = dvigone + halfbuf ;
    } 
    if ( dviptr > ( 2147483647L - dvioffset ) ) 
    {
      curs = -2 ;
      fatalerror ( 980 ) ;
    } 
    if ( dviptr > 0 ) 
    {
      writedvi ( 0 , dviptr - 1 ) ;
      flushdvi () ;
      dvioffset = dvioffset + dviptr ;
      dvigone = dvigone + dviptr ;
    } 
    dviptr = 0 ;
    dvilimit = dvibufsize ;
    ipcpage ( dvigone ) ;
  } 
#endif /* IPC */
  lab30: ;
  if ( ( eTeXmode == 1 ) ) 
  {
    if ( LRproblems > 0 ) 
    {
      {
	println () ;
	printnl ( 2008 ) ;
	printint ( LRproblems / 10000 ) ;
	print ( 2009 ) ;
	printint ( LRproblems % 10000 ) ;
	print ( 2010 ) ;
	LRproblems = 0 ;
      } 
      printchar ( 41 ) ;
      println () ;
    } 
    if ( ( LRptr != -268435455L ) || ( curdir != 0 ) ) 
    confusion ( 2012 ) ;
  } 
  if ( eqtb [29308 ].cint <= 0 ) 
  printchar ( 93 ) ;
  deadcycles = 0 ;
  fflush ( stdout ) ;
	;
#ifdef STAT
  if ( eqtb [29305 ].cint > 1 ) 
  {
    printnl ( 984 ) ;
    printint ( varused ) ;
    printchar ( 38 ) ;
    printint ( dynused ) ;
    printchar ( 59 ) ;
  } 
#endif /* STAT */
  flushnodelist ( p ) ;
	;
#ifdef STAT
  if ( eqtb [29305 ].cint > 1 ) 
  {
    print ( 985 ) ;
    printint ( varused ) ;
    printchar ( 38 ) ;
    printint ( dynused ) ;
    print ( 986 ) ;
    printint ( himemmin - lomemmax - 1 ) ;
    println () ;
  } 
#endif /* STAT */
} 
integer 
getpdfcompresslevel ( void ) 
{
  register integer Result; getpdfcompresslevel_regmem 
  Result = eqtb [29333 ].cint ;
  return Result ;
} 
integer 
getpdfsuppresswarningdupmap ( void ) 
{
  register integer Result; getpdfsuppresswarningdupmap_regmem 
  Result = eqtb [29360 ].cint ;
  return Result ;
} 
integer 
getpdfsuppresswarningpagegroup ( void ) 
{
  register integer Result; getpdfsuppresswarningpagegroup_regmem 
  Result = eqtb [29361 ].cint ;
  return Result ;
} 
integer 
getpdfsuppressptexinfo ( void ) 
{
  register integer Result; getpdfsuppressptexinfo_regmem 
  Result = eqtb [29363 ].cint ;
  return Result ;
} 
integer 
getpdfomitcharset ( void ) 
{
  register integer Result; getpdfomitcharset_regmem 
  Result = eqtb [29364 ].cint ;
  return Result ;
} 
internalfontnumber 
getnullfont ( void ) 
{
  register internalfontnumber Result; getnullfont_regmem 
  Result = 0 ;
  return Result ;
} 
internalfontnumber 
getfontbase ( void ) 
{
  register internalfontnumber Result; getfontbase_regmem 
  Result = 0 ;
  return Result ;
} 
halfword 
getnullcs ( void ) 
{
  register halfword Result; getnullcs_regmem 
  Result = 513 ;
  return Result ;
} 
halfword 
getnullptr ( void ) 
{
  register halfword Result; getnullptr_regmem 
  Result = -268435455L ;
  return Result ;
} 
integer 
zgettexint ( integer code ) 
{
  register integer Result; gettexint_regmem 
  Result = eqtb [29274 + code ].cint ;
  return Result ;
} 
scaled 
zgettexdimen ( integer code ) 
{
  register scaled Result; gettexdimen_regmem 
  Result = eqtb [29887 + code ].cint ;
  return Result ;
} 
scaled 
zgetxheight ( internalfontnumber f ) 
{
  register scaled Result; getxheight_regmem 
  Result = fontinfo [5 + parambase [f ]].cint ;
  return Result ;
} 
scaled 
zgetcharwidth ( internalfontnumber f , eightbits c ) 
{
  register scaled Result; getcharwidth_regmem 
  if ( ( ( fontbc [f ]<= c ) && ( c <= fontec [f ]) && ( fontinfo [
  charbase [f ]+ c ].qqqq .b0 > 0 ) ) ) 
  Result = fontinfo [widthbase [f ]+ fontinfo [charbase [f ]+ c ].qqqq 
  .b0 ].cint ;
  else Result = 0 ;
  return Result ;
} 
scaled 
zgetcharheight ( internalfontnumber f , eightbits c ) 
{
  register scaled Result; getcharheight_regmem 
  if ( ( ( fontbc [f ]<= c ) && ( c <= fontec [f ]) && ( fontinfo [
  charbase [f ]+ c ].qqqq .b0 > 0 ) ) ) 
  Result = fontinfo [heightbase [f ]+ ( fontinfo [charbase [f ]+ c ]
  .qqqq .b1 ) / 16 ].cint ;
  else Result = 0 ;
  return Result ;
} 
scaled 
zgetchardepth ( internalfontnumber f , eightbits c ) 
{
  register scaled Result; getchardepth_regmem 
  if ( ( ( fontbc [f ]<= c ) && ( c <= fontec [f ]) && ( fontinfo [
  charbase [f ]+ c ].qqqq .b0 > 0 ) ) ) 
  Result = fontinfo [depthbase [f ]+ ( fontinfo [charbase [f ]+ c ]
  .qqqq .b1 ) % 16 ].cint ;
  else Result = 0 ;
  return Result ;
} 
scaled 
zgetquad ( internalfontnumber f ) 
{
  register scaled Result; getquad_regmem 
  Result = fontinfo [6 + parambase [f ]].cint ;
  return Result ;
} 
scaled 
zgetslant ( internalfontnumber f ) 
{
  register scaled Result; getslant_regmem 
  Result = fontinfo [1 + parambase [f ]].cint ;
  return Result ;
} 
internalfontnumber 
newdummyfont ( void ) 
{
  register internalfontnumber Result; newdummyfont_regmem 
  Result = readfontinfo ( 513 , 997 , 345 , -1000 ) ;
  return Result ;
} 
void 
zshortdisplayn ( integer p , integer m ) 
{
  shortdisplayn_regmem 
  integer n  ;
  integer i  ;
  i = 0 ;
  fontinshortdisplay = 0 ;
  if ( p == -268435455L ) 
  return ;
  while ( p > memmin ) {
      
    if ( ( p >= himemmin ) ) 
    {
      if ( p <= memend ) 
      {
	if ( mem [p ].hh.b0 != fontinshortdisplay ) 
	{
	  if ( ( mem [p ].hh.b0 < 0 ) || ( mem [p ].hh.b0 > fontmax ) ) 
	  printchar ( 42 ) ;
	  else printfontidentifier ( mem [p ].hh.b0 ) ;
	  printchar ( 32 ) ;
	  fontinshortdisplay = mem [p ].hh.b0 ;
	} 
	print ( mem [p ].hh.b1 ) ;
      } 
    } 
    else {
	
      if ( ( mem [p ].hh.b0 == 10 ) || ( mem [p ].hh.b0 == 7 ) || ( mem [
      p ].hh.b0 == 12 ) || ( ( mem [p ].hh.b0 == 11 ) && ( mem [p ].hh.b1 
      == 1 ) ) ) 
      incr ( i ) ;
      if ( i >= m ) 
      return ;
      if ( ( mem [p ].hh.b0 == 7 ) ) 
      {
	print ( 124 ) ;
	shortdisplay ( mem [p + 1 ].hh .v.LH ) ;
	print ( 124 ) ;
	shortdisplay ( mem [p + 1 ].hh .v.RH ) ;
	print ( 124 ) ;
	n = mem [p ].hh.b1 ;
	while ( n > 0 ) {
	    
	  if ( mem [p ].hh .v.RH != -268435455L ) 
	  p = mem [p ].hh .v.RH ;
	  decr ( n ) ;
	} 
      } 
      else switch ( mem [p ].hh.b0 ) 
      {case 0 : 
      case 1 : 
      case 3 : 
      case 8 : 
      case 4 : 
      case 5 : 
      case 13 : 
	print ( 313 ) ;
	break ;
      case 2 : 
	printchar ( 124 ) ;
	break ;
      case 10 : 
	if ( mem [p + 1 ].hh .v.LH != membot ) 
	printchar ( 32 ) ;
	break ;
      case 9 : 
	if ( mem [p ].hh.b1 >= 4 ) 
	print ( 313 ) ;
	else printchar ( 36 ) ;
	break ;
      case 6 : 
	shortdisplay ( mem [p + 1 ].hh .v.RH ) ;
	break ;
      case 7 : 
	{
	  shortdisplay ( mem [p + 1 ].hh .v.LH ) ;
	  shortdisplay ( mem [p + 1 ].hh .v.RH ) ;
	  n = mem [p ].hh.b1 ;
	  while ( n > 0 ) {
	      
	    if ( mem [p ].hh .v.RH != -268435455L ) 
	    p = mem [p ].hh .v.RH ;
	    decr ( n ) ;
	  } 
	} 
	break ;
	default: 
	;
	break ;
      } 
    } 
    p = mem [p ].hh .v.RH ;
    if ( p == -268435455L ) 
    return ;
  } 
  fflush ( stdout ) ;
} 
integer 
zpdfgetmem ( integer s ) 
{
  register integer Result; pdfgetmem_regmem 
  integer a  ;
  if ( s > suppdfmemsize - pdfmemptr ) 
  overflow ( 998 , pdfmemsize ) ;
  if ( pdfmemptr + s > pdfmemsize ) 
  {
    a = 0.2 * pdfmemsize ;
    if ( pdfmemptr + s > pdfmemsize + a ) 
    pdfmemsize = pdfmemptr + s ;
    else if ( pdfmemsize < suppdfmemsize - a ) 
    pdfmemsize = pdfmemsize + a ;
    else pdfmemsize = suppdfmemsize ;
    pdfmem = xreallocarray ( pdfmem , integer , pdfmemsize ) ;
  } 
  Result = pdfmemptr ;
  pdfmemptr = pdfmemptr + s ;
  return Result ;
} 
integer 
zfixint ( integer val , integer min , integer max ) 
{
  register integer Result; fixint_regmem 
  if ( val < min ) 
  Result = min ;
  else if ( val > max ) 
  Result = max ;
  else Result = val ;
  return Result ;
} 
void 
checkpdfminorversion ( void ) 
{
  checkpdfminorversion_regmem 
  if ( ! pdfminorversionwritten ) 
  {
    pdfminorversionwritten = true ;
    if ( ( eqtb [29341 ].cint < 0 ) || ( eqtb [29341 ].cint > 9 ) ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 1000 ) ;
      } 
      println () ;
      {
	helpptr = 2 ;
	helpline [1 ]= 1001 ;
	helpline [0 ]= 1002 ;
      } 
      interror ( eqtb [29341 ].cint ) ;
      eqtb [29341 ].cint = 4 ;
    } 
    fixedpdfminorversion = eqtb [29341 ].cint ;
    fixedgamma = fixint ( eqtb [29345 ].cint , 0 , 1000000L ) ;
    fixedimagegamma = fixint ( eqtb [29346 ].cint , 0 , 1000000L ) ;
    fixedimagehicolor = fixint ( eqtb [29347 ].cint , 0 , 1 ) ;
    fixedimageapplygamma = fixint ( eqtb [29348 ].cint , 0 , 1 ) ;
    fixedpdfobjcompresslevel = fixint ( eqtb [29352 ].cint , 0 , 3 ) ;
    fixedpdfdraftmode = fixint ( eqtb [29357 ].cint , 0 , 1 ) ;
    fixedinclusioncopyfont = fixint ( eqtb [29358 ].cint , 0 , 1 ) ;
    if ( ( fixedpdfminorversion >= 5 ) && ( fixedpdfobjcompresslevel > 0 ) ) 
    pdfosenable = true ;
    else {
	
      if ( fixedpdfobjcompresslevel > 0 ) 
      {
	pdfwarning ( 1003 , 1004 , true , true ) ;
	fixedpdfobjcompresslevel = 0 ;
      } 
      pdfosenable = false ;
    } 
    ensurepdfopen () ;
    fixpdfoutput () ;
    pdfprint ( 1005 ) ;
    {
      pdfprintint ( fixedpdfminorversion ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
    pdfprint ( 37 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 208 ;
	incr ( pdfptr ) ;
      } 
    } 
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 212 ;
	incr ( pdfptr ) ;
      } 
    } 
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 197 ;
	incr ( pdfptr ) ;
      } 
    } 
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 216 ;
	incr ( pdfptr ) ;
      } 
    } 
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
  else {
      
    if ( fixedpdfminorversion != eqtb [29341 ].cint ) 
    pdferror ( 1006 , 1007 ) ;
  } 
} 
void 
ensurepdfopen ( void ) 
{
  ensurepdfopen_regmem 
  if ( outputfilename != 0 ) 
  return ;
  if ( jobname == 0 ) 
  openlogfile () ;
  packjobname ( 1008 ) ;
  if ( fixedpdfdraftmode == 0 ) 
  while ( ! bopenout ( pdffile ) ) promptfilename ( 944 , 1008 ) ;
  outputfilename = bmakenamestring ( pdffile ) ;
} 
void 
pdfflush ( void ) 
{
  pdfflush_regmem 
  longinteger savedpdfgone  ;
  if ( ! pdfosmode ) 
  {
    savedpdfgone = pdfgone ;
    switch ( zipwritestate ) 
    {case 0 : 
      if ( pdfptr > 0 ) 
      {
	if ( fixedpdfdraftmode == 0 ) 
	writepdf ( 0 , pdfptr - 1 ) ;
	pdfgone = pdfgone + pdfptr ;
	pdflastbyte = pdfbuf [pdfptr - 1 ];
      } 
      break ;
    case 1 : 
      if ( fixedpdfdraftmode == 0 ) 
      writezip ( false ) ;
      break ;
    case 2 : 
      {
	if ( fixedpdfdraftmode == 0 ) 
	writezip ( true ) ;
	zipwritestate = 0 ;
      } 
      break ;
    } 
    pdfptr = 0 ;
    if ( savedpdfgone > pdfgone ) 
    pdferror ( 1009 , 1010 ) ;
  } 
} 
void 
pdfbeginstream ( void ) 
{
  pdfbeginstream_regmem 
  {
    pdfprint ( 1011 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
  pdfseekwritelength = true ;
  pdfstreamlengthoffset = ( pdfgone + pdfptr ) - 11 ;
  pdfstreamlength = 0 ;
  pdflastbyte = 0 ;
  if ( eqtb [29333 ].cint > 0 ) 
  {
    {
      pdfprint ( 1012 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
    {
      pdfprint ( 1013 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
    {
      pdfprint ( 1014 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
    pdfflush () ;
    zipwritestate = 1 ;
  } 
  else {
      
    {
      pdfprint ( 1013 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
    {
      pdfprint ( 1014 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
    pdfsaveoffset = ( pdfgone + pdfptr ) ;
  } 
} 
void 
pdfendstream ( void ) 
{
  pdfendstream_regmem 
  if ( zipwritestate == 1 ) 
  zipwritestate = 2 ;
  else pdfstreamlength = ( pdfgone + pdfptr ) - pdfsaveoffset ;
  pdfflush () ;
  if ( pdfseekwritelength ) 
  writestreamlength ( pdfstreamlength , pdfstreamlengthoffset ) ;
  pdfseekwritelength = false ;
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 10 ;
      incr ( pdfptr ) ;
    } 
  } 
  {
    pdfprint ( 1015 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
  pdfendobj () ;
} 
void 
zadvcharwidth ( internalfontnumber f , eightbits c ) 
{
  advcharwidth_regmem 
  scaled w, sout  ;
  integer s  ;
  w = fontinfo [widthbase [f ]+ fontinfo [charbase [f ]+ effectivechar ( 
  true , f , c ) ].qqqq .b0 ].cint ;
  if ( isscalable ( f ) ) 
  {
    if ( pdfcurTma == 0 ) 
    {
      {
	if ( dividescaled ( w , pdffontsize [f ], 4 ) != 0 ) 
	;
      } 
      pdfdeltah = pdfdeltah + scaledout ;
    } 
    else {
	
      s = dividescaled ( roundxnoverd ( w , 1000 , 1000 + pdfcurTma ) , 
      pdffontsize [f ], 4 ) ;
      sout = roundxnoverd ( roundxnoverd ( pdffontsize [f ], abs ( s ) , 
      10000 ) , 1000 + pdfcurTma , 1000 ) ;
      if ( s < 0 ) 
      sout = - (integer) sout ;
      pdfdeltah = pdfdeltah + sout ;
    } 
  } 
  else pdfdeltah = pdfdeltah + getpkcharwidth ( f , w ) ;
} 
void 
zpdfprintreal ( integer m , integer d ) 
{
  pdfprintreal_regmem 
  if ( m < 0 ) 
  {
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 45 ;
	incr ( pdfptr ) ;
      } 
    } 
    m = - (integer) m ;
  } 
  pdfprintint ( m / tenpow [d ]) ;
  m = m % tenpow [d ];
  if ( m > 0 ) 
  {
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 46 ;
	incr ( pdfptr ) ;
      } 
    } 
    decr ( d ) ;
    while ( m < tenpow [d ]) {
	
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 48 ;
	  incr ( pdfptr ) ;
	} 
      } 
      decr ( d ) ;
    } 
    while ( m % 10 == 0 ) m = m / 10 ;
    pdfprintint ( m ) ;
  } 
} 
void 
zpdfprintbp ( scaled s ) 
{
  pdfprintbp_regmem 
  pdfprintreal ( dividescaled ( s , onehundredbp , fixeddecimaldigits + 2 ) , 
  fixeddecimaldigits ) ;
} 
void 
zpdfprintmagbp ( scaled s ) 
{
  pdfprintmagbp_regmem 
  preparemag () ;
  if ( eqtb [29291 ].cint != 1000 ) 
  s = roundxnoverd ( s , eqtb [29291 ].cint , 1000 ) ;
  pdfprintbp ( s ) ;
} 
void 
zpdfsetorigin ( scaled h , scaled v ) 
{
  pdfsetorigin_regmem 
  if ( ( abs ( h - pdforiginh ) >= minbpval ) || ( abs ( v - pdforiginv ) >= 
  minbpval ) ) 
  {
    pdfprint ( 1024 ) ;
    pdfprintbp ( h - pdforiginh ) ;
    pdforiginh = pdforiginh + scaledout ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 32 ;
	incr ( pdfptr ) ;
      } 
    } 
    pdfprintbp ( pdforiginv - v ) ;
    pdforiginv = pdforiginv - scaledout ;
    {
      pdfprint ( 1025 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
  } 
  pdfh = pdforiginh ;
  pdftjstarth = pdfh ;
  pdfv = pdforiginv ;
} 
void 
zpdfsetorigintemp ( scaled h , scaled v ) 
{
  pdfsetorigintemp_regmem 
  if ( ( abs ( h - pdforiginh ) >= minbpval ) || ( abs ( v - pdforiginv ) >= 
  minbpval ) ) 
  {
    pdfprint ( 1024 ) ;
    pdfprintbp ( h - pdforiginh ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 32 ;
	incr ( pdfptr ) ;
      } 
    } 
    pdfprintbp ( pdforiginv - v ) ;
    {
      pdfprint ( 1025 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
  } 
} 
void 
pdfendstring ( void ) 
{
  pdfendstring_regmem 
  if ( pdfdoingstring ) 
  {
    pdfprint ( 1026 ) ;
    pdfdoingstring = false ;
  } 
} 
void 
pdfendstringnl ( void ) 
{
  pdfendstringnl_regmem 
  if ( pdfdoingstring ) 
  {
    {
      pdfprint ( 1026 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
    pdfdoingstring = false ;
  } 
} 
void 
zpdfsettextmatrix ( scaled v , scaled vout , internalfontnumber f ) 
{
  pdfsettextmatrix_regmem 
  integer pdfnewTma  ;
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 32 ;
      incr ( pdfptr ) ;
    } 
  } 
  if ( f == pdff ) 
  pdfnewTma = pdfcurTma ;
  else if ( ! pdffontautoexpand [f ]) 
  pdfnewTma = 0 ;
  else pdfnewTma = pdffontexpandratio [f ];
  if ( ( pdfnewTma != 0 ) || ( ( pdfnewTma == 0 ) && ( pdfcurTma != 0 ) ) ) 
  {
    pdfprintreal ( 1000 + pdfnewTma , 3 ) ;
    pdfprint ( 1027 ) ;
    pdfprintbp ( curh - pdforiginh ) ;
    pdfh = pdforiginh + scaledout ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 32 ;
	incr ( pdfptr ) ;
      } 
    } 
    pdfprintbp ( pdforiginv - curv ) ;
    pdfv = pdforiginv - scaledout ;
    pdfprint ( 1028 ) ;
    pdfcurTma = pdfnewTma ;
    pdfassert ( pdfcurTma > -1000 ) ;
  } 
  else {
      
    pdfprintbp ( curh - pdftjstarth ) ;
    pdfh = pdftjstarth + scaledout ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 32 ;
	incr ( pdfptr ) ;
      } 
    } 
    pdfprintreal ( v , fixeddecimaldigits ) ;
    pdfv = pdfv - vout ;
    pdfprint ( 1029 ) ;
  } 
  pdftjstarth = pdfh ;
  pdfdeltah = 0 ;
} 
void 
zpdfusefont ( internalfontnumber f , integer fontnum ) 
{
  pdfusefont_regmem 
  {
    if ( dividescaled ( fontsize [f ], onehundredbp , 6 ) != 0 ) 
    ;
  } 
  pdffontsize [f ]= scaledout ;
  fontused [f ]= true ;
  pdfassert ( ( fontnum > 0 ) || ( ( fontnum < 0 ) && ( pdffontnum [
  - (integer) fontnum ]> 0 ) ) ) ;
  pdffontnum [f ]= fontnum ;
  if ( eqtb [29335 ].cint > 0 ) 
  {
    pdfwarning ( 0 , 1030 , true , true ) ;
    eqtb [29335 ].cint = 0 ;
  } 
} 
void 
zpdfinitfont ( internalfontnumber f ) 
{
  pdfinitfont_regmem 
  internalfontnumber k, b  ;
  integer i  ;
  pdfassert ( ! fontused [f ]) ;
  if ( pdffontautoexpand [f ]&& ( pdffontblink [f ]!= 0 ) ) 
  {
    b = pdffontblink [f ];
    if ( ! isscalable ( b ) ) 
    pdferror ( 1031 , 1032 ) ;
    if ( ! fontused [b ]) 
    pdfinitfont ( b ) ;
    pdffontmap [f ]= pdffontmap [b ];
  } 
  if ( isscalable ( f ) ) 
  {
    i = headtab [3 ];
    while ( i != 0 ) {
	
      k = objtab [i ].int0 ;
      if ( isscalable ( k ) && ( pdffontmap [k ]== pdffontmap [f ]) && ( 
      streqstr ( fontname [k ], fontname [f ]) || ( pdffontautoexpand [f 
      ]&& ( pdffontblink [f ]!= 0 ) && streqstr ( fontname [k ], fontname 
      [pdffontblink [f ]]) ) ) ) 
      {
	pdfassert ( pdffontnum [k ]!= 0 ) ;
	if ( pdffontnum [k ]< 0 ) 
	pdfusefont ( f , pdffontnum [k ]) ;
	else pdfusefont ( f , - (integer) k ) ;
	return ;
      } 
      i = objtab [i ].int1 ;
    } 
  } 
  pdfcreateobj ( 3 , f ) ;
  pdfusefont ( f , objptr ) ;
} 
void 
pdfinitfontcurval ( void ) 
{
  pdfinitfontcurval_regmem 
  pdfinitfont ( curval ) ;
} 
void 
zpdfsetfont ( internalfontnumber f ) 
{
  /* 40 41 */ pdfsetfont_regmem 
  halfword p  ;
  internalfontnumber k  ;
  if ( ! fontused [f ]) 
  pdfinitfont ( f ) ;
  {
    if ( pdffontnum [f ]< 0 ) 
    ff = - (integer) pdffontnum [f ];
    else ff = f ;
  } 
  k = ff ;
  p = pdffontlist ;
  while ( p != -268435455L ) {
      
    {
      if ( pdffontnum [mem [p ].hh .v.LH ]< 0 ) 
      ff = - (integer) pdffontnum [mem [p ].hh .v.LH ];
      else ff = mem [p ].hh .v.LH ;
    } 
    if ( ff == k ) 
    goto lab40 ;
    p = mem [p ].hh .v.RH ;
  } 
  {
    pdfappendlistarg = f ;
    pdffontlist = appendptr ( pdffontlist , pdfappendlistarg ) ;
  } 
  lab40: if ( ( k == pdflastf ) && ( fontsize [f ]== pdflastfs ) ) 
  return ;
  pdfprint ( 1033 ) ;
  pdfprintint ( k ) ;
  if ( pdfresnameprefix != 0 ) 
  pdfprint ( pdfresnameprefix ) ;
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 32 ;
      incr ( pdfptr ) ;
    } 
  } 
  pdfprintreal ( dividescaled ( fontsize [f ], onehundredbp , 6 ) , 4 ) ;
  pdfprint ( 1034 ) ;
  pdflastf = k ;
  pdflastfs = fontsize [f ];
} 
void 
pdfbegintext ( void ) 
{
  pdfbegintext_regmem 
  pdfsetorigin ( 0 , curpageheight ) ;
  {
    pdfprint ( 1035 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
  pdfdoingtext = true ;
  pdff = 0 ;
  pdflastf = 0 ;
  pdflastfs = 0 ;
  pdfdoingstring = false ;
  pdfcurTma = 0 ;
} 
void 
pdfreaddummyfont ( void ) 
{
  pdfreaddummyfont_regmem 
  if ( pdfdummyfont == 0 ) 
  {
    pdfdummyfont = readfontinfo ( 513 , 1036 , 345 , onebp ) ;
    pdfmarkchar ( pdfdummyfont , 32 ) ;
  } 
} 
void 
pdfinsertinterwordspace ( void ) 
{
  pdfinsertinterwordspace_regmem 
  pdfreaddummyfont () ;
  pdfsetfont ( pdfdummyfont ) ;
  pdfprint ( 1037 ) ;
} 
void 
zpdfbeginstring ( internalfontnumber f ) 
{
  pdfbeginstring_regmem 
  scaled sout, v, vout  ;
  integer s  ;
  boolean mustendstring  ;
  boolean mustinsertspace  ;
  if ( ! pdfdoingtext ) 
  pdfbegintext () ;
  if ( f != pdff ) 
  {
    pdfendstring () ;
    pdfsetfont ( f ) ;
  } 
  if ( pdfcurTma == 0 ) 
  {
    s = dividescaled ( curh - ( pdftjstarth + pdfdeltah ) , pdffontsize [f ]
    , 3 ) ;
    sout = scaledout ;
  } 
  else {
      
    s = dividescaled ( roundxnoverd ( curh - ( pdftjstarth + pdfdeltah ) , 
    1000 , 1000 + pdfcurTma ) , pdffontsize [f ], 3 ) ;
    if ( abs ( s ) < 32768L ) 
    {
      sout = roundxnoverd ( roundxnoverd ( pdffontsize [f ], abs ( s ) , 
      1000 ) , 1000 + pdfcurTma , 1000 ) ;
      if ( s < 0 ) 
      sout = - (integer) sout ;
    } 
  } 
  if ( abs ( curv - pdfv ) >= minbpval ) 
  {
    v = dividescaled ( pdfv - curv , onehundredbp , fixeddecimaldigits + 2 ) ;
    vout = scaledout ;
  } 
  else {
      
    v = 0 ;
    vout = 0 ;
  } 
  mustinsertspace = false ;
  mustendstring = false ;
  if ( genfakedinterwordspace && ( ( abs ( vout ) > 2 * fontinfo [5 + 
  parambase [f ]].cint ) || ( sout > fontinfo [2 + parambase [f ]].cint 
  - fontinfo [4 + parambase [f ]].cint ) || ( ( f != pdff ) && ( v == 0 ) 
  ) ) ) 
  {
    mustinsertspace = true ;
  } 
  if ( ( f != pdff ) || ( v != 0 ) || ( abs ( s ) >= 32768L ) || 
  mustinsertspace ) 
  {
    mustendstring = true ;
  } 
  if ( mustendstring ) 
  {
    pdfendstring () ;
    if ( mustinsertspace ) 
    {
      pdfinsertinterwordspace () ;
      pdfsetfont ( f ) ;
    } 
    pdfsettextmatrix ( v , vout , f ) ;
    pdff = f ;
    s = 0 ;
  } 
  if ( ! pdfdoingstring ) 
  {
    pdfprint ( 1044 ) ;
    if ( s == 0 ) 
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 40 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
  if ( s != 0 ) 
  {
    if ( pdfdoingstring ) 
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 41 ;
	incr ( pdfptr ) ;
      } 
    } 
    pdfprintint ( - (integer) s ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 40 ;
	incr ( pdfptr ) ;
      } 
    } 
    pdfdeltah = pdfdeltah + sout ;
  } 
  pdfdoingstring = true ;
} 
void 
pdfinsertfakespace ( void ) 
{
  pdfinsertfakespace_regmem 
  integer s  ;
  s = genfakedinterwordspace ;
  genfakedinterwordspace = 0 ;
  pdfreaddummyfont () ;
  pdfbeginstring ( pdfdummyfont ) ;
  pdfprint ( 32 ) ;
  pdfendstringnl () ;
  genfakedinterwordspace = s ;
} 
void 
pdfendtext ( void ) 
{
  pdfendtext_regmem 
  if ( pdfdoingtext ) 
  {
    pdfendstringnl () ;
    {
      pdfprint ( 1045 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
    pdfdoingtext = false ;
  } 
} 
void 
zpdfsetrule ( scaled x , scaled y , scaled w , scaled h ) 
{
  pdfsetrule_regmem 
  pdfendtext () ;
  {
    pdfprint ( 113 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
  if ( h <= onebp ) 
  {
    pdfsetorigintemp ( x , y - ( h + 1 ) / ((double) 2 ) ) ;
    pdfprint ( 1046 ) ;
    pdfprintbp ( h ) ;
    pdfprint ( 1047 ) ;
    pdfprintbp ( w ) ;
    {
      pdfprint ( 1048 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
  } 
  else if ( w <= onebp ) 
  {
    pdfsetorigintemp ( x + ( w + 1 ) / ((double) 2 ) , y ) ;
    pdfprint ( 1046 ) ;
    pdfprintbp ( w ) ;
    pdfprint ( 1049 ) ;
    pdfprintbp ( h ) ;
    {
      pdfprint ( 1050 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
  } 
  else {
      
    pdfsetorigintemp ( x , y ) ;
    pdfprint ( 1051 ) ;
    pdfprintbp ( w ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 32 ;
	incr ( pdfptr ) ;
      } 
    } 
    pdfprintbp ( h ) ;
    {
      pdfprint ( 1052 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
  } 
  {
    pdfprint ( 81 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
} 
void 
zpdfrectangle ( scaled left , scaled top , scaled right , scaled bottom ) 
{
  pdfrectangle_regmem 
  preparemag () ;
  pdfprint ( 1053 ) ;
  pdfprintmagbp ( ( ( left ) - pdforiginh ) ) ;
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 32 ;
      incr ( pdfptr ) ;
    } 
  } 
  pdfprintmagbp ( ( pdforiginv - ( bottom ) ) ) ;
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 32 ;
      incr ( pdfptr ) ;
    } 
  } 
  pdfprintmagbp ( ( ( right ) - pdforiginh ) ) ;
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 32 ;
      incr ( pdfptr ) ;
    } 
  } 
  pdfprintmagbp ( ( pdforiginv - ( top ) ) ) ;
  {
    pdfprint ( 93 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
} 
void 
zslowprintsubstr ( integer s , integer maxlen ) 
{
  slowprintsubstr_regmem 
  poolpointer j  ;
  if ( ( s >= strptr ) || ( s < 256 ) ) 
  print ( s ) ;
  else {
      
    j = strstart [s ];
    while ( ( j < strstart [s + 1 ]) && ( j <= strstart [s ]+ maxlen ) ) {
	
      print ( strpool [j ]) ;
      incr ( j ) ;
    } 
  } 
  if ( j < strstart [s + 1 ]) 
  print ( 277 ) ;
} 
void 
zliteral ( strnumber s , integer literalmode , boolean warn ) 
{
  literal_regmem 
  poolpointer j  ;
  j = strstart [s ];
  if ( literalmode == 3 ) 
  {
    if ( ! ( strinstr ( s , 1054 , 0 ) || strinstr ( s , 1055 , 0 ) ) ) 
    {
      if ( warn && ! ( strinstr ( s , 1056 , 0 ) || strinstr ( s , 1057 , 0 ) 
      || ( ( strstart [s + 1 ]- strstart [s ]) == 0 ) ) ) 
      {
	printnl ( 1058 ) ;
	printnl ( 1059 ) ;
	slowprintsubstr ( s , 64 ) ;
	println () ;
      } 
      return ;
    } 
    j = j + ( strstart [1055 ]- strstart [1054 ]) ;
    if ( strinstr ( s , 1060 , ( strstart [1055 ]- strstart [1054 ]) ) ) 
    {
      j = j + ( strstart [1061 ]- strstart [1060 ]) ;
      literalmode = 2 ;
    } 
    else if ( strinstr ( s , 1061 , ( strstart [1055 ]- strstart [1054 ]) 
    ) ) 
    {
      j = j + ( strstart [1062 ]- strstart [1061 ]) ;
      literalmode = 1 ;
    } 
    else literalmode = 0 ;
  } 
  switch ( literalmode ) 
  {case 0 : 
    {
      pdfendtext () ;
      pdfsetorigin ( curh , curv ) ;
    } 
    break ;
  case 1 : 
    pdfendtext () ;
    break ;
  case 2 : 
    pdfendstringnl () ;
    break ;
    default: 
    confusion ( 1062 ) ;
    break ;
  } 
  while ( j < strstart [s + 1 ]) {
      
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= strpool [j ];
	incr ( pdfptr ) ;
      } 
    } 
    incr ( j ) ;
  } 
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 10 ;
      incr ( pdfptr ) ;
    } 
  } 
} 
void 
zpdfprintfwint ( longinteger n , integer w ) 
{
  pdfprintfwint_regmem 
  integer k  ;
  k = 0 ;
  do {
      dig [k ]= n % 10 ;
    n = n / 10 ;
    incr ( k ) ;
  } while ( ! ( k == w ) ) ;
  {
    if ( pdfosmode && ( k + pdfptr > pdfbufsize ) ) 
    pdfosgetosbuf ( k ) ;
    else if ( ! pdfosmode && ( k > pdfbufsize ) ) 
    overflow ( 999 , pdfopbufsize ) ;
    else if ( ! pdfosmode && ( k + pdfptr > pdfbufsize ) ) 
    pdfflush () ;
  } 
  while ( k > 0 ) {
      
    decr ( k ) ;
    {
      pdfbuf [pdfptr ]= 48 + dig [k ];
      incr ( pdfptr ) ;
    } 
  } 
} 
void 
zpdfoutbytes ( longinteger n , integer w ) 
{
  pdfoutbytes_regmem 
  integer k  ;
  integer byte[8]  ;
  k = 0 ;
  do {
      byte [k ]= n % 256 ;
    n = n / 256 ;
    incr ( k ) ;
  } while ( ! ( k == w ) ) ;
  {
    if ( pdfosmode && ( k + pdfptr > pdfbufsize ) ) 
    pdfosgetosbuf ( k ) ;
    else if ( ! pdfosmode && ( k > pdfbufsize ) ) 
    overflow ( 999 , pdfopbufsize ) ;
    else if ( ! pdfosmode && ( k + pdfptr > pdfbufsize ) ) 
    pdfflush () ;
  } 
  while ( k > 0 ) {
      
    decr ( k ) ;
    {
      pdfbuf [pdfptr ]= byte [k ];
      incr ( pdfptr ) ;
    } 
  } 
} 
void 
zpdfintentry ( strnumber s , integer v ) 
{
  pdfintentry_regmem 
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 47 ;
      incr ( pdfptr ) ;
    } 
  } 
  pdfprint ( s ) ;
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 32 ;
      incr ( pdfptr ) ;
    } 
  } 
  pdfprintint ( v ) ;
} 
void 
zpdfintentryln ( strnumber s , integer v ) 
{
  pdfintentryln_regmem 
  pdfintentry ( s , v ) ;
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 10 ;
      incr ( pdfptr ) ;
    } 
  } 
} 
void 
zpdfindirect ( strnumber s , integer o ) 
{
  pdfindirect_regmem 
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 47 ;
      incr ( pdfptr ) ;
    } 
  } 
  pdfprint ( s ) ;
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 32 ;
      incr ( pdfptr ) ;
    } 
  } 
  pdfprintint ( o ) ;
  pdfprint ( 1072 ) ;
} 
void 
zpdfindirectln ( strnumber s , integer o ) 
{
  pdfindirectln_regmem 
  pdfindirect ( s , o ) ;
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 10 ;
      incr ( pdfptr ) ;
    } 
  } 
} 
void 
zpdfprintstr ( strnumber s ) 
{
  /* 30 */ pdfprintstr_regmem 
  poolpointer i, j  ;
  boolean ishexstring  ;
  i = strstart [s ];
  j = i + ( strstart [s + 1 ]- strstart [s ]) - 1 ;
  if ( i > j ) 
  {
    pdfprint ( 1073 ) ;
    return ;
  } 
  if ( ( strpool [i ]== '(' ) && ( strpool [j ]== ')' ) ) 
  {
    pdfprint ( s ) ;
    return ;
  } 
  ishexstring = false ;
  if ( ( strpool [i ]!= '<' ) || ( strpool [j ]!= '>' ) || odd ( ( 
  strstart [s + 1 ]- strstart [s ]) ) ) 
  goto lab30 ;
  incr ( i ) ;
  decr ( j ) ;
  while ( i < j ) {
      
    if ( ( ( ( strpool [i ]>= '0' ) && ( strpool [i ]<= '9' ) ) || ( ( 
    strpool [i ]>= 'A' ) && ( strpool [i ]<= 'F' ) ) || ( ( strpool [i ]
    >= 'a' ) && ( strpool [i ]<= 'f' ) ) ) && ( ( ( strpool [i + 1 ]>= '0' 
    ) && ( strpool [i + 1 ]<= '9' ) ) || ( ( strpool [i + 1 ]>= 'A' ) && ( 
    strpool [i + 1 ]<= 'F' ) ) || ( ( strpool [i + 1 ]>= 'a' ) && ( 
    strpool [i + 1 ]<= 'f' ) ) ) ) 
    i = i + 2 ;
    else goto lab30 ;
  } 
  ishexstring = true ;
  lab30: if ( ishexstring ) 
  pdfprint ( s ) ;
  else {
      
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 40 ;
	incr ( pdfptr ) ;
      } 
    } 
    pdfprint ( s ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 41 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
} 
void 
zpdfprintstrln ( strnumber s ) 
{
  pdfprintstrln_regmem 
  pdfprintstr ( s ) ;
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 10 ;
      incr ( pdfptr ) ;
    } 
  } 
} 
void 
zpdfstrentry ( strnumber s , strnumber v ) 
{
  pdfstrentry_regmem 
  if ( v == 0 ) 
  return ;
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 47 ;
      incr ( pdfptr ) ;
    } 
  } 
  pdfprint ( s ) ;
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 32 ;
      incr ( pdfptr ) ;
    } 
  } 
  pdfprintstr ( v ) ;
} 
void 
zpdfstrentryln ( strnumber s , strnumber v ) 
{
  pdfstrentryln_regmem 
  if ( v == 0 ) 
  return ;
  pdfstrentry ( s , v ) ;
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 10 ;
      incr ( pdfptr ) ;
    } 
  } 
} 
void 
zsettagcode ( internalfontnumber f , eightbits c , integer i ) 
{
  settagcode_regmem 
  integer fixedi  ;
  if ( ( ( fontbc [f ]<= c ) && ( c <= fontec [f ]) && ( fontinfo [
  charbase [f ]+ c ].qqqq .b0 > 0 ) ) ) 
  {
    fixedi = abs ( fixint ( i , -7 , 0 ) ) ;
    if ( fixedi >= 4 ) 
    {
      if ( ( ( fontinfo [charbase [f ]+ effectivechar ( true , f , c ) ]
      .qqqq .b2 ) % 4 ) == 3 ) 
      fontinfo [charbase [f ]+ effectivechar ( true , f , c ) ].qqqq .b2 = 
      ( fontinfo [charbase [f ]+ effectivechar ( true , f , c ) ].qqqq .b2 
      ) - 3 ;
      fixedi = fixedi - 4 ;
    } 
    if ( fixedi >= 2 ) 
    {
      if ( ( ( fontinfo [charbase [f ]+ effectivechar ( true , f , c ) ]
      .qqqq .b2 ) % 4 ) == 2 ) 
      fontinfo [charbase [f ]+ effectivechar ( true , f , c ) ].qqqq .b2 = 
      ( fontinfo [charbase [f ]+ effectivechar ( true , f , c ) ].qqqq .b2 
      ) - 2 ;
      fixedi = fixedi - 2 ;
    } 
    if ( fixedi >= 1 ) 
    {
      if ( ( ( fontinfo [charbase [f ]+ effectivechar ( true , f , c ) ]
      .qqqq .b2 ) % 4 ) == 1 ) 
      fontinfo [charbase [f ]+ effectivechar ( true , f , c ) ].qqqq .b2 = 
      ( fontinfo [charbase [f ]+ effectivechar ( true , f , c ) ].qqqq .b2 
      ) - 1 ;
    } 
  } 
} 
void 
zsetnoligatures ( internalfontnumber f ) 
{
  setnoligatures_regmem 
  integer c  ;
  {register integer for_end; c = fontbc [f ];for_end = fontec [f ]; if ( 
  c <= for_end) do 
    if ( ( fontinfo [charbase [f ]+ c ].qqqq .b0 > 0 ) ) {
	
      if ( ( ( fontinfo [charbase [f ]+ c ].qqqq .b2 ) % 4 ) == 1 ) 
      fontinfo [charbase [f ]+ c ].qqqq .b2 = ( fontinfo [charbase [f ]
      + c ].qqqq .b2 ) - 1 ;
    } 
  while ( c++ < for_end ) ;} 
} 
integer 
zinitfontbase ( integer v ) 
{
  register integer Result; initfontbase_regmem 
  integer i, j  ;
  i = pdfgetmem ( 256 ) ;
  {register integer for_end; j = 0 ;for_end = 255 ; if ( j <= for_end) do 
    pdfmem [i + j ]= v ;
  while ( j++ < for_end ) ;} 
  Result = i ;
  return Result ;
} 
void 
zsetlpcode ( internalfontnumber f , eightbits c , integer i ) 
{
  setlpcode_regmem 
  if ( pdffontlpbase [f ]== 0 ) 
  pdffontlpbase [f ]= initfontbase ( 0 ) ;
  pdfmem [pdffontlpbase [f ]+ c ]= fixint ( i , -1000 , 1000 ) ;
} 
void 
zsetrpcode ( internalfontnumber f , eightbits c , integer i ) 
{
  setrpcode_regmem 
  if ( pdffontrpbase [f ]== 0 ) 
  pdffontrpbase [f ]= initfontbase ( 0 ) ;
  pdfmem [pdffontrpbase [f ]+ c ]= fixint ( i , -1000 , 1000 ) ;
} 
void 
zsetefcode ( internalfontnumber f , eightbits c , integer i ) 
{
  setefcode_regmem 
  if ( pdffontefbase [f ]== 0 ) 
  pdffontefbase [f ]= initfontbase ( 1000 ) ;
  pdfmem [pdffontefbase [f ]+ c ]= fixint ( i , 0 , 1000 ) ;
} 
void 
zsetknbscode ( internalfontnumber f , eightbits c , integer i ) 
{
  setknbscode_regmem 
  if ( pdffontknbsbase [f ]== 0 ) 
  pdffontknbsbase [f ]= initfontbase ( 0 ) ;
  pdfmem [pdffontknbsbase [f ]+ c ]= fixint ( i , -1000 , 1000 ) ;
} 
void 
zsetstbscode ( internalfontnumber f , eightbits c , integer i ) 
{
  setstbscode_regmem 
  if ( pdffontstbsbase [f ]== 0 ) 
  pdffontstbsbase [f ]= initfontbase ( 0 ) ;
  pdfmem [pdffontstbsbase [f ]+ c ]= fixint ( i , -1000 , 1000 ) ;
} 
void 
zsetshbscode ( internalfontnumber f , eightbits c , integer i ) 
{
  setshbscode_regmem 
  if ( pdffontshbsbase [f ]== 0 ) 
  pdffontshbsbase [f ]= initfontbase ( 0 ) ;
  pdfmem [pdffontshbsbase [f ]+ c ]= fixint ( i , -1000 , 1000 ) ;
} 
void 
zsetknbccode ( internalfontnumber f , eightbits c , integer i ) 
{
  setknbccode_regmem 
  if ( pdffontknbcbase [f ]== 0 ) 
  pdffontknbcbase [f ]= initfontbase ( 0 ) ;
  pdfmem [pdffontknbcbase [f ]+ c ]= fixint ( i , -1000 , 1000 ) ;
} 
void 
zsetknaccode ( internalfontnumber f , eightbits c , integer i ) 
{
  setknaccode_regmem 
  if ( pdffontknacbase [f ]== 0 ) 
  pdffontknacbase [f ]= initfontbase ( 0 ) ;
  pdfmem [pdffontknacbase [f ]+ c ]= fixint ( i , -1000 , 1000 ) ;
} 
void 
zadjustinterwordglue ( halfword p , halfword g ) 
{
  adjustinterwordglue_regmem 
  scaled kn, st, sh  ;
  halfword q, r  ;
  halfword c  ;
  internalfontnumber f  ;
  if ( ! ( ! ( g >= himemmin ) && mem [g ].hh.b0 == 10 ) ) 
  {
    pdfwarning ( 1075 , 1076 , false , false ) ;
    return ;
  } 
  c = 256 ;
  if ( ( p >= himemmin ) ) 
  {
    c = mem [p ].hh.b1 ;
    f = mem [p ].hh.b0 ;
  } 
  else if ( mem [p ].hh.b0 == 6 ) 
  {
    c = mem [p + 1 ].hh.b1 ;
    f = mem [p + 1 ].hh.b0 ;
  } 
  else if ( ( mem [p ].hh.b0 == 11 ) && ( mem [p ].hh.b1 == 1 ) && ( 
  savetail != -268435455L ) ) 
  {
    r = savetail ;
    while ( ( mem [r ].hh .v.RH != -268435455L ) && ( mem [r ].hh .v.RH != 
    p ) ) r = mem [r ].hh .v.RH ;
    if ( ( mem [r ].hh .v.RH == p ) ) {
	
      if ( ( r >= himemmin ) ) 
      {
	c = mem [r ].hh.b1 ;
	f = mem [r ].hh.b0 ;
      } 
      else if ( mem [r ].hh.b0 == 6 ) 
      {
	c = mem [r + 1 ].hh.b1 ;
	f = mem [r + 1 ].hh.b0 ;
      } 
    } 
  } 
  if ( ( c == 256 ) ) 
  return ;
  kn = getknbscode ( f , c ) ;
  st = getstbscode ( f , c ) ;
  sh = getshbscode ( f , c ) ;
  if ( ( kn != 0 ) || ( st != 0 ) || ( sh != 0 ) ) 
  {
    q = newspec ( mem [g + 1 ].hh .v.LH ) ;
    deleteglueref ( mem [g + 1 ].hh .v.LH ) ;
    mem [q + 1 ].cint = mem [q + 1 ].cint + roundxnoverd ( fontinfo [6 + 
    parambase [f ]].cint , kn , 1000 ) ;
    mem [q + 2 ].cint = mem [q + 2 ].cint + roundxnoverd ( fontinfo [6 + 
    parambase [f ]].cint , st , 1000 ) ;
    mem [q + 3 ].cint = mem [q + 3 ].cint + roundxnoverd ( fontinfo [6 + 
    parambase [f ]].cint , sh , 1000 ) ;
    mem [g + 1 ].hh .v.LH = q ;
  } 
} 
halfword 
zgetautokern ( internalfontnumber f , halfword l , halfword r ) 
{
  register halfword Result; getautokern_regmem 
  scaled tmpw  ;
  integer k  ;
  halfword p  ;
  pdfassert ( ( l >= 0 ) && ( r >= 0 ) ) ;
  Result = -268435455L ;
  if ( ( eqtb [29355 ].cint <= 0 ) && ( eqtb [29354 ].cint <= 0 ) ) 
  return Result ;
  tmpw = 0 ;
  if ( ( eqtb [29355 ].cint > 0 ) && ( l < 256 ) ) 
  {
    k = getknaccode ( f , l ) ;
    if ( k != 0 ) 
    tmpw = roundxnoverd ( fontinfo [6 + parambase [f ]].cint , k , 1000 ) 
    ;
  } 
  if ( ( eqtb [29354 ].cint > 0 ) && ( r < 256 ) ) 
  {
    k = getknbccode ( f , r ) ;
    if ( k != 0 ) 
    tmpw = tmpw + roundxnoverd ( fontinfo [6 + parambase [f ]].cint , k , 
    1000 ) ;
  } 
  if ( tmpw != 0 ) 
  {
    p = newkern ( tmpw ) ;
    mem [p ].hh.b1 = 1 ;
    Result = p ;
  } 
  return Result ;
} 
strnumber 
zexpandfontname ( internalfontnumber f , integer e ) 
{
  register strnumber Result; expandfontname_regmem 
  unsigned char oldsetting  ;
  oldsetting = selector ;
  selector = 21 ;
  print ( fontname [f ]) ;
  if ( e > 0 ) 
  print ( 43 ) ;
  printint ( e ) ;
  selector = oldsetting ;
  Result = makestring () ;
  return Result ;
} 
internalfontnumber 
zautoexpandfont ( internalfontnumber f , integer e ) 
{
  register internalfontnumber Result; autoexpandfont_regmem 
  internalfontnumber k  ;
  integer nw, nk, ni, i  ;
  k = fontptr + 1 ;
  incr ( fontptr ) ;
  if ( ( fontptr >= fontmax ) ) 
  overflow ( 1077 , fontmax ) ;
  fontname [k ]= expandfontname ( f , e ) ;
  fontarea [k ]= fontarea [f ];
  hash [17626 + k ].v.RH = hash [17626 + f ].v.RH ;
  hyphenchar [k ]= hyphenchar [f ];
  skewchar [k ]= skewchar [f ];
  fontbchar [k ]= fontbchar [f ];
  fontfalsebchar [k ]= fontfalsebchar [f ];
  fontbc [k ]= fontbc [f ];
  fontec [k ]= fontec [f ];
  fontsize [k ]= fontsize [f ];
  fontdsize [k ]= fontdsize [f ];
  fontparams [k ]= fontparams [f ];
  fontglue [k ]= fontglue [f ];
  bcharlabel [k ]= bcharlabel [f ];
  charbase [k ]= charbase [f ];
  heightbase [k ]= heightbase [f ];
  depthbase [k ]= depthbase [f ];
  ligkernbase [k ]= ligkernbase [f ];
  extenbase [k ]= extenbase [f ];
  parambase [k ]= parambase [f ];
  nw = heightbase [f ]- widthbase [f ];
  ni = ligkernbase [f ]- italicbase [f ];
  nk = extenbase [f ]- ( kernbase [f ]+ 256 * ( 128 ) ) ;
  if ( ( fmemptr + nw + ni + nk >= fontmemsize ) ) 
  overflow ( 1078 , fontmemsize ) ;
  widthbase [k ]= fmemptr ;
  italicbase [k ]= widthbase [k ]+ nw ;
  kernbase [k ]= italicbase [k ]+ ni - 256 * ( 128 ) ;
  fmemptr = fmemptr + nw + ni + nk ;
  {register integer for_end; i = 0 ;for_end = nw - 1 ; if ( i <= for_end) do 
    fontinfo [widthbase [k ]+ i ].cint = roundxnoverd ( fontinfo [
    widthbase [f ]+ i ].cint , 1000 + e , 1000 ) ;
  while ( i++ < for_end ) ;} 
  {register integer for_end; i = 0 ;for_end = ni - 1 ; if ( i <= for_end) do 
    fontinfo [italicbase [k ]+ i ].cint = roundxnoverd ( fontinfo [
    italicbase [f ]+ i ].cint , 1000 + e , 1000 ) ;
  while ( i++ < for_end ) ;} 
  {register integer for_end; i = 0 ;for_end = nk - 1 ; if ( i <= for_end) do 
    fontinfo [kernbase [k ]+ 256 * ( 128 ) + i ].cint = roundxnoverd ( 
    fontinfo [kernbase [f ]+ 256 * ( 128 ) + i ].cint , 1000 + e , 1000 ) 
    ;
  while ( i++ < for_end ) ;} 
  Result = k ;
  return Result ;
} 
void 
zcopyexpandparams ( internalfontnumber k , internalfontnumber f , integer e ) 
{
  copyexpandparams_regmem 
  if ( pdffontrpbase [f ]== 0 ) 
  pdffontrpbase [f ]= initfontbase ( 0 ) ;
  if ( pdffontlpbase [f ]== 0 ) 
  pdffontlpbase [f ]= initfontbase ( 0 ) ;
  if ( pdffontefbase [f ]== 0 ) 
  pdffontefbase [f ]= initfontbase ( 1000 ) ;
  pdffontexpandratio [k ]= e ;
  pdffontstep [k ]= pdffontstep [f ];
  pdffontautoexpand [k ]= pdffontautoexpand [f ];
  pdffontblink [k ]= f ;
  pdffontlpbase [k ]= pdffontlpbase [f ];
  pdffontrpbase [k ]= pdffontrpbase [f ];
  pdffontefbase [k ]= pdffontefbase [f ];
  if ( pdffontknbsbase [f ]== 0 ) 
  pdffontknbsbase [f ]= initfontbase ( 0 ) ;
  if ( pdffontstbsbase [f ]== 0 ) 
  pdffontstbsbase [f ]= initfontbase ( 0 ) ;
  if ( pdffontshbsbase [f ]== 0 ) 
  pdffontshbsbase [f ]= initfontbase ( 0 ) ;
  if ( pdffontknbcbase [f ]== 0 ) 
  pdffontknbcbase [f ]= initfontbase ( 0 ) ;
  if ( pdffontknacbase [f ]== 0 ) 
  pdffontknacbase [f ]= initfontbase ( 0 ) ;
  pdffontknbsbase [k ]= pdffontknbsbase [f ];
  pdffontstbsbase [k ]= pdffontstbsbase [f ];
  pdffontshbsbase [k ]= pdffontshbsbase [f ];
  pdffontknbcbase [k ]= pdffontknbcbase [f ];
  pdffontknacbase [k ]= pdffontknacbase [f ];
} 
internalfontnumber 
ztfmlookup ( strnumber s , scaled fs ) 
{
  register internalfontnumber Result; tfmlookup_regmem 
  internalfontnumber k  ;
  if ( fs != 0 ) 
  {
    {register integer for_end; k = 1 ;for_end = fontptr ; if ( k <= for_end) 
    do 
      if ( ( fontarea [k ]!= 1074 ) && streqstr ( fontname [k ], s ) && ( 
      fontsize [k ]== fs ) ) 
      {
	flushstr ( s ) ;
	Result = k ;
	return Result ;
      } 
    while ( k++ < for_end ) ;} 
  } 
  else {
      
    {register integer for_end; k = 1 ;for_end = fontptr ; if ( k <= for_end) 
    do 
      if ( ( fontarea [k ]!= 1074 ) && streqstr ( fontname [k ], s ) ) 
      {
	flushstr ( s ) ;
	Result = k ;
	return Result ;
      } 
    while ( k++ < for_end ) ;} 
  } 
  Result = 0 ;
  return Result ;
} 
internalfontnumber 
zloadexpandfont ( internalfontnumber f , integer e ) 
{
  /* 40 */ register internalfontnumber Result; loadexpandfont_regmem 
  strnumber s  ;
  internalfontnumber k  ;
  s = expandfontname ( f , e ) ;
  k = tfmlookup ( s , fontsize [f ]) ;
  if ( k == 0 ) 
  {
    if ( pdffontautoexpand [f ]) 
    k = autoexpandfont ( f , e ) ;
    else k = readfontinfo ( 513 , s , 345 , fontsize [f ]) ;
  } 
  copyexpandparams ( k , f , e ) ;
  Result = k ;
  return Result ;
} 
integer 
zfixexpandvalue ( internalfontnumber f , integer e ) 
{
  register integer Result; fixexpandvalue_regmem 
  integer step  ;
  integer maxexpand  ;
  boolean neg  ;
  Result = 0 ;
  if ( e == 0 ) 
  return Result ;
  if ( e < 0 ) 
  {
    e = - (integer) e ;
    neg = true ;
    maxexpand = - (integer) pdffontexpandratio [pdffontshrink [f ]];
  } 
  else {
      
    neg = false ;
    maxexpand = pdffontexpandratio [pdffontstretch [f ]];
  } 
  if ( e > maxexpand ) 
  e = maxexpand ;
  else {
      
    step = pdffontstep [f ];
    if ( e % step > 0 ) 
    e = step * roundxnoverd ( e , 1 , step ) ;
  } 
  if ( neg ) 
  e = - (integer) e ;
  Result = e ;
  return Result ;
} 
internalfontnumber 
zgetexpandfont ( internalfontnumber f , integer e ) 
{
  register internalfontnumber Result; getexpandfont_regmem 
  internalfontnumber k  ;
  k = pdffontelink [f ];
  while ( k != 0 ) {
      
    if ( pdffontexpandratio [k ]== e ) 
    {
      Result = k ;
      return Result ;
    } 
    k = pdffontelink [k ];
  } 
  k = loadexpandfont ( f , e ) ;
  pdffontelink [k ]= pdffontelink [f ];
  pdffontelink [f ]= k ;
  Result = k ;
  return Result ;
} 
internalfontnumber 
zexpandfont ( internalfontnumber f , integer e ) 
{
  register internalfontnumber Result; expandfont_regmem 
  Result = f ;
  if ( e == 0 ) 
  return Result ;
  e = fixexpandvalue ( f , e ) ;
  if ( e == 0 ) 
  return Result ;
  if ( pdffontelink [f ]== 0 ) 
  pdferror ( 1031 , 1079 ) ;
  Result = getexpandfont ( f , e ) ;
  return Result ;
} 
void 
zsetexpandparams ( internalfontnumber f , boolean autoexpand , integer 
stretchlimit , integer shrinklimit , integer fontstep , integer expandratio ) 
{
  setexpandparams_regmem 
  pdffontstep [f ]= fontstep ;
  pdffontautoexpand [f ]= autoexpand ;
  if ( stretchlimit > 0 ) 
  pdffontstretch [f ]= getexpandfont ( f , stretchlimit ) ;
  if ( shrinklimit > 0 ) 
  pdffontshrink [f ]= getexpandfont ( f , - (integer) shrinklimit ) ;
  if ( expandratio != 0 ) 
  pdffontexpandratio [f ]= expandratio ;
} 
void 
zvfexpandlocalfonts ( internalfontnumber f ) 
{
  vfexpandlocalfonts_regmem 
  internalfontnumber lf  ;
  integer k  ;
  pdfassert ( pdffonttype [f ]== 1 ) ;
  {register integer for_end; k = 0 ;for_end = vflocalfontnum [f ]- 1 
  ; if ( k <= for_end) do 
    {
      lf = vfifnts [vfdefaultfont [f ]+ k ];
      setexpandparams ( lf , pdffontautoexpand [f ], pdffontexpandratio [
      pdffontstretch [f ]], - (integer) pdffontexpandratio [pdffontshrink 
      [f ]], pdffontstep [f ], pdffontexpandratio [f ]) ;
      if ( pdffonttype [lf ]== 1 ) 
      vfexpandlocalfonts ( lf ) ;
    } 
  while ( k++ < for_end ) ;} 
} 
void 
readexpandfont ( void ) 
{
  readexpandfont_regmem 
  integer shrinklimit, stretchlimit, fontstep  ;
  internalfontnumber f  ;
  boolean autoexpand  ;
  scanfontident () ;
  f = curval ;
  if ( f == 0 ) 
  pdferror ( 1031 , 868 ) ;
  if ( pdffontblink [f ]!= 0 ) 
  pdferror ( 1031 , 1080 ) ;
  scanoptionalequals () ;
  scanint () ;
  stretchlimit = fixint ( curval , 0 , 1000 ) ;
  scanint () ;
  shrinklimit = fixint ( curval , 0 , 500 ) ;
  scanint () ;
  fontstep = fixint ( curval , 0 , 100 ) ;
  if ( fontstep == 0 ) 
  pdferror ( 1031 , 1081 ) ;
  stretchlimit = stretchlimit - stretchlimit % fontstep ;
  if ( stretchlimit < 0 ) 
  stretchlimit = 0 ;
  shrinklimit = shrinklimit - shrinklimit % fontstep ;
  if ( shrinklimit < 0 ) 
  shrinklimit = 0 ;
  if ( ( stretchlimit == 0 ) && ( shrinklimit == 0 ) ) 
  pdferror ( 1031 , 1082 ) ;
  autoexpand = false ;
  if ( scankeyword ( 1083 ) ) 
  {
    autoexpand = true ;
    {
      getxtoken () ;
      if ( curcmd != 10 ) 
      backinput () ;
    } 
  } 
  if ( ( pdffontexpandratio [f ]!= 0 ) ) 
  pdferror ( 1031 , 1084 ) ;
  if ( ( pdffontstep [f ]!= 0 ) ) 
  {
    if ( pdffontstep [f ]!= fontstep ) 
    pdferror ( 1031 , 1085 ) ;
    if ( ( ( pdffontstretch [f ]== 0 ) && ( stretchlimit != 0 ) ) || ( ( 
    pdffontstretch [f ]!= 0 ) && ( pdffontexpandratio [pdffontstretch [f ]
    ]!= stretchlimit ) ) ) 
    pdferror ( 1031 , 1086 ) ;
    if ( ( ( pdffontshrink [f ]== 0 ) && ( shrinklimit != 0 ) ) || ( ( 
    pdffontshrink [f ]!= 0 ) && ( - (integer) pdffontexpandratio [
    pdffontshrink [f ]]!= shrinklimit ) ) ) 
    pdferror ( 1031 , 1087 ) ;
    if ( pdffontautoexpand [f ]!= autoexpand ) 
    pdferror ( 1031 , 1088 ) ;
  } 
  else {
      
    if ( ( pdffonttype [f ]!= 0 ) && ( pdffonttype [f ]!= 1 ) ) 
    pdfwarning ( 1031 , 1089 , true , true ) ;
    setexpandparams ( f , autoexpand , stretchlimit , shrinklimit , fontstep , 
    0 ) ;
    if ( pdffonttype [f ]== 1 ) 
    vfexpandlocalfonts ( f ) ;
  } 
} 
internalfontnumber 
zletterspacefont ( halfword u , internalfontnumber f , integer e ) 
{
  register internalfontnumber Result; letterspacefont_regmem 
  internalfontnumber k  ;
  scaled w, r  ;
  strnumber s  ;
  integer i, nw  ;
  unsigned char oldsetting  ;
  integer vfz  ;
  integer vfalpha  ;
  unsigned char vfbeta  ;
  k = readfontinfo ( u , fontname [f ], 345 , fontsize [f ]) ;
  if ( scankeyword ( 1090 ) ) 
  setnoligatures ( k ) ;
  nw = heightbase [k ]- widthbase [k ];
  {register integer for_end; i = 0 ;for_end = nw - 1 ; if ( i <= for_end) do 
    fontinfo [widthbase [k ]+ i ].cint = fontinfo [widthbase [k ]+ i ]
    .cint + roundxnoverd ( fontinfo [6 + parambase [k ]].cint , e , 1000 ) 
    ;
  while ( i++ < for_end ) ;} 
  flushstr ( fontname [k ]) ;
  {
    if ( poolptr + ( strstart [fontname [k ]+ 1 ]- strstart [fontname [k 
    ]]) + 7 > poolsize ) 
    overflow ( 259 , poolsize - initpoolptr ) ;
  } 
  oldsetting = selector ;
  selector = 21 ;
  print ( fontname [k ]) ;
  if ( e > 0 ) 
  print ( 43 ) ;
  printint ( e ) ;
  print ( 1091 ) ;
  selector = oldsetting ;
  fontname [k ]= makestring () ;
  allocvffnts () ;
  vfefnts [vfnf ]= 0 ;
  vfifnts [vfnf ]= f ;
  incr ( vfnf ) ;
  vflocalfontnum [k ]= 1 ;
  vfdefaultfont [k ]= vfnf - 1 ;
  pdffonttype [k ]= 1 ;
  vfz = fontsize [f ];
  {
    vfalpha = 16 ;
    while ( vfz >= 8388608L ) {
	
      vfz = vfz / 2 ;
      vfalpha = vfalpha + vfalpha ;
    } 
    vfbeta = 256 / vfalpha ;
    vfalpha = vfalpha * vfz ;
  } 
  w = roundxnoverd ( fontinfo [6 + parambase [f ]].cint , e , 2000 ) ;
  if ( w >= 0 ) 
  tmpw .qqqq .b0 = 0 ;
  else {
      
    tmpw .qqqq .b0 = 255 ;
    w = vfalpha + w ;
  } 
  r = w * vfbeta ;
  tmpw .qqqq .b1 = r / vfz ;
  r = r % vfz ;
  if ( r == 0 ) 
  tmpw .qqqq .b2 = 0 ;
  else {
      
    r = r * 256 ;
    tmpw .qqqq .b2 = r / vfz ;
    r = r % vfz ;
  } 
  if ( r == 0 ) 
  tmpw .qqqq .b3 = 0 ;
  else {
      
    r = r * 256 ;
    tmpw .qqqq .b3 = r / vfz ;
  } 
  vfpacketbase [k ]= newvfpacket ( k ) ;
  {register integer for_end; c = fontbc [k ];for_end = fontec [k ]; if ( 
  c <= for_end) do 
    {
      {
	if ( poolptr + 12 > poolsize ) 
	overflow ( 259 , poolsize - initpoolptr ) ;
      } 
      {
	strpool [poolptr ]= 146 ;
	incr ( poolptr ) ;
      } 
      {
	strpool [poolptr ]= tmpw .qqqq .b0 ;
	incr ( poolptr ) ;
      } 
      {
	strpool [poolptr ]= tmpw .qqqq .b1 ;
	incr ( poolptr ) ;
      } 
      {
	strpool [poolptr ]= tmpw .qqqq .b2 ;
	incr ( poolptr ) ;
      } 
      {
	strpool [poolptr ]= tmpw .qqqq .b3 ;
	incr ( poolptr ) ;
      } 
      if ( c < 128 ) 
      {
	strpool [poolptr ]= c ;
	incr ( poolptr ) ;
      } 
      else {
	  
	{
	  strpool [poolptr ]= 128 ;
	  incr ( poolptr ) ;
	} 
	{
	  strpool [poolptr ]= c ;
	  incr ( poolptr ) ;
	} 
      } 
      {
	strpool [poolptr ]= 146 ;
	incr ( poolptr ) ;
      } 
      {
	strpool [poolptr ]= tmpw .qqqq .b0 ;
	incr ( poolptr ) ;
      } 
      {
	strpool [poolptr ]= tmpw .qqqq .b1 ;
	incr ( poolptr ) ;
      } 
      {
	strpool [poolptr ]= tmpw .qqqq .b2 ;
	incr ( poolptr ) ;
      } 
      {
	strpool [poolptr ]= tmpw .qqqq .b3 ;
	incr ( poolptr ) ;
      } 
      s = makestring () ;
      storepacket ( k , c , s ) ;
      flushstr ( s ) ;
    } 
  while ( c++ < for_end ) ;} 
  Result = k ;
  return Result ;
} 
void 
znewletterspacedfont ( smallnumber a ) 
{
  newletterspacedfont_regmem 
  halfword u  ;
  strnumber t  ;
  unsigned char oldsetting  ;
  internalfontnumber f, k  ;
  getrtoken () ;
  u = curcs ;
  if ( u >= 514 ) 
  t = hash [u ].v.RH ;
  else if ( u >= 257 ) {
      
    if ( u == 513 ) 
    t = 1092 ;
    else t = u - 257 ;
  } 
  else {
      
    oldsetting = selector ;
    selector = 21 ;
    print ( 1092 ) ;
    print ( u - 1 ) ;
    selector = oldsetting ;
    {
      if ( poolptr + 1 > poolsize ) 
      overflow ( 259 , poolsize - initpoolptr ) ;
    } 
    t = makestring () ;
  } 
  if ( ( a >= 4 ) ) 
  geqdefine ( u , 87 , 0 ) ;
  else eqdefine ( u , 87 , 0 ) ;
  scanoptionalequals () ;
  scanfontident () ;
  k = curval ;
  scanint () ;
  f = letterspacefont ( u , k , fixint ( curval , -1000 , 1000 ) ) ;
  eqtb [u ].hh .v.RH = f ;
  eqtb [17626 + f ]= eqtb [u ];
  hash [17626 + f ].v.RH = t ;
} 
boolean 
zisletterspacedfont ( internalfontnumber f ) 
{
  /* 30 */ register boolean Result; isletterspacedfont_regmem 
  poolpointer i, j  ;
  Result = false ;
  if ( pdffonttype [f ]!= 1 ) 
  return Result ;
  i = strstart [fontname [f ]+ 1 ]- 1 ;
  j = strstart [fontname [f ]];
  if ( ( strpool [i - 1 ]!= 'l' ) || ( strpool [i ]!= 's' ) ) 
  return Result ;
  i = i - 2 ;
  while ( i >= j ) {
      
    if ( ( strpool [i ]< '0' ) || ( strpool [i ]> '9' ) ) 
    goto lab30 ;
    i = i - 1 ;
  } 
  lab30: if ( i < j ) 
  return Result ;
  if ( ( strpool [i ]!= '+' ) && ( strpool [i ]!= '-' ) ) 
  return Result ;
  Result = true ;
  return Result ;
} 
internalfontnumber 
zcopyfontinfo ( internalfontnumber f ) 
{
  register internalfontnumber Result; copyfontinfo_regmem 
  halfword lf, bc, ec, i  ;
  internalfontnumber k  ;
  if ( ( pdffontexpandratio [f ]!= 0 ) || ( pdffontstep [f ]!= 0 ) ) 
  pdferror ( 1093 , 1094 ) ;
  if ( isletterspacedfont ( f ) ) 
  pdferror ( 1093 , 1095 ) ;
  k = fontptr + 1 ;
  incr ( fontptr ) ;
  if ( ( fontptr >= fontmax ) ) 
  overflow ( 1077 , fontmax ) ;
  fontname [k ]= fontname [f ];
  fontarea [k ]= 1074 ;
  hyphenchar [k ]= hyphenchar [f ];
  skewchar [k ]= skewchar [f ];
  fontbchar [k ]= fontbchar [f ];
  fontfalsebchar [k ]= fontfalsebchar [f ];
  fontbc [k ]= fontbc [f ];
  fontec [k ]= fontec [f ];
  fontsize [k ]= fontsize [f ];
  fontdsize [k ]= fontdsize [f ];
  fontparams [k ]= fontparams [f ];
  fontglue [k ]= fontglue [f ];
  bcharlabel [k ]= bcharlabel [f ];
  bc = fontbc [f ];
  ec = fontec [f ];
  charbase [k ]= fmemptr - bc ;
  widthbase [k ]= charbase [k ]+ ec + 1 ;
  heightbase [k ]= widthbase [k ]+ ( heightbase [f ]- widthbase [f ]) 
  ;
  depthbase [k ]= heightbase [k ]+ ( depthbase [f ]- heightbase [f ]) 
  ;
  italicbase [k ]= depthbase [k ]+ ( italicbase [f ]- depthbase [f ]) 
  ;
  ligkernbase [k ]= italicbase [k ]+ ( ligkernbase [f ]- italicbase [f 
  ]) ;
  kernbase [k ]= ligkernbase [k ]+ ( kernbase [f ]- ligkernbase [f ]) 
  ;
  extenbase [k ]= kernbase [k ]+ ( extenbase [f ]- kernbase [f ]) ;
  parambase [k ]= extenbase [k ]+ ( parambase [f ]- extenbase [f ]) ;
  lf = ( parambase [f ]- charbase [f ]) + fontparams [f ]+ 1 ;
  if ( ( fmemptr + lf >= fontmemsize ) ) 
  overflow ( 1078 , fontmemsize ) ;
  {register integer for_end; i = 0 ;for_end = lf - 1 ; if ( i <= for_end) do 
    fontinfo [charbase [k ]+ bc + i ]= fontinfo [charbase [f ]+ bc + i 
    ];
  while ( i++ < for_end ) ;} 
  fmemptr = fmemptr + lf ;
  Result = k ;
  return Result ;
} 
void 
zmakefontcopy ( smallnumber a ) 
{
  makefontcopy_regmem 
  halfword u  ;
  strnumber t  ;
  unsigned char oldsetting  ;
  internalfontnumber f, k  ;
  getrtoken () ;
  u = curcs ;
  if ( u >= 514 ) 
  t = hash [u ].v.RH ;
  else if ( u >= 257 ) {
      
    if ( u == 513 ) 
    t = 1092 ;
    else t = u - 257 ;
  } 
  else {
      
    oldsetting = selector ;
    selector = 21 ;
    print ( 1092 ) ;
    print ( u - 1 ) ;
    selector = oldsetting ;
    {
      if ( poolptr + 1 > poolsize ) 
      overflow ( 259 , poolsize - initpoolptr ) ;
    } 
    t = makestring () ;
  } 
  if ( ( a >= 4 ) ) 
  geqdefine ( u , 87 , 0 ) ;
  else eqdefine ( u , 87 , 0 ) ;
  scanoptionalequals () ;
  scanfontident () ;
  k = curval ;
  f = copyfontinfo ( k ) ;
  eqtb [u ].hh .v.RH = f ;
  eqtb [17626 + f ]= eqtb [u ];
  hash [17626 + f ].v.RH = t ;
} 
void 
zvferror ( strnumber filename , strnumber msg ) 
{
  vferror_regmem 
  unsigned char oldsetting  ;
  strnumber s  ;
  {
    if ( poolptr + ( strstart [filename + 1 ]- strstart [filename ]) + 3 > 
    poolsize ) 
    overflow ( 259 , poolsize - initpoolptr ) ;
  } 
  oldsetting = selector ;
  selector = 21 ;
  print ( filename ) ;
  print ( 1096 ) ;
  s = makestring () ;
  selector = oldsetting ;
  pdferror ( s , msg ) ;
} 
eightbits 
vfbyte ( void ) 
{
  register eightbits Result; vfbyte_regmem 
  integer i  ;
  i = getc ( vffile ) ;
  if ( i < 0 ) 
  pdferror ( 1097 , 1098 ) ;
  Result = i ;
  return Result ;
} 
integer 
zvfreadsigned ( integer k ) 
{
  register integer Result; vfreadsigned_regmem 
  integer i  ;
  pdfassert ( ( k > 0 ) && ( k <= 4 ) ) ;
  i = vfbyte () ;
  if ( i >= 128 ) 
  i = i - 256 ;
  decr ( k ) ;
  while ( k > 0 ) {
      
    i = i * 256 + vfbyte () ;
    decr ( k ) ;
  } 
  Result = i ;
  return Result ;
} 
integer 
zvfreadunsigned ( integer k ) 
{
  register integer Result; vfreadunsigned_regmem 
  integer i  ;
  pdfassert ( ( k > 0 ) && ( k <= 4 ) ) ;
  i = vfbyte () ;
  if ( ( k == 4 ) && ( i >= 128 ) ) 
  vferror ( fontname [f ], 1023 ) ;
  decr ( k ) ;
  while ( k > 0 ) {
      
    i = i * 256 + vfbyte () ;
    decr ( k ) ;
  } 
  Result = i ;
  return Result ;
} 
void 
zvflocalfontwarning ( internalfontnumber f , internalfontnumber k , strnumber 
s ) 
{
  vflocalfontwarning_regmem 
  printnl ( s ) ;
  print ( 1099 ) ;
  print ( fontname [k ]) ;
  print ( 1100 ) ;
  print ( fontname [f ]) ;
  print ( 1101 ) ;
} 
internalfontnumber 
zvfdeffont ( internalfontnumber f ) 
{
  register internalfontnumber Result; vfdeffont_regmem 
  internalfontnumber k  ;
  strnumber s  ;
  scaled ds, fs  ;
  fourquarters cs  ;
  cs .b0 = vfbyte () ;
  cs .b1 = vfbyte () ;
  cs .b2 = vfbyte () ;
  cs .b3 = vfbyte () ;
  fs = storescaledf ( vfreadsigned ( 4 ) , fontsize [f ]) ;
  ds = vfreadsigned ( 4 ) / 16 ;
  tmpw .qqqq .b0 = vfbyte () ;
  tmpw .qqqq .b1 = vfbyte () ;
  while ( tmpw .qqqq .b0 > 0 ) {
      
    decr ( tmpw .qqqq .b0 ) ;
    {
      if ( vfbyte () != 0 ) 
      ;
    } 
  } 
  {
    if ( poolptr + tmpw .qqqq .b1 > poolsize ) 
    overflow ( 259 , poolsize - initpoolptr ) ;
  } 
  while ( tmpw .qqqq .b1 > 0 ) {
      
    decr ( tmpw .qqqq .b1 ) ;
    {
      strpool [poolptr ]= vfbyte () ;
      incr ( poolptr ) ;
    } 
  } 
  s = makestring () ;
  k = tfmlookup ( s , fs ) ;
  if ( k == 0 ) 
  k = readfontinfo ( 513 , s , 345 , fs ) ;
  if ( k != 0 ) 
  {
    if ( ( ( cs .b0 != 0 ) || ( cs .b1 != 0 ) || ( cs .b2 != 0 ) || ( cs .b3 
    != 0 ) ) && ( ( fontcheck [k ].b0 != 0 ) || ( fontcheck [k ].b1 != 0 ) 
    || ( fontcheck [k ].b2 != 0 ) || ( fontcheck [k ].b3 != 0 ) ) && ( ( 
    cs .b0 != fontcheck [k ].b0 ) || ( cs .b1 != fontcheck [k ].b1 ) || ( 
    cs .b2 != fontcheck [k ].b2 ) || ( cs .b3 != fontcheck [k ].b3 ) ) ) 
    vflocalfontwarning ( f , k , 1102 ) ;
    if ( ds != fontdsize [k ]) 
    vflocalfontwarning ( f , k , 1103 ) ;
  } 
  if ( ( pdffontstep [f ]!= 0 ) ) 
  setexpandparams ( k , pdffontautoexpand [f ], pdffontexpandratio [
  pdffontstretch [f ]], - (integer) pdffontexpandratio [pdffontshrink [f 
  ]], pdffontstep [f ], pdffontexpandratio [f ]) ;
  Result = k ;
  return Result ;
} 
void 
zdovf ( internalfontnumber f ) 
{
  dovf_regmem 
  integer cmd, k, n  ;
  integer cc, cmdlength, packetlength  ;
  scaled tfmwidth  ;
  strnumber s  ;
  vfstackindex stacklevel  ;
  internalfontnumber savevfnf  ;
  pdffonttype [f ]= 2 ;
  if ( autoexpandvf ( f ) ) 
  return ;
  stacklevel = 0 ;
  packfilename ( fontname [f ], 345 , 1096 ) ;
  if ( ! vfbopenin ( vffile ) ) 
  return ;
  if ( vfbyte () != 247 ) 
  vferror ( fontname [f ], 1105 ) ;
  if ( vfbyte () != 202 ) 
  vferror ( fontname [f ], 1106 ) ;
  cmdlength = vfbyte () ;
  {register integer for_end; k = 1 ;for_end = cmdlength ; if ( k <= for_end) 
  do 
    {
      if ( vfbyte () != 0 ) 
      ;
    } 
  while ( k++ < for_end ) ;} 
  tmpw .qqqq .b0 = vfbyte () ;
  tmpw .qqqq .b1 = vfbyte () ;
  tmpw .qqqq .b2 = vfbyte () ;
  tmpw .qqqq .b3 = vfbyte () ;
  if ( ( ( tmpw .qqqq .b0 != 0 ) || ( tmpw .qqqq .b1 != 0 ) || ( tmpw .qqqq 
  .b2 != 0 ) || ( tmpw .qqqq .b3 != 0 ) ) && ( ( fontcheck [f ].b0 != 0 ) || 
  ( fontcheck [f ].b1 != 0 ) || ( fontcheck [f ].b2 != 0 ) || ( fontcheck 
  [f ].b3 != 0 ) ) && ( ( tmpw .qqqq .b0 != fontcheck [f ].b0 ) || ( tmpw 
  .qqqq .b1 != fontcheck [f ].b1 ) || ( tmpw .qqqq .b2 != fontcheck [f ]
  .b2 ) || ( tmpw .qqqq .b3 != fontcheck [f ].b3 ) ) ) 
  {
    printnl ( 1107 ) ;
    print ( fontname [f ]) ;
    print ( 1108 ) ;
  } 
  if ( vfreadsigned ( 4 ) / 16 != fontdsize [f ]) 
  {
    printnl ( 1109 ) ;
    print ( fontname [f ]) ;
    print ( 1108 ) ;
  } 
  fflush ( stdout ) ;
  cmd = vfbyte () ;
  savevfnf = vfnf ;
  while ( ( cmd >= 243 ) && ( cmd <= 246 ) ) {
      
    allocvffnts () ;
    vfefnts [vfnf ]= vfreadunsigned ( cmd - 242 ) ;
    vfifnts [vfnf ]= vfdeffont ( f ) ;
    incr ( vfnf ) ;
    cmd = vfbyte () ;
  } 
  vfdefaultfont [f ]= savevfnf ;
  vflocalfontnum [f ]= vfnf - savevfnf ;
  vfpacketbase [f ]= newvfpacket ( f ) ;
  while ( cmd <= 242 ) {
      
    if ( cmd == 242 ) 
    {
      packetlength = vfreadunsigned ( 4 ) ;
      cc = vfreadunsigned ( 4 ) ;
      if ( ! ( ( fontbc [f ]<= cc ) && ( cc <= fontec [f ]) && ( fontinfo 
      [charbase [f ]+ cc ].qqqq .b0 > 0 ) ) ) 
      vferror ( fontname [f ], 1110 ) ;
      tfmwidth = storescaledf ( vfreadsigned ( 4 ) , fontsize [f ]) ;
    } 
    else {
	
      packetlength = cmd ;
      cc = vfbyte () ;
      if ( ! ( ( fontbc [f ]<= cc ) && ( cc <= fontec [f ]) && ( fontinfo 
      [charbase [f ]+ cc ].qqqq .b0 > 0 ) ) ) 
      vferror ( fontname [f ], 1110 ) ;
      tfmwidth = storescaledf ( vfreadunsigned ( 3 ) , fontsize [f ]) ;
    } 
    if ( packetlength < 0 ) 
    vferror ( fontname [f ], 1111 ) ;
    if ( packetlength > 10000 ) 
    vferror ( fontname [f ], 1112 ) ;
    if ( tfmwidth != fontinfo [widthbase [f ]+ fontinfo [charbase [f ]+ 
    effectivechar ( true , f , cc ) ].qqqq .b0 ].cint ) 
    {
      printnl ( 1113 ) ;
      print ( fontname [f ]) ;
      print ( 1108 ) ;
    } 
    {
      if ( poolptr + packetlength > poolsize ) 
      overflow ( 259 , poolsize - initpoolptr ) ;
    } 
    while ( packetlength > 0 ) {
	
      cmd = vfbyte () ;
      decr ( packetlength ) ;
      if ( ( cmd >= 0 ) && ( cmd <= 127 ) ) 
      cmdlength = 0 ;
      else if ( ( ( 171 <= cmd ) && ( cmd <= 234 ) ) || ( ( 235 <= cmd ) && ( 
      cmd <= 238 ) ) ) 
      {
	if ( cmd >= 235 ) 
	{
	  k = vfreadunsigned ( cmd - 234 ) ;
	  packetlength = packetlength - ( cmd - 234 ) ;
	} 
	else k = cmd - 171 ;
	if ( k >= 256 ) 
	vferror ( fontname [f ], 1116 ) ;
	n = 0 ;
	while ( ( n < vflocalfontnum [f ]) && ( vfefnts [vfdefaultfont [f 
	]+ n ]!= k ) ) incr ( n ) ;
	if ( n == vflocalfontnum [f ]) 
	vferror ( fontname [f ], 1117 ) ;
	if ( k <= 63 ) 
	{
	  strpool [poolptr ]= 171 + k ;
	  incr ( poolptr ) ;
	} 
	else {
	    
	  {
	    strpool [poolptr ]= 235 ;
	    incr ( poolptr ) ;
	  } 
	  {
	    strpool [poolptr ]= k ;
	    incr ( poolptr ) ;
	  } 
	} 
	cmdlength = 0 ;
	cmd = 138 ;
      } 
      else switch ( cmd ) 
      {case 132 : 
      case 137 : 
	cmdlength = 8 ;
	break ;
      case 128 : 
      case 129 : 
      case 130 : 
      case 131 : 
	cmdlength = cmd - 127 ;
	break ;
      case 133 : 
      case 134 : 
      case 135 : 
      case 136 : 
	cmdlength = cmd - 132 ;
	break ;
      case 143 : 
      case 144 : 
      case 145 : 
      case 146 : 
	cmdlength = cmd - 142 ;
	break ;
      case 148 : 
      case 149 : 
      case 150 : 
      case 151 : 
	cmdlength = cmd - 147 ;
	break ;
      case 153 : 
      case 154 : 
      case 155 : 
      case 156 : 
	cmdlength = cmd - 152 ;
	break ;
      case 157 : 
      case 158 : 
      case 159 : 
      case 160 : 
	cmdlength = cmd - 156 ;
	break ;
      case 162 : 
      case 163 : 
      case 164 : 
      case 165 : 
	cmdlength = cmd - 161 ;
	break ;
      case 167 : 
      case 168 : 
      case 169 : 
      case 170 : 
	cmdlength = cmd - 166 ;
	break ;
      case 239 : 
      case 240 : 
      case 241 : 
      case 242 : 
	{
	  cmdlength = vfreadunsigned ( cmd - 238 ) ;
	  packetlength = packetlength - ( cmd - 238 ) ;
	  if ( cmdlength > 10000 ) 
	  vferror ( fontname [f ], 1112 ) ;
	  if ( cmdlength < 0 ) 
	  vferror ( fontname [f ], 1118 ) ;
	  {
	    strpool [poolptr ]= 239 ;
	    incr ( poolptr ) ;
	  } 
	  {
	    strpool [poolptr ]= cmdlength ;
	    incr ( poolptr ) ;
	  } 
	  cmd = 138 ;
	} 
	break ;
      case 147 : 
      case 152 : 
      case 161 : 
      case 166 : 
      case 138 : 
	cmdlength = 0 ;
	break ;
      case 141 : 
      case 142 : 
	{
	  cmdlength = 0 ;
	  if ( cmd == 141 ) {
	      
	    if ( stacklevel == vfstacksize ) 
	    overflow ( 1119 , vfstacksize ) ;
	    else incr ( stacklevel ) ;
	  } 
	  else if ( stacklevel == 0 ) 
	  vferror ( fontname [f ], 1120 ) ;
	  else decr ( stacklevel ) ;
	} 
	break ;
	default: 
	vferror ( fontname [f ], 1121 ) ;
	break ;
      } 
      if ( cmd != 138 ) 
      {
	strpool [poolptr ]= cmd ;
	incr ( poolptr ) ;
      } 
      packetlength = packetlength - cmdlength ;
      while ( cmdlength > 0 ) {
	  
	decr ( cmdlength ) ;
	{
	  strpool [poolptr ]= vfbyte () ;
	  incr ( poolptr ) ;
	} 
      } 
    } 
    if ( stacklevel != 0 ) 
    vferror ( fontname [f ], 1114 ) ;
    if ( packetlength != 0 ) 
    vferror ( fontname [f ], 1115 ) ;
    s = makestring () ;
    storepacket ( f , cc , s ) ;
    flushstr ( s ) ;
    cmd = vfbyte () ;
  } 
  if ( cmd != 248 ) 
  vferror ( fontname [f ], 1104 ) ;
  bclose ( vffile ) ;
  pdffonttype [f ]= 1 ;
} 
void 
pdfcheckvfcurval ( void ) 
{
  pdfcheckvfcurval_regmem 
  internalfontnumber f  ;
  f = curval ;
  dovf ( f ) ;
  if ( pdffonttype [f ]== 1 ) 
  pdferror ( 590 , 1122 ) ;
} 
boolean 
zautoexpandvf ( internalfontnumber f ) 
{
  register boolean Result; autoexpandvf_regmem 
  internalfontnumber bf, lf  ;
  integer e, k  ;
  Result = false ;
  if ( ( ! pdffontautoexpand [f ]) || ( pdffontblink [f ]== 0 ) ) 
  return Result ;
  bf = pdffontblink [f ];
  if ( pdffonttype [bf ]== 0 ) 
  dovf ( bf ) ;
  if ( pdffonttype [bf ]!= 1 ) 
  return Result ;
  e = pdffontexpandratio [f ];
  {register integer for_end; k = 0 ;for_end = vflocalfontnum [bf ]- 1 
  ; if ( k <= for_end) do 
    {
      lf = vfdefaultfont [bf ]+ k ;
      allocvffnts () ;
      vfefnts [vfnf ]= vfefnts [lf ];
      vfifnts [vfnf ]= autoexpandfont ( vfifnts [lf ], e ) ;
      copyexpandparams ( vfifnts [vfnf ], vfifnts [lf ], e ) ;
      incr ( vfnf ) ;
    } 
  while ( k++ < for_end ) ;} 
  vfpacketbase [f ]= vfpacketbase [bf ];
  vflocalfontnum [f ]= vflocalfontnum [bf ];
  vfdefaultfont [f ]= vfnf - vflocalfontnum [f ];
  pdffonttype [f ]= 1 ;
  Result = true ;
  return Result ;
} 
integer 
zpacketreadsigned ( integer k ) 
{
  register integer Result; packetreadsigned_regmem 
  integer i  ;
  pdfassert ( ( k > 0 ) && ( k <= 4 ) ) ;
  i = packetbyte () ;
  if ( i >= 128 ) 
  i = i - 256 ;
  decr ( k ) ;
  while ( k > 0 ) {
      
    i = i * 256 + packetbyte () ;
    decr ( k ) ;
  } 
  Result = i ;
  return Result ;
} 
integer 
zpacketreadunsigned ( integer k ) 
{
  register integer Result; packetreadunsigned_regmem 
  integer i  ;
  pdfassert ( ( k > 0 ) && ( k <= 4 ) ) ;
  i = packetbyte () ;
  if ( ( k == 4 ) && ( i >= 128 ) ) 
  vferror ( fontname [f ], 1023 ) ;
  decr ( k ) ;
  while ( k > 0 ) {
      
    i = i * 256 + packetbyte () ;
    decr ( k ) ;
  } 
  Result = i ;
  return Result ;
} 
scaled 
zpacketscaled ( integer k , scaled fs ) 
{
  register scaled Result; packetscaled_regmem 
  Result = storescaledf ( packetreadsigned ( k ) , fs ) ;
  return Result ;
} 
void 
zdovfpacket ( internalfontnumber vff , eightbits c ) 
{
  /* 70 22 */ dovfpacket_regmem 
  internalfontnumber f, k, n  ;
  scaled savecurh, savecurv  ;
  integer cmd  ;
  boolean charmove  ;
  scaled w, x, y, z  ;
  strnumber s  ;
  incr ( vfcurs ) ;
  if ( vfcurs > vfmaxrecursion ) 
  overflow ( 1123 , vfmaxrecursion ) ;
  savecurv = curv ;
  savecurh = curh ;
  pushpacketstate () ;
  startpacket ( vff , c ) ;
  f = vfifnts [vfdefaultfont [vff ]];
  w = 0 ;
  x = 0 ;
  y = 0 ;
  z = 0 ;
  while ( vfpacketlength > 0 ) {
      
    cmd = packetbyte () ;
    if ( ( cmd >= 0 ) && ( cmd <= 127 ) ) 
    {
      if ( ! ( ( fontbc [f ]<= cmd ) && ( cmd <= fontec [f ]) && ( 
      fontinfo [charbase [f ]+ cmd ].qqqq .b0 > 0 ) ) ) 
      {
	charwarning ( f , cmd ) ;
	goto lab22 ;
      } 
      c = cmd ;
      charmove = true ;
      goto lab70 ;
    } 
    else if ( ( ( 171 <= cmd ) && ( cmd <= 234 ) ) || ( cmd == 235 ) ) 
    {
      if ( cmd == 235 ) 
      k = packetbyte () ;
      else k = cmd - 171 ;
      n = 0 ;
      while ( ( n < vflocalfontnum [vff ]) && ( vfefnts [vfdefaultfont [
      vff ]+ n ]!= k ) ) incr ( n ) ;
      if ( ( n == vflocalfontnum [vff ]) ) 
      pdferror ( 1097 , 1124 ) ;
      else f = vfifnts [vfdefaultfont [vff ]+ n ];
    } 
    else switch ( cmd ) 
    {case 141 : 
      {
	vfstack [vfstackptr ].stackh = curh ;
	vfstack [vfstackptr ].stackv = curv ;
	vfstack [vfstackptr ].stackw = w ;
	vfstack [vfstackptr ].stackx = x ;
	vfstack [vfstackptr ].stacky = y ;
	vfstack [vfstackptr ].stackz = z ;
	incr ( vfstackptr ) ;
      } 
      break ;
    case 142 : 
      {
	decr ( vfstackptr ) ;
	curh = vfstack [vfstackptr ].stackh ;
	curv = vfstack [vfstackptr ].stackv ;
	w = vfstack [vfstackptr ].stackw ;
	x = vfstack [vfstackptr ].stackx ;
	y = vfstack [vfstackptr ].stacky ;
	z = vfstack [vfstackptr ].stackz ;
      } 
      break ;
    case 128 : 
    case 129 : 
    case 130 : 
    case 131 : 
    case 133 : 
    case 134 : 
    case 135 : 
    case 136 : 
      {
	if ( ( 128 <= cmd ) && ( cmd <= 131 ) ) 
	{
	  tmpw .cint = packetreadunsigned ( cmd - 127 ) ;
	  charmove = true ;
	} 
	else {
	    
	  tmpw .cint = packetreadunsigned ( cmd - 132 ) ;
	  charmove = false ;
	} 
	if ( ! ( ( fontbc [f ]<= tmpw .cint ) && ( tmpw .cint <= fontec [f 
	]) && ( fontinfo [charbase [f ]+ tmpw .cint ].qqqq .b0 > 0 ) ) ) 
	{
	  charwarning ( f , tmpw .cint ) ;
	  goto lab22 ;
	} 
	c = tmpw .cint ;
	goto lab70 ;
      } 
      break ;
    case 132 : 
    case 137 : 
      {
	ruleht = packetscaled ( 4 , fontsize [vff ]) ;
	rulewd = packetscaled ( 4 , fontsize [vff ]) ;
	if ( ( rulewd > 0 ) && ( ruleht > 0 ) ) 
	{
	  pdfsetrule ( curh , curv , rulewd , ruleht ) ;
	  if ( cmd == 132 ) 
	  curh = curh + rulewd ;
	} 
      } 
      break ;
    case 143 : 
    case 144 : 
    case 145 : 
    case 146 : 
      curh = curh + packetscaled ( cmd - 142 , fontsize [vff ]) ;
      break ;
    case 147 : 
    case 148 : 
    case 149 : 
    case 150 : 
    case 151 : 
      {
	if ( cmd > 147 ) 
	w = packetscaled ( cmd - 147 , fontsize [vff ]) ;
	curh = curh + w ;
      } 
      break ;
    case 152 : 
    case 153 : 
    case 154 : 
    case 155 : 
    case 156 : 
      {
	if ( cmd > 152 ) 
	x = packetscaled ( cmd - 152 , fontsize [vff ]) ;
	curh = curh + x ;
      } 
      break ;
    case 157 : 
    case 158 : 
    case 159 : 
    case 160 : 
      curv = curv + packetscaled ( cmd - 156 , fontsize [vff ]) ;
      break ;
    case 161 : 
    case 162 : 
    case 163 : 
    case 164 : 
    case 165 : 
      {
	if ( cmd > 161 ) 
	y = packetscaled ( cmd - 161 , fontsize [vff ]) ;
	curv = curv + y ;
      } 
      break ;
    case 166 : 
    case 167 : 
    case 168 : 
    case 169 : 
    case 170 : 
      {
	if ( cmd > 166 ) 
	z = packetscaled ( cmd - 166 , fontsize [vff ]) ;
	curv = curv + z ;
      } 
      break ;
    case 239 : 
    case 240 : 
    case 241 : 
    case 242 : 
      {
	tmpw .cint = packetreadunsigned ( cmd - 238 ) ;
	{
	  if ( poolptr + tmpw .cint > poolsize ) 
	  overflow ( 259 , poolsize - initpoolptr ) ;
	} 
	while ( tmpw .cint > 0 ) {
	    
	  decr ( tmpw .cint ) ;
	  {
	    strpool [poolptr ]= packetbyte () ;
	    incr ( poolptr ) ;
	  } 
	} 
	s = makestring () ;
	literal ( s , 3 , false ) ;
	flushstr ( s ) ;
      } 
      break ;
      default: 
      pdferror ( 1097 , 1125 ) ;
      break ;
    } 
    goto lab22 ;
    lab70: if ( ( ( fontbc [f ]<= c ) && ( c <= fontec [f ]) && ( fontinfo 
    [charbase [f ]+ c ].qqqq .b0 > 0 ) ) ) 
    {
      if ( pdffonttype [f ]== 0 ) 
      dovf ( f ) ;
      if ( pdffonttype [f ]== 1 ) 
      dovfpacket ( f , c ) ;
      else {
	  
	pdfbeginstring ( f ) ;
	pdfprintchar ( f , c ) ;
	advcharwidth ( f , c ) ;
      } 
    } 
    else charwarning ( f , c ) ;
    if ( charmove ) 
    curh = curh + fontinfo [widthbase [f ]+ fontinfo [charbase [f ]+ 
    effectivechar ( true , f , c ) ].qqqq .b0 ].cint ;
    lab22: ;
  } 
  poppacketstate () ;
  curv = savecurv ;
  curh = savecurh ;
  decr ( vfcurs ) ;
} 
void 
zpdfoutliteral ( halfword p ) 
{
  pdfoutliteral_regmem 
  unsigned char oldsetting  ;
  strnumber s  ;
  oldsetting = selector ;
  selector = 21 ;
  showtokenlist ( mem [mem [p + 1 ].hh .v.RH ].hh .v.RH , -268435455L , 
  poolsize - poolptr ) ;
  selector = oldsetting ;
  s = makestring () ;
  literal ( s , mem [p + 1 ].hh .v.LH , false ) ;
  flushstr ( s ) ;
} 
void 
zpdfoutcolorstack ( halfword p ) 
{
  pdfoutcolorstack_regmem 
  unsigned char oldsetting  ;
  strnumber s  ;
  integer cmd  ;
  integer stackno  ;
  integer literalmode  ;
  cmd = mem [p + 1 ].hh .v.LH ;
  stackno = mem [p + 1 ].hh .v.RH ;
  if ( stackno >= colorstackused () ) 
  {
    printnl ( 345 ) ;
    print ( 1126 ) ;
    printint ( stackno ) ;
    print ( 1127 ) ;
    printnl ( 345 ) ;
    return ;
  } 
  switch ( cmd ) 
  {case 0 : 
  case 1 : 
    {
      oldsetting = selector ;
      selector = 21 ;
      showtokenlist ( mem [mem [p + 2 ].hh .v.RH ].hh .v.RH , -268435455L 
      , poolsize - poolptr ) ;
      selector = oldsetting ;
      s = makestring () ;
      if ( cmd == 0 ) 
      literalmode = colorstackset ( stackno , s ) ;
      else literalmode = colorstackpush ( stackno , s ) ;
      if ( ( strstart [s + 1 ]- strstart [s ]) > 0 ) 
      literal ( s , literalmode , false ) ;
      flushstr ( s ) ;
      return ;
    } 
    break ;
  case 2 : 
    literalmode = colorstackpop ( stackno ) ;
    break ;
  case 3 : 
    literalmode = colorstackcurrent ( stackno ) ;
    break ;
    default: 
    confusion ( 1128 ) ;
    break ;
  } 
  if ( ( poolptr - strstart [strptr ]) > 0 ) 
  {
    s = makestring () ;
    literal ( s , literalmode , false ) ;
    flushstr ( s ) ;
  } 
} 
void 
pdfoutcolorstackstartpage ( void ) 
{
  pdfoutcolorstackstartpage_regmem 
  integer i  ;
  integer max  ;
  integer startstatus  ;
  integer literalmode  ;
  strnumber s  ;
  i = 0 ;
  max = colorstackused () ;
  while ( i < max ) {
      
    startstatus = colorstackskippagestart ( i ) ;
    if ( startstatus == 0 ) 
    {
      literalmode = colorstackcurrent ( i ) ;
      if ( ( poolptr - strstart [strptr ]) > 0 ) 
      {
	s = makestring () ;
	literal ( s , literalmode , false ) ;
	flushstr ( s ) ;
      } 
    } 
    incr ( i ) ;
  } 
} 
void 
zpdfoutsetmatrix ( halfword p ) 
{
  pdfoutsetmatrix_regmem 
  unsigned char oldsetting  ;
  strnumber s  ;
  oldsetting = selector ;
  selector = 21 ;
  showtokenlist ( mem [mem [p + 1 ].hh .v.RH ].hh .v.RH , -268435455L , 
  poolsize - poolptr ) ;
  selector = oldsetting ;
  {
    if ( poolptr + 7 > poolsize ) 
    overflow ( 259 , poolsize - initpoolptr ) ;
  } 
  strpool [poolptr ]= 0 ;
  if ( pdfsetmatrix ( strstart [strptr ], curh , curpageheight - curv ) == 1 
  ) 
  {
    {
      if ( poolptr + 7 > poolsize ) 
      overflow ( 259 , poolsize - initpoolptr ) ;
    } 
    {
      strpool [poolptr ]= 32 ;
      incr ( poolptr ) ;
    } 
    {
      strpool [poolptr ]= 48 ;
      incr ( poolptr ) ;
    } 
    {
      strpool [poolptr ]= 32 ;
      incr ( poolptr ) ;
    } 
    {
      strpool [poolptr ]= 48 ;
      incr ( poolptr ) ;
    } 
    {
      strpool [poolptr ]= 32 ;
      incr ( poolptr ) ;
    } 
    {
      strpool [poolptr ]= 99 ;
      incr ( poolptr ) ;
    } 
    {
      strpool [poolptr ]= 109 ;
      incr ( poolptr ) ;
    } 
    s = makestring () ;
    literal ( s , 0 , false ) ;
  } 
  else {
      
    pdferror ( 1129 , 1130 ) ;
  } 
  flushstr ( s ) ;
} 
void 
zpdfoutsave ( halfword p ) 
{
  pdfoutsave_regmem 
  checkpdfsave ( curh , curv ) ;
  literal ( 113 , 0 , false ) ;
} 
void 
zpdfoutrestore ( halfword p ) 
{
  pdfoutrestore_regmem 
  checkpdfrestore ( curh , curv ) ;
  literal ( 81 , 0 , false ) ;
} 
void 
zpdfspecial ( halfword p ) 
{
  pdfspecial_regmem 
  unsigned char oldsetting  ;
  strnumber s  ;
  oldsetting = selector ;
  selector = 21 ;
  showtokenlist ( mem [mem [p + 1 ].hh .v.RH ].hh .v.RH , -268435455L , 
  poolsize - poolptr ) ;
  selector = oldsetting ;
  s = makestring () ;
  literal ( s , 3 , true ) ;
  flushstr ( s ) ;
} 
void 
zpdfprinttoks ( halfword p ) 
{
  pdfprinttoks_regmem 
  strnumber s  ;
  s = tokenstostring ( p ) ;
  if ( ( strstart [s + 1 ]- strstart [s ]) > 0 ) 
  pdfprint ( s ) ;
  flushstr ( s ) ;
} 
void 
zpdfprinttoksln ( halfword p ) 
{
  pdfprinttoksln_regmem 
  strnumber s  ;
  s = tokenstostring ( p ) ;
  if ( ( strstart [s + 1 ]- strstart [s ]) > 0 ) 
  {
    {
      pdfprint ( s ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
  } 
  flushstr ( s ) ;
} 
void 
zpdfwriteobj ( integer n ) 
{
  pdfwriteobj_regmem 
  strnumber s  ;
  bytefile f  ;
  s = tokenstostring ( pdfmem [objtab [n ].int4 + 0 ]) ;
  {
    deletetokenref ( pdfmem [objtab [n ].int4 + 0 ]) ;
    pdfmem [objtab [n ].int4 + 0 ]= -268435455L ;
  } 
  if ( pdfmem [objtab [n ].int4 + 1 ]> 0 ) 
  {
    pdfbegindict ( n , 0 ) ;
    if ( pdfmem [objtab [n ].int4 + 2 ]!= -268435455L ) 
    {
      pdfprinttoksln ( pdfmem [objtab [n ].int4 + 2 ]) ;
      {
	deletetokenref ( pdfmem [objtab [n ].int4 + 2 ]) ;
	pdfmem [objtab [n ].int4 + 2 ]= -268435455L ;
      } 
    } 
    pdfbeginstream () ;
  } 
  else pdfbeginobj ( n , 1 ) ;
  if ( pdfmem [objtab [n ].int4 + 3 ]> 0 ) 
  {
    curname = s ;
    curarea = 345 ;
    curext = 345 ;
    packfilename ( curname , curarea , curext ) ;
    if ( ! texbopenin ( f ) ) 
    pdferror ( 1161 , 1162 ) ;
    print ( 1068 ) ;
    print ( s ) ;
    if ( ! eof ( f ) ) 
    {
      while ( ! eof ( f ) ) {
	  
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= getc ( f ) ;
	  incr ( pdfptr ) ;
	} 
      } 
      if ( ( ! pdfmem [objtab [n ].int4 + 1 ]) && ( pdfptr > 0 ) && ( 
      pdfbuf [pdfptr - 1 ]!= 10 ) ) 
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
    print ( 1013 ) ;
    bclose ( f ) ;
  } 
  else if ( pdfmem [objtab [n ].int4 + 1 ]> 0 ) 
  pdfprint ( s ) ;
  else {
      
    pdfprint ( s ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
  if ( pdfmem [objtab [n ].int4 + 1 ]> 0 ) 
  pdfendstream () ;
  else pdfendobj () ;
  flushstr ( s ) ;
} 
void 
zflushwhatsitnode ( halfword p , smallnumber s ) 
{
  flushwhatsitnode_regmem 
  mem [p ].hh.b0 = 8 ;
  mem [p ].hh.b1 = s ;
  if ( mem [p ].hh .v.RH != -268435455L ) 
  pdferror ( 1163 , 1164 ) ;
  flushnodelist ( p ) ;
} 
void 
zpdfwriteimage ( integer n ) 
{
  pdfwriteimage_regmem 
  pdfbegindict ( n , 0 ) ;
  if ( pdfmem [objtab [n ].int4 + 3 ]!= -268435455L ) 
  {
    pdfprinttoksln ( pdfmem [objtab [n ].int4 + 3 ]) ;
    {
      deletetokenref ( pdfmem [objtab [n ].int4 + 3 ]) ;
      pdfmem [objtab [n ].int4 + 3 ]= -268435455L ;
    } 
  } 
  if ( fixedpdfdraftmode == 0 ) 
  writeimage ( pdfmem [objtab [n ].int4 + 4 ]) ;
  deleteimage ( pdfmem [objtab [n ].int4 + 4 ]) ;
} 
void 
zpdfprintrectspec ( halfword r ) 
{
  pdfprintrectspec_regmem 
  pdfprintmagbp ( ( ( mem [r + 1 ].cint ) - pdforiginh ) ) ;
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 32 ;
      incr ( pdfptr ) ;
    } 
  } 
  pdfprintmagbp ( ( pdforiginv - ( mem [r + 4 ].cint ) ) ) ;
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 32 ;
      incr ( pdfptr ) ;
    } 
  } 
  pdfprintmagbp ( ( ( mem [r + 3 ].cint ) - pdforiginh ) ) ;
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 32 ;
      incr ( pdfptr ) ;
    } 
  } 
  pdfprintmagbp ( ( pdforiginv - ( mem [r + 2 ].cint ) ) ) ;
} 
void 
zwarndestdup ( integer id , smallnumber byname , strnumber s1 , strnumber s2 ) 
{
  warndestdup_regmem 
  if ( eqtb [29359 ].cint > 0 ) 
  return ;
  pdfwarning ( s1 , 1825 , false , false ) ;
  if ( byname > 0 ) 
  {
    print ( 1811 ) ;
    printmark ( id ) ;
  } 
  else {
      
    print ( 1190 ) ;
    printint ( id ) ;
  } 
  print ( 1826 ) ;
  print ( s2 ) ;
  println () ;
  showcontext () ;
} 
void 
zwriteaction ( halfword p ) 
{
  writeaction_regmem 
  strnumber s  ;
  integer d  ;
  if ( mem [p ].hh.b0 == 3 ) 
  {
    pdfprinttoksln ( mem [p + 2 ].hh .v.LH ) ;
    return ;
  } 
  pdfprint ( 1233 ) ;
  if ( mem [p + 1 ].hh .v.LH != -268435455L ) 
  {
    pdfprint ( 1907 ) ;
    s = tokenstostring ( mem [p + 1 ].hh .v.LH ) ;
    if ( ( strpool [strstart [s ]]== 40 ) && ( strpool [strstart [s ]+ 
    ( strstart [s + 1 ]- strstart [s ]) - 1 ]== 41 ) ) 
    pdfprint ( s ) ;
    else {
	
      pdfprintstr ( s ) ;
    } 
    flushstr ( s ) ;
    pdfprint ( 32 ) ;
    if ( mem [p + 1 ].hh .v.RH > 0 ) 
    {
      pdfprint ( 1908 ) ;
      if ( mem [p + 1 ].hh .v.RH == 1 ) 
      pdfprint ( 1909 ) ;
      else pdfprint ( 1910 ) ;
    } 
  } 
  switch ( mem [p ].hh.b0 ) 
  {case 0 : 
    {
      if ( mem [p + 1 ].hh .v.LH == -268435455L ) 
      {
	pdfprint ( 1911 ) ;
	pdfprintint ( getobj ( 1 , mem [p ].hh .v.RH , false ) ) ;
	pdfprint ( 1072 ) ;
      } 
      else {
	  
	pdfprint ( 1912 ) ;
	pdfprintint ( mem [p ].hh .v.RH - 1 ) ;
      } 
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 32 ;
	  incr ( pdfptr ) ;
	} 
      } 
      pdfprint ( tokenstostring ( mem [p + 2 ].hh .v.LH ) ) ;
      flushstr ( lasttokensstring ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 93 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
    break ;
  case 1 : 
    {
      if ( mem [p + 1 ].hh .v.LH == -268435455L ) 
      {
	pdfprint ( 1913 ) ;
	d = getobj ( 5 , mem [p ].hh .v.RH , mem [p ].hh.b1 ) ;
      } 
      else pdfprint ( 1914 ) ;
      if ( mem [p ].hh.b1 > 0 ) 
      {
	pdfstrentry ( 68 , tokenstostring ( mem [p ].hh .v.RH ) ) ;
	flushstr ( lasttokensstring ) ;
      } 
      else if ( mem [p + 1 ].hh .v.LH == -268435455L ) 
      pdfindirect ( 68 , d ) ;
      else pdferror ( 1838 , 1812 ) ;
    } 
    break ;
  case 2 : 
    {
      pdfprint ( 1915 ) ;
      if ( mem [p + 1 ].hh .v.LH == -268435455L ) 
      d = getobj ( 9 , mem [p ].hh .v.RH , mem [p ].hh.b1 ) ;
      if ( mem [p ].hh.b1 > 0 ) 
      {
	pdfstrentry ( 68 , tokenstostring ( mem [p ].hh .v.RH ) ) ;
	flushstr ( lasttokensstring ) ;
      } 
      else if ( mem [p + 1 ].hh .v.LH == -268435455L ) 
      pdfindirect ( 68 , d ) ;
      else pdfintentry ( 68 , mem [p ].hh .v.RH ) ;
    } 
    break ;
  } 
  {
    pdfprint ( 1234 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
} 
void 
zsetrectdimens ( halfword p , halfword parentbox , scaled x , scaled y , 
scaled w , scaled h , scaled d , scaled margin ) 
{
  setrectdimens_regmem 
  mem [p + 1 ].cint = curh ;
  if ( ( w == -1073741824L ) ) 
  mem [p + 3 ].cint = x + mem [parentbox + 1 ].cint ;
  else mem [p + 3 ].cint = curh + w ;
  if ( ( h == -1073741824L ) ) 
  mem [p + 2 ].cint = y - mem [parentbox + 3 ].cint ;
  else mem [p + 2 ].cint = curv - h ;
  if ( ( d == -1073741824L ) ) 
  mem [p + 4 ].cint = y + mem [parentbox + 2 ].cint ;
  else mem [p + 4 ].cint = curv + d ;
  if ( isshippingpage && matrixused () ) 
  {
    matrixtransformrect ( mem [p + 1 ].cint , curpageheight - mem [p + 4 ]
    .cint , mem [p + 3 ].cint , curpageheight - mem [p + 2 ].cint ) ;
    mem [p + 1 ].cint = getllx () ;
    mem [p + 4 ].cint = curpageheight - getlly () ;
    mem [p + 3 ].cint = geturx () ;
    mem [p + 2 ].cint = curpageheight - getury () ;
  } 
  mem [p + 1 ].cint = mem [p + 1 ].cint - margin ;
  mem [p + 2 ].cint = mem [p + 2 ].cint - margin ;
  mem [p + 3 ].cint = mem [p + 3 ].cint + margin ;
  mem [p + 4 ].cint = mem [p + 4 ].cint + margin ;
} 
void 
zdoannot ( halfword p , halfword parentbox , scaled x , scaled y ) 
{
  doannot_regmem 
  if ( ! isshippingpage ) 
  pdferror ( 1838 , 1916 ) ;
  if ( doingleaders ) 
  return ;
  if ( ( objtab [mem [p + 6 ].cint ].int2 > -2 ) ) 
  mem [p + 6 ].cint = pdfnewobjnum () ;
  setrectdimens ( p , parentbox , x , y , mem [p + 1 ].cint , mem [p + 2 ]
  .cint , mem [p + 3 ].cint , 0 ) ;
  objtab [mem [p + 6 ].cint ].int4 = p ;
  {
    pdfappendlistarg = mem [p + 6 ].cint ;
    pdfannotlist = appendptr ( pdfannotlist , pdfappendlistarg ) ;
  } 
  if ( objtab [mem [p + 6 ].cint ].int2 == -2 ) 
  objtab [mem [p + 6 ].cint ].int2 = -1 ;
} 
void 
zpushlinklevel ( halfword p ) 
{
  pushlinklevel_regmem 
  if ( pdflinkstackptr >= pdfmaxlinklevel ) 
  overflow ( 1917 , pdfmaxlinklevel ) ;
  pdfassert ( ( mem [p ].hh.b0 == 8 ) && ( mem [p ].hh.b1 == 14 ) ) ;
  incr ( pdflinkstackptr ) ;
  pdflinkstack [pdflinkstackptr ].nestinglevel = curs ;
  pdflinkstack [pdflinkstackptr ].linknode = copynodelist ( p ) ;
  pdflinkstack [pdflinkstackptr ].reflinknode = p ;
} 
void 
poplinklevel ( void ) 
{
  poplinklevel_regmem 
  pdfassert ( pdflinkstackptr > 0 ) ;
  flushnodelist ( pdflinkstack [pdflinkstackptr ].linknode ) ;
  decr ( pdflinkstackptr ) ;
} 
void 
zdolink ( halfword p , halfword parentbox , scaled x , scaled y ) 
{
  dolink_regmem 
  if ( ! isshippingpage ) 
  pdferror ( 1838 , 1918 ) ;
  pdfassert ( mem [parentbox ].hh.b0 == 0 ) ;
  if ( ( objtab [mem [p + 6 ].cint ].int2 > -2 ) ) 
  mem [p + 6 ].cint = pdfnewobjnum () ;
  pushlinklevel ( p ) ;
  setrectdimens ( p , parentbox , x , y , mem [p + 1 ].cint , mem [p + 2 ]
  .cint , mem [p + 3 ].cint , eqtb [29912 ].cint ) ;
  objtab [mem [p + 6 ].cint ].int4 = p ;
  {
    pdfappendlistarg = mem [p + 6 ].cint ;
    pdflinklist = appendptr ( pdflinklist , pdfappendlistarg ) ;
  } 
  if ( objtab [mem [p + 6 ].cint ].int2 == -2 ) 
  objtab [mem [p + 6 ].cint ].int2 = -1 ;
} 
void 
endlink ( void ) 
{
  endlink_regmem 
  halfword p  ;
  if ( pdflinkstackptr < 1 ) 
  pdferror ( 1838 , 1919 ) ;
  if ( pdflinkstack [pdflinkstackptr ].nestinglevel != curs ) 
  pdferror ( 1838 , 1920 ) ;
  if ( ( mem [pdflinkstack [pdflinkstackptr ].linknode + 1 ].cint == 
  -1073741824L ) ) 
  {
    p = pdflinkstack [pdflinkstackptr ].reflinknode ;
    if ( isshippingpage && matrixused () ) 
    {
      matrixrecalculate ( curh + eqtb [29912 ].cint ) ;
      mem [p + 1 ].cint = getllx () - eqtb [29912 ].cint ;
      mem [p + 2 ].cint = curpageheight - getury () - eqtb [29912 ].cint ;
      mem [p + 3 ].cint = geturx () + eqtb [29912 ].cint ;
      mem [p + 4 ].cint = curpageheight - getlly () + eqtb [29912 ].cint ;
    } 
    else mem [p + 3 ].cint = curh + eqtb [29912 ].cint ;
  } 
  poplinklevel () ;
} 
void 
zappendlink ( halfword parentbox , scaled x , scaled y , smallnumber i ) 
{
  appendlink_regmem 
  halfword p  ;
  pdfassert ( mem [parentbox ].hh.b0 == 0 ) ;
  p = copynodelist ( pdflinkstack [i ].linknode ) ;
  pdflinkstack [i ].reflinknode = p ;
  mem [p ].hh .v.LH = 268435455L ;
  mem [p ].hh .v.RH = -268435455L ;
  setrectdimens ( p , parentbox , x , y , mem [p + 1 ].cint , mem [p + 2 ]
  .cint , mem [p + 3 ].cint , eqtb [29912 ].cint ) ;
  pdfcreateobj ( 0 , 0 ) ;
  objtab [objptr ].int4 = p ;
  {
    pdfappendlistarg = objptr ;
    pdflinklist = appendptr ( pdflinklist , pdfappendlistarg ) ;
  } 
} 
void 
zappendbead ( halfword p ) 
{
  appendbead_regmem 
  integer a, b, c, t  ;
  if ( ! isshippingpage ) 
  pdferror ( 1838 , 1921 ) ;
  t = getobj ( 9 , mem [p + 5 ].hh .v.RH , mem [p + 5 ].hh.b1 ) ;
  b = pdfnewobjnum () ;
  objtab [b ].int4 = pdfgetmem ( 5 ) ;
  pdfmem [objtab [b ].int4 + 1 ]= pdflastpage ;
  pdfmem [objtab [b ].int4 ]= p ;
  if ( mem [p + 6 ].hh .v.LH != -268435455L ) 
  pdfmem [objtab [b ].int4 + 4 ]= tokenstostring ( mem [p + 6 ].hh .v.LH 
  ) ;
  else pdfmem [objtab [b ].int4 + 4 ]= 0 ;
  if ( objtab [t ].int4 == 0 ) 
  {
    objtab [t ].int4 = b ;
    pdfmem [objtab [b ].int4 + 2 ]= b ;
    pdfmem [objtab [b ].int4 + 3 ]= b ;
  } 
  else {
      
    a = objtab [t ].int4 ;
    c = pdfmem [objtab [a ].int4 + 3 ];
    pdfmem [objtab [b ].int4 + 3 ]= c ;
    pdfmem [objtab [b ].int4 + 2 ]= a ;
    pdfmem [objtab [a ].int4 + 3 ]= b ;
    pdfmem [objtab [c ].int4 + 2 ]= b ;
  } 
  {
    pdfappendlistarg = b ;
    pdfbeadlist = appendptr ( pdfbeadlist , pdfappendlistarg ) ;
  } 
} 
void 
zdothread ( halfword p , halfword parentbox , scaled x , scaled y ) 
{
  dothread_regmem 
  if ( doingleaders ) 
  return ;
  if ( mem [p ].hh.b1 == 19 ) 
  {
    pdfthreadwd = mem [p + 1 ].cint ;
    pdfthreadht = mem [p + 2 ].cint ;
    pdfthreaddp = mem [p + 3 ].cint ;
    pdflastthreadid = mem [p + 5 ].hh .v.RH ;
    pdflastthreadnamedid = ( mem [p + 5 ].hh.b1 > 0 ) ;
    if ( pdflastthreadnamedid ) 
    incr ( mem [mem [p + 5 ].hh .v.RH ].hh .v.LH ) ;
    pdfthreadlevel = curs ;
  } 
  setrectdimens ( p , parentbox , x , y , mem [p + 1 ].cint , mem [p + 2 ]
  .cint , mem [p + 3 ].cint , eqtb [29914 ].cint ) ;
  appendbead ( p ) ;
  lastthread = p ;
} 
void 
zappendthread ( halfword parentbox , scaled x , scaled y ) 
{
  appendthread_regmem 
  halfword p  ;
  p = getnode ( 7 ) ;
  mem [p ].hh .v.LH = 268435455L ;
  mem [p ].hh .v.RH = -268435455L ;
  mem [p + 1 ].cint = pdfthreadwd ;
  mem [p + 2 ].cint = pdfthreadht ;
  mem [p + 3 ].cint = pdfthreaddp ;
  mem [p + 6 ].hh .v.LH = -268435455L ;
  mem [p + 5 ].hh .v.RH = pdflastthreadid ;
  if ( pdflastthreadnamedid ) 
  {
    incr ( mem [mem [p + 5 ].hh .v.RH ].hh .v.LH ) ;
    mem [p + 5 ].hh.b1 = 1 ;
  } 
  else mem [p + 5 ].hh.b1 = 0 ;
  setrectdimens ( p , parentbox , x , y , mem [p + 1 ].cint , mem [p + 2 ]
  .cint , mem [p + 3 ].cint , eqtb [29914 ].cint ) ;
  appendbead ( p ) ;
  lastthread = p ;
} 
void 
endthread ( void ) 
{
  endthread_regmem 
  if ( pdfthreadlevel != curs ) 
  pdferror ( 1838 , 1922 ) ;
  if ( ( pdfthreaddp == -1073741824L ) && ( lastthread != -268435455L ) ) 
  mem [lastthread + 4 ].cint = curv + eqtb [29914 ].cint ;
  if ( pdflastthreadnamedid ) 
  deletetokenref ( pdflastthreadid ) ;
  lastthread = -268435455L ;
} 
integer 
zopensubentries ( halfword p ) 
{
  register integer Result; opensubentries_regmem 
  integer k, c  ;
  integer l, r  ;
  k = 0 ;
  if ( pdfmem [objtab [p ].int4 + 4 ]!= 0 ) 
  {
    l = pdfmem [objtab [p ].int4 + 4 ];
    do {
	incr ( k ) ;
      c = opensubentries ( l ) ;
      if ( objtab [l ].int0 > 0 ) 
      k = k + c ;
      pdfmem [objtab [l ].int4 + 1 ]= p ;
      r = pdfmem [objtab [l ].int4 + 3 ];
      if ( r == 0 ) 
      pdfmem [objtab [p ].int4 + 5 ]= l ;
      l = r ;
    } while ( ! ( l == 0 ) ) ;
  } 
  if ( objtab [p ].int0 > 0 ) 
  objtab [p ].int0 = k ;
  else objtab [p ].int0 = - (integer) k ;
  Result = k ;
  return Result ;
} 
void 
zdodest ( halfword p , halfword parentbox , scaled x , scaled y ) 
{
  dodest_regmem 
  integer k  ;
  if ( ! isshippingpage ) 
  pdferror ( 1838 , 1923 ) ;
  if ( doingleaders ) 
  return ;
  k = getobj ( 5 , mem [p + 5 ].hh .v.RH , mem [p + 5 ].hh.b1 ) ;
  if ( objtab [k ].int4 != -268435455L ) 
  {
    warndestdup ( mem [p + 5 ].hh .v.RH , mem [p + 5 ].hh.b1 , 1838 , 1839 
    ) ;
    return ;
  } 
  objtab [k ].int4 = p ;
  {
    pdfappendlistarg = k ;
    pdfdestlist = appendptr ( pdfdestlist , pdfappendlistarg ) ;
  } 
  switch ( mem [p + 5 ].hh.b0 ) 
  {case 0 : 
    if ( matrixused () ) 
    setrectdimens ( p , parentbox , x , y , mem [p + 1 ].cint , mem [p + 2 
    ].cint , mem [p + 3 ].cint , eqtb [29913 ].cint ) ;
    else {
	
      mem [p + 1 ].cint = curh ;
      mem [p + 2 ].cint = curv ;
    } 
    break ;
  case 2 : 
  case 5 : 
    if ( matrixused () ) 
    setrectdimens ( p , parentbox , x , y , mem [p + 1 ].cint , mem [p + 2 
    ].cint , mem [p + 3 ].cint , eqtb [29913 ].cint ) ;
    else mem [p + 2 ].cint = curv ;
    break ;
  case 3 : 
  case 6 : 
    if ( matrixused () ) 
    setrectdimens ( p , parentbox , x , y , mem [p + 1 ].cint , mem [p + 2 
    ].cint , mem [p + 3 ].cint , eqtb [29913 ].cint ) ;
    else mem [p + 1 ].cint = curh ;
    break ;
  case 1 : 
  case 4 : 
    ;
    break ;
  case 7 : 
    setrectdimens ( p , parentbox , x , y , mem [p + 1 ].cint , mem [p + 2 
    ].cint , mem [p + 3 ].cint , eqtb [29913 ].cint ) ;
    break ;
  } 
} 
void 
zoutform ( halfword p ) 
{
  outform_regmem 
  pdfendtext () ;
  {
    pdfprint ( 113 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
  if ( pdflookuplist ( pdfxformlist , mem [p + 4 ].hh .v.LH ) == -268435455L 
  ) 
  {
    pdfappendlistarg = mem [p + 4 ].hh .v.LH ;
    pdfxformlist = appendptr ( pdfxformlist , pdfappendlistarg ) ;
  } 
  curv = curv + pdfmem [objtab [mem [p + 4 ].hh .v.LH ].int4 + 2 ];
  pdfprint ( 1024 ) ;
  pdfprintbp ( ( ( curh ) - pdforiginh ) ) ;
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 32 ;
      incr ( pdfptr ) ;
    } 
  } 
  pdfprintbp ( ( pdforiginv - ( curv ) ) ) ;
  {
    pdfprint ( 1025 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
  pdfprint ( 1145 ) ;
  pdfprintint ( objtab [mem [p + 4 ].hh .v.LH ].int0 ) ;
  if ( pdfresnameprefix != 0 ) 
  pdfprint ( pdfresnameprefix ) ;
  {
    pdfprint ( 1924 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
  {
    pdfprint ( 81 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
} 
void 
zoutimage ( halfword p ) 
{
  outimage_regmem 
  integer image, groupref  ;
  integer imgw, imgh  ;
  image = pdfmem [objtab [mem [p + 4 ].hh .v.LH ].int4 + 4 ];
  if ( ( imagerotate ( image ) == 90 ) || ( imagerotate ( image ) == 270 ) ) 
  {
    imgh = imagewidth ( image ) ;
    imgw = imageheight ( image ) ;
  } 
  else {
      
    imgw = imagewidth ( image ) ;
    imgh = imageheight ( image ) ;
  } 
  pdfendtext () ;
  {
    pdfprint ( 113 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
  if ( pdflookuplist ( pdfximagelist , mem [p + 4 ].hh .v.LH ) == 
  -268435455L ) 
  {
    pdfappendlistarg = mem [p + 4 ].hh .v.LH ;
    pdfximagelist = appendptr ( pdfximagelist , pdfappendlistarg ) ;
  } 
  if ( ! ispdfimage ( image ) ) 
  {
    if ( ispngimage ( image ) ) 
    {
      groupref = getimagegroupref ( image ) ;
      if ( ( groupref > 0 ) && ( pdfpagegroupval == 0 ) ) 
      pdfpagegroupval = groupref ;
    } 
    pdfprintreal ( extxnoverd ( mem [p + 1 ].cint , tenpow [6 ], 
    onehundredbp ) , 4 ) ;
    pdfprint ( 1140 ) ;
    pdfprintreal ( extxnoverd ( mem [p + 2 ].cint + mem [p + 3 ].cint , 
    tenpow [6 ], onehundredbp ) , 4 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 32 ;
	incr ( pdfptr ) ;
      } 
    } 
    pdfprintbp ( ( ( curh ) - pdforiginh ) ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 32 ;
	incr ( pdfptr ) ;
      } 
    } 
    pdfprintbp ( ( pdforiginv - ( curv ) ) ) ;
  } 
  else {
      
    groupref = getimagegroupref ( image ) ;
    if ( ( groupref != 0 ) && ( pdfpagegroupval == 0 ) ) 
    {
      if ( groupref == -1 ) 
      {
	pdfpagegroupval = pdfnewobjnum () ;
	setimagegroupref ( image , pdfpagegroupval ) ;
      } 
      else pdfpagegroupval = groupref ;
    } 
    pdfprintreal ( extxnoverd ( mem [p + 1 ].cint , tenpow [6 ], imgw ) , 
    6 ) ;
    pdfprint ( 1140 ) ;
    pdfprintreal ( extxnoverd ( mem [p + 2 ].cint + mem [p + 3 ].cint , 
    tenpow [6 ], imgh ) , 6 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 32 ;
	incr ( pdfptr ) ;
      } 
    } 
    pdfprintbp ( ( ( curh ) - pdforiginh ) - extxnoverd ( mem [p + 1 ].cint 
    , epdforigx ( image ) , imgw ) ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 32 ;
	incr ( pdfptr ) ;
      } 
    } 
    pdfprintbp ( ( pdforiginv - ( curv ) ) - extxnoverd ( mem [p + 2 ].cint 
    + mem [p + 3 ].cint , epdforigy ( image ) , imgh ) ) ;
  } 
  {
    pdfprint ( 1025 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
  pdfprint ( 1146 ) ;
  pdfprintint ( objtab [mem [p + 4 ].hh .v.LH ].int0 ) ;
  if ( pdfresnameprefix != 0 ) 
  pdfprint ( pdfresnameprefix ) ;
  {
    pdfprint ( 1924 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
  {
    pdfprint ( 81 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
} 
scaled 
zgapamount ( halfword p , scaled curpos ) 
{
  register scaled Result; gapamount_regmem 
  scaled snapunit, stretchamount, shrinkamount  ;
  scaled lastpos, nextpos, g, g2  ;
  snapunit = mem [mem [p + 1 ].hh .v.LH + 1 ].cint ;
  if ( mem [mem [p + 1 ].hh .v.LH ].hh.b0 > 0 ) 
  stretchamount = 1073741823L ;
  else stretchamount = mem [mem [p + 1 ].hh .v.LH + 2 ].cint ;
  if ( mem [mem [p + 1 ].hh .v.LH ].hh.b1 > 0 ) 
  shrinkamount = 1073741823L ;
  else shrinkamount = mem [mem [p + 1 ].hh .v.LH + 3 ].cint ;
  if ( mem [p ].hh.b1 == 35 ) 
  lastpos = pdfsnapyrefpos + snapunit * ( ( curpos - pdfsnapyrefpos ) / 
  snapunit ) ;
  else pdferror ( 1925 , 1926 ) ;
  nextpos = lastpos + snapunit ;
  g = 1073741823L ;
  g2 = 1073741823L ;
  Result = 0 ;
  if ( curpos - lastpos < shrinkamount ) 
  g = curpos - lastpos ;
  if ( ( nextpos - curpos < stretchamount ) ) 
  g2 = nextpos - curpos ;
  if ( ( g == 1073741823L ) && ( g2 == 1073741823L ) ) 
  return Result ;
  if ( g2 <= g ) 
  Result = g2 ;
  else Result = - (integer) g ;
  return Result ;
} 
halfword 
zgetvpos ( halfword p , halfword q , halfword b ) 
{
  register halfword Result; getvpos_regmem 
  scaled tmpv  ;
  glueord gorder  ;
  unsigned char gsign  ;
  real gluetemp  ;
  real curglue  ;
  scaled curg  ;
  halfword thisbox  ;
  tmpv = curv ;
  thisbox = b ;
  curg = 0 ;
  curglue = 0.0 ;
  gorder = mem [thisbox + 5 ].hh.b1 ;
  gsign = mem [thisbox + 5 ].hh.b0 ;
  while ( ( p != q ) && ( p != -268435455L ) ) {
      
    if ( ( p >= himemmin ) ) 
    confusion ( 1935 ) ;
    else {
	
      switch ( mem [p ].hh.b0 ) 
      {case 0 : 
      case 1 : 
      case 2 : 
	tmpv = tmpv + mem [p + 3 ].cint + mem [p + 2 ].cint ;
	break ;
      case 8 : 
	if ( ( mem [p ].hh.b1 == 10 ) || ( mem [p ].hh.b1 == 12 ) ) 
	tmpv = tmpv + mem [p + 2 ].cint + mem [p + 3 ].cint ;
	break ;
      case 10 : 
	{
	  {
	    g = mem [p + 1 ].hh .v.LH ;
	    ruleht = mem [g + 1 ].cint - curg ;
	    if ( gsign != 0 ) 
	    {
	      if ( gsign == 1 ) 
	      {
		if ( mem [g ].hh.b0 == gorder ) 
		{
		  curglue = curglue + mem [g + 2 ].cint ;
		  gluetemp = mem [thisbox + 6 ].gr * curglue ;
		  if ( gluetemp > 1000000000.0 ) 
		  gluetemp = 1000000000.0 ;
		  else if ( gluetemp < -1000000000.0 ) 
		  gluetemp = -1000000000.0 ;
		  curg = round ( gluetemp ) ;
		} 
	      } 
	      else if ( mem [g ].hh.b1 == gorder ) 
	      {
		curglue = curglue - mem [g + 3 ].cint ;
		gluetemp = mem [thisbox + 6 ].gr * curglue ;
		if ( gluetemp > 1000000000.0 ) 
		gluetemp = 1000000000.0 ;
		else if ( gluetemp < -1000000000.0 ) 
		gluetemp = -1000000000.0 ;
		curg = round ( gluetemp ) ;
	      } 
	    } 
	    ruleht = ruleht + curg ;
	  } 
	  tmpv = tmpv + ruleht ;
	} 
	break ;
      case 11 : 
	tmpv = tmpv + mem [p + 1 ].cint ;
	break ;
	default: 
	;
	break ;
      } 
    } 
    p = mem [p ].hh .v.RH ;
  } 
  Result = tmpv ;
  return Result ;
} 
void 
zdosnapycomp ( halfword p , halfword b ) 
{
  dosnapycomp_regmem 
  halfword q  ;
  scaled tmpv, g, g2  ;
  if ( ! ( ! ( p >= himemmin ) && ( mem [p ].hh.b0 == 8 ) && ( mem [p ]
  .hh.b1 == 36 ) ) ) 
  pdferror ( 1925 , 1936 ) ;
  q = p ;
  while ( ( q != -268435455L ) ) {
      
    if ( ! ( q >= himemmin ) && ( mem [q ].hh.b0 == 8 ) && ( mem [q ]
    .hh.b1 == 35 ) ) 
    {
      tmpv = getvpos ( p , q , b ) ;
      g = gapamount ( q , tmpv ) ;
      g2 = roundxnoverd ( g , mem [p + 1 ].cint , 1000 ) ;
      curv = curv + g2 ;
      mem [q + 2 ].cint = g - g2 ;
      if ( mem [q + 2 ].cint == 0 ) 
      mem [q + 2 ].cint = 1 ;
      return ;
    } 
    q = mem [q ].hh .v.RH ;
  } 
} 
void 
zdosnapy ( halfword p ) 
{
  dosnapy_regmem 
  incr ( countdosnapy ) ;
  if ( mem [p + 2 ].cint != 0 ) 
  curv = curv + mem [p + 2 ].cint ;
  else curv = curv + gapamount ( p , curv ) ;
} 
void 
pdfhlistout ( void ) 
{
  /* 21 13 14 15 40 22 */ pdfhlistout_regmem 
  scaled baseline  ;
  scaled leftedge  ;
  scaled saveh  ;
  halfword thisbox  ;
  glueord gorder  ;
  unsigned char gsign  ;
  halfword p  ;
  halfword leaderbox  ;
  scaled leaderwd  ;
  scaled lx  ;
  boolean outerdoingleaders  ;
  scaled edge  ;
  halfword prevp  ;
  real gluetemp  ;
  real curglue  ;
  scaled curg  ;
  smallnumber i  ;
  curg = 0 ;
  curglue = 0.0 ;
  thisbox = tempptr ;
  gorder = mem [thisbox + 5 ].hh.b1 ;
  gsign = mem [thisbox + 5 ].hh.b0 ;
  p = mem [thisbox + 5 ].hh .v.RH ;
  incr ( curs ) ;
  baseline = curv ;
  prevp = thisbox + 5 ;
  if ( ( eTeXmode == 1 ) ) 
  {
    {
      tempptr = getavail () ;
      mem [tempptr ].hh .v.LH = 0 ;
      mem [tempptr ].hh .v.RH = LRptr ;
      LRptr = tempptr ;
    } 
    if ( ( mem [thisbox ].hh.b1 ) == 2 ) {
	
      if ( curdir == 1 ) 
      {
	curdir = 0 ;
	curh = curh - mem [thisbox + 1 ].cint ;
      } 
      else mem [thisbox ].hh.b1 = 0 ;
    } 
    if ( ( curdir == 1 ) && ( ( mem [thisbox ].hh.b1 ) != 1 ) ) 
    {
      saveh = curh ;
      tempptr = p ;
      p = newkern ( 0 ) ;
      mem [prevp ].hh .v.RH = p ;
      curh = 0 ;
      mem [p ].hh .v.RH = reverse ( thisbox , -268435455L , curg , curglue ) 
      ;
      mem [p + 1 ].cint = - (integer) curh ;
      curh = saveh ;
      mem [thisbox ].hh.b1 = 1 ;
    } 
  } 
  leftedge = curh ;
  {register integer for_end; i = 1 ;for_end = pdflinkstackptr ; if ( i <= 
  for_end) do 
    {
      pdfassert ( ( mem [pdflinkstack [i ].linknode + 1 ].cint == 
      -1073741824L ) ) ;
      if ( ( pdflinkstack [i ].nestinglevel == curs ) ) 
      appendlink ( thisbox , leftedge , baseline , i ) ;
    } 
  while ( i++ < for_end ) ;} 
  while ( p != -268435455L ) lab21: if ( ( p >= himemmin ) ) 
  {
    do {
	f = mem [p ].hh.b0 ;
      c = mem [p ].hh.b1 ;
      if ( ( ( fontbc [f ]<= c ) && ( c <= fontec [f ]) && ( fontinfo [
      charbase [f ]+ c ].qqqq .b0 > 0 ) ) ) 
      {
	{
	  if ( pdffonttype [f ]== 0 ) 
	  dovf ( f ) ;
	  if ( pdffonttype [f ]== 1 ) 
	  dovfpacket ( f , c ) ;
	  else {
	      
	    pdfbeginstring ( f ) ;
	    pdfprintchar ( f , c ) ;
	    advcharwidth ( f , c ) ;
	  } 
	} 
	curh = curh + fontinfo [widthbase [f ]+ fontinfo [charbase [f ]+ 
	effectivechar ( true , f , c ) ].qqqq .b0 ].cint ;
	goto lab22 ;
      } 
      if ( mltexenabledp ) 
      {
	if ( c >= eqtb [29329 ].cint ) {
	    
	  if ( c <= eqtb [29330 ].cint ) {
	      
	    if ( ( eqtb [29018 + c ].hh .v.RH > 0 ) ) 
	    {
	      basec = ( eqtb [29018 + c ].hh .v.RH % 256 ) ;
	      accentc = ( eqtb [29018 + c ].hh .v.RH / 256 ) ;
	      if ( ( fontec [f ]>= basec ) ) {
		  
		if ( ( fontbc [f ]<= basec ) ) {
		    
		  if ( ( fontec [f ]>= accentc ) ) {
		      
		    if ( ( fontbc [f ]<= accentc ) ) 
		    {
		      iac = fontinfo [charbase [f ]+ effectivechar ( true , 
		      f , accentc ) ].qqqq ;
		      ibc = fontinfo [charbase [f ]+ effectivechar ( true , 
		      f , basec ) ].qqqq ;
		      if ( ( ibc .b0 > 0 ) ) {
			  
			if ( ( iac .b0 > 0 ) ) 
			goto lab40 ;
		      } 
		    } 
		  } 
		} 
	      } 
	      begindiagnostic () ;
	      printnl ( 2057 ) ;
	      print ( c ) ;
	      print ( 1614 ) ;
	      print ( accentc ) ;
	      print ( 32 ) ;
	      print ( basec ) ;
	      print ( 979 ) ;
	      slowprint ( fontname [f ]) ;
	      printchar ( 33 ) ;
	      enddiagnostic ( false ) ;
	      goto lab22 ;
	    } 
	  } 
	} 
	begindiagnostic () ;
	printnl ( 978 ) ;
	print ( 2056 ) ;
	print ( c ) ;
	print ( 979 ) ;
	slowprint ( fontname [f ]) ;
	printchar ( 33 ) ;
	enddiagnostic ( false ) ;
	goto lab22 ;
	lab40: if ( eqtb [29309 ].cint > 99 ) 
	{
	  begindiagnostic () ;
	  printnl ( 2058 ) ;
	  print ( c ) ;
	  print ( 1614 ) ;
	  print ( accentc ) ;
	  print ( 32 ) ;
	  print ( basec ) ;
	  print ( 979 ) ;
	  slowprint ( fontname [f ]) ;
	  printchar ( 46 ) ;
	  enddiagnostic ( false ) ;
	} 
	basexheight = fontinfo [5 + parambase [f ]].cint ;
	baseslant = fontinfo [1 + parambase [f ]].cint / ((double) 65536.0 
	) ;
	accentslant = baseslant ;
	basewidth = fontinfo [widthbase [f ]+ ibc .b0 ].cint ;
	baseheight = fontinfo [heightbase [f ]+ ( ibc .b1 ) / 16 ].cint ;
	accentwidth = fontinfo [widthbase [f ]+ iac .b0 ].cint ;
	accentheight = fontinfo [heightbase [f ]+ ( iac .b1 ) / 16 ].cint 
	;
	delta = round ( ( basewidth - accentwidth ) / ((double) 2.0 ) + 
	baseheight * baseslant - basexheight * accentslant ) ;
	curh = curh + delta ;
	if ( ( ( baseheight != basexheight ) && ( accentheight > 0 ) ) ) 
	{
	  curv = baseline + ( basexheight - baseheight ) ;
	  {
	    if ( pdffonttype [f ]== 0 ) 
	    dovf ( f ) ;
	    if ( pdffonttype [f ]== 1 ) 
	    dovfpacket ( f , accentc ) ;
	    else {
		
	      pdfbeginstring ( f ) ;
	      pdfprintchar ( f , accentc ) ;
	      advcharwidth ( f , accentc ) ;
	    } 
	  } 
	  curv = baseline ;
	} 
	else {
	    
	  {
	    if ( pdffonttype [f ]== 0 ) 
	    dovf ( f ) ;
	    if ( pdffonttype [f ]== 1 ) 
	    dovfpacket ( f , accentc ) ;
	    else {
		
	      pdfbeginstring ( f ) ;
	      pdfprintchar ( f , accentc ) ;
	      advcharwidth ( f , accentc ) ;
	    } 
	  } 
	} 
	curh = curh + accentwidth ;
	curh = curh + ( - (integer) accentwidth - delta ) ;
	{
	  if ( pdffonttype [f ]== 0 ) 
	  dovf ( f ) ;
	  if ( pdffonttype [f ]== 1 ) 
	  dovfpacket ( f , basec ) ;
	  else {
	      
	    pdfbeginstring ( f ) ;
	    pdfprintchar ( f , basec ) ;
	    advcharwidth ( f , basec ) ;
	  } 
	} 
	curh = curh + basewidth ;
      } 
      lab22: prevp = mem [prevp ].hh .v.RH ;
      p = mem [p ].hh .v.RH ;
    } while ( ! ( ! ( p >= himemmin ) ) ) ;
  } 
  else {
      
    switch ( mem [p ].hh.b0 ) 
    {case 0 : 
    case 1 : 
      if ( mem [p + 5 ].hh .v.RH == -268435455L ) 
      curh = curh + mem [p + 1 ].cint ;
      else {
	  
	curv = baseline + mem [p + 4 ].cint ;
	tempptr = p ;
	edge = curh + mem [p + 1 ].cint ;
	if ( curdir == 1 ) 
	curh = edge ;
	if ( mem [p ].hh.b0 == 1 ) 
	pdfvlistout () ;
	else pdfhlistout () ;
	curh = edge ;
	curv = baseline ;
      } 
      break ;
    case 2 : 
      {
	ruleht = mem [p + 3 ].cint ;
	ruledp = mem [p + 2 ].cint ;
	rulewd = mem [p + 1 ].cint ;
	goto lab14 ;
      } 
      break ;
    case 8 : 
      switch ( mem [p ].hh.b1 ) 
      {case 6 : 
	pdfoutliteral ( p ) ;
	break ;
      case 38 : 
	pdfoutcolorstack ( p ) ;
	break ;
      case 39 : 
	pdfoutsetmatrix ( p ) ;
	break ;
      case 40 : 
	pdfoutsave ( p ) ;
	break ;
      case 41 : 
	pdfoutrestore ( p ) ;
	break ;
      case 8 : 
	{
	  pdfappendlistarg = mem [p + 1 ].hh .v.LH ;
	  pdfobjlist = appendptr ( pdfobjlist , pdfappendlistarg ) ;
	} 
	break ;
      case 10 : 
	{
	  curv = baseline ;
	  edge = curh ;
	  outform ( p ) ;
	  curh = edge + mem [p + 1 ].cint ;
	  curv = baseline ;
	} 
	break ;
      case 12 : 
	{
	  curv = baseline + mem [p + 3 ].cint ;
	  edge = curh ;
	  outimage ( p ) ;
	  curh = edge + mem [p + 1 ].cint ;
	  curv = baseline ;
	} 
	break ;
      case 13 : 
	doannot ( p , thisbox , leftedge , baseline ) ;
	break ;
      case 14 : 
	dolink ( p , thisbox , leftedge , baseline ) ;
	break ;
      case 15 : 
	endlink () ;
	break ;
      case 17 : 
	dodest ( p , thisbox , leftedge , baseline ) ;
	break ;
      case 18 : 
	dothread ( p , thisbox , leftedge , baseline ) ;
	break ;
      case 19 : 
	pdferror ( 1838 , 1947 ) ;
	break ;
      case 20 : 
	pdferror ( 1838 , 1948 ) ;
	break ;
      case 21 : 
	{
	  pdflastxpos = curh ;
	  if ( isshippingpage ) 
	  pdflastypos = curpageheight - curv ;
	  else pdflastypos = pdfxformheight + pdfxformdepth - curv ;
	} 
	break ;
      case 3 : 
	pdfspecial ( p ) ;
	break ;
      case 34 : 
	{
	  pdfsnapxrefpos = curh ;
	  pdfsnapyrefpos = curv ;
	} 
	break ;
      case 36 : 
      case 35 : 
	;
	break ;
      case 43 : 
	genfakedinterwordspace = true ;
	break ;
      case 44 : 
	genfakedinterwordspace = false ;
	break ;
      case 45 : 
	pdfinsertfakespace () ;
	break ;
	default: 
	outwhat ( p ) ;
	break ;
      } 
      break ;
    case 10 : 
      {
	g = mem [p + 1 ].hh .v.LH ;
	rulewd = mem [g + 1 ].cint - curg ;
	if ( gsign != 0 ) 
	{
	  if ( gsign == 1 ) 
	  {
	    if ( mem [g ].hh.b0 == gorder ) 
	    {
	      curglue = curglue + mem [g + 2 ].cint ;
	      gluetemp = mem [thisbox + 6 ].gr * curglue ;
	      if ( gluetemp > 1000000000.0 ) 
	      gluetemp = 1000000000.0 ;
	      else if ( gluetemp < -1000000000.0 ) 
	      gluetemp = -1000000000.0 ;
	      curg = round ( gluetemp ) ;
	    } 
	  } 
	  else if ( mem [g ].hh.b1 == gorder ) 
	  {
	    curglue = curglue - mem [g + 3 ].cint ;
	    gluetemp = mem [thisbox + 6 ].gr * curglue ;
	    if ( gluetemp > 1000000000.0 ) 
	    gluetemp = 1000000000.0 ;
	    else if ( gluetemp < -1000000000.0 ) 
	    gluetemp = -1000000000.0 ;
	    curg = round ( gluetemp ) ;
	  } 
	} 
	rulewd = rulewd + curg ;
	if ( ( eTeXmode == 1 ) ) {
	    
	  if ( ( ( ( gsign == 1 ) && ( mem [g ].hh.b0 == gorder ) ) || ( ( 
	  gsign == 2 ) && ( mem [g ].hh.b1 == gorder ) ) ) ) 
	  {
	    {
	      if ( mem [g ].hh .v.RH == -268435455L ) 
	      freenode ( g , 4 ) ;
	      else decr ( mem [g ].hh .v.RH ) ;
	    } 
	    if ( mem [p ].hh.b1 < 100 ) 
	    {
	      mem [p ].hh.b0 = 11 ;
	      mem [p + 1 ].cint = rulewd ;
	    } 
	    else {
		
	      g = getnode ( 4 ) ;
	      mem [g ].hh.b0 = 4 ;
	      mem [g ].hh.b1 = 4 ;
	      mem [g + 1 ].cint = rulewd ;
	      mem [g + 2 ].cint = 0 ;
	      mem [g + 3 ].cint = 0 ;
	      mem [p + 1 ].hh .v.LH = g ;
	    } 
	  } 
	} 
	if ( mem [p ].hh.b1 >= 100 ) 
	{
	  leaderbox = mem [p + 1 ].hh .v.RH ;
	  if ( mem [leaderbox ].hh.b0 == 2 ) 
	  {
	    ruleht = mem [leaderbox + 3 ].cint ;
	    ruledp = mem [leaderbox + 2 ].cint ;
	    goto lab14 ;
	  } 
	  leaderwd = mem [leaderbox + 1 ].cint ;
	  if ( ( leaderwd > 0 ) && ( rulewd > 0 ) ) 
	  {
	    rulewd = rulewd + 10 ;
	    if ( curdir == 1 ) 
	    curh = curh - 10 ;
	    edge = curh + rulewd ;
	    lx = 0 ;
	    if ( mem [p ].hh.b1 == 100 ) 
	    {
	      saveh = curh ;
	      curh = leftedge + leaderwd * ( ( curh - leftedge ) / leaderwd ) 
	      ;
	      if ( curh < saveh ) 
	      curh = curh + leaderwd ;
	    } 
	    else {
		
	      lq = rulewd / leaderwd ;
	      lr = rulewd % leaderwd ;
	      if ( mem [p ].hh.b1 == 101 ) 
	      curh = curh + ( lr / 2 ) ;
	      else {
		  
		lx = lr / ( lq + 1 ) ;
		curh = curh + ( ( lr - ( lq - 1 ) * lx ) / 2 ) ;
	      } 
	    } 
	    while ( curh + leaderwd <= edge ) {
		
	      curv = baseline + mem [leaderbox + 4 ].cint ;
	      saveh = curh ;
	      tempptr = leaderbox ;
	      if ( curdir == 1 ) 
	      curh = curh + leaderwd ;
	      outerdoingleaders = doingleaders ;
	      doingleaders = true ;
	      if ( mem [leaderbox ].hh.b0 == 1 ) 
	      pdfvlistout () ;
	      else pdfhlistout () ;
	      doingleaders = outerdoingleaders ;
	      curv = baseline ;
	      curh = saveh + leaderwd + lx ;
	    } 
	    if ( curdir == 1 ) 
	    curh = edge ;
	    else curh = edge - 10 ;
	    goto lab15 ;
	  } 
	} 
	goto lab13 ;
      } 
      break ;
    case 40 : 
    case 11 : 
      curh = curh + mem [p + 1 ].cint ;
      break ;
    case 9 : 
      {
	if ( ( eTeXmode == 1 ) ) 
	{
	  if ( odd ( mem [p ].hh.b1 ) ) {
	      
	    if ( mem [LRptr ].hh .v.LH == ( 4 * ( mem [p ].hh.b1 / 4 ) + 3 
	    ) ) 
	    {
	      tempptr = LRptr ;
	      LRptr = mem [tempptr ].hh .v.RH ;
	      {
		mem [tempptr ].hh .v.RH = avail ;
		avail = tempptr ;
	;
#ifdef STAT
		decr ( dynused ) ;
#endif /* STAT */
	      } 
	    } 
	    else {
		
	      if ( mem [p ].hh.b1 > 4 ) 
	      incr ( LRproblems ) ;
	    } 
	  } 
	  else {
	      
	    {
	      tempptr = getavail () ;
	      mem [tempptr ].hh .v.LH = ( 4 * ( mem [p ].hh.b1 / 4 ) + 3 ) 
	      ;
	      mem [tempptr ].hh .v.RH = LRptr ;
	      LRptr = tempptr ;
	    } 
	    if ( ( mem [p ].hh.b1 / 8 ) != curdir ) 
	    {
	      saveh = curh ;
	      tempptr = mem [p ].hh .v.RH ;
	      rulewd = mem [p + 1 ].cint ;
	      freenode ( p , 2 ) ;
	      curdir = 1 - curdir ;
	      p = newedge ( curdir , rulewd ) ;
	      mem [prevp ].hh .v.RH = p ;
	      curh = curh - leftedge + rulewd ;
	      mem [p ].hh .v.RH = reverse ( thisbox , newedge ( 1 - curdir , 
	      0 ) , curg , curglue ) ;
	      mem [p + 2 ].cint = curh ;
	      curdir = 1 - curdir ;
	      curh = saveh ;
	      goto lab21 ;
	    } 
	  } 
	  mem [p ].hh.b0 = 11 ;
	} 
	curh = curh + mem [p + 1 ].cint ;
      } 
      break ;
    case 6 : 
      {
	mem [memtop - 12 ]= mem [p + 1 ];
	mem [memtop - 12 ].hh .v.RH = mem [p ].hh .v.RH ;
	p = memtop - 12 ;
	goto lab21 ;
      } 
      break ;
    case 14 : 
      {
	curh = curh + mem [p + 1 ].cint ;
	leftedge = curh + mem [p + 2 ].cint ;
	curdir = mem [p ].hh.b1 ;
      } 
      break ;
      default: 
      ;
      break ;
    } 
    goto lab15 ;
    lab14: if ( ( ruleht == -1073741824L ) ) 
    ruleht = mem [thisbox + 3 ].cint ;
    if ( ( ruledp == -1073741824L ) ) 
    ruledp = mem [thisbox + 2 ].cint ;
    ruleht = ruleht + ruledp ;
    if ( ( ruleht > 0 ) && ( rulewd > 0 ) ) 
    {
      curv = baseline + ruledp ;
      pdfsetrule ( curh , curv , rulewd , ruleht ) ;
      curv = baseline ;
    } 
    lab13: curh = curh + rulewd ;
    lab15: prevp = p ;
    p = mem [p ].hh .v.RH ;
  } 
  if ( ( eTeXmode == 1 ) ) 
  {
    {
      while ( mem [LRptr ].hh .v.LH != 0 ) {
	  
	if ( mem [LRptr ].hh .v.LH > 4 ) 
	LRproblems = LRproblems + 10000 ;
	{
	  tempptr = LRptr ;
	  LRptr = mem [tempptr ].hh .v.RH ;
	  {
	    mem [tempptr ].hh .v.RH = avail ;
	    avail = tempptr ;
	;
#ifdef STAT
	    decr ( dynused ) ;
#endif /* STAT */
	  } 
	} 
      } 
      {
	tempptr = LRptr ;
	LRptr = mem [tempptr ].hh .v.RH ;
	{
	  mem [tempptr ].hh .v.RH = avail ;
	  avail = tempptr ;
	;
#ifdef STAT
	  decr ( dynused ) ;
#endif /* STAT */
	} 
      } 
    } 
    if ( ( mem [thisbox ].hh.b1 ) == 2 ) 
    curdir = 1 ;
  } 
  decr ( curs ) ;
} 
void 
pdfvlistout ( void ) 
{
  /* 13 14 15 */ pdfvlistout_regmem 
  scaled leftedge  ;
  scaled topedge  ;
  scaled savev  ;
  halfword thisbox  ;
  glueord gorder  ;
  unsigned char gsign  ;
  halfword p  ;
  halfword leaderbox  ;
  scaled leaderht  ;
  scaled lx  ;
  boolean outerdoingleaders  ;
  scaled edge  ;
  real gluetemp  ;
  real curglue  ;
  scaled curg  ;
  curg = 0 ;
  curglue = 0.0 ;
  thisbox = tempptr ;
  gorder = mem [thisbox + 5 ].hh.b1 ;
  gsign = mem [thisbox + 5 ].hh.b0 ;
  p = mem [thisbox + 5 ].hh .v.RH ;
  incr ( curs ) ;
  leftedge = curh ;
  curv = curv - mem [thisbox + 3 ].cint ;
  topedge = curv ;
  if ( ( lastthread != -268435455L ) && ( pdfthreaddp == -1073741824L ) && ( 
  pdfthreadlevel == curs ) ) 
  appendthread ( thisbox , leftedge , topedge + mem [thisbox + 3 ].cint ) ;
  while ( p != -268435455L ) {
      
    if ( ( p >= himemmin ) ) 
    confusion ( 1131 ) ;
    else {
	
      switch ( mem [p ].hh.b0 ) 
      {case 0 : 
      case 1 : 
	if ( mem [p + 5 ].hh .v.RH == -268435455L ) 
	curv = curv + mem [p + 3 ].cint + mem [p + 2 ].cint ;
	else {
	    
	  curv = curv + mem [p + 3 ].cint ;
	  savev = curv ;
	  if ( curdir == 1 ) 
	  curh = leftedge - mem [p + 4 ].cint ;
	  else curh = leftedge + mem [p + 4 ].cint ;
	  tempptr = p ;
	  if ( mem [p ].hh.b0 == 1 ) 
	  pdfvlistout () ;
	  else pdfhlistout () ;
	  curv = savev + mem [p + 2 ].cint ;
	  curh = leftedge ;
	} 
	break ;
      case 2 : 
	{
	  ruleht = mem [p + 3 ].cint ;
	  ruledp = mem [p + 2 ].cint ;
	  rulewd = mem [p + 1 ].cint ;
	  goto lab14 ;
	} 
	break ;
      case 8 : 
	switch ( mem [p ].hh.b1 ) 
	{case 6 : 
	  pdfoutliteral ( p ) ;
	  break ;
	case 38 : 
	  pdfoutcolorstack ( p ) ;
	  break ;
	case 39 : 
	  pdfoutsetmatrix ( p ) ;
	  break ;
	case 40 : 
	  pdfoutsave ( p ) ;
	  break ;
	case 41 : 
	  pdfoutrestore ( p ) ;
	  break ;
	case 8 : 
	  {
	    pdfappendlistarg = mem [p + 1 ].hh .v.LH ;
	    pdfobjlist = appendptr ( pdfobjlist , pdfappendlistarg ) ;
	  } 
	  break ;
	case 10 : 
	  {
	    curv = curv + mem [p + 2 ].cint ;
	    savev = curv ;
	    curh = leftedge ;
	    outform ( p ) ;
	    curv = savev + mem [p + 3 ].cint ;
	    curh = leftedge ;
	  } 
	  break ;
	case 12 : 
	  {
	    curv = curv + mem [p + 2 ].cint + mem [p + 3 ].cint ;
	    savev = curv ;
	    curh = leftedge ;
	    outimage ( p ) ;
	    curv = savev ;
	    curh = leftedge ;
	  } 
	  break ;
	case 13 : 
	  doannot ( p , thisbox , leftedge , topedge + mem [thisbox + 3 ]
	  .cint ) ;
	  break ;
	case 14 : 
	  pdferror ( 1838 , 1945 ) ;
	  break ;
	case 15 : 
	  pdferror ( 1838 , 1946 ) ;
	  break ;
	case 17 : 
	  dodest ( p , thisbox , leftedge , topedge + mem [thisbox + 3 ]
	  .cint ) ;
	  break ;
	case 18 : 
	case 19 : 
	  dothread ( p , thisbox , leftedge , topedge + mem [thisbox + 3 ]
	  .cint ) ;
	  break ;
	case 20 : 
	  endthread () ;
	  break ;
	case 21 : 
	  {
	    pdflastxpos = curh ;
	    if ( isshippingpage ) 
	    pdflastypos = curpageheight - curv ;
	    else pdflastypos = pdfxformheight + pdfxformdepth - curv ;
	  } 
	  break ;
	case 3 : 
	  pdfspecial ( p ) ;
	  break ;
	case 34 : 
	  {
	    pdfsnapxrefpos = curh ;
	    pdfsnapyrefpos = curv ;
	  } 
	  break ;
	case 36 : 
	  dosnapycomp ( p , thisbox ) ;
	  break ;
	case 35 : 
	  dosnapy ( p ) ;
	  break ;
	case 43 : 
	  genfakedinterwordspace = true ;
	  break ;
	case 44 : 
	  genfakedinterwordspace = false ;
	  break ;
	case 45 : 
	  pdfinsertfakespace () ;
	  break ;
	  default: 
	  outwhat ( p ) ;
	  break ;
	} 
	break ;
      case 10 : 
	{
	  g = mem [p + 1 ].hh .v.LH ;
	  ruleht = mem [g + 1 ].cint - curg ;
	  if ( gsign != 0 ) 
	  {
	    if ( gsign == 1 ) 
	    {
	      if ( mem [g ].hh.b0 == gorder ) 
	      {
		curglue = curglue + mem [g + 2 ].cint ;
		gluetemp = mem [thisbox + 6 ].gr * curglue ;
		if ( gluetemp > 1000000000.0 ) 
		gluetemp = 1000000000.0 ;
		else if ( gluetemp < -1000000000.0 ) 
		gluetemp = -1000000000.0 ;
		curg = round ( gluetemp ) ;
	      } 
	    } 
	    else if ( mem [g ].hh.b1 == gorder ) 
	    {
	      curglue = curglue - mem [g + 3 ].cint ;
	      gluetemp = mem [thisbox + 6 ].gr * curglue ;
	      if ( gluetemp > 1000000000.0 ) 
	      gluetemp = 1000000000.0 ;
	      else if ( gluetemp < -1000000000.0 ) 
	      gluetemp = -1000000000.0 ;
	      curg = round ( gluetemp ) ;
	    } 
	  } 
	  ruleht = ruleht + curg ;
	  if ( mem [p ].hh.b1 >= 100 ) 
	  {
	    leaderbox = mem [p + 1 ].hh .v.RH ;
	    if ( mem [leaderbox ].hh.b0 == 2 ) 
	    {
	      rulewd = mem [leaderbox + 1 ].cint ;
	      ruledp = 0 ;
	      goto lab14 ;
	    } 
	    leaderht = mem [leaderbox + 3 ].cint + mem [leaderbox + 2 ]
	    .cint ;
	    if ( ( leaderht > 0 ) && ( ruleht > 0 ) ) 
	    {
	      ruleht = ruleht + 10 ;
	      edge = curv + ruleht ;
	      lx = 0 ;
	      if ( mem [p ].hh.b1 == 100 ) 
	      {
		savev = curv ;
		curv = topedge + leaderht * ( ( curv - topedge ) / leaderht ) 
		;
		if ( curv < savev ) 
		curv = curv + leaderht ;
	      } 
	      else {
		  
		lq = ruleht / leaderht ;
		lr = ruleht % leaderht ;
		if ( mem [p ].hh.b1 == 101 ) 
		curv = curv + ( lr / 2 ) ;
		else {
		    
		  lx = lr / ( lq + 1 ) ;
		  curv = curv + ( ( lr - ( lq - 1 ) * lx ) / 2 ) ;
		} 
	      } 
	      while ( curv + leaderht <= edge ) {
		  
		if ( curdir == 1 ) 
		curh = leftedge - mem [leaderbox + 4 ].cint ;
		else curh = leftedge + mem [leaderbox + 4 ].cint ;
		curv = curv + mem [leaderbox + 3 ].cint ;
		savev = curv ;
		tempptr = leaderbox ;
		outerdoingleaders = doingleaders ;
		doingleaders = true ;
		if ( mem [leaderbox ].hh.b0 == 1 ) 
		pdfvlistout () ;
		else pdfhlistout () ;
		doingleaders = outerdoingleaders ;
		curh = leftedge ;
		curv = savev - mem [leaderbox + 3 ].cint + leaderht + lx ;
	      } 
	      curv = edge - 10 ;
	      goto lab15 ;
	    } 
	  } 
	  goto lab13 ;
	} 
	break ;
      case 11 : 
	curv = curv + mem [p + 1 ].cint ;
	break ;
	default: 
	;
	break ;
      } 
      goto lab15 ;
      lab14: if ( ( rulewd == -1073741824L ) ) 
      rulewd = mem [thisbox + 1 ].cint ;
      ruleht = ruleht + ruledp ;
      curv = curv + ruleht ;
      if ( ( ruleht > 0 ) && ( rulewd > 0 ) ) 
      {
	if ( curdir == 1 ) 
	curh = curh - rulewd ;
	pdfsetrule ( curh , curv , rulewd , ruleht ) ;
	curh = leftedge ;
      } 
      goto lab15 ;
      lab13: curv = curv + ruleht ;
    } 
    lab15: p = mem [p ].hh .v.RH ;
  } 
  decr ( curs ) ;
} 
void 
fixpdfoutput ( void ) 
{
  fixpdfoutput_regmem 
  if ( ! fixedpdfoutputset ) 
  {
    fixedpdfoutput = eqtb [29332 ].cint ;
    fixedpdfoutputset = true ;
  } 
  else if ( fixedpdfoutput != eqtb [29332 ].cint ) 
  pdferror ( 1006 , 1132 ) ;
  if ( fixedpdfoutputset ) 
  fixpdfdraftmode () ;
} 
void 
fixpdfdraftmode ( void ) 
{
  fixpdfdraftmode_regmem 
  if ( ! fixedpdfdraftmodeset ) 
  {
    fixedpdfdraftmode = eqtb [29357 ].cint ;
    fixedpdfdraftmodeset = true ;
  } 
  else if ( fixedpdfdraftmode != eqtb [29357 ].cint ) 
  pdferror ( 1006 , 1133 ) ;
  if ( fixedpdfdraftmodeset && fixedpdfdraftmode > 0 ) 
  {
    fixedpdfdraftmodeset = true ;
    eqtb [29333 ].cint = 0 ;
    fixedpdfobjcompresslevel = 0 ;
  } 
} 
boolean 
zsubstrofstr ( strnumber s , strnumber t ) 
{
  /* 22 10 */ register boolean Result; substrofstr_regmem 
  poolpointer j, k, kk  ;
  k = strstart [t ];
  while ( ( k < strstart [t + 1 ]- ( strstart [s + 1 ]- strstart [s ]) ) 
  ) {
      
    j = strstart [s ];
    kk = k ;
    while ( ( j < strstart [s + 1 ]) ) {
	
      if ( strpool [j ]!= strpool [kk ]) 
      goto lab22 ;
      incr ( j ) ;
      incr ( kk ) ;
    } 
    Result = true ;
    return Result ;
    lab22: incr ( k ) ;
  } 
  Result = false ;
  return Result ;
} 
void 
zpdfshipout ( halfword p , boolean shippingpage ) 
{
  /* 30 31 */ pdfshipout_regmem 
  integer i, j, k  ;
  poolpointer s  ;
  boolean mediaboxgiven  ;
  halfword savefontlist  ;
  halfword saveobjlist  ;
  halfword saveximagelist  ;
  halfword savexformlist  ;
  integer saveimageprocset  ;
  integer savetextprocset  ;
  integer pdflastresources  ;
  if ( eqtb [29308 ].cint > 0 ) 
  {
    printnl ( 345 ) ;
    println () ;
    print ( 983 ) ;
  } 
  if ( ! initpdfoutput ) 
  {
    checkpdfminorversion () ;
    preparemag () ;
    fixeddecimaldigits = fixint ( eqtb [29334 ].cint , 0 , 4 ) ;
    minbpval = dividescaled ( onehundredbp , tenpow [fixeddecimaldigits + 2 ]
    , 0 ) ;
    if ( eqtb [29337 ].cint == 0 ) 
    eqtb [29337 ].cint = pkdpi ;
    fixedpkresolution = fixint ( eqtb [29337 ].cint , 72 , 8000 ) ;
    pkscalefactor = dividescaled ( 72 , fixedpkresolution , 5 + 
    fixeddecimaldigits ) ;
    if ( eqtb [27171 ].hh .v.RH != -268435455L ) 
    {
      kpseinitprog ( "PDFTEX" , fixedpkresolution , makecstring ( 
      tokenstostring ( eqtb [27171 ].hh .v.RH ) ) , nil ) ;
      {
	decr ( strptr ) ;
	poolptr = strstart [strptr ];
      } 
    } 
    else kpseinitprog ( "PDFTEX" , fixedpkresolution , nil , nil ) ;
    kpsesetprogramenabled ( kpsepkformat , 1 , kpsesrccompile ) ;
    setjobid ( eqtb [29297 ].cint , eqtb [29296 ].cint , eqtb [29295 ]
    .cint , eqtb [29294 ].cint ) ;
    if ( ( eqtb [29338 ].cint > 0 ) && ( pdfresnameprefix == 0 ) ) 
    pdfresnameprefix = getresnameprefix () ;
    initpdfoutput = true ;
  } 
  isshippingpage = shippingpage ;
  if ( shippingpage ) 
  {
    if ( termoffset > maxprintline - 9 ) 
    println () ;
    else if ( ( termoffset > 0 ) || ( fileoffset > 0 ) ) 
    printchar ( 32 ) ;
    printchar ( 91 ) ;
    j = 9 ;
    while ( ( eqtb [29375 + j ].cint == 0 ) && ( j > 0 ) ) decr ( j ) ;
    {register integer for_end; k = 0 ;for_end = j ; if ( k <= for_end) do 
      {
	printint ( eqtb [29375 + k ].cint ) ;
	if ( k < j ) 
	printchar ( 46 ) ;
      } 
    while ( k++ < for_end ) ;} 
    fflush ( stdout ) ;
  } 
  if ( eqtb [29308 ].cint > 0 ) 
  {
    if ( shippingpage ) 
    printchar ( 93 ) ;
    begindiagnostic () ;
    showbox ( p ) ;
    enddiagnostic ( true ) ;
  } 
  if ( ( mem [p + 3 ].cint > 1073741823L ) || ( mem [p + 2 ].cint > 
  1073741823L ) || ( mem [p + 3 ].cint + mem [p + 2 ].cint + eqtb [29906 
  ].cint > 1073741823L ) || ( mem [p + 1 ].cint + eqtb [29905 ].cint > 
  1073741823L ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 987 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 988 ;
      helpline [0 ]= 989 ;
    } 
    error () ;
    if ( eqtb [29308 ].cint <= 0 ) 
    {
      begindiagnostic () ;
      printnl ( 990 ) ;
      showbox ( p ) ;
      enddiagnostic ( true ) ;
    } 
    goto lab30 ;
  } 
  if ( mem [p + 3 ].cint + mem [p + 2 ].cint + eqtb [29906 ].cint > maxv 
  ) 
  maxv = mem [p + 3 ].cint + mem [p + 2 ].cint + eqtb [29906 ].cint ;
  if ( mem [p + 1 ].cint + eqtb [29905 ].cint > maxh ) 
  maxh = mem [p + 1 ].cint + eqtb [29905 ].cint ;
  fixpdfoutput () ;
  tempptr = p ;
  preparemag () ;
  pdflastresources = pdfnewobjnum () ;
  pdfpagegroupval = 0 ;
  pdffontlist = -268435455L ;
  pdfobjlist = -268435455L ;
  pdfxformlist = -268435455L ;
  pdfximagelist = -268435455L ;
  pdftextprocset = false ;
  pdfimageprocset = 0 ;
  if ( ! shippingpage ) 
  {
    pdfxformwidth = mem [p + 1 ].cint ;
    pdfxformheight = mem [p + 3 ].cint ;
    pdfxformdepth = mem [p + 2 ].cint ;
    pdfbegindict ( pdfcurform , 0 ) ;
    pdflaststream = pdfcurform ;
    curv = mem [p + 3 ].cint ;
    curh = 0 ;
    pdforiginh = 0 ;
    pdforiginv = pdfxformheight + pdfxformdepth ;
  } 
  else {
      
    curhoffset = eqtb [29908 ].cint + eqtb [29905 ].cint ;
    curvoffset = eqtb [29909 ].cint + eqtb [29906 ].cint ;
    if ( eqtb [29910 ].cint != 0 ) 
    curpagewidth = eqtb [29910 ].cint ;
    else curpagewidth = mem [p + 1 ].cint + 2 * curhoffset ;
    if ( eqtb [29911 ].cint != 0 ) 
    curpageheight = eqtb [29911 ].cint ;
    else curpageheight = mem [p + 3 ].cint + mem [p + 2 ].cint + 2 * 
    curvoffset ;
    pdflastpage = getobj ( 1 , totalpages + 1 , 0 ) ;
    objtab [pdflastpage ].int4 = 1 ;
    pdfnewdict ( 0 , 0 , 0 ) ;
    pdflaststream = objptr ;
    curh = curhoffset ;
    curv = mem [p + 3 ].cint + curvoffset ;
    pdforiginh = 0 ;
    pdforiginv = curpageheight ;
    pdfannotlist = -268435455L ;
    pdflinklist = -268435455L ;
    pdfdestlist = -268435455L ;
    pdfbeadlist = -268435455L ;
    lastthread = -268435455L ;
  } 
  if ( ! shippingpage ) 
  {
    {
      pdfprint ( 1134 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
    {
      pdfprint ( 1135 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
    if ( pdfmem [objtab [pdfcurform ].int4 + 4 ]!= -268435455L ) 
    {
      pdfprinttoksln ( pdfmem [objtab [pdfcurform ].int4 + 4 ]) ;
      {
	deletetokenref ( pdfmem [objtab [pdfcurform ].int4 + 4 ]) ;
	pdfmem [objtab [pdfcurform ].int4 + 4 ]= -268435455L ;
      } 
    } 
    pdfprint ( 1136 ) ;
    pdfprint ( 1051 ) ;
    pdfprintbp ( pdfxformwidth ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 32 ;
	incr ( pdfptr ) ;
      } 
    } 
    pdfprintbp ( pdfxformheight + pdfxformdepth ) ;
    {
      pdfprint ( 93 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
    {
      pdfprint ( 1137 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
    {
      pdfprint ( 1138 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
    pdfindirectln ( 1139 , pdflastresources ) ;
  } 
  pdfbeginstream () ;
  if ( shippingpage ) 
  {
    preparemag () ;
    if ( eqtb [29291 ].cint != 1000 ) 
    {
      pdfprintreal ( eqtb [29291 ].cint , 3 ) ;
      pdfprint ( 1140 ) ;
      pdfprintreal ( eqtb [29291 ].cint , 3 ) ;
      {
	pdfprint ( 1141 ) ;
	{
	  {
	    if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	    pdfosgetosbuf ( 1 ) ;
	    else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	    overflow ( 999 , pdfopbufsize ) ;
	    else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	    pdfflush () ;
	  } 
	  {
	    pdfbuf [pdfptr ]= 10 ;
	    incr ( pdfptr ) ;
	  } 
	} 
      } 
    } 
  } 
  pdfshipoutbegin ( shippingpage ) ;
  if ( shippingpage ) 
  pdfoutcolorstackstartpage () ;
  if ( mem [p ].hh.b0 == 1 ) 
  pdfvlistout () ;
  else pdfhlistout () ;
  if ( shippingpage ) 
  incr ( totalpages ) ;
  curs = -1 ;
  pdfendtext () ;
  pdfshipoutend ( shippingpage ) ;
  pdfendstream () ;
  if ( shippingpage ) 
  {
    pdfbegindict ( pdflastpage , 1 ) ;
    {
      pdfprint ( 1153 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
    pdfindirectln ( 1154 , pdflaststream ) ;
    pdfindirectln ( 1139 , pdflastresources ) ;
    mediaboxgiven = false ;
    if ( eqtb [27169 ].hh .v.RH != -268435455L ) 
    {
      s = tokenstostring ( eqtb [27169 ].hh .v.RH ) ;
      mediaboxgiven = substrofstr ( 1155 , s ) ;
      flushstr ( s ) ;
    } 
    if ( ! mediaboxgiven ) 
    {
      pdfprint ( 1156 ) ;
      pdfprintmagbp ( curpagewidth ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 32 ;
	  incr ( pdfptr ) ;
	} 
      } 
      pdfprintmagbp ( curpageheight ) ;
      {
	pdfprint ( 93 ) ;
	{
	  {
	    if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	    pdfosgetosbuf ( 1 ) ;
	    else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	    overflow ( 999 , pdfopbufsize ) ;
	    else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	    pdfflush () ;
	  } 
	  {
	    pdfbuf [pdfptr ]= 10 ;
	    incr ( pdfptr ) ;
	  } 
	} 
      } 
    } 
    if ( eqtb [27169 ].hh .v.RH != -268435455L ) 
    pdfprinttoksln ( eqtb [27169 ].hh .v.RH ) ;
    if ( totalpages % 6 == 1 ) 
    {
      pdfcreateobj ( 2 , 6 ) ;
      pdflastpages = objptr ;
    } 
    pdfindirectln ( 1158 , pdflastpages ) ;
    if ( pdfpagegroupval > 0 ) 
    {
      pdfprint ( 1157 ) ;
      pdfprintint ( pdfpagegroupval ) ;
      {
	pdfprint ( 1072 ) ;
	{
	  {
	    if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	    pdfosgetosbuf ( 1 ) ;
	    else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	    overflow ( 999 , pdfopbufsize ) ;
	    else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	    pdfflush () ;
	  } 
	  {
	    pdfbuf [pdfptr ]= 10 ;
	    incr ( pdfptr ) ;
	  } 
	} 
      } 
    } 
    if ( ( pdfannotlist != -268435455L ) || ( pdflinklist != -268435455L ) ) 
    {
      pdfprint ( 1159 ) ;
      k = pdfannotlist ;
      while ( k != -268435455L ) {
	  
	pdfprintint ( mem [k ].hh .v.LH ) ;
	pdfprint ( 1143 ) ;
	k = mem [k ].hh .v.RH ;
      } 
      k = pdflinklist ;
      while ( k != -268435455L ) {
	  
	pdfprintint ( mem [k ].hh .v.LH ) ;
	pdfprint ( 1143 ) ;
	k = mem [k ].hh .v.RH ;
      } 
      {
	pdfprint ( 93 ) ;
	{
	  {
	    if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	    pdfosgetosbuf ( 1 ) ;
	    else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	    overflow ( 999 , pdfopbufsize ) ;
	    else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	    pdfflush () ;
	  } 
	  {
	    pdfbuf [pdfptr ]= 10 ;
	    incr ( pdfptr ) ;
	  } 
	} 
      } 
    } 
    if ( pdfbeadlist != -268435455L ) 
    {
      k = pdfbeadlist ;
      pdfprint ( 1160 ) ;
      while ( k != -268435455L ) {
	  
	pdfprintint ( mem [k ].hh .v.LH ) ;
	pdfprint ( 1143 ) ;
	k = mem [k ].hh .v.RH ;
      } 
      {
	pdfprint ( 93 ) ;
	{
	  {
	    if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	    pdfosgetosbuf ( 1 ) ;
	    else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	    overflow ( 999 , pdfopbufsize ) ;
	    else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	    pdfflush () ;
	  } 
	  {
	    pdfbuf [pdfptr ]= 10 ;
	    incr ( pdfptr ) ;
	  } 
	} 
      } 
    } 
    pdfenddict () ;
  } 
  if ( pdfobjlist != -268435455L ) 
  {
    k = pdfobjlist ;
    while ( k != -268435455L ) {
	
      if ( ! ( objtab [mem [k ].hh .v.LH ].int2 > -1 ) ) 
      pdfwriteobj ( mem [k ].hh .v.LH ) ;
      k = mem [k ].hh .v.RH ;
    } 
  } 
  if ( pdfxformlist != -268435455L ) 
  {
    k = pdfxformlist ;
    while ( k != -268435455L ) {
	
      if ( ! ( objtab [mem [k ].hh .v.LH ].int2 > -1 ) ) 
      {
	savedpdfcurform = pdfcurform ;
	pdfcurform = mem [k ].hh .v.LH ;
	savefontlist = pdffontlist ;
	saveobjlist = pdfobjlist ;
	savexformlist = pdfxformlist ;
	saveximagelist = pdfximagelist ;
	savetextprocset = pdftextprocset ;
	saveimageprocset = pdfimageprocset ;
	pdffontlist = -268435455L ;
	pdfobjlist = -268435455L ;
	pdfxformlist = -268435455L ;
	pdfximagelist = -268435455L ;
	pdftextprocset = false ;
	pdfimageprocset = 0 ;
	pdfshipout ( pdfmem [objtab [pdfcurform ].int4 + 3 ], false ) ;
	pdfcurform = savedpdfcurform ;
	pdffontlist = savefontlist ;
	pdfobjlist = saveobjlist ;
	pdfxformlist = savexformlist ;
	pdfximagelist = saveximagelist ;
	pdftextprocset = savetextprocset ;
	pdfimageprocset = saveimageprocset ;
      } 
      k = mem [k ].hh .v.RH ;
    } 
  } 
  if ( pdfximagelist != -268435455L ) 
  {
    k = pdfximagelist ;
    while ( k != -268435455L ) {
	
      if ( ! ( objtab [mem [k ].hh .v.LH ].int2 > -1 ) ) 
      pdfwriteimage ( mem [k ].hh .v.LH ) ;
      k = mem [k ].hh .v.RH ;
    } 
  } 
  if ( shippingpage ) 
  {
    pdforiginh = 0 ;
    pdforiginv = curpageheight ;
    if ( pdfannotlist != -268435455L ) 
    {
      k = pdfannotlist ;
      while ( k != -268435455L ) {
	  
	i = objtab [mem [k ].hh .v.LH ].int4 ;
	pdfbegindict ( mem [k ].hh .v.LH , 1 ) ;
	{
	  pdfprint ( 1165 ) ;
	  {
	    {
	      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	      pdfosgetosbuf ( 1 ) ;
	      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	      overflow ( 999 , pdfopbufsize ) ;
	      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	      pdfflush () ;
	    } 
	    {
	      pdfbuf [pdfptr ]= 10 ;
	      incr ( pdfptr ) ;
	    } 
	  } 
	} 
	pdfprinttoksln ( mem [i + 5 ].hh .v.LH ) ;
	pdfrectangle ( mem [i + 1 ].cint , mem [i + 2 ].cint , mem [i + 3 
	].cint , mem [i + 4 ].cint ) ;
	pdfenddict () ;
	k = mem [k ].hh .v.RH ;
      } 
    } 
    if ( pdflinklist != -268435455L ) 
    {
      k = pdflinklist ;
      while ( k != -268435455L ) {
	  
	i = objtab [mem [k ].hh .v.LH ].int4 ;
	pdfbegindict ( mem [k ].hh .v.LH , 1 ) ;
	{
	  pdfprint ( 1165 ) ;
	  {
	    {
	      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	      pdfosgetosbuf ( 1 ) ;
	      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	      overflow ( 999 , pdfopbufsize ) ;
	      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	      pdfflush () ;
	    } 
	    {
	      pdfbuf [pdfptr ]= 10 ;
	      incr ( pdfptr ) ;
	    } 
	  } 
	} 
	if ( mem [mem [i + 5 ].hh .v.RH ].hh.b0 != 3 ) 
	{
	  pdfprint ( 1166 ) ;
	  {
	    {
	      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	      pdfosgetosbuf ( 1 ) ;
	      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	      overflow ( 999 , pdfopbufsize ) ;
	      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	      pdfflush () ;
	    } 
	    {
	      pdfbuf [pdfptr ]= 10 ;
	      incr ( pdfptr ) ;
	    } 
	  } 
	} 
	if ( mem [i + 5 ].hh .v.LH != -268435455L ) 
	pdfprinttoksln ( mem [i + 5 ].hh .v.LH ) ;
	pdfrectangle ( mem [i + 1 ].cint , mem [i + 2 ].cint , mem [i + 3 
	].cint , mem [i + 4 ].cint ) ;
	if ( mem [mem [i + 5 ].hh .v.RH ].hh.b0 != 3 ) 
	pdfprint ( 1167 ) ;
	writeaction ( mem [i + 5 ].hh .v.RH ) ;
	pdfenddict () ;
	k = mem [k ].hh .v.RH ;
      } 
      k = pdflinklist ;
      while ( k != -268435455L ) {
	  
	i = objtab [mem [k ].hh .v.LH ].int4 ;
	if ( mem [i ].hh .v.LH == 268435455L ) 
	flushwhatsitnode ( i , 14 ) ;
	k = mem [k ].hh .v.RH ;
      } 
    } 
    if ( pdfdestlist != -268435455L ) 
    {
      k = pdfdestlist ;
      while ( k != -268435455L ) {
	  
	if ( ( objtab [mem [k ].hh .v.LH ].int2 > -1 ) ) 
	pdferror ( 1161 , 1168 ) ;
	else {
	    
	  i = objtab [mem [k ].hh .v.LH ].int4 ;
	  if ( mem [i + 5 ].hh.b1 > 0 ) 
	  {
	    pdfbegindict ( mem [k ].hh .v.LH , 1 ) ;
	    pdfprint ( 1169 ) ;
	  } 
	  else pdfbeginobj ( mem [k ].hh .v.LH , 1 ) ;
	  {
	    {
	      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	      pdfosgetosbuf ( 1 ) ;
	      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	      overflow ( 999 , pdfopbufsize ) ;
	      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	      pdfflush () ;
	    } 
	    {
	      pdfbuf [pdfptr ]= 91 ;
	      incr ( pdfptr ) ;
	    } 
	  } 
	  pdfprintint ( pdflastpage ) ;
	  pdfprint ( 1143 ) ;
	  switch ( mem [i + 5 ].hh.b0 ) 
	  {case 0 : 
	    {
	      pdfprint ( 1170 ) ;
	      pdfprintmagbp ( ( ( mem [i + 1 ].cint ) - pdforiginh ) ) ;
	      {
		{
		  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfosgetosbuf ( 1 ) ;
		  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		  overflow ( 999 , pdfopbufsize ) ;
		  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfflush () ;
		} 
		{
		  pdfbuf [pdfptr ]= 32 ;
		  incr ( pdfptr ) ;
		} 
	      } 
	      pdfprintmagbp ( ( pdforiginv - ( mem [i + 2 ].cint ) ) ) ;
	      {
		{
		  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfosgetosbuf ( 1 ) ;
		  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		  overflow ( 999 , pdfopbufsize ) ;
		  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfflush () ;
		} 
		{
		  pdfbuf [pdfptr ]= 32 ;
		  incr ( pdfptr ) ;
		} 
	      } 
	      if ( mem [i + 6 ].hh .v.LH == -268435455L ) 
	      pdfprint ( 1171 ) ;
	      else {
		  
		pdfprintint ( mem [i + 6 ].hh .v.LH / 1000 ) ;
		{
		  {
		    if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		    pdfosgetosbuf ( 1 ) ;
		    else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		    overflow ( 999 , pdfopbufsize ) ;
		    else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		    pdfflush () ;
		  } 
		  {
		    pdfbuf [pdfptr ]= 46 ;
		    incr ( pdfptr ) ;
		  } 
		} 
		pdfprintint ( ( mem [i + 6 ].hh .v.LH % 1000 ) ) ;
	      } 
	    } 
	    break ;
	  case 1 : 
	    pdfprint ( 1172 ) ;
	    break ;
	  case 2 : 
	    {
	      pdfprint ( 1173 ) ;
	      pdfprintmagbp ( ( pdforiginv - ( mem [i + 2 ].cint ) ) ) ;
	    } 
	    break ;
	  case 3 : 
	    {
	      pdfprint ( 1174 ) ;
	      pdfprintmagbp ( ( ( mem [i + 1 ].cint ) - pdforiginh ) ) ;
	    } 
	    break ;
	  case 4 : 
	    pdfprint ( 1175 ) ;
	    break ;
	  case 5 : 
	    {
	      pdfprint ( 1176 ) ;
	      pdfprintmagbp ( ( pdforiginv - ( mem [i + 2 ].cint ) ) ) ;
	    } 
	    break ;
	  case 6 : 
	    {
	      pdfprint ( 1177 ) ;
	      pdfprintmagbp ( ( ( mem [i + 1 ].cint ) - pdforiginh ) ) ;
	    } 
	    break ;
	  case 7 : 
	    {
	      pdfprint ( 1178 ) ;
	      pdfprintrectspec ( i ) ;
	    } 
	    break ;
	    default: 
	    pdferror ( 1161 , 1179 ) ;
	    break ;
	  } 
	  {
	    pdfprint ( 93 ) ;
	    {
	      {
		if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		pdfosgetosbuf ( 1 ) ;
		else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		overflow ( 999 , pdfopbufsize ) ;
		else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		pdfflush () ;
	      } 
	      {
		pdfbuf [pdfptr ]= 10 ;
		incr ( pdfptr ) ;
	      } 
	    } 
	  } 
	  if ( mem [i + 5 ].hh.b1 > 0 ) 
	  pdfenddict () ;
	  else pdfendobj () ;
	} 
	k = mem [k ].hh .v.RH ;
      } 
    } 
    if ( pdfbeadlist != -268435455L ) 
    {
      k = pdfbeadlist ;
      while ( k != -268435455L ) {
	  
	pdfnewobj ( 0 , 0 , 1 ) ;
	{
	  {
	    if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	    pdfosgetosbuf ( 1 ) ;
	    else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	    overflow ( 999 , pdfopbufsize ) ;
	    else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	    pdfflush () ;
	  } 
	  {
	    pdfbuf [pdfptr ]= 91 ;
	    incr ( pdfptr ) ;
	  } 
	} 
	i = pdfmem [objtab [mem [k ].hh .v.LH ].int4 ];
	pdfprintrectspec ( i ) ;
	if ( mem [i ].hh .v.LH == 268435455L ) 
	flushwhatsitnode ( i , 19 ) ;
	{
	  pdfprint ( 93 ) ;
	  {
	    {
	      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	      pdfosgetosbuf ( 1 ) ;
	      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	      overflow ( 999 , pdfopbufsize ) ;
	      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	      pdfflush () ;
	    } 
	    {
	      pdfbuf [pdfptr ]= 10 ;
	      incr ( pdfptr ) ;
	    } 
	  } 
	} 
	pdfmem [objtab [mem [k ].hh .v.LH ].int4 ]= objptr ;
	pdfendobj () ;
	k = mem [k ].hh .v.RH ;
      } 
    } 
  } 
  pdfbegindict ( pdflastresources , 1 ) ;
  if ( shippingpage ) 
  {
    if ( eqtb [27170 ].hh .v.RH != -268435455L ) 
    pdfprinttoksln ( eqtb [27170 ].hh .v.RH ) ;
  } 
  else {
      
    if ( pdfmem [objtab [pdfcurform ].int4 + 5 ]!= -268435455L ) 
    {
      pdfprinttoksln ( pdfmem [objtab [pdfcurform ].int4 + 5 ]) ;
      {
	deletetokenref ( pdfmem [objtab [pdfcurform ].int4 + 5 ]) ;
	pdfmem [objtab [pdfcurform ].int4 + 5 ]= -268435455L ;
      } 
    } 
  } 
  if ( pdffontlist != -268435455L ) 
  {
    pdfprint ( 1142 ) ;
    k = pdffontlist ;
    while ( k != -268435455L ) {
	
      pdfprint ( 1033 ) ;
      {
	if ( pdffontnum [mem [k ].hh .v.LH ]< 0 ) 
	ff = - (integer) pdffontnum [mem [k ].hh .v.LH ];
	else ff = mem [k ].hh .v.LH ;
      } 
      pdfprintint ( ff ) ;
      if ( pdfresnameprefix != 0 ) 
      pdfprint ( pdfresnameprefix ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 32 ;
	  incr ( pdfptr ) ;
	} 
      } 
      pdfprintint ( pdffontnum [ff ]) ;
      pdfprint ( 1143 ) ;
      k = mem [k ].hh .v.RH ;
    } 
    {
      pdfprint ( 1013 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
    pdftextprocset = true ;
  } 
  if ( ( pdfxformlist != -268435455L ) || ( pdfximagelist != -268435455L ) ) 
  {
    pdfprint ( 1144 ) ;
    k = pdfxformlist ;
    while ( k != -268435455L ) {
	
      pdfprint ( 1145 ) ;
      pdfprintint ( objtab [mem [k ].hh .v.LH ].int0 ) ;
      if ( pdfresnameprefix != 0 ) 
      pdfprint ( pdfresnameprefix ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 32 ;
	  incr ( pdfptr ) ;
	} 
      } 
      pdfprintint ( mem [k ].hh .v.LH ) ;
      pdfprint ( 1143 ) ;
      k = mem [k ].hh .v.RH ;
    } 
    k = pdfximagelist ;
    while ( k != -268435455L ) {
	
      pdfprint ( 1146 ) ;
      pdfprintint ( objtab [mem [k ].hh .v.LH ].int0 ) ;
      if ( pdfresnameprefix != 0 ) 
      pdfprint ( pdfresnameprefix ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 32 ;
	  incr ( pdfptr ) ;
	} 
      } 
      pdfprintint ( mem [k ].hh .v.LH ) ;
      pdfprint ( 1143 ) ;
      updateimageprocset ( pdfmem [objtab [mem [k ].hh .v.LH ].int4 + 4 ]
      ) ;
      k = mem [k ].hh .v.RH ;
    } 
    {
      pdfprint ( 1013 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
  } 
  pdfprint ( 1147 ) ;
  if ( pdftextprocset ) 
  pdfprint ( 1148 ) ;
  if ( checkimageb ( pdfimageprocset ) ) 
  pdfprint ( 1149 ) ;
  if ( checkimagec ( pdfimageprocset ) ) 
  pdfprint ( 1150 ) ;
  if ( checkimagei ( pdfimageprocset ) ) 
  pdfprint ( 1151 ) ;
  {
    pdfprint ( 1152 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
  pdfenddict () ;
  flushlist ( pdffontlist ) ;
  flushlist ( pdfobjlist ) ;
  flushlist ( pdfxformlist ) ;
  flushlist ( pdfximagelist ) ;
  if ( shippingpage ) 
  {
    flushlist ( pdfannotlist ) ;
    flushlist ( pdflinklist ) ;
    flushlist ( pdfdestlist ) ;
    flushlist ( pdfbeadlist ) ;
  } 
  lab30: ;
  if ( ( eTeXmode == 1 ) ) 
  {
    if ( LRproblems > 0 ) 
    {
      {
	println () ;
	printnl ( 2008 ) ;
	printint ( LRproblems / 10000 ) ;
	print ( 2009 ) ;
	printint ( LRproblems % 10000 ) ;
	print ( 2010 ) ;
	LRproblems = 0 ;
      } 
      printchar ( 41 ) ;
      println () ;
    } 
    if ( ( LRptr != -268435455L ) || ( curdir != 0 ) ) 
    confusion ( 2012 ) ;
  } 
  if ( ( eqtb [29308 ].cint <= 0 ) && shippingpage ) 
  printchar ( 93 ) ;
  deadcycles = 0 ;
  fflush ( stdout ) ;
	;
#ifdef STAT
  if ( eqtb [29305 ].cint > 1 ) 
  {
    printnl ( 984 ) ;
    printint ( varused ) ;
    printchar ( 38 ) ;
    printint ( dynused ) ;
    printchar ( 59 ) ;
  } 
#endif /* STAT */
  flushnodelist ( p ) ;
	;
#ifdef STAT
  if ( eqtb [29305 ].cint > 1 ) 
  {
    print ( 985 ) ;
    printint ( varused ) ;
    printchar ( 38 ) ;
    printint ( dynused ) ;
    print ( 986 ) ;
    printint ( himemmin - lomemmax - 1 ) ;
    println () ;
  } 
#endif /* STAT */
} 
void 
zshipout ( halfword p ) 
{
  shipout_regmem 
  fixpdfoutput () ;
  if ( eqtb [29332 ].cint > 0 ) 
  pdfshipout ( p , true ) ;
  else dvishipout ( p ) ;
} 
boolean 
zstrlessstr ( strnumber s1 , strnumber s2 ) 
{
  register boolean Result; strlessstr_regmem 
  poolpointer j1, j2, e1, e2  ;
  packedASCIIcode c1, c2  ;
  j1 = strstart [s1 ];
  j2 = strstart [s2 ];
  e1 = j1 + ( strstart [s1 + 1 ]- strstart [s1 ]) ;
  e2 = j2 + ( strstart [s2 + 1 ]- strstart [s2 ]) ;
  while ( ( j1 < e1 ) && ( j2 < e2 ) ) {
      
    c1 = strpool [j1 ];
    incr ( j1 ) ;
    if ( ( c1 == 92 ) && ( j1 < e1 ) ) 
    {
      c1 = strpool [j1 ];
      incr ( j1 ) ;
      if ( ( c1 >= 48 ) && ( c1 <= 55 ) ) 
      {
	c1 = c1 - 48 ;
	if ( ( j1 < e1 ) && ( strpool [j1 ]>= 48 ) && ( strpool [j1 ]<= 55 
	) ) 
	{
	  c1 = 8 * c1 + strpool [j1 ]- 48 ;
	  incr ( j1 ) ;
	  if ( ( j1 < e1 ) && ( strpool [j1 ]>= 48 ) && ( strpool [j1 ]<= 
	  55 ) && ( c1 < 32 ) ) 
	  {
	    c1 = 8 * c1 + strpool [j1 ]- 48 ;
	    incr ( j1 ) ;
	  } 
	} 
      } 
      else {
	  
	switch ( c1 ) 
	{case 98 : 
	  c1 = 8 ;
	  break ;
	case 102 : 
	  c1 = 12 ;
	  break ;
	case 110 : 
	  c1 = 10 ;
	  break ;
	case 114 : 
	  c1 = 13 ;
	  break ;
	case 116 : 
	  c1 = 9 ;
	  break ;
	  default: 
	  ;
	  break ;
	} 
      } 
    } 
    c2 = strpool [j2 ];
    incr ( j2 ) ;
    if ( ( c2 == 92 ) && ( j2 < e2 ) ) 
    {
      c2 = strpool [j2 ];
      incr ( j2 ) ;
      if ( ( c2 >= 48 ) && ( c2 <= 55 ) ) 
      {
	c2 = c2 - 48 ;
	if ( ( j2 < e2 ) && ( strpool [j2 ]>= 48 ) && ( strpool [j2 ]<= 55 
	) ) 
	{
	  c2 = 8 * c2 + strpool [j2 ]- 48 ;
	  incr ( j2 ) ;
	  if ( ( j2 < e2 ) && ( strpool [j2 ]>= 48 ) && ( strpool [j2 ]<= 
	  55 ) && ( c2 < 32 ) ) 
	  {
	    c2 = 8 * c2 + strpool [j2 ]- 48 ;
	    incr ( j2 ) ;
	  } 
	} 
      } 
      else {
	  
	switch ( c2 ) 
	{case 98 : 
	  c2 = 8 ;
	  break ;
	case 102 : 
	  c2 = 12 ;
	  break ;
	case 110 : 
	  c2 = 10 ;
	  break ;
	case 114 : 
	  c2 = 13 ;
	  break ;
	case 116 : 
	  c2 = 9 ;
	  break ;
	  default: 
	  ;
	  break ;
	} 
      } 
    } 
    if ( c1 < c2 ) 
    {
      Result = true ;
      return Result ;
    } 
    else if ( c1 > c2 ) 
    {
      Result = false ;
      return Result ;
    } 
  } 
  if ( ( j1 >= e1 ) && ( j2 < e2 ) ) 
  Result = true ;
  else Result = false ;
  return Result ;
} 
void 
zsortdestnames ( integer l , integer r ) 
{
  sortdestnames_regmem 
  integer i, j  ;
  strnumber s  ;
  destnameentry e  ;
  i = l ;
  j = r ;
  s = destnames [( l + r ) / 2 ].objname ;
  do {
      while ( strlessstr ( destnames [i ].objname , s ) ) incr ( i ) ;
    while ( strlessstr ( s , destnames [j ].objname ) ) decr ( j ) ;
    if ( i <= j ) 
    {
      e = destnames [i ];
      destnames [i ]= destnames [j ];
      destnames [j ]= e ;
      incr ( i ) ;
      decr ( j ) ;
    } 
  } while ( ! ( i > j ) ) ;
  if ( l < j ) 
  sortdestnames ( l , j ) ;
  if ( i < r ) 
  sortdestnames ( i , r ) ;
} 
void 
zpdffixdest ( integer k ) 
{
  pdffixdest_regmem 
  if ( objtab [k ].int4 != -268435455L ) 
  return ;
  pdfwarning ( 1188 , 345 , false , false ) ;
  if ( objtab [k ].int0 < 0 ) 
  {
    print ( 1189 ) ;
    print ( - (integer) objtab [k ].int0 ) ;
    print ( 125 ) ;
  } 
  else {
      
    print ( 1190 ) ;
    printint ( objtab [k ].int0 ) ;
  } 
  print ( 1191 ) ;
  println () ;
  println () ;
  pdfbeginobj ( k , 1 ) ;
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 91 ;
      incr ( pdfptr ) ;
    } 
  } 
  pdfprintint ( headtab [1 ]) ;
  {
    pdfprint ( 1192 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
  pdfendobj () ;
} 
void 
pdfprintinfo ( void ) 
{
  pdfprintinfo_regmem 
  strnumber s  ;
  boolean creatorgiven, producergiven, creationdategiven, moddategiven, 
  trappedgiven  ;
  pdfnewdict ( 0 , 0 , 3 ) ;
  creatorgiven = false ;
  producergiven = false ;
  creationdategiven = false ;
  moddategiven = false ;
  trappedgiven = false ;
  if ( pdfinfotoks != -268435455L ) 
  {
    s = tokenstostring ( pdfinfotoks ) ;
    creatorgiven = substrofstr ( 1210 , s ) ;
    producergiven = substrofstr ( 1211 , s ) ;
    creationdategiven = substrofstr ( 1212 , s ) ;
    moddategiven = substrofstr ( 1213 , s ) ;
    trappedgiven = substrofstr ( 1214 , s ) ;
  } 
  if ( ! producergiven ) 
  {
    pdfprint ( 1219 ) ;
    pdfprintint ( 140 / 100 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 46 ;
	incr ( pdfptr ) ;
      } 
    } 
    pdfprintint ( 140 % 100 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 46 ;
	incr ( pdfptr ) ;
      } 
    } 
    pdfprint ( 257 ) ;
    {
      pdfprint ( 41 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
  } 
  if ( pdfinfotoks != -268435455L ) 
  {
    if ( ( strstart [s + 1 ]- strstart [s ]) > 0 ) 
    {
      {
	pdfprint ( s ) ;
	{
	  {
	    if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	    pdfosgetosbuf ( 1 ) ;
	    else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	    overflow ( 999 , pdfopbufsize ) ;
	    else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	    pdfflush () ;
	  } 
	  {
	    pdfbuf [pdfptr ]= 10 ;
	    incr ( pdfptr ) ;
	  } 
	} 
      } 
    } 
    flushstr ( s ) ;
    {
      deletetokenref ( pdfinfotoks ) ;
      pdfinfotoks = -268435455L ;
    } 
  } 
  if ( ! creatorgiven ) 
  pdfstrentryln ( 1215 , 1216 ) ;
  if ( eqtb [29362 ].cint == 0 ) 
  {
    if ( ! creationdategiven ) 
    {
      printcreationdate () ;
    } 
    if ( ! moddategiven ) 
    {
      printmoddate () ;
    } 
  } 
  if ( ! trappedgiven ) 
  {
    {
      pdfprint ( 1217 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
  } 
  if ( eqtb [29363 ].cint % 2 == 0 ) 
  {
    pdfstrentryln ( 1218 , pdftexbanner ) ;
  } 
  pdfenddict () ;
} 
void 
zscanspec ( groupcode c , boolean threecodes ) 
{
  /* 40 */ scanspec_regmem 
  integer s  ;
  unsigned char speccode  ;
  if ( threecodes ) 
  s = savestack [saveptr + 0 ].cint ;
  if ( scankeyword ( 1237 ) ) 
  speccode = 0 ;
  else if ( scankeyword ( 1238 ) ) 
  speccode = 1 ;
  else {
      
    speccode = 1 ;
    curval = 0 ;
    goto lab40 ;
  } 
  scandimen ( false , false , false ) ;
  lab40: if ( threecodes ) 
  {
    savestack [saveptr + 0 ].cint = s ;
    incr ( saveptr ) ;
  } 
  savestack [saveptr + 0 ].cint = speccode ;
  savestack [saveptr + 1 ].cint = curval ;
  saveptr = saveptr + 2 ;
  newsavelevel ( c ) ;
  scanleftbrace () ;
} 
boolean 
zcheckexpandpars ( internalfontnumber f ) 
{
  register boolean Result; checkexpandpars_regmem 
  internalfontnumber k  ;
  Result = false ;
  if ( ( pdffontstep [f ]== 0 ) || ( ( pdffontstretch [f ]== 0 ) && ( 
  pdffontshrink [f ]== 0 ) ) ) 
  return Result ;
  if ( curfontstep < 0 ) 
  curfontstep = pdffontstep [f ];
  else if ( curfontstep != pdffontstep [f ]) 
  pdferror ( 1031 , 1239 ) ;
  k = pdffontstretch [f ];
  if ( k != 0 ) 
  {
    if ( maxstretchratio < 0 ) 
    maxstretchratio = pdffontexpandratio [k ];
    else if ( maxstretchratio != pdffontexpandratio [k ]) 
    pdferror ( 1031 , 1240 ) ;
  } 
  k = pdffontshrink [f ];
  if ( k != 0 ) 
  {
    if ( maxshrinkratio < 0 ) 
    maxshrinkratio = - (integer) pdffontexpandratio [k ];
    else if ( maxshrinkratio != - (integer) pdffontexpandratio [k ]) 
    pdferror ( 1031 , 1240 ) ;
  } 
  Result = true ;
  return Result ;
} 
scaled 
zcharstretch ( internalfontnumber f , eightbits c ) 
{
  register scaled Result; charstretch_regmem 
  internalfontnumber k  ;
  scaled dw  ;
  integer ef  ;
  Result = 0 ;
  k = pdffontstretch [f ];
  ef = getefcode ( f , c ) ;
  if ( ( k != 0 ) && ( ef > 0 ) ) 
  {
    dw = fontinfo [widthbase [k ]+ fontinfo [charbase [k ]+ 
    effectivechar ( true , k , c ) ].qqqq .b0 ].cint - fontinfo [widthbase 
    [f ]+ fontinfo [charbase [f ]+ effectivechar ( true , f , c ) ].qqqq 
    .b0 ].cint ;
    if ( dw > 0 ) 
    Result = roundxnoverd ( dw , ef , 1000 ) ;
  } 
  return Result ;
} 
scaled 
zcharshrink ( internalfontnumber f , eightbits c ) 
{
  register scaled Result; charshrink_regmem 
  internalfontnumber k  ;
  scaled dw  ;
  integer ef  ;
  Result = 0 ;
  k = pdffontshrink [f ];
  ef = getefcode ( f , c ) ;
  if ( ( k != 0 ) && ( ef > 0 ) ) 
  {
    dw = fontinfo [widthbase [f ]+ fontinfo [charbase [f ]+ 
    effectivechar ( true , f , c ) ].qqqq .b0 ].cint - fontinfo [widthbase 
    [k ]+ fontinfo [charbase [k ]+ effectivechar ( true , k , c ) ].qqqq 
    .b0 ].cint ;
    if ( dw > 0 ) 
    Result = roundxnoverd ( dw , ef , 1000 ) ;
  } 
  return Result ;
} 
scaled 
zgetkern ( internalfontnumber f , eightbits lc , eightbits rc ) 
{
  /* 22 */ register scaled Result; getkern_regmem 
  fourquarters i  ;
  fourquarters j  ;
  fontindex k  ;
  Result = 0 ;
  i = fontinfo [charbase [f ]+ effectivechar ( true , f , lc ) ].qqqq ;
  if ( ( ( i .b2 ) % 4 ) != 1 ) 
  return Result ;
  k = ligkernbase [f ]+ i .b3 ;
  j = fontinfo [k ].qqqq ;
  if ( j .b0 <= 128 ) 
  goto lab23 ;
  k = ligkernbase [f ]+ 256 * j .b2 + j .b3 + 32768L - 256 * ( 128 ) ;
  lab22: j = fontinfo [k ].qqqq ;
  lab23: if ( ( j .b1 == rc ) && ( j .b0 <= 128 ) && ( j .b2 >= 128 ) ) 
  {
    Result = fontinfo [kernbase [f ]+ 256 * j .b2 + j .b3 ].cint ;
    return Result ;
  } 
  if ( j .b0 == 0 ) 
  incr ( k ) ;
  else {
      
    if ( j .b0 >= 128 ) 
    return Result ;
    k = k + j .b0 + 1 ;
  } 
  goto lab22 ;
  return Result ;
} 
scaled 
zkernstretch ( halfword p ) 
{
  register scaled Result; kernstretch_regmem 
  halfword l, r  ;
  scaled d  ;
  Result = 0 ;
  if ( ( prevcharp == -268435455L ) || ( mem [prevcharp ].hh .v.RH != p ) || 
  ( mem [p ].hh .v.RH == -268435455L ) ) 
  return Result ;
  l = prevcharp ;
  r = mem [p ].hh .v.RH ;
  if ( ! ( l >= himemmin ) ) {
      
    if ( mem [l ].hh.b0 == 6 ) 
    l = l + 1 ;
    else return Result ;
  } 
  if ( ! ( r >= himemmin ) ) {
      
    if ( mem [r ].hh.b0 == 6 ) 
    r = r + 1 ;
    else return Result ;
  } 
  if ( ! ( ( mem [l ].hh.b0 == mem [r ].hh.b0 ) && ( pdffontstretch [mem 
  [l ].hh.b0 ]!= 0 ) ) ) 
  return Result ;
  d = getkern ( pdffontstretch [mem [l ].hh.b0 ], mem [l ].hh.b1 , mem [
  r ].hh.b1 ) ;
  Result = roundxnoverd ( d - mem [p + 1 ].cint , getefcode ( mem [l ]
  .hh.b0 , mem [l ].hh.b1 ) , 1000 ) ;
  return Result ;
} 
scaled 
zkernshrink ( halfword p ) 
{
  register scaled Result; kernshrink_regmem 
  halfword l, r  ;
  scaled d  ;
  Result = 0 ;
  if ( ( prevcharp == -268435455L ) || ( mem [prevcharp ].hh .v.RH != p ) || 
  ( mem [p ].hh .v.RH == -268435455L ) ) 
  return Result ;
  l = prevcharp ;
  r = mem [p ].hh .v.RH ;
  if ( ! ( l >= himemmin ) ) {
      
    if ( mem [l ].hh.b0 == 6 ) 
    l = l + 1 ;
    else return Result ;
  } 
  if ( ! ( r >= himemmin ) ) {
      
    if ( mem [r ].hh.b0 == 6 ) 
    r = r + 1 ;
    else return Result ;
  } 
  if ( ! ( ( mem [l ].hh.b0 == mem [r ].hh.b0 ) && ( pdffontshrink [mem [
  l ].hh.b0 ]!= 0 ) ) ) 
  return Result ;
  d = getkern ( pdffontshrink [mem [l ].hh.b0 ], mem [l ].hh.b1 , mem [
  r ].hh.b1 ) ;
  Result = roundxnoverd ( mem [p + 1 ].cint - d , getefcode ( mem [l ]
  .hh.b0 , mem [l ].hh.b1 ) , 1000 ) ;
  return Result ;
} 
void 
zdosubstfont ( halfword p , integer exratio ) 
{
  dosubstfont_regmem 
  internalfontnumber f, k  ;
  halfword r  ;
  integer ef  ;
  if ( ! ( p >= himemmin ) && ( mem [p ].hh.b0 == 7 ) ) 
  {
    r = mem [p + 1 ].hh .v.LH ;
    while ( r != -268435455L ) {
	
      if ( ( r >= himemmin ) || ( mem [r ].hh.b0 == 6 ) ) 
      dosubstfont ( r , exratio ) ;
      r = mem [r ].hh .v.RH ;
    } 
    r = mem [p + 1 ].hh .v.RH ;
    while ( r != -268435455L ) {
	
      if ( ( r >= himemmin ) || ( mem [r ].hh.b0 == 6 ) ) 
      dosubstfont ( r , exratio ) ;
      r = mem [r ].hh .v.RH ;
    } 
    return ;
  } 
  if ( ( p >= himemmin ) ) 
  r = p ;
  else if ( mem [p ].hh.b0 == 6 ) 
  r = p + 1 ;
  else {
      
    pdferror ( 1031 , 1241 ) ;
  } 
  f = mem [r ].hh.b0 ;
  ef = getefcode ( f , mem [r ].hh.b1 ) ;
  if ( ef == 0 ) 
  return ;
  if ( ( pdffontstretch [f ]!= 0 ) && ( exratio > 0 ) ) 
  k = expandfont ( f , extxnoverd ( exratio * ef , pdffontexpandratio [
  pdffontstretch [f ]], 1000000L ) ) ;
  else if ( ( pdffontshrink [f ]!= 0 ) && ( exratio < 0 ) ) 
  k = expandfont ( f , extxnoverd ( exratio * ef , - (integer) 
  pdffontexpandratio [pdffontshrink [f ]], 1000000L ) ) ;
  else k = f ;
  if ( k != f ) 
  {
    mem [r ].hh.b0 = k ;
    if ( ! ( p >= himemmin ) ) 
    {
      r = mem [p + 1 ].hh .v.RH ;
      while ( r != -268435455L ) {
	  
	mem [r ].hh.b0 = k ;
	r = mem [r ].hh .v.RH ;
      } 
    } 
  } 
} 
scaled 
zcharpw ( halfword p , smallnumber side ) 
{
  register scaled Result; charpw_regmem 
  internalfontnumber f  ;
  integer c  ;
  Result = 0 ;
  if ( side == 0 ) 
  lastleftmostchar = -268435455L ;
  else lastrightmostchar = -268435455L ;
  if ( p == -268435455L ) 
  return Result ;
  if ( ! ( p >= himemmin ) ) 
  {
    if ( mem [p ].hh.b0 == 6 ) 
    p = p + 1 ;
    else return Result ;
  } 
  f = mem [p ].hh.b0 ;
  if ( side == 0 ) 
  {
    c = getlpcode ( f , mem [p ].hh.b1 ) ;
    lastleftmostchar = p ;
  } 
  else {
      
    c = getrpcode ( f , mem [p ].hh.b1 ) ;
    lastrightmostchar = p ;
  } 
  if ( c == 0 ) 
  return Result ;
  Result = roundxnoverd ( fontinfo [6 + parambase [f ]].cint , c , 1000 ) 
  ;
  return Result ;
} 
halfword 
znewmarginkern ( scaled w , halfword p , smallnumber side ) 
{
  register halfword Result; newmarginkern_regmem 
  halfword k  ;
  k = getnode ( 3 ) ;
  mem [k ].hh.b0 = 40 ;
  mem [k ].hh.b1 = side ;
  mem [k + 1 ].cint = w ;
  if ( p == -268435455L ) 
  pdferror ( 1242 , 1243 ) ;
  {
    mem [k + 2 ].hh .v.LH = avail ;
    if ( mem [k + 2 ].hh .v.LH == -268435455L ) 
    mem [k + 2 ].hh .v.LH = getavail () ;
    else {
	
      avail = mem [mem [k + 2 ].hh .v.LH ].hh .v.RH ;
      mem [mem [k + 2 ].hh .v.LH ].hh .v.RH = -268435455L ;
	;
#ifdef STAT
      incr ( dynused ) ;
#endif /* STAT */
    } 
  } 
  mem [mem [k + 2 ].hh .v.LH ].hh.b1 = mem [p ].hh.b1 ;
  mem [mem [k + 2 ].hh .v.LH ].hh.b0 = mem [p ].hh.b0 ;
  Result = k ;
  return Result ;
} 
halfword 
zhpack ( halfword p , scaled w , smallnumber m ) 
{
  /* 21 50 10 */ register halfword Result; hpack_regmem 
  halfword r  ;
  halfword q  ;
  scaled h, d, x  ;
  scaled s  ;
  halfword g  ;
  glueord o  ;
  internalfontnumber f  ;
  fourquarters i  ;
  eightbits hd  ;
  scaled fontstretch  ;
  scaled fontshrink  ;
  scaled k  ;
  lastbadness = 0 ;
  r = getnode ( 7 ) ;
  mem [r ].hh.b0 = 0 ;
  mem [r ].hh.b1 = 0 ;
  mem [r + 4 ].cint = 0 ;
  q = r + 5 ;
  mem [q ].hh .v.RH = p ;
  if ( m == 2 ) 
  {
    prevcharp = -268435455L ;
    fontstretch = 0 ;
    fontshrink = 0 ;
    fontexpandratio = 0 ;
  } 
  h = 0 ;
  d = 0 ;
  x = 0 ;
  totalstretch [0 ]= 0 ;
  totalshrink [0 ]= 0 ;
  totalstretch [1 ]= 0 ;
  totalshrink [1 ]= 0 ;
  totalstretch [2 ]= 0 ;
  totalshrink [2 ]= 0 ;
  totalstretch [3 ]= 0 ;
  totalshrink [3 ]= 0 ;
  if ( ( eqtb [29374 ].cint > 0 ) ) 
  {
    tempptr = getavail () ;
    mem [tempptr ].hh .v.LH = 0 ;
    mem [tempptr ].hh .v.RH = LRptr ;
    LRptr = tempptr ;
  } 
  while ( p != -268435455L ) {
      
    lab21: while ( ( p >= himemmin ) ) {
	
      if ( m >= 2 ) 
      {
	prevcharp = p ;
	switch ( m ) 
	{case 2 : 
	  {
	    f = mem [p ].hh.b0 ;
	    fontstretch = fontstretch + charstretch ( f , mem [p ].hh.b1 ) ;
	    fontshrink = fontshrink + charshrink ( f , mem [p ].hh.b1 ) ;
	  } 
	  break ;
	case 3 : 
	  dosubstfont ( p , fontexpandratio ) ;
	  break ;
	} 
      } 
      f = mem [p ].hh.b0 ;
      i = fontinfo [charbase [f ]+ effectivechar ( true , f , mem [p ]
      .hh.b1 ) ].qqqq ;
      hd = i .b1 ;
      x = x + fontinfo [widthbase [f ]+ i .b0 ].cint ;
      s = fontinfo [heightbase [f ]+ ( hd ) / 16 ].cint ;
      if ( s > h ) 
      h = s ;
      s = fontinfo [depthbase [f ]+ ( hd ) % 16 ].cint ;
      if ( s > d ) 
      d = s ;
      p = mem [p ].hh .v.RH ;
    } 
    if ( p != -268435455L ) 
    {
      switch ( mem [p ].hh.b0 ) 
      {case 0 : 
      case 1 : 
      case 2 : 
      case 13 : 
	{
	  x = x + mem [p + 1 ].cint ;
	  if ( mem [p ].hh.b0 >= 2 ) 
	  s = 0 ;
	  else s = mem [p + 4 ].cint ;
	  if ( mem [p + 3 ].cint - s > h ) 
	  h = mem [p + 3 ].cint - s ;
	  if ( mem [p + 2 ].cint + s > d ) 
	  d = mem [p + 2 ].cint + s ;
	} 
	break ;
      case 3 : 
      case 4 : 
      case 5 : 
	if ( ( adjusttail != -268435455L ) || ( preadjusttail != -268435455L ) 
	) 
	{
	  while ( mem [q ].hh .v.RH != p ) q = mem [q ].hh .v.RH ;
	  if ( mem [p ].hh.b0 == 5 ) 
	  {
	    if ( mem [p ].hh.b1 != 0 ) 
	    {
	      if ( preadjusttail == -268435455L ) 
	      confusion ( 1244 ) ;
	      mem [preadjusttail ].hh .v.RH = mem [p + 1 ].cint ;
	      while ( mem [preadjusttail ].hh .v.RH != -268435455L ) 
	      preadjusttail = mem [preadjusttail ].hh .v.RH ;
	    } 
	    else {
		
	      if ( adjusttail == -268435455L ) 
	      confusion ( 1244 ) ;
	      mem [adjusttail ].hh .v.RH = mem [p + 1 ].cint ;
	      while ( mem [adjusttail ].hh .v.RH != -268435455L ) adjusttail 
	      = mem [adjusttail ].hh .v.RH ;
	    } 
	    p = mem [p ].hh .v.RH ;
	    freenode ( mem [q ].hh .v.RH , 2 ) ;
	  } 
	  else {
	      
	    mem [adjusttail ].hh .v.RH = p ;
	    adjusttail = p ;
	    p = mem [p ].hh .v.RH ;
	  } 
	  mem [q ].hh .v.RH = p ;
	  p = q ;
	} 
	break ;
      case 8 : 
	if ( ( mem [p ].hh.b1 == 10 ) || ( mem [p ].hh.b1 == 12 ) ) 
	{
	  x = x + mem [p + 1 ].cint ;
	  s = 0 ;
	  if ( mem [p + 2 ].cint - s > h ) 
	  h = mem [p + 2 ].cint - s ;
	  if ( mem [p + 3 ].cint + s > d ) 
	  d = mem [p + 3 ].cint + s ;
	} 
	break ;
      case 10 : 
	{
	  g = mem [p + 1 ].hh .v.LH ;
	  x = x + mem [g + 1 ].cint ;
	  o = mem [g ].hh.b0 ;
	  totalstretch [o ]= totalstretch [o ]+ mem [g + 2 ].cint ;
	  o = mem [g ].hh.b1 ;
	  totalshrink [o ]= totalshrink [o ]+ mem [g + 3 ].cint ;
	  if ( mem [p ].hh.b1 >= 100 ) 
	  {
	    g = mem [p + 1 ].hh .v.RH ;
	    if ( mem [g + 3 ].cint > h ) 
	    h = mem [g + 3 ].cint ;
	    if ( mem [g + 2 ].cint > d ) 
	    d = mem [g + 2 ].cint ;
	  } 
	} 
	break ;
      case 40 : 
	{
	  if ( m == 2 ) 
	  {
	    f = mem [mem [p + 2 ].hh .v.LH ].hh.b0 ;
	    dosubstfont ( mem [p + 2 ].hh .v.LH , 1000 ) ;
	    if ( f != mem [mem [p + 2 ].hh .v.LH ].hh.b0 ) 
	    fontstretch = fontstretch - mem [p + 1 ].cint - charpw ( mem [p 
	    + 2 ].hh .v.LH , mem [p ].hh.b1 ) ;
	    mem [mem [p + 2 ].hh .v.LH ].hh.b0 = f ;
	    dosubstfont ( mem [p + 2 ].hh .v.LH , -1000 ) ;
	    if ( f != mem [mem [p + 2 ].hh .v.LH ].hh.b0 ) 
	    fontshrink = fontshrink - mem [p + 1 ].cint - charpw ( mem [p + 
	    2 ].hh .v.LH , mem [p ].hh.b1 ) ;
	    mem [mem [p + 2 ].hh .v.LH ].hh.b0 = f ;
	  } 
	  else if ( m == 3 ) 
	  {
	    dosubstfont ( mem [p + 2 ].hh .v.LH , fontexpandratio ) ;
	    mem [p + 1 ].cint = - (integer) charpw ( mem [p + 2 ].hh .v.LH 
	    , mem [p ].hh.b1 ) ;
	  } 
	  x = x + mem [p + 1 ].cint ;
	} 
	break ;
      case 11 : 
	{
	  if ( mem [p ].hh.b1 == 0 ) 
	  {
	    if ( m == 2 ) 
	    {
	      fontstretch = fontstretch + kernstretch ( p ) ;
	      fontshrink = fontshrink + kernshrink ( p ) ;
	    } 
	    else if ( m == 3 ) 
	    {
	      if ( fontexpandratio > 0 ) 
	      k = kernstretch ( p ) ;
	      else if ( fontexpandratio < 0 ) 
	      k = kernshrink ( p ) ;
	      else pdfassert ( 0 ) ;
	      if ( k != 0 ) 
	      {
		if ( ( mem [p ].hh .v.RH >= himemmin ) ) 
		mem [p + 1 ].cint = getkern ( mem [prevcharp ].hh.b0 , mem 
		[prevcharp ].hh.b1 , mem [mem [p ].hh .v.RH ].hh.b1 ) ;
		else if ( mem [mem [p ].hh .v.RH ].hh.b0 == 6 ) 
		mem [p + 1 ].cint = getkern ( mem [prevcharp ].hh.b0 , mem 
		[prevcharp ].hh.b1 , mem [mem [p ].hh .v.RH + 1 ].hh.b1 
		) ;
	      } 
	    } 
	  } 
	  x = x + mem [p + 1 ].cint ;
	} 
	break ;
      case 9 : 
	{
	  x = x + mem [p + 1 ].cint ;
	  if ( ( eqtb [29374 ].cint > 0 ) ) {
	      
	    if ( odd ( mem [p ].hh.b1 ) ) {
		
	      if ( mem [LRptr ].hh .v.LH == ( 4 * ( mem [p ].hh.b1 / 4 ) + 
	      3 ) ) 
	      {
		tempptr = LRptr ;
		LRptr = mem [tempptr ].hh .v.RH ;
		{
		  mem [tempptr ].hh .v.RH = avail ;
		  avail = tempptr ;
	;
#ifdef STAT
		  decr ( dynused ) ;
#endif /* STAT */
		} 
	      } 
	      else {
		  
		incr ( LRproblems ) ;
		mem [p ].hh.b0 = 11 ;
		mem [p ].hh.b1 = 1 ;
	      } 
	    } 
	    else {
		
	      tempptr = getavail () ;
	      mem [tempptr ].hh .v.LH = ( 4 * ( mem [p ].hh.b1 / 4 ) + 3 ) 
	      ;
	      mem [tempptr ].hh .v.RH = LRptr ;
	      LRptr = tempptr ;
	    } 
	  } 
	} 
	break ;
      case 6 : 
	{
	  if ( m == 3 ) 
	  dosubstfont ( p , fontexpandratio ) ;
	  {
	    mem [memtop - 12 ]= mem [p + 1 ];
	    mem [memtop - 12 ].hh .v.RH = mem [p ].hh .v.RH ;
	    p = memtop - 12 ;
	    goto lab21 ;
	  } 
	} 
	break ;
      case 7 : 
	if ( m == 3 ) 
	dosubstfont ( p , fontexpandratio ) ;
	break ;
	default: 
	;
	break ;
      } 
      p = mem [p ].hh .v.RH ;
    } 
  } 
  if ( adjusttail != -268435455L ) 
  mem [adjusttail ].hh .v.RH = -268435455L ;
  if ( preadjusttail != -268435455L ) 
  mem [preadjusttail ].hh .v.RH = -268435455L ;
  mem [r + 3 ].cint = h ;
  mem [r + 2 ].cint = d ;
  if ( m == 1 ) 
  w = x + w ;
  mem [r + 1 ].cint = w ;
  x = w - x ;
  if ( x == 0 ) 
  {
    mem [r + 5 ].hh.b0 = 0 ;
    mem [r + 5 ].hh.b1 = 0 ;
    mem [r + 6 ].gr = 0.0 ;
    goto lab10 ;
  } 
  else if ( x > 0 ) 
  {
    if ( totalstretch [3 ]!= 0 ) 
    o = 3 ;
    else if ( totalstretch [2 ]!= 0 ) 
    o = 2 ;
    else if ( totalstretch [1 ]!= 0 ) 
    o = 1 ;
    else o = 0 ;
    if ( ( m == 2 ) && ( o == 0 ) && ( fontstretch > 0 ) ) 
    {
      fontexpandratio = dividescaled ( x , fontstretch , 3 ) ;
      goto lab10 ;
    } 
    mem [r + 5 ].hh.b1 = o ;
    mem [r + 5 ].hh.b0 = 1 ;
    if ( totalstretch [o ]!= 0 ) 
    mem [r + 6 ].gr = x / ((double) totalstretch [o ]) ;
    else {
	
      mem [r + 5 ].hh.b0 = 0 ;
      mem [r + 6 ].gr = 0.0 ;
    } 
    if ( o == 0 ) {
	
      if ( mem [r + 5 ].hh .v.RH != -268435455L ) 
      {
	lastbadness = badness ( x , totalstretch [0 ]) ;
	if ( lastbadness > eqtb [29300 ].cint ) 
	{
	  println () ;
	  if ( lastbadness > 100 ) 
	  printnl ( 1245 ) ;
	  else printnl ( 1246 ) ;
	  print ( 1247 ) ;
	  printint ( lastbadness ) ;
	  goto lab50 ;
	} 
      } 
    } 
    goto lab10 ;
  } 
  else {
      
    if ( totalshrink [3 ]!= 0 ) 
    o = 3 ;
    else if ( totalshrink [2 ]!= 0 ) 
    o = 2 ;
    else if ( totalshrink [1 ]!= 0 ) 
    o = 1 ;
    else o = 0 ;
    if ( ( m == 2 ) && ( o == 0 ) && ( fontshrink > 0 ) ) 
    {
      fontexpandratio = dividescaled ( x , fontshrink , 3 ) ;
      goto lab10 ;
    } 
    mem [r + 5 ].hh.b1 = o ;
    mem [r + 5 ].hh.b0 = 2 ;
    if ( totalshrink [o ]!= 0 ) 
    mem [r + 6 ].gr = ( - (integer) x ) / ((double) totalshrink [o ]) ;
    else {
	
      mem [r + 5 ].hh.b0 = 0 ;
      mem [r + 6 ].gr = 0.0 ;
    } 
    if ( ( totalshrink [o ]< - (integer) x ) && ( o == 0 ) && ( mem [r + 5 
    ].hh .v.RH != -268435455L ) ) 
    {
      lastbadness = 1000000L ;
      mem [r + 6 ].gr = 1.0 ;
      if ( ( - (integer) x - totalshrink [0 ]> eqtb [29895 ].cint ) || ( 
      eqtb [29300 ].cint < 100 ) ) 
      {
	if ( ( eqtb [29903 ].cint > 0 ) && ( - (integer) x - totalshrink [0 
	]> eqtb [29895 ].cint ) ) 
	{
	  while ( mem [q ].hh .v.RH != -268435455L ) q = mem [q ].hh .v.RH 
	  ;
	  mem [q ].hh .v.RH = newrule () ;
	  mem [mem [q ].hh .v.RH + 1 ].cint = eqtb [29903 ].cint ;
	} 
	println () ;
	printnl ( 1253 ) ;
	printscaled ( - (integer) x - totalshrink [0 ]) ;
	print ( 1254 ) ;
	goto lab50 ;
      } 
    } 
    else if ( o == 0 ) {
	
      if ( mem [r + 5 ].hh .v.RH != -268435455L ) 
      {
	lastbadness = badness ( - (integer) x , totalshrink [0 ]) ;
	if ( lastbadness > eqtb [29300 ].cint ) 
	{
	  println () ;
	  printnl ( 1255 ) ;
	  printint ( lastbadness ) ;
	  goto lab50 ;
	} 
      } 
    } 
    goto lab10 ;
  } 
  lab50: if ( outputactive ) 
  print ( 1248 ) ;
  else {
      
    if ( packbeginline != 0 ) 
    {
      if ( packbeginline > 0 ) 
      print ( 1249 ) ;
      else print ( 1250 ) ;
      printint ( abs ( packbeginline ) ) ;
      print ( 1251 ) ;
    } 
    else print ( 1252 ) ;
    printint ( line ) ;
  } 
  println () ;
  fontinshortdisplay = 0 ;
  shortdisplay ( mem [r + 5 ].hh .v.RH ) ;
  println () ;
  begindiagnostic () ;
  showbox ( r ) ;
  enddiagnostic ( true ) ;
  lab10: if ( ( eqtb [29374 ].cint > 0 ) ) 
  {
    if ( mem [LRptr ].hh .v.LH != 0 ) 
    {
      while ( mem [q ].hh .v.RH != -268435455L ) q = mem [q ].hh .v.RH ;
      do {
	  tempptr = q ;
	q = newmath ( 0 , mem [LRptr ].hh .v.LH ) ;
	mem [tempptr ].hh .v.RH = q ;
	LRproblems = LRproblems + 10000 ;
	{
	  tempptr = LRptr ;
	  LRptr = mem [tempptr ].hh .v.RH ;
	  {
	    mem [tempptr ].hh .v.RH = avail ;
	    avail = tempptr ;
	;
#ifdef STAT
	    decr ( dynused ) ;
#endif /* STAT */
	  } 
	} 
      } while ( ! ( mem [LRptr ].hh .v.LH == 0 ) ) ;
    } 
    if ( LRproblems > 0 ) 
    {
      {
	println () ;
	printnl ( 2008 ) ;
	printint ( LRproblems / 10000 ) ;
	print ( 2009 ) ;
	printint ( LRproblems % 10000 ) ;
	print ( 2010 ) ;
	LRproblems = 0 ;
      } 
      goto lab50 ;
    } 
    {
      tempptr = LRptr ;
      LRptr = mem [tempptr ].hh .v.RH ;
      {
	mem [tempptr ].hh .v.RH = avail ;
	avail = tempptr ;
	;
#ifdef STAT
	decr ( dynused ) ;
#endif /* STAT */
      } 
    } 
    if ( LRptr != -268435455L ) 
    confusion ( 2007 ) ;
  } 
  if ( ( m == 2 ) && ( fontexpandratio != 0 ) ) 
  {
    fontexpandratio = fixint ( fontexpandratio , -1000 , 1000 ) ;
    q = mem [r + 5 ].hh .v.RH ;
    freenode ( r , 7 ) ;
    r = hpack ( q , w , 3 ) ;
  } 
  Result = r ;
  return Result ;
} 
halfword 
zvpackage ( halfword p , scaled h , smallnumber m , scaled l ) 
{
  /* 50 10 */ register halfword Result; vpackage_regmem 
  halfword r  ;
  scaled w, d, x  ;
  scaled s  ;
  halfword g  ;
  glueord o  ;
  lastbadness = 0 ;
  r = getnode ( 7 ) ;
  mem [r ].hh.b0 = 1 ;
  mem [r ].hh.b1 = 0 ;
  mem [r + 4 ].cint = 0 ;
  mem [r + 5 ].hh .v.RH = p ;
  w = 0 ;
  d = 0 ;
  x = 0 ;
  totalstretch [0 ]= 0 ;
  totalshrink [0 ]= 0 ;
  totalstretch [1 ]= 0 ;
  totalshrink [1 ]= 0 ;
  totalstretch [2 ]= 0 ;
  totalshrink [2 ]= 0 ;
  totalstretch [3 ]= 0 ;
  totalshrink [3 ]= 0 ;
  while ( p != -268435455L ) {
      
    if ( ( p >= himemmin ) ) 
    confusion ( 1256 ) ;
    else switch ( mem [p ].hh.b0 ) 
    {case 0 : 
    case 1 : 
    case 2 : 
    case 13 : 
      {
	x = x + d + mem [p + 3 ].cint ;
	d = mem [p + 2 ].cint ;
	if ( mem [p ].hh.b0 >= 2 ) 
	s = 0 ;
	else s = mem [p + 4 ].cint ;
	if ( mem [p + 1 ].cint + s > w ) 
	w = mem [p + 1 ].cint + s ;
      } 
      break ;
    case 8 : 
      if ( ( mem [p ].hh.b1 == 10 ) || ( mem [p ].hh.b1 == 12 ) ) 
      {
	x = x + d + mem [p + 2 ].cint ;
	d = mem [p + 3 ].cint ;
	s = 0 ;
	if ( mem [p + 1 ].cint + s > w ) 
	w = mem [p + 1 ].cint + s ;
      } 
      break ;
    case 10 : 
      {
	x = x + d ;
	d = 0 ;
	g = mem [p + 1 ].hh .v.LH ;
	x = x + mem [g + 1 ].cint ;
	o = mem [g ].hh.b0 ;
	totalstretch [o ]= totalstretch [o ]+ mem [g + 2 ].cint ;
	o = mem [g ].hh.b1 ;
	totalshrink [o ]= totalshrink [o ]+ mem [g + 3 ].cint ;
	if ( mem [p ].hh.b1 >= 100 ) 
	{
	  g = mem [p + 1 ].hh .v.RH ;
	  if ( mem [g + 1 ].cint > w ) 
	  w = mem [g + 1 ].cint ;
	} 
      } 
      break ;
    case 11 : 
      {
	x = x + d + mem [p + 1 ].cint ;
	d = 0 ;
      } 
      break ;
      default: 
      ;
      break ;
    } 
    p = mem [p ].hh .v.RH ;
  } 
  mem [r + 1 ].cint = w ;
  if ( d > l ) 
  {
    x = x + d - l ;
    mem [r + 2 ].cint = l ;
  } 
  else mem [r + 2 ].cint = d ;
  if ( m == 1 ) 
  h = x + h ;
  mem [r + 3 ].cint = h ;
  x = h - x ;
  if ( x == 0 ) 
  {
    mem [r + 5 ].hh.b0 = 0 ;
    mem [r + 5 ].hh.b1 = 0 ;
    mem [r + 6 ].gr = 0.0 ;
    goto lab10 ;
  } 
  else if ( x > 0 ) 
  {
    if ( totalstretch [3 ]!= 0 ) 
    o = 3 ;
    else if ( totalstretch [2 ]!= 0 ) 
    o = 2 ;
    else if ( totalstretch [1 ]!= 0 ) 
    o = 1 ;
    else o = 0 ;
    mem [r + 5 ].hh.b1 = o ;
    mem [r + 5 ].hh.b0 = 1 ;
    if ( totalstretch [o ]!= 0 ) 
    mem [r + 6 ].gr = x / ((double) totalstretch [o ]) ;
    else {
	
      mem [r + 5 ].hh.b0 = 0 ;
      mem [r + 6 ].gr = 0.0 ;
    } 
    if ( o == 0 ) {
	
      if ( mem [r + 5 ].hh .v.RH != -268435455L ) 
      {
	lastbadness = badness ( x , totalstretch [0 ]) ;
	if ( lastbadness > eqtb [29301 ].cint ) 
	{
	  println () ;
	  if ( lastbadness > 100 ) 
	  printnl ( 1245 ) ;
	  else printnl ( 1246 ) ;
	  print ( 1257 ) ;
	  printint ( lastbadness ) ;
	  goto lab50 ;
	} 
      } 
    } 
    goto lab10 ;
  } 
  else {
      
    if ( totalshrink [3 ]!= 0 ) 
    o = 3 ;
    else if ( totalshrink [2 ]!= 0 ) 
    o = 2 ;
    else if ( totalshrink [1 ]!= 0 ) 
    o = 1 ;
    else o = 0 ;
    mem [r + 5 ].hh.b1 = o ;
    mem [r + 5 ].hh.b0 = 2 ;
    if ( totalshrink [o ]!= 0 ) 
    mem [r + 6 ].gr = ( - (integer) x ) / ((double) totalshrink [o ]) ;
    else {
	
      mem [r + 5 ].hh.b0 = 0 ;
      mem [r + 6 ].gr = 0.0 ;
    } 
    if ( ( totalshrink [o ]< - (integer) x ) && ( o == 0 ) && ( mem [r + 5 
    ].hh .v.RH != -268435455L ) ) 
    {
      lastbadness = 1000000L ;
      mem [r + 6 ].gr = 1.0 ;
      if ( ( - (integer) x - totalshrink [0 ]> eqtb [29896 ].cint ) || ( 
      eqtb [29301 ].cint < 100 ) ) 
      {
	println () ;
	printnl ( 1258 ) ;
	printscaled ( - (integer) x - totalshrink [0 ]) ;
	print ( 1259 ) ;
	goto lab50 ;
      } 
    } 
    else if ( o == 0 ) {
	
      if ( mem [r + 5 ].hh .v.RH != -268435455L ) 
      {
	lastbadness = badness ( - (integer) x , totalshrink [0 ]) ;
	if ( lastbadness > eqtb [29301 ].cint ) 
	{
	  println () ;
	  printnl ( 1260 ) ;
	  printint ( lastbadness ) ;
	  goto lab50 ;
	} 
      } 
    } 
    goto lab10 ;
  } 
  lab50: if ( outputactive ) 
  print ( 1248 ) ;
  else {
      
    if ( packbeginline != 0 ) 
    {
      print ( 1250 ) ;
      printint ( abs ( packbeginline ) ) ;
      print ( 1251 ) ;
    } 
    else print ( 1252 ) ;
    printint ( line ) ;
    println () ;
  } 
  begindiagnostic () ;
  showbox ( r ) ;
  enddiagnostic ( true ) ;
  lab10: Result = r ;
  return Result ;
} 
void 
zappendtovlist ( halfword b ) 
{
  appendtovlist_regmem 
  scaled d  ;
  halfword p  ;
  if ( curlist .auxfield .cint > eqtb [29919 ].cint ) 
  {
    d = mem [eqtb [26629 ].hh .v.RH + 1 ].cint - curlist .auxfield .cint - 
    mem [b + 3 ].cint ;
    if ( d < eqtb [29889 ].cint ) 
    p = newparamglue ( 0 ) ;
    else {
	
      p = newskipparam ( 1 ) ;
      mem [tempptr + 1 ].cint = d ;
    } 
    mem [curlist .tailfield ].hh .v.RH = p ;
    curlist .tailfield = p ;
  } 
  mem [curlist .tailfield ].hh .v.RH = b ;
  curlist .tailfield = b ;
  curlist .auxfield .cint = mem [b + 2 ].cint ;
} 
halfword 
newnoad ( void ) 
{
  register halfword Result; newnoad_regmem 
  halfword p  ;
  p = getnode ( 4 ) ;
  mem [p ].hh.b0 = 16 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].hh = emptyfield ;
  mem [p + 3 ].hh = emptyfield ;
  mem [p + 2 ].hh = emptyfield ;
  Result = p ;
  return Result ;
} 
halfword 
znewstyle ( smallnumber s ) 
{
  register halfword Result; newstyle_regmem 
  halfword p  ;
  p = getnode ( 3 ) ;
  mem [p ].hh.b0 = 14 ;
  mem [p ].hh.b1 = s ;
  mem [p + 1 ].cint = 0 ;
  mem [p + 2 ].cint = 0 ;
  Result = p ;
  return Result ;
} 
halfword 
newchoice ( void ) 
{
  register halfword Result; newchoice_regmem 
  halfword p  ;
  p = getnode ( 3 ) ;
  mem [p ].hh.b0 = 15 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].hh .v.LH = -268435455L ;
  mem [p + 1 ].hh .v.RH = -268435455L ;
  mem [p + 2 ].hh .v.LH = -268435455L ;
  mem [p + 2 ].hh .v.RH = -268435455L ;
  Result = p ;
  return Result ;
} 
void 
showinfo ( void ) 
{
  showinfo_regmem 
  shownodelist ( mem [tempptr ].hh .v.LH ) ;
} 
halfword 
zfractionrule ( scaled t ) 
{
  register halfword Result; fractionrule_regmem 
  halfword p  ;
  p = newrule () ;
  mem [p + 3 ].cint = t ;
  mem [p + 2 ].cint = 0 ;
  Result = p ;
  return Result ;
} 
halfword 
zoverbar ( halfword b , scaled k , scaled t ) 
{
  register halfword Result; overbar_regmem 
  halfword p, q  ;
  p = newkern ( k ) ;
  mem [p ].hh .v.RH = b ;
  q = fractionrule ( t ) ;
  mem [q ].hh .v.RH = p ;
  p = newkern ( t ) ;
  mem [p ].hh .v.RH = q ;
  Result = vpackage ( p , 0 , 1 , 1073741823L ) ;
  return Result ;
} 
halfword 
zcharbox ( internalfontnumber f , quarterword c ) 
{
  register halfword Result; charbox_regmem 
  fourquarters q  ;
  eightbits hd  ;
  halfword b, p  ;
  q = fontinfo [charbase [f ]+ effectivechar ( true , f , c ) ].qqqq ;
  hd = q .b1 ;
  b = newnullbox () ;
  mem [b + 1 ].cint = fontinfo [widthbase [f ]+ q .b0 ].cint + fontinfo 
  [italicbase [f ]+ ( q .b2 ) / 4 ].cint ;
  mem [b + 3 ].cint = fontinfo [heightbase [f ]+ ( hd ) / 16 ].cint ;
  mem [b + 2 ].cint = fontinfo [depthbase [f ]+ ( hd ) % 16 ].cint ;
  p = getavail () ;
  mem [p ].hh.b1 = c ;
  mem [p ].hh.b0 = f ;
  mem [b + 5 ].hh .v.RH = p ;
  Result = b ;
  return Result ;
} 
void 
zstackintobox ( halfword b , internalfontnumber f , quarterword c ) 
{
  stackintobox_regmem 
  halfword p  ;
  p = charbox ( f , c ) ;
  mem [p ].hh .v.RH = mem [b + 5 ].hh .v.RH ;
  mem [b + 5 ].hh .v.RH = p ;
  mem [b + 3 ].cint = mem [p + 3 ].cint ;
} 
scaled 
zheightplusdepth ( internalfontnumber f , quarterword c ) 
{
  register scaled Result; heightplusdepth_regmem 
  fourquarters q  ;
  eightbits hd  ;
  q = fontinfo [charbase [f ]+ effectivechar ( true , f , c ) ].qqqq ;
  hd = q .b1 ;
  Result = fontinfo [heightbase [f ]+ ( hd ) / 16 ].cint + fontinfo [
  depthbase [f ]+ ( hd ) % 16 ].cint ;
  return Result ;
} 
halfword 
zvardelimiter ( halfword d , smallnumber s , scaled v ) 
{
  /* 40 22 */ register halfword Result; vardelimiter_regmem 
  halfword b  ;
  internalfontnumber f, g  ;
  quarterword c, x, y  ;
  integer m, n  ;
  scaled u  ;
  scaled w  ;
  fourquarters q  ;
  eightbits hd  ;
  fourquarters r  ;
  smallnumber z  ;
  boolean largeattempt  ;
  f = 0 ;
  w = 0 ;
  largeattempt = false ;
  z = mem [d ].qqqq .b0 ;
  x = mem [d ].qqqq .b1 ;
  while ( true ) {
      
    if ( ( z != 0 ) || ( x != 0 ) ) 
    {
      z = z + s + 16 ;
      do {
	  z = z - 16 ;
	g = eqtb [27690 + z ].hh .v.RH ;
	if ( g != 0 ) 
	{
	  y = x ;
	  if ( ( y >= fontbc [g ]) && ( y <= fontec [g ]) ) 
	  {
	    lab22: q = fontinfo [charbase [g ]+ y ].qqqq ;
	    if ( ( q .b0 > 0 ) ) 
	    {
	      if ( ( ( q .b2 ) % 4 ) == 3 ) 
	      {
		f = g ;
		c = y ;
		goto lab40 ;
	      } 
	      hd = q .b1 ;
	      u = fontinfo [heightbase [g ]+ ( hd ) / 16 ].cint + fontinfo 
	      [depthbase [g ]+ ( hd ) % 16 ].cint ;
	      if ( u > w ) 
	      {
		f = g ;
		c = y ;
		w = u ;
		if ( u >= v ) 
		goto lab40 ;
	      } 
	      if ( ( ( q .b2 ) % 4 ) == 2 ) 
	      {
		y = q .b3 ;
		goto lab22 ;
	      } 
	    } 
	  } 
	} 
      } while ( ! ( z < 16 ) ) ;
    } 
    if ( largeattempt ) 
    goto lab40 ;
    largeattempt = true ;
    z = mem [d ].qqqq .b2 ;
    x = mem [d ].qqqq .b3 ;
  } 
  lab40: if ( f != 0 ) {
      
    if ( ( ( q .b2 ) % 4 ) == 3 ) 
    {
      b = newnullbox () ;
      mem [b ].hh.b0 = 1 ;
      r = fontinfo [extenbase [f ]+ q .b3 ].qqqq ;
      c = r .b3 ;
      u = heightplusdepth ( f , c ) ;
      w = 0 ;
      q = fontinfo [charbase [f ]+ effectivechar ( true , f , c ) ].qqqq ;
      mem [b + 1 ].cint = fontinfo [widthbase [f ]+ q .b0 ].cint + 
      fontinfo [italicbase [f ]+ ( q .b2 ) / 4 ].cint ;
      c = r .b2 ;
      if ( c != 0 ) 
      w = w + heightplusdepth ( f , c ) ;
      c = r .b1 ;
      if ( c != 0 ) 
      w = w + heightplusdepth ( f , c ) ;
      c = r .b0 ;
      if ( c != 0 ) 
      w = w + heightplusdepth ( f , c ) ;
      n = 0 ;
      if ( u > 0 ) 
      while ( w < v ) {
	  
	w = w + u ;
	incr ( n ) ;
	if ( r .b1 != 0 ) 
	w = w + u ;
      } 
      c = r .b2 ;
      if ( c != 0 ) 
      stackintobox ( b , f , c ) ;
      c = r .b3 ;
      {register integer for_end; m = 1 ;for_end = n ; if ( m <= for_end) do 
	stackintobox ( b , f , c ) ;
      while ( m++ < for_end ) ;} 
      c = r .b1 ;
      if ( c != 0 ) 
      {
	stackintobox ( b , f , c ) ;
	c = r .b3 ;
	{register integer for_end; m = 1 ;for_end = n ; if ( m <= for_end) 
	do 
	  stackintobox ( b , f , c ) ;
	while ( m++ < for_end ) ;} 
      } 
      c = r .b0 ;
      if ( c != 0 ) 
      stackintobox ( b , f , c ) ;
      mem [b + 2 ].cint = w - mem [b + 3 ].cint ;
    } 
    else b = charbox ( f , c ) ;
  } 
  else {
      
    b = newnullbox () ;
    mem [b + 1 ].cint = eqtb [29898 ].cint ;
  } 
  mem [b + 4 ].cint = half ( mem [b + 3 ].cint - mem [b + 2 ].cint ) - 
  fontinfo [22 + parambase [eqtb [27692 + s ].hh .v.RH ]].cint ;
  Result = b ;
  return Result ;
} 
halfword 
zrebox ( halfword b , scaled w ) 
{
  register halfword Result; rebox_regmem 
  halfword p  ;
  internalfontnumber f  ;
  scaled v  ;
  if ( ( mem [b + 1 ].cint != w ) && ( mem [b + 5 ].hh .v.RH != 
  -268435455L ) ) 
  {
    if ( mem [b ].hh.b0 == 1 ) 
    b = hpack ( b , 0 , 1 ) ;
    p = mem [b + 5 ].hh .v.RH ;
    if ( ( ( p >= himemmin ) ) && ( mem [p ].hh .v.RH == -268435455L ) ) 
    {
      f = mem [p ].hh.b0 ;
      v = fontinfo [widthbase [f ]+ fontinfo [charbase [f ]+ 
      effectivechar ( true , f , mem [p ].hh.b1 ) ].qqqq .b0 ].cint ;
      if ( v != mem [b + 1 ].cint ) 
      mem [p ].hh .v.RH = newkern ( mem [b + 1 ].cint - v ) ;
    } 
    freenode ( b , 7 ) ;
    b = newglue ( membot + 12 ) ;
    mem [b ].hh .v.RH = p ;
    while ( mem [p ].hh .v.RH != -268435455L ) p = mem [p ].hh .v.RH ;
    mem [p ].hh .v.RH = newglue ( membot + 12 ) ;
    Result = hpack ( b , w , 0 ) ;
  } 
  else {
      
    mem [b + 1 ].cint = w ;
    Result = b ;
  } 
  return Result ;
} 
halfword 
zmathglue ( halfword g , scaled m ) 
{
  register halfword Result; mathglue_regmem 
  halfword p  ;
  integer n  ;
  scaled f  ;
  n = xovern ( m , 65536L ) ;
  f = texremainder ;
  if ( f < 0 ) 
  {
    decr ( n ) ;
    f = f + 65536L ;
  } 
  p = getnode ( 4 ) ;
  mem [p + 1 ].cint = multandadd ( n , mem [g + 1 ].cint , xnoverd ( mem [
  g + 1 ].cint , f , 65536L ) , 1073741823L ) ;
  mem [p ].hh.b0 = mem [g ].hh.b0 ;
  if ( mem [p ].hh.b0 == 0 ) 
  mem [p + 2 ].cint = multandadd ( n , mem [g + 2 ].cint , xnoverd ( mem [
  g + 2 ].cint , f , 65536L ) , 1073741823L ) ;
  else mem [p + 2 ].cint = mem [g + 2 ].cint ;
  mem [p ].hh.b1 = mem [g ].hh.b1 ;
  if ( mem [p ].hh.b1 == 0 ) 
  mem [p + 3 ].cint = multandadd ( n , mem [g + 3 ].cint , xnoverd ( mem [
  g + 3 ].cint , f , 65536L ) , 1073741823L ) ;
  else mem [p + 3 ].cint = mem [g + 3 ].cint ;
  Result = p ;
  return Result ;
} 
void 
zmathkern ( halfword p , scaled m ) 
{
  mathkern_regmem 
  integer n  ;
  scaled f  ;
  if ( mem [p ].hh.b1 == 99 ) 
  {
    n = xovern ( m , 65536L ) ;
    f = texremainder ;
    if ( f < 0 ) 
    {
      decr ( n ) ;
      f = f + 65536L ;
    } 
    mem [p + 1 ].cint = multandadd ( n , mem [p + 1 ].cint , xnoverd ( mem 
    [p + 1 ].cint , f , 65536L ) , 1073741823L ) ;
    mem [p ].hh.b1 = 1 ;
  } 
} 
void 
flushmath ( void ) 
{
  flushmath_regmem 
  flushnodelist ( mem [curlist .headfield ].hh .v.RH ) ;
  flushnodelist ( curlist .auxfield .cint ) ;
  mem [curlist .headfield ].hh .v.RH = -268435455L ;
  curlist .tailfield = curlist .headfield ;
  curlist .auxfield .cint = -268435455L ;
} 
halfword 
zcleanbox ( halfword p , smallnumber s ) 
{
  /* 40 */ register halfword Result; cleanbox_regmem 
  halfword q  ;
  smallnumber savestyle  ;
  halfword x  ;
  halfword r  ;
  switch ( mem [p ].hh .v.RH ) 
  {case 1 : 
    {
      curmlist = newnoad () ;
      mem [curmlist + 1 ]= mem [p ];
    } 
    break ;
  case 2 : 
    {
      q = mem [p ].hh .v.LH ;
      goto lab40 ;
    } 
    break ;
  case 3 : 
    curmlist = mem [p ].hh .v.LH ;
    break ;
    default: 
    {
      q = newnullbox () ;
      goto lab40 ;
    } 
    break ;
  } 
  savestyle = curstyle ;
  curstyle = s ;
  mlistpenalties = false ;
  mlisttohlist () ;
  q = mem [memtop - 3 ].hh .v.RH ;
  curstyle = savestyle ;
  {
    if ( curstyle < 4 ) 
    cursize = 0 ;
    else cursize = 16 * ( ( curstyle - 2 ) / 2 ) ;
    curmu = xovern ( fontinfo [6 + parambase [eqtb [27692 + cursize ].hh 
    .v.RH ]].cint , 18 ) ;
  } 
  lab40: if ( ( q >= himemmin ) || ( q == -268435455L ) ) 
  x = hpack ( q , 0 , 1 ) ;
  else if ( ( mem [q ].hh .v.RH == -268435455L ) && ( mem [q ].hh.b0 <= 1 
  ) && ( mem [q + 4 ].cint == 0 ) ) 
  x = q ;
  else x = hpack ( q , 0 , 1 ) ;
  q = mem [x + 5 ].hh .v.RH ;
  if ( ( q >= himemmin ) ) 
  {
    r = mem [q ].hh .v.RH ;
    if ( r != -268435455L ) {
	
      if ( mem [r ].hh .v.RH == -268435455L ) {
	  
	if ( ! ( r >= himemmin ) ) {
	    
	  if ( mem [r ].hh.b0 == 11 ) 
	  {
	    freenode ( r , 2 ) ;
	    mem [q ].hh .v.RH = -268435455L ;
	  } 
	} 
      } 
    } 
  } 
  Result = x ;
  return Result ;
} 
void 
zfetch ( halfword a ) 
{
  fetch_regmem 
  curc = mem [a ].hh.b1 ;
  curf = eqtb [27690 + mem [a ].hh.b0 + cursize ].hh .v.RH ;
  if ( curf == 0 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 345 ) ;
    } 
    printsize ( cursize ) ;
    printchar ( 32 ) ;
    printint ( mem [a ].hh.b0 ) ;
    print ( 1286 ) ;
    print ( curc ) ;
    printchar ( 41 ) ;
    {
      helpptr = 4 ;
      helpline [3 ]= 1287 ;
      helpline [2 ]= 1288 ;
      helpline [1 ]= 1289 ;
      helpline [0 ]= 1290 ;
    } 
    error () ;
    curi = nullcharacter ;
    mem [a ].hh .v.RH = 0 ;
  } 
  else {
      
    if ( ( curc >= fontbc [curf ]) && ( curc <= fontec [curf ]) ) 
    curi = fontinfo [charbase [curf ]+ curc ].qqqq ;
    else curi = nullcharacter ;
    if ( ! ( ( curi .b0 > 0 ) ) ) 
    {
      charwarning ( curf , curc ) ;
      mem [a ].hh .v.RH = 0 ;
    } 
  } 
} 
void 
zmakeover ( halfword q ) 
{
  makeover_regmem 
  mem [q + 1 ].hh .v.LH = overbar ( cleanbox ( q + 1 , 2 * ( curstyle / 2 ) 
  + 1 ) , 3 * fontinfo [8 + parambase [eqtb [27693 + cursize ].hh .v.RH ]
  ].cint , fontinfo [8 + parambase [eqtb [27693 + cursize ].hh .v.RH ]]
  .cint ) ;
  mem [q + 1 ].hh .v.RH = 2 ;
} 
void 
zmakeunder ( halfword q ) 
{
  makeunder_regmem 
  halfword p, x, y  ;
  scaled delta  ;
  x = cleanbox ( q + 1 , curstyle ) ;
  p = newkern ( 3 * fontinfo [8 + parambase [eqtb [27693 + cursize ].hh 
  .v.RH ]].cint ) ;
  mem [x ].hh .v.RH = p ;
  mem [p ].hh .v.RH = fractionrule ( fontinfo [8 + parambase [eqtb [27693 
  + cursize ].hh .v.RH ]].cint ) ;
  y = vpackage ( x , 0 , 1 , 1073741823L ) ;
  delta = mem [y + 3 ].cint + mem [y + 2 ].cint + fontinfo [8 + parambase 
  [eqtb [27693 + cursize ].hh .v.RH ]].cint ;
  mem [y + 3 ].cint = mem [x + 3 ].cint ;
  mem [y + 2 ].cint = delta - mem [y + 3 ].cint ;
  mem [q + 1 ].hh .v.LH = y ;
  mem [q + 1 ].hh .v.RH = 2 ;
} 
void 
zmakevcenter ( halfword q ) 
{
  makevcenter_regmem 
  halfword v  ;
  scaled delta  ;
  v = mem [q + 1 ].hh .v.LH ;
  if ( mem [v ].hh.b0 != 1 ) 
  confusion ( 614 ) ;
  delta = mem [v + 3 ].cint + mem [v + 2 ].cint ;
  mem [v + 3 ].cint = fontinfo [22 + parambase [eqtb [27692 + cursize ]
  .hh .v.RH ]].cint + half ( delta ) ;
  mem [v + 2 ].cint = delta - mem [v + 3 ].cint ;
} 
void 
zmakeradical ( halfword q ) 
{
  makeradical_regmem 
  halfword x, y  ;
  scaled delta, clr  ;
  x = cleanbox ( q + 1 , 2 * ( curstyle / 2 ) + 1 ) ;
  if ( curstyle < 2 ) 
  clr = fontinfo [8 + parambase [eqtb [27693 + cursize ].hh .v.RH ]]
  .cint + ( abs ( fontinfo [5 + parambase [eqtb [27692 + cursize ].hh 
  .v.RH ]].cint ) / 4 ) ;
  else {
      
    clr = fontinfo [8 + parambase [eqtb [27693 + cursize ].hh .v.RH ]]
    .cint ;
    clr = clr + ( abs ( clr ) / 4 ) ;
  } 
  y = vardelimiter ( q + 4 , cursize , mem [x + 3 ].cint + mem [x + 2 ]
  .cint + clr + fontinfo [8 + parambase [eqtb [27693 + cursize ].hh .v.RH 
  ]].cint ) ;
  delta = mem [y + 2 ].cint - ( mem [x + 3 ].cint + mem [x + 2 ].cint + 
  clr ) ;
  if ( delta > 0 ) 
  clr = clr + half ( delta ) ;
  mem [y + 4 ].cint = - (integer) ( mem [x + 3 ].cint + clr ) ;
  mem [y ].hh .v.RH = overbar ( x , clr , mem [y + 3 ].cint ) ;
  mem [q + 1 ].hh .v.LH = hpack ( y , 0 , 1 ) ;
  mem [q + 1 ].hh .v.RH = 2 ;
} 
void 
zmakemathaccent ( halfword q ) 
{
  /* 30 31 */ makemathaccent_regmem 
  halfword p, x, y  ;
  integer a  ;
  quarterword c  ;
  internalfontnumber f  ;
  fourquarters i  ;
  scaled s  ;
  scaled h  ;
  scaled delta  ;
  scaled w  ;
  fetch ( q + 4 ) ;
  if ( ( curi .b0 > 0 ) ) 
  {
    i = curi ;
    c = curc ;
    f = curf ;
    s = 0 ;
    if ( mem [q + 1 ].hh .v.RH == 1 ) 
    {
      fetch ( q + 1 ) ;
      if ( ( ( curi .b2 ) % 4 ) == 1 ) 
      {
	a = ligkernbase [curf ]+ curi .b3 ;
	curi = fontinfo [a ].qqqq ;
	if ( curi .b0 > 128 ) 
	{
	  a = ligkernbase [curf ]+ 256 * curi .b2 + curi .b3 + 32768L - 256 
	  * ( 128 ) ;
	  curi = fontinfo [a ].qqqq ;
	} 
	while ( true ) {
	    
	  if ( curi .b1 == skewchar [curf ]) 
	  {
	    if ( curi .b2 >= 128 ) {
		
	      if ( curi .b0 <= 128 ) 
	      s = fontinfo [kernbase [curf ]+ 256 * curi .b2 + curi .b3 ]
	      .cint ;
	    } 
	    goto lab31 ;
	  } 
	  if ( curi .b0 >= 128 ) 
	  goto lab31 ;
	  a = a + curi .b0 + 1 ;
	  curi = fontinfo [a ].qqqq ;
	} 
      } 
    } 
    lab31: ;
    x = cleanbox ( q + 1 , 2 * ( curstyle / 2 ) + 1 ) ;
    w = mem [x + 1 ].cint ;
    h = mem [x + 3 ].cint ;
    while ( true ) {
	
      if ( ( ( i .b2 ) % 4 ) != 2 ) 
      goto lab30 ;
      y = i .b3 ;
      i = fontinfo [charbase [f ]+ y ].qqqq ;
      if ( ! ( i .b0 > 0 ) ) 
      goto lab30 ;
      if ( fontinfo [widthbase [f ]+ i .b0 ].cint > w ) 
      goto lab30 ;
      c = y ;
    } 
    lab30: ;
    if ( h < fontinfo [5 + parambase [f ]].cint ) 
    delta = h ;
    else delta = fontinfo [5 + parambase [f ]].cint ;
    if ( ( mem [q + 2 ].hh .v.RH != 0 ) || ( mem [q + 3 ].hh .v.RH != 0 ) 
    ) {
	
      if ( mem [q + 1 ].hh .v.RH == 1 ) 
      {
	flushnodelist ( x ) ;
	x = newnoad () ;
	mem [x + 1 ]= mem [q + 1 ];
	mem [x + 2 ]= mem [q + 2 ];
	mem [x + 3 ]= mem [q + 3 ];
	mem [q + 2 ].hh = emptyfield ;
	mem [q + 3 ].hh = emptyfield ;
	mem [q + 1 ].hh .v.RH = 3 ;
	mem [q + 1 ].hh .v.LH = x ;
	x = cleanbox ( q + 1 , curstyle ) ;
	delta = delta + mem [x + 3 ].cint - h ;
	h = mem [x + 3 ].cint ;
      } 
    } 
    y = charbox ( f , c ) ;
    mem [y + 4 ].cint = s + half ( w - mem [y + 1 ].cint ) ;
    mem [y + 1 ].cint = 0 ;
    p = newkern ( - (integer) delta ) ;
    mem [p ].hh .v.RH = x ;
    mem [y ].hh .v.RH = p ;
    y = vpackage ( y , 0 , 1 , 1073741823L ) ;
    mem [y + 1 ].cint = mem [x + 1 ].cint ;
    if ( mem [y + 3 ].cint < h ) 
    {
      p = newkern ( h - mem [y + 3 ].cint ) ;
      mem [p ].hh .v.RH = mem [y + 5 ].hh .v.RH ;
      mem [y + 5 ].hh .v.RH = p ;
      mem [y + 3 ].cint = h ;
    } 
    mem [q + 1 ].hh .v.LH = y ;
    mem [q + 1 ].hh .v.RH = 2 ;
  } 
} 
void 
zmakefraction ( halfword q ) 
{
  makefraction_regmem 
  halfword p, v, x, y, z  ;
  scaled delta, delta1, delta2, shiftup, shiftdown, clr  ;
  if ( mem [q + 1 ].cint == 1073741824L ) 
  mem [q + 1 ].cint = fontinfo [8 + parambase [eqtb [27693 + cursize ]
  .hh .v.RH ]].cint ;
  x = cleanbox ( q + 2 , curstyle + 2 - 2 * ( curstyle / 6 ) ) ;
  z = cleanbox ( q + 3 , 2 * ( curstyle / 2 ) + 3 - 2 * ( curstyle / 6 ) ) ;
  if ( mem [x + 1 ].cint < mem [z + 1 ].cint ) 
  x = rebox ( x , mem [z + 1 ].cint ) ;
  else z = rebox ( z , mem [x + 1 ].cint ) ;
  if ( curstyle < 2 ) 
  {
    shiftup = fontinfo [8 + parambase [eqtb [27692 + cursize ].hh .v.RH ]
    ].cint ;
    shiftdown = fontinfo [11 + parambase [eqtb [27692 + cursize ].hh .v.RH 
    ]].cint ;
  } 
  else {
      
    shiftdown = fontinfo [12 + parambase [eqtb [27692 + cursize ].hh .v.RH 
    ]].cint ;
    if ( mem [q + 1 ].cint != 0 ) 
    shiftup = fontinfo [9 + parambase [eqtb [27692 + cursize ].hh .v.RH ]
    ].cint ;
    else shiftup = fontinfo [10 + parambase [eqtb [27692 + cursize ].hh 
    .v.RH ]].cint ;
  } 
  if ( mem [q + 1 ].cint == 0 ) 
  {
    if ( curstyle < 2 ) 
    clr = 7 * fontinfo [8 + parambase [eqtb [27693 + cursize ].hh .v.RH ]
    ].cint ;
    else clr = 3 * fontinfo [8 + parambase [eqtb [27693 + cursize ].hh 
    .v.RH ]].cint ;
    delta = half ( clr - ( ( shiftup - mem [x + 2 ].cint ) - ( mem [z + 3 ]
    .cint - shiftdown ) ) ) ;
    if ( delta > 0 ) 
    {
      shiftup = shiftup + delta ;
      shiftdown = shiftdown + delta ;
    } 
  } 
  else {
      
    if ( curstyle < 2 ) 
    clr = 3 * mem [q + 1 ].cint ;
    else clr = mem [q + 1 ].cint ;
    delta = half ( mem [q + 1 ].cint ) ;
    delta1 = clr - ( ( shiftup - mem [x + 2 ].cint ) - ( fontinfo [22 + 
    parambase [eqtb [27692 + cursize ].hh .v.RH ]].cint + delta ) ) ;
    delta2 = clr - ( ( fontinfo [22 + parambase [eqtb [27692 + cursize ]
    .hh .v.RH ]].cint - delta ) - ( mem [z + 3 ].cint - shiftdown ) ) ;
    if ( delta1 > 0 ) 
    shiftup = shiftup + delta1 ;
    if ( delta2 > 0 ) 
    shiftdown = shiftdown + delta2 ;
  } 
  v = newnullbox () ;
  mem [v ].hh.b0 = 1 ;
  mem [v + 3 ].cint = shiftup + mem [x + 3 ].cint ;
  mem [v + 2 ].cint = mem [z + 2 ].cint + shiftdown ;
  mem [v + 1 ].cint = mem [x + 1 ].cint ;
  if ( mem [q + 1 ].cint == 0 ) 
  {
    p = newkern ( ( shiftup - mem [x + 2 ].cint ) - ( mem [z + 3 ].cint - 
    shiftdown ) ) ;
    mem [p ].hh .v.RH = z ;
  } 
  else {
      
    y = fractionrule ( mem [q + 1 ].cint ) ;
    p = newkern ( ( fontinfo [22 + parambase [eqtb [27692 + cursize ].hh 
    .v.RH ]].cint - delta ) - ( mem [z + 3 ].cint - shiftdown ) ) ;
    mem [y ].hh .v.RH = p ;
    mem [p ].hh .v.RH = z ;
    p = newkern ( ( shiftup - mem [x + 2 ].cint ) - ( fontinfo [22 + 
    parambase [eqtb [27692 + cursize ].hh .v.RH ]].cint + delta ) ) ;
    mem [p ].hh .v.RH = y ;
  } 
  mem [x ].hh .v.RH = p ;
  mem [v + 5 ].hh .v.RH = x ;
  if ( curstyle < 2 ) 
  delta = fontinfo [20 + parambase [eqtb [27692 + cursize ].hh .v.RH ]]
  .cint ;
  else delta = fontinfo [21 + parambase [eqtb [27692 + cursize ].hh .v.RH 
  ]].cint ;
  x = vardelimiter ( q + 4 , cursize , delta ) ;
  mem [x ].hh .v.RH = v ;
  z = vardelimiter ( q + 5 , cursize , delta ) ;
  mem [v ].hh .v.RH = z ;
  mem [q + 1 ].cint = hpack ( x , 0 , 1 ) ;
} 
scaled 
zmakeop ( halfword q ) 
{
  register scaled Result; makeop_regmem 
  scaled delta  ;
  halfword p, v, x, y, z  ;
  quarterword c  ;
  fourquarters i  ;
  scaled shiftup, shiftdown  ;
  if ( ( mem [q ].hh.b1 == 0 ) && ( curstyle < 2 ) ) 
  mem [q ].hh.b1 = 1 ;
  if ( mem [q + 1 ].hh .v.RH == 1 ) 
  {
    fetch ( q + 1 ) ;
    if ( ( curstyle < 2 ) && ( ( ( curi .b2 ) % 4 ) == 2 ) ) 
    {
      c = curi .b3 ;
      i = fontinfo [charbase [curf ]+ c ].qqqq ;
      if ( ( i .b0 > 0 ) ) 
      {
	curc = c ;
	curi = i ;
	mem [q + 1 ].hh.b1 = c ;
      } 
    } 
    delta = fontinfo [italicbase [curf ]+ ( curi .b2 ) / 4 ].cint ;
    x = cleanbox ( q + 1 , curstyle ) ;
    if ( ( mem [q + 3 ].hh .v.RH != 0 ) && ( mem [q ].hh.b1 != 1 ) ) 
    mem [x + 1 ].cint = mem [x + 1 ].cint - delta ;
    mem [x + 4 ].cint = half ( mem [x + 3 ].cint - mem [x + 2 ].cint ) - 
    fontinfo [22 + parambase [eqtb [27692 + cursize ].hh .v.RH ]].cint ;
    mem [q + 1 ].hh .v.RH = 2 ;
    mem [q + 1 ].hh .v.LH = x ;
  } 
  else delta = 0 ;
  if ( mem [q ].hh.b1 == 1 ) 
  {
    x = cleanbox ( q + 2 , 2 * ( curstyle / 4 ) + 4 + ( curstyle % 2 ) ) ;
    y = cleanbox ( q + 1 , curstyle ) ;
    z = cleanbox ( q + 3 , 2 * ( curstyle / 4 ) + 5 ) ;
    v = newnullbox () ;
    mem [v ].hh.b0 = 1 ;
    mem [v + 1 ].cint = mem [y + 1 ].cint ;
    if ( mem [x + 1 ].cint > mem [v + 1 ].cint ) 
    mem [v + 1 ].cint = mem [x + 1 ].cint ;
    if ( mem [z + 1 ].cint > mem [v + 1 ].cint ) 
    mem [v + 1 ].cint = mem [z + 1 ].cint ;
    x = rebox ( x , mem [v + 1 ].cint ) ;
    y = rebox ( y , mem [v + 1 ].cint ) ;
    z = rebox ( z , mem [v + 1 ].cint ) ;
    mem [x + 4 ].cint = half ( delta ) ;
    mem [z + 4 ].cint = - (integer) mem [x + 4 ].cint ;
    mem [v + 3 ].cint = mem [y + 3 ].cint ;
    mem [v + 2 ].cint = mem [y + 2 ].cint ;
    if ( mem [q + 2 ].hh .v.RH == 0 ) 
    {
      freenode ( x , 7 ) ;
      mem [v + 5 ].hh .v.RH = y ;
    } 
    else {
	
      shiftup = fontinfo [11 + parambase [eqtb [27693 + cursize ].hh .v.RH 
      ]].cint - mem [x + 2 ].cint ;
      if ( shiftup < fontinfo [9 + parambase [eqtb [27693 + cursize ].hh 
      .v.RH ]].cint ) 
      shiftup = fontinfo [9 + parambase [eqtb [27693 + cursize ].hh .v.RH 
      ]].cint ;
      p = newkern ( shiftup ) ;
      mem [p ].hh .v.RH = y ;
      mem [x ].hh .v.RH = p ;
      p = newkern ( fontinfo [13 + parambase [eqtb [27693 + cursize ].hh 
      .v.RH ]].cint ) ;
      mem [p ].hh .v.RH = x ;
      mem [v + 5 ].hh .v.RH = p ;
      mem [v + 3 ].cint = mem [v + 3 ].cint + fontinfo [13 + parambase [
      eqtb [27693 + cursize ].hh .v.RH ]].cint + mem [x + 3 ].cint + mem 
      [x + 2 ].cint + shiftup ;
    } 
    if ( mem [q + 3 ].hh .v.RH == 0 ) 
    freenode ( z , 7 ) ;
    else {
	
      shiftdown = fontinfo [12 + parambase [eqtb [27693 + cursize ].hh 
      .v.RH ]].cint - mem [z + 3 ].cint ;
      if ( shiftdown < fontinfo [10 + parambase [eqtb [27693 + cursize ]
      .hh .v.RH ]].cint ) 
      shiftdown = fontinfo [10 + parambase [eqtb [27693 + cursize ].hh 
      .v.RH ]].cint ;
      p = newkern ( shiftdown ) ;
      mem [y ].hh .v.RH = p ;
      mem [p ].hh .v.RH = z ;
      p = newkern ( fontinfo [13 + parambase [eqtb [27693 + cursize ].hh 
      .v.RH ]].cint ) ;
      mem [z ].hh .v.RH = p ;
      mem [v + 2 ].cint = mem [v + 2 ].cint + fontinfo [13 + parambase [
      eqtb [27693 + cursize ].hh .v.RH ]].cint + mem [z + 3 ].cint + mem 
      [z + 2 ].cint + shiftdown ;
    } 
    mem [q + 1 ].cint = v ;
  } 
  Result = delta ;
  return Result ;
} 
void 
zmakeord ( halfword q ) 
{
  /* 20 10 */ makeord_regmem 
  integer a  ;
  halfword p, r  ;
  lab20: if ( mem [q + 3 ].hh .v.RH == 0 ) {
      
    if ( mem [q + 2 ].hh .v.RH == 0 ) {
	
      if ( mem [q + 1 ].hh .v.RH == 1 ) 
      {
	p = mem [q ].hh .v.RH ;
	if ( p != -268435455L ) {
	    
	  if ( ( mem [p ].hh.b0 >= 16 ) && ( mem [p ].hh.b0 <= 22 ) ) {
	      
	    if ( mem [p + 1 ].hh .v.RH == 1 ) {
		
	      if ( mem [p + 1 ].hh.b0 == mem [q + 1 ].hh.b0 ) 
	      {
		mem [q + 1 ].hh .v.RH = 4 ;
		fetch ( q + 1 ) ;
		if ( ( ( curi .b2 ) % 4 ) == 1 ) 
		{
		  a = ligkernbase [curf ]+ curi .b3 ;
		  curc = mem [p + 1 ].hh.b1 ;
		  curi = fontinfo [a ].qqqq ;
		  if ( curi .b0 > 128 ) 
		  {
		    a = ligkernbase [curf ]+ 256 * curi .b2 + curi .b3 + 
		    32768L - 256 * ( 128 ) ;
		    curi = fontinfo [a ].qqqq ;
		  } 
		  while ( true ) {
		      
		    if ( curi .b1 == curc ) {
			
		      if ( curi .b0 <= 128 ) {
			  
			if ( curi .b2 >= 128 ) 
			{
			  p = newkern ( fontinfo [kernbase [curf ]+ 256 * 
			  curi .b2 + curi .b3 ].cint ) ;
			  mem [p ].hh .v.RH = mem [q ].hh .v.RH ;
			  mem [q ].hh .v.RH = p ;
			  return ;
			} 
			else {
			    
			  {
			    if ( interrupt != 0 ) 
			    pauseforinstructions () ;
			  } 
			  switch ( curi .b2 ) 
			  {case 1 : 
			  case 5 : 
			    mem [q + 1 ].hh.b1 = curi .b3 ;
			    break ;
			  case 2 : 
			  case 6 : 
			    mem [p + 1 ].hh.b1 = curi .b3 ;
			    break ;
			  case 3 : 
			  case 7 : 
			  case 11 : 
			    {
			      r = newnoad () ;
			      mem [r + 1 ].hh.b1 = curi .b3 ;
			      mem [r + 1 ].hh.b0 = mem [q + 1 ].hh.b0 ;
			      mem [q ].hh .v.RH = r ;
			      mem [r ].hh .v.RH = p ;
			      if ( curi .b2 < 11 ) 
			      mem [r + 1 ].hh .v.RH = 1 ;
			      else mem [r + 1 ].hh .v.RH = 4 ;
			    } 
			    break ;
			    default: 
			    {
			      mem [q ].hh .v.RH = mem [p ].hh .v.RH ;
			      mem [q + 1 ].hh.b1 = curi .b3 ;
			      mem [q + 3 ]= mem [p + 3 ];
			      mem [q + 2 ]= mem [p + 2 ];
			      freenode ( p , 4 ) ;
			    } 
			    break ;
			  } 
			  if ( curi .b2 > 3 ) 
			  return ;
			  mem [q + 1 ].hh .v.RH = 1 ;
			  goto lab20 ;
			} 
		      } 
		    } 
		    if ( curi .b0 >= 128 ) 
		    return ;
		    a = a + curi .b0 + 1 ;
		    curi = fontinfo [a ].qqqq ;
		  } 
		} 
	      } 
	    } 
	  } 
	} 
      } 
    } 
  } 
} 
void 
zmakescripts ( halfword q , scaled delta ) 
{
  makescripts_regmem 
  halfword p, x, y, z  ;
  scaled shiftup, shiftdown, clr  ;
  smallnumber t  ;
  p = mem [q + 1 ].cint ;
  if ( ( p >= himemmin ) ) 
  {
    shiftup = 0 ;
    shiftdown = 0 ;
  } 
  else {
      
    z = hpack ( p , 0 , 1 ) ;
    if ( curstyle < 4 ) 
    t = 16 ;
    else t = 32 ;
    shiftup = mem [z + 3 ].cint - fontinfo [18 + parambase [eqtb [27692 + 
    t ].hh .v.RH ]].cint ;
    shiftdown = mem [z + 2 ].cint + fontinfo [19 + parambase [eqtb [27692 
    + t ].hh .v.RH ]].cint ;
    freenode ( z , 7 ) ;
  } 
  if ( mem [q + 2 ].hh .v.RH == 0 ) 
  {
    x = cleanbox ( q + 3 , 2 * ( curstyle / 4 ) + 5 ) ;
    mem [x + 1 ].cint = mem [x + 1 ].cint + eqtb [29899 ].cint ;
    if ( shiftdown < fontinfo [16 + parambase [eqtb [27692 + cursize ].hh 
    .v.RH ]].cint ) 
    shiftdown = fontinfo [16 + parambase [eqtb [27692 + cursize ].hh .v.RH 
    ]].cint ;
    clr = mem [x + 3 ].cint - ( abs ( fontinfo [5 + parambase [eqtb [
    27692 + cursize ].hh .v.RH ]].cint * 4 ) / 5 ) ;
    if ( shiftdown < clr ) 
    shiftdown = clr ;
    mem [x + 4 ].cint = shiftdown ;
  } 
  else {
      
    {
      x = cleanbox ( q + 2 , 2 * ( curstyle / 4 ) + 4 + ( curstyle % 2 ) ) ;
      mem [x + 1 ].cint = mem [x + 1 ].cint + eqtb [29899 ].cint ;
      if ( odd ( curstyle ) ) 
      clr = fontinfo [15 + parambase [eqtb [27692 + cursize ].hh .v.RH ]]
      .cint ;
      else if ( curstyle < 2 ) 
      clr = fontinfo [13 + parambase [eqtb [27692 + cursize ].hh .v.RH ]]
      .cint ;
      else clr = fontinfo [14 + parambase [eqtb [27692 + cursize ].hh 
      .v.RH ]].cint ;
      if ( shiftup < clr ) 
      shiftup = clr ;
      clr = mem [x + 2 ].cint + ( abs ( fontinfo [5 + parambase [eqtb [
      27692 + cursize ].hh .v.RH ]].cint ) / 4 ) ;
      if ( shiftup < clr ) 
      shiftup = clr ;
    } 
    if ( mem [q + 3 ].hh .v.RH == 0 ) 
    mem [x + 4 ].cint = - (integer) shiftup ;
    else {
	
      y = cleanbox ( q + 3 , 2 * ( curstyle / 4 ) + 5 ) ;
      mem [y + 1 ].cint = mem [y + 1 ].cint + eqtb [29899 ].cint ;
      if ( shiftdown < fontinfo [17 + parambase [eqtb [27692 + cursize ]
      .hh .v.RH ]].cint ) 
      shiftdown = fontinfo [17 + parambase [eqtb [27692 + cursize ].hh 
      .v.RH ]].cint ;
      clr = 4 * fontinfo [8 + parambase [eqtb [27693 + cursize ].hh .v.RH 
      ]].cint - ( ( shiftup - mem [x + 2 ].cint ) - ( mem [y + 3 ].cint 
      - shiftdown ) ) ;
      if ( clr > 0 ) 
      {
	shiftdown = shiftdown + clr ;
	clr = ( abs ( fontinfo [5 + parambase [eqtb [27692 + cursize ].hh 
	.v.RH ]].cint * 4 ) / 5 ) - ( shiftup - mem [x + 2 ].cint ) ;
	if ( clr > 0 ) 
	{
	  shiftup = shiftup + clr ;
	  shiftdown = shiftdown - clr ;
	} 
      } 
      mem [x + 4 ].cint = delta ;
      p = newkern ( ( shiftup - mem [x + 2 ].cint ) - ( mem [y + 3 ].cint 
      - shiftdown ) ) ;
      mem [x ].hh .v.RH = p ;
      mem [p ].hh .v.RH = y ;
      x = vpackage ( x , 0 , 1 , 1073741823L ) ;
      mem [x + 4 ].cint = shiftdown ;
    } 
  } 
  if ( mem [q + 1 ].cint == -268435455L ) 
  mem [q + 1 ].cint = x ;
  else {
      
    p = mem [q + 1 ].cint ;
    while ( mem [p ].hh .v.RH != -268435455L ) p = mem [p ].hh .v.RH ;
    mem [p ].hh .v.RH = x ;
  } 
} 
smallnumber 
zmakeleftright ( halfword q , smallnumber style , scaled maxd , scaled maxh ) 
{
  register smallnumber Result; makeleftright_regmem 
  scaled delta, delta1, delta2  ;
  curstyle = style ;
  {
    if ( curstyle < 4 ) 
    cursize = 0 ;
    else cursize = 16 * ( ( curstyle - 2 ) / 2 ) ;
    curmu = xovern ( fontinfo [6 + parambase [eqtb [27692 + cursize ].hh 
    .v.RH ]].cint , 18 ) ;
  } 
  delta2 = maxd + fontinfo [22 + parambase [eqtb [27692 + cursize ].hh 
  .v.RH ]].cint ;
  delta1 = maxh + maxd - delta2 ;
  if ( delta2 > delta1 ) 
  delta1 = delta2 ;
  delta = ( delta1 / 500 ) * eqtb [29292 ].cint ;
  delta2 = delta1 + delta1 - eqtb [29897 ].cint ;
  if ( delta < delta2 ) 
  delta = delta2 ;
  mem [q + 1 ].cint = vardelimiter ( q + 1 , cursize , delta ) ;
  Result = mem [q ].hh.b0 - ( 10 ) ;
  return Result ;
} 
void 
mlisttohlist ( void ) 
{
  /* 21 82 80 81 83 30 */ mlisttohlist_regmem 
  halfword mlist  ;
  boolean penalties  ;
  smallnumber style  ;
  smallnumber savestyle  ;
  halfword q  ;
  halfword r  ;
  smallnumber rtype  ;
  smallnumber t  ;
  halfword p, x, y, z  ;
  integer pen  ;
  smallnumber s  ;
  scaled maxh, maxd  ;
  scaled delta  ;
  mlist = curmlist ;
  penalties = mlistpenalties ;
  style = curstyle ;
  q = mlist ;
  r = -268435455L ;
  rtype = 17 ;
  maxh = 0 ;
  maxd = 0 ;
  {
    if ( curstyle < 4 ) 
    cursize = 0 ;
    else cursize = 16 * ( ( curstyle - 2 ) / 2 ) ;
    curmu = xovern ( fontinfo [6 + parambase [eqtb [27692 + cursize ].hh 
    .v.RH ]].cint , 18 ) ;
  } 
  while ( q != -268435455L ) {
      
    lab21: delta = 0 ;
    switch ( mem [q ].hh.b0 ) 
    {case 18 : 
      switch ( rtype ) 
      {case 18 : 
      case 17 : 
      case 19 : 
      case 20 : 
      case 22 : 
      case 30 : 
	{
	  mem [q ].hh.b0 = 16 ;
	  goto lab21 ;
	} 
	break ;
	default: 
	;
	break ;
      } 
      break ;
    case 19 : 
    case 21 : 
    case 22 : 
    case 31 : 
      {
	if ( rtype == 18 ) 
	mem [r ].hh.b0 = 16 ;
	if ( mem [q ].hh.b0 == 31 ) 
	goto lab80 ;
      } 
      break ;
    case 30 : 
      goto lab80 ;
      break ;
    case 25 : 
      {
	makefraction ( q ) ;
	goto lab82 ;
      } 
      break ;
    case 17 : 
      {
	delta = makeop ( q ) ;
	if ( mem [q ].hh.b1 == 1 ) 
	goto lab82 ;
      } 
      break ;
    case 16 : 
      makeord ( q ) ;
      break ;
    case 20 : 
    case 23 : 
      ;
      break ;
    case 24 : 
      makeradical ( q ) ;
      break ;
    case 27 : 
      makeover ( q ) ;
      break ;
    case 26 : 
      makeunder ( q ) ;
      break ;
    case 28 : 
      makemathaccent ( q ) ;
      break ;
    case 29 : 
      makevcenter ( q ) ;
      break ;
    case 14 : 
      {
	curstyle = mem [q ].hh.b1 ;
	{
	  if ( curstyle < 4 ) 
	  cursize = 0 ;
	  else cursize = 16 * ( ( curstyle - 2 ) / 2 ) ;
	  curmu = xovern ( fontinfo [6 + parambase [eqtb [27692 + cursize ]
	  .hh .v.RH ]].cint , 18 ) ;
	} 
	goto lab81 ;
      } 
      break ;
    case 15 : 
      {
	switch ( curstyle / 2 ) 
	{case 0 : 
	  {
	    p = mem [q + 1 ].hh .v.LH ;
	    mem [q + 1 ].hh .v.LH = -268435455L ;
	  } 
	  break ;
	case 1 : 
	  {
	    p = mem [q + 1 ].hh .v.RH ;
	    mem [q + 1 ].hh .v.RH = -268435455L ;
	  } 
	  break ;
	case 2 : 
	  {
	    p = mem [q + 2 ].hh .v.LH ;
	    mem [q + 2 ].hh .v.LH = -268435455L ;
	  } 
	  break ;
	case 3 : 
	  {
	    p = mem [q + 2 ].hh .v.RH ;
	    mem [q + 2 ].hh .v.RH = -268435455L ;
	  } 
	  break ;
	} 
	flushnodelist ( mem [q + 1 ].hh .v.LH ) ;
	flushnodelist ( mem [q + 1 ].hh .v.RH ) ;
	flushnodelist ( mem [q + 2 ].hh .v.LH ) ;
	flushnodelist ( mem [q + 2 ].hh .v.RH ) ;
	mem [q ].hh.b0 = 14 ;
	mem [q ].hh.b1 = curstyle ;
	mem [q + 1 ].cint = 0 ;
	mem [q + 2 ].cint = 0 ;
	if ( p != -268435455L ) 
	{
	  z = mem [q ].hh .v.RH ;
	  mem [q ].hh .v.RH = p ;
	  while ( mem [p ].hh .v.RH != -268435455L ) p = mem [p ].hh .v.RH 
	  ;
	  mem [p ].hh .v.RH = z ;
	} 
	goto lab81 ;
      } 
      break ;
    case 3 : 
    case 4 : 
    case 5 : 
    case 8 : 
    case 12 : 
    case 7 : 
      goto lab81 ;
      break ;
    case 2 : 
      {
	if ( mem [q + 3 ].cint > maxh ) 
	maxh = mem [q + 3 ].cint ;
	if ( mem [q + 2 ].cint > maxd ) 
	maxd = mem [q + 2 ].cint ;
	goto lab81 ;
      } 
      break ;
    case 10 : 
      {
	if ( mem [q ].hh.b1 == 99 ) 
	{
	  x = mem [q + 1 ].hh .v.LH ;
	  y = mathglue ( x , curmu ) ;
	  deleteglueref ( x ) ;
	  mem [q + 1 ].hh .v.LH = y ;
	  mem [q ].hh.b1 = 0 ;
	} 
	else if ( ( cursize != 0 ) && ( mem [q ].hh.b1 == 98 ) ) 
	{
	  p = mem [q ].hh .v.RH ;
	  if ( p != -268435455L ) {
	      
	    if ( ( mem [p ].hh.b0 == 10 ) || ( mem [p ].hh.b0 == 11 ) ) 
	    {
	      mem [q ].hh .v.RH = mem [p ].hh .v.RH ;
	      mem [p ].hh .v.RH = -268435455L ;
	      flushnodelist ( p ) ;
	    } 
	  } 
	} 
	goto lab81 ;
      } 
      break ;
    case 11 : 
      {
	mathkern ( q , curmu ) ;
	goto lab81 ;
      } 
      break ;
      default: 
      confusion ( 1291 ) ;
      break ;
    } 
    switch ( mem [q + 1 ].hh .v.RH ) 
    {case 1 : 
    case 4 : 
      {
	fetch ( q + 1 ) ;
	if ( ( curi .b0 > 0 ) ) 
	{
	  delta = fontinfo [italicbase [curf ]+ ( curi .b2 ) / 4 ].cint ;
	  p = newcharacter ( curf , curc ) ;
	  if ( ( mem [q + 1 ].hh .v.RH == 4 ) && ( fontinfo [2 + parambase 
	  [curf ]].cint != 0 ) ) 
	  delta = 0 ;
	  if ( ( mem [q + 3 ].hh .v.RH == 0 ) && ( delta != 0 ) ) 
	  {
	    mem [p ].hh .v.RH = newkern ( delta ) ;
	    delta = 0 ;
	  } 
	} 
	else p = -268435455L ;
      } 
      break ;
    case 0 : 
      p = -268435455L ;
      break ;
    case 2 : 
      p = mem [q + 1 ].hh .v.LH ;
      break ;
    case 3 : 
      {
	curmlist = mem [q + 1 ].hh .v.LH ;
	savestyle = curstyle ;
	mlistpenalties = false ;
	mlisttohlist () ;
	curstyle = savestyle ;
	{
	  if ( curstyle < 4 ) 
	  cursize = 0 ;
	  else cursize = 16 * ( ( curstyle - 2 ) / 2 ) ;
	  curmu = xovern ( fontinfo [6 + parambase [eqtb [27692 + cursize ]
	  .hh .v.RH ]].cint , 18 ) ;
	} 
	p = hpack ( mem [memtop - 3 ].hh .v.RH , 0 , 1 ) ;
      } 
      break ;
      default: 
      confusion ( 1292 ) ;
      break ;
    } 
    mem [q + 1 ].cint = p ;
    if ( ( mem [q + 3 ].hh .v.RH == 0 ) && ( mem [q + 2 ].hh .v.RH == 0 ) 
    ) 
    goto lab82 ;
    makescripts ( q , delta ) ;
    lab82: z = hpack ( mem [q + 1 ].cint , 0 , 1 ) ;
    if ( mem [z + 3 ].cint > maxh ) 
    maxh = mem [z + 3 ].cint ;
    if ( mem [z + 2 ].cint > maxd ) 
    maxd = mem [z + 2 ].cint ;
    freenode ( z , 7 ) ;
    lab80: r = q ;
    rtype = mem [r ].hh.b0 ;
    if ( rtype == 31 ) 
    {
      rtype = 30 ;
      curstyle = style ;
      {
	if ( curstyle < 4 ) 
	cursize = 0 ;
	else cursize = 16 * ( ( curstyle - 2 ) / 2 ) ;
	curmu = xovern ( fontinfo [6 + parambase [eqtb [27692 + cursize ]
	.hh .v.RH ]].cint , 18 ) ;
      } 
    } 
    lab81: q = mem [q ].hh .v.RH ;
  } 
  if ( rtype == 18 ) 
  mem [r ].hh.b0 = 16 ;
  p = memtop - 3 ;
  mem [p ].hh .v.RH = -268435455L ;
  q = mlist ;
  rtype = 0 ;
  curstyle = style ;
  {
    if ( curstyle < 4 ) 
    cursize = 0 ;
    else cursize = 16 * ( ( curstyle - 2 ) / 2 ) ;
    curmu = xovern ( fontinfo [6 + parambase [eqtb [27692 + cursize ].hh 
    .v.RH ]].cint , 18 ) ;
  } 
  while ( q != -268435455L ) {
      
    t = 16 ;
    s = 4 ;
    pen = 10000 ;
    switch ( mem [q ].hh.b0 ) 
    {case 17 : 
    case 20 : 
    case 21 : 
    case 22 : 
    case 23 : 
      t = mem [q ].hh.b0 ;
      break ;
    case 18 : 
      {
	t = 18 ;
	pen = eqtb [29283 ].cint ;
      } 
      break ;
    case 19 : 
      {
	t = 19 ;
	pen = eqtb [29284 ].cint ;
      } 
      break ;
    case 16 : 
    case 29 : 
    case 27 : 
    case 26 : 
      ;
      break ;
    case 24 : 
      s = 5 ;
      break ;
    case 28 : 
      s = 5 ;
      break ;
    case 25 : 
      {
	t = 23 ;
	s = 6 ;
      } 
      break ;
    case 30 : 
    case 31 : 
      t = makeleftright ( q , style , maxd , maxh ) ;
      break ;
    case 14 : 
      {
	curstyle = mem [q ].hh.b1 ;
	s = 3 ;
	{
	  if ( curstyle < 4 ) 
	  cursize = 0 ;
	  else cursize = 16 * ( ( curstyle - 2 ) / 2 ) ;
	  curmu = xovern ( fontinfo [6 + parambase [eqtb [27692 + cursize ]
	  .hh .v.RH ]].cint , 18 ) ;
	} 
	goto lab83 ;
      } 
      break ;
    case 8 : 
    case 12 : 
    case 2 : 
    case 7 : 
    case 5 : 
    case 3 : 
    case 4 : 
    case 10 : 
    case 11 : 
      {
	mem [p ].hh .v.RH = q ;
	p = q ;
	q = mem [q ].hh .v.RH ;
	mem [p ].hh .v.RH = -268435455L ;
	goto lab30 ;
      } 
      break ;
      default: 
      confusion ( 1293 ) ;
      break ;
    } 
    if ( rtype > 0 ) 
    {
      switch ( strpool [rtype * 8 + t + magicoffset ]) 
      {case 48 : 
	x = 0 ;
	break ;
      case 49 : 
	if ( curstyle < 4 ) 
	x = 15 ;
	else x = 0 ;
	break ;
      case 50 : 
	x = 15 ;
	break ;
      case 51 : 
	if ( curstyle < 4 ) 
	x = 16 ;
	else x = 0 ;
	break ;
      case 52 : 
	if ( curstyle < 4 ) 
	x = 17 ;
	else x = 0 ;
	break ;
	default: 
	confusion ( 1295 ) ;
	break ;
      } 
      if ( x != 0 ) 
      {
	y = mathglue ( eqtb [26628 + x ].hh .v.RH , curmu ) ;
	z = newglue ( y ) ;
	mem [y ].hh .v.RH = -268435455L ;
	mem [p ].hh .v.RH = z ;
	p = z ;
	mem [z ].hh.b1 = x + 1 ;
      } 
    } 
    if ( mem [q + 1 ].cint != -268435455L ) 
    {
      mem [p ].hh .v.RH = mem [q + 1 ].cint ;
      do {
	  p = mem [p ].hh .v.RH ;
      } while ( ! ( mem [p ].hh .v.RH == -268435455L ) ) ;
    } 
    if ( penalties ) {
	
      if ( mem [q ].hh .v.RH != -268435455L ) {
	  
	if ( pen < 10000 ) 
	{
	  rtype = mem [mem [q ].hh .v.RH ].hh.b0 ;
	  if ( rtype != 12 ) {
	      
	    if ( rtype != 19 ) 
	    {
	      z = newpenalty ( pen ) ;
	      mem [p ].hh .v.RH = z ;
	      p = z ;
	    } 
	  } 
	} 
      } 
    } 
    if ( mem [q ].hh.b0 == 31 ) 
    t = 20 ;
    rtype = t ;
    lab83: r = q ;
    q = mem [q ].hh .v.RH ;
    freenode ( r , s ) ;
    lab30: ;
  } 
} 
void 
pushalignment ( void ) 
{
  pushalignment_regmem 
  halfword p  ;
  p = getnode ( 6 ) ;
  mem [p ].hh .v.RH = alignptr ;
  mem [p ].hh .v.LH = curalign ;
  mem [p + 1 ].hh .v.LH = mem [memtop - 8 ].hh .v.RH ;
  mem [p + 1 ].hh .v.RH = curspan ;
  mem [p + 2 ].cint = curloop ;
  mem [p + 3 ].cint = alignstate ;
  mem [p + 4 ].hh .v.LH = curhead ;
  mem [p + 4 ].hh .v.RH = curtail ;
  mem [p + 5 ].hh .v.LH = curprehead ;
  mem [p + 5 ].hh .v.RH = curpretail ;
  alignptr = p ;
  curhead = getavail () ;
  curprehead = getavail () ;
} 
void 
popalignment ( void ) 
{
  popalignment_regmem 
  halfword p  ;
  {
    mem [curhead ].hh .v.RH = avail ;
    avail = curhead ;
	;
#ifdef STAT
    decr ( dynused ) ;
#endif /* STAT */
  } 
  {
    mem [curprehead ].hh .v.RH = avail ;
    avail = curprehead ;
	;
#ifdef STAT
    decr ( dynused ) ;
#endif /* STAT */
  } 
  p = alignptr ;
  curtail = mem [p + 4 ].hh .v.RH ;
  curhead = mem [p + 4 ].hh .v.LH ;
  curpretail = mem [p + 5 ].hh .v.RH ;
  curprehead = mem [p + 5 ].hh .v.LH ;
  alignstate = mem [p + 3 ].cint ;
  curloop = mem [p + 2 ].cint ;
  curspan = mem [p + 1 ].hh .v.RH ;
  mem [memtop - 8 ].hh .v.RH = mem [p + 1 ].hh .v.LH ;
  curalign = mem [p ].hh .v.LH ;
  alignptr = mem [p ].hh .v.RH ;
  freenode ( p , 6 ) ;
} 
void 
getpreambletoken ( void ) 
{
  /* 20 */ getpreambletoken_regmem 
  lab20: gettoken () ;
  while ( ( curchr == 256 ) && ( curcmd == 4 ) ) {
      
    gettoken () ;
    if ( curcmd > 102 ) 
    {
      expand () ;
      gettoken () ;
    } 
  } 
  if ( curcmd == 9 ) 
  fatalerror ( 674 ) ;
  if ( ( curcmd == 75 ) && ( curchr == 26639 ) ) 
  {
    scanoptionalequals () ;
    scanglue ( 2 ) ;
    if ( eqtb [29317 ].cint > 0 ) 
    geqdefine ( 26639 , 119 , curval ) ;
    else eqdefine ( 26639 , 119 , curval ) ;
    goto lab20 ;
  } 
} 
void 
initalign ( void ) 
{
  /* 30 31 32 22 */ initalign_regmem 
  halfword savecsptr  ;
  halfword p  ;
  savecsptr = curcs ;
  pushalignment () ;
  alignstate = -1000000L ;
  if ( ( curlist .modefield == 207 ) && ( ( curlist .tailfield != curlist 
  .headfield ) || ( curlist .auxfield .cint != -268435455L ) ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 776 ) ;
    } 
    printesc ( 594 ) ;
    print ( 1296 ) ;
    {
      helpptr = 3 ;
      helpline [2 ]= 1297 ;
      helpline [1 ]= 1298 ;
      helpline [0 ]= 1299 ;
    } 
    error () ;
    flushmath () ;
  } 
  pushnest () ;
  if ( curlist .modefield == 207 ) 
  {
    curlist .modefield = -1 ;
    curlist .auxfield .cint = nest [nestptr - 2 ].auxfield .cint ;
  } 
  else if ( curlist .modefield > 0 ) 
  curlist .modefield = - (integer) curlist .modefield ;
  scanspec ( 6 , false ) ;
  mem [memtop - 8 ].hh .v.RH = -268435455L ;
  curalign = memtop - 8 ;
  curloop = -268435455L ;
  scannerstatus = 4 ;
  warningindex = savecsptr ;
  alignstate = -1000000L ;
  while ( true ) {
      
    mem [curalign ].hh .v.RH = newparamglue ( 11 ) ;
    curalign = mem [curalign ].hh .v.RH ;
    if ( curcmd == 5 ) 
    goto lab30 ;
    p = memtop - 4 ;
    mem [p ].hh .v.RH = -268435455L ;
    while ( true ) {
	
      getpreambletoken () ;
      if ( curcmd == 6 ) 
      goto lab31 ;
      if ( ( curcmd <= 5 ) && ( curcmd >= 4 ) && ( alignstate == -1000000L ) ) 
      {
	if ( ( p == memtop - 4 ) && ( curloop == -268435455L ) && ( curcmd == 
	4 ) ) 
	curloop = curalign ;
	else {
	    
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 264 ) ;
	    print ( 1305 ) ;
	  } 
	  {
	    helpptr = 3 ;
	    helpline [2 ]= 1306 ;
	    helpline [1 ]= 1307 ;
	    helpline [0 ]= 1308 ;
	  } 
	  backerror () ;
	  goto lab31 ;
	} 
      } 
      else if ( ( curcmd != 10 ) || ( p != memtop - 4 ) ) 
      {
	mem [p ].hh .v.RH = getavail () ;
	p = mem [p ].hh .v.RH ;
	mem [p ].hh .v.LH = curtok ;
      } 
    } 
    lab31: ;
    mem [curalign ].hh .v.RH = newnullbox () ;
    curalign = mem [curalign ].hh .v.RH ;
    mem [curalign ].hh .v.LH = memtop - 9 ;
    mem [curalign + 1 ].cint = -1073741824L ;
    mem [curalign + 3 ].cint = mem [memtop - 4 ].hh .v.RH ;
    p = memtop - 4 ;
    mem [p ].hh .v.RH = -268435455L ;
    while ( true ) {
	
      lab22: getpreambletoken () ;
      if ( ( curcmd <= 5 ) && ( curcmd >= 4 ) && ( alignstate == -1000000L ) ) 
      goto lab32 ;
      if ( curcmd == 6 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 1309 ) ;
	} 
	{
	  helpptr = 3 ;
	  helpline [2 ]= 1306 ;
	  helpline [1 ]= 1307 ;
	  helpline [0 ]= 1310 ;
	} 
	error () ;
	goto lab22 ;
      } 
      mem [p ].hh .v.RH = getavail () ;
      p = mem [p ].hh .v.RH ;
      mem [p ].hh .v.LH = curtok ;
    } 
    lab32: mem [p ].hh .v.RH = getavail () ;
    p = mem [p ].hh .v.RH ;
    mem [p ].hh .v.LH = 19614 ;
    mem [curalign + 2 ].cint = mem [memtop - 4 ].hh .v.RH ;
  } 
  lab30: scannerstatus = 0 ;
  newsavelevel ( 6 ) ;
  if ( eqtb [27166 ].hh .v.RH != -268435455L ) 
  begintokenlist ( eqtb [27166 ].hh .v.RH , 13 ) ;
  alignpeek () ;
} 
void 
zinitspan ( halfword p ) 
{
  initspan_regmem 
  pushnest () ;
  if ( curlist .modefield == -104 ) 
  curlist .auxfield .hh .v.LH = 1000 ;
  else {
      
    curlist .auxfield .cint = eqtb [29919 ].cint ;
    normalparagraph () ;
  } 
  curspan = p ;
} 
void 
initrow ( void ) 
{
  initrow_regmem 
  pushnest () ;
  curlist .modefield = ( -105 ) - curlist .modefield ;
  if ( curlist .modefield == -104 ) 
  curlist .auxfield .hh .v.LH = 0 ;
  else curlist .auxfield .cint = 0 ;
  {
    mem [curlist .tailfield ].hh .v.RH = newglue ( mem [mem [memtop - 8 ]
    .hh .v.RH + 1 ].hh .v.LH ) ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  mem [curlist .tailfield ].hh.b1 = 12 ;
  curalign = mem [mem [memtop - 8 ].hh .v.RH ].hh .v.RH ;
  curtail = curhead ;
  curpretail = curprehead ;
  initspan ( curalign ) ;
} 
void 
initcol ( void ) 
{
  initcol_regmem 
  mem [curalign + 5 ].hh .v.LH = curcmd ;
  if ( curcmd == 63 ) 
  alignstate = 0 ;
  else {
      
    backinput () ;
    begintokenlist ( mem [curalign + 3 ].cint , 1 ) ;
  } 
} 
boolean 
fincol ( void ) 
{
  /* 10 */ register boolean Result; fincol_regmem 
  halfword p  ;
  halfword q, r  ;
  halfword s  ;
  halfword u  ;
  scaled w  ;
  glueord o  ;
  halfword n  ;
  if ( curalign == -268435455L ) 
  confusion ( 1311 ) ;
  q = mem [curalign ].hh .v.RH ;
  if ( q == -268435455L ) 
  confusion ( 1311 ) ;
  if ( alignstate < 500000L ) 
  fatalerror ( 674 ) ;
  p = mem [q ].hh .v.RH ;
  if ( ( p == -268435455L ) && ( mem [curalign + 5 ].hh .v.LH < 257 ) ) {
      
    if ( curloop != -268435455L ) 
    {
      mem [q ].hh .v.RH = newnullbox () ;
      p = mem [q ].hh .v.RH ;
      mem [p ].hh .v.LH = memtop - 9 ;
      mem [p + 1 ].cint = -1073741824L ;
      curloop = mem [curloop ].hh .v.RH ;
      q = memtop - 4 ;
      r = mem [curloop + 3 ].cint ;
      while ( r != -268435455L ) {
	  
	mem [q ].hh .v.RH = getavail () ;
	q = mem [q ].hh .v.RH ;
	mem [q ].hh .v.LH = mem [r ].hh .v.LH ;
	r = mem [r ].hh .v.RH ;
      } 
      mem [q ].hh .v.RH = -268435455L ;
      mem [p + 3 ].cint = mem [memtop - 4 ].hh .v.RH ;
      q = memtop - 4 ;
      r = mem [curloop + 2 ].cint ;
      while ( r != -268435455L ) {
	  
	mem [q ].hh .v.RH = getavail () ;
	q = mem [q ].hh .v.RH ;
	mem [q ].hh .v.LH = mem [r ].hh .v.LH ;
	r = mem [r ].hh .v.RH ;
      } 
      mem [q ].hh .v.RH = -268435455L ;
      mem [p + 2 ].cint = mem [memtop - 4 ].hh .v.RH ;
      curloop = mem [curloop ].hh .v.RH ;
      mem [p ].hh .v.RH = newglue ( mem [curloop + 1 ].hh .v.LH ) ;
    } 
    else {
	
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 1312 ) ;
      } 
      printesc ( 1301 ) ;
      {
	helpptr = 3 ;
	helpline [2 ]= 1313 ;
	helpline [1 ]= 1314 ;
	helpline [0 ]= 1315 ;
      } 
      mem [curalign + 5 ].hh .v.LH = 257 ;
      error () ;
    } 
  } 
  if ( mem [curalign + 5 ].hh .v.LH != 256 ) 
  {
    unsave () ;
    newsavelevel ( 6 ) ;
    {
      if ( curlist .modefield == -104 ) 
      {
	adjusttail = curtail ;
	preadjusttail = curpretail ;
	u = hpack ( mem [curlist .headfield ].hh .v.RH , 0 , 1 ) ;
	w = mem [u + 1 ].cint ;
	curtail = adjusttail ;
	adjusttail = -268435455L ;
	curpretail = preadjusttail ;
	preadjusttail = -268435455L ;
      } 
      else {
	  
	u = vpackage ( mem [curlist .headfield ].hh .v.RH , 0 , 1 , 0 ) ;
	w = mem [u + 3 ].cint ;
      } 
      n = 0 ;
      if ( curspan != curalign ) 
      {
	q = curspan ;
	do {
	    incr ( n ) ;
	  q = mem [mem [q ].hh .v.RH ].hh .v.RH ;
	} while ( ! ( q == curalign ) ) ;
	if ( n > 255 ) 
	confusion ( 1316 ) ;
	q = curspan ;
	while ( mem [mem [q ].hh .v.LH ].hh .v.RH < n ) q = mem [q ].hh 
	.v.LH ;
	if ( mem [mem [q ].hh .v.LH ].hh .v.RH > n ) 
	{
	  s = getnode ( 2 ) ;
	  mem [s ].hh .v.LH = mem [q ].hh .v.LH ;
	  mem [s ].hh .v.RH = n ;
	  mem [q ].hh .v.LH = s ;
	  mem [s + 1 ].cint = w ;
	} 
	else if ( mem [mem [q ].hh .v.LH + 1 ].cint < w ) 
	mem [mem [q ].hh .v.LH + 1 ].cint = w ;
      } 
      else if ( w > mem [curalign + 1 ].cint ) 
      mem [curalign + 1 ].cint = w ;
      mem [u ].hh.b0 = 13 ;
      mem [u ].hh.b1 = n ;
      if ( totalstretch [3 ]!= 0 ) 
      o = 3 ;
      else if ( totalstretch [2 ]!= 0 ) 
      o = 2 ;
      else if ( totalstretch [1 ]!= 0 ) 
      o = 1 ;
      else o = 0 ;
      mem [u + 5 ].hh.b1 = o ;
      mem [u + 6 ].cint = totalstretch [o ];
      if ( totalshrink [3 ]!= 0 ) 
      o = 3 ;
      else if ( totalshrink [2 ]!= 0 ) 
      o = 2 ;
      else if ( totalshrink [1 ]!= 0 ) 
      o = 1 ;
      else o = 0 ;
      mem [u + 5 ].hh.b0 = o ;
      mem [u + 4 ].cint = totalshrink [o ];
      popnest () ;
      mem [curlist .tailfield ].hh .v.RH = u ;
      curlist .tailfield = u ;
    } 
    {
      mem [curlist .tailfield ].hh .v.RH = newglue ( mem [mem [curalign ]
      .hh .v.RH + 1 ].hh .v.LH ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    mem [curlist .tailfield ].hh.b1 = 12 ;
    if ( mem [curalign + 5 ].hh .v.LH >= 257 ) 
    {
      Result = true ;
      return Result ;
    } 
    initspan ( p ) ;
  } 
  alignstate = 1000000L ;
  do {
      getxorprotected () ;
  } while ( ! ( curcmd != 10 ) ) ;
  curalign = p ;
  initcol () ;
  Result = false ;
  return Result ;
} 
void 
finrow ( void ) 
{
  finrow_regmem 
  halfword p  ;
  if ( curlist .modefield == -104 ) 
  {
    p = hpack ( mem [curlist .headfield ].hh .v.RH , 0 , 1 ) ;
    popnest () ;
    if ( curprehead != curpretail ) 
    {
      mem [curlist .tailfield ].hh .v.RH = mem [curprehead ].hh .v.RH ;
      curlist .tailfield = curpretail ;
    } 
    appendtovlist ( p ) ;
    if ( curhead != curtail ) 
    {
      mem [curlist .tailfield ].hh .v.RH = mem [curhead ].hh .v.RH ;
      curlist .tailfield = curtail ;
    } 
  } 
  else {
      
    p = vpackage ( mem [curlist .headfield ].hh .v.RH , 0 , 1 , 1073741823L 
    ) ;
    popnest () ;
    mem [curlist .tailfield ].hh .v.RH = p ;
    curlist .tailfield = p ;
    curlist .auxfield .hh .v.LH = 1000 ;
  } 
  mem [p ].hh.b0 = 13 ;
  mem [p + 6 ].cint = 0 ;
  if ( eqtb [27166 ].hh .v.RH != -268435455L ) 
  begintokenlist ( eqtb [27166 ].hh .v.RH , 13 ) ;
  alignpeek () ;
} 
void 
finalign ( void ) 
{
  finalign_regmem 
  halfword p, q, r, s, u, v  ;
  scaled t, w  ;
  scaled o  ;
  halfword n  ;
  scaled rulesave  ;
  memoryword auxsave  ;
  if ( curgroup != 6 ) 
  confusion ( 1317 ) ;
  unsave () ;
  if ( curgroup != 6 ) 
  confusion ( 1318 ) ;
  unsave () ;
  if ( nest [nestptr - 1 ].modefield == 207 ) 
  o = eqtb [29902 ].cint ;
  else o = 0 ;
  q = mem [mem [memtop - 8 ].hh .v.RH ].hh .v.RH ;
  do {
      flushlist ( mem [q + 3 ].cint ) ;
    flushlist ( mem [q + 2 ].cint ) ;
    p = mem [mem [q ].hh .v.RH ].hh .v.RH ;
    if ( mem [q + 1 ].cint == -1073741824L ) 
    {
      mem [q + 1 ].cint = 0 ;
      r = mem [q ].hh .v.RH ;
      s = mem [r + 1 ].hh .v.LH ;
      if ( s != membot ) 
      {
	incr ( mem [membot ].hh .v.RH ) ;
	deleteglueref ( s ) ;
	mem [r + 1 ].hh .v.LH = membot ;
      } 
    } 
    if ( mem [q ].hh .v.LH != memtop - 9 ) 
    {
      t = mem [q + 1 ].cint + mem [mem [mem [q ].hh .v.RH + 1 ].hh 
      .v.LH + 1 ].cint ;
      r = mem [q ].hh .v.LH ;
      s = memtop - 9 ;
      mem [s ].hh .v.LH = p ;
      n = 1 ;
      do {
	  mem [r + 1 ].cint = mem [r + 1 ].cint - t ;
	u = mem [r ].hh .v.LH ;
	while ( mem [r ].hh .v.RH > n ) {
	    
	  s = mem [s ].hh .v.LH ;
	  n = mem [mem [s ].hh .v.LH ].hh .v.RH + 1 ;
	} 
	if ( mem [r ].hh .v.RH < n ) 
	{
	  mem [r ].hh .v.LH = mem [s ].hh .v.LH ;
	  mem [s ].hh .v.LH = r ;
	  decr ( mem [r ].hh .v.RH ) ;
	  s = r ;
	} 
	else {
	    
	  if ( mem [r + 1 ].cint > mem [mem [s ].hh .v.LH + 1 ].cint ) 
	  mem [mem [s ].hh .v.LH + 1 ].cint = mem [r + 1 ].cint ;
	  freenode ( r , 2 ) ;
	} 
	r = u ;
      } while ( ! ( r == memtop - 9 ) ) ;
    } 
    mem [q ].hh.b0 = 13 ;
    mem [q ].hh.b1 = 0 ;
    mem [q + 3 ].cint = 0 ;
    mem [q + 2 ].cint = 0 ;
    mem [q + 5 ].hh.b1 = 0 ;
    mem [q + 5 ].hh.b0 = 0 ;
    mem [q + 6 ].cint = 0 ;
    mem [q + 4 ].cint = 0 ;
    q = p ;
  } while ( ! ( q == -268435455L ) ) ;
  saveptr = saveptr - 2 ;
  packbeginline = - (integer) curlist .mlfield ;
  if ( curlist .modefield == -1 ) 
  {
    rulesave = eqtb [29903 ].cint ;
    eqtb [29903 ].cint = 0 ;
    p = hpack ( mem [memtop - 8 ].hh .v.RH , savestack [saveptr + 1 ].cint 
    , savestack [saveptr + 0 ].cint ) ;
    eqtb [29903 ].cint = rulesave ;
  } 
  else {
      
    q = mem [mem [memtop - 8 ].hh .v.RH ].hh .v.RH ;
    do {
	mem [q + 3 ].cint = mem [q + 1 ].cint ;
      mem [q + 1 ].cint = 0 ;
      q = mem [mem [q ].hh .v.RH ].hh .v.RH ;
    } while ( ! ( q == -268435455L ) ) ;
    p = vpackage ( mem [memtop - 8 ].hh .v.RH , savestack [saveptr + 1 ]
    .cint , savestack [saveptr + 0 ].cint , 1073741823L ) ;
    q = mem [mem [memtop - 8 ].hh .v.RH ].hh .v.RH ;
    do {
	mem [q + 1 ].cint = mem [q + 3 ].cint ;
      mem [q + 3 ].cint = 0 ;
      q = mem [mem [q ].hh .v.RH ].hh .v.RH ;
    } while ( ! ( q == -268435455L ) ) ;
  } 
  packbeginline = 0 ;
  q = mem [curlist .headfield ].hh .v.RH ;
  s = curlist .headfield ;
  while ( q != -268435455L ) {
      
    if ( ! ( q >= himemmin ) ) {
	
      if ( mem [q ].hh.b0 == 13 ) 
      {
	if ( curlist .modefield == -1 ) 
	{
	  mem [q ].hh.b0 = 0 ;
	  mem [q + 1 ].cint = mem [p + 1 ].cint ;
	  if ( nest [nestptr - 1 ].modefield == 207 ) 
	  mem [q ].hh.b1 = 2 ;
	} 
	else {
	    
	  mem [q ].hh.b0 = 1 ;
	  mem [q + 3 ].cint = mem [p + 3 ].cint ;
	} 
	mem [q + 5 ].hh.b1 = mem [p + 5 ].hh.b1 ;
	mem [q + 5 ].hh.b0 = mem [p + 5 ].hh.b0 ;
	mem [q + 6 ].gr = mem [p + 6 ].gr ;
	mem [q + 4 ].cint = o ;
	r = mem [mem [q + 5 ].hh .v.RH ].hh .v.RH ;
	s = mem [mem [p + 5 ].hh .v.RH ].hh .v.RH ;
	do {
	    n = mem [r ].hh.b1 ;
	  t = mem [s + 1 ].cint ;
	  w = t ;
	  u = memtop - 4 ;
	  mem [r ].hh.b1 = 0 ;
	  while ( n > 0 ) {
	      
	    decr ( n ) ;
	    s = mem [s ].hh .v.RH ;
	    v = mem [s + 1 ].hh .v.LH ;
	    mem [u ].hh .v.RH = newglue ( v ) ;
	    u = mem [u ].hh .v.RH ;
	    mem [u ].hh.b1 = 12 ;
	    t = t + mem [v + 1 ].cint ;
	    if ( mem [p + 5 ].hh.b0 == 1 ) 
	    {
	      if ( mem [v ].hh.b0 == mem [p + 5 ].hh.b1 ) 
	      t = t + round ( mem [p + 6 ].gr * mem [v + 2 ].cint ) ;
	    } 
	    else if ( mem [p + 5 ].hh.b0 == 2 ) 
	    {
	      if ( mem [v ].hh.b1 == mem [p + 5 ].hh.b1 ) 
	      t = t - round ( mem [p + 6 ].gr * mem [v + 3 ].cint ) ;
	    } 
	    s = mem [s ].hh .v.RH ;
	    mem [u ].hh .v.RH = newnullbox () ;
	    u = mem [u ].hh .v.RH ;
	    t = t + mem [s + 1 ].cint ;
	    if ( curlist .modefield == -1 ) 
	    mem [u + 1 ].cint = mem [s + 1 ].cint ;
	    else {
		
	      mem [u ].hh.b0 = 1 ;
	      mem [u + 3 ].cint = mem [s + 1 ].cint ;
	    } 
	  } 
	  if ( curlist .modefield == -1 ) 
	  {
	    mem [r + 3 ].cint = mem [q + 3 ].cint ;
	    mem [r + 2 ].cint = mem [q + 2 ].cint ;
	    if ( t == mem [r + 1 ].cint ) 
	    {
	      mem [r + 5 ].hh.b0 = 0 ;
	      mem [r + 5 ].hh.b1 = 0 ;
	      mem [r + 6 ].gr = 0.0 ;
	    } 
	    else if ( t > mem [r + 1 ].cint ) 
	    {
	      mem [r + 5 ].hh.b0 = 1 ;
	      if ( mem [r + 6 ].cint == 0 ) 
	      mem [r + 6 ].gr = 0.0 ;
	      else mem [r + 6 ].gr = ( t - mem [r + 1 ].cint ) / ((double) 
	      mem [r + 6 ].cint ) ;
	    } 
	    else {
		
	      mem [r + 5 ].hh.b1 = mem [r + 5 ].hh.b0 ;
	      mem [r + 5 ].hh.b0 = 2 ;
	      if ( mem [r + 4 ].cint == 0 ) 
	      mem [r + 6 ].gr = 0.0 ;
	      else if ( ( mem [r + 5 ].hh.b1 == 0 ) && ( mem [r + 1 ].cint 
	      - t > mem [r + 4 ].cint ) ) 
	      mem [r + 6 ].gr = 1.0 ;
	      else mem [r + 6 ].gr = ( mem [r + 1 ].cint - t ) / ((double) 
	      mem [r + 4 ].cint ) ;
	    } 
	    mem [r + 1 ].cint = w ;
	    mem [r ].hh.b0 = 0 ;
	  } 
	  else {
	      
	    mem [r + 1 ].cint = mem [q + 1 ].cint ;
	    if ( t == mem [r + 3 ].cint ) 
	    {
	      mem [r + 5 ].hh.b0 = 0 ;
	      mem [r + 5 ].hh.b1 = 0 ;
	      mem [r + 6 ].gr = 0.0 ;
	    } 
	    else if ( t > mem [r + 3 ].cint ) 
	    {
	      mem [r + 5 ].hh.b0 = 1 ;
	      if ( mem [r + 6 ].cint == 0 ) 
	      mem [r + 6 ].gr = 0.0 ;
	      else mem [r + 6 ].gr = ( t - mem [r + 3 ].cint ) / ((double) 
	      mem [r + 6 ].cint ) ;
	    } 
	    else {
		
	      mem [r + 5 ].hh.b1 = mem [r + 5 ].hh.b0 ;
	      mem [r + 5 ].hh.b0 = 2 ;
	      if ( mem [r + 4 ].cint == 0 ) 
	      mem [r + 6 ].gr = 0.0 ;
	      else if ( ( mem [r + 5 ].hh.b1 == 0 ) && ( mem [r + 3 ].cint 
	      - t > mem [r + 4 ].cint ) ) 
	      mem [r + 6 ].gr = 1.0 ;
	      else mem [r + 6 ].gr = ( mem [r + 3 ].cint - t ) / ((double) 
	      mem [r + 4 ].cint ) ;
	    } 
	    mem [r + 3 ].cint = w ;
	    mem [r ].hh.b0 = 1 ;
	  } 
	  mem [r + 4 ].cint = 0 ;
	  if ( u != memtop - 4 ) 
	  {
	    mem [u ].hh .v.RH = mem [r ].hh .v.RH ;
	    mem [r ].hh .v.RH = mem [memtop - 4 ].hh .v.RH ;
	    r = u ;
	  } 
	  r = mem [mem [r ].hh .v.RH ].hh .v.RH ;
	  s = mem [mem [s ].hh .v.RH ].hh .v.RH ;
	} while ( ! ( r == -268435455L ) ) ;
      } 
      else if ( mem [q ].hh.b0 == 2 ) 
      {
	if ( ( mem [q + 1 ].cint == -1073741824L ) ) 
	mem [q + 1 ].cint = mem [p + 1 ].cint ;
	if ( ( mem [q + 3 ].cint == -1073741824L ) ) 
	mem [q + 3 ].cint = mem [p + 3 ].cint ;
	if ( ( mem [q + 2 ].cint == -1073741824L ) ) 
	mem [q + 2 ].cint = mem [p + 2 ].cint ;
	if ( o != 0 ) 
	{
	  r = mem [q ].hh .v.RH ;
	  mem [q ].hh .v.RH = -268435455L ;
	  q = hpack ( q , 0 , 1 ) ;
	  mem [q + 4 ].cint = o ;
	  mem [q ].hh .v.RH = r ;
	  mem [s ].hh .v.RH = q ;
	} 
      } 
    } 
    s = q ;
    q = mem [q ].hh .v.RH ;
  } 
  flushnodelist ( p ) ;
  popalignment () ;
  auxsave = curlist .auxfield ;
  p = mem [curlist .headfield ].hh .v.RH ;
  q = curlist .tailfield ;
  popnest () ;
  if ( curlist .modefield == 207 ) 
  {
    doassignments () ;
    if ( curcmd != 3 ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 1579 ) ;
      } 
      {
	helpptr = 2 ;
	helpline [1 ]= 1297 ;
	helpline [0 ]= 1298 ;
      } 
      backerror () ;
    } 
    else {
	
      getxtoken () ;
      if ( curcmd != 3 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 1575 ) ;
	} 
	{
	  helpptr = 2 ;
	  helpline [1 ]= 1576 ;
	  helpline [0 ]= 1577 ;
	} 
	backerror () ;
      } 
    } 
    flushnodelist ( curlist .eTeXauxfield ) ;
    popnest () ;
    {
      mem [curlist .tailfield ].hh .v.RH = newpenalty ( eqtb [29285 ].cint 
      ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    {
      mem [curlist .tailfield ].hh .v.RH = newparamglue ( 3 ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    mem [curlist .tailfield ].hh .v.RH = p ;
    if ( p != -268435455L ) 
    curlist .tailfield = q ;
    {
      mem [curlist .tailfield ].hh .v.RH = newpenalty ( eqtb [29286 ].cint 
      ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    {
      mem [curlist .tailfield ].hh .v.RH = newparamglue ( 4 ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    curlist .auxfield .cint = auxsave .cint ;
    resumeafterdisplay () ;
  } 
  else {
      
    curlist .auxfield = auxsave ;
    mem [curlist .tailfield ].hh .v.RH = p ;
    if ( p != -268435455L ) 
    curlist .tailfield = q ;
    if ( curlist .modefield == 1 ) 
    buildpage () ;
  } 
} 
void 
alignpeek ( void ) 
{
  /* 20 */ alignpeek_regmem 
  lab20: alignstate = 1000000L ;
  do {
      getxorprotected () ;
  } while ( ! ( curcmd != 10 ) ) ;
  if ( curcmd == 34 ) 
  {
    scanleftbrace () ;
    newsavelevel ( 7 ) ;
    if ( curlist .modefield == -1 ) 
    normalparagraph () ;
  } 
  else if ( curcmd == 2 ) 
  finalign () ;
  else if ( ( curcmd == 5 ) && ( curchr == 258 ) ) 
  goto lab20 ;
  else {
      
    initrow () ;
    initcol () ;
  } 
} 
halfword 
zfiniteshrink ( halfword p ) 
{
  register halfword Result; finiteshrink_regmem 
  halfword q  ;
  if ( noshrinkerroryet ) 
  {
    noshrinkerroryet = false ;
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 1319 ) ;
    } 
    {
      helpptr = 5 ;
      helpline [4 ]= 1320 ;
      helpline [3 ]= 1321 ;
      helpline [2 ]= 1322 ;
      helpline [1 ]= 1323 ;
      helpline [0 ]= 1324 ;
    } 
    error () ;
  } 
  q = newspec ( p ) ;
  mem [q ].hh.b1 = 0 ;
  deleteglueref ( p ) ;
  Result = q ;
  return Result ;
} 
void 
zpushnode ( halfword p ) 
{
  pushnode_regmem 
  if ( hliststacklevel > 512 ) 
  pdferror ( 1325 , 1326 ) ;
  hliststack [hliststacklevel ]= p ;
  hliststacklevel = hliststacklevel + 1 ;
} 
halfword 
popnode ( void ) 
{
  register halfword Result; popnode_regmem 
  hliststacklevel = hliststacklevel - 1 ;
  if ( hliststacklevel < 0 ) 
  pdferror ( 1327 , 1328 ) ;
  Result = hliststack [hliststacklevel ];
  return Result ;
} 
halfword 
zfindprotcharleft ( halfword l , boolean d ) 
{
  register halfword Result; findprotcharleft_regmem 
  halfword t  ;
  boolean run  ;
  if ( ( mem [l ].hh .v.RH != -268435455L ) && ( mem [l ].hh.b0 == 0 ) && 
  ( mem [l + 1 ].cint == 0 ) && ( mem [l + 3 ].cint == 0 ) && ( mem [l + 
  2 ].cint == 0 ) && ( mem [l + 5 ].hh .v.RH == -268435455L ) ) 
  l = mem [l ].hh .v.RH ;
  else if ( d ) 
  while ( ( mem [l ].hh .v.RH != -268435455L ) && ( ! ( ( l >= himemmin ) || 
  ( mem [l ].hh.b0 < 9 ) ) ) ) l = mem [l ].hh .v.RH ;
  hliststacklevel = 0 ;
  run = true ;
  do {
      t = l ;
    while ( run && ( mem [l ].hh.b0 == 0 ) && ( mem [l + 5 ].hh .v.RH != 
    -268435455L ) ) {
	
      pushnode ( l ) ;
      l = mem [l + 5 ].hh .v.RH ;
    } 
    while ( run && ( ! ( l >= himemmin ) && ( ( mem [l ].hh.b0 == 3 ) || ( 
    mem [l ].hh.b0 == 4 ) || ( mem [l ].hh.b0 == 5 ) || ( mem [l ].hh.b0 
    == 12 ) || ( ( mem [l ].hh.b0 == 8 ) && ( mem [l ].hh.b1 != 12 ) && ( 
    mem [l ].hh.b1 != 10 ) ) || ( ( mem [l ].hh.b0 == 7 ) && ( mem [l + 1 
    ].hh .v.LH == -268435455L ) && ( mem [l + 1 ].hh .v.RH == -268435455L ) 
    && ( mem [l ].hh.b1 == 0 ) ) || ( ( mem [l ].hh.b0 == 9 ) && ( mem [l 
    + 1 ].cint == 0 ) ) || ( ( mem [l ].hh.b0 == 11 ) && ( ( mem [l + 1 ]
    .cint == 0 ) || ( mem [l ].hh.b1 == 0 ) ) ) || ( ( mem [l ].hh.b0 == 
    10 ) && ( mem [l + 1 ].hh .v.LH == membot ) ) || ( ( mem [l ].hh.b0 == 
    0 ) && ( mem [l + 1 ].cint == 0 ) && ( mem [l + 3 ].cint == 0 ) && ( 
    mem [l + 2 ].cint == 0 ) && ( mem [l + 5 ].hh .v.RH == -268435455L ) ) 
    ) ) ) {
	
      while ( ( mem [l ].hh .v.RH == -268435455L ) && ( hliststacklevel > 0 
      ) ) {
	  
	l = popnode () ;
      } 
      if ( mem [l ].hh .v.RH != -268435455L ) 
      l = mem [l ].hh .v.RH ;
      else if ( hliststacklevel == 0 ) 
      run = false ;
    } 
  } while ( ! ( t == l ) ) ;
  Result = l ;
  return Result ;
} 
halfword 
zfindprotcharright ( halfword l , halfword r ) 
{
  register halfword Result; findprotcharright_regmem 
  halfword t  ;
  boolean run  ;
  Result = -268435455L ;
  if ( r == -268435455L ) 
  return Result ;
  hliststacklevel = 0 ;
  run = true ;
  do {
      t = r ;
    while ( run && ( mem [r ].hh.b0 == 0 ) && ( mem [r + 5 ].hh .v.RH != 
    -268435455L ) ) {
	
      pushnode ( l ) ;
      pushnode ( r ) ;
      l = mem [r + 5 ].hh .v.RH ;
      r = l ;
      while ( mem [r ].hh .v.RH != -268435455L ) r = mem [r ].hh .v.RH ;
    } 
    while ( run && ( ! ( r >= himemmin ) && ( ( mem [r ].hh.b0 == 3 ) || ( 
    mem [r ].hh.b0 == 4 ) || ( mem [r ].hh.b0 == 5 ) || ( mem [r ].hh.b0 
    == 12 ) || ( ( mem [r ].hh.b0 == 8 ) && ( mem [r ].hh.b1 != 12 ) && ( 
    mem [r ].hh.b1 != 10 ) ) || ( ( mem [r ].hh.b0 == 7 ) && ( mem [r + 1 
    ].hh .v.LH == -268435455L ) && ( mem [r + 1 ].hh .v.RH == -268435455L ) 
    && ( mem [r ].hh.b1 == 0 ) ) || ( ( mem [r ].hh.b0 == 9 ) && ( mem [r 
    + 1 ].cint == 0 ) ) || ( ( mem [r ].hh.b0 == 11 ) && ( ( mem [r + 1 ]
    .cint == 0 ) || ( mem [r ].hh.b1 == 0 ) ) ) || ( ( mem [r ].hh.b0 == 
    10 ) && ( mem [r + 1 ].hh .v.LH == membot ) ) || ( ( mem [r ].hh.b0 == 
    0 ) && ( mem [r + 1 ].cint == 0 ) && ( mem [r + 3 ].cint == 0 ) && ( 
    mem [r + 2 ].cint == 0 ) && ( mem [r + 5 ].hh .v.RH == -268435455L ) ) 
    ) ) ) {
	
      while ( ( r == l ) && ( hliststacklevel > 0 ) ) {
	  
	r = popnode () ;
	l = popnode () ;
      } 
      if ( ( r != l ) && ( r != -268435455L ) ) 
      r = prevrightmost ( l , r ) ;
      else if ( ( r == l ) && ( hliststacklevel == 0 ) ) 
      run = false ;
    } 
  } while ( ! ( t == r ) ) ;
  Result = r ;
  return Result ;
} 
scaled 
ztotalpw ( halfword q , halfword p ) 
{
  register scaled Result; totalpw_regmem 
  halfword l, r  ;
  integer n  ;
  if ( mem [q + 1 ].hh .v.RH == -268435455L ) 
  l = firstp ;
  else l = mem [mem [q + 1 ].hh .v.RH + 1 ].hh .v.RH ;
  r = prevrightmost ( prevp , p ) ;
  if ( ( p != -268435455L ) && ( mem [p ].hh.b0 == 7 ) && ( mem [p + 1 ]
  .hh .v.LH != -268435455L ) ) 
  {
    r = mem [p + 1 ].hh .v.LH ;
    while ( mem [r ].hh .v.RH != -268435455L ) r = mem [r ].hh .v.RH ;
  } 
  else r = findprotcharright ( l , r ) ;
  if ( ( l != -268435455L ) && ( mem [l ].hh.b0 == 7 ) ) 
  {
    if ( mem [l + 1 ].hh .v.RH != -268435455L ) 
    {
      l = mem [l + 1 ].hh .v.RH ;
      goto lab30 ;
    } 
    else {
	
      n = mem [l ].hh.b1 ;
      l = mem [l ].hh .v.RH ;
      while ( n > 0 ) {
	  
	if ( mem [l ].hh .v.RH != -268435455L ) 
	l = mem [l ].hh .v.RH ;
	decr ( n ) ;
      } 
    } 
  } 
  l = findprotcharleft ( l , true ) ;
  lab30: Result = charpw ( l , 0 ) + charpw ( r , 1 ) ;
  return Result ;
} 
void 
ztrybreak ( integer pi , smallnumber breaktype ) 
{
  /* 10 30 31 22 60 40 45 */ trybreak_regmem 
  halfword r  ;
  scaled marginkernstretch  ;
  scaled marginkernshrink  ;
  halfword lp, rp, cp  ;
  halfword prevr  ;
  halfword oldl  ;
  boolean nobreakyet  ;
  halfword prevprevr  ;
  halfword s  ;
  halfword q  ;
  halfword v  ;
  integer t  ;
  internalfontnumber f  ;
  halfword l  ;
  boolean noderstaysactive  ;
  scaled linewidth  ;
  unsigned char fitclass  ;
  halfword b  ;
  integer d  ;
  boolean artificialdemerits  ;
  halfword savelink  ;
  scaled shortfall  ;
  scaled g  ;
  if ( abs ( pi ) >= 10000 ) {
      
    if ( pi > 0 ) 
    goto lab10 ;
    else pi = -10000 ;
  } 
  nobreakyet = true ;
  prevr = memtop - 7 ;
  oldl = 0 ;
  curactivewidth [1 ]= activewidth [1 ];
  curactivewidth [2 ]= activewidth [2 ];
  curactivewidth [3 ]= activewidth [3 ];
  curactivewidth [4 ]= activewidth [4 ];
  curactivewidth [5 ]= activewidth [5 ];
  curactivewidth [6 ]= activewidth [6 ];
  if ( eqtb [29349 ].cint > 1 ) 
  {
    curactivewidth [7 ]= activewidth [7 ];
    curactivewidth [8 ]= activewidth [8 ];
  } 
  while ( true ) {
      
    lab22: r = mem [prevr ].hh .v.RH ;
    if ( mem [r ].hh.b0 == 2 ) 
    {
      curactivewidth [1 ]= curactivewidth [1 ]+ mem [r + 1 ].cint ;
      curactivewidth [2 ]= curactivewidth [2 ]+ mem [r + 2 ].cint ;
      curactivewidth [3 ]= curactivewidth [3 ]+ mem [r + 3 ].cint ;
      curactivewidth [4 ]= curactivewidth [4 ]+ mem [r + 4 ].cint ;
      curactivewidth [5 ]= curactivewidth [5 ]+ mem [r + 5 ].cint ;
      curactivewidth [6 ]= curactivewidth [6 ]+ mem [r + 6 ].cint ;
      if ( eqtb [29349 ].cint > 1 ) 
      {
	curactivewidth [7 ]= curactivewidth [7 ]+ mem [r + 7 ].cint ;
	curactivewidth [8 ]= curactivewidth [8 ]+ mem [r + 8 ].cint ;
      } 
      prevprevr = prevr ;
      prevr = r ;
      goto lab22 ;
    } 
    {
      l = mem [r + 1 ].hh .v.LH ;
      if ( l > oldl ) 
      {
	if ( ( minimumdemerits < 1073741823L ) && ( ( oldl != easyline ) || ( 
	r == memtop - 7 ) ) ) 
	{
	  if ( nobreakyet ) 
	  {
	    nobreakyet = false ;
	    breakwidth [1 ]= background [1 ];
	    breakwidth [2 ]= background [2 ];
	    breakwidth [3 ]= background [3 ];
	    breakwidth [4 ]= background [4 ];
	    breakwidth [5 ]= background [5 ];
	    breakwidth [6 ]= background [6 ];
	    if ( eqtb [29349 ].cint > 1 ) 
	    {
	      breakwidth [7 ]= background [7 ];
	      breakwidth [8 ]= background [8 ];
	    } 
	    s = curp ;
	    if ( breaktype > 0 ) {
		
	      if ( curp != -268435455L ) 
	      {
		t = mem [curp ].hh.b1 ;
		v = curp ;
		s = mem [curp + 1 ].hh .v.RH ;
		while ( t > 0 ) {
		    
		  decr ( t ) ;
		  v = mem [v ].hh .v.RH ;
		  if ( ( v >= himemmin ) ) 
		  {
		    f = mem [v ].hh.b0 ;
		    breakwidth [1 ]= breakwidth [1 ]- fontinfo [widthbase 
		    [f ]+ fontinfo [charbase [f ]+ effectivechar ( true , 
		    f , mem [v ].hh.b1 ) ].qqqq .b0 ].cint ;
		    if ( ( eqtb [29349 ].cint > 1 ) && checkexpandpars ( f ) 
		    ) 
		    {
		      prevcharp = v ;
		      breakwidth [7 ]= breakwidth [7 ]- charstretch ( f , 
		      mem [v ].hh.b1 ) ;
		      breakwidth [8 ]= breakwidth [8 ]- charshrink ( f , 
		      mem [v ].hh.b1 ) ;
		    } 
		  } 
		  else switch ( mem [v ].hh.b0 ) 
		  {case 6 : 
		    {
		      f = mem [v + 1 ].hh.b0 ;
		      breakwidth [1 ]= breakwidth [1 ]- fontinfo [
		      widthbase [f ]+ fontinfo [charbase [f ]+ 
		      effectivechar ( true , f , mem [v + 1 ].hh.b1 ) ]
		      .qqqq .b0 ].cint ;
		      if ( ( eqtb [29349 ].cint > 1 ) && checkexpandpars ( f 
		      ) ) 
		      {
			prevcharp = v ;
			breakwidth [7 ]= breakwidth [7 ]- charstretch ( f 
			, mem [v + 1 ].hh.b1 ) ;
			breakwidth [8 ]= breakwidth [8 ]- charshrink ( f , 
			mem [v + 1 ].hh.b1 ) ;
		      } 
		    } 
		    break ;
		  case 0 : 
		  case 1 : 
		  case 2 : 
		  case 11 : 
		    {
		      breakwidth [1 ]= breakwidth [1 ]- mem [v + 1 ]
		      .cint ;
		      if ( ( mem [v ].hh.b0 == 11 ) && ( eqtb [29349 ]
		      .cint > 1 ) && ( mem [v ].hh.b1 == 0 ) ) 
		      {
			breakwidth [7 ]= breakwidth [7 ]- kernstretch ( v 
			) ;
			breakwidth [8 ]= breakwidth [8 ]- kernshrink ( v ) 
			;
		      } 
		    } 
		    break ;
		    default: 
		    confusion ( 1329 ) ;
		    break ;
		  } 
		} 
		while ( s != -268435455L ) {
		    
		  if ( ( s >= himemmin ) ) 
		  {
		    f = mem [s ].hh.b0 ;
		    breakwidth [1 ]= breakwidth [1 ]+ fontinfo [widthbase 
		    [f ]+ fontinfo [charbase [f ]+ effectivechar ( true , 
		    f , mem [s ].hh.b1 ) ].qqqq .b0 ].cint ;
		    if ( ( eqtb [29349 ].cint > 1 ) && checkexpandpars ( f ) 
		    ) 
		    {
		      prevcharp = s ;
		      breakwidth [7 ]= breakwidth [7 ]+ charstretch ( f , 
		      mem [s ].hh.b1 ) ;
		      breakwidth [8 ]= breakwidth [8 ]+ charshrink ( f , 
		      mem [s ].hh.b1 ) ;
		    } 
		  } 
		  else switch ( mem [s ].hh.b0 ) 
		  {case 6 : 
		    {
		      f = mem [s + 1 ].hh.b0 ;
		      breakwidth [1 ]= breakwidth [1 ]+ fontinfo [
		      widthbase [f ]+ fontinfo [charbase [f ]+ 
		      effectivechar ( true , f , mem [s + 1 ].hh.b1 ) ]
		      .qqqq .b0 ].cint ;
		      if ( ( eqtb [29349 ].cint > 1 ) && checkexpandpars ( f 
		      ) ) 
		      {
			prevcharp = s ;
			breakwidth [7 ]= breakwidth [7 ]+ charstretch ( f 
			, mem [s + 1 ].hh.b1 ) ;
			breakwidth [8 ]= breakwidth [8 ]+ charshrink ( f , 
			mem [s + 1 ].hh.b1 ) ;
		      } 
		    } 
		    break ;
		  case 0 : 
		  case 1 : 
		  case 2 : 
		  case 11 : 
		    {
		      breakwidth [1 ]= breakwidth [1 ]+ mem [s + 1 ]
		      .cint ;
		      if ( ( mem [s ].hh.b0 == 11 ) && ( eqtb [29349 ]
		      .cint > 1 ) && ( mem [s ].hh.b1 == 0 ) ) 
		      {
			breakwidth [7 ]= breakwidth [7 ]+ kernstretch ( s 
			) ;
			breakwidth [8 ]= breakwidth [8 ]+ kernshrink ( s ) 
			;
		      } 
		    } 
		    break ;
		    default: 
		    confusion ( 1330 ) ;
		    break ;
		  } 
		  s = mem [s ].hh .v.RH ;
		} 
		breakwidth [1 ]= breakwidth [1 ]+ discwidth [1 ];
		if ( eqtb [29349 ].cint > 1 ) 
		{
		  breakwidth [7 ]= breakwidth [7 ]+ discwidth [7 ];
		  breakwidth [8 ]= breakwidth [8 ]+ discwidth [8 ];
		} 
		if ( mem [curp + 1 ].hh .v.RH == -268435455L ) 
		s = mem [v ].hh .v.RH ;
	      } 
	    } 
	    while ( s != -268435455L ) {
		
	      if ( ( s >= himemmin ) ) 
	      goto lab30 ;
	      switch ( mem [s ].hh.b0 ) 
	      {case 10 : 
		{
		  v = mem [s + 1 ].hh .v.LH ;
		  breakwidth [1 ]= breakwidth [1 ]- mem [v + 1 ].cint ;
		  breakwidth [2 + mem [v ].hh.b0 ]= breakwidth [2 + mem [
		  v ].hh.b0 ]- mem [v + 2 ].cint ;
		  breakwidth [6 ]= breakwidth [6 ]- mem [v + 3 ].cint ;
		} 
		break ;
	      case 12 : 
		;
		break ;
	      case 9 : 
		breakwidth [1 ]= breakwidth [1 ]- mem [s + 1 ].cint ;
		break ;
	      case 11 : 
		if ( mem [s ].hh.b1 != 1 ) 
		goto lab30 ;
		else breakwidth [1 ]= breakwidth [1 ]- mem [s + 1 ].cint 
		;
		break ;
		default: 
		goto lab30 ;
		break ;
	      } 
	      s = mem [s ].hh .v.RH ;
	    } 
	    lab30: ;
	  } 
	  if ( mem [prevr ].hh.b0 == 2 ) 
	  {
	    mem [prevr + 1 ].cint = mem [prevr + 1 ].cint - curactivewidth 
	    [1 ]+ breakwidth [1 ];
	    mem [prevr + 2 ].cint = mem [prevr + 2 ].cint - curactivewidth 
	    [2 ]+ breakwidth [2 ];
	    mem [prevr + 3 ].cint = mem [prevr + 3 ].cint - curactivewidth 
	    [3 ]+ breakwidth [3 ];
	    mem [prevr + 4 ].cint = mem [prevr + 4 ].cint - curactivewidth 
	    [4 ]+ breakwidth [4 ];
	    mem [prevr + 5 ].cint = mem [prevr + 5 ].cint - curactivewidth 
	    [5 ]+ breakwidth [5 ];
	    mem [prevr + 6 ].cint = mem [prevr + 6 ].cint - curactivewidth 
	    [6 ]+ breakwidth [6 ];
	    if ( eqtb [29349 ].cint > 1 ) 
	    {
	      mem [prevr + 7 ].cint = mem [prevr + 7 ].cint - 
	      curactivewidth [7 ]+ breakwidth [7 ];
	      mem [prevr + 8 ].cint = mem [prevr + 8 ].cint - 
	      curactivewidth [8 ]+ breakwidth [8 ];
	    } 
	  } 
	  else if ( prevr == memtop - 7 ) 
	  {
	    activewidth [1 ]= breakwidth [1 ];
	    activewidth [2 ]= breakwidth [2 ];
	    activewidth [3 ]= breakwidth [3 ];
	    activewidth [4 ]= breakwidth [4 ];
	    activewidth [5 ]= breakwidth [5 ];
	    activewidth [6 ]= breakwidth [6 ];
	    if ( eqtb [29349 ].cint > 1 ) 
	    {
	      activewidth [7 ]= breakwidth [7 ];
	      activewidth [8 ]= breakwidth [8 ];
	    } 
	  } 
	  else {
	      
	    q = getnode ( 9 ) ;
	    mem [q ].hh .v.RH = r ;
	    mem [q ].hh.b0 = 2 ;
	    mem [q ].hh.b1 = 0 ;
	    mem [q + 1 ].cint = breakwidth [1 ]- curactivewidth [1 ];
	    mem [q + 2 ].cint = breakwidth [2 ]- curactivewidth [2 ];
	    mem [q + 3 ].cint = breakwidth [3 ]- curactivewidth [3 ];
	    mem [q + 4 ].cint = breakwidth [4 ]- curactivewidth [4 ];
	    mem [q + 5 ].cint = breakwidth [5 ]- curactivewidth [5 ];
	    mem [q + 6 ].cint = breakwidth [6 ]- curactivewidth [6 ];
	    if ( eqtb [29349 ].cint > 1 ) 
	    {
	      mem [q + 7 ].cint = breakwidth [7 ]- curactivewidth [7 ];
	      mem [q + 8 ].cint = breakwidth [8 ]- curactivewidth [8 ];
	    } 
	    mem [prevr ].hh .v.RH = q ;
	    prevprevr = prevr ;
	    prevr = q ;
	  } 
	  if ( abs ( eqtb [29290 ].cint ) >= 1073741823L - minimumdemerits ) 
	  minimumdemerits = 1073741822L ;
	  else minimumdemerits = minimumdemerits + abs ( eqtb [29290 ].cint 
	  ) ;
	  {register integer for_end; fitclass = 0 ;for_end = 3 ; if ( 
	  fitclass <= for_end) do 
	    {
	      if ( minimaldemerits [fitclass ]<= minimumdemerits ) 
	      {
		q = getnode ( 2 ) ;
		mem [q ].hh .v.RH = passive ;
		passive = q ;
		mem [q + 1 ].hh .v.RH = curp ;
	;
#ifdef STAT
		incr ( passnumber ) ;
		mem [q ].hh .v.LH = passnumber ;
#endif /* STAT */
		mem [q + 1 ].hh .v.LH = bestplace [fitclass ];
		q = getnode ( activenodesize ) ;
		mem [q + 1 ].hh .v.RH = passive ;
		mem [q + 1 ].hh .v.LH = bestplline [fitclass ]+ 1 ;
		mem [q ].hh.b1 = fitclass ;
		mem [q ].hh.b0 = breaktype ;
		mem [q + 2 ].cint = minimaldemerits [fitclass ];
		if ( dolastlinefit ) 
		{
		  mem [q + 3 ].cint = bestplshort [fitclass ];
		  mem [q + 4 ].cint = bestplglue [fitclass ];
		} 
		mem [q ].hh .v.RH = r ;
		mem [prevr ].hh .v.RH = q ;
		prevr = q ;
	;
#ifdef STAT
		if ( eqtb [29306 ].cint > 0 ) 
		{
		  printnl ( 1331 ) ;
		  printint ( mem [passive ].hh .v.LH ) ;
		  print ( 1332 ) ;
		  printint ( mem [q + 1 ].hh .v.LH - 1 ) ;
		  printchar ( 46 ) ;
		  printint ( fitclass ) ;
		  if ( breaktype == 1 ) 
		  printchar ( 45 ) ;
		  print ( 1333 ) ;
		  printint ( mem [q + 2 ].cint ) ;
		  if ( dolastlinefit ) 
		  {
		    print ( 2048 ) ;
		    printscaled ( mem [q + 3 ].cint ) ;
		    if ( curp == -268435455L ) 
		    print ( 2049 ) ;
		    else print ( 1403 ) ;
		    printscaled ( mem [q + 4 ].cint ) ;
		  } 
		  print ( 1334 ) ;
		  if ( mem [passive + 1 ].hh .v.LH == -268435455L ) 
		  printchar ( 48 ) ;
		  else printint ( mem [mem [passive + 1 ].hh .v.LH ].hh 
		  .v.LH ) ;
		} 
#endif /* STAT */
	      } 
	      minimaldemerits [fitclass ]= 1073741823L ;
	    } 
	  while ( fitclass++ < for_end ) ;} 
	  minimumdemerits = 1073741823L ;
	  if ( r != memtop - 7 ) 
	  {
	    q = getnode ( 9 ) ;
	    mem [q ].hh .v.RH = r ;
	    mem [q ].hh.b0 = 2 ;
	    mem [q ].hh.b1 = 0 ;
	    mem [q + 1 ].cint = curactivewidth [1 ]- breakwidth [1 ];
	    mem [q + 2 ].cint = curactivewidth [2 ]- breakwidth [2 ];
	    mem [q + 3 ].cint = curactivewidth [3 ]- breakwidth [3 ];
	    mem [q + 4 ].cint = curactivewidth [4 ]- breakwidth [4 ];
	    mem [q + 5 ].cint = curactivewidth [5 ]- breakwidth [5 ];
	    mem [q + 6 ].cint = curactivewidth [6 ]- breakwidth [6 ];
	    if ( eqtb [29349 ].cint > 1 ) 
	    {
	      mem [q + 7 ].cint = curactivewidth [7 ]- breakwidth [7 ];
	      mem [q + 8 ].cint = curactivewidth [8 ]- breakwidth [8 ];
	    } 
	    mem [prevr ].hh .v.RH = q ;
	    prevprevr = prevr ;
	    prevr = q ;
	  } 
	} 
	if ( r == memtop - 7 ) 
	goto lab10 ;
	if ( l > easyline ) 
	{
	  linewidth = secondwidth ;
	  oldl = 268435454L ;
	} 
	else {
	    
	  oldl = l ;
	  if ( l > lastspecialline ) 
	  linewidth = secondwidth ;
	  else if ( eqtb [27158 ].hh .v.RH == -268435455L ) 
	  linewidth = firstwidth ;
	  else linewidth = mem [eqtb [27158 ].hh .v.RH + 2 * l ].cint ;
	} 
      } 
    } 
    {
      artificialdemerits = false ;
      shortfall = linewidth - curactivewidth [1 ];
      if ( eqtb [29350 ].cint > 1 ) 
      shortfall = shortfall + totalpw ( r , curp ) ;
      if ( ( eqtb [29349 ].cint > 1 ) && ( shortfall != 0 ) ) 
      {
	marginkernstretch = 0 ;
	marginkernshrink = 0 ;
	if ( eqtb [29350 ].cint > 1 ) 
	{
	  lp = lastleftmostchar ;
	  rp = lastrightmostchar ;
	  {
	    cp = avail ;
	    if ( cp == -268435455L ) 
	    cp = getavail () ;
	    else {
		
	      avail = mem [cp ].hh .v.RH ;
	      mem [cp ].hh .v.RH = -268435455L ;
	;
#ifdef STAT
	      incr ( dynused ) ;
#endif /* STAT */
	    } 
	  } 
	  if ( lp != -268435455L ) 
	  {
	    mem [cp ].hh.b1 = mem [lp ].hh.b1 ;
	    mem [cp ].hh.b0 = mem [lp ].hh.b0 ;
	    dosubstfont ( cp , 1000 ) ;
	    if ( mem [cp ].hh.b0 != mem [lp ].hh.b0 ) 
	    marginkernstretch = marginkernstretch + charpw ( lp , 0 ) - charpw 
	    ( cp , 0 ) ;
	    mem [cp ].hh.b0 = mem [lp ].hh.b0 ;
	    dosubstfont ( cp , -1000 ) ;
	    if ( mem [cp ].hh.b0 != mem [lp ].hh.b0 ) 
	    marginkernshrink = marginkernshrink + charpw ( cp , 0 ) - charpw ( 
	    lp , 0 ) ;
	  } 
	  if ( rp != -268435455L ) 
	  {
	    mem [cp ].hh.b1 = mem [rp ].hh.b1 ;
	    mem [cp ].hh.b0 = mem [rp ].hh.b0 ;
	    dosubstfont ( cp , 1000 ) ;
	    if ( mem [cp ].hh.b0 != mem [rp ].hh.b0 ) 
	    marginkernstretch = marginkernstretch + charpw ( rp , 0 ) - charpw 
	    ( cp , 0 ) ;
	    mem [cp ].hh.b0 = mem [rp ].hh.b0 ;
	    dosubstfont ( cp , -1000 ) ;
	    if ( mem [cp ].hh.b0 != mem [rp ].hh.b0 ) 
	    marginkernshrink = marginkernshrink + charpw ( cp , 0 ) - charpw ( 
	    rp , 0 ) ;
	  } 
	  {
	    mem [cp ].hh .v.RH = avail ;
	    avail = cp ;
	;
#ifdef STAT
	    decr ( dynused ) ;
#endif /* STAT */
	  } 
	} 
	if ( ( shortfall > 0 ) && ( ( curactivewidth [7 ]+ marginkernstretch 
	) > 0 ) ) 
	{
	  if ( ( curactivewidth [7 ]+ marginkernstretch ) > shortfall ) 
	  shortfall = ( ( curactivewidth [7 ]+ marginkernstretch ) / ( 
	  maxstretchratio / curfontstep ) ) / 2 ;
	  else shortfall = shortfall - ( curactivewidth [7 ]+ 
	  marginkernstretch ) ;
	} 
	else if ( ( shortfall < 0 ) && ( ( curactivewidth [8 ]+ 
	marginkernshrink ) > 0 ) ) 
	{
	  if ( ( curactivewidth [8 ]+ marginkernshrink ) > - (integer) 
	  shortfall ) 
	  shortfall = - (integer) ( ( curactivewidth [8 ]+ marginkernshrink 
	  ) / ( maxshrinkratio / curfontstep ) ) / 2 ;
	  else shortfall = shortfall + ( curactivewidth [8 ]+ 
	  marginkernshrink ) ;
	} 
      } 
      if ( shortfall > 0 ) {
	  
	if ( ( curactivewidth [3 ]!= 0 ) || ( curactivewidth [4 ]!= 0 ) || 
	( curactivewidth [5 ]!= 0 ) ) 
	{
	  if ( dolastlinefit ) 
	  {
	    if ( curp == -268435455L ) 
	    {
	      if ( ( mem [r + 3 ].cint == 0 ) || ( mem [r + 4 ].cint <= 0 
	      ) ) 
	      goto lab45 ;
	      if ( ( curactivewidth [3 ]!= fillwidth [0 ]) || ( 
	      curactivewidth [4 ]!= fillwidth [1 ]) || ( curactivewidth [
	      5 ]!= fillwidth [2 ]) ) 
	      goto lab45 ;
	      if ( mem [r + 3 ].cint > 0 ) 
	      g = curactivewidth [2 ];
	      else g = curactivewidth [6 ];
	      if ( g <= 0 ) 
	      goto lab45 ;
	      aritherror = false ;
	      g = fract ( g , mem [r + 3 ].cint , mem [r + 4 ].cint , 
	      1073741823L ) ;
	      if ( eqtb [29371 ].cint < 1000 ) 
	      g = fract ( g , eqtb [29371 ].cint , 1000 , 1073741823L ) ;
	      if ( aritherror ) {
		  
		if ( mem [r + 3 ].cint > 0 ) 
		g = 1073741823L ;
		else g = -1073741823L ;
	      } 
	      if ( g > 0 ) 
	      {
		if ( g > shortfall ) 
		g = shortfall ;
		if ( g > 7230584L ) {
		    
		  if ( curactivewidth [2 ]< 1663497L ) 
		  {
		    b = 10000 ;
		    fitclass = 0 ;
		    goto lab40 ;
		  } 
		} 
		b = badness ( g , curactivewidth [2 ]) ;
		if ( b > 12 ) {
		    
		  if ( b > 99 ) 
		  fitclass = 0 ;
		  else fitclass = 1 ;
		} 
		else fitclass = 2 ;
		goto lab40 ;
	      } 
	      else if ( g < 0 ) 
	      {
		if ( - (integer) g > curactivewidth [6 ]) 
		g = - (integer) curactivewidth [6 ];
		b = badness ( - (integer) g , curactivewidth [6 ]) ;
		if ( b > 12 ) 
		fitclass = 3 ;
		else fitclass = 2 ;
		goto lab40 ;
	      } 
	      lab45: ;
	    } 
	    shortfall = 0 ;
	  } 
	  b = 0 ;
	  fitclass = 2 ;
	} 
	else {
	    
	  if ( shortfall > 7230584L ) {
	      
	    if ( curactivewidth [2 ]< 1663497L ) 
	    {
	      b = 10000 ;
	      fitclass = 0 ;
	      goto lab31 ;
	    } 
	  } 
	  b = badness ( shortfall , curactivewidth [2 ]) ;
	  if ( b > 12 ) {
	      
	    if ( b > 99 ) 
	    fitclass = 0 ;
	    else fitclass = 1 ;
	  } 
	  else fitclass = 2 ;
	  lab31: ;
	} 
      } 
      else {
	  
	if ( - (integer) shortfall > curactivewidth [6 ]) 
	b = 10001 ;
	else b = badness ( - (integer) shortfall , curactivewidth [6 ]) ;
	if ( b > 12 ) 
	fitclass = 3 ;
	else fitclass = 2 ;
      } 
      if ( dolastlinefit ) 
      {
	if ( curp == -268435455L ) 
	shortfall = 0 ;
	if ( shortfall > 0 ) 
	g = curactivewidth [2 ];
	else if ( shortfall < 0 ) 
	g = curactivewidth [6 ];
	else g = 0 ;
      } 
      lab40: if ( ( b > 10000 ) || ( pi == -10000 ) ) 
      {
	if ( finalpass && ( minimumdemerits == 1073741823L ) && ( mem [r ]
	.hh .v.RH == memtop - 7 ) && ( prevr == memtop - 7 ) ) 
	artificialdemerits = true ;
	else if ( b > threshold ) 
	goto lab60 ;
	noderstaysactive = false ;
      } 
      else {
	  
	prevr = r ;
	if ( b > threshold ) 
	goto lab22 ;
	noderstaysactive = true ;
      } 
      if ( artificialdemerits ) 
      d = 0 ;
      else {
	  
	d = eqtb [29276 ].cint + b ;
	if ( abs ( d ) >= 10000 ) 
	d = 100000000L ;
	else d = d * d ;
	if ( pi != 0 ) {
	    
	  if ( pi > 0 ) 
	  d = d + pi * pi ;
	  else if ( pi > -10000 ) 
	  d = d - pi * pi ;
	} 
	if ( ( breaktype == 1 ) && ( mem [r ].hh.b0 == 1 ) ) {
	    
	  if ( curp != -268435455L ) 
	  d = d + eqtb [29288 ].cint ;
	  else d = d + eqtb [29289 ].cint ;
	} 
	if ( abs ( fitclass - mem [r ].hh.b1 ) > 1 ) 
	d = d + eqtb [29290 ].cint ;
      } 
	;
#ifdef STAT
      if ( eqtb [29306 ].cint > 0 ) 
      {
	if ( printednode != curp ) 
	{
	  printnl ( 345 ) ;
	  if ( curp == -268435455L ) 
	  shortdisplay ( mem [printednode ].hh .v.RH ) ;
	  else {
	      
	    savelink = mem [curp ].hh .v.RH ;
	    mem [curp ].hh .v.RH = -268435455L ;
	    printnl ( 345 ) ;
	    shortdisplay ( mem [printednode ].hh .v.RH ) ;
	    mem [curp ].hh .v.RH = savelink ;
	  } 
	  printednode = curp ;
	} 
	printnl ( 64 ) ;
	if ( curp == -268435455L ) 
	printesc ( 676 ) ;
	else if ( mem [curp ].hh.b0 != 10 ) 
	{
	  if ( mem [curp ].hh.b0 == 12 ) 
	  printesc ( 606 ) ;
	  else if ( mem [curp ].hh.b0 == 7 ) 
	  printesc ( 357 ) ;
	  else if ( mem [curp ].hh.b0 == 11 ) 
	  printesc ( 322 ) ;
	  else printesc ( 351 ) ;
	} 
	print ( 1335 ) ;
	if ( mem [r + 1 ].hh .v.RH == -268435455L ) 
	printchar ( 48 ) ;
	else printint ( mem [mem [r + 1 ].hh .v.RH ].hh .v.LH ) ;
	print ( 1336 ) ;
	if ( b > 10000 ) 
	printchar ( 42 ) ;
	else printint ( b ) ;
	print ( 1337 ) ;
	printint ( pi ) ;
	print ( 1338 ) ;
	if ( artificialdemerits ) 
	printchar ( 42 ) ;
	else printint ( d ) ;
      } 
#endif /* STAT */
      d = d + mem [r + 2 ].cint ;
      if ( d <= minimaldemerits [fitclass ]) 
      {
	minimaldemerits [fitclass ]= d ;
	bestplace [fitclass ]= mem [r + 1 ].hh .v.RH ;
	bestplline [fitclass ]= l ;
	if ( dolastlinefit ) 
	{
	  bestplshort [fitclass ]= shortfall ;
	  bestplglue [fitclass ]= g ;
	} 
	if ( d < minimumdemerits ) 
	minimumdemerits = d ;
      } 
      if ( noderstaysactive ) 
      goto lab22 ;
      lab60: mem [prevr ].hh .v.RH = mem [r ].hh .v.RH ;
      freenode ( r , activenodesize ) ;
      if ( prevr == memtop - 7 ) 
      {
	r = mem [memtop - 7 ].hh .v.RH ;
	if ( mem [r ].hh.b0 == 2 ) 
	{
	  activewidth [1 ]= activewidth [1 ]+ mem [r + 1 ].cint ;
	  activewidth [2 ]= activewidth [2 ]+ mem [r + 2 ].cint ;
	  activewidth [3 ]= activewidth [3 ]+ mem [r + 3 ].cint ;
	  activewidth [4 ]= activewidth [4 ]+ mem [r + 4 ].cint ;
	  activewidth [5 ]= activewidth [5 ]+ mem [r + 5 ].cint ;
	  activewidth [6 ]= activewidth [6 ]+ mem [r + 6 ].cint ;
	  if ( eqtb [29349 ].cint > 1 ) 
	  {
	    activewidth [7 ]= activewidth [7 ]+ mem [r + 7 ].cint ;
	    activewidth [8 ]= activewidth [8 ]+ mem [r + 8 ].cint ;
	  } 
	  curactivewidth [1 ]= activewidth [1 ];
	  curactivewidth [2 ]= activewidth [2 ];
	  curactivewidth [3 ]= activewidth [3 ];
	  curactivewidth [4 ]= activewidth [4 ];
	  curactivewidth [5 ]= activewidth [5 ];
	  curactivewidth [6 ]= activewidth [6 ];
	  if ( eqtb [29349 ].cint > 1 ) 
	  {
	    curactivewidth [7 ]= activewidth [7 ];
	    curactivewidth [8 ]= activewidth [8 ];
	  } 
	  mem [memtop - 7 ].hh .v.RH = mem [r ].hh .v.RH ;
	  freenode ( r , 9 ) ;
	} 
      } 
      else if ( mem [prevr ].hh.b0 == 2 ) 
      {
	r = mem [prevr ].hh .v.RH ;
	if ( r == memtop - 7 ) 
	{
	  curactivewidth [1 ]= curactivewidth [1 ]- mem [prevr + 1 ]
	  .cint ;
	  curactivewidth [2 ]= curactivewidth [2 ]- mem [prevr + 2 ]
	  .cint ;
	  curactivewidth [3 ]= curactivewidth [3 ]- mem [prevr + 3 ]
	  .cint ;
	  curactivewidth [4 ]= curactivewidth [4 ]- mem [prevr + 4 ]
	  .cint ;
	  curactivewidth [5 ]= curactivewidth [5 ]- mem [prevr + 5 ]
	  .cint ;
	  curactivewidth [6 ]= curactivewidth [6 ]- mem [prevr + 6 ]
	  .cint ;
	  if ( eqtb [29349 ].cint > 1 ) 
	  {
	    curactivewidth [7 ]= curactivewidth [7 ]- mem [prevr + 7 ]
	    .cint ;
	    curactivewidth [8 ]= curactivewidth [8 ]- mem [prevr + 8 ]
	    .cint ;
	  } 
	  mem [prevprevr ].hh .v.RH = memtop - 7 ;
	  freenode ( prevr , 9 ) ;
	  prevr = prevprevr ;
	} 
	else if ( mem [r ].hh.b0 == 2 ) 
	{
	  curactivewidth [1 ]= curactivewidth [1 ]+ mem [r + 1 ].cint ;
	  curactivewidth [2 ]= curactivewidth [2 ]+ mem [r + 2 ].cint ;
	  curactivewidth [3 ]= curactivewidth [3 ]+ mem [r + 3 ].cint ;
	  curactivewidth [4 ]= curactivewidth [4 ]+ mem [r + 4 ].cint ;
	  curactivewidth [5 ]= curactivewidth [5 ]+ mem [r + 5 ].cint ;
	  curactivewidth [6 ]= curactivewidth [6 ]+ mem [r + 6 ].cint ;
	  if ( eqtb [29349 ].cint > 1 ) 
	  {
	    curactivewidth [7 ]= curactivewidth [7 ]+ mem [r + 7 ].cint 
	    ;
	    curactivewidth [8 ]= curactivewidth [8 ]+ mem [r + 8 ].cint 
	    ;
	  } 
	  mem [prevr + 1 ].cint = mem [prevr + 1 ].cint + mem [r + 1 ]
	  .cint ;
	  mem [prevr + 2 ].cint = mem [prevr + 2 ].cint + mem [r + 2 ]
	  .cint ;
	  mem [prevr + 3 ].cint = mem [prevr + 3 ].cint + mem [r + 3 ]
	  .cint ;
	  mem [prevr + 4 ].cint = mem [prevr + 4 ].cint + mem [r + 4 ]
	  .cint ;
	  mem [prevr + 5 ].cint = mem [prevr + 5 ].cint + mem [r + 5 ]
	  .cint ;
	  mem [prevr + 6 ].cint = mem [prevr + 6 ].cint + mem [r + 6 ]
	  .cint ;
	  if ( eqtb [29349 ].cint > 1 ) 
	  {
	    mem [prevr + 7 ].cint = mem [prevr + 7 ].cint + mem [r + 7 ]
	    .cint ;
	    mem [prevr + 8 ].cint = mem [prevr + 8 ].cint + mem [r + 8 ]
	    .cint ;
	  } 
	  mem [prevr ].hh .v.RH = mem [r ].hh .v.RH ;
	  freenode ( r , 9 ) ;
	} 
      } 
    } 
  } 
  lab10: 
	;
#ifdef STAT
  if ( curp == printednode ) {
      
    if ( curp != -268435455L ) {
	
      if ( mem [curp ].hh.b0 == 7 ) 
      {
	t = mem [curp ].hh.b1 ;
	while ( t > 0 ) {
	    
	  decr ( t ) ;
	  printednode = mem [printednode ].hh .v.RH ;
	} 
      } 
#endif /* STAT */
    } 
  } 
} 
void 
zpostlinebreak ( boolean d ) 
{
  /* 30 31 */ postlinebreak_regmem 
  halfword q, r, s  ;
  halfword p, k  ;
  scaled w  ;
  boolean gluebreak  ;
  halfword ptmp  ;
  boolean discbreak  ;
  boolean postdiscbreak  ;
  scaled curwidth  ;
  scaled curindent  ;
  quarterword t  ;
  integer pen  ;
  halfword curline  ;
  halfword LRptr  ;
  LRptr = curlist .eTeXauxfield ;
  q = mem [bestbet + 1 ].hh .v.RH ;
  curp = -268435455L ;
  do {
      r = q ;
    q = mem [q + 1 ].hh .v.LH ;
    mem [r + 1 ].hh .v.LH = curp ;
    curp = r ;
  } while ( ! ( q == -268435455L ) ) ;
  curline = curlist .pgfield + 1 ;
  do {
      if ( ( eqtb [29374 ].cint > 0 ) ) 
    {
      q = mem [memtop - 3 ].hh .v.RH ;
      if ( LRptr != -268435455L ) 
      {
	tempptr = LRptr ;
	r = q ;
	do {
	    s = newmath ( 0 , ( mem [tempptr ].hh .v.LH - 1 ) ) ;
	  mem [s ].hh .v.RH = r ;
	  r = s ;
	  tempptr = mem [tempptr ].hh .v.RH ;
	} while ( ! ( tempptr == -268435455L ) ) ;
	mem [memtop - 3 ].hh .v.RH = r ;
      } 
      while ( q != mem [curp + 1 ].hh .v.RH ) {
	  
	if ( ! ( q >= himemmin ) ) {
	    
	  if ( mem [q ].hh.b0 == 9 ) {
	      
	    if ( odd ( mem [q ].hh.b1 ) ) 
	    {
	      if ( LRptr != -268435455L ) {
		  
		if ( mem [LRptr ].hh .v.LH == ( 4 * ( mem [q ].hh.b1 / 4 ) 
		+ 3 ) ) 
		{
		  tempptr = LRptr ;
		  LRptr = mem [tempptr ].hh .v.RH ;
		  {
		    mem [tempptr ].hh .v.RH = avail ;
		    avail = tempptr ;
	;
#ifdef STAT
		    decr ( dynused ) ;
#endif /* STAT */
		  } 
		} 
	      } 
	    } 
	    else {
		
	      tempptr = getavail () ;
	      mem [tempptr ].hh .v.LH = ( 4 * ( mem [q ].hh.b1 / 4 ) + 3 ) 
	      ;
	      mem [tempptr ].hh .v.RH = LRptr ;
	      LRptr = tempptr ;
	    } 
	  } 
	} 
	q = mem [q ].hh .v.RH ;
      } 
    } 
    q = mem [curp + 1 ].hh .v.RH ;
    discbreak = false ;
    postdiscbreak = false ;
    gluebreak = false ;
    if ( q != -268435455L ) {
	
      if ( mem [q ].hh.b0 == 10 ) 
      {
	deleteglueref ( mem [q + 1 ].hh .v.LH ) ;
	mem [q + 1 ].hh .v.LH = eqtb [26636 ].hh .v.RH ;
	mem [q ].hh.b1 = 9 ;
	incr ( mem [eqtb [26636 ].hh .v.RH ].hh .v.RH ) ;
	gluebreak = true ;
	goto lab30 ;
      } 
      else {
	  
	if ( mem [q ].hh.b0 == 7 ) 
	{
	  t = mem [q ].hh.b1 ;
	  if ( t == 0 ) 
	  r = mem [q ].hh .v.RH ;
	  else {
	      
	    r = q ;
	    while ( t > 1 ) {
		
	      r = mem [r ].hh .v.RH ;
	      decr ( t ) ;
	    } 
	    s = mem [r ].hh .v.RH ;
	    r = mem [s ].hh .v.RH ;
	    mem [s ].hh .v.RH = -268435455L ;
	    flushnodelist ( mem [q ].hh .v.RH ) ;
	    mem [q ].hh.b1 = 0 ;
	  } 
	  if ( mem [q + 1 ].hh .v.RH != -268435455L ) 
	  {
	    s = mem [q + 1 ].hh .v.RH ;
	    while ( mem [s ].hh .v.RH != -268435455L ) s = mem [s ].hh 
	    .v.RH ;
	    mem [s ].hh .v.RH = r ;
	    r = mem [q + 1 ].hh .v.RH ;
	    mem [q + 1 ].hh .v.RH = -268435455L ;
	    postdiscbreak = true ;
	  } 
	  if ( mem [q + 1 ].hh .v.LH != -268435455L ) 
	  {
	    s = mem [q + 1 ].hh .v.LH ;
	    mem [q ].hh .v.RH = s ;
	    while ( mem [s ].hh .v.RH != -268435455L ) s = mem [s ].hh 
	    .v.RH ;
	    mem [q + 1 ].hh .v.LH = -268435455L ;
	    q = s ;
	  } 
	  mem [q ].hh .v.RH = r ;
	  discbreak = true ;
	} 
	else if ( mem [q ].hh.b0 == 11 ) 
	mem [q + 1 ].cint = 0 ;
	else if ( mem [q ].hh.b0 == 9 ) 
	{
	  mem [q + 1 ].cint = 0 ;
	  if ( ( eqtb [29374 ].cint > 0 ) ) {
	      
	    if ( odd ( mem [q ].hh.b1 ) ) 
	    {
	      if ( LRptr != -268435455L ) {
		  
		if ( mem [LRptr ].hh .v.LH == ( 4 * ( mem [q ].hh.b1 / 4 ) 
		+ 3 ) ) 
		{
		  tempptr = LRptr ;
		  LRptr = mem [tempptr ].hh .v.RH ;
		  {
		    mem [tempptr ].hh .v.RH = avail ;
		    avail = tempptr ;
	;
#ifdef STAT
		    decr ( dynused ) ;
#endif /* STAT */
		  } 
		} 
	      } 
	    } 
	    else {
		
	      tempptr = getavail () ;
	      mem [tempptr ].hh .v.LH = ( 4 * ( mem [q ].hh.b1 / 4 ) + 3 ) 
	      ;
	      mem [tempptr ].hh .v.RH = LRptr ;
	      LRptr = tempptr ;
	    } 
	  } 
	} 
      } 
    } 
    else {
	
      q = memtop - 3 ;
      while ( mem [q ].hh .v.RH != -268435455L ) q = mem [q ].hh .v.RH ;
    } 
    lab30: if ( eqtb [29350 ].cint > 0 ) 
    {
      if ( discbreak && ( ( q >= himemmin ) || ( mem [q ].hh.b0 != 7 ) ) ) 
      {
	p = q ;
	ptmp = p ;
      } 
      else {
	  
	p = prevrightmost ( mem [memtop - 3 ].hh .v.RH , q ) ;
	ptmp = p ;
	p = findprotcharright ( mem [memtop - 3 ].hh .v.RH , p ) ;
      } 
      w = charpw ( p , 1 ) ;
      if ( w != 0 ) 
      {
	k = newmarginkern ( - (integer) w , lastrightmostchar , 1 ) ;
	mem [k ].hh .v.RH = mem [ptmp ].hh .v.RH ;
	mem [ptmp ].hh .v.RH = k ;
	if ( ( ptmp == q ) ) 
	q = mem [q ].hh .v.RH ;
      } 
    } 
    if ( ! gluebreak ) 
    {
      r = newparamglue ( 8 ) ;
      mem [r ].hh .v.RH = mem [q ].hh .v.RH ;
      mem [q ].hh .v.RH = r ;
      q = r ;
    } 
    if ( ( eqtb [29374 ].cint > 0 ) ) {
	
      if ( LRptr != -268435455L ) 
      {
	s = memtop - 3 ;
	r = mem [s ].hh .v.RH ;
	while ( r != q ) {
	    
	  s = r ;
	  r = mem [s ].hh .v.RH ;
	} 
	r = LRptr ;
	while ( r != -268435455L ) {
	    
	  tempptr = newmath ( 0 , mem [r ].hh .v.LH ) ;
	  mem [s ].hh .v.RH = tempptr ;
	  s = tempptr ;
	  r = mem [r ].hh .v.RH ;
	} 
	mem [s ].hh .v.RH = q ;
      } 
    } 
    r = mem [q ].hh .v.RH ;
    mem [q ].hh .v.RH = -268435455L ;
    q = mem [memtop - 3 ].hh .v.RH ;
    mem [memtop - 3 ].hh .v.RH = r ;
    if ( eqtb [29350 ].cint > 0 ) 
    {
      p = q ;
      p = findprotcharleft ( p , false ) ;
      w = charpw ( p , 0 ) ;
      if ( w != 0 ) 
      {
	k = newmarginkern ( - (integer) w , lastleftmostchar , 0 ) ;
	mem [k ].hh .v.RH = q ;
	q = k ;
      } 
    } 
    if ( eqtb [26635 ].hh .v.RH != membot ) 
    {
      r = newparamglue ( 7 ) ;
      mem [r ].hh .v.RH = q ;
      q = r ;
    } 
    if ( curline > lastspecialline ) 
    {
      curwidth = secondwidth ;
      curindent = secondindent ;
    } 
    else if ( eqtb [27158 ].hh .v.RH == -268435455L ) 
    {
      curwidth = firstwidth ;
      curindent = firstindent ;
    } 
    else {
	
      curwidth = mem [eqtb [27158 ].hh .v.RH + 2 * curline ].cint ;
      curindent = mem [eqtb [27158 ].hh .v.RH + 2 * curline - 1 ].cint ;
    } 
    adjusttail = memtop - 5 ;
    preadjusttail = memtop - 14 ;
    if ( eqtb [29349 ].cint > 0 ) 
    justbox = hpack ( q , curwidth , 2 ) ;
    else justbox = hpack ( q , curwidth , 0 ) ;
    mem [justbox + 4 ].cint = curindent ;
    if ( eqtb [29917 ].cint != eqtb [29919 ].cint ) 
    mem [justbox + 3 ].cint = eqtb [29917 ].cint ;
    if ( eqtb [29918 ].cint != eqtb [29919 ].cint ) 
    mem [justbox + 2 ].cint = eqtb [29918 ].cint ;
    if ( ( eqtb [29915 ].cint != eqtb [29919 ].cint ) && ( curline == 
    curlist .pgfield + 1 ) ) 
    mem [justbox + 3 ].cint = eqtb [29915 ].cint ;
    if ( ( eqtb [29916 ].cint != eqtb [29919 ].cint ) && ( curline + 1 == 
    bestline ) ) 
    mem [justbox + 2 ].cint = eqtb [29916 ].cint ;
    if ( memtop - 14 != preadjusttail ) 
    {
      mem [curlist .tailfield ].hh .v.RH = mem [memtop - 14 ].hh .v.RH ;
      curlist .tailfield = preadjusttail ;
    } 
    preadjusttail = -268435455L ;
    appendtovlist ( justbox ) ;
    if ( memtop - 5 != adjusttail ) 
    {
      mem [curlist .tailfield ].hh .v.RH = mem [memtop - 5 ].hh .v.RH ;
      curlist .tailfield = adjusttail ;
    } 
    adjusttail = -268435455L ;
    if ( curline + 1 != bestline ) 
    {
      q = eqtb [27429 ].hh .v.RH ;
      if ( q != -268435455L ) 
      {
	r = curline ;
	if ( r > mem [q + 1 ].cint ) 
	r = mem [q + 1 ].cint ;
	pen = mem [q + r + 1 ].cint ;
      } 
      else pen = eqtb [29287 ].cint ;
      q = eqtb [27430 ].hh .v.RH ;
      if ( q != -268435455L ) 
      {
	r = curline - curlist .pgfield ;
	if ( r > mem [q + 1 ].cint ) 
	r = mem [q + 1 ].cint ;
	pen = pen + mem [q + r + 1 ].cint ;
      } 
      else if ( curline == curlist .pgfield + 1 ) 
      pen = pen + eqtb [29279 ].cint ;
      if ( d ) 
      q = eqtb [27432 ].hh .v.RH ;
      else q = eqtb [27431 ].hh .v.RH ;
      if ( q != -268435455L ) 
      {
	r = bestline - curline - 1 ;
	if ( r > mem [q + 1 ].cint ) 
	r = mem [q + 1 ].cint ;
	pen = pen + mem [q + r + 1 ].cint ;
      } 
      else if ( curline + 2 == bestline ) {
	  
	if ( d ) 
	pen = pen + eqtb [29281 ].cint ;
	else pen = pen + eqtb [29280 ].cint ;
      } 
      if ( discbreak ) 
      pen = pen + eqtb [29282 ].cint ;
      if ( pen != 0 ) 
      {
	r = newpenalty ( pen ) ;
	mem [curlist .tailfield ].hh .v.RH = r ;
	curlist .tailfield = r ;
      } 
    } 
    incr ( curline ) ;
    curp = mem [curp + 1 ].hh .v.LH ;
    if ( curp != -268435455L ) {
	
      if ( ! postdiscbreak ) 
      {
	r = memtop - 3 ;
	while ( true ) {
	    
	  q = mem [r ].hh .v.RH ;
	  if ( q == mem [curp + 1 ].hh .v.RH ) 
	  goto lab31 ;
	  if ( ( q >= himemmin ) ) 
	  goto lab31 ;
	  if ( ( mem [q ].hh.b0 < 9 ) ) 
	  goto lab31 ;
	  if ( mem [q ].hh.b0 == 11 ) {
	      
	    if ( mem [q ].hh.b1 != 1 ) 
	    goto lab31 ;
	  } 
	  r = q ;
	  if ( mem [q ].hh.b0 == 9 ) {
	      
	    if ( ( eqtb [29374 ].cint > 0 ) ) {
		
	      if ( odd ( mem [q ].hh.b1 ) ) 
	      {
		if ( LRptr != -268435455L ) {
		    
		  if ( mem [LRptr ].hh .v.LH == ( 4 * ( mem [q ].hh.b1 / 4 
		  ) + 3 ) ) 
		  {
		    tempptr = LRptr ;
		    LRptr = mem [tempptr ].hh .v.RH ;
		    {
		      mem [tempptr ].hh .v.RH = avail ;
		      avail = tempptr ;
	;
#ifdef STAT
		      decr ( dynused ) ;
#endif /* STAT */
		    } 
		  } 
		} 
	      } 
	      else {
		  
		tempptr = getavail () ;
		mem [tempptr ].hh .v.LH = ( 4 * ( mem [q ].hh.b1 / 4 ) + 3 
		) ;
		mem [tempptr ].hh .v.RH = LRptr ;
		LRptr = tempptr ;
	      } 
	    } 
	  } 
	} 
	lab31: if ( r != memtop - 3 ) 
	{
	  mem [r ].hh .v.RH = -268435455L ;
	  flushnodelist ( mem [memtop - 3 ].hh .v.RH ) ;
	  mem [memtop - 3 ].hh .v.RH = q ;
	} 
      } 
    } 
  } while ( ! ( curp == -268435455L ) ) ;
  if ( ( curline != bestline ) || ( mem [memtop - 3 ].hh .v.RH != 
  -268435455L ) ) 
  confusion ( 1345 ) ;
  curlist .pgfield = bestline - 1 ;
  curlist .eTeXauxfield = LRptr ;
} 
smallnumber 
zreconstitute ( smallnumber j , smallnumber n , halfword bchar , halfword 
hchar ) 
{
  /* 22 30 */ register smallnumber Result; reconstitute_regmem 
  halfword p  ;
  halfword t  ;
  fourquarters q  ;
  halfword currh  ;
  halfword testchar  ;
  scaled w  ;
  fontindex k  ;
  hyphenpassed = 0 ;
  t = memtop - 4 ;
  w = 0 ;
  mem [memtop - 4 ].hh .v.RH = -268435455L ;
  curl = hu [j ];
  curq = t ;
  if ( j == 0 ) 
  {
    ligaturepresent = initlig ;
    p = initlist ;
    if ( ligaturepresent ) 
    lfthit = initlft ;
    while ( p > -268435455L ) {
	
      {
	mem [t ].hh .v.RH = getavail () ;
	t = mem [t ].hh .v.RH ;
	mem [t ].hh.b0 = hf ;
	mem [t ].hh.b1 = mem [p ].hh.b1 ;
      } 
      p = mem [p ].hh .v.RH ;
    } 
  } 
  else if ( curl < 256 ) 
  {
    mem [t ].hh .v.RH = getavail () ;
    t = mem [t ].hh .v.RH ;
    mem [t ].hh.b0 = hf ;
    mem [t ].hh.b1 = curl ;
  } 
  ligstack = -268435455L ;
  {
    if ( j < n ) 
    curr = hu [j + 1 ];
    else curr = bchar ;
    if ( odd ( hyf [j ]) ) 
    currh = hchar ;
    else currh = 256 ;
  } 
  lab22: if ( curl == 256 ) 
  {
    k = bcharlabel [hf ];
    if ( k == 0 ) 
    goto lab30 ;
    else q = fontinfo [k ].qqqq ;
  } 
  else {
      
    q = fontinfo [charbase [hf ]+ effectivechar ( true , hf , curl ) ]
    .qqqq ;
    if ( ( ( q .b2 ) % 4 ) != 1 ) 
    goto lab30 ;
    k = ligkernbase [hf ]+ q .b3 ;
    q = fontinfo [k ].qqqq ;
    if ( q .b0 > 128 ) 
    {
      k = ligkernbase [hf ]+ 256 * q .b2 + q .b3 + 32768L - 256 * ( 128 ) ;
      q = fontinfo [k ].qqqq ;
    } 
  } 
  if ( currh < 256 ) 
  testchar = currh ;
  else testchar = curr ;
  while ( true ) {
      
    if ( q .b1 == testchar ) {
	
      if ( q .b0 <= 128 ) {
	  
	if ( currh < 256 ) 
	{
	  hyphenpassed = j ;
	  hchar = 256 ;
	  currh = 256 ;
	  goto lab22 ;
	} 
	else {
	    
	  if ( hchar < 256 ) {
	      
	    if ( odd ( hyf [j ]) ) 
	    {
	      hyphenpassed = j ;
	      hchar = 256 ;
	    } 
	  } 
	  if ( q .b2 < 128 ) 
	  {
	    if ( curl == 256 ) 
	    lfthit = true ;
	    if ( j == n ) {
		
	      if ( ligstack == -268435455L ) 
	      rthit = true ;
	    } 
	    {
	      if ( interrupt != 0 ) 
	      pauseforinstructions () ;
	    } 
	    switch ( q .b2 ) 
	    {case 1 : 
	    case 5 : 
	      {
		curl = q .b3 ;
		ligaturepresent = true ;
	      } 
	      break ;
	    case 2 : 
	    case 6 : 
	      {
		curr = q .b3 ;
		if ( ligstack > -268435455L ) 
		mem [ligstack ].hh.b1 = curr ;
		else {
		    
		  ligstack = newligitem ( curr ) ;
		  if ( j == n ) 
		  bchar = 256 ;
		  else {
		      
		    p = getavail () ;
		    mem [ligstack + 1 ].hh .v.RH = p ;
		    mem [p ].hh.b1 = hu [j + 1 ];
		    mem [p ].hh.b0 = hf ;
		  } 
		} 
	      } 
	      break ;
	    case 3 : 
	      {
		curr = q .b3 ;
		p = ligstack ;
		ligstack = newligitem ( curr ) ;
		mem [ligstack ].hh .v.RH = p ;
	      } 
	      break ;
	    case 7 : 
	    case 11 : 
	      {
		if ( ligaturepresent ) 
		{
		  p = newligature ( hf , curl , mem [curq ].hh .v.RH ) ;
		  if ( lfthit ) 
		  {
		    mem [p ].hh.b1 = 2 ;
		    lfthit = false ;
		  } 
		  if ( false ) {
		      
		    if ( ligstack == -268435455L ) 
		    {
		      incr ( mem [p ].hh.b1 ) ;
		      rthit = false ;
		    } 
		  } 
		  mem [curq ].hh .v.RH = p ;
		  t = p ;
		  ligaturepresent = false ;
		} 
		curq = t ;
		curl = q .b3 ;
		ligaturepresent = true ;
	      } 
	      break ;
	      default: 
	      {
		curl = q .b3 ;
		ligaturepresent = true ;
		if ( ligstack > -268435455L ) 
		{
		  if ( mem [ligstack + 1 ].hh .v.RH > -268435455L ) 
		  {
		    mem [t ].hh .v.RH = mem [ligstack + 1 ].hh .v.RH ;
		    t = mem [t ].hh .v.RH ;
		    incr ( j ) ;
		  } 
		  p = ligstack ;
		  ligstack = mem [p ].hh .v.RH ;
		  freenode ( p , 2 ) ;
		  if ( ligstack == -268435455L ) 
		  {
		    if ( j < n ) 
		    curr = hu [j + 1 ];
		    else curr = bchar ;
		    if ( odd ( hyf [j ]) ) 
		    currh = hchar ;
		    else currh = 256 ;
		  } 
		  else curr = mem [ligstack ].hh.b1 ;
		} 
		else if ( j == n ) 
		goto lab30 ;
		else {
		    
		  {
		    mem [t ].hh .v.RH = getavail () ;
		    t = mem [t ].hh .v.RH ;
		    mem [t ].hh.b0 = hf ;
		    mem [t ].hh.b1 = curr ;
		  } 
		  incr ( j ) ;
		  {
		    if ( j < n ) 
		    curr = hu [j + 1 ];
		    else curr = bchar ;
		    if ( odd ( hyf [j ]) ) 
		    currh = hchar ;
		    else currh = 256 ;
		  } 
		} 
	      } 
	      break ;
	    } 
	    if ( q .b2 > 4 ) {
		
	      if ( q .b2 != 7 ) 
	      goto lab30 ;
	    } 
	    goto lab22 ;
	  } 
	  w = fontinfo [kernbase [hf ]+ 256 * q .b2 + q .b3 ].cint ;
	  goto lab30 ;
	} 
      } 
    } 
    if ( q .b0 >= 128 ) {
	
      if ( currh == 256 ) 
      goto lab30 ;
      else {
	  
	currh = 256 ;
	goto lab22 ;
      } 
    } 
    k = k + q .b0 + 1 ;
    q = fontinfo [k ].qqqq ;
  } 
  lab30: ;
  if ( ligaturepresent ) 
  {
    p = newligature ( hf , curl , mem [curq ].hh .v.RH ) ;
    if ( lfthit ) 
    {
      mem [p ].hh.b1 = 2 ;
      lfthit = false ;
    } 
    if ( rthit ) {
	
      if ( ligstack == -268435455L ) 
      {
	incr ( mem [p ].hh.b1 ) ;
	rthit = false ;
      } 
    } 
    mem [curq ].hh .v.RH = p ;
    t = p ;
    ligaturepresent = false ;
  } 
  if ( w != 0 ) 
  {
    mem [t ].hh .v.RH = newkern ( w ) ;
    t = mem [t ].hh .v.RH ;
    w = 0 ;
  } 
  if ( ligstack > -268435455L ) 
  {
    curq = t ;
    curl = mem [ligstack ].hh.b1 ;
    ligaturepresent = true ;
    {
      if ( mem [ligstack + 1 ].hh .v.RH > -268435455L ) 
      {
	mem [t ].hh .v.RH = mem [ligstack + 1 ].hh .v.RH ;
	t = mem [t ].hh .v.RH ;
	incr ( j ) ;
      } 
      p = ligstack ;
      ligstack = mem [p ].hh .v.RH ;
      freenode ( p , 2 ) ;
      if ( ligstack == -268435455L ) 
      {
	if ( j < n ) 
	curr = hu [j + 1 ];
	else curr = bchar ;
	if ( odd ( hyf [j ]) ) 
	currh = hchar ;
	else currh = 256 ;
      } 
      else curr = mem [ligstack ].hh.b1 ;
    } 
    goto lab22 ;
  } 
  Result = j ;
  return Result ;
} 
void 
hyphenate ( void ) 
{
  /* 50 30 40 41 42 45 10 */ hyphenate_regmem 
  unsigned char i, j, l  ;
  halfword q, r, s  ;
  halfword bchar  ;
  halfword majortail, minortail  ;
  ASCIIcode c  ;
  unsigned char cloc  ;
  integer rcount  ;
  halfword hyfnode  ;
  triepointer z  ;
  integer v  ;
  hyphpointer h  ;
  strnumber k  ;
  poolpointer u  ;
  {register integer for_end; j = 0 ;for_end = hn ; if ( j <= for_end) do 
    hyf [j ]= 0 ;
  while ( j++ < for_end ) ;} 
  h = hc [1 ];
  incr ( hn ) ;
  hc [hn ]= curlang ;
  {register integer for_end; j = 2 ;for_end = hn ; if ( j <= for_end) do 
    h = ( h + h + hc [j ]) % 607 ;
  while ( j++ < for_end ) ;} 
  while ( true ) {
      
    k = hyphword [h ];
    if ( k == 0 ) 
    goto lab45 ;
    if ( ( strstart [k + 1 ]- strstart [k ]) == hn ) 
    {
      j = 1 ;
      u = strstart [k ];
      do {
	  if ( strpool [u ]!= hc [j ]) 
	goto lab30 ;
	incr ( j ) ;
	incr ( u ) ;
      } while ( ! ( j > hn ) ) ;
      s = hyphlist [h ];
      while ( s != -268435455L ) {
	  
	hyf [mem [s ].hh .v.LH ]= 1 ;
	s = mem [s ].hh .v.RH ;
      } 
      decr ( hn ) ;
      goto lab40 ;
    } 
    lab30: ;
    h = hyphlink [h ];
    if ( h == 0 ) 
    goto lab45 ;
    decr ( h ) ;
  } 
  lab45: decr ( hn ) ;
  if ( trietrc [curlang + 1 ]!= curlang ) 
  return ;
  hc [0 ]= 0 ;
  hc [hn + 1 ]= 0 ;
  hc [hn + 2 ]= 256 ;
  {register integer for_end; j = 0 ;for_end = hn - rhyf + 1 ; if ( j <= 
  for_end) do 
    {
      z = trietrl [curlang + 1 ]+ hc [j ];
      l = j ;
      while ( hc [l ]== trietrc [z ]) {
	  
	if ( trietro [z ]!= mintrieop ) 
	{
	  v = trietro [z ];
	  do {
	      v = v + opstart [curlang ];
	    i = l - hyfdistance [v ];
	    if ( hyfnum [v ]> hyf [i ]) 
	    hyf [i ]= hyfnum [v ];
	    v = hyfnext [v ];
	  } while ( ! ( v == mintrieop ) ) ;
	} 
	incr ( l ) ;
	z = trietrl [z ]+ hc [l ];
      } 
    } 
  while ( j++ < for_end ) ;} 
  lab40: {
      register integer for_end; j = 0 ;for_end = lhyf - 1 ; if ( j <= 
  for_end) do 
    hyf [j ]= 0 ;
  while ( j++ < for_end ) ;} 
  {register integer for_end; j = 0 ;for_end = rhyf - 1 ; if ( j <= for_end) 
  do 
    hyf [hn - j ]= 0 ;
  while ( j++ < for_end ) ;} 
  {register integer for_end; j = lhyf ;for_end = hn - rhyf ; if ( j <= 
  for_end) do 
    if ( odd ( hyf [j ]) ) 
    goto lab41 ;
  while ( j++ < for_end ) ;} 
  return ;
  lab41: ;
  q = mem [hb ].hh .v.RH ;
  mem [hb ].hh .v.RH = -268435455L ;
  r = mem [ha ].hh .v.RH ;
  mem [ha ].hh .v.RH = -268435455L ;
  bchar = hyfbchar ;
  if ( ( ha >= himemmin ) ) {
      
    if ( mem [ha ].hh.b0 != hf ) 
    goto lab42 ;
    else {
	
      initlist = ha ;
      initlig = false ;
      hu [0 ]= mem [ha ].hh.b1 ;
    } 
  } 
  else if ( mem [ha ].hh.b0 == 6 ) {
      
    if ( mem [ha + 1 ].hh.b0 != hf ) 
    goto lab42 ;
    else {
	
      initlist = mem [ha + 1 ].hh .v.RH ;
      initlig = true ;
      initlft = ( mem [ha ].hh.b1 > 1 ) ;
      hu [0 ]= mem [ha + 1 ].hh.b1 ;
      if ( initlist == -268435455L ) {
	  
	if ( initlft ) 
	{
	  hu [0 ]= 256 ;
	  initlig = false ;
	} 
      } 
      freenode ( ha , 2 ) ;
    } 
  } 
  else {
      
    if ( ! ( r >= himemmin ) ) {
	
      if ( mem [r ].hh.b0 == 6 ) {
	  
	if ( mem [r ].hh.b1 > 1 ) 
	goto lab42 ;
      } 
    } 
    j = 1 ;
    s = ha ;
    initlist = -268435455L ;
    goto lab50 ;
  } 
  s = curp ;
  while ( mem [s ].hh .v.RH != ha ) s = mem [s ].hh .v.RH ;
  j = 0 ;
  goto lab50 ;
  lab42: s = ha ;
  j = 0 ;
  hu [0 ]= 256 ;
  initlig = false ;
  initlist = -268435455L ;
  lab50: flushnodelist ( r ) ;
  do {
      l = j ;
    j = reconstitute ( j , hn , bchar , hyfchar ) + 1 ;
    if ( hyphenpassed == 0 ) 
    {
      mem [s ].hh .v.RH = mem [memtop - 4 ].hh .v.RH ;
      while ( mem [s ].hh .v.RH > -268435455L ) s = mem [s ].hh .v.RH ;
      if ( odd ( hyf [j - 1 ]) ) 
      {
	l = j ;
	hyphenpassed = j - 1 ;
	mem [memtop - 4 ].hh .v.RH = -268435455L ;
      } 
    } 
    if ( hyphenpassed > 0 ) 
    do {
	r = getnode ( 2 ) ;
      mem [r ].hh .v.RH = mem [memtop - 4 ].hh .v.RH ;
      mem [r ].hh.b0 = 7 ;
      majortail = r ;
      rcount = 0 ;
      while ( mem [majortail ].hh .v.RH > -268435455L ) {
	  
	majortail = mem [majortail ].hh .v.RH ;
	incr ( rcount ) ;
      } 
      i = hyphenpassed ;
      hyf [i ]= 0 ;
      minortail = -268435455L ;
      mem [r + 1 ].hh .v.LH = -268435455L ;
      hyfnode = newcharacter ( hf , hyfchar ) ;
      if ( hyfnode != -268435455L ) 
      {
	incr ( i ) ;
	c = hu [i ];
	hu [i ]= hyfchar ;
	{
	  mem [hyfnode ].hh .v.RH = avail ;
	  avail = hyfnode ;
	;
#ifdef STAT
	  decr ( dynused ) ;
#endif /* STAT */
	} 
      } 
      while ( l <= i ) {
	  
	l = reconstitute ( l , i , fontbchar [hf ], 256 ) + 1 ;
	if ( mem [memtop - 4 ].hh .v.RH > -268435455L ) 
	{
	  if ( minortail == -268435455L ) 
	  mem [r + 1 ].hh .v.LH = mem [memtop - 4 ].hh .v.RH ;
	  else mem [minortail ].hh .v.RH = mem [memtop - 4 ].hh .v.RH ;
	  minortail = mem [memtop - 4 ].hh .v.RH ;
	  while ( mem [minortail ].hh .v.RH > -268435455L ) minortail = mem 
	  [minortail ].hh .v.RH ;
	} 
      } 
      if ( hyfnode != -268435455L ) 
      {
	hu [i ]= c ;
	l = i ;
	decr ( i ) ;
      } 
      minortail = -268435455L ;
      mem [r + 1 ].hh .v.RH = -268435455L ;
      cloc = 0 ;
      if ( bcharlabel [hf ]!= 0 ) 
      {
	decr ( l ) ;
	c = hu [l ];
	cloc = l ;
	hu [l ]= 256 ;
      } 
      while ( l < j ) {
	  
	do {
	    l = reconstitute ( l , hn , bchar , 256 ) + 1 ;
	  if ( cloc > 0 ) 
	  {
	    hu [cloc ]= c ;
	    cloc = 0 ;
	  } 
	  if ( mem [memtop - 4 ].hh .v.RH > -268435455L ) 
	  {
	    if ( minortail == -268435455L ) 
	    mem [r + 1 ].hh .v.RH = mem [memtop - 4 ].hh .v.RH ;
	    else mem [minortail ].hh .v.RH = mem [memtop - 4 ].hh .v.RH ;
	    minortail = mem [memtop - 4 ].hh .v.RH ;
	    while ( mem [minortail ].hh .v.RH > -268435455L ) minortail = 
	    mem [minortail ].hh .v.RH ;
	  } 
	} while ( ! ( l >= j ) ) ;
	while ( l > j ) {
	    
	  j = reconstitute ( j , hn , bchar , 256 ) + 1 ;
	  mem [majortail ].hh .v.RH = mem [memtop - 4 ].hh .v.RH ;
	  while ( mem [majortail ].hh .v.RH > -268435455L ) {
	      
	    majortail = mem [majortail ].hh .v.RH ;
	    incr ( rcount ) ;
	  } 
	} 
      } 
      if ( rcount > 127 ) 
      {
	mem [s ].hh .v.RH = mem [r ].hh .v.RH ;
	mem [r ].hh .v.RH = -268435455L ;
	flushnodelist ( r ) ;
      } 
      else {
	  
	mem [s ].hh .v.RH = r ;
	mem [r ].hh.b1 = rcount ;
      } 
      s = majortail ;
      hyphenpassed = j - 1 ;
      mem [memtop - 4 ].hh .v.RH = -268435455L ;
    } while ( ! ( ! odd ( hyf [j - 1 ]) ) ) ;
  } while ( ! ( j > hn ) ) ;
  mem [s ].hh .v.RH = q ;
  flushlist ( initlist ) ;
} 
boolean 
zeTeXenabled ( boolean b , quarterword j , halfword k ) 
{
  register boolean Result; eTeXenabled_regmem 
  if ( ! b ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 776 ) ;
    } 
    printcmdchr ( j , k ) ;
    {
      helpptr = 1 ;
      helpline [0 ]= 1951 ;
    } 
    error () ;
  } 
  Result = b ;
  return Result ;
} 
void 
showsavegroups ( void ) 
{
  /* 41 42 40 30 */ showsavegroups_regmem 
  integer p  ;
  short m  ;
  savepointer v  ;
  quarterword l  ;
  groupcode c  ;
  schar a  ;
  integer i  ;
  quarterword j  ;
  strnumber s  ;
  p = nestptr ;
  nest [p ]= curlist ;
  v = saveptr ;
  l = curlevel ;
  c = curgroup ;
  saveptr = curboundary ;
  decr ( curlevel ) ;
  a = 1 ;
  printnl ( 345 ) ;
  println () ;
  while ( true ) {
      
    printnl ( 379 ) ;
    printgroup ( true ) ;
    if ( curgroup == 0 ) 
    goto lab30 ;
    do {
	m = nest [p ].modefield ;
      if ( p > 0 ) 
      decr ( p ) ;
      else m = 1 ;
    } while ( ! ( m != 104 ) ) ;
    print ( 286 ) ;
    switch ( curgroup ) 
    {case 1 : 
      {
	incr ( p ) ;
	goto lab42 ;
      } 
      break ;
    case 2 : 
    case 3 : 
      s = 1466 ;
      break ;
    case 4 : 
      s = 1375 ;
      break ;
    case 5 : 
      s = 1465 ;
      break ;
    case 6 : 
      if ( a == 0 ) 
      {
	if ( m == -1 ) 
	s = 594 ;
	else s = 613 ;
	a = 1 ;
	goto lab41 ;
      } 
      else {
	  
	if ( a == 1 ) 
	print ( 1989 ) ;
	else printesc ( 1301 ) ;
	if ( p >= a ) 
	p = p - a ;
	a = 0 ;
	goto lab40 ;
      } 
      break ;
    case 7 : 
      {
	incr ( p ) ;
	a = -1 ;
	printesc ( 601 ) ;
	goto lab42 ;
      } 
      break ;
    case 8 : 
      {
	printesc ( 414 ) ;
	goto lab40 ;
      } 
      break ;
    case 9 : 
      goto lab42 ;
      break ;
    case 10 : 
    case 13 : 
      {
	if ( curgroup == 10 ) 
	printesc ( 357 ) ;
	else printesc ( 599 ) ;
	{register integer for_end; i = 1 ;for_end = 3 ; if ( i <= for_end) 
	do 
	  if ( i <= savestack [saveptr - 2 ].cint ) 
	  print ( 1261 ) ;
	while ( i++ < for_end ) ;} 
	goto lab42 ;
      } 
      break ;
    case 11 : 
      {
	if ( savestack [saveptr - 2 ].cint == 255 ) 
	printesc ( 360 ) ;
	else {
	    
	  printesc ( 337 ) ;
	  printint ( savestack [saveptr - 2 ].cint ) ;
	} 
	goto lab42 ;
      } 
      break ;
    case 12 : 
      {
	s = 614 ;
	goto lab41 ;
      } 
      break ;
    case 14 : 
      {
	incr ( p ) ;
	printesc ( 584 ) ;
	goto lab40 ;
      } 
      break ;
    case 15 : 
      {
	if ( m == 207 ) 
	printchar ( 36 ) ;
	else if ( nest [p ].modefield == 207 ) 
	{
	  printcmdchr ( 48 , savestack [saveptr - 2 ].cint ) ;
	  goto lab40 ;
	} 
	printchar ( 36 ) ;
	goto lab40 ;
      } 
      break ;
    case 16 : 
      {
	if ( mem [nest [p + 1 ].eTeXauxfield ].hh.b0 == 30 ) 
	printesc ( 1277 ) ;
	else printesc ( 1279 ) ;
	goto lab40 ;
      } 
      break ;
    } 
    i = savestack [saveptr - 4 ].cint ;
    if ( i != 0 ) {
	
      if ( i < 1073741824L ) 
      {
	if ( abs ( nest [p ].modefield ) == 1 ) 
	j = 21 ;
	else j = 22 ;
	if ( i > 0 ) 
	printcmdchr ( j , 0 ) ;
	else printcmdchr ( j , 1 ) ;
	printscaled ( abs ( i ) ) ;
	print ( 312 ) ;
      } 
      else if ( i < 1073807360L ) 
      {
	if ( i >= 1073774592L ) 
	{
	  printesc ( 1582 ) ;
	  i = i - ( 32768L ) ;
	} 
	printesc ( 611 ) ;
	printint ( i - 1073741824L ) ;
	printchar ( 61 ) ;
      } 
      else printcmdchr ( 31 , i - ( 1073807261L ) ) ;
    } 
    lab41: printesc ( s ) ;
    if ( savestack [saveptr - 2 ].cint != 0 ) 
    {
      printchar ( 32 ) ;
      if ( savestack [saveptr - 3 ].cint == 0 ) 
      print ( 1237 ) ;
      else print ( 1238 ) ;
      printscaled ( savestack [saveptr - 2 ].cint ) ;
      print ( 312 ) ;
    } 
    lab42: printchar ( 123 ) ;
    lab40: printchar ( 41 ) ;
    decr ( curlevel ) ;
    curgroup = savestack [saveptr ].hh.b1 ;
    saveptr = savestack [saveptr ].hh .v.RH ;
  } 
  lab30: saveptr = v ;
  curlevel = l ;
  curgroup = c ;
} 
halfword 
zprunepagetop ( halfword p , boolean s ) 
{
  /* 60 */ register halfword Result; prunepagetop_regmem 
  halfword prevp  ;
  halfword q, r  ;
  prevp = memtop - 3 ;
  mem [memtop - 3 ].hh .v.RH = p ;
  while ( p != -268435455L ) switch ( mem [p ].hh.b0 ) 
  {case 0 : 
  case 1 : 
  case 2 : 
    {
      q = newskipparam ( 10 ) ;
      mem [prevp ].hh .v.RH = q ;
      mem [q ].hh .v.RH = p ;
      if ( mem [tempptr + 1 ].cint > mem [p + 3 ].cint ) 
      mem [tempptr + 1 ].cint = mem [tempptr + 1 ].cint - mem [p + 3 ]
      .cint ;
      else mem [tempptr + 1 ].cint = 0 ;
      p = -268435455L ;
    } 
    break ;
  case 8 : 
  case 4 : 
  case 3 : 
    {
      if ( ( mem [p ].hh.b0 == 8 ) && ( ( mem [p ].hh.b1 == 35 ) || ( mem 
      [p ].hh.b1 == 36 ) ) ) 
      {
	print ( 1365 ) ;
	goto lab60 ;
      } 
      prevp = p ;
      p = mem [prevp ].hh .v.RH ;
    } 
    break ;
  case 10 : 
  case 11 : 
  case 12 : 
    {
      lab60: q = p ;
      p = mem [q ].hh .v.RH ;
      mem [q ].hh .v.RH = -268435455L ;
      mem [prevp ].hh .v.RH = p ;
      if ( s ) 
      {
	if ( discptr [3 ]== -268435455L ) 
	discptr [3 ]= q ;
	else mem [r ].hh .v.RH = q ;
	r = q ;
      } 
      else flushnodelist ( q ) ;
    } 
    break ;
    default: 
    confusion ( 1367 ) ;
    break ;
  } 
  Result = mem [memtop - 3 ].hh .v.RH ;
  return Result ;
} 
halfword 
zvertbreak ( halfword p , scaled h , scaled d ) 
{
  /* 30 45 90 */ register halfword Result; vertbreak_regmem 
  halfword prevp  ;
  halfword q, r  ;
  integer pi  ;
  integer b  ;
  integer leastcost  ;
  halfword bestplace  ;
  scaled prevdp  ;
  smallnumber t  ;
  prevp = p ;
  leastcost = 1073741823L ;
  activewidth [1 ]= 0 ;
  activewidth [2 ]= 0 ;
  activewidth [3 ]= 0 ;
  activewidth [4 ]= 0 ;
  activewidth [5 ]= 0 ;
  activewidth [6 ]= 0 ;
  prevdp = 0 ;
  while ( true ) {
      
    if ( p == -268435455L ) 
    pi = -10000 ;
    else switch ( mem [p ].hh.b0 ) 
    {case 0 : 
    case 1 : 
    case 2 : 
      {
	activewidth [1 ]= activewidth [1 ]+ prevdp + mem [p + 3 ].cint ;
	prevdp = mem [p + 2 ].cint ;
	goto lab45 ;
      } 
      break ;
    case 8 : 
      {
	if ( ( mem [p ].hh.b1 == 10 ) || ( mem [p ].hh.b1 == 12 ) ) 
	{
	  activewidth [1 ]= activewidth [1 ]+ prevdp + mem [p + 2 ].cint 
	  ;
	  prevdp = mem [p + 3 ].cint ;
	} 
	goto lab45 ;
      } 
      break ;
    case 10 : 
      if ( ( mem [prevp ].hh.b0 < 9 ) ) 
      pi = 0 ;
      else goto lab90 ;
      break ;
    case 11 : 
      {
	if ( mem [p ].hh .v.RH == -268435455L ) 
	t = 12 ;
	else t = mem [mem [p ].hh .v.RH ].hh.b0 ;
	if ( t == 10 ) 
	pi = 0 ;
	else goto lab90 ;
      } 
      break ;
    case 12 : 
      pi = mem [p + 1 ].cint ;
      break ;
    case 4 : 
    case 3 : 
      goto lab45 ;
      break ;
      default: 
      confusion ( 1368 ) ;
      break ;
    } 
    if ( pi < 10000 ) 
    {
      if ( activewidth [1 ]< h ) {
	  
	if ( ( activewidth [3 ]!= 0 ) || ( activewidth [4 ]!= 0 ) || ( 
	activewidth [5 ]!= 0 ) ) 
	b = 0 ;
	else b = badness ( h - activewidth [1 ], activewidth [2 ]) ;
      } 
      else if ( activewidth [1 ]- h > activewidth [6 ]) 
      b = 1073741823L ;
      else b = badness ( activewidth [1 ]- h , activewidth [6 ]) ;
      if ( b < 1073741823L ) {
	  
	if ( pi <= -10000 ) 
	b = pi ;
	else if ( b < 10000 ) 
	b = b + pi ;
	else b = 100000L ;
      } 
      if ( b <= leastcost ) 
      {
	bestplace = p ;
	leastcost = b ;
	bestheightplusdepth = activewidth [1 ]+ prevdp ;
      } 
      if ( ( b == 1073741823L ) || ( pi <= -10000 ) ) 
      goto lab30 ;
    } 
    if ( ( mem [p ].hh.b0 < 10 ) || ( mem [p ].hh.b0 > 11 ) ) 
    goto lab45 ;
    lab90: if ( mem [p ].hh.b0 == 11 ) 
    q = p ;
    else {
	
      q = mem [p + 1 ].hh .v.LH ;
      activewidth [2 + mem [q ].hh.b0 ]= activewidth [2 + mem [q ]
      .hh.b0 ]+ mem [q + 2 ].cint ;
      activewidth [6 ]= activewidth [6 ]+ mem [q + 3 ].cint ;
      if ( ( mem [q ].hh.b1 != 0 ) && ( mem [q + 3 ].cint != 0 ) ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 1369 ) ;
	} 
	{
	  helpptr = 4 ;
	  helpline [3 ]= 1370 ;
	  helpline [2 ]= 1371 ;
	  helpline [1 ]= 1372 ;
	  helpline [0 ]= 1324 ;
	} 
	error () ;
	r = newspec ( q ) ;
	mem [r ].hh.b1 = 0 ;
	deleteglueref ( q ) ;
	mem [p + 1 ].hh .v.LH = r ;
	q = r ;
      } 
    } 
    activewidth [1 ]= activewidth [1 ]+ prevdp + mem [q + 1 ].cint ;
    prevdp = 0 ;
    lab45: if ( prevdp > d ) 
    {
      activewidth [1 ]= activewidth [1 ]+ prevdp - d ;
      prevdp = d ;
    } 
    prevp = p ;
    p = mem [prevp ].hh .v.RH ;
  } 
  lab30: Result = bestplace ;
  return Result ;
} 
halfword 
zvsplit ( halfword n , scaled h ) 
{
  /* 10 30 */ register halfword Result; vsplit_regmem 
  halfword v  ;
  halfword p  ;
  halfword q  ;
  curval = n ;
  if ( curval < 256 ) 
  v = eqtb [27433 + curval ].hh .v.RH ;
  else {
      
    findsaelement ( 4 , curval , false ) ;
    if ( curptr == -268435455L ) 
    v = -268435455L ;
    else v = mem [curptr + 1 ].hh .v.RH ;
  } 
  flushnodelist ( discptr [3 ]) ;
  discptr [3 ]= -268435455L ;
  if ( saroot [6 ]!= -268435455L ) {
      
    if ( domarks ( 0 , 0 , saroot [6 ]) ) 
    saroot [6 ]= -268435455L ;
  } 
  if ( curmark [3 ]!= -268435455L ) 
  {
    deletetokenref ( curmark [3 ]) ;
    curmark [3 ]= -268435455L ;
    deletetokenref ( curmark [4 ]) ;
    curmark [4 ]= -268435455L ;
  } 
  if ( v == -268435455L ) 
  {
    Result = -268435455L ;
    return Result ;
  } 
  if ( mem [v ].hh.b0 != 1 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 345 ) ;
    } 
    printesc ( 1373 ) ;
    print ( 1374 ) ;
    printesc ( 1375 ) ;
    {
      helpptr = 2 ;
      helpline [1 ]= 1376 ;
      helpline [0 ]= 1377 ;
    } 
    error () ;
    Result = -268435455L ;
    return Result ;
  } 
  q = vertbreak ( mem [v + 5 ].hh .v.RH , h , eqtb [29893 ].cint ) ;
  p = mem [v + 5 ].hh .v.RH ;
  if ( p == q ) 
  mem [v + 5 ].hh .v.RH = -268435455L ;
  else while ( true ) {
      
    if ( mem [p ].hh.b0 == 4 ) {
	
      if ( mem [p + 1 ].hh .v.LH != 0 ) 
      {
	findsaelement ( 6 , mem [p + 1 ].hh .v.LH , true ) ;
	if ( mem [curptr + 2 ].hh .v.RH == -268435455L ) 
	{
	  mem [curptr + 2 ].hh .v.RH = mem [p + 1 ].hh .v.RH ;
	  incr ( mem [mem [p + 1 ].hh .v.RH ].hh .v.LH ) ;
	} 
	else deletetokenref ( mem [curptr + 3 ].hh .v.LH ) ;
	mem [curptr + 3 ].hh .v.LH = mem [p + 1 ].hh .v.RH ;
	incr ( mem [mem [p + 1 ].hh .v.RH ].hh .v.LH ) ;
      } 
      else if ( curmark [3 ]== -268435455L ) 
      {
	curmark [3 ]= mem [p + 1 ].hh .v.RH ;
	curmark [4 ]= curmark [3 ];
	mem [curmark [3 ]].hh .v.LH = mem [curmark [3 ]].hh .v.LH + 2 
	;
      } 
      else {
	  
	deletetokenref ( curmark [4 ]) ;
	curmark [4 ]= mem [p + 1 ].hh .v.RH ;
	incr ( mem [curmark [4 ]].hh .v.LH ) ;
      } 
    } 
    if ( mem [p ].hh .v.RH == q ) 
    {
      mem [p ].hh .v.RH = -268435455L ;
      goto lab30 ;
    } 
    p = mem [p ].hh .v.RH ;
  } 
  lab30: ;
  q = prunepagetop ( q , eqtb [29372 ].cint > 0 ) ;
  p = mem [v + 5 ].hh .v.RH ;
  freenode ( v , 7 ) ;
  if ( q != -268435455L ) 
  q = vpackage ( q , 0 , 1 , 1073741823L ) ;
  if ( curval < 256 ) 
  eqtb [27433 + curval ].hh .v.RH = q ;
  else {
      
    findsaelement ( 4 , curval , false ) ;
    if ( curptr != -268435455L ) 
    {
      mem [curptr + 1 ].hh .v.RH = q ;
      incr ( mem [curptr + 1 ].hh .v.LH ) ;
      deletesaref ( curptr ) ;
    } 
  } 
  Result = vpackage ( p , h , 0 , eqtb [29893 ].cint ) ;
  return Result ;
} 
void 
printtotals ( void ) 
{
  printtotals_regmem 
  printscaled ( pagesofar [1 ]) ;
  if ( pagesofar [2 ]!= 0 ) 
  {
    print ( 317 ) ;
    printscaled ( pagesofar [2 ]) ;
    print ( 345 ) ;
  } 
  if ( pagesofar [3 ]!= 0 ) 
  {
    print ( 317 ) ;
    printscaled ( pagesofar [3 ]) ;
    print ( 316 ) ;
  } 
  if ( pagesofar [4 ]!= 0 ) 
  {
    print ( 317 ) ;
    printscaled ( pagesofar [4 ]) ;
    print ( 1386 ) ;
  } 
  if ( pagesofar [5 ]!= 0 ) 
  {
    print ( 317 ) ;
    printscaled ( pagesofar [5 ]) ;
    print ( 1387 ) ;
  } 
  if ( pagesofar [6 ]!= 0 ) 
  {
    print ( 318 ) ;
    printscaled ( pagesofar [6 ]) ;
  } 
} 
void 
zfreezepagespecs ( smallnumber s ) 
{
  freezepagespecs_regmem 
  pagecontents = s ;
  pagesofar [0 ]= eqtb [29891 ].cint ;
  pagemaxdepth = eqtb [29892 ].cint ;
  pagesofar [7 ]= 0 ;
  pagesofar [1 ]= 0 ;
  pagesofar [2 ]= 0 ;
  pagesofar [3 ]= 0 ;
  pagesofar [4 ]= 0 ;
  pagesofar [5 ]= 0 ;
  pagesofar [6 ]= 0 ;
  leastpagecost = 1073741823L ;
	;
#ifdef STAT
  if ( eqtb [29307 ].cint > 0 ) 
  {
    begindiagnostic () ;
    printnl ( 1395 ) ;
    printscaled ( pagesofar [0 ]) ;
    print ( 1396 ) ;
    printscaled ( pagemaxdepth ) ;
    enddiagnostic ( false ) ;
  } 
#endif /* STAT */
} 
void 
zboxerror ( eightbits n ) 
{
  boxerror_regmem 
  error () ;
  begindiagnostic () ;
  printnl ( 990 ) ;
  showbox ( eqtb [27433 + n ].hh .v.RH ) ;
  enddiagnostic ( true ) ;
  flushnodelist ( eqtb [27433 + n ].hh .v.RH ) ;
  eqtb [27433 + n ].hh .v.RH = -268435455L ;
} 
void 
zensurevbox ( eightbits n ) 
{
  ensurevbox_regmem 
  halfword p  ;
  p = eqtb [27433 + n ].hh .v.RH ;
  if ( p != -268435455L ) {
      
    if ( mem [p ].hh.b0 == 0 ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 1397 ) ;
      } 
      {
	helpptr = 3 ;
	helpline [2 ]= 1398 ;
	helpline [1 ]= 1399 ;
	helpline [0 ]= 1400 ;
      } 
      boxerror ( n ) ;
    } 
  } 
} 
void 
zfireup ( halfword c ) 
{
  /* 10 */ fireup_regmem 
  halfword p, q, r, s  ;
  halfword prevp  ;
  unsigned char n  ;
  boolean wait  ;
  integer savevbadness  ;
  scaled savevfuzz  ;
  halfword savesplittopskip  ;
  if ( mem [bestpagebreak ].hh.b0 == 12 ) 
  {
    geqworddefine ( 29313 , mem [bestpagebreak + 1 ].cint ) ;
    mem [bestpagebreak + 1 ].cint = 10000 ;
  } 
  else geqworddefine ( 29313 , 10000 ) ;
  if ( saroot [6 ]!= -268435455L ) {
      
    if ( domarks ( 1 , 0 , saroot [6 ]) ) 
    saroot [6 ]= -268435455L ;
  } 
  if ( curmark [2 ]!= -268435455L ) 
  {
    if ( curmark [0 ]!= -268435455L ) 
    deletetokenref ( curmark [0 ]) ;
    curmark [0 ]= curmark [2 ];
    incr ( mem [curmark [0 ]].hh .v.LH ) ;
    deletetokenref ( curmark [1 ]) ;
    curmark [1 ]= -268435455L ;
  } 
  if ( c == bestpagebreak ) 
  bestpagebreak = -268435455L ;
  if ( eqtb [27688 ].hh .v.RH != -268435455L ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 345 ) ;
    } 
    printesc ( 429 ) ;
    print ( 1410 ) ;
    {
      helpptr = 2 ;
      helpline [1 ]= 1411 ;
      helpline [0 ]= 1400 ;
    } 
    boxerror ( 255 ) ;
  } 
  insertpenalties = 0 ;
  savesplittopskip = eqtb [26638 ].hh .v.RH ;
  if ( eqtb [29327 ].cint <= 0 ) 
  {
    r = mem [memtop ].hh .v.RH ;
    while ( r != memtop ) {
	
      if ( mem [r + 2 ].hh .v.LH != -268435455L ) 
      {
	n = mem [r ].hh.b1 ;
	ensurevbox ( n ) ;
	if ( eqtb [27433 + n ].hh .v.RH == -268435455L ) 
	eqtb [27433 + n ].hh .v.RH = newnullbox () ;
	p = eqtb [27433 + n ].hh .v.RH + 5 ;
	while ( mem [p ].hh .v.RH != -268435455L ) p = mem [p ].hh .v.RH ;
	mem [r + 2 ].hh .v.RH = p ;
      } 
      r = mem [r ].hh .v.RH ;
    } 
  } 
  q = memtop - 4 ;
  mem [q ].hh .v.RH = -268435455L ;
  prevp = memtop - 2 ;
  p = mem [prevp ].hh .v.RH ;
  while ( p != bestpagebreak ) {
      
    if ( mem [p ].hh.b0 == 3 ) 
    {
      if ( eqtb [29327 ].cint <= 0 ) 
      {
	r = mem [memtop ].hh .v.RH ;
	while ( mem [r ].hh.b1 != mem [p ].hh.b1 ) r = mem [r ].hh .v.RH 
	;
	if ( mem [r + 2 ].hh .v.LH == -268435455L ) 
	wait = true ;
	else {
	    
	  wait = false ;
	  s = mem [r + 2 ].hh .v.RH ;
	  mem [s ].hh .v.RH = mem [p + 4 ].hh .v.LH ;
	  if ( mem [r + 2 ].hh .v.LH == p ) 
	  {
	    if ( mem [r ].hh.b0 == 1 ) {
		
	      if ( ( mem [r + 1 ].hh .v.LH == p ) && ( mem [r + 1 ].hh 
	      .v.RH != -268435455L ) ) 
	      {
		while ( mem [s ].hh .v.RH != mem [r + 1 ].hh .v.RH ) s = 
		mem [s ].hh .v.RH ;
		mem [s ].hh .v.RH = -268435455L ;
		eqtb [26638 ].hh .v.RH = mem [p + 4 ].hh .v.RH ;
		mem [p + 4 ].hh .v.LH = prunepagetop ( mem [r + 1 ].hh 
		.v.RH , false ) ;
		if ( mem [p + 4 ].hh .v.LH != -268435455L ) 
		{
		  tempptr = vpackage ( mem [p + 4 ].hh .v.LH , 0 , 1 , 
		  1073741823L ) ;
		  mem [p + 3 ].cint = mem [tempptr + 3 ].cint + mem [
		  tempptr + 2 ].cint ;
		  freenode ( tempptr , 7 ) ;
		  wait = true ;
		} 
	      } 
	    } 
	    mem [r + 2 ].hh .v.LH = -268435455L ;
	    n = mem [r ].hh.b1 ;
	    tempptr = mem [eqtb [27433 + n ].hh .v.RH + 5 ].hh .v.RH ;
	    freenode ( eqtb [27433 + n ].hh .v.RH , 7 ) ;
	    eqtb [27433 + n ].hh .v.RH = vpackage ( tempptr , 0 , 1 , 
	    1073741823L ) ;
	  } 
	  else {
	      
	    while ( mem [s ].hh .v.RH != -268435455L ) s = mem [s ].hh 
	    .v.RH ;
	    mem [r + 2 ].hh .v.RH = s ;
	  } 
	} 
	mem [prevp ].hh .v.RH = mem [p ].hh .v.RH ;
	mem [p ].hh .v.RH = -268435455L ;
	if ( wait ) 
	{
	  mem [q ].hh .v.RH = p ;
	  q = p ;
	  incr ( insertpenalties ) ;
	} 
	else {
	    
	  deleteglueref ( mem [p + 4 ].hh .v.RH ) ;
	  freenode ( p , 5 ) ;
	} 
	p = prevp ;
      } 
    } 
    else if ( mem [p ].hh.b0 == 4 ) {
	
      if ( mem [p + 1 ].hh .v.LH != 0 ) 
      {
	findsaelement ( 6 , mem [p + 1 ].hh .v.LH , true ) ;
	if ( mem [curptr + 1 ].hh .v.RH == -268435455L ) 
	{
	  mem [curptr + 1 ].hh .v.RH = mem [p + 1 ].hh .v.RH ;
	  incr ( mem [mem [p + 1 ].hh .v.RH ].hh .v.LH ) ;
	} 
	if ( mem [curptr + 2 ].hh .v.LH != -268435455L ) 
	deletetokenref ( mem [curptr + 2 ].hh .v.LH ) ;
	mem [curptr + 2 ].hh .v.LH = mem [p + 1 ].hh .v.RH ;
	incr ( mem [mem [p + 1 ].hh .v.RH ].hh .v.LH ) ;
      } 
      else {
	  
	if ( curmark [1 ]== -268435455L ) 
	{
	  curmark [1 ]= mem [p + 1 ].hh .v.RH ;
	  incr ( mem [curmark [1 ]].hh .v.LH ) ;
	} 
	if ( curmark [2 ]!= -268435455L ) 
	deletetokenref ( curmark [2 ]) ;
	curmark [2 ]= mem [p + 1 ].hh .v.RH ;
	incr ( mem [curmark [2 ]].hh .v.LH ) ;
      } 
    } 
    prevp = p ;
    p = mem [prevp ].hh .v.RH ;
  } 
  eqtb [26638 ].hh .v.RH = savesplittopskip ;
  if ( p != -268435455L ) 
  {
    if ( mem [memtop - 1 ].hh .v.RH == -268435455L ) {
	
      if ( nestptr == 0 ) 
      curlist .tailfield = pagetail ;
      else nest [0 ].tailfield = pagetail ;
    } 
    mem [pagetail ].hh .v.RH = mem [memtop - 1 ].hh .v.RH ;
    mem [memtop - 1 ].hh .v.RH = p ;
    mem [prevp ].hh .v.RH = -268435455L ;
  } 
  savevbadness = eqtb [29301 ].cint ;
  eqtb [29301 ].cint = 10000 ;
  savevfuzz = eqtb [29896 ].cint ;
  eqtb [29896 ].cint = 1073741823L ;
  eqtb [27688 ].hh .v.RH = vpackage ( mem [memtop - 2 ].hh .v.RH , 
  bestsize , 0 , pagemaxdepth ) ;
  eqtb [29301 ].cint = savevbadness ;
  eqtb [29896 ].cint = savevfuzz ;
  if ( lastglue != 268435455L ) 
  deleteglueref ( lastglue ) ;
  pagecontents = 0 ;
  pagetail = memtop - 2 ;
  mem [memtop - 2 ].hh .v.RH = -268435455L ;
  lastglue = 268435455L ;
  lastpenalty = 0 ;
  lastkern = 0 ;
  lastnodetype = -1 ;
  pagesofar [7 ]= 0 ;
  pagemaxdepth = 0 ;
  if ( q != memtop - 4 ) 
  {
    mem [memtop - 2 ].hh .v.RH = mem [memtop - 4 ].hh .v.RH ;
    pagetail = q ;
  } 
  r = mem [memtop ].hh .v.RH ;
  while ( r != memtop ) {
      
    q = mem [r ].hh .v.RH ;
    freenode ( r , 4 ) ;
    r = q ;
  } 
  mem [memtop ].hh .v.RH = memtop ;
  if ( saroot [6 ]!= -268435455L ) {
      
    if ( domarks ( 2 , 0 , saroot [6 ]) ) 
    saroot [6 ]= -268435455L ;
  } 
  if ( ( curmark [0 ]!= -268435455L ) && ( curmark [1 ]== -268435455L ) ) 
  {
    curmark [1 ]= curmark [0 ];
    incr ( mem [curmark [0 ]].hh .v.LH ) ;
  } 
  if ( eqtb [27159 ].hh .v.RH != -268435455L ) {
      
    if ( deadcycles >= eqtb [29314 ].cint ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 1412 ) ;
      } 
      printint ( deadcycles ) ;
      print ( 1413 ) ;
      {
	helpptr = 3 ;
	helpline [2 ]= 1414 ;
	helpline [1 ]= 1415 ;
	helpline [0 ]= 1416 ;
      } 
      error () ;
    } 
    else {
	
      outputactive = true ;
      incr ( deadcycles ) ;
      pushnest () ;
      curlist .modefield = -1 ;
      curlist .auxfield .cint = eqtb [29919 ].cint ;
      curlist .mlfield = - (integer) line ;
      begintokenlist ( eqtb [27159 ].hh .v.RH , 6 ) ;
      newsavelevel ( 8 ) ;
      normalparagraph () ;
      scanleftbrace () ;
      return ;
    } 
  } 
  {
    if ( mem [memtop - 2 ].hh .v.RH != -268435455L ) 
    {
      if ( mem [memtop - 1 ].hh .v.RH == -268435455L ) {
	  
	if ( nestptr == 0 ) 
	curlist .tailfield = pagetail ;
	else nest [0 ].tailfield = pagetail ;
      } 
      else mem [pagetail ].hh .v.RH = mem [memtop - 1 ].hh .v.RH ;
      mem [memtop - 1 ].hh .v.RH = mem [memtop - 2 ].hh .v.RH ;
      mem [memtop - 2 ].hh .v.RH = -268435455L ;
      pagetail = memtop - 2 ;
    } 
    flushnodelist ( discptr [2 ]) ;
    discptr [2 ]= -268435455L ;
    shipout ( eqtb [27688 ].hh .v.RH ) ;
    eqtb [27688 ].hh .v.RH = -268435455L ;
  } 
} 
void 
buildpage ( void ) 
{
  /* 10 30 31 22 80 90 */ buildpage_regmem 
  halfword p  ;
  halfword q, r  ;
  integer b, c  ;
  integer pi  ;
  unsigned char n  ;
  scaled delta, h, w  ;
  if ( ( mem [memtop - 1 ].hh .v.RH == -268435455L ) || outputactive ) 
  return ;
  do {
      lab22: p = mem [memtop - 1 ].hh .v.RH ;
    if ( lastglue != 268435455L ) 
    deleteglueref ( lastglue ) ;
    lastpenalty = 0 ;
    lastkern = 0 ;
    lastnodetype = mem [p ].hh.b0 + 1 ;
    if ( mem [p ].hh.b0 == 10 ) 
    {
      lastglue = mem [p + 1 ].hh .v.LH ;
      incr ( mem [lastglue ].hh .v.RH ) ;
    } 
    else {
	
      lastglue = 268435455L ;
      if ( mem [p ].hh.b0 == 12 ) 
      lastpenalty = mem [p + 1 ].cint ;
      else if ( mem [p ].hh.b0 == 11 ) 
      lastkern = mem [p + 1 ].cint ;
    } 
    switch ( mem [p ].hh.b0 ) 
    {case 0 : 
    case 1 : 
    case 2 : 
      if ( pagecontents < 2 ) 
      {
	if ( pagecontents == 0 ) 
	freezepagespecs ( 2 ) ;
	else pagecontents = 2 ;
	q = newskipparam ( 9 ) ;
	if ( mem [tempptr + 1 ].cint > mem [p + 3 ].cint ) 
	mem [tempptr + 1 ].cint = mem [tempptr + 1 ].cint - mem [p + 3 ]
	.cint ;
	else mem [tempptr + 1 ].cint = 0 ;
	mem [q ].hh .v.RH = p ;
	mem [memtop - 1 ].hh .v.RH = q ;
	goto lab22 ;
      } 
      else {
	  
	pagesofar [1 ]= pagesofar [1 ]+ pagesofar [7 ]+ mem [p + 3 ]
	.cint ;
	pagesofar [7 ]= mem [p + 2 ].cint ;
	goto lab80 ;
      } 
      break ;
    case 8 : 
      if ( ( pagecontents < 2 ) && ( ( mem [p ].hh.b1 == 35 ) || ( mem [p ]
      .hh.b1 == 36 ) ) ) 
      {
	print ( 1365 ) ;
	goto lab31 ;
      } 
      else {
	  
	if ( ( mem [p ].hh.b1 == 10 ) || ( mem [p ].hh.b1 == 12 ) ) 
	{
	  pagesofar [1 ]= pagesofar [1 ]+ pagesofar [7 ]+ mem [p + 2 ]
	  .cint ;
	  pagesofar [7 ]= mem [p + 3 ].cint ;
	} 
	goto lab80 ;
      } 
      break ;
    case 10 : 
      if ( pagecontents < 2 ) 
      goto lab31 ;
      else if ( ( mem [pagetail ].hh.b0 < 9 ) ) 
      pi = 0 ;
      else goto lab90 ;
      break ;
    case 11 : 
      if ( pagecontents < 2 ) 
      goto lab31 ;
      else if ( mem [p ].hh .v.RH == -268435455L ) 
      return ;
      else if ( mem [mem [p ].hh .v.RH ].hh.b0 == 10 ) 
      pi = 0 ;
      else goto lab90 ;
      break ;
    case 12 : 
      if ( pagecontents < 2 ) 
      goto lab31 ;
      else pi = mem [p + 1 ].cint ;
      break ;
    case 4 : 
      goto lab80 ;
      break ;
    case 3 : 
      {
	if ( pagecontents == 0 ) 
	freezepagespecs ( 1 ) ;
	n = mem [p ].hh.b1 ;
	r = memtop ;
	while ( n >= mem [mem [r ].hh .v.RH ].hh.b1 ) r = mem [r ].hh 
	.v.RH ;
	n = n ;
	if ( mem [r ].hh.b1 != n ) 
	{
	  q = getnode ( 4 ) ;
	  mem [q ].hh .v.RH = mem [r ].hh .v.RH ;
	  mem [r ].hh .v.RH = q ;
	  r = q ;
	  mem [r ].hh.b1 = n ;
	  mem [r ].hh.b0 = 0 ;
	  ensurevbox ( n ) ;
	  if ( eqtb [27433 + n ].hh .v.RH == -268435455L ) 
	  mem [r + 3 ].cint = 0 ;
	  else mem [r + 3 ].cint = mem [eqtb [27433 + n ].hh .v.RH + 3 ]
	  .cint + mem [eqtb [27433 + n ].hh .v.RH + 2 ].cint ;
	  mem [r + 2 ].hh .v.LH = -268435455L ;
	  q = eqtb [26646 + n ].hh .v.RH ;
	  if ( eqtb [29375 + n ].cint == 1000 ) 
	  h = mem [r + 3 ].cint ;
	  else h = xovern ( mem [r + 3 ].cint , 1000 ) * eqtb [29375 + n ]
	  .cint ;
	  pagesofar [0 ]= pagesofar [0 ]- h - mem [q + 1 ].cint ;
	  pagesofar [2 + mem [q ].hh.b0 ]= pagesofar [2 + mem [q ]
	  .hh.b0 ]+ mem [q + 2 ].cint ;
	  pagesofar [6 ]= pagesofar [6 ]+ mem [q + 3 ].cint ;
	  if ( ( mem [q ].hh.b1 != 0 ) && ( mem [q + 3 ].cint != 0 ) ) 
	  {
	    {
	      if ( interaction == 3 ) 
	      ;
	      if ( filelineerrorstylep ) 
	      printfileline () ;
	      else printnl ( 264 ) ;
	      print ( 1405 ) ;
	    } 
	    printesc ( 412 ) ;
	    printint ( n ) ;
	    {
	      helpptr = 3 ;
	      helpline [2 ]= 1406 ;
	      helpline [1 ]= 1407 ;
	      helpline [0 ]= 1324 ;
	    } 
	    error () ;
	  } 
	} 
	if ( mem [r ].hh.b0 == 1 ) 
	insertpenalties = insertpenalties + mem [p + 1 ].cint ;
	else {
	    
	  mem [r + 2 ].hh .v.RH = p ;
	  delta = pagesofar [0 ]- pagesofar [1 ]- pagesofar [7 ]+ 
	  pagesofar [6 ];
	  if ( eqtb [29375 + n ].cint == 1000 ) 
	  h = mem [p + 3 ].cint ;
	  else h = xovern ( mem [p + 3 ].cint , 1000 ) * eqtb [29375 + n ]
	  .cint ;
	  if ( ( ( h <= 0 ) || ( h <= delta ) ) && ( mem [p + 3 ].cint + mem 
	  [r + 3 ].cint <= eqtb [29921 + n ].cint ) ) 
	  {
	    pagesofar [0 ]= pagesofar [0 ]- h ;
	    mem [r + 3 ].cint = mem [r + 3 ].cint + mem [p + 3 ].cint ;
	  } 
	  else {
	      
	    if ( eqtb [29375 + n ].cint <= 0 ) 
	    w = 1073741823L ;
	    else {
		
	      w = pagesofar [0 ]- pagesofar [1 ]- pagesofar [7 ];
	      if ( eqtb [29375 + n ].cint != 1000 ) 
	      w = xovern ( w , eqtb [29375 + n ].cint ) * 1000 ;
	    } 
	    if ( w > eqtb [29921 + n ].cint - mem [r + 3 ].cint ) 
	    w = eqtb [29921 + n ].cint - mem [r + 3 ].cint ;
	    q = vertbreak ( mem [p + 4 ].hh .v.LH , w , mem [p + 2 ].cint 
	    ) ;
	    mem [r + 3 ].cint = mem [r + 3 ].cint + bestheightplusdepth ;
	;
#ifdef STAT
	    if ( eqtb [29307 ].cint > 0 ) 
	    {
	      begindiagnostic () ;
	      printnl ( 1408 ) ;
	      printint ( n ) ;
	      print ( 1409 ) ;
	      printscaled ( w ) ;
	      printchar ( 44 ) ;
	      printscaled ( bestheightplusdepth ) ;
	      print ( 1337 ) ;
	      if ( q == -268435455L ) 
	      printint ( -10000 ) ;
	      else if ( mem [q ].hh.b0 == 12 ) 
	      printint ( mem [q + 1 ].cint ) ;
	      else printchar ( 48 ) ;
	      enddiagnostic ( false ) ;
	    } 
#endif /* STAT */
	    if ( eqtb [29375 + n ].cint != 1000 ) 
	    bestheightplusdepth = xovern ( bestheightplusdepth , 1000 ) * eqtb 
	    [29375 + n ].cint ;
	    pagesofar [0 ]= pagesofar [0 ]- bestheightplusdepth ;
	    mem [r ].hh.b0 = 1 ;
	    mem [r + 1 ].hh .v.RH = q ;
	    mem [r + 1 ].hh .v.LH = p ;
	    if ( q == -268435455L ) 
	    insertpenalties = insertpenalties - 10000 ;
	    else if ( mem [q ].hh.b0 == 12 ) 
	    insertpenalties = insertpenalties + mem [q + 1 ].cint ;
	  } 
	} 
	goto lab80 ;
      } 
      break ;
      default: 
      confusion ( 884 ) ;
      break ;
    } 
    if ( pi < 10000 ) 
    {
      if ( pagesofar [1 ]< pagesofar [0 ]) {
	  
	if ( ( pagesofar [3 ]!= 0 ) || ( pagesofar [4 ]!= 0 ) || ( 
	pagesofar [5 ]!= 0 ) ) 
	b = 0 ;
	else b = badness ( pagesofar [0 ]- pagesofar [1 ], pagesofar [2 ]
	) ;
      } 
      else if ( pagesofar [1 ]- pagesofar [0 ]> pagesofar [6 ]) 
      b = 1073741823L ;
      else b = badness ( pagesofar [1 ]- pagesofar [0 ], pagesofar [6 ]) 
      ;
      if ( b < 1073741823L ) {
	  
	if ( pi <= -10000 ) 
	c = pi ;
	else if ( b < 10000 ) 
	c = b + pi + insertpenalties ;
	else c = 100000L ;
      } 
      else c = b ;
      if ( insertpenalties >= 10000 ) 
      c = 1073741823L ;
	;
#ifdef STAT
      if ( eqtb [29307 ].cint > 0 ) 
      {
	begindiagnostic () ;
	printnl ( 37 ) ;
	print ( 1333 ) ;
	printtotals () ;
	print ( 1403 ) ;
	printscaled ( pagesofar [0 ]) ;
	print ( 1336 ) ;
	if ( b == 1073741823L ) 
	printchar ( 42 ) ;
	else printint ( b ) ;
	print ( 1337 ) ;
	printint ( pi ) ;
	print ( 1404 ) ;
	if ( c == 1073741823L ) 
	printchar ( 42 ) ;
	else printint ( c ) ;
	if ( c <= leastpagecost ) 
	printchar ( 35 ) ;
	enddiagnostic ( false ) ;
      } 
#endif /* STAT */
      if ( c <= leastpagecost ) 
      {
	bestpagebreak = p ;
	bestsize = pagesofar [0 ];
	leastpagecost = c ;
	r = mem [memtop ].hh .v.RH ;
	while ( r != memtop ) {
	    
	  mem [r + 2 ].hh .v.LH = mem [r + 2 ].hh .v.RH ;
	  r = mem [r ].hh .v.RH ;
	} 
      } 
      if ( ( c == 1073741823L ) || ( pi <= -10000 ) ) 
      {
	fireup ( p ) ;
	if ( outputactive ) 
	return ;
	goto lab30 ;
      } 
    } 
    if ( ( mem [p ].hh.b0 < 10 ) || ( mem [p ].hh.b0 > 11 ) ) 
    goto lab80 ;
    lab90: if ( mem [p ].hh.b0 == 11 ) 
    q = p ;
    else {
	
      q = mem [p + 1 ].hh .v.LH ;
      pagesofar [2 + mem [q ].hh.b0 ]= pagesofar [2 + mem [q ].hh.b0 ]
      + mem [q + 2 ].cint ;
      pagesofar [6 ]= pagesofar [6 ]+ mem [q + 3 ].cint ;
      if ( ( mem [q ].hh.b1 != 0 ) && ( mem [q + 3 ].cint != 0 ) ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 1401 ) ;
	} 
	{
	  helpptr = 4 ;
	  helpline [3 ]= 1402 ;
	  helpline [2 ]= 1371 ;
	  helpline [1 ]= 1372 ;
	  helpline [0 ]= 1324 ;
	} 
	error () ;
	r = newspec ( q ) ;
	mem [r ].hh.b1 = 0 ;
	deleteglueref ( q ) ;
	mem [p + 1 ].hh .v.LH = r ;
	q = r ;
      } 
    } 
    pagesofar [1 ]= pagesofar [1 ]+ pagesofar [7 ]+ mem [q + 1 ].cint 
    ;
    pagesofar [7 ]= 0 ;
    lab80: if ( pagesofar [7 ]> pagemaxdepth ) 
    {
      pagesofar [1 ]= pagesofar [1 ]+ pagesofar [7 ]- pagemaxdepth ;
      pagesofar [7 ]= pagemaxdepth ;
    } 
    mem [pagetail ].hh .v.RH = p ;
    pagetail = p ;
    mem [memtop - 1 ].hh .v.RH = mem [p ].hh .v.RH ;
    mem [p ].hh .v.RH = -268435455L ;
    goto lab30 ;
    lab31: mem [memtop - 1 ].hh .v.RH = mem [p ].hh .v.RH ;
    mem [p ].hh .v.RH = -268435455L ;
    if ( eqtb [29372 ].cint > 0 ) 
    {
      if ( discptr [2 ]== -268435455L ) 
      discptr [2 ]= p ;
      else mem [discptr [1 ]].hh .v.RH = p ;
      discptr [1 ]= p ;
    } 
    else flushnodelist ( p ) ;
    lab30: ;
  } while ( ! ( mem [memtop - 1 ].hh .v.RH == -268435455L ) ) ;
  if ( nestptr == 0 ) 
  curlist .tailfield = memtop - 1 ;
  else nest [0 ].tailfield = memtop - 1 ;
} 
void 
appspace ( void ) 
{
  appspace_regmem 
  halfword q  ;
  if ( ( curlist .auxfield .hh .v.LH >= 2000 ) && ( eqtb [26641 ].hh .v.RH 
  != membot ) ) 
  q = newparamglue ( 13 ) ;
  else {
      
    if ( eqtb [26640 ].hh .v.RH != membot ) 
    mainp = eqtb [26640 ].hh .v.RH ;
    else {
	
      mainp = fontglue [eqtb [27689 ].hh .v.RH ];
      if ( mainp == -268435455L ) 
      {
	mainp = newspec ( membot ) ;
	maink = parambase [eqtb [27689 ].hh .v.RH ]+ 2 ;
	mem [mainp + 1 ].cint = fontinfo [maink ].cint ;
	mem [mainp + 2 ].cint = fontinfo [maink + 1 ].cint ;
	mem [mainp + 3 ].cint = fontinfo [maink + 2 ].cint ;
	fontglue [eqtb [27689 ].hh .v.RH ]= mainp ;
      } 
    } 
    mainp = newspec ( mainp ) ;
    if ( curlist .auxfield .hh .v.LH >= 2000 ) 
    mem [mainp + 1 ].cint = mem [mainp + 1 ].cint + fontinfo [7 + 
    parambase [eqtb [27689 ].hh .v.RH ]].cint ;
    mem [mainp + 2 ].cint = xnoverd ( mem [mainp + 2 ].cint , curlist 
    .auxfield .hh .v.LH , 1000 ) ;
    mem [mainp + 3 ].cint = xnoverd ( mem [mainp + 3 ].cint , 1000 , 
    curlist .auxfield .hh .v.LH ) ;
    q = newglue ( mainp ) ;
    mem [mainp ].hh .v.RH = -268435455L ;
  } 
  mem [curlist .tailfield ].hh .v.RH = q ;
  curlist .tailfield = q ;
} 
void 
insertdollarsign ( void ) 
{
  insertdollarsign_regmem 
  backinput () ;
  curtok = 804 ;
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 264 ) ;
    print ( 1424 ) ;
  } 
  {
    helpptr = 2 ;
    helpline [1 ]= 1425 ;
    helpline [0 ]= 1426 ;
  } 
  inserror () ;
} 
void 
youcant ( void ) 
{
  youcant_regmem 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 264 ) ;
    print ( 781 ) ;
  } 
  printcmdchr ( curcmd , curchr ) ;
  printinmode ( curlist .modefield ) ;
} 
void 
reportillegalcase ( void ) 
{
  reportillegalcase_regmem 
  youcant () ;
  {
    helpptr = 4 ;
    helpline [3 ]= 1427 ;
    helpline [2 ]= 1428 ;
    helpline [1 ]= 1429 ;
    helpline [0 ]= 1430 ;
  } 
  error () ;
} 
boolean 
privileged ( void ) 
{
  register boolean Result; privileged_regmem 
  if ( curlist .modefield > 0 ) 
  Result = true ;
  else {
      
    reportillegalcase () ;
    Result = false ;
  } 
  return Result ;
} 
boolean 
itsallover ( void ) 
{
  /* 10 */ register boolean Result; itsallover_regmem 
  if ( privileged () ) 
  {
    if ( ( memtop - 2 == pagetail ) && ( curlist .headfield == curlist 
    .tailfield ) && ( deadcycles == 0 ) ) 
    {
      Result = true ;
      return Result ;
    } 
    backinput () ;
    {
      mem [curlist .tailfield ].hh .v.RH = newnullbox () ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    mem [curlist .tailfield + 1 ].cint = eqtb [29890 ].cint ;
    {
      mem [curlist .tailfield ].hh .v.RH = newglue ( membot + 8 ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    {
      mem [curlist .tailfield ].hh .v.RH = newpenalty ( -1073741824L ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    buildpage () ;
  } 
  Result = false ;
  return Result ;
} 
void 
appendglue ( void ) 
{
  appendglue_regmem 
  smallnumber s  ;
  s = curchr ;
  switch ( s ) 
  {case 0 : 
    curval = membot + 4 ;
    break ;
  case 1 : 
    curval = membot + 8 ;
    break ;
  case 2 : 
    curval = membot + 12 ;
    break ;
  case 3 : 
    curval = membot + 16 ;
    break ;
  case 4 : 
    scanglue ( 2 ) ;
    break ;
  case 5 : 
    scanglue ( 3 ) ;
    break ;
  } 
  {
    mem [curlist .tailfield ].hh .v.RH = newglue ( curval ) ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  if ( s >= 4 ) 
  {
    decr ( mem [curval ].hh .v.RH ) ;
    if ( s > 4 ) 
    mem [curlist .tailfield ].hh.b1 = 99 ;
  } 
} 
void 
appendkern ( void ) 
{
  appendkern_regmem 
  quarterword s  ;
  s = curchr ;
  scandimen ( s == 99 , false , false ) ;
  {
    mem [curlist .tailfield ].hh .v.RH = newkern ( curval ) ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  mem [curlist .tailfield ].hh.b1 = s ;
} 
void 
offsave ( void ) 
{
  offsave_regmem 
  halfword p  ;
  if ( curgroup == 0 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 927 ) ;
    } 
    printcmdchr ( curcmd , curchr ) ;
    {
      helpptr = 1 ;
      helpline [0 ]= 1448 ;
    } 
    error () ;
  } 
  else {
      
    backinput () ;
    p = getavail () ;
    mem [memtop - 3 ].hh .v.RH = p ;
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 707 ) ;
    } 
    switch ( curgroup ) 
    {case 14 : 
      {
	mem [p ].hh .v.LH = 19611 ;
	printesc ( 588 ) ;
      } 
      break ;
    case 15 : 
      {
	mem [p ].hh .v.LH = 804 ;
	printchar ( 36 ) ;
      } 
      break ;
    case 16 : 
      {
	mem [p ].hh .v.LH = 19612 ;
	mem [p ].hh .v.RH = getavail () ;
	p = mem [p ].hh .v.RH ;
	mem [p ].hh .v.LH = 3118 ;
	printesc ( 1447 ) ;
      } 
      break ;
      default: 
      {
	mem [p ].hh .v.LH = 637 ;
	printchar ( 125 ) ;
      } 
      break ;
    } 
    print ( 708 ) ;
    begintokenlist ( mem [memtop - 3 ].hh .v.RH , 4 ) ;
    {
      helpptr = 5 ;
      helpline [4 ]= 1442 ;
      helpline [3 ]= 1443 ;
      helpline [2 ]= 1444 ;
      helpline [1 ]= 1445 ;
      helpline [0 ]= 1446 ;
    } 
    error () ;
  } 
} 
void 
extrarightbrace ( void ) 
{
  extrarightbrace_regmem 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 264 ) ;
    print ( 1453 ) ;
  } 
  switch ( curgroup ) 
  {case 14 : 
    printesc ( 588 ) ;
    break ;
  case 15 : 
    printchar ( 36 ) ;
    break ;
  case 16 : 
    printesc ( 1278 ) ;
    break ;
  } 
  {
    helpptr = 5 ;
    helpline [4 ]= 1454 ;
    helpline [3 ]= 1455 ;
    helpline [2 ]= 1456 ;
    helpline [1 ]= 1457 ;
    helpline [0 ]= 1458 ;
  } 
  error () ;
  incr ( alignstate ) ;
} 
void 
normalparagraph ( void ) 
{
  normalparagraph_regmem 
  if ( eqtb [29293 ].cint != 0 ) 
  eqworddefine ( 29293 , 0 ) ;
  if ( eqtb [29904 ].cint != 0 ) 
  eqworddefine ( 29904 , 0 ) ;
  if ( eqtb [29315 ].cint != 1 ) 
  eqworddefine ( 29315 , 1 ) ;
  if ( eqtb [27158 ].hh .v.RH != -268435455L ) 
  eqdefine ( 27158 , 120 , -268435455L ) ;
  if ( eqtb [27429 ].hh .v.RH != -268435455L ) 
  eqdefine ( 27429 , 120 , -268435455L ) ;
} 
void 
zboxend ( integer boxcontext ) 
{
  boxend_regmem 
  halfword p  ;
  smallnumber a  ;
  if ( boxcontext < 1073741824L ) 
  {
    if ( curbox != -268435455L ) 
    {
      mem [curbox + 4 ].cint = boxcontext ;
      if ( abs ( curlist .modefield ) == 1 ) 
      {
	if ( preadjusttail != -268435455L ) 
	{
	  if ( memtop - 14 != preadjusttail ) 
	  {
	    mem [curlist .tailfield ].hh .v.RH = mem [memtop - 14 ].hh 
	    .v.RH ;
	    curlist .tailfield = preadjusttail ;
	  } 
	  preadjusttail = -268435455L ;
	} 
	appendtovlist ( curbox ) ;
	if ( adjusttail != -268435455L ) 
	{
	  if ( memtop - 5 != adjusttail ) 
	  {
	    mem [curlist .tailfield ].hh .v.RH = mem [memtop - 5 ].hh 
	    .v.RH ;
	    curlist .tailfield = adjusttail ;
	  } 
	  adjusttail = -268435455L ;
	} 
	if ( curlist .modefield > 0 ) 
	buildpage () ;
      } 
      else {
	  
	if ( abs ( curlist .modefield ) == 104 ) 
	curlist .auxfield .hh .v.LH = 1000 ;
	else {
	    
	  p = newnoad () ;
	  mem [p + 1 ].hh .v.RH = 2 ;
	  mem [p + 1 ].hh .v.LH = curbox ;
	  curbox = p ;
	} 
	mem [curlist .tailfield ].hh .v.RH = curbox ;
	curlist .tailfield = curbox ;
      } 
    } 
  } 
  else if ( boxcontext < 1073807360L ) 
  {
    if ( boxcontext < 1073774592L ) 
    {
      curval = boxcontext - 1073741824L ;
      a = 0 ;
    } 
    else {
	
      curval = boxcontext - 1073774592L ;
      a = 4 ;
    } 
    if ( curval < 256 ) {
	
      if ( ( a >= 4 ) ) 
      geqdefine ( 27433 + curval , 121 , curbox ) ;
      else eqdefine ( 27433 + curval , 121 , curbox ) ;
    } 
    else {
	
      findsaelement ( 4 , curval , true ) ;
      if ( ( a >= 4 ) ) 
      gsadef ( curptr , curbox ) ;
      else sadef ( curptr , curbox ) ;
    } 
  } 
  else if ( curbox != -268435455L ) {
      
    if ( boxcontext > 1073807360L ) 
    {
      do {
	  getxtoken () ;
      } while ( ! ( ( curcmd != 10 ) && ( curcmd != 0 ) ) ) ;
      if ( ( ( curcmd == 26 ) && ( abs ( curlist .modefield ) != 1 ) ) || ( ( 
      curcmd == 27 ) && ( abs ( curlist .modefield ) == 1 ) ) ) 
      {
	appendglue () ;
	mem [curlist .tailfield ].hh.b1 = boxcontext - ( 1073807261L ) ;
	mem [curlist .tailfield + 1 ].hh .v.RH = curbox ;
      } 
      else {
	  
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 1471 ) ;
	} 
	{
	  helpptr = 3 ;
	  helpline [2 ]= 1472 ;
	  helpline [1 ]= 1473 ;
	  helpline [0 ]= 1474 ;
	} 
	backerror () ;
	flushnodelist ( curbox ) ;
      } 
    } 
    else shipout ( curbox ) ;
  } 
} 
void 
zbeginbox ( integer boxcontext ) 
{
  /* 10 30 */ beginbox_regmem 
  halfword p, q  ;
  halfword r  ;
  boolean fm  ;
  halfword tx  ;
  quarterword m  ;
  halfword k  ;
  halfword n  ;
  switch ( curchr ) 
  {case 0 : 
    {
      scanregisternum () ;
      if ( curval < 256 ) 
      curbox = eqtb [27433 + curval ].hh .v.RH ;
      else {
	  
	findsaelement ( 4 , curval , false ) ;
	if ( curptr == -268435455L ) 
	curbox = -268435455L ;
	else curbox = mem [curptr + 1 ].hh .v.RH ;
      } 
      if ( curval < 256 ) 
      eqtb [27433 + curval ].hh .v.RH = -268435455L ;
      else {
	  
	findsaelement ( 4 , curval , false ) ;
	if ( curptr != -268435455L ) 
	{
	  mem [curptr + 1 ].hh .v.RH = -268435455L ;
	  incr ( mem [curptr + 1 ].hh .v.LH ) ;
	  deletesaref ( curptr ) ;
	} 
      } 
    } 
    break ;
  case 1 : 
    {
      scanregisternum () ;
      if ( curval < 256 ) 
      q = eqtb [27433 + curval ].hh .v.RH ;
      else {
	  
	findsaelement ( 4 , curval , false ) ;
	if ( curptr == -268435455L ) 
	q = -268435455L ;
	else q = mem [curptr + 1 ].hh .v.RH ;
      } 
      curbox = copynodelist ( q ) ;
    } 
    break ;
  case 2 : 
    {
      curbox = -268435455L ;
      if ( abs ( curlist .modefield ) == 207 ) 
      {
	youcant () ;
	{
	  helpptr = 1 ;
	  helpline [0 ]= 1476 ;
	} 
	error () ;
      } 
      else if ( ( curlist .modefield == 1 ) && ( curlist .headfield == curlist 
      .tailfield ) ) 
      {
	youcant () ;
	{
	  helpptr = 2 ;
	  helpline [1 ]= 1477 ;
	  helpline [0 ]= 1478 ;
	} 
	error () ;
      } 
      else {
	  
	tx = curlist .tailfield ;
	if ( ! ( tx >= himemmin ) ) {
	    
	  if ( ( mem [tx ].hh.b0 == 9 ) && ( mem [tx ].hh.b1 == 3 ) ) 
	  {
	    r = curlist .headfield ;
	    do {
		q = r ;
	      r = mem [q ].hh .v.RH ;
	    } while ( ! ( r == tx ) ) ;
	    tx = q ;
	  } 
	} 
	if ( ! ( tx >= himemmin ) ) {
	    
	  if ( ( mem [tx ].hh.b0 == 0 ) || ( mem [tx ].hh.b0 == 1 ) ) 
	  {
	    q = curlist .headfield ;
	    p = -268435455L ;
	    do {
		r = p ;
	      p = q ;
	      fm = false ;
	      if ( ! ( q >= himemmin ) ) {
		  
		if ( mem [q ].hh.b0 == 7 ) 
		{
		  {register integer for_end; m = 1 ;for_end = mem [q ]
		  .hh.b1 ; if ( m <= for_end) do 
		    p = mem [p ].hh .v.RH ;
		  while ( m++ < for_end ) ;} 
		  if ( p == tx ) 
		  goto lab30 ;
		} 
		else if ( ( mem [q ].hh.b0 == 9 ) && ( mem [q ].hh.b1 == 2 
		) ) 
		fm = true ;
	      } 
	      q = mem [p ].hh .v.RH ;
	    } while ( ! ( q == tx ) ) ;
	    q = mem [tx ].hh .v.RH ;
	    mem [p ].hh .v.RH = q ;
	    mem [tx ].hh .v.RH = -268435455L ;
	    if ( q == -268435455L ) {
		
	      if ( fm ) 
	      confusion ( 1475 ) ;
	      else curlist .tailfield = p ;
	    } 
	    else if ( fm ) 
	    {
	      curlist .tailfield = r ;
	      mem [r ].hh .v.RH = -268435455L ;
	      flushnodelist ( p ) ;
	    } 
	    curbox = tx ;
	    mem [curbox + 4 ].cint = 0 ;
	  } 
	} 
	lab30: ;
      } 
    } 
    break ;
  case 3 : 
    {
      scanregisternum () ;
      n = curval ;
      if ( ! scankeyword ( 1237 ) ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 1479 ) ;
	} 
	{
	  helpptr = 2 ;
	  helpline [1 ]= 1480 ;
	  helpline [0 ]= 1481 ;
	} 
	error () ;
      } 
      scandimen ( false , false , false ) ;
      curbox = vsplit ( n , curval ) ;
    } 
    break ;
    default: 
    {
      k = curchr - 4 ;
      savestack [saveptr + 0 ].cint = boxcontext ;
      if ( k == 104 ) {
	  
	if ( ( boxcontext < 1073741824L ) && ( abs ( curlist .modefield ) == 1 
	) ) 
	scanspec ( 3 , true ) ;
	else scanspec ( 2 , true ) ;
      } 
      else {
	  
	if ( k == 1 ) 
	scanspec ( 4 , true ) ;
	else {
	    
	  scanspec ( 5 , true ) ;
	  k = 1 ;
	} 
	normalparagraph () ;
      } 
      pushnest () ;
      curlist .modefield = - (integer) k ;
      if ( k == 1 ) 
      {
	curlist .auxfield .cint = eqtb [29919 ].cint ;
	if ( eqtb [27164 ].hh .v.RH != -268435455L ) 
	begintokenlist ( eqtb [27164 ].hh .v.RH , 11 ) ;
      } 
      else {
	  
	curlist .auxfield .hh .v.LH = 1000 ;
	if ( eqtb [27163 ].hh .v.RH != -268435455L ) 
	begintokenlist ( eqtb [27163 ].hh .v.RH , 10 ) ;
      } 
      return ;
    } 
    break ;
  } 
  boxend ( boxcontext ) ;
} 
void 
zscanbox ( integer boxcontext ) 
{
  scanbox_regmem 
  do {
      getxtoken () ;
  } while ( ! ( ( curcmd != 10 ) && ( curcmd != 0 ) ) ) ;
  if ( curcmd == 20 ) 
  beginbox ( boxcontext ) ;
  else if ( ( boxcontext >= 1073807361L ) && ( ( curcmd == 36 ) || ( curcmd == 
  35 ) ) ) 
  {
    curbox = scanrulespec () ;
    boxend ( boxcontext ) ;
  } 
  else {
      
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 1482 ) ;
    } 
    {
      helpptr = 3 ;
      helpline [2 ]= 1483 ;
      helpline [1 ]= 1484 ;
      helpline [0 ]= 1485 ;
    } 
    backerror () ;
  } 
} 
void 
zpackage ( smallnumber c ) 
{
  package_regmem 
  scaled h  ;
  halfword p  ;
  scaled d  ;
  d = eqtb [29894 ].cint ;
  unsave () ;
  saveptr = saveptr - 3 ;
  if ( curlist .modefield == -104 ) 
  curbox = hpack ( mem [curlist .headfield ].hh .v.RH , savestack [saveptr 
  + 2 ].cint , savestack [saveptr + 1 ].cint ) ;
  else {
      
    curbox = vpackage ( mem [curlist .headfield ].hh .v.RH , savestack [
    saveptr + 2 ].cint , savestack [saveptr + 1 ].cint , d ) ;
    if ( c == 4 ) 
    {
      h = 0 ;
      p = mem [curbox + 5 ].hh .v.RH ;
      if ( p != -268435455L ) {
	  
	if ( mem [p ].hh.b0 <= 2 ) 
	h = mem [p + 3 ].cint ;
      } 
      mem [curbox + 2 ].cint = mem [curbox + 2 ].cint - h + mem [curbox + 
      3 ].cint ;
      mem [curbox + 3 ].cint = h ;
    } 
  } 
  popnest () ;
  boxend ( savestack [saveptr + 0 ].cint ) ;
} 
smallnumber 
znormmin ( integer h ) 
{
  register smallnumber Result; normmin_regmem 
  if ( h <= 0 ) 
  Result = 1 ;
  else if ( h >= 63 ) 
  Result = 63 ;
  else Result = h ;
  return Result ;
} 
void 
znewgraf ( boolean indented ) 
{
  newgraf_regmem 
  curlist .pgfield = 0 ;
  if ( ( curlist .modefield == 1 ) || ( curlist .headfield != curlist 
  .tailfield ) ) 
  {
    mem [curlist .tailfield ].hh .v.RH = newparamglue ( 2 ) ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  pushnest () ;
  curlist .modefield = 104 ;
  curlist .auxfield .hh .v.LH = 1000 ;
  if ( eqtb [29324 ].cint <= 0 ) 
  curlang = 0 ;
  else if ( eqtb [29324 ].cint > 255 ) 
  curlang = 0 ;
  else curlang = eqtb [29324 ].cint ;
  curlist .auxfield .hh .v.RH = curlang ;
  curlist .pgfield = ( normmin ( eqtb [29325 ].cint ) * 64 + normmin ( eqtb 
  [29326 ].cint ) ) * 65536L + curlang ;
  if ( indented ) 
  {
    curlist .tailfield = newnullbox () ;
    mem [curlist .headfield ].hh .v.RH = curlist .tailfield ;
    mem [curlist .tailfield + 1 ].cint = eqtb [29887 ].cint ;
    if ( ( insertsrcspecialeverypar ) ) 
    insertsrcspecial () ;
  } 
  if ( eqtb [27160 ].hh .v.RH != -268435455L ) 
  begintokenlist ( eqtb [27160 ].hh .v.RH , 7 ) ;
  if ( nestptr == 1 ) 
  buildpage () ;
} 
void 
indentinhmode ( void ) 
{
  indentinhmode_regmem 
  halfword p, q  ;
  if ( curchr > 0 ) 
  {
    p = newnullbox () ;
    mem [p + 1 ].cint = eqtb [29887 ].cint ;
    if ( abs ( curlist .modefield ) == 104 ) 
    curlist .auxfield .hh .v.LH = 1000 ;
    else {
	
      q = newnoad () ;
      mem [q + 1 ].hh .v.RH = 2 ;
      mem [q + 1 ].hh .v.LH = p ;
      p = q ;
    } 
    {
      mem [curlist .tailfield ].hh .v.RH = p ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
  } 
} 
void 
headforvmode ( void ) 
{
  headforvmode_regmem 
  if ( curlist .modefield < 0 ) {
      
    if ( curcmd != 36 ) 
    offsave () ;
    else {
	
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 781 ) ;
      } 
      printesc ( 595 ) ;
      print ( 1489 ) ;
      {
	helpptr = 2 ;
	helpline [1 ]= 1490 ;
	helpline [0 ]= 1491 ;
      } 
      error () ;
    } 
  } 
  else {
      
    backinput () ;
    curtok = partoken ;
    backinput () ;
    curinput .indexfield = 4 ;
  } 
} 
void 
endgraf ( void ) 
{
  endgraf_regmem 
  if ( curlist .modefield == 104 ) 
  {
    if ( curlist .headfield == curlist .tailfield ) 
    popnest () ;
    else linebreak ( false ) ;
    if ( curlist .eTeXauxfield != -268435455L ) 
    {
      flushlist ( curlist .eTeXauxfield ) ;
      curlist .eTeXauxfield = -268435455L ;
    } 
    normalparagraph () ;
    errorcount = 0 ;
  } 
} 
void 
begininsertoradjust ( void ) 
{
  begininsertoradjust_regmem 
  if ( curcmd == 38 ) 
  curval = 255 ;
  else {
      
    scaneightbitint () ;
    if ( curval == 255 ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 1492 ) ;
      } 
      printesc ( 337 ) ;
      printint ( 255 ) ;
      {
	helpptr = 1 ;
	helpline [0 ]= 1493 ;
      } 
      error () ;
      curval = 0 ;
    } 
  } 
  savestack [saveptr + 0 ].cint = curval ;
  if ( ( curcmd == 38 ) && scankeyword ( 1494 ) ) 
  savestack [saveptr + 1 ].cint = 1 ;
  else savestack [saveptr + 1 ].cint = 0 ;
  saveptr = saveptr + 2 ;
  newsavelevel ( 11 ) ;
  scanleftbrace () ;
  normalparagraph () ;
  pushnest () ;
  curlist .modefield = -1 ;
  curlist .auxfield .cint = eqtb [29919 ].cint ;
} 
void 
makemark ( void ) 
{
  makemark_regmem 
  halfword p  ;
  halfword c  ;
  if ( curchr == 0 ) 
  c = 0 ;
  else {
      
    scanregisternum () ;
    c = curval ;
  } 
  p = scantoks ( false , true ) ;
  p = getnode ( 2 ) ;
  mem [p + 1 ].hh .v.LH = c ;
  mem [p ].hh.b0 = 4 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].hh .v.RH = defref ;
  mem [curlist .tailfield ].hh .v.RH = p ;
  curlist .tailfield = p ;
} 
void 
appendpenalty ( void ) 
{
  appendpenalty_regmem 
  scanint () ;
  {
    mem [curlist .tailfield ].hh .v.RH = newpenalty ( curval ) ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  if ( curlist .modefield == 1 ) 
  buildpage () ;
} 
void 
deletelast ( void ) 
{
  /* 10 */ deletelast_regmem 
  halfword p, q  ;
  halfword r  ;
  boolean fm  ;
  halfword tx  ;
  quarterword m  ;
  if ( ( curlist .modefield == 1 ) && ( curlist .tailfield == curlist 
  .headfield ) ) 
  {
    if ( ( curchr != 10 ) || ( lastglue != 268435455L ) ) 
    {
      youcant () ;
      {
	helpptr = 2 ;
	helpline [1 ]= 1477 ;
	helpline [0 ]= 1495 ;
      } 
      if ( curchr == 11 ) 
      helpline [0 ]= ( 1496 ) ;
      else if ( curchr != 10 ) 
      helpline [0 ]= ( 1497 ) ;
      error () ;
    } 
  } 
  else {
      
    tx = curlist .tailfield ;
    if ( ! ( tx >= himemmin ) ) {
	
      if ( ( mem [tx ].hh.b0 == 9 ) && ( mem [tx ].hh.b1 == 3 ) ) 
      {
	r = curlist .headfield ;
	do {
	    q = r ;
	  r = mem [q ].hh .v.RH ;
	} while ( ! ( r == tx ) ) ;
	tx = q ;
      } 
    } 
    if ( ! ( tx >= himemmin ) ) {
	
      if ( mem [tx ].hh.b0 == curchr ) 
      {
	q = curlist .headfield ;
	p = -268435455L ;
	do {
	    r = p ;
	  p = q ;
	  fm = false ;
	  if ( ! ( q >= himemmin ) ) {
	      
	    if ( mem [q ].hh.b0 == 7 ) 
	    {
	      {register integer for_end; m = 1 ;for_end = mem [q ].hh.b1 
	      ; if ( m <= for_end) do 
		p = mem [p ].hh .v.RH ;
	      while ( m++ < for_end ) ;} 
	      if ( p == tx ) 
	      return ;
	    } 
	    else if ( ( mem [q ].hh.b0 == 9 ) && ( mem [q ].hh.b1 == 2 ) ) 
	    fm = true ;
	  } 
	  q = mem [p ].hh .v.RH ;
	} while ( ! ( q == tx ) ) ;
	q = mem [tx ].hh .v.RH ;
	mem [p ].hh .v.RH = q ;
	mem [tx ].hh .v.RH = -268435455L ;
	if ( q == -268435455L ) {
	    
	  if ( fm ) 
	  confusion ( 1475 ) ;
	  else curlist .tailfield = p ;
	} 
	else if ( fm ) 
	{
	  curlist .tailfield = r ;
	  mem [r ].hh .v.RH = -268435455L ;
	  flushnodelist ( p ) ;
	} 
	flushnodelist ( tx ) ;
      } 
    } 
  } 
} 
void 
unpackage ( void ) 
{
  /* 30 10 */ unpackage_regmem 
  halfword p  ;
  halfword r  ;
  unsigned char c  ;
  if ( curchr > 1 ) 
  {
    mem [curlist .tailfield ].hh .v.RH = discptr [curchr ];
    discptr [curchr ]= -268435455L ;
    goto lab30 ;
  } 
  c = curchr ;
  scanregisternum () ;
  if ( curval < 256 ) 
  p = eqtb [27433 + curval ].hh .v.RH ;
  else {
      
    findsaelement ( 4 , curval , false ) ;
    if ( curptr == -268435455L ) 
    p = -268435455L ;
    else p = mem [curptr + 1 ].hh .v.RH ;
  } 
  if ( p == -268435455L ) 
  return ;
  if ( ( abs ( curlist .modefield ) == 207 ) || ( ( abs ( curlist .modefield ) 
  == 1 ) && ( mem [p ].hh.b0 != 1 ) ) || ( ( abs ( curlist .modefield ) == 
  104 ) && ( mem [p ].hh.b0 != 0 ) ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 1505 ) ;
    } 
    {
      helpptr = 3 ;
      helpline [2 ]= 1506 ;
      helpline [1 ]= 1507 ;
      helpline [0 ]= 1508 ;
    } 
    error () ;
    return ;
  } 
  if ( c == 1 ) 
  mem [curlist .tailfield ].hh .v.RH = copynodelist ( mem [p + 5 ].hh 
  .v.RH ) ;
  else {
      
    mem [curlist .tailfield ].hh .v.RH = mem [p + 5 ].hh .v.RH ;
    if ( curval < 256 ) 
    eqtb [27433 + curval ].hh .v.RH = -268435455L ;
    else {
	
      findsaelement ( 4 , curval , false ) ;
      if ( curptr != -268435455L ) 
      {
	mem [curptr + 1 ].hh .v.RH = -268435455L ;
	incr ( mem [curptr + 1 ].hh .v.LH ) ;
	deletesaref ( curptr ) ;
      } 
    } 
    freenode ( p , 7 ) ;
  } 
  lab30: while ( mem [curlist .tailfield ].hh .v.RH != -268435455L ) {
      
    r = mem [curlist .tailfield ].hh .v.RH ;
    if ( ! ( r >= himemmin ) && ( mem [r ].hh.b0 == 40 ) ) 
    {
      mem [curlist .tailfield ].hh .v.RH = mem [r ].hh .v.RH ;
      {
	mem [mem [r + 2 ].hh .v.LH ].hh .v.RH = avail ;
	avail = mem [r + 2 ].hh .v.LH ;
	;
#ifdef STAT
	decr ( dynused ) ;
#endif /* STAT */
      } 
      freenode ( r , 3 ) ;
    } 
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
} 
void 
appenditaliccorrection ( void ) 
{
  /* 10 */ appenditaliccorrection_regmem 
  halfword p  ;
  internalfontnumber f  ;
  if ( curlist .tailfield != curlist .headfield ) 
  {
    if ( ( curlist .tailfield >= himemmin ) ) 
    p = curlist .tailfield ;
    else if ( mem [curlist .tailfield ].hh.b0 == 6 ) 
    p = curlist .tailfield + 1 ;
    else return ;
    f = mem [p ].hh.b0 ;
    {
      mem [curlist .tailfield ].hh .v.RH = newkern ( fontinfo [italicbase [
      f ]+ ( fontinfo [charbase [f ]+ effectivechar ( true , f , mem [p ]
      .hh.b1 ) ].qqqq .b2 ) / 4 ].cint ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    mem [curlist .tailfield ].hh.b1 = 1 ;
  } 
} 
void 
appenddiscretionary ( void ) 
{
  appenddiscretionary_regmem 
  integer c  ;
  {
    mem [curlist .tailfield ].hh .v.RH = newdisc () ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  if ( curchr == 1 ) 
  {
    c = hyphenchar [eqtb [27689 ].hh .v.RH ];
    if ( c >= 0 ) {
	
      if ( c < 256 ) 
      mem [curlist .tailfield + 1 ].hh .v.LH = newcharacter ( eqtb [27689 ]
      .hh .v.RH , c ) ;
    } 
  } 
  else {
      
    incr ( saveptr ) ;
    savestack [saveptr - 1 ].cint = 0 ;
    newsavelevel ( 10 ) ;
    scanleftbrace () ;
    pushnest () ;
    curlist .modefield = -104 ;
    curlist .auxfield .hh .v.LH = 1000 ;
  } 
} 
void 
builddiscretionary ( void ) 
{
  /* 30 10 */ builddiscretionary_regmem 
  halfword p, q  ;
  integer n  ;
  unsave () ;
  q = curlist .headfield ;
  p = mem [q ].hh .v.RH ;
  n = 0 ;
  while ( p != -268435455L ) {
      
    if ( ! ( p >= himemmin ) ) {
	
      if ( mem [p ].hh.b0 > 2 ) {
	  
	if ( mem [p ].hh.b0 != 11 ) {
	    
	  if ( mem [p ].hh.b0 != 6 ) 
	  {
	    {
	      if ( interaction == 3 ) 
	      ;
	      if ( filelineerrorstylep ) 
	      printfileline () ;
	      else printnl ( 264 ) ;
	      print ( 1515 ) ;
	    } 
	    {
	      helpptr = 1 ;
	      helpline [0 ]= 1516 ;
	    } 
	    error () ;
	    begindiagnostic () ;
	    printnl ( 1517 ) ;
	    showbox ( p ) ;
	    enddiagnostic ( true ) ;
	    flushnodelist ( p ) ;
	    mem [q ].hh .v.RH = -268435455L ;
	    goto lab30 ;
	  } 
	} 
      } 
    } 
    q = p ;
    p = mem [q ].hh .v.RH ;
    incr ( n ) ;
  } 
  lab30: ;
  p = mem [curlist .headfield ].hh .v.RH ;
  popnest () ;
  switch ( savestack [saveptr - 1 ].cint ) 
  {case 0 : 
    mem [curlist .tailfield + 1 ].hh .v.LH = p ;
    break ;
  case 1 : 
    mem [curlist .tailfield + 1 ].hh .v.RH = p ;
    break ;
  case 2 : 
    {
      if ( ( n > 0 ) && ( abs ( curlist .modefield ) == 207 ) ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 1509 ) ;
	} 
	printesc ( 357 ) ;
	{
	  helpptr = 2 ;
	  helpline [1 ]= 1510 ;
	  helpline [0 ]= 1511 ;
	} 
	flushnodelist ( p ) ;
	n = 0 ;
	error () ;
      } 
      else mem [curlist .tailfield ].hh .v.RH = p ;
      if ( n <= 255 ) 
      mem [curlist .tailfield ].hh.b1 = n ;
      else {
	  
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 1512 ) ;
	} 
	{
	  helpptr = 2 ;
	  helpline [1 ]= 1513 ;
	  helpline [0 ]= 1514 ;
	} 
	error () ;
      } 
      if ( n > 0 ) 
      curlist .tailfield = q ;
      decr ( saveptr ) ;
      return ;
    } 
    break ;
  } 
  incr ( savestack [saveptr - 1 ].cint ) ;
  newsavelevel ( 10 ) ;
  scanleftbrace () ;
  pushnest () ;
  curlist .modefield = -104 ;
  curlist .auxfield .hh .v.LH = 1000 ;
} 
void 
makeaccent ( void ) 
{
  makeaccent_regmem 
  real s, t  ;
  halfword p, q, r  ;
  internalfontnumber f  ;
  scaled a, h, x, w, delta  ;
  fourquarters i  ;
  scancharnum () ;
  f = eqtb [27689 ].hh .v.RH ;
  p = newcharacter ( f , curval ) ;
  if ( p != -268435455L ) 
  {
    x = fontinfo [5 + parambase [f ]].cint ;
    s = fontinfo [1 + parambase [f ]].cint / ((double) 65536.0 ) ;
    a = fontinfo [widthbase [f ]+ fontinfo [charbase [f ]+ effectivechar 
    ( true , f , mem [p ].hh.b1 ) ].qqqq .b0 ].cint ;
    doassignments () ;
    q = -268435455L ;
    f = eqtb [27689 ].hh .v.RH ;
    if ( ( curcmd == 11 ) || ( curcmd == 12 ) || ( curcmd == 68 ) ) 
    q = newcharacter ( f , curchr ) ;
    else if ( curcmd == 16 ) 
    {
      scancharnum () ;
      q = newcharacter ( f , curval ) ;
    } 
    else backinput () ;
    if ( q != -268435455L ) 
    {
      t = fontinfo [1 + parambase [f ]].cint / ((double) 65536.0 ) ;
      i = fontinfo [charbase [f ]+ effectivechar ( true , f , mem [q ]
      .hh.b1 ) ].qqqq ;
      w = fontinfo [widthbase [f ]+ i .b0 ].cint ;
      h = fontinfo [heightbase [f ]+ ( i .b1 ) / 16 ].cint ;
      if ( h != x ) 
      {
	p = hpack ( p , 0 , 1 ) ;
	mem [p + 4 ].cint = x - h ;
      } 
      delta = round ( ( w - a ) / ((double) 2.0 ) + h * t - x * s ) ;
      r = newkern ( delta ) ;
      mem [r ].hh.b1 = 2 ;
      mem [curlist .tailfield ].hh .v.RH = r ;
      mem [r ].hh .v.RH = p ;
      curlist .tailfield = newkern ( - (integer) a - delta ) ;
      mem [curlist .tailfield ].hh.b1 = 2 ;
      mem [p ].hh .v.RH = curlist .tailfield ;
      p = q ;
    } 
    mem [curlist .tailfield ].hh .v.RH = p ;
    curlist .tailfield = p ;
    curlist .auxfield .hh .v.LH = 1000 ;
  } 
} 
void 
alignerror ( void ) 
{
  alignerror_regmem 
  if ( abs ( alignstate ) > 2 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 1522 ) ;
    } 
    printcmdchr ( curcmd , curchr ) ;
    if ( curtok == 1062 ) 
    {
      {
	helpptr = 6 ;
	helpline [5 ]= 1523 ;
	helpline [4 ]= 1524 ;
	helpline [3 ]= 1525 ;
	helpline [2 ]= 1526 ;
	helpline [1 ]= 1527 ;
	helpline [0 ]= 1528 ;
      } 
    } 
    else {
	
      {
	helpptr = 5 ;
	helpline [4 ]= 1523 ;
	helpline [3 ]= 1529 ;
	helpline [2 ]= 1526 ;
	helpline [1 ]= 1527 ;
	helpline [0 ]= 1528 ;
      } 
    } 
    error () ;
  } 
  else {
      
    backinput () ;
    if ( alignstate < 0 ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 739 ) ;
      } 
      incr ( alignstate ) ;
      curtok = 379 ;
    } 
    else {
	
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 1518 ) ;
      } 
      decr ( alignstate ) ;
      curtok = 637 ;
    } 
    {
      helpptr = 3 ;
      helpline [2 ]= 1519 ;
      helpline [1 ]= 1520 ;
      helpline [0 ]= 1521 ;
    } 
    inserror () ;
  } 
} 
void 
noalignerror ( void ) 
{
  noalignerror_regmem 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 264 ) ;
    print ( 1522 ) ;
  } 
  printesc ( 601 ) ;
  {
    helpptr = 2 ;
    helpline [1 ]= 1530 ;
    helpline [0 ]= 1531 ;
  } 
  error () ;
} 
void 
omiterror ( void ) 
{
  omiterror_regmem 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 264 ) ;
    print ( 1522 ) ;
  } 
  printesc ( 604 ) ;
  {
    helpptr = 2 ;
    helpline [1 ]= 1532 ;
    helpline [0 ]= 1531 ;
  } 
  error () ;
} 
void 
doendv ( void ) 
{
  doendv_regmem 
  baseptr = inputptr ;
  inputstack [baseptr ]= curinput ;
  while ( ( inputstack [baseptr ].indexfield != 2 ) && ( inputstack [
  baseptr ].locfield == -268435455L ) && ( inputstack [baseptr ].statefield 
  == 0 ) ) decr ( baseptr ) ;
  if ( ( inputstack [baseptr ].indexfield != 2 ) || ( inputstack [baseptr ]
  .locfield != -268435455L ) || ( inputstack [baseptr ].statefield != 0 ) ) 
  fatalerror ( 674 ) ;
  if ( curgroup == 6 ) 
  {
    endgraf () ;
    if ( fincol () ) 
    finrow () ;
  } 
  else offsave () ;
} 
void 
cserror ( void ) 
{
  cserror_regmem 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 264 ) ;
    print ( 927 ) ;
  } 
  printesc ( 577 ) ;
  {
    helpptr = 1 ;
    helpline [0 ]= 1534 ;
  } 
  error () ;
} 
void 
zpushmath ( groupcode c ) 
{
  pushmath_regmem 
  pushnest () ;
  curlist .modefield = -207 ;
  curlist .auxfield .cint = -268435455L ;
  newsavelevel ( c ) ;
} 
void 
zjustcopy ( halfword p , halfword h , halfword t ) 
{
  /* 40 45 */ justcopy_regmem 
  halfword r  ;
  unsigned char words  ;
  while ( p != -268435455L ) {
      
    words = 1 ;
    if ( ( p >= himemmin ) ) 
    r = getavail () ;
    else switch ( mem [p ].hh.b0 ) 
    {case 0 : 
    case 1 : 
      {
	r = getnode ( 7 ) ;
	mem [r + 6 ]= mem [p + 6 ];
	mem [r + 5 ]= mem [p + 5 ];
	words = 5 ;
	mem [r + 5 ].hh .v.RH = -268435455L ;
      } 
      break ;
    case 2 : 
      {
	r = getnode ( 4 ) ;
	words = 4 ;
      } 
      break ;
    case 6 : 
      {
	r = getavail () ;
	mem [r ]= mem [p + 1 ];
	goto lab40 ;
      } 
      break ;
    case 11 : 
    case 9 : 
      {
	r = getnode ( 2 ) ;
	words = 2 ;
      } 
      break ;
    case 10 : 
      {
	r = getnode ( 2 ) ;
	incr ( mem [mem [p + 1 ].hh .v.LH ].hh .v.RH ) ;
	mem [r + 1 ].hh .v.LH = mem [p + 1 ].hh .v.LH ;
	mem [r + 1 ].hh .v.RH = -268435455L ;
      } 
      break ;
    case 8 : 
      switch ( mem [p ].hh.b1 ) 
      {case 0 : 
	{
	  r = getnode ( 3 ) ;
	  words = 3 ;
	} 
	break ;
      case 1 : 
      case 3 : 
	{
	  r = getnode ( 2 ) ;
	  incr ( mem [mem [p + 1 ].hh .v.RH ].hh .v.LH ) ;
	  words = 2 ;
	} 
	break ;
      case 2 : 
      case 4 : 
	{
	  r = getnode ( 2 ) ;
	  words = 2 ;
	} 
	break ;
      case 6 : 
	{
	  r = getnode ( 2 ) ;
	  incr ( mem [mem [p + 1 ].hh .v.RH ].hh .v.LH ) ;
	  words = 2 ;
	} 
	break ;
      case 38 : 
	{
	  if ( mem [p + 1 ].hh .v.LH <= 1 ) 
	  {
	    r = getnode ( 3 ) ;
	    incr ( mem [mem [p + 2 ].hh .v.RH ].hh .v.LH ) ;
	    words = 3 ;
	  } 
	  else {
	      
	    r = getnode ( 2 ) ;
	    words = 2 ;
	  } 
	} 
	break ;
      case 39 : 
	{
	  r = getnode ( 2 ) ;
	  incr ( mem [mem [p + 1 ].hh .v.RH ].hh .v.LH ) ;
	  words = 2 ;
	} 
	break ;
      case 40 : 
	{
	  r = getnode ( 2 ) ;
	  words = 2 ;
	} 
	break ;
      case 41 : 
	{
	  r = getnode ( 2 ) ;
	  words = 2 ;
	} 
	break ;
      case 8 : 
	{
	  r = getnode ( 2 ) ;
	  words = 2 ;
	} 
	break ;
      case 10 : 
	{
	  r = getnode ( 5 ) ;
	  words = 5 ;
	} 
	break ;
      case 12 : 
	{
	  r = getnode ( 5 ) ;
	  words = 5 ;
	} 
	break ;
      case 13 : 
	{
	  r = getnode ( 7 ) ;
	  incr ( mem [mem [p + 5 ].hh .v.LH ].hh .v.LH ) ;
	  words = 7 ;
	} 
	break ;
      case 14 : 
	{
	  r = getnode ( 7 ) ;
	  mem [r + 2 ].cint = mem [p + 2 ].cint ;
	  mem [r + 3 ].cint = mem [p + 3 ].cint ;
	  mem [r + 1 ].cint = mem [p + 1 ].cint ;
	  mem [r + 5 ].hh .v.LH = mem [p + 5 ].hh .v.LH ;
	  if ( mem [r + 5 ].hh .v.LH != -268435455L ) 
	  incr ( mem [mem [r + 5 ].hh .v.LH ].hh .v.LH ) ;
	  mem [r + 5 ].hh .v.RH = mem [p + 5 ].hh .v.RH ;
	  incr ( mem [mem [r + 5 ].hh .v.RH + 2 ].hh .v.RH ) ;
	  mem [r + 6 ].cint = mem [p + 6 ].cint ;
	} 
	break ;
      case 15 : 
	r = getnode ( 2 ) ;
	break ;
      case 17 : 
	{
	  r = getnode ( 7 ) ;
	  if ( mem [p + 5 ].hh.b1 > 0 ) 
	  incr ( mem [mem [p + 5 ].hh .v.RH ].hh .v.LH ) ;
	  words = 7 ;
	} 
	break ;
      case 18 : 
      case 19 : 
	{
	  r = getnode ( 7 ) ;
	  if ( mem [p + 5 ].hh.b1 > 0 ) 
	  incr ( mem [mem [p + 5 ].hh .v.RH ].hh .v.LH ) ;
	  if ( mem [p + 6 ].hh .v.LH != -268435455L ) 
	  incr ( mem [mem [p + 6 ].hh .v.LH ].hh .v.LH ) ;
	  words = 7 ;
	} 
	break ;
      case 20 : 
	r = getnode ( 2 ) ;
	break ;
      case 21 : 
	r = getnode ( 2 ) ;
	break ;
      case 34 : 
	r = getnode ( 2 ) ;
	break ;
      case 35 : 
	{
	  incr ( mem [mem [p + 1 ].hh .v.LH ].hh .v.RH ) ;
	  r = getnode ( 3 ) ;
	  words = 3 ;
	} 
	break ;
      case 36 : 
	r = getnode ( 2 ) ;
	break ;
      case 43 : 
	r = getnode ( 2 ) ;
	break ;
      case 44 : 
	r = getnode ( 2 ) ;
	break ;
      case 45 : 
	r = getnode ( 2 ) ;
	break ;
	default: 
	confusion ( 1889 ) ;
	break ;
      } 
      break ;
      default: 
      goto lab45 ;
      break ;
    } 
    while ( words > 0 ) {
	
      decr ( words ) ;
      mem [r + words ]= mem [p + words ];
    } 
    lab40: mem [h ].hh .v.RH = r ;
    h = r ;
    lab45: p = mem [p ].hh .v.RH ;
  } 
  mem [h ].hh .v.RH = t ;
} 
void 
zjustreverse ( halfword p ) 
{
  /* 40 30 */ justreverse_regmem 
  halfword l  ;
  halfword t  ;
  halfword q  ;
  halfword m, n  ;
  m = -268435455L ;
  n = -268435455L ;
  if ( mem [memtop - 3 ].hh .v.RH == -268435455L ) 
  {
    justcopy ( mem [p ].hh .v.RH , memtop - 3 , -268435455L ) ;
    q = mem [memtop - 3 ].hh .v.RH ;
  } 
  else {
      
    q = mem [p ].hh .v.RH ;
    mem [p ].hh .v.RH = -268435455L ;
    flushnodelist ( mem [memtop - 3 ].hh .v.RH ) ;
  } 
  t = newedge ( curdir , 0 ) ;
  l = t ;
  curdir = 1 - curdir ;
  while ( q != -268435455L ) if ( ( q >= himemmin ) ) 
  do {
      p = q ;
    q = mem [p ].hh .v.RH ;
    mem [p ].hh .v.RH = l ;
    l = p ;
  } while ( ! ( ! ( q >= himemmin ) ) ) ;
  else {
      
    p = q ;
    q = mem [p ].hh .v.RH ;
    if ( mem [p ].hh.b0 == 9 ) {
	
      if ( odd ( mem [p ].hh.b1 ) ) {
	  
	if ( mem [LRptr ].hh .v.LH != ( 4 * ( mem [p ].hh.b1 / 4 ) + 3 ) ) 
	{
	  mem [p ].hh.b0 = 11 ;
	  incr ( LRproblems ) ;
	} 
	else {
	    
	  {
	    tempptr = LRptr ;
	    LRptr = mem [tempptr ].hh .v.RH ;
	    {
	      mem [tempptr ].hh .v.RH = avail ;
	      avail = tempptr ;
	;
#ifdef STAT
	      decr ( dynused ) ;
#endif /* STAT */
	    } 
	  } 
	  if ( n > -268435455L ) 
	  {
	    decr ( n ) ;
	    decr ( mem [p ].hh.b1 ) ;
	  } 
	  else {
	      
	    if ( m > -268435455L ) 
	    decr ( m ) ;
	    else goto lab40 ;
	    mem [p ].hh.b0 = 11 ;
	  } 
	} 
      } 
      else {
	  
	{
	  tempptr = getavail () ;
	  mem [tempptr ].hh .v.LH = ( 4 * ( mem [p ].hh.b1 / 4 ) + 3 ) ;
	  mem [tempptr ].hh .v.RH = LRptr ;
	  LRptr = tempptr ;
	} 
	if ( ( n > -268435455L ) || ( ( mem [p ].hh.b1 / 8 ) != curdir ) ) 
	{
	  incr ( n ) ;
	  incr ( mem [p ].hh.b1 ) ;
	} 
	else {
	    
	  mem [p ].hh.b0 = 11 ;
	  incr ( m ) ;
	} 
      } 
    } 
    mem [p ].hh .v.RH = l ;
    l = p ;
  } 
  goto lab30 ;
  lab40: mem [t + 1 ].cint = mem [p + 1 ].cint ;
  mem [t ].hh .v.RH = q ;
  freenode ( p , 2 ) ;
  lab30: mem [memtop - 3 ].hh .v.RH = l ;
} 
void 
initmath ( void ) 
{
  /* 21 40 45 30 */ initmath_regmem 
  scaled w  ;
  halfword j  ;
  integer x  ;
  scaled l  ;
  scaled s  ;
  halfword p  ;
  halfword q  ;
  internalfontnumber f  ;
  integer n  ;
  scaled v  ;
  scaled d  ;
  gettoken () ;
  if ( ( curcmd == 3 ) && ( curlist .modefield > 0 ) ) 
  {
    j = -268435455L ;
    w = -1073741823L ;
    if ( curlist .headfield == curlist .tailfield ) 
    {
      popnest () ;
      if ( curlist .eTeXauxfield == -268435455L ) 
      x = 0 ;
      else if ( mem [curlist .eTeXauxfield ].hh .v.LH >= 8 ) 
      x = -1 ;
      else x = 1 ;
    } 
    else {
	
      linebreak ( true ) ;
      if ( ( eTeXmode == 1 ) ) 
      {
	if ( eqtb [26636 ].hh .v.RH == membot ) 
	j = newkern ( 0 ) ;
	else j = newparamglue ( 8 ) ;
	if ( eqtb [26635 ].hh .v.RH == membot ) 
	p = newkern ( 0 ) ;
	else p = newparamglue ( 7 ) ;
	mem [p ].hh .v.RH = j ;
	j = newnullbox () ;
	mem [j + 1 ].cint = mem [justbox + 1 ].cint ;
	mem [j + 4 ].cint = mem [justbox + 4 ].cint ;
	mem [j + 5 ].hh .v.RH = p ;
	mem [j + 5 ].hh.b1 = mem [justbox + 5 ].hh.b1 ;
	mem [j + 5 ].hh.b0 = mem [justbox + 5 ].hh.b0 ;
	mem [j + 6 ].gr = mem [justbox + 6 ].gr ;
      } 
      v = mem [justbox + 4 ].cint ;
      if ( curlist .eTeXauxfield == -268435455L ) 
      x = 0 ;
      else if ( mem [curlist .eTeXauxfield ].hh .v.LH >= 8 ) 
      x = -1 ;
      else x = 1 ;
      if ( x >= 0 ) 
      {
	p = mem [justbox + 5 ].hh .v.RH ;
	mem [memtop - 3 ].hh .v.RH = -268435455L ;
      } 
      else {
	  
	v = - (integer) v - mem [justbox + 1 ].cint ;
	p = newmath ( 0 , 6 ) ;
	mem [memtop - 3 ].hh .v.RH = p ;
	justcopy ( mem [justbox + 5 ].hh .v.RH , p , newmath ( 0 , 7 ) ) ;
	curdir = 1 ;
      } 
      v = v + 2 * fontinfo [6 + parambase [eqtb [27689 ].hh .v.RH ]]
      .cint ;
      if ( ( eqtb [29374 ].cint > 0 ) ) 
      {
	tempptr = getavail () ;
	mem [tempptr ].hh .v.LH = 0 ;
	mem [tempptr ].hh .v.RH = LRptr ;
	LRptr = tempptr ;
      } 
      while ( p != -268435455L ) {
	  
	lab21: if ( ( p >= himemmin ) ) 
	{
	  f = mem [p ].hh.b0 ;
	  d = fontinfo [widthbase [f ]+ fontinfo [charbase [f ]+ 
	  effectivechar ( true , f , mem [p ].hh.b1 ) ].qqqq .b0 ].cint ;
	  goto lab40 ;
	} 
	switch ( mem [p ].hh.b0 ) 
	{case 0 : 
	case 1 : 
	case 2 : 
	  {
	    d = mem [p + 1 ].cint ;
	    goto lab40 ;
	  } 
	  break ;
	case 6 : 
	  {
	    mem [memtop - 12 ]= mem [p + 1 ];
	    mem [memtop - 12 ].hh .v.RH = mem [p ].hh .v.RH ;
	    p = memtop - 12 ;
	    goto lab21 ;
	  } 
	  break ;
	case 40 : 
	  d = mem [p + 1 ].cint ;
	  break ;
	case 11 : 
	  d = mem [p + 1 ].cint ;
	  break ;
	case 9 : 
	  {
	    d = mem [p + 1 ].cint ;
	    if ( ( eqtb [29374 ].cint > 0 ) ) {
		
	      if ( odd ( mem [p ].hh.b1 ) ) 
	      {
		if ( mem [LRptr ].hh .v.LH == ( 4 * ( mem [p ].hh.b1 / 4 ) 
		+ 3 ) ) 
		{
		  tempptr = LRptr ;
		  LRptr = mem [tempptr ].hh .v.RH ;
		  {
		    mem [tempptr ].hh .v.RH = avail ;
		    avail = tempptr ;
	;
#ifdef STAT
		    decr ( dynused ) ;
#endif /* STAT */
		  } 
		} 
		else if ( mem [p ].hh.b1 > 4 ) 
		{
		  w = 1073741823L ;
		  goto lab30 ;
		} 
	      } 
	      else {
		  
		{
		  tempptr = getavail () ;
		  mem [tempptr ].hh .v.LH = ( 4 * ( mem [p ].hh.b1 / 4 ) + 
		  3 ) ;
		  mem [tempptr ].hh .v.RH = LRptr ;
		  LRptr = tempptr ;
		} 
		if ( ( mem [p ].hh.b1 / 8 ) != curdir ) 
		{
		  justreverse ( p ) ;
		  p = memtop - 3 ;
		} 
	      } 
	    } 
	    else if ( mem [p ].hh.b1 >= 4 ) 
	    {
	      w = 1073741823L ;
	      goto lab30 ;
	    } 
	  } 
	  break ;
	case 14 : 
	  {
	    d = mem [p + 1 ].cint ;
	    curdir = mem [p ].hh.b1 ;
	  } 
	  break ;
	case 10 : 
	  {
	    q = mem [p + 1 ].hh .v.LH ;
	    d = mem [q + 1 ].cint ;
	    if ( mem [justbox + 5 ].hh.b0 == 1 ) 
	    {
	      if ( ( mem [justbox + 5 ].hh.b1 == mem [q ].hh.b0 ) && ( mem 
	      [q + 2 ].cint != 0 ) ) 
	      v = 1073741823L ;
	    } 
	    else if ( mem [justbox + 5 ].hh.b0 == 2 ) 
	    {
	      if ( ( mem [justbox + 5 ].hh.b1 == mem [q ].hh.b1 ) && ( mem 
	      [q + 3 ].cint != 0 ) ) 
	      v = 1073741823L ;
	    } 
	    if ( mem [p ].hh.b1 >= 100 ) 
	    goto lab40 ;
	  } 
	  break ;
	case 8 : 
	  if ( ( mem [p ].hh.b1 == 10 ) || ( mem [p ].hh.b1 == 12 ) ) 
	  d = mem [p + 1 ].cint ;
	  else d = 0 ;
	  break ;
	  default: 
	  d = 0 ;
	  break ;
	} 
	if ( v < 1073741823L ) 
	v = v + d ;
	goto lab45 ;
	lab40: if ( v < 1073741823L ) 
	{
	  v = v + d ;
	  w = v ;
	} 
	else {
	    
	  w = 1073741823L ;
	  goto lab30 ;
	} 
	lab45: p = mem [p ].hh .v.RH ;
      } 
      lab30: if ( ( eqtb [29374 ].cint > 0 ) ) 
      {
	while ( LRptr != -268435455L ) {
	    
	  tempptr = LRptr ;
	  LRptr = mem [tempptr ].hh .v.RH ;
	  {
	    mem [tempptr ].hh .v.RH = avail ;
	    avail = tempptr ;
	;
#ifdef STAT
	    decr ( dynused ) ;
#endif /* STAT */
	  } 
	} 
	if ( LRproblems != 0 ) 
	{
	  w = 1073741823L ;
	  LRproblems = 0 ;
	} 
      } 
      curdir = 0 ;
      flushnodelist ( mem [memtop - 3 ].hh .v.RH ) ;
    } 
    if ( eqtb [27158 ].hh .v.RH == -268435455L ) {
	
      if ( ( eqtb [29904 ].cint != 0 ) && ( ( ( eqtb [29315 ].cint >= 0 ) 
      && ( curlist .pgfield + 2 > eqtb [29315 ].cint ) ) || ( curlist 
      .pgfield + 1 < - (integer) eqtb [29315 ].cint ) ) ) 
      {
	l = eqtb [29890 ].cint - abs ( eqtb [29904 ].cint ) ;
	if ( eqtb [29904 ].cint > 0 ) 
	s = eqtb [29904 ].cint ;
	else s = 0 ;
      } 
      else {
	  
	l = eqtb [29890 ].cint ;
	s = 0 ;
      } 
    } 
    else {
	
      n = mem [eqtb [27158 ].hh .v.RH ].hh .v.LH ;
      if ( curlist .pgfield + 2 >= n ) 
      p = eqtb [27158 ].hh .v.RH + 2 * n ;
      else p = eqtb [27158 ].hh .v.RH + 2 * ( curlist .pgfield + 2 ) ;
      s = mem [p - 1 ].cint ;
      l = mem [p ].cint ;
    } 
    pushmath ( 15 ) ;
    curlist .modefield = 207 ;
    eqworddefine ( 29318 , -1 ) ;
    eqworddefine ( 29900 , w ) ;
    curlist .eTeXauxfield = j ;
    if ( ( eTeXmode == 1 ) ) 
    eqworddefine ( 29370 , x ) ;
    eqworddefine ( 29901 , l ) ;
    eqworddefine ( 29902 , s ) ;
    if ( eqtb [27162 ].hh .v.RH != -268435455L ) 
    begintokenlist ( eqtb [27162 ].hh .v.RH , 9 ) ;
    if ( nestptr == 1 ) 
    buildpage () ;
  } 
  else {
      
    backinput () ;
    {
      pushmath ( 15 ) ;
      eqworddefine ( 29318 , -1 ) ;
      if ( ( insertsrcspecialeverymath ) ) 
      insertsrcspecial () ;
      if ( eqtb [27161 ].hh .v.RH != -268435455L ) 
      begintokenlist ( eqtb [27161 ].hh .v.RH , 8 ) ;
    } 
  } 
} 
void 
starteqno ( void ) 
{
  starteqno_regmem 
  savestack [saveptr + 0 ].cint = curchr ;
  incr ( saveptr ) ;
  {
    pushmath ( 15 ) ;
    eqworddefine ( 29318 , -1 ) ;
    if ( ( insertsrcspecialeverymath ) ) 
    insertsrcspecial () ;
    if ( eqtb [27161 ].hh .v.RH != -268435455L ) 
    begintokenlist ( eqtb [27161 ].hh .v.RH , 8 ) ;
  } 
} 
void 
zscanmath ( halfword p ) 
{
  /* 20 21 10 */ scanmath_regmem 
  integer c  ;
  lab20: do {
      getxtoken () ;
  } while ( ! ( ( curcmd != 10 ) && ( curcmd != 0 ) ) ) ;
  lab21: switch ( curcmd ) 
  {case 11 : 
  case 12 : 
  case 68 : 
    {
      c = eqtb [28762 + curchr ].hh .v.RH ;
      if ( c == 32768L ) 
      {
	{
	  curcs = curchr + 1 ;
	  curcmd = eqtb [curcs ].hh.b0 ;
	  curchr = eqtb [curcs ].hh .v.RH ;
	  xtoken () ;
	  backinput () ;
	} 
	goto lab20 ;
      } 
    } 
    break ;
  case 16 : 
    {
      scancharnum () ;
      curchr = curval ;
      curcmd = 68 ;
      goto lab21 ;
    } 
    break ;
  case 17 : 
    {
      scanfifteenbitint () ;
      c = curval ;
    } 
    break ;
  case 69 : 
    c = curchr ;
    break ;
  case 15 : 
    {
      scantwentysevenbitint () ;
      c = curval / 4096 ;
    } 
    break ;
    default: 
    {
      backinput () ;
      scanleftbrace () ;
      savestack [saveptr + 0 ].cint = p ;
      incr ( saveptr ) ;
      pushmath ( 9 ) ;
      return ;
    } 
    break ;
  } 
  mem [p ].hh .v.RH = 1 ;
  mem [p ].hh.b1 = c % 256 ;
  if ( ( c >= 28672 ) && ( ( eqtb [29318 ].cint >= 0 ) && ( eqtb [29318 ]
  .cint < 16 ) ) ) 
  mem [p ].hh.b0 = eqtb [29318 ].cint ;
  else mem [p ].hh.b0 = ( c / 256 ) % 16 ;
} 
void 
zsetmathchar ( integer c ) 
{
  setmathchar_regmem 
  halfword p  ;
  if ( c >= 32768L ) 
  {
    curcs = curchr + 1 ;
    curcmd = eqtb [curcs ].hh.b0 ;
    curchr = eqtb [curcs ].hh .v.RH ;
    xtoken () ;
    backinput () ;
  } 
  else {
      
    p = newnoad () ;
    mem [p + 1 ].hh .v.RH = 1 ;
    mem [p + 1 ].hh.b1 = c % 256 ;
    mem [p + 1 ].hh.b0 = ( c / 256 ) % 16 ;
    if ( c >= 28672 ) 
    {
      if ( ( ( eqtb [29318 ].cint >= 0 ) && ( eqtb [29318 ].cint < 16 ) ) 
      ) 
      mem [p + 1 ].hh.b0 = eqtb [29318 ].cint ;
      mem [p ].hh.b0 = 16 ;
    } 
    else mem [p ].hh.b0 = 16 + ( c / 4096 ) ;
    mem [curlist .tailfield ].hh .v.RH = p ;
    curlist .tailfield = p ;
  } 
} 
void 
mathlimitswitch ( void ) 
{
  /* 10 */ mathlimitswitch_regmem 
  if ( curlist .headfield != curlist .tailfield ) {
      
    if ( mem [curlist .tailfield ].hh.b0 == 17 ) 
    {
      mem [curlist .tailfield ].hh.b1 = curchr ;
      return ;
    } 
  } 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 264 ) ;
    print ( 1538 ) ;
  } 
  {
    helpptr = 1 ;
    helpline [0 ]= 1539 ;
  } 
  error () ;
} 
void 
zscandelimiter ( halfword p , boolean r ) 
{
  scandelimiter_regmem 
  if ( r ) 
  scantwentysevenbitint () ;
  else {
      
    do {
	getxtoken () ;
    } while ( ! ( ( curcmd != 10 ) && ( curcmd != 0 ) ) ) ;
    switch ( curcmd ) 
    {case 11 : 
    case 12 : 
      curval = eqtb [29631 + curchr ].cint ;
      break ;
    case 15 : 
      scantwentysevenbitint () ;
      break ;
      default: 
      curval = -1 ;
      break ;
    } 
  } 
  if ( curval < 0 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 1540 ) ;
    } 
    {
      helpptr = 6 ;
      helpline [5 ]= 1541 ;
      helpline [4 ]= 1542 ;
      helpline [3 ]= 1543 ;
      helpline [2 ]= 1544 ;
      helpline [1 ]= 1545 ;
      helpline [0 ]= 1546 ;
    } 
    backerror () ;
    curval = 0 ;
  } 
  mem [p ].qqqq .b0 = ( curval / 1048576L ) % 16 ;
  mem [p ].qqqq .b1 = ( curval / 4096 ) % 256 ;
  mem [p ].qqqq .b2 = ( curval / 256 ) % 16 ;
  mem [p ].qqqq .b3 = curval % 256 ;
} 
void 
mathradical ( void ) 
{
  mathradical_regmem 
  {
    mem [curlist .tailfield ].hh .v.RH = getnode ( 5 ) ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  mem [curlist .tailfield ].hh.b0 = 24 ;
  mem [curlist .tailfield ].hh.b1 = 0 ;
  mem [curlist .tailfield + 1 ].hh = emptyfield ;
  mem [curlist .tailfield + 3 ].hh = emptyfield ;
  mem [curlist .tailfield + 2 ].hh = emptyfield ;
  scandelimiter ( curlist .tailfield + 4 , true ) ;
  scanmath ( curlist .tailfield + 1 ) ;
} 
void 
mathac ( void ) 
{
  mathac_regmem 
  if ( curcmd == 45 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 1547 ) ;
    } 
    printesc ( 597 ) ;
    print ( 1548 ) ;
    {
      helpptr = 2 ;
      helpline [1 ]= 1549 ;
      helpline [0 ]= 1550 ;
    } 
    error () ;
  } 
  {
    mem [curlist .tailfield ].hh .v.RH = getnode ( 5 ) ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  mem [curlist .tailfield ].hh.b0 = 28 ;
  mem [curlist .tailfield ].hh.b1 = 0 ;
  mem [curlist .tailfield + 1 ].hh = emptyfield ;
  mem [curlist .tailfield + 3 ].hh = emptyfield ;
  mem [curlist .tailfield + 2 ].hh = emptyfield ;
  mem [curlist .tailfield + 4 ].hh .v.RH = 1 ;
  scanfifteenbitint () ;
  mem [curlist .tailfield + 4 ].hh.b1 = curval % 256 ;
  if ( ( curval >= 28672 ) && ( ( eqtb [29318 ].cint >= 0 ) && ( eqtb [
  29318 ].cint < 16 ) ) ) 
  mem [curlist .tailfield + 4 ].hh.b0 = eqtb [29318 ].cint ;
  else mem [curlist .tailfield + 4 ].hh.b0 = ( curval / 256 ) % 16 ;
  scanmath ( curlist .tailfield + 1 ) ;
} 
void 
appendchoices ( void ) 
{
  appendchoices_regmem 
  {
    mem [curlist .tailfield ].hh .v.RH = newchoice () ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  incr ( saveptr ) ;
  savestack [saveptr - 1 ].cint = 0 ;
  pushmath ( 13 ) ;
  scanleftbrace () ;
} 
halfword 
zfinmlist ( halfword p ) 
{
  register halfword Result; finmlist_regmem 
  halfword q  ;
  if ( curlist .auxfield .cint != -268435455L ) 
  {
    mem [curlist .auxfield .cint + 3 ].hh .v.RH = 3 ;
    mem [curlist .auxfield .cint + 3 ].hh .v.LH = mem [curlist .headfield ]
    .hh .v.RH ;
    if ( p == -268435455L ) 
    q = curlist .auxfield .cint ;
    else {
	
      q = mem [curlist .auxfield .cint + 2 ].hh .v.LH ;
      if ( ( mem [q ].hh.b0 != 30 ) || ( curlist .eTeXauxfield == 
      -268435455L ) ) 
      confusion ( 1278 ) ;
      mem [curlist .auxfield .cint + 2 ].hh .v.LH = mem [curlist 
      .eTeXauxfield ].hh .v.RH ;
      mem [curlist .eTeXauxfield ].hh .v.RH = curlist .auxfield .cint ;
      mem [curlist .auxfield .cint ].hh .v.RH = p ;
    } 
  } 
  else {
      
    mem [curlist .tailfield ].hh .v.RH = p ;
    q = mem [curlist .headfield ].hh .v.RH ;
  } 
  popnest () ;
  Result = q ;
  return Result ;
} 
void 
buildchoices ( void ) 
{
  /* 10 */ buildchoices_regmem 
  halfword p  ;
  unsave () ;
  p = finmlist ( -268435455L ) ;
  switch ( savestack [saveptr - 1 ].cint ) 
  {case 0 : 
    mem [curlist .tailfield + 1 ].hh .v.LH = p ;
    break ;
  case 1 : 
    mem [curlist .tailfield + 1 ].hh .v.RH = p ;
    break ;
  case 2 : 
    mem [curlist .tailfield + 2 ].hh .v.LH = p ;
    break ;
  case 3 : 
    {
      mem [curlist .tailfield + 2 ].hh .v.RH = p ;
      decr ( saveptr ) ;
      return ;
    } 
    break ;
  } 
  incr ( savestack [saveptr - 1 ].cint ) ;
  pushmath ( 13 ) ;
  scanleftbrace () ;
} 
void 
subsup ( void ) 
{
  subsup_regmem 
  smallnumber t  ;
  halfword p  ;
  t = 0 ;
  p = -268435455L ;
  if ( curlist .tailfield != curlist .headfield ) {
      
    if ( ( mem [curlist .tailfield ].hh.b0 >= 16 ) && ( mem [curlist 
    .tailfield ].hh.b0 < 30 ) ) 
    {
      p = curlist .tailfield + 2 + curcmd - 7 ;
      t = mem [p ].hh .v.RH ;
    } 
  } 
  if ( ( p == -268435455L ) || ( t != 0 ) ) 
  {
    {
      mem [curlist .tailfield ].hh .v.RH = newnoad () ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    p = curlist .tailfield + 2 + curcmd - 7 ;
    if ( t != 0 ) 
    {
      if ( curcmd == 7 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 1551 ) ;
	} 
	{
	  helpptr = 1 ;
	  helpline [0 ]= 1552 ;
	} 
      } 
      else {
	  
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 1553 ) ;
	} 
	{
	  helpptr = 1 ;
	  helpline [0 ]= 1554 ;
	} 
      } 
      error () ;
    } 
  } 
  scanmath ( p ) ;
} 
void 
mathfraction ( void ) 
{
  mathfraction_regmem 
  smallnumber c  ;
  c = curchr ;
  if ( curlist .auxfield .cint != -268435455L ) 
  {
    if ( c >= 3 ) 
    {
      scandelimiter ( memtop - 12 , false ) ;
      scandelimiter ( memtop - 12 , false ) ;
    } 
    if ( c % 3 == 0 ) 
    scandimen ( false , false , false ) ;
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 1561 ) ;
    } 
    {
      helpptr = 3 ;
      helpline [2 ]= 1562 ;
      helpline [1 ]= 1563 ;
      helpline [0 ]= 1564 ;
    } 
    error () ;
  } 
  else {
      
    curlist .auxfield .cint = getnode ( 6 ) ;
    mem [curlist .auxfield .cint ].hh.b0 = 25 ;
    mem [curlist .auxfield .cint ].hh.b1 = 0 ;
    mem [curlist .auxfield .cint + 2 ].hh .v.RH = 3 ;
    mem [curlist .auxfield .cint + 2 ].hh .v.LH = mem [curlist .headfield ]
    .hh .v.RH ;
    mem [curlist .auxfield .cint + 3 ].hh = emptyfield ;
    mem [curlist .auxfield .cint + 4 ].qqqq = nulldelimiter ;
    mem [curlist .auxfield .cint + 5 ].qqqq = nulldelimiter ;
    mem [curlist .headfield ].hh .v.RH = -268435455L ;
    curlist .tailfield = curlist .headfield ;
    if ( c >= 3 ) 
    {
      scandelimiter ( curlist .auxfield .cint + 4 , false ) ;
      scandelimiter ( curlist .auxfield .cint + 5 , false ) ;
    } 
    switch ( c % 3 ) 
    {case 0 : 
      {
	scandimen ( false , false , false ) ;
	mem [curlist .auxfield .cint + 1 ].cint = curval ;
      } 
      break ;
    case 1 : 
      mem [curlist .auxfield .cint + 1 ].cint = 1073741824L ;
      break ;
    case 2 : 
      mem [curlist .auxfield .cint + 1 ].cint = 0 ;
      break ;
    } 
  } 
} 
void 
mathleftright ( void ) 
{
  mathleftright_regmem 
  smallnumber t  ;
  halfword p  ;
  halfword q  ;
  t = curchr ;
  if ( ( t != 30 ) && ( curgroup != 16 ) ) 
  {
    if ( curgroup == 15 ) 
    {
      scandelimiter ( memtop - 12 , false ) ;
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 927 ) ;
      } 
      if ( t == 1 ) 
      {
	printesc ( 1279 ) ;
	{
	  helpptr = 1 ;
	  helpline [0 ]= 1565 ;
	} 
      } 
      else {
	  
	printesc ( 1278 ) ;
	{
	  helpptr = 1 ;
	  helpline [0 ]= 1566 ;
	} 
      } 
      error () ;
    } 
    else offsave () ;
  } 
  else {
      
    p = newnoad () ;
    mem [p ].hh.b0 = t ;
    scandelimiter ( p + 1 , false ) ;
    if ( t == 1 ) 
    {
      mem [p ].hh.b0 = 31 ;
      mem [p ].hh.b1 = 1 ;
    } 
    if ( t == 30 ) 
    q = p ;
    else {
	
      q = finmlist ( p ) ;
      unsave () ;
    } 
    if ( t != 31 ) 
    {
      pushmath ( 16 ) ;
      mem [curlist .headfield ].hh .v.RH = q ;
      curlist .tailfield = p ;
      curlist .eTeXauxfield = p ;
    } 
    else {
	
      {
	mem [curlist .tailfield ].hh .v.RH = newnoad () ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
      mem [curlist .tailfield ].hh.b0 = 23 ;
      mem [curlist .tailfield + 1 ].hh .v.RH = 3 ;
      mem [curlist .tailfield + 1 ].hh .v.LH = q ;
    } 
  } 
} 
void 
zappdisplay ( halfword j , halfword b , scaled d ) 
{
  appdisplay_regmem 
  scaled z  ;
  scaled s  ;
  scaled e  ;
  integer x  ;
  halfword p, q, r, t, u  ;
  s = eqtb [29902 ].cint ;
  x = eqtb [29370 ].cint ;
  if ( x == 0 ) 
  mem [b + 4 ].cint = s + d ;
  else {
      
    z = eqtb [29901 ].cint ;
    p = b ;
    if ( x > 0 ) 
    e = z - d - mem [p + 1 ].cint ;
    else {
	
      e = d ;
      d = z - e - mem [p + 1 ].cint ;
    } 
    if ( j != -268435455L ) 
    {
      b = copynodelist ( j ) ;
      mem [b + 3 ].cint = mem [p + 3 ].cint ;
      mem [b + 2 ].cint = mem [p + 2 ].cint ;
      s = s - mem [b + 4 ].cint ;
      d = d + s ;
      e = e + mem [b + 1 ].cint - z - s ;
    } 
    if ( ( mem [p ].hh.b1 ) == 2 ) 
    q = p ;
    else {
	
      r = mem [p + 5 ].hh .v.RH ;
      freenode ( p , 7 ) ;
      if ( r == -268435455L ) 
      confusion ( 2013 ) ;
      if ( x > 0 ) 
      {
	p = r ;
	do {
	    q = r ;
	  r = mem [r ].hh .v.RH ;
	} while ( ! ( r == -268435455L ) ) ;
      } 
      else {
	  
	p = -268435455L ;
	q = r ;
	do {
	    t = mem [r ].hh .v.RH ;
	  mem [r ].hh .v.RH = p ;
	  p = r ;
	  r = t ;
	} while ( ! ( r == -268435455L ) ) ;
      } 
    } 
    if ( j == -268435455L ) 
    {
      r = newkern ( 0 ) ;
      t = newkern ( 0 ) ;
    } 
    else {
	
      r = mem [b + 5 ].hh .v.RH ;
      t = mem [r ].hh .v.RH ;
    } 
    u = newmath ( 0 , 3 ) ;
    if ( mem [t ].hh.b0 == 10 ) 
    {
      j = newskipparam ( 8 ) ;
      mem [q ].hh .v.RH = j ;
      mem [j ].hh .v.RH = u ;
      j = mem [t + 1 ].hh .v.LH ;
      mem [tempptr ].hh.b0 = mem [j ].hh.b0 ;
      mem [tempptr ].hh.b1 = mem [j ].hh.b1 ;
      mem [tempptr + 1 ].cint = e - mem [j + 1 ].cint ;
      mem [tempptr + 2 ].cint = - (integer) mem [j + 2 ].cint ;
      mem [tempptr + 3 ].cint = - (integer) mem [j + 3 ].cint ;
      mem [u ].hh .v.RH = t ;
    } 
    else {
	
      mem [t + 1 ].cint = e ;
      mem [t ].hh .v.RH = u ;
      mem [q ].hh .v.RH = t ;
    } 
    u = newmath ( 0 , 2 ) ;
    if ( mem [r ].hh.b0 == 10 ) 
    {
      j = newskipparam ( 7 ) ;
      mem [u ].hh .v.RH = j ;
      mem [j ].hh .v.RH = p ;
      j = mem [r + 1 ].hh .v.LH ;
      mem [tempptr ].hh.b0 = mem [j ].hh.b0 ;
      mem [tempptr ].hh.b1 = mem [j ].hh.b1 ;
      mem [tempptr + 1 ].cint = d - mem [j + 1 ].cint ;
      mem [tempptr + 2 ].cint = - (integer) mem [j + 2 ].cint ;
      mem [tempptr + 3 ].cint = - (integer) mem [j + 3 ].cint ;
      mem [r ].hh .v.RH = u ;
    } 
    else {
	
      mem [r + 1 ].cint = d ;
      mem [r ].hh .v.RH = p ;
      mem [u ].hh .v.RH = r ;
      if ( j == -268435455L ) 
      {
	b = hpack ( u , 0 , 1 ) ;
	mem [b + 4 ].cint = s ;
      } 
      else mem [b + 5 ].hh .v.RH = u ;
    } 
  } 
  appendtovlist ( b ) ;
} 
void 
aftermath ( void ) 
{
  aftermath_regmem 
  boolean l  ;
  boolean danger  ;
  integer m  ;
  halfword p  ;
  halfword a  ;
  halfword b  ;
  scaled w  ;
  scaled z  ;
  scaled e  ;
  scaled q  ;
  scaled d  ;
  scaled s  ;
  smallnumber g1, g2  ;
  halfword r  ;
  halfword t  ;
  halfword pret  ;
  halfword j  ;
  danger = false ;
  if ( curlist .modefield == 207 ) 
  j = curlist .eTeXauxfield ;
  if ( ( fontparams [eqtb [27692 ].hh .v.RH ]< 22 ) || ( fontparams [eqtb 
  [27708 ].hh .v.RH ]< 22 ) || ( fontparams [eqtb [27724 ].hh .v.RH ]< 
  22 ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 1567 ) ;
    } 
    {
      helpptr = 3 ;
      helpline [2 ]= 1568 ;
      helpline [1 ]= 1569 ;
      helpline [0 ]= 1570 ;
    } 
    error () ;
    flushmath () ;
    danger = true ;
  } 
  else if ( ( fontparams [eqtb [27693 ].hh .v.RH ]< 13 ) || ( fontparams [
  eqtb [27709 ].hh .v.RH ]< 13 ) || ( fontparams [eqtb [27725 ].hh .v.RH 
  ]< 13 ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 1571 ) ;
    } 
    {
      helpptr = 3 ;
      helpline [2 ]= 1572 ;
      helpline [1 ]= 1573 ;
      helpline [0 ]= 1574 ;
    } 
    error () ;
    flushmath () ;
    danger = true ;
  } 
  m = curlist .modefield ;
  l = false ;
  p = finmlist ( -268435455L ) ;
  if ( curlist .modefield == - (integer) m ) 
  {
    {
      getxtoken () ;
      if ( curcmd != 3 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 1575 ) ;
	} 
	{
	  helpptr = 2 ;
	  helpline [1 ]= 1576 ;
	  helpline [0 ]= 1577 ;
	} 
	backerror () ;
      } 
    } 
    curmlist = p ;
    curstyle = 2 ;
    mlistpenalties = false ;
    mlisttohlist () ;
    a = hpack ( mem [memtop - 3 ].hh .v.RH , 0 , 1 ) ;
    mem [a ].hh.b1 = 2 ;
    unsave () ;
    decr ( saveptr ) ;
    if ( savestack [saveptr + 0 ].cint == 1 ) 
    l = true ;
    danger = false ;
    if ( curlist .modefield == 207 ) 
    j = curlist .eTeXauxfield ;
    if ( ( fontparams [eqtb [27692 ].hh .v.RH ]< 22 ) || ( fontparams [
    eqtb [27708 ].hh .v.RH ]< 22 ) || ( fontparams [eqtb [27724 ].hh 
    .v.RH ]< 22 ) ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 1567 ) ;
      } 
      {
	helpptr = 3 ;
	helpline [2 ]= 1568 ;
	helpline [1 ]= 1569 ;
	helpline [0 ]= 1570 ;
      } 
      error () ;
      flushmath () ;
      danger = true ;
    } 
    else if ( ( fontparams [eqtb [27693 ].hh .v.RH ]< 13 ) || ( fontparams 
    [eqtb [27709 ].hh .v.RH ]< 13 ) || ( fontparams [eqtb [27725 ].hh 
    .v.RH ]< 13 ) ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 1571 ) ;
      } 
      {
	helpptr = 3 ;
	helpline [2 ]= 1572 ;
	helpline [1 ]= 1573 ;
	helpline [0 ]= 1574 ;
      } 
      error () ;
      flushmath () ;
      danger = true ;
    } 
    m = curlist .modefield ;
    p = finmlist ( -268435455L ) ;
  } 
  else a = -268435455L ;
  if ( m < 0 ) 
  {
    {
      mem [curlist .tailfield ].hh .v.RH = newmath ( eqtb [29888 ].cint , 
      0 ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    curmlist = p ;
    curstyle = 2 ;
    mlistpenalties = ( curlist .modefield > 0 ) ;
    mlisttohlist () ;
    mem [curlist .tailfield ].hh .v.RH = mem [memtop - 3 ].hh .v.RH ;
    while ( mem [curlist .tailfield ].hh .v.RH != -268435455L ) curlist 
    .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    {
      mem [curlist .tailfield ].hh .v.RH = newmath ( eqtb [29888 ].cint , 
      1 ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    curlist .auxfield .hh .v.LH = 1000 ;
    unsave () ;
  } 
  else {
      
    if ( a == -268435455L ) 
    {
      getxtoken () ;
      if ( curcmd != 3 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 1575 ) ;
	} 
	{
	  helpptr = 2 ;
	  helpline [1 ]= 1576 ;
	  helpline [0 ]= 1577 ;
	} 
	backerror () ;
      } 
    } 
    curmlist = p ;
    curstyle = 0 ;
    mlistpenalties = false ;
    mlisttohlist () ;
    p = mem [memtop - 3 ].hh .v.RH ;
    adjusttail = memtop - 5 ;
    preadjusttail = memtop - 14 ;
    b = hpack ( p , 0 , 1 ) ;
    p = mem [b + 5 ].hh .v.RH ;
    t = adjusttail ;
    adjusttail = -268435455L ;
    pret = preadjusttail ;
    preadjusttail = -268435455L ;
    w = mem [b + 1 ].cint ;
    z = eqtb [29901 ].cint ;
    s = eqtb [29902 ].cint ;
    if ( eqtb [29370 ].cint < 0 ) 
    s = - (integer) s - z ;
    if ( ( a == -268435455L ) || danger ) 
    {
      e = 0 ;
      q = 0 ;
    } 
    else {
	
      e = mem [a + 1 ].cint ;
      q = e + fontinfo [6 + parambase [eqtb [27692 ].hh .v.RH ]].cint ;
    } 
    if ( w + q > z ) 
    {
      if ( ( e != 0 ) && ( ( w - totalshrink [0 ]+ q <= z ) || ( totalshrink 
      [1 ]!= 0 ) || ( totalshrink [2 ]!= 0 ) || ( totalshrink [3 ]!= 0 ) 
      ) ) 
      {
	freenode ( b , 7 ) ;
	b = hpack ( p , z - q , 0 ) ;
      } 
      else {
	  
	e = 0 ;
	if ( w > z ) 
	{
	  freenode ( b , 7 ) ;
	  b = hpack ( p , z , 0 ) ;
	} 
      } 
      w = mem [b + 1 ].cint ;
    } 
    mem [b ].hh.b1 = 2 ;
    d = half ( z - w ) ;
    if ( ( e > 0 ) && ( d < 2 * e ) ) 
    {
      d = half ( z - w - e ) ;
      if ( p != -268435455L ) {
	  
	if ( ! ( p >= himemmin ) ) {
	    
	  if ( mem [p ].hh.b0 == 10 ) 
	  d = 0 ;
	} 
      } 
    } 
    {
      mem [curlist .tailfield ].hh .v.RH = newpenalty ( eqtb [29285 ].cint 
      ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    if ( ( d + s <= eqtb [29900 ].cint ) || l ) 
    {
      g1 = 3 ;
      g2 = 4 ;
    } 
    else {
	
      g1 = 5 ;
      g2 = 6 ;
    } 
    if ( l && ( e == 0 ) ) 
    {
      appdisplay ( j , a , 0 ) ;
      {
	mem [curlist .tailfield ].hh .v.RH = newpenalty ( 10000 ) ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
    } 
    else {
	
      mem [curlist .tailfield ].hh .v.RH = newparamglue ( g1 ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    if ( e != 0 ) 
    {
      r = newkern ( z - w - e - d ) ;
      if ( l ) 
      {
	mem [a ].hh .v.RH = r ;
	mem [r ].hh .v.RH = b ;
	b = a ;
	d = 0 ;
      } 
      else {
	  
	mem [b ].hh .v.RH = r ;
	mem [r ].hh .v.RH = a ;
      } 
      b = hpack ( b , 0 , 1 ) ;
    } 
    appdisplay ( j , b , d ) ;
    if ( ( a != -268435455L ) && ( e == 0 ) && ! l ) 
    {
      {
	mem [curlist .tailfield ].hh .v.RH = newpenalty ( 10000 ) ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
      appdisplay ( j , a , z - mem [a + 1 ].cint ) ;
      g2 = 0 ;
    } 
    if ( t != memtop - 5 ) 
    {
      mem [curlist .tailfield ].hh .v.RH = mem [memtop - 5 ].hh .v.RH ;
      curlist .tailfield = t ;
    } 
    if ( pret != memtop - 14 ) 
    {
      mem [curlist .tailfield ].hh .v.RH = mem [memtop - 14 ].hh .v.RH ;
      curlist .tailfield = pret ;
    } 
    {
      mem [curlist .tailfield ].hh .v.RH = newpenalty ( eqtb [29286 ].cint 
      ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    if ( g2 > 0 ) 
    {
      mem [curlist .tailfield ].hh .v.RH = newparamglue ( g2 ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    flushnodelist ( j ) ;
    resumeafterdisplay () ;
  } 
} 
void 
resumeafterdisplay ( void ) 
{
  resumeafterdisplay_regmem 
  if ( curgroup != 15 ) 
  confusion ( 1578 ) ;
  unsave () ;
  curlist .pgfield = curlist .pgfield + 3 ;
  pushnest () ;
  curlist .modefield = 104 ;
  curlist .auxfield .hh .v.LH = 1000 ;
  if ( eqtb [29324 ].cint <= 0 ) 
  curlang = 0 ;
  else if ( eqtb [29324 ].cint > 255 ) 
  curlang = 0 ;
  else curlang = eqtb [29324 ].cint ;
  curlist .auxfield .hh .v.RH = curlang ;
  curlist .pgfield = ( normmin ( eqtb [29325 ].cint ) * 64 + normmin ( eqtb 
  [29326 ].cint ) ) * 65536L + curlang ;
  {
    getxtoken () ;
    if ( curcmd != 10 ) 
    backinput () ;
  } 
  if ( nestptr == 1 ) 
  buildpage () ;
} 
void 
getrtoken ( void ) 
{
  /* 20 */ getrtoken_regmem 
  lab20: do {
      gettoken () ;
  } while ( ! ( curtok != 2592 ) ) ;
  if ( ( curcs == 0 ) || ( curcs > eqtbtop ) || ( ( curcs > 15514 ) && ( curcs 
  <= 30176 ) ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 1596 ) ;
    } 
    {
      helpptr = 5 ;
      helpline [4 ]= 1597 ;
      helpline [3 ]= 1598 ;
      helpline [2 ]= 1599 ;
      helpline [1 ]= 1600 ;
      helpline [0 ]= 1601 ;
    } 
    if ( curcs == 0 ) 
    backinput () ;
    curtok = 19609 ;
    inserror () ;
    goto lab20 ;
  } 
} 
void 
trapzeroglue ( void ) 
{
  trapzeroglue_regmem 
  if ( ( mem [curval + 1 ].cint == 0 ) && ( mem [curval + 2 ].cint == 0 ) 
  && ( mem [curval + 3 ].cint == 0 ) ) 
  {
    incr ( mem [membot ].hh .v.RH ) ;
    deleteglueref ( curval ) ;
    curval = membot ;
  } 
} 
void 
zdoregistercommand ( smallnumber a ) 
{
  /* 40 10 */ doregistercommand_regmem 
  halfword l, q, r, s  ;
  unsigned char p  ;
  boolean e  ;
  integer w  ;
  q = curcmd ;
  e = false ;
  {
    if ( q != 89 ) 
    {
      getxtoken () ;
      if ( ( curcmd >= 73 ) && ( curcmd <= 76 ) ) 
      {
	l = curchr ;
	p = curcmd - 73 ;
	goto lab40 ;
      } 
      if ( curcmd != 89 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 781 ) ;
	} 
	printcmdchr ( curcmd , curchr ) ;
	print ( 782 ) ;
	printcmdchr ( q , 0 ) ;
	{
	  helpptr = 1 ;
	  helpline [0 ]= 1625 ;
	} 
	error () ;
	return ;
      } 
    } 
    if ( ( curchr < membot ) || ( curchr > membot + 19 ) ) 
    {
      l = curchr ;
      p = ( mem [l ].hh.b0 / 16 ) ;
      e = true ;
    } 
    else {
	
      p = curchr - membot ;
      scanregisternum () ;
      if ( curval > 255 ) 
      {
	findsaelement ( p , curval , true ) ;
	l = curptr ;
	e = true ;
      } 
      else switch ( p ) 
      {case 0 : 
	l = curval + 29375 ;
	break ;
      case 1 : 
	l = curval + 29921 ;
	break ;
      case 2 : 
	l = curval + 26646 ;
	break ;
      case 3 : 
	l = curval + 26902 ;
	break ;
      } 
    } 
  } 
  lab40: if ( p < 2 ) {
      
    if ( e ) 
    w = mem [l + 2 ].cint ;
    else w = eqtb [l ].cint ;
  } 
  else if ( e ) 
  s = mem [l + 1 ].hh .v.RH ;
  else s = eqtb [l ].hh .v.RH ;
  if ( q == 89 ) 
  scanoptionalequals () ;
  else if ( scankeyword ( 1621 ) ) 
  ;
  aritherror = false ;
  if ( q < 91 ) {
      
    if ( p < 2 ) 
    {
      if ( p == 0 ) 
      scanint () ;
      else scandimen ( false , false , false ) ;
      if ( q == 90 ) 
      curval = curval + w ;
    } 
    else {
	
      scanglue ( p ) ;
      if ( q == 90 ) 
      {
	q = newspec ( curval ) ;
	r = s ;
	deleteglueref ( curval ) ;
	mem [q + 1 ].cint = mem [q + 1 ].cint + mem [r + 1 ].cint ;
	if ( mem [q + 2 ].cint == 0 ) 
	mem [q ].hh.b0 = 0 ;
	if ( mem [q ].hh.b0 == mem [r ].hh.b0 ) 
	mem [q + 2 ].cint = mem [q + 2 ].cint + mem [r + 2 ].cint ;
	else if ( ( mem [q ].hh.b0 < mem [r ].hh.b0 ) && ( mem [r + 2 ]
	.cint != 0 ) ) 
	{
	  mem [q + 2 ].cint = mem [r + 2 ].cint ;
	  mem [q ].hh.b0 = mem [r ].hh.b0 ;
	} 
	if ( mem [q + 3 ].cint == 0 ) 
	mem [q ].hh.b1 = 0 ;
	if ( mem [q ].hh.b1 == mem [r ].hh.b1 ) 
	mem [q + 3 ].cint = mem [q + 3 ].cint + mem [r + 3 ].cint ;
	else if ( ( mem [q ].hh.b1 < mem [r ].hh.b1 ) && ( mem [r + 3 ]
	.cint != 0 ) ) 
	{
	  mem [q + 3 ].cint = mem [r + 3 ].cint ;
	  mem [q ].hh.b1 = mem [r ].hh.b1 ;
	} 
	curval = q ;
      } 
    } 
  } 
  else {
      
    scanint () ;
    if ( p < 2 ) {
	
      if ( q == 91 ) {
	  
	if ( p == 0 ) 
	curval = multandadd ( w , curval , 0 , 2147483647L ) ;
	else curval = multandadd ( w , curval , 0 , 1073741823L ) ;
      } 
      else curval = xovern ( w , curval ) ;
    } 
    else {
	
      r = newspec ( s ) ;
      if ( q == 91 ) 
      {
	mem [r + 1 ].cint = multandadd ( mem [s + 1 ].cint , curval , 0 , 
	1073741823L ) ;
	mem [r + 2 ].cint = multandadd ( mem [s + 2 ].cint , curval , 0 , 
	1073741823L ) ;
	mem [r + 3 ].cint = multandadd ( mem [s + 3 ].cint , curval , 0 , 
	1073741823L ) ;
      } 
      else {
	  
	mem [r + 1 ].cint = xovern ( mem [s + 1 ].cint , curval ) ;
	mem [r + 2 ].cint = xovern ( mem [s + 2 ].cint , curval ) ;
	mem [r + 3 ].cint = xovern ( mem [s + 3 ].cint , curval ) ;
      } 
      curval = r ;
    } 
  } 
  if ( aritherror ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 1622 ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 1623 ;
      helpline [0 ]= 1624 ;
    } 
    if ( p >= 2 ) 
    deleteglueref ( curval ) ;
    error () ;
    return ;
  } 
  if ( p < 2 ) {
      
    if ( e ) {
	
      if ( ( a >= 4 ) ) 
      gsawdef ( l , curval ) ;
      else sawdef ( l , curval ) ;
    } 
    else if ( ( a >= 4 ) ) 
    geqworddefine ( l , curval ) ;
    else eqworddefine ( l , curval ) ;
  } 
  else {
      
    trapzeroglue () ;
    if ( e ) {
	
      if ( ( a >= 4 ) ) 
      gsadef ( l , curval ) ;
      else sadef ( l , curval ) ;
    } 
    else if ( ( a >= 4 ) ) 
    geqdefine ( l , 119 , curval ) ;
    else eqdefine ( l , 119 , curval ) ;
  } 
} 
void 
alteraux ( void ) 
{
  alteraux_regmem 
  halfword c  ;
  if ( curchr != abs ( curlist .modefield ) ) 
  reportillegalcase () ;
  else {
      
    c = curchr ;
    scanoptionalequals () ;
    if ( c == 1 ) 
    {
      scandimen ( false , false , false ) ;
      curlist .auxfield .cint = curval ;
    } 
    else {
	
      scanint () ;
      if ( ( curval <= 0 ) || ( curval > 32767 ) ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 1628 ) ;
	} 
	{
	  helpptr = 1 ;
	  helpline [0 ]= 1629 ;
	} 
	interror ( curval ) ;
      } 
      else curlist .auxfield .hh .v.LH = curval ;
    } 
  } 
} 
void 
alterprevgraf ( void ) 
{
  alterprevgraf_regmem 
  integer p  ;
  nest [nestptr ]= curlist ;
  p = nestptr ;
  while ( abs ( nest [p ].modefield ) != 1 ) decr ( p ) ;
  scanoptionalequals () ;
  scanint () ;
  if ( curval < 0 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 1361 ) ;
    } 
    printesc ( 607 ) ;
    {
      helpptr = 1 ;
      helpline [0 ]= 1630 ;
    } 
    interror ( curval ) ;
  } 
  else {
      
    nest [p ].pgfield = curval ;
    curlist = nest [nestptr ];
  } 
} 
void 
alterpagesofar ( void ) 
{
  alterpagesofar_regmem 
  unsigned char c  ;
  c = curchr ;
  scanoptionalequals () ;
  scandimen ( false , false , false ) ;
  pagesofar [c ]= curval ;
} 
void 
alterinteger ( void ) 
{
  alterinteger_regmem 
  smallnumber c  ;
  c = curchr ;
  scanoptionalequals () ;
  scanint () ;
  if ( c == 0 ) 
  deadcycles = curval ;
  else if ( c == 2 ) 
  {
    if ( ( curval < 0 ) || ( curval > 3 ) ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 1998 ) ;
      } 
      {
	helpptr = 2 ;
	helpline [1 ]= 1999 ;
	helpline [0 ]= 2000 ;
      } 
      interror ( curval ) ;
    } 
    else {
	
      curchr = curval ;
      newinteraction () ;
    } 
  } 
  else insertpenalties = curval ;
} 
void 
alterboxdimen ( void ) 
{
  alterboxdimen_regmem 
  smallnumber c  ;
  halfword b  ;
  c = curchr ;
  scanregisternum () ;
  if ( curval < 256 ) 
  b = eqtb [27433 + curval ].hh .v.RH ;
  else {
      
    findsaelement ( 4 , curval , false ) ;
    if ( curptr == -268435455L ) 
    b = -268435455L ;
    else b = mem [curptr + 1 ].hh .v.RH ;
  } 
  scanoptionalequals () ;
  scandimen ( false , false , false ) ;
  if ( b != -268435455L ) 
  mem [b + c ].cint = curval ;
} 
void 
znewfont ( smallnumber a ) 
{
  /* 50 */ newfont_regmem 
  halfword u  ;
  scaled s  ;
  internalfontnumber f  ;
  strnumber t  ;
  unsigned char oldsetting  ;
  if ( jobname == 0 ) 
  openlogfile () ;
  getrtoken () ;
  u = curcs ;
  if ( u >= 514 ) 
  t = hash [u ].v.RH ;
  else if ( u >= 257 ) {
      
    if ( u == 513 ) 
    t = 1092 ;
    else t = u - 257 ;
  } 
  else {
      
    oldsetting = selector ;
    selector = 21 ;
    print ( 1092 ) ;
    print ( u - 1 ) ;
    selector = oldsetting ;
    {
      if ( poolptr + 1 > poolsize ) 
      overflow ( 259 , poolsize - initpoolptr ) ;
    } 
    t = makestring () ;
  } 
  if ( ( a >= 4 ) ) 
  geqdefine ( u , 87 , 0 ) ;
  else eqdefine ( u , 87 , 0 ) ;
  scanoptionalequals () ;
  scanfilename () ;
  nameinprogress = true ;
  if ( scankeyword ( 1644 ) ) 
  {
    scandimen ( false , false , false ) ;
    s = curval ;
    if ( ( s <= 0 ) || ( s >= 134217728L ) ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 1646 ) ;
      } 
      printscaled ( s ) ;
      print ( 1647 ) ;
      {
	helpptr = 2 ;
	helpline [1 ]= 1648 ;
	helpline [0 ]= 1649 ;
      } 
      error () ;
      s = 10 * 65536L ;
    } 
  } 
  else if ( scankeyword ( 1645 ) ) 
  {
    scanint () ;
    s = - (integer) curval ;
    if ( ( curval <= 0 ) || ( curval > 32768L ) ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 631 ) ;
      } 
      {
	helpptr = 1 ;
	helpline [0 ]= 632 ;
      } 
      interror ( curval ) ;
      s = -1000 ;
    } 
  } 
  else s = -1000 ;
  nameinprogress = false ;
  {register integer for_end; f = 1 ;for_end = fontptr ; if ( f <= for_end) 
  do 
    if ( streqstr ( fontname [f ], curname ) && streqstr ( fontarea [f ], 
    curarea ) ) 
    {
      if ( pdffontstep [f ]== 0 ) 
      {
	if ( s > 0 ) 
	{
	  if ( s == fontsize [f ]) 
	  goto lab50 ;
	} 
	else if ( fontsize [f ]== xnoverd ( fontdsize [f ], - (integer) s 
	, 1000 ) ) 
	goto lab50 ;
      } 
    } 
  while ( f++ < for_end ) ;} 
  f = readfontinfo ( u , curname , curarea , s ) ;
  lab50: if ( ( a >= 4 ) ) 
  geqdefine ( u , 87 , f ) ;
  else eqdefine ( u , 87 , f ) ;
  eqtb [17626 + f ]= eqtb [u ];
  hash [17626 + f ].v.RH = t ;
} 
void 
newinteraction ( void ) 
{
  newinteraction_regmem 
  println () ;
  interaction = curchr ;
  if ( interaction == 0 ) 
  kpsemaketexdiscarderrors = 1 ;
  else kpsemaketexdiscarderrors = 0 ;
  if ( interaction == 0 ) 
  selector = 16 ;
  else selector = 17 ;
  if ( logopened ) 
  selector = selector + 2 ;
} 
void 
doassignments ( void ) 
{
  /* 10 */ doassignments_regmem 
  while ( true ) {
      
    do {
	getxtoken () ;
    } while ( ! ( ( curcmd != 10 ) && ( curcmd != 0 ) ) ) ;
    if ( curcmd <= 70 ) 
    return ;
    setboxallowed = false ;
    prefixedcommand () ;
    setboxallowed = true ;
  } 
} 
void 
openorclosein ( void ) 
{
  openorclosein_regmem 
  unsigned char c  ;
  unsigned char n  ;
  c = curchr ;
  scanfourbitint () ;
  n = curval ;
  if ( readopen [n ]!= 2 ) 
  {
    aclose ( readfile [n ]) ;
    readopen [n ]= 2 ;
  } 
  if ( c != 0 ) 
  {
    scanoptionalequals () ;
    scanfilename () ;
    packfilename ( curname , curarea , curext ) ;
    texinputtype = 0 ;
    if ( kpseinnameok ( stringcast ( nameoffile + 1 ) ) && aopenin ( readfile 
    [n ], kpsetexformat ) ) 
    readopen [n ]= 1 ;
  } 
} 
void 
issuemessage ( void ) 
{
  issuemessage_regmem 
  unsigned char oldsetting  ;
  unsigned char c  ;
  strnumber s  ;
  c = curchr ;
  mem [memtop - 12 ].hh .v.RH = scantoks ( false , true ) ;
  oldsetting = selector ;
  selector = 21 ;
  tokenshow ( defref ) ;
  selector = oldsetting ;
  flushlist ( defref ) ;
  {
    if ( poolptr + 1 > poolsize ) 
    overflow ( 259 , poolsize - initpoolptr ) ;
  } 
  s = makestring () ;
  if ( c == 0 ) 
  {
    if ( termoffset + ( strstart [s + 1 ]- strstart [s ]) > maxprintline - 
    2 ) 
    println () ;
    else if ( ( termoffset > 0 ) || ( fileoffset > 0 ) ) 
    printchar ( 32 ) ;
    slowprint ( s ) ;
    fflush ( stdout ) ;
  } 
  else {
      
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 264 ) ;
      print ( 345 ) ;
    } 
    slowprint ( s ) ;
    if ( eqtb [27167 ].hh .v.RH != -268435455L ) 
    useerrhelp = true ;
    else if ( longhelpseen ) 
    {
      helpptr = 1 ;
      helpline [0 ]= 1656 ;
    } 
    else {
	
      if ( interaction < 3 ) 
      longhelpseen = true ;
      {
	helpptr = 4 ;
	helpline [3 ]= 1657 ;
	helpline [2 ]= 1658 ;
	helpline [1 ]= 1659 ;
	helpline [0 ]= 1660 ;
      } 
    } 
    error () ;
    useerrhelp = false ;
  } 
  {
    decr ( strptr ) ;
    poolptr = strstart [strptr ];
  } 
} 
void 
shiftcase ( void ) 
{
  shiftcase_regmem 
  halfword b  ;
  halfword p  ;
  halfword t  ;
  eightbits c  ;
  b = curchr ;
  p = scantoks ( false , false ) ;
  p = mem [defref ].hh .v.RH ;
  while ( p != -268435455L ) {
      
    t = mem [p ].hh .v.LH ;
    if ( t < 4352 ) 
    {
      c = t % 256 ;
      if ( eqtb [b + c ].hh .v.RH != 0 ) 
      mem [p ].hh .v.LH = t - c + eqtb [b + c ].hh .v.RH ;
    } 
    p = mem [p ].hh .v.RH ;
  } 
  begintokenlist ( mem [defref ].hh .v.RH , 3 ) ;
  {
    mem [defref ].hh .v.RH = avail ;
    avail = defref ;
	;
#ifdef STAT
    decr ( dynused ) ;
#endif /* STAT */
  } 
} 
void 
showwhatever ( void ) 
{
  /* 50 */ showwhatever_regmem 
  halfword p  ;
  smallnumber t  ;
  unsigned char m  ;
  integer l  ;
  integer n  ;
  switch ( curchr ) 
  {case 3 : 
    {
      begindiagnostic () ;
      showactivities () ;
    } 
    break ;
  case 1 : 
    {
      scanregisternum () ;
      if ( curval < 256 ) 
      p = eqtb [27433 + curval ].hh .v.RH ;
      else {
	  
	findsaelement ( 4 , curval , false ) ;
	if ( curptr == -268435455L ) 
	p = -268435455L ;
	else p = mem [curptr + 1 ].hh .v.RH ;
      } 
      begindiagnostic () ;
      printnl ( 1676 ) ;
      printint ( curval ) ;
      printchar ( 61 ) ;
      if ( p == -268435455L ) 
      print ( 430 ) ;
      else showbox ( p ) ;
    } 
    break ;
  case 0 : 
    {
      gettoken () ;
      if ( interaction == 3 ) 
      ;
      printnl ( 1672 ) ;
      if ( curcs != 0 ) 
      {
	sprintcs ( curcs ) ;
	printchar ( 61 ) ;
      } 
      printmeaning () ;
      goto lab50 ;
    } 
    break ;
  case 4 : 
    {
      begindiagnostic () ;
      showsavegroups () ;
    } 
    break ;
  case 6 : 
    {
      begindiagnostic () ;
      printnl ( 345 ) ;
      println () ;
      if ( condptr == -268435455L ) 
      {
	printnl ( 379 ) ;
	print ( 1995 ) ;
      } 
      else {
	  
	p = condptr ;
	n = 0 ;
	do {
	    incr ( n ) ;
	  p = mem [p ].hh .v.RH ;
	} while ( ! ( p == -268435455L ) ) ;
	p = condptr ;
	t = curif ;
	l = ifline ;
	m = iflimit ;
	do {
	    printnl ( 1996 ) ;
	  printint ( n ) ;
	  print ( 646 ) ;
	  printcmdchr ( 107 , t ) ;
	  if ( m == 2 ) 
	  printesc ( 926 ) ;
	  if ( l != 0 ) 
	  {
	    print ( 1994 ) ;
	    printint ( l ) ;
	  } 
	  decr ( n ) ;
	  t = mem [p ].hh.b1 ;
	  l = mem [p + 1 ].cint ;
	  m = mem [p ].hh.b0 ;
	  p = mem [p ].hh .v.RH ;
	} while ( ! ( p == -268435455L ) ) ;
      } 
    } 
    break ;
    default: 
    {
      p = thetoks () ;
      if ( interaction == 3 ) 
      ;
      printnl ( 1672 ) ;
      tokenshow ( memtop - 3 ) ;
      flushlist ( mem [memtop - 3 ].hh .v.RH ) ;
      goto lab50 ;
    } 
    break ;
  } 
  enddiagnostic ( true ) ;
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 264 ) ;
    print ( 1677 ) ;
  } 
  if ( selector == 19 ) {
      
    if ( eqtb [29303 ].cint <= 0 ) 
    {
      selector = 17 ;
      print ( 1678 ) ;
      selector = 19 ;
    } 
  } 
  lab50: if ( interaction < 3 ) 
  {
    helpptr = 0 ;
    decr ( errorcount ) ;
  } 
  else if ( eqtb [29303 ].cint > 0 ) 
  {
    {
      helpptr = 3 ;
      helpline [2 ]= 1667 ;
      helpline [1 ]= 1668 ;
      helpline [0 ]= 1669 ;
    } 
  } 
  else {
      
    {
      helpptr = 5 ;
      helpline [4 ]= 1667 ;
      helpline [3 ]= 1668 ;
      helpline [2 ]= 1669 ;
      helpline [1 ]= 1670 ;
      helpline [0 ]= 1671 ;
    } 
  } 
  error () ;
} 
void 
znewwhatsit ( smallnumber s , smallnumber w ) 
{
  newwhatsit_regmem 
  halfword p  ;
  p = getnode ( w ) ;
  mem [p ].hh.b0 = 8 ;
  mem [p ].hh.b1 = s ;
  mem [curlist .tailfield ].hh .v.RH = p ;
  curlist .tailfield = p ;
} 
void 
znewwritewhatsit ( smallnumber w ) 
{
  newwritewhatsit_regmem 
  newwhatsit ( curchr , w ) ;
  if ( w != 2 ) 
  scanfourbitint () ;
  else {
      
    scanint () ;
    if ( curval < 0 ) 
    curval = 17 ;
    else if ( ( curval > 15 ) && ( curval != 18 ) ) 
    curval = 16 ;
  } 
  mem [curlist .tailfield + 1 ].hh .v.LH = curval ;
} 
void 
zcheckpdfoutput ( strnumber s , boolean iserror ) 
{
  checkpdfoutput_regmem 
  if ( eqtb [29332 ].cint <= 0 ) 
  {
    if ( iserror ) 
    pdferror ( s , 1759 ) ;
    else pdfwarning ( s , 1760 , true , true ) ;
  } 
} 
void 
scanpdfexttoks ( void ) 
{
  scanpdfexttoks_regmem 
  {
    if ( scantoks ( false , true ) != 0 ) 
    ;
  } 
} 
void 
comparestrings ( void ) 
{
  /* 30 */ comparestrings_regmem 
  strnumber s1, s2  ;
  poolpointer i1, i2, j1, j2  ;
  halfword savecurcs  ;
  savecurcs = curcs ;
  {
    if ( scantoks ( false , true ) != 0 ) 
    ;
  } 
  s1 = tokenstostring ( defref ) ;
  deletetokenref ( defref ) ;
  curcs = savecurcs ;
  {
    if ( scantoks ( false , true ) != 0 ) 
    ;
  } 
  s2 = tokenstostring ( defref ) ;
  deletetokenref ( defref ) ;
  i1 = strstart [s1 ];
  j1 = strstart [s1 + 1 ];
  i2 = strstart [s2 ];
  j2 = strstart [s2 + 1 ];
  while ( ( i1 < j1 ) && ( i2 < j2 ) ) {
      
    if ( strpool [i1 ]< strpool [i2 ]) 
    {
      curval = -1 ;
      goto lab30 ;
    } 
    if ( strpool [i1 ]> strpool [i2 ]) 
    {
      curval = 1 ;
      goto lab30 ;
    } 
    incr ( i1 ) ;
    incr ( i2 ) ;
  } 
  if ( ( i1 == j1 ) && ( i2 == j2 ) ) 
  curval = 0 ;
  else if ( i1 < j1 ) 
  curval = 1 ;
  else curval = -1 ;
  lab30: flushstr ( s2 ) ;
  flushstr ( s1 ) ;
  curvallevel = 0 ;
} 
void 
zscaleimage ( integer n ) 
{
  scaleimage_regmem 
  integer x, y, xr, yr  ;
  scaled w, h  ;
  integer defaultres  ;
  integer image  ;
  image = pdfmem [objtab [n ].int4 + 4 ];
  if ( ( imagerotate ( image ) == 90 ) || ( imagerotate ( image ) == 270 ) ) 
  {
    y = imagewidth ( image ) ;
    x = imageheight ( image ) ;
    yr = imagexres ( image ) ;
    xr = imageyres ( image ) ;
  } 
  else {
      
    x = imagewidth ( image ) ;
    y = imageheight ( image ) ;
    xr = imagexres ( image ) ;
    yr = imageyres ( image ) ;
  } 
  if ( ( xr > 65535L ) || ( yr > 65535L ) ) 
  {
    xr = 0 ;
    yr = 0 ;
    pdfwarning ( 1758 , 1790 , true , true ) ;
  } 
  if ( ( x <= 0 ) || ( y <= 0 ) || ( xr < 0 ) || ( yr < 0 ) ) 
  pdferror ( 1758 , 1791 ) ;
  if ( ispdfimage ( image ) ) 
  {
    w = x ;
    h = y ;
  } 
  else {
      
    defaultres = fixint ( eqtb [29336 ].cint , 0 , 65535L ) ;
    if ( ( defaultres > 0 ) && ( ( xr == 0 ) || ( yr == 0 ) ) ) 
    {
      xr = defaultres ;
      yr = defaultres ;
    } 
    if ( ( pdfmem [objtab [n ].int4 + 0 ]== -1073741824L ) && ( pdfmem [
    objtab [n ].int4 + 1 ]== -1073741824L ) ) 
    {
      if ( ( xr > 0 ) && ( yr > 0 ) ) 
      {
	w = extxnoverd ( onehundredinch , x , 100 * xr ) ;
	h = extxnoverd ( onehundredinch , y , 100 * yr ) ;
      } 
      else {
	  
	w = extxnoverd ( onehundredinch , x , 7200 ) ;
	h = extxnoverd ( onehundredinch , y , 7200 ) ;
      } 
    } 
  } 
  if ( ( pdfmem [objtab [n ].int4 + 0 ]== -1073741824L ) && ( pdfmem [
  objtab [n ].int4 + 1 ]== -1073741824L ) && ( pdfmem [objtab [n ].int4 
  + 2 ]== -1073741824L ) ) 
  {
    pdfmem [objtab [n ].int4 + 0 ]= w ;
    pdfmem [objtab [n ].int4 + 1 ]= h ;
    pdfmem [objtab [n ].int4 + 2 ]= 0 ;
  } 
  else if ( ( pdfmem [objtab [n ].int4 + 0 ]== -1073741824L ) ) 
  {
    if ( ( pdfmem [objtab [n ].int4 + 1 ]== -1073741824L ) ) 
    {
      pdfmem [objtab [n ].int4 + 0 ]= extxnoverd ( h , x , y ) ;
      pdfmem [objtab [n ].int4 + 1 ]= h - pdfmem [objtab [n ].int4 + 2 
      ];
    } 
    else if ( ( pdfmem [objtab [n ].int4 + 2 ]== -1073741824L ) ) 
    {
      pdfmem [objtab [n ].int4 + 0 ]= extxnoverd ( pdfmem [objtab [n ]
      .int4 + 1 ], x , y ) ;
      pdfmem [objtab [n ].int4 + 2 ]= 0 ;
    } 
    else {
	
      pdfmem [objtab [n ].int4 + 0 ]= extxnoverd ( pdfmem [objtab [n ]
      .int4 + 1 ]+ pdfmem [objtab [n ].int4 + 2 ], x , y ) ;
    } 
  } 
  else {
      
    if ( ( pdfmem [objtab [n ].int4 + 1 ]== -1073741824L ) && ( pdfmem [
    objtab [n ].int4 + 2 ]== -1073741824L ) ) 
    {
      pdfmem [objtab [n ].int4 + 1 ]= extxnoverd ( pdfmem [objtab [n ]
      .int4 + 0 ], y , x ) ;
      pdfmem [objtab [n ].int4 + 2 ]= 0 ;
    } 
    else if ( ( pdfmem [objtab [n ].int4 + 1 ]== -1073741824L ) ) 
    {
      pdfmem [objtab [n ].int4 + 1 ]= extxnoverd ( pdfmem [objtab [n ]
      .int4 + 0 ], y , x ) - pdfmem [objtab [n ].int4 + 2 ];
    } 
    else if ( ( pdfmem [objtab [n ].int4 + 2 ]== -1073741824L ) ) 
    {
      pdfmem [objtab [n ].int4 + 2 ]= 0 ;
    } 
    else ;
  } 
} 
integer 
scanpdfboxspec ( void ) 
{
  register integer Result; scanpdfboxspec_regmem 
  Result = 0 ;
  if ( scankeyword ( 1792 ) ) 
  Result = pdfboxspecmedia ;
  else if ( scankeyword ( 1793 ) ) 
  Result = pdfboxspeccrop ;
  else if ( scankeyword ( 1794 ) ) 
  Result = pdfboxspecbleed ;
  else if ( scankeyword ( 1795 ) ) 
  Result = pdfboxspectrim ;
  else if ( scankeyword ( 1796 ) ) 
  Result = pdfboxspecart ;
  return Result ;
} 
void 
scanaltrule ( void ) 
{
  /* 21 */ scanaltrule_regmem 
  if ( altrule == -268435455L ) 
  altrule = newrule () ;
  mem [altrule + 1 ].cint = -1073741824L ;
  mem [altrule + 3 ].cint = -1073741824L ;
  mem [altrule + 2 ].cint = -1073741824L ;
  lab21: if ( scankeyword ( 831 ) ) 
  {
    scandimen ( false , false , false ) ;
    mem [altrule + 1 ].cint = curval ;
    goto lab21 ;
  } 
  if ( scankeyword ( 832 ) ) 
  {
    scandimen ( false , false , false ) ;
    mem [altrule + 3 ].cint = curval ;
    goto lab21 ;
  } 
  if ( scankeyword ( 833 ) ) 
  {
    scandimen ( false , false , false ) ;
    mem [altrule + 2 ].cint = curval ;
    goto lab21 ;
  } 
} 
void 
scanimage ( void ) 
{
  /* 21 */ scanimage_regmem 
  integer k  ;
  strnumber named  ;
  strnumber s  ;
  integer page, pagebox, colorspace  ;
  incr ( pdfximagecount ) ;
  pdfcreateobj ( 8 , pdfximagecount ) ;
  k = objptr ;
  objtab [k ].int4 = pdfgetmem ( 5 ) ;
  scanaltrule () ;
  pdfmem [objtab [k ].int4 + 0 ]= mem [altrule + 1 ].cint ;
  pdfmem [objtab [k ].int4 + 1 ]= mem [altrule + 3 ].cint ;
  pdfmem [objtab [k ].int4 + 2 ]= mem [altrule + 2 ].cint ;
  if ( scankeyword ( 1783 ) ) 
  {
    scanpdfexttoks () ;
    pdfmem [objtab [k ].int4 + 3 ]= defref ;
  } 
  else pdfmem [objtab [k ].int4 + 3 ]= -268435455L ;
  named = 0 ;
  if ( scankeyword ( 1797 ) ) 
  {
    scanpdfexttoks () ;
    named = tokenstostring ( defref ) ;
    deletetokenref ( defref ) ;
  } 
  else if ( scankeyword ( 884 ) ) 
  {
    scanint () ;
    page = curval ;
  } 
  else page = 1 ;
  if ( scankeyword ( 1798 ) ) 
  {
    scanint () ;
    colorspace = curval ;
  } 
  else colorspace = 0 ;
  pagebox = scanpdfboxspec () ;
  if ( pagebox == 0 ) 
  pagebox = eqtb [29343 ].cint ;
  scanpdfexttoks () ;
  s = tokenstostring ( defref ) ;
  deletetokenref ( defref ) ;
  if ( eqtb [29339 ].cint != 0 ) 
  {
    pdfwarning ( 1799 , 1800 , true , true ) ;
    eqtb [29342 ].cint = eqtb [29339 ].cint ;
    eqtb [29339 ].cint = 0 ;
    warnpdfpagebox = false ;
  } 
  if ( eqtb [29340 ].cint != 0 ) 
  {
    pdfwarning ( 1799 , 1801 , true , true ) ;
    eqtb [29344 ].cint = eqtb [29340 ].cint ;
    eqtb [29340 ].cint = 0 ;
  } 
  if ( eqtb [29342 ].cint > 0 ) 
  {
    if ( warnpdfpagebox ) 
    {
      pdfwarning ( 1799 , 1802 , true , true ) ;
      warnpdfpagebox = false ;
    } 
    pagebox = eqtb [29342 ].cint ;
  } 
  if ( pagebox == 0 ) 
  pagebox = pdfboxspeccrop ;
  pdfmem [objtab [k ].int4 + 4 ]= readimage ( s , page , named , 
  colorspace , pagebox , eqtb [29341 ].cint , eqtb [29344 ].cint ) ;
  if ( named != 0 ) 
  flushstr ( named ) ;
  flushstr ( s ) ;
  scaleimage ( k ) ;
  pdflastximage = k ;
  pdflastximagepages = imagepages ( pdfmem [objtab [k ].int4 + 4 ]) ;
  pdflastximagecolordepth = imagecolordepth ( pdfmem [objtab [k ].int4 + 4 
  ]) ;
} 
halfword 
scanaction ( void ) 
{
  register halfword Result; scanaction_regmem 
  integer p  ;
  p = getnode ( 3 ) ;
  Result = p ;
  mem [p + 1 ].hh .v.LH = -268435455L ;
  mem [p + 2 ].hh .v.RH = -268435455L ;
  if ( scankeyword ( 1805 ) ) 
  mem [p ].hh.b0 = 3 ;
  else if ( scankeyword ( 1806 ) ) 
  mem [p ].hh.b0 = 1 ;
  else if ( scankeyword ( 1807 ) ) 
  mem [p ].hh.b0 = 2 ;
  else pdferror ( 1758 , 1808 ) ;
  if ( mem [p ].hh.b0 == 3 ) 
  {
    scanpdfexttoks () ;
    mem [p + 2 ].hh .v.LH = defref ;
    return Result ;
  } 
  if ( scankeyword ( 873 ) ) 
  {
    scanpdfexttoks () ;
    mem [p + 1 ].hh .v.LH = defref ;
  } 
  if ( scankeyword ( 884 ) ) 
  {
    if ( mem [p ].hh.b0 != 1 ) 
    pdferror ( 1758 , 1809 ) ;
    mem [p ].hh.b0 = 0 ;
    scanint () ;
    if ( curval <= 0 ) 
    pdferror ( 1758 , 1810 ) ;
    mem [p ].hh .v.RH = curval ;
    mem [p ].hh.b1 = 0 ;
    scanpdfexttoks () ;
    mem [p + 2 ].hh .v.LH = defref ;
  } 
  else if ( scankeyword ( 1811 ) ) 
  {
    scanpdfexttoks () ;
    mem [p ].hh.b1 = 1 ;
    mem [p ].hh .v.RH = defref ;
  } 
  else if ( scankeyword ( 1190 ) ) 
  {
    if ( ( mem [p ].hh.b0 == 1 ) && ( mem [p + 1 ].hh .v.LH != -268435455L 
    ) ) 
    pdferror ( 1758 , 1812 ) ;
    scanint () ;
    if ( curval <= 0 ) 
    pdferror ( 1758 , 1813 ) ;
    mem [p ].hh.b1 = 0 ;
    mem [p ].hh .v.RH = curval ;
  } 
  else pdferror ( 1758 , 1814 ) ;
  if ( scankeyword ( 1815 ) ) 
  {
    mem [p + 1 ].hh .v.RH = 1 ;
    {
      getxtoken () ;
      if ( curcmd != 10 ) 
      backinput () ;
    } 
  } 
  else if ( scankeyword ( 1816 ) ) 
  {
    mem [p + 1 ].hh .v.RH = 2 ;
    {
      getxtoken () ;
      if ( curcmd != 10 ) 
      backinput () ;
    } 
  } 
  else mem [p + 1 ].hh .v.RH = 0 ;
  if ( ( mem [p + 1 ].hh .v.RH > 0 ) && ( ( ( mem [p ].hh.b0 != 1 ) && ( 
  mem [p ].hh.b0 != 0 ) ) || ( mem [p + 1 ].hh .v.LH == -268435455L ) ) ) 
  pdferror ( 1758 , 1817 ) ;
  return Result ;
} 
void 
znewannotwhatsit ( smallnumber w , smallnumber s ) 
{
  newannotwhatsit_regmem 
  newwhatsit ( w , s ) ;
  scanaltrule () ;
  mem [curlist .tailfield + 1 ].cint = mem [altrule + 1 ].cint ;
  mem [curlist .tailfield + 2 ].cint = mem [altrule + 3 ].cint ;
  mem [curlist .tailfield + 3 ].cint = mem [altrule + 2 ].cint ;
  if ( ( w == 14 ) ) 
  {
    if ( scankeyword ( 1783 ) ) 
    {
      scanpdfexttoks () ;
      mem [curlist .tailfield + 5 ].hh .v.LH = defref ;
    } 
    else mem [curlist .tailfield + 5 ].hh .v.LH = -268435455L ;
  } 
  if ( ( w == 18 ) || ( w == 19 ) ) 
  {
    if ( scankeyword ( 1783 ) ) 
    {
      scanpdfexttoks () ;
      mem [curlist .tailfield + 6 ].hh .v.LH = defref ;
    } 
    else mem [curlist .tailfield + 6 ].hh .v.LH = -268435455L ;
  } 
} 
integer 
zoutlinelistcount ( halfword p ) 
{
  register integer Result; outlinelistcount_regmem 
  integer k  ;
  k = 1 ;
  while ( pdfmem [objtab [p ].int4 + 2 ]!= 0 ) {
      
    incr ( k ) ;
    p = pdfmem [objtab [p ].int4 + 2 ];
  } 
  Result = k ;
  return Result ;
} 
void 
scanthreadid ( void ) 
{
  scanthreadid_regmem 
  if ( scankeyword ( 1190 ) ) 
  {
    scanint () ;
    if ( curval <= 0 ) 
    pdferror ( 1758 , 1813 ) ;
    if ( curval > 268435455L ) 
    pdferror ( 1758 , 1023 ) ;
    mem [curlist .tailfield + 5 ].hh .v.RH = curval ;
    mem [curlist .tailfield + 5 ].hh.b1 = 0 ;
  } 
  else if ( scankeyword ( 1811 ) ) 
  {
    scanpdfexttoks () ;
    mem [curlist .tailfield + 5 ].hh .v.RH = defref ;
    mem [curlist .tailfield + 5 ].hh.b1 = 1 ;
  } 
  else pdferror ( 1758 , 1814 ) ;
} 
halfword 
znewsnapnode ( smallnumber s ) 
{
  register halfword Result; newsnapnode_regmem 
  halfword p  ;
  scanglue ( 2 ) ;
  if ( mem [curval + 1 ].cint < 0 ) 
  pdferror ( 1758 , 1844 ) ;
  p = getnode ( 3 ) ;
  mem [p ].hh.b0 = 8 ;
  mem [p ].hh.b1 = s ;
  mem [p ].hh .v.RH = -268435455L ;
  mem [p + 1 ].hh .v.LH = curval ;
  mem [p + 2 ].cint = 0 ;
  Result = p ;
  return Result ;
} 
halfword 
zconcattokens ( halfword q , halfword r ) 
{
  register halfword Result; concattokens_regmem 
  halfword p  ;
  if ( q == -268435455L ) 
  {
    Result = r ;
    return Result ;
  } 
  p = q ;
  while ( mem [p ].hh .v.RH != -268435455L ) p = mem [p ].hh .v.RH ;
  mem [p ].hh .v.RH = mem [r ].hh .v.RH ;
  {
    mem [r ].hh .v.RH = avail ;
    avail = r ;
	;
#ifdef STAT
    decr ( dynused ) ;
#endif /* STAT */
  } 
  Result = q ;
  return Result ;
} 
void 
pdfincludechars ( void ) 
{
  pdfincludechars_regmem 
  strnumber s  ;
  poolpointer k  ;
  internalfontnumber f  ;
  scanfontident () ;
  f = curval ;
  if ( f == 0 ) 
  pdferror ( 590 , 868 ) ;
  pdfcheckvfcurval () ;
  if ( ! fontused [f ]) 
  pdfinitfont ( f ) ;
  scanpdfexttoks () ;
  s = tokenstostring ( defref ) ;
  deletetokenref ( defref ) ;
  k = strstart [s ];
  while ( k < strstart [s + 1 ]) {
      
    pdfmarkchar ( f , strpool [k ]) ;
    incr ( k ) ;
  } 
  flushstr ( s ) ;
} 
void 
glyphtounicode ( void ) 
{
  glyphtounicode_regmem 
  strnumber s1, s2  ;
  scanpdfexttoks () ;
  s1 = tokenstostring ( defref ) ;
  deletetokenref ( defref ) ;
  scanpdfexttoks () ;
  s2 = tokenstostring ( defref ) ;
  deletetokenref ( defref ) ;
  deftounicode ( s1 , s2 ) ;
  flushstr ( s2 ) ;
  flushstr ( s1 ) ;
} 
void 
zthreadtitle ( integer thread ) 
{
  threadtitle_regmem 
  pdfprint ( 1861 ) ;
  if ( objtab [thread ].int0 < 0 ) 
  pdfprint ( - (integer) objtab [thread ].int0 ) ;
  else pdfprintint ( objtab [thread ].int0 ) ;
  {
    pdfprint ( 41 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
} 
void 
zpdffixthread ( integer thread ) 
{
  pdffixthread_regmem 
  halfword a  ;
  pdfwarning ( 1807 , 1862 , false , false ) ;
  if ( objtab [thread ].int0 < 0 ) 
  {
    print ( 1189 ) ;
    print ( - (integer) objtab [thread ].int0 ) ;
    print ( 125 ) ;
  } 
  else {
      
    print ( 1190 ) ;
    printint ( objtab [thread ].int0 ) ;
  } 
  print ( 1191 ) ;
  println () ;
  println () ;
  pdfnewdict ( 0 , 0 , 0 ) ;
  a = objptr ;
  pdfindirectln ( 84 , thread ) ;
  pdfindirectln ( 86 , a ) ;
  pdfindirectln ( 78 , a ) ;
  pdfindirectln ( 80 , headtab [1 ]) ;
  pdfprint ( 1863 ) ;
  pdfprintbp ( eqtb [29910 ].cint ) ;
  {
    {
      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfosgetosbuf ( 1 ) ;
      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
      overflow ( 999 , pdfopbufsize ) ;
      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
      pdfflush () ;
    } 
    {
      pdfbuf [pdfptr ]= 32 ;
      incr ( pdfptr ) ;
    } 
  } 
  pdfprintbp ( eqtb [29911 ].cint ) ;
  {
    pdfprint ( 93 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
  pdfenddict () ;
  pdfbegindict ( thread , 1 ) ;
  {
    pdfprint ( 1864 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
  threadtitle ( thread ) ;
  {
    pdfprint ( 1013 ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
  pdfindirectln ( 70 , a ) ;
  pdfenddict () ;
} 
void 
zoutthread ( integer thread ) 
{
  outthread_regmem 
  halfword a, b  ;
  integer lastattr  ;
  if ( objtab [thread ].int4 == 0 ) 
  {
    pdffixthread ( thread ) ;
    return ;
  } 
  pdfbegindict ( thread , 1 ) ;
  a = objtab [thread ].int4 ;
  b = a ;
  lastattr = 0 ;
  do {
      if ( pdfmem [objtab [a ].int4 + 4 ]!= 0 ) 
    lastattr = pdfmem [objtab [a ].int4 + 4 ];
    a = pdfmem [objtab [a ].int4 + 2 ];
  } while ( ! ( a == b ) ) ;
  if ( lastattr != 0 ) 
  {
    pdfprint ( lastattr ) ;
    {
      {
	if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfosgetosbuf ( 1 ) ;
	else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	overflow ( 999 , pdfopbufsize ) ;
	else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	pdfflush () ;
      } 
      {
	pdfbuf [pdfptr ]= 10 ;
	incr ( pdfptr ) ;
      } 
    } 
  } 
  else {
      
    {
      pdfprint ( 1864 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
    threadtitle ( thread ) ;
    {
      pdfprint ( 1013 ) ;
      {
	{
	  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfosgetosbuf ( 1 ) ;
	  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
	  overflow ( 999 , pdfopbufsize ) ;
	  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
	  pdfflush () ;
	} 
	{
	  pdfbuf [pdfptr ]= 10 ;
	  incr ( pdfptr ) ;
	} 
      } 
    } 
  } 
  pdfindirectln ( 70 , a ) ;
  pdfenddict () ;
  do {
      pdfbegindict ( a , 1 ) ;
    if ( a == b ) 
    pdfindirectln ( 84 , thread ) ;
    pdfindirectln ( 86 , pdfmem [objtab [a ].int4 + 3 ]) ;
    pdfindirectln ( 78 , pdfmem [objtab [a ].int4 + 2 ]) ;
    pdfindirectln ( 80 , pdfmem [objtab [a ].int4 + 1 ]) ;
    pdfindirectln ( 82 , pdfmem [objtab [a ].int4 ]) ;
    pdfenddict () ;
    a = pdfmem [objtab [a ].int4 + 2 ];
  } while ( ! ( a == b ) ) ;
} 
void 
doextension ( void ) 
{
  doextension_regmem 
  integer i, j, k  ;
  halfword p, q, r  ;
  switch ( curchr ) 
  {case 0 : 
    {
      newwritewhatsit ( 3 ) ;
      scanoptionalequals () ;
      scanfilename () ;
      mem [curlist .tailfield + 1 ].hh .v.RH = curname ;
      mem [curlist .tailfield + 2 ].hh .v.LH = curarea ;
      mem [curlist .tailfield + 2 ].hh .v.RH = curext ;
    } 
    break ;
  case 1 : 
    {
      k = curcs ;
      newwritewhatsit ( 2 ) ;
      curcs = k ;
      p = scantoks ( false , false ) ;
      mem [curlist .tailfield + 1 ].hh .v.RH = defref ;
    } 
    break ;
  case 2 : 
    {
      newwritewhatsit ( 2 ) ;
      mem [curlist .tailfield + 1 ].hh .v.RH = -268435455L ;
    } 
    break ;
  case 3 : 
    {
      newwhatsit ( 3 , 2 ) ;
      mem [curlist .tailfield + 1 ].hh .v.LH = -268435455L ;
      p = scantoks ( false , true ) ;
      mem [curlist .tailfield + 1 ].hh .v.RH = defref ;
    } 
    break ;
  case 4 : 
    {
      getxtoken () ;
      if ( curcmd == 59 ) 
      {
	if ( curchr <= 2 ) 
	{
	  p = curlist .tailfield ;
	  doextension () ;
	  outwhat ( curlist .tailfield ) ;
	  flushnodelist ( curlist .tailfield ) ;
	  curlist .tailfield = p ;
	  mem [p ].hh .v.RH = -268435455L ;
	} 
	else switch ( curchr ) 
	{case 7 : 
	  {
	    doextension () ;
	    if ( objtab [pdflastobj ].int4 == 0 ) 
	    pdferror ( 1758 , 1906 ) ;
	    pdfwriteobj ( pdflastobj ) ;
	  } 
	  break ;
	case 9 : 
	  {
	    doextension () ;
	    pdfcurform = pdflastxform ;
	    pdfshipout ( pdfmem [objtab [pdflastxform ].int4 + 3 ], false 
	    ) ;
	  } 
	  break ;
	case 11 : 
	  {
	    doextension () ;
	    pdfwriteimage ( pdflastximage ) ;
	  } 
	  break ;
	  default: 
	  backinput () ;
	  break ;
	} 
      } 
      else backinput () ;
    } 
    break ;
  case 5 : 
    if ( abs ( curlist .modefield ) != 104 ) 
    reportillegalcase () ;
    else {
	
      newwhatsit ( 4 , 2 ) ;
      scanint () ;
      if ( curval <= 0 ) 
      curlist .auxfield .hh .v.RH = 0 ;
      else if ( curval > 255 ) 
      curlist .auxfield .hh .v.RH = 0 ;
      else curlist .auxfield .hh .v.RH = curval ;
      mem [curlist .tailfield + 1 ].hh .v.RH = curlist .auxfield .hh .v.RH ;
      mem [curlist .tailfield + 1 ].hh.b0 = normmin ( eqtb [29325 ].cint ) 
      ;
      mem [curlist .tailfield + 1 ].hh.b1 = normmin ( eqtb [29326 ].cint ) 
      ;
    } 
    break ;
  case 13 : 
    {
      checkpdfoutput ( 1818 , true ) ;
      if ( scankeyword ( 1780 ) ) 
      {
	pdflastannot = pdfnewobjnum () ;
	{
	  getxtoken () ;
	  if ( curcmd != 10 ) 
	  backinput () ;
	} 
      } 
      else {
	  
	if ( scankeyword ( 1781 ) ) 
	{
	  scanint () ;
	  k = curval ;
	  if ( ( k <= 0 ) || ( k > objptr ) || ( objtab [k ].int4 != 0 ) ) 
	  pdferror ( 1758 , 1819 ) ;
	} 
	else k = pdfnewobjnum () ;
	newannotwhatsit ( 13 , 7 ) ;
	mem [curlist .tailfield + 6 ].cint = k ;
	scanpdfexttoks () ;
	mem [curlist .tailfield + 5 ].hh .v.LH = defref ;
	pdflastannot = k ;
      } 
    } 
    break ;
  case 23 : 
    {
      checkpdfoutput ( 1848 , false ) ;
      scanpdfexttoks () ;
      if ( eqtb [29332 ].cint > 0 ) 
      pdfcatalogtoks = concattokens ( pdfcatalogtoks , defref ) ;
      if ( scankeyword ( 1849 ) ) 
      {
	if ( pdfcatalogopenaction != 0 ) 
	pdferror ( 1758 , 1850 ) ;
	else {
	    
	  p = scanaction () ;
	  pdfnewobj ( 0 , 0 , 1 ) ;
	  if ( eqtb [29332 ].cint > 0 ) 
	  pdfcatalogopenaction = objptr ;
	  writeaction ( p ) ;
	  pdfendobj () ;
	  {
	    if ( mem [p + 2 ].hh .v.RH == -268435455L ) 
	    {
	      if ( mem [p ].hh.b0 == 3 ) 
	      deletetokenref ( mem [p + 2 ].hh .v.LH ) ;
	      else {
		  
		if ( mem [p + 1 ].hh .v.LH != -268435455L ) 
		deletetokenref ( mem [p + 1 ].hh .v.LH ) ;
		if ( mem [p ].hh.b0 == 0 ) 
		deletetokenref ( mem [p + 2 ].hh .v.LH ) ;
		else if ( mem [p ].hh.b1 > 0 ) 
		deletetokenref ( mem [p ].hh .v.RH ) ;
	      } 
	      freenode ( p , 3 ) ;
	    } 
	    else decr ( mem [p + 2 ].hh .v.RH ) ;
	  } 
	} 
      } 
    } 
    break ;
  case 17 : 
    {
      checkpdfoutput ( 1827 , true ) ;
      q = curlist .tailfield ;
      newwhatsit ( 17 , 7 ) ;
      if ( scankeyword ( 1190 ) ) 
      {
	scanint () ;
	if ( curval <= 0 ) 
	pdferror ( 1758 , 1813 ) ;
	if ( curval > 268435455L ) 
	pdferror ( 1758 , 1023 ) ;
	mem [curlist .tailfield + 5 ].hh .v.RH = curval ;
	mem [curlist .tailfield + 5 ].hh.b1 = 0 ;
      } 
      else if ( scankeyword ( 1811 ) ) 
      {
	scanpdfexttoks () ;
	mem [curlist .tailfield + 5 ].hh .v.RH = defref ;
	mem [curlist .tailfield + 5 ].hh.b1 = 1 ;
      } 
      else pdferror ( 1758 , 1814 ) ;
      if ( scankeyword ( 1828 ) ) 
      {
	mem [curlist .tailfield + 5 ].hh.b0 = 0 ;
	if ( scankeyword ( 1829 ) ) 
	{
	  scanint () ;
	  if ( curval > 268435455L ) 
	  pdferror ( 1758 , 1023 ) ;
	  mem [curlist .tailfield + 6 ].hh .v.LH = curval ;
	} 
	else mem [curlist .tailfield + 6 ].hh .v.LH = -268435455L ;
      } 
      else if ( scankeyword ( 1830 ) ) 
      mem [curlist .tailfield + 5 ].hh.b0 = 5 ;
      else if ( scankeyword ( 1831 ) ) 
      mem [curlist .tailfield + 5 ].hh.b0 = 6 ;
      else if ( scankeyword ( 1832 ) ) 
      mem [curlist .tailfield + 5 ].hh.b0 = 4 ;
      else if ( scankeyword ( 1833 ) ) 
      mem [curlist .tailfield + 5 ].hh.b0 = 2 ;
      else if ( scankeyword ( 1834 ) ) 
      mem [curlist .tailfield + 5 ].hh.b0 = 3 ;
      else if ( scankeyword ( 1835 ) ) 
      mem [curlist .tailfield + 5 ].hh.b0 = 7 ;
      else if ( scankeyword ( 1836 ) ) 
      mem [curlist .tailfield + 5 ].hh.b0 = 1 ;
      else pdferror ( 1758 , 1837 ) ;
      {
	getxtoken () ;
	if ( curcmd != 10 ) 
	backinput () ;
      } 
      if ( mem [curlist .tailfield + 5 ].hh.b0 == 7 ) 
      {
	scanaltrule () ;
	mem [curlist .tailfield + 1 ].cint = mem [altrule + 1 ].cint ;
	mem [curlist .tailfield + 2 ].cint = mem [altrule + 3 ].cint ;
	mem [curlist .tailfield + 3 ].cint = mem [altrule + 2 ].cint ;
      } 
      if ( mem [curlist .tailfield + 5 ].hh.b1 != 0 ) 
      {
	i = tokenstostring ( mem [curlist .tailfield + 5 ].hh .v.RH ) ;
	k = findobj ( 5 , i , true ) ;
	flushstr ( i ) ;
      } 
      else k = findobj ( 5 , mem [curlist .tailfield + 5 ].hh .v.RH , false 
      ) ;
      if ( ( k != 0 ) && ( objtab [k ].int4 != -268435455L ) ) 
      {
	warndestdup ( mem [curlist .tailfield + 5 ].hh .v.RH , mem [curlist 
	.tailfield + 5 ].hh.b1 , 1838 , 1839 ) ;
	flushnodelist ( curlist .tailfield ) ;
	curlist .tailfield = q ;
	mem [q ].hh .v.RH = -268435455L ;
      } 
    } 
    break ;
  case 15 : 
    {
      checkpdfoutput ( 1822 , true ) ;
      if ( abs ( curlist .modefield ) == 1 ) 
      pdferror ( 1758 , 1823 ) ;
      newwhatsit ( 15 , 2 ) ;
    } 
    break ;
  case 20 : 
    {
      checkpdfoutput ( 1842 , true ) ;
      newwhatsit ( 20 , 2 ) ;
    } 
    break ;
  case 25 : 
    {
      checkpdfoutput ( 1195 , true ) ;
      scanfontident () ;
      k = curval ;
      if ( k == 0 ) 
      pdferror ( 590 , 868 ) ;
      scanpdfexttoks () ;
      pdffontattr [k ]= tokenstostring ( defref ) ;
    } 
    break ;
  case 32 : 
    readexpandfont () ;
    break ;
  case 26 : 
    {
      checkpdfoutput ( 1854 , true ) ;
      pdfincludechars () ;
    } 
    break ;
  case 22 : 
    {
      checkpdfoutput ( 1847 , false ) ;
      scanpdfexttoks () ;
      if ( eqtb [29332 ].cint > 0 ) 
      pdfinfotoks = concattokens ( pdfinfotoks , defref ) ;
    } 
    break ;
  case 6 : 
    {
      checkpdfoutput ( 1761 , true ) ;
      newwhatsit ( 6 , 2 ) ;
      if ( scankeyword ( 885 ) ) 
      mem [curlist .tailfield + 1 ].hh .v.LH = 2 ;
      else if ( scankeyword ( 884 ) ) 
      mem [curlist .tailfield + 1 ].hh .v.LH = 1 ;
      else mem [curlist .tailfield + 1 ].hh .v.LH = 0 ;
      scanpdfexttoks () ;
      mem [curlist .tailfield + 1 ].hh .v.RH = defref ;
    } 
    break ;
  case 38 : 
    {
      checkpdfoutput ( 1762 , true ) ;
      scanint () ;
      if ( curval >= colorstackused () ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 1763 ) ;
	} 
	printint ( curval ) ;
	{
	  helpptr = 3 ;
	  helpline [2 ]= 1764 ;
	  helpline [1 ]= 1765 ;
	  helpline [0 ]= 1766 ;
	} 
	error () ;
	curval = 0 ;
      } 
      if ( curval < 0 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 1767 ) ;
	} 
	{
	  helpptr = 2 ;
	  helpline [1 ]= 1765 ;
	  helpline [0 ]= 1768 ;
	} 
	error () ;
	curval = 0 ;
      } 
      if ( scankeyword ( 1769 ) ) 
      {
	i = 0 ;
	j = 3 ;
      } 
      else if ( scankeyword ( 1770 ) ) 
      {
	i = 1 ;
	j = 3 ;
      } 
      else if ( scankeyword ( 1771 ) ) 
      {
	i = 2 ;
	j = 2 ;
      } 
      else if ( scankeyword ( 1772 ) ) 
      {
	i = 3 ;
	j = 2 ;
      } 
      else {
	  
	i = -1 ;
      } 
      if ( i >= 0 ) 
      {
	newwhatsit ( 38 , j ) ;
	mem [curlist .tailfield + 1 ].hh .v.RH = curval ;
	mem [curlist .tailfield + 1 ].hh .v.LH = i ;
	if ( i <= 1 ) 
	{
	  scanpdfexttoks () ;
	  mem [curlist .tailfield + 2 ].hh .v.RH = defref ;
	} 
      } 
      else {
	  
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 1773 ) ;
	} 
	{
	  helpptr = 3 ;
	  helpline [2 ]= 1774 ;
	  helpline [1 ]= 1775 ;
	  helpline [0 ]= 1776 ;
	} 
	error () ;
      } 
    } 
    break ;
  case 39 : 
    {
      checkpdfoutput ( 1129 , true ) ;
      newwhatsit ( 39 , 2 ) ;
      scanpdfexttoks () ;
      mem [curlist .tailfield + 1 ].hh .v.RH = defref ;
    } 
    break ;
  case 40 : 
    {
      checkpdfoutput ( 1777 , true ) ;
      newwhatsit ( 40 , 2 ) ;
    } 
    break ;
  case 41 : 
    {
      checkpdfoutput ( 1778 , true ) ;
      newwhatsit ( 41 , 2 ) ;
    } 
    break ;
  case 27 : 
    {
      checkpdfoutput ( 1855 , true ) ;
      scanpdfexttoks () ;
      pdfmapfile ( defref ) ;
      deletetokenref ( defref ) ;
    } 
    break ;
  case 28 : 
    {
      checkpdfoutput ( 1856 , true ) ;
      scanpdfexttoks () ;
      pdfmapline ( defref ) ;
      deletetokenref ( defref ) ;
    } 
    break ;
  case 24 : 
    {
      checkpdfoutput ( 1851 , true ) ;
      scanpdfexttoks () ;
      pdfnamestoks = concattokens ( pdfnamestoks , defref ) ;
    } 
    break ;
  case 7 : 
    {
      checkpdfoutput ( 1779 , true ) ;
      if ( scankeyword ( 1780 ) ) 
      {
	{
	  getxtoken () ;
	  if ( curcmd != 10 ) 
	  backinput () ;
	} 
	incr ( pdfobjcount ) ;
	pdfcreateobj ( 6 , pdfobjcount ) ;
	pdflastobj = objptr ;
      } 
      else {
	  
	k = -1 ;
	if ( scankeyword ( 1781 ) ) 
	{
	  scanint () ;
	  k = curval ;
	  if ( ( k <= 0 ) || ( k > objptr ) || ( objtab [k ].int4 != 0 ) ) 
	  {
	    pdfwarning ( 1779 , 1782 , true , true ) ;
	    pdfretval = -1 ;
	    k = -1 ;
	  } 
	} 
	if ( k < 0 ) 
	{
	  incr ( pdfobjcount ) ;
	  pdfcreateobj ( 6 , pdfobjcount ) ;
	  k = objptr ;
	} 
	objtab [k ].int4 = pdfgetmem ( 4 ) ;
	if ( scankeyword ( 1014 ) ) 
	{
	  pdfmem [objtab [k ].int4 + 1 ]= 1 ;
	  if ( scankeyword ( 1783 ) ) 
	  {
	    scanpdfexttoks () ;
	    pdfmem [objtab [k ].int4 + 2 ]= defref ;
	  } 
	  else pdfmem [objtab [k ].int4 + 2 ]= -268435455L ;
	} 
	else pdfmem [objtab [k ].int4 + 1 ]= 0 ;
	if ( scankeyword ( 873 ) ) 
	pdfmem [objtab [k ].int4 + 3 ]= 1 ;
	else pdfmem [objtab [k ].int4 + 3 ]= 0 ;
	scanpdfexttoks () ;
	pdfmem [objtab [k ].int4 + 0 ]= defref ;
	pdflastobj = k ;
      } 
    } 
    break ;
  case 16 : 
    {
      checkpdfoutput ( 1824 , true ) ;
      if ( scankeyword ( 1783 ) ) 
      {
	scanpdfexttoks () ;
	r = defref ;
      } 
      else r = 0 ;
      p = scanaction () ;
      if ( scankeyword ( 533 ) ) 
      {
	scanint () ;
	i = curval ;
      } 
      else i = 0 ;
      scanpdfexttoks () ;
      q = defref ;
      pdfnewobj ( 0 , 0 , 1 ) ;
      j = objptr ;
      writeaction ( p ) ;
      pdfendobj () ;
      {
	if ( mem [p + 2 ].hh .v.RH == -268435455L ) 
	{
	  if ( mem [p ].hh.b0 == 3 ) 
	  deletetokenref ( mem [p + 2 ].hh .v.LH ) ;
	  else {
	      
	    if ( mem [p + 1 ].hh .v.LH != -268435455L ) 
	    deletetokenref ( mem [p + 1 ].hh .v.LH ) ;
	    if ( mem [p ].hh.b0 == 0 ) 
	    deletetokenref ( mem [p + 2 ].hh .v.LH ) ;
	    else if ( mem [p ].hh.b1 > 0 ) 
	    deletetokenref ( mem [p ].hh .v.RH ) ;
	  } 
	  freenode ( p , 3 ) ;
	} 
	else decr ( mem [p + 2 ].hh .v.RH ) ;
      } 
      pdfcreateobj ( 4 , 0 ) ;
      k = objptr ;
      objtab [k ].int4 = pdfgetmem ( 8 ) ;
      pdfmem [objtab [k ].int4 + 6 ]= j ;
      objtab [k ].int0 = i ;
      pdfnewobj ( 0 , 0 , 1 ) ;
      pdfprintstrln ( tokenstostring ( q ) ) ;
      flushstr ( lasttokensstring ) ;
      deletetokenref ( q ) ;
      pdfendobj () ;
      pdfmem [objtab [k ].int4 ]= objptr ;
      pdfmem [objtab [k ].int4 + 2 ]= 0 ;
      pdfmem [objtab [k ].int4 + 3 ]= 0 ;
      pdfmem [objtab [k ].int4 + 4 ]= 0 ;
      pdfmem [objtab [k ].int4 + 5 ]= 0 ;
      pdfmem [objtab [k ].int4 + 1 ]= pdfparentoutline ;
      pdfmem [objtab [k ].int4 + 7 ]= r ;
      if ( pdffirstoutline == 0 ) 
      pdffirstoutline = k ;
      if ( pdflastoutline == 0 ) 
      {
	if ( pdfparentoutline != 0 ) 
	pdfmem [objtab [pdfparentoutline ].int4 + 4 ]= k ;
      } 
      else {
	  
	pdfmem [objtab [pdflastoutline ].int4 + 3 ]= k ;
	pdfmem [objtab [k ].int4 + 2 ]= pdflastoutline ;
      } 
      pdflastoutline = k ;
      if ( objtab [k ].int0 != 0 ) 
      {
	pdfparentoutline = k ;
	pdflastoutline = 0 ;
      } 
      else if ( ( pdfparentoutline != 0 ) && ( outlinelistcount ( k ) == abs ( 
      objtab [pdfparentoutline ].int0 ) ) ) 
      {
	j = pdflastoutline ;
	do {
	    pdfmem [objtab [pdfparentoutline ].int4 + 5 ]= j ;
	  j = pdfparentoutline ;
	  pdfparentoutline = pdfmem [objtab [pdfparentoutline ].int4 + 1 ]
	  ;
	} while ( ! ( ( pdfparentoutline == 0 ) || ( outlinelistcount ( j ) < 
	abs ( objtab [pdfparentoutline ].int0 ) ) ) ) ;
	if ( pdfparentoutline == 0 ) 
	pdflastoutline = pdffirstoutline ;
	else pdflastoutline = pdfmem [objtab [pdfparentoutline ].int4 + 4 ]
	;
	while ( pdfmem [objtab [pdflastoutline ].int4 + 3 ]!= 0 ) 
	pdflastoutline = pdfmem [objtab [pdflastoutline ].int4 + 3 ];
      } 
    } 
    break ;
  case 8 : 
    {
      checkpdfoutput ( 1785 , true ) ;
      scanint () ;
      pdfcheckobj ( 6 , curval ) ;
      newwhatsit ( 8 , 2 ) ;
      mem [curlist .tailfield + 1 ].hh .v.LH = curval ;
    } 
    break ;
  case 10 : 
    {
      checkpdfoutput ( 1789 , true ) ;
      scanint () ;
      pdfcheckobj ( 7 , curval ) ;
      newwhatsit ( 10 , 5 ) ;
      mem [curlist .tailfield + 4 ].hh .v.LH = curval ;
      mem [curlist .tailfield + 1 ].cint = pdfmem [objtab [curval ].int4 
      + 0 ];
      mem [curlist .tailfield + 2 ].cint = pdfmem [objtab [curval ].int4 
      + 1 ];
      mem [curlist .tailfield + 3 ].cint = pdfmem [objtab [curval ].int4 
      + 2 ];
    } 
    break ;
  case 12 : 
    {
      checkpdfoutput ( 1804 , true ) ;
      scanint () ;
      pdfcheckobj ( 8 , curval ) ;
      newwhatsit ( 12 , 5 ) ;
      mem [curlist .tailfield + 4 ].hh .v.LH = curval ;
      mem [curlist .tailfield + 1 ].cint = pdfmem [objtab [curval ].int4 
      + 0 ];
      mem [curlist .tailfield + 2 ].cint = pdfmem [objtab [curval ].int4 
      + 1 ];
      mem [curlist .tailfield + 3 ].cint = pdfmem [objtab [curval ].int4 
      + 2 ];
    } 
    break ;
  case 21 : 
    {
      newwhatsit ( 21 , 2 ) ;
    } 
    break ;
  case 34 : 
    {
      checkpdfoutput ( 1843 , true ) ;
      newwhatsit ( 34 , 2 ) ;
    } 
    break ;
  case 36 : 
    {
      checkpdfoutput ( 1846 , true ) ;
      newwhatsit ( 36 , 2 ) ;
      scanint () ;
      mem [curlist .tailfield + 1 ].cint = fixint ( curval , 0 , 1000 ) ;
    } 
    break ;
  case 35 : 
    {
      checkpdfoutput ( 1845 , true ) ;
      {
	mem [curlist .tailfield ].hh .v.RH = newsnapnode ( 35 ) ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
    } 
    break ;
  case 14 : 
    {
      checkpdfoutput ( 1820 , true ) ;
      if ( abs ( curlist .modefield ) == 1 ) 
      pdferror ( 1758 , 1821 ) ;
      k = pdfnewobjnum () ;
      newannotwhatsit ( 14 , 7 ) ;
      mem [curlist .tailfield + 5 ].hh .v.RH = scanaction () ;
      mem [curlist .tailfield + 6 ].cint = k ;
      pdflastlink = k ;
    } 
    break ;
  case 19 : 
    {
      checkpdfoutput ( 1841 , true ) ;
      newannotwhatsit ( 19 , 7 ) ;
      scanthreadid () ;
    } 
    break ;
  case 18 : 
    {
      checkpdfoutput ( 1840 , true ) ;
      newannotwhatsit ( 18 , 7 ) ;
      scanthreadid () ;
    } 
    break ;
  case 29 : 
    {
      checkpdfoutput ( 1852 , false ) ;
      scanpdfexttoks () ;
      if ( eqtb [29332 ].cint > 0 ) 
      pdftrailertoks = concattokens ( pdftrailertoks , defref ) ;
    } 
    break ;
  case 30 : 
    {
      checkpdfoutput ( 1853 , false ) ;
      scanpdfexttoks () ;
      if ( eqtb [29332 ].cint > 0 ) 
      pdftraileridtoks = concattokens ( pdftraileridtoks , defref ) ;
    } 
    break ;
  case 9 : 
    {
      checkpdfoutput ( 1786 , true ) ;
      incr ( pdfxformcount ) ;
      pdfcreateobj ( 7 , pdfxformcount ) ;
      k = objptr ;
      objtab [k ].int4 = pdfgetmem ( 6 ) ;
      if ( scankeyword ( 1783 ) ) 
      {
	scanpdfexttoks () ;
	pdfmem [objtab [k ].int4 + 4 ]= defref ;
      } 
      else pdfmem [objtab [k ].int4 + 4 ]= -268435455L ;
      if ( scankeyword ( 1787 ) ) 
      {
	scanpdfexttoks () ;
	pdfmem [objtab [k ].int4 + 5 ]= defref ;
      } 
      else pdfmem [objtab [k ].int4 + 5 ]= -268435455L ;
      scanregisternum () ;
      if ( curval < 256 ) 
      p = eqtb [27433 + curval ].hh .v.RH ;
      else {
	  
	findsaelement ( 4 , curval , false ) ;
	if ( curptr == -268435455L ) 
	p = -268435455L ;
	else p = mem [curptr + 1 ].hh .v.RH ;
      } 
      if ( p == -268435455L ) 
      pdferror ( 1758 , 1788 ) ;
      pdfmem [objtab [k ].int4 + 0 ]= mem [p + 1 ].cint ;
      pdfmem [objtab [k ].int4 + 1 ]= mem [p + 3 ].cint ;
      pdfmem [objtab [k ].int4 + 2 ]= mem [p + 2 ].cint ;
      pdfmem [objtab [k ].int4 + 3 ]= p ;
      if ( curval < 256 ) 
      eqtb [27433 + curval ].hh .v.RH = -268435455L ;
      else {
	  
	findsaelement ( 4 , curval , false ) ;
	if ( curptr != -268435455L ) 
	{
	  mem [curptr + 1 ].hh .v.RH = -268435455L ;
	  incr ( mem [curptr + 1 ].hh .v.LH ) ;
	  deletesaref ( curptr ) ;
	} 
      } 
      pdflastxform = k ;
    } 
    break ;
  case 11 : 
    {
      checkpdfoutput ( 1803 , true ) ;
      checkpdfminorversion () ;
      scanimage () ;
    } 
    break ;
  case 31 : 
    {
      secondsandmicros ( epochseconds , microseconds ) ;
    } 
    break ;
  case 33 : 
    {
      scanint () ;
      if ( curval < 0 ) 
      curval = - (integer) curval ;
      randomseed = curval ;
      initrandoms ( randomseed ) ;
    } 
    break ;
  case 37 : 
    {
      glyphtounicode () ;
    } 
    break ;
  case 42 : 
    {
      checkpdfoutput ( 1857 , true ) ;
      scanfontident () ;
      k = curval ;
      if ( k == 0 ) 
      pdferror ( 590 , 868 ) ;
      pdffontnobuiltintounicode [k ]= true ;
    } 
    break ;
  case 43 : 
    {
      checkpdfoutput ( 1858 , true ) ;
      newwhatsit ( 43 , 2 ) ;
    } 
    break ;
  case 44 : 
    {
      checkpdfoutput ( 1859 , true ) ;
      newwhatsit ( 44 , 2 ) ;
    } 
    break ;
  case 45 : 
    {
      checkpdfoutput ( 1860 , true ) ;
      newwhatsit ( 45 , 2 ) ;
    } 
    break ;
    default: 
    confusion ( 1758 ) ;
    break ;
  } 
} 
void 
fixlanguage ( void ) 
{
  fixlanguage_regmem 
  ASCIIcode l  ;
  if ( eqtb [29324 ].cint <= 0 ) 
  l = 0 ;
  else if ( eqtb [29324 ].cint > 255 ) 
  l = 0 ;
  else l = eqtb [29324 ].cint ;
  if ( l != curlist .auxfield .hh .v.RH ) 
  {
    newwhatsit ( 4 , 2 ) ;
    mem [curlist .tailfield + 1 ].hh .v.RH = l ;
    curlist .auxfield .hh .v.RH = l ;
    mem [curlist .tailfield + 1 ].hh.b0 = normmin ( eqtb [29325 ].cint ) ;
    mem [curlist .tailfield + 1 ].hh.b1 = normmin ( eqtb [29326 ].cint ) ;
  } 
} 
void 
insertsrcspecial ( void ) 
{
  insertsrcspecial_regmem 
  halfword toklist, p, q  ;
  if ( ( sourcefilenamestack [inopen ]> 0 && isnewsource ( 
  sourcefilenamestack [inopen ], line ) ) ) 
  {
    toklist = getavail () ;
    p = toklist ;
    mem [p ].hh .v.LH = 19619 ;
    mem [p ].hh .v.RH = getavail () ;
    p = mem [p ].hh .v.RH ;
    mem [p ].hh .v.LH = 379 ;
    q = strtoks ( makesrcspecial ( sourcefilenamestack [inopen ], line ) ) ;
    mem [p ].hh .v.RH = mem [memtop - 3 ].hh .v.RH ;
    p = q ;
    mem [p ].hh .v.RH = getavail () ;
    p = mem [p ].hh .v.RH ;
    mem [p ].hh .v.LH = 637 ;
    begintokenlist ( toklist , 4 ) ;
    remembersourceinfo ( sourcefilenamestack [inopen ], line ) ;
  } 
} 
void 
appendsrcspecial ( void ) 
{
  appendsrcspecial_regmem 
  halfword q  ;
  if ( ( sourcefilenamestack [inopen ]> 0 && isnewsource ( 
  sourcefilenamestack [inopen ], line ) ) ) 
  {
    newwhatsit ( 3 , 2 ) ;
    mem [curlist .tailfield + 1 ].hh .v.LH = 0 ;
    defref = getavail () ;
    mem [defref ].hh .v.LH = -268435455L ;
    q = strtoks ( makesrcspecial ( sourcefilenamestack [inopen ], line ) ) ;
    mem [defref ].hh .v.RH = mem [memtop - 3 ].hh .v.RH ;
    mem [curlist .tailfield + 1 ].hh .v.RH = defref ;
    remembersourceinfo ( sourcefilenamestack [inopen ], line ) ;
  } 
} 
void 
handlerightbrace ( void ) 
{
  handlerightbrace_regmem 
  halfword p, q  ;
  scaled d  ;
  integer f  ;
  switch ( curgroup ) 
  {case 1 : 
    unsave () ;
    break ;
  case 0 : 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 1449 ) ;
      } 
      {
	helpptr = 2 ;
	helpline [1 ]= 1450 ;
	helpline [0 ]= 1451 ;
      } 
      error () ;
    } 
    break ;
  case 14 : 
  case 15 : 
  case 16 : 
    extrarightbrace () ;
    break ;
  case 2 : 
    package ( 0 ) ;
    break ;
  case 3 : 
    {
      adjusttail = memtop - 5 ;
      preadjusttail = memtop - 14 ;
      package ( 0 ) ;
    } 
    break ;
  case 4 : 
    {
      endgraf () ;
      package ( 0 ) ;
    } 
    break ;
  case 5 : 
    {
      endgraf () ;
      package ( 4 ) ;
    } 
    break ;
  case 11 : 
    {
      endgraf () ;
      q = eqtb [26638 ].hh .v.RH ;
      incr ( mem [q ].hh .v.RH ) ;
      d = eqtb [29893 ].cint ;
      f = eqtb [29316 ].cint ;
      unsave () ;
      saveptr = saveptr - 2 ;
      p = vpackage ( mem [curlist .headfield ].hh .v.RH , 0 , 1 , 
      1073741823L ) ;
      popnest () ;
      if ( savestack [saveptr + 0 ].cint < 255 ) 
      {
	{
	  mem [curlist .tailfield ].hh .v.RH = getnode ( 5 ) ;
	  curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	} 
	mem [curlist .tailfield ].hh.b0 = 3 ;
	mem [curlist .tailfield ].hh.b1 = savestack [saveptr + 0 ].cint ;
	mem [curlist .tailfield + 3 ].cint = mem [p + 3 ].cint + mem [p + 
	2 ].cint ;
	mem [curlist .tailfield + 4 ].hh .v.LH = mem [p + 5 ].hh .v.RH ;
	mem [curlist .tailfield + 4 ].hh .v.RH = q ;
	mem [curlist .tailfield + 2 ].cint = d ;
	mem [curlist .tailfield + 1 ].cint = f ;
      } 
      else {
	  
	{
	  mem [curlist .tailfield ].hh .v.RH = getnode ( 2 ) ;
	  curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	} 
	mem [curlist .tailfield ].hh.b0 = 5 ;
	mem [curlist .tailfield ].hh.b1 = savestack [saveptr + 1 ].cint ;
	mem [curlist .tailfield + 1 ].cint = mem [p + 5 ].hh .v.RH ;
	deleteglueref ( q ) ;
      } 
      freenode ( p , 7 ) ;
      if ( nestptr == 0 ) 
      buildpage () ;
    } 
    break ;
  case 8 : 
    {
      if ( ( curinput .locfield != -268435455L ) || ( ( curinput .indexfield 
      != 6 ) && ( curinput .indexfield != 3 ) ) ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 1417 ) ;
	} 
	{
	  helpptr = 2 ;
	  helpline [1 ]= 1418 ;
	  helpline [0 ]= 1419 ;
	} 
	error () ;
	do {
	    gettoken () ;
	} while ( ! ( curinput .locfield == -268435455L ) ) ;
      } 
      endtokenlist () ;
      endgraf () ;
      unsave () ;
      outputactive = false ;
      insertpenalties = 0 ;
      if ( eqtb [27688 ].hh .v.RH != -268435455L ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 264 ) ;
	  print ( 1420 ) ;
	} 
	printesc ( 429 ) ;
	printint ( 255 ) ;
	{
	  helpptr = 3 ;
	  helpline [2 ]= 1421 ;
	  helpline [1 ]= 1422 ;
	  helpline [0 ]= 1423 ;
	} 
	boxerror ( 255 ) ;
      } 
      if ( curlist .tailfield != curlist .headfield ) 
      {
	mem [pagetail ].hh .v.RH = mem [curlist .headfield ].hh .v.RH ;
	pagetail = curlist .tailfield ;
      } 
      if ( mem [memtop - 2 ].hh .v.RH != -268435455L ) 
      {
	if ( mem [memtop - 1 ].hh .v.RH == -268435455L ) 
	nest [0 ].tailfield = pagetail ;
	mem [pagetail ].hh .v.RH = mem [memtop - 1 ].hh .v.RH ;
	mem [memtop - 1 ].hh .v.RH = mem [memtop - 2 ].hh .v.RH ;
	mem [memtop - 2 ].hh .v.RH = -268435455L ;
	pagetail = memtop - 2 ;
      } 
      flushnodelist ( discptr [2 ]) ;
      discptr [2 ]= -268435455L ;
      popnest () ;
      buildpage () ;
    } 
    break ;
  case 10 : 
    builddiscretionary () ;
    break ;
  case 6 : 
    {
      backinput () ;
      curtok = 19610 ;
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 707 ) ;
      } 
      printesc ( 1301 ) ;
      print ( 708 ) ;
      {
	helpptr = 1 ;
	helpline [0 ]= 1533 ;
      } 
      inserror () ;
    } 
    break ;
  case 7 : 
    {
      endgraf () ;
      unsave () ;
      alignpeek () ;
    } 
    break ;
  case 12 : 
    {
      endgraf () ;
      unsave () ;
      saveptr = saveptr - 2 ;
      p = vpackage ( mem [curlist .headfield ].hh .v.RH , savestack [
      saveptr + 1 ].cint , savestack [saveptr + 0 ].cint , 1073741823L ) ;
      popnest () ;
      {
	mem [curlist .tailfield ].hh .v.RH = newnoad () ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
      mem [curlist .tailfield ].hh.b0 = 29 ;
      mem [curlist .tailfield + 1 ].hh .v.RH = 2 ;
      mem [curlist .tailfield + 1 ].hh .v.LH = p ;
    } 
    break ;
  case 13 : 
    buildchoices () ;
    break ;
  case 9 : 
    {
      unsave () ;
      decr ( saveptr ) ;
      mem [savestack [saveptr + 0 ].cint ].hh .v.RH = 3 ;
      p = finmlist ( -268435455L ) ;
      mem [savestack [saveptr + 0 ].cint ].hh .v.LH = p ;
      if ( p != -268435455L ) {
	  
	if ( mem [p ].hh .v.RH == -268435455L ) {
	    
	  if ( mem [p ].hh.b0 == 16 ) 
	  {
	    if ( mem [p + 3 ].hh .v.RH == 0 ) {
		
	      if ( mem [p + 2 ].hh .v.RH == 0 ) 
	      {
		mem [savestack [saveptr + 0 ].cint ].hh = mem [p + 1 ]
		.hh ;
		freenode ( p , 4 ) ;
	      } 
	    } 
	  } 
	  else if ( mem [p ].hh.b0 == 28 ) {
	      
	    if ( savestack [saveptr + 0 ].cint == curlist .tailfield + 1 ) {
		
	      if ( mem [curlist .tailfield ].hh.b0 == 16 ) 
	      {
		q = curlist .headfield ;
		while ( mem [q ].hh .v.RH != curlist .tailfield ) q = mem [
		q ].hh .v.RH ;
		mem [q ].hh .v.RH = p ;
		freenode ( curlist .tailfield , 4 ) ;
		curlist .tailfield = p ;
	      } 
	    } 
	  } 
	} 
      } 
    } 
    break ;
    default: 
    confusion ( 1452 ) ;
    break ;
  } 
} 
void 
maincontrol ( void ) 
{
  /* 60 21 70 80 90 91 92 95 100 101 110 111 112 120 10 */ 
  maincontrol_regmem 
  integer t  ;
  halfword tmpk1, tmpk2  ;
  if ( eqtb [27165 ].hh .v.RH != -268435455L ) 
  begintokenlist ( eqtb [27165 ].hh .v.RH , 12 ) ;
  lab60: getxtoken () ;
  lab21: if ( interrupt != 0 ) {
      
    if ( OKtointerrupt ) 
    {
      backinput () ;
      {
	if ( interrupt != 0 ) 
	pauseforinstructions () ;
      } 
      goto lab60 ;
    } 
  } 
	;
#ifdef TEXMF_DEBUG
  if ( panicking ) 
  checkmem ( false ) ;
#endif /* TEXMF_DEBUG */
  if ( eqtb [29310 ].cint > 0 ) 
  showcurcmdchr () ;
  switch ( abs ( curlist .modefield ) + curcmd ) 
  {case 115 : 
  case 116 : 
  case 172 : 
    goto lab70 ;
    break ;
  case 120 : 
    {
      scancharnum () ;
      curchr = curval ;
      goto lab70 ;
    } 
    break ;
  case 169 : 
    {
      getxtoken () ;
      if ( ( curcmd == 11 ) || ( curcmd == 12 ) || ( curcmd == 68 ) || ( 
      curcmd == 16 ) ) 
      cancelboundary = true ;
      goto lab21 ;
    } 
    break ;
  case 114 : 
    if ( ( curlist .auxfield .hh .v.LH == 1000 ) || ( eqtb [29353 ].cint > 0 
    ) ) 
    goto lab120 ;
    else appspace () ;
    break ;
  case 168 : 
  case 271 : 
    goto lab120 ;
    break ;
  case 1 : 
  case 104 : 
  case 207 : 
  case 11 : 
  case 217 : 
  case 272 : 
    ;
    break ;
  case 40 : 
  case 143 : 
  case 246 : 
    {
      if ( curchr == 0 ) 
      {
	do {
	    getxtoken () ;
	} while ( ! ( curcmd != 10 ) ) ;
	goto lab21 ;
      } 
      else {
	  
	t = scannerstatus ;
	scannerstatus = 0 ;
	getnext () ;
	scannerstatus = t ;
	if ( curcs < 514 ) 
	curcs = primlookup ( curcs - 257 ) ;
	else curcs = primlookup ( hash [curcs ].v.RH ) ;
	if ( curcs != 0 ) 
	{
	  curcmd = eqtb [15526 + curcs ].hh.b0 ;
	  curchr = eqtb [15526 + curcs ].hh .v.RH ;
	  curtok = 19621 + curcs ;
	  goto lab21 ;
	} 
      } 
    } 
    break ;
  case 15 : 
    if ( itsallover () ) 
    return ;
    break ;
  case 23 : 
  case 125 : 
  case 228 : 
  case 71 : 
  case 174 : 
  case 277 : 
  case 39 : 
  case 45 : 
  case 49 : 
  case 152 : 
  case 7 : 
  case 110 : 
  case 213 : 
    reportillegalcase () ;
    break ;
  case 8 : 
  case 111 : 
  case 9 : 
  case 112 : 
  case 18 : 
  case 121 : 
  case 70 : 
  case 173 : 
  case 51 : 
  case 154 : 
  case 16 : 
  case 119 : 
  case 50 : 
  case 153 : 
  case 53 : 
  case 156 : 
  case 67 : 
  case 170 : 
  case 54 : 
  case 157 : 
  case 55 : 
  case 158 : 
  case 57 : 
  case 160 : 
  case 56 : 
  case 159 : 
  case 31 : 
  case 134 : 
  case 52 : 
  case 155 : 
  case 29 : 
  case 132 : 
  case 47 : 
  case 150 : 
  case 216 : 
  case 220 : 
  case 221 : 
  case 234 : 
  case 231 : 
  case 240 : 
  case 243 : 
    insertdollarsign () ;
    break ;
  case 37 : 
  case 139 : 
  case 242 : 
    {
      {
	mem [curlist .tailfield ].hh .v.RH = scanrulespec () ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
      if ( abs ( curlist .modefield ) == 1 ) 
      curlist .auxfield .cint = eqtb [29919 ].cint ;
      else if ( abs ( curlist .modefield ) == 104 ) 
      curlist .auxfield .hh .v.LH = 1000 ;
    } 
    break ;
  case 28 : 
  case 130 : 
  case 233 : 
  case 235 : 
    appendglue () ;
    break ;
  case 30 : 
  case 133 : 
  case 236 : 
  case 237 : 
    appendkern () ;
    break ;
  case 2 : 
  case 105 : 
    newsavelevel ( 1 ) ;
    break ;
  case 62 : 
  case 165 : 
  case 268 : 
    newsavelevel ( 14 ) ;
    break ;
  case 63 : 
  case 166 : 
  case 269 : 
    if ( curgroup == 14 ) 
    unsave () ;
    else offsave () ;
    break ;
  case 3 : 
  case 106 : 
  case 209 : 
    handlerightbrace () ;
    break ;
  case 22 : 
  case 126 : 
  case 229 : 
    {
      t = curchr ;
      scandimen ( false , false , false ) ;
      if ( t == 0 ) 
      scanbox ( curval ) ;
      else scanbox ( - (integer) curval ) ;
    } 
    break ;
  case 32 : 
  case 135 : 
  case 238 : 
    scanbox ( 1073807261L + curchr ) ;
    break ;
  case 21 : 
  case 124 : 
  case 227 : 
    beginbox ( 0 ) ;
    break ;
  case 44 : 
    newgraf ( curchr > 0 ) ;
    break ;
  case 12 : 
  case 13 : 
  case 17 : 
  case 69 : 
  case 4 : 
  case 24 : 
  case 36 : 
  case 46 : 
  case 48 : 
  case 27 : 
  case 34 : 
  case 65 : 
  case 66 : 
    {
      backinput () ;
      newgraf ( true ) ;
    } 
    break ;
  case 147 : 
  case 250 : 
    if ( curchr != 2 ) 
    indentinhmode () ;
    break ;
  case 14 : 
    {
      normalparagraph () ;
      if ( curlist .modefield > 0 ) 
      buildpage () ;
    } 
    break ;
  case 117 : 
    {
      if ( alignstate < 0 ) 
      offsave () ;
      endgraf () ;
      if ( curlist .modefield == 1 ) 
      buildpage () ;
    } 
    break ;
  case 118 : 
  case 131 : 
  case 140 : 
  case 128 : 
  case 136 : 
    headforvmode () ;
    break ;
  case 38 : 
  case 141 : 
  case 244 : 
  case 142 : 
  case 245 : 
    begininsertoradjust () ;
    break ;
  case 19 : 
  case 122 : 
  case 225 : 
    makemark () ;
    break ;
  case 43 : 
  case 146 : 
  case 249 : 
    appendpenalty () ;
    break ;
  case 26 : 
  case 129 : 
  case 232 : 
    deletelast () ;
    break ;
  case 25 : 
  case 127 : 
  case 230 : 
    unpackage () ;
    break ;
  case 148 : 
    appenditaliccorrection () ;
    break ;
  case 251 : 
    {
      mem [curlist .tailfield ].hh .v.RH = newkern ( 0 ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    break ;
  case 151 : 
  case 254 : 
    appenddiscretionary () ;
    break ;
  case 149 : 
    makeaccent () ;
    break ;
  case 6 : 
  case 109 : 
  case 212 : 
  case 5 : 
  case 108 : 
  case 211 : 
    alignerror () ;
    break ;
  case 35 : 
  case 138 : 
  case 241 : 
    noalignerror () ;
    break ;
  case 64 : 
  case 167 : 
  case 270 : 
    omiterror () ;
    break ;
  case 33 : 
    initalign () ;
    break ;
  case 137 : 
    if ( curchr > 0 ) 
    {
      if ( eTeXenabled ( ( eqtb [29374 ].cint > 0 ) , curcmd , curchr ) ) 
      {
	mem [curlist .tailfield ].hh .v.RH = newmath ( 0 , curchr ) ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
    } 
    else initalign () ;
    break ;
  case 239 : 
    if ( privileged () ) {
	
      if ( curgroup == 15 ) 
      initalign () ;
      else offsave () ;
    } 
    break ;
  case 10 : 
  case 113 : 
    doendv () ;
    break ;
  case 68 : 
  case 171 : 
  case 274 : 
    cserror () ;
    break ;
  case 107 : 
    initmath () ;
    break ;
  case 255 : 
    if ( privileged () ) {
	
      if ( curgroup == 15 ) 
      starteqno () ;
      else offsave () ;
    } 
    break ;
  case 208 : 
    {
      {
	mem [curlist .tailfield ].hh .v.RH = newnoad () ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
      backinput () ;
      scanmath ( curlist .tailfield + 1 ) ;
    } 
    break ;
  case 218 : 
  case 219 : 
  case 275 : 
    setmathchar ( eqtb [28762 + curchr ].hh .v.RH ) ;
    break ;
  case 223 : 
    {
      scancharnum () ;
      curchr = curval ;
      setmathchar ( eqtb [28762 + curchr ].hh .v.RH ) ;
    } 
    break ;
  case 224 : 
    {
      scanfifteenbitint () ;
      setmathchar ( curval ) ;
    } 
    break ;
  case 276 : 
    setmathchar ( curchr ) ;
    break ;
  case 222 : 
    {
      scantwentysevenbitint () ;
      setmathchar ( curval / 4096 ) ;
    } 
    break ;
  case 257 : 
    {
      {
	mem [curlist .tailfield ].hh .v.RH = newnoad () ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
      mem [curlist .tailfield ].hh.b0 = curchr ;
      scanmath ( curlist .tailfield + 1 ) ;
    } 
    break ;
  case 258 : 
    mathlimitswitch () ;
    break ;
  case 273 : 
    mathradical () ;
    break ;
  case 252 : 
  case 253 : 
    mathac () ;
    break ;
  case 263 : 
    {
      scanspec ( 12 , false ) ;
      normalparagraph () ;
      pushnest () ;
      curlist .modefield = -1 ;
      curlist .auxfield .cint = eqtb [29919 ].cint ;
      if ( ( insertsrcspecialeveryvbox ) ) 
      insertsrcspecial () ;
      if ( eqtb [27164 ].hh .v.RH != -268435455L ) 
      begintokenlist ( eqtb [27164 ].hh .v.RH , 11 ) ;
    } 
    break ;
  case 260 : 
    {
      mem [curlist .tailfield ].hh .v.RH = newstyle ( curchr ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    break ;
  case 262 : 
    {
      {
	mem [curlist .tailfield ].hh .v.RH = newglue ( membot ) ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
      mem [curlist .tailfield ].hh.b1 = 98 ;
    } 
    break ;
  case 261 : 
    appendchoices () ;
    break ;
  case 215 : 
  case 214 : 
    subsup () ;
    break ;
  case 259 : 
    mathfraction () ;
    break ;
  case 256 : 
    mathleftright () ;
    break ;
  case 210 : 
    if ( curgroup == 15 ) 
    aftermath () ;
    else offsave () ;
    break ;
  case 72 : 
  case 175 : 
  case 278 : 
  case 73 : 
  case 176 : 
  case 279 : 
  case 74 : 
  case 177 : 
  case 280 : 
  case 75 : 
  case 178 : 
  case 281 : 
  case 76 : 
  case 179 : 
  case 282 : 
  case 77 : 
  case 180 : 
  case 283 : 
  case 78 : 
  case 181 : 
  case 284 : 
  case 79 : 
  case 182 : 
  case 285 : 
  case 80 : 
  case 183 : 
  case 286 : 
  case 81 : 
  case 184 : 
  case 287 : 
  case 82 : 
  case 185 : 
  case 288 : 
  case 83 : 
  case 186 : 
  case 289 : 
  case 84 : 
  case 187 : 
  case 290 : 
  case 85 : 
  case 188 : 
  case 291 : 
  case 86 : 
  case 189 : 
  case 292 : 
  case 87 : 
  case 190 : 
  case 293 : 
  case 88 : 
  case 191 : 
  case 294 : 
  case 89 : 
  case 192 : 
  case 295 : 
  case 102 : 
  case 205 : 
  case 308 : 
  case 103 : 
  case 206 : 
  case 309 : 
  case 90 : 
  case 193 : 
  case 296 : 
  case 91 : 
  case 194 : 
  case 297 : 
  case 92 : 
  case 195 : 
  case 298 : 
  case 93 : 
  case 196 : 
  case 299 : 
  case 94 : 
  case 197 : 
  case 300 : 
  case 95 : 
  case 198 : 
  case 301 : 
  case 96 : 
  case 199 : 
  case 302 : 
  case 97 : 
  case 200 : 
  case 303 : 
  case 98 : 
  case 201 : 
  case 304 : 
  case 99 : 
  case 202 : 
  case 305 : 
  case 100 : 
  case 203 : 
  case 306 : 
  case 101 : 
  case 204 : 
  case 307 : 
    prefixedcommand () ;
    break ;
  case 41 : 
  case 144 : 
  case 247 : 
    {
      gettoken () ;
      aftertoken = curtok ;
    } 
    break ;
  case 42 : 
  case 145 : 
  case 248 : 
    {
      gettoken () ;
      saveforafter ( curtok ) ;
    } 
    break ;
  case 61 : 
  case 164 : 
  case 267 : 
    openorclosein () ;
    break ;
  case 59 : 
  case 162 : 
  case 265 : 
    issuemessage () ;
    break ;
  case 58 : 
  case 161 : 
  case 264 : 
    shiftcase () ;
    break ;
  case 20 : 
  case 123 : 
  case 226 : 
    showwhatever () ;
    break ;
  case 60 : 
  case 163 : 
  case 266 : 
    doextension () ;
    break ;
  } 
  goto lab60 ;
  lab70: if ( ( ( curlist .headfield == curlist .tailfield ) && ( curlist 
  .modefield > 0 ) ) ) 
  {
    if ( ( insertsrcspecialauto ) ) 
    appendsrcspecial () ;
  } 
  mains = eqtb [28506 + curchr ].hh .v.RH ;
  if ( mains == 1000 ) 
  curlist .auxfield .hh .v.LH = 1000 ;
  else if ( mains < 1000 ) 
  {
    if ( mains > 0 ) 
    curlist .auxfield .hh .v.LH = mains ;
  } 
  else if ( curlist .auxfield .hh .v.LH < 1000 ) 
  curlist .auxfield .hh .v.LH = 1000 ;
  else curlist .auxfield .hh .v.LH = mains ;
  savetail = -268435455L ;
  mainf = eqtb [27689 ].hh .v.RH ;
  bchar = fontbchar [mainf ];
  falsebchar = fontfalsebchar [mainf ];
  if ( curlist .modefield > 0 ) {
      
    if ( eqtb [29324 ].cint != curlist .auxfield .hh .v.RH ) 
    fixlanguage () ;
  } 
  {
    ligstack = avail ;
    if ( ligstack == -268435455L ) 
    ligstack = getavail () ;
    else {
	
      avail = mem [ligstack ].hh .v.RH ;
      mem [ligstack ].hh .v.RH = -268435455L ;
	;
#ifdef STAT
      incr ( dynused ) ;
#endif /* STAT */
    } 
  } 
  mem [ligstack ].hh.b0 = mainf ;
  curl = curchr ;
  mem [ligstack ].hh.b1 = curl ;
  curq = curlist .tailfield ;
  tmpk1 = getautokern ( mainf , 256 , curl ) ;
  if ( tmpk1 != -268435455L ) 
  {
    if ( curl < 256 ) 
    {
      if ( mem [curq ].hh .v.RH > -268435455L ) {
	  
	if ( mem [curlist .tailfield ].hh.b1 == hyphenchar [mainf ]) 
	insdisc = true ;
      } 
      if ( ligaturepresent ) 
      {
	mainp = newligature ( mainf , curl , mem [curq ].hh .v.RH ) ;
	if ( lfthit ) 
	{
	  mem [mainp ].hh.b1 = 2 ;
	  lfthit = false ;
	} 
	if ( rthit ) {
	    
	  if ( ligstack == -268435455L ) 
	  {
	    incr ( mem [mainp ].hh.b1 ) ;
	    rthit = false ;
	  } 
	} 
	if ( eqtb [29354 ].cint > 0 ) 
	tmpk2 = getautokern ( mainf , 256 , curl ) ;
	else tmpk2 = -268435455L ;
	if ( tmpk2 == -268435455L ) 
	{
	  mem [curq ].hh .v.RH = mainp ;
	  curlist .tailfield = mainp ;
	  ligaturepresent = false ;
	} 
	else {
	    
	  mem [curq ].hh .v.RH = tmpk2 ;
	  mem [tmpk2 ].hh .v.RH = mainp ;
	  curlist .tailfield = mainp ;
	  ligaturepresent = false ;
	} 
      } 
      if ( insdisc ) 
      {
	insdisc = false ;
	if ( curlist .modefield > 0 ) 
	{
	  mem [curlist .tailfield ].hh .v.RH = newdisc () ;
	  curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	} 
      } 
    } 
    savetail = curlist .tailfield ;
    {
      mem [curlist .tailfield ].hh .v.RH = tmpk1 ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    goto lab90 ;
  } 
  if ( cancelboundary ) 
  {
    cancelboundary = false ;
    maink = 0 ;
  } 
  else maink = bcharlabel [mainf ];
  if ( maink == 0 ) 
  goto lab92 ;
  curr = curl ;
  curl = 256 ;
  goto lab111 ;
  lab80: if ( curl < 256 ) 
  {
    if ( mem [curq ].hh .v.RH > -268435455L ) {
	
      if ( mem [curlist .tailfield ].hh.b1 == hyphenchar [mainf ]) 
      insdisc = true ;
    } 
    if ( ligaturepresent ) 
    {
      mainp = newligature ( mainf , curl , mem [curq ].hh .v.RH ) ;
      if ( lfthit ) 
      {
	mem [mainp ].hh.b1 = 2 ;
	lfthit = false ;
      } 
      if ( rthit ) {
	  
	if ( ligstack == -268435455L ) 
	{
	  incr ( mem [mainp ].hh.b1 ) ;
	  rthit = false ;
	} 
      } 
      if ( eqtb [29354 ].cint > 0 ) 
      tmpk2 = getautokern ( mainf , 256 , curl ) ;
      else tmpk2 = -268435455L ;
      if ( tmpk2 == -268435455L ) 
      {
	mem [curq ].hh .v.RH = mainp ;
	curlist .tailfield = mainp ;
	ligaturepresent = false ;
      } 
      else {
	  
	mem [curq ].hh .v.RH = tmpk2 ;
	mem [tmpk2 ].hh .v.RH = mainp ;
	curlist .tailfield = mainp ;
	ligaturepresent = false ;
      } 
    } 
    if ( insdisc ) 
    {
      insdisc = false ;
      if ( curlist .modefield > 0 ) 
      {
	mem [curlist .tailfield ].hh .v.RH = newdisc () ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
    } 
  } 
  lab90: if ( ligstack == -268435455L ) 
  goto lab21 ;
  curq = curlist .tailfield ;
  curl = mem [ligstack ].hh.b1 ;
  lab91: if ( ! ( ligstack >= himemmin ) ) 
  goto lab95 ;
  lab92: if ( ( effectivechar ( false , mainf , curchr ) > fontec [mainf ]) 
  || ( effectivechar ( false , mainf , curchr ) < fontbc [mainf ]) ) 
  {
    charwarning ( mainf , curchr ) ;
    {
      mem [ligstack ].hh .v.RH = avail ;
      avail = ligstack ;
	;
#ifdef STAT
      decr ( dynused ) ;
#endif /* STAT */
    } 
    goto lab60 ;
  } 
  maini = effectivecharinfo ( mainf , curl ) ;
  if ( ! ( maini .b0 > 0 ) ) 
  {
    charwarning ( mainf , curchr ) ;
    {
      mem [ligstack ].hh .v.RH = avail ;
      avail = ligstack ;
	;
#ifdef STAT
      decr ( dynused ) ;
#endif /* STAT */
    } 
    goto lab60 ;
  } 
  mem [curlist .tailfield ].hh .v.RH = ligstack ;
  curlist .tailfield = ligstack ;
  lab100: getnext () ;
  if ( curcmd == 11 ) 
  goto lab101 ;
  if ( curcmd == 12 ) 
  goto lab101 ;
  if ( curcmd == 68 ) 
  goto lab101 ;
  xtoken () ;
  if ( curcmd == 11 ) 
  goto lab101 ;
  if ( curcmd == 12 ) 
  goto lab101 ;
  if ( curcmd == 68 ) 
  goto lab101 ;
  if ( curcmd == 16 ) 
  {
    scancharnum () ;
    curchr = curval ;
    goto lab101 ;
  } 
  if ( curcmd == 65 ) 
  bchar = 256 ;
  curr = bchar ;
  ligstack = -268435455L ;
  goto lab110 ;
  lab101: mains = eqtb [28506 + curchr ].hh .v.RH ;
  if ( mains == 1000 ) 
  curlist .auxfield .hh .v.LH = 1000 ;
  else if ( mains < 1000 ) 
  {
    if ( mains > 0 ) 
    curlist .auxfield .hh .v.LH = mains ;
  } 
  else if ( curlist .auxfield .hh .v.LH < 1000 ) 
  curlist .auxfield .hh .v.LH = 1000 ;
  else curlist .auxfield .hh .v.LH = mains ;
  {
    ligstack = avail ;
    if ( ligstack == -268435455L ) 
    ligstack = getavail () ;
    else {
	
      avail = mem [ligstack ].hh .v.RH ;
      mem [ligstack ].hh .v.RH = -268435455L ;
	;
#ifdef STAT
      incr ( dynused ) ;
#endif /* STAT */
    } 
  } 
  mem [ligstack ].hh.b0 = mainf ;
  curr = curchr ;
  mem [ligstack ].hh.b1 = curr ;
  if ( curr == falsebchar ) 
  curr = 256 ;
  lab110: tmpk1 = getautokern ( mainf , curl , curr ) ;
  if ( tmpk1 != -268435455L ) 
  {
    if ( curl < 256 ) 
    {
      if ( mem [curq ].hh .v.RH > -268435455L ) {
	  
	if ( mem [curlist .tailfield ].hh.b1 == hyphenchar [mainf ]) 
	insdisc = true ;
      } 
      if ( ligaturepresent ) 
      {
	mainp = newligature ( mainf , curl , mem [curq ].hh .v.RH ) ;
	if ( lfthit ) 
	{
	  mem [mainp ].hh.b1 = 2 ;
	  lfthit = false ;
	} 
	if ( rthit ) {
	    
	  if ( ligstack == -268435455L ) 
	  {
	    incr ( mem [mainp ].hh.b1 ) ;
	    rthit = false ;
	  } 
	} 
	if ( eqtb [29354 ].cint > 0 ) 
	tmpk2 = getautokern ( mainf , 256 , curl ) ;
	else tmpk2 = -268435455L ;
	if ( tmpk2 == -268435455L ) 
	{
	  mem [curq ].hh .v.RH = mainp ;
	  curlist .tailfield = mainp ;
	  ligaturepresent = false ;
	} 
	else {
	    
	  mem [curq ].hh .v.RH = tmpk2 ;
	  mem [tmpk2 ].hh .v.RH = mainp ;
	  curlist .tailfield = mainp ;
	  ligaturepresent = false ;
	} 
      } 
      if ( insdisc ) 
      {
	insdisc = false ;
	if ( curlist .modefield > 0 ) 
	{
	  mem [curlist .tailfield ].hh .v.RH = newdisc () ;
	  curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	} 
      } 
    } 
    savetail = curlist .tailfield ;
    {
      mem [curlist .tailfield ].hh .v.RH = tmpk1 ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    goto lab90 ;
  } 
  if ( ( ( maini .b2 ) % 4 ) != 1 ) 
  goto lab80 ;
  if ( curr == 256 ) 
  goto lab80 ;
  maink = ligkernbase [mainf ]+ maini .b3 ;
  mainj = fontinfo [maink ].qqqq ;
  if ( mainj .b0 <= 128 ) 
  goto lab112 ;
  maink = ligkernbase [mainf ]+ 256 * mainj .b2 + mainj .b3 + 32768L - 256 * 
  ( 128 ) ;
  lab111: mainj = fontinfo [maink ].qqqq ;
  lab112: if ( mainj .b1 == curr ) {
      
    if ( mainj .b0 <= 128 ) 
    {
      if ( mainj .b2 >= 128 ) 
      {
	if ( curl < 256 ) 
	{
	  if ( mem [curq ].hh .v.RH > -268435455L ) {
	      
	    if ( mem [curlist .tailfield ].hh.b1 == hyphenchar [mainf ]) 
	    insdisc = true ;
	  } 
	  if ( ligaturepresent ) 
	  {
	    mainp = newligature ( mainf , curl , mem [curq ].hh .v.RH ) ;
	    if ( lfthit ) 
	    {
	      mem [mainp ].hh.b1 = 2 ;
	      lfthit = false ;
	    } 
	    if ( rthit ) {
		
	      if ( ligstack == -268435455L ) 
	      {
		incr ( mem [mainp ].hh.b1 ) ;
		rthit = false ;
	      } 
	    } 
	    if ( eqtb [29354 ].cint > 0 ) 
	    tmpk2 = getautokern ( mainf , 256 , curl ) ;
	    else tmpk2 = -268435455L ;
	    if ( tmpk2 == -268435455L ) 
	    {
	      mem [curq ].hh .v.RH = mainp ;
	      curlist .tailfield = mainp ;
	      ligaturepresent = false ;
	    } 
	    else {
		
	      mem [curq ].hh .v.RH = tmpk2 ;
	      mem [tmpk2 ].hh .v.RH = mainp ;
	      curlist .tailfield = mainp ;
	      ligaturepresent = false ;
	    } 
	  } 
	  if ( insdisc ) 
	  {
	    insdisc = false ;
	    if ( curlist .modefield > 0 ) 
	    {
	      mem [curlist .tailfield ].hh .v.RH = newdisc () ;
	      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	    } 
	  } 
	} 
	{
	  mem [curlist .tailfield ].hh .v.RH = newkern ( fontinfo [kernbase 
	  [mainf ]+ 256 * mainj .b2 + mainj .b3 ].cint ) ;
	  curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	} 
	goto lab90 ;
      } 
      if ( curl == 256 ) 
      lfthit = true ;
      else if ( ligstack == -268435455L ) 
      rthit = true ;
      {
	if ( interrupt != 0 ) 
	pauseforinstructions () ;
      } 
      switch ( mainj .b2 ) 
      {case 1 : 
      case 5 : 
	{
	  curl = mainj .b3 ;
	  maini = fontinfo [charbase [mainf ]+ effectivechar ( true , mainf 
	  , curl ) ].qqqq ;
	  ligaturepresent = true ;
	} 
	break ;
      case 2 : 
      case 6 : 
	{
	  curr = mainj .b3 ;
	  if ( ligstack == -268435455L ) 
	  {
	    ligstack = newligitem ( curr ) ;
	    bchar = 256 ;
	  } 
	  else if ( ( ligstack >= himemmin ) ) 
	  {
	    mainp = ligstack ;
	    ligstack = newligitem ( curr ) ;
	    mem [ligstack + 1 ].hh .v.RH = mainp ;
	  } 
	  else mem [ligstack ].hh.b1 = curr ;
	} 
	break ;
      case 3 : 
	{
	  curr = mainj .b3 ;
	  mainp = ligstack ;
	  ligstack = newligitem ( curr ) ;
	  mem [ligstack ].hh .v.RH = mainp ;
	} 
	break ;
      case 7 : 
      case 11 : 
	{
	  if ( curl < 256 ) 
	  {
	    if ( mem [curq ].hh .v.RH > -268435455L ) {
		
	      if ( mem [curlist .tailfield ].hh.b1 == hyphenchar [mainf ]) 
	      insdisc = true ;
	    } 
	    if ( ligaturepresent ) 
	    {
	      mainp = newligature ( mainf , curl , mem [curq ].hh .v.RH ) ;
	      if ( lfthit ) 
	      {
		mem [mainp ].hh.b1 = 2 ;
		lfthit = false ;
	      } 
	      if ( false ) {
		  
		if ( ligstack == -268435455L ) 
		{
		  incr ( mem [mainp ].hh.b1 ) ;
		  rthit = false ;
		} 
	      } 
	      if ( eqtb [29354 ].cint > 0 ) 
	      tmpk2 = getautokern ( mainf , 256 , curl ) ;
	      else tmpk2 = -268435455L ;
	      if ( tmpk2 == -268435455L ) 
	      {
		mem [curq ].hh .v.RH = mainp ;
		curlist .tailfield = mainp ;
		ligaturepresent = false ;
	      } 
	      else {
		  
		mem [curq ].hh .v.RH = tmpk2 ;
		mem [tmpk2 ].hh .v.RH = mainp ;
		curlist .tailfield = mainp ;
		ligaturepresent = false ;
	      } 
	    } 
	    if ( insdisc ) 
	    {
	      insdisc = false ;
	      if ( curlist .modefield > 0 ) 
	      {
		mem [curlist .tailfield ].hh .v.RH = newdisc () ;
		curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	      } 
	    } 
	  } 
	  curq = curlist .tailfield ;
	  curl = mainj .b3 ;
	  maini = fontinfo [charbase [mainf ]+ effectivechar ( true , mainf 
	  , curl ) ].qqqq ;
	  ligaturepresent = true ;
	} 
	break ;
	default: 
	{
	  curl = mainj .b3 ;
	  ligaturepresent = true ;
	  if ( ligstack == -268435455L ) 
	  goto lab80 ;
	  else goto lab91 ;
	} 
	break ;
      } 
      if ( mainj .b2 > 4 ) {
	  
	if ( mainj .b2 != 7 ) 
	goto lab80 ;
      } 
      if ( curl < 256 ) 
      goto lab110 ;
      maink = bcharlabel [mainf ];
      goto lab111 ;
    } 
  } 
  if ( mainj .b0 == 0 ) 
  incr ( maink ) ;
  else {
      
    if ( mainj .b0 >= 128 ) 
    goto lab80 ;
    maink = maink + mainj .b0 + 1 ;
  } 
  goto lab111 ;
  lab95: mainp = mem [ligstack + 1 ].hh .v.RH ;
  if ( mainp > -268435455L ) 
  {
    mem [curlist .tailfield ].hh .v.RH = mainp ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  tempptr = ligstack ;
  ligstack = mem [tempptr ].hh .v.RH ;
  freenode ( tempptr , 2 ) ;
  maini = fontinfo [charbase [mainf ]+ effectivechar ( true , mainf , curl 
  ) ].qqqq ;
  ligaturepresent = true ;
  if ( ligstack == -268435455L ) {
      
    if ( mainp > -268435455L ) 
    goto lab100 ;
    else curr = bchar ;
  } 
  else curr = mem [ligstack ].hh.b1 ;
  goto lab110 ;
  lab120: if ( eqtb [26640 ].hh .v.RH == membot ) 
  {
    {
      mainp = fontglue [eqtb [27689 ].hh .v.RH ];
      if ( mainp == -268435455L ) 
      {
	mainp = newspec ( membot ) ;
	maink = parambase [eqtb [27689 ].hh .v.RH ]+ 2 ;
	mem [mainp + 1 ].cint = fontinfo [maink ].cint ;
	mem [mainp + 2 ].cint = fontinfo [maink + 1 ].cint ;
	mem [mainp + 3 ].cint = fontinfo [maink + 2 ].cint ;
	fontglue [eqtb [27689 ].hh .v.RH ]= mainp ;
      } 
    } 
    tempptr = newglue ( mainp ) ;
  } 
  else tempptr = newparamglue ( 12 ) ;
  if ( eqtb [29353 ].cint > 0 ) 
  adjustinterwordglue ( curlist .tailfield , tempptr ) ;
  mem [curlist .tailfield ].hh .v.RH = tempptr ;
  curlist .tailfield = tempptr ;
  goto lab60 ;
} 
void 
giveerrhelp ( void ) 
{
  giveerrhelp_regmem 
  tokenshow ( eqtb [27167 ].hh .v.RH ) ;
} 
boolean 
openfmtfile ( void ) 
{
  /* 40 10 */ register boolean Result; openfmtfile_regmem 
  integer j  ;
  j = curinput .locfield ;
  if ( buffer [curinput .locfield ]== 38 ) 
  {
    incr ( curinput .locfield ) ;
    j = curinput .locfield ;
    buffer [last ]= 32 ;
    while ( buffer [j ]!= 32 ) incr ( j ) ;
    packbufferedname ( 0 , curinput .locfield , j - 1 ) ;
    if ( wopenin ( fmtfile ) ) 
    goto lab40 ;
    Fputs ( stdout ,  "Sorry, I can't find the format `" ) ;
    fputs ( stringcast ( nameoffile + 1 ) , stdout ) ;
    Fputs ( stdout ,  "'; will try `" ) ;
    fputs ( TEXformatdefault + 1 , stdout ) ;
    fprintf ( stdout , "%s\n",  "'." ) ;
    fflush ( stdout ) ;
  } 
  packbufferedname ( formatdefaultlength - 4 , 1 , 0 ) ;
  if ( ! wopenin ( fmtfile ) ) 
  {
    ;
    Fputs ( stdout ,  "I can't find the format file `" ) ;
    fputs ( TEXformatdefault + 1 , stdout ) ;
    fprintf ( stdout , "%s\n",  "'!" ) ;
    Result = false ;
    return Result ;
  } 
  lab40: curinput .locfield = j ;
  Result = true ;
  return Result ;
} 
void 
closefilesandterminate ( void ) 
{
  /* 30 31 */ closefilesandterminate_regmem 
  integer a, b, c, i, j, k, l  ;
  boolean isroot  ;
  boolean isnames  ;
  integer root, outlines, threads, namestree, dests  ;
  integer xrefoffsetwidth, nameshead, namestail  ;
  {register integer for_end; k = 0 ;for_end = 15 ; if ( k <= for_end) do 
    if ( writeopen [k ]) 
    aclose ( writefile [k ]) ;
  while ( k++ < for_end ) ;} 
	;
#ifdef STAT
  if ( eqtb [29305 ].cint > 0 ) {
      
    if ( logopened ) 
    {
      { putc ( ' ' ,  logfile );  putc ( '\n',  logfile ); }
      fprintf ( logfile , "%s%s\n",  "Here is how much of TeX's memory" , " you used:" ) 
      ;
      fprintf ( logfile , "%c%ld%s",  ' ' , (long)strptr - initstrptr , " string" ) ;
      if ( strptr != initstrptr + 1 ) 
      putc ( 's' ,  logfile );
      fprintf ( logfile , "%s%ld\n",  " out of " , (long)maxstrings - initstrptr ) ;
      fprintf ( logfile , "%c%ld%s%ld\n",  ' ' , (long)poolptr - initpoolptr ,       " string characters out of " , (long)poolsize - initpoolptr ) ;
      fprintf ( logfile , "%c%ld%s%ld\n",  ' ' , (long)lomemmax - memmin + memend - himemmin + 2 ,       " words of memory out of " , (long)memend + 1 - memmin ) ;
      fprintf ( logfile , "%c%ld%s%ld%c%ld\n",  ' ' , (long)cscount ,       " multiletter control sequences out of " , (long)15000 , '+' , (long)hashextra ) ;
      fprintf ( logfile , "%c%ld%s%ld%s",  ' ' , (long)fmemptr , " words of font info for " , (long)fontptr -       0 , " font" ) ;
      if ( fontptr != 1 ) 
      putc ( 's' ,  logfile );
      fprintf ( logfile , "%s%ld%s%ld\n",  ", out of " , (long)fontmemsize , " for " , (long)fontmax - 0 ) 
      ;
      fprintf ( logfile , "%c%ld%s",  ' ' , (long)hyphcount , " hyphenation exception" ) ;
      if ( hyphcount != 1 ) 
      putc ( 's' ,  logfile );
      fprintf ( logfile , "%s%ld\n",  " out of " , (long)hyphsize ) ;
      fprintf ( logfile , "%c%ld%s%ld%s%ld%s%ld%s%ld%s%ld%s%ld%s%ld%s%ld%s%ld%c\n",  ' ' , (long)maxinstack , "i," , (long)maxneststack , "n," ,       (long)maxparamstack , "p," , (long)maxbufstack + 1 , "b," , (long)maxsavestack + 6 ,       "s stack positions out of " , (long)stacksize , "i," , (long)nestsize , "n," ,       (long)paramsize , "p," , (long)bufsize , "b," , (long)savesize , 's' ) ;
    } 
  } 
#endif /* STAT */
  if ( ! fixedpdfoutputset ) 
  fixpdfoutput () ;
  if ( fixedpdfoutput > 0 ) 
  {
    if ( history == 3 ) 
    {
      removepdffile () ;
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 264 ) ;
	print ( 1702 ) ;
      } 
    } 
    else {
	
      if ( totalpages == 0 ) 
      {
	printnl ( 991 ) ;
	if ( pdfgone > 0 ) 
	garbagewarning () ;
      } 
      else {
	  
	if ( fixedpdfdraftmode == 0 ) 
	{
	  pdfflush () ;
	  if ( totalpages % 6 != 0 ) 
	  objtab [pdflastpages ].int0 = totalpages % 6 ;
	  flushjbig2page0objects () ;
	  k = headtab [1 ];
	  while ( objtab [k ].int4 == 0 ) {
	      
	    pdfwarning ( 1188 , 1193 , false , false ) ;
	    printint ( objtab [k ].int0 ) ;
	    print ( 1194 ) ;
	    println () ;
	    println () ;
	    k = objtab [k ].int1 ;
	  } 
	  headtab [1 ]= k ;
	  k = headtab [1 ];
	  l = 0 ;
	  do {
	      i = objtab [k ].int1 ;
	    objtab [k ].int1 = l ;
	    l = k ;
	    k = i ;
	  } while ( ! ( k == 0 ) ) ;
	  headtab [1 ]= l ;
	  k = headtab [2 ];
	  pagestail = k ;
	  l = 0 ;
	  do {
	      i = objtab [k ].int1 ;
	    objtab [k ].int1 = l ;
	    l = k ;
	    k = i ;
	  } while ( ! ( k == 0 ) ) ;
	  headtab [2 ]= l ;
	  k = headtab [5 ];
	  while ( k != 0 ) {
	      
	    pdffixdest ( k ) ;
	    k = objtab [k ].int1 ;
	  } 
	  {register integer for_end; k = 1 ;for_end = fontptr ; if ( k <= 
	  for_end) do 
	    if ( fontused [k ]&& hasfmentry ( k ) && ( pdffontnum [k ]< 0 
	    ) ) 
	    {
	      i = - (integer) pdffontnum [k ];
	      pdfassert ( pdffontnum [i ]> 0 ) ;
	      {register integer for_end; j = 0 ;for_end = 255 ; if ( j <= 
	      for_end) do 
		if ( pdfcharmarked ( k , j ) ) 
		pdfmarkchar ( i , j ) ;
	      while ( j++ < for_end ) ;} 
	      if ( ( ( strstart [pdffontattr [i ]+ 1 ]- strstart [
	      pdffontattr [i ]]) == 0 ) && ( ( strstart [pdffontattr [k ]
	      + 1 ]- strstart [pdffontattr [k ]]) != 0 ) ) 
	      pdffontattr [i ]= pdffontattr [k ];
	      else if ( ( ( strstart [pdffontattr [k ]+ 1 ]- strstart [
	      pdffontattr [k ]]) == 0 ) && ( ( strstart [pdffontattr [i ]
	      + 1 ]- strstart [pdffontattr [i ]]) != 0 ) ) 
	      pdffontattr [k ]= pdffontattr [i ];
	      else if ( ( ( strstart [pdffontattr [i ]+ 1 ]- strstart [
	      pdffontattr [i ]]) != 0 ) && ( ( strstart [pdffontattr [k ]
	      + 1 ]- strstart [pdffontattr [k ]]) != 0 ) && ! streqstr ( 
	      pdffontattr [i ], pdffontattr [k ]) ) 
	      {
		pdfwarning ( 1195 , 1196 , false , false ) ;
		printfontidentifier ( i ) ;
		print ( 1197 ) ;
		printfontidentifier ( k ) ;
		print ( 1198 ) ;
		printfontidentifier ( i ) ;
		println () ;
		println () ;
	      } 
	    } 
	  while ( k++ < for_end ) ;} 
	  fixedgentounicode = eqtb [29356 ].cint ;
	  k = headtab [3 ];
	  while ( k != 0 ) {
	      
	    f = objtab [k ].int0 ;
	    pdfassert ( pdffontnum [f ]> 0 ) ;
	    dopdffont ( k , f ) ;
	    k = objtab [k ].int1 ;
	  } 
	  writefontstuff () ;
	  a = sysobjptr + 1 ;
	  l = headtab [2 ];
	  k = headtab [1 ];
	  b = 0 ;
	  do {
	      i = 0 ;
	    c = 0 ;
	    if ( objtab [l ].int1 == 0 ) 
	    isroot = true ;
	    else isroot = false ;
	    do {
		if ( ! isroot ) 
	      {
		if ( i % 6 == 0 ) 
		{
		  pdflastpages = pdfnewobjnum () ;
		  if ( c == 0 ) 
		  c = pdflastpages ;
		  objtab [pagestail ].int1 = pdflastpages ;
		  pagestail = pdflastpages ;
		  objtab [pdflastpages ].int1 = 0 ;
		  objtab [pdflastpages ].int0 = objtab [l ].int0 ;
		} 
		else objtab [pdflastpages ].int0 = objtab [pdflastpages ]
		.int0 + objtab [l ].int0 ;
	      } 
	      pdfbegindict ( l , 1 ) ;
	      {
		pdfprint ( 1199 ) ;
		{
		  {
		    if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		    pdfosgetosbuf ( 1 ) ;
		    else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		    overflow ( 999 , pdfopbufsize ) ;
		    else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		    pdfflush () ;
		  } 
		  {
		    pdfbuf [pdfptr ]= 10 ;
		    incr ( pdfptr ) ;
		  } 
		} 
	      } 
	      pdfintentryln ( 1183 , objtab [l ].int0 ) ;
	      if ( ! isroot ) 
	      pdfindirectln ( 1158 , pdflastpages ) ;
	      pdfprint ( 1200 ) ;
	      j = 0 ;
	      do {
		  pdfprintint ( k ) ;
		pdfprint ( 1143 ) ;
		k = objtab [k ].int1 ;
		incr ( j ) ;
	      } while ( ! ( ( ( l < a ) && ( j == objtab [l ].int0 ) ) || ( 
	      k == 0 ) || ( ( k == b ) && ( b != 0 ) ) || ( j == 6 ) ) ) ;
	      removelastspace () ;
	      {
		pdfprint ( 93 ) ;
		{
		  {
		    if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		    pdfosgetosbuf ( 1 ) ;
		    else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		    overflow ( 999 , pdfopbufsize ) ;
		    else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		    pdfflush () ;
		  } 
		  {
		    pdfbuf [pdfptr ]= 10 ;
		    incr ( pdfptr ) ;
		  } 
		} 
	      } 
	      if ( k == 0 ) 
	      {
		k = headtab [2 ];
		headtab [2 ]= 0 ;
	      } 
	      if ( isroot && ( eqtb [27168 ].hh .v.RH != -268435455L ) ) 
	      pdfprinttoksln ( eqtb [27168 ].hh .v.RH ) ;
	      pdfenddict () ;
	      incr ( i ) ;
	      l = objtab [l ].int1 ;
	    } while ( ! ( ( l == c ) ) ) ;
	    b = c ;
	    if ( l == 0 ) 
	    goto lab30 ;
	  } while ( ! ( false ) ) ;
	  lab30: ;
	  if ( pdffirstoutline != 0 ) 
	  {
	    pdfnewdict ( 0 , 0 , 1 ) ;
	    outlines = objptr ;
	    l = pdffirstoutline ;
	    k = 0 ;
	    do {
		incr ( k ) ;
	      a = opensubentries ( l ) ;
	      if ( objtab [l ].int0 > 0 ) 
	      k = k + a ;
	      pdfmem [objtab [l ].int4 + 1 ]= objptr ;
	      l = pdfmem [objtab [l ].int4 + 3 ];
	    } while ( ! ( l == 0 ) ) ;
	    {
	      pdfprint ( 1180 ) ;
	      {
		{
		  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfosgetosbuf ( 1 ) ;
		  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		  overflow ( 999 , pdfopbufsize ) ;
		  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfflush () ;
		} 
		{
		  pdfbuf [pdfptr ]= 10 ;
		  incr ( pdfptr ) ;
		} 
	      } 
	    } 
	    pdfindirectln ( 1181 , pdffirstoutline ) ;
	    pdfindirectln ( 1182 , pdflastoutline ) ;
	    pdfintentryln ( 1183 , k ) ;
	    pdfenddict () ;
	    k = headtab [4 ];
	    while ( k != 0 ) {
		
	      if ( pdfmem [objtab [k ].int4 + 1 ]== pdfparentoutline ) 
	      {
		if ( pdfmem [objtab [k ].int4 + 2 ]== 0 ) 
		pdffirstoutline = k ;
		if ( pdfmem [objtab [k ].int4 + 3 ]== 0 ) 
		pdflastoutline = k ;
	      } 
	      pdfbegindict ( k , 1 ) ;
	      pdfindirectln ( 1184 , pdfmem [objtab [k ].int4 ]) ;
	      pdfindirectln ( 65 , pdfmem [objtab [k ].int4 + 6 ]) ;
	      if ( pdfmem [objtab [k ].int4 + 1 ]!= 0 ) 
	      pdfindirectln ( 1158 , pdfmem [objtab [k ].int4 + 1 ]) ;
	      if ( pdfmem [objtab [k ].int4 + 2 ]!= 0 ) 
	      pdfindirectln ( 1185 , pdfmem [objtab [k ].int4 + 2 ]) ;
	      if ( pdfmem [objtab [k ].int4 + 3 ]!= 0 ) 
	      pdfindirectln ( 1186 , pdfmem [objtab [k ].int4 + 3 ]) ;
	      if ( pdfmem [objtab [k ].int4 + 4 ]!= 0 ) 
	      pdfindirectln ( 1181 , pdfmem [objtab [k ].int4 + 4 ]) ;
	      if ( pdfmem [objtab [k ].int4 + 5 ]!= 0 ) 
	      pdfindirectln ( 1182 , pdfmem [objtab [k ].int4 + 5 ]) ;
	      if ( objtab [k ].int0 != 0 ) 
	      pdfintentryln ( 1183 , objtab [k ].int0 ) ;
	      if ( pdfmem [objtab [k ].int4 + 7 ]!= 0 ) 
	      {
		pdfprinttoksln ( pdfmem [objtab [k ].int4 + 7 ]) ;
		{
		  deletetokenref ( pdfmem [objtab [k ].int4 + 7 ]) ;
		  pdfmem [objtab [k ].int4 + 7 ]= -268435455L ;
		} 
	      } 
	      pdfenddict () ;
	      k = objtab [k ].int1 ;
	    } 
	  } 
	  else outlines = 0 ;
	  if ( pdfdestnamesptr == 0 ) 
	  {
	    dests = 0 ;
	    goto lab31 ;
	  } 
	  sortdestnames ( 0 , pdfdestnamesptr - 1 ) ;
	  nameshead = 0 ;
	  namestail = 0 ;
	  k = 0 ;
	  isnames = true ;
	  b = 0 ;
	  do {
	      do { pdfcreateobj ( 0 , 0 ) ;
	      l = objptr ;
	      if ( b == 0 ) 
	      b = l ;
	      if ( nameshead == 0 ) 
	      {
		nameshead = l ;
		namestail = l ;
	      } 
	      else {
		  
		objtab [namestail ].int1 = l ;
		namestail = l ;
	      } 
	      objtab [namestail ].int1 = 0 ;
	      pdfbegindict ( l , 1 ) ;
	      j = 0 ;
	      if ( isnames ) 
	      {
		objtab [l ].int0 = destnames [k ].objname ;
		pdfprint ( 1202 ) ;
		do {
		    pdfprintstr ( destnames [k ].objname ) ;
		  {
		    {
		      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		      pdfosgetosbuf ( 1 ) ;
		      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		      overflow ( 999 , pdfopbufsize ) ;
		      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		      pdfflush () ;
		    } 
		    {
		      pdfbuf [pdfptr ]= 32 ;
		      incr ( pdfptr ) ;
		    } 
		  } 
		  pdfprintint ( destnames [k ].objnum ) ;
		  pdfprint ( 1143 ) ;
		  incr ( j ) ;
		  incr ( k ) ;
		} while ( ! ( ( j == 6 ) || ( k == pdfdestnamesptr ) ) ) ;
		removelastspace () ;
		{
		  pdfprint ( 93 ) ;
		  {
		    {
		      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		      pdfosgetosbuf ( 1 ) ;
		      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		      overflow ( 999 , pdfopbufsize ) ;
		      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		      pdfflush () ;
		    } 
		    {
		      pdfbuf [pdfptr ]= 10 ;
		      incr ( pdfptr ) ;
		    } 
		  } 
		} 
		objtab [l ].int4 = destnames [k - 1 ].objname ;
		if ( k == pdfdestnamesptr ) 
		{
		  isnames = false ;
		  k = nameshead ;
		  b = 0 ;
		} 
	      } 
	      else {
		  
		objtab [l ].int0 = objtab [k ].int0 ;
		pdfprint ( 1200 ) ;
		do {
		    pdfprintint ( k ) ;
		  pdfprint ( 1143 ) ;
		  incr ( j ) ;
		  objtab [l ].int4 = objtab [k ].int4 ;
		  k = objtab [k ].int1 ;
		} while ( ! ( ( j == 6 ) || ( k == b ) || ( objtab [k ].int1 
		== 0 ) ) ) ;
		removelastspace () ;
		{
		  pdfprint ( 93 ) ;
		  {
		    {
		      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		      pdfosgetosbuf ( 1 ) ;
		      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		      overflow ( 999 , pdfopbufsize ) ;
		      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		      pdfflush () ;
		    } 
		    {
		      pdfbuf [pdfptr ]= 10 ;
		      incr ( pdfptr ) ;
		    } 
		  } 
		} 
		if ( k == b ) 
		b = 0 ;
	      } 
	      pdfprint ( 1203 ) ;
	      pdfprintstr ( objtab [l ].int0 ) ;
	      {
		{
		  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfosgetosbuf ( 1 ) ;
		  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		  overflow ( 999 , pdfopbufsize ) ;
		  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfflush () ;
		} 
		{
		  pdfbuf [pdfptr ]= 32 ;
		  incr ( pdfptr ) ;
		} 
	      } 
	      pdfprintstr ( objtab [l ].int4 ) ;
	      {
		pdfprint ( 93 ) ;
		{
		  {
		    if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		    pdfosgetosbuf ( 1 ) ;
		    else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		    overflow ( 999 , pdfopbufsize ) ;
		    else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		    pdfflush () ;
		  } 
		  {
		    pdfbuf [pdfptr ]= 10 ;
		    incr ( pdfptr ) ;
		  } 
		} 
	      } 
	      pdfenddict () ;
	    } while ( ! ( b == 0 ) ) ;
	    if ( k == l ) 
	    {
	      dests = l ;
	      goto lab31 ;
	    } 
	  } while ( ! ( false ) ) ;
	  lab31: if ( ( dests != 0 ) || ( pdfnamestoks != -268435455L ) ) 
	  {
	    pdfnewdict ( 0 , 0 , 1 ) ;
	    if ( ( dests != 0 ) ) 
	    pdfindirectln ( 1201 , dests ) ;
	    if ( pdfnamestoks != -268435455L ) 
	    {
	      pdfprinttoksln ( pdfnamestoks ) ;
	      {
		deletetokenref ( pdfnamestoks ) ;
		pdfnamestoks = -268435455L ;
	      } 
	    } 
	    pdfenddict () ;
	    namestree = objptr ;
	  } 
	  else namestree = 0 ;
	  if ( headtab [9 ]!= 0 ) 
	  {
	    pdfnewobj ( 0 , 0 , 1 ) ;
	    threads = objptr ;
	    {
	      {
		if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		pdfosgetosbuf ( 1 ) ;
		else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		overflow ( 999 , pdfopbufsize ) ;
		else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		pdfflush () ;
	      } 
	      {
		pdfbuf [pdfptr ]= 91 ;
		incr ( pdfptr ) ;
	      } 
	    } 
	    k = headtab [9 ];
	    while ( k != 0 ) {
		
	      pdfprintint ( k ) ;
	      pdfprint ( 1143 ) ;
	      k = objtab [k ].int1 ;
	    } 
	    removelastspace () ;
	    {
	      pdfprint ( 93 ) ;
	      {
		{
		  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfosgetosbuf ( 1 ) ;
		  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		  overflow ( 999 , pdfopbufsize ) ;
		  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfflush () ;
		} 
		{
		  pdfbuf [pdfptr ]= 10 ;
		  incr ( pdfptr ) ;
		} 
	      } 
	    } 
	    pdfendobj () ;
	    k = headtab [9 ];
	    while ( k != 0 ) {
		
	      outthread ( k ) ;
	      k = objtab [k ].int1 ;
	    } 
	  } 
	  else threads = 0 ;
	  pdfnewdict ( 0 , 0 , 1 ) ;
	  root = objptr ;
	  {
	    pdfprint ( 1204 ) ;
	    {
	      {
		if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		pdfosgetosbuf ( 1 ) ;
		else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		overflow ( 999 , pdfopbufsize ) ;
		else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		pdfflush () ;
	      } 
	      {
		pdfbuf [pdfptr ]= 10 ;
		incr ( pdfptr ) ;
	      } 
	    } 
	  } 
	  pdfindirectln ( 1205 , pdflastpages ) ;
	  if ( threads != 0 ) 
	  pdfindirectln ( 1206 , threads ) ;
	  if ( outlines != 0 ) 
	  pdfindirectln ( 1207 , outlines ) ;
	  if ( namestree != 0 ) 
	  pdfindirectln ( 1208 , namestree ) ;
	  if ( pdfcatalogtoks != -268435455L ) 
	  {
	    pdfprinttoksln ( pdfcatalogtoks ) ;
	    {
	      deletetokenref ( pdfcatalogtoks ) ;
	      pdfcatalogtoks = -268435455L ;
	    } 
	  } 
	  if ( pdfcatalogopenaction != 0 ) 
	  pdfindirectln ( 1209 , pdfcatalogopenaction ) ;
	  pdfenddict () ;
	  pdfprintinfo () ;
	  if ( pdfosenable ) 
	  {
	    pdfosswitch ( true ) ;
	    pdfoswriteobjstream () ;
	    pdfflush () ;
	    pdfosswitch ( false ) ;
	    pdfnewdict ( 0 , 0 , 0 ) ;
	    if ( ( ( objtab [sysobjptr ].int2 / ((double) 256 ) ) > 
	    16777215L ) ) 
	    xrefoffsetwidth = 5 ;
	    else if ( objtab [sysobjptr ].int2 > 16777215L ) 
	    xrefoffsetwidth = 4 ;
	    else if ( objtab [sysobjptr ].int2 > 65535L ) 
	    xrefoffsetwidth = 3 ;
	    else xrefoffsetwidth = 2 ;
	    l = 0 ;
	    objtab [l ].int2 = -2 ;
	    {register integer for_end; k = 1 ;for_end = sysobjptr ; if ( k 
	    <= for_end) do 
	      if ( ! ( objtab [k ].int2 > -1 ) ) 
	      {
		objtab [l ].int1 = k ;
		l = k ;
	      } 
	    while ( k++ < for_end ) ;} 
	    objtab [l ].int1 = 0 ;
	    {
	      pdfprint ( 1225 ) ;
	      {
		{
		  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfosgetosbuf ( 1 ) ;
		  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		  overflow ( 999 , pdfopbufsize ) ;
		  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfflush () ;
		} 
		{
		  pdfbuf [pdfptr ]= 10 ;
		  incr ( pdfptr ) ;
		} 
	      } 
	    } 
	    pdfprint ( 1226 ) ;
	    pdfprintint ( objptr + 1 ) ;
	    {
	      pdfprint ( 93 ) ;
	      {
		{
		  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfosgetosbuf ( 1 ) ;
		  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		  overflow ( 999 , pdfopbufsize ) ;
		  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfflush () ;
		} 
		{
		  pdfbuf [pdfptr ]= 10 ;
		  incr ( pdfptr ) ;
		} 
	      } 
	    } 
	    pdfintentryln ( 1227 , objptr + 1 ) ;
	    pdfprint ( 1228 ) ;
	    pdfprintint ( xrefoffsetwidth ) ;
	    {
	      pdfprint ( 1229 ) ;
	      {
		{
		  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfosgetosbuf ( 1 ) ;
		  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		  overflow ( 999 , pdfopbufsize ) ;
		  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfflush () ;
		} 
		{
		  pdfbuf [pdfptr ]= 10 ;
		  incr ( pdfptr ) ;
		} 
	      } 
	    } 
	    pdfindirectln ( 1230 , root ) ;
	    pdfindirectln ( 1231 , objptr - 1 ) ;
	    if ( pdftrailertoks != -268435455L ) 
	    {
	      pdfprinttoksln ( pdftrailertoks ) ;
	      {
		deletetokenref ( pdftrailertoks ) ;
		pdftrailertoks = -268435455L ;
	      } 
	    } 
	    if ( pdftraileridtoks != -268435455L ) 
	    printIDalt ( pdftraileridtoks ) ;
	    else printID ( outputfilename ) ;
	    {
	      {
		if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		pdfosgetosbuf ( 1 ) ;
		else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		overflow ( 999 , pdfopbufsize ) ;
		else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		pdfflush () ;
	      } 
	      {
		pdfbuf [pdfptr ]= 10 ;
		incr ( pdfptr ) ;
	      } 
	    } 
	    pdfbeginstream () ;
	    {register integer for_end; k = 0 ;for_end = sysobjptr ; if ( k 
	    <= for_end) do 
	      {
		if ( ! ( objtab [k ].int2 > -1 ) ) 
		{
		  {
		    {
		      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		      pdfosgetosbuf ( 1 ) ;
		      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		      overflow ( 999 , pdfopbufsize ) ;
		      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		      pdfflush () ;
		    } 
		    {
		      pdfbuf [pdfptr ]= 0 ;
		      incr ( pdfptr ) ;
		    } 
		  } 
		  pdfoutbytes ( objtab [k ].int1 , xrefoffsetwidth ) ;
		  {
		    {
		      if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		      pdfosgetosbuf ( 1 ) ;
		      else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		      overflow ( 999 , pdfopbufsize ) ;
		      else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		      pdfflush () ;
		    } 
		    {
		      pdfbuf [pdfptr ]= 255 ;
		      incr ( pdfptr ) ;
		    } 
		  } 
		} 
		else {
		    
		  if ( objtab [k ].int3 == -1 ) 
		  {
		    {
		      {
			if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
			pdfosgetosbuf ( 1 ) ;
			else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
			overflow ( 999 , pdfopbufsize ) ;
			else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
			pdfflush () ;
		      } 
		      {
			pdfbuf [pdfptr ]= 1 ;
			incr ( pdfptr ) ;
		      } 
		    } 
		    pdfoutbytes ( objtab [k ].int2 , xrefoffsetwidth ) ;
		    {
		      {
			if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
			pdfosgetosbuf ( 1 ) ;
			else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
			overflow ( 999 , pdfopbufsize ) ;
			else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
			pdfflush () ;
		      } 
		      {
			pdfbuf [pdfptr ]= 0 ;
			incr ( pdfptr ) ;
		      } 
		    } 
		  } 
		  else {
		      
		    {
		      {
			if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
			pdfosgetosbuf ( 1 ) ;
			else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
			overflow ( 999 , pdfopbufsize ) ;
			else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
			pdfflush () ;
		      } 
		      {
			pdfbuf [pdfptr ]= 2 ;
			incr ( pdfptr ) ;
		      } 
		    } 
		    pdfoutbytes ( objtab [k ].int2 , xrefoffsetwidth ) ;
		    {
		      {
			if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
			pdfosgetosbuf ( 1 ) ;
			else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
			overflow ( 999 , pdfopbufsize ) ;
			else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
			pdfflush () ;
		      } 
		      {
			pdfbuf [pdfptr ]= objtab [k ].int3 ;
			incr ( pdfptr ) ;
		      } 
		    } 
		  } 
		} 
	      } 
	    while ( k++ < for_end ) ;} 
	    pdfendstream () ;
	    pdfflush () ;
	  } 
	  else {
	      
	    l = 0 ;
	    objtab [l ].int2 = -2 ;
	    {register integer for_end; k = 1 ;for_end = sysobjptr ; if ( k 
	    <= for_end) do 
	      if ( ! ( objtab [k ].int2 > -1 ) ) 
	      {
		objtab [l ].int1 = k ;
		l = k ;
	      } 
	    while ( k++ < for_end ) ;} 
	    objtab [l ].int1 = 0 ;
	    pdfsaveoffset = ( pdfgone + pdfptr ) ;
	    {
	      pdfprint ( 1220 ) ;
	      {
		{
		  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfosgetosbuf ( 1 ) ;
		  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		  overflow ( 999 , pdfopbufsize ) ;
		  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfflush () ;
		} 
		{
		  pdfbuf [pdfptr ]= 10 ;
		  incr ( pdfptr ) ;
		} 
	      } 
	    } 
	    pdfprint ( 1221 ) ;
	    {
	      pdfprintint ( objptr + 1 ) ;
	      {
		{
		  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfosgetosbuf ( 1 ) ;
		  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		  overflow ( 999 , pdfopbufsize ) ;
		  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfflush () ;
		} 
		{
		  pdfbuf [pdfptr ]= 10 ;
		  incr ( pdfptr ) ;
		} 
	      } 
	    } 
	    pdfprintfwint ( objtab [0 ].int1 , 10 ) ;
	    {
	      pdfprint ( 1222 ) ;
	      {
		{
		  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfosgetosbuf ( 1 ) ;
		  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		  overflow ( 999 , pdfopbufsize ) ;
		  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfflush () ;
		} 
		{
		  pdfbuf [pdfptr ]= 10 ;
		  incr ( pdfptr ) ;
		} 
	      } 
	    } 
	    {register integer for_end; k = 1 ;for_end = objptr ; if ( k <= 
	    for_end) do 
	      {
		if ( ! ( objtab [k ].int2 > -1 ) ) 
		{
		  pdfprintfwint ( objtab [k ].int1 , 10 ) ;
		  {
		    pdfprint ( 1223 ) ;
		    {
		      {
			if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
			pdfosgetosbuf ( 1 ) ;
			else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
			overflow ( 999 , pdfopbufsize ) ;
			else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
			pdfflush () ;
		      } 
		      {
			pdfbuf [pdfptr ]= 10 ;
			incr ( pdfptr ) ;
		      } 
		    } 
		  } 
		} 
		else {
		    
		  pdfprintfwint ( objtab [k ].int2 , 10 ) ;
		  {
		    pdfprint ( 1224 ) ;
		    {
		      {
			if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
			pdfosgetosbuf ( 1 ) ;
			else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
			overflow ( 999 , pdfopbufsize ) ;
			else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
			pdfflush () ;
		      } 
		      {
			pdfbuf [pdfptr ]= 10 ;
			incr ( pdfptr ) ;
		      } 
		    } 
		  } 
		} 
	      } 
	    while ( k++ < for_end ) ;} 
	  } 
	  if ( ! pdfosenable ) 
	  {
	    {
	      pdfprint ( 1232 ) ;
	      {
		{
		  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfosgetosbuf ( 1 ) ;
		  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		  overflow ( 999 , pdfopbufsize ) ;
		  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfflush () ;
		} 
		{
		  pdfbuf [pdfptr ]= 10 ;
		  incr ( pdfptr ) ;
		} 
	      } 
	    } 
	    pdfprint ( 1233 ) ;
	    pdfintentryln ( 1227 , sysobjptr + 1 ) ;
	    pdfindirectln ( 1230 , root ) ;
	    pdfindirectln ( 1231 , sysobjptr ) ;
	    if ( pdftrailertoks != -268435455L ) 
	    {
	      pdfprinttoksln ( pdftrailertoks ) ;
	      {
		deletetokenref ( pdftrailertoks ) ;
		pdftrailertoks = -268435455L ;
	      } 
	    } 
	    if ( pdftraileridtoks != -268435455L ) 
	    printIDalt ( pdftraileridtoks ) ;
	    else printID ( outputfilename ) ;
	    {
	      pdfprint ( 1234 ) ;
	      {
		{
		  if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfosgetosbuf ( 1 ) ;
		  else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		  overflow ( 999 , pdfopbufsize ) ;
		  else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		  pdfflush () ;
		} 
		{
		  pdfbuf [pdfptr ]= 10 ;
		  incr ( pdfptr ) ;
		} 
	      } 
	    } 
	  } 
	  {
	    pdfprint ( 1235 ) ;
	    {
	      {
		if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		pdfosgetosbuf ( 1 ) ;
		else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		overflow ( 999 , pdfopbufsize ) ;
		else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		pdfflush () ;
	      } 
	      {
		pdfbuf [pdfptr ]= 10 ;
		incr ( pdfptr ) ;
	      } 
	    } 
	  } 
	  if ( pdfosenable ) 
	  {
	    pdfprintint ( objtab [sysobjptr ].int2 ) ;
	    {
	      {
		if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		pdfosgetosbuf ( 1 ) ;
		else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		overflow ( 999 , pdfopbufsize ) ;
		else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		pdfflush () ;
	      } 
	      {
		pdfbuf [pdfptr ]= 10 ;
		incr ( pdfptr ) ;
	      } 
	    } 
	  } 
	  else {
	      
	    pdfprintint ( pdfsaveoffset ) ;
	    {
	      {
		if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		pdfosgetosbuf ( 1 ) ;
		else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		overflow ( 999 , pdfopbufsize ) ;
		else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		pdfflush () ;
	      } 
	      {
		pdfbuf [pdfptr ]= 10 ;
		incr ( pdfptr ) ;
	      } 
	    } 
	  } 
	  {
	    pdfprint ( 1236 ) ;
	    {
	      {
		if ( pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		pdfosgetosbuf ( 1 ) ;
		else if ( ! pdfosmode && ( 1 > pdfbufsize ) ) 
		overflow ( 999 , pdfopbufsize ) ;
		else if ( ! pdfosmode && ( 1 + pdfptr > pdfbufsize ) ) 
		pdfflush () ;
	      } 
	      {
		pdfbuf [pdfptr ]= 10 ;
		incr ( pdfptr ) ;
	      } 
	    } 
	  } 
	  pdfflush () ;
	  printnl ( 992 ) ;
	  printfilename ( 0 , outputfilename , 0 ) ;
	  print ( 286 ) ;
	  printint ( totalpages ) ;
	  print ( 994 ) ;
	  if ( totalpages != 1 ) 
	  printchar ( 115 ) ;
	  print ( 995 ) ;
	  printint ( ( pdfgone + pdfptr ) ) ;
	  print ( 996 ) ;
	} 
	libpdffinish () ;
	if ( fixedpdfdraftmode == 0 ) 
	bclose ( pdffile ) ;
	else pdfwarning ( 0 , 1187 , true , true ) ;
      } 
      if ( logopened ) 
      {
	putc ('\n',  logfile );
	fprintf ( logfile , "%s\n",  "PDF statistics:" ) ;
	fprintf ( logfile , "%c%ld%s%ld%s%ld%c\n",  ' ' , (long)objptr , " PDF objects out of " , (long)objtabsize         , " (max. " , (long)supobjtabsize , ')' ) ;
	if ( pdfoscntr > 0 ) 
	{
	  fprintf ( logfile , "%c%ld%s%ld%s",  ' ' , (long)( ( pdfoscntr - 1 ) * pdfosmaxobjs +           pdfosobjidx + 1 ) , " compressed objects within " , (long)pdfoscntr ,           " object stream" ) ;
	  if ( pdfoscntr > 1 ) 
	  putc ( 's' ,  logfile );
	  putc ('\n',  logfile );
	} 
	fprintf ( logfile , "%c%ld%s%ld%s%ld%c\n",  ' ' , (long)pdfdestnamesptr ,         " named destinations out of " , (long)destnamessize , " (max. " ,         (long)supdestnamessize , ')' ) ;
	fprintf ( logfile , "%c%ld%s%ld%s%ld%c\n",  ' ' , (long)pdfmemptr ,         " words of extra memory for PDF output out of " , (long)pdfmemsize ,         " (max. " , (long)suppdfmemsize , ')' ) ;
      } 
    } 
  } 
  else {
      
    while ( curs > -1 ) {
	
      if ( curs > 0 ) 
      {
	dvibuf [dviptr ]= 142 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      else {
	  
	{
	  dvibuf [dviptr ]= 140 ;
	  incr ( dviptr ) ;
	  if ( dviptr == dvilimit ) 
	  dviswap () ;
	} 
	incr ( totalpages ) ;
      } 
      decr ( curs ) ;
    } 
    if ( totalpages == 0 ) 
    printnl ( 991 ) ;
    else if ( curs != -2 ) 
    {
      {
	dvibuf [dviptr ]= 248 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      dvifour ( lastbop ) ;
      lastbop = dvioffset + dviptr - 5 ;
      dvifour ( 25400000L ) ;
      dvifour ( 473628672L ) ;
      preparemag () ;
      dvifour ( eqtb [29291 ].cint ) ;
      dvifour ( maxv ) ;
      dvifour ( maxh ) ;
      {
	dvibuf [dviptr ]= maxpush / 256 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      {
	dvibuf [dviptr ]= maxpush % 256 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      {
	dvibuf [dviptr ]= ( totalpages / 256 ) % 256 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      {
	dvibuf [dviptr ]= totalpages % 256 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      while ( fontptr > 0 ) {
	  
	if ( fontused [fontptr ]) 
	dvifontdef ( fontptr ) ;
	decr ( fontptr ) ;
      } 
      {
	dvibuf [dviptr ]= 249 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      dvifour ( lastbop ) ;
      {
	dvibuf [dviptr ]= 2 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
	;
#ifdef IPC
      k = 7 - ( ( 3 + dvioffset + dviptr ) % 4 ) ;
#endif /* IPC */
	;
#ifndef IPC
      k = 4 + ( ( dvibufsize - dviptr ) % 4 ) ;
#endif /* not IPC */
      while ( k > 0 ) {
	  
	{
	  dvibuf [dviptr ]= 223 ;
	  incr ( dviptr ) ;
	  if ( dviptr == dvilimit ) 
	  dviswap () ;
	} 
	decr ( k ) ;
      } 
      if ( dvilimit == halfbuf ) 
      writedvi ( halfbuf , dvibufsize - 1 ) ;
      if ( dviptr > ( 2147483647L - dvioffset ) ) 
      {
	curs = -2 ;
	fatalerror ( 980 ) ;
      } 
      if ( dviptr > 0 ) 
      writedvi ( 0 , dviptr - 1 ) ;
      printnl ( 992 ) ;
      printfilename ( 0 , outputfilename , 0 ) ;
      print ( 286 ) ;
      printint ( totalpages ) ;
      if ( totalpages != 1 ) 
      print ( 993 ) ;
      else print ( 994 ) ;
      print ( 995 ) ;
      printint ( dvioffset + dviptr ) ;
      print ( 996 ) ;
      bclose ( dvifile ) ;
    } 
  } 
  if ( logopened ) 
  {
    putc ('\n',  logfile );
    aclose ( logfile ) ;
    selector = selector - 2 ;
    if ( selector == 17 ) 
    {
      printnl ( 1703 ) ;
      printfilename ( 0 , texmflogname , 0 ) ;
      printchar ( 46 ) ;
    } 
  } 
  println () ;
  if ( ( editnamestart != 0 ) && ( interaction > 0 ) ) 
  calledit ( strpool , editnamestart , editnamelength , editline ) ;
} 
#ifdef TEXMF_DEBUG
void 
debughelp ( void ) 
{
  /* 888 10 */ debughelp_regmem 
  integer k, l, m, n  ;
  while ( true ) {
      
    ;
    printnl ( 1712 ) ;
    fflush ( stdout ) ;
    read ( stdin , m ) ;
    if ( m < 0 ) 
    return ;
    else if ( m == 0 ) 
    dumpcore () ;
    else {
	
      read ( stdin , n ) ;
      switch ( m ) 
      {case 1 : 
	printword ( mem [n ]) ;
	break ;
      case 2 : 
	printint ( mem [n ].hh .v.LH ) ;
	break ;
      case 3 : 
	printint ( mem [n ].hh .v.RH ) ;
	break ;
      case 4 : 
	printword ( eqtb [n ]) ;
	break ;
      case 5 : 
	{
	  printscaled ( fontinfo [n ].cint ) ;
	  printchar ( 32 ) ;
	  printint ( fontinfo [n ].qqqq .b0 ) ;
	  printchar ( 58 ) ;
	  printint ( fontinfo [n ].qqqq .b1 ) ;
	  printchar ( 58 ) ;
	  printint ( fontinfo [n ].qqqq .b2 ) ;
	  printchar ( 58 ) ;
	  printint ( fontinfo [n ].qqqq .b3 ) ;
	} 
	break ;
      case 6 : 
	printword ( savestack [n ]) ;
	break ;
      case 7 : 
	showbox ( n ) ;
	break ;
      case 8 : 
	{
	  breadthmax = 10000 ;
	  depththreshold = poolsize - poolptr - 10 ;
	  shownodelist ( n ) ;
	} 
	break ;
      case 9 : 
	showtokenlist ( n , -268435455L , 1000 ) ;
	break ;
      case 10 : 
	slowprint ( n ) ;
	break ;
      case 11 : 
	checkmem ( n > 0 ) ;
	break ;
      case 12 : 
	searchmem ( n ) ;
	break ;
      case 13 : 
	{
	  read ( stdin , l ) ;
	  printcmdchr ( n , l ) ;
	} 
	break ;
      case 14 : 
	{register integer for_end; k = 0 ;for_end = n ; if ( k <= for_end) 
	do 
	  print ( buffer [k ]) ;
	while ( k++ < for_end ) ;} 
	break ;
      case 15 : 
	{
	  fontinshortdisplay = 0 ;
	  shortdisplay ( n ) ;
	} 
	break ;
      case 16 : 
	panicking = ! panicking ;
	break ;
	default: 
	print ( 63 ) ;
	break ;
      } 
    } 
  } 
} 
#endif /* TEXMF_DEBUG */
strnumber 
getnullstr ( void ) 
{
  register strnumber Result; getnullstr_regmem 
  Result = 345 ;
  return Result ;
} 
