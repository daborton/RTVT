#############################################################################
# Makefile for building: RTVT.app/Contents/MacOS/RTVT
# Generated by qmake (2.01a) (Qt 4.7.3) on: Tue Jan 31 13:36:55 2012
# Project:  RTVT.pro
# Template: app
# Command: /usr/bin/qmake -spec /usr/local/Qt4.7/mkspecs/macx-g++ -o Makefile RTVT.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_MULTIMEDIA_LIB -DQT_XMLPATTERNS_LIB -DQT_XML_LIB -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -gdwarf-2 -Wall -W $(DEFINES)
CXXFLAGS      = -pipe -g -gdwarf-2 -Wall -W $(DEFINES)
INCPATH       = -I/usr/local/Qt4.7/mkspecs/macx-g++ -I. -I/Library/Frameworks/QtCore.framework/Versions/4/Headers -I/usr/include/QtCore -I/Library/Frameworks/QtGui.framework/Versions/4/Headers -I/usr/include/QtGui -I/Library/Frameworks/QtOpenGL.framework/Versions/4/Headers -I/usr/include/QtOpenGL -I/Library/Frameworks/QtXml.framework/Versions/4/Headers -I/usr/include/QtXml -I/Library/Frameworks/QtXmlPatterns.framework/Versions/4/Headers -I/usr/include/QtXmlPatterns -I/Library/Frameworks/QtMultimedia.framework/Versions/4/Headers -I/usr/include/QtMultimedia -I/usr/include -I/Library/Frameworks/qwt.framework/Versions/6/Headers -I/usr/include/qwt -I/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers -I/System/Library/Frameworks/AGL.framework/Headers -I. -I. -F/Library/Frameworks
LINK          = g++
LFLAGS        = -headerpad_max_install_names
LIBS          = $(SUBLIBS) -F/Library/Frameworks -L/Library/Frameworks -framework qwt -F/Library/Frameworks/fftreal.framework/Headers/ -framework fftreal -F/Library/Frameworks/QtSvg.framework/ -framework QtSvg -framework QtGui -framework QtCore -framework QtMultimedia -framework ApplicationServices -framework CoreAudio -framework AudioUnit -framework AudioToolbox -framework QtXmlPatterns -framework QtNetwork -framework QtXml -framework QtOpenGL -framework OpenGL -framework AGL 
AR            = ar cq
RANLIB        = ranlib -s
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
STRIP         = 
INSTALL_FILE  = $(COPY_FILE)
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = $(COPY_FILE)
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
export MACOSX_DEPLOYMENT_TARGET = 10.4

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = rtvtmainwindow.cpp \
		main.cpp \
		rtvtwaveviewerglwidget.cpp \
		rtvtdataobject.cpp \
		rtvtchannelwidget.cpp \
		rtvtfiltercontroller.cpp \
		rtvtmockdatatransfer.cpp \
		rtvtcontinuousviewerwidget.cpp \
		multipagewidget.cpp \
		HUD_Plugins/rtvthudwaveview.cpp \
		HUD_Plugins/rtvthudcontrollerview.cpp \
		data_handling_plugins/bNEVwr.cpp \
		Filtering/FirKernels.cpp \
		RTVTTimer.cpp \
		External-Code/audiooutput.cpp \
		rtvttriggermodel.cpp \
		rtvtcontrolwindow.cpp \
		External-Code/utils.cpp \
		rtvtplotwindow.cpp moc_rtvtmainwindow.cpp \
		moc_rtvtwaveviewerglwidget.cpp \
		moc_rtvtchannelwidget.cpp \
		moc_rtvtcontinuousviewerwidget.cpp \
		moc_multipagewidget.cpp \
		moc_rtvthudwaveview.cpp \
		moc_rtvthudcontrollerview.cpp \
		moc_FirKernels.cpp \
		moc_audiooutput.cpp \
		moc_rtvttriggermodel.cpp \
		moc_rtvtcontrolwindow.cpp \
		moc_rtvtplotwindow.cpp
