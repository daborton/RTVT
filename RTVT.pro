QT += opengl \
    multimedia \
    xml \
    xmlpatterns
HEADERS += rtvtmainwindow.h \
    rtvtdataobject.h \
    rtvtwaveviewerglwidget.h \
    rtvtglobaldefinitions.h \
    rtvtchannelwidget.h \
    rtvtfiltercontroller.h \
    rtvtmockdatatransfer.h \
    rtvtcontinuousviewerwidget.h \
    multipagewidget.h \
    HUD_Plugins/rtvthudwaveview.h \
    HUD_Plugins/rtvthudcontrollerview.h \
    data_handling_plugins/bNEVwr.h \
    Filtering/FirKernels.h \
    RTVTTimer.h \
    External-Code/audiooutput.h \
    universalStructures.h \
    rtvttriggermodel.h \
    rtvtcontrolwindow.h \
    External-Code/utils.h \
    rtvtplotwindow.h
SOURCES += rtvtmainwindow.cpp \
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
    rtvtplotwindow.cpp
OTHER_FILES += Task_List.txt \
    qss/rtvthuddockstyle.qss \
    Filtering/null_filter.txt
FORMS += HUD_Plugins/rtvthudwaveview.ui \
    HUD_Plugins/rtvthudcontrollerview.ui \
    rtvtcontrolwindow.ui \
    rtvtplotwindow.ui
CONFIG += qwt

# LIBS += -F$${QWT_ROOT}/lib
qtAddLibrary(qwt)

# LIBS += -L/usr/local/qwt-6.0.1-svn/lib/qwt.framework/ -lqwt
# INCLUDEPATH += /usr/local/qwt-6.0.1-svn/lib/qwt.framework/Headers/
fftreal_dir = /Library/Frameworks/fftreal.framework/Headers/
LIBS += -F$${fftreal_dir}
LIBS += -framework \
    fftreal
QtSvgDir = /Library/Frameworks/QtSvg.framework/
LIBS += -F$${QtSvgDir}
LIBS += -framework \
    QtSvg
