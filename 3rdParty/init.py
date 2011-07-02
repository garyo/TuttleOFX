#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import sys
import urllib
import subprocess
import tarfile
import zipfile


osname		= os.name.lower()
sysplatform	= sys.platform.lower()
windows		= osname == "nt" and sysplatform.startswith("win")
macos		= sysplatform.startswith("darwin")
linux		= not windows and not macos
unix		= not windows

global current_file # global variable used in dlProgress function
current_file = ''

def copytree(src, dst, symlinks=False, ignore=None):
	import os
	from shutil import copy2, copystat, Error
	names = os.listdir(src)
	if ignore is not None:
		ignored_names = ignore(src, names)
	else:
		ignored_names = set()

	if not os.path.exists(dst):
		try:
			os.makedirs(dst)
		except OSError, exc:
			# XXX - this is pretty ugly
			if "file already exists" in exc[1]:  # Windows
				pass
			elif "File exists" in exc[1]:        # Linux
				pass
			else:
				raise

	errors = []
	for name in names:
		if name in ignored_names:
			continue
		srcname = os.path.join(src, name)
		dstname = os.path.join(dst, name)
		try:
			if symlinks and os.path.islink(srcname):
				linkto = os.readlink(srcname)
				os.symlink(linkto, dstname)
			elif os.path.isdir(srcname):
				copytree(srcname, dstname, symlinks, ignore)
			else:
				copy2(srcname, dstname)
				# XXX What about devices, sockets etc.?
		except (IOError, os.error), why:
			errors.append((srcname, dstname, str(why)))
			# catch the Error from the recursive copytree so that we can
			# continue with other files
		except Error, err:
			errors.extend(err.args[0])
		try:
			copystat(src, dst)
		except WindowsError:
			# can't copy file access times on Windows
			pass
		except OSError, why:
			errors.extend((src, dst, str(why)))
		if errors:
			raise Error, errors

def dlProgress(count, blockSize, totalSize):
	pcent = int( count * blockSize * 100/totalSize )
	sys.stdout.write( '\r' + current_file + '%d%% '% pcent)
	sys.stdout.flush()

global knowExtensions
knowExtensions = {	'tar':		'tar xf',
			'tar.gz':	'tar xfz',
			'tgz':		'tar xfz',
			'tar.bz2':	'tar xfj',
			'zip':		'unzip',
			'exe':		'' }

def getKnowExtensions( filename ):
	global knowExtensions
	return [f for f in knowExtensions.keys() if filename.endswith(f)]

def uncompress(filename, ext, inNewDirectory, libname):
	
	if ext == 'tar.gz' :
		tar = tarfile.open(filename, 'r:*')
		folder = './'
		tar.extractall( folder )
		
	if ext == 'tar.gz2' :
		tar = tarfile.open(filename, 'r:*')
		folder = './'
		tar.extractall( folder )
        if ext == 'tar.bz2' :
                        tar = tarfile.open(filename, 'r:*')
                        folder = './'
                        tar.extractall( folder )
	if ext == 'zip' :
                zip = zipfile.ZipFile( filename, 'r' )
		folder = './'
		zip.extractall( folder )
		
	if ext == 'exe' :
		fileToRun = filename+'.exe'
		os.startfile( fileToRun )
	
	if not os.path.exists( os.path.join( os.getcwd(), libname)):
		os.mkdir(os.path.join( os.getcwd() ,libname))
	#p = subprocess.Popen(cmd).communicate()
	#print 'uncompress and  copy', filename[:-len(ext)-1], libname, '\n'
	copytree(filename[:-len(ext)-1], libname)
	print 'end of uncompress\n'

def getAndUncompress( libraries ):
	for libname, url, inNewDirectory in libraries:
		print '_'*80
		print '--', libname
		parts = url.split('/')
		filename = [p for p in parts if len(getKnowExtensions(p))]
		#if len(filename) == 0:
		#	print '-'*40
		#	print 'No filename with a regognize extension in "'+libname+'" url="'+url+'"'
		#	print '-'*40
		#	continue
		filename = filename[0]
		print url, ' -> ', filename
		ext = getKnowExtensions(filename)[0]
		current_file = filename
		try:
			if os.path.isfile(filename): # if not already downloaded
				print 'Already downloaded: ', filename
			else:
				urllib.urlretrieve(url, filename, dlProgress)
			dirname = filename[:-len(ext)-1]
			#if os.path.isdir(libname) or os.path.islink(libname): # if not already uncompressed
			if os.path.isdir(filename[:-len(ext)-1]) :
				print 'Already uncompressed : ', dirname
			else:
				uncompress( filename, ext, inNewDirectory, libname )
		except Exception, e:
			print 'uncompress error (', str(e), ')'