OBJECTS       = rtvtmainwindow.o \
		main.o \
		rtvtwaveviewerglwidget.o \
		rtvtdataobject.o \
		rtvtchannelwidget.o \
		rtvtfiltercontroller.o \
		rtvtmockdatatransfer.o \
		rtvtcontinuousviewerwidget.o \
		multipagewidget.o \
		rtvthudwaveview.o \
		rtvthudcontrollerview.o \
		bNEVwr.o \
		FirKernels.o \
		RTVTTimer.o \
		audiooutput.o \
		rtvttriggermodel.o \
		rtvtcontrolwindow.o \
		utils.o \
		rtvtplotwindow.o \
		moc_rtvtmainwindow.o \
		moc_rtvtwaveviewerglwidget.o \
		moc_rtvtchannelwidget.o \
		moc_rtvtcontinuousviewerwidget.o \
		moc_multipagewidget.o \
		moc_rtvthudwaveview.o \
		moc_rtvthudcontrollerview.o \
		moc_FirKernels.o \
		moc_audiooutput.o \
		moc_rtvttriggermodel.o \
		moc_rtvtcontrolwindow.o \
		moc_rtvtplotwindow.o
DIST          = /usr/local/Qt4.7/mkspecs/common/unix.conf \
		/usr/local/Qt4.7/mkspecs/common/mac.conf \
		/usr/local/Qt4.7/mkspecs/common/mac-g++.conf \
		/usr/local/Qt4.7/mkspecs/qconfig.pri \
		/usr/local/Qt4.7/mkspecs/modules/qt_webkit_version.pri \
		/usr/local/Qt4.7/mkspecs/features/qt_functions.prf \
		/usr/local/Qt4.7/mkspecs/features/qt_config.prf \
		/usr/local/Qt4.7/mkspecs/features/exclusive_builds.prf \
		/usr/local/Qt4.7/mkspecs/features/default_pre.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/default_pre.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/dwarf2.prf \
		/usr/local/Qt4.7/mkspecs/features/debug.prf \
		/usr/local/Qt4.7/mkspecs/features/default_post.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/default_post.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/objective_c.prf \
		/usr/local/Qt4.7/mkspecs/features/warn_on.prf \
		/usr/local/Qt4.7/mkspecs/features/qt.prf \
		/usr/local/Qt4.7/mkspecs/features/unix/opengl.prf \
		/usr/local/Qt4.7/mkspecs/features/unix/thread.prf \
		/usr/local/Qt4.7/mkspecs/features/moc.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/rez.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/sdk.prf \
		/usr/local/Qt4.7/mkspecs/features/resources.prf \
		/usr/local/Qt4.7/mkspecs/features/uic.prf \
		/usr/local/Qt4.7/mkspecs/features/yacc.prf \
		/usr/local/Qt4.7/mkspecs/features/lex.prf \
		/usr/local/Qt4.7/mkspecs/features/include_source_dir.prf \
		RTVT.pro
QMAKE_TARGET  = RTVT
DESTDIR       = 
TARGET        = RTVT.app/Contents/MacOS/RTVT

####### Custom Compiler Variables
QMAKE_COMP_QMAKE_OBJECTIVE_CFLAGS = -pipe \
		-g \
		-gdwarf-2 \
		-Wall \
		-W


first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile RTVT.app/Contents/PkgInfo RTVT.app/Contents/Resources/empty.lproj RTVT.app/Contents/Info.plist $(TARGET)

