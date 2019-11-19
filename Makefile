CC=gcc
CXX=g++

DEBUGFLAGS = -O2 -DDISABLE_OUTLINE=1 -DPDF_PARSER_ONLY=1 

CFLAGS = $(DEBUGFLAGS) 
LDFLAGS =  $(DEBUGFLAGS) 
CXX_LINK = $(CXX) -o $@ $(LDFLAGS) 


utilsources = md5.c memory.c file.c kpseemu-c.c 

texsources = tex/pdftex0.c tex/pdftexini.c tex/pdftex-pool.c pdftexmain.c 

bibsources = bibtex.c bibtexmain.c

pdfsources = pdftexdir/avl.c pdftexdir/avlstuff.c \
		  pdftexdir/mapfile.c pdftexdir/utils.c pdftexdir/subfont.c pdftexdir/tounicode.c \
		  pdftexdir/vfpacket.c pdftexdir/writezip.c pdftexdir/writet3.c pdftexdir/writettf.c\
		  pdftexdir/writefont.c pdftexdir/writeimg.c pdftexdir/writejpg.c pdftexdir/writepng.c \
		  pdftexdir/writeenc.c pdftexdir/writet1.c pdftexdir/pkin.c pdftexdir/epdf.c pdftexdir/writejbig2.c

xpdfsources =  xpdf/FoFiBase.cc xpdf/FoFiEncodings.cc xpdf/FoFiIdentifier.cc \
    xpdf/FoFiTrueType.cc xpdf/FoFiType1.cc xpdf/FoFiType1C.cc\
	xpdf/FixedPoint.cc xpdf/gfile.cc xpdf/GHash.cc xpdf/GList.cc \
	xpdf/gmem.cc xpdf/gmempp.cc xpdf/GString.cc xpdf/AcroForm.cc \
	xpdf/PDF417Barcode.cc \
    xpdf/Annot.cc \
	xpdf/Array.cc \
	xpdf/BuiltinFont.cc \
	xpdf/BuiltinFontTables.cc \
	xpdf/CMap.cc \
	xpdf/Catalog.cc \
	xpdf/CharCodeToUnicode.cc \
	xpdf/Decrypt.cc \
	xpdf/Dict.cc \
	xpdf/Error.cc \
	xpdf/FontEncodingTables.cc \
	xpdf/Form.cc \
	xpdf/Function.cc \
	xpdf/Gfx.cc \
	xpdf/GfxFont.cc \
	xpdf/GfxState.cc \
	xpdf/GlobalParams.cc \
	xpdf/JArithmeticDecoder.cc \
	xpdf/JBIG2Stream.cc \
	xpdf/JPXStream.cc \
	xpdf/Lexer.cc \
	xpdf/Link.cc \
	xpdf/NameToCharCode.cc \
	xpdf/Object.cc \
	xpdf/OptionalContent.cc \
	xpdf/Outline.cc \
	xpdf/OutputDev.cc \
	xpdf/PDFDoc.cc \
	xpdf/PDFDocEncoding.cc \
	xpdf/PSTokenizer.cc \
	xpdf/Page.cc \
	xpdf/Parser.cc \
	xpdf/SecurityHandler.cc \
	xpdf/Stream.cc \
	xpdf/TextString.cc \
	xpdf/UnicodeMap.cc \
	xpdf/UnicodeRemapping.cc \
	xpdf/UTF8.cc \
	xpdf/XFAForm.cc \
	xpdf/XRef.cc \
	xpdf/Zoox.cc \
 	pdftexdir/pdftoepdf.cc

utilobjects = $(utilsources:.c=.o)

bibobjects = $(bibsources:.c=.o)

texobjects = $(texsources:.c=.o)

pdfobjects = $(pdfsources:.c=.o)

xpdfobjects = $(xpdfsources:.cc=.o)

pdftexlite: $(headers) $(texobjects) $(pdfobjects)  $(xpdfobjects) $(utilobjects)
	$(CXX_LINK) $(utilobjects) $(texobjects) $(pdfobjects) $(xpdfobjects) -lpng -lz -lcurl

# bibtexlite: $(headers) $(bibobjects)  $(utilobjects)
# 	$(CXX_LINK) $(utilobjects) $(bibobjects) -lcurl


$(utilobjects): %.o: %.c
	$(CC) -c $(CFLAGS) -I. -I tex/ -I pdftexdir/  $< -o $@

$(bibobjects): %.o: %.c
	$(CC) -c $(CFLAGS) -I.  $< -o $@

$(pdfobjects): %.o: %.c
	$(CC) -c $(CFLAGS) -I. -I tex/ -I pdftexdir/  $< -o $@

$(texobjects): %.o: %.c
	$(CC) -c $(CFLAGS) -I. -I tex/ -I pdftexdir/ $< -o $@

$(xpdfobjects): %.o: %.cc
	$(CC) -c $(CFLAGS) -I. -I tex/ -I pdftexdir/ -I xpdf/  $< -o $@


clean:
	rm -f depend *.o pdftexdir/*.o  pdftexdir/*.bc xpdf/*.bc xpdf/*.o cpdfetex a.out  tex/*.o  pdftexlite bibtexlite