allLibs = [
		('zlib','http://prdownloads.sourceforge.net/libpng/zlib-1.2.3.tar.gz', False) if not windows else ('zlib','http://downloads.sourceforge.net/project/libpng/zlib/1.2.3/zlib123.zip', True),
		('libpng', 'http://prdownloads.sourceforge.net/libpng/libpng-1.2.41.tar.gz', False) if not windows else ('libpng','http://downloads.sourceforge.net/project/libpng/libpng12/older-releases/1.2.41/lpng1241.zip', False),
		('ilmbase', 'http://download.savannah.nongnu.org/releases/openexr/ilmbase-1.0.1.tar.gz', False),
		('openexr', 'http://download.savannah.nongnu.org/releases/openexr/openexr-1.6.1.tar.gz', False),
		('ctl', 'http://sourceforge.net/projects/ampasctl/files/ctl/ctl-1.4.1/ctl-1.4.1.tar.gz/download', False),
                ('ctl', 'http://sourceforge.net/projects/ampasctl/files/ctl/ctl-1.4.1/ctl-1.4.1.tar.gz/download', False),
		('boost', 'http://prdownloads.sourceforge.net/boost/boost_1_46_0.tar.bz2', False) if not windows else ('boost', 'http://sourceforge.net/projects/boost/files/boost/1.46.1/boost_1_46_1.zip', False),
		('freetype','http://prdownloads.sourceforge.net/freetype/freetype-2.4.3.tar.gz', False) if not windows else ('freetype','http://prdownloads.sourceforge.net/freetype/freetype-2.4.3.tar.gz', False),
		('libraw','http://www.libraw.org/data/LibRaw-0.13.1.tar.gz', False) if not windows else ('libraw', 'http://www.libraw.org/data/LibRaw-0.13.5.zip', False),
		('libcaca','http://caca.zoy.org/files/libcaca/libcaca-0.99.beta17.tar.gz', False),
		('ImageMagick','ftp://ftp.imagemagick.org/pub/ImageMagick/ImageMagick-6.6.9-7.tar.gz', False) if not windows else ('ImageMagick','ftp://ftp.imagemagick.org/pub/ImageMagick/ImageMagick-6.7.0-9.zip',False),
		('lcms','http://downloads.sourceforge.net/project/lcms/lcms/2.1/lcms2-2.1.tar.gz', False) if not windows else ('lcms', 'http://downloads.sourceforge.net/project/lcms/lcms/2.1/lcms2-2.1.zip',False),
		('bzlib','http://www.bzip.org/1.0.6/bzip2-1.0.6.tar.gz',False),
		('libtiff','ftp://ftp.remotesensing.org/pub/libtiff/tiff-3.9.5.tar.gz', False) if not windows else ('libtiff','ftp://ftp.remotesensing.org/pub/libtiff/tiff-3.9.5.zip', False),
		('libtool','ftp://ftp.gnu.org/gnu/libtool/libtool-2.4.tar.gz',False),
		('libxml','ftp://xmlsoft.org/libxml2/libxml2-2.7.8.tar.gz',False) if not windows else ('libxml','ftp://xmlsoft.org/libxml2/win32/libxml2-2.7.7.win32.zip',False),
		('jasper','http://www.ece.uvic.ca/~mdadams/jasper/software/jasper-1.900.1.zip',False),
		('xz','http://tukaani.org/xz/xz-5.0.2.tar.gz', False),
                ('gvc','http://www.graphviz.org/pub/graphviz/stable/SOURCES/graphviz-2.26.3.tar.gz',False),
                ('libliquidrescale', 'http://liblqr.wikidot.com/local--files/en:download-page/liblqr-1-0.4.1.tar.bz2', False)
	]


def insertInFile( filename, linesIndexes, textToAppend ):
	file = open( filename , 'r' )
	fileTmp = open( 'tmp.txt' , 'w' )
	lines = file.readlines()

	nlist = list( lines )

	index = 0;

	for lineIndex in linesIndexes:
		nlist.insert( lineIndex , textToAppend[index]+'\n' )
		index+=1
	fileTmp.writelines( nlist )

	file.close()
	fileTmp.close()
	os.remove(filename)
	os.rename('tmp.txt', filename)
	#os.remove('tmp.txt')


if len( sys.argv ) == 1:
	getAndUncompress( allLibs )
else:
	libDic = {}
	for lib in allLibs:
		libDic[lib[0]] = lib
	
	for libname in sys.argv[1:]:
		getAndUncompress( [libDic[libname]] )

print '_'*80
print '-'*29 + ' Files modifications  ' + '-'*29

print "ctl/IlmCtl/CtlLex.cpp"
insertInFile("ctl/IlmCtl/CtlLex.cpp", (1, 63) , ("", "#include <cstdlib>" ) )
print "ctl/IlmCtlSimd/CtlSimdReg.cpp"
insertInFile("ctl/IlmCtlSimd/CtlSimdReg.cpp", (1, 58) , ( "", "#include <cstring>" ) )

print 'End of initialisation.'