$(TARGET): ui_rtvthudwaveview.h ui_rtvthudcontrollerview.h ui_rtvtcontrolwindow.h ui_rtvtplotwindow.h $(OBJECTS)  
	@$(CHK_DIR_EXISTS) RTVT.app/Contents/MacOS/ || $(MKDIR) RTVT.app/Contents/MacOS/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: RTVT.pro  /usr/local/Qt4.7/mkspecs/macx-g++/qmake.conf /usr/local/Qt4.7/mkspecs/common/unix.conf \
		/usr/local/Qt4.7/mkspecs/common/mac.conf \
		/usr/local/Qt4.7/mkspecs/common/mac-g++.conf \
		/usr/local/Qt4.7/mkspecs/qconfig.pri \
		/usr/local/Qt4.7/mkspecs/modules/qt_webkit_version.pri \
		/usr/local/Qt4.7/mkspecs/features/qt_functions.prf \
		/usr/local/Qt4.7/mkspecs/features/qt_config.prf \
		/usr/local/Qt4.7/mkspecs/features/exclusive_builds.prf \
		/usr/local/Qt4.7/mkspecs/features/default_pre.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/default_pre.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/dwarf2.prf \
		/usr/local/Qt4.7/mkspecs/features/debug.prf \
		/usr/local/Qt4.7/mkspecs/features/default_post.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/default_post.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/objective_c.prf \
		/usr/local/Qt4.7/mkspecs/features/warn_on.prf \
		/usr/local/Qt4.7/mkspecs/features/qt.prf \
		/usr/local/Qt4.7/mkspecs/features/unix/opengl.prf \
		/usr/local/Qt4.7/mkspecs/features/unix/thread.prf \
		/usr/local/Qt4.7/mkspecs/features/moc.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/rez.prf \
		/usr/local/Qt4.7/mkspecs/features/mac/sdk.prf \
		/usr/local/Qt4.7/mkspecs/features/resources.prf \
		/usr/local/Qt4.7/mkspecs/features/uic.prf \
		/usr/local/Qt4.7/mkspecs/features/yacc.prf \
		/usr/local/Qt4.7/mkspecs/features/lex.prf \
		/usr/local/Qt4.7/mkspecs/features/include_source_dir.prf \
		/Library/Frameworks/QtSvg.framework/QtSvg.prl \
		/Library/Frameworks/QtGui.framework/QtGui.prl \
		/Library/Frameworks/QtCore.framework/QtCore.prl \
		/Library/Frameworks/QtMultimedia.framework/QtMultimedia.prl \
		/Library/Frameworks/QtXmlPatterns.framework/QtXmlPatterns.prl \
		/Library/Frameworks/QtNetwork.framework/QtNetwork.prl \
		/Library/Frameworks/QtXml.framework/QtXml.prl \
		/Library/Frameworks/QtOpenGL.framework/QtOpenGL.prl
	$(QMAKE) -spec /usr/local/Qt4.7/mkspecs/macx-g++ -o Makefile RTVT.pro
/usr/local/Qt4.7/mkspecs/common/unix.conf:
/usr/local/Qt4.7/mkspecs/common/mac.conf:
/usr/local/Qt4.7/mkspecs/common/mac-g++.conf:
/usr/local/Qt4.7/mkspecs/qconfig.pri:
/usr/local/Qt4.7/mkspecs/modules/qt_webkit_version.pri:
/usr/local/Qt4.7/mkspecs/features/qt_functions.prf:
/usr/local/Qt4.7/mkspecs/features/qt_config.prf:
/usr/local/Qt4.7/mkspecs/features/exclusive_builds.prf:
/usr/local/Qt4.7/mkspecs/features/default_pre.prf:
/usr/local/Qt4.7/mkspecs/features/mac/default_pre.prf:
/usr/local/Qt4.7/mkspecs/features/mac/dwarf2.prf:
/usr/local/Qt4.7/mkspecs/features/debug.prf:
/usr/local/Qt4.7/mkspecs/features/default_post.prf:
/usr/local/Qt4.7/mkspecs/features/mac/default_post.prf:
/usr/local/Qt4.7/mkspecs/features/mac/objective_c.prf:
/usr/local/Qt4.7/mkspecs/features/warn_on.prf:
/usr/local/Qt4.7/mkspecs/features/qt.prf:
/usr/local/Qt4.7/mkspecs/features/unix/opengl.prf:
/usr/local/Qt4.7/mkspecs/features/unix/thread.prf:
/usr/local/Qt4.7/mkspecs/features/moc.prf:
/usr/local/Qt4.7/mkspecs/features/mac/rez.prf:
/usr/local/Qt4.7/mkspecs/features/mac/sdk.prf:
/usr/local/Qt4.7/mkspecs/features/resources.prf:
/usr/local/Qt4.7/mkspecs/features/uic.prf:
/usr/local/Qt4.7/mkspecs/features/yacc.prf:
/usr/local/Qt4.7/mkspecs/features/lex.prf:
/usr/local/Qt4.7/mkspecs/features/include_source_dir.prf:
/Library/Frameworks/QtSvg.framework/QtSvg.prl:
/Library/Frameworks/QtGui.framework/QtGui.prl:
/Library/Frameworks/QtCore.framework/QtCore.prl:
/Library/Frameworks/QtMultimedia.framework/QtMultimedia.prl:
/Library/Frameworks/QtXmlPatterns.framework/QtXmlPatterns.prl:
/Library/Frameworks/QtNetwork.framework/QtNetwork.prl:
/Library/Frameworks/QtXml.framework/QtXml.prl:
/Library/Frameworks/QtOpenGL.framework/QtOpenGL.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/local/Qt4.7/mkspecs/macx-g++ -o Makefile RTVT.pro

RTVT.app/Contents/PkgInfo: 
	@$(CHK_DIR_EXISTS) RTVT.app/Contents || $(MKDIR) RTVT.app/Contents 
	@$(DEL_FILE) RTVT.app/Contents/PkgInfo
	@echo "APPL????" >RTVT.app/Contents/PkgInfo
RTVT.app/Contents/Resources/empty.lproj: 
	@$(CHK_DIR_EXISTS) RTVT.app/Contents/Resources || $(MKDIR) RTVT.app/Contents/Resources 
	@touch RTVT.app/Contents/Resources/empty.lproj
	
RTVT.app/Contents/Info.plist: 
	@$(CHK_DIR_EXISTS) RTVT.app/Contents || $(MKDIR) RTVT.app/Contents 
	@$(DEL_FILE) RTVT.app/Contents/Info.plist
	@sed -e "s,@ICON@,,g" -e "s,@EXECUTABLE@,RTVT,g" -e "s,@TYPEINFO@,????,g" /usr/local/Qt4.7/mkspecs/macx-g++/Info.plist.app >RTVT.app/Contents/Info.plist
dist: 
	@$(CHK_DIR_EXISTS) .tmp/RTVT1.0.0 || $(MKDIR) .tmp/RTVT1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/RTVT1.0.0/ && $(COPY_FILE) --parents rtvtmainwindow.h rtvtdataobject.h rtvtwaveviewerglwidget.h rtvtglobaldefinitions.h rtvtchannelwidget.h rtvtfiltercontroller.h rtvtmockdatatransfer.h rtvtcontinuousviewerwidget.h multipagewidget.h HUD_Plugins/rtvthudwaveview.h HUD_Plugins/rtvthudcontrollerview.h data_handling_plugins/bNEVwr.h Filtering/FirKernels.h RTVTTimer.h External-Code/audiooutput.h universalStructures.h rtvttriggermodel.h rtvtcontrolwindow.h External-Code/utils.h rtvtplotwindow.h .tmp/RTVT1.0.0/ && $(COPY_FILE) --parents rtvtmainwindow.cpp main.cpp rtvtwaveviewerglwidget.cpp rtvtdataobject.cpp rtvtchannelwidget.cpp rtvtfiltercontroller.cpp rtvtmockdatatransfer.cpp rtvtcontinuousviewerwidget.cpp multipagewidget.cpp HUD_Plugins/rtvthudwaveview.cpp HUD_Plugins/rtvthudcontrollerview.cpp data_handling_plugins/bNEVwr.cpp Filtering/FirKernels.cpp RTVTTimer.cpp External-Code/audiooutput.cpp rtvttriggermodel.cpp rtvtcontrolwindow.cpp External-Code/utils.cpp rtvtplotwindow.cpp .tmp/RTVT1.0.0/ && $(COPY_FILE) --parents HUD_Plugins/rtvthudwaveview.ui HUD_Plugins/rtvthudcontrollerview.ui rtvtcontrolwindow.ui rtvtplotwindow.ui .tmp/RTVT1.0.0/ && (cd `dirname .tmp/RTVT1.0.0` && $(TAR) RTVT1.0.0.tar RTVT1.0.0 && $(COMPRESS) RTVT1.0.0.tar) && $(MOVE) `dirname .tmp/RTVT1.0.0`/RTVT1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/RTVT1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) -r RTVT.app
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_objective_c_make_all:
compiler_objective_c_clean:
compiler_moc_header_make_all: moc_rtvtmainwindow.cpp moc_rtvtwaveviewerglwidget.cpp moc_rtvtchannelwidget.cpp moc_rtvtcontinuousviewerwidget.cpp moc_multipagewidget.cpp moc_rtvthudwaveview.cpp moc_rtvthudcontrollerview.cpp moc_FirKernels.cpp moc_audiooutput.cpp moc_rtvttriggermodel.cpp moc_rtvtcontrolwindow.cpp moc_rtvtplotwindow.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_rtvtmainwindow.cpp moc_rtvtwaveviewerglwidget.cpp moc_rtvtchannelwidget.cpp moc_rtvtcontinuousviewerwidget.cpp moc_multipagewidget.cpp moc_rtvthudwaveview.cpp moc_rtvthudcontrollerview.cpp moc_FirKernels.cpp moc_audiooutput.cpp moc_rtvttriggermodel.cpp moc_rtvtcontrolwindow.cpp moc_rtvtplotwindow.cpp
moc_rtvtmainwindow.cpp: rtvtchannelwidget.h \
		rtvtcontinuousviewerwidget.h \
		rtvtglobaldefinitions.h \
		rtvtwaveviewerglwidget.h \
		universalStructures.h \
		External-Code/fftreal_wrapper.h \
		External-Code/utils.h \
		rtvtdataobject.h \
		cpshsusbhardwareabstractionlayer.h \
		cyapi.h \
		RTVTTimer.h \
		multipagewidget.h \
		HUD_Plugins/rtvthudcontrollerview.h \
		HUD_Plugins/rtvthudwaveview.h \
		rtvttriggermodel.h \
		data_handling_plugins/bNEVwr.h \
		External-Code/audiooutput.h \
		Filtering/FirKernels.h \
		rtvtmainwindow.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ rtvtmainwindow.h -o moc_rtvtmainwindow.cpp

moc_rtvtwaveviewerglwidget.cpp: universalStructures.h \
		rtvtglobaldefinitions.h \
		rtvtwaveviewerglwidget.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ rtvtwaveviewerglwidget.h -o moc_rtvtwaveviewerglwidget.cpp

moc_rtvtchannelwidget.cpp: rtvtcontinuousviewerwidget.h \
		rtvtglobaldefinitions.h \
		rtvtwaveviewerglwidget.h \
		universalStructures.h \
		External-Code/fftreal_wrapper.h \
		External-Code/utils.h \
		rtvtchannelwidget.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ rtvtchannelwidget.h -o moc_rtvtchannelwidget.cpp

moc_rtvtcontinuousviewerwidget.cpp: rtvtglobaldefinitions.h \
		rtvtcontinuousviewerwidget.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ rtvtcontinuousviewerwidget.h -o moc_rtvtcontinuousviewerwidget.cpp

moc_multipagewidget.cpp: multipagewidget.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ multipagewidget.h -o moc_multipagewidget.cpp

moc_rtvthudwaveview.cpp: rtvttriggermodel.h \
		rtvtwaveviewerglwidget.h \
		universalStructures.h \
		rtvtglobaldefinitions.h \
		HUD_Plugins/rtvthudwaveview.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ HUD_Plugins/rtvthudwaveview.h -o moc_rtvthudwaveview.cpp

moc_rtvthudcontrollerview.cpp: rtvtglobaldefinitions.h \
		HUD_Plugins/rtvthudcontrollerview.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ HUD_Plugins/rtvthudcontrollerview.h -o moc_rtvthudcontrollerview.cpp

moc_FirKernels.cpp: rtvtglobaldefinitions.h \
		Filtering/FirKernels.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ Filtering/FirKernels.h -o moc_FirKernels.cpp

moc_audiooutput.cpp: rtvtglobaldefinitions.h \
		External-Code/audiooutput.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ External-Code/audiooutput.h -o moc_audiooutput.cpp

moc_rtvttriggermodel.cpp: rtvtwaveviewerglwidget.h \
		universalStructures.h \
		rtvtglobaldefinitions.h \
		rtvttriggermodel.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ rtvttriggermodel.h -o moc_rtvttriggermodel.cpp

moc_rtvtcontrolwindow.cpp: rtvtglobaldefinitions.h \
		Filtering/FirKernels.h \
		rtvtmainwindow.h \
		rtvtchannelwidget.h \
		rtvtcontinuousviewerwidget.h \
		rtvtwaveviewerglwidget.h \
		universalStructures.h \
		External-Code/fftreal_wrapper.h \
		External-Code/utils.h \
		rtvtdataobject.h \
		cpshsusbhardwareabstractionlayer.h \
		cyapi.h \
		RTVTTimer.h \
		multipagewidget.h \
		HUD_Plugins/rtvthudcontrollerview.h \
		HUD_Plugins/rtvthudwaveview.h \
		rtvttriggermodel.h \
		data_handling_plugins/bNEVwr.h \
		External-Code/audiooutput.h \
		rtvtplotwindow.h \
		rtvtcontrolwindow.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ rtvtcontrolwindow.h -o moc_rtvtcontrolwindow.cpp

moc_rtvtplotwindow.cpp: External-Code/fftreal_wrapper.h \
		External-Code/utils.h \
		rtvtplotwindow.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ rtvtplotwindow.h -o moc_rtvtplotwindow.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_rez_source_make_all:
compiler_rez_source_clean:
compiler_uic_make_all: ui_rtvthudwaveview.h ui_rtvthudcontrollerview.h ui_rtvtcontrolwindow.h ui_rtvtplotwindow.h
compiler_uic_clean:
	-$(DEL_FILE) ui_rtvthudwaveview.h ui_rtvthudcontrollerview.h ui_rtvtcontrolwindow.h ui_rtvtplotwindow.h
ui_rtvthudwaveview.h: HUD_Plugins/rtvthudwaveview.ui
	/Developer/Tools/Qt/uic HUD_Plugins/rtvthudwaveview.ui -o ui_rtvthudwaveview.h

ui_rtvthudcontrollerview.h: HUD_Plugins/rtvthudcontrollerview.ui
	/Developer/Tools/Qt/uic HUD_Plugins/rtvthudcontrollerview.ui -o ui_rtvthudcontrollerview.h

ui_rtvtcontrolwindow.h: rtvtcontrolwindow.ui
	/Developer/Tools/Qt/uic rtvtcontrolwindow.ui -o ui_rtvtcontrolwindow.h

ui_rtvtplotwindow.h: rtvtplotwindow.ui
	/Developer/Tools/Qt/uic rtvtplotwindow.ui -o ui_rtvtplotwindow.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

rtvtmainwindow.o: rtvtmainwindow.cpp rtvtmainwindow.h \
		rtvtchannelwidget.h \
		rtvtcontinuousviewerwidget.h \
		rtvtglobaldefinitions.h \
		rtvtwaveviewerglwidget.h \
		universalStructures.h \
		External-Code/fftreal_wrapper.h \
		External-Code/utils.h \
		rtvtdataobject.h \
		cpshsusbhardwareabstractionlayer.h \
		cyapi.h \
		RTVTTimer.h \
		multipagewidget.h \
		HUD_Plugins/rtvthudcontrollerview.h \
		HUD_Plugins/rtvthudwaveview.h \
		rtvttriggermodel.h \
		data_handling_plugins/bNEVwr.h \
		External-Code/audiooutput.h \
		Filtering/FirKernels.h \
		External-Code/memcpy.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o rtvtmainwindow.o rtvtmainwindow.cpp

main.o: main.cpp rtvtmainwindow.h \
		rtvtchannelwidget.h \
		rtvtcontinuousviewerwidget.h \
		rtvtglobaldefinitions.h \
		rtvtwaveviewerglwidget.h \
		universalStructures.h \
		External-Code/fftreal_wrapper.h \
		External-Code/utils.h \
		rtvtdataobject.h \
		cpshsusbhardwareabstractionlayer.h \
		cyapi.h \
		RTVTTimer.h \
		multipagewidget.h \
		HUD_Plugins/rtvthudcontrollerview.h \
		HUD_Plugins/rtvthudwaveview.h \
		rtvttriggermodel.h \
		data_handling_plugins/bNEVwr.h \
		External-Code/audiooutput.h \
		Filtering/FirKernels.h \
		rtvtcontrolwindow.h \
		rtvtplotwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

rtvtwaveviewerglwidget.o: rtvtwaveviewerglwidget.cpp rtvtwaveviewerglwidget.h \
		universalStructures.h \
		rtvtglobaldefinitions.h \
		rtvtchannelwidget.h \
		rtvtcontinuousviewerwidget.h \
		External-Code/fftreal_wrapper.h \
		External-Code/utils.h \
		RTVTTimer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o rtvtwaveviewerglwidget.o rtvtwaveviewerglwidget.cpp

rtvtdataobject.o: rtvtdataobject.cpp rtvtdataobject.h \
		rtvtglobaldefinitions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o rtvtdataobject.o rtvtdataobject.cpp

rtvtchannelwidget.o: rtvtchannelwidget.cpp rtvtchannelwidget.h \
		rtvtcontinuousviewerwidget.h \
		rtvtglobaldefinitions.h \
		rtvtwaveviewerglwidget.h \
		universalStructures.h \
		External-Code/fftreal_wrapper.h \
		External-Code/utils.h \
		rtvtmainwindow.h \
		rtvtdataobject.h \
		cpshsusbhardwareabstractionlayer.h \
		cyapi.h \
		RTVTTimer.h \
		multipagewidget.h \
		HUD_Plugins/rtvthudcontrollerview.h \
		HUD_Plugins/rtvthudwaveview.h \
		rtvttriggermodel.h \
		data_handling_plugins/bNEVwr.h \
		External-Code/audiooutput.h \
		Filtering/FirKernels.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o rtvtchannelwidget.o rtvtchannelwidget.cpp

rtvtfiltercontroller.o: rtvtfiltercontroller.cpp rtvtfiltercontroller.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o rtvtfiltercontroller.o rtvtfiltercontroller.cpp

rtvtmockdatatransfer.o: rtvtmockdatatransfer.cpp rtvtmockdatatransfer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o rtvtmockdatatransfer.o rtvtmockdatatransfer.cpp

rtvtcontinuousviewerwidget.o: rtvtcontinuousviewerwidget.cpp rtvtcontinuousviewerwidget.h \
		rtvtglobaldefinitions.h \
		rtvtchannelwidget.h \
		rtvtwaveviewerglwidget.h \
		universalStructures.h \
		External-Code/fftreal_wrapper.h \
		External-Code/utils.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o rtvtcontinuousviewerwidget.o rtvtcontinuousviewerwidget.cpp

multipagewidget.o: multipagewidget.cpp multipagewidget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o multipagewidget.o multipagewidget.cpp

rtvthudwaveview.o: HUD_Plugins/rtvthudwaveview.cpp HUD_Plugins/rtvthudwaveview.h \
		rtvttriggermodel.h \
		rtvtwaveviewerglwidget.h \
		universalStructures.h \
		rtvtglobaldefinitions.h \
		ui_rtvthudwaveview.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o rtvthudwaveview.o HUD_Plugins/rtvthudwaveview.cpp

rtvthudcontrollerview.o: HUD_Plugins/rtvthudcontrollerview.cpp HUD_Plugins/rtvthudcontrollerview.h \
		rtvtglobaldefinitions.h \
		ui_rtvthudcontrollerview.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o rtvthudcontrollerview.o HUD_Plugins/rtvthudcontrollerview.cpp

bNEVwr.o: data_handling_plugins/bNEVwr.cpp data_handling_plugins/bNEVwr.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o bNEVwr.o data_handling_plugins/bNEVwr.cpp

FirKernels.o: Filtering/FirKernels.cpp Filtering/FirKernels.h \
		rtvtglobaldefinitions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o FirKernels.o Filtering/FirKernels.cpp

RTVTTimer.o: RTVTTimer.cpp RTVTTimer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o RTVTTimer.o RTVTTimer.cpp

audiooutput.o: External-Code/audiooutput.cpp External-Code/audiooutput.h \
		rtvtglobaldefinitions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o audiooutput.o External-Code/audiooutput.cpp

rtvttriggermodel.o: rtvttriggermodel.cpp rtvttriggermodel.h \
		rtvtwaveviewerglwidget.h \
		universalStructures.h \
		rtvtglobaldefinitions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o rtvttriggermodel.o rtvttriggermodel.cpp

rtvtcontrolwindow.o: rtvtcontrolwindow.cpp rtvtcontrolwindow.h \
		rtvtglobaldefinitions.h \
		Filtering/FirKernels.h \
		rtvtmainwindow.h \
		rtvtchannelwidget.h \
		rtvtcontinuousviewerwidget.h \
		rtvtwaveviewerglwidget.h \
		universalStructures.h \
		External-Code/fftreal_wrapper.h \
		External-Code/utils.h \
		rtvtdataobject.h \
		cpshsusbhardwareabstractionlayer.h \
		cyapi.h \
		RTVTTimer.h \
		multipagewidget.h \
		HUD_Plugins/rtvthudcontrollerview.h \
		HUD_Plugins/rtvthudwaveview.h \
		rtvttriggermodel.h \
		data_handling_plugins/bNEVwr.h \
		External-Code/audiooutput.h \
		rtvtplotwindow.h \
		ui_rtvtcontrolwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o rtvtcontrolwindow.o rtvtcontrolwindow.cpp

utils.o: External-Code/utils.cpp External-Code/utils.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o utils.o External-Code/utils.cpp

rtvtplotwindow.o: rtvtplotwindow.cpp rtvtplotwindow.h \
		External-Code/fftreal_wrapper.h \
		External-Code/utils.h \
		ui_rtvtplotwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o rtvtplotwindow.o rtvtplotwindow.cpp

moc_rtvtmainwindow.o: moc_rtvtmainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_rtvtmainwindow.o moc_rtvtmainwindow.cpp

moc_rtvtwaveviewerglwidget.o: moc_rtvtwaveviewerglwidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_rtvtwaveviewerglwidget.o moc_rtvtwaveviewerglwidget.cpp

moc_rtvtchannelwidget.o: moc_rtvtchannelwidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_rtvtchannelwidget.o moc_rtvtchannelwidget.cpp

moc_rtvtcontinuousviewerwidget.o: moc_rtvtcontinuousviewerwidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_rtvtcontinuousviewerwidget.o moc_rtvtcontinuousviewerwidget.cpp

moc_multipagewidget.o: moc_multipagewidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_multipagewidget.o moc_multipagewidget.cpp

moc_rtvthudwaveview.o: moc_rtvthudwaveview.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_rtvthudwaveview.o moc_rtvthudwaveview.cpp

moc_rtvthudcontrollerview.o: moc_rtvthudcontrollerview.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_rtvthudcontrollerview.o moc_rtvthudcontrollerview.cpp

moc_FirKernels.o: moc_FirKernels.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_FirKernels.o moc_FirKernels.cpp

moc_audiooutput.o: moc_audiooutput.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_audiooutput.o moc_audiooutput.cpp

moc_rtvttriggermodel.o: moc_rtvttriggermodel.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_rtvttriggermodel.o moc_rtvttriggermodel.cpp

moc_rtvtcontrolwindow.o: moc_rtvtcontrolwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_rtvtcontrolwindow.o moc_rtvtcontrolwindow.cpp

moc_rtvtplotwindow.o: moc_rtvtplotwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_rtvtplotwindow.o moc_rtvtplotwindow.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

